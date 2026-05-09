# HelicopterSlowDeathUpdate

HelicopterSlowDeathUpdate provides slow death functionality specifically for helicopter units.

## Overview

The `HelicopterSlowDeathUpdate` class manages extended death sequences specifically designed for helicopter units, featuring crash animations, spiral descent patterns, and realistic helicopter crash physics. It extends SlowDeathBehavior to provide specialized helicopter death mechanics including spiral orbits, self-rotation, and controlled descent patterns that create dramatic and realistic helicopter crash sequences.

## Usage

Used by helicopter units that need extended death sequences with crash animations and effects. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Death sequences are limited by spiral orbit and self-spin parameters
- Crash patterns are controlled by forward speed and damping settings
- Self-rotation is limited by minimum and maximum spin rates
- Update delays control the frequency of physics calculations

**Conditions**:
- HelicopterSlowDeathUpdate creates dramatic spiral descent patterns during death
- The update applies realistic helicopter crash physics with orbital motion
- Self-rotation effects simulate out-of-control helicopter spinning
- Forward speed damping creates realistic deceleration during crashes
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own crash patterns

**Dependencies**:
- Extends SlowDeathBehavior for base death functionality
- Uses physics system for spiral orbit and rotation calculations
- Integrates with animation system for crash sequences

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Spiral Orbit Settings](#spiral-orbit-settings)
  - [Self-Rotation Settings](#self-rotation-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Spiral Orbit Settings

#### `SpiralOrbitTurnRate` *(v1.04)*
- **Type**: `Real` (angular velocity)
- **Description**: Rate of turning during spiral orbit descent. Higher values create tighter spiral patterns. Lower values create wider, more gradual spiral descents
- **Default**: `0.0`
- **Example**: `SpiralOrbitTurnRate = 90.0`

#### `SpiralOrbitForwardSpeed` *(v1.04)*
- **Type**: `Real` (velocity)
- **Description**: Forward speed during spiral orbit descent. Higher values create faster spiral descents. Lower values create slower, more controlled descents
- **Default**: `0.0`
- **Example**: `SpiralOrbitForwardSpeed = 10.0`

#### `SpiralOrbitForwardSpeedDamping` *(v1.04)*
- **Type**: `Real`
- **Description**: Rate of forward speed reduction during descent. Higher values cause faster deceleration. Lower values maintain speed longer during descent
- **Default**: `0.0`
- **Example**: `SpiralOrbitForwardSpeedDamping = 0.1`

### Self-Rotation Settings

#### `MinSelfSpin` *(v1.04)*
- **Type**: `Real` (angular velocity)
- **Description**: Minimum self-rotation speed for helicopter spinning. Higher values ensure faster minimum spinning. Lower values allow slower spinning
- **Default**: `0.0`
- **Example**: `MinSelfSpin = 180.0`

#### `MaxSelfSpin` *(v1.04)*
- **Type**: `Real` (angular velocity)
- **Description**: Maximum self-rotation speed for helicopter spinning. Higher values allow faster maximum spinning. Lower values limit maximum spinning speed
- **Default**: `0.0`
- **Example**: `MaxSelfSpin = 360.0`

#### `SelfSpinUpdateDelay` *(v1.04)*
- **Type**: `Real` (milliseconds)
- **Description**: Time delay between self-spin updates. Higher values create less frequent spin changes. Lower values create more frequent spin variations
- **Default**: `0.0`
- **Example**: `SelfSpinUpdateDelay = 100.0`

#### `SelfSpinUpdateAmount` *(v1.04)*
- **Type**: `Real` (angle)
- **Description**: Amount of spin change per update cycle. Higher values create more dramatic spin changes. Lower values create more gradual spin variations
- **Default**: `0.0`
- **Example**: `SelfSpinUpdateAmount = 5.0`

## Examples

### Basic Helicopter Crash
```ini
Behavior = HelicopterSlowDeathUpdate ModuleTag_01
  SpiralOrbitTurnRate = 45.0
  SpiralOrbitForwardSpeed = 5.0
  SpiralOrbitForwardSpeedDamping = 0.05
  MinSelfSpin = 90.0
  MaxSelfSpin = 270.0
End
```

### Dramatic Helicopter Crash
```ini
Behavior = HelicopterSlowDeathUpdate ModuleTag_02
  SpiralOrbitTurnRate = 90.0
  SpiralOrbitForwardSpeed = 15.0
  SpiralOrbitForwardSpeedDamping = 0.1
  MinSelfSpin = 180.0
  MaxSelfSpin = 540.0
  SelfSpinUpdateDelay = 50.0
  SelfSpinUpdateAmount = 10.0
End
```

## Template

```ini
Behavior = HelicopterSlowDeathUpdate ModuleTag_XX
  ; Spiral Orbit Settings
  SpiralOrbitTurnRate = 0.0              ; // spiral turn rate during descent *(v1.04)*
  SpiralOrbitForwardSpeed = 0.0          ; // forward speed during spiral descent *(v1.04)*
  SpiralOrbitForwardSpeedDamping = 0.0   ; // speed reduction rate *(v1.04)*
  
  ; Self-Rotation Settings
  MinSelfSpin = 0.0                      ; // minimum self-rotation speed *(v1.04)*
  MaxSelfSpin = 0.0                      ; // maximum self-rotation speed *(v1.04)*
  SelfSpinUpdateDelay = 0.0              ; // delay between spin updates *(v1.04)*
  SelfSpinUpdateAmount = 0.0             ; // spin change amount per update *(v1.04)*
End
```

## Notes

- HelicopterSlowDeathUpdate extends SlowDeathBehavior with helicopter-specific crash mechanics
- The update creates realistic spiral descent patterns that simulate out-of-control helicopter crashes
- Self-rotation effects add dramatic spinning motion to enhance crash realism
- Forward speed damping creates gradual deceleration for realistic crash physics
- This update is commonly used by helicopter units for cinematic death sequences
- Spiral orbit parameters control the overall crash trajectory and descent pattern

## Source Files

**Base Class:** [`SlowDeathBehavior`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SlowDeathBehavior.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/HelicopterSlowDeathUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/HelicopterSlowDeathUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/HelicopterSlowDeathUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/HelicopterSlowDeathUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet