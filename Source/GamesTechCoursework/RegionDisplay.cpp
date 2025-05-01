// Fill out your copyright notice in the Description page of Project Settings.

#include "RegionDisplay.h"

// Called when the widget is constructed
void URegionDisplay::NativeConstruct()
{
	Super::NativeConstruct();

	// Set default region name as a Starter Region
	RegionName->SetText(FText::FromString("Starter Region"));
}

// Function to set the region name displayed in the widget
void URegionDisplay::SetName(FString name)
{
	// Set the region name text
	RegionName->SetText(FText::FromString(name));
}
