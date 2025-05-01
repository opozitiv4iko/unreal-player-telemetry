// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_DragonFindPlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Dragon_Controller.h"
#include "DragonKeys.h"
#include "Kismet/GameplayStatics.h"

UBTT_DragonFindPlayerLocation::UBTT_DragonFindPlayerLocation(FObjectInitializer const& A_PObjectInit)
{
	// Set the node name to "Find Player Location"
	NodeName = TEXT("Find Player Location");
}

EBTNodeResult::Type UBTT_DragonFindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& A_PTreeComp, uint8* A_PNodeMem)
{
	// Get AI Controller
	auto const PAIController = Cast<ADragon_Controller>(A_PTreeComp.GetAIOwner());

	// Check if the AI controller is valid
	if (!PAIController)
	{
		return EBTNodeResult::Failed;
	}

	// Check if the player is in the "Mountains" region
	ATriggerRegion* MountainsRegion = nullptr;
	TArray<AActor*> OverlappingActors;
	PAIController->GetPawn()->GetOverlappingActors(OverlappingActors, ATriggerRegion::StaticClass());
	for (AActor* Actor : OverlappingActors)
	{
		ATriggerRegion* TriggerRegion = Cast<ATriggerRegion>(Actor);
		if (TriggerRegion && TriggerRegion->RegionName == "Mountains")
		{
			MountainsRegion = TriggerRegion;
			break;
		}
	}

	// If player is in the "Mountains" region, set its location as target
	if (MountainsRegion && MountainsRegion->IsOverlappingActor(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn()))
	{
		// Get Nav System
		UNavigationSystemV1* PNavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

		// Get Player reference
		APawn* PPlayer = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn();

		// Set the target location to the player's location
		if (PNavSystem && PPlayer)
		{
			PAIController->GetBlackboard()->SetValueAsVector(DragonKeys::TargetLocation, PPlayer->GetActorLocation());
		}

		// Finish execution
		FinishLatentTask(A_PTreeComp, EBTNodeResult::Succeeded);

		return EBTNodeResult::Succeeded;
	}

	// If player is not in the "Mountains" region, return Failed
	return EBTNodeResult::Failed;
}
