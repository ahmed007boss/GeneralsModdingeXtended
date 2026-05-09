# EjectPilotDie

EjectPilotDie creates pilot objects when aircraft or vehicles are destroyed, with different behavior for air vs ground ejections.

## Overview

The `EjectPilotDie` class manages pilot ejection when aircraft or vehicles are destroyed. It can create different objects depending on whether the vehicle is in the air or on the ground, and plays appropriate audio effects for pilot ejection. This behavior is commonly used for aircraft, helicopters, and other vehicles that have pilots that can be ejected.

## Usage

Used by aircraft and vehicles that need to eject pilots when destroyed, such as fighter jets, helicopters, and other pilot-operated vehicles. This is a **die module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- EjectPilotDie only triggers when the object actually dies
- Object creation is limited by the specified ObjectCreationList definitions
- Air vs ground ejection is determined by the object's altitude above terrain
- The behavior requires valid object template definitions to function
- Audio effects require proper voice and sound event definitions

**Conditions**:
- EjectPilotDie can create different objects for air vs ground ejections
- The behavior automatically determines ejection type based on object altitude
- Audio effects are played for both voice and sound ejection events
- The behavior integrates with the death system for conditional activation
- Created objects inherit the dying object's team and player ownership
- **Multiple instances behavior**: Multiple instances can exist with different conditions; all matching instances will eject their pilots simultaneously

**Dependencies**:
- Requires valid ObjectCreationList definitions to function correctly
- The behavior relies on the death system for activation timing
- Audio events require proper VoiceEject and SoundEject definitions in the object template

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Object Creation](#object-creation)
  - [Pilot Settings](#pilot-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

### Object Creation

#### `AirCreationList` *(v1.04)*
- **Type**: `ObjectCreationList` (see [ObjectCreationList documentation](../ObjectCreationList.md))
- **Description**: Object creation list used when the vehicle is in the air (significantly above terrain). When set, spawns the specified objects during air ejections. When NULL (default), no objects are created during air ejections
- **Default**: `NULL` (none)
- **Example**: `AirCreationList = ChinaInfantryPilot`

#### `GroundCreationList` *(v1.04)*
- **Type**: `ObjectCreationList` (see [ObjectCreationList documentation](../ObjectCreationList.md))
- **Description**: Object creation list used when the vehicle is on or near the ground. When set, spawns the specified objects during ground ejections. When NULL (default), no objects are created during ground ejections
- **Default**: `NULL` (none)
- **Example**: `GroundCreationList = ChinaInfantryPilot`

### Pilot Settings

#### `InvulnerableTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time duration that ejected pilots are invulnerable to damage. Higher values provide longer protection periods for ejected pilots, allowing them to escape safely. At 0 (default), ejected pilots have no invulnerability period
- **Default**: `0`
- **Example**: `InvulnerableTime = 5000`

## Examples

### Aircraft Pilot Ejection
```ini
Die = EjectPilotDie ModuleTag_PilotEject
  AirCreationList = USAInfantryPilot
  GroundCreationList = USAInfantryPilot
  InvulnerableTime = 3000
End
```

### Helicopter Pilot Ejection
```ini
Die = EjectPilotDie ModuleTag_HeliPilot
  AirCreationList = ChinaInfantryPilot
  GroundCreationList = ChinaInfantryPilot
  InvulnerableTime = 5000
End
```

### Different Air/Ground Ejections
```ini
Die = EjectPilotDie ModuleTag_DifferentEject
  AirCreationList = GLAInfantryPilotParachute
  GroundCreationList = GLAInfantryPilot
  InvulnerableTime = 2000
End
```

## Template

```ini
Die = EjectPilotDie ModuleTag_XX
  ; Object Creation
  AirCreationList =                   ; // object to create when in air *(v1.04)*
  GroundCreationList =                ; // object to create when on ground *(v1.04)*

  ; Pilot Settings
  InvulnerableTime = 0                ; // pilot invulnerability duration *(v1.04)*
End
```

## Notes

- EjectPilotDie can create different objects for air vs ground ejections
- The behavior automatically determines ejection type based on object altitude
- Audio effects are played for both voice and sound ejection events
- The behavior integrates with the death system for conditional activation
- Created objects inherit the dying object's team and player ownership
- Audio events require proper VoiceEject and SoundEject definitions in the object template

## Source Files

**Base Class:** [`DieModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/EjectPilotDie.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/EjectPilotDie.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Die/EjectPilotDie.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Die/EjectPilotDie.cpp)