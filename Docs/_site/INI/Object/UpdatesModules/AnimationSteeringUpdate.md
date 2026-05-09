# AnimationSteeringUpdate

Update module that provides animation steering functionality for objects with animated movement and configurable transition timing.

## Overview

AnimationSteeringUpdate is an update module that provides animation steering functionality for objects with animated movement. It handles animation-based steering and movement control for objects that use animated locomotion. The module supports configurable transition timing to control how smoothly objects transition between different movement states.

AnimationSteeringUpdate must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that need animation-based steering and movement control. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Requires proper animation system integration for functionality
- Cannot function without proper update and animation systems
- Animation steering is limited to animated objects
- Requires proper transition timing configuration

**Conditions**:
- Multiple instances behavior: Multiple AnimationSteeringUpdate modules can exist independently, each managing different animation steering systems
- Always active once assigned to an object
- Continuously manages animation-based steering and movement control
- Creates smooth animated movement with configurable transitions

**Dependencies**:
- Depends on the animation system for movement control
- Requires proper update system for continuous management
- Inherits all functionality from UpdateModule

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Transition Configuration](#transition-configuration)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

### Transition Configuration

#### `MinTransitionTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Minimum time for transition between different movement states. Higher values create slower, more gradual transitions. Lower values create faster, more abrupt transitions. At 300 (default), transitions take at least 300 milliseconds
- **Default**: `300`
- **Example**: `MinTransitionTime = 300`

## Examples

### Basic Animation Steering
```ini
Behavior = AnimationSteeringUpdate ModuleTag_SteerUpdate
  MinTransitionTime = 300
End
```

### Fast Animation Steering
```ini
Behavior = AnimationSteeringUpdate ModuleTag_17
  MinTransitionTime = 150
End
```

### Slow Animation Steering
```ini
Behavior = AnimationSteeringUpdate ModuleTag_09
  MinTransitionTime = 600
End
```

## Template

```ini
Behavior = AnimationSteeringUpdate ModuleTag_XX
  ; Transition Configuration
  MinTransitionTime = 300             ; // minimum transition time in milliseconds *(v1.04)*
End
```

## Notes

- AnimationSteeringUpdate provides smooth animation-based movement control for objects
- The module handles animation steering and movement transitions with configurable timing
- Transition timing controls how smoothly objects change between different movement states
- This creates realistic animated movement with proper steering mechanics

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/AnimationSteeringUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/AnimationSteeringUpdate.cpp)
