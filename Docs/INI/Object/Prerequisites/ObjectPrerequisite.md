# <span style="color:#5bbcff; font-weight:bold;">ObjectPrerequisite</span>

Status: AI-generated, 0/2 reviews

## Overview

The `ObjectPrerequisite` block defines checks about a specific object (the unit/building this block is attached to). You can require or forbid types, tags, upgrades, levels, components, nearby objects, or inventory item counts. Used as a child block inside other INI entries to gate behaviors, effects, or supply.

Available only in:
*(GMX Zero Hour)*

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
  - [Limitations](#limitations)
  - [Conditions](#conditions)
  - [Dependencies](#dependencies)
- [Properties](#properties)
  - [Object Type and KindOf](#object-type-and-kindof)
  - [Upgrades and Levels](#upgrades-and-levels)
  - [Model/Status Flags](#modelstatus-flags)
  - [Components](#components)
  - [Nearby Objects](#nearby-objects)
  - [Inventory Items](#inventory-items)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
- [Reviewers](#reviewers)

## Usage

Place as a child block under parent entries that support object prerequisites (e.g., behavior modules). For example, used by `AutoSupplyItemBehavior` as `TargetPrerequisite`.

- Multiple entries of the same property follow the logic described in each category (AND/OR as noted).
- Names refer to other documented entities and should use their string names.

**Limitations**:
- Requires the host to be an [Object](../Object.md). If the host lacks a body, component checks cannot pass.
- Nearby checks depend on partition scanning and map presence; zero range will never match.

**Conditions**:
- Any property can be combined to tailor eligibility (e.g., specific type AND upgrade present AND has at least 3 of an item).

**Dependencies**:
- When properties reference other entities: link to their docs (e.g., upgrades → [Upgrade](../Upgrade.md)).

## Properties

### Object Type and KindOf

- `ObjectIs`
  - Type: Object name (see [Object](../Object.md))
  - Description: Object must be exactly this template.
  - Default: none
  - Example: `ObjectIs = AmericaTankCrusader`
- `ObjectIsNot`
  - Type: Object name (see [Object](../Object.md))
  - Description: Object must NOT be this template.
  - Default: none
  - Example: `ObjectIsNot = AmericaTankPaladin`
- `ObjectIsKindOf`
  - Type: KindOf name (e.g., TANK, INFANTRY)
  - Description: Object must be any of the listed KindOf.
  - Default: none
  - Example: `ObjectIsKindOf = VEHICLE`
- `ObjectIsNoKindOf`
  - Type: KindOf name
  - Description: Object must NOT be any of the listed KindOf.
  - Default: none
  - Example: `ObjectIsNoKindOf = AIRCRAFT`

### Upgrades and Levels

- `ObjectHasUpgrade`
  - Type: Upgrade name or list (see [Upgrade](../Upgrade.md))
  - Description: All listed upgrades must be present on the object.
  - Default: none
  - Example: `ObjectHasUpgrade = Upgrade_ArmorPiercingRounds`
- `ObjectHasNotUpgrade`
  - Type: Upgrade name or list (see [Upgrade](../Upgrade.md))
  - Description: None of the listed upgrades can be present.
  - Default: none
  - Example: `ObjectHasNotUpgrade = Upgrade_SelfRepair`
- `ObjectLevelMoreThan`
  - Type: Int
  - Description: Object veterancy level must be strictly greater than this value.
  - Default: -1 (disabled)
  - Example: `ObjectLevelMoreThan = 1`
- `ObjectLevelLessThan`
  - Type: Int
  - Description: Object veterancy level must be strictly less than this value.
  - Default: -1 (disabled)
  - Example: `ObjectLevelLessThan = 3`

### Model/Status Flags

- `ObjectHasModelCondition`
  - Type: ModelCondition flag name
  - Description: Requires the model condition(s) to be set.
  - Default: none
  - Example: `ObjectHasModelCondition = FIRING_A`
- `ObjectHasNoModelCondition`
  - Type: ModelCondition flag name
  - Description: Forbids the model condition(s).
  - Default: none
  - Example: `ObjectHasNoModelCondition = STUNNED`
- `ObjectHasStatus`
  - Type: Status flag name
  - Description: Requires the status flag(s) to be set.
  - Default: none
  - Example: `ObjectHasStatus = STEALTHED`
- `ObjectHasNoStatus`
  - Type: Status flag name
  - Description: Forbids the status flag(s).
  - Default: none
  - Example: `ObjectHasNoStatus = JAMMED`

### Components

- `ObjectHasComponent`
  - Type: Component name (see [Component](../ObjectBody/ObjectComponents/Component.md))
  - Description: Requires a component with positive max health to exist.
  - Default: none
  - Example: `ObjectHasComponent = Engine`
- `ObjectHasNoComponent`
  - Type: Component name
  - Description: Forbids a component with positive max health.
  - Default: none
  - Example: `ObjectHasNoComponent = Turret`
- `ObjectHasWorkingComponent`
  - Type: Component name
  - Description: Requires the component to exist and not be downed/user-disabled.
  - Default: none
  - Example: `ObjectHasWorkingComponent = Electronics`
- `ObjectHasNoWorkingComponent`
  - Type: Component name
  - Description: Forbids any component that is currently working.
  - Default: none
  - Example: `ObjectHasNoWorkingComponent = WeaponMount`

### Nearby Objects

- `ObjectHasNearbyObject`
  - Type: Repeated pairs: ObjectName Distance
  - Description: Passes if any one of the listed (OR) object types is within the given meters.
  - Default: none
  - Example: `ObjectHasNearbyObject = SupplyDock 300 WarFactory 200`
- `ObjectHasNearbyKindOf`
  - Type: Repeated pairs: KindOfName Distance
  - Description: Passes if any one of the listed (OR) KindOf types is within the given meters.
  - Default: none
  - Example: `ObjectHasNearbyKindOf = STRUCTURE 250 INFANTRY 120`
- `ObjectHasNoNearbyObject`
  - Type: Repeated pairs: ObjectName Distance
  - Description: Fails if any listed object type is within range.
  - Default: none
  - Example: `ObjectHasNoNearbyObject = DemoTrap 100`
- `ObjectHasNoNearbyKindOf`
  - Type: Repeated pairs: KindOfName Distance
  - Description: Fails if any listed KindOf type is within range.
  - Default: none
  - Example: `ObjectHasNoNearbyKindOf = DEFENSIVE_STRUCTURE 200`

### Inventory Items

- `HasAtLeastItem`
  - Type: Repeated pairs: ItemName Count (Item from [InventoryBehavior](../ObjectBehaviorsModules/InventoryBehavior.md))
  - Description: Passes if any one (OR) item meets or exceeds the required count.
  - Default: none
  - Example: `HasAtLeastItem = Tank155HEATAmmo 2 Tank155APAmmo 2`
- `HasAtMostItem`
  - Type: Repeated pairs: ItemName Count
  - Description: Passes if any one (OR) item count is at or below the required count.
  - Default: none
  - Example: `HasAtMostItem = RepairKit 1 Flares 0`
- `ItemStorageFull`
  - Type: Item name list
  - Description: Passes if any one (OR) item storage is full.
  - Default: none
  - Example: `ItemStorageFull = RepairKit Flares`
- `ItemStorageNotFull`
  - Type: Item name list
  - Description: Passes if any one (OR) item storage is not full.
  - Default: none
  - Example: `ItemStorageNotFull = Tank155HEATAmmo Tank155APAmmo`
- `ItemStorageEmpty`
  - Type: Item name list
  - Description: Passes if any one (OR) item storage is empty.
  - Default: none
  - Example: `ItemStorageEmpty = Flares`

## Examples

```ini
; Require a tank with Veteran level and at least 3 HEAT rounds
TargetPrerequisite
  ObjectIsKindOf = TANK
  ObjectLevelMoreThan = 0          ; >0 means Veteran or higher
  HasAtLeastItem = Tank155HEATAmmo 3
End
```

```ini
; Forbid units with working Engine component and any nearby enemy structure within 200m
TargetPrerequisite
  ObjectHasNoWorkingComponent = Engine
  ObjectHasNoNearbyKindOf = STRUCTURE 200
End
```

```ini
; Allow if either RepairKit is full or Flares storage is not full
TargetPrerequisite
  ItemStorageFull = RepairKit
  ItemStorageNotFull = Flares
End
```

## Template

```ini
TargetPrerequisite
  ; Object Type and KindOf
  ObjectIs = ObjectName
  ObjectIsNot = ObjectName
  ObjectIsKindOf = KINDOF_NAME
  ObjectIsNoKindOf = KINDOF_NAME

  ; Upgrades and Levels
  ObjectHasUpgrade = UpgradeName
  ObjectHasNotUpgrade = UpgradeName
  ObjectLevelMoreThan = -1
  ObjectLevelLessThan = -1

  ; Model/Status Flags
  ObjectHasModelCondition = FLAG_NAME
  ObjectHasNoModelCondition = FLAG_NAME
  ObjectHasStatus = STATUS_NAME
  ObjectHasNoStatus = STATUS_NAME

  ; Components
  ObjectHasComponent = ComponentName
  ObjectHasNoComponent = ComponentName
  ObjectHasWorkingComponent = ComponentName
  ObjectHasNoWorkingComponent = ComponentName

  ; Nearby Objects
  ObjectHasNearbyObject = ObjectName 150
  ObjectHasNearbyKindOf = KINDOF_NAME 200
  ObjectHasNoNearbyObject = ObjectName 150
  ObjectHasNoNearbyKindOf = KINDOF_NAME 200

  ; Inventory Items
  HasAtLeastItem = ItemName 3
  HasAtMostItem = ItemName 1
  ItemStorageFull = ItemName
  ItemStorageNotFull = ItemName
  ItemStorageEmpty = ItemName
End
```

## Notes

- Nearby checks use OR logic per line: any one listed item satisfies the condition.
- Inventory item names must match items defined with [InventoryBehavior](../ObjectBehaviorsModules/InventoryBehavior.md).

## Source Files

- Header: `Common/ObjectPrerequisite.h`
- Source: `GeneralsMD/Code/GameEngine/Source/Common/RTS/ObjectPrerequisite.cpp`

## Changes History

- GMX Zero Hour — Adds ObjectPrerequisite system (child prerequisite block for object checks).

## Document Log

- 16/01/2025 — AI — Initial documentation created per authoring guide

## Status

- Documentation Status: AI-generated
- Last Updated: 16/01/2025 by AI
- Certification: 0/2 reviews

### Reviewers

- (pending)


