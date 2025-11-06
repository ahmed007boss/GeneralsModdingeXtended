# PoisonedBehavior

Update module that manages poison damage effects, including continuous damage over time and poison duration tracking.

## Overview

PoisonedBehavior is an update module that handles poison damage effects on objects. When an object receives poison damage, this module activates and begins applying continuous damage over time at specified intervals. The poison effect continues for a configurable duration after the last poison dose, creating a persistent damage-over-time effect that can be countered by healing.

PoisonedBehavior must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that should suffer from poison damage effects with continuous damage over time and poison duration tracking. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Only responds to poison damage types
- Cannot function without proper damage and healing systems
- Poison effects are stopped by healing
- Requires poison damage types to function properly

**Conditions**:
- Multiple instances behavior: Multiple PoisonedBehavior modules can exist independently, each managing different poison effects
- Always active once assigned to an object
- Activates when poison damage is received and continues until healed
- Creates tactical poison effects that require healing to counter

**Dependencies**:
- Requires poison damage types to function
- Depends on the damage and healing systems
- Inherits functionality from UpdateModule and DamageModuleInterface

## Properties

### Poison Configuration

#### `PoisonDamageInterval` *(v1.04)*
- **Type**: `UnsignedInt` (frames)
- **Description**: Interval in frames between poison damage applications. Higher values apply poison damage less frequently. When set to 0 (default), no poison damage interval is used
- **Default**: `0`
- **Example**: `PoisonDamageInterval = 60`

#### `PoisonDuration` *(v1.04)*
- **Type**: `UnsignedInt` (frames)
- **Description**: Duration in frames that poison effects last after the last poison dose. Higher values make poison effects last longer. When set to 0 (default), no poison duration is applied
- **Default**: `0`
- **Example**: `PoisonDuration = 300`

## Examples

### Basic Poison Effect
```ini
Update = PoisonedBehavior ModuleTag_01
  PoisonDamageInterval = 30
  PoisonDuration = 180
End
```

### Long-Lasting Poison
```ini
Update = PoisonedBehavior ModuleTag_02
  PoisonDamageInterval = 45
  PoisonDuration = 600
End
```

### Quick Poison Damage
```ini
Update = PoisonedBehavior ModuleTag_03
  PoisonDamageInterval = 15
  PoisonDuration = 120
End
```

## Template

```ini
Update = PoisonedBehavior ModuleTag_XX
  ; Poison Configuration
  PoisonDamageInterval = 0            ; // frames between poison damage applications *(v1.04)*
  PoisonDuration = 0                  ; // frames poison effects last after last dose *(v1.04)*
End
```

## Notes

- PoisonedBehavior manages poison damage effects with continuous damage over time
- Activates when objects receive poison damage and continues until healed
- Includes configurable damage intervals and poison duration
- Commonly used for poison weapons, environmental hazards, and damage-over-time effects
- The module tracks poison damage amounts and applies them at specified intervals
- Creates tactical poison effects that require healing to counter

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/PoisonedBehavior.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/PoisonedBehavior.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/PoisonedBehavior.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/PoisonedBehavior.cpp)