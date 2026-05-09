# PilotFindVehicleUpdate

PilotFindVehicleUpdate provides pilot find vehicle functionality for objects that can find and enter vehicles.

## Overview

The `PilotFindVehicleUpdate` class manages pilot behavior for objects that need to find and enter nearby vehicles. It handles scanning for available vehicles, evaluating vehicle suitability, and coordinating pilot entry into vehicles. This update is commonly used by pilots, crew members, and other units that can operate vehicles or enter them as passengers.

## Usage

Used by objects that can find and enter vehicles, such as pilots and crew members. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Vehicle finding is limited by scan range and frequency parameters
- Vehicle entry is controlled by minimum health requirements
- Scanning behavior depends on available vehicles and their status
- Pilot behavior is limited by vehicle availability and accessibility

**Conditions**:
- PilotFindVehicleUpdate continuously scans for nearby vehicles
- The update evaluates vehicle suitability based on health and other criteria
- Pilot entry is coordinated with vehicle systems and crew management
- Scanning frequency and range control pilot behavior efficiency
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own scanning parameters

**Dependencies**:
- Requires vehicle system integration for pilot entry
- Uses scanning system for vehicle detection
- Integrates with crew management system

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Scan Settings](#scan-settings)
  - [Vehicle Requirements](#vehicle-requirements)
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
- **Description**: How often the pilot scans for nearby vehicles. Higher values reduce scan frequency but improve performance. Lower values provide more frequent scanning
- **Default**: `0`
- **Example**: `ScanRate = 1000`

#### `ScanRange` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Maximum distance at which the pilot can detect vehicles. Higher values allow detection of vehicles farther away. Lower values limit detection to nearby vehicles
- **Default**: `0.0`
- **Example**: `ScanRange = 100.0`

### Vehicle Requirements

#### `MinHealth` *(v1.04)*
- **Type**: `Real` (percentage)
- **Description**: Minimum health percentage required for pilot to enter a vehicle. Higher values require healthier vehicles. Lower values allow entry into more damaged vehicles
- **Default**: `0.0`
- **Example**: `MinHealth = 50.0`

## Examples

### Basic Pilot
```ini
Behavior = PilotFindVehicleUpdate ModuleTag_04
  ScanRate = 1000
  ScanRange = 100.0
  MinHealth = 50.0
End
```

### Aggressive Pilot
```ini
Behavior = PilotFindVehicleUpdate ModuleTag_05
  ScanRate = 500
  ScanRange = 150.0
  MinHealth = 25.0
End
```

### Selective Pilot
```ini
Behavior = PilotFindVehicleUpdate ModuleTag_06
  ScanRate = 2000
  ScanRange = 75.0
  MinHealth = 75.0
End
```

## Template

```ini
Behavior = PilotFindVehicleUpdate ModuleTag_XX
  ; Scan Settings
  ScanRate = 0                          ; // how often to scan for vehicles *(v1.04)*
  ScanRange = 0.0                       ; // maximum detection range *(v1.04)*
  
  ; Vehicle Requirements
  MinHealth = 0.0                       ; // minimum vehicle health required *(v1.04)*
End
```

## Notes

- PilotFindVehicleUpdate provides intelligent vehicle finding and entry mechanics
- The update continuously scans for suitable vehicles within specified range
- Health requirements ensure pilots enter vehicles in good condition
- Scanning parameters control pilot behavior efficiency and responsiveness
- This update is commonly used by pilots, crew members, and vehicle operators
- Vehicle finding creates realistic pilot behavior and crew management

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/PilotFindVehicleUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/PilotFindVehicleUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/PilotFindVehicleUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/PilotFindVehicleUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet