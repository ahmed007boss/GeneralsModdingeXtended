# DamDie

DamDie provides special death effects for dam structures that enable water wave objects when destroyed.

## Overview

The `DamDie` class manages the special death behavior of dam structures. When a dam dies, it automatically enables all water wave objects on the map by clearing their disabled status. This creates the visual and gameplay effect of water flowing when dams are destroyed. This behavior is specifically designed for dam structures and their water wave effects.

## Usage

Used by dam structures that need to enable water wave effects when destroyed. This is a **die module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- DamDie only triggers when the dam object actually dies
- The behavior requires water wave objects with KINDOF_WAVEGUIDE to exist on the map
- Water wave enabling is limited to objects that are currently disabled
- The behavior provides no additional effects beyond enabling water waves
- The behavior requires the death system to function properly

**Conditions**:
- DamDie automatically enables all water wave objects when the dam dies
- The behavior searches for objects with KINDOF_WAVEGUIDE kind of flags
- Disabled water wave objects are automatically enabled when the dam dies
- The behavior integrates with the death system for conditional activation
- **Multiple instances behavior**: Only one instance should be used per dam object; multiple instances are unnecessary since water wave enabling is a single action

**Dependencies**:
- Requires water wave objects with KINDOF_WAVEGUIDE to exist on the map
- The behavior relies on the death system for activation timing

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

DamDie has no additional properties beyond those inherited from DieModule (death types, veterancy levels, status requirements, etc.).

## Examples

### Standard Dam Death
```ini
Die = DamDie ModuleTag_DamDeath
End
```

### Conditional Dam Death
```ini
Die = DamDie ModuleTag_ConditionalDam
  DeathTypes = NONE +EXPLODED +BURNED
End
```

### Construction-Complete Dam Death
```ini
Die = DamDie ModuleTag_CompleteDam
  RequiredStatus = OBJECT_STATUS_UNDER_CONSTRUCTION
End
```

## Template

```ini
Die = DamDie ModuleTag_XX
  ; No additional properties - uses base DieModule properties
End
```

## Notes

- DamDie automatically enables all water wave objects when the dam dies
- The behavior searches for objects with KINDOF_WAVEGUIDE kind of flags
- Disabled water wave objects are automatically enabled when the dam dies
- The behavior integrates with the death system for conditional activation
- This behavior is specifically designed for dam structures and their water wave effects

## Source Files

**Base Class:** [`DieModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DamDie.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DamDie.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Die/DamDie.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Die/DamDie.cpp)