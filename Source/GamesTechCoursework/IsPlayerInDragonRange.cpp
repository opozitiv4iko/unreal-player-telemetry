// Fill out your copyright notice in the Description page of Project Settings.


#include "IsPlayerInDragonRange.h"
#include "Kismet/GameplayStatics.h"
#include "Dragon_Controller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DragonKeys.h"

UIsPlayerInDragonRange::UIsPlayerInDragonRange()
{
	// Set bNotifyBecomeRelevant to true to notify when the node becomes relevant
	bNotifyBecomeRelevant = true;

	// Set the node name to Is Player In Dragon Range
	NodeName = TEXT("Is Player In Dragon Range");
}

void UIsPlayerInDragonRange::OnBecomeRelevant(UBehaviorTreeComponent& A_PTreeComp, uint8* A_PNodeMem)
{
	Super::OnBecomeRelevant(A_PTreeComp, A_PNodeMem);

	// Get AI Controller
	ADragon_Controller* PaiController = Cast<ADragon_Controller>(A_PTreeComp.GetAIOwner());
	APawn* PDragon = PaiController->GetPawn();

	// Get Player Controller and Pawn
	APlayerController* PPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	// Set Blackboard key to whether or not player is in range
	PaiController->GetBlackboard()->SetValueAsBool(DragonKeys::IsPlayerInDragonRange, PDragon->GetDistanceTo(PPlayerController->GetPawn())<= M_FRange);
}
