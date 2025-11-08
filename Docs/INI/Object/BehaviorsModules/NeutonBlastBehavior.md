# NeutonBlastBehavior

Update module that provides neutron blast functionality for objects that can create area-of-effect neutron radiation effects.

## Overview

NeutonBlastBehavior is an update module that provides neutron blast functionality for objects that can create area-of-effect neutron radiation effects. It handles neutron blast creation, radiation effects, and area-of-effect damage. The module is designed for neutron weapons, neutron generators, and other objects that can create devastating neutron radiation effects.

NeutonBlastBehavior must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that can create neutron blast effects, such as neutron weapons or special neutron generators. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Designed for neutron blast and radiation effects
- Requires proper damage and update systems for functionality
- Cannot function without proper death and update systems
- Requires proper neutron blast configuration for effects

**Conditions**:
- Multiple instances behavior: Multiple NeutonBlastBehavior modules can exist independently, each creating different neutron blast systems
- Always active once assigned to an object
- Continuously manages neutron blast creation and radiation effects
- Creates devastating neutron radiation capabilities with area-of-effect damage

**Dependencies**:
- Depends on the death system for blast triggering
- Requires proper damage system for radiation effects
- Inherits functionality from UpdateModule and DieModuleInterface

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

NeutonBlastBehavior does not expose any additional INI-parsable properties beyond those inherited from UpdateModule. The module handles neutron blast operations through internal logic and timing systems.

## Examples

### Basic Neutron Blast
```ini
Behavior = NeutonBlastBehavior ModuleTag_01
  ; No additional properties required
End
```

### Neutron Weapon Blast
```ini
Behavior = NeutonBlastBehavior ModuleTag_02
  ; Neutron blast operations handled internally
End
```

### Neutron Generator Blast
```ini
Behavior = NeutonBlastBehavior ModuleTag_03
  ; Radiation effects handled internally
End
```

## Template

```ini
Behavior = NeutonBlastBehavior ModuleTag_XX
  ; No additional properties - all functionality handled internally
End
```

## Notes

- NeutonBlastBehavior provides devastating neutron radiation capabilities with area-of-effect damage
- The module handles neutron blast creation and radiation effects internally
- Neutron blast operations are triggered by death events and create powerful radiation effects
- This creates realistic neutron weapon behavior with proper radiation mechanics

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h), [`DieModuleInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/NeutonBlastBehavior.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/NeutonBlastBehavior.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/NeutonBlastBehavior.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/NeutonBlastBehavior.cpp)
