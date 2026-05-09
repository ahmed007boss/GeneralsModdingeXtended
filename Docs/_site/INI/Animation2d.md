# Animation2d INI Documentation

## Overview

The `Animation2d` INI file contains 2D animation definitions for user interface elements, status indicators, visual effects, and other 2D graphical components. These animations are composed of sequences of images that can be played in various modes to create dynamic visual effects in the game interface.

## Usage

Animation2d configurations are used throughout the game for UI animations, status effects, and visual feedback. This is a **global configuration file** that defines reusable animation templates. The animations are loaded from the `Data\INI\Animation2D` directory and can be referenced by name throughout the game.

**Limitations**:
- Animation2d is limited to 2D image sequences only
- Animation performance depends on the number of frames and update frequency
- Image assets must be pre-loaded and available in the game data
- Animation modes are predefined and cannot be extended through INI

**Conditions**:
- Animation2d manages 2D animation templates and instances
- The configuration handles animation timing, sequencing, and playback modes
- Animation operations provide visual feedback and interface enhancement
- Animation management creates smooth and responsive user experiences
- **Multiple instances behavior**: Multiple instances of the same animation can run independently with different timing

**Dependencies**:
- Uses Image assets that must be loaded separately
- Integrates with the game's rendering system for display
- Uses the Anim2DCollection system for template management

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Animation Control](#animation-control)
  - [Frame Management](#frame-management)
  - [Image Assets](#image-assets)
- [AnimationMode Values](#animationmode-values)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Animation Control *(v1.04)*

#### `AnimationMode` *(v1.04)*
- **Type**: `Anim2DMode` (see [AnimationMode Values](#animationmode-values) section)
- **Description**: Controls how the animation plays back. Determines whether the animation loops, plays once, or uses ping-pong behavior.
- **Default**: `ANIM_2D_ONCE`
- **Example**: `AnimationMode = LOOP` // Animation repeats continuously

#### `AnimationDelay` *(v1.04)*
- **Type**: `UnsignedShort`
- **Description**: Duration in milliseconds between each frame update. Lower values make animations play faster.
- **Default**: `30`
- **Example**: `AnimationDelay = 60` // Animation plays at half speed

#### `RandomizeStartFrame` *(v1.04)*
- **Type**: `Bool`
- **Description**: If yes, each animation instance will start from a random frame instead of frame 0. Creates variety in animation timing.
- **Default**: `No`
- **Example**: `RandomizeStartFrame = Yes` // Each instance starts at different frame

### Frame Management *(v1.04)*

#### `NumberImages` *(v1.04)*
- **Type**: `UnsignedShort`
- **Description**: Total number of image frames in this animation. Must match the number of Image entries.
- **Default**: `1`
- **Example**: `NumberImages = 16` // Animation has 16 frames

### Image Assets *(v1.04)*

#### `Image` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Name of an image asset to use as a frame in the animation. Must be defined in order (Image 0, Image 1, etc.).
- **Default**: None
- **Example**: `Image = SCPCross000` // First frame uses SCPCross000 image

#### `ImageSequence` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Defines a sequence of images using a naming pattern. More efficient than individual Image entries for sequential naming.
- **Default**: None
- **Example**: `ImageSequence = SCPCross` // Loads SCPCross000, SCPCross001, etc.

## AnimationMode Values *(v1.04)*

The AnimationMode property accepts the following values:

- **`NONE`** *(v1.04)* - No animation mode (invalid state)
- **`ONCE`** *(v1.04)* - Play animation once from start to finish, then stop
- **`ONCE_BACKWARDS`** *(v1.04)* - Play animation once from finish to start, then stop
- **`LOOP`** *(v1.04)* - Play animation continuously, restarting from frame 0 after reaching the end
- **`LOOP_BACKWARDS`** *(v1.04)* - Play animation continuously in reverse, restarting from last frame after reaching frame 0
- **`PING_PONG`** *(v1.04)* - Play animation forward, then backward, then forward again (continuous)
- **`PING_PONG_BACKWARDS`** *(v1.04)* - Start playing animation backward, then forward, then backward again (continuous)

## Examples

### Basic Healing Animation
```ini
Animation DefaultHeal
    AnimationMode          = LOOP
    AnimationDelay         = 30
    RandomizeStartFrame    = Yes
    NumberImages           = 16
    Image                  = SCPCross000
    Image                  = SCPCross001
    Image                  = SCPCross002
    ; ... more images up to SCPCross015
End
```

### Structure Repair Animation
```ini
Animation StructureHeal
    AnimationMode          = PING_PONG
    AnimationDelay         = 60
    RandomizeStartFrame    = Yes
    NumberImages           = 10
    Image                  = SCPWrench000
    Image                  = SCPWrench001
    ; ... more images up to SCPWrench009
End
```

### Status Indicator Animation
```ini
Animation StatusBlink
    AnimationMode          = LOOP
    AnimationDelay         = 100
    RandomizeStartFrame    = No
    NumberImages           = 2
    Image                  = StatusOn
    Image                  = StatusOff
End
```

### Using ImageSequence
```ini
Animation ExplosionEffect
    AnimationMode          = ONCE
    AnimationDelay         = 50
    RandomizeStartFrame    = No
    NumberImages           = 20
    ImageSequence          = Explosion
End
```

## Template

```ini
Animation AnimationName
    AnimationMode          = LOOP              ; // Animation playback mode *(v1.04)*
    AnimationDelay         = 30                ; // Milliseconds between frame updates *(v1.04)*
    RandomizeStartFrame    = No                ; // Start from random frame for variety *(v1.04)*
    NumberImages           = 16                ; // Total number of frames in animation *(v1.04)*
    Image                  = FrameImage000     ; // First frame image *(v1.04)*
    Image                  = FrameImage001     ; // Second frame image *(v1.04)*
    ; ... continue with more Image entries
    ; OR use ImageSequence for sequential naming:
    ; ImageSequence          = FrameImage      ; // Loads FrameImage000, FrameImage001, etc. *(v1.04)*
End
```

## Notes

- Animation2d provides 2D animation capabilities for user interface and visual effects
- The configuration manages animation timing, sequencing, and playback behavior
- Animation operations enhance visual feedback and user experience
- Animation management creates smooth and responsive interface elements
- This configuration is essential for UI animations and status indicators
- Animation coordination ensures consistent visual timing across the interface
- Image assets must be loaded separately and referenced by name
- AnimationDelay controls playback speed - lower values = faster animation
- RandomizeStartFrame prevents synchronized animations from looking mechanical
- AnimationMode determines the playback behavior and looping characteristics
- NumberImages must exactly match the number of Image or ImageSequence entries
- ImageSequence is more efficient for sequentially named image assets
- Animation templates are loaded once and can be instantiated multiple times
- Each animation instance maintains its own timing and frame state

## Source Files

- Header: [`GeneralsMD/Code/GameEngine/Include/GameClient/Anim2D.h`](../../GeneralsMD/Code/GameEngine/Include/GameClient/Anim2D.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameClient/System/Anim2D.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameClient/System/Anim2D.cpp)
- INI Parser: [`GeneralsMD/Code/GameEngine/Source/Common/INI/INIAnimation.cpp`](../../GeneralsMD/Code/GameEngine/Source/Common/INI/INIAnimation.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet