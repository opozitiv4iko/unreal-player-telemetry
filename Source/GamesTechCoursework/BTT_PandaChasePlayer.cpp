// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_PandaChasePlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Panda_Controller.h"
#include "PandaKeys.h"
#include "TriggerRegion.h"
#include "Kismet/GameplayStatics.h"

UBTT_PandaChasePlayer::UBTT_PandaChasePlayer(FObjectInitializer const& A_PObjectInit)
{
	// Set the node name to "Chase Player"
	NodeName = TEXT("Chase Player");
}

EBTNodeResult::Type UBTT_PandaChasePlayer::ExecuteTask(UBehaviorTreeComponent& A_PTreeComp, uint8* A_PNodeMem)
{
	// Get AI Controller
	auto const PAIController = Cast<APanda_Controller>(A_PTreeComp.GetAIOwner());

	// Check if the AI controller is valid
	if (!PAIController)
	{
		return EBTNodeResult::Failed;
	}

	// Check if the player is in the "Forest" region
	ATriggerRegion* ForestRegion = nullptr;
	TArray<AActor*> OverlappingActors;
	PAIController->GetPawn()->GetOverlappingActors(OverlappingActors, ATriggerRegion::StaticClass());
	for (AActor* Actor : OverlappingActors)
	{
		ATriggerRegion* TriggerRegion = Cast<ATriggerRegion>(Actor);
		if (TriggerRegion && TriggerRegion->RegionName == "Forest")
		{
			ForestRegion = TriggerRegion;
			break;
		}
	}

	// If player is not in the "Forest" region, return Failed
	if (!ForestRegion || !ForestRegion->IsOverlappingActor(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn()))
	{
		return EBTNodeResult::Failed;
	}

	// Get Nav System
	UNavigationSystemV1* PNavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

	// Get the location of the player from the blackboard
	FVector TargetLocation = PAIController->GetBlackboard()->GetValueAsVector(PandaKeys::TargetLocation);

	// Tell the AI to move towards the player
	if (PNavSystem && TargetLocation != FVector::ZeroVector)
	{
		PAIController->MoveToLocation(TargetLocation);
	}

	// Finish execution
	FinishLatentTask(A_PTreeComp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
	
}
