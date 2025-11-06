# RadarUpdate

RadarUpdate provides radar functionality for objects that can detect or provide radar coverage.

## Overview

The `RadarUpdate` class manages radar operations including radar extension, coverage area management, and radar system activation. It handles radar extension timing, radar coverage activation, and provides radar system interface functionality. This update is commonly used by radar buildings, radar vehicles, and any objects that provide radar detection and coverage capabilities.

## Usage

Used by objects that can provide radar coverage, detect other objects, or manage radar systems. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Radar operations are limited by extension timing parameters
- Radar coverage depends on radar system capabilities and positioning
- Radar activation is controlled by extension sequence timing
- Radar effectiveness varies based on environmental conditions

**Conditions**:
- RadarUpdate manages radar extension and coverage activation sequences
- The update handles radar system activation and deactivation
- Radar extension timing controls the speed of radar operations
- Radar coverage provides detection capabilities for friendly units
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own radar parameters

**Dependencies**:
- Uses radar system for detection and coverage management
- Integrates with building animation system for radar extension

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Radar Extension Settings](#radar-extension-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Radar Extension Settings

#### `RadarExtendTime` *(v1.04)*
- **Type**: `Real` (milliseconds)
- **Description**: Time required to extend radar for full coverage activation. Higher values create slower radar extension. Lower values create faster radar extension
- **Default**: `0.0`
- **Example**: `RadarExtendTime = 4000`

## Examples

### Basic Radar Building
```ini
Behavior = RadarUpdate ModuleTag_Upgrade01
  RadarExtendTime = 4000
End
```

### Advanced Radar System
```ini
Behavior = RadarUpdate ModuleTag_Radar3
  RadarExtendTime   = 4000     ;in mSeconds
End
```

### Radar Upgrade
```ini
Behavior = RadarUpdate ModuleTag_11
  RadarExtendTime   = 4000     ;in mSeconds
End
```

## Template

```ini
Behavior = RadarUpdate ModuleTag_XX
  ; Radar Extension Settings
  RadarExtendTime = 0.0                ; // time to extend radar for coverage *(v1.04)*
End
```

## Notes

- RadarUpdate provides radar system management and coverage activation
- The update handles radar extension sequences for coverage activation
- Radar extension timing controls the responsiveness of radar operations
- This update is commonly used by radar buildings, radar vehicles, and detection systems
- Radar coverage provides essential detection capabilities for tactical operations

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RadarUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RadarUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/RadarUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/RadarUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet