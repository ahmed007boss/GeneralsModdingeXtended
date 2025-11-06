# PreorderCreate

Create module that sets preorder status on buildings when they are completed, based on the player's preorder status.

## Overview

PreorderCreate is a create module that manages preorder status for buildings when they are completed. It checks if the controlling player has preordered the game and sets the appropriate model condition state accordingly. This creates visual differentiation between preorder and regular versions of buildings, providing special recognition for players who preordered the game.

PreorderCreate must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by buildings that should have different visual appearances based on whether the player preordered the game. This is a **create module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Only affects buildings with model condition states
- Cannot function without proper player preorder status tracking
- Only applies visual changes, no gameplay effects
- Requires proper model condition state support

**Conditions**:
- Multiple instances behavior: Multiple PreorderCreate modules can exist independently, each managing different preorder effects
- Always active once assigned to an object
- Triggers during onBuildComplete events
- Creates exclusive visual content for preorder players

**Dependencies**:
- Requires objects with model condition state support
- Depends on player preorder status tracking
- Inherits all functionality from CreateModule

## Properties

This module does not expose any INI-parsable properties.

## Examples

### Basic Preorder Building
```ini
Create = PreorderCreate ModuleTag_01
End
```

### Preorder-Only Building
```ini
Create = PreorderCreate ModuleTag_02
End
```

## Template

```ini
Create = PreorderCreate ModuleTag_XX
  ; No additional properties
End
```

## Notes

- PreorderCreate manages preorder status for buildings when construction completes
- Sets MODELCONDITION_PREORDER state for preorder players
- Provides visual recognition for preorder players
- Commonly used for special buildings and structures
- The module automatically handles preorder status based on player status
- Creates exclusive visual content for preorder players

## Source Files

**Base Class:** [`CreateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/PreorderCreate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/PreorderCreate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Create/PreorderCreate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Create/PreorderCreate.cpp)