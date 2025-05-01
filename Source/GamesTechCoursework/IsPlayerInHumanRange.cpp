// Fill out your copyright notice in the Description page of Project Settings.


#include "IsPlayerInHumanRange.h"
#include "Kismet/GameplayStatics.h"
#include "Human_Controller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "HumanKeys.h"

UIsPlayerInHumanRange::UIsPlayerInHumanRange()
{
	// Set bNotifyBecomeRelevant to true to notify when the node becomes relevant
	bNotifyBecomeRelevant = true;

	// Set the node name to Is Player In Human Range
	NodeName = TEXT("Is Player In Human Range");
}

void UIsPlayerInHumanRange::OnBecomeRelevant(UBehaviorTreeComponent& A_PTreeComp, uint8* A_PNodeMem)
{
	Super::OnBecomeRelevant(A_PTreeComp, A_PNodeMem);

	// Get AI Controller
	AHuman_Controller* PaiController = Cast<AHuman_Controller>(A_PTreeComp.GetAIOwner());
	APawn* PHuman = PaiController->GetPawn();

	// Get Player Controller and Pawn
	APlayerController* PPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	// Set Blackboard key to whether or not player is in range
	PaiController->GetBlackboard()->SetValueAsBool(HumanKeys::IsPlayerInHumanRange, PHuman->GetDistanceTo(PPlayerController->GetPawn())<= M_FRange);
}
