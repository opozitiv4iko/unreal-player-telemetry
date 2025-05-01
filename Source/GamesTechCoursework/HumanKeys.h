#pragma once

#include "Runtime/Core/Public/UObject/NameTypes.h"
#include "Runtime/Core/Public/Containers/UnrealString.h"

// Namespace for defining keys used in Human behavior tree blackboard
namespace HumanKeys
{
	// Key for storing target location in blackboard
	TCHAR const* const TargetLocation = TEXT("TargetLocation");

	// Key for indicating whether player is in human's range in blackboard
	TCHAR const* const IsPlayerInHumanRange = TEXT("IsPlayerInHumanRange");
}
