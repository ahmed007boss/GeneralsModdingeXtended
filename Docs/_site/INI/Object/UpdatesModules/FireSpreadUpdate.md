# FireSpreadUpdate

FireSpreadUpdate provides fire spread functionality for objects that can spread fire or be affected by fire.

## Overview

The `FireSpreadUpdate` class manages fire spreading mechanics that allow objects to create fire effects that can spread to nearby flammable objects. It creates ember effects at random intervals and attempts to spread fire to other objects within a specified range. This update is commonly used by burning objects, fire-based weapons, and environmental fire effects to create realistic fire propagation systems.

## Usage

Used by objects that can spread fire to nearby objects or are affected by fire spread mechanics. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Fire spread is limited by the specified range and delay parameters
- Only spreads to objects that are flammable or can catch fire
- Spread attempts are limited by random delay intervals
- Requires proper ember object creation lists to function

**Conditions**:
- FireSpreadUpdate creates ember effects at random intervals within the specified range
- The update attempts to spread fire to nearby flammable objects
- Spread timing is controlled by minimum and maximum delay parameters
- Fire spread range determines how far embers can travel
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own spread patterns

**Dependencies**:
- Requires Object Creation Lists (OCL) for ember effects
- Needs flammable objects nearby to spread fire to
- Uses random timing for realistic fire spread behavior

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Fire Spread Settings](#fire-spread-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Fire Spread Settings

#### `OCLEmbers` *(v1.04)*
- **Type**: `ObjectCreationList`
- **Description**: Object Creation List for ember effects that spread fire. When set, creates ember objects that can ignite nearby flammable objects. When empty, no fire spreading occurs
- **Default**: `NULL`
- **Example**: `OCLEmbers = OCL_BurningEmbers`

#### `MinSpreadDelay` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Minimum delay between fire spread attempts. Higher values reduce fire spread frequency. Lower values allow more frequent fire spreading
- **Default**: `1000` (1 second)
- **Example**: `MinSpreadDelay = 500`

#### `MaxSpreadDelay` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Maximum delay between fire spread attempts. Higher values create more varied fire spread timing. Lower values create more consistent fire spreading
- **Default**: `2000` (2 seconds)
- **Example**: `MaxSpreadDelay = 3000`

#### `SpreadTryRange` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Maximum range for fire spread attempts. Higher values allow fire to spread farther. Lower values limit fire spread to nearby objects only
- **Default**: `100.0`
- **Example**: `SpreadTryRange = 150.0`

## Examples

### Basic Fire Spread
```ini
Behavior = FireSpreadUpdate ModuleTag_06
  OCLEmbers = OCL_BurningEmbers
  MinSpreadDelay = 1000
  MaxSpreadDelay = 2000
End
```

### Rapid Fire Spread
```ini
Behavior = FireSpreadUpdate ModuleTag_07
  OCLEmbers = OCL_BurningEmbers
  MinSpreadDelay = 500
  MaxSpreadDelay = 1000
  SpreadTryRange = 200.0
End
```

### Slow Fire Spread
```ini
Behavior = FireSpreadUpdate ModuleTag_08
  OCLEmbers = OCL_BurningEmbers
  MinSpreadDelay = 2000
  MaxSpreadDelay = 4000
  SpreadTryRange = 75.0
End
```

## Template

```ini
Behavior = FireSpreadUpdate ModuleTag_XX
  OCLEmbers = OCL_BurningEmbers     ; // object creation list for ember effects *(v1.04)*
  MinSpreadDelay = 1000             ; // minimum delay between spread attempts in milliseconds *(v1.04)*
  MaxSpreadDelay = 2000             ; // maximum delay between spread attempts in milliseconds *(v1.04)*
  SpreadTryRange = 100.0            ; // maximum range for fire spread attempts *(v1.04)*
End
```

## Notes

- FireSpreadUpdate creates realistic fire propagation by spawning ember effects at random intervals
- The update uses random timing between minimum and maximum delays for natural fire spread behavior
- Fire can only spread to objects that are flammable or have fire susceptibility
- Ember effects are created using Object Creation Lists (OCL) for visual and functional fire spreading
- This update is commonly used by burning buildings, fire weapons, and environmental fire effects
- Fire spread range and timing should be balanced for realistic fire behavior

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FireSpreadUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FireSpreadUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/FireSpreadUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/FireSpreadUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet