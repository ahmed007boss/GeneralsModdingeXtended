# NeutronMissileSlowDeathUpdate

Specialized slow death behavior module for neutron missile superweapons with multiple blast waves and scorch effects.

## Overview

NeutronMissileSlowDeathUpdate is a specialized slow death behavior module designed for neutron missile superweapons. It creates multiple blast waves with different timing, damage, and effects, including scorch marks on the terrain. The module supports up to 9 different blast waves, each with configurable delays, damage radii, and visual effects. This creates the dramatic multi-stage explosion sequence characteristic of neutron missile impacts.

NeutronMissileSlowDeathUpdate must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by neutron missile objects that should create multi-stage blast sequences with different timing, damage, and effects when they die. This is a **slow death behavior module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Limited to maximum 9 blast waves (MAX_NEUTRON_BLASTS constant)
- Requires valid blast configurations to function
- Cannot be used when the object is disabled
- Effects are limited to the configured blast parameters
- Requires proper blast wave configuration for functionality

**Conditions**:
- Multiple instances behavior: Multiple NeutronMissileSlowDeathUpdate modules can exist independently, each creating different blast sequences
- Always active once assigned to an object
- Blast waves are triggered based on configured delays
- Creates dramatic multi-stage explosion sequences with physics effects

**Dependencies**:
- Requires valid blast configurations for each wave
- Depends on the physics system for push forces and toppling
- Inherits all functionality from SlowDeathBehavior

## Properties

### Scorch Effects

#### `ScorchMarkSize` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Size of the scorch mark left on the terrain after the neutron missile impact. Higher values create larger scorch marks. When set to 0 (default), no scorch mark is created
- **Default**: `0.0`
- **Example**: `ScorchMarkSize = 150.0`

### Visual Effects

#### `FXList` *(v1.04)*
- **Type**: `FXList` (see [FXList documentation](../FXList.md))
- **Description**: Visual effects played during the neutron missile sequence. When set, displays the specified effects throughout the blast sequence. When NULL (default), no visual effects are shown
- **Default**: `NULL` (none)
- **Example**: `FXList = FX_NeutronMissileExplosion`

### Blast Wave Configuration

Each blast wave (1-9) has the following properties:

#### `BlastXEnabled` *(v1.04)*
- **Type**: `Bool`
- **Description**: Determines if blast wave X is enabled. When `Yes`, the blast wave will be triggered. When `No` (default), the blast wave is skipped
- **Default**: `No`
- **Example**: `Blast1Enabled = Yes`

#### `BlastXDelay` *(v1.04)*
- **Type**: `Real` (milliseconds)
- **Description**: Delay after death before blast wave X is triggered. Higher values delay the blast wave longer. When set to 0 (default), the blast wave triggers immediately
- **Default**: `0.0`
- **Example**: `Blast1Delay = 1000.0`

#### `BlastXScorchDelay` *(v1.04)*
- **Type**: `Real` (milliseconds)
- **Description**: Delay after death before scorch effects for blast wave X are applied. Higher values delay scorch effects longer. When set to 0 (default), scorch effects trigger immediately
- **Default**: `0.0`
- **Example**: `Blast1ScorchDelay = 2000.0`

#### `BlastXInnerRadius` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Inner radius of blast wave X where maximum damage is applied. Higher values create larger inner damage zones. When set to 0 (default), no inner radius is used
- **Default**: `0.0`
- **Example**: `Blast1InnerRadius = 50.0`

#### `BlastXOuterRadius` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Outer radius of blast wave X where minimum damage is applied. Higher values create larger blast areas. When set to 0 (default), no outer radius is used
- **Default**: `0.0`
- **Example**: `Blast1OuterRadius = 200.0`

#### `BlastXMaxDamage` *(v1.04)*
- **Type**: `Real` (damage)
- **Description**: Maximum damage applied in the inner radius of blast wave X. Higher values cause more damage. When set to 0 (default), no maximum damage is applied
- **Default**: `0.0`
- **Example**: `Blast1MaxDamage = 1000.0`

#### `BlastXMinDamage` *(v1.04)*
- **Type**: `Real` (damage)
- **Description**: Minimum damage applied in the outer radius of blast wave X. Higher values cause more damage. When set to 0 (default), no minimum damage is applied
- **Default**: `0.0`
- **Example**: `Blast1MinDamage = 100.0`

#### `BlastXToppleSpeed` *(v1.04)*
- **Type**: `Real` (speed)
- **Description**: Speed at which objects are toppled by blast wave X. Higher values topple objects faster. When set to 0 (default), no toppling occurs
- **Default**: `0.0`
- **Example**: `Blast1ToppleSpeed = 50.0`

#### `BlastXPushForce` *(v1.04)*
- **Type**: `Real` (force)
- **Description**: Magnitude of physics force applied to push objects away from blast wave X. Higher values push objects further. When set to 0 (default), no push force is applied
- **Default**: `0.0`
- **Example**: `Blast1PushForce = 1000.0`

## Examples

### Basic Neutron Missile
```ini
Update = NeutronMissileSlowDeathUpdate ModuleTag_01
  ScorchMarkSize = 200.0
  FXList = FX_NeutronMissileExplosion
  
  Blast1Enabled = Yes
  Blast1Delay = 0.0
  Blast1ScorchDelay = 1000.0
  Blast1InnerRadius = 100.0
  Blast1OuterRadius = 300.0
  Blast1MaxDamage = 2000.0
  Blast1MinDamage = 500.0
  Blast1ToppleSpeed = 75.0
  Blast1PushForce = 1500.0
End
```

### Multi-Wave Neutron Missile
```ini
Update = NeutronMissileSlowDeathUpdate ModuleTag_02
  ScorchMarkSize = 250.0
  FXList = FX_AdvancedNeutronMissile
  
  ; Primary Blast
  Blast1Enabled = Yes
  Blast1Delay = 0.0
  Blast1ScorchDelay = 500.0
  Blast1InnerRadius = 150.0
  Blast1OuterRadius = 400.0
  Blast1MaxDamage = 3000.0
  Blast1MinDamage = 800.0
  Blast1ToppleSpeed = 100.0
  Blast1PushForce = 2000.0
  
  ; Secondary Blast
  Blast2Enabled = Yes
  Blast2Delay = 2000.0
  Blast2ScorchDelay = 2500.0
  Blast2InnerRadius = 75.0
  Blast2OuterRadius = 200.0
  Blast2MaxDamage = 1500.0
  Blast2MinDamage = 400.0
  Blast2ToppleSpeed = 50.0
  Blast2PushForce = 1000.0
End
```

## Template

```ini
Update = NeutronMissileSlowDeathUpdate ModuleTag_XX
  ; Scorch Effects
  ScorchMarkSize = 0.0               ; // size of terrain scorch mark *(v1.04)*
  
  ; Visual Effects
  FXList =                           ; // neutron missile visual effects *(v1.04)*
  
  ; Blast Wave 1 Configuration
  Blast1Enabled = No                 ; // enable blast wave 1 *(v1.04)*
  Blast1Delay = 0.0                  ; // delay before blast wave 1 *(v1.04)*
  Blast1ScorchDelay = 0.0            ; // delay before scorch effects *(v1.04)*
  Blast1InnerRadius = 0.0            ; // inner damage radius *(v1.04)*
  Blast1OuterRadius = 0.0            ; // outer damage radius *(v1.04)*
  Blast1MaxDamage = 0.0              ; // maximum damage in inner radius *(v1.04)*
  Blast1MinDamage = 0.0              ; // minimum damage in outer radius *(v1.04)*
  Blast1ToppleSpeed = 0.0            ; // object toppling speed *(v1.04)*
  Blast1PushForce = 0.0              ; // physics push force magnitude *(v1.04)*
  
  ; Blast Wave 2 Configuration
  Blast2Enabled = No                 ; // enable blast wave 2 *(v1.04)*
  Blast2Delay = 0.0                  ; // delay before blast wave 2 *(v1.04)*
  Blast2ScorchDelay = 0.0            ; // delay before scorch effects *(v1.04)*
  Blast2InnerRadius = 0.0            ; // inner damage radius *(v1.04)*
  Blast2OuterRadius = 0.0            ; // outer damage radius *(v1.04)*
  Blast2MaxDamage = 0.0              ; // maximum damage in inner radius *(v1.04)*
  Blast2MinDamage = 0.0              ; // minimum damage in outer radius *(v1.04)*
  Blast2ToppleSpeed = 0.0            ; // object toppling speed *(v1.04)*
  Blast2PushForce = 0.0              ; // physics push force magnitude *(v1.04)*
  
  ; Additional blast waves 3-9 follow the same pattern...
End
```

## Notes

- NeutronMissileSlowDeathUpdate creates multi-stage blast sequences for neutron missile superweapons
- Supports up to 9 different blast waves with individual timing and damage configurations
- Each blast wave can have different inner/outer radii, damage amounts, and effects
- Includes scorch mark creation on terrain for visual impact
- Creates dramatic multi-stage explosion sequences with physics effects
- Commonly used for superweapon impacts and large-scale destruction
- The module manages blast timing, damage application, and visual effects
- Objects can be toppled and pushed by blast waves with configurable forces

## Source Files

**Base Class:** [`SlowDeathBehavior`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SlowDeathBehavior.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/NeutronMissileSlowDeathUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/NeutronMissileSlowDeathUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/NeutronMissileSlowDeathUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/NeutronMissileSlowDeathUpdate.cpp)
