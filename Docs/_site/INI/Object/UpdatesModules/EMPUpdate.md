# EMPUpdate

EMPUpdate provides electromagnetic pulse (EMP) functionality for objects that can create or be affected by EMP effects.

## Overview

The `EMPUpdate` class manages electromagnetic pulse effects that can disable nearby objects within a specified radius. It creates visual effects with scaling and color transitions, applies EMP damage to affected objects, and manages the lifetime of the EMP field. The update can target specific object types and exclude certain categories from EMP effects.

## Usage

Used by objects that can create EMP effects or are affected by electromagnetic pulse attacks. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- EMP effects only affect objects within the specified radius
- Objects can be excluded using DoesNotAffect mask or KindOf filters
- Visual effects are limited by the specified lifetime and scaling parameters
- EMP duration is controlled by DisabledDuration property

**Conditions**:
- EMPUpdate creates an expanding EMP field that affects nearby objects
- The update applies EMP damage and visual effects to qualifying targets
- Objects can be filtered by KindOf requirements and forbidden types
- Visual scaling and color transitions occur over the EMP lifetime
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own radius and effects

**Dependencies**:
- Requires objects with EMP vulnerability to be affected
- Visual effects depend on particle system templates
- Target filtering uses KindOf system for object type checking

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Timing Properties](#timing-properties)
  - [Visual Properties](#visual-properties)
  - [Effect Properties](#effect-properties)
  - [Target Filtering](#target-filtering)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Timing Properties

#### `Lifetime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Total duration of the EMP effect. Higher values make the EMP field last longer, affecting more objects. Lower values create shorter, more intense EMP bursts
- **Default**: `1`
- **Example**: `Lifetime = 1500`

#### `StartFadeTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time when the EMP field starts fading out. Higher values maintain full intensity longer. Lower values cause earlier fading of the EMP effect
- **Default**: `0`
- **Example**: `StartFadeTime = 400`

### Visual Properties

#### `StartScale` *(v1.04)*
- **Type**: `Real`
- **Description**: Initial size scale of the EMP visual effect. Higher values create larger initial EMP fields. Lower values start with smaller visual effects
- **Default**: `1.0`
- **Example**: `StartScale = 1.0`

#### `TargetScaleMin` *(v1.04)*
- **Type**: `Real`
- **Description**: Minimum final size scale of the EMP visual effect. Higher values maintain larger EMP fields at the end. Lower values cause more dramatic shrinking
- **Default**: `1.0`
- **Example**: `TargetScaleMin = 0.5`

#### `TargetScaleMax` *(v1.04)*
- **Type**: `Real`
- **Description**: Maximum final size scale of the EMP visual effect. Higher values allow larger final EMP fields. Lower values limit maximum expansion
- **Default**: `1.0`
- **Example**: `TargetScaleMax = 2.0`

#### `DisabledDuration` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Duration that affected objects remain disabled by EMP. Higher values disable targets longer. At 0, objects are not disabled but may still take EMP damage
- **Default**: `0`
- **Example**: `DisabledDuration = 7000`

#### `StartColor` *(v1.04)*
- **Type**: `RGBColor`
- **Description**: Initial color of the EMP visual effect. Controls the starting appearance of the EMP field
- **Default**: `0xffffffff` (white)
- **Example**: `StartColor = 0x00ff00ff` (green)

#### `EndColor` *(v1.04)*
- **Type**: `RGBColor`
- **Description**: Final color of the EMP visual effect as it fades. Controls the ending appearance of the EMP field
- **Default**: `0x00000000` (transparent)
- **Example**: `EndColor = 0x00000000`

#### `DisableFXParticleSystem` *(v1.04)*
- **Type**: `ParticleSystemTemplate`
- **Description**: Particle system played when objects are disabled by EMP. When set, displays visual effects on disabled targets. When empty, no disable effects are shown
- **Default**: `NULL`
- **Example**: `DisableFXParticleSystem = PS_EMPDisable`

#### `SparksPerCubicFoot` *(v1.04)*
- **Type**: `Real`
- **Description**: Density of spark effects within the EMP field. Higher values create more spark effects. Lower values reduce visual spark density
- **Default**: `0.001`
- **Example**: `SparksPerCubicFoot = 0.005`

### Effect Properties

#### `EffectRadius` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Radius of the EMP effect area. Higher values affect objects farther away. Lower values create more focused EMP effects
- **Default**: `200.0`
- **Example**: `EffectRadius = 300.0`

#### `DoesNotAffect` *(v1.04)*
- **Type**: `WeaponAffectsMaskType` (bit flags)
- **Description**: Object categories that are immune to EMP effects. When set, objects matching these categories are not affected by EMP. When 0, all qualifying objects can be affected
- **Default**: `0` (affects all)
- **Example**: `DoesNotAffect = ALLIES`

#### `DoesNotAffectMyOwnBuildings` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether EMP affects the owner's own buildings. When true, the EMP does not affect buildings owned by the same player. When false (default), all qualifying buildings can be affected
- **Default**: `No`
- **Example**: `DoesNotAffectMyOwnBuildings = Yes`

### Target Filtering

#### `VictimRequiredKindOf` *(v1.04)*
- **Type**: `KindOfMaskType` (bit flags)
- **Description**: Object types that must be present for EMP to affect them. When set, only objects with matching types can be affected. When 0, all object types can be affected
- **Default**: `0` (all types)
- **Example**: `VictimRequiredKindOf = VEHICLE STRUCTURE`

#### `VictimForbiddenKindOf` *(v1.04)*
- **Type**: `KindOfMaskType` (bit flags)
- **Description**: Object types that cannot be affected by EMP. When set, objects with matching types are immune to EMP effects. When 0, no object types are forbidden
- **Default**: `0` (no restrictions)
- **Example**: `VictimForbiddenKindOf = INFANTRY`

## Examples

### Basic EMP Effect
```ini
Behavior = EMPUpdate ModuleTag_03
  Lifetime = 1500
  EffectRadius = 200.0
  DisabledDuration = 0
  StartFadeTime = 750
End
```

### EMP with Disable Effect
```ini
Behavior = EMPUpdate ModuleTag_02
  Lifetime = 750
  EffectRadius = 150.0
  DisabledDuration = 7000
  StartFadeTime = 400
  DisableFXParticleSystem = PS_EMPDisable
End
```

### Large EMP Field
```ini
Behavior = EMPUpdate ModuleTag_01
  Lifetime = 3000
  EffectRadius = 400.0
  DisabledDuration = 5000
  StartFadeTime = 1500
  StartScale = 2.0
  TargetScaleMax = 3.0
  SparksPerCubicFoot = 0.01
End
```

## Template

```ini
Behavior = EMPUpdate ModuleTag_XX
  ; Timing Properties
  Lifetime = 1500                    ; // total duration in milliseconds *(v1.04)*
  StartFadeTime = 750                ; // when fading begins in milliseconds *(v1.04)*
  DisabledDuration = 7000            ; // how long targets stay disabled *(v1.04)*
  
  ; Visual Properties
  StartScale = 1.0                   ; // initial visual scale *(v1.04)*
  TargetScaleMin = 0.5               ; // minimum final scale *(v1.04)*
  TargetScaleMax = 2.0               ; // maximum final scale *(v1.04)*
  StartColor = 0xffffffff            ; // initial color *(v1.04)*
  EndColor = 0x00000000              ; // final color *(v1.04)*
  SparksPerCubicFoot = 0.001         ; // spark effect density *(v1.04)*
  
  ; Effect Properties
  EffectRadius = 200.0               ; // EMP effect radius *(v1.04)*
  DisableFXParticleSystem =          ; // disable effect particle system *(v1.04)*
  DoesNotAffect =                    ; // immune object categories *(v1.04)*
  DoesNotAffectMyOwnBuildings = No   ; // affect own buildings *(v1.04)*
  VictimRequiredKindOf =             ; // required object types *(v1.04)*
  VictimForbiddenKindOf =            ; // forbidden object types *(v1.04)*
End
```

## Notes

- EMPUpdate creates expanding EMP fields that affect nearby objects within the specified radius
- The update can disable objects for a specified duration or apply EMP damage without disabling
- Visual effects include scaling transitions and color fading over the EMP lifetime
- Object targeting can be filtered by KindOf requirements and exclusion masks
- EMP effects can be configured to avoid affecting the owner's own buildings
- The update integrates with the particle system for visual feedback on disabled objects

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/EMPUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/EMPUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/EMPUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/EMPUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet
