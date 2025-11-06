# MissileLauncherBuildingUpdate

MissileLauncherBuildingUpdate provides missile launcher building functionality for structures that can launch missiles.

## Overview

The `MissileLauncherBuildingUpdate` class manages missile launcher building operations including door mechanisms, special power integration, and launch sequence coordination. It handles the opening and closing of missile silo doors, manages launch timing, and coordinates with special power systems for missile launch operations. This update is commonly used by missile silos, nuclear launch facilities, and other buildings that house and launch large missiles.

## Usage

Used by missile launcher buildings to handle missile launch operations, targeting, and building-specific mechanics. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Launch operations are limited by door opening and closing sequences
- Special power integration requires proper special power templates
- Door timing is controlled by specified duration parameters
- Visual and audio effects depend on proper FX and audio templates

**Conditions**:
- MissileLauncherBuildingUpdate manages complete door opening and closing sequences
- The update coordinates with special power systems for missile launch authorization
- Door states control building appearance and launch readiness
- Launch sequences include proper timing for door operations
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own door and launch parameters

**Dependencies**:
- Requires special power system integration for launch authorization
- Uses FX system for door operation visual effects
- Integrates with audio system for door operation sounds
- Uses building animation system for door movements

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Special Power Settings](#special-power-settings)
  - [Door Timing Settings](#door-timing-settings)
  - [Visual Effects Settings](#visual-effects-settings)
  - [Audio Settings](#audio-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Special Power Settings

#### `SpecialPowerTemplate` *(v1.04)*
- **Type**: `SpecialPowerTemplate`
- **Description**: Special power template that controls missile launch authorization and targeting. When set, enables special power integration. When empty, no special power coordination occurs
- **Default**: `NULL`
- **Example**: `SpecialPowerTemplate = SuperweaponNeutronMissile`

### Door Timing Settings

#### `DoorOpenTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time required to open missile silo doors. Higher values create slower door opening. Lower values create faster door opening
- **Default**: `0`
- **Example**: `DoorOpenTime = 8000`

#### `DoorWaitOpenTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time to keep doors open after missile launch. Higher values keep doors open longer. Lower values close doors sooner after launch
- **Default**: `0`
- **Example**: `DoorWaitOpenTime = 2000`

#### `DoorCloseTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time required to close missile silo doors. Higher values create slower door closing. Lower values create faster door closing
- **Default**: `0`
- **Example**: `DoorCloseTime = 1000`

### Visual Effects Settings

#### `DoorOpeningFX` *(v1.04)*
- **Type**: `FXList`
- **Description**: Effects played while doors are opening. When set, displays opening effects. When empty, no opening effects are shown
- **Default**: `NULL`
- **Example**: `DoorOpeningFX = FX_DoorOpening`

#### `DoorOpenFX` *(v1.04)*
- **Type**: `FXList`
- **Description**: Effects played when doors are fully open. When set, displays open effects. When empty, no open effects are shown
- **Default**: `NULL`
- **Example**: `DoorOpenFX = FX_DoorOpen`

#### `DoorWaitingToCloseFX` *(v1.04)*
- **Type**: `FXList`
- **Description**: Effects played while waiting to close doors after launch. When set, displays waiting effects. When empty, no waiting effects are shown
- **Default**: `NULL`
- **Example**: `DoorWaitingToCloseFX = FX_DoorWaiting`

#### `DoorClosingFX` *(v1.04)*
- **Type**: `FXList`
- **Description**: Effects played while doors are closing. When set, displays closing effects. When empty, no closing effects are shown
- **Default**: `NULL`
- **Example**: `DoorClosingFX = FX_DoorClosing`

#### `DoorClosedFX` *(v1.04)*
- **Type**: `FXList`
- **Description**: Effects played when doors are fully closed. When set, displays closed effects. When empty, no closed effects are shown
- **Default**: `NULL`
- **Example**: `DoorClosedFX = FX_DoorClosed`

### Audio Settings

#### `DoorOpenIdleAudio` *(v1.04)*
- **Type**: `AudioEventRTS`
- **Description**: Audio played continuously while doors are open and idle. When set, plays idle audio. When empty, no idle audio is played
- **Default**: `NULL`
- **Example**: `DoorOpenIdleAudio = Audio_DoorIdle`

## Examples

### Basic Missile Launcher
```ini
Behavior = MissileLauncherBuildingUpdate ModuleTag_11
  SpecialPowerTemplate = SuperweaponShtora
  DoorOpenTime         = 1000
  DoorWaitOpenTime     = 1000
End
```

### Nuclear Missile Silo
```ini
Behavior = MissileLauncherBuildingUpdate ModuleTag_09
  SpecialPowerTemplate = SuperweaponNeutronMissile
  DoorOpenTime         = 8000
  DoorWaitOpenTime     = 2000
End
```

### Guardian Shield Launcher
```ini
Behavior = MissileLauncherBuildingUpdate ModuleTag_18
  SpecialPowerTemplate = SpecialAbilityGuardianShield
  DoorOpenTime         = 1
  DoorWaitOpenTime     = 1
End
```

## Template

```ini
Behavior = MissileLauncherBuildingUpdate ModuleTag_XX
  ; Special Power Settings
  SpecialPowerTemplate =                ; // special power template for launch authorization *(v1.04)*
  
  ; Door Timing Settings
  DoorOpenTime = 0                      ; // time to open doors *(v1.04)*
  DoorWaitOpenTime = 0                  ; // time to keep doors open *(v1.04)*
  DoorCloseTime = 0                     ; // time to close doors *(v1.04)*
  
  ; Visual Effects Settings
  DoorOpeningFX =                       ; // effects while opening *(v1.04)*
  DoorOpenFX =                          ; // effects when open *(v1.04)*
  DoorWaitingToCloseFX =                ; // effects while waiting to close *(v1.04)*
  DoorClosingFX =                       ; // effects while closing *(v1.04)*
  DoorClosedFX =                        ; // effects when closed *(v1.04)*
  
  ; Audio Settings
  DoorOpenIdleAudio =                   ; // audio while doors are open *(v1.04)*
End
```

## Notes

- MissileLauncherBuildingUpdate provides sophisticated missile launch building mechanics
- The update manages complete door operation sequences with proper timing
- Special power integration ensures proper authorization and targeting for missile launches
- Visual and audio effects enhance the dramatic impact of missile launch operations
- This update is commonly used by missile silos, nuclear facilities, and defensive missile systems
- Door timing parameters control the pacing and realism of missile launch sequences

## Source Files

**Base Class:** [`SpecialPowerUpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerUpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/MissileLauncherBuildingUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/MissileLauncherBuildingUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/MissileLauncherBuildingUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/MissileLauncherBuildingUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet