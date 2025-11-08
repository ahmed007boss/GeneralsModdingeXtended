# SupplyWarehouseCripplingBehavior

Update module that provides crippling functionality for supply warehouses when they are damaged or destroyed with reduced functionality.

## Overview

SupplyWarehouseCripplingBehavior is an update module that provides crippling functionality for supply warehouses when they are damaged or destroyed. It manages reduced functionality and crippling effects for supply warehouse structures, allowing them to operate at reduced capacity when damaged. The module handles damage-based functionality reduction and provides visual feedback for crippled states.

SupplyWarehouseCripplingBehavior must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by supply warehouse structures to handle crippling effects and reduced functionality when damaged. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Designed specifically for supply warehouse structures
- Requires proper damage and update systems for functionality
- Cannot function without proper damage system integration
- Crippling effects are limited by damage thresholds

**Conditions**:
- Multiple instances behavior: Multiple SupplyWarehouseCripplingBehavior modules can exist independently, each managing different crippling systems
- Always active once assigned to an object
- Continuously monitors damage levels and applies crippling effects
- Creates realistic damage-based functionality reduction

**Dependencies**:
- Depends on the damage system for crippling trigger detection
- Requires proper update system for continuous monitoring
- Inherits functionality from UpdateModule and DamageModuleInterface

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

SupplyWarehouseCripplingBehavior does not expose any additional INI-parsable properties beyond those inherited from UpdateModule. The module handles crippling operations through internal logic and damage system integration.

## Examples

### Basic Supply Warehouse Crippling
```ini
Behavior = SupplyWarehouseCripplingBehavior ModuleTag_01
  ; No additional properties required
End
```

### Enhanced Supply Warehouse Crippling
```ini
Behavior = SupplyWarehouseCripplingBehavior ModuleTag_02
  ; Crippling operations handled internally
End
```

### Advanced Supply Warehouse Crippling
```ini
Behavior = SupplyWarehouseCripplingBehavior ModuleTag_03
  ; Damage-based functionality reduction handled internally
End
```

## Template

```ini
Behavior = SupplyWarehouseCripplingBehavior ModuleTag_XX
  ; No additional properties - all functionality handled internally
End
```

## Notes

- SupplyWarehouseCripplingBehavior provides realistic damage-based functionality reduction for supply warehouses
- The module handles crippling effects and reduced capacity when structures are damaged
- Crippling effects provide visual and functional feedback for damaged supply warehouses
- This creates realistic damage mechanics for supply warehouse structures

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h), [`DamageModuleInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DamageModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyWarehouseCripplingBehavior.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyWarehouseCripplingBehavior.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/SupplyWarehouseCripplingBehavior.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/SupplyWarehouseCripplingBehavior.cpp)
