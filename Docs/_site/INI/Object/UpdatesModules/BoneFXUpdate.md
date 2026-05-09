# BoneFXUpdate

Update module that provides bone-based visual effects functionality for objects with skeletal animations and configurable particle systems.

## Overview

BoneFXUpdate is an update module that provides bone-based visual effects functionality for objects with skeletal animations. It manages particle systems and FX lists that are attached to specific bones in animated models, creating dynamic visual effects that follow the object's skeletal structure. The module supports multiple particle systems for different damage states and bone configurations.

BoneFXUpdate must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that need bone-based visual effects, such as animated models with skeletal systems. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Requires valid particle system and FX list templates for visual effects
- Cannot function without proper update and visual systems
- Bone effects are limited to objects with skeletal animations
- Requires proper bone naming and animation system integration

**Conditions**:
- Multiple instances behavior: Multiple BoneFXUpdate modules can exist independently, each managing different bone effect systems
- Always active once assigned to an object
- Continuously manages bone-based visual effects and particle systems
- Creates dynamic visual effects that follow skeletal animations

**Dependencies**:
- Depends on the animation system for bone tracking
- Requires proper particle system and FX templates for visual effects
- Inherits all functionality from UpdateModule

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Particle Systems](#particle-systems)
  - [FX Lists](#fx-lists)
  - [Damage Types](#damage-types)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

### Particle Systems

#### `PristineParticleSystem1` *(v1.04)*
- **Type**: `ParticleSystemTemplate` (see [ParticleSystem documentation](../../ParticleSystem.md))
- **Description**: Primary particle system attached to specified bone when object is in pristine condition. When set, displays particle effects on the specified bone. When empty (default), no pristine particle effects are shown
- **Default**: `""` (empty)
- **Example**: `PristineParticleSystem1 = bone:ENGINE01 OnlyOnce:Yes 1600 1800 PSys:UnderWaterShipSplash`

#### `PristineParticleSystem2` *(v1.04)*
- **Type**: `ParticleSystemTemplate` (see [ParticleSystem documentation](../../ParticleSystem.md))
- **Description**: Secondary particle system attached to specified bone when object is in pristine condition. When set, displays additional particle effects on the specified bone. When empty (default), no secondary pristine particle effects are shown
- **Default**: `""` (empty)
- **Example**: `PristineParticleSystem2 = bone:ENGINE01 OnlyOnce:No 1800 1800 PSys:BigTorpedoExhaust`

### FX Lists

#### `RubbleFXList1` *(v1.04)*
- **Type**: `FXList` (see [FXList documentation](../../FXList.md))
- **Description**: FX list played when object transitions to rubble state. When set, displays visual effects during rubble transitions. When empty (default), no rubble effects are shown
- **Default**: `""` (empty)
- **Example**: `RubbleFXList1 = bone:Smoke02 OnlyOnce:Yes 3000 3000 FXList:FX_DefaultStructureSecondary`

### Damage Types

#### `DamageFXTypes` *(v1.04)*
- **Type**: `DamageType` (see [DamageType documentation](../../DamageType.md))
- **Description**: Damage types that trigger bone-based FX effects. When set, FX effects are triggered by specified damage types. When empty (default), all damage types trigger effects
- **Default**: `ALL`
- **Example**: `DamageFXTypes = ALL -WATER`

#### `DamageParticleTypes` *(v1.04)*
- **Type**: `DamageType` (see [DamageType documentation](../../DamageType.md))
- **Description**: Damage types that trigger bone-based particle effects. When set, particle effects are triggered by specified damage types. When empty (default), all damage types trigger particle effects
- **Default**: `ALL`
- **Example**: `DamageParticleTypes = ALL -WATER`

## Examples

### Basic Bone FX Update
```ini
Behavior = BoneFXUpdate ModuleTag_09c
  PristineParticleSystem1 = bone:ENGINE01 OnlyOnce:Yes 1600 1800 PSys:UnderWaterShipSplash
  PristineParticleSystem2 = bone:ENGINE01 OnlyOnce:No 1800 1800 PSys:BigTorpedoExhaust
End
```

### Engine Flame Bone FX Update
```ini
Behavior = BoneFXUpdate ModuleTag_09b
  PristineParticleSystem1 = bone:ENGINE01 OnlyOnce:Yes 0 0 PSys:BastionEngineFlameLeftCase
  PristineParticleSystem2 = bone:ENGINE01 OnlyOnce:Yes 0 0 PSys:BastionEngineFlameRightCase
End
```

### Damage-Based Bone FX Update
```ini
Behavior = BoneFXUpdate ModuleTag_05
  DamageFXTypes = ALL -WATER
  RubbleFXList1 = bone:Smoke02 OnlyOnce:Yes 3000 3000 FXList:FX_DefaultStructureSecondary
  DamageParticleTypes = ALL -WATER
  RubbleParticleSystem1 = bone:Fire02 OnlyOnce:Yes 3000 3000 PSys:StructureToppleSmokeTrail
End
```

## Template

```ini
Behavior = BoneFXUpdate ModuleTag_XX
  ; Particle Systems
  PristineParticleSystem1 =                    ; // primary pristine particle system *(v1.04)*
  PristineParticleSystem2 =                    ; // secondary pristine particle system *(v1.04)*
  
  ; FX Lists
  RubbleFXList1 =                              ; // FX list for rubble state *(v1.04)*
  
  ; Damage Types
  DamageFXTypes = ALL                          ; // damage types that trigger FX *(v1.04)*
  DamageParticleTypes = ALL                    ; // damage types that trigger particles *(v1.04)*
End
```

## Notes

- BoneFXUpdate provides dynamic visual effects that follow skeletal animations
- The module manages particle systems and FX lists attached to specific bones
- Bone-based effects create realistic visual feedback for animated objects
- This creates immersive visual effects that enhance the realism of skeletal animations

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdate.cpp)
