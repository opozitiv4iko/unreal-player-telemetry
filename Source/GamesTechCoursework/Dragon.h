// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Dragon.generated.h"

UCLASS()
class GAMESTECHCOURSEWORK_API ADragon : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADragon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Combat fields
	float M_FHealth = 90.f;
	FVector M_VWorldSpawnLocation;
	bool M_BInCombat = false;
	
	// Combat methods
	void DragonAttack();

	void TakeDamage(float A_FDamage);

	// Death handling methods
	void Die();
	void Reset();


	
};
