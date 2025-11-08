# CreateObjectDie

CreateObjectDie creates objects when the parent object dies or is destroyed.

## Overview

The `CreateObjectDie` class manages object creation upon death, allowing objects to spawn replacement units, structures, or effects when they are destroyed. It can transfer health information from the dying object to the newly created object, maintaining continuity in certain scenarios. This behavior is commonly used for unit transformations, structure replacements, and death effects that spawn additional objects.

## Usage

Used by objects that need to create other objects when they die, such as transformable units, replaceable structures, or objects with death effects. This is a **die module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- CreateObjectDie only triggers when the object actually dies
- Object creation is limited by the specified ObjectCreationList definition
- Health transfer only works between objects with compatible body systems
- The behavior requires valid object template definitions to function
- Created objects inherit the dying object's team and player ownership

**Conditions**:
- CreateObjectDie can create objects at the same location as the dying object
- The behavior integrates with the death system for conditional activation
- Health transfer preserves subdual damage, electronic warfare damage, and previous health
- Attacker information can be transferred to the newly created object
- The behavior supports conditional activation based on death types and conditions
- **Multiple instances behavior**: Multiple instances can exist with different conditions; all matching instances will create their objects simultaneously

**Dependencies**:
- Requires valid ObjectCreationList definitions to function correctly
- The behavior relies on the death system for activation timing

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Object Creation](#object-creation)
  - [Health Transfer](#health-transfer)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

### Object Creation

#### `CreationList` *(v1.04)*
- **Type**: `ObjectCreationList` (see [ObjectCreationList documentation](../ObjectCreationList.md))
- **Description**: Object creation list that defines what objects to create when the parent dies. When set, spawns the specified objects at the dying object's location. When NULL (default), no objects are created on death
- **Default**: `NULL` (none)
- **Example**: `CreationList = ChinaInfantryMinigunner`

### Health Transfer

#### `TransferPreviousHealth` *(v1.04, Generals Zero Hour only)*
- **Type**: `Bool`
- **Description**: Whether to transfer previous health, subdual damage, and EW damage from the dying object to the newly created object. When true, created objects inherit the damage state of the dying object. When false (default), created objects spawn at full health
- **Default**: `No`
- **Example**: `TransferPreviousHealth = Yes`

## Examples

### Unit Transformation on Death
```ini
Die = CreateObjectDie ModuleTag_Transform
  CreationList = ChinaInfantryMinigunner
End
```

### Structure Replacement
```ini
Die = CreateObjectDie ModuleTag_Replace
  CreationList = ChinaBuildingWarFactory
End
```

### Health Transfer Death
```ini
Die = CreateObjectDie ModuleTag_HealthTransfer
  CreationList = GLAInfantryRebel
  TransferPreviousHealth = Yes
End
```

### Multiple Death Effects
```ini
Die = CreateObjectDie ModuleTag_Explosion
  CreationList = ChinaInfantryMinigunner
  DeathTypes = NONE +EXPLODED
End
```

## Template

```ini
Die = CreateObjectDie ModuleTag_XX
  CreationList =                     ; // object creation list to spawn *(v1.04)*
  TransferPreviousHealth = No        ; // transfer health from dying object *(v1.04, Generals Zero Hour only)*
End
```

## Notes

- CreateObjectDie can create objects at the same location as the dying object
- The behavior integrates with the death system for conditional activation
- Health transfer preserves subdual damage, electronic warfare damage, and previous health
- Attacker information can be transferred to the newly created object
- The behavior supports conditional activation based on death types and conditions
- TransferPreviousHealth property is exclusive to Generals Zero Hour (v1.04)

## Source Files

**Base Class:** [`DieModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateObjectDie.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateObjectDie.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Die/CreateObjectDie.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Die/CreateObjectDie.cpp)