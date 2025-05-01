// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Human_Controller.generated.h"


UCLASS()
class GAMESTECHCOURSEWORK_API AHuman_Controller : public AAIController
{
	GENERATED_BODY()

public:
	AHuman_Controller(FObjectInitializer const& A_PObjectInit);
	
	// Overrides
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* A_PPawn) override;

	// Method to get black board
	class UBlackboardComponent* GetBlackboard() const;
	
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
