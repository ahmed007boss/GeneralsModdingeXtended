# RailedTransportDockUpdate

RailedTransportDockUpdate provides docking functionality specifically for railed transport systems.

## Overview

The `RailedTransportDockUpdate` class manages docking operations for railed transport units that need to dock with rail stations or other rail facilities. It handles rail-specific docking mechanics including pull/push operations, tolerance distances, and rail-based transport coordination. This update is commonly used by railed transport units, rail stations, and objects that need specialized rail docking functionality.

## Usage

Used by railed transport units that need to dock with rail stations or other rail facilities. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Rail docking operations are limited by pull/push duration parameters
- Tolerance distance controls docking precision and positioning
- Rail coordination depends on proper rail network integration
- Docking operations are controlled by rail-specific timing parameters

**Conditions**:
- RailedTransportDockUpdate manages rail-specific docking and transport operations
- The update handles pull/push operations for rail-based transport coordination
- Tolerance distance ensures proper rail alignment and positioning
- Rail docking creates realistic rail transport operations
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own rail parameters

**Dependencies**:
- Extends DockUpdate for base docking functionality
- Requires rail system integration for rail-based transport
- Uses dock interface for docking operations

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Rail Operations Settings](#rail-operations-settings)
  - [Positioning Settings](#positioning-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Rail Operations Settings

#### `PullInsideDuration` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time required to pull transport inside the rail facility. Higher values create slower pull operations. Lower values create faster pull operations
- **Default**: `0`
- **Example**: `PullInsideDuration = 4500`

#### `PushOutsideDuration` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time required to push transport outside the rail facility. Higher values create slower push operations. Lower values create faster push operations
- **Default**: `0`
- **Example**: `PushOutsideDuration = 4500`

### Positioning Settings

#### `ToleranceDistance` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Distance tolerance for rail docking operations. Higher values allow more positioning flexibility. Lower values require more precise positioning
- **Default**: `0.0`
- **Example**: `ToleranceDistance = 5.0`

## Examples

### Basic Rail Transport Dock
```ini
Behavior = RailedTransportDockUpdate ModuleTag_06
  NumberApproachPositions = 9
  PullInsideDuration      = 4500  ; in milliseconds
  PushOutsideDuration     = 4500  ; in milliseconds
End
```

## Template

```ini
Behavior = RailedTransportDockUpdate ModuleTag_XX
  ; Rail Operations Settings
  PullInsideDuration = 0                   ; // time to pull transport inside *(v1.04)*
  PushOutsideDuration = 0                  ; // time to push transport outside *(v1.04)*
  
  ; Positioning Settings
  ToleranceDistance = 0.0                  ; // distance tolerance for docking *(v1.04)*
End
```

## Notes

- RailedTransportDockUpdate extends DockUpdate with specialized rail transport docking mechanics
- The update provides rail-specific pull/push operations for transport coordination
- Tolerance distance ensures proper rail alignment and positioning accuracy
- This update is commonly used by railed transport units, rail stations, and rail-based facilities
- Rail docking operations create realistic rail transport system management

## Source Files

**Base Class:** [`DockUpdate`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DockUpdate.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RailedTransportDockUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RailedTransportDockUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/DockUpdate/RailedTransportDockUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/DockUpdate/RailedTransportDockUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet