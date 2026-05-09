# CheckpointUpdate

Update module that provides checkpoint functionality for objects that can create or manage checkpoints for save and restore operations.

## Overview

CheckpointUpdate is an update module that provides checkpoint functionality for objects that can create or manage checkpoints for save and restore operations. It handles checkpoint creation, progress saving, and checkpoint-based system management. The module integrates with the game's checkpoint system to provide reliable save and restore capabilities.

CheckpointUpdate must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that need to create checkpoints, save progress, or manage checkpoint-based systems. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Requires proper checkpoint system integration for functionality
- Cannot function without proper update system
- Checkpoint operations are limited by system capabilities
- Requires proper save and restore system integration

**Conditions**:
- Multiple instances behavior: Multiple CheckpointUpdate modules can exist independently, each managing different checkpoint systems
- Always active once assigned to an object
- Continuously manages checkpoint creation and progress saving
- Creates reliable checkpoint-based save and restore capabilities

**Dependencies**:
- Depends on the checkpoint system for save and restore operations
- Requires proper update system for continuous management
- Inherits all functionality from UpdateModule

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

CheckpointUpdate does not expose any additional INI-parsable properties beyond those inherited from UpdateModule. The module handles checkpoint operations through internal logic and checkpoint system integration.

## Examples

### Basic Checkpoint Update
```ini
Behavior = CheckpointUpdate ModuleTag_03
  ; No additional properties required
End
```

### Enhanced Checkpoint Update
```ini
Behavior = CheckpointUpdate ModuleTag_04
  ; Checkpoint operations handled internally
End
```

### Advanced Checkpoint Update
```ini
Behavior = CheckpointUpdate ModuleTag_05
  ; Progress saving handled internally
End
```

## Template

```ini
Behavior = CheckpointUpdate ModuleTag_XX
  ; No additional properties - all functionality handled internally
End
```

## Notes

- CheckpointUpdate provides reliable checkpoint creation and progress saving capabilities
- The module handles checkpoint operations through the game's checkpoint system
- Checkpoint functionality ensures reliable save and restore operations
- This creates robust checkpoint-based save systems for game progression

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/CheckpointUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/CheckpointUpdate.cpp)
