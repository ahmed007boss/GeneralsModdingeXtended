# DestroyDie

DestroyDie provides the default destruction behavior for objects when they die.

## Overview

The `DestroyDie` class is the standard death module that handles object destruction when an object dies. It simply removes the object from the game world by calling the game logic's destroy object function. This is the most basic death behavior and serves as the default for most objects that don't require special death effects or object creation.

## Usage

Used by objects that need standard destruction behavior when they die, such as most units, buildings, and projectiles. This is a **die module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- DestroyDie only triggers when the object actually dies
- The behavior provides no special effects or object creation
- Object destruction is immediate and irreversible
- The behavior requires the death system to function properly

**Conditions**:
- DestroyDie provides the default destruction behavior for most objects
- The behavior integrates with the death system for conditional activation
- Object destruction is handled by the game logic system
- The behavior supports conditional activation based on death types and conditions
- **Multiple instances behavior**: Only one instance should be used per object; multiple instances are unnecessary since destruction is a single action

**Dependencies**:
- Requires the game logic system to function correctly
- The behavior relies on the death system for activation timing

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

DestroyDie has no additional properties beyond those inherited from DieModule (death types, veterancy levels, status requirements, etc.).

## Examples

### Standard Unit Death
```ini
Die = DestroyDie ModuleTag_Death
End
```

### Conditional Death
```ini
Die = DestroyDie ModuleTag_Conditional
  DeathTypes = NONE +EXPLODED +BURNED
End
```

### Veterancy-Based Death
```ini
Die = DestroyDie ModuleTag_Veteran
  VeterancyLevels = VETERAN +ELITE
End
```

## Template

```ini
Die = DestroyDie ModuleTag_XX
  ; No additional properties - uses base DieModule properties
End
```

## Notes

- DestroyDie provides the default destruction behavior for most objects
- The behavior integrates with the death system for conditional activation
- Object destruction is handled by the game logic system
- The behavior supports conditional activation based on death types and conditions
- This is the simplest death behavior and requires no additional configuration

## Source Files

**Base Class:** [`DieModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DestroyDie.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DestroyDie.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Die/DestroyDie.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Die/DestroyDie.cpp)