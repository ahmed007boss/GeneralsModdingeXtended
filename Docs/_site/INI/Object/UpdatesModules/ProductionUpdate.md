# ProductionUpdate

ProductionUpdate provides production functionality for objects that can produce other objects or units.

## Overview

The `ProductionUpdate` class manages production operations for buildings and facilities that can produce units, structures, or other objects. It handles production queues, door animations, construction completion sequences, and quantity modifiers for enhanced production capabilities. This update is commonly used by production buildings, factories, barracks, and any facility that produces units or objects.

## Usage

Used by production buildings and facilities that need to manage unit production, queues, and production mechanics. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Production operations are limited by queue entries and door animation parameters
- Construction completion is controlled by specified duration parameters
- Quantity modifiers are limited by available production capacity
- Disabled types processing depends on proper type classification

**Conditions**:
- ProductionUpdate manages complete production lifecycle from queue to completion
- The update handles door animations for production facility operations
- Production queues control unit production ordering and management
- Construction completion sequences provide visual feedback for production
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own production parameters

**Dependencies**:
- Uses production system for unit creation and management
- Integrates with animation system for door operations
- Uses queue system for production ordering

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Production Settings](#production-settings)
  - [Door Animation Settings](#door-animation-settings)
  - [Construction Settings](#construction-settings)
  - [Modifier Settings](#modifier-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Production Settings

#### `MaxQueueEntries` *(v1.04)*
- **Type**: `Int`
- **Description**: Maximum number of production queue entries allowed. Higher values allow longer production queues. Lower values limit queue length and prevent multiple simultaneous productions
- **Default**: `0`
- **Example**: `MaxQueueEntries = 1`

### Door Animation Settings

#### `NumDoorAnimations` *(v1.04)*
- **Type**: `Int`
- **Description**: Number of door animations to play during production. Higher values create more complex door sequences. Lower values create simpler door operations
- **Default**: `0`
- **Example**: `NumDoorAnimations = 1`

#### `DoorOpeningTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time required to open doors for production. Higher values create slower door opening. Lower values create faster door opening
- **Default**: `0`
- **Example**: `DoorOpeningTime = 1500`

#### `DoorWaitOpenTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time to keep doors open after production completion. Higher values keep doors open longer. Lower values close doors sooner
- **Default**: `0`
- **Example**: `DoorWaitOpenTime = 3000`

#### `DoorCloseTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time required to close doors after production. Higher values create slower door closing. Lower values create faster door closing
- **Default**: `0`
- **Example**: `DoorCloseTime = 1000`

### Construction Settings

#### `ConstructionCompleteDuration` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Duration of construction completion sequence. Higher values create longer completion sequences. Lower values create shorter completion sequences
- **Default**: `0`
- **Example**: `ConstructionCompleteDuration = 2000`

### Modifier Settings

#### `QuantityModifier` *(v1.04)*
- **Type**: `QuantityModifier` (vector)
- **Description**: Modifiers that affect production quantities and capabilities. When set, applies specified quantity modifiers. When empty, no quantity modifiers are applied
- **Default**: `""`
- **Example**: `QuantityModifier = ProductionSpeed:1.5`

#### `DisabledTypesToProcess` *(v1.04)*
- **Type**: `DisabledMaskType` (bit flags)
- **Description**: Object types that are disabled from processing during production. When set, specified types are excluded. When empty, no types are disabled
- **Default**: `0`
- **Example**: `DisabledTypesToProcess = UPGRADE`

## Examples

### Basic Production Building
```ini
Behavior = ProductionUpdate ModuleTag_Production01
  NumDoorAnimations = 1
  DoorOpeningTime = 1500
  DoorWaitOpenTime = 3000
End
```

### Advanced Production Building
```ini
Behavior = ProductionUpdate ModuleTag_12
  NumDoorAnimations            = 2
  DoorOpeningTime              = 2000  ;in mSeconds
  DoorWaitOpenTime             = 3000  ;in mSeconds
End
```

### Single Queue Production
```ini
Behavior = ProductionUpdate ModuleTag_09
  MaxQueueEntries = 1; So you can't build multiple upgrades in the same frame
End
```

## Template

```ini
Behavior = ProductionUpdate ModuleTag_XX
  ; Production Settings
  MaxQueueEntries = 0                   ; // maximum production queue entries *(v1.04)*
  
  ; Door Animation Settings
  NumDoorAnimations = 0                 ; // number of door animations *(v1.04)*
  DoorOpeningTime = 0                   ; // time to open doors *(v1.04)*
  DoorWaitOpenTime = 0                  ; // time to keep doors open *(v1.04)*
  DoorCloseTime = 0                     ; // time to close doors *(v1.04)*
  
  ; Construction Settings
  ConstructionCompleteDuration = 0      ; // construction completion duration *(v1.04)*
  
  ; Modifier Settings
  QuantityModifier =                    ; // production quantity modifiers *(v1.04)*
  DisabledTypesToProcess =              ; // disabled object types *(v1.04)*
End
```

## Notes

- ProductionUpdate provides comprehensive production management for buildings and facilities
- The update handles complete production lifecycle including queue management and door animations
- Door animation sequences create realistic production facility operations
- Quantity modifiers enhance production capabilities and customization
- This update is commonly used by production buildings, factories, barracks, and manufacturing facilities
- Construction completion sequences provide visual feedback for production operations

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ProductionUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ProductionUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/ProductionUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/ProductionUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet