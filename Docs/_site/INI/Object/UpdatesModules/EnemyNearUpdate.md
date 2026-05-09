# EnemyNearUpdate

EnemyNearUpdate provides enemy detection functionality for objects that can detect nearby enemies and respond accordingly.

## Overview

The `EnemyNearUpdate` class manages enemy detection systems that scan for nearby enemy units within a specified range. It provides real-time enemy detection capabilities that can trigger various responses when enemies are detected or when the area becomes clear. The update is commonly used by defensive structures, stealth detectors, and tactical systems that need to monitor their surroundings for threats.

## Usage

Used by objects that need to detect nearby enemies and respond to enemy presence or absence. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Enemy detection is limited to the object's line-of-sight and radar range
- Scan frequency is controlled by ScanDelayTime to manage performance
- Only detects enemies that are currently alive and within range

**Conditions**:
- EnemyNearUpdate continuously scans for enemies at regular intervals
- The update can trigger different behaviors when enemies are detected vs. when area is clear
- Detection works based on the object's radar and line-of-sight systems
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own scan timing

**Dependencies**:
- Requires radar or detection systems to identify enemy units
- Uses the game's line-of-sight and radar range calculations
- Integrates with AI systems for enemy classification

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Scan Settings](#scan-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Scan Settings

#### `ScanDelayTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time interval between enemy detection scans. Lower values provide more frequent scanning but use more CPU resources. Higher values reduce CPU usage but may delay enemy detection
- **Default**: `1000` (1 second)
- **Example**: `ScanDelayTime = 500`

## Examples

### Basic Enemy Detection
```ini
Behavior = EnemyNearUpdate ModuleTag_03
  ScanDelayTime = 1000
End
```

### Frequent Enemy Scanning
```ini
Behavior = EnemyNearUpdate ModuleTag_04
  ScanDelayTime = 500
End
```

### Infrequent Enemy Scanning
```ini
Behavior = EnemyNearUpdate ModuleTag_05
  ScanDelayTime = 2000
End
```

## Template

```ini
Behavior = EnemyNearUpdate ModuleTag_XX
  ScanDelayTime = 1000          ; // milliseconds between enemy detection scans *(v1.04)*
End
```

## Notes

- EnemyNearUpdate provides basic enemy detection functionality without additional parameters
- The update automatically uses the object's radar and line-of-sight systems for detection
- Scan frequency should be balanced between responsiveness and performance
- This update is commonly used by defensive structures and stealth detection systems
- Enemy detection results can be used to trigger other behaviors or special powers

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/EnemyNearUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/EnemyNearUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/EnemyNearUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/EnemyNearUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet