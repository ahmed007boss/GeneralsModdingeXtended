# OCLSpecialPower

Special power module that creates objects using Object Creation Lists (OCL) with configurable placement locations and upgrade support.

## Overview

OCLSpecialPower is a special power module that creates objects using Object Creation Lists (OCL) when the special power is activated. It supports different placement locations, upgrade-based OCL selection, and position adjustment for passable terrain. This module is commonly used for special powers that spawn units, buildings, or other objects at specific locations.

OCLSpecialPower must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that should create other objects using Object Creation Lists when special powers are activated. This is a **special power module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Requires valid Object Creation Lists to function
- Cannot create objects when special power conditions are not met
- Placement is limited to configured location types
- Requires proper OCL templates for object creation

**Conditions**:
- Multiple instances behavior: Multiple OCLSpecialPower modules can exist independently, each creating different objects
- Always active once assigned to an object
- Triggers when special power is activated
- Creates tactical advantages through strategic object placement

**Dependencies**:
- Requires valid Object Creation Lists for object creation
- Depends on the special power system for activation
- Inherits all functionality from SpecialPowerModule

## Properties

### Object Creation Configuration

#### `OCL` *(v1.04)*
- **Type**: `ObjectCreationList`
- **Description**: Default Object Creation List used to create objects when the special power is activated. When set, creates the specified objects. When NULL (default), no objects are created
- **Default**: `NULL` (none)
- **Example**: `OCL = OCL_SpecialPowerUnits`

#### `UpgradeOCL` *(v1.04)*
- **Type**: `ScienceType` + `ObjectCreationList` (pairs)
- **Description**: Pairs of science types and Object Creation Lists for upgrade-based object creation. When the player has the specified science, uses the corresponding OCL instead of the default. When empty (default), no upgrade-based OCLs are used
- **Default**: `None`
- **Example**: 
```
UpgradeOCL = SCIENCE_ADVANCED_TECHNOLOGY OCL_AdvancedUnits
UpgradeOCL = SCIENCE_SUPERWEAPONS OCL_SuperweaponUnits
```

### Placement Configuration

#### `CreateLocation` *(v1.04)*
- **Type**: `OCLCreateLocType` (enum)
- **Description**: Location type for object creation. Determines where objects are placed relative to the source and target. When set to CREATE_AT_EDGE_NEAR_SOURCE (default), objects are created at the edge near the source
- **Default**: `CREATE_AT_EDGE_NEAR_SOURCE`
- **Example**: `CreateLocation = CREATE_AT_LOCATION`

#### `OCLAdjustPositionToPassable` *(v1.04)*
- **Type**: `Bool`
- **Description**: Determines if object positions are adjusted to the nearest passable terrain. When `Yes`, positions are adjusted to passable terrain. When `No` (default), positions are not adjusted
- **Default**: `No`
- **Example**: `OCLAdjustPositionToPassable = Yes`

### Reference Object

#### `ReferenceObject` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Name of the reference object template for placement calculations. When set, used for script placement calculations for construction sites. When empty (default), no reference object is used
- **Default**: `""` (empty)
- **Example**: `ReferenceObject = BuildingConstructionSite`

## Enum Value Lists

#### `OCLCreateLocType` Values *(v1.04)*
**Source:** [OCLSpecialPower.h](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/OCLSpecialPower.h) - `OCLCreateLocType` enum definition

- **`CREATE_AT_EDGE_NEAR_SOURCE`** *(v1.04)* - Create objects at the edge near the source
- **`CREATE_AT_EDGE_NEAR_TARGET`** *(v1.04)* - Create objects at the edge near the target
- **`CREATE_AT_LOCATION`** *(v1.04)* - Create objects at the specified location
- **`USE_OWNER_OBJECT`** *(v1.04)* - Create objects at the owner object's location
- **`CREATE_ABOVE_LOCATION`** *(v1.04)* - Create objects above the specified location
- **`CREATE_AT_EDGE_FARTHEST_FROM_TARGET`** *(v1.04)* - Create objects at the edge farthest from the target

## Examples

### Basic Unit Spawn
```ini
SpecialPower = OCLSpecialPower ModuleTag_01
  OCL = OCL_SpecialPowerUnits
  CreateLocation = CREATE_AT_EDGE_NEAR_SOURCE
  OCLAdjustPositionToPassable = Yes
End
```

### Upgrade-Based Unit Spawn
```ini
SpecialPower = OCLSpecialPower ModuleTag_02
  OCL = OCL_BasicUnits
  UpgradeOCL = SCIENCE_ADVANCED_TECHNOLOGY OCL_AdvancedUnits
  UpgradeOCL = SCIENCE_SUPERWEAPONS OCL_SuperweaponUnits
  CreateLocation = CREATE_AT_LOCATION
  OCLAdjustPositionToPassable = No
End
```

### Construction Site Spawn
```ini
SpecialPower = OCLSpecialPower ModuleTag_03
  OCL = OCL_ConstructionSite
  CreateLocation = CREATE_AT_EDGE_NEAR_TARGET
  OCLAdjustPositionToPassable = Yes
  ReferenceObject = BuildingConstructionSite
End
```

## Template

```ini
SpecialPower = OCLSpecialPower ModuleTag_XX
  ; Object Creation Configuration
  OCL =                                 ; // default object creation list *(v1.04)*
  UpgradeOCL = SCIENCE_TYPE OCL_NAME    ; // upgrade-based object creation *(v1.04)*
  
  ; Placement Configuration
  CreateLocation = CREATE_AT_EDGE_NEAR_SOURCE ; // object placement location *(v1.04)*
  OCLAdjustPositionToPassable = No      ; // adjust positions to passable terrain *(v1.04)*
  
  ; Reference Object
  ReferenceObject =                     ; // reference object for placement calculations *(v1.04)*
End
```

## Notes

- OCLSpecialPower creates objects using Object Creation Lists when special powers are activated
- Supports upgrade-based OCL selection for different technology levels
- Includes configurable placement locations and terrain adjustment
- Commonly used for unit spawning, building construction, and special power effects
- The module manages object creation based on special power activation and placement rules
- Creates tactical advantages through strategic object placement

## Source Files

**Base Class:** [`SpecialPowerModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/OCLSpecialPower.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/OCLSpecialPower.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/SpecialPower/OCLSpecialPower.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/SpecialPower/OCLSpecialPower.cpp)