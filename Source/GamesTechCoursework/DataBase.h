#pragma once

#include "SQLiteDatabase.h"
#include "Async/Async.h"
#include "CoreMinimal.h"
#include "Enemies.h"
#include "Region.h"
#include "DataBase.generated.h"

UCLASS()
class GAMESTECHCOURSEWORK_API ADataBase : public AActor
{
	GENERATED_BODY() 

public:
	// Constructor declaration
	ADataBase(); 

	// Static function declaration to get database path
	static FString DataBasePath(); 

	// Function to log player damage
	void LogPlayerDamage(ERegion RegionName, EEnemies Damager, bool Critical, float Damage); 

	// Static function declaration to ensure database creation
	static void EnsureCreated(); 

	// Function to count player deaths
	size_t CountDeaths(); 

	// Function to count player deaths caused by a specific enemy
	size_t CountDeathsByDamager(EEnemies Damager); 

protected:
	// Override of BeginPlay function from AActor
	virtual void BeginPlay() override; 

	// Override of EndPlay function from AActor
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override; 

private:
	// Shared pointer to SQLiteDatabase for database operations
	TSharedPtr<FSQLiteDatabase> Database; 
};