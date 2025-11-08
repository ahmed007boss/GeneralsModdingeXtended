# TargetingUpdate

TargetingUpdate provides targeting functionality for objects that can target other objects.

## Overview

The `TargetingUpdate` class manages targeting operations for objects that can target other objects, manage targeting systems, or handle target acquisition. It handles target acquisition, target tracking, and targeting system integration. This update is commonly used by combat units, weapons systems, and objects that need targeting capabilities.

## Usage

Used by objects that need to target other objects, manage targeting systems, or handle target acquisition. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Targeting operations are limited by targeting system capabilities and target parameters
- Target acquisition depends on proper targeting system integration
- Target tracking is controlled by targeting parameters and system capabilities
- Targeting effectiveness varies based on targeting system capabilities

**Conditions**:
- TargetingUpdate manages targeting operations and target acquisition
- The update handles target tracking, target acquisition, and targeting system integration
- Targeting operations provide target acquisition and tracking capabilities
- Target tracking creates realistic targeting system operations
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own targeting parameters

**Dependencies**:
- Uses targeting system for target acquisition and tracking
- Integrates with combat system for targeting operations
- Uses detection system for target identification

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

*No examples of TargetingUpdate were found in the INI files.*

## Template

```ini
Behavior = TargetingUpdate ModuleTag_XX
  ; Properties will be documented from source files
End
```

## Notes

- TargetingUpdate provides targeting operations and target acquisition capabilities
- The update manages target tracking, target acquisition, and targeting system integration
- Targeting operations provide essential target acquisition and tracking capabilities
- Target tracking creates realistic targeting system operations and coordination
- This update is commonly used by combat units, weapons systems, and targeting objects
- Targeting coordination ensures efficient target acquisition and tracking operations

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/TargetingUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/TargetingUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/TargetingUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/TargetingUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet