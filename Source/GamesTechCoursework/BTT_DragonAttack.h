// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_DragonAttack.generated.h"

UCLASS()
class GAMESTECHCOURSEWORK_API UBTT_DragonAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	// Constructor declaration for UBTT_DragonAttack
	UBTT_DragonAttack(FObjectInitializer const& A_PObjectInit);

	// Method declaration for ExecuteTask
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& A_PTreeComp, uint8* A_PNodeMem);
	
};
