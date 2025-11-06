# ActiveShroudUpgrade

ActiveShroudUpgrade provides active shroud functionality for objects that can create or manage active shroud effects.

## Overview

The `ActiveShroudUpgrade` class manages active shroud operations for objects that can create active shroud effects, provide shroud coverage, or manage shroud-based systems. It handles shroud range enhancement, shroud activation, and shroud system integration. This upgrade is commonly used by objects that provide shroud coverage, shroud systems, and units with shroud capabilities.

## Usage

Used by objects that can create active shroud effects, provide shroud coverage, or manage shroud-based systems. This is an **upgrade module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Active shroud operations are limited by shroud range parameters and shroud system capabilities
- Shroud activation depends on proper upgrade system integration
- Shroud management is controlled by shroud parameters and system capabilities
- Shroud effectiveness varies based on shroud capabilities

**Conditions**:
- ActiveShroudUpgrade manages active shroud operations and shroud system coordination
- The upgrade handles shroud range enhancement, shroud activation, and shroud management
- Active shroud operations provide shroud coverage and shroud system capabilities
- Shroud management creates realistic shroud system operations
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own shroud parameters

**Dependencies**:
- Uses upgrade system for shroud upgrade activation
- Integrates with shroud system for shroud coverage
- Uses range system for shroud range management

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Shroud Settings](#shroud-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Shroud Settings

#### `NewShroudRange` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: New shroud range when upgrade is active. Higher values provide greater shroud coverage. Lower values provide smaller shroud coverage
- **Default**: `0.0`
- **Example**: `NewShroudRange = 9999.0`

## Examples

### Basic Active Shroud Upgrade
```ini
Behavior = ActiveShroudUpgrade ModuleTag_ShroudModule01
  TriggeredBy = Upgrade_GroundRadarDrone
  NewShroudRange = 9999.0
End
```

### Active Shroud Upgrade with Range
```ini
Behavior = ActiveShroudUpgrade ModuleTag_12
  TriggeredBy = Upgrade_RUSSIA
  RequiresAllTriggers = No
  NewShroudRange = 375.0
End
```

### Advanced Active Shroud Upgrade
```ini
Behavior = ActiveShroudUpgrade ModuleTag_03
  TriggeredBy = Upgrade_RUSSIA
  RequiresAllTriggers = No
  NewShroudRange = 375.0
End
```

## Template

```ini
Behavior = ActiveShroudUpgrade ModuleTag_XX
  ; Shroud Settings
  NewShroudRange = 0.0                ; // new shroud range when upgrade is active *(v1.04)*
End
```

## Notes

- ActiveShroudUpgrade provides active shroud operations and shroud system coordination capabilities
- The upgrade manages shroud range enhancement, shroud activation, and shroud management
- Active shroud operations provide essential shroud coverage and shroud system capabilities
- Shroud management creates realistic shroud system operations and coordination
- This upgrade is commonly used by objects that provide shroud coverage, shroud systems, and shroud capability units
- Shroud coordination ensures efficient shroud coverage and system integration operations

## Source Files

**Base Class:** [`UpgradeModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ActiveShroudUpgrade.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ActiveShroudUpgrade.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/ActiveShroudUpgrade.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/ActiveShroudUpgrade.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet