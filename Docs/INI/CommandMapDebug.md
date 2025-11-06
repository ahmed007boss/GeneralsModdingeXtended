# CommandMapDebug INI Documentation

## Overview

The `CommandMapDebug` INI file contains debug-specific keyboard and input mapping configuration settings for development and testing commands. CommandMapDebug extends the regular CommandMap system with additional debug commands that are only available in debug builds, providing developers with specialized tools for testing, debugging, and development workflows.

## Usage

CommandMapDebug configurations are used to map keyboard keys and modifier combinations to debug-specific commands and development tools. This is a **debug-only configuration file** that extends the regular CommandMap system. The debug command mapping system provides developers with specialized input handling for testing scenarios and development workflows.

**Limitations**:
- CommandMapDebug only works in debug builds (RTS_DEBUG defined)
- Debug commands are limited to development and testing scenarios
- CommandMapDebug cannot override system-level input restrictions
- Debug input mappings depend on proper debug game message type definitions

**Conditions**:
- CommandMapDebug manages debug input handling across all game modes
- The configuration handles debug key bindings for different development contexts
- Debug command operations provide specialized testing and development tools
- Debug command management creates flexible development input systems
- **Multiple instances behavior**: Each debug command message type can have only one key mapping, but multiple debug commands can share the same key with different modifiers

**Dependencies**:
- Uses debug GameMessage types for command identification
- Integrates with the debug input system for keyboard and mouse handling
- Referenced by the MetaEventTranslator for debug input processing
- Requires RTS_DEBUG build flag to be active

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
- [Debug Key Values](#debug-key-values)
- [Transition Values](#transition-values)
- [Modifier Values](#modifier-values)
- [Debug Category Values](#debug-category-values)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Debug Command Mapping Properties *(v1.04)*

#### `Key` *(v1.04)*
- **Type**: `MappableKeyType` (see [Debug Key Values](#debug-key-values) section)
- **Description**: Defines the keyboard key that triggers this debug command. Can be any valid keyboard key including function keys, number pad keys, and special keys.
- **Default**: `MK_NONE` (no key assigned)
- **Example**: `Key = KEY_F1` // F1 key triggers this debug command

#### `Transition` *(v1.04)*
- **Type**: `MappableKeyTransition` (see [Transition Values](#transition-values) section)
- **Description**: Defines when the debug command is triggered based on key state changes. Controls whether the command fires on key press, release, or double-click.
- **Default**: `DOWN` (command triggers on key press)
- **Example**: `Transition = UP` // Debug command triggers when key is released

#### `Modifiers` *(v1.04)*
- **Type**: `MappableKeyModState` (see [Modifier Values](#modifier-values) section)
- **Description**: Defines required modifier key combinations (Ctrl, Alt, Shift) that must be held when the main key is pressed. Multiple modifiers can be combined.
- **Default**: `NONE` (no modifiers required)
- **Example**: `Modifiers = CTRL_ALT` // Debug command requires Ctrl+Alt+main key

#### `UseableIn` *(v1.04)*
- **Type**: `CommandUsableInType` (see CommandUsableIn documentation)
- **Description**: Defines in which game contexts this debug command can be used. Controls whether the command works in-game, in menus, during replays, etc.
- **Default**: `COMMANDUSABLE_NONE` (command disabled)
- **Example**: `UseableIn = COMMANDUSABLE_GAME` // Debug command works only during gameplay

#### `Category` *(v1.04)*
- **Type**: `MappableKeyCategories` (see [Debug Category Values](#debug-category-values) section)
- **Description**: Defines the debug category this command belongs to for organization in key mapping dialogs and documentation.
- **Default**: `CATEGORY_DEBUG` (debug category)
- **Example**: `Category = CATEGORY_DEBUG` // Debug command is in debug category

#### `Description` *(v1.04)*
- **Type**: `UnicodeString` (translated text key)
- **Description**: Provides a detailed description of what this debug command does, displayed in help text and key mapping dialogs.
- **Default**: Empty string
- **Example**: `Description = GUI:DebugCommandDescription` // References translated description text

#### `DisplayName` *(v1.04)*
- **Type**: `UnicodeString` (translated text key)
- **Description**: Provides a short display name for this debug command, shown in key mapping dialogs and interface elements.
- **Default**: Empty string
- **Example**: `DisplayName = GUI:DebugCommandDisplayName` // References translated display name

## Debug Key Values *(v1.04)*

The Key property accepts the same keyboard keys as regular CommandMap (see [CommandMap Key Values](CommandMap.md#key-values) section), but debug commands typically use:

### Debug-Specific Key Patterns
- **Function Keys (F1-F12)**: Commonly used for debug commands
- **Alt Combinations**: Alt+key combinations for debug-only commands
- **Ctrl+Alt Combinations**: Advanced debug commands
- **Special Keys**: Keys not used in regular gameplay

## Transition Values *(v1.04)*

The Transition property accepts the same values as regular CommandMap:

- **`DOWN`** *(v1.04)* - Debug command triggers when key is pressed down
- **`UP`** *(v1.04)* - Debug command triggers when key is released
- **`DOUBLEDOWN`** *(v1.04)* - Debug command triggers on double-click (two quick presses)

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

## Debug Category Values *(v1.04)*

The Category property accepts the same values as regular CommandMap, but debug commands typically use:

- **`CATEGORY_DEBUG`** *(v1.04)* - Debug and development commands (most common)
- **`CATEGORY_CONTROL`** *(v1.04)* - Debug game control commands
- **`CATEGORY_INTERFACE`** *(v1.04)* - Debug interface commands
- **`CATEGORY_MISC`** *(v1.04)* - Miscellaneous debug commands

## Examples

### Debug Demo Commands
```ini
CommandMapDebug MSG_META_DEMO_REMOVE_PREREQ
    Key = KEY_P
    Transition = DOWN
    Modifiers = ALT
    UseableIn = COMMANDUSABLE_GAME
    Category = CATEGORY_DEBUG
    Description = GUI:DemoRemovePrereqDescription
    DisplayName = GUI:DemoRemovePrereq
End

CommandMapDebug MSG_META_DEMO_FREE_BUILD
    Key = KEY_B
    Transition = DOWN
    Modifiers = ALT
    UseableIn = COMMANDUSABLE_GAME
    Category = CATEGORY_DEBUG
    Description = GUI:DemoFreeBuildDescription
    DisplayName = GUI:DemoFreeBuild
End
```

### Debug Testing Commands
```ini
CommandMapDebug MSG_META_DEBUG_TOGGLE_WIREFRAME
    Key = KEY_F1
    Transition = DOWN
    Modifiers = CTRL
    UseableIn = COMMANDUSABLE_EVERYWHERE
    Category = CATEGORY_DEBUG
    Description = GUI:DebugToggleWireframeDescription
    DisplayName = GUI:DebugToggleWireframe
End

CommandMapDebug MSG_META_DEBUG_SHOW_FPS
    Key = KEY_F2
    Transition = DOWN
    Modifiers = CTRL
    UseableIn = COMMANDUSABLE_EVERYWHERE
    Category = CATEGORY_DEBUG
    Description = GUI:DebugShowFPSDescription
    DisplayName = GUI:DebugShowFPS
End
```

### Debug Development Commands
```ini
CommandMapDebug MSG_META_DEBUG_TOGGLE_CONSOLE
    Key = KEY_GRAVE
    Transition = DOWN
    Modifiers = NONE
    UseableIn = COMMANDUSABLE_EVERYWHERE
    Category = CATEGORY_DEBUG
    Description = GUI:DebugToggleConsoleDescription
    DisplayName = GUI:DebugToggleConsole
End

CommandMapDebug MSG_META_DEBUG_RELOAD_SCRIPTS
    Key = KEY_R
    Transition = DOWN
    Modifiers = CTRL_ALT
    UseableIn = COMMANDUSABLE_EVERYWHERE
    Category = CATEGORY_DEBUG
    Description = GUI:DebugReloadScriptsDescription
    DisplayName = GUI:DebugReloadScripts
End
```

## Template

```ini
CommandMapDebug MSG_META_DEBUG_COMMAND_NAME
    Key = MK_NONE                        ; // Keyboard key for this debug command *(v1.04)*
    Transition = DOWN                    ; // When command triggers (DOWN/UP/DOUBLEDOWN) *(v1.04)*
    Modifiers = NONE                     ; // Required modifier keys (NONE/CTRL/ALT/SHIFT/combinations) *(v1.04)*
    UseableIn = COMMANDUSABLE_NONE       ; // Where command can be used *(v1.04)*
    Category = CATEGORY_DEBUG            ; // Debug command category for organization *(v1.04)*
    Description = GUI:DebugCommandDesc   ; // Detailed description text key *(v1.04)*
    DisplayName = GUI:DebugCommandName   ; // Short display name text key *(v1.04)*
End
```

## Notes

- CommandMapDebug provides specialized input handling for development and testing workflows
- The configuration manages debug key bindings for different development contexts
- Debug command operations create flexible and powerful development tools
- Debug command management ensures efficient testing and debugging experiences
- This configuration is essential for development workflow optimization
- Debug command coordination creates consistent input behavior across different debug scenarios
- Debug key mappings can be reassigned to different keys for personal preference
- Modifier combinations allow multiple debug commands to share the same main key
- Transition settings control when debug commands trigger (press, release, double-click)
- UseableIn settings prevent debug commands from interfering with inappropriate contexts
- Category organization helps developers find and understand related debug commands
- Description and DisplayName properties provide clear debug command information
- CommandMapDebug templates are reusable and can be applied to multiple debug game message types
- The debug command mapping system works in conjunction with the debug input system
- Debug key mappings are only available in debug builds (RTS_DEBUG defined)
- Debug commands should not conflict with regular gameplay commands
- Alt and Ctrl+Alt combinations are commonly used for debug commands
- Function keys (F1-F12) are popular choices for debug commands
- Debug commands are typically organized in the CATEGORY_DEBUG category
- The debug command mapping system integrates with the regular CommandMap system
- Debug commands can be disabled by setting UseableIn to COMMANDUSABLE_NONE
- Debug command descriptions should clearly indicate their debug nature
- Debug commands may have different behavior in debug vs release builds

## Source Files

**Base Class:** [MetaMapRec](../../GeneralsMD/Code/GameEngine/Include/GameClient/MetaEvent.h)
- Header: [`GeneralsMD/Code/GameEngine/Include/GameClient/MetaEvent.h`](../../GeneralsMD/Code/GameEngine/Include/GameClient/MetaEvent.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameClient/MessageStream/MetaEvent.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameClient/MessageStream/MetaEvent.cpp)
- INI Parser: [`GeneralsMD/Code/GameEngine/Source/Common/INI/INI.cpp`](../../GeneralsMD/Code/GameEngine/Source/Common/INI/INI.cpp)
- Debug Loader: [`GeneralsMD/Code/GameEngine/Source/Common/GameEngine.cpp`](../../GeneralsMD/Code/GameEngine/Source/Common/GameEngine.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet
