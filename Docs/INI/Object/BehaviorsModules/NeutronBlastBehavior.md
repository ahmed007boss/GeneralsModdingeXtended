# NeutronBlastBehavior

Update module that creates neutron blast effects that eliminate infantry units within a specified radius, regardless of their location or protection.

## Overview

NeutronBlastBehavior is an update module that creates neutron blast effects designed to eliminate infantry units within a specified radius. The blast can affect airborne units and can be configured to target allies or enemies. This creates a powerful area-of-effect weapon that specifically targets infantry, making it effective against hidden or protected infantry units.

NeutronBlastBehavior must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that should create neutron blast effects that eliminate infantry units within a specified radius when they die. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Primarily affects infantry units
- Limited to the specified blast radius
- Cannot function without proper death and update systems
- Requires proper blast configuration for functionality

**Conditions**:
- Multiple instances behavior: Multiple NeutronBlastBehavior modules can exist independently, each creating different blast effects
- Always active once assigned to an object
- Triggers during death events and manages blast effects
- Creates powerful anti-infantry capabilities with area-of-effect damage

**Dependencies**:
- Depends on the death system for blast triggering
- Inherits functionality from UpdateModule and DieModuleInterface

## Properties

### Blast Configuration

#### `BlastRadius` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Radius of the neutron blast effect. Higher values create larger blast areas. When set to 10 (default), creates a 10-unit radius blast
- **Default**: `10.0`
- **Example**: `BlastRadius = 50.0`

### Target Selection

#### `AffectAirborne` *(v1.04)*
- **Type**: `Bool`
- **Description**: Determines if airborne units are affected by the neutron blast. When `Yes` (default), airborne units are affected. When `No`, airborne units are not affected
- **Default**: `Yes`
- **Example**: `AffectAirborne = No`

#### `AffectAllies` *(v1.04)*
- **Type**: `Bool`
- **Description**: Determines if allied units are affected by the neutron blast. When `Yes` (default), allied units are affected. When `No`, allied units are not affected
- **Default**: `Yes`
- **Example**: `AffectAllies = No`

## Examples

### Basic Neutron Blast
```ini
Update = NeutronBlastBehavior ModuleTag_01
  BlastRadius = 25.0
  AffectAirborne = Yes
  AffectAllies = No
End
```

### Large Area Blast
```ini
Update = NeutronBlastBehavior ModuleTag_02
  BlastRadius = 100.0
  AffectAirborne = Yes
  AffectAllies = Yes
End
```

### Ground-Only Blast
```ini
Update = NeutronBlastBehavior ModuleTag_03
  BlastRadius = 40.0
  AffectAirborne = No
  AffectAllies = No
End
```

## Template

```ini
Update = NeutronBlastBehavior ModuleTag_XX
  ; Blast Configuration
  BlastRadius = 10.0                    ; // radius of neutron blast effect *(v1.04)*
  
  ; Target Selection
  AffectAirborne = Yes                  ; // affect airborne units *(v1.04)*
  AffectAllies = Yes                    ; // affect allied units *(v1.04)*
End
```

## Notes

- NeutronBlastBehavior creates neutron blast effects that eliminate infantry units
- Can affect units regardless of their location or protection
- Supports configurable blast radius and target selection
- Commonly used for superweapon effects and area denial weapons
- The module manages blast effects during death events
- Creates powerful anti-infantry capabilities with area-of-effect damage

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/NeutronBlastBehavior.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/NeutronBlastBehavior.h)
