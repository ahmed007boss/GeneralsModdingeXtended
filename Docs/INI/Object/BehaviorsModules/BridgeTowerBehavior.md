# BridgeTowerBehavior

Behavior module that manages individual bridge tower structures and their connections to bridge segments with destruction handling.

## Overview

BridgeTowerBehavior is a behavior module that manages individual bridge tower structures and their connections to bridge segments. It coordinates with bridge systems, manages tower-specific functionality, and handles tower destruction sequences. The module provides the foundation for bridge tower operations and ensures proper integration with the overall bridge system.

BridgeTowerBehavior must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by bridge tower objects to coordinate with bridge segments, manage tower-specific functionality, and handle tower destruction. This is a **behavior module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Designed specifically for bridge tower structures
- Requires proper bridge system integration for functionality
- Cannot function without proper death and behavior systems
- Requires proper bridge segment connections for operations

**Conditions**:
- Multiple instances behavior: Multiple BridgeTowerBehavior modules can exist independently, each managing different bridge tower systems
- Always active once assigned to an object
- Continuously manages tower connections and bridge coordination
- Creates realistic bridge tower operations with proper destruction handling

**Dependencies**:
- Depends on the bridge system for proper tower integration
- Requires proper death system for destruction sequences
- Inherits functionality from BehaviorModule, BridgeTowerBehaviorInterface, and DieModuleInterface

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

BridgeTowerBehavior does not expose any additional INI-parsable properties beyond those inherited from BehaviorModule. The module handles tower operations through internal logic and bridge system integration.

## Examples

### Basic Bridge Tower
```ini
Behavior = BridgeTowerBehavior ModuleTag_03
  ; No additional properties required
End
```

### Bridge Tower with Operations
```ini
Behavior = BridgeTowerBehavior ModuleTag_03
  ; Tower operations handled internally
End
```

### Bridge Tower Destruction
```ini
Behavior = BridgeTowerBehavior ModuleTag_03
  ; Destruction sequences handled internally
End
```

## Template

```ini
Behavior = BridgeTowerBehavior ModuleTag_XX
  ; No additional properties - all functionality handled internally
End
```

## Notes

- BridgeTowerBehavior manages individual bridge tower operations and connections
- The module handles tower-specific functionality and bridge coordination internally
- Tower operations are integrated with the overall bridge system for realistic behavior
- This creates proper bridge tower mechanics with destruction handling

## Source Files

**Base Class:** [`BehaviorModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h), [`BridgeTowerBehaviorInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BridgeTowerBehavior.h), [`DieModuleInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BridgeTowerBehavior.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BridgeTowerBehavior.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeTowerBehavior.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeTowerBehavior.cpp)
