# CrushDie

CrushDie provides crushing death effects and visual feedback for objects that are crushed.

## Overview

The `CrushDie` class manages crushing death effects that occur when objects are crushed by other objects. It determines the type of crush (total, front-end, or back-end) based on the crushing object's position and plays appropriate audio effects. The behavior also updates the object's visual state to show crushed conditions. This behavior is commonly used for vehicles, structures, and other objects that can be crushed.

## Usage

Used by objects that can be crushed and need visual/audio feedback for crushing effects, such as vehicles, structures, or crushable objects. This is a **die module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- CrushDie only triggers when the object receives crush damage
- The behavior requires a valid damage dealer to determine crush type
- Audio effects are limited by sound percent settings
- Visual effects are limited to front and back crush conditions
- The behavior only works with crush damage type

**Conditions**:
- CrushDie determines crush type based on the crushing object's position relative to the victim
- The behavior supports total crush, front-end crush, and back-end crush types
- Audio effects are played based on crush type and probability settings
- Visual model conditions are updated to show crushed state
- The behavior integrates with the physics system for crush detection
- **Multiple instances behavior**: Only one instance should be used per object; multiple instances may cause conflicts in crush state management

**Dependencies**:
- Requires valid audio event definitions to function correctly
- The behavior relies on the physics system for crush detection and damage

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Audio Effects](#audio-effects)
  - [Audio Probabilities](#audio-probabilities)
- [Enum Value Lists](#enum-value-lists)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

### Audio Effects

#### `TotalCrushSound` *(v1.04)*
- **Type**: `AudioEventRTS`
- **Description**: Audio event played when the object is totally crushed. When set, plays the specified sound effect during total crushing. When empty (default), no sound is played
- **Default**: `""` (empty)
- **Example**: `TotalCrushSound = VehicleCrushTotal`

#### `BackEndCrushSound` *(v1.04)*
- **Type**: `AudioEventRTS`
- **Description**: Audio event played when the back end of the object is crushed. When set, plays the specified sound effect during back-end crushing. When empty (default), no sound is played
- **Default**: `""` (empty)
- **Example**: `BackEndCrushSound = VehicleCrushBack`

#### `FrontEndCrushSound` *(v1.04)*
- **Type**: `AudioEventRTS`
- **Description**: Audio event played when the front end of the object is crushed. When set, plays the specified sound effect during front-end crushing. When empty (default), no sound is played
- **Default**: `""` (empty)
- **Example**: `FrontEndCrushSound = VehicleCrushFront`

### Audio Probabilities

#### `TotalCrushSoundPercent` *(v1.04)*
- **Type**: `Int` (0-100)
- **Description**: Probability percentage for playing total crush sound. Higher values (up to 100) increase the chance the sound plays. Lower values reduce the likelihood. At 0, the sound never plays
- **Default**: `100`
- **Example**: `TotalCrushSoundPercent = 100`

#### `BackEndCrushSoundPercent` *(v1.04)*
- **Type**: `Int` (0-100)
- **Description**: Probability percentage for playing back-end crush sound. Higher values (up to 100) increase the chance the sound plays. Lower values reduce the likelihood. At 0, the sound never plays
- **Default**: `100`
- **Example**: `BackEndCrushSoundPercent = 75`

#### `FrontEndCrushSoundPercent` *(v1.04)*
- **Type**: `Int` (0-100)
- **Description**: Probability percentage for playing front-end crush sound. Higher values (up to 100) increase the chance the sound plays. Lower values reduce the likelihood. At 0, the sound never plays
- **Default**: `100`
- **Example**: `FrontEndCrushSoundPercent = 75`

## Enum Value Lists

#### `CrushEnum` Values *(v1.04)*
**Source:** [CrushDie.h](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CrushDie.h#45) - `CrushEnum` enum definition

- **`TOTAL_CRUSH`** *(v1.04)* - Object is totally crushed
- **`BACK_END_CRUSH`** *(v1.04)* - Back end of object is crushed
- **`FRONT_END_CRUSH`** *(v1.04)* - Front end of object is crushed
- **`NO_CRUSH`** *(v1.04)* - No crush occurred

## Examples

### Vehicle Crush Effects
```ini
Die = CrushDie ModuleTag_Crush
  TotalCrushSound = VehicleCrushTotal
  BackEndCrushSound = VehicleCrushBack
  FrontEndCrushSound = VehicleCrushFront
  TotalCrushSoundPercent = 100
  BackEndCrushSoundPercent = 75
  FrontEndCrushSoundPercent = 75
End
```

### Structure Crush Effects
```ini
Die = CrushDie ModuleTag_StructureCrush
  TotalCrushSound = BuildingCrush
  TotalCrushSoundPercent = 100
End
```

### High-Probability Crush
```ini
Die = CrushDie ModuleTag_HighProb
  TotalCrushSound = VehicleCrushTotal
  TotalCrushSoundPercent = 100
  BackEndCrushSoundPercent = 100
  FrontEndCrushSoundPercent = 100
End
```

## Template

```ini
Die = CrushDie ModuleTag_XX
  ; Audio Effects
  TotalCrushSound =                   ; // audio event for total crush *(v1.04)*
  BackEndCrushSound =                 ; // audio event for back-end crush *(v1.04)*
  FrontEndCrushSound =                ; // audio event for front-end crush *(v1.04)*

  ; Audio Probabilities
  TotalCrushSoundPercent = 100        ; // probability for total crush sound *(v1.04)*
  BackEndCrushSoundPercent = 100      ; // probability for back-end crush sound *(v1.04)*
  FrontEndCrushSoundPercent = 100     ; // probability for front-end crush sound *(v1.04)*
End
```

## Notes

- CrushDie determines crush type based on the crushing object's position relative to the victim
- The behavior supports total crush, front-end crush, and back-end crush types
- Audio effects are played based on crush type and probability settings
- Visual model conditions are updated to show crushed state
- The behavior integrates with the physics system for crush detection
- Crush type determination considers the victim's front and back crush states

## Source Files

**Base Class:** [`DieModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CrushDie.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CrushDie.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Die/CrushDie.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Die/CrushDie.cpp)