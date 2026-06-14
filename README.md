# C++ Turn-Based Combat System

## Overview
This project is a modular turn-based combat system built in C++. It simulates RPG style battles between two combatants with abilities, items, status effects, and an XP-based progression system. 

The goal of this project was to practice object-oriented design, system architecture, and gameplay loop implementation in C++. 

## Features
### Combat System 
- Turn-based battle simulation between two combatants
- Basic attacks with damage scaling
- Win/lose conditions based on health
### Abilities
- Multiple ability types (e.g., Fireball, Heal, Drain, Strike)
- Mana cost and cooldown system
- Some abilities apply status effects
- Function pointer based ability dispatch system
### Items
- Consumable items with limited stock
- Self-target and opponent-target item effects
- Buffs and debuffs (attack, defense, mana, health)
### Status Effects
- Status system including effects like Burn, Shock, Poison, Freeze, etc.
- Chance-based activation from abilities
- Tick damage system for ongoing effects
### Progression System
- XP-based leveling system
- Multiple level-ups handled in a single battle resolution
- Stat growth per level (Health, Attack, Defense, Mana)
- Increasing XP thresholds for progression

## Architecture Highlights
- Object-oriented design using multiple interacting classes:
  - Combatant: core entity handling stats and actions
  - Combat_Manager: controls turn flow and battle logic
  - Ability: handles skills, cooldowns, and effects
  - Item: consumable effects and inventory logic
  - Status_Effect: handles buffs, debuffs, and tick effects
  - Progression: XP and leveling system
  - Input_Command: handles player input and AI decision selection
- Function pointer dispatch system for abilities and status effects
- Separation of combat logic and entity state

## How to Build / Run
### Requirements 
- C++17 or higher
- Visual Studio or any C++ compiler
### Build (Visual Studio)
1. Open .sln file
2. Build Solution (Ctrl + Shift + B)
3. Run in Debug mode

## Example Output
```text
FIREBALL IS USED, DEALS 96
Ember Prime WINS THE BATTLE!
Ember Prime LEVELED UP TO 3
HEALTH + 25 
ATTACK + 15
DEFENSE + 12
MANA + 10
```
---

## Purpose of Project
This project was built to explore: 
- Game loop architecture
- Class interaction in C++
- State management systems
- Core RPG mechanics implementation
It serves as a foundation for future game engine or gameplay system development.

## Future Improvements
- AI decision-making improvements
- Better balancing system for abilities and stats
- Save/load system for combat states
- Data-driven configuration (JSON or files)
- UI layer (text or graphical)

## Design Goals
- Modular and extensible combat architecture
- Clear separation between gameplay systems
- Expandable ability and status effect system using function pointers
- Scalable progression system for future balancing

## Author
Built by Nigel Howard
