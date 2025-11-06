# AIUpdate

Base class for AI update modules that handle artificial intelligence and decision-making for objects in the game engine.

## Overview

AIUpdate is the abstract base class for all AI update modules that handle artificial intelligence and decision-making for objects. It provides the fundamental interface for AI behaviors, pathfinding, combat decisions, and strategic planning. This module serves as the foundation for specialized AI implementations like AssaultTransportAIUpdate, ChinookAIUpdate, and other AI types that implement specific AI behaviors.

AIUpdate must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used as the base class for specialized AI update modules that implement different AI behaviors and decision-making systems. This is a **base AI update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Abstract base class - cannot be used directly
- Requires concrete implementation for actual functionality
- Only one AI update module per object
- Must be implemented by derived classes for specific behavior

**Conditions**:
- Multiple instances behavior: Multiple AIUpdate instances cannot exist - only one AI update module per object
- Always active once assigned to an object
- Provides interface for AI decision-making and behavior control
- Creates foundation for specialized AI implementations

**Dependencies**:
- Inherits all properties and functionality from UpdateModule
- Requires concrete implementation by derived classes
- Depends on AI systems for proper functionality

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

AIUpdate is an abstract base class and does not expose any additional INI-parsable properties beyond those inherited from UpdateModule. All functionality is implemented by derived classes such as:

- **AssaultTransportAIUpdate**: For assault transport vehicle AI
- **ChinookAIUpdate**: For Chinook helicopter AI
- **Other AI update modules**: For specific AI behaviors

## Examples

*AIUpdate is a base class and is not directly used in INI files. See derived classes like AssaultTransportAIUpdate, ChinookAIUpdate, and other AI update modules for actual usage examples.*

## Template

*AIUpdate is an abstract base class and cannot be instantiated directly. Use derived classes like AssaultTransportAIUpdate or ChinookAIUpdate for actual implementations.*

## Notes

- AIUpdate provides the fundamental interface for artificial intelligence and decision-making
- All AI update modules inherit from this base class and implement its virtual methods
- The module handles AI behaviors, pathfinding, combat decisions, and strategic planning
- Specialized AI types implement specific behaviors while maintaining the common interface
- This creates a consistent AI system across all object types

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp)
