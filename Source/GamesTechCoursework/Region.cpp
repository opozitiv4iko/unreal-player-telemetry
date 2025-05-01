#include "Region.h"

// Function to get the name of a region based on its enum value
FString RegionName(ERegion Region)
{
	switch (Region)
	{
	case ERegion::Forest:
		return "Forest";
	case  ERegion::Mountains:
		return "Mountains";
	case  ERegion::City:
		return "City";
	default:
		return "Unknown";
	}
}
