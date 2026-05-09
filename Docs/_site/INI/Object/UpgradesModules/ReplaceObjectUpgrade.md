# ReplaceObjectUpgrade

ReplaceObjectUpgrade provides the ability to completely replace an object with a different object type when an upgrade is applied, creating a seamless transformation effect.

## Overview

The `ReplaceObjectUpgrade` class manages complete object replacement when specific upgrades are applied. This upgrade module allows objects to be transformed into entirely different object types while preserving their position, team, selection state, and squad membership. The behavior is commonly used for units that undergo major transformations, such as buildings that change into different structures or units that evolve into more advanced forms.

## Usage

Used by objects that need to be completely replaced with a different object type when upgrades are applied. This is an **upgrade module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- The replacement object must exist and be properly defined
- The original object is completely destroyed and replaced
- All original object state is lost except for position, team, selection, and squad membership
- The replacement object starts with full health and default state

**Conditions**:
- ReplaceObjectUpgrade completely replaces the object when the specified upgrade is applied
- The upgrade integrates with the upgrade system for conditional activation
- The replacement preserves the original object's position, team, selection state, and squad membership
- The replacement object is automatically marked as built and construction complete
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own replacement object

**Dependencies**:
- Requires an object with upgrade system integration
- The replacement object must exist in the game's object templates
- Objects must have proper team and player systems to function correctly
- The pathfinding system must be available for proper object placement

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

### Replacement Settings

#### `ReplaceObject` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: The name of the object template to replace the current object with. This must be a valid object template that exists in the game. The replacement object will be created at the exact same position and with the same team as the original object
- **Default**: `""` (empty)
- **Example**: `ReplaceObject = "ChinaAdvancedTank"`

## Examples

### Basic Unit Evolution
```ini
Upgrade = ReplaceObjectUpgrade ModuleTag_Evolution
  ReplaceObject = "ChinaEliteTank"
  TriggeredBy = Upgrade_EliteTraining
End
```

### Building Transformation
```ini
Upgrade = ReplaceObjectUpgrade ModuleTag_Upgrade
  ReplaceObject = "ChinaAdvancedWarFactory"
  TriggeredBy = Upgrade_AdvancedTechnology
  ConflictsWith = Upgrade_BasicTechnology
End
```

### Faction-Specific Replacement
```ini
Upgrade = ReplaceObjectUpgrade ModuleTag_FactionChange
  ReplaceObject = "GLATechnical"
  TriggeredBy = Upgrade_GLAModification
End
```

### Conditional Replacement
```ini
Upgrade = ReplaceObjectUpgrade ModuleTag_ConditionalReplace
  ReplaceObject = "USAAvancedSoldier"
  TriggeredBy = Upgrade_AdvancedTraining
  RequiresAll = Yes
End
```

## Template

```ini
Upgrade = ReplaceObjectUpgrade ModuleTag_XX
  ; Replacement Settings
  ReplaceObject =                  ; // object template to replace with *(v1.04)*
  
  ; Upgrade Integration (inherited from UpgradeModule)
  TriggeredBy =                    ; // required upgrade flags *(v1.04)*
  ConflictsWith =                  ; // conflicting upgrade flags *(v1.04)*
  RequiresAll = No                 ; // require all TriggeredBy upgrades *(v1.04)*
End
```

## Notes

- ReplaceObjectUpgrade completely replaces the object when the specified upgrade is applied
- The upgrade integrates with the upgrade system for conditional activation
- The replacement preserves the original object's position, team, selection state, and squad membership
- The replacement object is automatically marked as built and construction complete
- The original object is completely destroyed and replaced with the new object
- All original object state is lost except for position, team, selection, and squad membership
- The replacement object must exist in the game's object templates
- The pathfinding system is properly updated to reflect the object change

## Source Files

**Base Class:** [`UpgradeModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ReplaceObjectUpgrade.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ReplaceObjectUpgrade.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/ReplaceObjectUpgrade.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/ReplaceObjectUpgrade.cpp)

## Changes History

- **v1.04**: Initial implementation
- **Bugfix**: Fixed selection and squad membership preservation during object replacement

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet
