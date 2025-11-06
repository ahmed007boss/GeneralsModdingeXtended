# MobMemberSlavedUpdate

MobMemberSlavedUpdate provides mob member slaved functionality for objects that are part of mob formations.

## Overview

The `MobMemberSlavedUpdate` class manages slaved behavior for objects that are part of mob formations and need to coordinate with a master object. It handles catch-up logic, positioning relative to the master, and provides behavioral parameters for mob coordination. This update is commonly used by scout drones, support units, and other objects that operate as part of a larger group under the control of a master unit.

## Usage

Used by objects that are part of mob formations and need to coordinate with other mob members. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Mob coordination is limited by catch-up radius and positioning parameters
- Squirrelly behavior is controlled by randomness factors
- Crisis bail time provides emergency teleportation when coordination fails
- Mob behavior depends on master object availability and commands

**Conditions**:
- MobMemberSlavedUpdate manages positioning and coordination with master objects
- The update handles catch-up logic when units get too far from their master
- Squirrelly behavior adds randomness to mob member positioning
- Crisis bail time provides emergency repositioning when coordination fails
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own master coordination

**Dependencies**:
- Requires master object for coordination and positioning reference
- Uses slaved update interface for master-slave relationships
- Integrates with positioning system for catch-up calculations

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Positioning Settings](#positioning-settings)
  - [Behavior Settings](#behavior-settings)
  - [Emergency Settings](#emergency-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Positioning Settings

#### `MustCatchUpRadius` *(v1.04)*
- **Type**: `Int` (distance)
- **Description**: Maximum distance from master when idle before triggering catch-up behavior. Higher values allow greater separation before catch-up. Lower values require closer positioning
- **Default**: `40`
- **Example**: `MustCatchUpRadius = 40`

#### `NoNeedToCatchUpRadius` *(v1.04)*
- **Type**: `Int` (distance)
- **Description**: Allowable wander distance from master while guarding. Higher values allow greater wandering range. Lower values require closer positioning during guard duty
- **Default**: `15`
- **Example**: `NoNeedToCatchUpRadius = 15`

### Behavior Settings

#### `Squirrelliness` *(v1.04)*
- **Type**: `Real`
- **Description**: Randomness factor for mob member positioning and behavior. Higher values create more erratic, unpredictable movement. Lower values create more organized, predictable behavior
- **Default**: `0.0`
- **Example**: `Squirrelliness = 0.05`

### Emergency Settings

#### `CatchUpCrisisBailTime` *(v1.04)*
- **Type**: `UnsignedInt` (frames)
- **Description**: Time in consecutive frames outside catch-up radius before emergency teleportation to master. Higher values allow longer separation before emergency bail. Lower values trigger emergency bail sooner
- **Default**: `999999` (effectively infinite)
- **Example**: `CatchUpCrisisBailTime = 300`

## Examples

### Basic Scout Drone
```ini
Behavior = MobMemberSlavedUpdate ModuleTag_04
  MustCatchUpRadius   = 40
  NoNeedToCatchUpRadius = 15
  Squirrelliness = 0.05
End
```

### Large Formation Unit
```ini
Behavior = MobMemberSlavedUpdate ModuleTag_04
  MustCatchUpRadius   = 70   ; bigger; bigger; bigger; bigger; bigger; bigger
  NoNeedToCatchUpRadius = 25 ; bigger; bigger; bigger; bigger; bigger; bigger
  Squirrelliness = 0.00      ; zero; zero; zero; zero; zero; zero
End
```

### Erratic Mob Member
```ini
Behavior = MobMemberSlavedUpdate ModuleTag_04
  MustCatchUpRadius   = 40
  NoNeedToCatchUpRadius = 15
  Squirrelliness = 0.05
  CatchUpCrisisBailTime = 150
End
```

## Template

```ini
Behavior = MobMemberSlavedUpdate ModuleTag_XX
  ; Positioning Settings
  MustCatchUpRadius = 40               ; // maximum distance before catch-up *(v1.04)*
  NoNeedToCatchUpRadius = 15           ; // allowable wander distance *(v1.04)*
  
  ; Behavior Settings
  Squirrelliness = 0.0                 ; // randomness factor for behavior *(v1.04)*
  
  ; Emergency Settings
  CatchUpCrisisBailTime = 999999       ; // frames before emergency bail *(v1.04)*
End
```

## Notes

- MobMemberSlavedUpdate provides sophisticated mob coordination and positioning mechanics
- The update manages catch-up logic to keep mob members coordinated with their master
- Squirrelly behavior adds realistic randomness to mob member positioning
- Emergency bail time provides failsafe teleportation when coordination completely fails
- This update is commonly used by scout drones, support units, and formation members
- Mob behavior creates realistic group dynamics with both coordination and individual variation

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h), [`SlavedUpdateInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/MobMemberSlavedUpdate.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/MobMemberSlavedUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/MobMemberSlavedUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/MobMemberSlavedUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/MobMemberSlavedUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet