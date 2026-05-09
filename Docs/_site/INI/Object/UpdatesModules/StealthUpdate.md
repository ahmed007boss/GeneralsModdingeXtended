# StealthUpdate

StealthUpdate provides stealth functionality for objects that can become stealthy or invisible.

## Overview

The `StealthUpdate` class manages stealth operations for objects that can enter stealth mode, become invisible, or have stealth-related abilities. It handles stealth delays, movement thresholds, forbidden conditions, opacity settings, and stealth behavior management. This update is commonly used by stealth units, invisible objects, and units with stealth capabilities.

## Usage

Used by objects that can enter stealth mode, become invisible, or have stealth-related abilities. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Stealth operations are limited by stealth delay and movement threshold parameters
- Stealth effectiveness depends on forbidden conditions and status requirements
- Opacity settings control stealth visibility and detection
- Stealth behavior is controlled by stealth conditions and requirements

**Conditions**:
- StealthUpdate manages stealth mode activation, deactivation, and behavior
- The update handles stealth delays, movement thresholds, and forbidden conditions
- Stealth operations provide tactical advantages for concealment and surprise attacks
- Opacity settings control stealth visibility and detection capabilities
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own stealth parameters

**Dependencies**:
- Uses stealth system for stealth mode management
- Integrates with movement system for stealth movement thresholds
- Uses opacity system for stealth visibility control

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Stealth Behavior Settings](#stealth-behavior-settings)
  - [Visibility Settings](#visibility-settings)
  - [Condition Settings](#condition-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Stealth Behavior Settings

#### `StealthDelay` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time delay before stealth mode activates. Higher values create longer delays. Lower values create faster stealth activation
- **Default**: `0`
- **Example**: `StealthDelay = 2000`

#### `MoveThresholdSpeed` *(v1.04)*
- **Type**: `Real` (velocity)
- **Description**: Movement speed threshold for stealth operations. Higher values allow faster movement while stealthed. Lower values require slower movement for stealth
- **Default**: `0.0`
- **Example**: `MoveThresholdSpeed = 10.0`

#### `StealthForbiddenConditions` *(v1.04)*
- **Type**: `BitString32` (bit flags)
- **Description**: Conditions that prevent stealth mode activation. When set, specified conditions prevent stealth. When empty, no conditions prevent stealth
- **Default**: `0`
- **Example**: `StealthForbiddenConditions = FIRING_PRIMARY FIRING_SECONDARY`

### Visibility Settings

#### `FriendlyOpacityMin` *(v1.04)*
- **Type**: `Real` (percentage)
- **Description**: Minimum opacity for friendly units when stealthed. Higher values create more visible stealth. Lower values create more invisible stealth
- **Default**: `0.0`
- **Example**: `FriendlyOpacityMin = 0.5`

#### `FriendlyOpacityMax` *(v1.04)*
- **Type**: `Real` (percentage)
- **Description**: Maximum opacity for friendly units when stealthed. Higher values create more visible stealth. Lower values create more invisible stealth
- **Default**: `0.0`
- **Example**: `FriendlyOpacityMax = 0.8`

#### `PulseFrequency` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Frequency of stealth pulse effects. Higher values create slower pulses. Lower values create faster pulses
- **Default**: `0`
- **Example**: `PulseFrequency = 1000`

### Condition Settings

#### `HintDetectableConditions` *(v1.04)*
- **Type**: `ObjectStatusMaskType` (bit flags)
- **Description**: Conditions that hint at detectability. When set, specified conditions hint at detection. When empty, no hint conditions
- **Default**: `0`
- **Example**: `HintDetectableConditions = MOVING`

#### `RequiredStatus` *(v1.04)*
- **Type**: `ObjectStatusMaskType` (bit flags)
- **Description**: Required status for stealth activation. When set, specified status is required. When empty, no status requirements
- **Default**: `0`
- **Example**: `RequiredStatus = IDLE`

#### `ForbiddenStatus` *(v1.04)*
- **Type**: `ObjectStatusMaskType` (bit flags)
- **Description**: Forbidden status for stealth activation. When set, specified status prevents stealth. When empty, no status restrictions
- **Default**: `0`
- **Example**: `ForbiddenStatus = ATTACKING`

#### `DisguisesAsTeam` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether stealth disguises the unit as team. When true, unit appears as team. When false, unit appears as enemy
- **Default**: `No`
- **Example**: `DisguisesAsTeam = Yes`

#### `RevealDistanceFromTarget` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Distance from target that reveals stealth. Higher values reveal stealth at greater distances. Lower values reveal stealth at closer distances
- **Default**: `0.0`
- **Example**: `RevealDistanceFromTarget = 50.0`

#### `OrderIdleEnemiesToAttackMeUponReveal` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether to order idle enemies to attack upon reveal. When true, orders idle enemies to attack. When false, no orders are given
- **Default**: `No`
- **Example**: `OrderIdleEnemiesToAttackMeUponReveal = Yes`

## Examples

### Basic Stealth Unit
```ini
Behavior = StealthUpdate ModuleTag_GPSStealth01
  StealthDelay                = 2000 ; msec
  StealthForbiddenConditions  = FIRING_PRIMARY FIRING_SECONDARY FIRING_TERTIARY RIDERS_ATTACKING
  InnateStealth               = Yes
End
```

### Movement-Based Stealth
```ini
Behavior = StealthUpdate ModuleStealth_01
  StealthDelay                = 500 ; msec
  StealthForbiddenConditions  = MOVING
  InnateStealth               = No ;Requires upgrade first
End
```

### Advanced Stealth with Conditions
```ini
Behavior = StealthUpdate ModuleStealth_GPSScramblerGenericStealthModule
  StealthDelay                = 2000 ; msec
  InnateStealth               = Yes
  StealthForbiddenConditions  = ATTACKING USING_ABILITY
End
```

## Template

```ini
Behavior = StealthUpdate ModuleTag_XX
  ; Stealth Behavior Settings
  StealthDelay = 0                       ; // time delay before stealth activation *(v1.04)*
  MoveThresholdSpeed = 0.0               ; // movement speed threshold for stealth *(v1.04)*
  StealthForbiddenConditions =           ; // conditions that prevent stealth *(v1.04)*
  
  ; Visibility Settings
  FriendlyOpacityMin = 0.0               ; // minimum opacity for friendly units *(v1.04)*
  FriendlyOpacityMax = 0.0               ; // maximum opacity for friendly units *(v1.04)*
  PulseFrequency = 0                     ; // frequency of stealth pulse effects *(v1.04)*
  
  ; Condition Settings
  HintDetectableConditions =             ; // conditions that hint at detectability *(v1.04)*
  RequiredStatus =                       ; // required status for stealth activation *(v1.04)*
  ForbiddenStatus =                      ; // forbidden status for stealth activation *(v1.04)*
  DisguisesAsTeam = No                   ; // whether stealth disguises as team *(v1.04)*
  RevealDistanceFromTarget = 0.0         ; // distance from target that reveals stealth *(v1.04)*
  OrderIdleEnemiesToAttackMeUponReveal = No ; // whether to order enemies to attack on reveal *(v1.04)*
End
```

## Notes

- StealthUpdate provides comprehensive stealth mode management and behavior control
- The update handles stealth delays, movement thresholds, and forbidden conditions
- Stealth operations provide tactical advantages for concealment and surprise attacks
- Opacity settings control stealth visibility and detection capabilities
- This update is commonly used by stealth units, invisible objects, and units with stealth capabilities
- Stealth behavior creates realistic concealment and detection mechanics for tactical gameplay

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StealthUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StealthUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/StealthUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/StealthUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet