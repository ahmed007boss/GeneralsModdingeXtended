# TransitionDamageFX

Damage module that provides visual effects for damage transitions and damage state changes with particle systems and FX lists.

## Overview

TransitionDamageFX is a damage module that provides visual effects for damage transitions and damage state changes. It manages particle systems and FX lists that are triggered when objects transition between different damage states (pristine, damaged, really damaged, rubble). The module provides visual feedback for damage progression and creates immersive damage effects.

TransitionDamageFX must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that need visual effects when transitioning between different damage states. This is a **damage module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Requires valid particle system and FX list templates for visual effects
- Cannot function without proper damage and visual systems
- Visual effects are limited to damage state transitions
- Requires proper particle system and FX integration

**Conditions**:
- Multiple instances behavior: Multiple TransitionDamageFX modules can exist independently, each managing different visual effects
- Always active once assigned to an object
- Triggers during damage state transitions
- Creates visual feedback for damage progression

**Dependencies**:
- Depends on the damage system for state transition detection
- Requires proper particle system and FX templates for visual effects
- Inherits all functionality from DamageModule

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Visual Effects](#visual-effects)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

### Visual Effects

#### `ReallyDamagedParticleSystem1` *(v1.04)*
- **Type**: `ParticleSystemTemplate` (see [ParticleSystem documentation](../../ParticleSystem.md))
- **Description**: Particle system played when object transitions to really damaged state. When set, displays visual effects during damage state transitions. When empty (default), no particle effects are shown
- **Default**: `""` (empty)
- **Example**: `ReallyDamagedParticleSystem1 = Bone:Smoke RandomBone:Yes PSys:SmallLightSmokeColumn`

#### `ReallyDamagedFXList1` *(v1.04)*
- **Type**: `FXList` (see [FXList documentation](../../FXList.md))
- **Description**: FX list played when object transitions to really damaged state. When set, displays visual effects during damage state transitions. When empty (default), no FX effects are shown
- **Default**: `""` (empty)
- **Example**: `ReallyDamagedFXList1 = Loc: X:0 Y:0 Z:0 FXList:FX_CrusaderDamageTransition`

## Examples

### Basic Transition Damage FX
```ini
Behavior = TransitionDamageFX ModuleTag_08
  ReallyDamagedParticleSystem1 = Bone:Smoke RandomBone:Yes PSys:SmallLightSmokeColumn
  ReallyDamagedFXList1 = Loc: X:0 Y:0 Z:0 FXList:FX_CrusaderDamageTransition
End
```

### Enhanced Transition Damage FX
```ini
Behavior = TransitionDamageFX ModuleTag_16
  ReallyDamagedParticleSystem1 = Bone:Smoke RandomBone:Yes PSys:SmallLightSmokeColumn
  ReallyDamagedFXList1 = Loc: X:0 Y:0 Z:0 FXList:FX_CrusaderDamageTransition
End
```

### Commented Transition Damage FX
```ini
; Behavior = TransitionDamageFX ModuleTag_Death02
;   ReallyDamagedParticleSystem1 = Bone:Smoke RandomBone:Yes PSys:SmallLightSmokeColumn
;   ReallyDamagedFXList1 = Loc: X:0 Y:0 Z:0 FXList:FX_CrusaderDamageTransition
```

## Template

```ini
Behavior = TransitionDamageFX ModuleTag_XX
  ; Visual Effects
  ReallyDamagedParticleSystem1 =      ; // particle system for really damaged state *(v1.04)*
  ReallyDamagedFXList1 =              ; // FX list for really damaged state *(v1.04)*
End
```

## Notes

- TransitionDamageFX provides visual feedback for damage state transitions
- The module handles particle systems and FX lists during damage progression
- Visual effects enhance immersion during damage state changes
- This creates realistic damage progression with proper visual feedback

## Source Files

**Base Class:** [`DamageModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DamageModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DamageModule.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DamageModule.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Damage/TransitionDamageFX.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Damage/TransitionDamageFX.cpp)
