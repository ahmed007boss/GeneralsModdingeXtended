# OCLUpdate

OCLUpdate provides Object Creation List functionality for objects that can spawn other objects over time.

## Overview

The `OCLUpdate` class manages Object Creation List (OCL) spawning mechanics that allow objects to create other objects at specified intervals. It handles delayed object creation, faction-specific OCL variations, and provides countdown feedback for timing. This update is commonly used by buildings, vehicles, and special objects that need to spawn units, effects, or other objects over time.

## Usage

Used by objects that need to spawn other objects using Object Creation Lists at specified intervals. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Object creation is limited by OCL templates and faction variations
- Spawning timing is controlled by minimum and maximum delay parameters
- Edge creation requires proper positioning and boundary detection
- Faction triggering depends on proper faction identification

**Conditions**:
- OCLUpdate manages delayed object creation using Object Creation Lists
- The update handles faction-specific OCL variations for different civilizations
- Random delay ranges create varied spawning patterns
- Edge creation places spawned objects at map boundaries
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own spawning parameters

**Dependencies**:
- Requires Object Creation List templates for spawning objects
- Uses faction system for civilization-specific variations
- Integrates with positioning system for edge creation

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [OCL Settings](#ocl-settings)
  - [Timing Settings](#timing-settings)
  - [Creation Settings](#creation-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### OCL Settings

#### `OCL` *(v1.04)*
- **Type**: `ObjectCreationList`
- **Description**: Default Object Creation List to use for spawning objects. When set, spawns objects from this list. When empty, no default spawning occurs
- **Default**: `NULL`
- **Example**: `OCL = OCL_SupplyCrate`

#### `FactionOCL` *(v1.04)*
- **Type**: `FactionOCLList` (vector)
- **Description**: Faction-specific Object Creation Lists that override the default OCL. When set, uses faction-specific lists. When empty, uses default OCL for all factions
- **Default**: `""`
- **Example**: `FactionOCL = USA:OCL_USASupplyCrate China:OCL_ChinaSupplyCrate GLA:OCL_GLASupplyCrate`

### Timing Settings

#### `MinDelay` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Minimum delay between OCL spawns. Higher values create longer minimum delays. Lower values allow faster spawning
- **Default**: `0`
- **Example**: `MinDelay = 30000`

#### `MaxDelay` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Maximum delay between OCL spawns. Higher values create longer maximum delays. Lower values create shorter delays
- **Default**: `0`
- **Example**: `MaxDelay = 60000`

### Creation Settings

#### `CreateAtEdge` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether to create spawned objects at map edges. When true, objects spawn at map boundaries. When false, objects spawn at normal positions
- **Default**: `No`
- **Example**: `CreateAtEdge = Yes`

#### `FactionTriggered` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether OCL spawning is triggered by faction-specific conditions. When true, uses faction triggers. When false, uses default spawning logic
- **Default**: `No`
- **Example**: `FactionTriggered = Yes`

## Examples

### Basic Supply Crate Spawner
```ini
Behavior = OCLUpdate ModuleTag_03
  OCL = OCL_SupplyCrate
  MinDelay = 30000
  MaxDelay = 60000
End
```

### Faction-Specific Spawner
```ini
Behavior = OCLUpdate ModuleTag_04
  OCL = OCL_DefaultCrate
  FactionOCL = USA:OCL_USASupplyCrate China:OCL_ChinaSupplyCrate GLA:OCL_GLASupplyCrate
  MinDelay = 45000
  MaxDelay = 90000
  CreateAtEdge = Yes
End
```

### Edge Spawner
```ini
Behavior = OCLUpdate ModuleTag_05
  OCL = OCL_EdgeSpawn
  MinDelay = 20000
  MaxDelay = 40000
  CreateAtEdge = Yes
  FactionTriggered = Yes
End
```

## Template

```ini
Behavior = OCLUpdate ModuleTag_XX
  ; OCL Settings
  OCL =                                 ; // default object creation list *(v1.04)*
  FactionOCL =                          ; // faction-specific OCL variations *(v1.04)*
  
  ; Timing Settings
  MinDelay = 0                          ; // minimum delay between spawns *(v1.04)*
  MaxDelay = 0                          ; // maximum delay between spawns *(v1.04)*
  
  ; Creation Settings
  CreateAtEdge = No                     ; // spawn objects at map edges *(v1.04)*
  FactionTriggered = No                 ; // use faction-specific triggers *(v1.04)*
End
```

## Notes

- OCLUpdate provides flexible object spawning mechanics using Object Creation Lists
- The update supports faction-specific variations for different civilizations
- Random delay ranges create varied and unpredictable spawning patterns
- Edge creation allows objects to spawn at map boundaries for strategic placement
- This update is commonly used by supply buildings, resource generators, and spawn points
- Countdown feedback provides timing information for spawned object creation

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/OCLUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/OCLUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/OCLUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/OCLUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet