// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_WeaponComponent.h"
#include "FPSCharacter.h"
#include "GamesTechCourseworkProjectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Panda.h"
#include "Dragon.h"
#include "Human.h"

// Sets default values for this component's properties
UTP_WeaponComponent::UTP_WeaponComponent()
{
}

void UTP_WeaponComponent::Fire()
{
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}

	// Try and line trace
	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
		if (PlayerController == nullptr || PlayerController->PlayerCameraManager == nullptr)
		{
			return;
		}

		const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
		const FVector CameraLocation = PlayerController->PlayerCameraManager->GetCameraLocation();
		const FVector StartLocation = CameraLocation + SpawnRotation.Vector() * M_VMuzzleOffset.Z; // Offset from camera along Z axis

		// Set up Query params
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(Character); // Ignoring the character during line tracing

		// Set up hit result
		FHitResult OutHit;

		// Line Trace
		const FVector EndLocation = StartLocation + SpawnRotation.Vector() * 3000; // End Line point
		World->LineTraceSingleByChannel(OutHit, StartLocation, EndLocation, ECC_Pawn, QueryParams);
		//DrawDebugLine(World, StartLocation, EndLocation, FColor::Blue, false, 5.f, 5, 5.f );

		// Try to cast hit to an enemy
		APanda* PPanda = Cast<APanda>(OutHit.GetActor());
		if (PPanda)
		{
			PPanda->TakeDamage(3.0f);
		}

		ADragon* PDragon = Cast<ADragon>(OutHit.GetActor());
		if (PDragon)
		{
			PDragon->TakeDamage(3.0f);
		}

		AHuman* PHuman = Cast<AHuman>(OutHit.GetActor());
		if (PHuman)
		{
			PHuman->TakeDamage(3.0f);
		}

		
		// Play and play sound if specified
		if (M_PFireSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, M_PFireSound, StartLocation);
		}

		// Try and spawn muzzle flash particle system
		if (M_PMuzzleFlash != nullptr)
		{

			UNiagaraFunctionLibrary::SpawnSystemAtLocation(World, M_PMuzzleFlash, StartLocation, SpawnRotation);
		}
		
	}
}

void UTP_WeaponComponent::AttachWeapon(AFPSCharacter* TargetCharacter)
{
	if (TargetCharacter == nullptr)
	{
		return;
	}
	
	Character = TargetCharacter;
	if (Character == nullptr)
	{
		return;
	}

	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));

	// Set up action bindings
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->AddMappingContext(FireMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			// Fire
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UTP_WeaponComponent::Fire);
		}
	}
}

void UTP_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Character == nullptr)
	{
		return;
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(FireMappingContext);
		}
	}
}
