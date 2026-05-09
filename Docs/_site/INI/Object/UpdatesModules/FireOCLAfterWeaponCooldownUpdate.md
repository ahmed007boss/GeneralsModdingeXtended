# FireOCLAfterWeaponCooldownUpdate

FireOCLAfterWeaponCooldownUpdate provides functionality for firing Object Creation List (OCL) effects after weapon cooldown periods have elapsed.

## Overview

The `FireOCLAfterWeaponCooldownUpdate` class manages the creation of objects using Object Creation Lists (OCL) after weapon firing cooldowns. It monitors weapon firing events and creates OCL objects based on weapon usage patterns, upgrade requirements, and timing constraints. This update is commonly used for creating persistent effects, area denial weapons, or environmental objects that spawn after weapon use.

## Usage

Used by objects that need to create OCL effects after weapon cooldown periods. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- OCL creation is limited by weapon cooldown timing
- Requires minimum shots to be fired before creating OCL objects
- OCL lifetime is controlled by specified duration parameters
- Upgrade requirements must be met for OCL creation

**Conditions**:
- FireOCLAfterWeaponCooldownUpdate monitors weapon firing events and cooldowns
- OCL objects are created after the specified weapon slot completes its cooldown
- Minimum shot requirements must be met before OCL creation begins
- Upgrade conditions control when the OCL creation is active
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own weapon slots and OCL settings

**Dependencies**:
- Requires objects with weapon systems to monitor firing events
- Uses Object Creation Lists (OCL) for spawning new objects
- Integrates with upgrade system for conditional activation

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Weapon Settings](#weapon-settings)
  - [OCL Settings](#ocl-settings)
  - [Upgrade Settings](#upgrade-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Weapon Settings

#### `WeaponSlot` *(v1.04)*
- **Type**: `WeaponSlotType` (enum)
- **Description**: The weapon slot to monitor for firing events and cooldowns. Determines which weapon's firing pattern triggers OCL creation
- **Default**: `PRIMARY`
- **Example**: `WeaponSlot = SECONDARY`
- **Available Values**: See [WeaponSlotType Values](#weaponslottype-values) section

### OCL Settings

#### `OCL` *(v1.04)*
- **Type**: `ObjectCreationList`
- **Description**: The Object Creation List to spawn after weapon cooldown. When set, creates the specified objects. When empty, no objects are created
- **Default**: `NULL`
- **Example**: `OCL = OCL_PoisonFieldMedium`

#### `MinShotsToCreateOCL` *(v1.04)*
- **Type**: `UnsignedInt`
- **Description**: Minimum number of shots that must be fired before OCL creation begins. Higher values require more weapon usage before triggering OCL. Lower values allow OCL creation sooner
- **Default**: `0`
- **Example**: `MinShotsToCreateOCL = 5`

#### `OCLLifetimePerSecond` *(v1.04)*
- **Type**: `UnsignedInt`
- **Description**: Lifetime duration for created OCL objects in frames per second. Higher values create longer-lasting objects. Lower values create shorter-lived objects
- **Default**: `0`
- **Example**: `OCLLifetimePerSecond = 60`

#### `OCLLifetimeMaxCap` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Maximum lifetime cap for created OCL objects. Higher values allow longer maximum lifetimes. Lower values limit maximum object duration
- **Default**: `0` (no cap)
- **Example**: `OCLLifetimeMaxCap = 30000`

### Upgrade Settings

#### `TriggeredBy` *(v1.04)*
- **Type**: `UpgradeMaskType` (bit flags)
- **Description**: Upgrades that must be active for OCL creation to trigger. When set, only objects with these upgrades will create OCL effects. When empty, no upgrade requirements
- **Default**: `0` (no requirements)
- **Example**: `TriggeredBy = Upgrade_GLAAnthraxBeta Upgrade_Veterancy_HEROIC`

#### `ConflictsWith` *(v1.04)*
- **Type**: `UpgradeMaskType` (bit flags)
- **Description**: Upgrades that prevent OCL creation when active. When set, objects with these upgrades will not create OCL effects. When empty, no upgrade conflicts
- **Default**: `0` (no conflicts)
- **Example**: `ConflictsWith = Upgrade_GLAAnthraxBeta`

## WeaponSlotType Values *(v1.04)*

- **`PRIMARY`** *(v1.04)* - Primary weapon slot
- **`SECONDARY`** *(v1.04)* - Secondary weapon slot
- **`TERTIARY`** *(v1.04)* - Tertiary weapon slot

## Examples

### GLA Toxin Truck with Upgrade Trigger
```ini
Behavior = FireOCLAfterWeaponCooldownUpdate Upgrade_04
  WeaponSlot = SECONDARY
  TriggeredBy = Upgrade_GLAAnthraxBeta Upgrade_Veterancy_HEROIC
  OCL = OCL_PoisonFieldUpgradedMedium
End
```

### GLA Toxin Truck with Upgrade Conflicts
```ini
Behavior = FireOCLAfterWeaponCooldownUpdate ModuleTag_08
  WeaponSlot = SECONDARY
  ConflictsWith = Upgrade_GLAAnthraxBeta Upgrade_Veterancy_HEROIC
  OCL = OCL_PoisonFieldMedium
  MinShotsToCreateOCL = 3
End
```

### GLA CINE Unit with Lifetime Settings
```ini
Behavior = FireOCLAfterWeaponCooldownUpdate ModuleTag_13
  WeaponSlot = SECONDARY
  OCL = OCL_PoisonFieldMedium
  MinShotsToCreateOCL = 5
  OCLLifetimePerSecond = 60
  OCLLifetimeMaxCap = 45000
End
```

## Template

```ini
Behavior = FireOCLAfterWeaponCooldownUpdate ModuleTag_XX
  ; Weapon Settings
  WeaponSlot = SECONDARY           ; // weapon slot to monitor *(v1.04)*
  
  ; OCL Settings
  OCL =                            ; // object creation list to spawn *(v1.04)*
  MinShotsToCreateOCL = 0          ; // minimum shots before OCL creation *(v1.04)*
  OCLLifetimePerSecond = 0         ; // OCL lifetime in frames per second *(v1.04)*
  OCLLifetimeMaxCap = 0            ; // maximum OCL lifetime in milliseconds *(v1.04)*
  
  ; Upgrade Settings
  TriggeredBy =                    ; // required upgrades for activation *(v1.04)*
  ConflictsWith =                  ; // conflicting upgrades *(v1.04)*
End
```

## Notes

- FireOCLAfterWeaponCooldownUpdate creates objects after weapon cooldowns complete
- The update monitors weapon firing events and tracks shot counts
- OCL lifetime can be controlled through both per-second and maximum cap settings
- Upgrade requirements allow conditional OCL creation based on object upgrades
- This update is commonly used for creating persistent area effects or environmental objects
- Multiple instances can monitor different weapon slots simultaneously

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h), [`UpgradeMux`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FireOCLAfterWeaponCooldownUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FireOCLAfterWeaponCooldownUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/FireOCLAfterWeaponCooldownUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/FireOCLAfterWeaponCooldownUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet