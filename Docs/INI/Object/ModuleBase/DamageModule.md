# DamageModule

Abstract base class for all damage handling and body state change modules in Command & Conquer Generals.

## Overview

DamageModule is an abstract base class that provides the interface for damage handling and body state change behavior. It defines how objects respond to damage, healing, and body damage state transitions. This module is essential for implementing various damage-related behaviors like armor effects, damage multipliers, and state-based responses.

DamageModule must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used as the foundation for all damage handling and body state change modules that respond to damage, healing, and body damage state transitions. This is an **abstract base class** that must be inherited by specific damage implementations. Cannot be used directly in INI files - only concrete implementations can be used.

**Limitations**:
- Cannot be instantiated directly - must be inherited by specific damage implementations
- Cannot be used in INI files - only concrete implementations are usable
- Requires concrete implementation of damage and healing callback methods
- Only responds to damage events when properly integrated with the damage system

**Conditions**:
- Multiple instances behavior: Multiple damage modules can exist independently, each handling different damage scenarios
- Always active once assigned to an object
- Callbacks are triggered by the damage system when appropriate events occur

**Dependencies**:
- Requires proper damage system integration
- Depends on the body damage state system for state change notifications
- Inherits all functionality from BehaviorModule

## Properties

This is an abstract base class with no additional INI-parsable properties beyond those inherited from BehaviorModule.

## Notes

- DamageModule is an abstract base class that defines the damage interface
- Concrete implementations handle specific damage scenarios
- The onDamage() callback is triggered when objects receive damage
- The onHealing() callback is triggered when objects receive healing
- The onBodyDamageStateChange() callback is triggered when body damage states change
- Essential for objects that need special damage handling or state-based responses
- Commonly used for armor effects, damage multipliers, and conditional damage responses
- Provides hooks for damage modification, state-based behavior, and healing effects

## Source Files

**Base Class:** [`BehaviorModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DamageModule.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DamageModule.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Damage/DamageModule.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Damage/DamageModule.cpp)