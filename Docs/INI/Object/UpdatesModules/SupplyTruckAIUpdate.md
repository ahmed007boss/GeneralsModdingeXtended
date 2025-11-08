# SupplyTruckAIUpdate

SupplyTruckAIUpdate provides AI update functionality for supply truck units.

## Overview

The `SupplyTruckAIUpdate` class manages AI-driven supply operations for supply truck units including resource transport, supply center coordination, warehouse management, and logistics operations. It handles supply truck behavior, resource management, and supply system integration. This update is commonly used by supply truck units, logistics vehicles, and units that manage resource transport.

## Usage

Used by supply truck units to handle AI-driven supply operations, resource transport, and logistics. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Supply operations are limited by box capacity and action delay parameters
- Supply coordination depends on proper supply center and warehouse integration
- Resource transport is controlled by AI behavior and logistics parameters
- Supply effectiveness varies based on supply system capabilities

**Conditions**:
- SupplyTruckAIUpdate manages AI-driven supply operations and resource transport
- The update handles supply center and warehouse coordination for logistics
- Supply operations provide resource management and transport capabilities
- AI behavior creates autonomous supply truck operations
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own supply parameters

**Dependencies**:
- Uses AI system for autonomous supply truck behavior
- Integrates with supply system for resource management
- Uses logistics system for supply coordination

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Supply Capacity Settings](#supply-capacity-settings)
  - [Action Timing Settings](#action-timing-settings)
  - [Audio Settings](#audio-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Supply Capacity Settings

#### `MaxBoxes` *(v1.04)*
- **Type**: `Int`
- **Description**: Maximum number of supply boxes the truck can carry. Higher values increase carrying capacity. Lower values decrease carrying capacity
- **Default**: `0`
- **Example**: `MaxBoxes = 4`

### Action Timing Settings

#### `SupplyCenterActionDelay` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Delay for supply center actions. Higher values create slower supply center operations. Lower values create faster supply center operations
- **Default**: `0`
- **Example**: `SupplyCenterActionDelay = 25`

#### `SupplyWarehouseActionDelay` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Delay for supply warehouse actions. Higher values create slower warehouse operations. Lower values create faster warehouse operations
- **Default**: `0`
- **Example**: `SupplyWarehouseActionDelay = 25`

#### `SupplyWarehouseScanDistance` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Distance to scan for supply warehouses. Higher values scan for warehouses at greater distances. Lower values scan for warehouses at closer distances
- **Default**: `0.0`
- **Example**: `SupplyWarehouseScanDistance = 100.0`

### Audio Settings

#### `SuppliesDepletedVoice` *(v1.04)*
- **Type**: `AudioEventRTS`
- **Description**: Voice message to play when supplies are depleted. When set, plays specified voice message. When empty, no voice message is played
- **Default**: `""`
- **Example**: `SuppliesDepletedVoice = SuppliesDepletedVoice`

## Examples

### Basic Supply Truck
```ini
Behavior = SupplyTruckAIUpdate ModuleTag_AI01
  MaxBoxes = 4
  SupplyCenterActionDelay = 25
  SupplyWarehouseActionDelay = 25
End
```

### Advanced Supply Truck
```ini
Behavior = SupplyTruckAIUpdate ModuleTag_03
 MaxBoxes                = 8
  SupplyCenterActionDelay = 3500
  SupplyWarehouseActionDelay = 1500 ; ms per box (many small transactions)
End
```

### Supply Truck with Scan Distance
```ini
Behavior = SupplyTruckAIUpdate ModuleTag_03
  MaxBoxes = 4
  SupplyCenterActionDelay = 400     ; ms for whole thing (one transaction)
  SupplyWarehouseActionDelay = 1000 ; ms per box (many small transactions)
End
```

## Template

```ini
Behavior = SupplyTruckAIUpdate ModuleTag_XX
  ; Supply Capacity Settings
  MaxBoxes = 0                        ; // maximum number of supply boxes *(v1.04)*
  
  ; Action Timing Settings
  SupplyCenterActionDelay = 0         ; // delay for supply center actions *(v1.04)*
  SupplyWarehouseActionDelay = 0      ; // delay for supply warehouse actions *(v1.04)*
  SupplyWarehouseScanDistance = 0.0   ; // distance to scan for supply warehouses *(v1.04)*
  
  ; Audio Settings
  SuppliesDepletedVoice =             ; // voice message when supplies depleted *(v1.04)*
End
```

## Notes

- SupplyTruckAIUpdate provides sophisticated AI-driven supply operations and resource transport
- The update manages supply capacity, action timing, and warehouse coordination
- Supply operations provide essential resource management and logistics capabilities
- AI behavior creates autonomous supply truck operations for efficient resource transport
- This update is commonly used by supply truck units, logistics vehicles, and resource transport units
- Supply coordination ensures efficient resource management and distribution

## Source Files

**Base Class:** [`AIUpdateInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h), [`SupplyTruckAIInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyTruckAIUpdate.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyTruckAIUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyTruckAIUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/SupplyTruckAIUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/SupplyTruckAIUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet