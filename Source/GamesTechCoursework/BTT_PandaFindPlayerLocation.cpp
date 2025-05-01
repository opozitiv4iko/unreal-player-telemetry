// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_PandaFindPlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Panda_Controller.h"
#include "PandaKeys.h"
#include "TriggerRegion.h"
#include "Kismet/GameplayStatics.h"

UBTT_PandaFindPlayerLocation::UBTT_PandaFindPlayerLocation(FObjectInitializer const& A_PObjectInit)
{
	// Set the node name to "Find Player Location"
	NodeName = TEXT("Find Player Location");
}

EBTNodeResult::Type UBTT_PandaFindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& A_PTreeComp, uint8* A_PNodeMem)
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

	// If player is in the "Forest" region, set its location as target
	if (ForestRegion && ForestRegion->IsOverlappingActor(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn()))
	{
		// Get Nav System
		UNavigationSystemV1* PNavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

		// Get Player reference
		APawn* PPlayer = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn();

		// Set the target location to the player's location
		if (PNavSystem && PPlayer)
		{
			PAIController->GetBlackboard()->SetValueAsVector(PandaKeys::TargetLocation, PPlayer->GetActorLocation());
		}

		// Finish execution
		FinishLatentTask(A_PTreeComp, EBTNodeResult::Succeeded);

		return EBTNodeResult::Succeeded;
	}

	// If player is not in the "Forest" region, return Failed
	return EBTNodeResult::Failed;
	
}