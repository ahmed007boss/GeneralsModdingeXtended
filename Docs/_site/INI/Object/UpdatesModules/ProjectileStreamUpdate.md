# ProjectileStreamUpdate

ProjectileStreamUpdate provides projectile stream functionality for objects that can create projectile streams.

## Overview

The `ProjectileStreamUpdate` class manages projectile stream creation and management for objects that can generate continuous streams of projectiles. It handles stream-based projectile systems, rapid-fire weapons, and continuous projectile generation. This update is commonly used by rapid-fire weapons, stream-based projectiles, and weapons that create continuous projectile effects.

## Usage

Used by objects that can create projectile streams, such as rapid-fire weapons or stream-based projectiles. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Projectile stream creation is limited by weapon and projectile system capabilities
- Stream management depends on projectile templates and stream parameters
- Performance impact varies based on stream complexity and projectile count
- Stream effects are limited by graphics system capabilities

**Conditions**:
- ProjectileStreamUpdate manages continuous projectile stream generation
- The update handles stream-based projectile creation and management
- Stream parameters control projectile frequency and characteristics
- Projectile streams create continuous weapon effects
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own stream parameters

**Dependencies**:
- Requires projectile system for stream generation
- Uses weapon system for stream-based weapon functionality
- Integrates with graphics system for stream visualization

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

*Properties documentation will be added when this page is completed from the corresponding C++ source files.*

## Examples

### Example 1
```ini
Behavior = ProjectileStreamUpdate ModuleTag_02
  ;nothing
End
```

### Example 2
```ini
Behavior = ProjectileStreamUpdate ModuleTag_02
  ;nothing
End
```

### Example 3
```ini
Behavior = ProjectileStreamUpdate ModuleTag_02
  ;nothing
End
```

*All examples of ProjectileStreamUpdate were identical with no properties.*

## Template

```ini
Behavior = ProjectileStreamUpdate ModuleTag_XX
  ; Properties will be documented from source files
End
```

## Notes

- ProjectileStreamUpdate provides continuous projectile stream generation capabilities
- The update manages stream-based projectile systems for rapid-fire weapons
- Projectile streams create continuous weapon effects and visual impact
- This update is commonly used by rapid-fire weapons, stream-based projectiles, and continuous fire systems
- Stream management ensures efficient projectile generation and performance

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ProjectileStreamUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ProjectileStreamUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/ProjectileStreamUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/ProjectileStreamUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet