# BaseRenerateUpdate

Update module that provides base regeneration functionality for objects that can regenerate health over time at their base location.

## Overview

BaseRenerateUpdate is an update module that provides base regeneration functionality for objects that can regenerate health or resources over time at their base or home location. It handles health regeneration for objects when they are at their base, providing automatic healing over time. The module integrates with the global base regeneration system to provide consistent healing mechanics.

BaseRenerateUpdate must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that need to regenerate health or resources over time at their base or home location. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Requires proper damage system integration for health management
- Cannot function without proper update and damage systems
- Base regeneration is limited to base location proximity
- Requires global base regeneration system configuration

**Conditions**:
- Multiple instances behavior: Multiple BaseRenerateUpdate modules can exist independently, each managing different regeneration systems
- Always active once assigned to an object
- Continuously manages health regeneration when at base location
- Creates automatic healing capabilities for base-based objects

**Dependencies**:
- Depends on the damage system for health management
- Requires proper update system for continuous regeneration
- Inherits functionality from UpdateModule and DamageModuleInterface

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

BaseRenerateUpdate does not expose any additional INI-parsable properties beyond those inherited from UpdateModule. The module handles base regeneration through internal logic and global base regeneration system integration.

## Examples

### Basic Base Regeneration
```ini
Behavior = BaseRenerateUpdate ModuleTag_01
  ; No additional properties required
End
```

### Enhanced Base Regeneration
```ini
Behavior = BaseRenerateUpdate ModuleTag_02
  ; Base regeneration handled internally
End
```

### Advanced Base Regeneration
```ini
Behavior = BaseRenerateUpdate ModuleTag_03
  ; Health regeneration at base handled internally
End
```

## Template

```ini
Behavior = BaseRenerateUpdate ModuleTag_XX
  ; No additional properties - all functionality handled internally
End
```

## Notes

- BaseRenerateUpdate provides automatic health regeneration for objects at their base location
- The module integrates with the global base regeneration system for consistent healing mechanics
- Base regeneration provides tactical advantages for units operating near their home base
- This creates realistic base support capabilities for strategic gameplay

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h), [`DamageModuleInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DamageModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BaseRegenerateUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BaseRegenerateUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/BaseRenerateUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/BaseRenerateUpdate.cpp)
