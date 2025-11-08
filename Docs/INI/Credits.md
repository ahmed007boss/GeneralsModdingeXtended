# Credits INI Documentation

## Overview

The `Credits` INI file contains credits configuration settings and parameters for game credits display and management. Credits define the scrolling text display that shows game development team information, acknowledgments, and legal notices during game startup or in dedicated credits screens.

## Usage

Credits are defined as a single configuration block in INI files that controls the scrolling text display for game credits. This is a **display configuration system** that manages text formatting, scrolling behavior, and color schemes. The credits system provides a professional presentation of development team information and legal acknowledgments.

**Limitations**:
- Credits display is limited to predefined text content and formatting options
- Scrolling behavior is controlled by fixed parameters
- Text content must be pre-defined and cannot be dynamically modified
- Color schemes are limited to the predefined color options

**Conditions**:
- Credits manage text display formatting and scrolling behavior
- The configuration handles text styles, colors, and layout options
- Credits operations provide professional presentation of development information
- Credits management ensures consistent and readable text display
- **Multiple instances behavior**: Only one credits configuration is active at a time

**Dependencies**:
- Uses localization system for text content display
- Integrates with the game's rendering system for text display
- Uses color and formatting systems for visual presentation

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Scrolling Properties](#scrolling-properties)
  - [Color Properties](#color-properties)
  - [Text Content Properties](#text-content-properties)
- [Text Style Values](#text-style-values)
- [Examples](#examples)
- [Best Practices](#best-practices)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Scrolling Properties *(v1.04)*

#### `ScrollRate` *(v1.04)*
- **Type**: `Int`
- **Description**: Number of pixels to move the credits text each scroll update. Higher values make text scroll faster.
- **Default**: `2`
- **Example**: `ScrollRate = 3` // Text scrolls 3 pixels per update

#### `ScrollRateEveryFrames` *(v1.04)*
- **Type**: `Int`
- **Description**: Number of frames to wait between scroll updates. Higher values make scrolling slower.
- **Default**: `1`
- **Example**: `ScrollRateEveryFrames = 2` // Scroll every 2 frames

#### `ScrollDown` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether to scroll the credits downward (Yes) or upward (No). Upward scrolling is the standard direction.
- **Default**: `No`
- **Example**: `ScrollDown = Yes` // Credits scroll downward

### Color Properties *(v1.04)*

#### `TitleColor` *(v1.04)*
- **Type**: `Color` (RGBA format)
- **Description**: Color for TITLE style text. Specified as R:Red G:Green B:Blue A:Alpha values (0-255 each).
- **Default**: `R:161 G:179 B:255 A:255`
- **Example**: `TitleColor = R:255 G:255 B:255 A:255` // White title color

#### `MinorTitleColor` *(v1.04)*
- **Type**: `Color` (RGBA format)
- **Description**: Color for MINORTITLE style text. Specified as R:Red G:Green B:Blue A:Alpha values (0-255 each).
- **Default**: `R:161 G:179 B:255 A:255`
- **Example**: `MinorTitleColor = R:200 G:200 B:255 A:255` // Light blue minor title color

#### `NormalColor` *(v1.04)*
- **Type**: `Color` (RGBA format)
- **Description**: Color for NORMAL style text. Specified as R:Red G:Green B:Blue A:Alpha values (0-255 each).
- **Default**: `R:209 G:218 B:255 A:255`
- **Example**: `NormalColor = R:255 G:255 B:255 A:255` // White normal text color

### Text Content Properties *(v1.04)*

#### `Style` *(v1.04)*
- **Type**: `TextStyle` (see [Text Style Values](#text-style-values) section)
- **Description**: Sets the text style for all following Text entries until another Style is declared.
- **Default**: `NORMAL`
- **Example**: `Style = TITLE` // Following text uses title style

#### `Text` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Text content to display. Can be quoted strings, localization keys, or special values.
- **Format**: 
  - Quoted strings: `"Text Content"`
  - Localization keys: `GUI:KeyName` or `CREDITS:KeyName`
  - Blank content: `<BLANK>`
- **Example**: 
  ```
  Text = "John Doe"           // Direct text
  Text = GUI:Programmer       // Localized text
  Text = <BLANK>              // Empty text
  ```

#### `Blank` *(v1.04)*
- **Type**: `Command`
- **Description**: Inserts a blank line in the credits display for spacing and visual separation.
- **Default**: None
- **Example**: `Blank` // Adds empty line

## Text Style Values *(v1.04)*

The Style property accepts the following values:

- **`TITLE`** *(v1.04)* - Largest font size, used for main titles and company names
- **`MINORTITLE`** *(v1.04)* - Medium font size, used for section headers and important categories
- **`NORMAL`** *(v1.04)* - Smallest font size, used for regular text like names and descriptions
- **`COLUMN`** *(v1.04)* - Same size as NORMAL but arranges text in two columns side by side

## Examples

### Basic Credits Structure
```ini
Credits
    ScrollRate = 2
    ScrollRateEveryFrames = 1
    ScrollDown = No
    TitleColor = R:255 G:255 B:255 A:255
    MinorTitleColor = R:200 G:200 B:255 A:255
    NormalColor = R:255 G:255 B:255 A:255
    
    Style = TITLE
    Text = "EA Pacific"
    Blank
    Style = NORMAL
    Text = GUI:LegalNotice
    Blank
    Style = MINORTITLE
    Text = GUI:Programmers
    Style = NORMAL
    Text = "John Doe"
    Text = "Jane Smith"
End
```

### Column Format Example
```ini
Credits
    ScrollRate = 3
    ScrollRateEveryFrames = 1
    ScrollDown = No
    TitleColor = R:255 G:255 B:255 A:255
    MinorTitleColor = R:200 G:200 B:255 A:255
    NormalColor = R:255 G:255 B:255 A:255
    
    Style = TITLE
    Text = "Development Team"
    Blank
    Style = MINORTITLE
    Text = GUI:Programming
    Style = COLUMN
    Text = GUI:LeadProgrammer
    Text = "John Doe"
    Text = GUI:SeniorProgrammer
    Text = "Jane Smith"
    Text = GUI:JuniorProgrammer
    Text = <BLANK>
End
```

## Best Practices

### Credits Organization

1. **Logical Structure**: Organize credits in a logical hierarchy (company, departments, individuals)
2. **Consistent Formatting**: Use consistent text styles for similar content types
3. **Appropriate Spacing**: Use Blank lines to separate different sections
4. **Professional Presentation**: Ensure credits look professional and complete

### Text Content

1. **Localization Keys**: Use localization keys for titles and categories that might be translated
2. **Direct Names**: Use quoted strings for actual names that should not be translated
3. **Column Usage**: Use COLUMN style for side-by-side information like titles and names
4. **Blank Spacing**: Use Blank entries to create visual separation between sections

### Scrolling Configuration

1. **Readable Speed**: Set ScrollRate and ScrollRateEveryFrames for comfortable reading
2. **Standard Direction**: Use upward scrolling (ScrollDown = No) as the standard
3. **Color Contrast**: Ensure text colors have good contrast against the background
4. **Consistent Colors**: Use consistent color schemes across all text styles

## Template

```ini
Credits
    ScrollRate = 2                      ; // Pixels to move per scroll update *(v1.04)*
    ScrollRateEveryFrames = 1           ; // Frames between scroll updates *(v1.04)*
    ScrollDown = No                     ; // Scroll direction (No = upward) *(v1.04)*
    TitleColor = R:255 G:255 B:255 A:255 ; // Color for TITLE style *(v1.04)*
    MinorTitleColor = R:200 G:200 B:255 A:255 ; // Color for MINORTITLE style *(v1.04)*
    NormalColor = R:255 G:255 B:255 A:255 ; // Color for NORMAL style *(v1.04)*
    
    Style = TITLE                       ; // Set text style to TITLE *(v1.04)*
    Text = "Company Name"               ; // Title text *(v1.04)*
    Blank                               ; // Add blank line *(v1.04)*
    Style = NORMAL                      ; // Set text style to NORMAL *(v1.04)*
    Text = GUI:LegalNotice              ; // Normal text using localization *(v1.04)*
    Text = "Direct Text"                ; // Direct text content *(v1.04)*
    Blank                               ; // Add blank line *(v1.04)*
    Style = MINORTITLE                  ; // Set text style to MINORTITLE *(v1.04)*
    Text = GUI:DepartmentName           ; // Minor title text *(v1.04)*
    Style = COLUMN                      ; // Set text style to COLUMN *(v1.04)*
    Text = GUI:PositionTitle            ; // Column header *(v1.04)*
    Text = "Person Name"                ; // Column content *(v1.04)*
End
```

## Notes

- Credits provide professional presentation of development team information and legal notices
- The configuration manages text formatting, scrolling behavior, and visual presentation
- Credits operations create polished and readable text displays for game information
- Credits management ensures consistent and professional presentation standards
- This configuration is essential for game startup screens and dedicated credits displays
- Credits coordination creates unified text presentation across different content types
- Scrolling properties control the speed and direction of text movement
- Color properties define the visual appearance of different text styles
- Text content properties manage the actual content and formatting of credits
- Text styles provide hierarchical formatting for different types of information
- Localization integration allows credits to be translated for different languages
- Column formatting enables side-by-side presentation of related information
- Blank spacing creates visual separation and improves readability
- Credits are displayed during game startup or in dedicated credits screens
- The system supports both localized and direct text content
- Color values use RGBA format with values from 0-255 for each component
- Scrolling direction and speed can be customized for different presentation needs
- Text styles create visual hierarchy for different types of information
- The credits system integrates with the game's rendering and localization systems

## Source Files

- Header: [`GeneralsMD\Code\GameEngine\Include\GameClient\Credits.h`](..\GeneralsMD\Code\GameEngine\Include\GameClient\Credits.h)
- Source: [`GeneralsMD\Code\GameEngine\Source\GameClient\Credits.cpp`](..\GeneralsMD\Code\GameEngine\Source\GameClient\Credits.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet



