# <span style="color:#5bbcff; font-weight:bold;">InventoryBehavior</span>

Status: AI-generated, 0/2 reviews

## Overview

The `InventoryBehavior` module lets an object manage a limited set of named items with counts. Each item can have a display name, maximum storage, initial amount, cost per item, an optional icon shown when empty, and an emptiness threshold. Use this to gate abilities, ammo-like resources, repair kits, or consumables that deplete and can be replenished.

Available only in:
*(GMX Zero Hour)*

## Table of Contents

- [Overview](#overview)
- [Properties](#properties)
  - [Inventory Item Settings](#inventory-item-settings)
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
- [Status](#status)
- [Reviewers](#reviewers)

## Properties

### Inventory Item Settings

Available only in:
*(GMX Zero Hour)*

Inventory items are configured as named sub-blocks using `Item = <Key>` inside the behavior. Each item block contains the item settings listed below.

#### `DisplayName`
Available only in:
*(GMX Zero Hour)*

- **Type**: `UnicodeString`
- **Description**: Human-friendly name shown in UI for this item key.
- **Default**: empty
- **Example**: `DisplayName = Field Repair Kit`

#### `MaxStorageCount`
Available only in:
*(GMX Zero Hour)*

- **Type**: `Real`
- **Description**: Maximum amount that can be held for this item. Higher values allow more stock.
- **Default**: `0.0`
- **Example**: `MaxStorageCount = 6`

#### `InitialAvailableAmount`
Available only in:
*(GMX Zero Hour)*

- **Type**: `Real`
- **Description**: Amount available at object creation. If it exceeds [MaxStorageCount](#maxstoragecount), it is effectively capped by gameplay at the maximum.
- **Default**: `0.0`
- **Example**: `InitialAvailableAmount = 3`

#### `CostPerItem`
Available only in:
*(GMX Zero Hour)*

- **Type**: `Int`
- **Description**: Cost (credits) to replenish one unit of this item, used by custom logic/UI.
- **Default**: `0`
- **Example**: `CostPerItem = 200`

#### `EmptyIconAnimation`
Available only in:
*(GMX Zero Hour)*

- **Type**: `Animation2d` (see [Animation2d documentation](../Animation2d.md))
- **Description**: Icon animation to show when this item is empty. Leave unset for no icon.
- **Default**: none
- **Example**: `EmptyIconAnimation = Icon_Repair_Empty`

#### `EmptyThreshold`
Available only in:
*(GMX Zero Hour)*

- **Type**: `Real`
- **Description**: Amount at or below which the item is considered empty. Controls when the empty icon triggers via [EmptyIconAnimation](#emptyiconanimation).
- **Default**: `0.0`
- **Example**: `EmptyThreshold = 0.0`

## Examples

### Single resource with UI icon

```ini
Behavior = InventoryBehavior ModuleTag_Inventory
  Item = Ammo
    DisplayName = High-Explosive Ammo
    MaxStorageCount = 6
    InitialAvailableAmount = 2
    CostPerItem = 100
    EmptyIconAnimation = Icon_Ammo_Empty
    EmptyThreshold = 0.0
  End
End
```

### Multiple consumables

```ini
Behavior = InventoryBehavior ModuleTag_Inventory
  Item = RepairKit
    DisplayName = Field Repair Kit
    MaxStorageCount = 3
    InitialAvailableAmount = 1
    CostPerItem = 200
  End

  Item = Flares
    DisplayName = Decoy Flares
    MaxStorageCount = 5
    InitialAvailableAmount = 0
    CostPerItem = 150
    EmptyIconAnimation = Icon_Flares_Empty
  End
End
```

### Threshold-based empty state

```ini
Behavior = InventoryBehavior ModuleTag_Inventory
  Item = EnergyCell
    DisplayName = Energy Cell
    MaxStorageCount = 100
    InitialAvailableAmount = 25
    EmptyThreshold = 5
  End
End
```

### Ammo-only minimal config

```ini
Behavior = InventoryBehavior ModuleTag_Inventory
  Item = Ammo
    MaxStorageCount = 4
    InitialAvailableAmount = 4
  End
End
```

### UI-only empty icon

```ini
Behavior = InventoryBehavior ModuleTag_Inventory
  Item = Tool
    EmptyIconAnimation = Icon_Tool_Empty
  End
End
```

### Fuel with Locomotor consumption

```ini
; Inventory items
Behavior = InventoryBehavior ModuleTag_Inventory
  Item = Fuel
    DisplayName = Fuel
    MaxStorageCount = 100
    InitialAvailableAmount = 50
  End
End

; Movement that consumes Fuel over time
Locomotor = SomeLocomotorName
  ConsumeItem = Fuel          ; // inventory item key to use as fuel
  ConsumeRate = 1.5           ; // units per second
End
```

### Auto-supply nearby units (pairs with AutoSupplyItemBehavior)

```ini
; Automatically supplies nearby allies with Fuel
Behavior = AutoSupplyItemBehavior ModuleTag_AutoFuel
  SupplyItemKey = Fuel           ; // item key to give
  SupplyAmount = 5               ; // amount per tick
  SupplyRadius = 150             ; // range to search
  SupplyDelay = 1000             ; // milliseconds between ticks
  SupplyAllUnits = Yes           ; // supply everyone in range
  ; TargetPrerequisite block optional to filter targets
End
```

### Multiple ammo types consumed by weapons (pairs with Weapon)

```ini
; Two distinct ammo items on the same object
Behavior = InventoryBehavior ModuleTag_Inventory
  Item = Tank155HEATAmmo
    DisplayName = 155mm HEAT Rounds
    MaxStorageCount = 20
    InitialAvailableAmount = 8
  End
  Item = Tank155APAmmo
    DisplayName = 155mm AP Rounds
    MaxStorageCount = 20
    InitialAvailableAmount = 12
  End
End

; Two weapons configured to consume different ammo types
Weapon TankMainGunHEAT
  ; ... normal weapon settings ...
  ConsumeInventory = Tank155HEATAmmo
  ClipSize = 5
End

Weapon TankMainGunAP
  ; ... normal weapon settings ...
  ConsumeInventory = Tank155APAmmo
  ClipSize = 5
End
```

## Usage

Place under `Behavior = InventoryBehavior ModuleTag_XX` inside [Object](../Object.md) entries. See [Template](#template) for correct syntax.

**Limitations**:
- Item keys must be unique within the same behavior; reusing the same key can override or collide depending on loading order.
- [InitialAvailableAmount](#initialavailableamount) is effectively limited by [MaxStorageCount](#maxstoragecount) in gameplay.
- Empty icon display requires a valid [EmptyIconAnimation](#emptyiconanimation) and an item count at or below [EmptyThreshold](#emptythreshold).
- Fuel usage requires a locomotor configured with [ConsumeItem](../Locomotor.md#consumeitem) and [ConsumeRate](../Locomotor.md#consumerate). Without these, movement will not drain fuel and is effectively unlimited (default behavior).

**Conditions**:
- Items are consumed, replenished, or checked by game logic that you connect via upgrades, behaviors, commands, or scripts. Typical usage includes checking counts before allowing actions.
- Display name is used by UI when present.
- When paired with [Locomotor](../Locomotor.md): if [ConsumeItem](../Locomotor.md#consumeitem) is set and [ConsumeRate](../Locomotor.md#consumerate) > 0, movement drains that item per second. If the item is missing or insufficient, movement may pause or fail until replenished. UI can display current and max fuel based on the configured [ConsumeItem](../Locomotor.md#consumeitem). If a locomotor does not specify [ConsumeItem](../Locomotor.md#consumeitem), movement does not consume inventory (unlimited; default).
- With AI/updates: AI flight/movement logic (see [JetAIUpdate](../ObjectUpdates/JetAIUpdate.md)) checks whether enough of the configured fuel item is available each second. If there isn’t enough fuel, units may delay actions, return to base, or stop until refueled.
- With parking/resupply: [ParkingPlaceBehavior](../ObjectBehaviorsModules/ParkingPlaceBehavior.md) can top up items when parked; [AutoSupplyItemBehavior](../ObjectBehaviorsModules/AutoSupplyItemBehavior.md) can add items automatically to nearby units.
- With command buttons: Resupply commands can refill items. Typical flow fills a consuming weapon's clip first (if empty), then tops up the remaining inventory to its [MaxStorageCount](#maxstoragecount). See [CommandButton](../CommandButton.md) for binding resupply actions.
 - With command buttons: Resupply commands can refill items. Typical flow fills a consuming weapon's clip first (if empty), then tops up the remaining inventory to its [MaxStorageCount](#maxstoragecount). The total cost is calculated per item using each item's [CostPerItem](#costperitem). See [CommandButton](../CommandButton.md) for binding resupply actions and [InventoryUpgrade](../ObjectUpgrades/InventoryUpgrade.md) if you need to adjust costs dynamically.
- With weapons: Weapons that declare an inventory name in their configuration (see [Weapon documentation](../Weapon.md), property `ConsumeInventory`) will reduce that item's amount when firing. If the item runs out, the weapon cannot fire until resupplied or reloaded. UI ammo pips and clip reload timings still apply. If a weapon does not specify `ConsumeInventory`, firing does not consume inventory (unlimited; default).

**Dependencies**:
- For icons, you must have a valid [Animation2d](../Animation2d.md) resource defined with the given name; otherwise no icon is shown.
- Any consumption/replenishment rules depend on the systems you pair with this behavior (commands, upgrades, scripts) to call into inventory operations.
- Fuel interactions depend on a configured [Locomotor](../Locomotor.md) that declares [ConsumeItem](../Locomotor.md#consumeitem) and [ConsumeRate](../Locomotor.md#consumerate). Without a locomotor, fuel will not be consumed.
- Automated resupply depends on systems like [ParkingPlaceBehavior](../ObjectBehaviorsModules/ParkingPlaceBehavior.md) or [AutoSupplyItemBehavior](../ObjectBehaviorsModules/AutoSupplyItemBehavior.md). If not present, items must be replenished by other means (e.g., upgrades, scripts, or command buttons).
 - Command-based resupply depends on a command/button that triggers replenishment on the selected unit(s). Without a bound command, players cannot request resupply manually.
 - Weapon-based consumption depends on weapons configured to use an inventory item (see [Weapon documentation](../Weapon.md), property `ConsumeInventory`). Without that, firing will not use inventory.
 - Command-based resupply also depends on sufficient player credits to cover the calculated total based on [CostPerItem](#costperitem); without enough credits, resupply will not complete.

## Template

```ini
Behavior = InventoryBehavior ModuleTag_XX
  ; Example items — add as many as needed
  Item = Key
    DisplayName = Name              ; // shown in UI *(GMX Zero Hour)*
    MaxStorageCount = 0             ; // maximum amount *(GMX Zero Hour)*
    InitialAvailableAmount = 0      ; // starting amount *(GMX Zero Hour)*
    CostPerItem = 0                 ; // cost to replenish *(GMX Zero Hour)*
    EmptyIconAnimation = Icon_Name  ; // icon when empty *(GMX Zero Hour)*
    EmptyThreshold = 0.0            ; // threshold considered empty *(GMX Zero Hour)*
  End
End
```

## Notes

- Use distinct item keys for different resources (e.g., `Ammo`, `RepairKit`, `Flares`).
- Set [EmptyThreshold](#emptythreshold) above `0.0` if you want the empty icon to show before the count hits absolute zero.
- Pair with upgrade/command logic to consume or replenish items during gameplay.

## Modder Recommended Use Scenarios

(pending modder review)

## Source Files

- Header: [GeneralsMD/Code/GameEngine/Include/GameLogic/Module/InventoryBehavior.h](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/InventoryBehavior.h)

## Changes History

- GMX Zero Hour — Adds InventoryBehavior (item storage/consumption behavior).

## Document Log

- 15/01/2025 — AI — Initial documentation created following authoring guide

## Status

- Documentation Status: AI-generated
- Last Updated: 15/01/2025 by AI
- Certification: 0/2 reviews

### Reviewers

- (pending)


