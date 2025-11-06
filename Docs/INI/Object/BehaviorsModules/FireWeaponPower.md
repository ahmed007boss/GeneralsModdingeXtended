# FireWeaponPower

FireWeaponPower provides special weapon firing capabilities for superweapons and special powers.

## Overview

The `FireWeaponPower` class enables objects to fire their weapons as part of special power activation. It automatically reloads all ammo and directs the AI to attack specific targets or locations with a configurable number of shots. This behavior is commonly used for superweapons, special abilities, and automated defensive systems that need to fire weapons on command.

## Usage

Used by objects that need to fire weapons as part of special power activation, such as superweapons, defensive systems, or special ability units. This is a **special power module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- FireWeaponPower only functions when the special power is activated
- The behavior requires the object to have weapons and AI capabilities
- Maximum shots fired is limited by the MaxShotsToFire setting
- The behavior only works when the object is not disabled
- FireWeaponPower is exclusive to Generals Zero Hour (v1.04)

**Conditions**:
- FireWeaponPower automatically reloads all ammunition before firing
- The behavior can target specific objects, locations, or fire without a specific target
- Turrets are automatically directed to attack the same target as the main weapon
- The behavior integrates with the AI system for weapon firing coordination
- Special power timing and cooldown systems control when the behavior can activate
- **Multiple instances behavior**: Only one instance should be used per object; multiple instances may cause conflicts in weapon firing coordination

**Dependencies**:
- Requires valid weapon definitions and AI system integration to function
- The behavior relies on SpecialPowerModule base functionality for activation timing

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Weapon Control](#weapon-control)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

### Weapon Control

#### `MaxShotsToFire` *(v1.04, Generals Zero Hour only)*
- **Type**: `UnsignedInt`
- **Description**: Maximum number of shots to fire when the special power is activated. Higher values allow the special power to fire more projectiles per activation, increasing damage potential
- **Default**: `1`
- **Example**: `MaxShotsToFire = 3`

## Examples

### Superweapon Fire Power
```ini
SpecialPower = FireWeaponPower ModuleTag_SuperWeapon
  MaxShotsToFire = 5
End
```

### Defensive System Fire Power
```ini
SpecialPower = FireWeaponPower ModuleTag_Defense
  MaxShotsToFire = 1
End
```

### Multi-Shot Special Power
```ini
SpecialPower = FireWeaponPower ModuleTag_MultiShot
  MaxShotsToFire = 10
End
```

## Template

```ini
SpecialPower = FireWeaponPower ModuleTag_XX
  MaxShotsToFire = 1                   ; // maximum shots to fire when activated *(v1.04, Generals Zero Hour only)*
End
```

## Notes

- FireWeaponPower automatically reloads all ammunition before firing
- The behavior can target specific objects, locations, or fire without a specific target
- Turrets are automatically directed to attack the same target as the main weapon
- The behavior integrates with the AI system for weapon firing coordination
- Special power timing and cooldown systems control when the behavior can activate
- FireWeaponPower is exclusive to Generals Zero Hour (v1.04)

## Source Files

**Base Class:** [`SpecialPowerModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FireWeaponPower.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FireWeaponPower.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/SpecialPower/FireWeaponPower.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/SpecialPower/FireWeaponPower.cpp)