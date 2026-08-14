# Player Death Telemetry in Unreal Engine 5

A gameplay telemetry system built in Unreal Engine 5 with C++. Every time the player dies, the game writes a record to a SQL database — which region they were in, which enemy killed them, how much damage they'd taken, and where on the map they fell.

The point isn't the game. It's that the deaths become queryable data. Studios use exactly this kind of telemetry to find difficulty spikes: if 70% of deaths in a region come from one enemy type, that region is unbalanced, and the data tells you before a player complains.

Built as coursework for BSc Computer Science (Games), University of Greenwich.
