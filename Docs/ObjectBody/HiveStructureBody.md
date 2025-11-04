# HiveStructureBody

Structure body module that propagates damage to slaves when available, otherwise absorbs or takes the damage itself.

## Overview

HiveStructureBody is a specialized structure body module that can redirect incoming damage to slave objects (created by SpawnBehavior) or contained objects (via ContainModule) instead of taking the damage itself. When no slaves are available, it can either absorb the damage completely or take it normally. This creates a "hive mind" effect where the main structure is protected by its minions.

HiveStructureBody must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by structures that should redirect incoming damage to slave objects or contained objects instead of taking the damage themselves. This is a **body module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Requires either a SpawnBehavior module or ContainModule to function
- Can only propagate damage to existing slave/contained objects
- Damage propagation only works for specified damage types
- Only one body module per object

**Conditions**:
- Multiple instances behavior: Multiple HiveStructureBody modules cannot exist - only one body module per object
- Always active once assigned to an object
- Damage propagation requires active slaves or contained objects
- Creates a "hive mind" effect where the main structure is protected by its minions

**Dependencies**:
- Requires SpawnBehavior module or ContainModule for slave/contained object access
- Inherits all properties and functionality from StructureBody
- Depends on proper damage type flag definitions

## Properties

### Damage Propagation

#### `PropagateDamageTypesToSlavesWhenExisting` *(v1.04)*
- **Type**: `DamageTypeFlags` (bit flags)
- **Description**: Damage types that should be redirected to slave/contained objects when they are available. When set, incoming damage of these types is transferred to the closest slave/contained object. When empty (default), no damage propagation occurs
- **Default**: `0` (none)
- **Example**: `PropagateDamageTypesToSlavesWhenExisting = EXPLOSION BALLISTIC`

#### `SwallowDamageTypesIfSlavesNotExisting` *(v1.04)*
- **Type**: `DamageTypeFlags` (bit flags)
- **Description**: Damage types that should be completely absorbed when no slaves/contained objects are available. When set, these damage types are negated and cause no effect. When empty (default), all damage is taken normally when no slaves exist
- **Default**: `0` (none)
- **Example**: `SwallowDamageTypesIfSlavesNotExisting = EXPLOSION`

## Examples

### Hive Structure with Explosion Protection
```ini
Body = HiveStructureBody ModuleTag_01
  ; Inherited from StructureBody/ActiveBody
  MaxHealth = 2000.0
  InitialHealth = 2000.0
  
  ; Damage Propagation
  PropagateDamageTypesToSlavesWhenExisting = EXPLOSION BALLISTIC
  SwallowDamageTypesIfSlavesNotExisting = EXPLOSION
End

Behavior = SpawnBehavior ModuleTag_02
  SpawnNumber = 3
  SpawnReplaceDelay = 10000
  SpawnUpgrade = Upgrade_HiveSpawn
End
```

### Transport with Damage Redirection
```ini
Body = HiveStructureBody ModuleTag_03
  ; Inherited from StructureBody/ActiveBody
  MaxHealth = 1500.0
  InitialHealth = 1500.0
  
  ; Damage Propagation
  PropagateDamageTypesToSlavesWhenExisting = BALLISTIC
  SwallowDamageTypesIfSlavesNotExisting = 0
End

Module = ContainModule ModuleTag_04
  Max = 5
  Initial = 0
End
```

## Template

```ini
Body = HiveStructureBody ModuleTag_XX
  ; Inherits all StructureBody/ActiveBody properties
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

  ; Damage Propagation
  PropagateDamageTypesToSlavesWhenExisting = 0 ; // damage types to redirect to slaves *(v1.04)*
  SwallowDamageTypesIfSlavesNotExisting = 0    ; // damage types to absorb when no slaves *(v1.04)*
End
```

## Notes

- HiveStructureBody requires either SpawnBehavior or ContainModule to function properly
- Damage propagation only occurs when slaves/contained objects are available
- The closest slave/contained object to the damage source receives the damage
- Damage absorption (swallowing) only occurs when no slaves exist and the damage type matches
- If no slaves exist and damage type doesn't match swallow criteria, damage is taken normally
- Creates interesting tactical scenarios where destroying slaves makes the hive vulnerable

## Source Files

**Base Class:** [`StructureBody`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StructureBody.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/HiveStructureBody.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/HiveStructureBody.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Body/HiveStructureBody.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Body/HiveStructureBody.cpp)