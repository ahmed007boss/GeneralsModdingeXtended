# SpecialPowerCreate

Create module that provides functionality for creating special power effects when objects are created or spawned.

## Overview

SpecialPowerCreate is a create module that provides functionality for creating special power effects when objects are created or spawned. It handles the initialization and setup of special power capabilities for objects during their creation process. The module integrates with the special power system to enable special abilities upon object creation.

SpecialPowerCreate must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that can trigger special powers upon creation or when specific conditions are met. This is a **create module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Requires proper special power system integration for functionality
- Cannot function without proper create and special power systems
- Special power creation is limited to object creation events
- Requires proper special power templates for effects

**Conditions**:
- Multiple instances behavior: Multiple SpecialPowerCreate modules can exist independently, each creating different special power effects
- Always active once assigned to an object
- Triggers during onCreate and onBuildComplete events
- Creates special power capabilities for new objects

**Dependencies**:
- Depends on the create system for object creation events
- Requires proper special power system for effect creation
- Inherits all functionality from CreateModule

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

SpecialPowerCreate does not expose any additional INI-parsable properties beyond those inherited from CreateModule. The module handles special power creation through internal logic and special power system integration.

## Examples

### Basic Special Power Create
```ini
Behavior = SpecialPowerCreate ModuleTag_16
  ; No additional properties required
End
```

### Faction Building Special Power Create
```ini
Behavior = SpecialPowerCreate ModuleTag_16
  ; Special power creation handled internally
End
```

### Aircraft Special Power Create
```ini
Behavior = SpecialPowerCreate ModuleTag_05
  ; Special power initialization handled internally
End
```

## Template

```ini
Behavior = SpecialPowerCreate ModuleTag_XX
  ; No additional properties - all functionality handled internally
End
```

## Notes

- SpecialPowerCreate initializes special power capabilities for objects during creation
- The module handles special power setup and integration internally
- Special power creation is coordinated with the overall special power system
- This creates proper special power initialization for new objects and structures

## Source Files

**Base Class:** [`CreateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateModule.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateModule.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Create/SpecialPowerCreate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Create/SpecialPowerCreate.cpp)
