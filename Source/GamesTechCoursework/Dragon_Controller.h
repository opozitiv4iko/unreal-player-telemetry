// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TriggerRegion.h"
#include "RegionDisplay.h"
#include "Dragon_Controller.generated.h"

UCLASS()
class GAMESTECHCOURSEWORK_API ADragon_Controller : public AAIController
{
	GENERATED_BODY()

public:
	ADragon_Controller(FObjectInitializer const& A_PObjectInit);
	
	// Overrides
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* A_PPawn) override;

	// Method to get black board
	class UBlackboardComponent* GetBlackboard() const;

	// Function to get the name of the current region
	FString GetCurrentRegionName();

	// Three components
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI")
	class UBehaviorTreeComponent* M_PBehaviorTreeComponent;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI")
	class UBehaviorTree* M_PBehaviorTree;

private:
	// ReSharper disable once CppUE4ProbableMemoryIssuesWithUObject
	class UBlackboardComponent* M_PBlackboard;
	
	
};
