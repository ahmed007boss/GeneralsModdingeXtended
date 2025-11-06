# HiveStructureBody

Status: AI-generated, 0/2 reviews

## Overview

The `HiveStructureBody` module extends StructureBody with damage redirection capabilities. It redirects specified damage types from the structure to its slave objects (created by SpawnBehavior) or to contained objects (via ContainModule) when they are present. If no slaves/contained objects exist, it can optionally absorb (swallow) certain damage types instead of taking them normally. This creates a "hive mind" effect where the main structure is protected by its minions. This is a module added inside `Object` entries.

Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
  - [Limitations](#limitations)
  - [Conditions](#conditions)
  - [Dependencies](#dependencies)
- [Properties](#properties)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Modder Recommended Use Scenarios](#modder-recommended-use-scenarios)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Document Log](#document-log)
- [Status](#status)
- [Reviewers](#reviewers)

## Usage

Place under `Body = HiveStructureBody ModuleTag_XX` inside `Object` entries. In GMX, HiveStructureBody can also be added to `ObjectExtend` entries. See [Template](#template) for correct syntax.

**Placement**:
- **Retail**: HiveStructureBody can only be added to `Object` entries.
- **GMX**: HiveStructureBody can be added to both `Object` and `ObjectExtend` entries.

Only one body module (ActiveBody, InactiveBody, StructureBody, HiveStructureBody, etc.) can exist per object. If multiple body modules are added to the same object, the game will crash with a "Duplicate bodies" assertion error during object creation. This restriction applies regardless of `ModuleTag` names - the object can only have one body module total.

**Limitations**:
- Requires either a SpawnBehavior module or ContainModule to function
- Can only propagate damage to existing slave/contained objects
- Damage propagation only works for specified damage types

**Conditions**:
- Always active once assigned to an object
- Damage propagation requires active slaves or contained objects
- Creates a "hive mind" effect where the main structure is protected by its minions

**Dependencies**:
- Requires [SpawnBehavior](../ObjectBehaviorsModules/SpawnBehavior.md) and/or [ContainModule](../ObjectModules/ContainModule.md) to supply slaves/contained objects.
- Valid damage type names (see [DamageType](../DamageType.md)).
- Inherits health/visual-state behavior from [StructureBody](StructureBody.md) / [ActiveBody](ActiveBody.md).
- Objects with HiveStructureBody can be healed by [AutoHealBehavior](../ObjectBehaviorsModules/AutoHealBehavior.md). AutoHealBehavior heals main health and, when [ComponentHealingAmount](../ObjectBehaviorsModules/AutoHealBehavior.md#componenthealingamount) is set (GMX Zero Hour only), can also heal components. Component healing respects each component's [HealingType](ObjectComponents/Component.md#healingtype) setting.
- **ObjectExtend (GMX only)**: When HiveStructureBody is added to an `ObjectExtend` entry with the same `ModuleTag` name as the base object, the base object's HiveStructureBody module is automatically replaced. ObjectExtend automatically clears modules with matching `ModuleTag` names when adding new modules.
- **ObjectReskin (both Retail and GMX)**: ObjectReskin uses the same module system as Object. Adding HiveStructureBody to an ObjectReskin entry with the same `ModuleTag` name as the base object will cause a duplicate module tag error, as ObjectReskin does not support automatic module replacement like ObjectExtend.

## Properties

### Damage Propagation

#### `PropagateDamageTypesToSlavesWhenExisting`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `DamageTypeFlags` (bit flags)
- **Description**: Damage types that should be redirected to slave/contained objects when they are available. When set, incoming damage of these types is transferred to the closest slave/contained object. When empty (default), no damage propagation occurs
- **Default**: `0` (none)
- **Example**: `PropagateDamageTypesToSlavesWhenExisting = EXPLOSION BALLISTIC`

#### `SwallowDamageTypesIfSlavesNotExisting`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `DamageTypeFlags` (bit flags)
- **Description**: Damage types that should be completely absorbed when no slaves/contained objects are available. When set, these damage types are negated and cause no effect. When empty (default), all damage is taken normally when no slaves exist
- **Default**: `0` (none)
- **Example**: `SwallowDamageTypesIfSlavesNotExisting = EXPLOSION`

## Examples

### Hive Structure with Explosion Protection
```ini
Body = HiveStructureBody ModuleTag_01
  ; Inherited from StructureBody/ActiveBody
  MaxHealth = 2000.0
  InitialHealth = 2000.0
  
  ; Damage Propagation
  PropagateDamageTypesToSlavesWhenExisting = EXPLOSION BALLISTIC
  SwallowDamageTypesIfSlavesNotExisting = EXPLOSION
End

Behavior = SpawnBehavior ModuleTag_02
  SpawnNumber = 3
  SpawnReplaceDelay = 10000
  SpawnUpgrade = Upgrade_HiveSpawn
End
```

### Transport with Damage Redirection
```ini
Body = HiveStructureBody ModuleTag_03
  ; Inherited from StructureBody/ActiveBody
  MaxHealth = 1500.0
  InitialHealth = 1500.0
  
  ; Damage Propagation
  PropagateDamageTypesToSlavesWhenExisting = BALLISTIC
  SwallowDamageTypesIfSlavesNotExisting = 0
End

Module = ContainModule ModuleTag_04
  Max = 5
  Initial = 0
End
```

## Template

```ini
Body = HiveStructureBody ModuleTag_XX
  ; Inherits all StructureBody/ActiveBody properties
  MaxHealth = 100.0                  ; // maximum health points *(GMX, Retail 1.04)*
  InitialHealth = 100.0              ; // starting health points *(GMX, Retail 1.04)*

  ; Subdual Damage Settings (GMX Zero Hour, Retail Zero Hour 1.04)
  SubdualDamageCap = 0.0             ; // maximum subdual damage before subdual *(GMX Zero Hour, Retail Zero Hour 1.04)*
  SubdualDamageHealRate = 0          ; // milliseconds between subdual damage healing *(GMX Zero Hour, Retail Zero Hour 1.04)*
  SubdualDamageHealAmount = 0.0      ; // amount of subdual damage healed per interval *(GMX Zero Hour, Retail Zero Hour 1.04)*

  ; Electronic Warfare Settings (Generals Zero Hour only)
  JammingDamageCap = 0.0                  ; // maximum jamming damage before jamming *(GMX Zero Hour only)*
  JammingDamageHealRate = 0               ; // milliseconds between jamming damage healing *(GMX Zero Hour only)*
  JammingDamageHealAmount = 0.0           ; // amount of jamming damage healed per interval *(GMX Zero Hour only)*
  CanBeJammedByDirectJammers = No        ; // whether object can be jammed by direct jammers *(GMX Zero Hour only)*
  CanBeJammedByAreaJammers = No          ; // whether object can be jammed by area jammers *(GMX Zero Hour only)*

  ; Damage Propagation
  PropagateDamageTypesToSlavesWhenExisting = 0 ; // damage types to redirect to slaves/contained *(GMX, Retail 1.04)*
  SwallowDamageTypesIfSlavesNotExisting = 0    ; // damage types to absorb if no slaves/contained *(GMX, Retail 1.04)*
End
```

## Notes

- Damage states are updated automatically when [MaxHealth](#maxhealth) changes. HiveStructureBody inherits the damage state system from StructureBody/ActiveBody (see [ActiveBody documentation](ActiveBody.md#bodydamagetype-values) for complete damage state enum values).
- HiveStructureBody requires either SpawnBehavior or ContainModule to function properly. Damage propagation only occurs when slaves/contained objects are available.
- The closest slave/contained object to the damage source receives the redirected damage. Damage absorption (swallowing) only occurs when no slaves exist and the damage type matches the swallow criteria.
- If no slaves exist and the damage type doesn't match swallow criteria, damage is taken normally by the structure.
- Subdual damage types that affect this system: `SUBDUAL_MISSILE`, `SUBDUAL_VEHICLE`, `SUBDUAL_BUILDING`, and `SUBDUAL_UNRESISTABLE` (see [DamageType documentation](../DamageType.md)).
- Jamming damage types that affect this system: `ELECTRONIC_JAMMING` and `JAMMING_UNRESISTABLE` (see [DamageType documentation](../DamageType.md)).

## Modder Recommended Use Scenarios

- HiveStructureBody is used by objects like StingerSite which has slaved objects.

## Source Files

**Base Class:** [StructureBody](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StructureBody.h) (GMX Zero Hour), [StructureBody](../../Generals/Code/GameEngine/Include/GameLogic/Module/StructureBody.h) (GMX Generals)

- Header (GMX Zero Hour): [HiveStructureBody.h](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/HiveStructureBody.h)
- Source (GMX Zero Hour): [HiveStructureBody.cpp](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Body/HiveStructureBody.cpp)
- Header (GMX Generals): [HiveStructureBody.h](../../Generals/Code/GameEngine/Include/GameLogic/Module/HiveStructureBody.h)
- Source (GMX Generals): [HiveStructureBody.cpp](../../Generals/Code/GameEngine/Source/GameLogic/Object/Body/HiveStructureBody.cpp)

## Changes History

- GMX Zero Hour — Inherits Electronic Warfare (Jamming) system and component system from StructureBody/ActiveBody.

## Document Log

- 16/12/2025 — AI — Initial document created.

## Status

- Documentation Status: AI-generated
- Last Updated: 16/12/2025 by AI
- Certification: 0/2 reviews

### Reviewers

- (pending)