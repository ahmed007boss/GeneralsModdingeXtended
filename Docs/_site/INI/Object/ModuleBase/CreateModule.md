# CreateModule

Abstract base class for all object creation and build completion modules in Command & Conquer Generals.

## Overview

CreateModule is an abstract base class that provides the interface for object creation and build completion behavior. It defines when objects become active in the game world and how they handle the transition from construction to operational status. This module is essential for implementing various creation behaviors like spawn effects, initial setup, and build completion notifications.

CreateModule must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used as the foundation for all object creation and build completion modules that handle object initialization and construction completion. This is an **abstract base class** that must be inherited by specific creation implementations. Cannot be used directly in INI files - only concrete implementations can be used.

**Limitations**:
- Cannot be instantiated directly - must be inherited by specific creation implementations
- Cannot be used in INI files - only concrete implementations are usable
- Requires concrete implementation of creation and build completion methods
- Only triggers during object creation and build completion phases

**Conditions**:
- Multiple instances behavior: Multiple create modules can exist independently, each handling different creation scenarios
- Always active once assigned to an object
- onCreate() is called when the object becomes a code object
- onBuildComplete() is called when construction finishes

**Dependencies**:
- Requires proper object construction and build completion system
- Depends on the game engine's object lifecycle management
- Inherits all functionality from BehaviorModule

## Properties

This is an abstract base class with no additional INI-parsable properties beyond those inherited from BehaviorModule.

## Notes

- CreateModule is an abstract base class that defines the creation interface
- Concrete implementations handle specific creation scenarios
- The onCreate() method is called when objects become active code objects
- The onBuildComplete() method is called when construction finishes
- Prevents multiple calls to onBuildComplete() through internal flag management
- Essential for objects that need special initialization or build completion effects
- Commonly used for spawn effects, initial AI setup, and construction completion notifications

## Source Files

**Base Class:** [`BehaviorModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateModule.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateModule.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Create/CreateModule.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Create/CreateModule.cpp)