// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RegionDisplay.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Engine/TriggerBox.h"
#include "TriggerRegion.generated.h"

UCLASS()
class GAMESTECHCOURSEWORK_API ATriggerRegion : public ATriggerBox
{
	GENERATED_BODY()
	
public:
	
	// Constructor
	ATriggerRegion();

	// Function called when an actor enters the trigger region
	UFUNCTION()
	void EnteredRegion(class AActor* OverlappedActor, class AActor* OtherActor);

	// Property for storing the name of the region
	UPROPERTY(EditAnywhere)
	FString RegionName;

	// Instance of the region display widget associated with this trigger region
	UPROPERTY()
	URegionDisplay* RegionWidgetInstance;
};