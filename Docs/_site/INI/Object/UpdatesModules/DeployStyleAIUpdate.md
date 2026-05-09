# DeployStyleAIUpdate

AI update module that provides AI functionality for deployable units and structures with configurable pack/unpack timing and turret functionality controls.

## Overview

DeployStyleAIUpdate is an AI update module that provides AI functionality for deployable units and structures. It handles AI-driven deployment logic, pack and unpack timing, and deployment mode management. The module supports configurable deployment animations and turret functionality controls that depend on deployment state.

DeployStyleAIUpdate must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by units that can deploy into different modes or structures with AI-driven deployment logic. This is an **AI update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Designed specifically for deployable units and structures
- Requires proper AI and deployment systems for functionality
- Cannot function without proper update and AI systems
- Deployment operations are limited by animation timing and positioning

**Conditions**:
- Multiple instances behavior: Multiple DeployStyleAIUpdate modules can exist independently, each managing different deployment systems
- Always active once assigned to an object
- Continuously manages AI-driven deployment and mode switching operations
- Creates specialized AI behaviors for deployable units

**Dependencies**:
- Depends on the AI system for deployment decisions
- Requires proper deployment system for mode switching operations
- Inherits functionality from AIUpdateInterface

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Timing Configuration](#timing-configuration)
  - [Functionality Control](#functionality-control)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

### Timing Configuration

#### `PackTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time required to pack the unit from deployed to mobile state. Higher values create slower packing operations. Lower values create faster packing operations. At 1667 (default), packing takes 1.667 seconds
- **Default**: `1667`
- **Example**: `PackTime = 1667`

#### `UnpackTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time required to unpack the unit from mobile to deployed state. Higher values create slower unpacking operations. Lower values create faster unpacking operations. At 1667 (default), unpacking takes 1.667 seconds
- **Default**: `1667`
- **Example**: `UnpackTime = 1667`

### Functionality Control

#### `TurretsFunctionOnlyWhenDeployed` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether turrets only function when the unit is deployed. When true, turrets are disabled in mobile mode and enabled in deployed mode. When false (default), turrets function in all modes
- **Default**: `No`
- **Example**: `TurretsFunctionOnlyWhenDeployed = Yes`

#### `ManualDeployAnimations` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether deployment animations are manually controlled. When true, animations are manually triggered and managed. When false (default), animations are automatically managed by the deployment system
- **Default**: `Yes`
- **Example**: `ManualDeployAnimations = No`

## Examples

### Basic Deploy Style AI
```ini
Behavior = DeployStyleAIUpdate ModuleTag_04
  PackTime = 1667
  UnpackTime = 1667
  TurretsFunctionOnlyWhenDeployed = Yes
End
```

### Fast Deploy Style AI
```ini
Behavior = DeployStyleAIUpdate ModuleTag_03
  PackTime = 500
  UnpackTime = 600
  ManualDeployAnimations = No
End
```

### Slow Deploy Style AI
```ini
Behavior = DeployStyleAIUpdate ModuleTag_05
  PackTime = 3000
  UnpackTime = 3000
  TurretsFunctionOnlyWhenDeployed = Yes
End
```

## Template

```ini
Behavior = DeployStyleAIUpdate ModuleTag_XX
  ; Timing Configuration
  PackTime = 1667                           ; // milliseconds to pack from deployed to mobile *(v1.04)*
  UnpackTime = 1667                         ; // milliseconds to unpack from mobile to deployed *(v1.04)*
  
  ; Functionality Control
  TurretsFunctionOnlyWhenDeployed = No      ; // whether turrets only work when deployed *(v1.04)*
  ManualDeployAnimations = Yes              ; // whether deployment animations are manual *(v1.04)*
End
```

## Notes

- DeployStyleAIUpdate provides specialized AI behaviors for deployable units
- The module manages pack and unpack timing with configurable deployment speeds
- Turret functionality can be tied to deployment state for tactical gameplay
- Manual animation control allows for custom deployment sequences
- This creates realistic deployment mechanics with proper timing and functionality controls

## Source Files

**Base Class:** [`AIUpdateInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DeployStyleAIUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DeployStyleAIUpdate.cpp)
