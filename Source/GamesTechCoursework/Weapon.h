// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TP_WeaponComponent.h"
#include "Weapon.generated.h"

UCLASS()
class GAMESTECHCOURSEWORK_API AWeapon : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh");
	UStaticMeshComponent* M_PMesh;

public:
	// Weapon Sound
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* M_PFireSound;
	
	//Muzzle Offset
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	FVector M_VMuzzleOffset = FVector(100.0f, 0, 10.0f);

	// Muzzle Flash
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SFX")
	UNiagaraSystem* M_PMuzzleFlash;
	
	// Sets default values for this actor's properties
	AWeapon();

	// Weapon Component
	UTP_WeaponComponent* M_PWeaponComponent;

	// Ammo Sizes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SFX")
	int M_IClipSize = 200;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
