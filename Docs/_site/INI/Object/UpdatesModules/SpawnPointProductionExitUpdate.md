# SpawnPointProductionExitUpdate

SpawnPointProductionExitUpdate provides spawn point-based production exit functionality for objects.

## Overview

The `SpawnPointProductionExitUpdate` class manages spawn point-based production exit operations for buildings that use specific spawn points for unit exit and deployment. It handles spawn point positioning, unit creation at specific locations, and spawn point-based exit coordination. This update is commonly used by production buildings, barracks, and facilities that use designated spawn points for unit deployment.

## Usage

Used by production buildings that use specific spawn points for unit exit and deployment. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Spawn point operations are limited by spawn point bone positioning and availability
- Unit creation depends on proper spawn point bone configuration
- Exit coordination requires proper spawn point integration
- Spawn point effectiveness varies based on bone positioning and object geometry

**Conditions**:
- SpawnPointProductionExitUpdate manages spawn point-based unit production and exit coordination
- The update handles spawn point bone positioning for unit creation and deployment
- Spawn point operations provide precise unit placement and exit coordination
- Spawn point bones control unit creation locations and deployment positioning
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own spawn point parameters

**Dependencies**:
- Uses production system for unit creation and exit coordination
- Integrates with bone system for spawn point positioning
- Uses exit interface for production exit coordination

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Spawn Point Settings](#spawn-point-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Spawn Point Settings

#### `SpawnPointBoneName` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Name of the bone used as spawn point for unit creation. When set, units spawn at specified bone location. When empty, uses default spawn point
- **Default**: `""`
- **Example**: `SpawnPointBoneName = Tripod`

## Examples

### Basic Spawn Point Production
```ini
Behavior = SpawnPointProductionExitUpdate ModuleTag_05
  SpawnPointBoneName = Tripod
End
```

### Spawn Point Production with Named Bone
```ini
Behavior = SpawnPointProductionExitUpdate ModuleTag_Defender02
  SpawnPointBoneName = SpawnPoint
End
```

### Spawn Point Production with Standard Bone
```ini
Behavior = SpawnPointProductionExitUpdate ModuleTag_06
  SpawnPointBoneName = SpawnPoint
End
```

## Template

```ini
Behavior = SpawnPointProductionExitUpdate ModuleTag_XX
  ; Spawn Point Settings
  SpawnPointBoneName =                    ; // name of bone used as spawn point *(v1.04)*
End
```

## Notes

- SpawnPointProductionExitUpdate provides precise spawn point-based unit production and exit coordination
- The update manages spawn point bone positioning for accurate unit placement
- Spawn point bones control unit creation locations and deployment positioning
- This update is commonly used by production buildings, barracks, and facilities with designated spawn points
- Spawn point operations provide precise unit placement and exit coordination for tactical positioning

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h), [`ExitInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpawnPointProductionExitUpdate.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpawnPointProductionExitUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpawnPointProductionExitUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/SpawnPointProductionExitUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/SpawnPointProductionExitUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet