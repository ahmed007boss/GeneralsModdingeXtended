# ImmortalBody

Body module that prevents health from dropping below 1 point, making objects truly immortal.

## Overview

ImmortalBody is a specialized body module that prevents objects from ever dying by ensuring their health never drops below 1 point. Unlike HighlanderBody which allows death from unresistable damage, ImmortalBody prevents all death regardless of damage type. Objects can still take damage and show damage states, but they can never be destroyed through health loss.

ImmortalBody must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that should be truly immortal and never die from any type of damage. This is a **body module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Cannot die from any type of damage
- Health is clamped to minimum 1 point
- Still shows damage states and visual effects
- Only one body module per object

**Conditions**:
- Multiple instances behavior: Multiple ImmortalBody modules cannot exist - only one body module per object
- Always active once assigned to an object
- Health is automatically maintained at minimum 1 point
- Creates truly indestructible objectives, markers, or special units

**Dependencies**:
- Inherits all properties and functionality from ActiveBody
- Requires proper armor and damage type definitions
- Depends on the damage system for health change prevention

## Properties

ImmortalBody inherits all properties from ActiveBody with no additional INI-parsable properties. See [ActiveBody documentation](ActiveBody.md) for complete property list.

## Examples

### Truly Immortal Hero Unit
```ini
Body = ImmortalBody ModuleTag_01
  MaxHealth = 1000.0
  InitialHealth = 1000.0
  SubdualDamageCap = 0.0
  SubdualDamageHealRate = 0
  SubdualDamageHealAmount = 0.0
  EWDamageCap = 0.0
  EWDamageHealRate = 0
  EWDamageHealAmount = 0.0
End
```

### Indestructible Objective Marker
```ini
Body = ImmortalBody ModuleTag_02
  MaxHealth = 500.0
  InitialHealth = 500.0
  SubdualDamageCap = 0.0
  SubdualDamageHealRate = 0
  SubdualDamageHealAmount = 0.0
  EWDamageCap = 0.0
  EWDamageHealRate = 0
  EWDamageHealAmount = 0.0
End
```

## Template

```ini
Body = ImmortalBody ModuleTag_XX
  ; Inherits all ActiveBody properties
  MaxHealth = 100.0                  ; // maximum health points *(v1.04)*
  InitialHealth = 100.0              ; // starting health points *(v1.04)*

  ; Subdual Damage Settings (Generals Zero Hour only)
  SubdualDamageCap = 0.0             ; // maximum subdual damage *(v1.04, Generals Zero Hour only)*
  SubdualDamageHealRate = 0          ; // subdual damage heal rate *(v1.04, Generals Zero Hour only)*
  SubdualDamageHealAmount = 0.0      ; // subdual damage heal amount *(v1.04, Generals Zero Hour only)*

  ; Electronic Warfare Settings (Generals Zero Hour only)
  EWDamageCap = 0.0                  ; // maximum electronic warfare damage *(v1.04, Generals Zero Hour only)*
  EWDamageHealRate = 0               ; // electronic warfare damage heal rate *(v1.04, Generals Zero Hour only)*
  EWDamageHealAmount = 0.0           ; // electronic warfare damage heal amount *(v1.04, Generals Zero Hour only)*
End
```

## Notes

- ImmortalBody objects can take damage normally but cannot die from it
- Health is automatically clamped to minimum 1 point for all damage types
- All damage calculations, armor, and status effects work normally
- Objects still show damage states and visual effects
- Cannot be destroyed by any means through health loss
- Useful for creating truly indestructible objectives, markers, or special units
- Objects can still be removed through other means (like special powers or script commands)

## Source Files

**Base Class:** [`ActiveBody`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ActiveBody.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ImmortalBody.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ImmortalBody.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Body/ImmortalBody.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Body/ImmortalBody.cpp)