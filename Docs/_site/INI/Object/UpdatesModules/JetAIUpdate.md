# JetAIUpdate

JetAIUpdate provides AI update functionality for jet aircraft units.

## Overview

The `JetAIUpdate` class manages AI-driven flight operations for jet aircraft units, handling takeoff, landing, combat, airfield management, and specialized jet behaviors. It provides sophisticated flight AI including runway requirements, parking management, lock-on mechanics, and custom locomotor sets for different flight phases. This update is commonly used by fighter jets, bombers, and other aircraft that require complex flight AI and airfield coordination.

## Usage

Used by jet aircraft to handle AI-driven flight operations, combat, and airfield management. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Flight operations are limited by runway availability and parking space
- Lock-on mechanics require proper cursor templates and timing
- Custom locomotor sets are limited to specific flight phases
- Out-of-ammo damage is percentage-based, not absolute values

**Conditions**:
- JetAIUpdate manages complete flight lifecycle from takeoff to landing
- The update handles airfield coordination including parking and runway usage
- Combat operations include lock-on mechanics and attack patterns
- Custom locomotor sets provide different flight behaviors for different phases
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own flight parameters

**Dependencies**:
- Requires airfield systems for takeoff and landing operations
- Uses locomotor system for flight movement and pathfinding
- Integrates with weapon systems for combat operations
- Uses lock-on system for targeting mechanics

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Flight Settings](#flight-settings)
  - [Combat Settings](#combat-settings)
  - [Airfield Settings](#airfield-settings)
  - [Lock-on Settings](#lock-on-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Flight Settings

#### `OutOfAmmoDamagePerSecond` *(v1.04)*
- **Type**: `Real` (percentage)
- **Description**: Damage taken per second when out of ammo, expressed as percentage of max health. Higher values cause more damage when out of ammo. Lower values cause less damage
- **Default**: `0.0`
- **Example**: `OutOfAmmoDamagePerSecond = 10%`

#### `TakeoffDistForMaxLift` *(v1.04)*
- **Type**: `Real` (percentage)
- **Description**: Percentage of takeoff distance that provides maximum lift. Higher values provide lift sooner during takeoff. Lower values require more distance before achieving full lift
- **Default**: `0.0`
- **Example**: `TakeoffDistForMaxLift = 0%`

#### `MinHeight` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Minimum height above ground when taxiing. Higher values keep aircraft higher during ground operations. Lower values allow closer ground clearance
- **Default**: `0.0`
- **Example**: `MinHeight = 5`

#### `NeedsRunway` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether the jet requires runways for takeoff and landing. When true, jet must use runways. When false, jet can take off and land vertically or from any surface
- **Default**: `Yes`
- **Example**: `NeedsRunway = No`

### Combat Settings

#### `SneakyOffsetWhenAttacking` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Offset distance for stealthy attack approaches. Higher values create larger attack offsets. Lower values create more direct attack paths
- **Default**: `0.0`
- **Example**: `SneakyOffsetWhenAttacking = 100.0`

#### `TakeoffPause` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Pre-takeoff pause duration. Higher values create longer delays before takeoff. Lower values allow faster takeoff sequences
- **Default**: `0`
- **Example**: `TakeoffPause = 2000`

#### `AttackLocomotorType` *(v1.04)*
- **Type**: `LocomotorSetType` (enum)
- **Description**: Custom locomotor set used during attack phases. When set, uses specified locomotor for attacks. When empty, uses default attack locomotor
- **Default**: `LOCOMOTORSET_INVALID`
- **Example**: `AttackLocomotorType = LOCOMOTORSET_ATTACK`

#### `AttackLocomotorPersistTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: How long custom attack locomotor persists after attack completion. Higher values maintain attack locomotor longer. Lower values return to normal locomotor sooner
- **Default**: `0`
- **Example**: `AttackLocomotorPersistTime = 5000`

#### `AttackersMissPersistTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: How long immunity to enemy attacks persists after our attack. Higher values provide longer immunity. Lower values provide shorter immunity
- **Default**: `0`
- **Example**: `AttackersMissPersistTime = 3000`

#### `ReturnForAmmoLocomotorType` *(v1.04)*
- **Type**: `LocomotorSetType` (enum)
- **Description**: Custom locomotor set used when returning for ammunition. When set, uses specified locomotor for return trips. When empty, uses default return locomotor
- **Default**: `LOCOMOTORSET_INVALID`
- **Example**: `ReturnForAmmoLocomotorType = LOCOMOTORSET_RETURN`

### Airfield Settings

#### `KeepsParkingSpaceWhenAirborne` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether jet retains parking space reservation while airborne. When true, parking space remains reserved. When false, parking space becomes available to other aircraft
- **Default**: `No`
- **Example**: `KeepsParkingSpaceWhenAirborne = Yes`

#### `ParkingOffset` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Offset distance for parking position adjustment. Higher values create larger parking offsets. Lower values provide more precise parking
- **Default**: `0.0`
- **Example**: `ParkingOffset = 10.0`

### Lock-on Settings

#### `LockonTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time required for lock-on targeting. Higher values require longer lock-on times. Lower values allow faster lock-on
- **Default**: `0`
- **Example**: `LockonTime = 2000`

#### `LockonCursor` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Template used for lock-on cursor display. When set, displays specified cursor during lock-on. When empty, uses default lock-on cursor
- **Default**: `""`
- **Example**: `LockonCursor = "LockonCursorTemplate"`

#### `LockonInitialDist` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Initial distance for lock-on cursor positioning. Higher values start lock-on cursor farther away. Lower values start lock-on cursor closer
- **Default**: `0.0`
- **Example**: `LockonInitialDist = 200.0`

#### `LockonFreq` *(v1.04)*
- **Type**: `Real`
- **Description**: Frequency of lock-on updates. Higher values provide more frequent lock-on updates. Lower values provide less frequent updates
- **Default**: `0.0`
- **Example**: `LockonFreq = 10.0`

#### `LockonAngleSpin` *(v1.04)*
- **Type**: `Real` (angle)
- **Description**: Number of times lock-on cursor spins around target. Higher values create more spin rotations. Lower values create fewer rotations
- **Default**: `0.0`
- **Example**: `LockonAngleSpin = 2.0`

## Examples

### Basic Jet with Out-of-Ammo Damage
```ini
Behavior = JetAIUpdate ModuleTag_06
  OutOfAmmoDamagePerSecond = 10%  ; amount of damage to take per SEC (not per frame) when out of ammo
                                  ; note that it's expressed as a percent of max health, not an absolute
  TakeoffDistForMaxLift     = 0%   ; larger numbers give more lift sooner when taking off
End
```

### Jet with Runway Requirements
```ini
Behavior = JetAIUpdate ModuleTag_06
  MinHeight                     = 5
  NeedsRunway                   = No
  KeepsParkingSpaceWhenAirborne = No
End
```

### Advanced Combat Jet
```ini
Behavior = JetAIUpdate ModuleTag_05
  OutOfAmmoDamagePerSecond  = 10%  ; amount of damage to take per SEC (not per frame) when out of ammo
                                  ; note that it's expressed as a percent of max health, not an absolute
  TakeoffDistForMaxLift     = 0%   ; larger numbers give more lift sooner when taking off
  AttackLocomotorType = LOCOMOTORSET_ATTACK
  AttackLocomotorPersistTime = 5000
  LockonTime = 2000
  LockonFreq = 10.0
End
```

## Template

```ini
Behavior = JetAIUpdate ModuleTag_XX
  ; Flight Settings
  OutOfAmmoDamagePerSecond = 0.0         ; // damage per second when out of ammo (percentage) *(v1.04)*
  TakeoffDistForMaxLift = 0.0            ; // percentage of takeoff distance for max lift *(v1.04)*
  MinHeight = 0.0                        ; // minimum height when taxiing *(v1.04)*
  NeedsRunway = Yes                      ; // requires runways for takeoff/landing *(v1.04)*
  
  ; Combat Settings
  SneakyOffsetWhenAttacking = 0.0        ; // stealth attack offset distance *(v1.04)*
  TakeoffPause = 0                       ; // pre-takeoff pause duration *(v1.04)*
  AttackLocomotorType =                  ; // custom locomotor for attacks *(v1.04)*
  AttackLocomotorPersistTime = 0         ; // attack locomotor persistence time *(v1.04)*
  AttackersMissPersistTime = 0           ; // immunity time after attacks *(v1.04)*
  ReturnForAmmoLocomotorType =           ; // custom locomotor for returning *(v1.04)*
  
  ; Airfield Settings
  KeepsParkingSpaceWhenAirborne = No     ; // retain parking space when airborne *(v1.04)*
  ParkingOffset = 0.0                    ; // parking position offset *(v1.04)*
  
  ; Lock-on Settings
  LockonTime = 0                         ; // lock-on targeting time *(v1.04)*
  LockonCursor =                         ; // lock-on cursor template *(v1.04)*
  LockonInitialDist = 0.0                ; // initial lock-on distance *(v1.04)*
  LockonFreq = 0.0                       ; // lock-on update frequency *(v1.04)*
  LockonAngleSpin = 0.0                  ; // lock-on cursor spin rotations *(v1.04)*
End
```

## Notes

- JetAIUpdate provides comprehensive flight AI for sophisticated aircraft operations
- The update manages complete flight lifecycle including takeoff, combat, and landing
- Custom locomotor sets allow different flight behaviors for different operational phases
- Lock-on mechanics provide realistic targeting systems for air-to-air and air-to-ground combat
- Out-of-ammo damage encourages aircraft to return for resupply rather than continuing without ammunition
- This update is commonly used by fighter jets, bombers, and other advanced aircraft
- Airfield coordination ensures proper takeoff/landing sequencing and parking management

## Source Files

**Base Class:** [`AIUpdateInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/JetAIUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/JetAIUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/JetAIUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/JetAIUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet