# BridgeScaffoldBehavior

Update module that manages bridge scaffold structures during construction and destruction phases with configurable movement and timing.

## Overview

BridgeScaffoldBehavior is an update module that manages bridge scaffold structures during construction and destruction phases. It controls construction progress, movement animations, and destruction sequences for bridge scaffolding. The module provides configurable speeds for different operations and supports timed destruction sequences.

BridgeScaffoldBehavior must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by bridge scaffold objects to control construction progress, movement animations, and destruction sequences. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Designed specifically for bridge scaffold structures
- Requires proper bridge system integration for functionality
- Cannot function without proper update and damage systems
- Requires proper timing configuration for sequences

**Conditions**:
- Multiple instances behavior: Multiple BridgeScaffoldBehavior modules can exist independently, each managing different scaffold systems
- Always active once assigned to an object
- Continuously manages scaffold construction and destruction operations
- Creates realistic bridge construction and destruction sequences

**Dependencies**:
- Depends on the bridge system for proper scaffold integration
- Requires proper update and damage systems for functionality
- Inherits functionality from UpdateModule and BridgeScaffoldBehaviorInterface

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

BridgeScaffoldBehavior does not expose any additional INI-parsable properties beyond those inherited from UpdateModule. The module handles scaffold operations through internal logic and timing systems.

## Examples

### Basic Bridge Scaffold
```ini
Behavior = BridgeScaffoldBehavior ModuleTag_02
  ; No additional properties required
End
```

### Bridge Scaffold with Construction
```ini
Behavior = BridgeScaffoldBehavior ModuleTag_02
  ; Construction and movement handled internally
End
```

### Bridge Scaffold Destruction
```ini
Behavior = BridgeScaffoldBehavior ModuleTag_02
  ; Destruction sequences handled internally
End
```

## Template

```ini
Behavior = BridgeScaffoldBehavior ModuleTag_XX
  ; No additional properties - all functionality handled internally
End
```

## Notes

- BridgeScaffoldBehavior manages bridge scaffold operations during construction and destruction phases
- The module handles construction progress, movement animations, and destruction sequences internally
- Scaffold operations are coordinated with the overall bridge system for realistic construction sequences
- This creates proper bridge construction and destruction mechanics with scaffold support

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h), [`BridgeScaffoldBehaviorInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BridgeScaffoldBehavior.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BridgeScaffoldBehavior.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BridgeScaffoldBehavior.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeScaffoldBehavior.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeScaffoldBehavior.cpp)
