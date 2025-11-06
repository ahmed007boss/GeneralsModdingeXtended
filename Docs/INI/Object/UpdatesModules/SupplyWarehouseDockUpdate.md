# SupplyWarehouseDockUpdate

SupplyWarehouseDockUpdate provides docking functionality specifically for supply warehouse facilities.

## Overview

The `SupplyWarehouseDockUpdate` class manages docking operations for objects that need to dock with supply warehouses for resource storage and management operations. It handles supply warehouse docking, approach positioning, and supply coordination. This update is commonly used by supply warehouse facilities, resource storage buildings, and objects that provide supply storage services.

## Usage

Used by objects that need to dock with supply warehouses for resource storage and management operations. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Supply warehouse docking is limited by approach positioning and passthrough parameters
- Docking operations depend on proper supply warehouse integration
- Supply coordination requires proper supply system integration
- Docking effectiveness varies based on supply warehouse capabilities

**Conditions**:
- SupplyWarehouseDockUpdate manages supply warehouse docking and supply coordination
- The update handles approach positioning, passthrough control, and supply operations
- Supply warehouse docking provides resource storage and supply capabilities
- Approach positioning creates realistic supply warehouse operations
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own supply parameters

**Dependencies**:
- Extends DockUpdate for base docking functionality
- Requires supply system integration for supply operations
- Uses dock interface for docking operations

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Docking Settings](#docking-settings)
  - [Supply Settings](#supply-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Docking Settings

#### `AllowsPassthrough` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether units can pass through while docking. When true, allows passthrough. When false, prevents passthrough
- **Default**: `No`
- **Example**: `AllowsPassthrough = No`

#### `NumberApproachPositions` *(v1.04)*
- **Type**: `Int`
- **Description**: Number of approach positions for docking. Higher values allow more approach positions. Lower values limit approach positions. -1 means infinite approach positions
- **Default**: `0`
- **Example**: `NumberApproachPositions = -1`

### Supply Settings

#### `StartingBoxes` *(v1.04)*
- **Type**: `UnsignedInt`
- **Description**: Number of starting supply boxes. Higher values start with more boxes. Lower values start with fewer boxes
- **Default**: `0`
- **Example**: `StartingBoxes = 800`

#### `DeleteWhenEmpty` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether to delete the warehouse when empty. When true, deletes when empty. When false, keeps warehouse when empty
- **Default**: `No`
- **Example**: `DeleteWhenEmpty = Yes`

## Examples

### Basic Supply Warehouse Dock
```ini
Behavior = SupplyWarehouseDockUpdate ModuleTag_06
  AllowsPassthrough = No ;You can't drive through this guy while docking.  Use this when the dock points are all outside
  NumberApproachPositions = -1 ; This is a Boneless dock, so this means infinite can approach
  StartingBoxes     = 800 ; Even if you use a script to set the cash value, this will determine graphically what "full" is.
End
```

### Supply Warehouse Dock with Passthrough
```ini
Behavior = SupplyWarehouseDockUpdate ModuleTag_04
  AllowsPassthrough = Yes ;You can't drive through this guy while docking.  Use this when the dock points are all outside
  NumberApproachPositions = -1 ; This is a Boneless dock, so this means infinite can approach
  StartingBoxes     = 50 ; Even if you use a script to set the cash value, this will determine graphically what "full" is.
End
```

### Supply Warehouse Dock with Deletion
```ini
Behavior = SupplyWarehouseDockUpdate ModuleTag_04
  NumberApproachPositions = -1 ; There are 5 approach bones in the art
  StartingBoxes     = 240 ; Even if you use a script to set the cash value, this will determine graphically what "full" is.
  DeleteWhenEmpty = Yes
End
```

## Template

```ini
Behavior = SupplyWarehouseDockUpdate ModuleTag_XX
  ; Docking Settings
  AllowsPassthrough = No                 ; // whether units can pass through while docking *(v1.04)*
  NumberApproachPositions = 0            ; // number of approach positions for docking *(v1.04)*
  
  ; Supply Settings
  StartingBoxes = 0                      ; // number of starting supply boxes *(v1.04)*
  DeleteWhenEmpty = No                   ; // whether to delete when empty *(v1.04)*
End
```

## Notes

- SupplyWarehouseDockUpdate extends DockUpdate with specialized supply warehouse docking mechanics
- The update provides supply warehouse docking and supply coordination functionality
- Approach positioning creates realistic supply warehouse operations and resource storage
- This update is commonly used by supply warehouse facilities, resource storage buildings, and supply coordination objects
- Supply warehouse docking ensures efficient resource storage and supply operations

## Source Files

**Base Class:** [`DockUpdate`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DockUpdate.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyWarehouseDockUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyWarehouseDockUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/DockUpdate/SupplyWarehouseDockUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/DockUpdate/SupplyWarehouseDockUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet