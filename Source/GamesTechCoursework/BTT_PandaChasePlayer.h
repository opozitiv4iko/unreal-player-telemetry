// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_PandaChasePlayer.generated.h"


UCLASS()
class GAMESTECHCOURSEWORK_API UBTT_PandaChasePlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	// Constructor declaration for UBTT_PandaChasePlayer
	UBTT_PandaChasePlayer(FObjectInitializer const& A_PObjectInit);

	// Method declaration for ExecuteTask
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& A_PTreeComp, uint8* A_PNodeMem);
};
