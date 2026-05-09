# JetSlowDeathBehavior

Specialized slow death behavior module for aircraft with realistic crash sequences including rolling, falling, and ground impact effects.

## Overview

JetSlowDeathBehavior is a specialized slow death behavior module designed for aircraft that creates realistic crash sequences. It includes multiple phases: initial death effects, secondary effects, ground impact, and final explosion. The module simulates aircraft physics including rolling, falling, and spinning behaviors during the crash sequence.

JetSlowDeathBehavior must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by aircraft that should have realistic crash sequences with multiple phases including rolling, falling, ground impact, and final explosion. This is a **slow death behavior module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Designed specifically for aircraft with locomotor systems
- Requires valid FX lists and object creation lists for effects
- Cannot function without proper physics and locomotor integration
- Requires proper aircraft physics and movement systems

**Conditions**:
- Multiple instances behavior: Multiple JetSlowDeathBehavior modules can exist independently, each creating different crash sequences
- Always active once assigned to an object
- Triggers during death events and manages the complete crash sequence
- Creates dramatic and realistic aircraft destruction sequences

**Dependencies**:
- Requires valid FX lists and object creation lists for visual effects
- Depends on the physics system for realistic crash physics
- Inherits all functionality from SlowDeathBehavior

## Properties

### Ground Death Effects

#### `FXOnGroundDeath` *(v1.04)*
- **Type**: `FXList` (see [FXList documentation](../FXList.md))
- **Description**: Visual effects played when the aircraft is destroyed while on the ground. When set, displays the specified effects for ground-based destruction. When NULL (default), no ground death effects are shown
- **Default**: `NULL` (none)
- **Example**: `FXOnGroundDeath = FX_JetGroundExplosion`

#### `OCLOnGroundDeath` *(v1.04)*
- **Type**: `ObjectCreationList`
- **Description**: Objects created when the aircraft is destroyed while on the ground. When set, spawns the specified objects for ground-based destruction. When NULL (default), no objects are created
- **Default**: `NULL` (none)
- **Example**: `OCLOnGroundDeath = OCL_JetGroundDebris`

### Initial Death Effects

#### `FXInitialDeath` *(v1.04)*
- **Type**: `FXList` (see [FXList documentation](../FXList.md))
- **Description**: Visual effects played immediately when the aircraft begins its death sequence. When set, displays the specified effects at death initiation. When NULL (default), no initial death effects are shown
- **Default**: `NULL` (none)
- **Example**: `FXInitialDeath = FX_JetInitialDamage`

#### `OCLInitialDeath` *(v1.04)*
- **Type**: `ObjectCreationList`
- **Description**: Objects created immediately when the aircraft begins its death sequence. When set, spawns the specified objects at death initiation. When NULL (default), no objects are created
- **Default**: `NULL` (none)
- **Example**: `OCLInitialDeath = OCL_JetInitialDebris`

### Secondary Effects

#### `DelaySecondaryFromInitialDeath` *(v1.04)*
- **Type**: `UnsignedInt` (frames)
- **Description**: Delay in frames between initial death and secondary effects. Higher values delay secondary effects longer. When set to 0 (default), secondary effects trigger immediately
- **Default**: `0`
- **Example**: `DelaySecondaryFromInitialDeath = 30`

#### `FXSecondary` *(v1.04)*
- **Type**: `FXList` (see [FXList documentation](../FXList.md))
- **Description**: Visual effects played during the secondary phase of the crash sequence. When set, displays the specified effects during secondary phase. When NULL (default), no secondary effects are shown
- **Default**: `NULL` (none)
- **Example**: `FXSecondary = FX_JetSecondaryExplosion`

#### `OCLSecondary` *(v1.04)*
- **Type**: `ObjectCreationList`
- **Description**: Objects created during the secondary phase of the crash sequence. When set, spawns the specified objects during secondary phase. When NULL (default), no objects are created
- **Default**: `NULL` (none)
- **Example**: `OCLSecondary = OCL_JetSecondaryDebris`

### Ground Impact Effects

#### `FXHitGround` *(v1.04)*
- **Type**: `FXList` (see [FXList documentation](../FXList.md))
- **Description**: Visual effects played when the aircraft impacts the ground. When set, displays the specified effects on ground impact. When NULL (default), no ground impact effects are shown
- **Default**: `NULL` (none)
- **Example**: `FXHitGround = FX_JetGroundImpact`

#### `OCLHitGround` *(v1.04)*
- **Type**: `ObjectCreationList`
- **Description**: Objects created when the aircraft impacts the ground. When set, spawns the specified objects on ground impact. When NULL (default), no objects are created
- **Default**: `NULL` (none)
- **Example**: `OCLHitGround = OCL_JetImpactDebris`

### Final Explosion

#### `DelayFinalBlowUpFromHitGround` *(v1.04)*
- **Type**: `UnsignedInt` (frames)
- **Description**: Delay in frames between ground impact and final explosion. Higher values delay the final explosion longer. When set to 0 (default), final explosion triggers immediately
- **Default**: `0`
- **Example**: `DelayFinalBlowUpFromHitGround = 60`

#### `FXFinalBlowUp` *(v1.04)*
- **Type**: `FXList` (see [FXList documentation](../FXList.md))
- **Description**: Visual effects played during the final explosion phase. When set, displays the specified effects for the final explosion. When NULL (default), no final explosion effects are shown
- **Default**: `NULL` (none)
- **Example**: `FXFinalBlowUp = FX_JetFinalExplosion`

#### `OCLFinalBlowUp` *(v1.04)*
- **Type**: `ObjectCreationList`
- **Description**: Objects created during the final explosion phase. When set, spawns the specified objects for the final explosion. When NULL (default), no objects are created
- **Default**: `NULL` (none)
- **Example**: `OCLFinalBlowUp = OCL_JetFinalDebris`

### Physics Parameters

#### `RollRate` *(v1.04)*
- **Type**: `Real` (rate)
- **Description**: Initial roll rate of the aircraft during the crash sequence. Higher values make the aircraft roll faster. When set to 0 (default), no initial roll occurs
- **Default**: `0.0`
- **Example**: `RollRate = 2.5`

#### `RollRateDelta` *(v1.04)*
- **Type**: `Real` (rate change)
- **Description**: Rate of change for the roll rate over time. Higher values make the roll rate change faster. When set to 1 (default), roll rate remains constant
- **Default**: `1.0`
- **Example**: `RollRateDelta = 0.8`

#### `PitchRate` *(v1.04)*
- **Type**: `Real` (rate)
- **Description**: Pitch rotation rate of the aircraft after hitting the ground. Higher values make the aircraft pitch faster. When set to 0 (default), no pitch rotation occurs
- **Default**: `0.0`
- **Example**: `PitchRate = 1.5`

#### `FallHowFast` *(v1.04)*
- **Type**: `Real` (gravity fraction)
- **Description**: Fraction of gravity used to modify the aircraft's locomotor lift during falling. Higher values make the aircraft fall faster. When set to 0 (default), normal gravity is used
- **Default**: `0.0`
- **Example**: `FallHowFast = 0.5`

### Audio Effects

#### `DeathLoopSound` *(v1.04)*
- **Type**: `AudioEventRTS`
- **Description**: Looping audio event played during the death sequence. When set, plays the specified sound throughout the crash sequence. When empty (default), no death loop sound is played
- **Default**: `""` (empty)
- **Example**: `DeathLoopSound = Audio_DeathLoop`

## Examples

### Basic Jet Crash
```ini
Update = JetSlowDeathBehavior ModuleTag_01
  FXInitialDeath = FX_JetInitialDamage
  OCLInitialDeath = OCL_JetInitialDebris
  DelaySecondaryFromInitialDeath = 30
  FXSecondary = FX_JetSecondaryExplosion
  OCLSecondary = OCL_JetSecondaryDebris
  FXHitGround = FX_JetGroundImpact
  OCLHitGround = OCL_JetImpactDebris
  DelayFinalBlowUpFromHitGround = 60
  FXFinalBlowUp = FX_JetFinalExplosion
  OCLFinalBlowUp = OCL_JetFinalDebris
  RollRate = 2.0
  RollRateDelta = 0.9
  PitchRate = 1.0
  FallHowFast = 0.3
  DeathLoopSound = Audio_JetDeathLoop
End
```

### Simple Jet Death
```ini
Update = JetSlowDeathBehavior ModuleTag_02
  FXOnGroundDeath = FX_SimpleJetExplosion
  OCLOnGroundDeath = OCL_SimpleJetDebris
  RollRate = 1.5
  FallHowFast = 0.5
End
```

## Template

```ini
Update = JetSlowDeathBehavior ModuleTag_XX
  ; Ground Death Effects
  FXOnGroundDeath =                     ; // visual effects for ground death *(v1.04)*
  OCLOnGroundDeath =                     ; // objects created for ground death *(v1.04)*
  
  ; Initial Death Effects
  FXInitialDeath =                       ; // visual effects for initial death *(v1.04)*
  OCLInitialDeath =                      ; // objects created for initial death *(v1.04)*
  
  ; Secondary Effects
  DelaySecondaryFromInitialDeath = 0     ; // delay before secondary effects *(v1.04)*
  FXSecondary =                          ; // visual effects for secondary phase *(v1.04)*
  OCLSecondary =                         ; // objects created for secondary phase *(v1.04)*
  
  ; Ground Impact Effects
  FXHitGround =                          ; // visual effects for ground impact *(v1.04)*
  OCLHitGround =                         ; // objects created for ground impact *(v1.04)*
  
  ; Final Explosion
  DelayFinalBlowUpFromHitGround = 0      ; // delay before final explosion *(v1.04)*
  FXFinalBlowUp =                        ; // visual effects for final explosion *(v1.04)*
  OCLFinalBlowUp =                       ; // objects created for final explosion *(v1.04)*
  
  ; Physics Parameters
  RollRate = 0.0                         ; // initial roll rate *(v1.04)*
  RollRateDelta = 1.0                    ; // roll rate change over time *(v1.04)*
  PitchRate = 0.0                        ; // pitch rotation rate after ground impact *(v1.04)*
  FallHowFast = 0.0                      ; // gravity fraction for falling *(v1.04)*
  
  ; Audio Effects
  DeathLoopSound =                       ; // looping death sound *(v1.04)*
End
```

## Notes

- JetSlowDeathBehavior creates realistic aircraft crash sequences with multiple phases
- Includes physics simulation for rolling, falling, and ground impact
- Supports multiple visual and audio effects throughout the crash sequence
- Commonly used for aircraft, jets, and other flying vehicles
- The module manages the complete crash sequence from initial damage to final explosion
- Creates dramatic and realistic aircraft destruction sequences

## Source Files

**Base Class:** [`SlowDeathBehavior`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SlowDeathBehavior.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/JetSlowDeathBehavior.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/JetSlowDeathBehavior.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/JetSlowDeathBehavior.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/JetSlowDeathBehavior.cpp)