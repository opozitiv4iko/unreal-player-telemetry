// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerRegion.h"

ATriggerRegion::ATriggerRegion()
{
	// Set default region name
	RegionName = "Starter Region";

	// Bind the EnteredRegion function to the OnActorBeginOverlap event
	OnActorBeginOverlap.AddDynamic(this, &ATriggerRegion::EnteredRegion);
}

// Called when an actor overlaps with the trigger region
void ATriggerRegion::EnteredRegion(AActor* OverlappedActor, AActor* OtherActor)
{
	// Check if the other actor is valid and not this trigger region itself
	if (OtherActor && OtherActor != this)
	{
		// Find all widgets of type URegionDisplay in the world
		TArray<UUserWidget*> FoundWidgets;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(),FoundWidgets, URegionDisplay::StaticClass());

		// If at least one widget is found
		if (FoundWidgets.Num() > 0)
		{
			// Get the first widget and cast it to URegionDisplay
			RegionWidgetInstance = Cast<URegionDisplay>(FoundWidgets[0]);

			// If casting is successful
			if (RegionWidgetInstance)
			{
				// Set the region name in the widget
				RegionWidgetInstance->SetName(RegionName);
			}
		}
	}
}
