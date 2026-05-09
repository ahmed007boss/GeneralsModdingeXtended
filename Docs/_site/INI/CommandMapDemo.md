# CommandMapDemo INI Documentation

## Overview

The `CommandMapDemo` INI file contains demo-specific keyboard and input mapping configuration settings for demonstration and presentation modes. CommandMapDemo extends the regular CommandMap system with additional demo commands that are available when debug cheats are enabled in release builds, providing demonstration tools for showcasing game features and capabilities.

## Usage

CommandMapDemo configurations are used to map keyboard keys and modifier combinations to demo-specific commands and presentation tools. This is a **demo-only configuration file** that extends the regular CommandMap system. The demo command mapping system provides demonstration tools for showcasing game features, testing scenarios, and presentation workflows.

**Limitations**:
- CommandMapDemo only works when `_ALLOW_DEBUG_CHEATS_IN_RELEASE` is defined
- Demo commands are limited to demonstration and presentation scenarios
- CommandMapDemo cannot override system-level input restrictions
- Demo input mappings depend on proper demo game message type definitions

**Conditions**:
- CommandMapDemo manages demo input handling across all game modes
- The configuration handles demo key bindings for different demonstration contexts
- Demo command operations provide specialized demonstration and presentation tools
- Demo command management creates flexible demonstration input systems
- **Multiple instances behavior**: Each demo command message type can have only one key mapping, but multiple demo commands can share the same key with different modifiers

**Dependencies**:
- Uses demo GameMessage types for command identification
- Integrates with the demo input system for keyboard and mouse handling
- Referenced by the MetaEventTranslator for demo input processing
- Requires `_ALLOW_DEBUG_CHEATS_IN_RELEASE` build flag to be active

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
- [Demo Key Values](#demo-key-values)
- [Transition Values](#transition-values)
- [Modifier Values](#modifier-values)
- [Demo Category Values](#demo-category-values)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Demo Command Mapping Properties *(v1.04)*

#### `Key` *(v1.04)*
- **Type**: `MappableKeyType` (see [Demo Key Values](#demo-key-values) section)
- **Description**: Defines the keyboard key that triggers this demo command. Can be any valid keyboard key including function keys, number pad keys, and special keys.
- **Default**: `MK_NONE` (no key assigned)
- **Example**: `Key = KEY_F1` // F1 key triggers this demo command

#### `Transition` *(v1.04)*
- **Type**: `MappableKeyTransition` (see [Transition Values](#transition-values) section)
- **Description**: Defines when the demo command is triggered based on key state changes. Controls whether the command fires on key press, release, or double-click.
- **Default**: `DOWN` (command triggers on key press)
- **Example**: `Transition = UP` // Demo command triggers when key is released

#### `Modifiers` *(v1.04)*
- **Type**: `MappableKeyModState` (see [Modifier Values](#modifier-values) section)
- **Description**: Defines required modifier key combinations (Ctrl, Alt, Shift) that must be held when the main key is pressed. Multiple modifiers can be combined.
- **Default**: `NONE` (no modifiers required)
- **Example**: `Modifiers = CTRL_ALT` // Demo command requires Ctrl+Alt+main key

#### `UseableIn` *(v1.04)*
- **Type**: `CommandUsableInType` (see CommandUsableIn documentation)
- **Description**: Defines in which game contexts this demo command can be used. Controls whether the command works in-game, in menus, during replays, etc.
- **Default**: `COMMANDUSABLE_NONE` (command disabled)
- **Example**: `UseableIn = COMMANDUSABLE_GAME` // Demo command works only during gameplay

#### `Category` *(v1.04)*
- **Type**: `MappableKeyCategories` (see [Demo Category Values](#demo-category-values) section)
- **Description**: Defines the demo category this command belongs to for organization in key mapping dialogs and documentation.
- **Default**: `CATEGORY_DEBUG` (debug category)
- **Example**: `Category = CATEGORY_DEBUG` // Demo command is in debug category

#### `Description` *(v1.04)*
- **Type**: `UnicodeString` (translated text key)
- **Description**: Provides a detailed description of what this demo command does, displayed in help text and key mapping dialogs.
- **Default**: Empty string
- **Example**: `Description = GUI:DemoCommandDescription` // References translated description text

#### `DisplayName` *(v1.04)*
- **Type**: `UnicodeString` (translated text key)
- **Description**: Provides a short display name for this demo command, shown in key mapping dialogs and interface elements.
- **Default**: Empty string
- **Example**: `DisplayName = GUI:DemoCommandDisplayName` // References translated display name

## Demo Key Values *(v1.04)*

The Key property accepts the same keyboard keys as regular CommandMap (see [CommandMap Key Values](CommandMap.md#key-values) section), but demo commands typically use:

### Demo-Specific Key Patterns
- **Function Keys (F1-F12)**: Commonly used for demo commands
- **Alt Combinations**: Alt+key combinations for demo-only commands
- **Ctrl+Alt Combinations**: Advanced demo commands
- **Special Keys**: Keys not used in regular gameplay

## Transition Values *(v1.04)*

The Transition property accepts the same values as regular CommandMap:

- **`DOWN`** *(v1.04)* - Demo command triggers when key is pressed down
- **`UP`** *(v1.04)* - Demo command triggers when key is released
- **`DOUBLEDOWN`** *(v1.04)* - Demo command triggers on double-click (two quick presses)

## Modifier Values *(v1.04)*

The Modifiers property accepts the same values as regular CommandMap:

- **`NONE`** *(v1.04)* - No modifier keys required
- **`CTRL`** *(v1.04)* - Ctrl key must be held
- **`ALT`** *(v1.04)* - Alt key must be held
- **`SHIFT`** *(v1.04)* - Shift key must be held
- **`CTRL_ALT`** *(v1.04)* - Both Ctrl and Alt keys must be held
- **`SHIFT_CTRL`** *(v1.04)* - Both Shift and Ctrl keys must be held
- **`SHIFT_ALT`** *(v1.04)* - Both Shift and Alt keys must be held
- **`SHIFT_ALT_CTRL`** *(v1.04)* - All three modifier keys must be held

## Demo Category Values *(v1.04)*

The Category property accepts the same values as regular CommandMap, but demo commands typically use:

- **`CATEGORY_DEBUG`** *(v1.04)* - Demo and presentation commands (most common)
- **`CATEGORY_CONTROL`** *(v1.04)* - Demo game control commands
- **`CATEGORY_INTERFACE`** *(v1.04)* - Demo interface commands
- **`CATEGORY_MISC`** *(v1.04)* - Miscellaneous demo commands

## Examples

### Demo Presentation Commands
```ini
CommandMapDemo MSG_META_DEMO_SHOWCASE_UNITS
    Key = KEY_F1
    Transition = DOWN
    Modifiers = CTRL
    UseableIn = COMMANDUSABLE_EVERYWHERE
    Category = CATEGORY_DEBUG
    Description = GUI:DemoShowcaseUnitsDescription
    DisplayName = GUI:DemoShowcaseUnits
End

CommandMapDemo MSG_META_DEMO_TOGGLE_FOG
    Key = KEY_F2
    Transition = DOWN
    Modifiers = CTRL
    UseableIn = COMMANDUSABLE_EVERYWHERE
    Category = CATEGORY_DEBUG
    Description = GUI:DemoToggleFogDescription
    DisplayName = GUI:DemoToggleFog
End
```

### Demo Testing Commands
```ini
CommandMapDemo MSG_META_DEMO_INSTANT_BUILD
    Key = KEY_B
    Transition = DOWN
    Modifiers = CTRL_ALT
    UseableIn = COMMANDUSABLE_GAME
    Category = CATEGORY_DEBUG
    Description = GUI:DemoInstantBuildDescription
    DisplayName = GUI:DemoInstantBuild
End

CommandMapDemo MSG_META_DEMO_UNLIMITED_RESOURCES
    Key = KEY_M
    Transition = DOWN
    Modifiers = CTRL_ALT
    UseableIn = COMMANDUSABLE_GAME
    Category = CATEGORY_DEBUG
    Description = GUI:DemoUnlimitedResourcesDescription
    DisplayName = GUI:DemoUnlimitedResources
End
```

### Demo Feature Commands
```ini
CommandMapDemo MSG_META_DEMO_SPAWN_UNITS
    Key = KEY_S
    Transition = DOWN
    Modifiers = CTRL
    UseableIn = COMMANDUSABLE_GAME
    Category = CATEGORY_DEBUG
    Description = GUI:DemoSpawnUnitsDescription
    DisplayName = GUI:DemoSpawnUnits
End

CommandMapDemo MSG_META_DEMO_TOGGLE_GODMODE
    Key = KEY_G
    Transition = DOWN
    Modifiers = CTRL
    UseableIn = COMMANDUSABLE_GAME
    Category = CATEGORY_DEBUG
    Description = GUI:DemoToggleGodmodeDescription
    DisplayName = GUI:DemoToggleGodmode
End
```

## Template

```ini
CommandMapDemo MSG_META_DEMO_COMMAND_NAME
    Key = MK_NONE                        ; // Keyboard key for this demo command *(v1.04)*
    Transition = DOWN                    ; // When command triggers (DOWN/UP/DOUBLEDOWN) *(v1.04)*
    Modifiers = NONE                     ; // Required modifier keys (NONE/CTRL/ALT/SHIFT/combinations) *(v1.04)*
    UseableIn = COMMANDUSABLE_NONE       ; // Where command can be used *(v1.04)*
    Category = CATEGORY_DEBUG            ; // Demo command category for organization *(v1.04)*
    Description = GUI:DemoCommandDesc    ; // Detailed description text key *(v1.04)*
    DisplayName = GUI:DemoCommandName    ; // Short display name text key *(v1.04)*
End
```

## Notes

- CommandMapDemo provides specialized input handling for demonstration and presentation workflows
- The configuration manages demo key bindings for different demonstration contexts
- Demo command operations create flexible and powerful demonstration tools
- Demo command management ensures efficient presentation and testing experiences
- This configuration is essential for demonstration workflow optimization
- Demo command coordination creates consistent input behavior across different demo scenarios
- Demo key mappings can be reassigned to different keys for personal preference
- Modifier combinations allow multiple demo commands to share the same main key
- Transition settings control when demo commands trigger (press, release, double-click)
- UseableIn settings prevent demo commands from interfering with inappropriate contexts
- Category organization helps developers find and understand related demo commands
- Description and DisplayName properties provide clear demo command information
- CommandMapDemo templates are reusable and can be applied to multiple demo game message types
- The demo command mapping system works in conjunction with the demo input system
- Demo key mappings are only available when `_ALLOW_DEBUG_CHEATS_IN_RELEASE` is defined
- Demo commands should not conflict with regular gameplay commands
- Alt and Ctrl+Alt combinations are commonly used for demo commands
- Function keys (F1-F12) are popular choices for demo commands
- Demo commands are typically organized in the CATEGORY_DEBUG category
- The demo command mapping system integrates with the regular CommandMap system
- Demo commands can be disabled by setting UseableIn to COMMANDUSABLE_NONE
- Demo command descriptions should clearly indicate their demo nature
- Demo commands may have different behavior in demo vs regular builds

## Source Files

**Base Class:** [MetaMapRec](../GeneralsMD/Code/GameEngine/Include/GameClient/MetaEvent.h)
- Header: [`GeneralsMD/Code/GameEngine/Include/GameClient/MetaEvent.h`](../GeneralsMD/Code/GameEngine/Include/GameClient/MetaEvent.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameClient/MessageStream/MetaEvent.cpp`](../GeneralsMD/Code/GameEngine/Source/GameClient/MessageStream/MetaEvent.cpp)
- INI Parser: [`GeneralsMD/Code/GameEngine/Source/Common/INI/INI.cpp`](../GeneralsMD/Code/GameEngine/Source/Common/INI/INI.cpp)
- Demo Loader: [`GeneralsMD/Code/GameEngine/Source/Common/GameEngine.cpp`](../GeneralsMD/Code/GameEngine/Source/Common/GameEngine.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet
