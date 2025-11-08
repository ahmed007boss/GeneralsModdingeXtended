# CommandButton INI Documentation

## Overview

The `CommandButton` class represents a single command button in the game's user interface. These buttons appear in the control bar and allow players to execute various commands such as building units, constructing structures, using special powers, and more.

**CommandButtons** are INI-based configuration entries that define the clickable buttons used to trigger player actions. They represent the core **user interface elements** that connect the player’s input to in-game functionality.

Each CommandButton specifies what happens when clicked—such as training a unit, constructing a building, activating a special power, or toggling a mode. They can also control costs, prerequisites, tooltips, and associated sounds or animations.

CommandButtons are typically grouped into **[CommandSets](CommandSet.md)** , which assign collections of buttons to units, structures, or command bars

## Source Files

- Header: [`GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h`](../GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h) - `CommandButton` class definition
- Source: [`GeneralsMD/Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp`](../GeneralsMD/Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp) - `CommandButton` parsing logic

## Usage

A CommandButton is defined inside an .ini file located in the CommandButton folder (e.g., CommandButton\MyCustomButtons.ini).
This structure is introduced by GMX — in the vanilla game, all CommandButtons are hardcoded in a single CommandButton.ini file.

When GMX is used, the engine automatically loads all .ini files from the CommandButton directory and merges them at runtime. This allows modders to keep buttons organized across multiple files (per faction, unit type, or feature) instead of maintaining one massive file.

A CommandButton definition on its own does nothing. It only becomes visible and usable when:

- Added to a **[CommandSets](CommandSet.md)** → attached to a unit, building, or interface slot.
- Linked to a sidebar shortcut → such as the right-side quick action buttons.

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Basic Properties](#basic-properties)
  - [Display Properties](#display-properties)
  - [Overlay Image Properties](#overlay-image-properties)
  - [Prerequisites and Requirements](#prerequisites-and-requirements)
  - [Modifier Key and Click Type Buttons](#modifier-key-and-click-type-buttons)
  - [Alternative Command Buttons (Prerequisite-Based Replacement)](#alternative-command-buttons-prerequisite-based-replacement)
    - [Available Prerequisite Types](#available-prerequisite-types)
- [Enum Value Lists](#enum-value-lists)
  - [Command Values (GUICommandType)](#command-values-guicommandtype)
  - [WeaponSlot Values (WeaponSlotType)](#weaponslot-values-weaponslottype)
  - [ButtonBorderType Values (CommandButtonMappedBorderType)](#buttonbordertype-values-commandbuttonmappedbordertype)
  - [RadiusCursorType Values](#radiuscursortype-values)
  - [CommandOption Enum Values](#commandoption-enum-values)
- [Examples](#examples)
  - [Basic Unit Build Button](#basic-unit-build-button)
  - [Player Upgrade Button](#player-upgrade-button)
  - [Object Upgrade Button](#object-upgrade-button)
  - [Special Power Button](#special-power-button)
  - [Weapon Switching Button](#weapon-switching-button)
  - [Science Purchase Button](#science-purchase-button)
  - [Complex Prerequisites Example](#complex-prerequisites-example)
  - [Command Button with Overlay Images (New Feature)](#command-button-with-overlay-images-new-feature)
  - [Alternative Command Buttons (New Feature)](#alternative-command-buttons-new-feature)
  - [Modifier Key Button Example](#modifier-key-button-example)
  - [Fire Weapon Button](#fire-weapon-button)
- [Best Practices](#best-practices)
  - [Command Button Design](#command-button-design)
  - [Prerequisites and Requirements](#prerequisites-and-requirements-1)
  - [Alternative Buttons](#alternative-buttons)
  - [Display and UI](#display-and-ui)
  - [Performance and Maintenance](#performance-and-maintenance)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Basic Properties

#### `Command` *(v1.04)*

- **Type**: `GUICommandType`
- **Description**: Defines the type of command this button executes
- **Values**:
  - `UNIT_BUILD` - Build a unit
  - `DOZER_CONSTRUCT` - Construct a building
  - `OBJECT_UPGRADE` - Upgrade an object
  - `PLAYER_UPGRADE` - Research a player upgrade
  - `SPECIAL_POWER` - Use a special power
  - `WEAPON_FIRE` - Fire a weapon
  - [And many more...](#command-values-guicommandtype)
- **Example**: `Command = UNIT_BUILD`

#### `Options` *(v1.04)*

- **Type**: `CommandOptionMaskType` (bit flags)
- **Description**: Various behavioral options for the command button. Accepts multiple options separated by spaces
- **Example**: `Options = NEED_TARGET_POS OK_FOR_MULTI_SELECT`
- **Available Options**: See [CommandOption Enum Values](#commandoption-enum-values) section below

#### `Object` *(v1.04)*

- **Type**: `object` (see [Object documentation](Object.md))
- **Description**: The object/unit template this button creates or targets
- **Example**: `Object = USAInfantry`

#### `Upgrade` *(v1.04)*

- **Type**: `upgrade` (see [Upgrade documentation](Upgrade.md))
- **Description**: The upgrade template this button researches
- **Example**: `Upgrade = USAUpgradeInfantryWeapons`

#### `WeaponSlot` *(v1.04)*

- **Type**: `WeaponSlotType`
- **Description**: Which weapon slot to use when firing
- **Example**: `WeaponSlot = PRIMARY_WEAPON`
- **Available Values**: See [WeaponSlot Values](#weaponslot-values-weaponslottype) section below

#### `MaxShotsToFire` *(v1.04)*

- **Type**: `Int`
- **Description**: Maximum number of shots to fire when using this command
- **Example**: `MaxShotsToFire = 3`

#### `Science` *(v1.04)*

- **Type**: `ScienceType` (vector)
- **Description**: Science requirements for this button to be available
- **Example**: `Science = USAAdvancedWeapons`

#### `SpecialPower` *(v1.04)*

- **Type**: `specialPower` (see [SpecialPower documentation](SpecialPower.md))
- **Description**: The special power this button activates
- **Example**: `SpecialPower = USACarpetBomb`

### Display Properties

#### `TextLabel` *(v1.04)*

- **Type**: `AsciiString`
- **Description**: Localized text key displayed on the button
- **Format**: `CONTROLBAR:KeyName` (e.g., `CONTROLBAR:ToolTipGLABuildBlackMarketDomestic`)
- **Example**: `TextLabel = "CONTROLBAR:BuildInfantry"`

#### `DescriptLabel` *(v1.04)*

- **Type**: `AsciiString`
- **Description**: Localized description text key shown in tooltips
- **Format**: `CONTROLBAR:KeyName` (e.g., `CONTROLBAR:ConstructGLADomesticTrade`)
- **Example**: `DescriptLabel = "CONTROLBAR:BuildInfantryDesc"`

#### `PurchasedLabel` *(v1.04)*

- **Type**: `AsciiString`
- **Description**: Localized text key shown when the item is already purchased/owned
- **Format**: `CONTROLBAR:KeyName`
- **Example**: `PurchasedLabel = "CONTROLBAR:AlreadyOwned"`

#### `ConflictingLabel` *(v1.04)*

- **Type**: `AsciiString`
- **Description**: Localized text key shown when there are conflicting requirements
- **Format**: `CONTROLBAR:KeyName`
- **Example**: `ConflictingLabel = "CONTROLBAR:ConflictsWithUpgrade"`

### Overlay Image Properties

#### `ButtonImage` *(v1.04)*

- **Type**: `MappedImage`
- **Description**: Image reference for the button icon (defined as MappedImage, not direct file path)
- **Example**: `ButtonImage = "USAInfantry_ic"`

#### `OverlayImage` *(GMX Upcoming)*

- **Type**: `MappedImage`
- **Description**: Additional overlay image drawn on top of the button for visual indicators (special abilities, status effects, etc.)
- **Default**: Empty (no overlay)
- **Example**: `OverlayImage = "SpecialAbilityOverlay"`
- **Usage**: Used for displaying additional visual information like special abilities, cooldown indicators, or status effects

#### `OverlayImage2` *(GMX Upcoming)*

- **Type**: `MappedImage`
- **Description**: Second additional overlay image drawn on top of the button for visual indicators
- **Default**: Empty (no overlay)
- **Example**: `OverlayImage2 = "StatusEffectOverlay"`
- **Usage**: Used for displaying a second layer of visual information, such as multiple status effects or additional indicators

#### `CursorName` *(v1.04)*

- **Type**: `AsciiString`
- **Description**: Cursor to show when hovering over valid targets
- **Example**: `CursorName = "Attack"`

#### `InvalidCursorName` *(v1.04)*

- **Type**: `AsciiString`
- **Description**: Cursor to show when hovering over invalid targets
- **Example**: `InvalidCursorName = "Invalid"`

#### `ButtonBorderType` *(v1.04)*

- **Type**: `CommandButtonMappedBorderType`
- **Description**: Visual border type for the button
- **Example**: `ButtonBorderType = BUILD`
- **Available Values**: See [ButtonBorderType Values](#buttonbordertype-values-commandbuttonmappedbordertype) section below

#### `RadiusCursorType` *(v1.04)*

- **Type**: `RadiusCursorType`
- **Description**: Type of radius cursor for area-effect commands
- **Example**: `RadiusCursorType = ATTACK`
- **Available Values**: See [RadiusCursorType Values](#radiuscursortype-values) section below

#### `UnitSpecificSound` *(v1.04)*

- **Type**: `AudioEventRTS`
- **Description**: Sound to play when this command is used
- **Example**: `UnitSpecificSound = USAInfantryVoiceAttack`

### Prerequisites and Requirements

#### `RequireElectronics` *(v1.04, Generals Zero Hour only)*

- **Type**: `Bool`
- **Description**: Whether this command requires electronics to function
- **Example**: `RequireElectronics = true`

#### `RequiredUpgradeToAppear` *(v1.04, Generals Zero Hour only)*

- **Type**: `upgrade` (see [Upgrade documentation](Upgrade.md))
- **Description**: Upgrade required for this button to appear
- **Example**: `RequiredUpgradeToAppear = USAAdvancedWeapons`

#### `ConflictUpgradeToDisappear` *(v1.04, Generals Zero Hour only)*

- **Type**: `upgrade` (see [Upgrade documentation](Upgrade.md))
- **Description**: Upgrade that causes this button to disappear
- **Example**: `ConflictUpgradeToDisappear = USAOldWeapons`

#### `RequiredUpgradeToEnable` *(v1.04, Generals Zero Hour only)*

- **Type**: `upgrade` (see [Upgrade documentation](Upgrade.md))
- **Description**: Upgrade required for this button to be enabled
- **Example**: `RequiredUpgradeToEnable = USAAdvancedWeapons`

#### `ConflictUpgradeToDisable` *(v1.04, Generals Zero Hour only)*

- **Type**: `upgrade` (see [Upgrade documentation](Upgrade.md))
- **Description**: Upgrade that disables this button
- **Example**: `ConflictUpgradeToDisable = USAOldWeapons`

#### `EnablePrerequisites` *(v1.04, Generals Zero Hour only)*

- **Type**: `ProductionPrerequisite` block (see [ProductionPrerequisite documentation](ProductionPrerequisite.md))
- **Description**: Prerequisites that must be satisfied for this button to be enabled
- **Format**: Block format with specific prerequisite types
- **Example**:

```
EnablePrerequisites
    Science = SCIENCE_AdvancedWeapons
    Upgrade = Upgrade_InfantryWeapons
End
```

#### `VisiblePrerequisites` *(v1.04, Generals Zero Hour only)*

- **Type**: `ProductionPrerequisite` block (see [ProductionPrerequisite documentation](ProductionPrerequisite.md))
- **Description**: Prerequisites that must be satisfied for this button to be visible
- **Format**: Block format with specific prerequisite types
- **Example**:

```
VisiblePrerequisites
    Science = SCIENCE_AdvancedWeapons
    Upgrade = Upgrade_InfantryWeapons
End
```

### Modifier Key and Click Type Buttons *(v1.04, Generals Zero Hour only)*

#### `LeftClickCtrlButton` *(v1.04, Generals Zero Hour only)*

- **Type**: `AsciiString`
- **Description**: Name of the button that replaces this button when Ctrl+Left-Click is used
- **Example**: `LeftClickCtrlButton = "Command_AdvancedInfantry"`

#### `LeftClickAltButton` *(v1.04, Generals Zero Hour only)*

- **Type**: `AsciiString`
- **Description**: Name of the button that replaces this button when Alt+Left-Click is used
- **Example**: `LeftClickAltButton = "Command_EliteInfantry"`

#### `LeftClickShiftButton` *(v1.04, Generals Zero Hour only)*

- **Type**: `AsciiString`
- **Description**: Name of the button that replaces this button when Shift+Left-Click is used
- **Example**: `LeftClickShiftButton = "Command_VeteranInfantry"`

#### `LeftClickCtrlAltButton` *(v1.04, Generals Zero Hour only)*

- **Type**: `AsciiString`
- **Description**: Name of the button that replaces this button when Ctrl+Alt+Left-Click is used
- **Example**: `LeftClickCtrlAltButton = "Command_HeroInfantry"`

#### `LeftClickCtrlShiftButton` *(v1.04, Generals Zero Hour only)*

- **Type**: `AsciiString`
- **Description**: Name of the button that replaces this button when Ctrl+Shift+Left-Click is used
- **Example**: `LeftClickCtrlShiftButton = "Command_AdvancedVeteranInfantry"`

#### `LeftClickAltShiftButton` *(v1.04, Generals Zero Hour only)*

- **Type**: `AsciiString`
- **Description**: Name of the button that replaces this button when Alt+Shift+Left-Click is used
- **Example**: `LeftClickAltShiftButton = "Command_EliteVeteranInfantry"`

#### `LeftClickCtrlAltShiftButton` *(v1.04, Generals Zero Hour only)*

- **Type**: `AsciiString`
- **Description**: Name of the button that replaces this button when Ctrl+Alt+Shift+Left-Click is used
- **Example**: `LeftClickCtrlAltShiftButton = "Command_UltimateInfantry"`

#### `RightClickButton` *(v1.04, Generals Zero Hour only)*

- **Type**: `AsciiString`
- **Description**: Name of the button that replaces this button when Right-Click is used
- **Example**: `RightClickButton = "Command_InfantryAttack"`

#### `RightClickCtrlButton` *(v1.04, Generals Zero Hour only)*

- **Type**: `AsciiString`
- **Description**: Name of the button that replaces this button when Ctrl+Right-Click is used
- **Example**: `RightClickCtrlButton = "Command_InfantryDefend"`

#### `RightClickAltButton` *(v1.04, Generals Zero Hour only)*

- **Type**: `AsciiString`
- **Description**: Name of the button that replaces this button when Alt+Right-Click is used
- **Example**: `RightClickAltButton = "Command_InfantryPatrol"`

#### `RightClickShiftButton` *(v1.04, Generals Zero Hour only)*

- **Type**: `AsciiString`
- **Description**: Name of the button that replaces this button when Shift+Right-Click is used
- **Example**: `RightClickShiftButton = "Command_InfantryGuard"`

#### `RightClickCtrlAltButton` *(v1.04, Generals Zero Hour only)*

- **Type**: `AsciiString`
- **Description**: Name of the button that replaces this button when Ctrl+Alt+Right-Click is used
- **Example**: `RightClickCtrlAltButton = "Command_InfantrySpecial"`

#### `RightClickCtrlShiftButton` *(v1.04, Generals Zero Hour only)*

- **Type**: `AsciiString`
- **Description**: Name of the button that replaces this button when Ctrl+Shift+Right-Click is used
- **Example**: `RightClickCtrlShiftButton = "Command_InfantryAdvanced"`

#### `RightClickAltShiftButton` *(v1.04, Generals Zero Hour only)*

- **Type**: `AsciiString`
- **Description**: Name of the button that replaces this button when Alt+Shift+Right-Click is used
- **Example**: `RightClickAltShiftButton = "Command_InfantryElite"`

#### `RightClickCtrlAltShiftButton` *(v1.04, Generals Zero Hour only)*

- **Type**: `AsciiString`
- **Description**: Name of the button that replaces this button when Ctrl+Alt+Shift+Right-Click is used
- **Example**: `RightClickCtrlAltShiftButton = "Command_InfantryUltimate"`

### Alternative Command Buttons (Prerequisite-Based Replacement) *(v1.04, Generals Zero Hour only)*

#### `AlternativeButton1` *(v1.04, Generals Zero Hour only)*

- **Type**: `AsciiString`
- **Description**: Name of the first alternative button that completely replaces this button when prerequisites are satisfied
- **Example**: `AlternativeButton1 = "AdvancedInfantry"`

#### `AlternativeButton2` *(v1.04, Generals Zero Hour only)*

- **Type**: `AsciiString`
- **Description**: Name of the second alternative button that completely replaces this button when prerequisites are satisfied
- **Example**: `AlternativeButton2 = "EliteInfantry"`

#### `AlternativeButton3` *(v1.04, Generals Zero Hour only)*

- **Type**: `AsciiString`
- **Description**: Name of the third alternative button that completely replaces this button when prerequisites are satisfied
- **Example**: `AlternativeButton3 = "VeteranInfantry"`

#### `AlternativeButton4` *(v1.04, Generals Zero Hour only)*

- **Type**: `AsciiString`
- **Description**: Name of the fourth alternative button that completely replaces this button when prerequisites are satisfied
- **Example**: `AlternativeButton4 = "HeroInfantry"`

#### `AlternativeButton1Prerequisites` *(v1.04, Generals Zero Hour only)*

- **Type**: `ProductionPrerequisite` block
- **Description**: Prerequisites that must be satisfied for AlternativeButton1 to replace the original
- **Format**: Block format with specific prerequisite types
- **Example**:

```
AlternativeButton1Prerequisites
    Upgrade = Upgrade_SecondEcoL2
    ObjectNotExist = Upgrade_SecondEcoL1
End
```

#### `AlternativeButton2Prerequisites` *(v1.04, Generals Zero Hour only)*

- **Type**: `ProductionPrerequisite` block
- **Description**: Prerequisites that must be satisfied for AlternativeButton2 to replace the original
- **Format**: Block format with specific prerequisite types
- **Example**:

```
AlternativeButton2Prerequisites
    Science = SCIENCE_AdvancedWeapons
    UpgradeNotExist = Upgrade_BasicWeapons
End
```

#### `AlternativeButton3Prerequisites` *(v1.04, Generals Zero Hour only)*

- **Type**: `ProductionPrerequisite` block
- **Description**: Prerequisites that must be satisfied for AlternativeButton3 to replace the original
- **Format**: Block format with specific prerequisite types
- **Example**:

```
AlternativeButton3Prerequisites
    Upgrade = Upgrade_EliteTraining
    Science = SCIENCE_EliteForces
End
```

#### `AlternativeButton4Prerequisites` *(v1.04, Generals Zero Hour only)*

- **Type**: `ProductionPrerequisite` block
- **Description**: Prerequisites that must be satisfied for AlternativeButton4 to replace the original
- **Format**: Block format with specific prerequisite types
- **Example**:

```
AlternativeButton4Prerequisites
    Science = SCIENCE_HeroForces
    Upgrade = Upgrade_HeroTraining
    ObjectNotExist = Upgrade_BasicTraining
End
```

#### Available Prerequisite Types

- **`Upgrade`** - Requires specific upgrade to be researched
- **`ObjectNotExist`** - Requires object/upgrade to not exist
- **`Science`** - Requires specific science to be researched
- **`UpgradeNotExist`** - Requires upgrade to not exist
- **`Object`** - Requires specific object to exist
- **`ObjectCount`** - Requires specific number of objects
- **And many more...** - See [ProductionPrerequisite documentation](#productionprerequisite-types) for complete list

## Enum Value Lists

#### Command Values (GUICommandType)

**Source:** [ControlBar.h](../GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h) - `GUICommandType` enum definition

- **`NONE`** *(v1.04)* - Invalid command
- **`DOZER_CONSTRUCT`** *(v1.04)* - Dozer construct
- **`DOZER_CONSTRUCT_CANCEL`** *(v1.04)* - Cancel a dozer construction process
- **`UNIT_BUILD`** *(v1.04)* - Build a unit
- **`CANCEL_UNIT_BUILD`** *(v1.04)* - Cancel a unit build
- **`PLAYER_UPGRADE`** *(v1.04)* - Put an upgrade that applies to the player in the queue
- **`OBJECT_UPGRADE`** *(v1.04)* - Put an object upgrade in the queue
- **`CANCEL_UPGRADE`** *(v1.04)* - Cancel an upgrade
- **`ATTACK_MOVE`** *(v1.04)* - Attack move command
- **`GUARD`** *(v1.04)* - Guard command
- **`GUARD_WITHOUT_PURSUIT`** *(v1.04)* - Guard command, no pursuit out of guard area
- **`GUARD_FLYING_UNITS_ONLY`** *(v1.04)* - Guard command, ignore nonflyers
- **`STOP`** *(v1.04)* - Stop moving
- **`WAYPOINTS`** *(v1.04)* - Create a set of waypoints for this unit
- **`EXIT_CONTAINER`** *(v1.04)* - An inventory box for a container like a structure or transport
- **`EVACUATE`** *(v1.04)* - Dump all our contents
- **`EXECUTE_RAILED_TRANSPORT`** *(v1.04)* - Execute railed transport sequence
- **`BEACON_DELETE`** *(v1.04)* - Delete a beacon
- **`SET_RALLY_POINT`** *(v1.04)* - Set rally point for a structure
- **`SELL`** *(v1.04)* - Sell a structure
- **`FIRE_WEAPON`** *(v1.04)* - Fire a weapon
- **`SPECIAL_POWER`** *(v1.04)* - Do a special power
- **`PURCHASE_SCIENCE`** *(v1.04)* - Purchase science
- **`HACK_INTERNET`** *(v1.04)* - Gain income from the ether (by hacking the internet)
- **`TOGGLE_OVERCHARGE`** *(v1.04)* - Overcharge command for power plants
- **`POW_RETURN_TO_PRISON`** *(v1.04)* - POW Truck, return to prison
- **`COMBATDROP`** *(v1.04)* - Rappel contents to ground or building
- **`SWITCH_WEAPON`** *(v1.04)* - Switch weapon use
- **`HIJACK_VEHICLE`** *(v1.04)* - Context sensitive command mode
- **`CONVERT_TO_CARBOMB`** *(v1.04)* - Context sensitive command mode
- **`SABOTAGE_BUILDING`** *(v1.04)* - Context sensitive command mode
- **`PICK_UP_PRISONER`** *(v1.04)* - POW Truck assigned to pick up a specific prisoner
- **`PLACE_BEACON`** *(v1.04)* - Context-insensitive command mode
- **`SPECIAL_POWER_FROM_SHORTCUT`** *(v1.04)* - Do a special power from localPlayer's command center, regardless of selection
- **`SPECIAL_POWER_CONSTRUCT`** *(v1.04)* - Do a special power using the construct building interface
- **`SPECIAL_POWER_CONSTRUCT_FROM_SHORTCUT`** *(v1.04)* - Do a shortcut special power using the construct building interface
- **`SELECT_ALL_UNITS_OF_TYPE`** *(v1.04)* - Select all units of type
- **`COMMAND_SWITCH_COMMAND_SET`** *(v1.04)* - Switch command set
- **`COMMAND_SWITCH_COMMAND_SET2`** *(v1.04)* - Switch command set 2
- **`COMMAND_SWITCH_COMMAND_SET3`** *(v1.04)* - Switch command set 3
- **`COMMAND_SWITCH_COMMAND_SET4`** *(v1.04)* - Switch command set 4

#### WeaponSlot Values (WeaponSlotType)

**Source:** [Weapon.h](../GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h) - `WeaponSlotType` enum definition

- **`PRIMARY_WEAPON`** *(v1.04)* - Primary weapon slot
- **`SECONDARY_WEAPON`** *(v1.04)* - Secondary weapon slot
- **`TERTIARY_WEAPON`** *(v1.04)* - Tertiary weapon slot

#### ButtonBorderType Values (CommandButtonMappedBorderType)

**Source:** [ControlBar.h](../GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h) - `CommandButtonMappedBorderType` enum definition

- **`NONE`** *(v1.04)* - No border
- **`BUILD`** *(v1.04)* - Build button border
- **`UPGRADE`** *(v1.04)* - Upgrade button border
- **`ACTION`** *(v1.04)* - Action button border
- **`SYSTEM`** *(v1.04)* - System/special power button border

#### RadiusCursorType Values

**Source:** [ControlBar.h](../GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h) - `RadiusCursorType` enum definition

- **`RADIUSCURSOR_NONE`** *(v1.04)* - No radius cursor
- **`RADIUSCURSOR_ATTACK_DAMAGE_AREA`** *(v1.04)* - Attack damage area radius cursor
- **`RADIUSCURSOR_ATTACK_SCATTER_AREA`** *(v1.04)* - Attack scatter area radius cursor
- **`RADIUSCURSOR_ATTACK_CONTINUE_AREA`** *(v1.04)* - Attack continue area radius cursor
- **`RADIUSCURSOR_GUARD_AREA`** *(v1.04)* - Guard area radius cursor
- **`RADIUSCURSOR_EMERGENCY_REPAIR`** *(v1.04)* - Emergency repair radius cursor
- **`RADIUSCURSOR_FRIENDLY_SPECIALPOWER`** *(v1.04)* - Friendly special power radius cursor
- **`RADIUSCURSOR_OFFENSIVE_SPECIALPOWER`** *(v1.04)* - Offensive special power radius cursor
- **`RADIUSCURSOR_SUPERWEAPON_SCATTER_AREA`** *(v1.04)* - Superweapon scatter area radius cursor

#### CommandOption Enum Values

**Source:** [ControlBar.h](../GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h) - `CommandOption` enum definition

- **`COMMAND_OPTION_NONE`** *(v1.04)* - No special options
- **`NEED_TARGET_ENEMY_OBJECT`** *(v1.04)* - Command needs user to select enemy target
- **`NEED_TARGET_NEUTRAL_OBJECT`** *(v1.04)* - Command needs user to select neutral target
- **`NEED_TARGET_ALLY_OBJECT`** *(v1.04)* - Command needs user to select ally target
- **`NEED_TARGET_PRISONER`** *(v1.04)* - Needs user to select prisoner object
- **`ALLOW_SHRUBBERY_TARGET`** *(v1.04)* - Allow neutral shrubbery as a target
- **`NEED_TARGET_POS`** *(v1.04)* - Command needs user to select target position
- **`NEED_UPGRADE`** *(v1.04)* - Command requires upgrade to be enabled
- **`NEED_SPECIAL_POWER_SCIENCE`** *(v1.04)* - Command requires a science in the special power specified
- **`OK_FOR_MULTI_SELECT`** *(v1.04)* - Command is ok to show when multiple objects selected
- **`CONTEXTMODE_COMMAND`** *(v1.04)* - Context sensitive command mode that requires code to determine cursor validity
- **`CHECK_LIKE`** *(v1.04)* - Dynamically change the UI element push button to be "check like"
- **`ALLOW_MINE_TARGET`** *(v1.04)* - Allow (land)mines as a target
- **`ATTACK_OBJECTS_POSITION`** *(v1.04)* - For weapons that need an object target but attack the position indirectly
- **`OPTION_ONE`** *(v1.04)* - User data option 1
- **`OPTION_TWO`** *(v1.04)* - User data option 2
- **`OPTION_THREE`** *(v1.04)* - User data option 3
- **`NOT_QUEUEABLE`** *(v1.04)* - Option not build queueable (can only build when queue is empty)
- **`SINGLE_USE_COMMAND`** *(v1.04)* - Once used, it can never be used again
- **`COMMAND_FIRED_BY_SCRIPT`** *(v1.04)* - Used only by code to tell special powers they have been fired by a script
- **`SCRIPT_ONLY`** *(v1.04)* - Only a script can use this command (not by users)
- **`IGNORES_UNDERPOWERED`** *(v1.04)* - Button isn't disabled if its object is merely underpowered
- **`USES_MINE_CLEARING_WEAPONSET`** *(v1.04)* - Uses the special mine-clearing weaponset, even if not current
- **`CAN_USE_WAYPOINTS`** *(v1.04)* - Button has option to use a waypoint path
- **`MUST_BE_STOPPED`** *(v1.04)* - Unit must be stopped in order to be able to use button
- **`NEED_UPGRADE_TO_APPEAR`** *(v1.04)* - Command requires upgrade to be enabled

## Examples

### Basic Unit Build Button

```
CommandButton Command_ConstructChinaTank99
  Command       = UNIT_BUILD
  Object        = ChinaTankType99
  TextLabel     = CONTROLBAR:ConstructChinaTank99
  ButtonImage   = Type99_ic_L
  ButtonBorderType        = BUILD
  DescriptLabel           = CONTROLBAR:ToolTipChinaBuildT99
End
```

### Player Upgrade Button

```
CommandButton Command_UpgradeChinaFanaticism
  Command       = PLAYER_UPGRADE
  Upgrade       = Upgrade_Fanaticism
  Science       = SCIENCE_ChinaNationalism
  TextLabel     = CONTROLBAR:UpgradeChinaFanaticism
  ButtonImage   = SSNationalism
  ButtonBorderType        = UPGRADE
  DescriptLabel           = CONTROLBAR:TooltipChinaUpgradeFanaticism
End
```

### Object Upgrade Button

```
CommandButton Command_UpgradeEMPMines
  Command       = OBJECT_UPGRADE
  Upgrade       = Upgrade_ChinaEMPMines
  TextLabel     = CONTROLBAR:UpgradeEMPMines
  ButtonImage   = SNEMPMine
  ButtonBorderType        = UPGRADE
  DescriptLabel           = CONTROLBAR:ToolTipUpgradeChinaEMPMines
End
```

### Special Power Button

```
CommandButton Command_China_RadarPusleEmission
  Command           = FIRE_WEAPON
  MaxShotsToFire    = 9999
  WeaponSlot        = PRIMARY_WEAPON
  SpecialPower      = Radar_FE
  Options           = NEED_SPECIAL_POWER_SCIENCE NEED_TARGET_POS CONTEXTMODE_COMMAND OK_FOR_MULTI_SELECT
  TextLabel         = CONTROLBAR:RadarDirectionalPulseEmission
  ButtonBorderType  = ACTION
  ButtonImage       = China_PusleEmission
  DescriptLabel     = CONTROLBAR:ToolTipRadarDirectionalPulseEmission
  CursorName        = LaserGuidedMissiles
  RadiusCursorType  = RADIUSCURSOR_OFFENSIVE_SPECIALPOWER
End
```

### Weapon Switching Button

```
CommandButton Command_HJ9firemode1
  Command = SWITCH_WEAPON
  WeaponSlot = PRIMARY_WEAPON
  Options = CHECK_LIKE OK_FOR_MULTI_SELECT
  TextLabel = CONTROLBAR:HJ9Switchtotosfiremode1
  ButtonImage  = HJ9FM1_ic
  ButtonBorderType = ACTION
  DescriptLabel  = CONTROLBAR:ToolTipHJ9Switchtotosfiremode1
End
```

### Science Purchase Button

```
CommandButton Command_PurchaseScienceNationalism
  Command           = PURCHASE_SCIENCE
  Science           = SCIENCE_ChinaNationalism
  ButtonImage       = ChinaNationalism_ic
  ButtonBorderType  = UPGRADE
  UnitSpecificSound = UnitPromoted
End
```

### Complex Prerequisites Example

```
CommandButton Command_UpgradeChinaHelixPropagandaTower
  Command       = OBJECT_UPGRADE
  Upgrade       = Upgrade_GenericObject600
  Science       = SCIENCE_ChinaNationalism
  Options       = OK_FOR_MULTI_SELECT NOT_QUEUEABLE
  TextLabel     = CONTROLBAR:UpgradeChinaHelixPropagandaTower
  ButtonImage   = SNHelixUp02
  ButtonBorderType        = UPGRADE
  DescriptLabel           = CONTROLBAR:TooltipUpgradeChinaHelixPropagandaTower
  UnitSpecificSound       = HelixVoiceModeSpeakerTower
End
```

### Command Button with Overlay Images (New Feature)

```
CommandButton Command_SpecialUnitWithOverlays
  Command       = UNIT_BUILD
  Object        = SpecialEliteUnit
  TextLabel     = CONTROLBAR:BuildSpecialEliteUnit
  ButtonImage   = EliteUnit_ic_L
  OverlayImage  = VeterancyOverlay
  OverlayImage2 = SpecialAbilityOverlay
  ButtonBorderType        = BUILD
  DescriptLabel           = CONTROLBAR:ToolTipBuildSpecialEliteUnit
End
```

### Alternative Command Buttons (New Feature)

```
CommandButton Command_ConstructChinaInfantryRedguard
  Command       = UNIT_BUILD
  Object        = ChinaInfantryRedguard
  TextLabel     = CONTROLBAR:ConstructChinaInfantryRedguard
  ButtonImage   = Redguard_ic_L
  ButtonBorderType        = BUILD
  DescriptLabel           = CONTROLBAR:ToolTipChinaBuildRedguard
  
  ; Alternative buttons based on prerequisites
  AlternativeButton1 = "Command_ConstructChinaInfantryRedguardMMF"
  AlternativeButton1Prerequisites
      Upgrade = Upgrade_MMF
      Science = SCIENCE_AdvancedInfantry
  End
  
  ; Alternative buttons for modifier keys (existing feature)
  RightClickButton = "Command_ConstructChinaInfantryRedguard"
  RightClickCtrlButton = "Command_ConstructChinaInfantryRedguardMMF"
End
```

### Modifier Key Button Example

```
CommandButton Command_ConstructChinaInfantryRedguard
  Command       = UNIT_BUILD
  Object        = ChinaInfantryRedguard
  TextLabel     = CONTROLBAR:ConstructChinaInfantryRedguard
  ButtonImage   = Redguard_ic_L
  ButtonBorderType        = BUILD
  DescriptLabel           = CONTROLBAR:ToolTipChinaBuildRedguard
  
  ; Different behavior for modifier keys
  RightClickButton = "Command_ConstructChinaInfantryRedguard"
  RightClickCtrlButton = "Command_ConstructChinaInfantryRedguardMMF"
  RightClickAltButton = "Command_ConstructChinaInfantryRedguardDFF"
End
```

### Fire Weapon Button

```
CommandButton Command_DF21FireWeapon
  Command             = FIRE_WEAPON
  WeaponSlot          = SECONDARY_WEAPON
  MaxShotsToFire      = 1
  Options             = NEED_SPECIAL_POWER_SCIENCE NEED_TARGET_POS CONTEXTMODE_COMMAND OK_FOR_MULTI_SELECT
  TextLabel           = CONTROLBAR:MissileAttack
  ButtonImage         = BallisticMissileFire_L
  ButtonBorderType    = ACTION
  SpecialPower        = DF21GroundAttack
  RadiusCursorType    = RADIUSCURSOR_ATTACK_DAMAGE_AREA
  UnitSpecificSound   = DF21Launch
End
```

## Best Practices

### Command Button Design

1. **Use descriptive names** - Command button names should clearly indicate their function
2. **Consistent naming conventions** - Follow established patterns (e.g., `Command_Construct`, `Command_Upgrade`)
3. **Proper localization** - Always use `CONTROLBAR:KeyName` format for text labels
4. **Appropriate button borders** - Use correct border types (BUILD, UPGRADE, ACTION, SYSTEM)

### Prerequisites and Requirements

1. **Logical prerequisite chains** - Design prerequisites that make sense in gameplay progression
2. **Clear conflict resolution** - Use `ConflictUpgradeToDisable` to prevent conflicting upgrades
3. **Progressive unlocking** - Use `RequiredUpgradeToAppear` for natural progression
4. **Block format consistency** - Always use proper block format for prerequisites

### Alternative Buttons

1. **Meaningful alternatives** - Alternative buttons should provide clear gameplay benefits
2. **Consistent prerequisite patterns** - Use similar prerequisite structures across related buttons
3. **Modifier key logic** - Design modifier key combinations that are intuitive for players
4. **Performance consideration** - Don't overuse alternative buttons as they increase complexity

### Display and UI

1. **Clear visual indicators** - Use appropriate button images and border types
2. **Helpful tooltips** - Provide descriptive text that explains button functionality
3. **Consistent cursor behavior** - Use appropriate cursor types for different command types
4. **Sound feedback** - Add unit-specific sounds for better player feedback
5. **Overlay Image Guidelines** - Use overlay images sparingly to avoid visual clutter
   - Reserve `OverlayImage` for primary additional indicators (veterancy, special abilities)
   - Use `OverlayImage2` for secondary indicators (status effects, cooldowns)
   - Ensure overlay images are semi-transparent or small enough not to obscure the main button
   - Test overlay combinations to ensure they remain readable

### Performance and Maintenance

1. **Efficient prerequisite checks** - Keep prerequisite logic simple and fast
2. **Avoid circular dependencies** - Ensure prerequisite chains don't create loops
3. **Documentation** - Comment complex prerequisite logic for future maintenance
4. **Testing** - Test all alternative button combinations and prerequisite scenarios

## Template

```ini
CommandButton CommandButtonName
    Command = NONE                           ; // Command type (UNIT_BUILD/PLAYER_UPGRADE/etc.) *(v1.04)*
    Object = ObjectName                      ; // Object to create or target *(v1.04)*
    Upgrade = UpgradeName                    ; // Upgrade to research *(v1.04)*
    SpecialPower = SpecialPowerName          ; // Special power to activate *(v1.04)*
    Science = ScienceName                    ; // Science requirement *(v1.04)*
    WeaponSlot = PRIMARY_WEAPON              ; // Weapon slot to use *(v1.04)*
    MaxShotsToFire = 1                       ; // Maximum shots to fire *(v1.04)*
    Options = NONE                           ; // Command options (NEED_TARGET_POS/etc.) *(v1.04)*
    TextLabel = CONTROLBAR:ButtonText        ; // Button text label *(v1.04)*
    DescriptLabel = CONTROLBAR:ButtonDesc    ; // Button description *(v1.04)*
    ButtonImage = ButtonIcon                 ; // Button icon image *(v1.04)*
    OverlayImage = OverlayIcon1              ; // First overlay image *(GMX Upcoming)*
    OverlayImage2 = OverlayIcon2             ; // Second overlay image *(GMX Upcoming)*
    ButtonBorderType = BUILD                 ; // Button border type *(v1.04)*
    CursorName = Attack                      ; // Valid target cursor *(v1.04)*
    InvalidCursorName = Invalid              ; // Invalid target cursor *(v1.04)*
    RadiusCursorType = RADIUSCURSOR_NONE     ; // Radius cursor type *(v1.04)*
    UnitSpecificSound = SoundEvent           ; // Sound to play *(v1.04)*
    ; Zero Hour only properties:
    RequireElectronics = false               ; // Requires electronics *(v1.04, Generals Zero Hour only)*
    RequiredUpgradeToAppear = UpgradeName    ; // Upgrade required to appear *(v1.04, Generals Zero Hour only)*
    ConflictUpgradeToDisappear = UpgradeName ; // Upgrade that makes button disappear *(v1.04, Generals Zero Hour only)*
    RequiredUpgradeToEnable = UpgradeName    ; // Upgrade required to enable *(v1.04, Generals Zero Hour only)*
    ConflictUpgradeToDisable = UpgradeName   ; // Upgrade that disables button *(v1.04, Generals Zero Hour only)*
    LeftClickCtrlButton = ButtonName         ; // Ctrl+Left-Click alternative *(v1.04, Generals Zero Hour only)*
    LeftClickAltButton = ButtonName          ; // Alt+Left-Click alternative *(v1.04, Generals Zero Hour only)*
    LeftClickShiftButton = ButtonName        ; // Shift+Left-Click alternative *(v1.04, Generals Zero Hour only)*
    RightClickButton = ButtonName            ; // Right-Click alternative *(v1.04, Generals Zero Hour only)*
    AlternativeButton1 = ButtonName          ; // First alternative button *(v1.04, Generals Zero Hour only)*
    AlternativeButton2 = ButtonName          ; // Second alternative button *(v1.04, Generals Zero Hour only)*
    AlternativeButton3 = ButtonName          ; // Third alternative button *(v1.04, Generals Zero Hour only)*
    AlternativeButton4 = ButtonName          ; // Fourth alternative button *(v1.04, Generals Zero Hour only)*
End
```

## Notes

- CommandButtons provide user interface elements for player actions and game commands
- The configuration manages button appearance, behavior, and functionality for different game contexts
- Command operations create interactive elements that connect player input to game functionality
- Command management ensures intuitive and responsive user interface experiences
- This configuration is essential for user interface design and player interaction
- Command coordination creates consistent button behavior across different game modes
- Button properties control visual appearance, text labels, and interaction behavior
- Prerequisite systems manage button availability based on game state and player progress
- Alternative buttons provide dynamic button replacement based on modifiers or prerequisites
- Command options control specific behaviors like target requirements and multi-select support
- Button images are defined as MappedImage references, not direct file paths
- All text labels support localization through the game's text system
- Each CommandButton must have a unique name across all INI files
- CommandButtons are defined in `.ini` files within the game's data directories in a root folder called "CommandButton"
- **GMX Feature**: Multiple `.ini` files in the CommandButton directory are automatically merged at runtime (vs. vanilla single CommandButton.ini file)
- Multiple CommandButtons can be grouped into [CommandSets](CommandSet.md) for different contexts
- **Version Compatibility**: All properties marked with `*(v1.04)*` are available in Generals Zero Hour; `*(v1.04, Generals Zero Hour only)*` indicates features unique to Zero Hour vs. original Generals
- CommandButtons integrate with the game's command system for executing player actions
- Button borders provide visual categorization (BUILD, UPGRADE, ACTION, SYSTEM)
- Cursor systems provide visual feedback for valid and invalid targets
- Sound systems provide audio feedback for button interactions

## Source Files

**Base Class:** [CommandButton](../../GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h)
- Header: [`GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h`](../../GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp)

## Changes History

- **GMX Upcoming**: Added `OverlayImage` and `OverlayImage2` properties for additional visual indicators on command buttons
- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated - Updated with Overlay Image Properties
- **Last Updated**: 27/06/2025 by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet
