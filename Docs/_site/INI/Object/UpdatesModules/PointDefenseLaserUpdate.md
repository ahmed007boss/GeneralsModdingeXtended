# PointDefenseLaserUpdate

PointDefenseLaserUpdate provides point defense laser functionality for objects that can automatically engage incoming threats.

## Overview

The `PointDefenseLaserUpdate` class manages point defense laser systems that automatically scan for and engage incoming threats such as missiles, projectiles, and aircraft. It handles target detection, weapon firing, and defensive coordination to protect friendly units and structures. This update is commonly used by point defense systems, anti-missile defenses, and automated defensive weapons.

## Usage

Used by objects that can automatically engage incoming threats with point defense weapons. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Defense operations are limited by scan range and frequency parameters
- Target engagement is controlled by weapon template and target type restrictions
- Velocity prediction is limited by target movement patterns
- Defense effectiveness depends on weapon accuracy and target characteristics

**Conditions**:
- PointDefenseLaserUpdate continuously scans for incoming threats
- The update prioritizes targets based on primary and secondary target types
- Weapon firing is coordinated with target detection and engagement
- Velocity prediction improves accuracy against moving targets
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own defense parameters

**Dependencies**:
- Requires weapon system integration for defensive firing
- Uses scanning system for threat detection
- Integrates with targeting system for engagement coordination

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Weapon Settings](#weapon-settings)
  - [Target Settings](#target-settings)
  - [Scan Settings](#scan-settings)
  - [Engagement Settings](#engagement-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Weapon Settings

#### `WeaponTemplate` *(v1.04)*
- **Type**: `WeaponTemplate`
- **Description**: Weapon template used for point defense engagements. When set, uses specified weapon for defense. When empty, no defensive weapon is available
- **Default**: `NULL`
- **Example**: `WeaponTemplate = WeaponPointDefenseLaser`

### Target Settings

#### `PrimaryTargetTypes` *(v1.04)*
- **Type**: `KindOfMaskType` (bit flags)
- **Description**: Primary target types that the point defense prioritizes for engagement. When set, prioritizes specified target types. When empty, no primary targets are defined
- **Default**: `0`
- **Example**: `PrimaryTargetTypes = PROJECTILE MISSILE`

#### `SecondaryTargetTypes` *(v1.04)*
- **Type**: `KindOfMaskType` (bit flags)
- **Description**: Secondary target types that the point defense engages when no primary targets are available. When set, engages specified target types. When empty, no secondary targets are defined
- **Default**: `0`
- **Example**: `SecondaryTargetTypes = AIRCRAFT`

### Scan Settings

#### `ScanRate` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: How often the point defense scans for incoming threats. Higher values reduce scan frequency but improve performance. Lower values provide more frequent scanning
- **Default**: `0`
- **Example**: `ScanRate = 500`

#### `ScanRange` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Maximum range at which the point defense can detect and engage threats. Higher values provide longer engagement range. Lower values limit engagement to nearby threats
- **Default**: `0.0`
- **Example**: `ScanRange = 300.0`

### Engagement Settings

#### `PredictTargetVelocityFactor` *(v1.04)*
- **Type**: `Real`
- **Description**: Factor used to predict target velocity for improved accuracy. Higher values provide more aggressive velocity prediction. Lower values provide more conservative prediction
- **Default**: `0.0`
- **Example**: `PredictTargetVelocityFactor = 1.5`

## Examples

### Basic Point Defense
```ini
Behavior = PointDefenseLaserUpdate ModuleTag_08
  WeaponTemplate = WeaponPointDefenseLaser
  PrimaryTargetTypes = PROJECTILE MISSILE
  ScanRate = 500
  ScanRange = 300.0
End
```

### Advanced Point Defense
```ini
Behavior = PointDefenseLaserUpdate ModuleTag_09
  WeaponTemplate = WeaponAdvancedPointDefense
  PrimaryTargetTypes = PROJECTILE MISSILE
  SecondaryTargetTypes = AIRCRAFT
  ScanRate = 250
  ScanRange = 400.0
  PredictTargetVelocityFactor = 1.5
End
```

### Missile Defense Only
```ini
Behavior = PointDefenseLaserUpdate ModuleTag_10
  WeaponTemplate = WeaponMissileDefense
  PrimaryTargetTypes = MISSILE
  ScanRate = 1000
  ScanRange = 500.0
  PredictTargetVelocityFactor = 2.0
End
```

## Template

```ini
Behavior = PointDefenseLaserUpdate ModuleTag_XX
  ; Weapon Settings
  WeaponTemplate =                       ; // weapon template for defense *(v1.04)*
  
  ; Target Settings
  PrimaryTargetTypes =                   ; // primary target types *(v1.04)*
  SecondaryTargetTypes =                 ; // secondary target types *(v1.04)*
  
  ; Scan Settings
  ScanRate = 0                          ; // how often to scan for threats *(v1.04)*
  ScanRange = 0.0                       ; // maximum engagement range *(v1.04)*
  
  ; Engagement Settings
  PredictTargetVelocityFactor = 0.0      ; // velocity prediction factor *(v1.04)*
End
```

## Notes

- PointDefenseLaserUpdate provides sophisticated automatic defense against incoming threats
- The update prioritizes targets based on primary and secondary target type classifications
- Velocity prediction improves accuracy when engaging fast-moving targets
- Scanning parameters control defense responsiveness and engagement range
- This update is commonly used by point defense systems, anti-missile defenses, and automated weapons
- Target type filtering ensures appropriate engagement of different threat categories

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/PointDefenseLaserUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/PointDefenseLaserUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/PointDefenseLaserUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/PointDefenseLaserUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet