# Eva INI Documentation

## Overview

The `Eva` INI file contains EVA (Electronic Video Agent) configuration settings and parameters for user interface voice systems and tactical notifications. EVA provides automated voice announcements and alerts to inform players about important game events, tactical situations, and system status.

## Usage

EVA templates are defined in INI files and specify the voice announcements and alerts that play during gameplay. This is a **template configuration system** that defines voice response behavior. The EVA system provides tactical information and status updates through voice announcements.

**Limitations**:
- EVA is limited to predefined message types and voice responses
- Voice responses are fixed and cannot be dynamically modified
- Message timing is controlled by fixed parameters
- Voice responses depend on proper audio system configuration

**Conditions**:
- EVA manages voice announcements and tactical notifications
- The configuration handles message priorities, timing, and voice selection
- EVA operations provide tactical information and status updates
- EVA management ensures appropriate voice feedback for game events
- **Multiple instances behavior**: Only one EVA system is active per player

**Dependencies**:
- Uses audio system for voice playback
- Integrates with the game event system for triggering
- Uses faction-specific voice systems for different sides
- Referenced by the game's notification system

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [EVA Check Info Properties](#eva-check-info-properties)
  - [EVA Side Sounds Properties](#eva-side-sounds-properties)
- [EvaMessage Values](#evamessage-values)
- [Examples](#examples)
- [Best Practices](#best-practices)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### EVA Check Info Properties *(v1.04)*

#### `Priority` *(v1.04)*
- **Type**: `UnsignedInt`
- **Description**: Message priority level. Higher values indicate more important messages that will be played in preference to lower priority messages.
- **Default**: `1`
- **Example**: `Priority = 10` // High priority message

#### `TimeBetweenChecksMS` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Minimum time between checks for this message type. Prevents spam by limiting how often the system checks if this message should play.
- **Default**: `30000` (30 seconds)
- **Example**: `TimeBetweenChecksMS = 15000` // Check every 15 seconds

#### `ExpirationTimeMS` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: How long the message remains active after being triggered. After this time, the message expires and stops playing.
- **Default**: `5000` (5 seconds)
- **Example**: `ExpirationTimeMS = 10000` // Message expires after 10 seconds

#### `SideSounds` *(v1.04)*
- **Type**: `EvaSideSounds` block
- **Description**: Faction-specific voice responses for this message. Different factions can have different voice actors and responses.
- **Default**: None
- **Example**: 
  ```
  SideSounds = ChinaSideSounds
  ```

### EVA Side Sounds Properties *(v1.04)*

#### `Side` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Faction identifier for this set of voice responses. Must match a valid faction name.
- **Default**: `""`
- **Example**: `Side = "China"` // China faction voice responses

#### `Sounds` *(v1.04)*
- **Type**: `AsciiStringList`
- **Description**: List of audio event names for voice responses. Multiple sounds can be specified for variety.
- **Default**: None
- **Example**: 
  ```
  Sounds = "EVA_China_LowPower1"
  Sounds = "EVA_China_LowPower2"
  ```

## EvaMessage Values *(v1.04)*

The EvaMessage system accepts the following values:

- **`EVA_LowPower`** *(v1.04)* - Low power warning
- **`EVA_InsufficientFunds`** *(v1.04)* - Insufficient funds notification
- **`EVA_SuperweaponDetected_Own_ParticleCannon`** *(v1.04)* - Own particle cannon detected
- **`EVA_SuperweaponDetected_Own_Nuke`** *(v1.04)* - Own nuclear weapon detected
- **`EVA_SuperweaponDetected_Own_ScudStorm`** *(v1.04)* - Own SCUD storm detected
- **`EVA_SuperweaponDetected_Ally_ParticleCannon`** *(v1.04)* - Ally particle cannon detected
- **`EVA_SuperweaponDetected_Ally_Nuke`** *(v1.04)* - Ally nuclear weapon detected
- **`EVA_SuperweaponDetected_Ally_ScudStorm`** *(v1.04)* - Ally SCUD storm detected
- **`EVA_SuperweaponDetected_Enemy_ParticleCannon`** *(v1.04)* - Enemy particle cannon detected
- **`EVA_SuperweaponDetected_Enemy_Nuke`** *(v1.04)* - Enemy nuclear weapon detected
- **`EVA_SuperweaponDetected_Enemy_ScudStorm`** *(v1.04)* - Enemy SCUD storm detected
- **`EVA_SuperweaponLaunched_Own_ParticleCannon`** *(v1.04)* - Own particle cannon launched
- **`EVA_SuperweaponLaunched_Own_Nuke`** *(v1.04)* - Own nuclear weapon launched
- **`EVA_SuperweaponLaunched_Own_ScudStorm`** *(v1.04)* - Own SCUD storm launched
- **`EVA_SuperweaponLaunched_Ally_ParticleCannon`** *(v1.04)* - Ally particle cannon launched
- **`EVA_SuperweaponLaunched_Ally_Nuke`** *(v1.04)* - Ally nuclear weapon launched
- **`EVA_SuperweaponLaunched_Ally_ScudStorm`** *(v1.04)* - Ally SCUD storm launched
- **`EVA_SuperweaponLaunched_Enemy_ParticleCannon`** *(v1.04)* - Enemy particle cannon launched
- **`EVA_SuperweaponLaunched_Enemy_Nuke`** *(v1.04)* - Enemy nuclear weapon launched
- **`EVA_SuperweaponLaunched_Enemy_ScudStorm`** *(v1.04)* - Enemy SCUD storm launched
- **`EVA_SuperweaponReady_Own_ParticleCannon`** *(v1.04)* - Own particle cannon ready
- **`EVA_SuperweaponReady_Own_Nuke`** *(v1.04)* - Own nuclear weapon ready
- **`EVA_SuperweaponReady_Own_ScudStorm`** *(v1.04)* - Own SCUD storm ready
- **`EVA_SuperweaponReady_Ally_ParticleCannon`** *(v1.04)* - Ally particle cannon ready
- **`EVA_SuperweaponReady_Ally_Nuke`** *(v1.04)* - Ally nuclear weapon ready
- **`EVA_SuperweaponReady_Ally_ScudStorm`** *(v1.04)* - Ally SCUD storm ready
- **`EVA_SuperweaponReady_Enemy_ParticleCannon`** *(v1.04)* - Enemy particle cannon ready
- **`EVA_SuperweaponReady_Enemy_Nuke`** *(v1.04)* - Enemy nuclear weapon ready
- **`EVA_SuperweaponReady_Enemy_ScudStorm`** *(v1.04)* - Enemy SCUD storm ready
- **`EVA_BuldingLost`** *(v1.04)* - Building lost notification
- **`EVA_BaseUnderAttack`** *(v1.04)* - Base under attack warning
- **`EVA_AllyUnderAttack`** *(v1.04)* - Ally under attack notification
- **`EVA_BeaconDetected`** *(v1.04)* - Beacon detected notification
- **`EVA_EnemyBlackLotusDetected`** *(v1.04)* - Enemy Black Lotus detected
- **`EVA_EnemyJarmenKellDetected`** *(v1.04)* - Enemy Jarmen Kell detected
- **`EVA_EnemyColonelBurtonDetected`** *(v1.04)* - Enemy Colonel Burton detected
- **`EVA_OwnBlackLotusDetected`** *(v1.04)* - Own Black Lotus detected
- **`EVA_OwnJarmenKellDetected`** *(v1.04)* - Own Jarmen Kell detected
- **`EVA_OwnColonelBurtonDetected`** *(v1.04)* - Own Colonel Burton detected
- **`EVA_UnitLost`** *(v1.04)* - Unit lost notification
- **`EVA_GeneralLevelUp`** *(v1.04)* - General level up notification
- **`EVA_VehicleStolen`** *(v1.04)* - Vehicle stolen notification
- **`EVA_BuildingStolen`** *(v1.04)* - Building stolen notification
- **`EVA_CashStolen`** *(v1.04)* - Cash stolen notification
- **`EVA_UpgradeComplete`** *(v1.04)* - Upgrade complete notification
- **`EVA_BuildingBeingStolen`** *(v1.04)* - Building being stolen warning
- **`EVA_BuildingSabotaged`** *(v1.04)* - Building sabotaged notification
- **`EVA_SuperweaponLaunched_Own_GPS_Scrambler`** *(v1.04)* - Own GPS scrambler launched
- **`EVA_SuperweaponLaunched_Ally_GPS_Scrambler`** *(v1.04)* - Ally GPS scrambler launched
- **`EVA_SuperweaponLaunched_Enemy_GPS_Scrambler`** *(v1.04)* - Enemy GPS scrambler launched
- **`EVA_SuperweaponLaunched_Own_Sneak_Attack`** *(v1.04)* - Own sneak attack launched
- **`EVA_SuperweaponLaunched_Ally_Sneak_Attack`** *(v1.04)* - Ally sneak attack launched
- **`EVA_SuperweaponLaunched_Enemy_Sneak_Attack`** *(v1.04)* - Enemy sneak attack launched

## Examples

### Low Power Warning
```ini
EvaCheckInfo EVA_LowPower
    Priority = 5
    TimeBetweenChecksMS = 30000
    ExpirationTimeMS = 5000
    
    SideSounds = ChinaLowPowerSounds
End

EvaSideSounds ChinaLowPowerSounds
    Side = "China"
    Sounds = "EVA_China_LowPower1"
    Sounds = "EVA_China_LowPower2"
End
```

### Base Under Attack Warning
```ini
EvaCheckInfo EVA_BaseUnderAttack
    Priority = 10
    TimeBetweenChecksMS = 15000
    ExpirationTimeMS = 10000
    
    SideSounds = ChinaBaseAttackSounds
End

EvaSideSounds ChinaBaseAttackSounds
    Side = "China"
    Sounds = "EVA_China_BaseUnderAttack1"
    Sounds = "EVA_China_BaseUnderAttack2"
    Sounds = "EVA_China_BaseUnderAttack3"
End
```

### Nuclear Weapon Detected
```ini
EvaCheckInfo EVA_SuperweaponDetected_Enemy_Nuke
    Priority = 15
    TimeBetweenChecksMS = 60000
    ExpirationTimeMS = 15000
    
    SideSounds = ChinaNukeDetectedSounds
End

EvaSideSounds ChinaNukeDetectedSounds
    Side = "China"
    Sounds = "EVA_China_NukeDetected1"
    Sounds = "EVA_China_NukeDetected2"
End
```

### General Level Up Notification
```ini
EvaCheckInfo EVA_GeneralLevelUp
    Priority = 8
    TimeBetweenChecksMS = 5000
    ExpirationTimeMS = 3000
    
    SideSounds = ChinaGeneralLevelUpSounds
End

EvaSideSounds ChinaGeneralLevelUpSounds
    Side = "China"
    Sounds = "EVA_China_GeneralLevelUp1"
    Sounds = "EVA_China_GeneralLevelUp2"
End
```

## Best Practices

### Message Priority Design

1. **Critical Alerts**: Use high priorities (15+) for critical threats like nuclear weapons
2. **Tactical Warnings**: Use medium priorities (5-10) for base attacks and unit losses
3. **Status Updates**: Use low priorities (1-5) for routine notifications
4. **Balanced Priority**: Ensure important messages aren't overshadowed by less critical ones

### Timing Configuration

1. **Check Intervals**: Set appropriate check intervals to prevent spam
2. **Expiration Times**: Use longer expiration for critical messages
3. **Response Timing**: Balance responsiveness with performance
4. **Message Overlap**: Prevent multiple similar messages from playing simultaneously

### Faction-Specific Voices

1. **Voice Variety**: Provide multiple voice options for each message type
2. **Faction Consistency**: Maintain consistent voice actors per faction
3. **Audio Quality**: Ensure high-quality voice recordings
4. **Cultural Appropriateness**: Use appropriate voice actors for each faction

### Message Categories

1. **Superweapon Messages**: Group related superweapon notifications together
2. **Tactical Alerts**: Separate tactical warnings from status updates
3. **Hero Detection**: Use specific messages for hero unit detection
4. **Resource Management**: Provide clear notifications for resource issues

## Template

```ini
EvaCheckInfo EVA_MessageName
    Priority = 5                          ; // Message priority level *(v1.04)*
    TimeBetweenChecksMS = 30000           ; // Time between checks (ms) *(v1.04)*
    ExpirationTimeMS = 5000               ; // Message expiration time (ms) *(v1.04)*
    
    SideSounds = FactionMessageSounds     ; // Faction-specific voice responses *(v1.04)*
End

EvaSideSounds FactionMessageSounds
    Side = "FactionName"                  ; // Faction identifier *(v1.04)*
    Sounds = "EVA_Faction_Message1"       ; // First voice response *(v1.04)*
    Sounds = "EVA_Faction_Message2"       ; // Second voice response *(v1.04)*
    Sounds = "EVA_Faction_Message3"       ; // Third voice response *(v1.04)*
End
```

## Notes

- EVA provides automated voice announcements and tactical notifications during gameplay
- The configuration manages message priorities, timing, and faction-specific voice responses
- EVA operations create immersive audio feedback for important game events
- EVA management ensures appropriate voice guidance and tactical information
- This configuration is essential for player awareness and tactical decision-making
- EVA coordination creates consistent voice feedback across different game situations
- Message priorities control which notifications take precedence when multiple events occur
- Timing parameters prevent message spam and ensure appropriate response intervals
- Faction-specific voices provide immersive and culturally appropriate audio feedback
- The system supports multiple voice variations for each message type to avoid repetition
- EVA messages are triggered by game events and tactical situations
- Voice responses are played through the game's audio system
- The system integrates with the game's notification and event management systems
- EVA templates are defined in INI files and loaded by the EVA system
- Message timing and priority can be adjusted to balance information with gameplay flow
- The system supports different voice actors and responses for each faction
- EVA provides critical tactical information that helps players make informed decisions
- Voice announcements enhance immersion and provide audio cues for important events
- The system can be enabled/disabled to control audio feedback during gameplay

## Source Files

**Base Class:** [EvaCheckInfo](../../GeneralsMD/Code/GameEngine/Include/GameClient/Eva.h)
- Header: [`GeneralsMD/Code/GameEngine/Include/GameClient/Eva.h`](../../GeneralsMD/Code/GameEngine/Include/GameClient/Eva.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameClient/Eva.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameClient/Eva.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet
