# StunnedUpdate

StunnedUpdate provides stunned functionality for objects that can be stunned or paralyzed.

## Overview

The `StunnedUpdate` class manages stunned behavior for objects that can be stunned, paralyzed, or have their movement/actions restricted. It handles stunned state management, paralysis effects, and stunned behavior coordination. This update is commonly used by units that can be stunned, paralyzed objects, and units with stunned capabilities.

## Usage

Used by objects that can be stunned, paralyzed, or have their movement/actions restricted. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Stunned operations are limited by stunned system capabilities and stunned parameters
- Stunned behavior depends on proper stunned system integration
- Paralysis effects are controlled by stunned parameters and system capabilities
- Stunned effectiveness varies based on stunned capabilities

**Conditions**:
- StunnedUpdate manages stunned operations and paralysis effects
- The update handles stunned behavior, paralysis effects, and stunned system integration
- Stunned operations provide paralysis and movement restriction capabilities
- Stunned behavior creates realistic stunned operations
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own stunned parameters

**Dependencies**:
- Uses stunned system for stunned operations
- Integrates with movement system for paralysis effects
- Uses behavior system for stunned behavior management

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

*No examples of StunnedUpdate were found in the INI files.*

## Template

```ini
Behavior = StunnedUpdate ModuleTag_XX
  ; Properties will be documented from source files
End
```

## Notes

- StunnedUpdate provides stunned operations and paralysis effects capabilities
- The update manages stunned behavior, paralysis effects, and stunned system integration
- Stunned operations provide paralysis and movement restriction capabilities
- Stunned behavior creates realistic stunned operations and coordination
- This update is commonly used by units that can be stunned, paralyzed objects, and stunned capability units
- Stunned coordination ensures efficient paralysis and movement restriction operations

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StunnedUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StunnedUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/StunnedUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/StunnedUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet