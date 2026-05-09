# UpgradeDie

Die module that provides death mechanics for triggering upgrades when objects die with upgrade removal and death type filtering.

## Overview

UpgradeDie is a die module that provides death mechanics for triggering upgrades when objects die. It can remove specific upgrades from objects or players when the object is destroyed, and supports death type filtering to control when the upgrade removal occurs. This is commonly used for freeing up object-based upgrades when producer objects are destroyed.

UpgradeDie must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that need to trigger upgrades or special effects when they die. This is a **die module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Requires valid upgrade templates for upgrade removal functionality
- Cannot function without proper death and upgrade systems
- Upgrade removal is limited to object death events
- Requires proper upgrade system integration

**Conditions**:
- Multiple instances behavior: Multiple UpgradeDie modules can exist independently, each managing different upgrade removals
- Always active once assigned to an object
- Triggers during death events to remove upgrades
- Creates upgrade management for producer objects

**Dependencies**:
- Depends on the death system for triggering upgrade removal
- Requires proper upgrade system for upgrade management
- Inherits all functionality from DieModule

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Upgrade Configuration](#upgrade-configuration)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

### Upgrade Configuration

#### `UpgradeToRemove` *(v1.04)*
- **Type**: `AsciiString` (see [Upgrade documentation](../../Upgrade.md))
- **Description**: Name of the upgrade template to remove when the object dies. When set, removes the specified upgrade from the object or player. When empty (default), no upgrade is removed
- **Default**: `""` (empty)
- **Example**: `UpgradeToRemove = Upgrade_GenericObject300 ModuleTag_Tower04`

## Examples

### Basic Upgrade Die
```ini
Behavior = UpgradeDie ModuleTag_RemUP
  DeathTypes = ALL
  UpgradeToRemove = Upgrade_GenericObject300 ModuleTag_Tower04
End
```

### Alternative Upgrade Die
```ini
Behavior = UpgradeDie ModuleTag_RemUP
  DeathTypes = ALL
  UpgradeToRemove = Upgrade_GenericObject300 ModuleTag_Tower04
End
```

### Tower Upgrade Die
```ini
Behavior = UpgradeDie ModuleTag_RemUP
  DeathTypes = ALL
  UpgradeToRemove = Upgrade_GenericObject300 ModuleTag_Tower04
End
```

## Template

```ini
Behavior = UpgradeDie ModuleTag_XX
  ; Inherited from DieModule
  DeathTypes = ALL                   ; // death types that trigger this behavior *(v1.04)*
  
  ; Upgrade Configuration
  UpgradeToRemove =                  ; // upgrade template to remove on death *(v1.04)*
End
```

## Notes

- UpgradeDie removes upgrades when objects die, freeing up upgrade slots
- The module is commonly used for producer objects that grant object-based upgrades
- When the producer object is destroyed, the upgrade is automatically removed
- This creates proper upgrade management for producer-consumer relationships

## Source Files

**Base Class:** [`DieModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Die/UpgradeDie.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Die/UpgradeDie.cpp)
