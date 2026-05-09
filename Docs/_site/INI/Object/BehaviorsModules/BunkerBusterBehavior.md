# BunkerBusterBehavior

Update module that provides specialized behavior for bunker buster weapons and projectiles that can penetrate structures and create seismic effects.

## Overview

BunkerBusterBehavior is an update module designed for bunker buster weapons and projectiles that can penetrate structures and create devastating effects. It handles penetration mechanics, delayed detonation, structure-specific damage, and seismic effects. The module supports upgrade-based activation and provides visual feedback during penetration and detonation phases.

BunkerBusterBehavior must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by bunker buster projectiles and weapons to handle penetration mechanics, delayed detonation, and structure-specific damage. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Designed specifically for bunker buster weapons and projectiles
- Requires proper upgrade system for conditional activation
- Cannot function without proper damage and update systems
- Requires proper FX and weapon templates for effects

**Conditions**:
- Multiple instances behavior: Multiple BunkerBusterBehavior modules can exist independently, each managing different bunker buster systems
- Always active once assigned to an object
- Continuously monitors for target acquisition and penetration opportunities
- Creates devastating anti-structure capabilities with seismic effects

**Dependencies**:
- Depends on the upgrade system for conditional activation
- Requires proper weapon templates for shockwave and occupant damage
- Inherits functionality from UpdateModule and DieModuleInterface

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Upgrade Requirements](#upgrade-requirements)
  - [Visual Effects](#visual-effects)
  - [Seismic Effects](#seismic-effects)
  - [Weapon Templates](#weapon-templates)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

### Upgrade Requirements

#### `UpgradeRequired` *(v1.04)*
- **Type**: `AsciiString` (see [Upgrade documentation](../Upgrade.md))
- **Description**: Name of the upgrade required to activate bunker buster functionality. When set, the bunker buster only functions when the specified upgrade is active. When empty (default), no upgrade is required
- **Default**: `""` (empty)
- **Example**: `UpgradeRequired = Upgrade_AmericaLaserMissiles`

### Visual Effects

#### `DetonationFX` *(v1.04)*
- **Type**: `FXList` (see [FXList documentation](../FXList.md))
- **Description**: FX list executed upon final detonation. When set, displays visual effects during the main explosion. When empty (default), no detonation effects are shown
- **Default**: `""` (empty)
- **Example**: `DetonationFX = FX_BunkerBusterExplosion`

#### `CrashThroughBunkerFX` *(v1.04)*
- **Type**: `FXList` (see [FXList documentation](../FXList.md))
- **Description**: FX list executed as the projectile crashes through bunker structures. When set, displays visual effects during penetration. When empty (default), no penetration effects are shown
- **Default**: `""` (empty)
- **Example**: `CrashThroughBunkerFX = WeaponFX_BunkerBusterIntialImpact`

#### `CrashThroughBunkerFXFrequency` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Frequency at which crash-through effects are played during penetration. Lower values create more frequent effects. Higher values create less frequent effects. At 4 (default), effects play every 4 milliseconds
- **Default**: `4`
- **Example**: `CrashThroughBunkerFXFrequency = 571`

### Seismic Effects

#### `SeismicEffectRadius` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Radius of seismic effects created by the bunker buster detonation. Higher values create larger seismic impact areas. Lower values create smaller, more focused seismic effects
- **Default**: `140.0`
- **Example**: `SeismicEffectRadius = 200.0`

#### `SeismicEffectMagnitude` *(v1.04)*
- **Type**: `Real`
- **Description**: Magnitude of seismic effects created by the bunker buster detonation. Higher values create more intense seismic effects. Lower values create gentler seismic effects
- **Default**: `6.0`
- **Example**: `SeismicEffectMagnitude = 5.0`

### Weapon Templates

#### `ShockwaveWeapon` *(v1.04)*
- **Type**: `Weapon` (see [Weapon documentation](../Weapon.md))
- **Description**: Weapon template fired when the bunker buster detonates to generate shockwave effects. When set, creates additional shockwave damage. When empty (default), no shockwave weapon is fired
- **Default**: `""` (empty)
- **Example**: `ShockwaveWeapon = BunkerBusterShockwaveWeaponSmall`

#### `OccupantDamageWeapon` *(v1.04)*
- **Type**: `Weapon` (see [Weapon documentation](../Weapon.md))
- **Description**: Weapon template used to damage occupants of structures struck by the bunker buster. When set, applies damage to garrisoned units. When empty (default), no occupant damage is applied
- **Default**: `""` (empty)
- **Example**: `OccupantDamageWeapon = BunkerBusterOccupantDamageWeapon`

## Examples

### Basic Bunker Buster
```ini
Behavior = BunkerBusterBehavior ModuleTag_04
  UpgradeRequired = Upgrade_AmericaLaserMissiles
  DetonationFX = FX_BunkerBusterExplosion
  CrashThroughBunkerFX = WeaponFX_BunkerBusterIntialImpact
  CrashThroughBunkerFXFrequency = 571
  SeismicEffectRadius = 200
  SeismicEffectMagnitude = 5
  ShockwaveWeapon = BunkerBusterShockwaveWeaponSmall
End
```

### Enhanced Bunker Buster with Occupant Damage
```ini
Behavior = BunkerBusterBehavior ModuleTag_05
  UpgradeRequired = Upgrade_AmericaLaserMissiles
  DetonationFX = FX_BunkerBusterExplosion
  CrashThroughBunkerFX = WeaponFX_BunkerBusterIntialImpact
  CrashThroughBunkerFXFrequency = 300
  SeismicEffectRadius = 250
  SeismicEffectMagnitude = 7
  ShockwaveWeapon = BunkerBusterShockwaveWeaponSmall
  OccupantDamageWeapon = BunkerBusterOccupantDamageWeapon
End
```

### No Upgrade Required Bunker Buster
```ini
Behavior = BunkerBusterBehavior ModuleTag_13
  DetonationFX = FX_BunkerBusterExplosion
  CrashThroughBunkerFX = WeaponFX_BunkerBusterIntialImpact
  CrashThroughBunkerFXFrequency = 571
  SeismicEffectRadius = 200
  SeismicEffectMagnitude = 5
  ShockwaveWeapon = BunkerBusterShockwaveWeaponSmall
End
```

## Template

```ini
Behavior = BunkerBusterBehavior ModuleTag_XX
  ; Upgrade Requirements
  UpgradeRequired =                       ; // required upgrade for activation *(v1.04)*
  
  ; Visual Effects
  DetonationFX =                          ; // FX list for final detonation *(v1.04)*
  CrashThroughBunkerFX =                  ; // FX list for penetration effects *(v1.04)*
  CrashThroughBunkerFXFrequency = 4       ; // frequency of penetration effects *(v1.04)*
  
  ; Seismic Effects
  SeismicEffectRadius = 140.0             ; // radius of seismic effects *(v1.04)*
  SeismicEffectMagnitude = 6.0            ; // magnitude of seismic effects *(v1.04)*
  
  ; Weapon Templates
  ShockwaveWeapon =               ; // weapon for shockwave effects *(v1.04)*
  OccupantDamageWeapon =          ; // weapon for occupant damage *(v1.04)*
End
```

## Notes

- BunkerBusterBehavior provides devastating anti-structure capabilities with penetration and seismic effects
- The module supports upgrade-based activation for conditional functionality
- Visual effects provide feedback during both penetration and detonation phases
- Seismic effects create area-of-impact damage beyond the initial detonation
- Shockwave and occupant damage weapons provide additional tactical effects
- This creates realistic bunker buster behavior with proper penetration mechanics

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h), [`DieModuleInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BunkerBusterBehavior.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BunkerBusterBehavior.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/BunkerBusterBehavior.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/BunkerBusterBehavior.cpp)
