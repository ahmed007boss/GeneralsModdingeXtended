# CommandMap INI Documentation

## Overview

The `CommandMap` class represents keyboard and mouse input mapping configurations for meta-commands (system commands) in the game. It maps physical key combinations to game actions like pause, fast forward, frame stepping, and other system-level controls that affect gameplay, replay, and interface behavior.

## Source Files

- Header: [`GeneralsMD/Code/GameEngine/Include/GameClient/MetaEvent.h`](../../GeneralsMD/Code/GameEngine/Include/GameClient/MetaEvent.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameClient/MessageStream/MetaEvent.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameClient/MessageStream/MetaEvent.cpp)

## Usage

CommandMap is defined as blocks in INI files with meta-command names followed by key mapping properties. Each block maps a specific meta-command to keyboard/mouse input combinations with modifiers and usage contexts.

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Key Mapping Properties](#key-mapping-properties)
- [Enum Value Lists](#enum-value-lists)
  - [Key Names](#key-names)
  - [Transition Types](#transition-types)
  - [Modifier States](#modifier-states)
  - [Command Categories](#command-categories)
  - [Usable In Contexts](#usable-in-contexts)
- [Examples](#examples)
- [Best Practices](#best-practices)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Key Mapping Properties

#### `Key` *(v1.04)*
- **Type**: `MappableKeyType` (see [Key Names](#key-names) section)
- **Description**: The physical key or mouse button to trigger this command
- **Default**: `MK_NONE` (no key assigned)
- **Example**: `Key = MK_P`

#### `Transition` *(v1.04)*
- **Type**: `MappableKeyTransition` (see [Transition Types](#transition-types) section)
- **Description**: When the key action triggers (key down, key up, or double-click)
- **Default**: `DOWN`
- **Example**: `Transition = DOWN`

#### `Modifiers` *(v1.04)*
- **Type**: `MappableKeyModState` (see [Modifier States](#modifier-states) section)
- **Description**: Required modifier keys (Ctrl, Alt, Shift) that must be held
- **Default**: `NONE`
- **Example**: `Modifiers = CTRL`

#### `UseableIn` *(v1.04)*
- **Type**: `CommandUsableInType` (see [Usable In Contexts](#usable-in-contexts) section)
- **Description**: Game contexts where this command can be used (bitfield)
- **Default**: `COMMANDUSABLE_NONE`
- **Example**: `UseableIn = COMMANDUSABLE_EVERYWHERE`

#### `Category` *(v1.04)*
- **Type**: `MappableKeyCategories` (see [Command Categories](#command-categories) section)
- **Description**: Category for organizing commands in the key mapping interface
- **Default**: `CATEGORY_MISC`
- **Example**: `Category = CATEGORY_CONTROL`

#### `Description` *(v1.04)*
- **Type**: `UnicodeString`
- **Description**: Localized description text for this command (read-only, set by game)
- **Example**: `Description = "Pause the game"`

#### `DisplayName` *(v1.04)*
- **Type**: `UnicodeString`
- **Description**: Localized display name for this command (read-only, set by game)
- **Example**: `DisplayName = "Pause"`

## Enum Value Lists

### Key Names *(v1.04)*

#### Keypad Keys
- **`KEY_KP0`** - Keypad 0
- **`KEY_KP1`** - Keypad 1
- **`KEY_KP2`** - Keypad 2
- **`KEY_KP3`** - Keypad 3
- **`KEY_KP4`** - Keypad 4
- **`KEY_KP5`** - Keypad 5
- **`KEY_KP6`** - Keypad 6
- **`KEY_KP7`** - Keypad 7
- **`KEY_KP8`** - Keypad 8
- **`KEY_KP9`** - Keypad 9
- **`KEY_KPDIVIDE`** - Keypad divide (/)
- **`KEY_KPMULTIPLY`** - Keypad multiply (*)
- **`KEY_KPMINUS`** - Keypad minus (-)
- **`KEY_KPPLUS`** - Keypad plus (+)
- **`KEY_KPENTER`** - Keypad enter
- **`KEY_KPDECIMAL`** - Keypad decimal (.)

#### Function Keys
- **`KEY_F1`** - F1
- **`KEY_F2`** - F2
- **`KEY_F3`** - F3
- **`KEY_F4`** - F4
- **`KEY_F5`** - F5
- **`KEY_F6`** - F6
- **`KEY_F7`** - F7
- **`KEY_F8`** - F8
- **`KEY_F9`** - F9
- **`KEY_F10`** - F10
- **`KEY_F11`** - F11
- **`KEY_F12`** - F12

#### Letter Keys
- **`KEY_A`** - A
- **`KEY_B`** - B
- **`KEY_C`** - C
- **`KEY_D`** - D
- **`KEY_E`** - E
- **`KEY_F`** - F
- **`KEY_G`** - G
- **`KEY_H`** - H
- **`KEY_I`** - I
- **`KEY_J`** - J
- **`KEY_K`** - K
- **`KEY_L`** - L
- **`KEY_M`** - M
- **`KEY_N`** - N
- **`KEY_O`** - O
- **`KEY_P`** - P
- **`KEY_Q`** - Q
- **`KEY_R`** - R
- **`KEY_S`** - S
- **`KEY_T`** - T
- **`KEY_U`** - U
- **`KEY_V`** - V
- **`KEY_W`** - W
- **`KEY_X`** - X
- **`KEY_Y`** - Y
- **`KEY_Z`** - Z

#### Number Keys
- **`KEY_0`** - 0
- **`KEY_1`** - 1
- **`KEY_2`** - 2
- **`KEY_3`** - 3
- **`KEY_4`** - 4
- **`KEY_5`** - 5
- **`KEY_6`** - 6
- **`KEY_7`** - 7
- **`KEY_8`** - 8
- **`KEY_9`** - 9

#### Special Keys
- **`KEY_SPACE`** - Space
- **`KEY_ENTER`** - Enter
- **`KEY_ESCAPE`** - Escape
- **`KEY_TAB`** - Tab
- **`KEY_BACKSPACE`** - Backspace
- **`KEY_DELETE`** - Delete
- **`KEY_INSERT`** - Insert
- **`KEY_HOME`** - Home
- **`KEY_END`** - End
- **`KEY_PAGEUP`** - Page Up
- **`KEY_PAGEDOWN`** - Page Down
- **`KEY_UP`** - Up Arrow
- **`KEY_DOWN`** - Down Arrow
- **`KEY_LEFT`** - Left Arrow
- **`KEY_RIGHT`** - Right Arrow

#### Mouse Buttons
- **`MOUSE_LEFT`** - Left Mouse Button
- **`MOUSE_RIGHT`** - Right Mouse Button
- **`MOUSE_MIDDLE`** - Middle Mouse Button
- **`MOUSE_BUTTON4`** - Mouse Button 4
- **`MOUSE_BUTTON5`** - Mouse Button 5

### Transition Types *(v1.04)*

- **`DOWN`** - Trigger when key is pressed down
- **`UP`** - Trigger when key is released
- **`DOUBLEDOWN`** - Trigger on double-click/press

### Modifier States *(v1.04)*

- **`NONE`** - No modifier keys required
- **`CTRL`** - Ctrl key must be held
- **`ALT`** - Alt key must be held
- **`SHIFT`** - Shift key must be held
- **`CTRL_ALT`** - Both Ctrl and Alt must be held
- **`SHIFT_CTRL`** - Both Shift and Ctrl must be held
- **`SHIFT_ALT`** - Both Shift and Alt must be held
- **`SHIFT_ALT_CTRL`** - All three modifiers must be held

### Command Categories *(v1.04)*

- **`CATEGORY_CONTROL`** - Game control commands (pause, speed, etc.)
- **`CATEGORY_INFORMATION`** - Information display commands
- **`CATEGORY_INTERFACE`** - User interface commands
- **`CATEGORY_SELECTION`** - Unit selection commands
- **`CATEGORY_TAUNT`** - Taunt and communication commands
- **`CATEGORY_TEAM`** - Team and multiplayer commands
- **`CATEGORY_MISC`** - Miscellaneous commands
- **`CATEGORY_DEBUG`** - Debug and development commands

### Usable In Contexts *(v1.04)*

- **`COMMANDUSABLE_NONE`** - Cannot be used anywhere
- **`COMMANDUSABLE_GAME`** - Can be used during gameplay
- **`COMMANDUSABLE_OBSERVER`** - Can be used when observing
- **`COMMANDUSABLE_EVERYWHERE`** - Can be used in all contexts

## Examples

### Basic Pause Command
```ini
CommandMap MSG_META_TOGGLE_PAUSE
  Key = MK_P
  Transition = DOWN
  Modifiers = NONE
  UseableIn = COMMANDUSABLE_OBSERVER
  Category = CATEGORY_CONTROL
End
```

### Framerate Control with Modifiers
```ini
CommandMap MSG_META_INCREASE_MAX_RENDER_FPS
  Key = MK_KPPLUS
  Transition = DOWN
  Modifiers = CTRL
  UseableIn = COMMANDUSABLE_EVERYWHERE
  Category = CATEGORY_CONTROL
End

CommandMap MSG_META_DECREASE_MAX_RENDER_FPS
  Key = MK_KPMINUS
  Transition = DOWN
  Modifiers = CTRL
  UseableIn = COMMANDUSABLE_EVERYWHERE
  Category = CATEGORY_CONTROL
End
```

### Frame Stepping for Observers
```ini
CommandMap MSG_META_STEP_FRAME
  Key = MK_O
  Transition = DOWN
  Modifiers = NONE
  UseableIn = COMMANDUSABLE_OBSERVER
  Category = CATEGORY_CONTROL
End

CommandMap MSG_META_STEP_FRAME_ALT
  Key = MK_O
  Transition = DOWN
  Modifiers = SHIFT
  UseableIn = COMMANDUSABLE_EVERYWHERE
  Category = CATEGORY_CONTROL
End
```

### Worker Selection Command
```ini
CommandMap MSG_META_SELECT_NEXT_IDLE_WORKER
  Key = MK_I
  Transition = DOWN
  Modifiers = CTRL
  UseableIn = COMMANDUSABLE_GAME
  Category = CATEGORY_SELECTION
End
```

### Debug Commands
```ini
CommandMap MSG_META_DEMO_REMOVE_PREREQ
  Key = MK_P
  Transition = DOWN
  Modifiers = ALT
  UseableIn = COMMANDUSABLE_GAME
  Category = CATEGORY_DEBUG
End

CommandMap MSG_META_DEMO_FREE_BUILD
  Key = MK_B
  Transition = DOWN
  Modifiers = ALT
  UseableIn = COMMANDUSABLE_GAME
  Category = CATEGORY_DEBUG
End
```

## Best Practices

### Key Assignment

1. **Avoid Conflicts**: Don't assign the same key combination to multiple commands
2. **Logical Grouping**: Use consistent modifier patterns for related commands
3. **Accessibility**: Use easily accessible keys for frequently used commands
4. **Modifier Usage**: Use modifiers to avoid conflicts with gameplay keys

### Context Usage

1. **Observer Commands**: Use `COMMANDUSABLE_OBSERVER` for replay/observer-specific commands
2. **Game Commands**: Use `COMMANDUSABLE_GAME` for gameplay-affecting commands
3. **Universal Commands**: Use `COMMANDUSABLE_EVERYWHERE` for system commands
4. **Context Separation**: Keep observer and player commands separate to avoid conflicts

### Category Organization

1. **Logical Grouping**: Group related commands in the same category
2. **User Interface**: Use categories that make sense in the key mapping dialog
3. **Consistency**: Use consistent categorization across similar commands
4. **Debug Separation**: Keep debug commands in separate categories

### Key Selection

1. **Function Keys**: Use F-keys for less frequent system commands
2. **Keypad**: Use keypad keys for numeric or directional commands
3. **Letters**: Use letter keys for frequently used commands (with modifiers)
4. **Mouse**: Use mouse buttons sparingly for meta-commands

### Modifier Patterns

1. **Ctrl**: Use for system/control commands
2. **Alt**: Use for debug/development commands
3. **Shift**: Use for alternative versions of commands
4. **Combinations**: Use multiple modifiers for advanced commands

## Template

```ini
CommandMap MSG_META_COMMAND_NAME
    Key = MK_NONE                        ; // Keyboard key for this command *(v1.04)*
    Transition = DOWN                    ; // When command triggers (DOWN/UP/DOUBLEDOWN) *(v1.04)*
    Modifiers = NONE                     ; // Required modifier keys (NONE/CTRL/ALT/SHIFT/combinations) *(v1.04)*
    UseableIn = COMMANDUSABLE_NONE       ; // Where command can be used *(v1.04)*
    Category = CATEGORY_MISC             ; // Command category for organization *(v1.04)*
    Description = GUI:CommandDescription ; // Detailed description text key *(v1.04)*
    DisplayName = GUI:CommandDisplayName ; // Short display name text key *(v1.04)*
End
```

## Notes

- CommandMap provides customizable input handling for enhanced player experience
- The configuration manages key bindings for different interface contexts and game modes
- Command operations create flexible and personalized control schemes
- Command management ensures intuitive and efficient input handling
- This configuration is essential for user interface customization and accessibility
- Command coordination creates consistent input behavior across different game modes
- Key mappings can be reassigned to different keys for personal preference
- Modifier combinations allow multiple commands to share the same main key
- Transition settings control when commands trigger (press, release, double-click)
- UseableIn settings prevent commands from interfering with inappropriate contexts
- Category organization helps players find and understand related commands
- Description and DisplayName properties provide user-friendly command information
- CommandMap templates are reusable and can be applied to multiple game message types
- The command mapping system works in conjunction with the input system for keyboard and mouse handling
- Default key mappings are provided for common commands but can be overridden
- CommandMap is managed by the `MetaMap` singleton system
- Meta-commands are system-level actions that affect game state, not unit commands
- Key mappings are loaded from INI files and can be customized by players
- The system supports both keyboard and mouse input mapping
- Commands can be restricted to specific game contexts (gameplay vs observer mode)
- Debug commands are only available in debug builds
- The key mapping system integrates with the game's options menu
- Default key mappings are automatically generated if not specified in INI files
- Command descriptions and display names are localized through the game's text system
- The system supports both key press and key release triggers
- Double-click detection is available for mouse buttons
- Modifier key combinations allow for extensive key customization without conflicts

## Source Files

**Base Class:** [MetaMapRec](../../GeneralsMD/Code/GameEngine/Include/GameClient/MetaEvent.h)
- Header: [`GeneralsMD/Code/GameEngine/Include/GameClient/MetaEvent.h`](../../GeneralsMD/Code/GameEngine/Include/GameClient/MetaEvent.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameClient/MessageStream/MetaEvent.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameClient/MessageStream/MetaEvent.cpp)
- INI Parser: [`GeneralsMD/Code/GameEngine/Source/Common/INI/INI.cpp`](../../GeneralsMD/Code/GameEngine/Source/Common/INI/INI.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet
