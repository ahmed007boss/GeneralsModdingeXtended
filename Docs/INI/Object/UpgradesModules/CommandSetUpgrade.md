# CommandSetUpgrade

CommandSetUpgrade provides the ability to change an object's command set (available commands/buttons) when an upgrade is applied, allowing for dynamic command availability based on upgrade status.

## Overview

The `CommandSetUpgrade` class manages command set changes for objects when specific upgrades are applied. This upgrade module allows objects to have different available commands depending on their upgrade state, providing enhanced functionality and new capabilities. The behavior supports both primary and alternative command sets, with conditional logic to choose between them based on additional upgrade requirements.

## Usage

Used by objects that need to change their available commands when upgrades are applied. This is an **upgrade module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Only changes the command set strings, not the actual command functionality
- The new command sets must exist and be properly defined
- Command set changes are applied immediately when the upgrade is activated
- Alternative command sets require additional upgrade conditions to be met

**Conditions**:
- CommandSetUpgrade changes the object's command set when the specified upgrade is applied
- The upgrade integrates with the upgrade system for conditional activation
- Alternative command sets can be used if additional upgrade conditions are met
- The UI is automatically refreshed to show the new command set
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own command set changes

**Dependencies**:
- Requires an object with upgrade system integration
- The new command sets must exist in the game's command set definitions
- Objects must have proper command set system integration
- The control bar UI system must be available for proper display

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)

## Properties

### Command Set Settings

#### `CommandSet` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: The primary command set to use when this upgrade is applied. This replaces the object's default command set and provides new available commands
- **Default**: `""` (empty)
- **Example**: `CommandSet = "ChinaEliteTankCommandSet"`

#### `CommandSetAlt` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: The alternative command set to use if the TriggerAlt upgrade condition is met. This provides an additional layer of conditional command availability
- **Default**: `""` (empty)
- **Example**: `CommandSetAlt = "ChinaEliteTankAdvancedCommandSet"`

#### `CommandSet2` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: The second command set to use when this upgrade is applied. This provides additional command slots for the object
- **Default**: `""` (empty)
- **Example**: `CommandSet2 = "ChinaEliteTankCommandSet2"`

#### `CommandSet2Alt` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: The alternative second command set to use if the TriggerAlt upgrade condition is met
- **Default**: `""` (empty)
- **Example**: `CommandSet2Alt = "ChinaEliteTankAdvancedCommandSet2"`

#### `CommandSet3` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: The third command set to use when this upgrade is applied. This provides additional command slots for the object
- **Default**: `""` (empty)
- **Example**: `CommandSet3 = "ChinaEliteTankCommandSet3"`

#### `CommandSet3Alt` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: The alternative third command set to use if the TriggerAlt upgrade condition is met
- **Default**: `""` (empty)
- **Example**: `CommandSet3Alt = "ChinaEliteTankAdvancedCommandSet3"`

#### `CommandSet4` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: The fourth command set to use when this upgrade is applied. This provides additional command slots for the object
- **Default**: `""` (empty)
- **Example**: `CommandSet4 = "ChinaEliteTankCommandSet4"`

#### `CommandSet4Alt` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: The alternative fourth command set to use if the TriggerAlt upgrade condition is met
- **Default**: `""` (empty)
- **Example**: `CommandSet4Alt = "ChinaEliteTankAdvancedCommandSet4"`

### Alternative Trigger Settings

#### `TriggerAlt` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: The upgrade name that triggers the use of alternative command sets. When this upgrade is active (either on the player or object), the alternative command sets are used instead of the primary ones
- **Default**: `"none"`
- **Example**: `TriggerAlt = "Upgrade_AdvancedTraining"`

## Examples

### Basic Command Set Change
```ini
Upgrade = CommandSetUpgrade ModuleTag_EliteCommands
  CommandSet = "ChinaEliteTankCommandSet"
  TriggeredBy = Upgrade_EliteTraining
End
```

### Advanced Command Set with Alternatives
```ini
Upgrade = CommandSetUpgrade ModuleTag_AdvancedCommands
  CommandSet = "ChinaAdvancedTankCommandSet"
  CommandSetAlt = "ChinaAdvancedTankEliteCommandSet"
  TriggerAlt = "Upgrade_EliteTraining"
  TriggeredBy = Upgrade_AdvancedTraining
End
```

### Multiple Command Sets
```ini
Upgrade = CommandSetUpgrade ModuleTag_MultiCommands
  CommandSet = "ChinaTankCommandSet"
  CommandSet2 = "ChinaTankCommandSet2"
  CommandSet3 = "ChinaTankCommandSet3"
  CommandSet4 = "ChinaTankCommandSet4"
  TriggeredBy = Upgrade_MultiTraining
End
```

### Conditional Command Sets
```ini
Upgrade = CommandSetUpgrade ModuleTag_ConditionalCommands
  CommandSet = "ChinaBasicTankCommandSet"
  CommandSetAlt = "ChinaEliteTankCommandSet"
  CommandSet2 = "ChinaBasicTankCommandSet2"
  CommandSet2Alt = "ChinaEliteTankCommandSet2"
  TriggerAlt = "Upgrade_EliteTraining"
  TriggeredBy = Upgrade_BasicTraining
End
```

## Template

```ini
Upgrade = CommandSetUpgrade ModuleTag_XX
  ; Command Set Settings
  CommandSet =                     ; // primary command set *(v1.04)*
  CommandSetAlt =                  ; // alternative command set *(v1.04)*
  CommandSet2 =                    ; // second command set *(v1.04)*
  CommandSet2Alt =                 ; // alternative second command set *(v1.04)*
  CommandSet3 =                    ; // third command set *(v1.04)*
  CommandSet3Alt =                 ; // alternative third command set *(v1.04)*
  CommandSet4 =                    ; // fourth command set *(v1.04)*
  CommandSet4Alt =                 ; // alternative fourth command set *(v1.04)*
  
  ; Alternative Trigger Settings
  TriggerAlt = none                ; // upgrade that triggers alternatives *(v1.04)*
  
  ; Upgrade Integration (inherited from UpgradeModule)
  TriggeredBy =                    ; // required upgrade flags *(v1.04)*
  ConflictsWith =                  ; // conflicting upgrade flags *(v1.04)*
  RequiresAll = No                 ; // require all TriggeredBy upgrades *(v1.04)*
End
```

## Notes

- CommandSetUpgrade changes the object's command set when the specified upgrade is applied
- The upgrade integrates with the upgrade system for conditional activation
- Alternative command sets can be used if additional upgrade conditions are met
- The UI is automatically refreshed to show the new command set
- The new command sets must exist in the game's command set definitions
- Objects can have up to four different command sets (CommandSet, CommandSet2, CommandSet3, CommandSet4)
- Alternative command sets provide additional conditional logic for command availability
- The TriggerAlt upgrade can be either a player upgrade or an object upgrade

## Source Files

**Base Class:** [`UpgradeModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CommandSetUpgrade.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CommandSetUpgrade.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/CommandSetUpgrade.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/CommandSetUpgrade.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet
