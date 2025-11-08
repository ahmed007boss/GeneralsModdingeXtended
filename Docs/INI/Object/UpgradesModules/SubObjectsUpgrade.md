# SubObjectsUpgrade

SubObjectsUpgrade provides the ability to show or hide sub-objects when an upgrade is applied, allowing for dynamic visual changes and sub-object visibility control.

## Overview

The `SubObjectsUpgrade` class manages sub-object visibility when specific upgrades are applied. This upgrade module allows objects to show or hide specific sub-objects when the upgrade is activated, providing a way to change the visual appearance of objects. The behavior is commonly used for units that gain new visual elements, buildings that show additional components, or objects that change their appearance based on upgrade status.

## Usage

Used by objects that need to show or hide sub-objects when upgrades are applied. This is an **upgrade module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Only affects sub-object visibility, not other object properties
- Sub-object names must match existing sub-objects in the model
- Visibility changes are applied immediately when the upgrade is activated
- Objects must have sub-object systems to function properly

**Conditions**:
- SubObjectsUpgrade shows or hides sub-objects when the specified upgrade is applied
- The upgrade integrates with the upgrade system for conditional activation
- Sub-object visibility changes override animation sub-object states
- Multiple sub-objects can be shown or hidden in the same upgrade
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own sub-object visibility changes

**Dependencies**:
- Requires an object with upgrade system integration
- Objects must have sub-object systems to function properly
- Sub-object names must match existing sub-objects in the model

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

### Sub-Object Visibility Settings

#### `ShowSubObject` *(v1.04)*
- **Type**: `AsciiString` (multiple entries)
- **Description**: Names of sub-objects to show when this upgrade is applied. These sub-objects will become visible when the upgrade is activated. Multiple entries can be specified
- **Default**: `""` (empty)
- **Example**: `ShowSubObject = "EliteWeapon"`

#### `HideSubObject` *(v1.04)*
- **Type**: `AsciiString` (multiple entries)
- **Description**: Names of sub-objects to hide when this upgrade is applied. These sub-objects will become invisible when the upgrade is activated. Multiple entries can be specified
- **Default**: `""` (empty)
- **Example**: `HideSubObject = "BasicWeapon"`

## Examples

### Basic Sub-Object Showing
```ini
Upgrade = SubObjectsUpgrade ModuleTag_ShowSubObject
  ShowSubObject = "EliteWeapon"
  TriggeredBy = Upgrade_EliteTraining
End
```

### Sub-Object Hiding
```ini
Upgrade = SubObjectsUpgrade ModuleTag_HideSubObject
  HideSubObject = "BasicWeapon"
  TriggeredBy = Upgrade_WeaponUpgrade
End
```

### Multiple Sub-Object Changes
```ini
Upgrade = SubObjectsUpgrade ModuleTag_MultiSubObject
  ShowSubObject = "EliteWeapon"
  ShowSubObject = "EliteArmor"
  HideSubObject = "BasicWeapon"
  HideSubObject = "BasicArmor"
  TriggeredBy = Upgrade_EliteTraining
End
```

### Conditional Sub-Object Visibility
```ini
Upgrade = SubObjectsUpgrade ModuleTag_ConditionalSubObject
  ShowSubObject = "AdvancedComponent"
  HideSubObject = "BasicComponent"
  TriggeredBy = Upgrade_AdvancedTraining
  ConflictsWith = Upgrade_BasicTraining
End
```

## Template

```ini
Upgrade = SubObjectsUpgrade ModuleTag_XX
  ; Sub-Object Visibility Settings
  ShowSubObject =                    ; // sub-object to show *(v1.04)*
  ShowSubObject =                    ; // additional sub-object to show *(v1.04)*
  HideSubObject =                    ; // sub-object to hide *(v1.04)*
  HideSubObject =                    ; // additional sub-object to hide *(v1.04)*
  
  ; Upgrade Integration (inherited from UpgradeModule)
  TriggeredBy =                      ; // required upgrade flags *(v1.04)*
  ConflictsWith =                    ; // conflicting upgrade flags *(v1.04)*
  RequiresAll = No                   ; // require all TriggeredBy upgrades *(v1.04)*
End
```

## Notes

- SubObjectsUpgrade shows or hides sub-objects when the specified upgrade is applied
- The upgrade integrates with the upgrade system for conditional activation
- Sub-object visibility changes override animation sub-object states
- Multiple sub-objects can be shown or hidden in the same upgrade
- Only affects sub-object visibility, not other object properties
- Sub-object names must match existing sub-objects in the model
- Visibility changes are applied immediately when the upgrade is activated
- Objects must have sub-object systems to function properly
- The upgrade can show and hide different sub-objects simultaneously

## Source Files

**Base Class:** [`UpgradeModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SubObjectsUpgrade.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SubObjectsUpgrade.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/SubObjectsUpgrade.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/SubObjectsUpgrade.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet
