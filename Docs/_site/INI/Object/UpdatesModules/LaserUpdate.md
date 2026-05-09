# LaserUpdate

LaserUpdate provides laser functionality for objects that can create or use laser effects.

## Overview

The `LaserUpdate` class manages laser beam creation and visual effects for objects that can generate laser beams, laser weapons, or laser-based special effects. It handles particle system effects for laser muzzles and targets, manages laser beam rendering, and provides punch-through effects for enhanced visual impact. This update is commonly used by laser weapons, point defense systems, and special laser-based abilities.

## Usage

Used by objects that can create laser beams, laser weapons, or laser-based special effects. This is a **client update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Laser effects are limited by particle system templates
- Punch-through effects require proper scalar configuration
- Visual effects depend on client-side rendering capabilities
- Laser beam rendering is limited by graphics system performance

**Conditions**:
- LaserUpdate creates visual laser beams between specified start and end positions
- The update manages particle system effects for laser muzzles and targets
- Punch-through effects enhance laser visual impact when targets are destroyed
- Laser beam properties can be dynamically adjusted during runtime
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own laser effects

**Dependencies**:
- Requires particle system templates for muzzle and target effects
- Uses client rendering system for laser beam visualization
- Integrates with weapon systems for laser weapon functionality

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Particle System Settings](#particle-system-settings)
  - [Visual Effects Settings](#visual-effects-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Particle System Settings

#### `MuzzleParticleSystem` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Particle system template for muzzle flare effects while laser is active. When set, displays muzzle effects. When empty, no muzzle effects are shown
- **Default**: `""`
- **Example**: `MuzzleParticleSystem = RedFlare`

#### `TargetParticleSystem` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Particle system template for target impact effects while laser is active. When set, displays target effects. When empty, no target effects are shown
- **Default**: `""`
- **Example**: `TargetParticleSystem = GenericRedLaserFlare`

### Visual Effects Settings

#### `PunchThroughScalar` *(v1.04)*
- **Type**: `Real`
- **Description**: Length multiplier when laser target is destroyed, creating punch-through visual effect. Higher values create longer punch-through effects. At 0, no punch-through effect occurs
- **Default**: `0.0`
- **Example**: `PunchThroughScalar = 1.5`

## Examples

### Basic Red Laser
```ini
ClientUpdate = LaserUpdate ModuleTag_02
  MuzzleParticleSystem = RedFlare
  TargetParticleSystem = GenericRedLaserFlare
End
```

### Green Laser with Punch-Through
```ini
ClientUpdate = LaserUpdate ModuleTag_02
  MuzzleParticleSystem = GenericGreenLaserFlare
  TargetParticleSystem = GenericGreenLaserFlare
End
```

### Point Defense Laser
```ini
ClientUpdate = LaserUpdate ModuleTag_07
  MuzzleParticleSystem = GreenPointDefenseLaserFlare
  TargetParticleSystem = GenericGreenLaserFlare
  PunchThroughScalar = 1.5 ; If our target dies, we get this much bigger so it looks like we punched through
End
```

## Template

```ini
ClientUpdate = LaserUpdate ModuleTag_XX
  ; Particle System Settings
  MuzzleParticleSystem =                ; // particle system for muzzle flare *(v1.04)*
  TargetParticleSystem =                ; // particle system for target impact *(v1.04)*
  
  ; Visual Effects Settings
  PunchThroughScalar = 0.0              ; // punch-through effect multiplier *(v1.04)*
End
```

## Notes

- LaserUpdate is a client-side update module that handles laser visual effects
- The update creates realistic laser beams with particle system effects at both ends
- Punch-through effects enhance visual impact when laser targets are destroyed
- Particle system templates control the appearance of muzzle and target effects
- This update is commonly used by laser weapons, point defense systems, and special abilities
- Laser beam rendering integrates with the game's graphics system for optimal performance

## Source Files

**Base Class:** [`ClientUpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ClientUpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/LaserUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/LaserUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/LaserUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/LaserUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet