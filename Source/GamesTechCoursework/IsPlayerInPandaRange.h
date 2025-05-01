// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "IsPlayerInPandaRange.generated.h"


UCLASS()
class GAMESTECHCOURSEWORK_API UIsPlayerInPandaRange : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	// Constructor
	UIsPlayerInPandaRange();

	//Method for when service is called
	void OnBecomeRelevant(UBehaviorTreeComponent& A_PTreeComp, uint8* A_PNodeMem);

	// Field for range
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI");
	float M_FRange = 100.0f;
};
