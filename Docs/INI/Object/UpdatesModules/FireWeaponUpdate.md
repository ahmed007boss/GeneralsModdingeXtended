# FireWeaponUpdate

FireWeaponUpdate provides weapon firing functionality for objects that can fire weapons.

## Overview

The `FireWeaponUpdate` class manages weapon firing systems that allow objects to automatically fire weapons at regular intervals or under specific conditions. It handles weapon cooldowns, firing delays, and exclusive weapon timing to prevent multiple weapons from firing simultaneously. This update is commonly used by defensive structures, automated turrets, and special weapon systems that need continuous or triggered firing behavior.

## Usage

Used by objects that need to fire weapons, manage weapon cooldowns, and handle weapon firing mechanics. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Weapon firing is limited by weapon cooldowns and initial delays
- Exclusive weapon delays prevent simultaneous firing of multiple weapons
- Requires valid weapon templates to function properly
- Weapon range and targeting depend on the weapon template settings

**Conditions**:
- FireWeaponUpdate automatically fires the specified weapon at regular intervals
- The update respects weapon cooldowns and firing restrictions
- Initial delays prevent immediate weapon firing upon object creation
- Exclusive weapon delays coordinate firing between multiple weapons
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own weapon and timing

**Dependencies**:
- Requires valid weapon templates for firing
- Uses weapon system for cooldown and firing mechanics
- Integrates with targeting systems for weapon direction

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Weapon Settings](#weapon-settings)
  - [Timing Settings](#timing-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Weapon Settings

#### `Weapon` *(v1.04)*
- **Type**: `WeaponTemplate`
- **Description**: The weapon template to fire automatically. When set, the update will fire this weapon. When empty, no weapon firing occurs
- **Default**: `NULL`
- **Example**: `Weapon = GPSScramblerSelfWeapon`

### Timing Settings

#### `InitialDelay` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Delay before the first weapon firing attempt. Higher values delay initial weapon firing longer. Lower values allow sooner initial firing
- **Default**: `0`
- **Example**: `InitialDelay = 1000`

#### `ExclusiveWeaponDelay` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time delay that prevents other weapons from firing after this weapon fires. Higher values create longer exclusive periods. Lower values allow more frequent weapon switching
- **Default**: `0` (no exclusivity)
- **Example**: `ExclusiveWeaponDelay = 1000`

## Examples

### Basic Weapon Firing
```ini
Behavior = FireWeaponUpdate ModuleTag_StealthField02
  Weapon = GPSScramblerSelfWeapon
End
```

### Weapon with Initial Delay
```ini
Behavior = FireWeaponUpdate ModuleTag_20
  Weapon = GLASpawnSpecialPowerObject
  InitialDelay = 2000
End
```

### Exclusive Weapon System
```ini
Behavior = FireWeaponUpdate ModuleTag_StealthField01
  Weapon = GPSScramblerStationWeapon
  ExclusiveWeaponDelay = 1000
End
```

## Template

```ini
Behavior = FireWeaponUpdate ModuleTag_XX
  ; Weapon Settings
  Weapon =                           ; // weapon template to fire automatically *(v1.04)*
  
  ; Timing Settings
  InitialDelay = 0                   ; // delay before first firing attempt *(v1.04)*
  ExclusiveWeaponDelay = 0           ; // delay preventing other weapons from firing *(v1.04)*
End
```

## Notes

- FireWeaponUpdate provides automated weapon firing for defensive and special systems
- The update automatically manages weapon cooldowns and firing timing
- Exclusive weapon delays help coordinate multiple weapon systems on the same object
- Initial delays prevent weapons from firing immediately when objects are created
- This update is commonly used by defensive structures, stealth systems, and automated turrets
- Weapon effectiveness depends on the weapon template's range, damage, and targeting settings

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FireWeaponUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FireWeaponUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/FireWeaponUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/FireWeaponUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet