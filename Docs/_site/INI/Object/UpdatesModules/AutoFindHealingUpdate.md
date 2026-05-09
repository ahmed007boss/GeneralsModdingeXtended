# AutoFindHealingUpdate

AutoFindHealingUpdate provides automatic healing search functionality for objects that can find and move to healing facilities when damaged.

## Overview

The `AutoFindHealingUpdate` class manages automatic healing search systems that allow units to find and move to healing facilities when their health falls below certain thresholds. It scans for nearby healing pads and commands the unit to move to the closest one for healing. The update only works for AI-controlled units and requires the unit to be idle to seek healing.

## Usage

Used by AI-controlled units that need to automatically find and move to healing facilities when damaged. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Only works for AI-controlled units (not human players)
- Units must be idle to seek healing (busy units won't interrupt their current task)
- Only searches for objects with HEAL_PAD KindOf flag
- Healing search is limited by the specified scan range

**Conditions**:
- AutoFindHealingUpdate scans for healing facilities within the specified range
- The update uses health percentage thresholds to determine when to seek healing
- Units must be idle and below the NeverHeal threshold to actively search for healing
- Units below the AlwaysHeal threshold will seek healing even if busy
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own scan rates and thresholds

**Dependencies**:
- Requires an object with AI system (AIUpdateInterface) to function
- Requires an object with health system (BodyModuleInterface) to check health levels
- Objects with HEAL_PAD KindOf flag can be targeted for healing

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Scan Settings](#scan-settings)
  - [Health Thresholds](#health-thresholds)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Scan Settings

#### `ScanRate` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time interval between healing facility scans. Lower values provide more frequent scanning but use more CPU resources. Higher values reduce CPU usage but may delay healing detection
- **Default**: `0` (scan every frame)
- **Example**: `ScanRate = 1000`

#### `ScanRange` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Maximum distance to search for healing facilities. Higher values allow finding healing facilities farther away. Lower values limit search to nearby facilities only
- **Default**: `0.0` (no range limit)
- **Example**: `ScanRange = 300.0`

### Health Thresholds

#### `NeverHeal` *(v1.04)*
- **Type**: `Real` (percentage)
- **Description**: Health percentage above which the unit will never seek healing. Higher values (closer to 1.0) make units more reluctant to seek healing. Lower values allow units to seek healing at higher health levels
- **Default**: `0.95` (95% health)
- **Example**: `NeverHeal = 0.85`

#### `AlwaysHeal` *(v1.04)*
- **Type**: `Real` (percentage)
- **Description**: Health percentage below which the unit will always seek healing, even if busy. Higher values make units seek healing sooner when critically damaged. Lower values require more severe damage before seeking healing
- **Default**: `0.25` (25% health)
- **Example**: `AlwaysHeal = 0.25`

## Examples

### Infantry Auto Healing
```ini
Behavior = AutoFindHealingUpdate ModuleTag_05
  ScanRate = 1000
  ScanRange = 300
  NeverHeal = 0.85
  AlwaysHeal = 0.25
End
```

### Vehicle Auto Healing
```ini
Behavior = AutoFindHealingUpdate ModuleTag_04
  ScanRate = 2000
  ScanRange = 500
  NeverHeal = 0.90
  AlwaysHeal = 0.30
End
```

### Aggressive Healing Search
```ini
Behavior = AutoFindHealingUpdate ModuleTag_06
  ScanRate = 500
  ScanRange = 400
  NeverHeal = 0.80
  AlwaysHeal = 0.40
End
```

## Template

```ini
Behavior = AutoFindHealingUpdate ModuleTag_XX
  ScanRate = 1000               ; // milliseconds between healing scans *(v1.04)*
  ScanRange = 300.0             ; // maximum distance to search for healing *(v1.04)*
  NeverHeal = 0.95              ; // health percentage above which never seek healing *(v1.04)*
  AlwaysHeal = 0.25             ; // health percentage below which always seek healing *(v1.04)*
End
```

## Notes

- AutoFindHealingUpdate only works for AI-controlled units, not human players
- Units must be idle to seek healing unless their health is below the AlwaysHeal threshold
- The update searches for objects with HEAL_PAD KindOf flag within the specified range
- Health thresholds are expressed as percentages (0.0 to 1.0) of maximum health
- The update integrates with the AI system to command units to move to healing facilities
- Scan rate affects CPU usage - more frequent scanning uses more resources

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AutoFindHealingUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AutoFindHealingUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/AutoFindHealingUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/AutoFindHealingUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- [Reviews (0)](#modder-reviews)
