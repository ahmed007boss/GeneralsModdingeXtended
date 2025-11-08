# HealUpgrade

HealUpgrade provides healing functionality for objects that can heal themselves or other objects.

## Overview

The `HealUpgrade` class manages healing operations for objects that can heal themselves, heal other objects, or provide healing capabilities. It handles healing activation, healing management, and healing system integration. This upgrade is commonly used by objects that provide healing capabilities, healing systems, and units with healing capabilities.

## Usage

Used by objects that can heal themselves, heal other objects, or provide healing capabilities. This is an **upgrade module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Healing operations are limited by healing parameters and healing system capabilities
- Healing activation depends on proper upgrade system integration
- Healing management is controlled by healing parameters and system capabilities
- Healing effectiveness varies based on healing capabilities

**Conditions**:
- HealUpgrade manages healing operations and healing system coordination
- The upgrade handles healing activation, healing management, and healing system integration
- Healing operations provide healing capabilities and healing system capabilities
- Healing management creates realistic healing system operations
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own healing parameters

**Dependencies**:
- Uses upgrade system for healing upgrade activation
- Integrates with healing system for healing capabilities
- Uses healing coordination system for healing management

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

*Properties documentation will be added when this page is completed from the corresponding C++ source files.*

## Examples

*No examples of HealUpgrade were found in the INI files.*

## Template

```ini
Behavior = HealUpgrade ModuleTag_XX
  ; Properties will be documented from source files
End
```

## Notes

- HealUpgrade provides healing operations and healing system coordination capabilities
- The upgrade manages healing activation, healing management, and healing system integration
- Healing operations provide essential healing capabilities and healing system capabilities
- Healing management creates realistic healing system operations and coordination
- This upgrade is commonly used by objects that provide healing capabilities, healing systems, and healing capability units
- Healing coordination ensures efficient healing and system integration operations

## Source Files

**Base Class:** [`UpgradeModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/HealUpgrade.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/HealUpgrade.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/HealUpgrade.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/HealUpgrade.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet