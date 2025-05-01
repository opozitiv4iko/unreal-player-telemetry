// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Panda.h"
#include "GameFramework/GameModeBase.h"
#include "GamesTechCourseworkGameMode.generated.h"

UCLASS(minimalapi)
class AGamesTechCourseworkGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;
	
public:
	AGamesTechCourseworkGameMode();

protected:
	

private:
	
};



