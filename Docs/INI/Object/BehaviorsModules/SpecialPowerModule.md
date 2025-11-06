# SpecialPowerModule

Base class for special power modules that handle special power functionality in the game engine.

## Overview

SpecialPowerModule is the abstract base class for all special power modules that handle special power functionality. It provides the fundamental interface for special power activation, execution, and management. This module serves as the foundation for specialized special power implementations like OCLSpecialPower, CashBountyPower, FireWeaponPower, and other special power types that implement specific special power behaviors.

SpecialPowerModule must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used as the base class for specialized special power modules that implement different special power behaviors. This is a **base special power module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Abstract base class - cannot be used directly
- Requires concrete implementation for actual functionality
- Only one special power module per object
- Must be implemented by derived classes for specific behavior

**Conditions**:
- Multiple instances behavior: Multiple SpecialPowerModule instances cannot exist - only one special power module per object
- Always active once assigned to an object
- Provides interface for special power activation and execution
- Creates foundation for specialized special power implementations

**Dependencies**:
- Inherits all properties and functionality from BehaviorModule
- Requires concrete implementation by derived classes
- Depends on special power systems for proper functionality

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

SpecialPowerModule is an abstract base class and does not expose any additional INI-parsable properties beyond those inherited from BehaviorModule. All functionality is implemented by derived classes such as:

- **OCLSpecialPower**: For special powers that create objects
- **CashBountyPower**: For special powers that provide cash rewards
- **FireWeaponPower**: For special powers that fire weapons
- **Other special power modules**: For specific special power behaviors

## Examples

*SpecialPowerModule is a base class and is not directly used in INI files. See derived classes like OCLSpecialPower, CashBountyPower, FireWeaponPower, and other special power modules for actual usage examples.*

## Template

*SpecialPowerModule is an abstract base class and cannot be instantiated directly. Use derived classes like OCLSpecialPower or CashBountyPower for actual implementations.*

## Notes

- SpecialPowerModule provides the fundamental interface for special power functionality
- All special power modules inherit from this base class and implement its virtual methods
- The module handles special power activation, execution, and management behaviors
- Specialized special power types implement specific behaviors while maintaining the common interface
- This creates a consistent special power system across all object types

## Source Files

**Base Class:** [`BehaviorModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/SpecialPower/SpecialPowerModule.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/SpecialPower/SpecialPowerModule.cpp)
