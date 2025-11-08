# AssaultTransportAIUpdate

AI update module that provides AI functionality for assault transport vehicles with specialized transport and combat behaviors.

## Overview

AssaultTransportAIUpdate is an AI update module that provides AI functionality for assault transport vehicles. It handles AI-driven movement, combat decisions, and transport operations for assault transport vehicles. The module provides specialized AI behaviors for vehicles that can transport units while engaging in combat operations.

AssaultTransportAIUpdate must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by assault transport vehicles to handle AI-driven movement, combat, and transport operations. This is an **AI update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Designed specifically for assault transport vehicles
- Requires proper AI and transport systems for functionality
- Cannot function without proper update and AI systems
- Transport operations are limited by vehicle capacity

**Conditions**:
- Multiple instances behavior: Multiple AssaultTransportAIUpdate modules can exist independently, each managing different assault transport systems
- Always active once assigned to an object
- Continuously manages AI-driven transport and combat operations
- Creates specialized AI behaviors for assault transport vehicles

**Dependencies**:
- Depends on the AI system for decision-making
- Requires proper transport system for unit transport operations
- Inherits functionality from AIUpdateInterface and AssaultTransportAIInterface

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

AssaultTransportAIUpdate does not expose any additional INI-parsable properties beyond those inherited from AIUpdateInterface. The module handles assault transport AI operations through internal logic and AI system integration.

## Examples

### Basic Assault Transport AI
```ini
Behavior = AssaultTransportAIUpdate ModuleTag_01
  ; No additional properties required
End
```

### Enhanced Assault Transport AI
```ini
Behavior = AssaultTransportAIUpdate ModuleTag_02
  ; Assault transport AI operations handled internally
End
```

### Advanced Assault Transport AI
```ini
Behavior = AssaultTransportAIUpdate ModuleTag_03
  ; Transport and combat AI handled internally
End
```

## Template

```ini
Behavior = AssaultTransportAIUpdate ModuleTag_XX
  ; No additional properties - all functionality handled internally
End
```

## Notes

- AssaultTransportAIUpdate provides specialized AI behaviors for assault transport vehicles
- The module handles AI-driven transport and combat operations
- Assault transport AI combines transport capabilities with combat decision-making
- This creates realistic AI behaviors for vehicles that can transport units while engaging in combat

## Source Files

**Base Class:** [`AIUpdateInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h), [`AssaultTransportAIInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AssaultTransportAIUpdate.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AssaultTransportAIUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AssaultTransportAIUpdate.cpp)
