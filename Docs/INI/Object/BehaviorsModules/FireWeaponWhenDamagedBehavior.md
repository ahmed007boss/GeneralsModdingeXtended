# FireWeaponWhenDamagedBehavior

FireWeaponWhenDamagedBehavior allows objects to automatically fire weapons when they receive damage or continuously fire weapons based on their damage state.

## Overview

The `FireWeaponWhenDamagedBehavior` class manages reactive and continuous weapon firing based on damage events and damage states. It can fire different weapons when receiving damage (reaction weapons) or continuously fire weapons based on the object's current damage state (continuous weapons). The behavior integrates with the upgrade system for conditional activation and supports different weapons for each damage state (pristine, damaged, really damaged, rubble).

## Usage

Used by objects that need reactive combat capabilities, such as defensive structures, units that retaliate when attacked, or objects that continuously fire weapons based on their condition. This is a **behavior module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Weapons only fire when the behavior is upgrade-activated
- Reaction weapons only fire when damage exceeds the specified threshold
- Continuous weapons fire every update cycle when active
- Continuous weapons require the behavior to be upgrade-active and will wake the update module
- Weapons fire at the object's current position when triggered

**Conditions**:
- Different weapons can be specified for each damage state (pristine, damaged, really damaged, rubble)
- The behavior integrates with the upgrade system for conditional activation
- Damage filtering allows precise control over when reaction weapons fire
- **Multiple instances behavior**: Multiple instances can exist but each manages its own weapons independently; no property conflicts occur

**Dependencies**:
- Requires valid weapon template definitions to function
- Weapons are automatically created and managed by the behavior
- The behavior handles weapon reloading and firing automatically

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Activation Settings](#activation-settings)
  - [Damage Filter Settings](#damage-filter-settings)
  - [Reaction Weapon Settings](#reaction-weapon-settings)
  - [Continuous Weapon Settings](#continuous-weapon-settings)
  - [Upgrade Integration](#upgrade-integration)
- [Enum Value Lists](#enum-value-lists)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

### Activation Settings

#### `StartsActive` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether the behavior starts active (upgraded) when the object is created
- **Example**: `StartsActive = Yes`

### Damage Filter Settings

#### `DamageTypes` *(v1.04)*
- **Type**: `DamageTypeFlags` (bit flags) (see [DamageType Values](#damagetype-values) section)
- **Description**: Damage types that trigger reaction weapons (defaults to all damage types)
- **Example**: `DamageTypes = EXPLOSIVE +FLAME`

#### `DamageAmount` *(v1.04)*
- **Type**: `Real`
- **Description**: Minimum damage amount required to trigger reaction weapons
- **Example**: `DamageAmount = 10.0`

### Reaction Weapon Settings

#### `ReactionWeaponPristine` *(v1.04)*
- **Type**: `Weapon`
- **Description**: Weapon fired when pristine object receives qualifying damage
- **Example**: `ReactionWeaponPristine = Weapon_RetaliationPristine`

#### `ReactionWeaponDamaged` *(v1.04)*
- **Type**: `Weapon`
- **Description**: Weapon fired when damaged object receives qualifying damage
- **Example**: `ReactionWeaponDamaged = Weapon_RetaliationDamaged`

#### `ReactionWeaponReallyDamaged` *(v1.04)*
- **Type**: `Weapon`
- **Description**: Weapon fired when really damaged object receives qualifying damage
- **Example**: `ReactionWeaponReallyDamaged = Weapon_RetaliationReallyDamaged`

#### `ReactionWeaponRubble` *(v1.04)*
- **Type**: `Weapon`
- **Description**: Weapon fired when rubble object receives qualifying damage
- **Example**: `ReactionWeaponRubble = Weapon_RetaliationRubble`

### Continuous Weapon Settings

#### `ContinuousWeaponPristine` *(v1.04)*
- **Type**: `Weapon`
- **Description**: Weapon fired continuously while pristine object is active
- **Example**: `ContinuousWeaponPristine = Weapon_ContinuousPristine`

#### `ContinuousWeaponDamaged` *(v1.04)*
- **Type**: `Weapon`
- **Description**: Weapon fired continuously while damaged object is active
- **Example**: `ContinuousWeaponDamaged = Weapon_ContinuousDamaged`

#### `ContinuousWeaponReallyDamaged` *(v1.04)*
- **Type**: `Weapon`
- **Description**: Weapon fired continuously while really damaged object is active
- **Example**: `ContinuousWeaponReallyDamaged = Weapon_ContinuousReallyDamaged`

#### `ContinuousWeaponRubble` *(v1.04)*
- **Type**: `Weapon`
- **Description**: Weapon fired continuously while rubble object is active
- **Example**: `ContinuousWeaponRubble = Weapon_ContinuousRubble`

### Upgrade Integration

#### `TriggeredBy` *(v1.04)*
- **Type**: `UpgradeMaskType` (bit flags)
- **Description**: Required upgrade flags to activate the weapon firing behavior
- **Example**: `TriggeredBy = Upgrade_DefensiveSystems`

#### `ConflictsWith` *(v1.04)*
- **Type**: `UpgradeMaskType` (bit flags)
- **Description**: Upgrade flags that conflict with this weapon firing behavior
- **Example**: `ConflictsWith = Upgrade_StealthMode`

#### `RequiresAll` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether all TriggeredBy upgrades must be active (true) or just one (false)
- **Example**: `RequiresAll = Yes`

## Enum Value Lists

#### `DamageType` Values *(v1.04)*
**Source:** [Damage.h](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h#155) - `DamageType` enum definition

- **`DAMAGE_NONE`** *(v1.04)* - No damage
- **`DAMAGE_EXPLOSIVE`** *(v1.04)* - Explosive damage
- **`DAMAGE_FLAME`** *(v1.04)* - Flame damage
- **`DAMAGE_BULLET`** *(v1.04)* - Bullet damage
- **`DAMAGE_KNIFE`** *(v1.04)* - Knife damage
- **`DAMAGE_LASER`** *(v1.04)* - Laser damage
- **`DAMAGE_POISON`** *(v1.04)* - Poison damage
- **`DAMAGE_CRUSH`** *(v1.04)* - Crush damage
- **`DAMAGE_HEALING`** *(v1.04)* - Healing damage
- **`DAMAGE_UNRESISTABLE`** *(v1.04)* - Unresistable damage
- **`DAMAGE_EMP`** *(v1.04)* - EMP damage
- **`DAMAGE_DEPLOY`** *(v1.04)* - Deploy damage
- **`DAMAGE_PARTICLE_BEAM`** *(v1.04)* - Particle beam damage
- **`DAMAGE_EXTRA_1`** *(v1.04)* - Extra damage type 1
- **`DAMAGE_EXTRA_2`** *(v1.04)* - Extra damage type 2
- **`DAMAGE_EXTRA_3`** *(v1.04)* - Extra damage type 3
- **`DAMAGE_EXTRA_4`** *(v1.04)* - Extra damage type 4
- **`DAMAGE_EXTRA_5`** *(v1.04)* - Extra damage type 5

## Examples

### GLA Jammer Van Reactive Defense
```ini
Behavior = FireWeaponWhenDamagedBehavior ModuleTag_IronCrutain
  StartsActive = Yes
  DamageTypes = ALL
  DamageAmount = 1.0
  ReactionWeaponPristine = IronCrutainDroneWeapon
  ReactionWeaponDamaged = IronCrutainDroneWeapon
  ReactionWeaponReallyDamaged = IronCrutainDroneWeapon
  ReactionWeaponRubble = IronCrutainDroneWeapon
End
```

### Defensive Structure with Continuous Fire
```ini
Behavior = FireWeaponWhenDamagedBehavior ModuleTag_Defense
  StartsActive = No
  TriggeredBy = Upgrade_DefensiveSystems
  DamageTypes = EXPLOSIVE +FLAME
  DamageAmount = 5.0
  ReactionWeaponPristine = Weapon_DefensiveRetaliation
  ReactionWeaponDamaged = Weapon_DefensiveRetaliationDamaged
  ContinuousWeaponPristine = Weapon_DefensiveContinuous
  ContinuousWeaponDamaged = Weapon_DefensiveContinuousDamaged
  ContinuousWeaponReallyDamaged = Weapon_DefensiveContinuousReallyDamaged
End
```

### Advanced Retaliation System
```ini
Behavior = FireWeaponWhenDamagedBehavior ModuleTag_AdvancedRetaliation
  StartsActive = No
  TriggeredBy = Upgrade_AdvancedDefense
  DamageTypes = ALL -HEALING
  DamageAmount = 10.0
  ReactionWeaponPristine = Weapon_AdvancedRetaliationPristine
  ReactionWeaponDamaged = Weapon_AdvancedRetaliationDamaged
  ReactionWeaponReallyDamaged = Weapon_AdvancedRetaliationReallyDamaged
  ReactionWeaponRubble = Weapon_AdvancedRetaliationRubble
  ContinuousWeaponPristine = Weapon_AdvancedContinuousPristine
  ContinuousWeaponDamaged = Weapon_AdvancedContinuousDamaged
End
```

### Emergency Defense Mode
```ini
Behavior = FireWeaponWhenDamagedBehavior ModuleTag_Emergency
  StartsActive = No
  TriggeredBy = Upgrade_EmergencyDefense
  RequiresAll = Yes
  DamageTypes = EXPLOSIVE +FLAME +BULLET
  DamageAmount = 25.0
  ReactionWeaponPristine = Weapon_EmergencyBlast
  ReactionWeaponDamaged = Weapon_EmergencyBlast
  ReactionWeaponReallyDamaged = Weapon_EmergencyBlast
  ContinuousWeaponRubble = Weapon_EmergencyContinuous
End
```

## Template

```ini
Behavior = FireWeaponWhenDamagedBehavior ModuleTag_XX
  ; Activation Settings
  StartsActive = No                 ; // whether behavior starts active *(v1.04)*

  ; Damage Filter Settings
  DamageTypes = ALL                 ; // damage types that trigger reaction weapons *(v1.04)*
  DamageAmount = 0.0                ; // minimum damage to trigger reaction weapons *(v1.04)*

  ; Reaction Weapon Settings (fire when damaged)
  ReactionWeaponPristine =          ; // weapon fired when pristine and damaged *(v1.04)*
  ReactionWeaponDamaged =           ; // weapon fired when damaged and damaged *(v1.04)*
  ReactionWeaponReallyDamaged =     ; // weapon fired when really damaged and damaged *(v1.04)*
  ReactionWeaponRubble =            ; // weapon fired when rubble and damaged *(v1.04)*

  ; Continuous Weapon Settings (fire continuously)
  ContinuousWeaponPristine =        ; // weapon fired continuously when pristine *(v1.04)*
  ContinuousWeaponDamaged =         ; // weapon fired continuously when damaged *(v1.04)*
  ContinuousWeaponReallyDamaged =   ; // weapon fired continuously when really damaged *(v1.04)*
  ContinuousWeaponRubble =          ; // weapon fired continuously when rubble *(v1.04)*

  ; Upgrade Integration
  TriggeredBy =                     ; // required upgrade flags *(v1.04)*
  ConflictsWith =                   ; // conflicting upgrade flags *(v1.04)*
  RequiresAll = No                  ; // require all TriggeredBy upgrades *(v1.04)*
End
```

## Notes

- FireWeaponWhenDamagedBehavior supports both reactive and continuous weapon firing modes
- Reaction weapons fire only when the object receives qualifying damage
- Continuous weapons fire every update cycle when the behavior is active
- Different weapons can be specified for each damage state (pristine, damaged, really damaged, rubble)
- The behavior integrates with the upgrade system for conditional activation
- Weapons are automatically created and managed by the behavior
- Damage filtering allows precise control over when reaction weapons fire
- Continuous weapons require the behavior to be upgrade-active and will wake the update module
- The behavior handles weapon reloading and firing automatically
- Weapons fire at the object's current position when triggered

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h), [`UpgradeMux`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h), [`DamageModuleInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DamageModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FireWeaponWhenDamagedBehavior.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FireWeaponWhenDamagedBehavior.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/FireWeaponWhenDamagedBehavior.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/FireWeaponWhenDamagedBehavior.cpp)