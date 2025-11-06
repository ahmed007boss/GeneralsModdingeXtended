# RebuildHoleExposeDie

Die module that provides death mechanics for exposing rebuild holes when structures are destroyed, allowing them to be rebuilt.

## Overview

RebuildHoleExposeDie is a die module that provides death mechanics for exposing rebuild holes when structures are destroyed. It creates rebuild holes at the location of destroyed structures, allowing them to be rebuilt by workers. The module supports configurable hole types and maximum health values for the exposed holes.

RebuildHoleExposeDie must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by structures that create rebuild holes when destroyed, allowing them to be rebuilt. This is a **die module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Requires valid hole object templates for rebuild functionality
- Cannot function without proper death system
- Hole exposure is limited to structure destruction events
- Requires proper hole health configuration for rebuilding

**Conditions**:
- Multiple instances behavior: Multiple RebuildHoleExposeDie modules can exist independently, each exposing different hole types
- Always active once assigned to an object
- Triggers during death events to expose rebuild holes
- Creates rebuild opportunities for destroyed structures

**Dependencies**:
- Depends on the death system for triggering hole exposure
- Requires proper hole object templates for rebuilding operations
- Inherits all functionality from DieModule

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Hole Configuration](#hole-configuration)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

### Hole Configuration

#### `HoleName` *(v1.04)*
- **Type**: `AsciiString` (see [Object documentation](../Object.md))
- **Description**: Name of the rebuild hole object template to create when the structure is destroyed. When set, creates a rebuild hole at the structure's location. When empty (default), no rebuild hole is created
- **Default**: `""` (empty)
- **Example**: `HoleName = GLAHoleRadarStation`

#### `HoleMaxHealth` *(v1.04)*
- **Type**: `Real`
- **Description**: Maximum health points for the rebuild hole. Higher values make the hole more durable and require more work to rebuild. Lower values make the hole easier to rebuild but more vulnerable. At 500 (default), the hole has 500 health points
- **Default**: `500.0`
- **Example**: `HoleMaxHealth = 500`

## Examples

### Basic Rebuild Hole Exposure
```ini
Behavior = RebuildHoleExposeDie ModuleTag_Death04
  HoleName = GLAHoleRadarStation
  HoleMaxHealth = 500
End
```

### High Health Rebuild Hole
```ini
Behavior = RebuildHoleExposeDie ModuleTag_08
  HoleName = GLAHoleAirfield
  HoleMaxHealth = 1000
End
```

### Low Health Rebuild Hole
```ini
Behavior = RebuildHoleExposeDie ModuleTag_321
  HoleName = GLAHoleArtilleryBunker
  HoleMaxHealth = 250
End
```

## Template

```ini
Behavior = RebuildHoleExposeDie ModuleTag_XX
  ; Hole Configuration
  HoleName =                         ; // rebuild hole object template *(v1.04)*
  HoleMaxHealth = 500.0              ; // maximum health of the rebuild hole *(v1.04)*
End
```

## Notes

- RebuildHoleExposeDie creates rebuild holes when structures are destroyed
- The module allows destroyed structures to be rebuilt by workers
- Hole health determines how much work is required to rebuild the structure
- This creates realistic rebuilding mechanics for destroyed buildings

## Source Files

**Base Class:** [`DieModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Die/RebuildHoleExposeDie.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Die/RebuildHoleExposeDie.cpp)
