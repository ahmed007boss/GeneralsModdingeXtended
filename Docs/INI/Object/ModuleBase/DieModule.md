# DieModule

Abstract base class for all death handling modules in Command & Conquer Generals.

## Overview

DieModule is an abstract base class that provides the interface for death handling behavior with conditional activation based on death types, veterancy levels, and object status. It defines how objects respond when they die, with sophisticated filtering to determine when specific death behaviors should activate. This module is essential for implementing various death-related behaviors like spawn effects, resource recovery, and death notifications.

DieModule must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used as the foundation for all death handling modules that respond to object death events with configurable conditions and effects. This is an **abstract base class** that must be inherited by specific death implementations. Cannot be used directly in INI files - only concrete implementations can be used.

**Limitations**:
- Cannot be instantiated directly - must be inherited by specific death implementations
- Cannot be used in INI files - only concrete implementations are usable
- Requires concrete implementation of death callback method

**Conditions**:
- Multiple instances behavior: Multiple die modules can exist independently, each handling different death scenarios
- Always active once assigned to an object
- Callbacks are triggered by the death system when appropriate conditions are met

**Dependencies**:
- Requires proper death system integration
- Depends on the damage system for death information
- Relies on object status and veterancy systems for condition checking

## Properties

### Death Type Filtering

#### `DeathTypes` *(v1.04)*
- **Type**: `DeathTypeFlags` (see [DeathTypeFlags Values](#deathtypeflags-values) section)
- **Description**: Bit flags specifying which death types trigger this module. When set to specific death types, only objects dying from those causes will activate this module. When set to ALL, any death type will trigger the module
- **Default**: `DEATH_TYPE_FLAGS_ALL`
- **Example**: `DeathTypes = DEATH_TYPE_CRUSHED | DEATH_TYPE_SABOTAGED`

### Veterancy Level Filtering

#### `VeterancyLevels` *(v1.04)*
- **Type**: `VeterancyLevelFlags` (see [VeterancyLevelFlags Values](#veterancylevelflags-values) section)
- **Description**: Bit flags specifying which veterancy levels trigger this module. When set to specific levels, only objects with those veterancy levels will activate this module when they die. When set to ALL, any veterancy level will trigger the module
- **Default**: `VETERANCY_LEVEL_FLAGS_ALL`
- **Example**: `VeterancyLevels = VETERANCY_ELITE`

### Status Requirements

#### `RequiredStatus` *(v1.04)*
- **Type**: `ObjectStatusMaskType` (see [ObjectStatusMaskType Values](#objectstatusmasktype-values) section)
- **Description**: Bit flags specifying status conditions that must be present for the module to activate. When set, objects must have these status flags active to trigger the death behavior. When 0, no specific status is required
- **Default**: `0`
- **Example**: `RequiredStatus = OBJECT_STATUS_UNDER_CONSTRUCTION`

#### `ExemptStatus` *(v1.04)*
- **Type**: `ObjectStatusMaskType` (see [ObjectStatusMaskType Values](#objectstatusmasktype-values) section)
- **Description**: Bit flags specifying status conditions that prevent the module from activating. When set, objects with these status flags will not trigger the death behavior. When 0, no status exemptions apply
- **Default**: `0`
- **Example**: `ExemptStatus = OBJECT_STATUS_INVULNERABLE`

## Enum Value Lists

### DeathTypeFlags Values *(v1.04)*

- **`DEATH_TYPE_NORMAL`** *(v1.04)* - Normal death from damage
- **`DEATH_TYPE_CRUSHED`** *(v1.04)* - Death from being crushed
- **`DEATH_TYPE_SABOTAGED`** *(v1.04)* - Death from sabotage
- **`DEATH_TYPE_FROM_FALLING`** *(v1.04)* - Death from falling damage
- **`DEATH_TYPE_FROM_EXPLOSION`** *(v1.04)* - Death from explosion
- **`DEATH_TYPE_FROM_BEING_EATEN`** *(v1.04)* - Death from being eaten
- **`DEATH_TYPE_SUICIDE`** *(v1.04)* - Death from suicide
- **`DEATH_TYPE_BURNED`** *(v1.04)* - Death from burning
- **`DEATH_TYPE_DETONATED`** *(v1.04)* - Death from detonation
- **`DEATH_TYPE_FLAGS_ALL`** *(v1.04)* - All death types (default)

### VeterancyLevelFlags Values *(v1.04)*

- **`VETERANCY_REGULAR`** *(v1.04)* - Regular veterancy level
- **`VETERANCY_VETERAN`** *(v1.04)* - Veteran veterancy level
- **`VETERANCY_ELITE`** *(v1.04)* - Elite veterancy level
- **`VETERANCY_HEROIC`** *(v1.04)* - Heroic veterancy level
- **`VETERANCY_LEVEL_FLAGS_ALL`** *(v1.04)* - All veterancy levels (default)

### ObjectStatusMaskType Values *(v1.04)*

- **`OBJECT_STATUS_SOLD`** *(v1.04)* - Object is being sold
- **`OBJECT_STATUS_UNDER_CONSTRUCTION`** *(v1.04)* - Object is under construction
- **`OBJECT_STATUS_UNSELECTABLE`** *(v1.04)* - Object cannot be selected
- **`OBJECT_STATUS_DESTROYED`** *(v1.04)* - Object is destroyed
- **`OBJECT_STATUS_CAN_ATTACK`** *(v1.04)* - Object can attack
- **`OBJECT_STATUS_BRIDGE`** *(v1.04)* - Object is a bridge
- **`OBJECT_STATUS_FAERIE_FIRE`** *(v1.04)* - Object has faerie fire effect
- **`OBJECT_STATUS_UNDERGOING_REPAIR`** *(v1.04)* - Object is being repaired
- **`OBJECT_STATUS_RIDER1`** *(v1.04)* - Object has rider 1
- **`OBJECT_STATUS_RIDER2`** *(v1.04)* - Object has rider 2
- **`OBJECT_STATUS_RIDER3`** *(v1.04)* - Object has rider 3
- **`OBJECT_STATUS_RIDER4`** *(v1.04)* - Object has rider 4
- **`OBJECT_STATUS_RIDER5`** *(v1.04)* - Object has rider 5
- **`OBJECT_STATUS_RIDER6`** *(v1.04)* - Object has rider 6
- **`OBJECT_STATUS_RIDER7`** *(v1.04)* - Object has rider 7
- **`OBJECT_STATUS_RIDER8`** *(v1.04)* - Object has rider 8
- **`OBJECT_STATUS_NO_COLLISIONS`** *(v1.04)* - Object has no collisions
- **`OBJECT_STATUS_NO_GARRISON`** *(v1.04)* - Object cannot be garrisoned
- **`OBJECT_STATUS_IGNORING_STEALTH`** *(v1.04)* - Object ignores stealth
- **`OBJECT_STATUS_DETECTED`** *(v1.04)* - Object is detected
- **`OBJECT_STATUS_DISGUISED`** *(v1.04)* - Object is disguised
- **`OBJECT_STATUS_AIRBORNE_TARGET`** *(v1.04)* - Object is airborne target
- **`OBJECT_STATUS_MASKED`** *(v1.04)* - Object is masked
- **`OBJECT_STATUS_OPERATIONAL`** *(v1.04)* - Object is operational
- **`OBJECT_STATUS_UNDERGOING_DEPLOYMENT`** *(v1.04)* - Object is deploying
- **`OBJECT_STATUS_LOST`** *(v1.04)* - Object is lost
- **`OBJECT_STATUS_SOLD`** *(v1.04)* - Object is being sold
- **`OBJECT_STATUS_UNDER_CONSTRUCTION`** *(v1.04)* - Object is under construction
- **`OBJECT_STATUS_UNSELECTABLE`** *(v1.04)* - Object cannot be selected
- **`OBJECT_STATUS_DESTROYED`** *(v1.04)* - Object is destroyed
- **`OBJECT_STATUS_CAN_ATTACK`** *(v1.04)* - Object can attack
- **`OBJECT_STATUS_BRIDGE`** *(v1.04)* - Object is a bridge
- **`OBJECT_STATUS_FAERIE_FIRE`** *(v1.04)* - Object has faerie fire effect
- **`OBJECT_STATUS_UNDERGOING_REPAIR`** *(v1.04)* - Object is being repaired
- **`OBJECT_STATUS_RIDER1`** *(v1.04)* - Object has rider 1
- **`OBJECT_STATUS_RIDER2`** *(v1.04)* - Object has rider 2
- **`OBJECT_STATUS_RIDER3`** *(v1.04)* - Object has rider 3
- **`OBJECT_STATUS_RIDER4`** *(v1.04)* - Object has rider 4
- **`OBJECT_STATUS_RIDER5`** *(v1.04)* - Object has rider 5
- **`OBJECT_STATUS_RIDER6`** *(v1.04)* - Object has rider 6
- **`OBJECT_STATUS_RIDER7`** *(v1.04)* - Object has rider 7
- **`OBJECT_STATUS_RIDER8`** *(v1.04)* - Object has rider 8
- **`OBJECT_STATUS_NO_COLLISIONS`** *(v1.04)* - Object has no collisions
- **`OBJECT_STATUS_NO_GARRISON`** *(v1.04)* - Object cannot be garrisoned
- **`OBJECT_STATUS_IGNORING_STEALTH`** *(v1.04)* - Object ignores stealth
- **`OBJECT_STATUS_DETECTED`** *(v1.04)* - Object is detected
- **`OBJECT_STATUS_DISGUISED`** *(v1.04)* - Object is disguised
- **`OBJECT_STATUS_AIRBORNE_TARGET`** *(v1.04)* - Object is airborne target
- **`OBJECT_STATUS_MASKED`** *(v1.04)* - Object is masked
- **`OBJECT_STATUS_OPERATIONAL`** *(v1.04)* - Object is operational
- **`OBJECT_STATUS_UNDERGOING_DEPLOYMENT`** *(v1.04)* - Object is deploying
- **`OBJECT_STATUS_LOST`** *(v1.04)* - Object is lost

## Notes

- DieModule is an abstract base class that defines the death interface with conditional activation
- Concrete implementations handle specific death scenarios based on filtering conditions
- The onDie() callback is triggered when objects die and meet the specified conditions
- Sophisticated filtering system allows different death behaviors for different circumstances
- Essential for objects that need special death handling based on context
- Commonly used for spawn effects, resource recovery, death notifications, and conditional death behaviors
- The filtering system enables complex death scenarios based on how and when objects die

## Source Files

**Base Class:** [`BehaviorModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Die/DieModule.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Die/DieModule.cpp)
