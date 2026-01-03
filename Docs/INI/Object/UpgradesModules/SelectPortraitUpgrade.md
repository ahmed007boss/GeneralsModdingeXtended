# SelectPortraitUpgrade

SelectPortraitUpgrade provides the ability to change an object's select portrait image and/or video when an upgrade is applied, allowing for dynamic portrait changes based on upgrade status.

## Overview

The `SelectPortraitUpgrade` class manages select portrait changes for objects when specific upgrades are applied. This upgrade module allows objects to have different portrait images and videos depending on their upgrade state, providing visual feedback to players about the object's current status or capabilities. The behavior is commonly used for units that change their appearance when upgraded, such as basic units becoming elite versions with a new portrait.

## Usage

Used by objects that need to change their select portrait when upgrades are applied. This is an **upgrade module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Only changes the portrait shown in the UI when the unit is selected, not any other visual elements
- The new portrait is applied immediately when the upgrade is activated
- Portrait changes are permanent until the upgrade is removed (if applicable)
- The portrait image must exist in the game's mapped image collection
- The video file must exist in the game's data directory

**Conditions**:
- SelectPortraitUpgrade changes the object's select portrait when the specified upgrade is applied
- The upgrade integrates with the upgrade system for conditional activation
- The portrait change is visible in the control bar when the unit is selected
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own portrait changes

**Dependencies**:
- Requires an object with upgrade system integration
- Objects must have a portrait display system to function properly
- The upgrade system must be properly configured for the object
- Portrait images must be defined in the game's mapped image collection
- Portrait videos must be in a supported format (.bik)

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

### Portrait Settings

#### `SelectPortrait` *(v1.04+)*
- **Type**: `AsciiString`
- **Description**: The name of the mapped image to use as the new select portrait when this upgrade is applied. This image will replace the object's default portrait in the control bar when selected. The image name must match an entry in the game's mapped image collection
- **Default**: `""` (empty - no change to portrait image)
- **Example**: `SelectPortrait = EUIEliteTankPortrait`

#### `SelectPortraitVideo` *(v1.04+)*
- **Type**: `AsciiString`
- **Description**: The filename of the video to play as the select portrait when this upgrade is applied. This video will replace the object's default portrait video (if any) in the control bar when selected. The video file must exist in the game's data directory
- **Default**: `""` (empty - no change to portrait video)
- **Example**: `SelectPortraitVideo = EUIEliteTank.bik`

## Examples

### Basic Elite Unit Portrait Change
```ini
Upgrade = SelectPortraitUpgrade ModuleTag_ElitePortrait
  SelectPortrait = EUIEliteTankPortrait
  TriggeredBy = Upgrade_EliteTraining
End
```

### Portrait with Video Change
```ini
Upgrade = SelectPortraitUpgrade ModuleTag_AdvancedPortrait
  SelectPortrait = EUIAdvancedTankPortrait
  SelectPortraitVideo = EUIAdvancedTank.bik
  TriggeredBy = Upgrade_AdvancedTraining
End
```

### Video-Only Change
```ini
Upgrade = SelectPortraitUpgrade ModuleTag_VideoUpgrade
  SelectPortraitVideo = EUIVeteranUnit.bik
  TriggeredBy = Upgrade_VeteranTraining
End
```

### Faction-Specific Portrait Change
```ini
Upgrade = SelectPortraitUpgrade ModuleTag_FactionPortrait
  SelectPortrait = EUIGLATechnicalUpgraded
  SelectPortraitVideo = EUIGLATechnicalUpgraded.bik
  TriggeredBy = Upgrade_GLAModification
  ConflictsWith = Upgrade_USAModification
End
```

### Combined with DisplayNameUpgrade
```ini
; Change both name and portrait when upgraded
Upgrade = DisplayNameUpgrade ModuleTag_EliteName
  DisplayName = "Elite Tank"
  DisplayPluralName = "Elite Tanks"
  TriggeredBy = Upgrade_EliteTraining
End

Upgrade = SelectPortraitUpgrade ModuleTag_ElitePortrait
  SelectPortrait = EUIEliteTankPortrait
  SelectPortraitVideo = EUIEliteTank.bik
  TriggeredBy = Upgrade_EliteTraining
End
```

## Template

```ini
Upgrade = SelectPortraitUpgrade ModuleTag_XX
  ; Portrait Settings
  SelectPortrait =               ; // new portrait image name when upgrade is applied *(v1.04+)*
  SelectPortraitVideo =          ; // new portrait video filename when upgrade is applied *(v1.04+)*
  
  ; Upgrade Integration (inherited from UpgradeModule)
  TriggeredBy =                  ; // required upgrade flags *(v1.04)*
  ConflictsWith =                ; // conflicting upgrade flags *(v1.04)*
  RequiresAll = No               ; // require all TriggeredBy upgrades *(v1.04)*
End
```

## Notes

- SelectPortraitUpgrade changes the object's select portrait image and/or video when the specified upgrade is applied
- The upgrade integrates with the upgrade system for conditional activation
- Portrait changes are visible in the control bar when the unit is selected
- You can specify just the image, just the video, or both - empty values will not override the existing portrait
- The portrait image must be defined in the game's mapped image collection (MappedImages.ini or similar)
- The video file must be in Bink format (.bik) and located in the game's data directory
- Portrait changes are permanent until the upgrade is removed (if applicable)
- This module works well in combination with DisplayNameUpgrade for complete visual identity changes

## Source Files

**Base Class:** [`UpgradeModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SelectPortraitUpgrade.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SelectPortraitUpgrade.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/SelectPortraitUpgrade.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/SelectPortraitUpgrade.cpp)

## Changes History

- **v1.04+**: Initial implementation by Ahmed Salah (January 2026)

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: January 2026 by @Ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet
