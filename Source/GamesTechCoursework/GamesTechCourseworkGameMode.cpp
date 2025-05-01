// Copyright Epic Games, Inc. All Rights Reserved.

#include "GamesTechCourseworkGameMode.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Panda.h"
#include "Kismet/GameplayStatics.h"
#include "TriggerRegion.h"


void AGamesTechCourseworkGameMode::BeginPlay()
{
	Super::BeginPlay();
}

AGamesTechCourseworkGameMode::AGamesTechCourseworkGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}

	