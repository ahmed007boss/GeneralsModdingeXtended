# POWTruckAIUpdate

POWTruckAIUpdate provides AI update functionality for Prisoner of War (POW) truck units.

## Overview

The `POWTruckAIUpdate` class manages AI-driven prisoner capture, transport, and delivery operations for POW truck units. It handles prisoner loading, transport to prison facilities, and coordination with prison systems. This update is commonly used by POW truck units that capture enemy personnel and transport them to prison facilities for interrogation or detention.

## Usage

Used by POW truck units to handle AI-driven prisoner capture, transport, and delivery operations. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Prisoner operations are limited by boredom time and prison distance parameters
- Prisoner capture depends on valid targets and prison availability
- Transport operations are controlled by AI task management
- Prison coordination requires proper prison facility integration

**Conditions**:
- POWTruckAIUpdate manages complete prisoner capture and transport lifecycle
- The update handles prisoner loading, transport, and delivery to prison facilities
- Boredom time controls how long trucks wait before seeking new targets
- Prison distance parameters control proximity requirements for prison operations
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own prisoner operations

**Dependencies**:
- Requires prison system integration for prisoner delivery
- Uses AI system for autonomous prisoner capture behavior
- Integrates with transport system for prisoner movement

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [AI Behavior Settings](#ai-behavior-settings)
  - [Prison Coordination Settings](#prison-coordination-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### AI Behavior Settings

#### `BoredTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time after which the POW truck becomes bored and seeks new targets in automatic mode. Higher values allow longer waiting periods. Lower values make trucks more aggressive in seeking targets
- **Default**: `0`
- **Example**: `BoredTime = 30000`

### Prison Coordination Settings

#### `AtPrisonDistance` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Distance from prison considered "at the prison" for waiting and coordination purposes. Higher values provide larger coordination zones. Lower values require closer proximity to prisons
- **Default**: `0.0`
- **Example**: `AtPrisonDistance = 50.0`

## Examples

### Basic POW Truck
```ini
Behavior = POWTruckAIUpdate ModuleTag_04
  BoredTime = 30000
  AtPrisonDistance = 50.0
End
```

### Aggressive POW Truck
```ini
Behavior = POWTruckAIUpdate ModuleTag_05
  BoredTime = 15000
  AtPrisonDistance = 30.0
End
```

### Patient POW Truck
```ini
Behavior = POWTruckAIUpdate ModuleTag_06
  BoredTime = 60000
  AtPrisonDistance = 75.0
End
```

## Template

```ini
Behavior = POWTruckAIUpdate ModuleTag_XX
  ; AI Behavior Settings
  BoredTime = 0                         ; // time before seeking new targets *(v1.04)*
  
  ; Prison Coordination Settings
  AtPrisonDistance = 0.0                ; // distance considered "at prison" *(v1.04)*
End
```

## Notes

- POWTruckAIUpdate provides sophisticated AI-driven prisoner capture and transport mechanics
- The update manages complete prisoner lifecycle from capture to delivery
- Boredom time creates realistic AI behavior patterns for POW truck operations
- Prison coordination ensures proper prisoner delivery and facility management
- This update is commonly used by POW truck units, prisoner transport vehicles, and interrogation units
- AI task management provides autonomous prisoner capture and transport capabilities

## Source Files

**Base Class:** [`AIUpdateInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h), [`POWTruckAIUpdateInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/POWTruckAIUpdate.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/POWTruckAIUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/POWTruckAIUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/POWTruckAIUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/POWTruckAIUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet