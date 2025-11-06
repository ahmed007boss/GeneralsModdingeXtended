# <span style="color:#5bbcff; font-weight:bold;">AutoSupplyItemBehavior</span> *(GMX)*

Status: AI-generated, 0/2 reviews

## Overview

`AutoSupplyItemBehavior` automatically supplies a chosen inventory item to nearby eligible units at a fixed time interval within a configured radius. It searches allies around the host object, filters by a target prerequisite, and either supplies all matches or the single unit that needs it the most. Intended for field supply vehicles, support stations, and logistics helpers.

Available only in:
*(GMX Zero Hour)*

## Table of Contents

- [Overview](#overview)
- [Properties](#properties)
  - [Supply Settings](#supply-settings)
  - [Target Filtering](#target-filtering)
- [Examples](#examples)
- [Usage](#usage)
  - [Limitations](#limitations)
  - [Conditions](#conditions)
  - [Dependencies](#dependencies)
- [Template](#template)
- [Notes](#notes)
- [Modder Recommended Use Scenarios](#modder-recommended-use-scenarios)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Document Log](#document-log)
- [Status](#status)
- [Reviewers](#reviewers)

## Properties

### Supply Settings
Available only in:
*(GMX Zero Hour)*

<a id="supplyitemkey"></a>
- `SupplyItemKey`
  - Type: Item key (AsciiString). Item must exist in [InventoryBehavior](./InventoryBehavior.md) of receivers
  - Description: Name of the inventory item to supply.
  - Default: empty (disabled)
  - Example: `SupplyItemKey = Fuel`
<a id="supplyamount"></a>
- `SupplyAmount`
  - Type: `Real`
  - Description: Amount added per supply tick. Higher values refill faster.
  - Default: `1.0`
  - Example: `SupplyAmount = 5`
<a id="supplyradius"></a>
- `SupplyRadius`
  - Type: `Real`
  - Description: Search radius in game distance units for eligible targets.
  - Default: `100.0`
  - Example: `SupplyRadius = 150`
- `SupplyDelay`
  - Type: `UnsignedInt` (milliseconds)
  - Description: Interval between supply ticks. Lower values supply more frequently.
  - Default: `1000`
  - Example: `SupplyDelay = 500`
<a id="supplyallunits"></a>
- `SupplyAllUnits`
  - Type: `Bool`
  - Description: When `Yes`, supplies every eligible target in range each tick; when `No`, supplies only the single unit most in need of the item.
  - Default: `No`
  - Example: `SupplyAllUnits = Yes`

### Target Filtering
Available only in:
*(GMX Zero Hour)*

<a id="targetprerequisite"></a>
- `TargetPrerequisite`
  - Type: `ObjectPrerequisite` block (see [ObjectPrerequisite](../Prerequisites/ObjectPrerequisite.md))
  - Description: Filters which units can be supplied (e.g., restrict by KindOf, upgrade states, components, inventory states).
  - Default: empty (no additional filtering)
  - Example:
    ```ini
    TargetPrerequisite
      ObjectIsKindOf = VEHICLE
    End
    ```

## Examples

```ini
; Supply Fuel to nearby allied vehicles every second within 150 range
Behavior = AutoSupplyItemBehavior ModuleTag_FuelSupply
  SupplyItemKey   = Fuel
  SupplyAmount    = 5
  SupplyRadius    = 150
  SupplyDelay     = 1000
  SupplyAllUnits  = Yes
  TargetPrerequisite
    ObjectIsKindOf = VEHICLE
  End
End
```

```ini
; Ammo supplier that refills one unit at a time (lowest amount first)
Behavior = AutoSupplyItemBehavior ModuleTag_AmmoSupply
  SupplyItemKey   = Ammo
  SupplyAmount    = 2
  SupplyRadius    = 120
  SupplyDelay     = 750
  SupplyAllUnits  = No
End
```

## Usage

Place under `Behavior = AutoSupplyItemBehavior ModuleTag_XX` inside [Object](../Object.md) entries. See [Template](#template) for correct syntax.

### Limitations
- Supply is paused if the host is restricted from replenishment for the [SupplyItemKey](#supplyitemkey) (e.g., storage component destroyed). The behavior checks restriction before each tick.
- If a receiver’s item storage is already full for [SupplyItemKey](#supplyitemkey), that unit is skipped.
- Requires at least one eligible nearby target within [SupplyRadius](#supplyradius).

### Conditions
- When [SupplyAllUnits](#supplyallunits) is `Yes`, all eligible targets within [SupplyRadius](#supplyradius) receive [SupplyAmount](#supplyamount) each tick.
- When [SupplyAllUnits](#supplyallunits) is `No`, the single best target (lowest current amount of the item) is supplied per tick.
- A receiver must expose an [InventoryBehavior](./InventoryBehavior.md) with an item entry matching [SupplyItemKey](#supplyitemkey).
- [TargetPrerequisite](../Prerequisites/ObjectPrerequisite.md) further restricts which units can be supplied.

### Dependencies
- Receiver-side [InventoryBehavior](./InventoryBehavior.md): defines the item key and storage limits.
- Optional [ObjectPrerequisite](../Prerequisites/ObjectPrerequisite.md) via [TargetPrerequisite](#targetprerequisite) to filter receivers.
- Component systems may restrict replenishment (see [InventoryStorageComponent](../ObjectBody/ObjectComponents/InventoryStorageComponent.md)) — if storage destruction restricts replenishment for the item, supply is skipped until restored.

## Template

```ini
Behavior = AutoSupplyItemBehavior ModuleTag_XX
  SupplyItemKey   =                ; // item key to supply *(GMX Zero Hour)*
  SupplyAmount    = 1              ; // amount per tick *(GMX Zero Hour)*
  SupplyRadius    = 100            ; // search radius *(GMX Zero Hour)*
  SupplyDelay     = 1000           ; // milliseconds between ticks *(GMX Zero Hour)*
  SupplyAllUnits  = No             ; // Yes = supply all, No = best-one *(GMX Zero Hour)*

  TargetPrerequisite               ; // optional filter (ObjectPrerequisite) *(GMX Zero Hour)*
    ; ObjectIsKindOf = VEHICLE
  End
End
```

## Notes
- The behavior supplies allies by default (relationship filter). Adjust who receives supply via [TargetPrerequisite](../Prerequisites/ObjectPrerequisite.md) conditions (e.g., team/faction conditions once available).
- For dense areas, prefer `SupplyAllUnits = No` to spread supply over time and reduce spikes.
- Pair with UI feedback (icons or FX) on receivers if desired via other systems.
- Works with any item key defined in [InventoryBehavior](./InventoryBehavior.md) on both the supplier and receivers.

## Modder Recommended Use Scenarios

(pending modder review)

## Source Files

- **Base Class:** [UpdateModule](../../Core/GameEngine/Include/GameLogic/Module/UpdateModule.h)
- Header: [GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AutoSupplyItemBehavior.h](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AutoSupplyItemBehavior.h)
- Source: [GeneralsMD/Code/GameEngine/Source/GameLogic/Module/AutoSupplyItemBehavior.cpp](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Module/AutoSupplyItemBehavior.cpp)

## Changes History

- GMX Zero Hour — Adds AutoSupplyItemBehavior (automatic nearby supply of inventory items).

## Document Log

- 15/01/2025 — AI — Initial documentation created per authoring guide

## Status

- Documentation Status: AI-generated
- Last Updated: 15/01/2025 by AI
- Certification: 0/2 reviews

### Reviewers

- (pending)


