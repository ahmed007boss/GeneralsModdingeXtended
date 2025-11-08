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

- Multiple entries of the same property follow the logic described in each category (AND/OR as noted). For object-name style lists, multiple names on one line are OR; repeating the line creates additional checks combined by AND.
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
  - Description: Object must be exactly this template. If the name is misspelled or doesn't exist, results are unpredictable — always use the exact object template name.
  - Default: none
  - Example: `ObjectIs = AmericaTankCrusader`
- `ObjectIsNot`
  - Type: Object name (see [Object](../Object.md))
  - Description: Object must NOT be this template. If the name is misspelled or doesn't exist, results are unpredictable — always use the exact object template name.
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
  - Description: All listed upgrades must be present on the object. If an upgrade name is wrong or doesn't exist, the game will stop at load with an error — use exact upgrade names.
  - Default: none
  - Example: `ObjectHasUpgrade = Upgrade_ArmorPiercingRounds`
- `ObjectHasNotUpgrade`
  - Type: Upgrade name or list (see [Upgrade](../Upgrade.md))
  - Description: None of the listed upgrades can be present. If an upgrade name is wrong or doesn't exist, the game will stop at load with an error — use exact upgrade names.
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
  - Description: Requires the model condition(s) to be set. If a flag name doesn't exist, this condition will never pass.
  - Default: none
  - Example: `ObjectHasModelCondition = FIRING_A`
- `ObjectHasNoModelCondition`
  - Type: ModelCondition flag name
  - Description: Forbids the model condition(s). If a flag name doesn't exist, this condition may appear to have no effect.
  - Default: none
  - Example: `ObjectHasNoModelCondition = STUNNED`
- `ObjectHasStatus`
  - Type: Status flag name
  - Description: Requires the status flag(s) to be set. If a flag name doesn't exist, this condition will never pass.
  - Default: none
  - Example: `ObjectHasStatus = STEALTHED`
- `ObjectHasNoStatus`
  - Type: Status flag name
  - Description: Forbids the status flag(s). If a flag name doesn't exist, this condition may appear to have no effect.
  - Default: none
  - Example: `ObjectHasNoStatus = JAMMED`

### Components

- `ObjectHasComponent`
  - Type: Component name (see [Component](../ObjectBody/ObjectComponents/Component.md))
  - Description: Requires a component with positive max health to exist. If the component name doesn't exist on this object, this condition will never pass.
  - Default: none
  - Example: `ObjectHasComponent = Engine`
- `ObjectHasNoComponent`
  - Type: Component name
  - Description: Forbids a component with positive max health. If the component name doesn't exist on this object, this condition already holds.
  - Default: none
  - Example: `ObjectHasNoComponent = Turret`
- `ObjectHasWorkingComponent`
  - Type: Component name
  - Description: Requires the component to exist and not be downed/user-disabled. If the component name doesn't exist on this object, this condition will never pass.
  - Default: none
  - Example: `ObjectHasWorkingComponent = Electronics`
- `ObjectHasNoWorkingComponent`
  - Type: Component name
  - Description: Forbids any component that is currently working. If the component name doesn't exist on this object, this condition already holds.
  - Default: none
  - Example: `ObjectHasNoWorkingComponent = WeaponMount`

### Nearby Objects

- `ObjectHasNearbyObject`
  - Type: Repeated pairs: ObjectName Distance
  - Description: Passes if any one of the listed (OR) object types is within the given meters. If an object name doesn't exist, that entry will never match.
  - Default: none
  - Example: `ObjectHasNearbyObject = SupplyDock 300 WarFactory 200`
- `ObjectHasNearbyKindOf`
  - Type: Repeated pairs: KindOfName Distance
  - Description: Passes if any one of the listed (OR) KindOf types is within the given meters. If a KindOf name is wrong, the game may stop loading with an error — use exact KindOf names.
  - Default: none
  - Example: `ObjectHasNearbyKindOf = STRUCTURE 250 INFANTRY 120`
- `ObjectHasNoNearbyObject`
  - Type: Repeated pairs: ObjectName Distance
  - Description: Fails if any listed object type is within range. If an object name doesn't exist, that entry will never match.
  - Default: none
  - Example: `ObjectHasNoNearbyObject = DemoTrap 100`
- `ObjectHasNoNearbyKindOf`
  - Type: Repeated pairs: KindOfName Distance
  - Description: Fails if any listed KindOf type is within range. If a KindOf name is wrong, the game may stop loading with an error — use exact KindOf names.
  - Default: none
  - Example: `ObjectHasNoNearbyKindOf = DEFENSIVE_STRUCTURE 200`

### Inventory Items

- `HasAtLeastItem`
  - Type: Repeated pairs: ItemName Count (Item from [InventoryBehavior](../ObjectBehaviorsModules/InventoryBehavior.md))
  - Description: Passes if any one (OR) item meets or exceeds the required count. If an item name doesn't exist for this object, that entry will never match.
  - Default: none
  - Example: `HasAtLeastItem = Tank155HEATAmmo 2 Tank155APAmmo 2`
- `HasAtMostItem`
  - Type: Repeated pairs: ItemName Count
  - Description: Passes if any one (OR) item count is at or below the required count. If an item name doesn't exist for this object, that entry will never match.
  - Default: none
  - Example: `HasAtMostItem = RepairKit 1 Flares 0`
- `ItemStorageFull`
  - Type: Item name list
  - Description: Passes if any one (OR) item storage is full. If an item name doesn't exist for this object, that entry will never match.
  - Default: none
  - Example: `ItemStorageFull = RepairKit Flares`
- `ItemStorageNotFull`
  - Type: Item name list
  - Description: Passes if any one (OR) item storage is not full. If an item name doesn't exist for this object, that entry will never match.
  - Default: none
  - Example: `ItemStorageNotFull = Tank155HEATAmmo Tank155APAmmo`
- `ItemStorageEmpty`
  - Type: Item name list
  - Description: Passes if any one (OR) item storage is empty. If an item name doesn't exist for this object, that entry will never match.
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
  ObjectIs = ObjectName                     ; exact object template must match
  ObjectIsNot = ObjectName                  ; object template must NOT match
  ObjectIsKindOf = KINDOF_NAME              ; must be any of these KindOf
  ObjectIsNoKindOf = KINDOF_NAME            ; must NOT be any of these KindOf

  ; Upgrades and Levels
  ObjectHasUpgrade = UpgradeName            ; requires listed upgrade(s)
  ObjectHasNotUpgrade = UpgradeName         ; forbids listed upgrade(s)
  ObjectLevelMoreThan = -1                  ; veterancy strictly greater than value
  ObjectLevelLessThan = -1                  ; veterancy strictly less than value

  ; Model/Status Flags
  ObjectHasModelCondition = FLAG_NAME       ; requires model condition flag(s)
  ObjectHasNoModelCondition = FLAG_NAME     ; forbids model condition flag(s)
  ObjectHasStatus = STATUS_NAME             ; requires status flag(s)
  ObjectHasNoStatus = STATUS_NAME           ; forbids status flag(s)

  ; Components
  ObjectHasComponent = ComponentName        ; component exists and has health
  ObjectHasNoComponent = ComponentName      ; component must not exist/active
  ObjectHasWorkingComponent = ComponentName ; component exists and is working
  ObjectHasNoWorkingComponent = ComponentName ; component exists but not working

  ; Nearby Objects
  ObjectHasNearbyObject = ObjectName 150    ; any listed object within meters
  ObjectHasNearbyKindOf = KINDOF_NAME 200   ; any listed KindOf within meters
  ObjectHasNoNearbyObject = ObjectName 150  ; none of these objects within meters
  ObjectHasNoNearbyKindOf = KINDOF_NAME 200 ; none of these KindOf within meters

  ; Inventory Items
  HasAtLeastItem = ItemName 3               ; item count ≥ required
  HasAtMostItem = ItemName 1                ; item count ≤ required
  ItemStorageFull = ItemName                ; storage full for any listed item
  ItemStorageNotFull = ItemName             ; storage not full for any listed item
  ItemStorageEmpty = ItemName               ; storage empty for any listed item
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


