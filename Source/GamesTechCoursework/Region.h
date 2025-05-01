#pragma once

// Enum defining types of regions
enum class ERegion : char
{
	Forest = 'F',
	Mountains = 'M',
	City = 'C',
	
};

// Function to get the name of a region based on its enum value
FString RegionName(ERegion);
