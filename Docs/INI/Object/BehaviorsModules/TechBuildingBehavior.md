# TechBuildingBehavior

Update module that provides technology building functionality for structures that provide research or technology benefits.

## Overview

TechBuildingBehavior is an update module that provides technology building functionality for structures that provide research or technology benefits. It manages research capabilities, technology unlocks, and special technology-based abilities for technology buildings. The module handles technology progression and provides integration with the research and upgrade systems.

TechBuildingBehavior must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by technology buildings to provide research capabilities, technology unlocks, or special technology-based abilities. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Designed specifically for technology buildings
- Requires proper research and technology systems for functionality
- Cannot function without proper update and death systems
- Technology benefits are limited by research system integration

**Conditions**:
- Multiple instances behavior: Multiple TechBuildingBehavior modules can exist independently, each managing different technology systems
- Always active once assigned to an object
- Continuously manages technology building operations and research capabilities
- Creates research and technology advancement capabilities

**Dependencies**:
- Depends on the research system for technology progression
- Requires proper update and death systems for functionality
- Inherits functionality from UpdateModule and DieModuleInterface

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

TechBuildingBehavior does not expose any additional INI-parsable properties beyond those inherited from UpdateModule. The module handles technology building operations through internal logic and research system integration.

## Examples

### Basic Tech Building Behavior
```ini
Behavior = TechBuildingBehavior ModuleTag_09
  ; No additional properties required
End
```

### Enhanced Tech Building Behavior
```ini
Behavior = TechBuildingBehavior ModuleTag_10
  ; Technology building operations handled internally
End
```

### Advanced Tech Building Behavior
```ini
Behavior = TechBuildingBehavior ModuleTag_12
  ; Research capabilities handled internally
End
```

## Template

```ini
Behavior = TechBuildingBehavior ModuleTag_XX
  ; No additional properties - all functionality handled internally
End
```

## Notes

- TechBuildingBehavior provides research and technology advancement capabilities for technology buildings
- The module handles technology building operations and research system integration
- Technology buildings enable research capabilities and technology unlocks
- This creates proper technology progression mechanics for strategic gameplay

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h), [`DieModuleInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/TechBuildingBehavior.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/TechBuildingBehavior.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/TechBuildingBehavior.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/TechBuildingBehavior.cpp)
