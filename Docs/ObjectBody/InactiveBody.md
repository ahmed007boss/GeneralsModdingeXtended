# InactiveBody

InactiveBody provides an indestructible body system for objects that cannot be damaged or affected by the world.

## Overview

The `InactiveBody` class provides a body system for objects that are effectively indestructible and cannot be damaged or affected by normal game mechanics. These objects are marked as "effectively dead" and bypass most health and damage calculations. This behavior is commonly used for decorative objects, terrain features, and objects that should not interact with the damage system.

## Usage

Used by objects that should be indestructible and unaffected by damage, such as decorative objects, terrain features, or special objects that should not interact with the damage system. This is a **body module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- InactiveBody objects cannot be damaged or healed
- The behavior bypasses all armor and damage calculations
- Objects with InactiveBody are marked as "effectively dead"
- The behavior provides no health management functionality
- Objects cannot change damage states or be affected by veterancy

**Conditions**:
- InactiveBody provides indestructible body functionality
- The behavior automatically marks objects as "effectively dead"
- All damage and healing attempts are ignored
- Armor systems and damage states are not applicable
- The behavior bypasses all health-related calculations
- **Multiple instances behavior**: Only one body module should exist per object; multiple instances may cause conflicts in health management

**Dependencies**:
- Requires the object system to function correctly
- The behavior relies on the damage system for interface compatibility

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

InactiveBody has no additional properties beyond those inherited from BodyModule.

## Examples

### Decorative Object
```ini
Body = InactiveBody ModuleTag_Decorative
End
```

### Terrain Feature
```ini
Body = InactiveBody ModuleTag_Terrain
End
```

### Special Indestructible Object
```ini
Body = InactiveBody ModuleTag_Indestructible
End
```

## Template

```ini
Body = InactiveBody ModuleTag_XX
  ; No additional properties - uses base BodyModule properties
End
```

## Notes

- InactiveBody provides indestructible body functionality
- The behavior automatically marks objects as "effectively dead"
- All damage and healing attempts are ignored
- Armor systems and damage states are not applicable
- The behavior bypasses all health-related calculations
- This is commonly used for decorative objects and terrain features

## Source Files

**Base Class:** [`BodyModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/InactiveBody.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/InactiveBody.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Body/InactiveBody.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Body/InactiveBody.cpp)