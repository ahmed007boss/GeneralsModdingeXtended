# SupplyCenterProductionExitUpdate

SupplyCenterProductionExitUpdate provides production exit functionality specifically for supply center facilities.

## Overview

The `SupplyCenterProductionExitUpdate` class manages production exit operations for supply center buildings that need specialized exit mechanics for supply-related units. It handles unit creation points, rally points, and supply center exit coordination. This update is commonly used by supply center buildings, resource production facilities, and objects that provide supply-related unit production.

## Usage

Used by supply center buildings that need specialized exit mechanics for supply-related units. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Supply center production exit is limited by unit creation points and rally point positioning
- Exit coordination depends on proper supply center integration
- Unit creation depends on proper positioning and supply center configuration
- Exit effectiveness varies based on supply center capabilities

**Conditions**:
- SupplyCenterProductionExitUpdate manages supply center production exit and unit coordination
- The update handles unit creation points, rally points, and supply center exit coordination
- Production exit provides supply-related unit production and deployment capabilities
- Unit creation points control unit placement and supply center operations
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own supply parameters

**Dependencies**:
- Uses production system for unit creation and exit coordination
- Integrates with positioning system for unit placement
- Uses exit interface for production exit coordination

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Positioning Settings](#positioning-settings)
  - [Supply Settings](#supply-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Positioning Settings

#### `UnitCreatePoint` *(v1.04)*
- **Type**: `Coord3D`
- **Description**: 3D coordinates where produced units are created. When set, units spawn at specified coordinates. When empty, uses default creation point
- **Default**: `X:0.0 Y:0.0 Z:0.0`
- **Example**: `UnitCreatePoint = X:0.0 Y:0.0 Z:0.0`

#### `NaturalRallyPoint` *(v1.04)*
- **Type**: `Coord3D`
- **Description**: 3D coordinates where produced units naturally rally after creation. When set, units move to specified rally point. When empty, uses default rally point
- **Default**: `X:0.0 Y:0.0 Z:0.0`
- **Example**: `NaturalRallyPoint = X:36.0 Y:0.0 Z:0.0`

### Supply Settings

#### `GrantTemporaryStealth` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Duration of temporary stealth granted during supply operations. Higher values grant longer stealth. Lower values grant shorter stealth
- **Default**: `0`
- **Example**: `GrantTemporaryStealth = 20000`

## Examples

### Basic Supply Center Production Exit
```ini
Behavior = SupplyCenterProductionExitUpdate ModuleTag_11
  UnitCreatePoint   = X:  0.0  Y:  0.0   Z:0.0
  NaturalRallyPoint = X: 36.0  Y:  0.0   Z:0.0;NaturalRallyPointX must always match GeometryMajorRadius! -ML
  ;GrantTemporaryStealth = 20000
End
```

### Supply Center Production Exit with Rally Point
```ini
Behavior = SupplyCenterProductionExitUpdate ModuleTag_11
  UnitCreatePoint   = X:  0.0  Y:  0.0   Z:0.0
  NaturalRallyPoint = X: 52.0  Y:  0.0   Z:0.0;NaturalRallyPointX must always match GeometryMajorRadius! -ML
End
```

### Supply Center Production Exit with Offset
```ini
Behavior = SupplyCenterProductionExitUpdate ModuleTag_11
  UnitCreatePoint   = X:  0.0  Y:  25.0   Z:0.0
  NaturalRallyPoint = X: 60.0  Y:  25.0   Z:0.0;NaturalRallyPointX must always match GeometryMajorRadius! -ML
End
```

## Template

```ini
Behavior = SupplyCenterProductionExitUpdate ModuleTag_XX
  ; Positioning Settings
  UnitCreatePoint = X:0.0 Y:0.0 Z:0.0     ; // 3D coordinates for unit creation *(v1.04)*
  NaturalRallyPoint = X:0.0 Y:0.0 Z:0.0   ; // 3D coordinates for unit rally point *(v1.04)*
  
  ; Supply Settings
  GrantTemporaryStealth = 0              ; // duration of temporary stealth granted *(v1.04)*
End
```

## Notes

- SupplyCenterProductionExitUpdate provides specialized production exit capabilities for supply center facilities
- The update manages unit creation points, rally points, and supply center exit coordination
- Production exit provides supply-related unit production and deployment capabilities
- Unit creation points control unit placement and supply center operations
- This update is commonly used by supply center buildings, resource production facilities, and supply-related production units
- Supply center exit coordination ensures efficient unit production and deployment

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h), [`ExitInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyCenterProductionExitUpdate.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyCenterProductionExitUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyCenterProductionExitUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/SupplyCenterProductionExitUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/SupplyCenterProductionExitUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet