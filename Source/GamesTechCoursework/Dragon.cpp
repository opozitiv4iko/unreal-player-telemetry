// Fill out your copyright notice in the Description page of Project Settings.


#include "Dragon.h"
#include "Kismet/GameplayStatics.h"
#include "TriggerRegion.h"
#include "FPSCharacter.h"
#include "Enemies.h"

// Sets default values
ADragon::ADragon()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADragon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADragon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADragon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Function to initiate a dragon attack on the player character.
void ADragon::DragonAttack()
{
	// Get a reference to the player character.
	AFPSCharacter* PPlayer = Cast<AFPSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    
	// Inflict damage on the player character.
	PPlayer->TakeDamage(5.0f, EEnemies::Dragon);
}

// Function to handle the dragon taking damage.
void ADragon::TakeDamage(float A_FDamage)
{
	// Decrease the dragon's health based on the amount of damage received.
	M_FHealth -= A_FDamage;

	// Check if the dragon's health has reached zero or below.
	if (M_FHealth <= 0)
	{
		// If the dragon's health is depleted, trigger the Die function.
		Die();
	}
}

// Function to handle the dragon's death.
void ADragon::Die()
{
	// Destroy the dragon actor.
	Destroy();
}

void ADragon::Reset()
{
	//Super::Reset();
}

