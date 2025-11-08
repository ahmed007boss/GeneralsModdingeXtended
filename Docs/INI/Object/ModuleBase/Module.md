# Module

Abstract base class for all game modules in Command & Conquer Generals, providing the foundation for object behavior and functionality.

## Overview

Module is the abstract base class that provides the foundation for all game modules in Command & Conquer Generals. It defines the core interface for modules that can be attached to objects, drawables, and things to provide specific functionality. This includes behavior modules, update modules, draw modules, and client update modules. The module system allows for modular object design where different aspects of object behavior can be implemented as separate, reusable components.

Module must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used as the foundation for all game modules that provide specific functionality to objects, drawables, and things. This is an **abstract base class** that must be inherited by specific module implementations. Cannot be used directly in INI files - only concrete implementations can be used.

**Limitations**:
- Cannot be instantiated directly - must be inherited by specific module implementations
- Cannot be used in INI files - only concrete implementations are usable
- Requires concrete implementation of module-specific functionality
- Must be properly registered with the game engine's module system

**Conditions**:
- Multiple instances behavior: Multiple modules can exist independently, each providing different functionality
- Always active once assigned to an object
- Modules are automatically managed by the game engine's module system
- Supports different module types: behavior, update, draw, client update

**Dependencies**:
- Requires proper module data for initialization
- Depends on the game engine's module management system
- Inherits from GameMemoryObject for memory management

## Properties

This is an abstract base class with no additional INI-parsable properties beyond those inherited from ModuleData.


## Notes

- Module is the abstract base class for all game modules
- Provides the foundation for modular object design
- Supports different module types: behavior, draw, client update
- Modules can implement various interfaces: update, die, damage, create, collide, body, contain, upgrade, special power, destroy, draw, client update
- Essential for the game's modular architecture where objects are composed of multiple modules
- Each module type has specific functionality and interfaces
- Modules are automatically managed by the game engine's module system

## Source Files

**Base Class:** [`GameMemoryObject`](../../GeneralsMD/Code/GameEngine/Include/Common/GameMemory.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/Common/Module.h`](../../GeneralsMD/Code/GameEngine/Include/Common/Module.h)
