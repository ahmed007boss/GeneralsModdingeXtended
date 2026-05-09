# FXList INI Documentation

## Overview

The `FXList` INI file contains FX list configuration settings and parameters for visual effects, audio effects, and particle systems. FX lists are collections of effect nuggets that create combined audio-visual effects for weapons, damage, explosions, and other game events.

## Usage

FX list templates are defined in INI files and specify the visual and audio effects that play during specific game events. This is a **template configuration system** that defines combined audio-visual effects. The FX list system provides visual and audio feedback for combat, explosions, and other game events.

**Limitations**:
- FX lists are limited to predefined effect nugget types
- Effects are fixed and cannot be dynamically modified during runtime
- Effect timing is controlled by fixed parameters
- Visual effects depend on proper graphics system configuration

**Conditions**:
- FX lists manage combined audio-visual effects for game events
- The configuration handles effect types, parameters, and positioning
- FX list operations provide visual and audio feedback for combat and events
- FX list management ensures appropriate effects for different game situations
- **Multiple instances behavior**: FX lists are shared between multiple objects

**Dependencies**:
- Uses graphics system for visual effects and particle systems
- Uses audio system for sound effects
- Integrates with the game's effect rendering system
- Uses particle system templates for visual effects
- Referenced by weapons, damage systems, and other game objects

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Sound Effects](#sound-effects)
  - [Ray Effects](#ray-effects)
  - [Tracer Effects](#tracer-effects)
  - [Light Pulse Effects](#light-pulse-effects)
  - [View Shake Effects](#view-shake-effects)
  - [Terrain Scorch Effects](#terrain-scorch-effects)
  - [Particle System Effects](#particle-system-effects)
  - [FX List at Bone Position Effects](#fx-list-at-bone-position-effects)
- [Examples](#examples)
- [Best Practices](#best-practices)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Sound Effects *(v1.04)*

#### `Sound` *(v1.04)*
- **Type**: `Sound` block
- **Description**: Audio effect to play when the FX list is triggered. Provides sound feedback for the effect.
- **Default**: None
- **Example**: 
  ```
  Sound
      Name = WeaponFireSound
  End
  ```

#### Sound Properties *(v1.04)*

##### `Name` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Name of the audio event to play. Must reference a valid audio event defined in the audio system.
- **Default**: None
- **Example**: `Name = ExplosionMOAB` // Plays the MOAB explosion sound

### Ray Effects *(v1.04)*

#### `RayEffect` *(v1.04)*
- **Type**: `RayEffect` block
- **Description**: Ray-based visual effect that creates a line or beam between two points. Used for lasers, energy beams, and similar effects.
- **Default**: None
- **Example**: 
  ```
  RayEffect
      Name = LaserBeamEffect
  End
  ```

#### Ray Effect Properties *(v1.04)*

##### `Name` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Name of the ray effect template to use.
- **Default**: None
- **Example**: `Name = LaserBeamRay` // Uses the laser beam ray effect

### Tracer Effects *(v1.04)*

#### `Tracer` *(v1.04)*
- **Type**: `Tracer` block
- **Description**: Tracer effect that creates a visible trail for projectiles. Shows the path of bullets, missiles, and other projectiles.
- **Default**: None
- **Example**: 
  ```
  Tracer
      Name = BulletTracerEffect
  End
  ```

#### Tracer Properties *(v1.04)*

##### `Name` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Name of the tracer effect template to use.
- **Default**: None
- **Example**: `Name = BulletTracer` // Uses the bullet tracer effect

### Light Pulse Effects *(v1.04)*

#### `LightPulse` *(v1.04)*
- **Type**: `LightPulse` block
- **Description**: Light pulse effect that creates a brief flash of light. Used for explosions, muzzle flashes, and other bright effects.
- **Default**: None
- **Example**: 
  ```
  LightPulse
      Name = ExplosionFlash
  End
  ```

#### Light Pulse Properties *(v1.04)*

##### `Name` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Name of the light pulse effect template to use.
- **Default**: None
- **Example**: `Name = MuzzleFlash` // Uses the muzzle flash light effect

### View Shake Effects *(v1.04)*

#### `ViewShake` *(v1.04)*
- **Type**: `ViewShake` block
- **Description**: View shake effect that causes the camera to shake. Used for explosions, impacts, and other powerful effects.
- **Default**: None
- **Example**: 
  ```
  ViewShake
      Type = SEVERE
  End
  ```

#### View Shake Properties *(v1.04)*

##### `Type` *(v1.04)*
- **Type**: `ViewShakeType`
- **Description**: Intensity of the camera shake effect.
- **Default**: `SUBTLE`
- **Available Values**: `SUBTLE`, `STRONG`, `SEVERE`, `CINE_INSANE`
- **Example**: `Type = SEVERE` // Strong camera shake for major explosions

### Terrain Scorch Effects *(v1.04)*

#### `TerrainScorch` *(v1.04)*
- **Type**: `TerrainScorch` block
- **Description**: Terrain scorch effect that creates burn marks or damage on the terrain. Used for explosions, fires, and other destructive effects.
- **Default**: None
- **Example**: 
  ```
  TerrainScorch
      Type = RANDOM
      Radius = 30
  End
  ```

#### Terrain Scorch Properties *(v1.04)*

##### `Type` *(v1.04)*
- **Type**: `TerrainScorchType`
- **Description**: Type of terrain damage to apply.
- **Default**: `RANDOM`
- **Available Values**: `RANDOM`, `CRATER`
- **Example**: `Type = RANDOM` // Creates random burn marks

##### `Radius` *(v1.04)*
- **Type**: `Real`
- **Description**: Radius of the terrain damage area in world units.
- **Default**: `10`
- **Example**: `Radius = 30` // 30-unit radius damage area

### Particle System Effects *(v1.04)*

#### `ParticleSystem` *(v1.04)*
- **Type**: `ParticleSystem` block
- **Description**: Particle system effect that creates particle-based visual effects. Used for smoke, fire, sparks, and other particle effects.
- **Default**: None
- **Example**: 
  ```
  ParticleSystem
      Name = ExplosionParticles
      Offset = X:0 Y:0 Z:10
      Count = 3
      Radius = 15 30 UNIFORM
  End
  ```

#### Particle System Properties *(v1.04)*

##### `Name` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Name of the particle system template to use. Must reference a valid particle system template.
- **Default**: None
- **Example**: `Name = ArtilleryBlowUpLight` // Uses the artillery light particle system

##### `Offset` *(v1.04)*
- **Type**: `Coord3D`
- **Description**: Position offset for the particle system relative to the trigger location.
- **Format**: `Offset = X:value Y:value Z:value`
- **Default**: `X:0 Y:0 Z:0`
- **Example**: `Offset = X:5 Y:0 Z:5` // 5 units forward and up

##### `Count` *(v1.04)*
- **Type**: `UnsignedInt`
- **Description**: Number of particle system instances to create. Used for multiple effects at random positions.
- **Default**: `1`
- **Example**: `Count = 3` // Creates 3 particle system instances

##### `Radius` *(v1.04)*
- **Type**: `Real` or `RealRange`
- **Description**: Radius for random positioning of multiple particle system instances.
- **Format**: `Radius = min max UNIFORM` or `Radius = value`
- **Default**: `0`
- **Example**: `Radius = 15 30 UNIFORM` // Random radius between 15 and 30 units

##### `Height` *(v1.04)*
- **Type**: `Real` or `RealRange`
- **Description**: Height variation for random positioning of multiple particle system instances.
- **Format**: `Height = min max UNIFORM` or `Height = value`
- **Default**: `0`
- **Example**: `Height = 0 20 UNIFORM` // Random height between 0 and 20 units

##### `InitialDelay` *(v1.04)*
- **Type**: `UnsignedIntRange` (milliseconds)
- **Description**: Delay before the particle system starts playing.
- **Format**: `InitialDelay = min max UNIFORM`
- **Default**: `0`
- **Example**: `InitialDelay = 100 120 UNIFORM` // Delay between 100-120ms

##### `OrientToObject` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether the particle system should orient itself to the object's rotation.
- **Default**: `No`
- **Example**: `OrientToObject = Yes` // Particle system follows object rotation

##### `RotateY` *(v1.04)*
- **Type**: `Real` (degrees)
- **Description**: Y-axis rotation offset for the particle system.
- **Default**: `0`
- **Example**: `RotateY = 90` // Rotate 90 degrees around Y-axis

### FX List at Bone Position Effects *(v1.04)*

#### `FXListAtBonePos` *(v1.04)*
- **Type**: `FXListAtBonePos` block
- **Description**: Effect that plays another FX list at a specific bone position on an object. Used for weapon muzzle flashes, engine effects, and other bone-attached effects.
- **Default**: None
- **Example**: 
  ```
  FXListAtBonePos
      FX = MuzzleFlashEffect
      Bone = MuzzleBone
  End
  ```

#### FX List at Bone Position Properties *(v1.04)*

##### `FX` *(v1.04)*
- **Type**: `FXList` (see [FXList documentation](FXList.md))
- **Description**: Name of the FX list to play at the bone position.
- **Default**: None
- **Example**: `FX = MuzzleFlashFX` // Plays the muzzle flash effect

##### `Bone` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Name of the bone on the object where the effect should be played.
- **Default**: None
- **Example**: `Bone = MuzzleBone` // Plays effect at the muzzle bone

## Examples

### Simple Sound Effect
```ini
FXList FX_USA_Helipad_Complete
    Sound
        Name = EVAAmericaConstructionComplete
    End
End
```

### Complex Explosion Effect (Real Example)
```ini
FXList PCL191MissileDetonation
    ParticleSystem
        Name = ArtilleryBlowUpLight
        Count = 1
        Offset = X:-30 Y:0 Z:00
    End
    ParticleSystem
        Name = ArtilleryExplosion_Stage01
    End
    
    ; Stage02: Shockwave
    ParticleSystem
        Name = HeavySAM_Explosion_Shockwave
        InitialDelay = 20 25 UNIFORM
        Offset = X:0.0 Y:0.0 Z:18.0
    End
    
    ; Stage03: Sparks
    ParticleSystem
        Name = HeavyAntiAirExplosionSparks
        InitialDelay = 28 35 UNIFORM
        Offset = X:0.0 Y:0.0 Z:20.0
    End
    
    ParticleSystem
        Name = HeavyAntiAirExplosionSparks2
        InitialDelay = 40 45 UNIFORM
        Offset = X:0.0 Y:0.0 Z:10.0
    End
    
    ; Stage04: Explosion Bright Small
    ParticleSystem
        Name = TEODHeavyAirExplosion
        InitialDelay = 45 52 UNIFORM
        Offset = X:0.0 Y:0.0 Z:10.0
    End
    
    ; Stage05: Explosion Bright Big
    ParticleSystem
        Name = HeavyAntiAirExplosionSmoke
        InitialDelay = 80 90 UNIFORM
        Offset = X:0.0 Y:0.0 Z:10.0
    End
    
    ParticleSystem
        Name = ScudMissleLauncherExplosionArms
        InitialDelay = 45 52 UNIFORM
        Offset = X:0.0 Y:0.0 Z:5.0
    End
    
    ParticleSystem
        Name = ScudMissleLauncherExplosionTrailArms
        InitialDelay = 45 52 UNIFORM
        Offset = X:0.0 Y:0.0 Z:10.0
    End
    
    TerrainScorch
        Type = RANDOM
        Radius = 30
    End
    
    ViewShake
        Type = SEVERE
    End
    
    Sound
        Name = CarDie
    End
End
```

### Helicopter Delivery Effect
```ini
FXList FX_HelicopterDeliversObject_Dust
    ParticleSystem
        Name = HelicopterDeliverObjectDust
        Offset = X:5 Y:0 Z:5
    End
    ViewShake
        Type = SUBTLE
    End
    Sound
        Name = PlaceBuilding
    End
End
```

### Vehicle Damage Transition Effect
```ini
FXList FX_HumveeDamageTransition
    ParticleSystem
        Name = HumveeTransitionExplosion1
        Offset = X:0 Y:0 Z:10
    End
    ViewShake
        Type = SUBTLE
    End
    Sound
        Name = VehicleDamagedState
    End
End
```

### Multiple Sound Effects
```ini
FXList FX_ComancheBladeExplosion
    ParticleSystem
        Name = TankStruckSparks
        Count = 5
        Radius = 5 5 UNIFORM
    End
    Sound
        Name = ComancheSpinExplosion
    End
End
```

### Missile Launch Effect
```ini
FXList WeaponFX_BastionMissileIgnition
    ParticleSystem
        Name = BastionRearSmoke
        Offset = X:0.0 Y:0.0 Z:-10.0
        OrientToObject = Yes
        RotateY = 90
    End
    ParticleSystem
        Name = BlowUpLight
        Offset = X:0.0 Y:0.0 Z:0.0
        InitialDelay = 0 0 UNIFORM
        OrientToObject = Yes
    End
End
```

## Best Practices

### Effect Combination Design

1. **Layered Effects**: Combine multiple effect types for rich visual and audio feedback
2. **Performance Balance**: Balance visual quality with performance impact
3. **Effect Timing**: Synchronize audio and visual effects for maximum impact
4. **Resource Management**: Reuse common effects across multiple FX lists

### Audio-Visual Synchronization

1. **Sound Timing**: Ensure sound effects match visual effect timing
2. **Volume Balance**: Balance sound effect volumes with visual impact
3. **Effect Duration**: Match audio and visual effect durations
4. **Spatial Audio**: Use appropriate audio positioning for 3D effects

### Performance Optimization

1. **Effect Complexity**: Use appropriate complexity for the intended use case
2. **Particle Count**: Limit particle system complexity for better performance
3. **Effect Culling**: Use appropriate culling for distant effects
4. **Memory Usage**: Minimize memory usage for frequently used effects

### Visual Effect Design

1. **Color Coordination**: Use consistent color schemes across related effects
2. **Scale Appropriateness**: Ensure effects are appropriately sized for their context
3. **Duration Matching**: Match effect duration to the triggering event
4. **Impact Clarity**: Ensure effects clearly communicate the event that triggered them

### Effect Categories

1. **Weapon Effects**: Group weapon-related effects for consistency
2. **Explosion Effects**: Use consistent explosion effect patterns
3. **Environmental Effects**: Create reusable environmental effect templates
4. **Special Effects**: Design unique effects for special abilities and powers

## Template

```ini
FXList FXListName
    ; Audio effects:
    Sound
        Name = AudioEventName               ; // Audio event name *(v1.04)*
    End
    
    ; Particle system effects:
    ParticleSystem
        Name = ParticleSystemName           ; // Particle system template *(v1.04)*
        Offset = X:0 Y:0 Z:0                ; // Position offset *(v1.04)*
        Count = 1                           ; // Number of instances *(v1.04)*
        Radius = 0                          ; // Random radius *(v1.04)*
        Height = 0                          ; // Random height *(v1.04)*
        InitialDelay = 0 0 UNIFORM          ; // Start delay (ms) *(v1.04)*
        OrientToObject = No                 ; // Follow object rotation *(v1.04)*
        RotateY = 0                         ; // Y-axis rotation (degrees) *(v1.04)*
    End
    
    ; Camera shake effects:
    ViewShake
        Type = SUBTLE                       ; // Shake intensity *(v1.04)*
    End
    
    ; Terrain damage effects:
    TerrainScorch
        Type = RANDOM                       ; // Scorch type *(v1.04)*
        Radius = 10                         ; // Damage radius *(v1.04)*
    End
    
    ; Additional effects (if needed):
    ; RayEffect
    ;     Name = RayEffectName              ; // Ray-based effect *(v1.04)*
    ; End
    ; 
    ; Tracer
    ;     Name = TracerName                 ; // Tracer effect *(v1.04)*
    ; End
    ; 
    ; LightPulse
    ;     Name = LightPulseName             ; // Light flash effect *(v1.04)*
    ; End
    ; 
    ; FXListAtBonePos
    ;     FX = BoneFXListName               ; // Bone-attached effect *(v1.04)*
    ;     Bone = BoneName                   ; // Bone name *(v1.04)*
    ; End
End
```

## Notes

- FX lists provide combined audio-visual effects for weapons, damage, explosions, and other game events
- The configuration manages effect types, parameters, and positioning for immersive feedback
- FX list operations create rich visual and audio experiences for combat and events
- FX list management ensures appropriate effects for different game situations and contexts
- This configuration is essential for creating immersive and engaging gameplay experiences
- FX list coordination creates consistent effect patterns across different game events
- Effect nuggets can be combined in various ways to create unique and compelling effects
- The system supports multiple effect types working together for maximum visual and audio impact
- FX lists are shared between multiple objects to optimize memory usage and performance
- Effects are triggered by game events and provide immediate feedback to players
- Visual effects are rendered through the game's graphics system and particle engine
- Audio effects are played through the game's audio system with appropriate positioning
- The system integrates with weapons, damage systems, and other game objects
- FX list templates are defined in INI files and loaded by the FX list system
- Effect parameters can be adjusted to balance visual impact with performance
- The system supports complex effect combinations for special abilities and powers
- FX lists provide critical feedback that helps players understand game events and combat results
- Effect timing and synchronization are crucial for creating convincing and impactful effects
- The system can be optimized for different performance levels and hardware capabilities
- FX lists enhance immersion and provide clear visual and audio cues for important events

## Source Files

**Base Class:** [FXList](../../GeneralsMD/Code/GameEngine/Include/GameClient/FXList.h)
- Header: [`GeneralsMD/Code/GameEngine/Include/GameClient/FXList.h`](../../GeneralsMD/Code/GameEngine/Include/GameClient/FXList.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameClient/FXList.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameClient/FXList.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet
