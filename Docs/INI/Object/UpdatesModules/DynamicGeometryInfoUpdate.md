# DynamicGeometryInfoUpdate

Base class for dynamic geometry information update modules that provide dynamic geometry information functionality for objects with changing geometry.

## Overview

DynamicGeometryInfoUpdate is the abstract base class for all dynamic geometry information update modules that provide dynamic geometry information functionality for objects with changing geometry. It provides the fundamental interface for geometry management, dynamic geometry updates, and geometry state changes. This module serves as the foundation for specialized dynamic geometry implementations like FirestormDynamicGeometryInfoUpdate.

DynamicGeometryInfoUpdate must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used as the base class for specialized dynamic geometry information update modules that implement different dynamic geometry behaviors. This is a **base dynamic geometry update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Abstract base class - cannot be used directly
- Requires concrete implementation for actual functionality
- Only one dynamic geometry update module per object
- Must be implemented by derived classes for specific behavior

**Conditions**:
- Multiple instances behavior: Multiple DynamicGeometryInfoUpdate instances cannot exist - only one dynamic geometry update module per object
- Always active once assigned to an object
- Provides interface for dynamic geometry management and updates
- Creates foundation for specialized dynamic geometry implementations

**Dependencies**:
- Inherits all properties and functionality from UpdateModule
- Requires concrete implementation by derived classes
- Depends on geometry systems for proper functionality

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

DynamicGeometryInfoUpdate is an abstract base class and does not expose any additional INI-parsable properties beyond those inherited from UpdateModule. All functionality is implemented by derived classes such as:

- **FirestormDynamicGeometryInfoUpdate**: For firestorm effects with dynamic geometry
- **Other dynamic geometry update modules**: For specific dynamic geometry behaviors

## Examples

*DynamicGeometryInfoUpdate is a base class and is not directly used in INI files. See derived classes like FirestormDynamicGeometryInfoUpdate for actual usage examples.*

## Template

*DynamicGeometryInfoUpdate is an abstract base class and cannot be instantiated directly. Use derived classes like FirestormDynamicGeometryInfoUpdate for actual implementations.*

## Notes

- DynamicGeometryInfoUpdate provides the fundamental interface for dynamic geometry management
- All dynamic geometry update modules inherit from this base class and implement its virtual methods
- The module handles geometry updates, state changes, and dynamic geometry coordination
- Specialized dynamic geometry types implement specific behaviors while maintaining the common interface
- This creates a consistent dynamic geometry system across all object types

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/DynamicGeometryInfoUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/DynamicGeometryInfoUpdate.cpp)
