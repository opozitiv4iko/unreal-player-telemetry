// Fill out your copyright notice in the Description page of Project Settings.


#include "Human_Controller.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "TriggerRegion.h"
#include "Kismet/GameplayStatics.h"

AHuman_Controller::AHuman_Controller(FObjectInitializer const& A_PObjectInit)
{
    // Get the behavior tree from reference
    static ConstructorHelpers::FObjectFinder<UBehaviorTree> TreeFinder(TEXT("/Script/AIModule.BehaviorTree'/Game/FirstPerson/AI/Human/BT_HumanBT.BT_HumanBT'"));
    if (TreeFinder.Succeeded())
    {
        M_PBehaviorTree = TreeFinder.Object;
    }
    // Initialize the behavior tree and blackboard components
    M_PBehaviorTreeComponent = A_PObjectInit.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorTree Component"));
    M_PBlackboard = A_PObjectInit.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("Blackboard Component"));
}

void AHuman_Controller::BeginPlay()
{
    Super::BeginPlay();
    // Check if M_PBehaviorTree and M_PBehaviorTreeComponent are successfully initialized
    if (M_PBehaviorTree && M_PBehaviorTreeComponent)
    {
        // Start the behavior tree
        RunBehaviorTree(M_PBehaviorTree);
        M_PBehaviorTreeComponent->StartTree(*M_PBehaviorTree);
    }
    else
    {
        // Error handling: output error message or log
        UE_LOG(LogTemp, Error, TEXT("M_PBehaviorTree or M_PBehaviorTreeComponent is not initialized."));
    }
}

void AHuman_Controller::OnPossess(APawn* A_PPawn)
{
    // Call the parent OnPossess method
    Super::OnPossess(A_PPawn);

    // Initialize blackboard only if M_PBlackboard, M_PBehaviorTree, and BlackboardAsset are initialized
    if (M_PBlackboard && M_PBehaviorTree && M_PBehaviorTree->BlackboardAsset)
    {
        M_PBlackboard->InitializeBlackboard(*M_PBehaviorTree->BlackboardAsset);
    }
    else
    {
        // Error handling: output error message or log
        UE_LOG(LogTemp, Error, TEXT("M_PBlackboard or M_PBehaviorTree or BlackboardAsset is not initialized."));
    }
}

// Function to get the blackboard component
UBlackboardComponent* AHuman_Controller::GetBlackboard() const
{
    return M_PBlackboard;
}

// Function to get the name of the current region
FString AHuman_Controller::GetCurrentRegionName()
{
    // Get the current location of the human
    FVector HumanLocation = GetPawn()->GetActorLocation();

    // Check all TriggerRegion actors in the world
    TArray<AActor*> FoundRegions;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATriggerRegion::StaticClass(), FoundRegions);

    for (AActor* RegionActor : FoundRegions)
    {
        ATriggerRegion* TriggerRegion = Cast<ATriggerRegion>(RegionActor);
        if (TriggerRegion && TriggerRegion->GetComponentsBoundingBox().IsInside(HumanLocation))
        {
            // Human is inside this TriggerRegion, return its name
            return TriggerRegion->RegionName;
        }
    }
    // If human is not inside any TriggerRegion, return an empty string
    return FString();
}