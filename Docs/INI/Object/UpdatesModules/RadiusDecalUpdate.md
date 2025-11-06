# RadiusDecalUpdate

RadiusDecalUpdate provides radius decal functionality for objects that can create radius-based visual effects.

## Overview

The `RadiusDecalUpdate` class manages radius decal creation and management for objects that need to display area-of-effect indicators, range markers, or radius-based visual effects. It handles decal creation, positioning, and removal for visual feedback systems. This update is commonly used by weapons, abilities, and objects that need to show radius-based effects or range indicators.

## Usage

Used by objects that can create radius decals for area-of-effect visualization or range indicators. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Radius decal creation is limited by decal system capabilities and graphics performance
- Decal positioning depends on coordinate accuracy and terrain conditions
- Decal management is controlled by decal lifecycle parameters
- Visual effects are limited by graphics system capabilities

**Conditions**:
- RadiusDecalUpdate manages radius decal creation, positioning, and removal
- The update handles decal lifecycle management and visual feedback
- Decal positioning provides accurate area-of-effect visualization
- Radius decals create visual indicators for range and effect areas
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own decal parameters

**Dependencies**:
- Uses decal system for visual effect creation and management
- Integrates with graphics system for decal rendering
- Uses positioning system for decal placement

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

### Example 1
```ini
Behavior = RadiusDecalUpdate ModuleTag_17
  ; nothing
End
```

*Only 1 example of RadiusDecalUpdate was found in the INI files.*

## Template

```ini
Behavior = RadiusDecalUpdate ModuleTag_XX
  ; Properties will be documented from source files
End
```

## Notes

- RadiusDecalUpdate provides radius decal creation and management for visual effects
- The update handles decal lifecycle including creation, positioning, and removal
- Radius decals provide visual feedback for area-of-effect abilities and range indicators
- This update is commonly used by weapons, abilities, and objects requiring radius visualization
- Decal management ensures efficient visual effect creation and performance

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RadiusDecalUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RadiusDecalUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/RadiusDecalUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/RadiusDecalUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet