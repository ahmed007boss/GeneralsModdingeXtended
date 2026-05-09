# HijackerUpdate

HijackerUpdate provides hijacking functionality for objects that can hijack other objects.

## Overview

The `HijackerUpdate` class manages hijacking mechanics that allow objects to take control of other vehicles, buildings, or systems. It handles the hijacking process including target selection, attachment to target objects, parachute deployment for airborne hijacking, and coordination with the hijacking unit's behavior. This update is commonly used by hijacker units and special forces that can capture enemy equipment.

## Usage

Used by objects that can hijack other vehicles, buildings, or systems. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Hijacking is limited by target selection and attachment parameters
- Parachute deployment requires proper parachute templates
- Target attachment depends on bone structure and positioning
- Hijacking success depends on target vulnerability and range

**Conditions**:
- HijackerUpdate manages the hijacking process from target selection to completion
- The update handles attachment to target objects using specified bone attachments
- Parachute deployment is used for airborne hijacking operations
- Target coordination ensures proper hijacking behavior and control transfer
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own targets

**Dependencies**:
- Requires target objects with hijackable properties
- Uses parachute system for airborne hijacking
- Integrates with attachment system for bone-based connections

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Target Settings](#target-settings)
  - [Parachute Settings](#parachute-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Target Settings

#### `AttachToTargetBone` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Bone name on target object where the hijacker attaches. When set, hijacker attaches to this specific bone. When empty, uses default attachment point
- **Default**: `""`
- **Example**: `AttachToTargetBone = "HijackerPoint"`

### Parachute Settings

#### `ParachuteName` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Name of parachute template to deploy during airborne hijacking. When set, deploys the specified parachute. When empty, no parachute is used
- **Default**: `""`
- **Example**: `ParachuteName = "AmericaParachute"`

## Examples

### Basic Hijacker
```ini
Behavior = HijackerUpdate ModuleTag_04
  ParachuteName = AmericaParachute
End
```

### Hijacker with Target Attachment
```ini
Behavior = HijackerUpdate ModuleTag_03
  ParachuteName = AmericaParachute
  AttachToTargetBone = "HijackerPoint"
End
```

### Ground-Based Hijacker
```ini
Behavior = HijackerUpdate ModuleTag_05
  AttachToTargetBone = "EntryPoint"
End
```

## Template

```ini
Behavior = HijackerUpdate ModuleTag_XX
  ; Target Settings
  AttachToTargetBone =                  ; // bone name for target attachment *(v1.04)*
  
  ; Parachute Settings
  ParachuteName =                       ; // parachute template for airborne hijacking *(v1.04)*
End
```

## Notes

- HijackerUpdate provides comprehensive hijacking mechanics for capturing enemy equipment
- The update handles both ground-based and airborne hijacking operations
- Target attachment uses bone-based positioning for realistic hijacker placement
- Parachute deployment enables dramatic airborne hijacking scenarios
- This update is commonly used by hijacker units, special forces, and infiltration units
- Hijacking success depends on proper target selection and positioning

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/HijackerUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/HijackerUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/HijackerUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/HijackerUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet