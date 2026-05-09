# DestroyModule

Abstract base class for all object destruction handling modules in Command & Conquer Generals.

## Overview

DestroyModule is an abstract base class that provides the interface for object destruction behavior. It defines how objects handle their destruction and cleanup when they are removed from the game world. This module is essential for implementing various destruction behaviors like cleanup effects, resource recovery, and destruction notifications.

DestroyModule must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used as the foundation for all object destruction handling modules that manage object cleanup and destruction events. This is an **abstract base class** that must be inherited by specific destruction implementations. Cannot be used directly in INI files - only concrete implementations can be used.

**Limitations**:
- Cannot be instantiated directly - must be inherited by specific destruction implementations
- Cannot be used in INI files - only concrete implementations are usable
- Requires concrete implementation of destruction callback method

**Conditions**:
- Multiple instances behavior: Multiple destroy modules can exist independently, each handling different destruction scenarios
- Always active once assigned to an object
- onDestroy() is called when the object is destroyed

**Dependencies**:
- Requires proper object destruction system integration
- Depends on the game engine's object lifecycle management

## Properties

This is an abstract base class with no additional INI-parsable properties beyond those inherited from BehaviorModule.


## Notes

- DestroyModule is an abstract base class that defines the destruction interface
- Concrete implementations handle specific destruction scenarios
- The onDestroy() method is called when objects are destroyed
- Essential for objects that need special cleanup or destruction effects
- Commonly used for resource recovery, cleanup effects, and destruction notifications
- Provides hooks for destruction-related behavior and cleanup operations

## Source Files

**Base Class:** [`BehaviorModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DestroyModule.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DestroyModule.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Destroy/DestroyModule.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Destroy/DestroyModule.cpp)