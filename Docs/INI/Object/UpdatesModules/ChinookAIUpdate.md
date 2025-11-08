# ChinookAIUpdate

AI update module that provides AI functionality for Chinook helicopter units with supply transport capabilities, auto-acquisition systems, and rotor wash effects.

## Overview

ChinookAIUpdate is an AI update module that provides AI functionality for Chinook helicopter units. It handles AI-driven flight operations, supply transport, combat missions, and helicopter-specific behaviors. The module manages supply center and warehouse interactions, auto-acquisition systems, and visual effects like rotor wash.

ChinookAIUpdate must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by Chinook helicopters to handle AI-driven flight operations, transport, and combat missions. This is an **AI update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Designed specifically for Chinook helicopter units
- Requires proper AI and supply systems for functionality
- Cannot function without proper update and AI systems
- Supply operations are limited by helicopter capacity and range

**Conditions**:
- Multiple instances behavior: Multiple ChinookAIUpdate modules can exist independently, each managing different Chinook systems
- Always active once assigned to an object
- Continuously manages AI-driven flight and supply operations
- Creates specialized AI behaviors for Chinook helicopter units

**Dependencies**:
- Depends on the AI system for flight and combat decisions
- Requires proper supply system for transport operations
- Inherits functionality from SupplyTruckAIUpdate

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Supply Configuration](#supply-configuration)
  - [AI Behavior](#ai-behavior)
  - [Visual Effects](#visual-effects)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

### Supply Configuration

#### `MaxBoxes` *(v1.04)*
- **Type**: `UnsignedInt`
- **Description**: Maximum number of supply boxes the Chinook can carry. Higher values increase transport capacity but may affect flight performance. Lower values reduce capacity but improve flight characteristics. At 8 (default), the Chinook can carry 8 supply boxes
- **Default**: `8`
- **Example**: `MaxBoxes = 8`

#### `SupplyCenterActionDelay` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time delay for supply center operations including loading and unloading. Higher values create slower supply operations. Lower values create faster supply operations. At 3000 (default), supply center operations take 3 seconds
- **Default**: `3000`
- **Example**: `SupplyCenterActionDelay = 3000`

#### `SupplyWarehouseActionDelay` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time delay per supply box for warehouse operations. Higher values create slower per-box operations. Lower values create faster per-box operations. At 1250 (default), each box takes 1.25 seconds
- **Default**: `1250`
- **Example**: `SupplyWarehouseActionDelay = 1250`

#### `SupplyWarehouseScanDistance` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Maximum distance to scan for supply warehouses before returning home. Higher values allow searching farther for warehouses. Lower values limit warehouse search range. At 700 (default), searches within 700 units
- **Default**: `700.0`
- **Example**: `SupplyWarehouseScanDistance = 700`

#### `SuppliesDepletedVoice` *(v1.04)*
- **Type**: `AsciiString` (see [Voice documentation](../../Voice.md))
- **Description**: Voice message played when supplies are depleted. When set, plays audio message when Chinook runs out of supplies. When empty (default), no voice message is played
- **Default**: `""` (empty)
- **Example**: `SuppliesDepletedVoice = ChinookVoiceSuppliesDepleted`

### AI Behavior

#### `AutoAcquireEnemiesWhenIdle` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether the Chinook automatically acquires enemy targets when idle. When true, the Chinook will engage enemies when not performing other tasks. When false (default), the Chinook will not automatically engage enemies
- **Default**: `No`
- **Example**: `AutoAcquireEnemiesWhenIdle = Yes`

#### `MoodAttackCheckRate` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time interval for checking attack mood and target acquisition. Higher values check less frequently but use fewer resources. Lower values check more frequently for faster target acquisition. At 333 (default), checks every 333 milliseconds
- **Default**: `333`
- **Example**: `MoodAttackCheckRate = 333`

### Visual Effects

#### `RotorWashParticleSystem` *(v1.04)*
- **Type**: `ParticleSystemTemplate` (see [ParticleSystem documentation](../../ParticleSystem.md))
- **Description**: Particle system for rotor wash effects. When set, displays rotor wash particle effects during flight. When empty (default), no rotor wash effects are shown
- **Default**: `""` (empty)
- **Example**: `RotorWashParticleSystem = HelixRotorWashRing`

## Examples

### Basic Chinook AI Update
```ini
Behavior = ChinookAIUpdate ModuleTag_07
  MaxBoxes = 8
  SupplyCenterActionDelay = 3000
  SupplyWarehouseActionDelay = 1250
  SupplyWarehouseScanDistance = 700
  SuppliesDepletedVoice = ChinookVoiceSuppliesDepleted
End
```

### Combat Chinook AI Update
```ini
Behavior = ChinookAIUpdate ModuleTag_04
  AutoAcquireEnemiesWhenIdle = Yes
  MoodAttackCheckRate = 333
  RotorWashParticleSystem = HelixRotorWashRing
End
```

### Enhanced Chinook AI Update
```ini
Behavior = ChinookAIUpdate ModuleTag_05
  MaxBoxes = 8
  SupplyCenterActionDelay = 3500
  SupplyWarehouseActionDelay = 1250
  SupplyWarehouseScanDistance = 700
  SuppliesDepletedVoice = ChinookVoiceSuppliesDepleted
End
```

## Template

```ini
Behavior = ChinookAIUpdate ModuleTag_XX
  ; Supply Configuration
  MaxBoxes = 8                           ; // maximum supply boxes to carry *(v1.04)*
  SupplyCenterActionDelay = 3000         ; // milliseconds for supply center operations *(v1.04)*
  SupplyWarehouseActionDelay = 1250      ; // milliseconds per box for warehouse operations *(v1.04)*
  SupplyWarehouseScanDistance = 700.0    ; // maximum distance to scan for warehouses *(v1.04)*
  SuppliesDepletedVoice =                ; // voice message when supplies depleted *(v1.04)*
  
  ; AI Behavior
  AutoAcquireEnemiesWhenIdle = No        ; // whether to auto-acquire enemies when idle *(v1.04)*
  MoodAttackCheckRate = 333              ; // milliseconds between attack mood checks *(v1.04)*
  
  ; Visual Effects
  RotorWashParticleSystem =              ; // particle system for rotor wash effects *(v1.04)*
End
```

## Notes

- ChinookAIUpdate provides specialized AI behaviors for Chinook helicopter units
- The module manages supply transport operations with configurable capacity and timing
- Auto-acquisition systems enable autonomous combat behavior when idle
- Rotor wash effects enhance visual realism during flight operations
- This creates realistic helicopter AI with both transport and combat capabilities

## Source Files

**Base Class:** [`SupplyTruckAIUpdate`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyTruckAIUpdate.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/ChinookAIUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/ChinookAIUpdate.cpp)
