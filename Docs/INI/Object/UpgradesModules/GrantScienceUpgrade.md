# GrantScienceUpgrade

GrantScienceUpgrade provides the ability to grant science/technology to players when an upgrade is applied, allowing for automatic technology advancement based on upgrade status.

## Overview

The `GrantScienceUpgrade` class manages science/technology granting for players when specific upgrades are applied. This upgrade module allows objects to automatically grant science to the controlling player when the upgrade is activated, providing a way to advance technology without manual research. The behavior is commonly used for buildings that provide technology bonuses or special conditions that grant scientific knowledge.

## Usage

Used by objects that need to grant science/technology to players when upgrades are applied. This is an **upgrade module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Only grants science to the controlling player, not other players
- The science must exist in the game's science system
- Science is granted immediately when the upgrade is activated
- Cannot grant science to objects, only players

**Conditions**:
- GrantScienceUpgrade grants science to the player when the specified upgrade is applied
- The upgrade integrates with the upgrade system for conditional activation
- Science is granted to the controlling player of the object
- The science must exist in the game's science store
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own science granting

**Dependencies**:
- Requires an object with upgrade system integration
- The science must exist in the game's science system
- Objects must have proper player system integration
- The science store must be available for science lookup

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

### Science Granting Settings

#### `GrantScience` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: The internal name of the science/technology to grant to the player when this upgrade is applied. This must be a valid science that exists in the game's science system. The science will be granted to the controlling player
- **Default**: `""` (empty)
- **Example**: `GrantScience = "Science_AdvancedWeapons"`

## Examples

### Basic Science Grant
```ini
Upgrade = GrantScienceUpgrade ModuleTag_GrantScience
  GrantScience = "Science_AdvancedWeapons"
  TriggeredBy = Upgrade_WeaponResearch
End
```

### Technology Advancement
```ini
Upgrade = GrantScienceUpgrade ModuleTag_TechnologyAdvancement
  GrantScience = "Science_AdvancedArmor"
  TriggeredBy = Upgrade_ArmorResearch
End
```

### Multiple Science Grants
```ini
Upgrade = GrantScienceUpgrade ModuleTag_GrantScience1
  GrantScience = "Science_BasicWeapons"
  TriggeredBy = Upgrade_BasicResearch
End

Upgrade = GrantScienceUpgrade ModuleTag_GrantScience2
  GrantScience = "Science_AdvancedWeapons"
  TriggeredBy = Upgrade_AdvancedResearch
End
```

### Conditional Science Grant
```ini
Upgrade = GrantScienceUpgrade ModuleTag_ConditionalScience
  GrantScience = "Science_EliteTraining"
  TriggeredBy = Upgrade_EliteResearch
  ConflictsWith = Upgrade_BasicResearch
End
```

## Template

```ini
Upgrade = GrantScienceUpgrade ModuleTag_XX
  ; Science Granting Settings
  GrantScience =                    ; // internal name of science to grant *(v1.04)*
  
  ; Upgrade Integration (inherited from UpgradeModule)
  TriggeredBy =                     ; // required upgrade flags *(v1.04)*
  ConflictsWith =                   ; // conflicting upgrade flags *(v1.04)*
  RequiresAll = No                  ; // require all TriggeredBy upgrades *(v1.04)*
End
```

## Notes

- GrantScienceUpgrade grants science to the player when the specified upgrade is applied
- The upgrade integrates with the upgrade system for conditional activation
- Science is granted to the controlling player of the object
- The science must exist in the game's science store
- Only grants science to the controlling player, not other players
- The science must exist in the game's science system
- Science is granted immediately when the upgrade is activated
- Cannot grant science to objects, only players
- The science is looked up by internal name from the science store

## Source Files

**Base Class:** [`UpgradeModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/GrantScienceUpgrade.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/GrantScienceUpgrade.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/GrantScienceUpgrade.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/GrantScienceUpgrade.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet
