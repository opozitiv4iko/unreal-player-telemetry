// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_PandaAttack.h"
#include "Panda.h"
#include "Panda_Controller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PandaKeys.h"

UBTT_PandaAttack::UBTT_PandaAttack(FObjectInitializer const& A_PObjectInit)
{
	// Set the node name to "Panda Attack"
	NodeName = TEXT("Panda Attack");
}

EBTNodeResult::Type UBTT_PandaAttack::ExecuteTask(UBehaviorTreeComponent& A_PTreeComp, uint8* A_PNodeMem)
{
	// Get AI Controller and Panda from pawn
	APanda_Controller* PAIController = Cast<APanda_Controller>(A_PTreeComp.GetAIOwner());
	APanda* P_Panda = Cast<APanda>(PAIController->GetPawn());

	// Get bool value from key to check whether we can attack
	bool BPandaCanAttack = PAIController->GetBlackboard()->GetValueAsBool(PandaKeys::IsPlayerInPandaRange);
	if (BPandaCanAttack)
	{
		// Run Panda Attack method	
		P_Panda->PandaAttack();
	}
	
	// Finish execution
	FinishLatentTask(A_PTreeComp, EBTNodeResult::Succeeded);
	
	return EBTNodeResult::Succeeded;
}
