# ProneUpdate

ProneUpdate provides prone functionality for objects that can go prone or enter prone positions.

## Overview

The `ProneUpdate` class manages prone behavior for objects that can go prone for stealth, protection, or tactical positioning. It handles prone state transitions, damage-to-frames ratio calculations, and prone positioning mechanics. This update is commonly used by infantry units, snipers, and other units that can go prone for tactical advantages.

## Usage

Used by objects that can go prone for stealth, protection, or tactical positioning. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Prone behavior is limited by damage-to-frames ratio parameters
- Prone positioning depends on terrain and environmental conditions
- Prone state transitions are controlled by specified ratio calculations
- Prone effectiveness varies based on unit type and tactical situation

**Conditions**:
- ProneUpdate manages prone state transitions and positioning
- The update handles damage-to-frames ratio calculations for prone behavior
- Prone positioning provides tactical advantages and protection
- Prone state affects unit visibility and combat effectiveness
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own prone parameters

**Dependencies**:
- Uses positioning system for prone placement
- Integrates with combat system for prone combat mechanics
- Uses animation system for prone state transitions

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Combat Settings](#combat-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Combat Settings

#### `DamageToFramesRatio` *(v1.04)*
- **Type**: `Real`
- **Description**: Ratio of damage to frames used for prone behavior calculations. Higher values create more damage-resistant prone behavior. Lower values create less damage-resistant prone behavior
- **Default**: `0.0`
- **Example**: `DamageToFramesRatio = 0.5`

## Examples

*No examples of ProneUpdate were found in the INI files (only commented out examples).*

## Template

```ini
Behavior = ProneUpdate ModuleTag_XX
  ; Combat Settings
  DamageToFramesRatio = 0.0              ; // damage to frames ratio for prone behavior *(v1.04)*
End
```

## Notes

- ProneUpdate provides tactical prone positioning and behavior mechanics
- The update manages prone state transitions and damage calculations
- Damage-to-frames ratio affects prone unit effectiveness and survivability
- Prone positioning provides tactical advantages in combat situations
- This update is commonly used by infantry units, snipers, and tactical units
- Prone behavior creates realistic tactical positioning and stealth mechanics

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ProneUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ProneUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/ProneUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/ProneUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet