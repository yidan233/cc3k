# cc3k
# CC3K - Chambers of the Cursed King

## Introduction
CC3K is a dungeon crawler game where a player starts randomly generated in one of five chambers on a floor, needing to reach the fifth floor alive to win. Each floor is filled with enemies, potions, and gold. Enemies attack within one block radius, potions provide buffs or debuffs when picked up, and gold can be collected for points.

## Game Mechanics
- **Player Movement**: Navigate through floors, avoiding or engaging enemies, and collecting items.
- **Combat**: Engage in turn-based combat with enemies within close proximity.
- **Items**: Collect potions and gold, each affecting the player's stats or score.
- **Progression**: Move to the next floor by finding the stairs, aiming to reach and survive the fifth floor.

## Class Overview
- **Item**: Base class for game items with subclasses `Potion` and `Gold`.
  - **Potion**: Implements Decorator Pattern for dynamic effect application.
  - **Gold**: Stores gold amounts that players can collect.
- **Character**: Observer pattern with subclasses `Player` (subject) and `Enemy` (observers).
- **Cell**: Represents a unit area on the floor storing items or characters.
- **Chamber**: Manages item spawning within a chamber using a vector of cell pointers.
- **Floor**: Handles the layout and item distribution across the game floor.
- **GameFlow**: Acts as the game controller, managing the game state and player actions.

## Design Patterns
- **Decorator**: Used in `Potion` for effect management.
- **Observer**: Applied in `Character` for enemy alerts on player moves.
- **Inheritance**: Shared functionalities across classes.
- **RAII**: Resource management using smart pointers to prevent memory leaks.

## Building the Project
To build CC3K, ensure you have a C++ compiler that supports C++11 or later. Use the following commands:
```bash
g++ -std=c++11 *.cpp -o cc3k
./cc3k
