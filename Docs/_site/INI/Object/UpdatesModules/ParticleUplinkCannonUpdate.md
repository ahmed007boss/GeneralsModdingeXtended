# ParticleUplinkCannonUpdate

ParticleUplinkCannonUpdate provides particle uplink cannon functionality for objects that can create particle beam effects.

## Overview

The `ParticleUplinkCannonUpdate` class manages particle uplink cannon operations including charging sequences, antenna deployment, beam generation, and particle system effects. It handles the complete firing sequence from initial charge through beam travel, with sophisticated particle effects and laser connections. This update is commonly used by particle cannon weapons, uplink systems, and advanced energy weapons.

## Usage

Used by objects that can create particle beam effects, uplink cannons, or advanced energy weapons. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Cannon operations are limited by charging and deployment timing parameters
- Particle effects depend on proper particle system templates
- Beam generation requires valid laser and connector templates
- Special power integration requires proper special power templates

**Conditions**:
- ParticleUplinkCannonUpdate manages complete particle cannon firing sequence
- The update handles charging, antenna deployment, and beam generation phases
- Particle effects provide visual feedback for cannon operations
- Laser connectors create beam connections between cannon components
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own cannon parameters

**Dependencies**:
- Requires special power system integration for cannon authorization
- Uses particle system for visual effects and beam generation
- Integrates with laser system for beam connections
- Uses bone system for effect positioning

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Special Power Settings](#special-power-settings)
  - [Timing Settings](#timing-settings)
  - [Effect Settings](#effect-settings)
  - [Beam Settings](#beam-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Special Power Settings

#### `SpecialPowerTemplate` *(v1.04)*
- **Type**: `SpecialPowerTemplate`
- **Description**: Special power template that controls particle cannon authorization and targeting. When set, enables special power integration. When empty, no special power coordination occurs
- **Default**: `NULL`
- **Example**: `SpecialPowerTemplate = SpecialAbilityParticleCannon`

### Timing Settings

#### `BeginChargeTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time required to begin charging the particle cannon. Higher values create longer charge initiation. Lower values allow faster charge start
- **Default**: `0`
- **Example**: `BeginChargeTime = 2000`

#### `RaiseAntennaTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time required to raise the cannon antenna. Higher values create slower antenna deployment. Lower values create faster deployment
- **Default**: `0`
- **Example**: `RaiseAntennaTime = 3000`

#### `ReadyDelayTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Delay time before cannon is ready to fire after antenna deployment. Higher values create longer ready delays. Lower values allow faster readiness
- **Default**: `0`
- **Example**: `ReadyDelayTime = 1000`

#### `WidthGrowTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time for beam width to grow to full size. Higher values create slower width growth. Lower values create faster growth
- **Default**: `0`
- **Example**: `WidthGrowTime = 1500`

#### `BeamTravelTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time for beam to travel to target. Higher values create slower beam travel. Lower values create faster travel
- **Default**: `0`
- **Example**: `BeamTravelTime = 500`

#### `TotalFiringTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Total duration of the entire firing sequence. Higher values create longer firing sequences. Lower values create shorter sequences
- **Default**: `0`
- **Example**: `TotalFiringTime = 8000`

#### `RevealRange` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Range at which the cannon reveals itself or becomes visible. Higher values reveal at greater distances. Lower values reveal at closer distances
- **Default**: `0.0`
- **Example**: `RevealRange = 500.0`

### Effect Settings

#### `OuterEffectBoneName` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Base bone name for outer particle effects. When set, effects attach to this bone. When empty, no outer effects are used
- **Default**: `""`
- **Example**: `OuterEffectBoneName = "EffectBone01"`

#### `OuterEffectNumBones` *(v1.04)*
- **Type**: `UnsignedInt`
- **Description**: Number of outer effect bones to use for particle effects. Higher values create more effect points. Lower values create fewer effect points
- **Default**: `0`
- **Example**: `OuterEffectNumBones = 8`

#### `OuterNodesLightFlareParticleSystem` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Particle system template for light flare effects on outer nodes. When set, displays light flares. When empty, no light flares are shown
- **Default**: `""`
- **Example**: `OuterNodesLightFlareParticleSystem = ParticleLightFlare`

#### `OuterNodesMediumFlareParticleSystem` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Particle system template for medium flare effects on outer nodes. When set, displays medium flares. When empty, no medium flares are shown
- **Default**: `""`
- **Example**: `OuterNodesMediumFlareParticleSystem = ParticleMediumFlare`

#### `OuterNodesIntenseFlareParticleSystem` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Particle system template for intense flare effects on outer nodes. When set, displays intense flares. When empty, no intense flares are shown
- **Default**: `""`
- **Example**: `OuterNodesIntenseFlareParticleSystem = ParticleIntenseFlare`

### Beam Settings

#### `ConnectorBoneName` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Bone name for laser connector effects. When set, connectors attach to this bone. When empty, no connectors are used
- **Default**: `""`
- **Example**: `ConnectorBoneName = "ConnectorBone"`

#### `ConnectorMediumLaserName` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Laser template name for medium connector effects. When set, displays medium laser connectors. When empty, no medium connectors are shown
- **Default**: `""`
- **Example**: `ConnectorMediumLaserName = LaserMediumConnector`

## Examples

### Basic Particle Cannon
```ini
Behavior = ParticleUplinkCannonUpdate ModuleTag_08
  SpecialPowerTemplate = SpecialAbilityParticleCannon
  BeginChargeTime = 2000
  RaiseAntennaTime = 3000
  TotalFiringTime = 8000
End
```

### Advanced Particle Cannon with Effects
```ini
Behavior = ParticleUplinkCannonUpdate ModuleTag_08
  SpecialPowerTemplate = SpecialAbilityParticleCannon
  BeginChargeTime = 2000
  RaiseAntennaTime = 3000
  ReadyDelayTime = 1000
  WidthGrowTime = 1500
  BeamTravelTime = 500
  TotalFiringTime = 8000
  RevealRange = 500.0
  OuterEffectBoneName = "EffectBone01"
  OuterEffectNumBones = 8
End
```

## Template

```ini
Behavior = ParticleUplinkCannonUpdate ModuleTag_XX
  ; Special Power Settings
  SpecialPowerTemplate =                ; // special power template for authorization *(v1.04)*
  
  ; Timing Settings
  BeginChargeTime = 0                   ; // time to begin charging *(v1.04)*
  RaiseAntennaTime = 0                  ; // time to raise antenna *(v1.04)*
  ReadyDelayTime = 0                    ; // delay before ready to fire *(v1.04)*
  WidthGrowTime = 0                     ; // time for beam width to grow *(v1.04)*
  BeamTravelTime = 0                    ; // time for beam to travel *(v1.04)*
  TotalFiringTime = 0                   ; // total firing sequence duration *(v1.04)*
  RevealRange = 0.0                     ; // range at which cannon reveals *(v1.04)*
  
  ; Effect Settings
  OuterEffectBoneName =                 ; // base bone for outer effects *(v1.04)*
  OuterEffectNumBones = 0               ; // number of outer effect bones *(v1.04)*
  OuterNodesLightFlareParticleSystem =  ; // light flare particle system *(v1.04)*
  OuterNodesMediumFlareParticleSystem = ; // medium flare particle system *(v1.04)*
  OuterNodesIntenseFlareParticleSystem =; // intense flare particle system *(v1.04)*
  
  ; Beam Settings
  ConnectorBoneName =                   ; // bone for laser connectors *(v1.04)*
  ConnectorMediumLaserName =            ; // medium laser connector template *(v1.04)*
End
```

## Notes

- ParticleUplinkCannonUpdate provides sophisticated particle cannon mechanics with complete firing sequences
- The update manages charging, antenna deployment, and beam generation with precise timing
- Multiple particle system effects create dramatic visual impact for cannon operations
- Laser connectors provide realistic beam connections between cannon components
- This update is commonly used by advanced energy weapons, particle cannons, and uplink systems
- Special power integration ensures proper authorization and targeting for cannon operations

## Source Files

**Base Class:** [`SpecialPowerUpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerUpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ParticleUplinkCannonUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ParticleUplinkCannonUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/ParticleUplinkCannonUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/ParticleUplinkCannonUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet