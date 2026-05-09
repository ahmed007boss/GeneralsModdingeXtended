# RepairDockUpdate

RepairDockUpdate provides docking functionality specifically for repair facilities and repair operations.

## Overview

The `RepairDockUpdate` class manages docking operations for objects that need to dock with repair facilities for maintenance and repair operations. It handles repair-specific docking mechanics including healing time, repair coordination, and maintenance operations. This update is commonly used by repair facilities, maintenance buildings, and objects that provide repair services.

## Usage

Used by objects that need to dock with repair facilities for maintenance and repair operations. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Repair operations are limited by healing time parameters
- Repair coordination depends on proper repair facility integration
- Docking operations are controlled by repair-specific timing parameters
- Repair effectiveness varies based on facility capabilities

**Conditions**:
- RepairDockUpdate manages repair-specific docking and maintenance operations
- The update handles healing time calculations for repair coordination
- Repair operations provide maintenance and healing capabilities
- Docking creates realistic repair facility operations
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own repair parameters

**Dependencies**:
- Extends DockUpdate for base docking functionality
- Requires repair system integration for healing operations
- Uses dock interface for docking operations

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Repair Settings](#repair-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Repair Settings

#### `TimeForFullHeal` *(v1.04)*
- **Type**: `Real` (milliseconds)
- **Description**: Time required to fully heal a docked object. Higher values create slower healing. Lower values create faster healing
- **Default**: `0.0`
- **Example**: `TimeForFullHeal = 5000`

## Examples

### Basic Repair Dock
```ini
Behavior = RepairDockUpdate ModuleTag_09
  TimeForFullHeal   = 5000   ;(in milliseconds)     
  NumberApproachPositions = 5
End
```

### Advanced Repair Dock
```ini
Behavior = RepairDockUpdate ModuleTag_14
  TimeForFullHeal   = 5000   ;(in milliseconds)     
  NumberApproachPositions = 5
End
```

### Repair Dock with Passthrough
```ini
Behavior = RepairDockUpdate ModuleTag_05
  TimeForFullHeal   = 5000   ;(in milliseconds)   
  AllowsPassthrough = Yes 
  NumberApproachPositions = 5
End
```

## Template

```ini
Behavior = RepairDockUpdate ModuleTag_XX
  ; Repair Settings
  TimeForFullHeal = 0.0                  ; // time required for full healing *(v1.04)*
End
```

## Notes

- RepairDockUpdate extends DockUpdate with specialized repair facility docking mechanics
- The update provides healing time management for repair operations
- Repair operations create realistic maintenance and healing capabilities
- This update is commonly used by repair facilities, maintenance buildings, and repair stations
- Healing time controls the effectiveness and speed of repair operations

## Source Files

**Base Class:** [`DockUpdate`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DockUpdate.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RepairDockUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RepairDockUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/DockUpdate/RepairDockUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/DockUpdate/RepairDockUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet