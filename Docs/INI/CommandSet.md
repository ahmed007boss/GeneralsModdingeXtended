# CommandSet INI Documentation

## Overview
The `CommandSet` class represents a collection of CommandButtons that are displayed together in the game's control bar. CommandSets provide context-sensitive command interfaces that change based on the selected object, building, or game state.


## Usage

CommandSets are defined in `.ini` files within the game's data directories in a root folder called "CommandSet". They are typically associated with specific objects, buildings, or game contexts and determine which [CommandButtons](CommandButton.md) are available to the player at any given time. This is a **context-sensitive configuration system** that manages command button collections. The command set system allows objects to have different available commands based on their state, upgrades, or context.

**Limitations**:
- CommandSets can only contain up to 18 command button slots
- Only slots 1-14 are visible in the user interface
- All referenced CommandButtons must be valid and defined
- CommandSet names must be unique across all INI files

**Conditions**:
- CommandSets manage command button availability across different game contexts
- The configuration handles dynamic command switching based on upgrades and user input
- Command operations provide context-sensitive user interface elements
- Command management creates flexible and responsive control systems
- **Multiple instances behavior**: Each object can have only one active CommandSet, but multiple objects can share the same CommandSet template

**Dependencies**:
- Uses CommandButton definitions for individual command functionality
- Integrates with object templates through the CommandSet property
- Referenced by CommandSetupgradeModule for automatic switching
- Requires valid CommandButton references for all defined slots

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Basic Properties](#basic-properties)
- [Command Set Assignment](#command-set-assignment)
  - [Object-Based Assignment](#object-based-assignment)
  - [Building-Based Assignment](#building-based-assignment)
  - [Command Set Switching](#command-set-switching)
    - [User-Initiated Switching](#user-initiated-switching)
    - [Automatic Switching (CommandSetupgradeModule)](#automatic-switching-commandsetupgrademodule)
- [Examples](#examples)
  - [Basic Dozer Command Set](#basic-dozer-command-set)
  - [Faction-Specific Dozer Command Set](#faction-specific-dozer-command-set)
  - [Unit Command Set](#unit-command-set)
  - [Destroyed Building Command Set](#destroyed-building-command-set)
- [Command Set Limits](#command-set-limits)
  - [Maximum Commands](#maximum-commands)
  - [UI Layout](#ui-layout)
  - [Command Set Switching](#command-set-switching-1)
- [Best Practices](#best-practices)
  - [Command Organization](#command-organization)
  - [Command Set Naming](#command-set-naming)
  - [Performance Considerations](#performance-considerations)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Basic Properties

#### Command Button Slots *(v1.04)*
- **Type**: [`commandButton`](CommandButton.md) (up to 18 slots) *(Generals Zero Hour only)*
- **Description**: Individual command buttons in this set
- **Index**: 1 to 18 (only slots 1-14 are visible in UI) *(slots 13-18 are Generals Zero Hour only)*
- **Example**: 
```
CommandSet BZK600CommandSet
  1  = Command_SU34Bomb
  2  = Command_UpgradeChinaBZKReloadDrone
  11 = Command_AttackMove
  13 = Command_Guard    ; *(Generals Zero Hour only)*
  14 = Command_Stop     ; *(Generals Zero Hour only)*
End
```


## Command Set Assignment

### Object-Based Assignment
Command sets are typically assigned to objects through their template definitions:

```
Object USAInfantry
; ... other properties ...
CommandSet = "USAInfantryCommandSet"
END
```

### Building-Based Assignment
Buildings use command sets to define their production capabilities:

```
Object USABarracks
; ... other properties ...
CommandSet = "USABarracksCommandSet"
END
```

### Command Set Switching
There are two types of command set switching:

#### User-Initiated Switching
- **Switch Command Set Buttons**: Up to 5 command sets can be switched by clicking buttons with type `SWITCH_COMMAND_SET`
- **Player Selection**: User manually clicks buttons to switch between different command sets
- **Examples**: `COMMAND_SWITCH_COMMAND_SET`, `COMMAND_SWITCH_COMMAND_SET2`, etc.

#### Automatic Switching (CommandSetupgradeModule)
- **CommandSetupgradeModule**: Automatically changes command sets based on upgrades
- **Upgrade-Based**: Command sets change when specific upgrades are researched
- **Automatic**: No user interaction required - happens automatically when conditions are met

## Examples

### Basic Dozer Command Set
```
CommandSet ChinaDozerCommandSet
  1  = Command_ConstructChinaBarracks
  2  = Command_ConstructChinaPowerPlant
  3  = Command_ConstructChinaGattlingCannon
  4  = Command_ConstructChinaSupplyCenter
  5  = Command_ConstructChinaBunker
  6  = Command_ConstructChinaInternetCenter
  7  = Command_ConstructChinaPropagandaCenter
  8  = Command_ConstructChinaWarFactory
  9  = Command_ConstructChinaSpeakerTower
  10 = Command_ConstructChinaAirfield
  13 = Command_DisarmMinesAtPosition
  14 = Command_ConstructChinaCommandCenter
  18 = Command_ConstructChinaPowerPlant_AI
End
```

### Faction-Specific Dozer Command Set
```
CommandSet ChinaDozerCommandSetEWF
  1  = Command_ConstructChinaBarracks
  2  = Command_ConstructChinaPowerPlant
  3  = Command_ConstructChinaGattlingCannon
  4  = Command_ConstructChinaSupplyCenter
  5  = Command_ConstructChinaBunkerEWF
  6  = Command_ConstructChinaInternetCenter
  7  = Command_ConstructChinaPropagandaCenter
  8  = Command_ConstructChinaWarFactory
  9  = Command_ConstructChinaSpeakerTower
  10 = Command_ConstructChinaAirfield
  13 = Command_DisarmMinesAtPosition
  14 = Command_ConstructChinaCommandCenter
  17 = Command_ConstructChinaBunker
  18 = Command_ConstructChinaPowerPlant_AI
End
```

### Unit Command Set
```
CommandSet BZK600CommandSet
  1  = Command_SU34Bomb
  2  = Command_UpgradeChinaBZKReloadDrone
  11 = Command_AttackMove
  13 = Command_Guard
  14 = Command_Stop
End
```

### Destroyed Building Command Set
```
CommandSet DestroyedOilDerrickCommandSet
  1  = Command_UpgradeOilDerrickRebuild
End
```

## Command Set Limits

### Maximum Commands *(v1.04)*
- **Total Slots**: 18 command button slots (numbered 1-18) *(Generals Zero Hour only)*
- **Visible Slots**: Only slots 1-14 are visible in the UI
- **Hidden Slots**: Slots 15-18 are available but not displayed *(Generals Zero Hour only)*
- **Unused Slots**: Empty slots are automatically hidden in the UI

### UI Layout
Command buttons appear in the UI in a 2x7 grid layout:
```
+--+--+--+--+--+--+--+
|01|03|05|07|09|11|13|
+--+--+--+--+--+--+--+
|02|04|06|08|10|12|14|
+--+--+--+--+--+--+--+
```

### Command Set Switching
Command sets can be dynamically switched in two ways:
- **User-Initiated**: Manual switching via `SWITCH_COMMAND_SET` buttons
- **Automatic**: Via CommandSetupgradeModule based on upgrades

## Best Practices

### Command Organization
1. **Group related commands together**
2. **Place most common commands first**
3. **Use consistent button ordering across similar units**
4. **Leave unused slots empty (they will be hidden)**

### Command Set Naming
1. **Use descriptive names that indicate the context**
2. **Include faction prefix (USA, China, GLA)**
3. **Use consistent naming conventions**
4. **Avoid special characters in names**

### Performance Considerations
1. **Keep command sets reasonably sized**
2. **Avoid unnecessary command set switching**
3. **Use prerequisites to control button availability**
4. **Consider UI layout when designing command sets**

## Template

```ini
CommandSet CommandSetName
    1  = CommandButton1                       ; // First command button slot *(v1.04)*
    2  = CommandButton2                       ; // Second command button slot *(v1.04)*
    3  = CommandButton3                       ; // Third command button slot *(v1.04)*
    4  = CommandButton4                       ; // Fourth command button slot *(v1.04)*
    5  = CommandButton5                       ; // Fifth command button slot *(v1.04)*
    6  = CommandButton6                       ; // Sixth command button slot *(v1.04)*
    7  = CommandButton7                       ; // Seventh command button slot *(v1.04)*
    8  = CommandButton8                       ; // Eighth command button slot *(v1.04)*
    9  = CommandButton9                       ; // Ninth command button slot *(v1.04)*
    10 = CommandButton10                      ; // Tenth command button slot *(v1.04)*
    11 = CommandButton11                      ; // Eleventh command button slot *(v1.04)*
    12 = CommandButton12                      ; // Twelfth command button slot *(v1.04)*
    13 = CommandButton13                      ; // Thirteenth command button slot *(v1.04)*
    14 = CommandButton14                      ; // Fourteenth command button slot *(v1.04)*
    15 = CommandButton15                      ; // Fifteenth command button slot *(v1.04, Generals Zero Hour only)*
    16 = CommandButton16                      ; // Sixteenth command button slot *(v1.04, Generals Zero Hour only)*
    17 = CommandButton17                      ; // Seventeenth command button slot *(v1.04, Generals Zero Hour only)*
    18 = CommandButton18                      ; // Eighteenth command button slot *(v1.04, Generals Zero Hour only)*
End
```

## Notes

- CommandSets provide context-sensitive command button collections for user interface management
- The configuration manages command availability and organization across different game contexts
- Command operations create flexible and responsive control interfaces for players
- Command management ensures intuitive and efficient user interaction experiences
- This configuration is essential for user interface design and player control
- Command coordination creates consistent button behavior across different objects and contexts
- Command button slots control the order and availability of interface elements
- Dynamic switching allows command sets to change based on upgrades and context
- UI layout systems organize command buttons in logical and accessible arrangements
- Command set assignment connects command collections to specific objects and buildings
- Performance considerations ensure efficient command set switching and rendering
- CommandSets are defined in `.ini` files within the game's data directories in a root folder called "CommandSet" and in root file with name `CommandSet.ini`
- Each CommandSet must have a unique name - no two CommandSets can share the same name even across multiple files
- Command sets support dynamic switching based on upgrades
- All command buttons within a set must be valid CommandButton definitions
- Maximum of 18 command button slots per set (only 14 visible in UI)
- Up to 3 alternative command sets (CommandSet2-CommandSet4) can be defined
- Command sets integrate with the game's command system for executing player actions
- Button slot organization affects user interface layout and player experience
- Command set switching provides dynamic interface adaptation based on game state
- UI visibility controls ensure clean interface presentation with unused slots hidden

## Source Files

**Base Class:** [CommandSet](../GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h)
- Header: [`GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h`](../GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp`](../GeneralsMD/Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet


