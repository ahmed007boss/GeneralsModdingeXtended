# SupplyWarehouseCreate

Create module that provides functionality for creating supply warehouse effects when objects are created or spawned.

## Overview

SupplyWarehouseCreate is a create module that provides functionality for creating supply warehouse effects when objects are created or spawned. It handles the initialization and setup of supply warehouse capabilities for objects during their creation process. The module integrates with the supply system to enable supply storage and management upon object creation.

SupplyWarehouseCreate must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that can create supply warehouse effects upon creation or when specific conditions are met. This is a **create module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Requires proper supply system integration for functionality
- Cannot function without proper create and supply systems
- Supply warehouse creation is limited to object creation events
- Requires proper supply templates for effects

**Conditions**:
- Multiple instances behavior: Multiple SupplyWarehouseCreate modules can exist independently, each creating different supply warehouse effects
- Always active once assigned to an object
- Triggers during onCreate and onBuildComplete events
- Creates supply warehouse capabilities for new objects

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

SupplyWarehouseCreate does not expose any additional INI-parsable properties beyond those inherited from CreateModule. The module handles supply warehouse creation through internal logic and supply system integration.

## Examples

### Basic Supply Warehouse Create
```ini
Behavior = SupplyWarehouseCreate ModuleTag_05
  ; No additional properties required
End
```

### Alternative Supply Warehouse Create
```ini
Behavior = SupplyWarehouseCreate ModuleTag_03
  ; Supply warehouse creation handled internally
End
```

### Third Supply Warehouse Create
```ini
Behavior = SupplyWarehouseCreate ModuleTag_04
  ; Supply warehouse initialization handled internally
End
```

## Template

```ini
Behavior = SupplyWarehouseCreate ModuleTag_XX
  ; No additional properties - all functionality handled internally
End
```

## Notes

- SupplyWarehouseCreate initializes supply warehouse capabilities for objects during creation
- The module handles supply warehouse setup and integration internally
- Supply warehouse creation is coordinated with the overall supply system
- This creates proper supply warehouse initialization for new objects and structures

## Source Files

**Base Class:** [`CreateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateModule.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateModule.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Create/SupplyWarehouseCreate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Create/SupplyWarehouseCreate.cpp)
