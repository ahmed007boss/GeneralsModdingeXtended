# ModelConditionUpgrade

ModelConditionUpgrade provides the ability to set model condition flags for objects when an upgrade is applied, allowing for visual state changes and model condition modifications.

## Overview

The `ModelConditionUpgrade` class manages model condition flag changes for objects when specific upgrades are applied. This upgrade module allows objects to have their visual state or model condition changed by setting specific model condition flags. The behavior is commonly used for units that change their appearance, enter special states, or have visual upgrades that affect their model condition.

## Usage

Used by objects that need to change their model condition when upgrades are applied. This is an **upgrade module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Only sets a single model condition flag per upgrade
- The model condition flag must be valid
- Model condition changes are applied immediately when the upgrade is activated
- Objects must have model condition systems to function properly

**Conditions**:
- ModelConditionUpgrade sets model condition flags when the specified upgrade is applied
- The upgrade integrates with the upgrade system for conditional activation
- Model condition flags affect the object's visual state and appearance
- The upgrade can set any valid model condition flag
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own model condition changes

**Dependencies**:
- Requires an object with upgrade system integration
- Objects must have model condition systems to function properly
- The model condition flag must be valid and supported

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

### Model Condition Settings

#### `ConditionFlag` *(v1.04)*
- **Type**: `ModelConditionFlagType`
- **Description**: The model condition flag to set when this upgrade is applied. This flag affects the object's visual state and appearance. The flag must be a valid model condition type
- **Default**: `MODELCONDITION_INVALID`
- **Example**: `ConditionFlag = MODELCONDITION_ELITE`

## Examples

### Basic Model Condition Change
```ini
Upgrade = ModelConditionUpgrade ModuleTag_ModelCondition
  ConditionFlag = MODELCONDITION_ELITE
  TriggeredBy = Upgrade_EliteTraining
End
```

### Visual State Upgrade
```ini
Upgrade = ModelConditionUpgrade ModuleTag_VisualUpgrade
  ConditionFlag = MODELCONDITION_UPGRADED
  TriggeredBy = Upgrade_VisualUpgrade
End
```

### Special State Activation
```ini
Upgrade = ModelConditionUpgrade ModuleTag_SpecialState
  ConditionFlag = MODELCONDITION_SPECIAL
  TriggeredBy = Upgrade_SpecialTraining
End
```

### Conditional Model Change
```ini
Upgrade = ModelConditionUpgrade ModuleTag_ConditionalModel
  ConditionFlag = MODELCONDITION_ADVANCED
  TriggeredBy = Upgrade_AdvancedTraining
  ConflictsWith = Upgrade_BasicTraining
End
```

## Template

```ini
Upgrade = ModelConditionUpgrade ModuleTag_XX
  ; Model Condition Settings
  ConditionFlag = MODELCONDITION_INVALID  ; // model condition flag to set *(v1.04)*
  
  ; Upgrade Integration (inherited from UpgradeModule)
  TriggeredBy =                           ; // required upgrade flags *(v1.04)*
  ConflictsWith =                         ; // conflicting upgrade flags *(v1.04)*
  RequiresAll = No                        ; // require all TriggeredBy upgrades *(v1.04)*
End
```

## Notes

- ModelConditionUpgrade sets model condition flags when the specified upgrade is applied
- The upgrade integrates with the upgrade system for conditional activation
- Model condition flags affect the object's visual state and appearance
- The upgrade can set any valid model condition flag
- Only sets a single model condition flag per upgrade
- The model condition flag must be valid
- Model condition changes are applied immediately when the upgrade is activated
- Objects must have model condition systems to function properly
- The model condition flag affects the object's visual representation and state

## Source Files

**Base Class:** [`UpgradeModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ModelConditionUpgrade.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ModelConditionUpgrade.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/ModelConditionUpgrade.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/ModelConditionUpgrade.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet
