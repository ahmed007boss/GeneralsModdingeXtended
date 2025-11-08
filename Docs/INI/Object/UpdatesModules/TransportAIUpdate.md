# TransportAIUpdate

TransportAIUpdate provides AI update functionality for transport vehicle units.

## Overview

The `TransportAIUpdate` class manages AI-driven transport operations for transport vehicle units including cargo management, transport coordination, and logistics operations. It handles transport behavior, turret systems, and transport system integration. This update is commonly used by transport vehicle units, logistics vehicles, and units that manage cargo transport.

## Usage

Used by transport vehicles to handle AI-driven transport operations, cargo management, and logistics. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Transport operations are limited by AI behavior and transport parameters
- Transport coordination depends on proper transport system integration
- Cargo management is controlled by transport capacity and logistics parameters
- Transport effectiveness varies based on transport capabilities

**Conditions**:
- TransportAIUpdate manages AI-driven transport operations and cargo management
- The update handles transport behavior, turret systems, and transport coordination
- Transport operations provide cargo management and logistics capabilities
- AI behavior creates autonomous transport operations
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own transport parameters

**Dependencies**:
- Uses AI system for autonomous transport behavior
- Integrates with transport system for cargo management
- Uses turret system for transport defense capabilities

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [AI Behavior Settings](#ai-behavior-settings)
  - [Turret Settings](#turret-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### AI Behavior Settings

#### `AutoAcquireEnemiesWhenIdle` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether to automatically acquire enemies when idle. When true, automatically acquires enemies. When false, manual target acquisition required
- **Default**: `No`
- **Example**: `AutoAcquireEnemiesWhenIdle = Yes`

### Turret Settings

#### `TurretTurnRate` *(v1.04)*
- **Type**: `Real` (degrees per second)
- **Description**: Rate at which turret turns. Higher values create faster turret turning. Lower values create slower turret turning
- **Default**: `0.0`
- **Example**: `TurretTurnRate = 180`

#### `ControlledWeaponSlots` *(v1.04)*
- **Type**: `WeaponSlotType` (bit flags)
- **Description**: Weapon slots controlled by turret. When set, specified slots are controlled. When empty, no slots are controlled
- **Default**: `0`
- **Example**: `ControlledWeaponSlots = PRIMARY SECONDARY`

#### `RecenterTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time to wait during idle before recentering turret. Higher values create longer delays. Lower values create shorter delays
- **Default**: `0`
- **Example**: `RecenterTime = 5000`

## Examples

### Basic Transport AI
```ini
Behavior = TransportAIUpdate ModuleTag_03
  Turret
    TurretTurnRate = 180
    RecenterTime = 5000   ; how long to wait during idle before recentering
End
```

### Transport AI with Weapon Control
```ini
Behavior = TransportAIUpdate ModuleTag_03
  Turret
    ControlledWeaponSlots = PRIMARY SECONDARY
    TurretTurnRate        = 280
End
```

### Transport AI with Auto Acquisition
```ini
Behavior = TransportAIUpdate ModuleTag_15
  AutoAcquireEnemiesWhenIdle = Yes
  Turret
    TurretTurnRate = 120
End
```

## Template

```ini
Behavior = TransportAIUpdate ModuleTag_XX
  ; AI Behavior Settings
  AutoAcquireEnemiesWhenIdle = No        ; // whether to auto-acquire enemies when idle *(v1.04)*
  
  ; Turret Settings
  TurretTurnRate = 0.0                   ; // rate at which turret turns *(v1.04)*
  ControlledWeaponSlots =                ; // weapon slots controlled by turret *(v1.04)*
  RecenterTime = 0                       ; // time to wait before recentering turret *(v1.04)*
End
```

## Notes

- TransportAIUpdate provides sophisticated AI-driven transport operations and cargo management
- The update manages transport behavior, turret systems, and transport coordination
- Transport operations provide essential cargo management and logistics capabilities
- AI behavior creates autonomous transport operations for efficient cargo transport
- This update is commonly used by transport vehicle units, logistics vehicles, and cargo transport units
- Transport coordination ensures efficient cargo management and logistics operations

## Source Files

**Base Class:** [`AIUpdateInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/TransportAIUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/TransportAIUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/TransportAIUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/TransportAIUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet