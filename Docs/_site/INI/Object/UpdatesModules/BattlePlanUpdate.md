# BattlePlanUpdate

Special power update module that provides battle plan functionality for objects that can execute complex battle strategies with transition timings and message systems.

## Overview

BattlePlanUpdate is a special power update module that provides battle plan functionality for objects that can execute complex battle strategies. It manages battle plan transitions, animation timings, and message systems for coordinated combat operations. The module supports different battle plan types including bombardment, hold the line, and search and destroy operations.

BattlePlanUpdate must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that need to execute battle plans, coordinate attacks, and manage complex combat strategies. This is a **special power update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Requires valid special power templates for battle plan activation
- Cannot function without proper special power and update systems
- Battle plan execution is limited to special power activation
- Requires proper animation and message system integration

**Conditions**:
- Multiple instances behavior: Multiple BattlePlanUpdate modules can exist independently, each managing different battle plan systems
- Always active once assigned to an object
- Triggers when special power is activated to execute battle plans
- Creates coordinated combat strategies with visual and audio feedback

**Dependencies**:
- Depends on the special power system for battle plan activation
- Requires proper animation system for transition timings
- Inherits all functionality from SpecialPowerUpdateModule

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Special Power Configuration](#special-power-configuration)
  - [Transition Timings](#transition-timings)
  - [Message System](#message-system)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

### Special Power Configuration

#### `SpecialPowerTemplate` *(v1.04)*
- **Type**: `AsciiString` (see [SpecialPower documentation](../../SpecialPower.md))
- **Description**: Name of the special power template that triggers battle plan execution. When the specified special power is activated, battle plans are executed. When empty (default), no special power triggers battle plans
- **Default**: `""` (empty)
- **Example**: `SpecialPowerTemplate = SpecialAbilityChangeBattlePlans`

### Transition Timings

#### `BombardmentPlanAnimationTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Duration of bombardment plan transition animations. Higher values create slower, more dramatic transitions. Lower values create faster transitions. At 7000 (default), bombardment transitions take 7 seconds
- **Default**: `7000`
- **Example**: `BombardmentPlanAnimationTime = 7000`

#### `HoldTheLinePlanAnimationTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Duration of hold the line plan transition animations. Higher values create slower, more dramatic transitions. Lower values create faster transitions. At 7000 (default), hold the line transitions take 7 seconds
- **Default**: `7000`
- **Example**: `HoldTheLinePlanAnimationTime = 7000`

#### `SearchAndDestroyPlanAnimationTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Duration of search and destroy plan transition animations. Higher values create slower, more dramatic transitions. Lower values create faster transitions. At 7000 (default), search and destroy transitions take 7 seconds
- **Default**: `7000`
- **Example**: `SearchAndDestroyPlanAnimationTime = 7000`

#### `TransitionIdleTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Idle time between battle plan transitions. Higher values create longer pauses between plan changes. Lower values create faster plan switching. At 0 (default), no idle time between transitions
- **Default**: `0`
- **Example**: `TransitionIdleTime = 0`

### Message System

#### `BombardmentMessageLabel` *(v1.04)*
- **Type**: `AsciiString` (see [Message documentation](../../Message.md))
- **Description**: Message label displayed when bombardment battle plan is initiated. When set, shows message to players when bombardment begins. When empty (default), no bombardment message is displayed
- **Default**: `""` (empty)
- **Example**: `BombardmentMessageLabel = MESSAGE:BattlePlanBombardmentInitiated`

## Examples

### Basic Battle Plan Update
```ini
Behavior = BattlePlanUpdate ModuleTag_14
  SpecialPowerTemplate = SpecialAbilityChangeBattlePlans
  BombardmentPlanAnimationTime = 7000
  HoldTheLinePlanAnimationTime = 7000
  SearchAndDestroyPlanAnimationTime = 7000
  TransitionIdleTime = 0
  BombardmentMessageLabel = MESSAGE:BattlePlanBombardmentInitiated
End
```

### Fast Battle Plan Update
```ini
Behavior = BattlePlanUpdate ModuleTag_15
  SpecialPowerTemplate = SpecialAbilityChangeBattlePlans
  BombardmentPlanAnimationTime = 3000
  HoldTheLinePlanAnimationTime = 3000
  SearchAndDestroyPlanAnimationTime = 3000
  TransitionIdleTime = 500
  BombardmentMessageLabel = MESSAGE:BattlePlanBombardmentInitiated
End
```

### Slow Battle Plan Update
```ini
Behavior = BattlePlanUpdate ModuleTag_16
  SpecialPowerTemplate = SpecialAbilityChangeBattlePlans
  BombardmentPlanAnimationTime = 10000
  HoldTheLinePlanAnimationTime = 10000
  SearchAndDestroyPlanAnimationTime = 10000
  TransitionIdleTime = 2000
  BombardmentMessageLabel = MESSAGE:BattlePlanBombardmentInitiated
End
```

## Template

```ini
Behavior = BattlePlanUpdate ModuleTag_XX
  ; Special Power Configuration
  SpecialPowerTemplate =                    ; // special power that triggers battle plans *(v1.04)*
  
  ; Transition Timings
  BombardmentPlanAnimationTime = 7000       ; // milliseconds for bombardment transitions *(v1.04)*
  HoldTheLinePlanAnimationTime = 7000       ; // milliseconds for hold the line transitions *(v1.04)*
  SearchAndDestroyPlanAnimationTime = 7000  ; // milliseconds for search and destroy transitions *(v1.04)*
  TransitionIdleTime = 0                    ; // milliseconds idle between transitions *(v1.04)*
  
  ; Message System
  BombardmentMessageLabel =                 ; // message displayed when bombardment begins *(v1.04)*
End
```

## Notes

- BattlePlanUpdate provides coordinated combat strategies with multiple battle plan types
- The module manages battle plan transitions with configurable animation timings
- Message systems provide player feedback during battle plan execution
- This creates realistic command and control capabilities for strategic combat operations

## Source Files

**Base Class:** [`SpecialPowerUpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerUpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/BattlePlanUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/BattlePlanUpdate.cpp)
