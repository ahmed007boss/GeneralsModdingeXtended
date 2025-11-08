# BridgeBehavior

Update module that manages bridge structures, including tower connections, destruction sequences, and bridge functionality.

## Overview

BridgeBehavior is an update module that manages the complex behavior of bridge structures in the game. It coordinates between bridge towers, manages bridge integrity, handles destruction sequences, and controls scaffolding operations. The module supports different bridge types and provides visual effects and object creation during bridge destruction sequences.

BridgeBehavior must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by bridge objects to coordinate between bridge towers, manage bridge integrity, and handle bridge-specific behaviors. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Designed specifically for bridge structures
- Requires proper bridge tower connections for functionality
- Cannot function without proper damage and update systems
- Requires proper FX and OCL templates for visual effects

**Conditions**:
- Multiple instances behavior: Multiple BridgeBehavior modules can exist independently, each managing different bridge systems
- Always active once assigned to an object
- Continuously manages bridge integrity and tower connections
- Creates realistic bridge operations with construction and destruction sequences

**Dependencies**:
- Depends on the damage system for bridge destruction
- Requires bridge tower objects for proper functionality
- Inherits functionality from UpdateModule, BridgeBehaviorInterface, and DamageModuleInterface

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Scaffolding Configuration](#scaffolding-configuration)
  - [Destruction Effects](#destruction-effects)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

### Scaffolding Configuration

#### `LateralScaffoldSpeed` *(v1.04)*
- **Type**: `Real` (velocity)
- **Description**: Speed at which scaffolding moves laterally during construction or destruction. Higher values create faster lateral movement. Lower values create slower, more controlled movement
- **Default**: `1.0`
- **Example**: `LateralScaffoldSpeed = 100.0`

#### `VerticalScaffoldSpeed` *(v1.04)*
- **Type**: `Real` (velocity)
- **Description**: Speed at which scaffolding moves vertically during construction or destruction. Higher values create faster vertical movement. Lower values create slower, more controlled movement
- **Default**: `1.0`
- **Example**: `VerticalScaffoldSpeed = 70.0`

### Destruction Effects

#### `BridgeDieFX` *(v1.04)*
- **Type**: `FXList` (see [FXList documentation](../FXList.md))
- **Description**: FX list executed during bridge destruction with timing and bone location information. When set, displays visual effects during destruction. When empty (default), no destruction effects are shown
- **Default**: `""` (empty)
- **Example**: `BridgeDieFX = FX_BridgeDestruction Delay:1000 <Bone:MainSpan>`

#### `BridgeDieOCL` *(v1.04)*
- **Type**: `ObjectCreationList` (see [ObjectCreationList documentation](../ObjectCreationList.md))
- **Description**: Object creation list executed during bridge destruction with timing and bone location information. When set, creates objects during destruction. When empty (default), no objects are created
- **Default**: `""` (empty)
- **Example**: `BridgeDieOCL = OCL_BridgeDebris Delay:500 <Bone:SupportBeam>`

## Examples

### System Bridge Behavior
```ini
Behavior = BridgeBehavior ModuleTag_03
  LateralScaffoldSpeed = 100.0
  VerticalScaffoldSpeed = 70.0
End
```

### Civilian Building Bridge
```ini
Behavior = BridgeBehavior ModuleTag_03
  LateralScaffoldSpeed = 80.0
  VerticalScaffoldSpeed = 60.0
End
```

### System Bridge with Destruction Effects
```ini
Behavior = BridgeBehavior ModuleTag_05
  LateralScaffoldSpeed = 120.0
  VerticalScaffoldSpeed = 90.0
  BridgeDieFX = FX_BridgeDestruction Delay:1000 <Bone:MainSpan>
  BridgeDieOCL = OCL_BridgeDebris Delay:500 <Bone:SupportBeam>
End
```

## Template

```ini
Behavior = BridgeBehavior ModuleTag_XX
  ; Scaffolding Configuration
  LateralScaffoldSpeed = 1.0            ; // lateral scaffolding movement speed *(v1.04)*
  VerticalScaffoldSpeed = 1.0           ; // vertical scaffolding movement speed *(v1.04)*
  
  ; Destruction Effects
  BridgeDieFX =                         ; // FX list for bridge destruction *(v1.04)*
  BridgeDieOCL =                        ; // OCL for bridge destruction *(v1.04)*
End
```

## Notes

- BridgeBehavior manages complex bridge operations including construction and destruction sequences
- The module coordinates between bridge towers and manages bridge integrity
- Scaffolding operations can be controlled with configurable movement speeds
- Destruction sequences support timed effects and object creation at specific bone locations
- This creates realistic bridge behavior with proper construction and destruction mechanics

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h), [`BridgeBehaviorInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BridgeBehavior.h), [`DamageModuleInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DamageModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BridgeBehavior.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BridgeBehavior.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehavior.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehavior.cpp)
