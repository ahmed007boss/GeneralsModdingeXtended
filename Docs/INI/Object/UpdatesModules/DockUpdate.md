# DockUpdate

Base class for docking update modules that provide docking functionality for objects that can dock with other objects or structures.

## Overview

DockUpdate is the abstract base class for all docking update modules that provide docking functionality for objects that can dock with other objects or structures. It provides the fundamental interface for docking operations, dock management, and docking coordination. This module serves as the foundation for specialized docking implementations like SupplyCenterDockUpdate, RepairDockUpdate, and other docking types.

DockUpdate must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used as the base class for specialized docking update modules that implement different docking behaviors. This is a **base docking update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Abstract base class - cannot be used directly
- Requires concrete implementation for actual functionality
- Only one docking update module per object
- Must be implemented by derived classes for specific behavior

**Conditions**:
- Multiple instances behavior: Multiple DockUpdate instances cannot exist - only one docking update module per object
- Always active once assigned to an object
- Provides interface for docking operations and coordination
- Creates foundation for specialized docking implementations

**Dependencies**:
- Inherits all properties and functionality from UpdateModule
- Requires concrete implementation by derived classes
- Depends on docking systems for proper functionality

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

DockUpdate is an abstract base class and does not expose any additional INI-parsable properties beyond those inherited from UpdateModule. All functionality is implemented by derived classes such as:

- **SupplyCenterDockUpdate**: For supply center docking operations
- **RepairDockUpdate**: For repair facility docking operations
- **SupplyWarehouseDockUpdate**: For supply warehouse docking operations
- **Other docking update modules**: For specific docking behaviors

## Examples

*DockUpdate is a base class and is not directly used in INI files. See derived classes like SupplyCenterDockUpdate, RepairDockUpdate, SupplyWarehouseDockUpdate, and RailedTransportDockUpdate for actual usage examples.*

## Template

*DockUpdate is an abstract base class and cannot be instantiated directly. Use derived classes like SupplyCenterDockUpdate or RepairDockUpdate for actual implementations.*

## Notes

- DockUpdate provides the fundamental interface for docking functionality
- All docking update modules inherit from this base class and implement its virtual methods
- The module handles docking operations, dock management, and docking coordination
- Specialized docking types implement specific behaviors while maintaining the common interface
- This creates a consistent docking system across all object types

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h), [`DockUpdateInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DockUpdate.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DockUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DockUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/DockUpdate/DockUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/DockUpdate/DockUpdate.cpp)
