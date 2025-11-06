# GrantStealthBehavior

Update module that grants stealth to allied units within an expanding radius, with visual effects and unit type filtering.

## Overview

GrantStealthBehavior is an update module that creates an expanding stealth field around an object, granting stealth to allied units within its radius. The stealth field grows from a starting radius to a final radius over time, and the granting object is destroyed when the field reaches maximum size. This creates a temporary stealth effect that can cloak multiple allied units simultaneously.

GrantStealthBehavior must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that should create an expanding stealth field that grants stealth to allied units within its radius. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Only affects allied units within the expanding radius
- Grants stealth only to units that already have stealth capability
- The granting object is destroyed when the field reaches maximum size
- Cannot grant stealth to units that don't have StealthUpdate modules
- Requires units to have existing stealth capability to receive grants

**Conditions**:
- Multiple instances behavior: Multiple GrantStealthBehavior modules can exist independently, each creating separate stealth fields
- Always active once assigned to an object
- Continuously scans and grants stealth to eligible units
- Creates tactical stealth opportunities for multiple units simultaneously

**Dependencies**:
- Requires units to have StealthUpdate modules to receive stealth grants
- Depends on the stealth system for stealth state management
- Inherits all functionality from UpdateModule

## Properties

### Radius Settings

#### `StartRadius` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Initial radius of the stealth field when the behavior begins. Higher values start with a larger stealth area. When set to 0 (default), the stealth field starts at the object's position
- **Default**: `0.0`
- **Example**: `StartRadius = 25.0`

#### `FinalRadius` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Maximum radius the stealth field will reach before the granting object is destroyed. Higher values create larger final stealth areas. When set to 200 (default), the field expands to 200 units
- **Default**: `200.0`
- **Example**: `FinalRadius = 300.0`

#### `RadiusGrowRate` *(v1.04)*
- **Type**: `Real` (distance per update)
- **Description**: Rate at which the stealth field radius expands each update cycle. Higher values make the field grow faster. When set to 10 (default), the radius increases by 10 units per update
- **Default**: `10.0`
- **Example**: `RadiusGrowRate = 15.0`

### Unit Filtering

#### `KindOf` *(v1.04)*
- **Type**: `KindOfMaskType` (bit flags)
- **Description**: Bitmask of unit types that can receive stealth grants. Only units matching these types will be granted stealth. When set to all types (default), any unit type can receive stealth
- **Default**: `SET_ALL_KINDOFMASK_BITS` (all unit types)
- **Example**: `KindOf = INFANTRY`

### Visual Effects

#### `RadiusParticleSystemName` *(v1.04)*
- **Type**: `ParticleSystemTemplate`
- **Description**: Particle system template for visual effects that follow the expanding stealth field. When set, displays particle effects that grow with the stealth radius. When NULL (default), no visual effects are shown
- **Default**: `NULL` (none)
- **Example**: `RadiusParticleSystemName = PS_StealthField`

## Examples

### Basic Stealth Field
```ini
Update = GrantStealthBehavior ModuleTag_01
  StartRadius = 0.0
  FinalRadius = 150.0
  RadiusGrowRate = 12.0
  KindOf = INFANTRY
  RadiusParticleSystemName = PS_StealthField
End
```

### Large Stealth Burst
```ini
Update = GrantStealthBehavior ModuleTag_02
  StartRadius = 50.0
  FinalRadius = 400.0
  RadiusGrowRate = 20.0
  KindOf = INFANTRY VEHICLE
  RadiusParticleSystemName = PS_LargeStealthField
End
```

### Vehicle-Only Stealth Field
```ini
Update = GrantStealthBehavior ModuleTag_03
  StartRadius = 25.0
  FinalRadius = 200.0
  RadiusGrowRate = 10.0
  KindOf = VEHICLE
  RadiusParticleSystemName = PS_VehicleStealthField
End
```

## Template

```ini
Update = GrantStealthBehavior ModuleTag_XX
  ; Radius Settings
  StartRadius = 0.0                    ; // initial stealth field radius *(v1.04)*
  FinalRadius = 200.0                  ; // maximum stealth field radius *(v1.04)*
  RadiusGrowRate = 10.0                ; // radius expansion rate per update *(v1.04)*
  
  ; Unit Filtering
  KindOf = SET_ALL_KINDOFMASK_BITS     ; // unit types that can receive stealth *(v1.04)*
  
  ; Visual Effects
  RadiusParticleSystemName =           ; // stealth field visual effects *(v1.04)*
End
```

## Notes

- GrantStealthBehavior creates an expanding stealth field that grants stealth to allied units
- The stealth field grows from StartRadius to FinalRadius at RadiusGrowRate per update
- Only affects units that have StealthUpdate modules and match the specified KindOf filter
- The granting object is automatically destroyed when the field reaches FinalRadius
- Creates tactical stealth opportunities for multiple units simultaneously
- Commonly used by stealth generators, special powers, or temporary stealth effects
- Visual effects can be added to show the expanding stealth field
- Units that receive stealth grants flash briefly to indicate the effect

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/GrantStealthBehavior.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/GrantStealthBehavior.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/GrantStealthBehavior.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/GrantStealthBehavior.cpp)