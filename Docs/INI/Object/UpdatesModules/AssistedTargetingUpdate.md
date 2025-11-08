# AssistedTargetingUpdate

Update module that provides assisted targeting functionality for objects with enhanced targeting systems and improved accuracy.

## Overview

AssistedTargetingUpdate is an update module that provides assisted targeting functionality for objects with enhanced targeting systems. It improves target acquisition accuracy and provides assistance for targeting operations. The module helps objects acquire and track targets more effectively, providing enhanced targeting capabilities for improved combat performance.

AssistedTargetingUpdate must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that need assisted targeting capabilities for improved accuracy and target acquisition. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Requires proper targeting system integration for functionality
- Cannot function without proper update and targeting systems
- Assisted targeting is limited to objects with targeting capabilities
- Requires proper weapon system integration for targeting assistance

**Conditions**:
- Multiple instances behavior: Multiple AssistedTargetingUpdate modules can exist independently, each managing different assisted targeting systems
- Always active once assigned to an object
- Continuously manages assisted targeting and target acquisition
- Creates enhanced targeting capabilities for improved combat performance

**Dependencies**:
- Depends on the targeting system for target acquisition
- Requires proper update system for continuous management
- Inherits all functionality from UpdateModule

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

AssistedTargetingUpdate does not expose any additional INI-parsable properties beyond those inherited from UpdateModule. The module handles assisted targeting operations through internal logic and targeting system integration.

## Examples

### Basic Assisted Targeting
```ini
Behavior = AssistedTargetingUpdate ModuleTag_01
  ; No additional properties required
End
```

### Enhanced Assisted Targeting
```ini
Behavior = AssistedTargetingUpdate ModuleTag_02
  ; Assisted targeting operations handled internally
End
```

### Advanced Assisted Targeting
```ini
Behavior = AssistedTargetingUpdate ModuleTag_03
  ; Enhanced target acquisition handled internally
End
```

## Template

```ini
Behavior = AssistedTargetingUpdate ModuleTag_XX
  ; No additional properties - all functionality handled internally
End
```

## Notes

- AssistedTargetingUpdate provides enhanced targeting capabilities for improved combat performance
- The module handles assisted targeting and target acquisition operations
- Enhanced targeting improves accuracy and target acquisition speed
- This creates realistic assisted targeting mechanics for advanced weapon systems

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/AssistedTargetingUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/AssistedTargetingUpdate.cpp)
