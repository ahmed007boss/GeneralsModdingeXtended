# FireWeaponCollide

Collision module that fires a weapon when objects collide with the parent object.

## Overview

FireWeaponCollide is a collision detection module that automatically fires a weapon when other objects collide with the parent object. This is commonly used for proximity mines, explosive barrels, and other objects that should damage or destroy anything that touches them. The module can fire continuously while objects are in contact or fire only once per collision event.

FireWeaponCollide must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that should fire weapons when other objects collide with them. This is a **collision module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Cannot fire at the ground (terrain collisions are ignored)
- Requires a valid weapon template to function
- Weapon firing is subject to object status conditions
- Requires proper collision detection system

**Conditions**:
- Multiple instances behavior: Multiple FireWeaponCollide modules can exist independently, each with different weapons and conditions
- Fires continuously while objects are in collision contact
- Can be configured to fire only once ever or repeatedly
- Creates proximity-based weapon effects

**Dependencies**:
- Requires a valid weapon template for collision weapon
- Depends on object status conditions for firing authorization
- Requires proper collision detection between objects

## Properties

### Weapon Settings

#### `CollideWeapon` *(v1.04)*
- **Type**: `Weapon` (see [Weapon documentation](../Weapon.md))
- **Description**: Weapon template to fire when objects collide with the parent. When set, fires the specified weapon at colliding objects. When NULL (default), no weapon is fired on collision
- **Default**: `NULL` (none)
- **Example**: `CollideWeapon = WeaponProximityMine`

### Firing Control

#### `FireOnce` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether to fire the weapon only once ever during the object's lifetime. When true, the weapon fires only on the first collision. When false (default), the weapon fires continuously while objects are in contact
- **Default**: `No`
- **Example**: `FireOnce = Yes`

### Status Requirements

#### `RequiredStatus` *(v1.04)*
- **Type**: `ObjectStatusMaskType` (bit flags)
- **Description**: Required object status flags that must all be present for the weapon to fire. When set, all specified status flags must be active. When empty (default), no status requirements exist
- **Default**: `0` (none)
- **Example**: `RequiredStatus = UNDER_CONSTRUCTION`

#### `ForbiddenStatus` *(v1.04)*
- **Type**: `ObjectStatusMaskType` (bit flags)
- **Description**: Forbidden object status flags that prevent weapon firing when present. When set, any of the specified status flags will prevent firing. When empty (default), no status restrictions exist
- **Default**: `0` (none)
- **Example**: `ForbiddenStatus = DESTROYED`

## Examples

### Proximity Mine
```ini
Collide = FireWeaponCollide ModuleTag_01
  CollideWeapon = WeaponProximityMine
  FireOnce = Yes
  RequiredStatus = 
  ForbiddenStatus = DESTROYED
End
```

### Explosive Barrel
```ini
Collide = FireWeaponCollide ModuleTag_02
  CollideWeapon = WeaponBarrelExplosion
  FireOnce = Yes
  RequiredStatus = 
  ForbiddenStatus = DESTROYED UNDER_CONSTRUCTION
End
```

## Template

```ini
Collide = FireWeaponCollide ModuleTag_XX
  ; Weapon Settings
  CollideWeapon =                   ; // weapon to fire on collision *(v1.04)*
  
  ; Firing Control
  FireOnce = No                     ; // fire only once ever *(v1.04)*
  
  ; Status Requirements
  RequiredStatus = 0                ; // required status flags *(v1.04)*
  ForbiddenStatus = 0               ; // forbidden status flags *(v1.04)*
End
```

## Notes

- FireWeaponCollide fires weapons at colliding objects every frame while in contact
- Ground/terrain collisions are ignored and do not trigger weapon firing
- The module can fire continuously or be limited to firing only once
- Status requirements allow fine control over when weapons can fire
- Multiple objects can be damaged simultaneously if they are all in collision contact

## Source Files

**Base Class:** [`CollideModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CollideModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FireWeaponCollide.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FireWeaponCollide.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Collide/FireWeaponCollide.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Collide/FireWeaponCollide.cpp)