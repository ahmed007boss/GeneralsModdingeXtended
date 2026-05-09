# KeepObjectDie

KeepObjectDie provides a death behavior that keeps the object in the world as rubble instead of destroying it.

## Overview

The `KeepObjectDie` class is a simple death module that prevents objects from being completely destroyed when they die. Instead of removing the object from the game world, it allows the object to remain as rubble or debris. This behavior is commonly used for civilian buildings, structures, and objects that should leave visual remains when destroyed.

## Usage

Used by objects that should remain in the world as rubble when destroyed, such as civilian buildings, structures, or objects that need visual remains. This is a **die module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- KeepObjectDie only prevents object destruction when the object dies
- The behavior provides no additional effects beyond keeping the object in the world
- Objects remain in their current state when they die
- The behavior requires the death system to function properly

**Conditions**:
- KeepObjectDie allows objects to remain in the world as rubble when they die
- The behavior integrates with the death system for conditional activation
- Objects keep their current visual state and position when they die
- The behavior supports conditional activation based on death types and conditions
- **Multiple instances behavior**: Only one instance should be used per object; multiple instances are unnecessary since object keeping is a single action

**Dependencies**:
- Requires the death system to function correctly
- The behavior relies on the object's current state for visual appearance

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

KeepObjectDie has no additional properties beyond those inherited from DieModule (death types, veterancy levels, status requirements, etc.).

## Examples

### Civilian Building Rubble
```ini
Die = KeepObjectDie ModuleTag_Rubble
End
```

### Conditional Rubble
```ini
Die = KeepObjectDie ModuleTag_ConditionalRubble
  DeathTypes = NONE +EXPLODED +BURNED
End
```

### Structure Rubble
```ini
Die = KeepObjectDie ModuleTag_StructureRubble
  DeathTypes = NONE +CRUSHED
End
```

## Template

```ini
Die = KeepObjectDie ModuleTag_XX
  ; No additional properties - uses base DieModule properties
End
```

## Notes

- KeepObjectDie allows objects to remain in the world as rubble when they die
- The behavior integrates with the death system for conditional activation
- Objects keep their current visual state and position when they die
- The behavior supports conditional activation based on death types and conditions
- This behavior is commonly used for civilian buildings and structures that should leave visual remains

## Source Files

**Base Class:** [`DieModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/KeepObjectDie.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/KeepObjectDie.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Die/KeepObjectDie.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Die/KeepObjectDie.cpp)