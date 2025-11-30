## Cargo & Port Scheduling System

This repository contains my solution to HW2 from the **Advanced Topics in OOP** course.  
The assignment was to model a simplified **cargo shipping system** between ports, using graphs and time tables to reason about routes and schedules.

### What this project does
- Reads input files that describe:
  - Ports and their connections.
  - Containers and shipping routes.
  - Timing information for arrivals/departures.
- Validates:
  - Port names.
  - Date/time formats.
- Builds internal graphs to represent:
  - Connectivity between ports.
  - Time‑dependent constraints.
- Processes commands and writes results to an output file.

### Design highlights
- **Language**: C++
- **Key ideas**:
  - Object‑oriented design with several collaborating classes.
  - Separate graphs for “time” and “containers”.
  - Domain‑specific exception type for clearer error handling.
- **Main components**:
  - `CargoSystem` – main façade that loads files, parses commands and runs the logic.
  - `TimeGraph`, `ContainersGraph`, `Port` – graph and domain entities.
  - `CustomException` – used for reporting invalid input or inconsistent state.
  - `main.cpp` – handles CLI flags and ties everything together.

