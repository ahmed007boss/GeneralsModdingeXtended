# SpecialAbilityUpdate

SpecialAbilityUpdate provides special ability functionality for objects that have special abilities.

## Overview

The `SpecialAbilityUpdate` class manages special ability operations for objects that have special abilities that can be activated, managed, or controlled. It handles special power templates, ability ranges, preparation times, pack/unpack operations, and special object management. This update is commonly used by units with special abilities, special power users, and objects with unique capabilities.

## Usage

Used by objects that have special abilities that can be activated, managed, or controlled. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Special ability operations are limited by special power templates and ability parameters
- Ability ranges control activation and abort distances for special abilities
- Preparation times control ability activation timing and responsiveness
- Special object management depends on proper object configuration and attachment

**Conditions**:
- SpecialAbilityUpdate manages special ability activation, preparation, and execution
- The update handles ability ranges, preparation times, and pack/unpack operations
- Special abilities provide unique capabilities and tactical advantages
- Special object management creates additional objects and effects for abilities
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own ability parameters

**Dependencies**:
- Uses special power system for ability activation and management
- Integrates with object system for special object creation and management
- Uses audio system for ability sound effects

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Ability Settings](#ability-settings)
  - [Timing Settings](#timing-settings)
  - [Special Object Settings](#special-object-settings)
  - [Audio Settings](#audio-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Ability Settings

#### `SpecialPowerTemplate` *(v1.04)*
- **Type**: `SpecialPowerTemplate`
- **Description**: Template defining the special power/ability to be used. When set, provides special power functionality. When empty, no special power is available
- **Default**: `""`
- **Example**: `SpecialPowerTemplate = SpecialAbilityRangerCaptureBuilding`

#### `StartAbilityRange` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Range at which ability can be started. Higher values allow ability activation at greater distances. Lower values require closer proximity
- **Default**: `0.0`
- **Example**: `StartAbilityRange = 5.0`

#### `AbilityAbortRange` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Range at which ability will be aborted. Higher values allow ability continuation at greater distances. Lower values abort ability sooner
- **Default**: `0.0`
- **Example**: `AbilityAbortRange = 10.0`

### Timing Settings

#### `PreparationTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time required for ability preparation. Higher values create longer preparation. Lower values create faster preparation
- **Default**: `0`
- **Example**: `PreparationTime = 0`

#### `PersistentPrepTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time for persistent preparation. Higher values create longer persistent preparation. Lower values create shorter persistent preparation
- **Default**: `0`
- **Example**: `PersistentPrepTime = 0`

#### `PackTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time required for packing/unpacking operations. Higher values create longer pack/unpack times. Lower values create faster pack/unpack times
- **Default**: `0`
- **Example**: `PackTime = 0`

#### `UnpackTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time required for unpacking operations. Higher values create longer unpack times. Lower values create faster unpack times
- **Default**: `0`
- **Example**: `UnpackTime = 3000`

#### `PreTriggerUnstealthTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time before trigger to unstealth. Higher values unstealth earlier. Lower values unstealth later
- **Default**: `0`
- **Example**: `PreTriggerUnstealthTime = 0`

### Special Object Settings

#### `SpecialObject` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Name of special object to create. When set, creates specified special object. When empty, no special object is created
- **Default**: `""`
- **Example**: `SpecialObject = SpecialAbilityObject`

#### `SpecialObjectAttachToBone` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Bone name to attach special object to. When set, attaches to specified bone. When empty, uses default attachment
- **Default**: `""`
- **Example**: `SpecialObjectAttachToBone = BoneName`

#### `MaxSpecialObjects` *(v1.04)*
- **Type**: `UnsignedInt`
- **Description**: Maximum number of special objects allowed. Higher values allow more special objects. Lower values limit special object count
- **Default**: `0`
- **Example**: `MaxSpecialObjects = 1`

### Audio Settings

#### `PackSound` *(v1.04)*
- **Type**: `AudioEventRTS`
- **Description**: Sound to play during packing operations. When set, plays specified sound. When empty, no pack sound is played
- **Default**: `""`
- **Example**: `PackSound = PackSound`

#### `UnpackSound` *(v1.04)*
- **Type**: `AudioEventRTS`
- **Description**: Sound to play during unpacking operations. When set, plays specified sound. When empty, no unpack sound is played
- **Default**: `""`
- **Example**: `UnpackSound = UnpackSound`

#### `PrepSoundLoop` *(v1.04)*
- **Type**: `AudioEventRTS`
- **Description**: Sound to loop during preparation. When set, loops specified sound. When empty, no prep sound loop is played
- **Default**: `""`
- **Example**: `PrepSoundLoop = PrepSoundLoop`

#### `TriggerSound` *(v1.04)*
- **Type**: `AudioEventRTS`
- **Description**: Sound to play when ability is triggered. When set, plays specified sound. When empty, no trigger sound is played
- **Default**: `""`
- **Example**: `TriggerSound = TriggerSound`

## Examples

### Basic Special Ability
```ini
Behavior = SpecialAbilityUpdate ModuleTag_19
  SpecialPowerTemplate  = SpecialAbilityRangerCaptureBuilding
  StartAbilityRange  = 5.0
  UnpackTime            = 3000  ; (changing this will scale anim speed)
End
```

### Special Ability with Preparation
```ini
Behavior = SpecialAbilityUpdate ModuleTag_09
  SpecialPowerTemplate = SpecialAbilityColonelBurtonRemoteCharges
  StartAbilityRange = 0.0
  PreparationTime = 0
End
```

### Special Ability with Range
```ini
Behavior = SpecialAbilityUpdate ModuleTag_Disguise02
  SpecialPowerTemplate = SpecialAbilityDisguiseAsVehicle
  StartAbilityRange = 1000000.0
  ApproachRequiresLOS = No
End
```

## Template

```ini
Behavior = SpecialAbilityUpdate ModuleTag_XX
  ; Ability Settings
  SpecialPowerTemplate =                   ; // special power template *(v1.04)*
  StartAbilityRange = 0.0                  ; // range to start ability *(v1.04)*
  AbilityAbortRange = 0.0                  ; // range to abort ability *(v1.04)*
  
  ; Timing Settings
  PreparationTime = 0                      ; // time for ability preparation *(v1.04)*
  PersistentPrepTime = 0                   ; // time for persistent preparation *(v1.04)*
  PackTime = 0                            ; // time for packing operations *(v1.04)*
  UnpackTime = 0                          ; // time for unpacking operations *(v1.04)*
  PreTriggerUnstealthTime = 0             ; // time before trigger to unstealth *(v1.04)*
  
  ; Special Object Settings
  SpecialObject =                          ; // name of special object to create *(v1.04)*
  SpecialObjectAttachToBone =              ; // bone to attach special object to *(v1.04)*
  MaxSpecialObjects = 0                    ; // maximum number of special objects *(v1.04)*
  
  ; Audio Settings
  PackSound =                              ; // sound during packing *(v1.04)*
  UnpackSound =                            ; // sound during unpacking *(v1.04)*
  PrepSoundLoop =                          ; // sound loop during preparation *(v1.04)*
  TriggerSound =                           ; // sound when ability is triggered *(v1.04)*
End
```

## Notes

- SpecialAbilityUpdate provides comprehensive special ability management and activation
- The update handles ability ranges, preparation times, and pack/unpack operations
- Special abilities provide unique capabilities and tactical advantages for units
- Special object management creates additional objects and effects for ability enhancement
- This update is commonly used by units with special abilities, special power users, and unique capability objects
- Audio settings provide immersive sound effects for ability operations

## Source Files

**Base Class:** [`SpecialPowerUpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerUpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialAbilityUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialAbilityUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/SpecialAbilityUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet