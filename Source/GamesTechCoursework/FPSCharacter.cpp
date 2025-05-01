// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "TP_WeaponComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "DataBase.h"
#include "TriggerRegion.h"
#include "Engine/TriggerBase.h"


//////////////////////////////////////////////////////////////////////////
// AGamesTechCourseworkCharacter

AFPSCharacter::AFPSCharacter()
{
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
	
}


void AFPSCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	
	
	EquipWeapon();
	
	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	
	//Add the HUD to our viewport
	if (M_CPlayerHUD != nullptr)
	{
		UUserWidget* HUD = CreateWidget<UUserWidget>(Cast<APlayerController>(GetController()),M_CPlayerHUD);
		HUD->AddToViewport(9999);
	}

	
	
}

//////////////////////////////////////////////////////////////////////////// Input

void AFPSCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFPSCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFPSCharacter::Look);

		//Fire
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AFPSCharacter::Shoot);
	}
}


void AFPSCharacter::TakeDamage(float A_FDamage, EEnemies Damager)
{
	TArray<AActor*> OverlappingActors;
	ATriggerRegion* TriggerRegion = nullptr;
	
	// Deal damage
	M_FHealth -= A_FDamage;

	// Get Player Region
	this->GetOverlappingActors(OverlappingActors, ATriggerRegion::StaticClass());
	for (AActor* Actor : OverlappingActors)
	{
		TriggerRegion = Cast<ATriggerRegion>(Actor);
		if (TriggerRegion)
			break;
	}

	// Get all actors of type ADataBase
	TArray<AActor*>Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADataBase::StaticClass(), Actors);

	// Cast the first actor to ADataBase
	ADataBase* DataBase = static_cast<ADataBase*>(Actors[0]);
	
	DataBase->LogPlayerDamage(static_cast<ERegion>(**TriggerRegion->RegionName), Damager, M_FHealth<= 0, A_FDamage);
	
	// Death handling
	if (M_FHealth <= 0)
	{
		Die();
	}
}

void AFPSCharacter::Die()
{
	TArray<AActor*>Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADataBase::StaticClass(), Actors);
	ADataBase* DataBase = static_cast<ADataBase*>(Actors[0]);

	// Print info about death statistics 
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Killed by Panda: %llu"), DataBase->CountDeathsByDamager(EEnemies::Panda)));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Killed by Dragon: %llu"), DataBase->CountDeathsByDamager(EEnemies::Dragon)));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Killed by Human: %llu"), DataBase->CountDeathsByDamager(EEnemies::Human)));
	}

	//Restarting the Level
	UGameplayStatics::OpenLevel(GetWorld(), FName(GetWorld()->GetName()), true);
	
}

void AFPSCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AFPSCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AFPSCharacter::Shoot(const FInputActionValue& Value)
{
	// Get the animation instance of the first person mesh
	UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance(); 
	if (AnimInstance !=nullptr)
	{
		// If the fire montage is valid, play it
		if (M_PFireMontage != nullptr)
		{
			AnimInstance->Montage_Play(M_PFireMontage);
		}
	}

}


void AFPSCharacter::EquipWeapon()
{
	// Get the player controller
	APlayerController* PController = Cast<APlayerController>(GetController());

	// Get the camera rotation and the owner's location
	const FRotator PRotation = PController->PlayerCameraManager->GetCameraRotation();
	const FVector PLocation = GetOwner()->GetActorLocation();

	// Set up spawn parameters
	FActorSpawnParameters PSpawnParams;
	PSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// Spawn the weapon actor at the owner's location with the camera rotation
	AActor* PGun= GetWorld()->SpawnActor<AActor>(M_CGun, PLocation, PRotation, PSpawnParams);

	// Attach the weapon component to the character
	UTP_WeaponComponent* PWeapon = Cast<UTP_WeaponComponent>(PGun->GetComponentByClass(UTP_WeaponComponent::StaticClass()));
	PWeapon->AttachWeapon(this);
}
