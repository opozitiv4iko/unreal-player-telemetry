// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TriggerRegion.h"
#include "Panda.generated.h"

UCLASS()
class GAMESTECHCOURSEWORK_API APanda : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APanda();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Combat fields
	float M_FHealth = 30.f;
	FVector M_VWorldSpawnLocation;
	bool M_BInCombat = false;
	
	// Combat methods
	void PandaAttack();

	void TakeDamage(float A_FDamage);

	// Death handling methods
	void Die();
	
	void Reset();

	
};
