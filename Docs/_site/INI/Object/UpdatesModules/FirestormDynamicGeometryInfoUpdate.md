# FirestormDynamicGeometryInfoUpdate

FirestormDynamicGeometryInfoUpdate provides firestorm dynamic geometry information functionality for objects with firestorm effects.

## Overview

The `FirestormDynamicGeometryInfoUpdate` class manages firestorm effects with dynamic geometry that changes over time. It creates multiple particle systems, handles damage over time, manages scorch marks, and controls the visual evolution of firestorm effects. This update extends DynamicGeometryInfoUpdate to provide specialized firestorm behavior with damage, visual effects, and terrain modification.

## Usage

Used by objects that have firestorm effects with dynamic geometry that changes over time. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Firestorm effects are limited to 16 particle systems maximum
- Damage is applied at regular intervals based on delay settings
- Height restrictions limit damage to objects within specified elevation ranges
- Particle systems require proper templates to function correctly

**Conditions**:
- FirestormDynamicGeometryInfoUpdate creates multiple particle systems for layered firestorm effects
- The update applies damage over time to objects within the firestorm area
- Scorch marks are placed on terrain to show firestorm impact
- Dynamic geometry changes create evolving firestorm visual effects
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own particle systems and damage

**Dependencies**:
- Requires particle system templates for visual effects
- Uses FXList for additional firestorm effects
- Integrates with damage system for area-of-effect damage
- Uses terrain system for scorch mark placement

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Timing Properties](#timing-properties)
  - [Damage Properties](#damage-properties)
  - [Visual Properties](#visual-properties)
  - [Particle Systems](#particle-systems)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Timing Properties

#### `InitialDelay` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Delay before firestorm effects begin. Higher values delay firestorm start. Lower values begin firestorm effects sooner
- **Default**: `800`
- **Example**: `InitialDelay = 1000`

### Damage Properties

#### `DelayBetweenDamageFrames` *(v1.04)*
- **Type**: `Real` (milliseconds)
- **Description**: Time interval between damage application cycles. Higher values reduce damage frequency. Lower values apply damage more frequently
- **Default**: `100.0`
- **Example**: `DelayBetweenDamageFrames = 200.0`

#### `DamageAmount` *(v1.04)*
- **Type**: `Real`
- **Description**: Amount of damage applied per damage cycle. Higher values cause more damage per cycle. Lower values cause less damage per cycle
- **Default**: `50.0`
- **Example**: `DamageAmount = 75.0`

#### `MaxHeightForDamage` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Maximum height above the firestorm that can take damage. Higher values allow damage to taller objects. Lower values limit damage to lower objects only
- **Default**: `10.0`
- **Example**: `MaxHeightForDamage = 15.0`

### Visual Properties

#### `InitialHeight` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Initial height of the firestorm effect. Higher values create taller initial firestorms. Lower values create shorter initial effects
- **Default**: `8.0`
- **Example**: `InitialHeight = 10.0`

#### `InitialMajorRadius` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Initial radius of the firestorm effect. Higher values create larger initial firestorms. Lower values create smaller initial effects
- **Default**: `5.0`
- **Example**: `InitialMajorRadius = 7.0`

#### `FXList` *(v1.04)*
- **Type**: `FXList`
- **Description**: Additional effects list for firestorm visual enhancements. When set, plays additional visual effects. When empty, no additional effects are shown
- **Default**: `NULL`
- **Example**: `FXList = FX_FirestormEffects`

#### `ParticleOffsetZ` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Vertical offset for particle system positioning. Higher values raise particle systems above the firestorm. Lower values lower particle systems closer to ground
- **Default**: `0.0`
- **Example**: `ParticleOffsetZ = 2.0`

#### `ScorchSize` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Size of scorch marks placed on terrain. Higher values create larger scorch marks. Lower values create smaller scorch marks
- **Default**: `10.0`
- **Example**: `ScorchSize = 15.0`

### Particle Systems

#### `ParticleSystem1` through `ParticleSystem16` *(v1.04)*
- **Type**: `ParticleSystemTemplate`
- **Description**: Particle system templates for firestorm visual effects. Each system creates a different layer of the firestorm effect. Up to 16 particle systems can be used simultaneously
- **Default**: `NULL`
- **Example**: `ParticleSystem1 = PS_FirestormCore`

## Examples

### Basic Firestorm Effect
```ini
Behavior = FirestormDynamicGeometryInfoUpdate ModuleTag_03
  InitialDelay = 800
  InitialHeight = 8.0
  InitialMajorRadius = 5.0
  DelayBetweenDamageFrames = 100.0
  DamageAmount = 50.0
End
```

### Large Firestorm with Multiple Effects
```ini
Behavior = FirestormDynamicGeometryInfoUpdate ModuleTag_04
  InitialDelay = 1000
  InitialHeight = 12.0
  InitialMajorRadius = 15.0
  DelayBetweenDamageFrames = 150.0
  DamageAmount = 75.0
  MaxHeightForDamage = 20.0
  ParticleSystem1 = PS_FirestormCore
  ParticleSystem2 = PS_FirestormFlames
  FXList = FX_FirestormEffects
  ScorchSize = 20.0
End
```

### Intense Firestorm
```ini
Behavior = FirestormDynamicGeometryInfoUpdate ModuleTag_05
  InitialDelay = 500
  InitialHeight = 15.0
  InitialMajorRadius = 10.0
  DelayBetweenDamageFrames = 50.0
  DamageAmount = 100.0
  MaxHeightForDamage = 25.0
  ParticleOffsetZ = 3.0
End
```

## Template

```ini
Behavior = FirestormDynamicGeometryInfoUpdate ModuleTag_XX
  ; Timing Properties
  InitialDelay = 800                    ; // delay before firestorm begins *(v1.04)*
  
  ; Damage Properties
  DelayBetweenDamageFrames = 100.0      ; // time between damage cycles *(v1.04)*
  DamageAmount = 50.0                   ; // damage per cycle *(v1.04)*
  MaxHeightForDamage = 10.0             ; // maximum height for damage *(v1.04)*
  
  ; Visual Properties
  InitialHeight = 8.0                   ; // initial firestorm height *(v1.04)*
  InitialMajorRadius = 5.0              ; // initial firestorm radius *(v1.04)*
  FXList =                              ; // additional effects list *(v1.04)*
  ParticleOffsetZ = 0.0                 ; // particle system vertical offset *(v1.04)*
  ScorchSize = 10.0                     ; // scorch mark size *(v1.04)*
  
  ; Particle Systems (up to 16)
  ParticleSystem1 =                     ; // first particle system *(v1.04)*
  ParticleSystem2 =                     ; // second particle system *(v1.04)*
  ParticleSystem3 =                     ; // third particle system *(v1.04)*
  ; ... up to ParticleSystem16
End
```

## Notes

- FirestormDynamicGeometryInfoUpdate extends DynamicGeometryInfoUpdate with firestorm-specific functionality
- The update can use up to 16 different particle systems for complex layered firestorm effects
- Damage is applied continuously over time to objects within the firestorm area
- Scorch marks are automatically placed on terrain to show firestorm impact
- Height restrictions prevent damage to objects too high above the firestorm
- This update is commonly used for superweapon firestorm effects and large area damage

## Source Files

**Base Class:** [`DynamicGeometryInfoUpdate`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DynamicGeometryInfoUpdate.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FirestormDynamicGeometryInfoUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FirestormDynamicGeometryInfoUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/FirestormDynamicGeometryInfoUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/FirestormDynamicGeometryInfoUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet