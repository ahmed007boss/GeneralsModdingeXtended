# RebuildHoleBehavior

Update module that provides functionality for rebuilding destroyed structures or filling holes left by destroyed objects with worker spawning and health regeneration.

## Overview

RebuildHoleBehavior is an update module that provides functionality for rebuilding destroyed structures or filling holes in the terrain left by destroyed buildings. It manages worker object spawning, health regeneration of rebuild holes, and coordinates the rebuilding process. The module supports configurable worker types, respawn delays, and health regeneration rates.

RebuildHoleBehavior must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that can rebuild destroyed structures or fill holes in the terrain left by destroyed buildings. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Requires valid worker object templates for rebuilding functionality
- Cannot function without proper update and death systems
- Worker respawn is limited by configured delay timing
- Health regeneration is limited to specified percentage rates

**Conditions**:
- Multiple instances behavior: Multiple RebuildHoleBehavior modules can exist independently, each managing different rebuild systems
- Always active once assigned to an object
- Continuously manages worker spawning and hole health regeneration
- Creates automated rebuilding capabilities with worker coordination

**Dependencies**:
- Depends on the update system for continuous management
- Requires proper worker object templates for rebuilding operations
- Inherits functionality from UpdateModule, DieModuleInterface, and RebuildHoleBehaviorInterface

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Worker Configuration](#worker-configuration)
  - [Health Regeneration](#health-regeneration)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

### Worker Configuration

#### `WorkerObjectName` *(v1.04)*
- **Type**: `AsciiString` (see [Object documentation](../Object.md))
- **Description**: Name of the worker object template to spawn for rebuilding operations. When set, creates workers to rebuild destroyed structures. When empty (default), no workers are spawned
- **Default**: `""` (empty)
- **Example**: `WorkerObjectName = GLAInfantryWorker`

#### `WorkerRespawnDelay` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time delay before respawning workers after they are destroyed or removed. Higher values require longer waiting periods before new workers appear. Lower values provide faster worker replacement. At 20000 (default), workers respawn after 20 seconds
- **Default**: `20000`
- **Example**: `WorkerRespawnDelay = 20000`

### Health Regeneration

#### `HoleHealthRegen%PerSecond` *(v1.04)*
- **Type**: `Real` (percentage)
- **Description**: Percentage of maximum health regenerated per second for rebuild holes. Higher values provide faster hole healing rates. Lower values provide slower, more gradual hole recovery. At 0.5% (default), holes heal 0.5% of their max health per second
- **Default**: `0.005` (0.5%)
- **Example**: `HoleHealthRegen%PerSecond = 0.5%`

## Examples

### Basic Rebuild Hole
```ini
Behavior = RebuildHoleBehavior ModuleTag_04
  WorkerObjectName = GLAInfantryWorker
  WorkerRespawnDelay = 20000
  HoleHealthRegen%PerSecond = 0.5%
End
```

### Fast Rebuild Hole
```ini
Behavior = RebuildHoleBehavior ModuleTag_05
  WorkerObjectName = GLAInfantryWorker
  WorkerRespawnDelay = 10000
  HoleHealthRegen%PerSecond = 1.0%
End
```

### Slow Rebuild Hole
```ini
Behavior = RebuildHoleBehavior ModuleTag_06
  WorkerObjectName = GLAInfantryWorker
  WorkerRespawnDelay = 30000
  HoleHealthRegen%PerSecond = 0.25%
End
```

## Template

```ini
Behavior = RebuildHoleBehavior ModuleTag_XX
  ; Worker Configuration
  WorkerObjectName =                   ; // worker template for rebuilding *(v1.04)*
  WorkerRespawnDelay = 20000           ; // milliseconds before worker respawn *(v1.04)*
  
  ; Health Regeneration
  HoleHealthRegen%PerSecond = 0.005    ; // percentage of max health healed per second *(v1.04)*
End
```

## Notes

- RebuildHoleBehavior provides automated rebuilding capabilities for destroyed structures
- The module manages worker spawning and health regeneration of rebuild holes
- Worker respawn delays control how quickly rebuilding operations resume
- Health regeneration allows holes to heal over time without worker intervention
- This creates realistic rebuilding mechanics with proper worker coordination

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h), [`DieModuleInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h), [`RebuildHoleBehaviorInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RebuildHoleBehavior.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RebuildHoleBehavior.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RebuildHoleBehavior.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/RebuildHoleBehavior.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/RebuildHoleBehavior.cpp)
