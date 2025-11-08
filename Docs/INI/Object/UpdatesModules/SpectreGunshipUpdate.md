# SpectreGunshipUpdate

SpectreGunshipUpdate provides update functionality specifically for Spectre gunship units.

## Overview

The `SpectreGunshipUpdate` class manages update operations for Spectre gunship units that need specialized update mechanics and operations. It handles gunship operations, weapon systems, orbit mechanics, and special power integration for Spectre gunship functionality. This update is commonly used by Spectre gunship units, aerial combat systems, and units with specialized gunship capabilities.

## Usage

Used by Spectre gunship units that need specialized update mechanics and operations. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Spectre gunship operations are limited by special power templates and gunship parameters
- Gunship operations depend on proper weapon system configuration
- Orbit mechanics require proper orbit parameters and coordination
- Gunship effectiveness varies based on gunship capabilities

**Conditions**:
- SpectreGunshipUpdate manages Spectre gunship operations and weapon systems
- The update handles gunship operations, weapon systems, and orbit mechanics
- Gunship operations provide specialized aerial combat capabilities
- Orbit mechanics create realistic gunship orbital operations
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own gunship parameters

**Dependencies**:
- Uses special power system for gunship activation
- Integrates with weapon system for gunship weapons
- Uses orbit system for gunship orbital mechanics

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Gunship Settings](#gunship-settings)
  - [Weapon Settings](#weapon-settings)
  - [Orbit Settings](#orbit-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Gunship Settings

#### `SpecialPowerTemplate` *(v1.04)*
- **Type**: `SpecialPowerTemplate`
- **Description**: Template defining the special power for gunship operations. When set, provides special power functionality. When empty, no special power is available
- **Default**: `""`
- **Example**: `SpecialPowerTemplate = SuperweaponSpectreGunship`

### Weapon Settings

#### `GattlingStrafeFXParticleSystem` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Particle system for Gatling strafe effects. When set, creates specified particle effect. When empty, no Gatling strafe effect is created
- **Default**: `""`
- **Example**: `GattlingStrafeFXParticleSystem = SpectreGattlingArmsSmoke`

#### `HowitzerWeapon` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Name of the howitzer weapon to use. When set, uses specified howitzer weapon. When empty, uses default howitzer weapon
- **Default**: `""`
- **Example**: `HowitzerWeapon = SpectreHowitzerGun`

### Orbit Settings

#### `OrbitInsertionSlope` *(v1.04)*
- **Type**: `Real`
- **Description**: Steepness of orbit entry for gunship operations. Higher values create steeper orbit entry. Lower values create gentler orbit entry
- **Default**: `0.0`
- **Example**: `OrbitInsertionSlope = 0.7`

#### `GunshipOrbitRadius` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Radius of the gunship orbit. Higher values create larger orbits. Lower values create smaller orbits
- **Default**: `0.0`
- **Example**: `GunshipOrbitRadius = 300`

## Examples

### Basic Spectre Gunship
```ini
Behavior = SpectreGunshipUpdate ModuleTag_06
  GattlingStrafeFXParticleSystem  = SpectreGattlingArmsSmoke
  SpecialPowerTemplate            = SuperweaponSpectreGunship
  HowitzerWeapon          = SpectreHowitzerGun
End
```

### AWACS Gunship
```ini
Behavior = SpectreGunshipUpdate ModuleTag_06
  SpecialPowerTemplate            = SuperweaponAWACS
  OrbitInsertionSlope     = 0.7   ; steepness of orbit entry
  GunshipOrbitRadius      = 300
End
```

### Advanced AWACS Gunship
```ini
Behavior = SpectreGunshipUpdate ModuleTag_06
  SpecialPowerTemplate            = SuperweaponAWACS
  OrbitInsertionSlope     = 0.7   ; steepness of orbit entry
  GunshipOrbitRadius      = 350
End
```

## Template

```ini
Behavior = SpectreGunshipUpdate ModuleTag_XX
  ; Gunship Settings
  SpecialPowerTemplate =                   ; // special power template for gunship operations *(v1.04)*
  
  ; Weapon Settings
  GattlingStrafeFXParticleSystem =         ; // particle system for Gatling strafe effects *(v1.04)*
  HowitzerWeapon =                         ; // name of howitzer weapon to use *(v1.04)*
  
  ; Orbit Settings
  OrbitInsertionSlope = 0.0                ; // steepness of orbit entry *(v1.04)*
  GunshipOrbitRadius = 0.0                 ; // radius of gunship orbit *(v1.04)*
End
```

## Notes

- SpectreGunshipUpdate provides specialized update capabilities for Spectre gunship units
- The update manages gunship operations, weapon systems, and orbit mechanics
- Gunship operations provide specialized aerial combat capabilities for tactical advantage
- Orbit mechanics create realistic gunship orbital operations and area control
- This update is commonly used by Spectre gunship units, aerial combat systems, and specialized gunship units
- Gunship operations create powerful aerial combat capabilities for tactical operations

## Source Files

**Base Class:** [`SpecialPowerUpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerUpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpectreGunshipUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpectreGunshipUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/SpectreGunshipUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/SpectreGunshipUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet