# SpawnBehavior

SpawnBehavior provides spawning functionality for objects that can create or spawn other objects.

## Overview

The `SpawnBehavior` class manages the creation, maintenance, and replacement of spawned objects. It can create multiple spawns, replace them when they die, and control their behavior. The spawner can maintain a specific number of active spawns and automatically replace lost ones. The behavior is commonly used for defensive structures that spawn garrison units, spawn points that create reinforcements, and special generators that produce supporting units.

## Usage

Used by objects that can spawn other units or objects, such as spawn points, production buildings, or special spawn generators. This is a **behavior module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Spawned objects inherit the spawner's team and player
- Spawn replacement is limited by SpawnReplaceDelay timing
- Maximum spawn count is limited by SpawnNumber setting
- The behavior supports both continuous spawning and one-shot spawning modes
- Spawned objects are created with the same team and player as the spawner

**Conditions**:
- SpawnBehavior can maintain a specific number of active spawns and automatically replace lost ones
- Multiple spawn templates can be specified for variety in spawned units
- Spawned units can be controlled as a group through the SpawnBehaviorInterface
- The spawner can propagate damage to its spawns based on damage type flags
- Aggregate health allows the spawner to represent the combined health of all its spawns
- Spawns can be configured to require the spawner's existence or operate independently
- The behavior integrates with the death system for conditional spawning based on death types
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own spawn settings and timing

**Dependencies**:
- Requires valid SpawnTemplateName definitions to function

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Spawn Configuration](#spawn-configuration)
  - [Spawn Control](#spawn-control)
  - [Spawn Behavior](#spawn-behavior)
  - [Damage Propagation](#damage-propagation)
  - [Death Conditions](#death-conditions)
- [Enum Value Lists](#enum-value-lists)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

### Spawn Configuration

#### `SpawnNumber` *(v1.04)*
- **Type**: `Int`
- **Description**: Maximum number of spawns to maintain at any time
- **Example**: `SpawnNumber = 3`

#### `SpawnTemplateName` *(v1.04)*
- **Type**: `AsciiString` (can be specified multiple times)
- **Description**: Template name of the object to spawn
- **Example**: `SpawnTemplateName = GLAInfantryDushkaGunner`

#### `SpawnReplaceDelay` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time delay before replacing a lost spawn
- **Example**: `SpawnReplaceDelay = 40000`

#### `InitialBurst` *(v1.04)*
- **Type**: `Int`
- **Description**: Number of spawns to create immediately when the behavior starts
- **Example**: `InitialBurst = 2`

### Spawn Control

#### `OneShot` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether to spawn only once and then become dormant
- **Example**: `OneShot = Yes`

#### `CanReclaimOrphans` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether to reclaim existing orphaned spawn objects instead of creating new ones
- **Example**: `CanReclaimOrphans = No`

#### `ExitByBudding` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether to create each new spawn atop an existing one
- **Example**: `ExitByBudding = Yes`

### Spawn Behavior

#### `SpawnedRequireSpawner` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether spawned objects can only exist while the spawner is alive
- **Example**: `SpawnedRequireSpawner = Yes`

#### `SlavesHaveFreeWill` *(v1.04, Generals Zero Hour only)*
- **Type**: `Bool`
- **Description**: Whether spawned units can act independently and don't attack when parent attacks
- **Example**: `SlavesHaveFreeWill = No`

#### `AggregateHealth` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether to calculate an offset for the health box, averaging all spawn health
- **Example**: `AggregateHealth = Yes`

### Damage Propagation

#### `PropagateDamageTypesToSlavesWhenExisting` *(v1.04)*
- **Type**: `DamageTypeFlags` (bit flags) (see [DamageType Values](#damagetype-values) section)
- **Description**: Damage types to propagate to existing spawned units
- **Example**: `PropagateDamageTypesToSlavesWhenExisting = NONE +FLAME +EXPLOSIVE`

### Death Conditions

#### `DeathTypes` *(v1.04)*
- **Type**: `DeathTypeFlags` (bit flags) (see [DeathType Values](#deathtype-values) section)
- **Description**: Death types that trigger spawn behavior
- **Example**: `DeathTypes = NONE +EXPLODED +BURNED`

#### `VeterancyLevels` *(v1.04)*
- **Type**: `VeterancyLevelFlags` (bit flags)
- **Description**: Veterancy levels that trigger spawn behavior
- **Example**: `VeterancyLevels = VETERAN +ELITE`

#### `ExemptStatus` *(v1.04)*
- **Type**: `ObjectStatusMaskType` (bit flags)
- **Description**: Object status bits that prevent spawn behavior from triggering
- **Example**: `ExemptStatus = OBJECT_STATUS_SOLD`

#### `RequiredStatus` *(v1.04)*
- **Type**: `ObjectStatusMaskType` (bit flags)
- **Description**: Object status bits that must be set for spawn behavior to trigger
- **Example**: `RequiredStatus = OBJECT_STATUS_UNDER_CONSTRUCTION`

## Enum Value Lists

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

#### `DamageType` Values *(v1.04)*
**Source:** [Damage.h](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h#155) - `DamageType` enum definition

- **`DAMAGE_NONE`** *(v1.04)* - No damage
- **`DAMAGE_EXPLOSIVE`** *(v1.04)* - Explosive damage
- **`DAMAGE_FLAME`** *(v1.04)* - Flame damage
- **`DAMAGE_BULLET`** *(v1.04)* - Bullet damage
- **`DAMAGE_KNIFE`** *(v1.04)* - Knife damage
- **`DAMAGE_LASER`** *(v1.04)* - Laser damage
- **`DAMAGE_POISON`** *(v1.04)* - Poison damage
- **`DAMAGE_CRUSH`** *(v1.04)* - Crush damage
- **`DAMAGE_HEALING`** *(v1.04)* - Healing damage
- **`DAMAGE_UNRESISTABLE`** *(v1.04)* - Unresistable damage
- **`DAMAGE_EMP`** *(v1.04)* - EMP damage
- **`DAMAGE_DEPLOY`** *(v1.04)* - Deploy damage
- **`DAMAGE_PARTICLE_BEAM`** *(v1.04)* - Particle beam damage
- **`DAMAGE_EXTRA_1`** *(v1.04)* - Extra damage type 1
- **`DAMAGE_EXTRA_2`** *(v1.04)* - Extra damage type 2
- **`DAMAGE_EXTRA_3`** *(v1.04)* - Extra damage type 3
- **`DAMAGE_EXTRA_4`** *(v1.04)* - Extra damage type 4
- **`DAMAGE_EXTRA_5`** *(v1.04)* - Extra damage type 5

## Examples

### Dushka Nest Spawn Behavior
```ini
Behavior = SpawnBehavior ModuleTag_06
  SpawnNumber = 1
  SpawnReplaceDelay = 40000
  SpawnTemplateName = GLAInfantryDushkaGunner
  CanReclaimOrphans = No
End
```

### AT Site Spawn Behavior
```ini
Behavior = SpawnBehavior ModuleTag_Defender01
  SpawnNumber = 3
  SpawnReplaceDelay = 30000
  SpawnTemplateName = GLAInfantryATSiteDefender
  SpawnTemplateName = GLAInfantryATSiteDefender
  SpawnTemplateName = GLAInfantryATSiteDefender
  CanReclaimOrphans = No
  SpawnedRequireSpawner = Yes
  SlavesHaveFreeWill = No
End
```

### One-Shot Spawn
```ini
Behavior = SpawnBehavior ModuleTag_Reinforcements
  SpawnNumber = 5
  InitialBurst = 5
  OneShot = Yes
  SpawnTemplateName = USAInfantryRanger
  SpawnTemplateName = USAInfantryRanger
  SpawnTemplateName = USAInfantryRanger
  SpawnTemplateName = USAInfantryRanger
  SpawnTemplateName = USAInfantryRanger
End
```

### Aggregate Health Spawn
```ini
Behavior = SpawnBehavior ModuleTag_HealthAggregate
  SpawnNumber = 2
  SpawnReplaceDelay = 20000
  SpawnTemplateName = ChinaInfantryMinigunner
  AggregateHealth = Yes
  ExitByBudding = Yes
  PropagateDamageTypesToSlavesWhenExisting = NONE +FLAME
End
```

## Template

```ini
Behavior = SpawnBehavior ModuleTag_XX
  ; Spawn Configuration
  SpawnNumber = 1                   ; // maximum number of spawns to maintain *(v1.04)*
  SpawnTemplateName =               ; // template name of object to spawn *(v1.04)*
  SpawnReplaceDelay = 30000         ; // delay before replacing lost spawns *(v1.04)*
  InitialBurst = 0                  ; // spawns to create immediately *(v1.04)*

  ; Spawn Control
  OneShot = No                      ; // spawn only once and become dormant *(v1.04)*
  CanReclaimOrphans = No            ; // reclaim existing orphaned spawns *(v1.04)*
  ExitByBudding = No                ; // create new spawns atop existing ones *(v1.04)*

  ; Spawn Behavior
  SpawnedRequireSpawner = No        ; // spawns require spawner to exist *(v1.04)*
  SlavesHaveFreeWill = No           ; // spawns can act independently *(v1.04, Generals Zero Hour only)*
  AggregateHealth = No              ; // calculate aggregate health offset *(v1.04)*

  ; Damage Propagation
  PropagateDamageTypesToSlavesWhenExisting = NONE ; // damage types to propagate *(v1.04)*

  ; Death Conditions
  DeathTypes = NONE                 ; // death types that trigger behavior *(v1.04)*
  VeterancyLevels =                 ; // veterancy levels that trigger behavior *(v1.04)*
  ExemptStatus =                    ; // status bits that prevent triggering *(v1.04)*
  RequiredStatus =                  ; // required status bits for triggering *(v1.04)*
End
```

## Notes

- SpawnBehavior can maintain a specific number of active spawns and automatically replace lost ones
- Multiple spawn templates can be specified for variety in spawned units
- The behavior supports both continuous spawning and one-shot spawning modes
- Spawned units can be controlled as a group through the SpawnBehaviorInterface
- The spawner can propagate damage to its spawns based on damage type flags
- Aggregate health allows the spawner to represent the combined health of all its spawns
- Spawns can be configured to require the spawner's existence or operate independently
- The behavior integrates with the death system for conditional spawning based on death types
- Spawned objects are created with the same team and player as the spawner

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h), [`SpawnBehaviorInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpawnBehavior.h), [`DieModuleInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpawnBehavior.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpawnBehavior.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/SpawnBehavior.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/SpawnBehavior.cpp)
