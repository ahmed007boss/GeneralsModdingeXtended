# VeterancyGainCreate

Create module that provides functionality for granting veterancy experience when objects are created or spawned.

## Overview

VeterancyGainCreate is a create module that provides functionality for granting veterancy experience when objects are created or spawned. It handles the initialization and setup of veterancy gain capabilities for objects during their creation process. The module integrates with the veterancy system to enable experience gain upon object creation.

VeterancyGainCreate must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that can grant veterancy experience to other objects upon creation or when specific conditions are met. This is a **create module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Requires proper veterancy system integration for functionality
- Cannot function without proper create and veterancy systems
- Veterancy gain is limited to object creation events
- Requires proper veterancy templates for effects

**Conditions**:
- Multiple instances behavior: Multiple VeterancyGainCreate modules can exist independently, each creating different veterancy gain effects
- Always active once assigned to an object
- Triggers during onCreate and onBuildComplete events
- Creates veterancy gain capabilities for new objects

**Dependencies**:
- Depends on the create system for object creation events
- Requires proper veterancy system for experience gain
- Inherits all functionality from CreateModule

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

VeterancyGainCreate does not expose any additional INI-parsable properties beyond those inherited from CreateModule. The module handles veterancy gain through internal logic and veterancy system integration.

## Examples

### Basic Veterancy Gain Create
```ini
Behavior = VeterancyGainCreate Upgrade_09
  ; No additional properties required
End
```

### CINE Unit Veterancy Gain Create
```ini
Behavior = VeterancyGainCreate ModuleTag_02
  ; Veterancy gain handled internally
End
```

### System Veterancy Gain Create
```ini
Behavior = VeterancyGainCreate ModuleTag_05
  ; Veterancy gain initialization handled internally
End
```

## Template

```ini
Behavior = VeterancyGainCreate ModuleTag_XX
  ; No additional properties - all functionality handled internally
End
```

## Notes

- VeterancyGainCreate initializes veterancy gain capabilities for objects during creation
- The module handles veterancy gain setup and integration internally
- Veterancy gain is coordinated with the overall veterancy system
- This creates proper veterancy gain initialization for new objects and structures

## Source Files

**Base Class:** [`CreateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateModule.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateModule.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Create/VeterancyGainCreate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Create/VeterancyGainCreate.cpp)
