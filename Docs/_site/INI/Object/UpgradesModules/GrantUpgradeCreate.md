# GrantUpgradeCreate

GrantUpgradeCreate provides the ability to automatically grant upgrades to players or objects when they are created, allowing for automatic upgrade distribution based on object creation.

## Overview

The `GrantUpgradeCreate` class manages automatic upgrade granting when objects are created. This create module allows objects to automatically grant upgrades to either the controlling player or the object itself upon creation, providing a way to distribute upgrades without manual intervention. The behavior supports both player upgrades and object upgrades, with conditional execution based on object status.

## Usage

Used by objects that need to automatically grant upgrades when they are created. This is a **create module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Only grants upgrades upon object creation or build completion
- The upgrade must exist in the game's upgrade system
- Upgrades are granted immediately when conditions are met
- Cannot grant upgrades to other objects or players

**Conditions**:
- GrantUpgradeCreate automatically grants upgrades when the object is created
- The upgrade can be granted to either the player or the object itself
- Conditional execution based on object status (ExemptStatus)
- The upgrade is granted when the object is no longer under construction
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own upgrade granting

**Dependencies**:
- Requires an object with create module system integration
- The upgrade must exist in the game's upgrade system
- Objects must have proper player or upgrade system integration
- The upgrade center must be available for upgrade lookup

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

### Upgrade Granting Settings

#### `UpgradeToGrant` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: The name of the upgrade to be granted when the object is created. This must be a valid upgrade template that exists in the game's upgrade system. The upgrade will be granted to either the player or the object depending on the upgrade type
- **Default**: `""` (empty)
- **Example**: `UpgradeToGrant = "Upgrade_EliteTraining"`

#### `ExemptStatus` *(v1.04)*
- **Type**: `ObjectStatusMaskType` (bit flags)
- **Description**: Object status flags that prevent the upgrade from being granted. When the object has any of these status flags, the upgrade will not be granted. This allows for conditional upgrade granting based on object state
- **Default**: `0` (no exemptions)
- **Example**: `ExemptStatus = OBJECT_STATUS_UNDER_CONSTRUCTION`

## Examples

### Basic Player Upgrade Grant
```ini
Create = GrantUpgradeCreate ModuleTag_GrantUpgrade
  UpgradeToGrant = "Upgrade_EliteTraining"
  ExemptStatus = OBJECT_STATUS_UNDER_CONSTRUCTION
End
```

### Object Upgrade Grant
```ini
Create = GrantUpgradeCreate ModuleTag_GrantObjectUpgrade
  UpgradeToGrant = "Upgrade_WeaponTraining"
  ExemptStatus = OBJECT_STATUS_UNDER_CONSTRUCTION
End
```

### Conditional Upgrade Grant
```ini
Create = GrantUpgradeCreate ModuleTag_ConditionalGrant
  UpgradeToGrant = "Upgrade_AdvancedTechnology"
  ExemptStatus = OBJECT_STATUS_UNDER_CONSTRUCTION OBJECT_STATUS_DISABLED
End
```

### Multiple Upgrade Grants
```ini
Create = GrantUpgradeCreate ModuleTag_GrantUpgrade1
  UpgradeToGrant = "Upgrade_BasicTraining"
  ExemptStatus = OBJECT_STATUS_UNDER_CONSTRUCTION
End

Create = GrantUpgradeCreate ModuleTag_GrantUpgrade2
  UpgradeToGrant = "Upgrade_AdvancedTraining"
  ExemptStatus = OBJECT_STATUS_UNDER_CONSTRUCTION
End
```

## Template

```ini
Create = GrantUpgradeCreate ModuleTag_XX
  ; Upgrade Granting Settings
  UpgradeToGrant =                    ; // name of upgrade to grant *(v1.04)*
  ExemptStatus =                      ; // status flags that prevent granting *(v1.04)*
End
```

## Notes

- GrantUpgradeCreate automatically grants upgrades when the object is created
- The upgrade can be granted to either the player or the object itself
- Conditional execution based on object status (ExemptStatus)
- The upgrade is granted when the object is no longer under construction
- Only grants upgrades upon object creation or build completion
- The upgrade must exist in the game's upgrade system
- Upgrades are granted immediately when conditions are met
- Cannot grant upgrades to other objects or players
- The upgrade type determines whether it's granted to the player or the object

## Source Files

**Base Class:** [`CreateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/GrantUpgradeCreate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/GrantUpgradeCreate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Create/GrantUpgradeCreate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Create/GrantUpgradeCreate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet
