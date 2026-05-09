# BodyModule

BodyModule provides the base interface for all body systems that manage health, damage, and physical state.

## Overview

The `BodyModule` class is the abstract base class for all body systems in the game. It defines the interface for health management, damage handling, and physical state control. Body modules are responsible for managing an object's health, armor, damage states, and interactions with the damage system. This is the foundation for all other body types like ActiveBody, InactiveBody, and StructureBody.

## Usage

Used as the base class for all body system implementations. This is a **body module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- BodyModule is an abstract base class and cannot be used directly
- The behavior requires implementation of all virtual methods by derived classes
- Health and damage calculations are handled by the specific body implementation
- The behavior requires the damage system to function properly

**Conditions**:
- BodyModule defines the interface for all body system functionality
- The behavior provides virtual methods for damage, healing, and health management
- Damage states and armor systems are managed by the specific body implementation
- The behavior integrates with the damage system for all health-related operations
- **Multiple instances behavior**: Only one body module should exist per object; multiple instances may cause conflicts in health management

**Dependencies**:
- Requires implementation by derived classes to function correctly
- The behavior relies on the damage system for health calculations

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
- [Enum Value Lists](#enum-value-lists)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

BodyModule has no additional properties beyond those inherited from BehaviorModule.

## Enum Value Lists

#### `BodyDamageType` Values *(v1.04)*
**Source:** [BodyModule.h](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h#53) - `BodyDamageType` enum definition

- **`BODY_PRISTINE`** *(v1.04)* - Unit appears in pristine condition
- **`BODY_DAMAGED`** *(v1.04)* - Unit has been damaged
- **`BODY_REALLYDAMAGED`** *(v1.04)* - Unit is extremely damaged/nearly destroyed
- **`BODY_RUBBLE`** *(v1.04)* - Unit has been reduced to rubble/corpse/exploded hulk

#### `MaxHealthChangeType` Values *(v1.04)*
**Source:** [BodyModule.h](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h#75) - `MaxHealthChangeType` enum definition

- **`SAME_CURRENTHEALTH`** *(v1.04)* - Keep current health unchanged
- **`PRESERVE_RATIO`** *(v1.04)* - Preserve health percentage ratio
- **`ADD_CURRENT_HEALTH_TOO`** *(v1.04)* - Add to current health as well
- **`FULLY_HEAL`** *(v1.04)* - Fully heal the object

## Examples

### Base Body Module (Abstract)
```ini
; BodyModule is abstract - use derived classes like ActiveBody, InactiveBody, etc.
```

### Active Body Implementation
```ini
Body = ActiveBody ModuleTag_Body
  InitialHealth = 100%
End
```

### Structure Body Implementation
```ini
Body = StructureBody ModuleTag_StructureBody
  InitialHealth = 100%
End
```

## Template

```ini
; BodyModule is abstract - use derived classes:
; Body = ActiveBody ModuleTag_XX
; Body = InactiveBody ModuleTag_XX  
; Body = StructureBody ModuleTag_XX
; etc.
```

## Notes

- BodyModule defines the interface for all body system functionality
- The behavior provides virtual methods for damage, healing, and health management
- Damage states and armor systems are managed by the specific body implementation
- The behavior integrates with the damage system for all health-related operations
- This is an abstract base class that must be implemented by derived classes

## Source Files

**Base Class:** [`BehaviorModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Body/BodyModule.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Body/BodyModule.cpp)