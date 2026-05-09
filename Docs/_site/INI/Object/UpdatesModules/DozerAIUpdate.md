# DozerAIUpdate

AI update module that provides AI functionality for dozer units and construction vehicles with repair capabilities and autonomous behavior systems.

## Overview

DozerAIUpdate is an AI update module that provides AI functionality for dozer units and construction vehicles. It handles AI-driven construction, repair, and building operations with configurable repair rates, boredom behavior, and autonomous operation capabilities. The module manages repair operations, idle behavior, and construction coordination.

DozerAIUpdate must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by dozer units to handle AI-driven construction, repair, and building operations. This is an **AI update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Designed specifically for dozer and construction units
- Requires proper AI and construction systems for functionality
- Cannot function without proper update and AI systems
- Construction operations are limited by unit capabilities and positioning

**Conditions**:
- Multiple instances behavior: Multiple DozerAIUpdate modules can exist independently, each managing different dozer systems
- Always active once assigned to an object
- Continuously manages AI-driven construction and repair operations
- Creates specialized AI behaviors for construction and repair units

**Dependencies**:
- Depends on the AI system for construction and repair decisions
- Requires proper construction system for building operations
- Inherits functionality from AIUpdateInterface and DozerAIInterface

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Repair Configuration](#repair-configuration)
  - [Behavior Configuration](#behavior-configuration)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

### Repair Configuration

#### `RepairHealthPercentPerSecond` *(v1.04)*
- **Type**: `Real` (percentage)
- **Description**: Percentage of maximum health repaired per second during repair operations. Higher values provide faster repair rates. Lower values provide slower repair rates. At 2% (default), repairs 2% of max health per second
- **Default**: `0.02` (2%)
- **Example**: `RepairHealthPercentPerSecond = 2%`

### Behavior Configuration

#### `BoredTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time before the dozer becomes bored and looks for work. Higher values create less frequent autonomous behavior. Lower values create more frequent autonomous behavior. At 5000 (default), becomes bored after 5 seconds of inactivity
- **Default**: `5000`
- **Example**: `BoredTime = 5000`

#### `BoredRange` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Range within which the dozer looks for work when bored. Higher values extend the search range for repair targets. Lower values limit the search range. At 150 (default), searches within 150 units when bored
- **Default**: `150.0`
- **Example**: `BoredRange = 150`

## Examples

### Basic Dozer AI
```ini
Behavior = DozerAIUpdate ModuleTag_03
  RepairHealthPercentPerSecond = 2%
  BoredTime = 5000
  BoredRange = 150
End
```

### Fast Repair Dozer AI
```ini
Behavior = DozerAIUpdate ModuleTag_03
  RepairHealthPercentPerSecond = 3%
  BoredTime = 5000
  BoredRange = 200
End
```

### Patient Dozer AI
```ini
Behavior = DozerAIUpdate ModuleTag_04
  RepairHealthPercentPerSecond = 2%
  BoredTime = 10000
  BoredRange = 100
End
```

## Template

```ini
Behavior = DozerAIUpdate ModuleTag_XX
  ; Repair Configuration
  RepairHealthPercentPerSecond = 0.02  ; // percentage of max health repaired per second *(v1.04)*
  
  ; Behavior Configuration
  BoredTime = 5000                     ; // milliseconds before becoming bored *(v1.04)*
  BoredRange = 150.0                   ; // distance to search for work when bored *(v1.04)*
End
```

## Notes

- DozerAIUpdate provides specialized AI behaviors for construction and repair units
- The module manages repair rates with configurable health restoration per second
- Boredom behavior enables autonomous work-seeking when idle
- Configurable search ranges allow for flexible autonomous operation
- This creates realistic construction unit AI with proper repair and autonomous behaviors

## Source Files

**Base Class:** [`AIUpdateInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h), [`DozerAIInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DozerAIUpdate.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerAIUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerAIUpdate.cpp)
