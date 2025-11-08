# BodyModule

Base class for all body modules that manage health, damage, and destruction mechanics in the game engine.

## Overview

BodyModule is the abstract base class for all body modules that handle health, damage, and destruction mechanics. It provides the fundamental interface for damage processing, health management, and visual condition evaluation. This module serves as the foundation for specialized body implementations like ActiveBody, StructureBody, and other body types that implement specific health and damage behaviors.

BodyModule must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used as the base class for specialized body modules that implement different health and damage systems. This is a **base body module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Abstract base class - cannot be used directly
- Requires concrete implementation for actual functionality
- Only one body module per object
- Must be implemented by derived classes for specific behavior

**Conditions**:
- Multiple instances behavior: Multiple BodyModule instances cannot exist - only one body module per object
- Always active once assigned to an object
- Provides interface for damage processing and health management
- Creates foundation for specialized body implementations

**Dependencies**:
- Inherits all properties and functionality from BehaviorModule
- Requires concrete implementation by derived classes
- Depends on damage and armor systems for proper functionality

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

BodyModule is an abstract base class and does not expose any additional INI-parsable properties beyond those inherited from BehaviorModule. All functionality is implemented by derived classes such as:

- **ActiveBody**: For units and vehicles with health and damage
- **StructureBody**: For buildings and structures with health and damage
- **InactiveBody**: For objects without health systems
- **HighlanderBody**: For nearly invulnerable objects
- **ImmortalBody**: For truly indestructible objects
- **UndeadBody**: For objects with second life mechanics

## Examples

*BodyModule is a base class and is not directly used in INI files. See derived classes like ActiveBody, StructureBody, and other body modules for actual usage examples.*

## Template

*BodyModule is an abstract base class and cannot be instantiated directly. Use derived classes like ActiveBody or StructureBody for actual implementations.*

## Notes

- BodyModule provides the fundamental interface for health and damage management
- All body modules inherit from this base class and implement its virtual methods
- The module handles damage processing, health management, and visual condition evaluation
- Specialized body types implement specific behaviors while maintaining the common interface
- This creates a consistent damage and health system across all object types

## Source Files

**Base Class:** [`BehaviorModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Body/BodyModule.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Body/BodyModule.cpp)
