# InstantDeathBehavior

Die module that provides instant death effects including random FX, object creation, and weapon firing when objects die.

## Overview

InstantDeathBehavior is a die module that creates immediate death effects when objects die, including random visual effects, object creation, and weapon firing. It randomly selects from lists of FX, object creation lists, and weapons to create varied death effects. This module is commonly used for explosive objects, traps, and units that should have dramatic death sequences.

InstantDeathBehavior must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that should create immediate death effects including random visual effects, object creation, and weapon firing when they die. This is a **die module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Requires valid FX lists, object creation lists, or weapon templates to function
- Only activates when death conditions are met (inherits DieModule filtering)
- Cannot prevent other death behaviors from running simultaneously
- Objects are immediately destroyed after effects are triggered
- Effects are randomly selected from available options

**Conditions**:
- Multiple instances behavior: Multiple InstantDeathBehavior modules can exist independently, each providing different death effects
- Only activates when the object dies and meets the specified death conditions
- Randomly selects from available effects when multiple options exist
- Creates dramatic death sequences with varied effects

**Dependencies**:
- Requires valid FX lists for visual effects
- Requires valid object creation lists for spawning objects
- Requires valid weapon templates for weapon firing
- Inherits all functionality from DieModule

## Properties

### Visual Effects

#### `FX` *(v1.04)*
- **Type**: `FXList` (multiple entries) (see [FXList documentation](../FXList.md))
- **Description**: List of FX list templates for death visual effects. When multiple entries exist, one is randomly selected when the object dies. When empty (default), no visual effects are played
- **Default**: `None`
- **Example**: 
```
FX = FX_ExplosionLarge
FX = FX_ExplosionMedium
FX = FX_FireBurst
```

### Object Creation

#### `OCL` *(v1.04)*
- **Type**: `ObjectCreationList` (multiple entries)
- **Description**: List of object creation list templates for spawning objects on death. When multiple entries exist, one is randomly selected when the object dies. When empty (default), no objects are created
- **Default**: `None`
- **Example**: 
```
OCL = OCL_DebrisSmall
OCL = OCL_DebrisMedium
OCL = OCL_ExplosiveRemnants
```

### Weapon Effects

#### `Weapon` *(v1.04)*
- **Type**: `Weapon` (multiple entries) (see [Weapon documentation](../Weapon.md))
- **Description**: List of weapon templates to fire on death. When multiple entries exist, one is randomly selected when the object dies. When empty (default), no weapons are fired
- **Default**: `None`
- **Example**: 
```
Weapon = WeaponExplosionSmall
Weapon = WeaponExplosionMedium
Weapon = WeaponExplosionLarge
```

## Examples

### Basic Explosive Death
```ini
Die = InstantDeathBehavior ModuleTag_01
  FX = FX_ExplosionSmall
  OCL = OCL_DebrisSmall
  Weapon = WeaponExplosionSmall
End
```

### Varied Explosive Effects
```ini
Die = InstantDeathBehavior ModuleTag_02
  FX = FX_ExplosionLarge
  FX = FX_FireBurst
  FX = FX_SmokeCloud
  
  OCL = OCL_DebrisLarge
  OCL = OCL_ExplosiveRemnants
  OCL = OCL_FireDebris
  
  Weapon = WeaponExplosionLarge
  Weapon = WeaponExplosionMedium
End
```

### Trap Death Effects
```ini
Die = InstantDeathBehavior ModuleTag_03
  FX = FX_TrapExplosion
  OCL = OCL_TrapDebris
  Weapon = WeaponTrapExplosion
End
```

## Template

```ini
Die = InstantDeathBehavior ModuleTag_XX
  ; Visual Effects
  FX =                               ; // death visual effects *(v1.04)*
  FX =                               ; // additional death visual effects *(v1.04)*
  
  ; Object Creation
  OCL =                              ; // objects to create on death *(v1.04)*
  OCL =                              ; // additional objects to create *(v1.04)*
  
  ; Weapon Effects
  Weapon =                           ; // weapons to fire on death *(v1.04)*
  Weapon =                           ; // additional weapons to fire *(v1.04)*
End
```

## Notes

- InstantDeathBehavior creates immediate death effects including visual effects, object creation, and weapon firing
- When multiple effects of the same type are specified, one is randomly selected
- Objects are immediately destroyed after all effects are triggered
- Commonly used for explosive objects, traps, and units with dramatic death sequences
- Provides variety in death effects through random selection from available options
- The module ensures objects are properly marked as dead before triggering effects
- Effects are applied in order: visual effects, object creation, then weapon firing

## Source Files

**Base Class:** [`DieModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/InstantDeathBehavior.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/InstantDeathBehavior.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/InstantDeathBehavior.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/InstantDeathBehavior.cpp)