# SlavedUpdate

SlavedUpdate provides slaved functionality for objects that are controlled by or slaved to other objects.

## Overview

The `SlavedUpdate` class manages slaved behavior for objects that are controlled by or slaved to other objects, such as turrets, weapons, or controlled units. It handles guard ranges, attack ranges, scout ranges, repair operations, and coordination with master objects. This update is commonly used by turrets, slaved weapons, and units that operate under the control of other objects.

## Usage

Used by objects that are slaved to other objects, such as turrets, weapons, or controlled units. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Slaved operations are limited by range parameters and master object control
- Guard and attack ranges control slaved object behavior and positioning
- Repair operations depend on proper repair system integration
- Scout operations are controlled by scout range parameters

**Conditions**:
- SlavedUpdate manages slaved object behavior and coordination with master objects
- The update handles guard ranges, attack ranges, and scout ranges for slaved operations
- Repair operations provide maintenance capabilities for slaved objects
- Slaved coordination creates realistic master-slave object relationships
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own slaved parameters

**Dependencies**:
- Uses slaved system for master-slave coordination
- Integrates with repair system for maintenance operations
- Uses positioning system for range-based operations

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Range Settings](#range-settings)
  - [Repair Settings](#repair-settings)
  - [Coordination Settings](#coordination-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Range Settings

#### `GuardMaxRange` *(v1.04)*
- **Type**: `Int` (distance)
- **Description**: Maximum range from master when guarding. Higher values allow greater guard range. Lower values keep slaved objects closer to master
- **Default**: `0`
- **Example**: `GuardMaxRange = 1`

#### `GuardWanderRange` *(v1.04)*
- **Type**: `Int` (distance)
- **Description**: Maximum range from master when wandering while guarding. Higher values allow greater wander range. Lower values keep slaved objects closer to master
- **Default**: `0`
- **Example**: `GuardWanderRange = 1`

#### `AttackRange` *(v1.04)*
- **Type**: `Int` (distance)
- **Description**: Maximum range from master when attacking. Higher values allow greater attack range. Lower values keep slaved objects closer to master
- **Default**: `0`
- **Example**: `AttackRange = 1`

#### `AttackWanderRange` *(v1.04)*
- **Type**: `Int` (distance)
- **Description**: Maximum range from master when wandering while attacking. Higher values allow greater wander range. Lower values keep slaved objects closer to master
- **Default**: `0`
- **Example**: `AttackWanderRange = 1`

#### `ScoutRange` *(v1.04)*
- **Type**: `Int` (distance)
- **Description**: Maximum range from master when scouting. Higher values allow greater scout range. Lower values keep slaved objects closer to master
- **Default**: `0`
- **Example**: `ScoutRange = 1`

#### `ScoutWanderRange` *(v1.04)*
- **Type**: `Int` (distance)
- **Description**: Maximum range from master when wandering while scouting. Higher values allow greater wander range. Lower values keep slaved objects closer to master
- **Default**: `0`
- **Example**: `ScoutWanderRange = 1`

### Repair Settings

#### `RepairRange` *(v1.04)*
- **Type**: `Int` (distance)
- **Description**: Maximum range from master for repair operations. Higher values allow greater repair range. Lower values keep slaved objects closer to master
- **Default**: `0`
- **Example**: `RepairRange = 1`

#### `RepairMinAltitude` *(v1.04)*
- **Type**: `Real` (altitude)
- **Description**: Minimum altitude for repair operations. Higher values require higher altitude. Lower values allow lower altitude repairs
- **Default**: `0.0`
- **Example**: `RepairMinAltitude = 10.0`

#### `RepairMaxAltitude` *(v1.04)*
- **Type**: `Real` (altitude)
- **Description**: Maximum altitude for repair operations. Higher values allow higher altitude repairs. Lower values limit altitude for repairs
- **Default**: `0.0`
- **Example**: `RepairMaxAltitude = 100.0`

#### `RepairRatePerSecond` *(v1.04)*
- **Type**: `Real` (rate)
- **Description**: Rate of repair per second. Higher values create faster repair. Lower values create slower repair
- **Default**: `0.0`
- **Example**: `RepairRatePerSecond = 10.0`

#### `RepairWhenBelowHealth%` *(v1.04)*
- **Type**: `Int` (percentage)
- **Description**: Health percentage below which repair operations begin. Higher values trigger repair sooner. Lower values trigger repair later
- **Default**: `0`
- **Example**: `RepairWhenBelowHealth% = 75`

#### `RepairMinReadyTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Minimum time before repair operations can begin. Higher values create longer delays. Lower values allow faster repair initiation
- **Default**: `0`
- **Example**: `RepairMinReadyTime = 1000`

### Coordination Settings

#### `DistToTargetToGrantRangeBonus` *(v1.04)*
- **Type**: `Int` (distance)
- **Description**: Distance to target that grants range bonus. Higher values provide range bonus at greater distances. Lower values provide range bonus at closer distances
- **Default**: `0`
- **Example**: `DistToTargetToGrantRangeBonus = 50`

## Examples

### Basic Slaved Object
```ini
Behavior = SlavedUpdate ModuleTag_064
End
```

### Slaved Object with Ranges
```ini
Behavior = SlavedUpdate ModuleTag_07
  GuardMaxRange = 1 ;How far away from master I'm allowed when master is idle (doesn't wander)
  GuardWanderRange = 1 ;How far away I'm allowed to wander from master while guarding.
  AttackRange = 1 ;How far away from master I'm allowed when master is attacking a target.
End
```

### Slaved Object with Layer Control
```ini
Behavior = SlavedUpdate ModuleTag_05
  StayOnSameLayerAsMaster = Yes
End
```

## Template

```ini
Behavior = SlavedUpdate ModuleTag_XX
  ; Range Settings
  GuardMaxRange = 0                      ; // maximum guard range from master *(v1.04)*
  GuardWanderRange = 0                   ; // maximum wander range while guarding *(v1.04)*
  AttackRange = 0                        ; // maximum attack range from master *(v1.04)*
  AttackWanderRange = 0                  ; // maximum wander range while attacking *(v1.04)*
  ScoutRange = 0                         ; // maximum scout range from master *(v1.04)*
  ScoutWanderRange = 0                   ; // maximum wander range while scouting *(v1.04)*
  
  ; Repair Settings
  RepairRange = 0                        ; // maximum repair range from master *(v1.04)*
  RepairMinAltitude = 0.0                ; // minimum altitude for repair *(v1.04)*
  RepairMaxAltitude = 0.0                ; // maximum altitude for repair *(v1.04)*
  RepairRatePerSecond = 0.0              ; // repair rate per second *(v1.04)*
  RepairWhenBelowHealth% = 0             ; // health percentage to trigger repair *(v1.04)*
  RepairMinReadyTime = 0                 ; // minimum time before repair can begin *(v1.04)*
  
  ; Coordination Settings
  DistToTargetToGrantRangeBonus = 0      ; // distance to target for range bonus *(v1.04)*
End
```

## Notes

- SlavedUpdate provides sophisticated slaved object behavior and master-slave coordination
- The update manages range-based operations including guard, attack, scout, and repair ranges
- Repair operations provide maintenance capabilities for slaved objects
- Range parameters control slaved object behavior and positioning relative to master objects
- This update is commonly used by turrets, slaved weapons, and units operating under master control
- Slaved coordination creates realistic master-slave object relationships and tactical positioning

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h), [`SlavedUpdateInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SlavedUpdate.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SlavedUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SlavedUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/SlavedUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/SlavedUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet