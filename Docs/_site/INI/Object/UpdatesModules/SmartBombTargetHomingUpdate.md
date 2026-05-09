# SmartBombTargetHomingUpdate

SmartBombTargetHomingUpdate provides smart bomb target homing functionality for objects that can create smart bomb effects.

## Overview

The `SmartBombTargetHomingUpdate` class manages smart bomb target homing and guidance systems for objects that can create smart bombs with target acquisition capabilities. It handles course correction, target tracking, and homing behavior for smart bomb projectiles. This update is commonly used by smart bomb weapons, guided missiles, and projectiles with homing capabilities.

## Usage

Used by objects that can create smart bombs with target homing capabilities and guidance systems. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Smart bomb homing is limited by course correction scalar parameters
- Target acquisition depends on proper target detection and tracking
- Homing behavior is controlled by course correction calculations
- Guidance effectiveness varies based on target movement and evasion

**Conditions**:
- SmartBombTargetHomingUpdate manages smart bomb homing and target tracking
- The update handles course correction calculations for homing behavior
- Target homing provides intelligent guidance for smart bomb projectiles
- Course correction scalar controls homing responsiveness and accuracy
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own homing parameters

**Dependencies**:
- Uses targeting system for target acquisition and tracking
- Integrates with projectile system for homing behavior
- Uses guidance system for course correction calculations

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Homing Settings](#homing-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Homing Settings

#### `CourseCorrectionScalar` *(v1.04)*
- **Type**: `Real`
- **Description**: Scalar value controlling course correction behavior. Higher values (closer to 1.0) create less aggressive homing. Lower values (closer to 0.0) create more aggressive homing. 1.0 = no homing, 0.0 = snap to target, 0.99 = smooth homing
- **Default**: `0.0`
- **Example**: `CourseCorrectionScalar = 0.99`

## Examples

### Basic Smart Bomb
```ini
Behavior = SmartBombTargetHomingUpdate ModuleTag_11
  CourseCorrectionScalar = 0.99 ; 1=no homing, 0=snapto; 0.99=smooth, 0.95=too-fast
End
```

### Aggressive Smart Bomb
```ini
Behavior = SmartBombTargetHomingUpdate ModuleTag_11
  CourseCorrectionScalar = 0.95 ; 1=no homing, 0=snapto; 0.99=smooth, 0.95=too-fast
End
```

### Smooth Smart Bomb
```ini
Behavior = SmartBombTargetHomingUpdate ModuleTag_11
  CourseCorrectionScalar = 0.99 ; 1=no homing, 0=snapto; 0.99=smooth, 0.95=too-fast
End
```

## Template

```ini
Behavior = SmartBombTargetHomingUpdate ModuleTag_XX
  ; Homing Settings
  CourseCorrectionScalar = 0.0            ; // course correction scalar for homing behavior *(v1.04)*
End
```

## Notes

- SmartBombTargetHomingUpdate provides intelligent target homing and guidance for smart bomb projectiles
- The update manages course correction calculations for realistic homing behavior
- Course correction scalar controls the balance between homing accuracy and smoothness
- Target homing creates intelligent guidance systems for smart bomb weapons
- This update is commonly used by smart bomb weapons, guided missiles, and homing projectiles
- Homing behavior provides tactical advantages for precision targeting and engagement

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SmartBombTargetHomingUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SmartBombTargetHomingUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/SmartBombTargetHomingUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/SmartBombTargetHomingUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet