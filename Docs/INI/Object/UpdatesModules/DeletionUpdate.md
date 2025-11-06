# DeletionUpdate

Update module that provides deletion functionality for objects that need to be automatically deleted after a certain time or when specific conditions are met.

## Overview

DeletionUpdate is an update module that provides deletion functionality for objects that need to be automatically deleted after a certain time or when specific conditions are met. It manages object lifetimes with configurable minimum and maximum lifetime values, providing automatic cleanup for temporary objects. The module supports random lifetime variation within specified ranges.

DeletionUpdate must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that need to be automatically deleted after a specific duration or when certain conditions are met. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Requires proper update system integration for timing functionality
- Cannot function without proper update system
- Deletion timing is limited by configured lifetime values
- Requires proper object destruction system integration

**Conditions**:
- Multiple instances behavior: Multiple DeletionUpdate modules can exist independently, each managing different deletion systems
- Always active once assigned to an object
- Continuously tracks object lifetime and performs deletion when appropriate
- Creates automatic object cleanup with configurable timing

**Dependencies**:
- Depends on the update system for lifetime tracking
- Requires proper object destruction system for deletion operations
- Inherits all functionality from UpdateModule

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Lifetime Configuration](#lifetime-configuration)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

### Lifetime Configuration

#### `MinLifetime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Minimum lifetime before object deletion. Higher values extend the minimum time before deletion. Lower values allow earlier deletion. At 1000 (default), objects live at least 1000 milliseconds
- **Default**: `1000`
- **Example**: `MinLifetime = 1000`

#### `MaxLifetime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Maximum lifetime before object deletion. Higher values extend the maximum time before deletion. Lower values force earlier deletion. At 1000 (default), objects live at most 1000 milliseconds
- **Default**: `1000`
- **Example**: `MaxLifetime = 1000`

## Examples

### Basic Deletion Update
```ini
Behavior = DeletionUpdate ModuleTag_03
  MinLifetime = 1000
  MaxLifetime = 1000
End
```

### Fast Deletion Update
```ini
Behavior = DeletionUpdate ModuleTag_09d
  MinLifetime = 300
  MaxLifetime = 300
End
```

### Extended Deletion Update
```ini
Behavior = DeletionUpdate ModuleTag_04
  MinLifetime = 2000
  MaxLifetime = 2000
End
```

## Template

```ini
Behavior = DeletionUpdate ModuleTag_XX
  ; Lifetime Configuration
  MinLifetime = 1000                     ; // minimum milliseconds before deletion *(v1.04)*
  MaxLifetime = 1000                     ; // maximum milliseconds before deletion *(v1.04)*
End
```

## Notes

- DeletionUpdate provides automatic object cleanup with configurable timing
- The module manages object lifetimes with minimum and maximum lifetime values
- Random lifetime variation within specified ranges adds realism to object deletion
- This creates reliable automatic cleanup for temporary objects and effects

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/DeletionUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/DeletionUpdate.cpp)
