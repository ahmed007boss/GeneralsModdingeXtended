# ObjectCreationUpgrade

ObjectCreationUpgrade provides the ability to create objects using ObjectCreationList (OCL) when an upgrade is applied, allowing for dynamic object spawning based on upgrade status.

## Overview

The `ObjectCreationUpgrade` class manages object creation when specific upgrades are applied. This upgrade module allows objects to spawn other objects using ObjectCreationList (OCL) when the upgrade is activated, providing a way to create additional units, structures, or effects. The behavior is commonly used for buildings that spawn units, units that create support objects, or special effects that generate additional game elements.

## Usage

Used by objects that need to create other objects when upgrades are applied. This is an **upgrade module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Only creates objects using ObjectCreationList (OCL)
- The OCL must exist and be properly defined
- Object creation occurs immediately when the upgrade is activated
- Created objects are owned by the same player as the upgrading object

**Conditions**:
- ObjectCreationUpgrade creates objects when the specified upgrade is applied
- The upgrade integrates with the upgrade system for conditional activation
- Objects are created using the specified ObjectCreationList (OCL)
- Created objects are owned by the same player as the upgrading object
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own object creation

**Dependencies**:
- Requires an object with upgrade system integration
- The ObjectCreationList (OCL) must exist and be properly defined
- Objects must have proper player system integration
- The object creation system must be available

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

### Object Creation Settings

#### `UpgradeObject` *(v1.04)*
- **Type**: `ObjectCreationList`
- **Description**: The ObjectCreationList (OCL) to use for creating objects when this upgrade is applied. This OCL defines what objects to create, where to create them, and how many to create. The OCL must exist and be properly defined
- **Default**: `NULL` (none)
- **Example**: `UpgradeObject = OCL_EliteUnitSpawn`

## Examples

### Basic Unit Spawning
```ini
Upgrade = ObjectCreationUpgrade ModuleTag_UnitSpawn
  UpgradeObject = OCL_EliteUnitSpawn
  TriggeredBy = Upgrade_EliteTraining
End
```

### Structure Creation
```ini
Upgrade = ObjectCreationUpgrade ModuleTag_StructureCreation
  UpgradeObject = OCL_SupportStructure
  TriggeredBy = Upgrade_SupportTraining
End
```

### Multiple Object Creation
```ini
Upgrade = ObjectCreationUpgrade ModuleTag_MultiCreation
  UpgradeObject = OCL_MultipleUnits
  TriggeredBy = Upgrade_MultiTraining
End
```

### Conditional Object Creation
```ini
Upgrade = ObjectCreationUpgrade ModuleTag_ConditionalCreation
  UpgradeObject = OCL_ConditionalUnits
  TriggeredBy = Upgrade_ConditionalTraining
  ConflictsWith = Upgrade_BasicTraining
End
```

## Template

```ini
Upgrade = ObjectCreationUpgrade ModuleTag_XX
  ; Object Creation Settings
  UpgradeObject =                    ; // ObjectCreationList to use *(v1.04)*
  
  ; Upgrade Integration (inherited from UpgradeModule)
  TriggeredBy =                      ; // required upgrade flags *(v1.04)*
  ConflictsWith =                    ; // conflicting upgrade flags *(v1.04)*
  RequiresAll = No                   ; // require all TriggeredBy upgrades *(v1.04)*
End
```

## Notes

- ObjectCreationUpgrade creates objects when the specified upgrade is applied
- The upgrade integrates with the upgrade system for conditional activation
- Objects are created using the specified ObjectCreationList (OCL)
- Created objects are owned by the same player as the upgrading object
- Only creates objects using ObjectCreationList (OCL)
- The OCL must exist and be properly defined
- Object creation occurs immediately when the upgrade is activated
- Created objects are owned by the same player as the upgrading object
- The OCL defines what objects to create, where to create them, and how many to create

## Source Files

**Base Class:** [`UpgradeModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ObjectCreationUpgrade.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ObjectCreationUpgrade.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/ObjectCreationUpgrade.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/ObjectCreationUpgrade.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet
