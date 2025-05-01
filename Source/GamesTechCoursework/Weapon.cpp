// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	M_PMesh = CreateDefaultSubobject<UStaticMeshComponent>("Weapon Mesh");
	M_PMesh->SetupAttachment(RootComponent);

	M_PWeaponComponent = CreateDefaultSubobject<UTP_WeaponComponent>("Weapon Component");
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	// Assign weapon component variables
	M_PWeaponComponent->M_PFireSound = M_PFireSound;
	M_PWeaponComponent->M_VMuzzleOffset = M_VMuzzleOffset;
	M_PWeaponComponent->M_PMuzzleFlash = M_PMuzzleFlash;
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

