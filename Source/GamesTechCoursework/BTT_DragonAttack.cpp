// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_DragonAttack.h"
#include "Dragon.h"
#include "Dragon_Controller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DragonKeys.h"

UBTT_DragonAttack::UBTT_DragonAttack(FObjectInitializer const& A_PObjectInit)
{
	// Set the node name to "Dragon Attack"
	NodeName = TEXT("Dragon Attack");
}

EBTNodeResult::Type UBTT_DragonAttack::ExecuteTask(UBehaviorTreeComponent& A_PTreeComp, uint8* A_PNodeMem)
{
	// Get AI Controller and Dragon from pawn
	ADragon_Controller* PAIController = Cast<ADragon_Controller>(A_PTreeComp.GetAIOwner());
	ADragon* P_Dragon = Cast<ADragon>(PAIController->GetPawn());

	// Get bool value from key to check whether we can attack
	bool BDragonCanAttack = PAIController->GetBlackboard()->GetValueAsBool(DragonKeys::IsPlayerInDragonRange);
	if (BDragonCanAttack)
	{
		// Run Dragon Attack method	
		P_Dragon->DragonAttack();
	}
	
	// Finish execution
	FinishLatentTask(A_PTreeComp, EBTNodeResult::Succeeded);
	
	return EBTNodeResult::Succeeded;
}
