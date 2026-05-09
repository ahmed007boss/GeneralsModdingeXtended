# LaserUpdate

Client update module that manages laser beam rendering, particle effects, and visual updates for laser weapons and effects.

## Overview

LaserUpdate is a client update module that handles the visual rendering and particle effects for laser beams in the game. It manages laser positioning, particle systems for muzzle and target effects, and provides dynamic width scaling for laser appearance. This module is commonly used for laser weapons, cutting tools, and visual laser effects.

LaserUpdate must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that should render laser beams with particle effects and dynamic positioning. This is a **client update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Client-side only module for visual effects
- Requires valid particle system templates for effects
- Laser visibility depends on parent and target object states
- Cannot function without proper initialization
- Only provides visual effects, no gameplay impact

**Conditions**:
- Multiple instances behavior: Multiple LaserUpdate modules can exist independently, each managing different laser effects
- Always active once assigned to an object
- Continuously updates laser positioning and effects
- Manages laser beam rendering and particle system effects

**Dependencies**:
- Requires valid particle system templates for visual effects
- Depends on parent and target objects for positioning
- Inherits all functionality from ClientUpdateModule

## Properties

### Particle Effects

#### `MuzzleParticleSystem` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Name of the particle system template for muzzle flare effects at the laser source. When set, displays particle effects at the laser's starting point. When empty (default), no muzzle effects are shown
- **Default**: `""` (empty)
- **Example**: `MuzzleParticleSystem = PS_LaserMuzzleFlare`

#### `TargetParticleSystem` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Name of the particle system template for target effects at the laser's impact point. When set, displays particle effects where the laser hits. When empty (default), no target effects are shown
- **Default**: `""` (empty)
- **Example**: `TargetParticleSystem = PS_LaserTargetImpact`

### Laser Behavior

#### `PunchThroughScalar` *(v1.04)*
- **Type**: `Real` (multiplier)
- **Description**: Length modifier for the laser when it loses its target object. Higher values extend the laser further when targets are lost. When set to 0 (default), the laser maintains its original length
- **Default**: `0.0`
- **Example**: `PunchThroughScalar = 1.5`

## Examples

### Basic Laser Weapon
```ini
Update = LaserUpdate ModuleTag_01
  MuzzleParticleSystem = PS_LaserMuzzleFlare
  TargetParticleSystem = PS_LaserTargetImpact
  PunchThroughScalar = 1.0
End
```

### Cutting Laser Tool
```ini
Update = LaserUpdate ModuleTag_02
  MuzzleParticleSystem = PS_CuttingLaserMuzzle
  TargetParticleSystem = PS_CuttingLaserImpact
  PunchThroughScalar = 2.0
End
```

### Simple Laser Effect
```ini
Update = LaserUpdate ModuleTag_03
  MuzzleParticleSystem = PS_SimpleLaserMuzzle
  TargetParticleSystem = PS_SimpleLaserTarget
  PunchThroughScalar = 0.0
End
```

## Template

```ini
Update = LaserUpdate ModuleTag_XX
  ; Particle Effects
  MuzzleParticleSystem =             ; // muzzle flare particle system *(v1.04)*
  TargetParticleSystem =             ; // target impact particle system *(v1.04)*
  
  ; Laser Behavior
  PunchThroughScalar = 0.0           ; // length modifier when target lost *(v1.04)*
End
```

## Notes

- LaserUpdate manages laser beam visual rendering and particle effects
- Provides dynamic width scaling and positioning updates
- Handles muzzle and target particle effects for enhanced visual impact
- Supports punch-through behavior when targets are lost
- Commonly used for laser weapons, cutting tools, and visual laser effects
- The module manages laser positioning between parent and target objects
- Includes decay and widening effects for dynamic laser appearance
- Client-side only module focused on visual presentation

## Source Files

**Base Class:** [`ClientUpdateModule`](../../GeneralsMD/Code/GameEngine/Include/Common/ClientUpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/LaserUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/LaserUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/LaserUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/LaserUpdate.cpp)
