#include "Enemies.h"

// Function to get the name of an enemy based on its enum value
FString EnemyName(EEnemies Enemy)
{
		switch (Enemy)
		{
		case EEnemies::Panda:
			return "Panda";
		case  EEnemies::Dragon:
			return "Dragon";
		case  EEnemies::Human:
			return "Human";
		default:
			return "Unknown";	
		}
}
