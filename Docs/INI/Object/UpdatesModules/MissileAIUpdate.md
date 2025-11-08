# MissileAIUpdate

MissileAIUpdate provides AI update functionality for missile and projectile systems.

## Overview

The `MissileAIUpdate` class manages AI-driven flight paths, targeting, and guidance systems for missiles and projectiles. It handles missile states from pre-launch through destruction, manages fuel systems, ignition delays, and provides sophisticated targeting including lock-on mechanics and target following. This update is commonly used by guided missiles, rockets, torpedoes, and other projectile weapons that require intelligent flight behavior.

## Usage

Used by missiles and projectiles to handle AI-driven flight paths, targeting, and guidance systems. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Flight behavior is limited by fuel lifetime and weapon speed constraints
- Target following requires valid target objects or positions
- Lock-on mechanics depend on target proximity and missile capabilities
- Garrison hit mechanics are limited by specified object types

**Conditions**:
- MissileAIUpdate manages complete missile lifecycle from pre-launch to destruction
- The update handles multiple missile states including launch, ignition, attack, and death phases
- Target following can be enabled or disabled based on configuration
- Fuel systems control missile lifetime and behavior when fuel is exhausted
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own flight parameters

**Dependencies**:
- Requires AI system integration for autonomous flight behavior
- Uses weapon system for speed constraints and targeting
- Integrates with FX system for ignition and impact effects
- Uses targeting system for lock-on and guidance mechanics

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Flight Settings](#flight-settings)
  - [Targeting Settings](#targeting-settings)
  - [Fuel Settings](#fuel-settings)
  - [Garrison Hit Settings](#garrison-hit-settings)
  - [Destruction Settings](#destruction-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Flight Settings

#### `TryToFollowTarget` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether the missile attempts to follow and track moving targets. When true, missile actively pursues target objects. When false, missile flies to target position without tracking
- **Default**: `Yes`
- **Example**: `TryToFollowTarget = Yes`

#### `UseWeaponSpeed` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether missile speed is limited by weapon template settings. When true, missile speed is constrained by weapon parameters. When false, missile uses its own speed settings
- **Default**: `Yes`
- **Example**: `UseWeaponSpeed = Yes`

#### `InitialVelocity` *(v1.04)*
- **Type**: `Real` (velocity)
- **Description**: Initial velocity of the missile upon launch. Higher values create faster initial missile speeds. Lower values create slower initial speeds
- **Default**: `0.0`
- **Example**: `InitialVelocity = 50.0`

#### `DistanceToTravelBeforeTurning` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Distance the missile travels straight before beginning to turn toward target. Higher values create longer straight flight paths. Lower values allow immediate turning
- **Default**: `0.0`
- **Example**: `DistanceToTravelBeforeTurning = 600`

### Targeting Settings

#### `DistanceToTargetBeforeDiving` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Distance from target at which missile begins diving attack. Higher values start diving farther from target. Lower values dive closer to target
- **Default**: `0.0`
- **Example**: `DistanceToTargetBeforeDiving = 100.0`

#### `DistanceToTargetForLock` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Distance from target at which missile achieves guaranteed hit lock. Higher values provide longer lock-on range. Lower values require closer approach for lock-on
- **Default**: `0.0`
- **Example**: `DistanceToTargetForLock = 50.0`

#### `DistanceScatterWhenJammed` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Random scatter distance when missile is jammed or loses guidance. Higher values create larger scatter patterns. Lower values create smaller scatter patterns
- **Default**: `0.0`
- **Example**: `DistanceScatterWhenJammed = 200.0`

### Fuel Settings

#### `FuelLifetime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Duration of missile fuel before engine cutoff. Higher values provide longer flight time. At 0, missile has infinite fuel
- **Default**: `0` (infinite)
- **Example**: `FuelLifetime = 99999`

#### `IgnitionDelay` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Delay between missile launch and engine ignition. Higher values create longer delays before missile becomes active. Lower values allow faster ignition
- **Default**: `0`
- **Example**: `IgnitionDelay = 500`

#### `IgnitionFX` *(v1.04)*
- **Type**: `FXList`
- **Description**: Effects played when missile engines ignite. When set, displays ignition effects. When empty, no ignition effects are shown
- **Default**: `NULL`
- **Example**: `IgnitionFX = FX_MissileIgnition`

#### `DetonateOnNoFuel` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether missile explodes when fuel runs out. When true, missile detonates when fuel exhausted. When false, missile continues gliding without engine
- **Default**: `No`
- **Example**: `DetonateOnNoFuel = Yes`

### Garrison Hit Settings

#### `GarrisonHitKillCount` *(v1.04)*
- **Type**: `UnsignedInt`
- **Description**: Number of garrisoned units killed when missile hits garrisoned building. Higher values kill more units. Lower values kill fewer units
- **Default**: `0`
- **Example**: `GarrisonHitKillCount = 3`

#### `GarrisonHitKillRequiredKindOf` *(v1.04)*
- **Type**: `KindOfMaskType` (bit flags)
- **Description**: Unit types that can be killed by garrison hits. When set, only specified unit types are affected. When empty, all unit types can be affected
- **Default**: `0` (all types)
- **Example**: `GarrisonHitKillRequiredKindOf = INFANTRY`

#### `GarrisonHitKillForbiddenKindOf` *(v1.04)*
- **Type**: `KindOfMaskType` (bit flags)
- **Description**: Unit types that cannot be killed by garrison hits. When set, specified unit types are immune. When empty, no unit types are immune
- **Default**: `0` (no restrictions)
- **Example**: `GarrisonHitKillForbiddenKindOf = VEHICLE`

#### `GarrisonHitKillFX` *(v1.04)*
- **Type**: `FXList`
- **Description**: Effects played when garrisoned units are killed by missile hit. When set, displays kill effects. When empty, no kill effects are shown
- **Default**: `NULL`
- **Example**: `GarrisonHitKillFX = FX_GarrisonKill`

### Destruction Settings

#### `DetonateCallsKill` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether detonation calls kill() function instead of destroy. When true, uses kill() for destruction. When false, uses destroy() for destruction
- **Default**: `No`
- **Example**: `DetonateCallsKill = Yes`

## Examples

### Basic Guided Missile
```ini
Behavior = MissileAIUpdate ModuleTag_05
  TryToFollowTarget       = Yes 
  FuelLifetime            = 99999
  UseWeaponSpeed          = Yes
End
```

### Missile with Detonation
```ini
Behavior = MissileAIUpdate ModuleTag_07
  DetonateCallsKill = Yes
  TryToFollowTarget = Yes
  FuelLifetime = 2333
End
```

### Non-Guided Missile
```ini
Behavior = MissileAIUpdate ModuleTag_04
  DetonateCallsKill = Yes
  TryToFollowTarget       = No
  FuelLifetime        = 9999
End
```

## Template

```ini
Behavior = MissileAIUpdate ModuleTag_XX
  ; Flight Settings
  TryToFollowTarget = Yes               ; // whether missile tracks moving targets *(v1.04)*
  UseWeaponSpeed = Yes                  ; // limit speed by weapon template *(v1.04)*
  InitialVelocity = 0.0                 ; // initial missile velocity *(v1.04)*
  DistanceToTravelBeforeTurning = 0.0   ; // distance before turning toward target *(v1.04)*
  
  ; Targeting Settings
  DistanceToTargetBeforeDiving = 0.0    ; // distance to start diving attack *(v1.04)*
  DistanceToTargetForLock = 0.0         ; // distance for guaranteed hit lock *(v1.04)*
  DistanceScatterWhenJammed = 0.0       ; // scatter distance when jammed *(v1.04)*
  
  ; Fuel Settings
  FuelLifetime = 0                      ; // missile fuel duration *(v1.04)*
  IgnitionDelay = 0                     ; // delay before engine ignition *(v1.04)*
  IgnitionFX =                          ; // effects when engines ignite *(v1.04)*
  DetonateOnNoFuel = No                 ; // explode when fuel exhausted *(v1.04)*
  
  ; Garrison Hit Settings
  GarrisonHitKillCount = 0              ; // units killed in garrison hits *(v1.04)*
  GarrisonHitKillRequiredKindOf =       ; // required unit types for garrison kills *(v1.04)*
  GarrisonHitKillForbiddenKindOf =      ; // forbidden unit types for garrison kills *(v1.04)*
  GarrisonHitKillFX =                   ; // effects for garrison kills *(v1.04)*
  
  ; Destruction Settings
  DetonateCallsKill = No                ; // use kill() instead of destroy() *(v1.04)*
End
```

## Notes

- MissileAIUpdate provides sophisticated AI-driven missile behavior with multiple flight phases
- The update manages complete missile lifecycle from pre-launch through destruction
- Target following and lock-on mechanics provide realistic guided missile behavior
- Fuel systems create realistic missile flight limitations and behaviors
- Garrison hit mechanics allow missiles to damage units inside buildings
- This update is commonly used by guided missiles, rockets, torpedoes, and smart projectiles
- Multiple missile states provide fine-grained control over missile behavior phases

## Source Files

**Base Class:** [`AIUpdateInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h), [`ProjectileUpdateInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/MissileAIUpdate.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/MissileAIUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/MissileAIUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/MissileAIUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/MissileAIUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet