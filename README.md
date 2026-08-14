# Player Damage Telemetry in Unreal Engine 5

A first-person shooter built in Unreal Engine 5.2 (C++) where every hit the player takes is
logged to a SQLite database — which region it happened in, which enemy did it, how much damage,
whether it was the killing blow, and when.

The game is the vehicle; the point is the telemetry. Studios instrument games exactly like this
to find difficulty spikes: if most deaths in one region come from one enemy, that region is
unbalanced, and the data says so before a player ever complains.

Coursework for BSc Computer Science (Games), University of Greenwich.

## The game

- Three regions: **Forest**, **Mountains**, **City**
- Three enemies: **Panda**, **Dragon**, **Human**, each driven by its own Behaviour Tree
- Enemies only locate and chase the player inside their own region
- First-person shooting with line tracing, HUD health bar and a region-name widget

## The data

Every damage event writes one row to `PlayerDeaths` in a SQLite database at
`Content/Database/DBPlayerDeath.db`:

| Column | Type | Notes |
|---|---|---|
| `Id` | INTEGER | Primary key, autoincrement |
| `Region` | TEXT | Constrained to `'Forest'`, `'Mountains'`, `'City'` |
| `Enemy` | TEXT | Constrained to `'Panda'`, `'Dragon'`, `'Human'` |
| `Damage` | REAL | Damage dealt by this hit |
| `Critical` | INTEGER | `1` if this hit killed the player |
| `DamageTime` | DATETIME | When it happened |

The `CHECK` constraints on `Region` and `Enemy` mean invalid values can't enter the table —
data integrity is enforced by the schema, not by trusting the calling code.

## Questions the data answers

```sql
-- Which enemy kills players most often?
SELECT Enemy, COUNT(*) AS Deaths
FROM PlayerDeaths
WHERE Critical = 1
GROUP BY Enemy
ORDER BY Deaths DESC;

-- Which region is hardest, and what's killing people there?
SELECT Region, Enemy, COUNT(*) AS Deaths
FROM PlayerDeaths
WHERE Critical = 1
GROUP BY Region, Enemy
ORDER BY Deaths DESC;

-- How much damage does a player absorb before dying, by region?
SELECT Region, SUM(Damage) AS TotalDamage, COUNT(*) AS Hits
FROM PlayerDeaths
GROUP BY Region;
```

`CountDeaths()` and `CountDeathsByDamager()` in `DataBase.cpp` run the first two of these
in-engine using prepared statements.

## How it works

```
Enemy Behaviour Tree attack task
        │
        ▼
AFPSCharacter::TakeDamage(Damage, Damager)     FPSCharacter.cpp
        │
        ▼
ADataBase::LogPlayerDamage(Region, Enemy,      DataBase.cpp
                           Critical, Damage)
        │
        ▼
AsyncTask on a background thread  ──  INSERT runs off the game thread
        │
        ▼
SQLite: Content/Database/DBPlayerDeath.db
```

Writes are dispatched with `AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, ...)` so
database I/O never blocks the game loop and can't cause a frame hitch. The database is opened
in `BeginPlay()`, closed in `EndPlay()`, and `EnsureCreated()` builds the schema on first run
if the file doesn't exist yet.

## Key files

| File | Role |
|---|---|
| `Source/GamesTechCoursework/DataBase.h/.cpp` | Schema creation, async logging, aggregate queries |
| `Source/GamesTechCoursework/FPSCharacter.h/.cpp` | Player, health, damage handling, death |
| `Source/GamesTechCoursework/Region.h` | `ERegion` enum and name lookup |
| `Source/GamesTechCoursework/Enemies.h` | `EEnemies` enum and name lookup |
| `Source/GamesTechCoursework/BTT_*.cpp` | Behaviour Tree tasks — find, chase, attack, per enemy |
| `Source/GamesTechCoursework/Panda_Controller.cpp` | AI controller |

## Running it

1. Clone the repo
2. Open `GamesTechCoursework.uproject` in Unreal Engine 5.2
3. Play. The database is created automatically on first run at
   `Content/Database/DBPlayerDeath.db`
4. Open that file with any SQLite client to query it
