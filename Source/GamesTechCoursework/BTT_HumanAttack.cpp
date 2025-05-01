// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_HumanAttack.h"
#include "Human.h"
#include "Human_Controller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "HumanKeys.h"

UBTT_HumanAttack::UBTT_HumanAttack(FObjectInitializer const& A_PObjectInit)
{
	// Set the node name to "Human Attack"
	NodeName = TEXT("Human Attack");
}

EBTNodeResult::Type UBTT_HumanAttack::ExecuteTask(UBehaviorTreeComponent& A_PTreeComp, uint8* A_PNodeMem)
{
	// Get AI Controller and Human from pawn
	AHuman_Controller* PAIController = Cast<AHuman_Controller>(A_PTreeComp.GetAIOwner());
	AHuman* P_Human = Cast<AHuman>(PAIController->GetPawn());

	// Get bool value from key to check whether we can attack
	bool BDragonCanAttack = PAIController->GetBlackboard()->GetValueAsBool(HumanKeys::IsPlayerInHumanRange);
	if (BDragonCanAttack)
	{
		// Run Human Attack method	
		P_Human->HumanAttack();
	}
	
	// Finish execution
	FinishLatentTask(A_PTreeComp, EBTNodeResult::Succeeded);
	
	return EBTNodeResult::Succeeded;
}
