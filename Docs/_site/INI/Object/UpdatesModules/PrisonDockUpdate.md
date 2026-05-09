# PrisonDockUpdate

PrisonDockUpdate provides docking functionality specifically for prison systems and prisoner management.

## Overview

The `PrisonDockUpdate` class manages docking operations for prison facilities, handling prisoner transfer, loading, and unloading operations. It extends DockUpdate to provide specialized prison docking mechanics including prisoner coordination, prison facility management, and prisoner transport integration. This update is commonly used by prison facilities, detention centers, and objects that need to coordinate with prisoner transport systems.

## Usage

Used by objects that need to dock with prison facilities for prisoner transfer or management. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Prison docking is limited by dock system capabilities and prison capacity
- Prisoner transfer operations depend on prison facility availability
- Docking coordination requires proper prison system integration
- Prison operations are controlled by dock update functionality

**Conditions**:
- PrisonDockUpdate manages specialized prison docking and prisoner transfer operations
- The update handles prisoner loading, unloading, and prison facility coordination
- Dock operations are coordinated with prison management systems
- Prisoner transfer creates realistic prison facility operations
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own prison operations

**Dependencies**:
- Extends DockUpdate for base docking functionality
- Requires prison system integration for prisoner management
- Uses dock interface for docking operations

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

*No examples of PrisonDockUpdate were found in the INI files.*

## Template

```ini
Behavior = PrisonDockUpdate ModuleTag_XX
  ; Properties will be documented from source files
End
```

## Notes

- PrisonDockUpdate extends DockUpdate with specialized prison facility docking mechanics
- The update provides prisoner transfer and prison coordination functionality
- Prison docking operations create realistic prison facility management
- This update is commonly used by prison facilities, detention centers, and prisoner transport coordination
- Dock interface integration ensures proper prison system coordination

## Source Files

**Base Class:** [`DockUpdate`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DockUpdate.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/PrisonDockUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/PrisonDockUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/DockUpdate/PrisonDockUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/DockUpdate/PrisonDockUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet