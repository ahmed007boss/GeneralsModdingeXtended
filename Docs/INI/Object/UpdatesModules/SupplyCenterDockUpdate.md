# SupplyCenterDockUpdate

SupplyCenterDockUpdate provides docking functionality specifically for supply center facilities.

## Overview

The `SupplyCenterDockUpdate` class manages docking operations for objects that need to dock with supply centers for resource management and supply operations. It handles supply center docking, approach positioning, and supply coordination. This update is commonly used by supply center facilities, resource management buildings, and objects that provide supply services.

## Usage

Used by objects that need to dock with supply centers for resource management and supply operations. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Supply center docking is limited by approach positioning and passthrough parameters
- Docking operations depend on proper supply center integration
- Supply coordination requires proper supply system integration
- Docking effectiveness varies based on supply center capabilities

**Conditions**:
- SupplyCenterDockUpdate manages supply center docking and supply coordination
- The update handles approach positioning, passthrough control, and supply operations
- Supply center docking provides resource management and supply capabilities
- Approach positioning creates realistic supply center operations
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own supply parameters

**Dependencies**:
- Extends DockUpdate for base docking functionality
- Requires supply system integration for supply operations
- Uses dock interface for docking operations

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Docking Settings](#docking-settings)
  - [Supply Settings](#supply-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Docking Settings

#### `AllowsPassthrough` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether units can pass through while docking. When true, allows passthrough. When false, prevents passthrough
- **Default**: `No`
- **Example**: `AllowsPassthrough = No`

#### `NumberApproachPositions` *(v1.04)*
- **Type**: `Int`
- **Description**: Number of approach positions for docking. Higher values allow more approach positions. Lower values limit approach positions. -1 means infinite approach positions
- **Default**: `0`
- **Example**: `NumberApproachPositions = -1`

### Supply Settings

#### `GrantTemporaryStealth` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Duration of temporary stealth granted during supply operations. Higher values grant longer stealth. Lower values grant shorter stealth
- **Default**: `0`
- **Example**: `GrantTemporaryStealth = 20000`

## Examples

### Basic Supply Center Dock
```ini
Behavior = SupplyCenterDockUpdate ModuleTag_13
  AllowsPassthrough = No ;You can't drive through this guy while docking.  Use this when the dock points are all outside
  NumberApproachPositions = -1 ; This is a Boneless dock, so this means infinite can approach
  GrantTemporaryStealth = 20000
End
```

### Supply Center Dock with Passthrough
```ini
Behavior = SupplyCenterDockUpdate ModuleTag_13
  AllowsPassthrough = No ;You can't drive through this guy while docking.  Use this when the dock points are all outside
  NumberApproachPositions = -1 ; This is a Boneless dock, so this means infinite can approach
End
```

### Supply Center Dock with Approach Positions
```ini
Behavior = SupplyCenterDockUpdate ModuleTag_13
  AllowsPassthrough = No ;You can't drive through this guy while docking.  Use this when the dock points are all outside
  NumberApproachPositions = 9 ; There are 9 approach bones in the art
End
```

## Template

```ini
Behavior = SupplyCenterDockUpdate ModuleTag_XX
  ; Docking Settings
  AllowsPassthrough = No                 ; // whether units can pass through while docking *(v1.04)*
  NumberApproachPositions = 0            ; // number of approach positions for docking *(v1.04)*
  
  ; Supply Settings
  GrantTemporaryStealth = 0              ; // duration of temporary stealth granted *(v1.04)*
End
```

## Notes

- SupplyCenterDockUpdate extends DockUpdate with specialized supply center docking mechanics
- The update provides supply center docking and supply coordination functionality
- Approach positioning creates realistic supply center operations and resource management
- This update is commonly used by supply center facilities, resource management buildings, and supply coordination objects
- Supply center docking ensures efficient resource management and supply operations

## Source Files

**Base Class:** [`DockUpdate`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DockUpdate.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyCenterDockUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyCenterDockUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/DockUpdate/SupplyCenterDockUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/DockUpdate/SupplyCenterDockUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet