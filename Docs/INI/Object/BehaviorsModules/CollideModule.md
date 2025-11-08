# CollideModule

Abstract base class for all collision detection and response modules in Command & Conquer Generals.

## Overview

CollideModule is an abstract base class that provides the interface for collision detection and response behavior. It defines how objects interact when they collide with other objects or the terrain. This module is essential for implementing various collision behaviors like vehicle crashes, projectile impacts, and object interactions.

CollideModule must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used as the foundation for all collision detection and response modules that handle object interactions and collision events. This is an **abstract base class** that must be inherited by specific collision implementations. Cannot be used directly in INI files - only concrete implementations can be used.

**Limitations**:
- Cannot be instantiated directly - must be inherited by specific collision implementations
- Cannot be used in INI files - only concrete implementations are usable
- Requires concrete implementation of collision response methods
- Only responds to collision events when properly integrated with the collision system

**Conditions**:
- Multiple instances behavior: Multiple collide modules can exist independently, each handling different collision scenarios
- Always active once assigned to an object
- Collision detection supports both object-to-object and object-to-terrain interactions

**Dependencies**:
- Requires proper object geometry and physics data for collision detection
- Depends on the game engine's collision detection system
- Inherits all functionality from BehaviorModule

## Properties

This is an abstract base class with no additional INI-parsable properties beyond those inherited from BehaviorModule.

## Notes

- CollideModule is an abstract base class that defines the collision interface
- Concrete implementations handle specific collision scenarios
- The `onCollide` method is called when collisions occur
- Collision detection supports both object-to-object and object-to-terrain interactions
- Special collision types include hijacked vehicles, sabotage buildings, car bombs, railroads, and salvage crates

## Source Files

**Base Class:** [`BehaviorModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CollideModule.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CollideModule.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Collide/CollideModule.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Collide/CollideModule.cpp)