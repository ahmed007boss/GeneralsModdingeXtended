# StatusBitsUpgrade

StatusBitsUpgrade provides the ability to set and clear object status flags when an upgrade is applied, allowing for dynamic status changes based on upgrade status.

## Overview

The `StatusBitsUpgrade` class manages object status flag changes when specific upgrades are applied. This upgrade module allows objects to have their status flags modified by setting or clearing specific status bits when the upgrade is activated. The behavior is commonly used for units that change their operational status, enter special states, or have status modifications that affect their behavior.

## Usage

Used by objects that need to change their status flags when upgrades are applied. This is an **upgrade module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Only affects object status flags, not other object properties
- Status changes are applied immediately when the upgrade is activated
- Objects must have status flag systems to function properly
- Status flags must be valid and supported

**Conditions**:
- StatusBitsUpgrade modifies object status flags when the specified upgrade is applied
- The upgrade integrates with the upgrade system for conditional activation
- Status flags can be both set and cleared in the same upgrade
- Status changes affect the object's behavior and capabilities
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own status changes

**Dependencies**:
- Requires an object with upgrade system integration
- Objects must have status flag systems to function properly
- The status flags must be valid and supported

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)

## Properties

### Status Flag Settings

#### `StatusToSet` *(v1.04)*
- **Type**: `ObjectStatusMaskType` (bit flags)
- **Description**: Object status flags to set when this upgrade is applied. These flags will be added to the object's current status, enabling new capabilities or states
- **Default**: `0` (no flags)
- **Example**: `StatusToSet = OBJECT_STATUS_CAN_ATTACK`

#### `StatusToClear` *(v1.04)*
- **Type**: `ObjectStatusMaskType` (bit flags)
- **Description**: Object status flags to clear when this upgrade is applied. These flags will be removed from the object's current status, disabling capabilities or states
- **Default**: `0` (no flags)
- **Example**: `StatusToClear = OBJECT_STATUS_UNDER_CONSTRUCTION`

## Examples

### Basic Status Flag Setting
```ini
Upgrade = StatusBitsUpgrade ModuleTag_StatusSet
  StatusToSet = OBJECT_STATUS_CAN_ATTACK
  TriggeredBy = Upgrade_WeaponTraining
End
```

### Status Flag Clearing
```ini
Upgrade = StatusBitsUpgrade ModuleTag_StatusClear
  StatusToClear = OBJECT_STATUS_UNDER_CONSTRUCTION
  TriggeredBy = Upgrade_ConstructionComplete
End
```

### Combined Status Changes
```ini
Upgrade = StatusBitsUpgrade ModuleTag_StatusChange
  StatusToSet = OBJECT_STATUS_CAN_ATTACK OBJECT_STATUS_ACTIVE
  StatusToClear = OBJECT_STATUS_UNDER_CONSTRUCTION OBJECT_STATUS_DISABLED
  TriggeredBy = Upgrade_Activation
End
```

### Conditional Status Modification
```ini
Upgrade = StatusBitsUpgrade ModuleTag_ConditionalStatus
  StatusToSet = OBJECT_STATUS_ELITE
  StatusToClear = OBJECT_STATUS_BASIC
  TriggeredBy = Upgrade_EliteTraining
  ConflictsWith = Upgrade_BasicTraining
End
```

## Template

```ini
Upgrade = StatusBitsUpgrade ModuleTag_XX
  ; Status Flag Settings
  StatusToSet =                     ; // status flags to set *(v1.04)*
  StatusToClear =                   ; // status flags to clear *(v1.04)*
  
  ; Upgrade Integration (inherited from UpgradeModule)
  TriggeredBy =                     ; // required upgrade flags *(v1.04)*
  ConflictsWith =                   ; // conflicting upgrade flags *(v1.04)*
  RequiresAll = No                  ; // require all TriggeredBy upgrades *(v1.04)*
End
```

## Notes

- StatusBitsUpgrade modifies object status flags when the specified upgrade is applied
- The upgrade integrates with the upgrade system for conditional activation
- Status flags can be both set and cleared in the same upgrade
- Status changes affect the object's behavior and capabilities
- Only affects object status flags, not other object properties
- Status changes are applied immediately when the upgrade is activated
- Objects must have status flag systems to function properly
- Status flags must be valid and supported
- The upgrade can modify multiple status flags simultaneously

## Source Files

**Base Class:** [`UpgradeModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StatusBitsUpgrade.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StatusBitsUpgrade.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/StatusBitsUpgrade.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/StatusBitsUpgrade.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet
