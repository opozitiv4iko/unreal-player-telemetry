#pragma once

#include "Runtime/Core/Public/UObject/NameTypes.h"
#include "Runtime/Core/Public/Containers/UnrealString.h"

// Namespace for defining keys used in Panda behavior tree blackboard
namespace PandaKeys
{
	// Key for storing target location in blackboard
	TCHAR const* const TargetLocation = TEXT("TargetLocation");
	
	// Key for indicating whether player is in panda's range in blackboard
	TCHAR const* const IsPlayerInPandaRange = TEXT("IsPlayerInPandaRange");
}
