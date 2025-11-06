# DrawGroupInfo INI Documentation

## Overview

The `DrawGroupInfo` INI file contains draw group configuration settings and parameters for text rendering and UI display systems. DrawGroupInfo defines font properties, text colors, positioning, and drop shadow effects for different UI elements and text display groups.

## Usage

DrawGroupInfo templates are defined in INI files and specify the visual appearance and positioning of text elements in the game's user interface. This is a **template configuration system** that defines text rendering properties. The draw group system provides consistent text formatting and positioning across different UI elements.

**Limitations**:
- DrawGroupInfo is limited to text rendering and positioning properties
- Font properties are fixed and cannot be dynamically modified
- Positioning is limited to pixel or percentage-based offsets
- Color properties are limited to predefined color values

**Conditions**:
- DrawGroupInfo manages text rendering appearance and positioning
- The configuration handles font properties, colors, and positioning options
- Draw group operations provide consistent text display formatting
- Draw group management ensures unified text appearance across UI elements
- **Multiple instances behavior**: Multiple DrawGroupInfo templates can exist with different text formatting configurations

**Dependencies**:
- Uses font system for text rendering
- Integrates with the UI rendering system for text display
- Uses color system for text and shadow colors
- Referenced by UI elements for text formatting

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Font Properties](#font-properties)
  - [Color Properties](#color-properties)
  - [Positioning Properties](#positioning-properties)
  - [Drop Shadow Properties](#drop-shadow-properties)
- [Examples](#examples)
- [Best Practices](#best-practices)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Font Properties *(v1.04)*

#### `FontName` *(v1.04)*
- **Type**: `AsciiString` (quoted)
- **Description**: Name of the font to use for text rendering. Must be a valid font name available in the system.
- **Default**: `""`
- **Example**: `FontName = "Arial"` // Uses Arial font

#### `FontSize` *(v1.04)*
- **Type**: `Int`
- **Description**: Size of the font in points. Larger values create bigger text.
- **Default**: `12`
- **Example**: `FontSize = 16` // 16-point font size

#### `FontIsBold` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether the font should be rendered in bold. Makes text appear thicker and more prominent.
- **Default**: `No`
- **Example**: `FontIsBold = Yes` // Bold text rendering

### Color Properties *(v1.04)*

#### `UsePlayerColor` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether to use the player's team color for text instead of the specified ColorForText. Useful for player-specific UI elements.
- **Default**: `No`
- **Example**: `UsePlayerColor = Yes` // Text uses player's team color

#### `ColorForText` *(v1.04)*
- **Type**: `Color` (RGBA format)
- **Description**: Color for the main text. Specified as R:Red G:Green B:Blue A:Alpha values (0-255 each). Ignored if UsePlayerColor is Yes.
- **Default**: `R:255 G:255 B:255 A:255`
- **Example**: `ColorForText = R:255 G:255 B:0 A:255` // Yellow text

#### `ColorForTextDropShadow` *(v1.04)*
- **Type**: `Color` (RGBA format)
- **Description**: Color for the text drop shadow. Specified as R:Red G:Green B:Blue A:Alpha values (0-255 each).
- **Default**: `R:0 G:0 B:0 A:255`
- **Example**: `ColorForTextDropShadow = R:0 G:0 B:0 A:128` // Semi-transparent black shadow

### Positioning Properties *(v1.04)*

#### `DrawPositionXPixel` *(v1.04)*
- **Type**: `Int`
- **Description**: X-axis position offset in pixels from the default position. Positive values move right, negative values move left.
- **Default**: `0`
- **Example**: `DrawPositionXPixel = 10` // Move 10 pixels right

#### `DrawPositionXPercent` *(v1.04)*
- **Type**: `Real` (percentage)
- **Description**: X-axis position offset as a percentage of screen width (0.0 to 1.0). Overrides DrawPositionXPixel when specified.
- **Default**: `0.0`
- **Example**: `DrawPositionXPercent = 0.1` // Move 10% of screen width right

#### `DrawPositionYPixel` *(v1.04)*
- **Type**: `Int`
- **Description**: Y-axis position offset in pixels from the default position. Positive values move down, negative values move up.
- **Default**: `0`
- **Example**: `DrawPositionYPixel = -5` // Move 5 pixels up

#### `DrawPositionYPercent` *(v1.04)*
- **Type**: `Real` (percentage)
- **Description**: Y-axis position offset as a percentage of screen height (0.0 to 1.0). Overrides DrawPositionYPixel when specified.
- **Default**: `0.0`
- **Example**: `DrawPositionYPercent = 0.05` // Move 5% of screen height up

### Drop Shadow Properties *(v1.04)*

#### `DropShadowOffsetX` *(v1.04)*
- **Type**: `Int`
- **Description**: Horizontal offset for the drop shadow in pixels. Positive values create shadow to the right, negative values create shadow to the left.
- **Default**: `1`
- **Example**: `DropShadowOffsetX = 2` // Shadow offset 2 pixels right

#### `DropShadowOffsetY` *(v1.04)*
- **Type**: `Int`
- **Description**: Vertical offset for the drop shadow in pixels. Positive values create shadow below text, negative values create shadow above text.
- **Default**: `1`
- **Example**: `DropShadowOffsetY = 2` // Shadow offset 2 pixels down

## Examples

### Basic Text Display
```ini
DrawGroupInfo BasicText
    FontName = "Arial"
    FontSize = 12
    FontIsBold = No
    UsePlayerColor = No
    ColorForText = R:255 G:255 B:255 A:255
    ColorForTextDropShadow = R:0 G:0 B:0 A:128
    DropShadowOffsetX = 1
    DropShadowOffsetY = 1
    DrawPositionXPixel = 0
    DrawPositionYPixel = 0
End
```

### Bold Title Text
```ini
DrawGroupInfo TitleText
    FontName = "Arial"
    FontSize = 18
    FontIsBold = Yes
    UsePlayerColor = No
    ColorForText = R:255 G:255 B:0 A:255
    ColorForTextDropShadow = R:0 G:0 B:0 A:255
    DropShadowOffsetX = 2
    DropShadowOffsetY = 2
    DrawPositionXPixel = 10
    DrawPositionYPixel = 5
End
```

### Player-Specific Text
```ini
DrawGroupInfo PlayerText
    FontName = "Arial"
    FontSize = 14
    FontIsBold = No
    UsePlayerColor = Yes
    ColorForText = R:255 G:255 B:255 A:255
    ColorForTextDropShadow = R:0 G:0 B:0 A:192
    DropShadowOffsetX = 1
    DropShadowOffsetY = 1
    DrawPositionXPercent = 0.1
    DrawPositionYPercent = 0.05
End
```

### Centered Text with Large Shadow
```ini
DrawGroupInfo CenteredText
    FontName = "Arial"
    FontSize = 16
    FontIsBold = Yes
    UsePlayerColor = No
    ColorForText = R:255 G:255 B:255 A:255
    ColorForTextDropShadow = R:0 G:0 B:0 A:128
    DropShadowOffsetX = 3
    DropShadowOffsetY = 3
    DrawPositionXPercent = 0.5
    DrawPositionYPercent = 0.5
End
```

## Best Practices

### Font Selection

1. **Consistent Fonts**: Use consistent font families across similar UI elements
2. **Readable Sizes**: Ensure font sizes are readable at different screen resolutions
3. **Bold Usage**: Use bold text sparingly for emphasis and titles
4. **Font Availability**: Use fonts that are available on all target systems

### Color Design

1. **High Contrast**: Ensure text colors have good contrast against backgrounds
2. **Player Colors**: Use player colors for player-specific information
3. **Consistent Palette**: Maintain consistent color schemes across UI elements
4. **Shadow Colors**: Use appropriate shadow colors that enhance readability

### Positioning

1. **Pixel vs Percentage**: Use pixel positioning for precise control, percentage for responsive design
2. **Consistent Offsets**: Maintain consistent positioning patterns across similar elements
3. **Screen Compatibility**: Test positioning on different screen resolutions
4. **Visual Hierarchy**: Use positioning to create clear visual hierarchy

### Drop Shadows

1. **Subtle Effects**: Use subtle drop shadows that enhance readability without being distracting
2. **Consistent Direction**: Maintain consistent shadow direction across UI elements
3. **Appropriate Offset**: Use appropriate shadow offsets that provide depth without blurring
4. **Color Coordination**: Coordinate shadow colors with the overall color scheme

## Template

```ini
DrawGroupInfo DrawGroupInfoName
    FontName = "Arial"                   ; // Font name for text rendering *(v1.04)*
    FontSize = 12                        ; // Font size in points *(v1.04)*
    FontIsBold = No                      ; // Whether text is bold *(v1.04)*
    UsePlayerColor = No                  ; // Use player's team color *(v1.04)*
    ColorForText = R:255 G:255 B:255 A:255 ; // Text color (RGBA) *(v1.04)*
    ColorForTextDropShadow = R:0 G:0 B:0 A:128 ; // Shadow color (RGBA) *(v1.04)*
    DropShadowOffsetX = 1                ; // Horizontal shadow offset *(v1.04)*
    DropShadowOffsetY = 1                ; // Vertical shadow offset *(v1.04)*
    DrawPositionXPixel = 0               ; // X position offset in pixels *(v1.04)*
    DrawPositionXPercent = 0.0           ; // X position offset as percentage *(v1.04)*
    DrawPositionYPixel = 0               ; // Y position offset in pixels *(v1.04)*
    DrawPositionYPercent = 0.0           ; // Y position offset as percentage *(v1.04)*
End
```

## Notes

- DrawGroupInfo provides consistent text rendering and positioning for UI elements
- The configuration manages font properties, colors, positioning, and drop shadow effects
- Draw group operations create unified text appearance across different UI components
- Draw group management ensures consistent text formatting and visual hierarchy
- This configuration is essential for professional and readable text display in the game interface
- Draw group coordination creates visual consistency across different UI elements
- Font properties control the basic appearance and readability of text
- Color properties provide visual distinction and player identification
- Positioning properties enable precise text placement and responsive design
- Drop shadow properties enhance text readability and visual depth
- The system supports both pixel-based and percentage-based positioning
- Player color integration allows for team-specific text coloring
- Font rendering is handled by the system's font management system
- Text positioning can be overridden by percentage values when specified
- Drop shadow effects provide visual depth and improved readability
- The system integrates with the UI rendering system for text display
- DrawGroupInfo templates are defined in INI files and loaded by the system
- Text rendering properties cannot be modified during runtime
- The system supports complex text formatting with multiple property combinations

## Source Files

**Base Class:** [DrawGroupInfo](../../GeneralsMD/Code/GameEngine/Include/GameClient/DrawGroupInfo.h)
- Header: [`GeneralsMD/Code/GameEngine/Include/GameClient/DrawGroupInfo.h`](../../GeneralsMD/Code/GameEngine/Include/GameClient/DrawGroupInfo.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/Common/INI/INIDrawGroupInfo.cpp`](../../GeneralsMD/Code/GameEngine/Source/Common/INI/INIDrawGroupInfo.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet
