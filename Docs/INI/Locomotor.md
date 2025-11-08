# Locomotor INI Documentation

## Overview

Locomotors control movement capabilities and behavior (ground, air, hover, etc.) for objects. A `locomotor` template defines speeds, accelerations, turning, z-axis behavior, appearance, suspension, friction, and various movement flags. Objects reference locomotors via `Locomotor` blocks on their templates.

## Source Files

- Header: `GeneralsMD/Code/GameEngine/Include/GameLogic/Locomotor.h` – `Locomotor`, enums
- Header: `GeneralsMD/Code/GameEngine/Include/GameLogic/LocomotorSet.h` – surfaces enum and names
- Source: `Generals/Code/GameEngine/Source/GameLogic/Object/Locomotor.cpp` – parse table and behavior

## Usage

- INI: Inside an `Object` template, use `Locomotor = <LocomotorName>` via AI/update parsing. The `LocomotorDefinition` is defined at root:
  - `Locomotor <Name> ... End`
- Surfaces determine pathfinding and terrain capability; appearance sets movement model.

## Properties

### General Settings

#### Surfaces (v1.04)
- Type: Bit flags (LocomotorSurfaceTypeMask)
- Description: Allowed surface categories
- Values: `GROUND WATER CLIFF AIR RUBBLE`

#### Appearance (v1.04)
- Type: LocomotorAppearance
- Description: Movement model used for steering and animation
- Values: `TWO_LEGS FOUR_WHEELS TREADS HOVER THRUST WINGS CLIMBER OTHER MOTORCYCLE`

#### GroupMovementPriority (v1.04)
- Type: LocomotorPriority
- Description: Desired position in group formations
- Values: `MOVES_BACK MOVES_MIDDLE MOVES_FRONT`

### Speed and Turning

#### Speed (v1.04)
- Type: Velocity (dist/sec)
- Description: Maximum forward speed

#### SpeedDamaged (v1.04)
- Type: Velocity
- Description: Max speed when damaged (defaults to Speed if omitted)

#### TurnRate (v1.04)
- Type: Angular velocity (rads/sec)
- Description: Max turn rate

#### TurnRateDamaged (v1.04)
- Type: Angular velocity
- Description: Max turn rate when damaged (defaults to TurnRate)

#### Acceleration (v1.04)
- Type: Acceleration
- Description: Max forward acceleration

#### AccelerationDamaged (v1.04)
- Type: Acceleration
- Description: Max forward acceleration when damaged (defaults to Acceleration)

#### Braking (v1.04)
- Type: Acceleration
- Description: Max deceleration used when stopping

#### MinSpeed (v1.04)
- Type: Velocity
- Description: Minimum allowed movement speed

#### MinTurnSpeed (v1.04)
- Type: Velocity
- Description: Minimum speed at which turning is possible (wheeled)

### Z Axis Behavior

#### ZAxisBehavior (v1.04)
- Type: LocomotorBehaviorZ
- Description: Control of vertical behavior relative to ground/buildings/water
- Values: `NO_Z_MOTIVE_FORCE SEA_LEVEL SURFACE_RELATIVE_HEIGHT ABSOLUTE_HEIGHT FIXED_SURFACE_RELATIVE_HEIGHT FIXED_ABSOLUTE_HEIGHT FIXED_RELATIVE_TO_GROUND_AND_BUILDINGS RELATIVE_TO_HIGHEST_LAYER`

#### PreferredHeight (v1.04)
- Type: Real
- Description: Target altitude or offset depending on Z behavior

#### PreferredHeightDamping (v1.04)
- Type: Real
- Description: Smoothing factor for approaching preferred height (0..1+)

#### SpeedLimitZ (v1.04)
- Type: Velocity
- Description: Vertical speed clamp used by Z handlers

### Flight/Thrust Specific

#### MaxThrustAngle (v1.04)
- Type: Angle (radians)
- Description: Max deflection of thrust vector (THRUST appearance)

#### CirclingRadius (v1.04)
- Type: Real
- Description: Circle radius when maintaining position (wings)

### Friction and Grounding

#### Extra2DFriction (v1.04)
- Type: Real per second (internally converted per frame)
- Description: Additional horizontal friction applied

#### Apply2DFrictionWhenAirborne (v1.04)
- Type: Bool
- Description: Apply 2D friction even when airborne

#### StickToGround (v1.04)
- Type: Bool
- Description: Prevent leaving ground (no airtime)

### Lift

#### Lift (v1.04)
- Type: Acceleration
- Description: Maximum vertical lift capability

#### LiftDamaged (v1.04)
- Type: Acceleration
- Description: Lift when damaged (defaults to Lift)

### Motion Model Tuning

#### AccelerationPitchLimit (v1.04)
- Type: Angle
- Description: Max pitch up under acceleration

#### BounceAmount (v1.04)
- Type: Angular velocity
- Description: Vertical bounce amplitude (rough terrain)

#### PitchStiffness (v1.04)
- Type: Real
- Description: Suspension stiffness in pitch

#### RollStiffness (v1.04)
- Type: Real
- Description: Suspension stiffness in roll

#### PitchDamping (v1.04)
- Type: Real
- Description: Suspension damping in pitch

#### RollDamping (v1.04)
- Type: Real
- Description: Suspension damping in roll

#### ThrustRoll (v1.04)
- Type: Real
- Description: Roll amount due to thrust (aircraft)

#### ThrustWobbleRate (v1.04)
- Type: Real
- Description: Wobble frequency for thrust vehicles

#### ThrustMinWobble (v1.04)
- Type: Real
- Description: Minimum wobble amplitude

#### ThrustMaxWobble (v1.04)
- Type: Real
- Description: Maximum wobble amplitude

#### PitchInDirectionOfZVelFactor (v1.04)
- Type: Real
- Description: Pitch response to vertical speed

#### ForwardVelocityPitchFactor (v1.04)
- Type: Real
- Description: Pitch response to forward speed

#### LateralVelocityRollFactor (v1.04)
- Type: Real
- Description: Roll response to lateral speed

#### ForwardAccelerationPitchFactor (v1.04)
- Type: Real
- Description: Pitch response to forward acceleration

#### LateralAccelerationRollFactor (v1.04)
- Type: Real
- Description: Roll response to lateral acceleration

#### UniformAxialDamping (v1.04)
- Type: Real
- Description: Damping for pitch/roll rate

#### TurnPivotOffset (v1.04)
- Type: Real
- Description: Turning pivot (-1 rear, 0 center, 1 front)

### Flags and Misc

#### LocomotorWorksWhenDead (v1.04)
- Type: Bool
- Description: Keep locomotion active when dead

#### AllowAirborneMotiveForce (v1.04)
- Type: Bool
- Description: Allow motive force while airborne

#### DownhillOnly (v1.04)
- Type: Bool
- Description: Gravity-only motion (no motive force)

#### CanMoveBackwards (v1.04)
- Type: Bool
- Description: Allow backward movement

#### HasSuspension (v1.04)
- Type: Bool
- Description: Enable independent wheel suspension

#### FrontWheelTurnAngle (v1.04)
- Type: Angle
- Description: Max steering angle for front wheels

#### MaximumWheelExtension (v1.04)
- Type: Real
- Description: Max wheel drop distance (negative)

#### MaximumWheelCompression (v1.04)
- Type: Real
- Description: Max wheel compression distance (positive)

#### CloseEnoughDist (v1.04)
- Type: Real
- Description: Distance threshold to consider destination reached

#### CloseEnoughDist3D (v1.04)
- Type: Bool
- Description: Use 3D distance for close-enough test

#### SlideIntoPlaceTime (v1.04)
- Type: Duration
- Description: Factor controlling ultra-accurate slide-in

### Wander Behavior

#### WanderWidthFactor (v1.04)
- Type: Real
- Description: Lateral wandering amplitude factor

#### WanderLengthFactor (v1.04)
- Type: Real
- Description: Longitudinal wandering factor

#### WanderAboutPointRadius (v1.04)
- Type: Real
- Description: Radius around goal point for wandering

## Enum Value Lists

#### LocomotorSurfaceType (v1.04)
- GROUND, WATER, CLIFF, AIR, RUBBLE

#### LocomotorAppearance (v1.04)
- LOCO_LEGS_TWO, LOCO_WHEELS_FOUR, LOCO_TREADS, LOCO_HOVER, LOCO_THRUST, LOCO_WINGS, LOCO_CLIMBER, LOCO_OTHER, LOCO_MOTORCYCLE

#### LocomotorPriority (v1.04)
- LOCO_MOVES_BACK, LOCO_MOVES_MIDDLE, LOCO_MOVES_FRONT

#### LocomotorBehaviorZ (v1.04)
- Z_NO_Z_MOTIVE_FORCE, Z_SEA_LEVEL, Z_SURFACE_RELATIVE_HEIGHT, Z_ABSOLUTE_HEIGHT, Z_FIXED_SURFACE_RELATIVE_HEIGHT, Z_FIXED_ABSOLUTE_HEIGHT, Z_RELATIVE_TO_GROUND_AND_BUILDINGS, Z_SMOOTH_RELATIVE_TO_HIGHEST_LAYER

## Examples

### Ground Treads
```
Locomotor TankTreads
  Surfaces                  = GROUND RUBBLE
  Appearance                = TREADS
  GroupMovementPriority     = MOVES_MIDDLE
  Speed                     = 40
  SpeedDamaged              = 30
  TurnRate                  = 2.0
  TurnRateDamaged           = 1.5
  Acceleration              = 20
  AccelerationDamaged       = 15
  Braking                   = 30
  MinSpeed                  = 0
  MinTurnSpeed              = 5
  ZAxisBehavior             = NO_Z_MOTIVE_FORCE
  Extra2DFriction           = 0.2
  StickToGround             = Yes
  HasSuspension             = Yes
  PitchStiffness            = 0.2
  RollStiffness             = 0.2
  PitchDamping              = 0.9
  RollDamping               = 0.9
  CloseEnoughDist           = 1.0
End
```

### Helicopter Hover
```
Locomotor HelicopterHover
  Surfaces                  = AIR
  Appearance                = HOVER
  Speed                     = 80
  TurnRate                  = 2.5
  Acceleration              = 30
  Lift                      = 20
  PreferredHeight           = 60
  PreferredHeightDamping    = 0.5
  SpeedLimitZ               = 15
  Apply2DFrictionWhenAirborne = Yes
  AllowAirborneMotiveForce  = Yes
  ZAxisBehavior             = SURFACE_RELATIVE_HEIGHT
  ThrustWobbleRate          = 0.2
  ThrustMinWobble           = 0.0
  ThrustMaxWobble           = 0.4
End
```

## Notes

- THRUST appearance disallows ZAxisBehavior/lift and requires non-zero speeds; the parser enforces constraints.
- Damaged variants default to undamaged values when omitted.
- `Extra2DFriction` is specified per second; engine converts to per-frame.

## Template

```
Locomotor <Name>
  Surfaces                      = GROUND WATER CLIFF AIR RUBBLE   ; allowed surfaces
  Appearance                    = TREADS                          ; movement model
  GroupMovementPriority         = MOVES_MIDDLE                    ; formation preference

  Speed                         = 40                              ; max speed
  SpeedDamaged                  = 30                              ; damaged max speed
  TurnRate                      = 2.0                             ; max turn rate
  TurnRateDamaged               = 1.5                             ; damaged turn rate
  Acceleration                  = 20                              ; accel
  AccelerationDamaged           = 15                              ; damaged accel
  Braking                       = 30                              ; decel
  MinSpeed                      = 0                               ; min movement speed
  MinTurnSpeed                  = 5                               ; min speed to turn (wheels)

  PreferredHeight               = 0                               ; target altitude/offset
  PreferredHeightDamping        = 1.0                             ; smoothing factor
  CirclingRadius                = 0                               ; wings maintain radius
  Extra2DFriction               = 0.2                             ; friction per sec
  SpeedLimitZ                   = 999999                          ; vertical speed cap
  MaxThrustAngle                = 0                               ; thrust deflection (THRUST)
  ZAxisBehavior                 = NO_Z_MOTIVE_FORCE               ; vertical behavior

  AccelerationPitchLimit        = 0                               ; max pitch on accel
  BounceAmount                  = 0                               ; terrain bounce
  PitchStiffness                = 0.1                             ; suspension stiffness
  RollStiffness                 = 0.1
  PitchDamping                  = 0.9
  RollDamping                   = 0.9
  ThrustRoll                    = 0.0                             ; thrust roll
  ThrustWobbleRate              = 0.0                             ; wobble rate
  ThrustMinWobble               = 0.0
  ThrustMaxWobble               = 0.0
  PitchInDirectionOfZVelFactor  = 0                               ; pitch from z-vel
  ForwardVelocityPitchFactor    = 0                               ; pitch from fwd vel
  LateralVelocityRollFactor     = 0                               ; roll from lat vel
  ForwardAccelerationPitchFactor= 0                               ; pitch from accel
  LateralAccelerationRollFactor = 0                               ; roll from accel
  UniformAxialDamping           = 1.0                             ; rate damping
  TurnPivotOffset               = 0                               ; -1 rear, 0 center, 1 front

  LocomotorWorksWhenDead        = No
  AllowAirborneMotiveForce      = No
  Apply2DFrictionWhenAirborne   = No
  DownhillOnly                  = No
  StickToGround                 = No
  CanMoveBackwards              = No
  HasSuspension                 = No
  FrontWheelTurnAngle           = 0                               ; front wheel steer angle
  MaximumWheelExtension         = 0                               ; wheel drop (neg)
  MaximumWheelCompression       = 0                               ; wheel compress (pos)
  CloseEnoughDist               = 1.0                             ; arrival tolerance
  CloseEnoughDist3D             = No                              ; 3D arrival checks
  SlideIntoPlaceTime            = 0                               ; ultra-accurate slide factor

  WanderWidthFactor             = 0.0                             ; wander sideways
  WanderLengthFactor            = 1.0                             ; wander forward
  WanderAboutPointRadius        = 0.0                             ; wander radius
End
```

