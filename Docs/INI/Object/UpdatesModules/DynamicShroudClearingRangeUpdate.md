# DynamicShroudClearingRangeUpdate

Update module that provides dynamic shroud clearing range functionality for objects that can clear fog of war with configurable vision range changes and timing.

## Overview

DynamicShroudClearingRangeUpdate is an update module that provides dynamic shroud clearing range functionality for objects that can clear fog of war. It manages dynamic vision range changes over time, configurable shrink delays and timing, and gradual vision range reduction. The module supports objects that start with full vision and gradually lose their shroud clearing capabilities.

DynamicShroudClearingRangeUpdate must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that can clear shroud or fog of war with dynamic range that changes over time. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Requires proper shroud system integration for functionality
- Cannot function without proper update and shroud systems
- Vision range changes are limited by configured timing parameters
- Requires proper shroud clearing system integration

**Conditions**:
- Multiple instances behavior: Multiple DynamicShroudClearingRangeUpdate modules can exist independently, each managing different shroud systems
- Always active once assigned to an object
- Continuously manages dynamic vision range changes and shroud clearing
- Creates dynamic shroud clearing capabilities with configurable timing

**Dependencies**:
- Depends on the shroud system for vision range management
- Requires proper update system for dynamic range changes
- Inherits all functionality from UpdateModule

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Vision Configuration](#vision-configuration)
  - [Timing Configuration](#timing-configuration)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

### Vision Configuration

#### `FinalVision` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Final vision range after shrinking is complete. Higher values maintain better vision after shrinking. Lower values reduce vision significantly. At 0.0 (default), no vision remains after shrinking
- **Default**: `0.0`
- **Example**: `FinalVision = 0.0`

### Timing Configuration

#### `ShrinkDelay` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time delay before vision range starts shrinking. Higher values maintain full vision longer. Lower values start shrinking sooner. At 5000 (default), shrinking begins after 5 seconds
- **Default**: `5000`
- **Example**: `ShrinkDelay = 5000`

#### `ShrinkTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Duration of the vision range shrinking process. Higher values create slower, more gradual shrinking. Lower values create faster shrinking. At 2500 (default), shrinking takes 2.5 seconds
- **Default**: `2500`
- **Example**: `ShrinkTime = 2500`

#### `ChangeInterval` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time interval between vision range updates during shrinking. Higher values create less frequent updates but smoother transitions. Lower values create more frequent updates. At 50 (default), updates every 50 milliseconds
- **Default**: `50`
- **Example**: `ChangeInterval = 50`

## Examples

### Basic Dynamic Shroud Clearing
```ini
Behavior = DynamicShroudClearingRangeUpdate ModuleTag_02
  FinalVision = 0.0
  ShrinkDelay = 5000
  ShrinkTime = 2500
End
```

### Partial Vision Retention
```ini
Behavior = DynamicShroudClearingRangeUpdate ModuleTag_04
  FinalVision = 300.0
  ChangeInterval = 50
  ShrinkDelay = 2000
End
```

### Extended Vision Duration
```ini
Behavior = DynamicShroudClearingRangeUpdate ModuleTag_03
  FinalVision = 0.0
  ShrinkDelay = 10000
  ShrinkTime = 5000
End
```

## Template

```ini
Behavior = DynamicShroudClearingRangeUpdate ModuleTag_XX
  ; Vision Configuration
  FinalVision = 0.0                       ; // final vision range after shrinking *(v1.04)*
  
  ; Timing Configuration
  ShrinkDelay = 5000                      ; // milliseconds before shrinking starts *(v1.04)*
  ShrinkTime = 2500                       ; // milliseconds for shrinking duration *(v1.04)*
  ChangeInterval = 50                     ; // milliseconds between vision updates *(v1.04)*
End
```

## Notes

- DynamicShroudClearingRangeUpdate provides dynamic vision range changes for shroud clearing
- The module manages gradual vision range reduction with configurable timing
- Objects can start with full vision and gradually lose their shroud clearing capabilities
- This creates realistic temporary vision mechanics for reconnaissance units and effects

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/DynamicShroudClearingRangeUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/DynamicShroudClearingRangeUpdate.cpp)
