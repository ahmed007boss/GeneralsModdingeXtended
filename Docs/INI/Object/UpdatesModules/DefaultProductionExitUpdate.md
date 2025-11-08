# DefaultProductionExitUpdate

Update module that provides default production exit functionality for objects that produce other objects with configurable unit creation points and rally points.

## Overview

DefaultProductionExitUpdate is an update module that provides default production exit functionality for objects that produce other objects. It manages unit creation points where produced units spawn and natural rally points where units move after creation. The module handles standard exit mechanics for production buildings and facilities.

DefaultProductionExitUpdate must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by production buildings and facilities that need standard exit mechanics for produced units. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Requires proper production system integration for functionality
- Cannot function without proper update and production systems
- Exit mechanics are limited by building geometry and positioning
- Requires proper unit movement system integration

**Conditions**:
- Multiple instances behavior: Multiple DefaultProductionExitUpdate modules can exist independently, each managing different exit systems
- Always active once assigned to an object
- Continuously manages unit creation and rally point positioning
- Creates standard production exit mechanics for buildings

**Dependencies**:
- Depends on the production system for unit creation
- Requires proper update system for exit management
- Inherits functionality from UpdateModule and ExitInterface

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Exit Configuration](#exit-configuration)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

### Exit Configuration

#### `UnitCreatePoint` *(v1.04)*
- **Type**: `Coord3D` (coordinate)
- **Description**: Location where produced units are created relative to the building. When set, units spawn at the specified coordinates. When empty (default), units spawn at the building's center
- **Default**: `X:0 Y:0 Z:0`
- **Example**: `UnitCreatePoint = X:10 Y:23 Z:0`

#### `NaturalRallyPoint` *(v1.04)*
- **Type**: `Coord3D` (coordinate)
- **Description**: Default rally point where produced units move after creation. When set, units automatically move to this location after spawning. When empty (default), units remain at the creation point
- **Default**: `X:0 Y:0 Z:0`
- **Example**: `NaturalRallyPoint = X:25 Y:23 Z:0`

## Examples

### Basic Production Exit
```ini
Behavior = DefaultProductionExitUpdate ModuleTag_Production02
  UnitCreatePoint = X:10 Y:23 Z:0
  NaturalRallyPoint = X:25 Y:23 Z:0
End
```

### Side Exit Production
```ini
Behavior = DefaultProductionExitUpdate ModuleTag_06
  UnitCreatePoint = X:5.0 Y:0.0 Z:0.0
  NaturalRallyPoint = X:65.0 Y:0.0 Z:0.0
End
```

### Rear Exit Production
```ini
Behavior = DefaultProductionExitUpdate ModuleTag_11
  UnitCreatePoint = X:-10.0 Y:-30.0 Z:0.0
  NaturalRallyPoint = X:53.0 Y:-30.0 Z:0.0
End
```

## Template

```ini
Behavior = DefaultProductionExitUpdate ModuleTag_XX
  ; Exit Configuration
  UnitCreatePoint = X:0 Y:0 Z:0           ; // coordinates where units are created *(v1.04)*
  NaturalRallyPoint = X:0 Y:0 Z:0         ; // coordinates where units move after creation *(v1.04)*
End
```

## Notes

- DefaultProductionExitUpdate provides standard production exit mechanics for buildings
- The module manages unit creation points and natural rally points for produced units
- Configurable coordinates allow for flexible unit spawning and positioning
- This creates realistic production flow with proper unit placement and movement

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h), [`ExitInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DefaultProductionExitUpdate.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ProductionExitUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ProductionExitUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/DefaultProductionExitUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/DefaultProductionExitUpdate.cpp)
