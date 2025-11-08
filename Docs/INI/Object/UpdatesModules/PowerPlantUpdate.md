# PowerPlantUpdate

PowerPlantUpdate provides power plant functionality for objects that can generate power or manage power systems.

## Overview

The `PowerPlantUpdate` class manages power plant operations including rod extension mechanics, power generation control, and power plant interface functionality. It handles the extension and retraction of control rods to regulate power output and provides interface methods for external power plant control. This update is commonly used by nuclear power plants, conventional power plants, and other power generation facilities.

## Usage

Used by power plant buildings and structures that need to manage power generation and distribution. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Power plant operations are limited by rod extension timing parameters
- Power generation control depends on rod extension state
- Interface functionality is limited to rod extension control
- Power output is controlled by rod positioning

**Conditions**:
- PowerPlantUpdate manages control rod extension and retraction sequences
- The update handles power generation regulation through rod control
- Rod extension timing controls the speed of power plant operations
- Power plant interface provides external control capabilities
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own rod control parameters

**Dependencies**:
- Uses power system integration for power generation
- Integrates with building animation system for rod movements

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Rod Control Settings](#rod-control-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Rod Control Settings

#### `RodsExtendTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time required to extend control rods for power regulation. Higher values create slower rod extension. Lower values create faster rod extension
- **Default**: `0`
- **Example**: `RodsExtendTime = 1500`

## Examples

### Basic Power Plant
```ini
Behavior = PowerPlantUpdate ModuleTag_ED01b
  RodsExtendTime = 1500
End
```

### Fast Power Plant
```ini
Behavior = PowerPlantUpdate ModuleTag_ED01b
  RodsExtendTime = 500
End
```

### Nuclear Power Plant
```ini
Behavior = PowerPlantUpdate ModuleTag_09
  RodsExtendTime = 600
End
```

## Template

```ini
Behavior = PowerPlantUpdate ModuleTag_XX
  ; Rod Control Settings
  RodsExtendTime = 0                    ; // time to extend control rods *(v1.04)*
End
```

## Notes

- PowerPlantUpdate provides control rod management for power plant operations
- The update handles power generation regulation through rod extension control
- Rod extension timing controls the responsiveness of power plant operations
- This update is commonly used by nuclear power plants, conventional power plants, and power generation facilities
- Power plant interface allows external systems to control rod operations

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h), [`PowerPlantUpdateInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/PowerPlantUpdate.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/PowerPlantUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/PowerPlantUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/PowerPlantUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/PowerPlantUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet