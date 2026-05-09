# BattleBusSlowDeathBehavior

Specialized slow death behavior for Battle Bus units that creates dramatic "fake death" sequences where the bus is thrown into the air before landing and becoming disabled.

## Overview

BattleBusSlowDeathBehavior is a specialized slow death behavior module designed for Battle Bus units. It creates a dramatic two-stage death sequence where the bus first performs a "fake death" - being thrown into the air with physics effects - before the actual destruction occurs. This creates cinematic death sequences that enhance the visual impact of destroying these large vehicles.

BattleBusSlowDeathBehavior must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by Battle Bus units that should have dramatic two-stage death sequences with physics-based throwing effects and passenger damage. This is a **slow death behavior module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Designed specifically for Battle Bus units
- Requires proper physics system for throwing effects
- Cannot function without proper death and update systems
- Requires proper FX and OCL templates for visual effects

**Conditions**:
- Multiple instances behavior: Multiple BattleBusSlowDeathBehavior modules can exist independently, each creating different death sequences
- Always active once assigned to an object
- Triggers during death events and manages two-stage death sequences
- Creates dramatic cinematic death effects with physics and visual feedback

**Dependencies**:
- Depends on the death system for triggering fake death sequences
- Requires physics system for throwing and landing effects
- Inherits all functionality from SlowDeathBehavior

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Fake Death Effects](#fake-death-effects)
  - [Physics Configuration](#physics-configuration)
  - [Passenger Damage](#passenger-damage)
  - [Hulk Management](#hulk-management)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

### Fake Death Effects

#### `FXStartUndeath` *(v1.04)*
- **Type**: `FXList` (see [FXList documentation](../FXList.md))
- **Description**: FX list executed when the fake death sequence begins. When set, displays visual effects during the throwing phase. When empty (default), no start effects are shown
- **Default**: `""` (empty)
- **Example**: `FXStartUndeath = FX_BigTruckDeathFX`

#### `OCLStartUndeath` *(v1.04)*
- **Type**: `ObjectCreationList` (see [ObjectCreationList documentation](../ObjectCreationList.md))
- **Description**: Object creation list executed when the fake death sequence begins. When set, creates objects during the throwing phase. When empty (default), no objects are created
- **Default**: `""` (empty)
- **Example**: `OCLStartUndeath = OCL_BattleBusStartUndeath`

#### `FXHitGround` *(v1.04)*
- **Type**: `FXList` (see [FXList documentation](../FXList.md))
- **Description**: FX list executed when the bus hits the ground after being thrown. When set, displays visual effects on landing. When empty (default), no landing effects are shown
- **Default**: `""` (empty)
- **Example**: `FXHitGround = FX_ArmoredVehicleHitGround`

#### `OCLHitGround` *(v1.04)*
- **Type**: `ObjectCreationList` (see [ObjectCreationList documentation](../ObjectCreationList.md))
- **Description**: Object creation list executed when the bus hits the ground after being thrown. When set, creates objects on landing. When empty (default), no objects are created
- **Default**: `""` (empty)
- **Example**: `OCLHitGround = OCL_BattleBusHitGround`

### Physics Configuration

#### `ThrowForce` *(v1.04)*
- **Type**: `Real`
- **Description**: Force applied to throw the bus into the air during fake death. Higher values create more dramatic throwing effects with greater distance and height. Lower values create gentler throwing effects
- **Default**: `1.0`
- **Example**: `ThrowForce = 2.5`

### Passenger Damage

#### `PercentDamageToPassengers` *(v1.04)*
- **Type**: `Real` (percentage)
- **Description**: Percentage of damage applied to passengers when the fake death sequence begins. Higher values cause more damage to passengers during the throwing phase. At 0 (default), passengers take no damage
- **Default**: `0.0`
- **Example**: `PercentDamageToPassengers = 50%`

### Hulk Management

#### `EmptyHulkDestructionDelay` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time delay before destroying an empty hulk after passengers have been removed. Higher values allow empty hulks to persist longer. At 0 (default), empty hulks are not automatically destroyed
- **Default**: `0`
- **Example**: `EmptyHulkDestructionDelay = 1000`

## Examples

### Basic Battle Bus Slow Death
```ini
Behavior = BattleBusSlowDeathBehavior DeathTag_01
  DeathTypes = ALL -CRUSHED -SPLATTED -EXTRA_4 -POISONED -POISONED_BETA -EXTRA_8
  ModifierBonusPerOverkillPercent = 20%
  FXStartUndeath = FX_BigTruckDeathFX
  OCLStartUndeath = OCL_BattleBusStartUndeath
  FXHitGround = FX_ArmoredVehicleHitGround
  OCLHitGround = OCL_BattleBusHitGround
  PercentDamageToPassengers = 50%
  EmptyHulkDestructionDelay = 1000
  DestructionDelay = 0
End
```

### Enhanced Battle Bus with Stronger Throw
```ini
Behavior = BattleBusSlowDeathBehavior DeathTag_02
  DeathTypes = ALL -CRUSHED -SPLATTED
  ThrowForce = 2.5
  FXStartUndeath = FX_BigTruckDeathFX
  FXHitGround = FX_ArmoredVehicleHitGround
  PercentDamageToPassengers = 75%
  EmptyHulkDestructionDelay = 2000
End
```

### Cinematic Battle Bus Death
```ini
Behavior = BattleBusSlowDeathBehavior ModuleTag_08
  DeathTypes = ALL -CRUSHED -SPLATTED -EXTRA_4 -POISONED -POISONED_BETA -EXTRA_8
  ModifierBonusPerOverkillPercent = 20%
  FXStartUndeath = FX_BigTruckDeathFX
  OCLStartUndeath = OCL_BattleBusStartUndeath
  FXHitGround = FX_ArmoredVehicleHitGround
  OCLHitGround = OCL_BattleBusHitGround
  PercentDamageToPassengers = 50%
  EmptyHulkDestructionDelay = 1000
  DestructionDelay = 0
End
```

## Template

```ini
Behavior = BattleBusSlowDeathBehavior ModuleTag_XX
  ; Inherited from SlowDeathBehavior
  DeathTypes =                          ; // death types that trigger this behavior *(v1.04)*
  ModifierBonusPerOverkillPercent =     ; // overkill damage modifier *(v1.04)*
  DestructionDelay = 0                  ; // delay before destruction *(v1.04)*
  
  ; Fake Death Effects
  FXStartUndeath =                      ; // FX list for start of fake death *(v1.04)*
  OCLStartUndeath =                     ; // OCL for start of fake death *(v1.04)*
  FXHitGround =                         ; // FX list when hitting ground *(v1.04)*
  OCLHitGround =                        ; // OCL when hitting ground *(v1.04)*
  
  ; Physics Configuration
  ThrowForce = 1.0                      ; // force applied to throw bus *(v1.04)*
  
  ; Passenger Damage
  PercentDamageToPassengers = 0.0       ; // damage percentage to passengers *(v1.04)*
  
  ; Hulk Management
  EmptyHulkDestructionDelay = 0         ; // delay before destroying empty hulk *(v1.04)*
End
```

## Notes

- BattleBusSlowDeathBehavior creates dramatic two-stage death sequences for Battle Bus units
- The fake death sequence includes physics-based throwing effects and passenger damage
- Visual effects and object creation can be triggered at multiple points during the sequence
- Empty hulks can be automatically destroyed after a configurable delay
- This behavior is specifically designed for Battle Bus units and their unique death mechanics
- Inherits all functionality from SlowDeathBehavior for standard slow death operations

## Source Files

**Base Class:** [`SlowDeathBehavior`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SlowDeathBehavior.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BattleBusSlowDeathBehavior.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BattleBusSlowDeathBehavior.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/BattleBusSlowDeathBehavior.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/BattleBusSlowDeathBehavior.cpp)
