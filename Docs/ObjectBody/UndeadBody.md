# UndeadBody

Body module that provides a "second life" when the object would normally die, allowing it to continue fighting with reduced health and different armor.

## Overview

UndeadBody is a specialized body module that intercepts the first death and grants the object a "second life" instead of dying. When the object would normally die from health-damaging damage, it instead survives with 1 health point, then immediately transitions to its second life with new maximum health and armor. This creates a "zombie" or "undead" effect where objects appear to die but continue fighting.

UndeadBody must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that should have a second life after death, becoming "undead" with different armor and health characteristics. This is a **body module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Only works once per object lifetime
- Second death is permanent
- Requires SlowDeathBehavior module to function properly
- Unresistable damage bypasses the second life mechanic
- Only one body module per object

**Conditions**:
- Multiple instances behavior: Multiple UndeadBody modules cannot exist - only one body module per object
- Always active once assigned to an object
- Second life triggers when health would drop to 0 or below
- Creates dramatic second life mechanics for special units or boss characters

**Dependencies**:
- Requires SlowDeathBehavior module for proper second life activation
- Inherits all properties and functionality from ActiveBody
- Depends on proper armor set definitions for second life armor

## Properties

### Second Life Settings

#### `SecondLifeMaxHealth` *(v1.04)*
- **Type**: `Real`
- **Description**: Maximum health points for the object's second life. When the object "dies" the first time, it transitions to this new maximum health. Higher values make the second life more durable. When set to 1 (default), the second life is very fragile
- **Default**: `1.0`
- **Example**: `SecondLifeMaxHealth = 50.0`

## Examples

### Zombie Infantry Unit
```ini
Body = UndeadBody ModuleTag_01
  ; First Life Settings
  MaxHealth = 100.0
  InitialHealth = 100.0
  
  ; Second Life Settings
  SecondLifeMaxHealth = 50.0
  
  ; Subdual Damage Settings (Generals Zero Hour only)
  SubdualDamageCap = 0.0
  SubdualDamageHealRate = 0
  SubdualDamageHealAmount = 0.0
  
  ; Electronic Warfare Settings (Generals Zero Hour only)
  EWDamageCap = 0.0
  EWDamageHealRate = 0
  EWDamageHealAmount = 0.0
End

Behavior = SlowDeathBehavior ModuleTag_02
  DeathTypes = NORMAL
  MinDamage = 0.0
  MaxDamage = 1000.0
  Probability = 100
  ; ... other SlowDeathBehavior properties
End
```

### Undead Vehicle
```ini
Body = UndeadBody ModuleTag_03
  ; First Life Settings
  MaxHealth = 500.0
  InitialHealth = 500.0
  
  ; Second Life Settings
  SecondLifeMaxHealth = 200.0
  
  ; Subdual Damage Settings (Generals Zero Hour only)
  SubdualDamageCap = 0.0
  SubdualDamageHealRate = 0
  SubdualDamageHealAmount = 0.0
  
  ; Electronic Warfare Settings (Generals Zero Hour only)
  EWDamageCap = 0.0
  EWDamageHealRate = 0
  EWDamageHealAmount = 0.0
End
```

## Template

```ini
Body = UndeadBody ModuleTag_XX
  ; First Life Settings (inherited from ActiveBody)
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

  ; Second Life Settings
  SecondLifeMaxHealth = 1.0          ; // maximum health for second life *(v1.04)*
End
```

## Notes

- UndeadBody provides a "second life" mechanic where objects survive their first death
- When the object would die, it instead transitions to second life with new health and armor
- The second life uses ARMORSET_SECOND_LIFE for different damage resistance
- Requires SlowDeathBehavior module to properly trigger the second life transition
- Unresistable damage bypasses the second life and causes immediate death
- Second death is permanent and cannot be prevented
- Creates interesting tactical scenarios where enemies must "kill" units twice
- Commonly used for zombie-themed units or units with resurrection capabilities

## Source Files

**Base Class:** [`ActiveBody`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ActiveBody.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UndeadBody.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UndeadBody.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Body/UndeadBody.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Body/UndeadBody.cpp)