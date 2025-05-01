// Fill out your copyright notice in the Description page of Project Settings.


#include "Panda.h"
#include "Kismet/GameplayStatics.h"
#include "FPSCharacter.h"
#include "Enemies.h"

// Sets default values
APanda::APanda()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APanda::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APanda::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APanda::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APanda::PandaAttack()
{
	AFPSCharacter* PPlayer = Cast<AFPSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	PPlayer->TakeDamage(2.0f, EEnemies::Panda);
}

void APanda::TakeDamage(float A_FDamage)
{
	// Deal Damage
	M_FHealth -= A_FDamage;

	// Death handling
	if (M_FHealth <= 0)
	{
		Die();
	}
		
}

void APanda::Die()
{
	Destroy();
}

void APanda::Reset()
{
	//Super::Reset();
}

