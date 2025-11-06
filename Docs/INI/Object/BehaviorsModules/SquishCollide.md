# SquishCollide

Collision module that allows objects to be crushed by larger vehicles when run over.

## Overview

SquishCollide is a collision detection module that enables smaller objects (like infantry) to be crushed when run over by larger vehicles with crush capabilities. The module checks if the crushing object is moving toward the victim and applies massive crush damage. It includes special logic to prevent crushing during hijacking attempts and TNT placement by tank hunters.

SquishCollide must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that should be crushed by larger vehicles when run over. This is a **collision module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Only works when the crushing object has a crush level greater than 0
- Requires the crushing object to be moving toward the victim
- Does not work during hijacking or TNT placement operations
- Only affects non-allied objects
- Requires proper physics and geometry data for collision detection

**Conditions**:
- Multiple instances behavior: Multiple SquishCollide modules can exist independently
- Active when objects are in collision contact
- Requires proper physics and geometry data for collision detection
- Creates realistic vehicle crushing mechanics

**Dependencies**:
- Requires crushing objects to have crush level capabilities
- Depends on physics system for velocity calculations
- Requires proper geometry collision detection

## Properties

SquishCollide inherits all properties from CollideModule with no additional INI-parsable properties.

## Examples

### Infantry Unit Susceptible to Crushing
```ini
Collide = SquishCollide ModuleTag_01
End
```

### Light Vehicle with Crush Vulnerability
```ini
Collide = SquishCollide ModuleTag_02
End
```

## Template

```ini
Collide = SquishCollide ModuleTag_XX
  ; No additional properties - inherits from CollideModule
End
```

## Notes

- SquishCollide enables objects to be crushed by vehicles with crush capabilities
- Crushing only occurs when the vehicle is moving toward the victim object
- Special exceptions prevent crushing during hijacking attempts and TNT placement
- Objects must have a crush level greater than 0 to crush other objects
- Crush damage uses DAMAGE_CRUSH type with DEATH_CRUSHED death type
- The crushing object must not be allied with the victim
- Geometry collision detection ensures actual physical contact occurs
- Commonly used on infantry and light vehicles that should be vulnerable to being run over

## Source Files

**Base Class:** [`CollideModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CollideModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SquishCollide.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SquishCollide.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Collide/SquishCollide.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Collide/SquishCollide.cpp)