#include "DataBase.h"
#include <ctime>

ADataBase::ADataBase(): Database(new FSQLiteDatabase)
{
    // Constructor initializes the Database pointer with a new instance of FSQLiteDatabase
}

FString ADataBase::DataBasePath()
{
    // Function to get the path of the database file
    return FPaths::ProjectContentDir() + "Database/DBPlayerDeath.db";
}

void ADataBase::LogPlayerDamage(ERegion Region, EEnemies Damager, bool Critical, float Damage)
{
    // Function to log player damage

    // Get current time as a string
    FString Time = FDateTime::Now().ToString();

    // Create a shared pointer to the Database object
    TSharedPtr<FSQLiteDatabase> Data_base(Database);

    // Asynchronously execute database operation
    AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [Data_base, Time, Damager, Region, Critical, Damage]()
    {
        // Construct SQL query to insert data into the database
        FString Query = FString::Printf(
            TEXT("INSERT INTO PlayerDeaths (Region, Enemy, DamageTime, Critical, Damage) ")
            TEXT("VALUES ('%s', '%s', '%s', %d, %f);"),
            *RegionName(Region), *EnemyName(Damager), *Time, Critical, Damage);

        // Execute the query
        if (!Data_base->Execute(*Query))
        {
            // Display error message if execution fails
            if (GEngine)
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
                    TEXT("Adding row FAILED. Try again!!!"));
        }
    });
}

void ADataBase::EnsureCreated()
{
    // Function to ensure that the database and required table are created

    // Check if the database file doesn't exist
    if (!FPaths::FileExists(DataBasePath()))
    {
        // Create a local instance of FSQLiteDatabase
        FSQLiteDatabase Database;

        // Attempt to open the database file for read-write create mode
        if (Database.Open(*DataBasePath(), ESQLiteDatabaseOpenMode::ReadWriteCreate))
        {
            // SQL query to create the table if it doesn't exist
            FString Query =
                TEXT("CREATE TABLE IF NOT EXISTS PlayerDeaths (")
                TEXT("Id INTEGER PRIMARY KEY AUTOINCREMENT, ")
                TEXT("Region TEXT CHECK ( Region IN ('Forest', 'Mountains', 'City')), ")
                TEXT("Enemy TEXT CHECK ( Enemy IN ( 'Panda', 'Dragon', 'Human')), ")
                TEXT("Damage REAL, ")
                TEXT("Critical INTEGER, ")
                TEXT("DamageTime DATETIME);");

            // Execute the query
            if (!Database.Execute(*Query))
            {
                // Display error message if execution fails
                if (GEngine)
                    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Table creation FAILED. Try again!!!"));
            }
        }
        else
        {
            // Display error message if database opening fails
            if (GEngine)
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("DataBase creation FAILED. Try again!!!"));
        }

        // Close the database
        Database.Close();
    }
}

size_t ADataBase::CountDeaths()
{
    // Function to count player deaths

    // SQL query to count player deaths where Critical is 1 (true)
    FString Query = TEXT("SELECT COUNT(*) FROM PlayerDeaths WHERE Critical = 1;");

    // Prepare SQL statement
    FSQLitePreparedStatement Statement;

    // Initialize count variable
    size_t Count = -1; 

    // Create and execute the prepared statement
    Statement.Create(*Database, *Query, ESQLitePreparedStatementFlags::None);
    if (Statement.Execute())
    {
        // Move to the first row
        Statement.Step();

        // Get count value
        Statement.GetColumnValueByIndex(0, Count); 
    }
    else
    {
        // Display error message if execution fails
        if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Count Deaths FAILED. Try again!!!"));
    }

    // Destroy the statement
    Statement.Destroy();

    // Return the count
    return Count; 
}

size_t ADataBase::CountDeathsByDamager(EEnemies Damager)
{
    // Function to count player deaths caused by a specific enemy

    // SQL query to count player deaths where Critical is 1 (true) and Enemy matches the provided Damager
    FString Query = FString::Printf(TEXT("SELECT COUNT(*) FROM PlayerDeaths WHERE Critical = 1 AND Enemy = '%s';"), *EnemyName(Damager));

    // Prepare SQL statement
    FSQLitePreparedStatement Statement;

    // Initialize count variable
    size_t Count = -1; 

    // Create and execute the prepared statement
    Statement.Create(*Database, *Query, ESQLitePreparedStatementFlags::None);
    if (Statement.Execute())
    {
        // Move to the first row
        Statement.Step();
        
        // Get count value
        Statement.GetColumnValueByIndex(0, Count); 
    }
    else
    {
        // Display error message if execution fails
        if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Count Deaths FAILED. Try again!!!"));
    }

    // Destroy the statement
    Statement.Destroy(); 

    // Return the count
    return Count; 
}

void ADataBase::BeginPlay()
{
    // Override of BeginPlay function from AActor

    // Call the parent class's BeginPlay function
    Super::BeginPlay(); 

    // Ensure that the database and required table are created
    EnsureCreated();

    // Attempt to open the database file for read-write mode
    if (!Database->Open(*DataBasePath(), ESQLiteDatabaseOpenMode::ReadWrite))
    {
        // Display error message if opening fails
        if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("DataBase creation FAILED. Try again!!!"));

        // Close the database
        Database->Close(); 
    }
}

void ADataBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    // Override of EndPlay function from AActor

    // Call the parent class's EndPlay function
    Super::EndPlay(EndPlayReason); 

    // Close the database
    Database->Close(); 
}