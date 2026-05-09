# SlowDeathBehavior

SlowDeathBehavior provides extended death sequences for objects with multiple phases, animations, and special effects.

## Overview

The `SlowDeathBehavior` class manages complex death sequences that occur over time with multiple phases (initial, midpoint, final). It handles sinking into terrain, flinging objects through the air, visual effects, object creation, and weapon firing during different death phases. The behavior is commonly used for vehicles, structures, and units that need elaborate destruction animations.

## Usage

Used by objects that need elaborate death sequences with multiple phases, animations, and special effects. This is a **behavior module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Effects only trigger when the object dies or is destroyed
- Death sequences are affected by game LOD (Level of Detail) settings for performance optimization
- Objects with physics can be flung and will bounce and collide during death sequences
- Infantry objects automatically disable shadows when sinking to prevent visual artifacts

**Conditions**:
- Death sequences are conditional based on death type, veterancy level, and upgrade state
- Multiple SlowDeathBehavior instances can exist on the same object with different probability modifiers
- **Multiple instances behavior**: Each instance operates independently with its own probability calculation; effects combine if multiple instances trigger simultaneously
- Death sequences can create objects, fire weapons, and play visual effects at different phases
- The behavior integrates with the death system for conditional activation based on death types

**Dependencies**:
- Requires proper FXList, ObjectCreationList, and Weapon definitions to function correctly

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Death Timing Settings](#death-timing-settings)
  - [Probability Settings](#probability-settings)
  - [Sinking Settings](#sinking-settings)
  - [Destruction Settings](#destruction-settings)
  - [Flinging Settings](#flinging-settings)
  - [Phase Effects](#phase-effects)
  - [Death Conditions](#death-conditions)
- [Enum Value Lists](#enum-value-lists)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

### Death Timing Settings

#### `SinkDelay` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time delay before the object starts sinking into the terrain
- **Example**: `SinkDelay = 2000`

#### `SinkDelayVariance` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Random variance added to SinkDelay for variation
- **Example**: `SinkDelayVariance = 500`

#### `DestructionDelay` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time delay before the object is completely destroyed
- **Example**: `DestructionDelay = 8000`

#### `DestructionDelayVariance` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Random variance added to DestructionDelay for variation
- **Example**: `DestructionDelayVariance = 1000`

### Probability Settings

#### `ProbabilityModifier` *(v1.04)*
- **Type**: `Int`
- **Description**: Base probability modifier for this death behavior when multiple exist
- **Example**: `ProbabilityModifier = 10`

#### `ModifierBonusPerOverkillPercent` *(v1.04)*
- **Type**: `Real` (percentage)
- **Description**: Additional probability bonus per percentage of overkill damage
- **Example**: `ModifierBonusPerOverkillPercent = 5.0`

### Sinking Settings

#### `SinkRate` *(v1.04)*
- **Type**: `Real` (velocity)
- **Description**: Rate at which the object sinks into the terrain (units per frame)
- **Example**: `SinkRate = 0.5`

### Destruction Settings

#### `DestructionAltitude` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Altitude below which the object is considered destroyed
- **Example**: `DestructionAltitude = -10.0`

### Flinging Settings

#### `FlingForce` *(v1.04)*
- **Type**: `Real` (force)
- **Description**: Base force applied to fling the object through the air
- **Example**: `FlingForce = 15.0`

#### `FlingForceVariance` *(v1.04)*
- **Type**: `Real` (force)
- **Description**: Random variance added to FlingForce for variation
- **Example**: `FlingForceVariance = 5.0`

#### `FlingPitch` *(v1.04)*
- **Type**: `Real` (angle)
- **Description**: Base pitch angle for flinging the object
- **Example**: `FlingPitch = 45.0`

#### `FlingPitchVariance` *(v1.04)*
- **Type**: `Real` (angle)
- **Description**: Random variance added to FlingPitch for variation
- **Example**: `FlingPitchVariance = 15.0`

### Phase Effects

#### `FX` *(v1.04)*
- **Type**: `FXList` (multiple entries per phase)
- **Description**: Visual effects played during specific death phases (see [SlowDeathPhase Values](#slowdeathphase-values) section)
- **Example**: 
```ini
FX = INITIAL FX_BigTruckDeathFX
FX = FINAL FX_BuggyNewDeathExplosion
```

#### `OCL` *(v1.04)*
- **Type**: `ObjectCreationList` (multiple entries per phase)
- **Description**: Objects created during specific death phases (see [SlowDeathPhase Values](#slowdeathphase-values) section)
- **Example**: 
```ini
OCL = INITIAL OCL_ExplosionDebris
OCL = FINAL OCL_RadarVanDeathEffect
```

#### `Weapon` *(v1.04)*
- **Type**: `Weapon` (multiple entries per phase)
- **Description**: Weapons fired during specific death phases (see [SlowDeathPhase Values](#slowdeathphase-values) section)
- **Example**: 
```ini
Weapon = INITIAL Weapon_DeathExplosion
Weapon = FINAL Weapon_FinalBlast
```

### Death Conditions

#### `DeathTypes` *(v1.04)*
- **Type**: `DeathTypeFlags` (bit flags) (see [DeathType Values](#deathtype-values) section)
- **Description**: Death types that trigger this slow death behavior
- **Example**: `DeathTypes = ALL -CRUSHED -SPLATTED -POISONED`

#### `VeterancyLevels` *(v1.04)*
- **Type**: `VeterancyLevelFlags` (bit flags)
- **Description**: Veterancy levels that trigger this slow death behavior
- **Example**: `VeterancyLevels = VETERAN +ELITE`

#### `ExemptStatus` *(v1.04)*
- **Type**: `ObjectStatusMaskType` (bit flags)
- **Description**: Object status bits that prevent this slow death behavior from triggering
- **Example**: `ExemptStatus = OBJECT_STATUS_SOLD`

#### `RequiredStatus` *(v1.04)*
- **Type**: `ObjectStatusMaskType` (bit flags)
- **Description**: Object status bits that must be set for this slow death behavior to trigger
- **Example**: `RequiredStatus = OBJECT_STATUS_UNDER_CONSTRUCTION`

## Enum Value Lists

#### `SlowDeathPhase` Values *(v1.04)*
**Source:** [SlowDeathBehavior.h](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SlowDeathBehavior.h#51) - `SlowDeathPhaseType` enum definition

- **`INITIAL`** *(v1.04)* - Initial death phase (begins immediately when death starts)
- **`MIDPOINT`** *(v1.04)* - Midpoint death phase (occurs between 35% and 65% of death duration)
- **`FINAL`** *(v1.04)* - Final death phase (occurs at the end before destruction)

#### `DeathType` Values *(v1.04)*
**Source:** [Damage.h](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h#187) - `DeathType` enum definition

- **`DEATH_NORMAL`** *(v1.04)* - Normal death
- **`DEATH_NONE`** *(v1.04)* - No death (special case)
- **`DEATH_CRUSHED`** *(v1.04)* - Crushed death
- **`DEATH_BURNED`** *(v1.04)* - Burned death
- **`DEATH_EXPLODED`** *(v1.04)* - Exploded death
- **`DEATH_POISONED`** *(v1.04)* - Poisoned death
- **`DEATH_SUICIDED`** *(v1.04)* - Suicide death
- **`DEATH_RUBBLE`** *(v1.04)* - Rubble death
- **`DEATH_FADED`** *(v1.04)* - Faded death
- **`DEATH_KNOCKBACK`** *(v1.04)* - Knockback death
- **`DEATH_LAVA`** *(v1.04)* - Lava death
- **`DEATH_DETONATED`** *(v1.04)* - Detonated death
- **`DEATH_EXTRA_1`** *(v1.04)* - Extra death type 1
- **`DEATH_EXTRA_2`** *(v1.04)* - Extra death type 2
- **`DEATH_EXTRA_3`** *(v1.04)* - Extra death type 3
- **`DEATH_EXTRA_4`** *(v1.04)* - Extra death type 4
- **`DEATH_EXTRA_5`** *(v1.04)* - Extra death type 5

## Examples

### Scout Van Slow Death with Sinking
```ini
Behavior = SlowDeathBehavior DeathTag_01
  DeathTypes = ALL -CRUSHED -SPLATTED -POISONED -POISONED_BETA -EXTRA_8
  SinkRate = 0.5
  SinkDelay = 2000
  SinkDelayVariance = 500
  DestructionDelay = 8000
  DestructionDelayVariance = 1000
  DestructionAltitude = -10.0
  ProbabilityModifier = 10
  FX = INITIAL FX_BigTruckDeathFX
  FX = FINAL FX_BuggyNewDeathExplosion
  OCL = FINAL OCL_RadarVanDeathEffect
End
```

### Vehicle with Flinging Death
```ini
Behavior = SlowDeathBehavior DeathTag_Fling
  DeathTypes = ALL -CRUSHED -SPLATTED
  FlingForce = 15.0
  FlingForceVariance = 5.0
  FlingPitch = 45.0
  FlingPitchVariance = 15.0
  DestructionDelay = 5000
  FX = INITIAL FX_VehicleExplosion
  FX = MIDPOINT FX_VehicleSmoke
  FX = FINAL FX_VehicleFinalBlast
  Weapon = FINAL Weapon_DeathExplosion
End
```

### High Probability Death for Overkill
```ini
Behavior = SlowDeathBehavior DeathTag_Spectacular
  DeathTypes = ALL -CRUSHED -SPLATTED
  ProbabilityModifier = 5
  ModifierBonusPerOverkillPercent = 10.0
  DestructionDelay = 12000
  DestructionDelayVariance = 2000
  FX = INITIAL FX_SpectacularExplosion
  FX = MIDPOINT FX_FireAndSmoke
  FX = FINAL FX_FinalBlast
  OCL = FINAL OCL_ExplosionDebris
End
```

### Infantry Sinking Death
```ini
Behavior = SlowDeathBehavior DeathTag_Infantry
  DeathTypes = ALL -CRUSHED -SPLATTED
  SinkRate = 0.3
  SinkDelay = 1000
  DestructionDelay = 4000
  DestructionAltitude = -5.0
  FX = INITIAL FX_InfantryDeath
  OCL = FINAL OCL_InfantryCorpse
End
```

## Template

```ini
Behavior = SlowDeathBehavior ModuleTag_XX
  ; Death Timing Settings
  SinkDelay = 2000                   ; // milliseconds before sinking starts *(v1.04)*
  SinkDelayVariance = 500            ; // random variance for sink delay *(v1.04)*
  DestructionDelay = 8000            ; // milliseconds before destruction *(v1.04)*
  DestructionDelayVariance = 1000    ; // random variance for destruction delay *(v1.04)*

  ; Probability Settings
  ProbabilityModifier = 10           ; // base probability modifier *(v1.04)*
  ModifierBonusPerOverkillPercent = 0.0 ; // bonus per overkill percentage *(v1.04)*

  ; Sinking Settings
  SinkRate = 0.5                     ; // rate of sinking into terrain *(v1.04)*
  DestructionAltitude = -10.0        ; // altitude for destruction *(v1.04)*

  ; Flinging Settings
  FlingForce = 0.0                   ; // force to fling object *(v1.04)*
  FlingForceVariance = 0.0           ; // variance for fling force *(v1.04)*
  FlingPitch = 0.0                   ; // pitch angle for flinging *(v1.04)*
  FlingPitchVariance = 0.0           ; // variance for fling pitch *(v1.04)*

  ; Phase Effects
  FX = INITIAL FX_InitialEffect      ; // initial phase effect *(v1.04)*
  FX = MIDPOINT FX_MidpointEffect    ; // midpoint phase effect *(v1.04)*
  FX = FINAL FX_FinalEffect          ; // final phase effect *(v1.04)*
  OCL = INITIAL OCL_InitialObjects   ; // initial phase objects *(v1.04)*
  OCL = MIDPOINT OCL_MidpointObjects ; // midpoint phase objects *(v1.04)*
  OCL = FINAL OCL_FinalObjects       ; // final phase objects *(v1.04)*
  Weapon = INITIAL Weapon_Initial    ; // initial phase weapon *(v1.04)*
  Weapon = MIDPOINT Weapon_Midpoint  ; // midpoint phase weapon *(v1.04)*
  Weapon = FINAL Weapon_Final        ; // final phase weapon *(v1.04)*

  ; Death Conditions
  DeathTypes = ALL                   ; // death types that trigger behavior *(v1.04)*
  VeterancyLevels =                  ; // veterancy levels that trigger behavior *(v1.04)*
  ExemptStatus =                     ; // status bits that prevent triggering *(v1.04)*
  RequiredStatus =                   ; // required status bits for triggering *(v1.04)*
End
```

## Notes

- SlowDeathBehavior creates multi-phase death sequences with initial, midpoint, and final phases
- Objects can sink into terrain, be flung through the air, or follow other death patterns
- Multiple SlowDeathBehavior instances can exist on the same object with different probability modifiers
- Death sequences are affected by game LOD (Level of Detail) settings for performance optimization
- Overkill damage increases the probability of spectacular death sequences
- Objects with physics can be flung and will bounce and collide during death sequences
- Infantry objects automatically disable shadows when sinking to prevent visual artifacts
- Death sequences can create objects, fire weapons, and play visual effects at different phases
- The behavior integrates with the death system for conditional activation based on death types

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h), [`DieModuleInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h), [`SlowDeathBehaviorInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SlowDeathBehavior.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SlowDeathBehavior.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SlowDeathBehavior.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/SlowDeathBehavior.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/SlowDeathBehavior.cpp)