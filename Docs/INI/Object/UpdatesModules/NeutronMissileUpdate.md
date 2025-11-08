# NeutronMissileUpdate

NeutronMissileUpdate provides neutron missile functionality for objects that can create or use neutron missile effects.

## Overview

The `NeutronMissileUpdate` class manages neutron missile behavior including flight patterns, targeting mechanics, and neutron weapon deployment. It handles specialized neutron missile flight characteristics, delivery mechanics, and neutron blast effects. This update is commonly used by neutron missiles, neutron weapons, and superweapon systems that deploy neutron-based destructive effects.

## Usage

Used by objects that can create neutron missiles, neutron weapons, or neutron-based special effects. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Flight behavior is limited by neutron missile-specific parameters
- Delivery mechanics are controlled by neutron weapon characteristics
- Neutron effects depend on proper FX and decal templates
- Special speed and acceleration are limited by specified factors

**Conditions**:
- NeutronMissileUpdate manages specialized neutron missile flight and targeting
- The update handles neutron weapon delivery mechanics and impact patterns
- Special speed and acceleration create dramatic neutron missile flight patterns
- Neutron blast effects and delivery decals provide visual impact
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own neutron parameters

**Dependencies**:
- Uses FX system for launch and ignition effects
- Integrates with decal system for delivery impact marks
- Uses projectile system for missile flight mechanics

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Flight Settings](#flight-settings)
  - [Special Effects Settings](#special-effects-settings)
  - [Delivery Settings](#delivery-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Flight Settings

#### `DistanceToTravelBeforeTurning` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Distance the neutron missile travels straight before beginning to turn toward target. Higher values create longer straight flight paths. Lower values allow immediate turning
- **Default**: `0.0`
- **Example**: `DistanceToTravelBeforeTurning = 600`

#### `MaxTurnRate` *(v1.04)*
- **Type**: `Real` (angular velocity)
- **Description**: Maximum turning rate for neutron missile during flight. Higher values allow sharper turns. Lower values create more gradual turning
- **Default**: `0.0`
- **Example**: `MaxTurnRate = 7200`

#### `ForwardDamping` *(v1.04)*
- **Type**: `Real`
- **Description**: Forward velocity damping factor for neutron missile. Higher values create more damping. Lower values maintain velocity better
- **Default**: `0.0`
- **Example**: `ForwardDamping = 0.1`

#### `RelativeSpeed` *(v1.04)*
- **Type**: `Real`
- **Description**: Relative speed factor for neutron missile flight. Higher values create faster flight. Lower values create slower flight
- **Default**: `0.0`
- **Example**: `RelativeSpeed = 1.0`

#### `TargetFromDirectlyAbove` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Distance offset for targeting from directly above target. Higher values create larger offset. Lower values create smaller offset
- **Default**: `0.0`
- **Example**: `TargetFromDirectlyAbove = 100.0`

### Special Effects Settings

#### `LaunchFX` *(v1.04)*
- **Type**: `FXList`
- **Description**: Effects played when neutron missile launches. When set, displays launch effects. When empty, no launch effects are shown
- **Default**: `NULL`
- **Example**: `LaunchFX = FX_NeutronLaunch`

#### `IgnitionFX` *(v1.04)*
- **Type**: `FXList`
- **Description**: Effects played when neutron missile engines ignite. When set, displays ignition effects. When empty, no ignition effects are shown
- **Default**: `NULL`
- **Example**: `IgnitionFX = FX_NeutronIgnition`

#### `SpecialSpeedTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Duration of special speed boost for neutron missile. Higher values provide longer speed boost. Lower values provide shorter boost
- **Default**: `0`
- **Example**: `SpecialSpeedTime = 5000`

#### `SpecialSpeedHeight` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Height at which special speed boost activates. Higher values activate boost at greater heights. Lower values activate boost closer to ground
- **Default**: `0.0`
- **Example**: `SpecialSpeedHeight = 1000.0`

#### `SpecialAccelFactor` *(v1.04)*
- **Type**: `Real`
- **Description**: Acceleration factor for special speed boost. Higher values provide greater acceleration. Lower values provide less acceleration
- **Default**: `0.0`
- **Example**: `SpecialAccelFactor = 2.0`

#### `SpecialJitterDistance` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Jitter distance for special speed effects. Higher values create more jitter. Lower values create less jitter
- **Default**: `0.0`
- **Example**: `SpecialJitterDistance = 50.0`

### Delivery Settings

#### `DeliveryDecal` *(v1.04)*
- **Type**: `RadiusDecalTemplate`
- **Description**: Decal template for neutron missile delivery impact marks. When set, creates delivery decals. When empty, no delivery decals are created
- **Default**: `NULL`
- **Example**: `DeliveryDecal = NeutronImpactDecal`

## Examples

### Basic Neutron Missile
```ini
Behavior = NeutronMissileUpdate ModuleTag_03
  DistanceToTravelBeforeTurning = 600       ; goes straight up a long ways first
  MaxTurnRate = 7200                        ; huge, since it turns off-camera
  ForwardDamping = 0.1
End
```

### Advanced Neutron Missile
```ini
Behavior = NeutronMissileUpdate ModuleTag_07
  DistanceToTravelBeforeTurning = 600       ; goes straight up a long ways first
  MaxTurnRate = 7200                        ; huge, since it turns off-camera
  ForwardDamping = 0.1
  SpecialSpeedTime = 3000
  SpecialAccelFactor = 1.5
  LaunchFX = FX_NeutronLaunch
  IgnitionFX = FX_NeutronIgnition
End
```

## Template

```ini
Behavior = NeutronMissileUpdate ModuleTag_XX
  ; Flight Settings
  DistanceToTravelBeforeTurning = 0.0      ; // distance before turning toward target *(v1.04)*
  MaxTurnRate = 0.0                        ; // maximum turning rate *(v1.04)*
  ForwardDamping = 0.0                     ; // forward velocity damping *(v1.04)*
  RelativeSpeed = 0.0                      ; // relative speed factor *(v1.04)*
  TargetFromDirectlyAbove = 0.0            ; // targeting offset from above *(v1.04)*
  
  ; Special Effects Settings
  LaunchFX =                               ; // effects when missile launches *(v1.04)*
  IgnitionFX =                             ; // effects when engines ignite *(v1.04)*
  SpecialSpeedTime = 0                     ; // duration of special speed boost *(v1.04)*
  SpecialSpeedHeight = 0.0                 ; // height for special speed activation *(v1.04)*
  SpecialAccelFactor = 0.0                 ; // acceleration factor for boost *(v1.04)*
  SpecialJitterDistance = 0.0              ; // jitter distance for effects *(v1.04)*
  
  ; Delivery Settings
  DeliveryDecal =                          ; // decal template for impact marks *(v1.04)*
End
```

## Notes

- NeutronMissileUpdate provides specialized neutron missile flight and delivery mechanics
- The update manages neutron weapon deployment with dramatic flight patterns
- Special speed and acceleration effects create cinematic neutron missile behavior
- Delivery decals provide visual impact marks for neutron weapon strikes
- This update is commonly used by neutron missiles, neutron superweapons, and nuclear weapons
- Neutron missile behavior creates realistic superweapon deployment sequences

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h), [`DieModuleInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h), [`ProjectileUpdateInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/NeutronMissileUpdate.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/NeutronMissileUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/NeutronMissileUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/NeutronMissileUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/NeutronMissileUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet