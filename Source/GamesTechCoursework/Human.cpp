// Fill out your copyright notice in the Description page of Project Settings.


#include "Human.h"
#include "Kismet/GameplayStatics.h"
#include "FPSCharacter.h"
#include "Enemies.h"

// Sets default values
AHuman::AHuman()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHuman::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHuman::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHuman::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AHuman::HumanAttack()
{
	AFPSCharacter* PPlayer = Cast<AFPSCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	PPlayer->TakeDamage(10.0f, EEnemies::Human);
}

void AHuman::TakeDamage(float A_FDamage)
{
	// Deal Damage
	M_FHealth -= A_FDamage;

	// Death handling
	if (M_FHealth <= 0)
	{
		Die();
	}
}

void AHuman::Die()
{
	Destroy();
}

void AHuman::Reset()
{
	//Super::Reset();
}

