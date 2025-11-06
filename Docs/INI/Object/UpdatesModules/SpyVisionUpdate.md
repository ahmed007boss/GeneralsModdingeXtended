# SpyVisionUpdate

SpyVisionUpdate provides spy vision functionality for objects that can provide spy vision or enhanced visibility.

## Overview

The `SpyVisionUpdate` class manages spy vision operations for objects that can provide spy vision, enhanced visibility, or stealth detection capabilities. It handles spy vision activation, duration management, and enhanced visibility coordination. This update is commonly used by spy units, reconnaissance units, and objects that provide enhanced visibility capabilities.

## Usage

Used by objects that can provide spy vision, enhanced visibility, or stealth detection capabilities. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Spy vision operations are limited by upgrade requirements and duration parameters
- Spy vision activation depends on proper upgrade system integration
- Duration management is controlled by self-powered duration parameters
- Spy vision effectiveness varies based on upgrade capabilities

**Conditions**:
- SpyVisionUpdate manages spy vision activation, duration, and enhanced visibility
- The update handles spy vision operations and upgrade system integration
- Spy vision provides tactical advantages for reconnaissance and stealth detection
- Duration management creates realistic spy vision operational periods
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own spy vision parameters

**Dependencies**:
- Uses upgrade system for spy vision activation
- Integrates with vision system for enhanced visibility
- Uses timer system for duration management

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Upgrade Settings](#upgrade-settings)
  - [Duration Settings](#duration-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Upgrade Settings

#### `NeedsUpgrade` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether spy vision requires an upgrade to activate. When true, upgrade is required. When false, no upgrade is required
- **Default**: `No`
- **Example**: `NeedsUpgrade = Yes`

#### `SelfPowered` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether spy vision is self-powered and turns on/off automatically. When true, self-powered operation. When false, manual control required
- **Default**: `No`
- **Example**: `SelfPowered = Yes`

### Duration Settings

#### `SelfPoweredDuration` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Duration of self-powered spy vision operation. Higher values create longer operation periods. Lower values create shorter operation periods
- **Default**: `0`
- **Example**: `SelfPoweredDuration = 30000`

## Examples

### Basic Spy Vision
```ini
Behavior         = SpyVisionUpdate ModuleTag_08
  NeedsUpgrade  = Yes
  SelfPowered   = Yes         ; No SpecialPower module, turns self on and off on timers
  SelfPoweredDuration = 30000
End
```

### Short Duration Spy Vision
```ini
Behavior         = SpyVisionUpdate ModuleTag_15
  NeedsUpgrade  = Yes
  SelfPowered   = Yes        ; No SpecialPower module, turns self on and off on timers (No timers means always on)
  SelfPoweredDuration = 3000
End
```

## Template

```ini
Behavior = SpyVisionUpdate ModuleTag_XX
  ; Upgrade Settings
  NeedsUpgrade = No                      ; // whether spy vision requires upgrade *(v1.04)*
  SelfPowered = No                       ; // whether spy vision is self-powered *(v1.04)*
  
  ; Duration Settings
  SelfPoweredDuration = 0                ; // duration of self-powered operation *(v1.04)*
End
```

## Notes

- SpyVisionUpdate provides spy vision and enhanced visibility capabilities
- The update manages spy vision activation, duration, and upgrade system integration
- Spy vision provides tactical advantages for reconnaissance and stealth detection
- Duration management creates realistic spy vision operational periods
- This update is commonly used by spy units, reconnaissance units, and enhanced visibility objects
- Spy vision coordination ensures efficient reconnaissance and stealth detection capabilities

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h), [`UpgradeMux`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpyVisionUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpyVisionUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/SpyVisionUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/SpyVisionUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet