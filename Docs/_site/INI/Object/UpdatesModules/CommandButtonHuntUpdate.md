# CommandButtonHuntUpdate

Update module that provides command button hunt functionality for objects that can hunt targets based on command button actions and player commands.

## Overview

CommandButtonHuntUpdate is an update module that provides command button hunt functionality for objects that can hunt targets based on command button actions. It enables units to use command button hunt scripts and respond to player commands for target hunting operations. The module integrates with the command system to provide responsive hunt behaviors.

CommandButtonHuntUpdate must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that need to hunt targets when specific command buttons are activated or pressed. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Requires proper command system integration for functionality
- Cannot function without proper update and command systems
- Hunt operations are limited by command button availability
- Requires proper target acquisition system integration

**Conditions**:
- Multiple instances behavior: Multiple CommandButtonHuntUpdate modules can exist independently, each managing different hunt systems
- Always active once assigned to an object
- Responds to command button activations for hunt operations
- Creates command-driven target hunting capabilities

**Dependencies**:
- Depends on the command system for button activation
- Requires proper update system for hunt behavior management
- Inherits all functionality from UpdateModule

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

CommandButtonHuntUpdate does not expose any additional INI-parsable properties beyond those inherited from UpdateModule. The module handles command button hunt operations through internal logic and command system integration.

## Examples

### Basic Command Button Hunt
```ini
Behavior = CommandButtonHuntUpdate ModuleTag_11
  ; Allows use of command button hunt script with this unit
End
```

### Alternative Command Button Hunt
```ini
Behavior = CommandButtonHuntUpdate ModuleTag_02
  ; Command button hunt operations handled internally
End
```

### Advanced Command Button Hunt
```ini
Behavior = CommandButtonHuntUpdate ModuleTag_12
  ; Allows use of command button hunt script with this unit
End
```

## Template

```ini
Behavior = CommandButtonHuntUpdate ModuleTag_XX
  ; No additional properties - all functionality handled internally
End
```

## Notes

- CommandButtonHuntUpdate enables command-driven target hunting capabilities
- The module integrates with the command system for responsive hunt behaviors
- Command button hunt scripts provide flexible target acquisition mechanics
- This creates intuitive player control over unit hunting behaviors

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/CommandButtonHuntUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/CommandButtonHuntUpdate.cpp)
