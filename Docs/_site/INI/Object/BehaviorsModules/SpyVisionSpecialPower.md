# SpyVisionSpecialPower

Special power module that provides spy vision functionality for enhanced visibility and reconnaissance capabilities.

## Overview

SpyVisionSpecialPower is a special power module that provides spy vision functionality for enhanced visibility and reconnaissance capabilities. It enables objects to provide spy vision or enhanced visibility as special powers, allowing players to gain tactical advantages through improved reconnaissance and intelligence gathering.

SpyVisionSpecialPower must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that can provide spy vision or enhanced visibility as special powers. This is a **special power module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Requires proper special power system integration for functionality
- Cannot function without proper special power and vision systems
- Spy vision effects are limited by special power activation
- Requires proper vision system for enhanced visibility

**Conditions**:
- Multiple instances behavior: Multiple SpyVisionSpecialPower modules can exist independently, each providing different spy vision capabilities
- Always active once assigned to an object
- Triggers when special power is activated
- Creates enhanced reconnaissance and intelligence gathering capabilities

**Dependencies**:
- Depends on the special power system for activation
- Requires proper vision system for enhanced visibility effects
- Inherits all functionality from SpecialPowerModule

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

SpyVisionSpecialPower does not expose any additional INI-parsable properties beyond those inherited from SpecialPowerModule. The module handles spy vision operations through internal logic and special power system integration.

## Examples

### Basic Spy Vision Special Power
```ini
Behavior = SpyVisionSpecialPower ModuleTag_01
  ; No additional properties required
End
```

### Enhanced Spy Vision Special Power
```ini
Behavior = SpyVisionSpecialPower ModuleTag_02
  ; Spy vision operations handled internally
End
```

### Advanced Spy Vision Special Power
```ini
Behavior = SpyVisionSpecialPower ModuleTag_03
  ; Enhanced visibility handled internally
End
```

## Template

```ini
Behavior = SpyVisionSpecialPower ModuleTag_XX
  ; No additional properties - all functionality handled internally
End
```

## Notes

- SpyVisionSpecialPower provides enhanced reconnaissance and intelligence gathering capabilities
- The module handles spy vision operations through special power activation
- Spy vision effects provide tactical advantages through improved visibility
- This creates powerful reconnaissance capabilities for strategic gameplay

## Source Files

**Base Class:** [`SpecialPowerModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/SpecialPower/SpyVisionSpecialPower.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/SpecialPower/SpyVisionSpecialPower.cpp)
