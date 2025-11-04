# <span style="color:#5bbcff; font-weight:bold;">HiveStructureBody</span>

Status: AI-generated, 0/2 reviews

## Overview

The `HiveStructureBody` module redirects specified damage types from the structure to its slave objects (via [SpawnBehavior](../ObjectBehaviorsModules/SpawnBehavior.md)) or to contained objects (via [ContainModule](../ObjectModules/ContainModule.md)) when they are present. If no slaves/contained objects exist, it can optionally absorb (swallow) certain damage types instead of taking them normally. This creates a "hive" effect that protects the main structure.

Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
  - [Limitations](#limitations)
  - [Conditions](#conditions)
  - [Dependencies](#dependencies)
- [Properties](#properties)
  - [Damage Propagation](#damage-propagation)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Document Log](#document-log)
- [Status](#status)
- [Reviewers](#reviewers)

## Usage

Place under `Body = HiveStructureBody ModuleTag_XX` inside [Object](../Object.md) entries. See [Template](#template) for correct syntax.

**Limitations**:
- Requires [SpawnBehavior](../ObjectBehaviorsModules/SpawnBehavior.md) or [ContainModule](../ObjectModules/ContainModule.md) to redirect damage.
- Only redirects or swallows the damage types listed in properties; other types behave normally.
- Only one body module may exist per object (ActiveBody/StructureBody/ImmortalBody/etc.).

**Conditions**:
- Always active once added to an object.
- Damage redirection requires at least one slave/contained object; otherwise, swallow rules may apply.
- Objects with HiveStructureBody can be targeted by [Weapon](../Weapon.md); armor (see [Armor](../Armor.md)) applies before redirection/swallowing.
- **ObjectExtend (GMX only)**: Adding HiveStructureBody in `ObjectExtend` with the same `ModuleTag` name replaces the base object's body module.
- **ObjectReskin (both Retail and GMX)**: Adding a body module with the same `ModuleTag` name causes a duplicate-module error (no automatic replacement).

**Dependencies**:
- [SpawnBehavior](../ObjectBehaviorsModules/SpawnBehavior.md) and/or [ContainModule](../ObjectModules/ContainModule.md) to supply slaves/contained objects.
- Valid damage type names (see [DamageType](../DamageType.md)).
- Inherits health/visual-state behavior from [StructureBody](./StructureBody.md) / [ActiveBody](./ActiveBody.md).

## Properties

### Damage Propagation

#### `PropagateDamageTypesToSlavesWhenExisting`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `DamageTypeFlags` (see [DamageType](../DamageType.md))
- **Description**: Redirect these damage types to the closest slave/contained object when present. Empty means no redirection. Use valid damage type names; invalid names will fail to parse.
- **Default**: `0` (none)
- **Example**: `PropagateDamageTypesToSlavesWhenExisting = EXPLOSION BALLISTIC`

#### `SwallowDamageTypesIfSlavesNotExisting`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `DamageTypeFlags` (see [DamageType](../DamageType.md))
- **Description**: When no slaves/contained objects exist, completely absorb these damage types (no effect on the structure). Empty means damage is taken normally. Use valid damage type names; invalid names will fail to parse.
- **Default**: `0` (none)
- **Example**: `SwallowDamageTypesIfSlavesNotExisting = EXPLOSION`

## Examples

```ini
Body = HiveStructureBody ModuleTag_01
  ; Health (from StructureBody/ActiveBody)
  MaxHealth = 2000.0
  InitialHealth = 2000.0

  ; Damage Propagation
  PropagateDamageTypesToSlavesWhenExisting = EXPLOSION BALLISTIC
  SwallowDamageTypesIfSlavesNotExisting = EXPLOSION
End

Behavior = SpawnBehavior ModuleTag_Slaves
  SpawnNumber = 3
  SpawnReplaceDelay = 10000
End
```

```ini
Body = HiveStructureBody ModuleTag_Transport
  MaxHealth = 1500.0
  InitialHealth = 1500.0

  ; Redirect ballistic damage to contained units; do not swallow
  PropagateDamageTypesToSlavesWhenExisting = BALLISTIC
  SwallowDamageTypesIfSlavesNotExisting = 0
End

Module = ContainModule ModuleTag_Contain
  Max = 5
  Initial = 0
End
```

## Template

```ini
Body = HiveStructureBody ModuleTag_XX
  ; Inherits health/state from StructureBody/ActiveBody
  MaxHealth = 100.0                       ; // maximum health *(GMX, Retail 1.04)*
  InitialHealth = 100.0                   ; // starting health *(GMX, Retail 1.04)*

  ; Damage Propagation
  PropagateDamageTypesToSlavesWhenExisting = 0  ; // redirect these types to slaves/contained *(GMX, Retail 1.04)*
  SwallowDamageTypesIfSlavesNotExisting = 0     ; // absorb these types if no slaves/contained *(GMX, Retail 1.04)*
End
```

## Notes

- Redirection chooses the closest eligible slave/contained object for the listed damage types.
- Swallowing applies only when there are no available slave/contained objects.
- Armor and resistances apply before redirection/swallowing.
- Use valid [DamageType](../DamageType.md) names; invalid names will abort parsing.
- Only one body module is allowed per object; multiple bodies cause a startup assertion.
- Recommended for hive-like structures protected by spawned drones or garrisoned units.

## Source Files

**Base Class:** [StructureBody](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StructureBody.h) (GMX Zero Hour), [StructureBody](../../Generals/Code/GameEngine/Include/GameLogic/Module/StructureBody.h) (GMX Generals)

- Header (GMX Zero Hour): [GeneralsMD/Code/GameEngine/Include/GameLogic/Module/HiveStructureBody.h](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/HiveStructureBody.h)
- Source (GMX Zero Hour): [GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Body/HiveStructureBody.cpp](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Body/HiveStructureBody.cpp)
- Header (GMX Generals): [Generals/Code/GameEngine/Include/GameLogic/Module/HiveStructureBody.h](../../Generals/Code/GameEngine/Include/GameLogic/Module/HiveStructureBody.h)
- Source (GMX Generals): [Generals/Code/GameEngine/Source/GameLogic/Object/Body/HiveStructureBody.cpp](../../Generals/Code/GameEngine/Source/GameLogic/Object/Body/HiveStructureBody.cpp)

## Changes History

- GMX — Adds HiveStructureBody (damage redirection/swallowing for structures).

## Document Log

- 16/12/2025 — AI — Initial document created.

## Status

- Documentation Status: AI-generated
- Last Updated: 16/12/2025 by AI
- Certification: 0/2 reviews

### Reviewers

- (pending)
