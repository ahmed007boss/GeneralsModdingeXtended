# StealthDetectorUpdate

StealthDetectorUpdate provides stealth detection functionality for objects that can detect stealth units.

## Overview

The `StealthDetectorUpdate` class manages stealth detection operations for objects that can detect stealth units, provide stealth detection coverage, or manage stealth detection systems. It handles detection rates, detection ranges, stealth detection capabilities, and stealth unit identification. This update is commonly used by radar systems, detection units, and objects that provide stealth detection capabilities.

## Usage

Used by objects that can detect stealth units, provide stealth detection coverage, or manage stealth detection systems. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Stealth detection is limited by detection rate and range parameters
- Detection capabilities depend on proper stealth detection system integration
- Detection operations are controlled by detection timing and range parameters
- Stealth detection effectiveness varies based on stealth unit capabilities

**Conditions**:
- StealthDetectorUpdate manages stealth detection and identification operations
- The update handles detection rates, ranges, and stealth unit identification
- Stealth detection provides tactical advantages for identifying hidden units
- Detection operations create realistic stealth detection capabilities
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own detection parameters

**Dependencies**:
- Uses stealth detection system for stealth unit identification
- Integrates with radar system for detection coverage
- Uses audio system for detection sound effects

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Detection Settings](#detection-settings)
  - [Audio Settings](#audio-settings)
  - [Visual Effects Settings](#visual-effects-settings)
  - [Target Filtering Settings](#target-filtering-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Detection Settings

#### `DetectionRate` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: How often to rescan for stealthed units. Higher values create slower detection. Lower values create faster detection
- **Default**: `0`
- **Example**: `DetectionRate = 500`

#### `DetectionRange` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Range for stealth detection. Higher values detect stealth units at greater distances. Lower values detect stealth units at closer distances
- **Default**: `0.0`
- **Example**: `DetectionRange = 285`

#### `InitiallyDisabled` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether stealth detection starts disabled. When true, detection starts disabled. When false, detection starts enabled
- **Default**: `No`
- **Example**: `InitiallyDisabled = No`

### Audio Settings

#### `PingSound` *(v1.04)*
- **Type**: `AudioEventRTS`
- **Description**: Sound to play when detecting stealth units. When set, plays specified sound. When empty, no ping sound is played
- **Default**: `""`
- **Example**: `PingSound = StealthPingSound`

#### `LoudPingSound` *(v1.04)*
- **Type**: `AudioEventRTS`
- **Description**: Loud sound to play when detecting stealth units. When set, plays specified loud sound. When empty, no loud ping sound is played
- **Default**: `""`
- **Example**: `LoudPingSound = StealthLoudPingSound`

### Visual Effects Settings

#### `IRBeaconParticleSysName` *(v1.04)*
- **Type**: `ParticleSystemTemplate`
- **Description**: Particle system for IR beacon effects. When set, creates specified particle effect. When empty, no IR beacon effect is created
- **Default**: `""`
- **Example**: `IRBeaconParticleSysName = IRBeaconEffect`

#### `IRParticleSysName` *(v1.04)*
- **Type**: `ParticleSystemTemplate`
- **Description**: Particle system for IR detection effects. When set, creates specified particle effect. When empty, no IR effect is created
- **Default**: `""`
- **Example**: `IRParticleSysName = IREffect`

#### `IRBrightParticleSysName` *(v1.04)*
- **Type**: `ParticleSystemTemplate`
- **Description**: Particle system for bright IR detection effects. When set, creates specified bright particle effect. When empty, no bright IR effect is created
- **Default**: `""`
- **Example**: `IRBrightParticleSysName = IRBrightEffect`

#### `IRGridParticleSysName` *(v1.04)*
- **Type**: `ParticleSystemTemplate`
- **Description**: Particle system for IR grid effects. When set, creates specified grid particle effect. When empty, no IR grid effect is created
- **Default**: `""`
- **Example**: `IRGridParticleSysName = IRGridEffect`

#### `IRParticleSysBone` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Bone name for IR particle system attachment. When set, attaches to specified bone. When empty, uses default attachment
- **Default**: `""`
- **Example**: `IRParticleSysBone = IRBone`

### Target Filtering Settings

#### `ExtraRequiredKindOf` *(v1.04)*
- **Type**: `KindOfMaskType` (bit flags)
- **Description**: Additional required object types for detection. When set, only detects specified types. When empty, no additional type requirements
- **Default**: `0`
- **Example**: `ExtraRequiredKindOf = AIRCRAFT`

#### `ExtraForbiddenKindOf` *(v1.04)*
- **Type**: `KindOfMaskType` (bit flags)
- **Description**: Object types forbidden from detection. When set, excludes specified types. When empty, no type exclusions
- **Default**: `0`
- **Example**: `ExtraForbiddenKindOf = AIRCRAFT DRONE`

## Examples

### Basic Stealth Detector
```ini
Behavior = StealthDetectorUpdate ModuleTag_AirDetection1
  DetectionRate   = 500   ; how often to rescan for stealthed things in my sight (msec)
  DetectionRange = 285 ;Dustin, enable this for independant balancing!
  ExtraForbiddenKindOf     = AIRCRAFT DRONE
End
```

### Aircraft Detection
```ini
Behavior = StealthDetectorUpdate ModuleTag_12
  DetectionRate   = 2000
  DetectionRange = 0
  ExtraRequiredKindOf      = AIRCRAFT
End
```

### Advanced Stealth Detection
```ini
Behavior = StealthDetectorUpdate ModuleTag_10
  DetectionRate   = 1500   ; how often to rescan for stealthed things in my sight (msec)
  DetectionRange = 230 ;Dustin, enable this for independant balancing!
  ExtraRequiredKindOf      = AIRCRAFT 
End
```

## Template

```ini
Behavior = StealthDetectorUpdate ModuleTag_XX
  ; Detection Settings
  DetectionRate = 0                      ; // how often to rescan for stealth units *(v1.04)*
  DetectionRange = 0.0                   ; // range for stealth detection *(v1.04)*
  InitiallyDisabled = No                 ; // whether detection starts disabled *(v1.04)*
  
  ; Audio Settings
  PingSound =                            ; // sound when detecting stealth units *(v1.04)*
  LoudPingSound =                        ; // loud sound when detecting stealth units *(v1.04)*
  
  ; Visual Effects Settings
  IRBeaconParticleSysName =              ; // particle system for IR beacon effects *(v1.04)*
  IRParticleSysName =                    ; // particle system for IR detection effects *(v1.04)*
  IRBrightParticleSysName =              ; // particle system for bright IR effects *(v1.04)*
  IRGridParticleSysName =                ; // particle system for IR grid effects *(v1.04)*
  IRParticleSysBone =                    ; // bone for IR particle system attachment *(v1.04)*
  
  ; Target Filtering Settings
  ExtraRequiredKindOf =                  ; // additional required object types *(v1.04)*
  ExtraForbiddenKindOf =                 ; // forbidden object types *(v1.04)*
End
```

## Notes

- StealthDetectorUpdate provides comprehensive stealth detection and identification capabilities
- The update manages detection rates, ranges, and stealth unit identification
- Stealth detection provides tactical advantages for identifying hidden enemy units
- Visual effects create immersive IR detection feedback for stealth identification
- This update is commonly used by radar systems, detection units, and stealth detection facilities
- Target filtering allows precise control over what types of units can be detected

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StealthDetectorUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StealthDetectorUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/StealthDetectorUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/StealthDetectorUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet