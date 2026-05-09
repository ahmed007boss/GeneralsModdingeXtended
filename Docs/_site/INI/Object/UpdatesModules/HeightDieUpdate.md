# HeightDieUpdate

HeightDieUpdate provides height-based death functionality for objects that can die based on height conditions.

## Overview

The `HeightDieUpdate` class manages death mechanics for objects that die when they fall below certain height thresholds or meet specific height-based death conditions. It monitors object altitude and triggers death when height conditions are met, with options for considering structure heights, movement direction, and particle system cleanup. This update is commonly used by projectiles, falling objects, and units that need height-based destruction.

## Usage

Used by objects that need to die when they fall below a certain height or meet height-based death conditions. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Death is triggered only when height conditions are met
- Height calculations may include or exclude structure heights
- Death can be restricted to downward movement only
- Particle system cleanup occurs at specified heights

**Conditions**:
- HeightDieUpdate monitors object altitude relative to terrain or structures
- Death is triggered when the object falls below the specified target height
- Height calculations can include structure heights underneath the object
- Death can be restricted to only occur when moving downward
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own height thresholds

**Dependencies**:
- Requires terrain and height calculation systems
- Uses particle system for cleanup operations
- Integrates with death system for object destruction

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Height Settings](#height-settings)
  - [Movement Settings](#movement-settings)
  - [Cleanup Settings](#cleanup-settings)
  - [Timing Settings](#timing-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Height Settings

#### `TargetHeight` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Height above terrain at which the object will die. Higher values cause death at greater heights. Lower values require the object to fall closer to the ground before dying
- **Default**: `1.0`
- **Example**: `TargetHeight = 3.0`

#### `TargetHeightIncludesStructures` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether height calculations include structure heights underneath the object. When true, height is measured from the top of structures. When false, height is measured from terrain only
- **Default**: `Yes`
- **Example**: `TargetHeightIncludesStructures = No`

### Movement Settings

#### `OnlyWhenMovingDown` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether death only occurs when the object is moving downward. When true, objects must be falling to trigger death. When false, death occurs regardless of movement direction
- **Default**: `No`
- **Example**: `OnlyWhenMovingDown = Yes`

### Cleanup Settings

#### `DestroyAttachedParticlesAtHeight` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Height at which attached particle systems are destroyed before death. Higher values destroy particles sooner. Lower values destroy particles closer to death
- **Default**: `0.0` (disabled)
- **Example**: `DestroyAttachedParticlesAtHeight = 5.0`

#### `SnapToGroundOnDeath` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether the object snaps to ground level when it dies. When true, object is positioned at ground level upon death. When false, object dies at current height
- **Default**: `No`
- **Example**: `SnapToGroundOnDeath = Yes`

### Timing Settings

#### `InitialDelay` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Delay before height death checking begins. Higher values prevent immediate death after object creation. Lower values allow sooner height death checking
- **Default**: `0`
- **Example**: `InitialDelay = 1000`

## Examples

### Basic Height Death
```ini
Behavior = HeightDieUpdate ModuleTag_06
  TargetHeight = 1.0
  TargetHeightIncludesStructures = Yes
  OnlyWhenMovingDown = Yes
End
```

### High Altitude Death with Initial Delay
```ini
Behavior = HeightDieUpdate ModuleTag_03
  TargetHeight = 3.0                          ;;; changed from previous, 50
  TargetHeightIncludesStructures = Yes
  InitialDelay = 2000
End
```

### Extreme Height Death with Cleanup
```ini
Behavior = HeightDieUpdate ModuleTag_08
  TargetHeight        = 900.0
  TargetHeightIncludesStructures = Yes
  OnlyWhenMovingDown  = Yes
  DestroyAttachedParticlesAtHeight = 10.0
  SnapToGroundOnDeath = Yes
End
```

## Template

```ini
Behavior = HeightDieUpdate ModuleTag_XX
  ; Height Settings
  TargetHeight = 1.0                  ; // height above terrain for death *(v1.04)*
  TargetHeightIncludesStructures = Yes ; // include structure heights in calculation *(v1.04)*
  
  ; Movement Settings
  OnlyWhenMovingDown = No             ; // death only when moving downward *(v1.04)*
  
  ; Cleanup Settings
  DestroyAttachedParticlesAtHeight = 0.0 ; // height to destroy particle systems *(v1.04)*
  SnapToGroundOnDeath = No           ; // snap to ground when dying *(v1.04)*
  
  ; Timing Settings
  InitialDelay = 0                   ; // delay before height checking begins *(v1.04)*
End
```

## Notes

- HeightDieUpdate provides height-based death mechanics for falling objects and projectiles
- The update can consider both terrain and structure heights for accurate death triggering
- Movement direction restrictions allow for more realistic falling object behavior
- Particle system cleanup prevents visual artifacts when objects die at height
- This update is commonly used by projectiles, bombs, and falling units
- Initial delays prevent objects from dying immediately upon creation

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/HeightDieUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/HeightDieUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/HeightDieUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/HeightDieUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet