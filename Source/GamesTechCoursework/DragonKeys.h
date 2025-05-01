#pragma once

#include "Runtime/Core/Public/UObject/NameTypes.h"
#include "Runtime/Core/Public/Containers/UnrealString.h"

// Namespace for defining keys used in Dragon behavior tree blackboard
namespace DragonKeys
{
	// Key for storing target location in blackboard
	TCHAR const* const TargetLocation = TEXT("TargetLocation");
	
	// Key for indicating whether player is in dragon's range in blackboard
	TCHAR const* const IsPlayerInDragonRange = TEXT("IsPlayerInDragonRange");
}
