# WeaponSetUpgrade

WeaponSetUpgrade provides the ability to change an object's weapon set when an upgrade is applied, allowing for different weapon configurations based on upgrade status.

## Overview

The `WeaponSetUpgrade` class manages weapon set changes for objects when specific upgrades are applied. This upgrade module allows objects to have different weapon configurations depending on their upgrade state, providing enhanced combat capabilities. The behavior works by setting weapon set flags that the weapon system uses to select the appropriate weapon set from the object's configuration.

## Usage

Used by objects that need to change their weapon configuration when upgrades are applied. This is an **upgrade module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Only changes weapon set flags, not the actual weapon definitions
- The new weapon sets must exist in the object's weapon configuration
- Weapon set changes are applied immediately when the upgrade is activated
- Objects must have weapon systems to function properly

**Conditions**:
- WeaponSetUpgrade changes the object's weapon set when the specified upgrade is applied
- The upgrade integrates with the upgrade system for conditional activation
- Weapon set flags are used by the weapon system to select appropriate weapons
- The upgrade can both set new weapon set flags and clear existing ones
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own weapon set changes

**Dependencies**:
- Requires an object with upgrade system integration
- The new weapon sets must exist in the object's weapon configuration
- Objects must have weapon systems to function properly
- The weapon set system must be properly configured

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
- [Enum Value Lists](#enum-value-lists)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)

## Properties

### Weapon Set Settings

#### `WeaponSetFlag` *(v1.04)*
- **Type**: `WeaponSetType` (see [WeaponSetType Values](#weaponsettype-values) section)
- **Description**: The weapon set flag to set when this upgrade is applied. This flag is used by the weapon system to select the appropriate weapon set from the object's configuration
- **Default**: `WEAPONSET_PLAYER_UPGRADE`
- **Example**: `WeaponSetFlag = WEAPONSET_ELITE`

#### `WeaponSetFlagToClear` *(v1.04)*
- **Type**: `WeaponSetType` (see [WeaponSetType Values](#weaponsettype-values) section)
- **Description**: The weapon set flag to clear when this upgrade is applied. This is useful for overriding previous upgrades or switching between different weapon configurations
- **Default**: `WEAPONSET_COUNT` (undefined, no clearing)
- **Example**: `WeaponSetFlagToClear = WEAPONSET_VETERAN`

## Enum Value Lists

#### `WeaponSetType` Values *(v1.04)*
**Source:** [WeaponSetType.h](../../GeneralsMD/Code/GameEngine/Include/GameLogic/WeaponSetType.h#44) - `WeaponSetType` enum definition

- **`VETERAN`** *(v1.04)* - Veteran weapon set
- **`ELITE`** *(v1.04)* - Elite weapon set
- **`HERO`** *(v1.04)* - Hero weapon set
- **`PLAYER_UPGRADE`** *(v1.04)* - Player upgrade weapon set
- **`CRATEUPGRADE_ONE`** *(v1.04)* - Crate upgrade weapon set one
- **`CRATEUPGRADE_TWO`** *(v1.04)* - Crate upgrade weapon set two
- **`VEHICLE_HIJACK`** *(v1.04)* - Vehicle hijack weapon set
- **`CARBOMB`** *(v1.04)* - Car bomb weapon set
- **`MINE_CLEARING_DETAIL`** *(v1.04)* - Mine clearing weapon set
- **`RIDER1`** *(v1.04)* - Rider weapon set one
- **`RIDER2`** *(v1.04)* - Rider weapon set two
- **`RIDER3`** *(v1.04)* - Rider weapon set three
- **`RIDER4`** *(v1.04)* - Rider weapon set four
- **`RIDER5`** *(v1.04)* - Rider weapon set five
- **`RIDER6`** *(v1.04)* - Rider weapon set six
- **`RIDER7`** *(v1.04)* - Rider weapon set seven
- **`RIDER8`** *(v1.04)* - Rider weapon set eight
- **`PLAYER_UPGRADE2`** *(v1.04)* - Player upgrade weapon set two
- **`PLAYER_UPGRADE3`** *(v1.04)* - Player upgrade weapon set three
- **`PLAYER_UPGRADE4`** *(v1.04)* - Player upgrade weapon set four

## Examples

### Basic Elite Weapon Set
```ini
Upgrade = WeaponSetUpgrade ModuleTag_EliteWeapons
  WeaponSetFlag = WEAPONSET_ELITE
  TriggeredBy = Upgrade_EliteTraining
End
```

### Weapon Set with Flag Clearing
```ini
Upgrade = WeaponSetUpgrade ModuleTag_WeaponUpgrade
  WeaponSetFlag = WEAPONSET_PLAYER_UPGRADE
  WeaponSetFlagToClear = WEAPONSET_VETERAN
  TriggeredBy = Upgrade_WeaponTraining
End
```

### Hero Weapon Set
```ini
Upgrade = WeaponSetUpgrade ModuleTag_HeroWeapons
  WeaponSetFlag = WEAPONSET_HERO
  TriggeredBy = Upgrade_HeroTraining
End
```

### Multiple Upgrade Weapon Set
```ini
Upgrade = WeaponSetUpgrade ModuleTag_AdvancedWeapons
  WeaponSetFlag = WEAPONSET_PLAYER_UPGRADE2
  WeaponSetFlagToClear = WEAPONSET_PLAYER_UPGRADE
  TriggeredBy = Upgrade_AdvancedWeaponTraining
End
```

## Template

```ini
Upgrade = WeaponSetUpgrade ModuleTag_XX
  ; Weapon Set Settings
  WeaponSetFlag = WEAPONSET_PLAYER_UPGRADE  ; // weapon set flag to set *(v1.04)*
  WeaponSetFlagToClear = WEAPONSET_COUNT    ; // weapon set flag to clear *(v1.04)*
  
  ; Upgrade Integration (inherited from UpgradeModule)
  TriggeredBy =                             ; // required upgrade flags *(v1.04)*
  ConflictsWith =                           ; // conflicting upgrade flags *(v1.04)*
  RequiresAll = No                          ; // require all TriggeredBy upgrades *(v1.04)*
End
```

## Notes

- WeaponSetUpgrade changes the object's weapon set when the specified upgrade is applied
- The upgrade integrates with the upgrade system for conditional activation
- Weapon set flags are used by the weapon system to select appropriate weapons
- The upgrade can both set new weapon set flags and clear existing ones
- Only changes weapon set flags, not the actual weapon definitions
- The new weapon sets must exist in the object's weapon configuration
- Objects must have weapon systems to function properly
- The weapon set system uses these flags to determine which weapon configuration to use

## Source Files

**Base Class:** [`UpgradeModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/WeaponSetUpgrade.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/WeaponSetUpgrade.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/WeaponSetUpgrade.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/WeaponSetUpgrade.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet
