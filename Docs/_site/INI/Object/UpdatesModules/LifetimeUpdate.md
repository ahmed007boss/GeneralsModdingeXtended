# LifetimeUpdate

LifetimeUpdate provides lifetime management functionality for objects with limited lifespans.

## Overview

The `LifetimeUpdate` class manages lifetime mechanics for objects that have limited lifespans and need to be destroyed or managed after a certain time period. It provides random lifetime ranges, automatic destruction, and sleep optimization to efficiently manage temporary objects. This update is commonly used by projectiles, effects, temporary objects, and any entity that should exist for a specific duration before being removed.

## Usage

Used by objects that have limited lifespans and need to be managed or destroyed after a certain time. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Object lifetime is limited by minimum and maximum lifetime parameters
- Destruction occurs automatically when lifetime expires
- Lifetime ranges provide randomization for varied object lifespans
- Sleep optimization reduces CPU usage for long-lived objects

**Conditions**:
- LifetimeUpdate automatically destroys objects when their lifetime expires
- The update uses random lifetime ranges to create varied object lifespans
- Sleep optimization reduces update frequency for objects with long lifetimes
- Lifetime can be dynamically adjusted during runtime
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own lifetime settings

**Dependencies**:
- Uses object destruction system for lifetime expiration
- Integrates with update system for sleep optimization

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Lifetime Settings](#lifetime-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Lifetime Settings

#### `MinLifetime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Minimum lifetime duration for the object. Higher values ensure longer minimum lifespans. Lower values allow shorter minimum lifespans
- **Default**: `0`
- **Example**: `MinLifetime = 3800`

#### `MaxLifetime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Maximum lifetime duration for the object. Higher values allow longer maximum lifespans. Lower values limit maximum lifespans
- **Default**: `0`
- **Example**: `MaxLifetime = 3800`

## Examples

### Fixed Lifetime Object
```ini
Behavior = LifetimeUpdate ModuleTag_04
  MinLifetime = 3800
  MaxLifetime = 3800
End
```

### Long-Lived Object
```ini
Behavior = LifetimeUpdate ModuleTag_10
  MinLifetime = 9000   ; min lifetime in msec
  MaxLifetime = 9000 ; max lifetime in msec
End
```

### Short-Lived Effect
```ini
Behavior = LifetimeUpdate ModuleTag_09
    MinLifetime = 1000
    MaxLifetime = 1000
End
```

## Template

```ini
Behavior = LifetimeUpdate ModuleTag_XX
  MinLifetime = 0                      ; // minimum lifetime in milliseconds *(v1.04)*
  MaxLifetime = 0                      ; // maximum lifetime in milliseconds *(v1.04)*
End
```

## Notes

- LifetimeUpdate provides efficient lifetime management for temporary objects
- The update automatically destroys objects when their lifetime expires
- Random lifetime ranges create varied object lifespans for more natural behavior
- Sleep optimization reduces CPU usage by minimizing update frequency for long-lived objects
- This update is commonly used by projectiles, effects, temporary buildings, and environmental objects
- Lifetime parameters can be set to create fixed or variable object lifespans

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/LifetimeUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/LifetimeUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/LifetimeUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/LifetimeUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet