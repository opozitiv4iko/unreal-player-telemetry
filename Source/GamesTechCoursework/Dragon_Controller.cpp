// Fill out your copyright notice in the Description page of Project Settings.


#include "Dragon_Controller.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "TriggerRegion.h"
#include "Kismet/GameplayStatics.h"

ADragon_Controller::ADragon_Controller(FObjectInitializer const& A_PObjectInit)
{
	// Get the behavior tree from reference
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> TreeFinder(TEXT("/Script/AIModule.BehaviorTree'/Game/FirstPerson/AI/Dragons/BT_DragonBT.BT_DragonBT'"));
	if (TreeFinder.Succeeded())
	{
		M_PBehaviorTree = TreeFinder.Object;
	}
	// Init the true and blackboard components
	M_PBehaviorTreeComponent = A_PObjectInit.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorTree Component"));
	M_PBlackboard = A_PObjectInit.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("Blackboard Component"));
}

void ADragon_Controller::BeginPlay()
{
    Super::BeginPlay();

    // Check if the behavior tree and its component were successfully initialized.
    if (M_PBehaviorTree && M_PBehaviorTreeComponent)
    {
        // Start the behavior tree.
        RunBehaviorTree(M_PBehaviorTree);
        M_PBehaviorTreeComponent->StartTree(*M_PBehaviorTree);
    }
    else
    {
        // Handle error: Log an error message.
        UE_LOG(LogTemp, Error, TEXT("M_PBehaviorTree or M_PBehaviorTreeComponent is not initialized."));
    }
}

void ADragon_Controller::OnPossess(APawn* A_PPawn)
{
    // Call the parent OnPossess method.
    Super::OnPossess(A_PPawn);

    // Initialize the blackboard if both the blackboard and behavior tree are initialized.
    if (M_PBlackboard && M_PBehaviorTree && M_PBehaviorTree->BlackboardAsset)
    {
        M_PBlackboard->InitializeBlackboard(*M_PBehaviorTree->BlackboardAsset);
    }
    else
    {
        // Handle error: Log an error message.
        UE_LOG(LogTemp, Error, TEXT("M_PBlackboard or M_PBehaviorTree or BlackboardAsset is not initialized."));
    }
}

// Function to retrieve the blackboard component.
UBlackboardComponent* ADragon_Controller::GetBlackboard() const
{
    return M_PBlackboard;
}

// Function to get the name of the current region the dragon is in.
FString ADragon_Controller::GetCurrentRegionName()
{
    // Get the current location of the dragon.
    FVector DragonLocation = GetPawn()->GetActorLocation();

    // Find all TriggerRegion actors in the world.
    TArray<AActor*> FoundRegions;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATriggerRegion::StaticClass(), FoundRegions);

    // Iterate through the found TriggerRegion actors.
    for (AActor* RegionActor : FoundRegions)
    {
        ATriggerRegion* TriggerRegion = Cast<ATriggerRegion>(RegionActor);
        if (TriggerRegion && TriggerRegion->GetComponentsBoundingBox().IsInside(DragonLocation))
        {
            // If the dragon is inside a TriggerRegion, return its name.
            return TriggerRegion->RegionName;
        }
    }
    // If the dragon is not inside any TriggerRegion, return an empty string.
    return FString();
}