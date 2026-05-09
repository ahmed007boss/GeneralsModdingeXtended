# SpecialPowerCompletionDie

Die module that provides death mechanics for triggering object destruction when special powers are completed.

## Overview

SpecialPowerCompletionDie is a die module that provides death mechanics for triggering object destruction when special powers are completed. It monitors for the completion of specified special powers and automatically destroys the object when those powers finish. This is commonly used for temporary objects that should be removed after special power effects are complete.

SpecialPowerCompletionDie must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that need to die or be destroyed when special powers are completed. This is a **die module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Requires valid special power templates for completion monitoring
- Cannot function without proper death system
- Object destruction is limited to special power completion events
- Requires proper special power system integration

**Conditions**:
- Multiple instances behavior: Multiple SpecialPowerCompletionDie modules can exist independently, each monitoring different special powers
- Always active once assigned to an object
- Triggers during special power completion events
- Creates automatic cleanup for temporary special power objects

**Dependencies**:
- Depends on the death system for object destruction
- Requires proper special power system for completion monitoring
- Inherits all functionality from DieModule

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Special Power Configuration](#special-power-configuration)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

### Special Power Configuration

#### `SpecialPowerTemplate` *(v1.04)*
- **Type**: `AsciiString` (see [SpecialPower documentation](../../SpecialPower.md))
- **Description**: Name of the special power template to monitor for completion. When the specified special power completes, the object will be destroyed. When empty (default), no special power is monitored
- **Default**: `""` (empty)
- **Example**: `SpecialPowerTemplate = SU30GroundAttack`

## Examples

### Basic Special Power Completion Die
```ini
Behavior = SpecialPowerCompletionDie ModuleTag_06
  SpecialPowerTemplate = SU30GroundAttack
End
```

### Alternative Special Power Completion Die
```ini
Behavior = SpecialPowerCompletionDie ModuleTag_09
  SpecialPowerTemplate = SU30GroundAttack
End
```

### Third Special Power Completion Die
```ini
Behavior = SpecialPowerCompletionDie ModuleTag_11
  SpecialPowerTemplate = SU30GroundAttack
End
```

## Template

```ini
Behavior = SpecialPowerCompletionDie ModuleTag_XX
  ; Special Power Configuration
  SpecialPowerTemplate =              ; // special power to monitor for completion *(v1.04)*
End
```

## Notes

- SpecialPowerCompletionDie automatically destroys objects when special powers complete
- The module monitors for the completion of specified special powers
- This creates automatic cleanup for temporary objects created by special powers
- Commonly used for projectiles, effects, or temporary units that should be removed after special power completion

## Source Files

**Base Class:** [`DieModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Die/SpecialPowerCompletionDie.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Die/SpecialPowerCompletionDie.cpp)
