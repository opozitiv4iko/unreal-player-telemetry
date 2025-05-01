#pragma once

// Enum defining types of enemies
enum class EEnemies : char
{
	Panda = 'P',
	Dragon = 'D',
	Human = 'H',
};

// Function to get the name of an enemy based on its enum value
FString EnemyName(EEnemies);