# SupplyCenterCreate

Create module that provides functionality for creating supply center effects when objects are created or spawned.

## Overview

SupplyCenterCreate is a create module that provides functionality for creating supply center effects when objects are created or spawned. It handles the initialization and setup of supply center capabilities for objects during their creation process. The module integrates with the supply system to enable supply generation and management upon object creation.

SupplyCenterCreate must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that can create supply center effects upon creation or when specific conditions are met. This is a **create module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Requires proper supply system integration for functionality
- Cannot function without proper create and supply systems
- Supply center creation is limited to object creation events
- Requires proper supply templates for effects

**Conditions**:
- Multiple instances behavior: Multiple SupplyCenterCreate modules can exist independently, each creating different supply center effects
- Always active once assigned to an object
- Triggers during onCreate and onBuildComplete events
- Creates supply center capabilities for new objects

**Dependencies**:
- Depends on the create system for object creation events
- Requires proper supply system for effect creation
- Inherits all functionality from CreateModule

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

SupplyCenterCreate does not expose any additional INI-parsable properties beyond those inherited from CreateModule. The module handles supply center creation through internal logic and supply system integration.

## Examples

### Basic Supply Center Create
```ini
Behavior = SupplyCenterCreate ModuleTag_05
  ; No additional properties required
End
```

### China Supply Center Create
```ini
Behavior = SupplyCenterCreate ModuleTag_06
  ; Supply center creation handled internally
End
```

### Russia Supply Post Create
```ini
Behavior = SupplyCenterCreate ModuleTag_08
  ; Supply center initialization handled internally
End
```

## Template

```ini
Behavior = SupplyCenterCreate ModuleTag_XX
  ; No additional properties - all functionality handled internally
End
```

## Notes

- SupplyCenterCreate initializes supply center capabilities for objects during creation
- The module handles supply center setup and integration internally
- Supply center creation is coordinated with the overall supply system
- This creates proper supply center initialization for new objects and structures

## Source Files

**Base Class:** [`CreateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateModule.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateModule.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Create/SupplyCenterCreate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Create/SupplyCenterCreate.cpp)
