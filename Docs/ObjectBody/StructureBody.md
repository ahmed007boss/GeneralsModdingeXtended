# StructureBody

StructureBody provides an active body system specifically designed for structures with constructor tracking.

## Overview

The `StructureBody` class extends ActiveBody with additional functionality for structures, including constructor object tracking. It manages health, damage states, and armor systems like ActiveBody, but also tracks which object built the structure. This behavior is commonly used for buildings, defensive structures, and other constructed objects that need to maintain relationships with their builders.

## Usage

Used by structures that need active health management and constructor tracking, such as buildings, defensive structures, and constructed objects. This is a **body module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- StructureBody requires the same health and damage system as ActiveBody
- Constructor tracking is limited to a single constructor object
- The behavior requires valid object references for constructor tracking
- Health and damage calculations are handled by the ActiveBody base class
- The behavior requires the damage system to function properly

**Conditions**:
- StructureBody provides active health management with constructor tracking
- The behavior tracks which object built the structure
- Health, damage states, and armor systems are managed by ActiveBody
- The behavior integrates with the damage system for all health-related operations
- Constructor information can be retrieved and modified during the structure's lifetime
- **Multiple instances behavior**: Only one body module should exist per object; multiple instances may cause conflicts in health management

**Dependencies**:
- Requires ActiveBody base functionality to function correctly
- The behavior relies on the damage system for health calculations
- Constructor tracking requires valid object references

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

StructureBody has no additional properties beyond those inherited from ActiveBody.

## Examples

### Standard Structure Body
```ini
Body = StructureBody ModuleTag_Structure
  InitialHealth = 100%
End
```

### Defensive Structure Body
```ini
Body = StructureBody ModuleTag_Defense
  InitialHealth = 100%
End
```

### Production Structure Body
```ini
Body = StructureBody ModuleTag_Production
  InitialHealth = 100%
End
```

## Template

```ini
Body = StructureBody ModuleTag_XX
  ; Uses ActiveBody properties:
  ; InitialHealth = 100%                 ; // initial health percentage *(v1.04)*
  ; SubdualDamageCap = 0.0               ; // subdual damage cap *(v1.04, Generals Zero Hour only)*
  ; SubdualDamageHealRate = 0            ; // subdual damage heal rate *(v1.04, Generals Zero Hour only)*
  ; SubdualDamageHealAmount = 0.0        ; // subdual damage heal amount *(v1.04, Generals Zero Hour only)*
  ; EWDamageCap = 0.0                    ; // electronic warfare damage cap *(v1.04, Generals Zero Hour only)*
  ; EWDamageHealRate = 0                 ; // electronic warfare damage heal rate *(v1.04, Generals Zero Hour only)*
  ; EWDamageHealAmount = 0.0             ; // electronic warfare damage heal amount *(v1.04, Generals Zero Hour only)*
End
```

## Notes

- StructureBody provides active health management with constructor tracking
- The behavior tracks which object built the structure
- Health, damage states, and armor systems are managed by ActiveBody
- The behavior integrates with the damage system for all health-related operations
- Constructor information can be retrieved and modified during the structure's lifetime
- This is commonly used for buildings and constructed objects that need builder tracking

## Source Files

**Base Class:** [`ActiveBody`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ActiveBody.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StructureBody.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StructureBody.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Body/StructureBody.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Body/StructureBody.cpp)