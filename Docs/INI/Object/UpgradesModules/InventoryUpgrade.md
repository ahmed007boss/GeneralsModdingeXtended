# InventoryUpgrade

InventoryUpgrade provides inventory enhancement functionality for objects that can upgrade their inventory storage capacity or add new inventory items.

## Overview

The `InventoryUpgrade` class manages inventory enhancement operations for objects that can upgrade their inventory storage capacity, add new inventory items, or modify existing inventory configurations. It handles inventory enhancement activation, inventory modification, and inventory system integration. This upgrade is commonly used by objects that provide inventory enhancement, storage systems, and units with inventory upgrade capabilities.

## Usage

Used by objects that can upgrade their inventory storage capacity, add new inventory items, or modify existing inventory configurations. This is an **upgrade module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Inventory enhancement operations are limited by inventory parameters and inventory system capabilities
- Inventory activation depends on proper upgrade system integration
- Inventory management is controlled by inventory parameters and system capabilities
- Inventory effectiveness varies based on inventory capabilities

**Conditions**:
- InventoryUpgrade manages inventory enhancement operations and inventory system coordination
- The upgrade handles inventory enhancement activation, inventory modification, and inventory management
- Inventory enhancement operations provide storage enhancement and inventory system capabilities
- Inventory management creates realistic inventory system operations
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own inventory parameters

**Dependencies**:
- Uses upgrade system for inventory upgrade activation
- Integrates with inventory system for storage enhancement
- Uses inventory coordination system for inventory management

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

#### `TriggeredBy` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Specifies the player upgrade that triggers this inventory upgrade. When the player completes this upgrade, the inventory enhancement will be applied to all objects with this upgrade module.
- **Default**: Empty string
- **Example**: `TriggeredBy = Upgrade_EnhancedArmory`

#### `Item` *(v1.04)*
- **Type**: `InventoryItemUpgrade` block
- **Description**: Defines an inventory item upgrade configuration. Each Item block can modify an existing inventory item or create a new one. Multiple Item blocks can be used in a single upgrade.
- **Default**: None
- **Example**: See [Examples](#examples) section

#### `MaxStorageCount` *(v1.04)*
- **Type**: `Int`
- **Description**: Sets the absolute maximum storage capacity for the inventory item. Use this to set a specific storage limit.
- **Default**: -1 (no change)
- **Example**: `MaxStorageCount = 10`

#### `AddMaxStorageCount` *(v1.04)*
- **Type**: `Int`
- **Description**: Adds to the existing maximum storage capacity for the inventory item. Use this to increase storage capacity incrementally.
- **Default**: 0 (no change)
- **Example**: `AddMaxStorageCount = 5`

#### `InitialAvailableAmount` *(v1.04)*
- **Type**: `Int`
- **Description**: Sets the absolute initial available amount for the inventory item. Use this to set a specific initial amount.
- **Default**: -1 (no change)
- **Example**: `InitialAvailableAmount = 3`

#### `AddInitialAvailableAmount` *(v1.04)*
- **Type**: `Int`
- **Description**: Adds to the existing initial available amount for the inventory item. Use this to increase initial amount incrementally.
- **Default**: 0 (no change)
- **Example**: `AddInitialAvailableAmount = 2`

#### `DisplayName` *(v1.04)*
- **Type**: `UnicodeString`
- **Description**: Sets the display name for the inventory item. This is typically used when creating new items or changing the display name of existing items.
- **Default**: Empty string (no change)
- **Example**: `DisplayName = Item:RocketAmmo`

#### `CostPerItem` *(v1.04)*
- **Type**: `Int`
- **Description**: Sets the cost per item for replenishment. This is typically used when creating new items or modifying the cost of existing items.
- **Default**: -1 (no change)
- **Example**: `CostPerItem = 100`

## Examples

### Basic Storage Capacity Upgrade
```ini
Behavior = InventoryUpgrade ModuleTag_StorageUpgrade
  TriggeredBy = Upgrade_StorageExpansion
  Item = Ammo
    AddMaxStorageCount = 5
  End
End
```

### Multiple Item Modifications
```ini
Behavior = InventoryUpgrade ModuleTag_EnhancedArmory
  TriggeredBy = Upgrade_EnhancedArmory
  
  ; Modify existing item - set both MaxStorageCount and InitialAvailableAmount
  Item = zzz
    MaxStorageCount = 5
    InitialAvailableAmount = 5
  End
  
  ; Modify existing item - add to MaxStorageCount
  Item = yyy
    AddMaxStorageCount = 10
  End
  
  ; Add new item with full configuration
  Item = xxx
    DisplayName = Item:SCUDExplosiveTwoStageMissle
    MaxStorageCount = 5
    InitialAvailableAmount = 5
    CostPerItem = 250
  End
End
```

### New Weapon Ammunition
```ini
Behavior = InventoryUpgrade ModuleTag_NewWeapons
  TriggeredBy = Upgrade_AdvancedWeapons
  Item = RocketAmmo
    DisplayName = Item:RocketAmmo
    MaxStorageCount = 10
    InitialAvailableAmount = 5
    CostPerItem = 100
  End
  Item = SpecialGrenades
    DisplayName = Item:SpecialGrenades
    MaxStorageCount = 5
    InitialAvailableAmount = 2
    CostPerItem = 200
  End
End
```

### Simple Capacity Increase
```ini
Behavior = InventoryUpgrade ModuleTag_StorageExpansion
  TriggeredBy = Upgrade_StorageExpansion
  Item = Ammo
    AddMaxStorageCount = 3
  End
End
```

## Template

```ini
Behavior = InventoryUpgrade ModuleTag_XX
  TriggeredBy = Upgrade_PlayerUpgradeName
  
  Item = ItemName
    MaxStorageCount = 5                    ; Set absolute max storage *(v1.04)*
    AddMaxStorageCount = 3                 ; Add to existing max storage *(v1.04)*
    InitialAvailableAmount = 2             ; Set absolute initial amount *(v1.04)*
    AddInitialAvailableAmount = 1          ; Add to existing initial amount *(v1.04)*
    DisplayName = Item:DisplayName         ; Set display name *(v1.04)*
    CostPerItem = 100                      ; Set cost per item *(v1.04)*
  End
End
```

## Notes

- InventoryUpgrade provides inventory enhancement operations and inventory system coordination capabilities
- The upgrade manages inventory enhancement activation, inventory modification, and inventory management
- Inventory enhancement operations provide essential storage enhancement and inventory system capabilities
- Inventory management creates realistic inventory system operations and coordination
- This upgrade is commonly used by objects that provide inventory enhancement, storage systems, and inventory upgrade capability units
- Inventory coordination ensures efficient storage enhancement and system integration operations
- **New items**: Items with `DisplayName` or `CostPerItem` set are considered new items and will be created if they don't exist
- **Existing items**: Items without `DisplayName` or `CostPerItem` modifications will only modify existing inventory items
- **Upgrade reversal**: When the upgrade is removed (object destroyed/captured), all changes are properly reverted

## Source Files

**Base Class:** [`UpgradeModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/InventoryUpgrade.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/InventoryUpgrade.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/InventoryUpgrade.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/InventoryUpgrade.cpp)

## Changes History

- **15/01/2025**: Initial implementation by @ahmed Salah using AI
  - Added InventoryUpgrade module with flexible INI format support
  - Implemented multiple item upgrade types (set/add values)
  - Added support for creating new inventory items
  - Integrated with existing upgrade system and module registration

## Status

- **Documentation Status**: Complete
- **Last Updated**: 15/01/2025 by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet
