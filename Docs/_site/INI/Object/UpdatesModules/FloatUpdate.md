# FloatUpdate

FloatUpdate provides floating functionality for objects that can float on water or other surfaces.

## Overview

The `FloatUpdate` class manages floating mechanics for objects that need to maintain buoyancy on water surfaces or have floating behavior. It provides simple enable/disable functionality for floating behavior, allowing objects to be lifted by water or other floating systems, or to remain stationary while still being affected by floating physics like swaying motions.

## Usage

Used by objects that need to float on water, maintain buoyancy, or have floating mechanics. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Floating behavior is controlled by a simple enabled/disabled state
- Objects must be positioned over water or floating surfaces to be affected
- Floating physics depend on the game's water and physics systems

**Conditions**:
- FloatUpdate provides basic floating enable/disable functionality
- When enabled, objects can be lifted by water and floating systems
- When disabled, objects remain stationary but may still sway like buoys
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own enabled state

**Dependencies**:
- Requires water or floating surface systems to function
- Uses physics system for floating calculations

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Floating Settings](#floating-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Floating Settings

#### `Enabled` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether the object can be lifted by floating systems. When true, the object can be raised by water and floating mechanics. When false, the object remains stationary but may still sway like a buoy
- **Default**: `No`
- **Example**: `Enabled = Yes`

## Examples

### Disabled Floating (Buoy Effect)
```ini
Behavior = FloatUpdate UpdateTag_01
  Enabled = No ; 'no' because we dont want to be lifted by this update, just swayed around like a buoy
End
```

### Enabled Floating
```ini
Behavior = FloatUpdate UpdateTag_02
  Enabled = Yes
End
```

## Template

```ini
Behavior = FloatUpdate ModuleTag_XX
  Enabled = No                       ; // whether object can be lifted by floating systems *(v1.04)*
End
```

## Notes

- FloatUpdate provides simple floating enable/disable functionality
- When disabled, objects act like buoys - they sway but aren't lifted by water
- When enabled, objects can be raised and lowered by water and floating systems
- This update is commonly used by boats, floating objects, and water-based units
- The update integrates with the game's water and physics systems for realistic floating behavior

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FloatUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FloatUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/FloatUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/FloatUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet