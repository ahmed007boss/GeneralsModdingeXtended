# CreateCrateDie

Die module that creates supply crates when objects die, with various condition checks for crate spawning.

## Overview

CreateCrateDie is a die module that spawns supply crates when objects die, based on various conditions such as creation chance, veterancy level, killer type, and killer science requirements. The module can create different types of crates with different probabilities and conditions. It's commonly used to provide supply drops when units are destroyed, creating tactical resource opportunities.

CreateCrateDie must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that should create supply crates when they die, based on various conditions such as creation chance, veterancy level, killer type, and killer science requirements. This is a **die module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Cannot create crates when killed by allied units
- Requires valid crate templates to function
- Crate creation depends on various condition checks
- May fail to create crates if no suitable spawn location is found
- Allied kills do not generate crates to prevent exploitation

**Conditions**:
- Multiple instances behavior: Multiple CreateCrateDie modules can exist independently, each creating different crate types
- Only activates when the object dies from appropriate damage
- Crate creation is subject to probability and condition checks
- Creates tactical opportunities for resource gathering when destroying enemy units

**Dependencies**:
- Requires valid crate templates in the crate system
- Depends on the partition manager for spawn location finding
- Inherits all functionality from DieModule

## Properties

### Crate Creation

#### `CrateData` *(v1.04)*
- **Type**: `CrateTemplate` (multiple entries)
- **Description**: List of crate templates that can be created when the object dies. Each entry specifies a crate type with associated conditions (creation chance, veterancy requirements, killer type requirements, killer science requirements). When multiple entries exist, the system tests each one in order and creates the first matching crate
- **Default**: `None`
- **Example**: 
```
CrateData = CrateSupplyBox
CrateData = CrateAmmoBox
```

## Examples

### Basic Supply Crate Creation
```ini
Die = CreateCrateDie ModuleTag_01
  CrateData = CrateSupplyBox
End
```

### Veteran Unit Crate Drop
```ini
Die = CreateCrateDie ModuleTag_02
  CrateData = CrateSupplyBox
  CrateData = CrateAmmoBox
  CrateData = CrateExperienceBox
End
```

### Elite Unit Special Crates
```ini
Die = CreateCrateDie ModuleTag_03
  CrateData = CrateSupplyBox
  CrateData = CrateSpecialWeapon
  CrateData = CrateUpgrade
End
```

## Template

```ini
Die = CreateCrateDie ModuleTag_XX
  ; Crate Creation
  CrateData =                     ; // crate template to create on death *(v1.04)*
End
```

## Notes

- CreateCrateDie creates supply crates when objects die based on various conditions
- Crate creation is tested against multiple conditions: creation chance, veterancy level, killer type, and killer science
- Crates are spawned near the dying object's location, with fallback to larger search radius if needed
- Allied kills do not generate crates to prevent exploitation
- Computer-controlled killers are notified of crate creation for AI awareness
- Crate ownership can be set to the dying object's team or remain neutral
- Multiple crate types can be specified with different conditions and probabilities
- Creates tactical opportunities for resource gathering when destroying enemy units

## Source Files

**Base Class:** [`DieModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateCrateDie.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateCrateDie.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Die/CreateCrateDie.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Die/CreateCrateDie.cpp)