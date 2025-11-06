# DisplayNameUpgrade

DisplayNameUpgrade provides the ability to change an object's display name when an upgrade is applied, allowing for dynamic name changes based on upgrade status.

## Overview

The `DisplayNameUpgrade` class manages display name changes for objects when specific upgrades are applied. This upgrade module allows objects to have different names depending on their upgrade state, providing visual feedback to players about the object's current status or capabilities. The behavior is commonly used for units that change their designation when upgraded, such as basic units becoming elite versions.

## Usage

Used by objects that need to change their display name when upgrades are applied. This is an **upgrade module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Only changes the display name shown in the UI, not the internal object name
- The new display name is applied immediately when the upgrade is activated
- Display name changes are permanent until the upgrade is removed (if applicable)

**Conditions**:
- DisplayNameUpgrade changes the object's display name when the specified upgrade is applied
- The upgrade integrates with the upgrade system for conditional activation
- The display name change is visible in all UI elements that show the object's name
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own display name changes

**Dependencies**:
- Requires an object with upgrade system integration
- Objects must have a display name system to function properly
- The upgrade system must be properly configured for the object

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

### Display Name Settings

#### `DisplayName` *(v1.04)*
- **Type**: `UnicodeString`
- **Description**: The new display name to show when this upgrade is applied. This name will replace the object's default display name in all UI elements. The name is automatically translated using the game's localization system
- **Default**: `""` (empty)
- **Example**: `DisplayName = "Elite Tank"`

## Examples

### Basic Elite Unit Name Change
```ini
Upgrade = DisplayNameUpgrade ModuleTag_EliteName
  DisplayName = "Elite Tank"
  TriggeredBy = Upgrade_EliteTraining
End
```

### Advanced Unit Designation
```ini
Upgrade = DisplayNameUpgrade ModuleTag_AdvancedDesignation
  DisplayName = "Advanced Battle Tank"
  TriggeredBy = Upgrade_AdvancedTraining
  ConflictsWith = Upgrade_BasicTraining
End
```

### Faction-Specific Name Change
```ini
Upgrade = DisplayNameUpgrade ModuleTag_FactionName
  DisplayName = "GLA Technical"
  TriggeredBy = Upgrade_GLAModification
End
```

### Veteran Unit Naming
```ini
Upgrade = DisplayNameUpgrade ModuleTag_VeteranName
  DisplayName = "Veteran Infantry"
  TriggeredBy = Upgrade_VeteranTraining
  RequiresAll = Yes
End
```

## Template

```ini
Upgrade = DisplayNameUpgrade ModuleTag_XX
  ; Display Name Settings
  DisplayName =                    ; // new display name when upgrade is applied *(v1.04)*
  
  ; Upgrade Integration (inherited from UpgradeModule)
  TriggeredBy =                    ; // required upgrade flags *(v1.04)*
  ConflictsWith =                  ; // conflicting upgrade flags *(v1.04)*
  RequiresAll = No                 ; // require all TriggeredBy upgrades *(v1.04)*
End
```

## Notes

- DisplayNameUpgrade changes the object's display name when the specified upgrade is applied
- The upgrade integrates with the upgrade system for conditional activation
- Display name changes are visible in all UI elements that show the object's name
- The display name is automatically translated using the game's localization system
- The upgrade system must be properly configured for the object to function
- Display name changes are permanent until the upgrade is removed (if applicable)

## Source Files

**Base Class:** [`UpgradeModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DisplayNameUpgrade.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DisplayNameUpgrade.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/DisplayNameUpgrade.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/DisplayNameUpgrade.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet
