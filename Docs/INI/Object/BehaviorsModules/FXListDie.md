# FXListDie

FXListDie provides death mechanics with visual effects lists when objects die or are destroyed.

## Overview

The `FXListDie` class manages visual effects that are played when objects die or are destroyed. It supports conditional activation based on death types, veterancy levels, and upgrade states. The behavior is commonly used to create appropriate visual feedback for different types of destruction, such as explosions, crushing, burning, or other death effects.

## Usage

Used by objects that need complex visual effects when they die or are destroyed. This is a **behavior module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Effects only trigger when the object dies or is destroyed
- Multiple FXListDie behaviors can exist on the same object with different conditions
- Effects are played when death conditions are met

**Conditions**:
- Death effects are conditional based on death type, veterancy level, and upgrade state
- FXListDie supports conditional activation based on death types, veterancy levels, and upgrade states
- The behavior integrates with the death system for conditional activation
- The behavior works with other death behaviors like SlowDeathBehavior
- **Multiple instances behavior**: Multiple instances can exist with different conditions; all matching instances will trigger their effects simultaneously

**Dependencies**:
- Requires proper FXList definitions to function correctly
- The behavior is commonly used to create appropriate visual feedback for different types of destruction
- Death effects include explosions, crushing, burning, or other death effects

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Visual Effects](#visual-effects)
  - [Upgrade Integration](#upgrade-integration)
  - [Death Conditions](#death-conditions)
- [Enum Value Lists](#enum-value-lists)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

### Visual Effects

#### `DeathFX` *(v1.04)*
- **Type**: `FXList` (see [FXList documentation](../FXList.md))
- **Description**: Visual effects list played when the object dies
- **Example**: `DeathFX = FX_StructureMediumDeath`

#### `OrientToObject` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether the effects should be oriented to face the damage dealer
- **Example**: `OrientToObject = Yes`

#### `StartsActive` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether the death behavior is active from the start
- **Example**: `StartsActive = Yes`

### Upgrade Integration

#### `TriggeredBy` *(v1.04)*
- **Type**: `UpgradeMaskType` (bit flags)
- **Description**: Required upgrade flags to activate the death effects
- **Example**: `TriggeredBy = Upgrade_GLADemolition`

#### `ConflictsWith` *(v1.04)*
- **Type**: `UpgradeMaskType` (bit flags)
- **Description**: Upgrade flags that conflict with this death behavior
- **Example**: `ConflictsWith = Upgrade_GLAStealth`

#### `RequiresAll` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether all TriggeredBy upgrades must be active (true) or just one (false)
- **Example**: `RequiresAll = No`

### Death Conditions

#### `DeathTypes` *(v1.04)*
- **Type**: `DeathTypeFlags` (bit flags) (see [DeathType Values](#deathtype-values) section)
- **Description**: Death types that trigger these effects
- **Example**: `DeathTypes = NONE +CRUSHED +EXPLODED`

#### `VeterancyLevels` *(v1.04)*
- **Type**: `VeterancyLevelFlags` (bit flags)
- **Description**: Veterancy levels that trigger these effects
- **Example**: `VeterancyLevels = VETERAN +ELITE`

#### `ExemptStatus` *(v1.04)*
- **Type**: `ObjectStatusMaskType` (bit flags)
- **Description**: Object status bits that prevent these effects from triggering
- **Example**: `ExemptStatus = OBJECT_STATUS_SOLD`

#### `RequiredStatus` *(v1.04)*
- **Type**: `ObjectStatusMaskType` (bit flags)
- **Description**: Object status bits that must be set for effects to trigger
- **Example**: `RequiredStatus = OBJECT_STATUS_UNDER_CONSTRUCTION`

## Enum Value Lists

#### `DeathType` Values *(v1.04)*
**Source:** [Damage.h](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h#187) - `DeathType` enum definition

- **`DEATH_NORMAL`** *(v1.04)* - Normal death
- **`DEATH_NONE`** *(v1.04)* - No death (special case)
- **`DEATH_CRUSHED`** *(v1.04)* - Crushed death
- **`DEATH_BURNED`** *(v1.04)* - Burned death
- **`DEATH_EXPLODED`** *(v1.04)* - Exploded death
- **`DEATH_POISONED`** *(v1.04)* - Poisoned death
- **`DEATH_SUICIDED`** *(v1.04)* - Suicide death
- **`DEATH_RUBBLE`** *(v1.04)* - Rubble death
- **`DEATH_FADED`** *(v1.04)* - Faded death
- **`DEATH_KNOCKBACK`** *(v1.04)* - Knockback death
- **`DEATH_LAVA`** *(v1.04)* - Lava death
- **`DEATH_DETONATED`** *(v1.04)* - Detonated death
- **`DEATH_EXTRA_1`** *(v1.04)* - Extra death type 1
- **`DEATH_EXTRA_2`** *(v1.04)* - Extra death type 2
- **`DEATH_EXTRA_3`** *(v1.04)* - Extra death type 3
- **`DEATH_EXTRA_4`** *(v1.04)* - Extra death type 4
- **`DEATH_EXTRA_5`** *(v1.04)* - Extra death type 5

## Examples

### Scout Van Crushing Death
```ini
Behavior = FXListDie DeathTag_03
  DeathTypes = NONE +CRUSHED +SPLATTED
  DeathFX = FX_CarCrush
  OrientToObject = Yes
End
```

### Airfield Destruction
```ini
Behavior = FXListDie ModuleTag_19
  DeathFX = FX_StructureMediumDeath
  StartsActive = Yes
End
```

### Artillery Bunker Destruction
```ini
Behavior = FXListDie ModuleTag_324
  DeathFX = FX_StructureSmallDeath
  DeathTypes = NONE +EXPLODED +BURNED
End
```

### Upgrade-Based Death Effects
```ini
Behavior = FXListDie ModuleTag_Demo
  DeathFX = FX_DemolitionExplosion
  TriggeredBy = Upgrade_GLADemolition
  DeathTypes = NONE +EXPLODED
  OrientToObject = No
End
```

## Template

```ini
Behavior = FXListDie ModuleTag_XX
  ; Visual Effects
  DeathFX =                        ; // visual effects when object dies *(v1.04)*
  OrientToObject = Yes             ; // orient effects to damage dealer *(v1.04)*
  StartsActive = Yes               ; // whether death behavior starts active *(v1.04)*

  ; Upgrade Integration
  TriggeredBy =                    ; // required upgrade flags *(v1.04)*
  ConflictsWith =                  ; // conflicting upgrade flags *(v1.04)*
  RequiresAll = No                 ; // require all TriggeredBy upgrades *(v1.04)*

  ; Death Conditions
  DeathTypes = NONE                ; // death types that trigger effects *(v1.04)*
  VeterancyLevels =                ; // veterancy levels that trigger effects *(v1.04)*
  ExemptStatus =                   ; // status bits that prevent triggering *(v1.04)*
  RequiredStatus =                 ; // required status bits for triggering *(v1.04)*
End
```

## Notes

- FXListDie provides visual feedback for object destruction through customizable effects
- Death effects can be conditional based on death type, veterancy level, and upgrade state
- Effects can be oriented to face the damage dealer or positioned at the object's location
- Multiple death types can be combined using bit flags (e.g., `+CRUSHED +EXPLODED`)
- The behavior integrates with the upgrade system for conditional activation
- Death effects are played when objects with ActiveBody (see [ActiveBody documentation](../ObjectModules/ActiveBody.md)) are destroyed
- Effects can be enhanced with particle systems and sound effects defined in the FXList

## Source Files

**Base Class:** [`DieModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h), [`UpgradeMux`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FXListDie.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FXListDie.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Die/FXListDie.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Die/FXListDie.cpp)
