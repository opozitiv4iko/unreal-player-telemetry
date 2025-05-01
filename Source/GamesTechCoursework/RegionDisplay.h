// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "RegionDisplay.generated.h"

UCLASS()
class GAMESTECHCOURSEWORK_API URegionDisplay : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Function to set the region name displayed in the widget
	UFUNCTION(BlueprintCallable)
	void SetName(FString name);

protected:
	// Called when the widget is constructed
	void NativeConstruct() override;

	// Widget component for displaying region name
	UPROPERTY(meta = (BindWidget))
	UTextBlock* RegionName;
	
};
