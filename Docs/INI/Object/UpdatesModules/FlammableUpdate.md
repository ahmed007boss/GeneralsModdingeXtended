# FlammableUpdate

FlammableUpdate provides flammability functionality for objects that can catch fire or be affected by fire.

## Overview

The `FlammableUpdate` class manages fire susceptibility and burning mechanics for objects that can catch fire, spread fire, or be affected by fire damage and effects. It handles the transition from normal to aflame to burned states, applies fire damage over time, and manages fire-related visual and audio effects. This update is commonly used by buildings, vehicles, and objects that need realistic fire behavior.

## Usage

Used by objects that can catch fire, spread fire, or are affected by fire damage and effects. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Fire damage is limited by flame damage limits and expiration delays
- Burning states transition through normal → aflame → burned progression
- Fire susceptibility depends on object type and current state
- Damage amounts and timing are controlled by specified parameters

**Conditions**:
- FlammableUpdate manages three fire states: normal, aflame, and burned
- Objects can be ignited by fire damage or environmental fire effects
- Fire damage is applied continuously while aflame
- State transitions occur based on timing and damage thresholds
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own fire states

**Dependencies**:
- Requires damage system integration for fire damage application
- Uses audio system for burning sound effects
- Integrates with fire spread systems for environmental ignition

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Fire State Settings](#fire-state-settings)
  - [Damage Settings](#damage-settings)
  - [Audio Settings](#audio-settings)
  - [Fire Damage Limits](#fire-damage-limits)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Fire State Settings

#### `BurnedDelay` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time delay before object becomes permanently burned. Higher values allow longer aflame periods before burning. At 0, objects never become permanently burned
- **Default**: `0` (never burned)
- **Example**: `BurnedDelay = 10000`

#### `AflameDuration` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Duration that object stays aflame before returning to normal or becoming burned. Higher values create longer burning periods. Lower values create shorter burning periods
- **Default**: `5000` (5 seconds)
- **Example**: `AflameDuration = 8000`

### Damage Settings

#### `AflameDamageDelay` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time interval between fire damage applications while aflame. Higher values reduce fire damage frequency. At 0, no fire damage is applied
- **Default**: `500` (0.5 seconds)
- **Example**: `AflameDamageDelay = 1000`

#### `AflameDamageAmount` *(v1.04)*
- **Type**: `Int`
- **Description**: Amount of damage applied per fire damage cycle while aflame. Higher values cause more damage per cycle. Lower values cause less damage per cycle
- **Default**: `5`
- **Example**: `AflameDamageAmount = 10`

### Audio Settings

#### `BurningSoundName` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Sound effect to play continuously while object is aflame. When set, plays the specified sound loop. When empty, no burning sound is played
- **Default**: `""` (no sound)
- **Example**: `BurningSoundName = BuildingFireLoop`

### Fire Damage Limits

#### `FlameDamageLimit` *(v1.04)*
- **Type**: `Real`
- **Description**: Maximum total fire damage the object can take before becoming immune to further fire damage. Higher values allow more fire damage. Lower values limit fire damage exposure
- **Default**: `0.0` (no limit)
- **Example**: `FlameDamageLimit = 1000.0`

#### `FlameDamageExpiration` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time delay before fire damage limit resets, allowing object to take fire damage again. Higher values create longer immunity periods. At 0, fire damage limit never resets
- **Default**: `0` (never resets)
- **Example**: `FlameDamageExpiration = 30000`

## Examples

### Basic Flammable Object
```ini
Behavior = FlammableUpdate ModuleTag_Death01
  AflameDuration = 5000
  AflameDamageAmount = 5
  AflameDamageDelay = 500
End
```

### Detailed Flammable Object
```ini
Behavior = FlammableUpdate ModuleTag_06
  AflameDuration = 5000         ; If I catch fire, I'll burn for this long...
  AflameDamageAmount = 3       ; taking this much damage...
  AflameDamageDelay = 500       ; this often.
  BurningSoundName = BuildingFireLoop
  BurnedDelay = 15000
End
```

### Fire-Resistant Object
```ini
Behavior = FlammableUpdate ModuleTag_17
  AflameDuration = 3000
  AflameDamageAmount = 2
  AflameDamageDelay = 1000
  FlameDamageLimit = 500.0
  FlameDamageExpiration = 60000
End
```

## Template

```ini
Behavior = FlammableUpdate ModuleTag_XX
  ; Fire State Settings
  BurnedDelay = 0                    ; // delay before becoming permanently burned *(v1.04)*
  AflameDuration = 5000              ; // duration while aflame in milliseconds *(v1.04)*
  
  ; Damage Settings
  AflameDamageDelay = 500            ; // time between fire damage cycles *(v1.04)*
  AflameDamageAmount = 5             ; // damage per fire damage cycle *(v1.04)*
  
  ; Audio Settings
  BurningSoundName =                 ; // sound to play while aflame *(v1.04)*
  
  ; Fire Damage Limits
  FlameDamageLimit = 0.0             ; // maximum total fire damage *(v1.04)*
  FlameDamageExpiration = 0          ; // time before fire damage limit resets *(v1.04)*
End
```

## Notes

- FlammableUpdate manages realistic fire behavior with three distinct states: normal, aflame, and burned
- Objects transition through fire states based on damage and timing parameters
- Fire damage is applied continuously while aflame, creating realistic burning effects
- Burning sound effects provide audio feedback for fire state changes
- Fire damage limits prevent objects from taking infinite fire damage
- This update is commonly used by buildings, vehicles, and environmental objects
- Fire susceptibility can be controlled through damage limits and expiration timers

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h), [`DamageModuleInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DamageModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FlammableUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FlammableUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/FlammableUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/FlammableUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet