# AudioSettings INI Documentation

## Overview

The `AudioSettings` class represents global audio configuration settings for the game's sound system. It controls audio file paths, hardware settings, volume levels, 3D audio positioning, and microphone behavior for immersive sound experiences.

## Source Files

- Header: [`Core/GameEngine/Include/Common/AudioSettings.h`](../../Core/GameEngine/Include/Common/AudioSettings.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/Common/INI/INI.cpp`](../../GeneralsMD/Code/GameEngine/Source/Common/INI/INI.cpp)

## Usage

AudioSettings is defined as a single global configuration block in INI files. It sets up the entire audio system including file paths, hardware preferences, volume defaults, and 3D audio behavior.

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [File Path Settings](#file-path-settings)
  - [Audio Hardware Settings](#audio-hardware-settings)
  - [Audio Quality Settings](#audio-quality-settings)
  - [Audio Performance Settings](#audio-performance-settings)
  - [Volume Settings](#volume-settings)
  - [3D Audio Settings](#3d-audio-settings)
  - [Microphone Settings](#microphone-settings)
  - [Zoom Audio Settings](#zoom-audio-settings)
- [Examples](#examples)
- [Best Practices](#best-practices)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### File Path Settings

#### `AudioRoot` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Base directory for all audio files relative to the current working directory
- **Default**: `Data\Audio`
- **Example**: `AudioRoot = Data\Audio`

#### `SoundsFolder` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Subfolder within AudioRoot containing sound effect files
- **Default**: `Sounds`
- **Example**: `SoundsFolder = Sounds`

#### `MusicFolder` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Subfolder within AudioRoot containing music track files
- **Default**: `Tracks`
- **Example**: `MusicFolder = Tracks`

#### `StreamingFolder` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Subfolder within AudioRoot containing streaming audio files (speech, music)
- **Default**: `Speech`
- **Example**: `StreamingFolder = Speech`

#### `SoundsExtension` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: File extension for sound effect files (without the dot)
- **Default**: `wav`
- **Example**: `SoundsExtension = wav`

### Audio Hardware Settings

#### `UseDigital` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether to use digital audio output (should be Yes for best quality)
- **Default**: `Yes`
- **Example**: `UseDigital = Yes`

#### `UseMidi` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether to use MIDI audio (should be No for modern systems)
- **Default**: `No`
- **Example**: `UseMidi = No`

### Audio Quality Settings

#### `OutputRate` *(v1.04)*
- **Type**: `Int`
- **Description**: Audio sample rate in Hz (higher = better quality, more CPU usage)
- **Common Values**: `11025`, `22050`, `44100`, `48000`
- **Default**: `44100`
- **Example**: `OutputRate = 44100`

#### `OutputBits` *(v1.04)*
- **Type**: `Int`
- **Description**: Audio bit depth (8 or 16 bits per sample)
- **Values**: `8`, `16`
- **Default**: `16`
- **Example**: `OutputBits = 16`

#### `OutputChannels` *(v1.04)*
- **Type**: `Int`
- **Description**: Number of audio output channels
- **Values**: `1` (mono), `2` (stereo)
- **Default**: `2`
- **Example**: `OutputChannels = 2`

### Audio Performance Settings

#### `SampleCount2D` *(v1.04)*
- **Type**: `Int`
- **Description**: Maximum number of 2D (UI) audio samples that can play simultaneously
- **Default**: `4`
- **Example**: `SampleCount2D = 4`

#### `SampleCount3D` *(v1.04)*
- **Type**: `Int`
- **Description**: Maximum number of 3D (world) audio samples that can play simultaneously
- **Default**: `25`
- **Example**: `SampleCount3D = 25`

#### `StreamCount` *(v1.04)*
- **Type**: `Int`
- **Description**: Maximum number of streaming audio sources that can play simultaneously
- **Default**: `3`
- **Example**: `StreamCount = 3`

#### `AudioFootprintInBytes` *(v1.04)*
- **Type**: `UnsignedInt`
- **Description**: Maximum memory usage for audio cache in bytes
- **Default**: `4194304` (4 MB)
- **Example**: `AudioFootprintInBytes = 4194304`

#### `MinSampleVolume` *(v1.04)*
- **Type**: `Real`
- **Description**: Minimum volume threshold - sounds quieter than this are culled for performance
- **Default**: `2.0`
- **Example**: `MinSampleVolume = 2.0`

### Volume Settings

#### `DefaultSoundVolume` *(v1.04)*
- **Type**: `Real` (percentage)
- **Description**: Default volume for sound effects (never changed by game - read-only)
- **Default**: `80%` (0.8)
- **Example**: `DefaultSoundVolume = 80%`

#### `Default3DSoundVolume` *(v1.04)*
- **Type**: `Real` (percentage)
- **Description**: Default volume for 3D sound effects (never changed by game - read-only)
- **Default**: `80%` (0.8)
- **Example**: `Default3DSoundVolume = 80%`

#### `DefaultSpeechVolume` *(v1.04)*
- **Type**: `Real` (percentage)
- **Description**: Default volume for speech/voice (never changed by game - read-only)
- **Default**: `70%` (0.7)
- **Example**: `DefaultSpeechVolume = 70%`

#### `DefaultMusicVolume` *(v1.04)*
- **Type**: `Real` (percentage)
- **Description**: Default volume for music (never changed by game - read-only)
- **Default**: `55%` (0.55)
- **Example**: `DefaultMusicVolume = 55%`

#### `DefaultMoneyTransactionVolume` *(v1.04)*
- **Type**: `Real` (percentage)
- **Description**: Default volume for money deposit/withdraw sounds
- **Default**: `100%` (Generals), `0%` (Zero Hour - originally broken)
- **Example**: `DefaultMoneyTransactionVolume = 100%`

#### `Relative2DVolume` *(v1.04)*
- **Type**: `Real` (percentage)
- **Description**: Relative volume adjustment between 2D and 3D sounds
- **Behavior**:
  - Negative values: 2D sounds = 100% - |x|%, 3D sounds = 100%
  - Positive values: 2D sounds = 100%, 3D sounds = 100% - x%
  - Zero: Both play at same volume
- **Default**: `-10%`
- **Example**: `Relative2DVolume = -10%`

### 3D Audio Settings

#### `GlobalMinRange` *(v1.04)*
- **Type**: `Int`
- **Description**: Minimum audible range for 3D audio when global type is specified
- **Default**: `5000`
- **Example**: `GlobalMinRange = 5000`

#### `GlobalMaxRange` *(v1.04)*
- **Type**: `Int`
- **Description**: Maximum audible range for 3D audio when global type is specified
- **Default**: `500000`
- **Example**: `GlobalMaxRange = 500000`

#### `Preferred3DHW1` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: First preferred 3D audio hardware provider
- **Default**: `"Creative Labs EAX (TM)"`
- **Example**: `Preferred3DHW1 = "Creative Labs EAX (TM)"`

#### `Preferred3DHW2` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Second preferred 3D audio hardware provider
- **Default**: `"Aureal A3D Interactive (TM)"`
- **Example**: `Preferred3DHW2 = "Aureal A3D Interactive (TM)"`

#### `Preferred3DSW` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Preferred 3D audio software fallback
- **Default**: `"Miles Fast 2D Positional Audio"`
- **Example**: `Preferred3DSW = "Miles Fast 2D Positional Audio"`

### Microphone Settings

#### `MicrophoneDesiredHeightAboveTerrain` *(v1.04)*
- **Type**: `Real`
- **Description**: Desired height of the virtual microphone above terrain for improved panning
- **Purpose**: Improves audio positioning between aircraft and ground vehicles
- **Default**: `50.0`
- **Example**: `MicrophoneDesiredHeightAboveTerrain = 50.0`

#### `MicrophoneMaxPercentageBetweenGroundAndCamera` *(v1.04)*
- **Type**: `Real` (percentage)
- **Description**: Maximum percentage of distance between ground and camera for microphone positioning
- **Purpose**: Prevents microphone from going behind camera during close zoom
- **Default**: `33.3%`
- **Example**: `MicrophoneMaxPercentageBetweenGroundAndCamera = 33.3%`

### Zoom Audio Settings

#### `ZoomMinDistance` *(v1.04)*
- **Type**: `Real`
- **Description**: Minimum distance from microphone to apply full zoom audio bonus
- **Default**: `130.0`
- **Example**: `ZoomMinDistance = 130.0`

#### `ZoomMaxDistance` *(v1.04)*
- **Type**: `Real`
- **Description**: Maximum distance from microphone to receive any zoom audio bonus
- **Default**: `425.0`
- **Example**: `ZoomMaxDistance = 425.0`

#### `ZoomSoundVolumePercentageAmount` *(v1.04)*
- **Type**: `Real` (percentage)
- **Description**: Amount of 3D sound volume dedicated to zoom audio effects
- **Note**: Higher values reduce normal sound volume range
- **Default**: `20%`
- **Example**: `ZoomSoundVolumePercentageAmount = 20%`

#### `TimeBetweenDrawableSounds` *(v1.04)*
- **Type**: `Int` (milliseconds)
- **Description**: Time interval between ambient drawable sound attempts
- **Purpose**: Performance optimization for frequently culled ambient sounds
- **Default**: `1000`
- **Example**: `TimeBetweenDrawableSounds = 1000`

#### `TimeToFadeAudio` *(v1.04)*
- **Type**: `Int` (milliseconds)
- **Description**: Duration for audio fade in/out transitions
- **Default**: `2000`
- **Example**: `TimeToFadeAudio = 2000`

## Examples

### Basic Audio Settings
```ini
AudioSettings
  AudioRoot = Data\Audio
  SoundsFolder = Sounds
  MusicFolder = Tracks
  StreamingFolder = Speech
  SoundsExtension = wav
  UseDigital = Yes
  UseMidi = No
  OutputRate = 44100
  OutputBits = 16
  OutputChannels = 2
  SampleCount2D = 4
  SampleCount3D = 25
  StreamCount = 3
  AudioFootprintInBytes = 4194304
  MinSampleVolume = 2.0
  DefaultSoundVolume = 80%
  Default3DSoundVolume = 80%
  DefaultSpeechVolume = 70%
  DefaultMusicVolume = 55%
  Relative2DVolume = -10%
  MicrophoneDesiredHeightAboveTerrain = 50.0
  MicrophoneMaxPercentageBetweenGroundAndCamera = 33.3%
  ZoomMinDistance = 130.0
  ZoomMaxDistance = 425.0
  ZoomSoundVolumePercentageAmount = 20%
  TimeBetweenDrawableSounds = 1000
  TimeToFadeAudio = 2000
End
```

### High Performance Settings
```ini
AudioSettings
  AudioRoot = Data\Audio
  SoundsFolder = Sounds
  MusicFolder = Tracks
  StreamingFolder = Speech
  SoundsExtension = wav
  UseDigital = Yes
  UseMidi = No
  OutputRate = 22050
  OutputBits = 16
  OutputChannels = 2
  SampleCount2D = 2
  SampleCount3D = 15
  StreamCount = 2
  AudioFootprintInBytes = 2097152
  MinSampleVolume = 5.0
  DefaultSoundVolume = 80%
  Default3DSoundVolume = 80%
  DefaultSpeechVolume = 70%
  DefaultMusicVolume = 55%
  Relative2DVolume = -10%
  MicrophoneDesiredHeightAboveTerrain = 50.0
  MicrophoneMaxPercentageBetweenGroundAndCamera = 33.3%
  ZoomMinDistance = 130.0
  ZoomMaxDistance = 425.0
  ZoomSoundVolumePercentageAmount = 20%
  TimeBetweenDrawableSounds = 1500
  TimeToFadeAudio = 1000
End
```

### High Quality Settings
```ini
AudioSettings
  AudioRoot = Data\Audio
  SoundsFolder = Sounds
  MusicFolder = Tracks
  StreamingFolder = Speech
  SoundsExtension = wav
  UseDigital = Yes
  UseMidi = No
  OutputRate = 48000
  OutputBits = 16
  OutputChannels = 2
  SampleCount2D = 8
  SampleCount3D = 50
  StreamCount = 5
  AudioFootprintInBytes = 8388608
  MinSampleVolume = 1.0
  DefaultSoundVolume = 80%
  Default3DSoundVolume = 80%
  DefaultSpeechVolume = 70%
  DefaultMusicVolume = 55%
  Relative2DVolume = -10%
  MicrophoneDesiredHeightAboveTerrain = 50.0
  MicrophoneMaxPercentageBetweenGroundAndCamera = 33.3%
  ZoomMinDistance = 130.0
  ZoomMaxDistance = 425.0
  ZoomSoundVolumePercentageAmount = 20%
  TimeBetweenDrawableSounds = 500
  TimeToFadeAudio = 3000
End
```

## Best Practices

### Performance Optimization

1. **Adjust Sample Counts**: Lower `SampleCount2D` and `SampleCount3D` for better performance on older systems
2. **Reduce Audio Cache**: Lower `AudioFootprintInBytes` to save memory
3. **Increase Min Volume**: Higher `MinSampleVolume` values cull more sounds for better performance
4. **Lower Sample Rate**: Use `22050` instead of `44100` for better performance with minimal quality loss

### Quality Settings

1. **Use High Sample Rates**: `44100` or `48000` for best audio quality
2. **Increase Sample Counts**: Higher values allow more simultaneous sounds
3. **Lower Min Volume**: Allows quieter sounds to play
4. **Increase Audio Cache**: More memory for better audio streaming

### 3D Audio Tuning

1. **Microphone Height**: Keep `MicrophoneDesiredHeightAboveTerrain` around 50 for good aircraft/ground balance
2. **Zoom Settings**: Adjust `ZoomMinDistance` and `ZoomMaxDistance` for optimal zoom audio behavior
3. **Volume Balance**: Use `Relative2DVolume` to balance UI sounds vs world sounds

### File Organization

1. **Consistent Paths**: Use consistent folder structure across all audio files
2. **File Extensions**: Stick to `.wav` for best compatibility
3. **Streaming Audio**: Place large files (music, speech) in the streaming folder

## Template

```ini
AudioSettings
    AudioRoot = Data\Audio                    ; // Base directory for audio files *(v1.04)*
    SoundsFolder = Sounds                     ; // Sound effects subfolder *(v1.04)*
    MusicFolder = Tracks                      ; // Music files subfolder *(v1.04)*
    StreamingFolder = Speech                  ; // Streaming audio subfolder *(v1.04)*
    SoundsExtension = wav                     ; // Sound file extension *(v1.04)*
    UseDigital = Yes                          ; // Use digital audio output *(v1.04)*
    UseMidi = No                             ; // Use MIDI audio *(v1.04)*
    OutputRate = 44100                       ; // Audio sample rate in Hz *(v1.04)*
    OutputBits = 16                          ; // Audio bit depth *(v1.04)*
    OutputChannels = 2                       ; // Number of audio channels *(v1.04)*
    SampleCount2D = 4                        ; // Max 2D audio samples *(v1.04)*
    SampleCount3D = 25                       ; // Max 3D audio samples *(v1.04)*
    StreamCount = 3                          ; // Max streaming audio sources *(v1.04)*
    AudioFootprintInBytes = 4194304          ; // Audio cache memory limit *(v1.04)*
    MinSampleVolume = 2.0                    ; // Minimum volume threshold *(v1.04)*
    DefaultSoundVolume = 80%                 ; // Default sound effects volume *(v1.04)*
    Default3DSoundVolume = 80%               ; // Default 3D sound volume *(v1.04)*
    DefaultSpeechVolume = 70%                ; // Default speech volume *(v1.04)*
    DefaultMusicVolume = 55%                 ; // Default music volume *(v1.04)*
    DefaultMoneyTransactionVolume = 100%     ; // Default money transaction volume *(v1.04)*
    Relative2DVolume = -10%                  ; // 2D/3D volume balance *(v1.04)*
    GlobalMinRange = 5000                    ; // Min 3D audio range *(v1.04)*
    GlobalMaxRange = 500000                  ; // Max 3D audio range *(v1.04)*
    Preferred3DHW1 = "Creative Labs EAX (TM)" ; // First 3D hardware preference *(v1.04)*
    Preferred3DHW2 = "Aureal A3D Interactive (TM)" ; // Second 3D hardware preference *(v1.04)*
    Preferred3DSW = "Miles Fast 2D Positional Audio" ; // 3D software fallback *(v1.04)*
    MicrophoneDesiredHeightAboveTerrain = 50.0 ; // Virtual microphone height *(v1.04)*
    MicrophoneMaxPercentageBetweenGroundAndCamera = 33.3% ; // Microphone positioning limit *(v1.04)*
    ZoomMinDistance = 130.0                  ; // Min distance for zoom audio *(v1.04)*
    ZoomMaxDistance = 425.0                  ; // Max distance for zoom audio *(v1.04)*
    ZoomSoundVolumePercentageAmount = 20%    ; // Zoom audio volume amount *(v1.04)*
    TimeBetweenDrawableSounds = 1000         ; // Time between ambient sounds *(v1.04)*
    TimeToFadeAudio = 2000                   ; // Audio fade duration *(v1.04)*
End
```

## Notes

- AudioSettings provides comprehensive audio configuration for immersive sound experiences
- The configuration manages audio file paths, hardware settings, and volume levels across all game modes
- Audio operations create realistic 3D positioning and dynamic volume adjustments
- Audio management ensures optimal performance and quality for different hardware capabilities
- This configuration is essential for audio system optimization and player experience
- Audio coordination creates consistent sound behavior across different game scenarios
- File path settings organize audio assets in logical directory structures
- Hardware preferences control 3D audio implementation and fallback options
- Volume settings provide default levels for different audio categories
- 3D audio settings create realistic spatial sound positioning
- Microphone system improves audio positioning between aircraft and ground units
- Zoom audio creates dynamic volume changes based on camera distance
- Performance settings balance audio quality with system resources
- AudioSettings is a global configuration that affects the entire audio system
- Default volume values are read-only and never modified by the game
- The microphone system improves 3D audio positioning for better immersion
- Zoom audio settings create dynamic volume changes based on camera distance
- Hardware preferences are tried in order (HW1, HW2, then software fallback)
- Money transaction volume was originally broken in Zero Hour (set to 0%) but can be fixed
- Audio cache size directly affects memory usage and streaming performance
- Sample counts may be limited by hardware capabilities regardless of settings
- The audio system automatically falls back to software 3D audio if hardware is unavailable
- Time-based settings (fade, drawable sounds) help balance performance vs audio quality

## Source Files

- Header: [`Core/GameEngine/Include/Common/AudioSettings.h`](../../Core/GameEngine/Include/Common/AudioSettings.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/Common/INI/INI.cpp`](../../GeneralsMD/Code/GameEngine/Source/Common/INI/INI.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet 
