# HordeUpdate

HordeUpdate provides horde functionality for objects that can form or join hordes.

## Overview

The `HordeUpdate` class manages horde mechanics that allow objects to form groups, join existing hordes, or coordinate with other units in horde formations. It tracks nearby units, determines horde membership based on proximity and type, and manages horde-based bonuses and behaviors. This update is commonly used by infantry units, vehicles, and formations that benefit from group coordination and horde bonuses.

## Usage

Used by objects that can form hordes, join existing hordes, or coordinate with other units in horde formations. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Horde formation is limited by proximity and unit type requirements
- Horde bonuses are controlled by minimum count and radius parameters
- Rub-off effects require close proximity to true horde members
- Flag display depends on proper sub-object naming

**Conditions**:
- HordeUpdate continuously monitors nearby units for horde formation opportunities
- The update determines horde membership based on unit types, proximity, and alliance status
- Rub-off effects allow non-horde units to gain horde benefits when near true horde members
- Flag systems provide visual indication of horde membership
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own horde parameters

**Dependencies**:
- Requires unit type classification (KindOf) system
- Uses alliance system for determining friendly vs. enemy units
- Integrates with visual system for flag display

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Horde Formation Settings](#horde-formation-settings)
  - [Proximity Settings](#proximity-settings)
  - [Behavior Settings](#behavior-settings)
  - [Visual Settings](#visual-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Horde Formation Settings

#### `UpdateRate` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: How often to recheck horde status and update horde membership. Higher values reduce update frequency but improve performance. Lower values provide more responsive horde formation
- **Default**: `1000` (1 second)
- **Example**: `UpdateRate = 1000`

#### `KindOf` *(v1.04)*
- **Type**: `KindOfMaskType` (bit flags)
- **Description**: Unit types that count towards horde formation. When set, only units with matching types contribute to horde status. When empty, all unit types can contribute
- **Default**: `0` (all types)
- **Example**: `KindOf = INFANTRY VEHICLE`

#### `Count` *(v1.04)*
- **Type**: `Int`
- **Description**: Minimum number of units required to achieve horde status. Higher values require more units for horde formation. Lower values allow smaller hordes
- **Default**: `0`
- **Example**: `Count = 5`

### Proximity Settings

#### `Radius` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: How close other units must be to count towards horde formation. Higher values allow units farther away to contribute. Lower values require closer proximity
- **Default**: `30.0`
- **Example**: `Radius = 50.0`

#### `RubOffRadius` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: If unit is this close to a true horde member, it gains honorary horde status. Higher values allow farther rub-off effects. Lower values require closer proximity for rub-off
- **Default**: `60.0`
- **Example**: `RubOffRadius = 75.0`

### Behavior Settings

#### `AlliesOnly` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether only allied units count towards horde formation. When true, only friendly units contribute to horde status. When false, all qualifying units can contribute
- **Default**: `Yes`
- **Example**: `AlliesOnly = No`

#### `ExactMatch` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether only exact same unit types count towards horde formation. When true, only identical unit types contribute. When false, all KindOf-compatible units contribute
- **Default**: `No`
- **Example**: `ExactMatch = Yes`

#### `Action` *(v1.04)*
- **Type**: `HordeActionType` (enum)
- **Description**: What action to take when horde status is achieved. Controls the behavior and bonuses applied when the unit becomes part of a horde
- **Default**: `HORDE_ACTION_NONE`
- **Example**: `Action = HORDE_ACTION_BONUS`
- **Available Values**: See [HordeActionType Values](#hordeactiontype-values) section

#### `AllowedNationalism` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether nationalism bonuses are allowed for this horde. When true, enables nationalism-based horde bonuses. When false, nationalism effects are disabled
- **Default**: `No`
- **Example**: `AllowedNationalism = Yes`

### Visual Settings

#### `FlagSubObjectNames` *(v1.04)*
- **Type**: `AsciiString` (vector)
- **Description**: Names of flag sub-objects to display when in horde. When set, displays flags on specified sub-objects. When empty, no flags are shown
- **Default**: `""`
- **Example**: `FlagSubObjectNames = "Flag01" "Flag02"`

## HordeActionType Values *(v1.04)*

- **`HORDE_ACTION_NONE`** *(v1.04)* - No special action when in horde
- **`HORDE_ACTION_BONUS`** *(v1.04)* - Apply horde bonuses when in horde
- **`HORDE_ACTION_FLAG`** *(v1.04)* - Display horde flags when in horde
- **`HORDE_ACTION_COMBINED`** *(v1.04)* - Apply both bonuses and flags when in horde

## Examples

### Basic Infantry Horde
```ini
Behavior = HordeUpdate ModuleTag_06
  RubOffRadius = 60    ; if I am this close to a real hordesman, I will get to be an honorary hordesman
  UpdateRate = 1000    ; how often to recheck horde status (msec)
  Radius = 30          ; how close other units must be to us to count towards our horde-ness (~30 feet or so)
End
```

### Vehicle Horde with Larger Radius
```ini
Behavior = HordeUpdate ModuleTag_04A
  RubOffRadius = 150    ; if I am this close to a real hordesman, I will get to be an honorary hordesman
  UpdateRate = 1000     ; how often to recheck horde status (msec)
  Radius = 75           ; how close other units must be to us to count towards our horde-ness (~30 feet or so)
End
```

### Specialized Horde with Flags
```ini
Behavior = HordeUpdate ModuleTag_04
  RubOffRadius = 60    ; if I am this close to a real hordesman, I will get to be an honorary hordesman
  UpdateRate = 1000    ; how often to recheck horde status (msec)
  Radius = 50          ; how close other units must be to us to count towards our horde-ness (~30 feet or so)
  Action = HORDE_ACTION_COMBINED
  FlagSubObjectNames = "Flag01" "Flag02"
  AllowedNationalism = Yes
End
```

## Template

```ini
Behavior = HordeUpdate ModuleTag_XX
  ; Horde Formation Settings
  UpdateRate = 1000                    ; // how often to recheck horde status *(v1.04)*
  KindOf =                             ; // unit types that count towards horde *(v1.04)*
  Count = 0                            ; // minimum units for horde status *(v1.04)*
  
  ; Proximity Settings
  Radius = 30.0                        ; // proximity for horde formation *(v1.04)*
  RubOffRadius = 60.0                  ; // proximity for honorary horde status *(v1.04)*
  
  ; Behavior Settings
  AlliesOnly = Yes                     ; // only allied units count *(v1.04)*
  ExactMatch = No                      ; // only exact same types count *(v1.04)*
  Action = HORDE_ACTION_NONE           ; // action when horde status achieved *(v1.04)*
  AllowedNationalism = No              ; // allow nationalism bonuses *(v1.04)*
  
  ; Visual Settings
  FlagSubObjectNames =                 ; // flag sub-object names *(v1.04)*
End
```

## Notes

- HordeUpdate provides sophisticated group formation mechanics for coordinated unit behavior
- The update enables both true horde membership and honorary horde status through rub-off effects
- Proximity-based horde formation creates realistic tactical groupings
- Flag systems provide visual feedback for horde membership
- This update is commonly used by infantry formations, vehicle groups, and specialized units
- Horde bonuses and nationalism effects enhance group combat effectiveness

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h), [`HordeUpdateInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/HordeUpdate.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/HordeUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/HordeUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/HordeUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/HordeUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet