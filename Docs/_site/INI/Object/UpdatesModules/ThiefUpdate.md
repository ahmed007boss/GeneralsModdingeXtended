# ThiefUpdate

ThiefUpdate provides thief functionality for objects that can steal resources or items.

## Overview

The `ThiefUpdate` class manages thief operations for objects that can steal resources, items, or other valuables from other objects or players. It handles theft operations, resource acquisition, and thief behavior management. This update is commonly used by thief units, resource stealing objects, and units with theft capabilities.

## Usage

Used by objects that can steal resources, items, or other valuables from other objects or players. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Thief operations are limited by theft system capabilities and thief parameters
- Resource theft depends on proper theft system integration
- Theft behavior is controlled by thief parameters and system capabilities
- Theft effectiveness varies based on thief capabilities

**Conditions**:
- ThiefUpdate manages thief operations and resource theft
- The update handles theft behavior, resource acquisition, and thief system integration
- Thief operations provide resource theft and acquisition capabilities
- Theft behavior creates realistic thief operations
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own thief parameters

**Dependencies**:
- Uses theft system for resource theft operations
- Integrates with resource system for resource acquisition
- Uses behavior system for thief behavior management

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

*No examples of ThiefUpdate were found in the INI files.*

## Template

```ini
Behavior = ThiefUpdate ModuleTag_XX
  ; Properties will be documented from source files
End
```

## Notes

- ThiefUpdate provides thief operations and resource theft capabilities
- The update manages theft behavior, resource acquisition, and thief system integration
- Thief operations provide resource theft and acquisition capabilities
- Theft behavior creates realistic thief operations and coordination
- This update is commonly used by thief units, resource stealing objects, and theft capability units
- Thief coordination ensures efficient resource theft and acquisition operations

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ThiefUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ThiefUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/ThiefUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/ThiefUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet