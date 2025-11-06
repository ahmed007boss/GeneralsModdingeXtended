# QueueProductionExitUpdate

QueueProductionExitUpdate provides queue-based production exit functionality for objects that produce multiple units.

## Overview

The `QueueProductionExitUpdate` class manages queue-based production exit operations for buildings that produce multiple units in sequence. It handles unit creation points, rally points, exit delays, and airborne creation options for coordinated unit production and deployment. This update is commonly used by production buildings, barracks, and facilities that produce multiple units with proper exit coordination.

## Usage

Used by production buildings that need queue management for multiple unit production and exit coordination. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Production exit is limited by unit creation points and rally point positioning
- Exit delays control unit deployment timing and coordination
- Airborne creation depends on proper positioning and unit capabilities
- Initial burst production is limited by specified burst parameters

**Conditions**:
- QueueProductionExitUpdate manages queue-based unit production and exit coordination
- The update handles unit creation points and natural rally point positioning
- Exit delays ensure proper unit deployment sequencing
- Airborne creation options provide flexible unit deployment methods
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own production parameters

**Dependencies**:
- Uses production system for unit creation and queue management
- Integrates with positioning system for unit placement
- Uses exit interface for production exit coordination

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Positioning Settings](#positioning-settings)
  - [Exit Control Settings](#exit-control-settings)
  - [Production Settings](#production-settings)
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
- **Example**: `UnitCreatePoint = X:0.0 Y:-25.0 Z:0.0`

#### `NaturalRallyPoint` *(v1.04)*
- **Type**: `Coord3D`
- **Description**: 3D coordinates where produced units naturally rally after creation. When set, units move to specified rally point. When empty, uses default rally point
- **Default**: `X:0.0 Y:0.0 Z:0.0`
- **Example**: `NaturalRallyPoint = X:36.0 Y:-25.0 Z:0.0`

### Exit Control Settings

#### `ExitDelay` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Delay between unit exits for queue management. Higher values create longer delays between unit exits. Lower values allow faster unit deployment
- **Default**: `0`
- **Example**: `ExitDelay = 7000`

#### `AllowAirborneCreation` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether units can be created in airborne state. When true, units can spawn airborne. When false, units spawn on ground
- **Default**: `No`
- **Example**: `AllowAirborneCreation = Yes`

### Production Settings

#### `InitialBurst` *(v1.04)*
- **Type**: `UnsignedInt`
- **Description**: Number of units to produce in initial burst before normal queue processing. Higher values create larger initial bursts. Lower values create smaller bursts
- **Default**: `0`
- **Example**: `InitialBurst = 3`

## Examples

### Basic Queue Production
```ini
Behavior = QueueProductionExitUpdate ModuleTag_06
  UnitCreatePoint   = X:  0.0  Y:  0.0   Z:0.0
  NaturalRallyPoint = X: 0.0  Y:  0.0   Z:0.0
  ExitDelay     = 7000 ; 7 sec
End
```

### Advanced Queue Production
```ini
Behavior = QueueProductionExitUpdate ModuleTag_11
  UnitCreatePoint   = X:  0.0  Y:  -25.0   Z:0.0
  NaturalRallyPoint = X: 36.0  Y:  -25.0   Z:0.0;NaturalRallyPointX must always match GeometryMajorRadius! -ML
  ExitDelay = 300 ; Mainly for the multiple produced Red Guard.  Make them come out one at a time.
End
```

### Queue Production with Rally Point
```ini
Behavior = QueueProductionExitUpdate ModuleTag_09
  UnitCreatePoint   = X:  0.0  Y:  29.0   Z:0.0
  NaturalRallyPoint = X: 80.0  Y:  29.0   Z:0.0;NaturalRallyPointX must always match GeometryMajorRadius! -ML
  ExitDelay = 300 ; Mainly for the multiple produced Red Guard.  Make them come out one at a time.
End
```

## Template

```ini
Behavior = QueueProductionExitUpdate ModuleTag_XX
  ; Positioning Settings
  UnitCreatePoint = X:0.0 Y:0.0 Z:0.0     ; // 3D coordinates for unit creation *(v1.04)*
  NaturalRallyPoint = X:0.0 Y:0.0 Z:0.0   ; // 3D coordinates for unit rally point *(v1.04)*
  
  ; Exit Control Settings
  ExitDelay = 0                           ; // delay between unit exits *(v1.04)*
  AllowAirborneCreation = No              ; // allow airborne unit creation *(v1.04)*
  
  ; Production Settings
  InitialBurst = 0                        ; // number of units in initial burst *(v1.04)*
End
```

## Notes

- QueueProductionExitUpdate provides sophisticated queue-based unit production and exit coordination
- The update manages unit creation points and rally points for proper unit deployment
- Exit delays ensure coordinated unit deployment and prevent overcrowding
- Airborne creation options provide flexible unit deployment methods
- This update is commonly used by production buildings, barracks, and multi-unit production facilities
- Initial burst production allows for rapid initial unit deployment

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h), [`ExitInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/QueueProductionExitUpdate.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/QueueProductionExitUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/QueueProductionExitUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/QueueProductionExitUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/QueueProductionExitUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet