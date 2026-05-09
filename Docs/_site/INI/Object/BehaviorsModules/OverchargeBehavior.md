# OverchargeBehavior

Update module that provides overcharge functionality for power plants, allowing increased power production at the cost of health drain.

## Overview

OverchargeBehavior is an update module that enables objects (typically power plants) to enter an overcharge state that increases their power production while gradually draining their health. The module provides toggle functionality and health-based restrictions to prevent overcharge when the object is too damaged. This creates a risk-reward mechanic where players can temporarily boost power output at the expense of object health.

OverchargeBehavior must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that should have overcharge functionality allowing increased power production at the cost of health drain. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Requires objects to have power production capabilities
- Cannot overcharge when health is below the specified threshold
- Health drain continues until overcharge is disabled
- Requires proper power production system integration

**Conditions**:
- Multiple instances behavior: Multiple OverchargeBehavior modules can exist independently, each providing different overcharge effects
- Always active once assigned to an object
- Can be toggled on/off by the player
- Creates tactical decisions between power output and object longevity

**Dependencies**:
- Requires objects with power production capabilities
- Depends on the damage system for health management
- Inherits functionality from UpdateModule and DamageModuleInterface

## Properties

### Health Management

#### `HealthPercentToDrainPerSecond` *(v1.04)*
- **Type**: `Real` (percentage)
- **Description**: Percentage of health drained per second while overcharge is active. Higher values cause faster health drain. When set to 0 (default), no health drain occurs
- **Default**: `0.0`
- **Example**: `HealthPercentToDrainPerSecond = 0.05`

#### `NotAllowedWhenHealthBelowPercent` *(v1.04)*
- **Type**: `Real` (percentage)
- **Description**: Health percentage threshold below which overcharge is not allowed. When object health is below this percentage, overcharge cannot be activated. When set to 0 (default), no health restriction is applied
- **Default**: `0.0`
- **Example**: `NotAllowedWhenHealthBelowPercent = 0.25`

## Examples

### Basic Overcharge
```ini
Update = OverchargeBehavior ModuleTag_01
  HealthPercentToDrainPerSecond = 0.02
  NotAllowedWhenHealthBelowPercent = 0.3
End
```

### High-Risk Overcharge
```ini
Update = OverchargeBehavior ModuleTag_02
  HealthPercentToDrainPerSecond = 0.1
  NotAllowedWhenHealthBelowPercent = 0.5
End
```

### Safe Overcharge
```ini
Update = OverchargeBehavior ModuleTag_03
  HealthPercentToDrainPerSecond = 0.01
  NotAllowedWhenHealthBelowPercent = 0.1
End
```

## Template

```ini
Update = OverchargeBehavior ModuleTag_XX
  ; Health Management
  HealthPercentToDrainPerSecond = 0.0   ; // health drain rate per second *(v1.04)*
  NotAllowedWhenHealthBelowPercent = 0.0 ; // health threshold for overcharge restriction *(v1.04)*
End
```

## Notes

- OverchargeBehavior provides overcharge functionality for power plants and similar objects
- Increases power production while gradually draining object health
- Includes health-based restrictions to prevent overcharge when objects are too damaged
- Commonly used for power plants and energy-generating structures
- The module manages overcharge state and health drain automatically
- Creates tactical decisions between power output and object longevity

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/OverchargeBehavior.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/OverchargeBehavior.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/OverchargeBehavior.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/OverchargeBehavior.cpp)