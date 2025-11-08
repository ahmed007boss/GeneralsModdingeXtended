# ExperienceScalarUpgrade

ExperienceScalarUpgrade provides the ability to modify experience gain rates for objects when an upgrade is applied, allowing for enhanced experience acquisition and value.

## Overview

The `ExperienceScalarUpgrade` class manages experience gain modifications when specific upgrades are applied. This upgrade module allows objects to have their experience gain rates modified by adding scalar values to both the experience they receive and the experience value they provide when killed. The behavior is commonly used for units that gain enhanced experience through training, elite status, or special abilities.

## Usage

Used by objects that need modified experience gain rates when upgrades are applied. This is an **upgrade module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Only affects experience gain rates, not other experience properties
- Experience scalar changes are applied immediately when the upgrade is activated
- Objects must have ExperienceTracker systems to function properly
- Scalar values are additive to existing experience rates

**Conditions**:
- ExperienceScalarUpgrade modifies experience gain rates when the specified upgrade is applied
- The upgrade integrates with the upgrade system for conditional activation
- Experience scalars affect both incoming experience gain and outgoing experience value
- The upgrade can modify both experience received and experience given when killed
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own experience scalar modifications

**Dependencies**:
- Requires an object with upgrade system integration
- The experience system must be available for scalar modifications

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

### Experience Gain Settings

#### `AddXPScalar` *(v1.04)*
- **Type**: `Real`
- **Description**: Additive bonus to the scalar for experience this unit gains. This value is added to the object's current experience scalar, increasing the rate at which it gains experience from combat, objectives, and other sources. Higher values result in faster experience gain
- **Default**: `0.0`
- **Example**: `AddXPScalar = 0.5`

#### `XPGrantedOnDeathScalar` *(GMX Upcoming)*
- **Type**: `Real`
- **Description**: Additive bonus to the scalar for experience this unit gives when killed. This value is added to the object's current experience value scalar, increasing the amount of experience other units gain when this unit is destroyed. Higher values result in more valuable targets. This property is newly added in the GMX release
- **Default**: `0.0`
- **Example**: `XPGrantedOnDeathScalar = 0.3`

## Examples

### Basic Experience Boost
```ini
Upgrade = ExperienceScalarUpgrade ModuleTag_ExperienceBoost
  AddXPScalar = 0.5
  TriggeredBy = Upgrade_ExperienceTraining
End
```

### Enhanced Experience Value (GMX Upcoming)
```ini
Upgrade = ExperienceScalarUpgrade ModuleTag_ExperienceValue
  AddXPScalar = 0.3
  XPGrantedOnDeathScalar = 0.2
  TriggeredBy = Upgrade_EliteTraining
End
```

### Combined Experience Modifications
```ini
Upgrade = ExperienceScalarUpgrade ModuleTag_CombinedExperience
  AddXPScalar = 0.4
  XPGrantedOnDeathScalar = 0.2
  TriggeredBy = Upgrade_AdvancedTraining
End
```

### Elite Experience Enhancement
```ini
Upgrade = ExperienceScalarUpgrade ModuleTag_EliteExperience
  AddXPScalar = 0.8
  XPGrantedOnDeathScalar = 0.6
  TriggeredBy = Upgrade_EliteTraining
  ConflictsWith = Upgrade_BasicTraining
End
```

## Template

```ini
Upgrade = ExperienceScalarUpgrade ModuleTag_XX
  ; Experience Gain Settings
  AddXPScalar = 0.0                 ; // additive bonus to experience gain scalar *(v1.04)*
  XPGrantedOnDeathScalar = 0.0      ; // additive bonus to experience granted on death scalar *(GMX Upcoming)*
  
  ; Upgrade Integration (inherited from UpgradeModule)
  TriggeredBy =                     ; // required upgrade flags *(v1.04)*
  ConflictsWith =                   ; // conflicting upgrade flags *(v1.04)*
  RequiresAll = No                  ; // require all TriggeredBy upgrades *(v1.04)*
End
```

## Notes

- ExperienceScalarUpgrade modifies experience gain rates when the specified upgrade is applied
- The upgrade integrates with the upgrade system for conditional activation
- Experience scalars affect both incoming experience gain and outgoing experience value
- The upgrade can modify both experience received and experience given when killed
- Only affects experience gain rates, not other experience properties
- Experience scalar changes are applied immediately when the upgrade is activated
- Scalar values are additive to existing experience rates
- The upgrade enhances both the unit's ability to gain experience and its value as a target
- `XPGrantedOnDeathScalar` is newly added in the GMX release

## Source Files

**Base Class:** [UpgradeModule](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h)

- Header: [GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ExperienceScalarUpgrade.h](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ExperienceScalarUpgrade.h) (line 43)
- Source: [GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/ExperienceScalarUpgrade.cpp](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/ExperienceScalarUpgrade.cpp) (line 40)

## Changes History

- **GMX Upcoming**: Added `XPGrantedOnDeathScalar` property for enhanced experience value modification
- **v1.04**: Original implementation with only `AddXPScalar` property

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet