# SpecialPower INI Documentation

## Overview

The `SpecialPower` INI file contains special power configuration settings and parameters for special abilities and power systems. Special powers are unique abilities that can be activated by specific units, buildings, or factions to provide tactical advantages, such as calling in airstrikes, deploying special units, or using powerful effects.

## Usage

Special power templates are defined in INI files and specify the configuration for special abilities used by units and buildings. This is a **template configuration system** that defines special power properties and behavior. The special power system provides unique tactical abilities for different factions and units.

**Limitations**:
- Special powers are limited to predefined power types
- Activation requires specific science prerequisites
- Powers have cooldown periods between uses
- Some powers require specific target types or locations

**Conditions**:
- Special powers provide tactical advantages through unique abilities
- The configuration handles power types, timing, costs, and effects
- Special power operations create strategic gameplay opportunities
- Special power management ensures balanced and fair gameplay
- **Multiple instances behavior**: Special power templates are shared between multiple objects

**Dependencies**:
- Uses science system for prerequisite checking
- Uses audio system for power activation sounds
- Integrates with the command system for power activation
- Uses the special power module system for execution
- Referenced by units, buildings, and other game objects

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Basic Power Configuration](#basic-power-configuration)
  - [Timing and Cooldown](#timing-and-cooldown)
  - [Audio Configuration](#audio-configuration)
  - [Visual and UI Configuration](#visual-and-ui-configuration)
  - [Advanced Configuration](#advanced-configuration)
- [SpecialPowerType Values](#specialpowertype-values)
- [AcademyClassificationType Values](#academyclassificationtype-values)
- [Examples](#examples)
- [Best Practices](#best-practices)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)

## Properties

### Basic Power Configuration *(v1.04)*

#### `Enum` *(v1.04)*
- **Type**: `SpecialPowerType`
- **Description**: Type of special power that determines its behavior and category. This enum value is used by the game engine to identify and process the power correctly.
- **Default**: `SPECIAL_INVALID`
- **Available Values**: See [SpecialPowerType Values](#specialpowertype-values) section
- **Example**: `Enum = SPECIAL_DAISY_CUTTER` // Daisy cutter bombing special power

#### `RequiredScience` *(v1.04)*
- **Type**: `ScienceType` (see [Science documentation](Science.md))
- **Description**: Science prerequisite required to use this special power. When set, the player must have researched this science to activate the power. When `SCIENCE_INVALID` (default), no science is required.
- **Default**: `SCIENCE_INVALID`
- **Example**: `RequiredScience = SCIENCE_ADVANCED_RADAR` // Requires advanced radar science

#### `CostPerUse` *(v1.04)*
- **Type**: `UnsignedInt`
- **Description**: Cost in credits to use this special power. When set to a value greater than 0, the player must pay this cost each time the power is activated.
- **Default**: `0`
- **Example**: `CostPerUse = 500` // Costs 500 credits per use

### Timing and Cooldown *(v1.04)*

#### `ReloadTime` *(v1.04)*
- **Type**: `UnsignedInt` (frames)
- **Description**: Time in frames before this special power can be used again after activation. This creates a cooldown period between power uses.
- **Default**: `0`
- **Example**: `ReloadTime = 3000` // 50 second cooldown (at 60 FPS)

#### `SharedSyncedTimer` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether this special power shares its timer across all of the player's command centers. When true, using the power at one command center affects all command centers.
- **Default**: `No`
- **Example**: `SharedSyncedTimer = Yes` // Timer shared across all command centers

#### `DetectionTime` *(v1.04)*
- **Type**: `UnsignedInt` (frames)
- **Description**: Time in frames after using infiltration powers (like defection) before ex-comrades realize what happened. Used for stealth-based special powers.
- **Default**: `0`
- **Example**: `DetectionTime = 1800` // 30 second detection delay (at 60 FPS)

### Audio Configuration *(v1.04)*

#### `InitiateSound` *(v1.04)*
- **Type**: `AudioEventRTS`
- **Description**: Sound to play when the special power is initiated by the player. This sound plays at the activating unit or building.
- **Default**: None
- **Example**: `InitiateSound = EVAAmericaAirstrikeIncoming` // Plays airstrike announcement

#### `InitiateAtLocationSound` *(v1.04)*
- **Type**: `AudioEventRTS`
- **Description**: Sound to play at the target location when the special power is activated. This provides audio feedback at the impact or effect location.
- **Default**: None
- **Example**: `InitiateAtLocationSound = EVAAmericaAirstrikeIncoming` // Plays sound at target

### Visual and UI Configuration *(v1.04)*

#### `PublicTimer` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether to display a countdown timer for this special power that all players can see. When true, shows when the power will be available again.
- **Default**: `No`
- **Example**: `PublicTimer = Yes` // Shows public countdown timer

#### `ShortcutPower` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether this special power can be activated from the side panel shortcut interface. When true, allows quick access to the power.
- **Default**: `No`
- **Example**: `ShortcutPower = Yes` // Available in shortcut panel

#### `RadiusCursorRadius` *(v1.04)*
- **Type**: `Real`
- **Description**: Size of the radius cursor shown when targeting this special power. When set to a value greater than 0, displays a targeting circle.
- **Default**: `0`
- **Example**: `RadiusCursorRadius = 100.0` // 100-unit radius cursor

### Advanced Configuration *(v1.04)*

#### `ViewObjectDuration` *(v1.04)*
- **Type**: `UnsignedInt` (frames)
- **Description**: Lifetime in frames of a view object created to watch the special power effect. Used for powers that create temporary observation objects.
- **Default**: `0`
- **Example**: `ViewObjectDuration = 600` // 10 second view duration (at 60 FPS)

#### `ViewObjectRange` *(v1.04)*
- **Type**: `Real`
- **Description**: Vision range of the view object created by this special power. Determines how far the temporary observer can see.
- **Default**: `0`
- **Example**: `ViewObjectRange = 200.0` // 200-unit vision range

#### `AcademyClassify` *(v1.04)*
- **Type**: `AcademyClassificationType`
- **Description**: Classification used by the academy system to evaluate advice based on player actions. This helps the academy provide relevant tips.
- **Default**: `ACT_NONE`
- **Available Values**: See [AcademyClassificationType Values](#academyclassificationtype-values) section
- **Example**: `AcademyClassify = ACT_SUPERPOWER` // Classified as superpower for academy

## SpecialPowerType Values *(v1.04)*

The SpecialPowerType enum defines all available special power types:

### Superweapons *(v1.04)*
- **`SPECIAL_INVALID`** *(v1.04)* - Invalid or uninitialized power
- **`SPECIAL_DAISY_CUTTER`** *(v1.04)* - Daisy cutter bombing
- **`SPECIAL_PARADROP_AMERICA`** *(v1.04)* - American paradrop
- **`SPECIAL_CARPET_BOMB`** *(v1.04)* - Carpet bombing
- **`SPECIAL_CLUSTER_MINES`** *(v1.04)* - Cluster mine deployment
- **`SPECIAL_EMP_PULSE`** *(v1.04)* - EMP pulse attack
- **`SPECIAL_NAPALM_STRIKE`** *(v1.04)* - Napalm strike
- **`SPECIAL_CASH_HACK`** *(v1.04)* - Cash hacking ability
- **`SPECIAL_NEUTRON_MISSILE`** *(v1.04)* - Neutron missile
- **`SPECIAL_SPY_SATELLITE`** *(v1.04)* - Spy satellite
- **`SPECIAL_DEFECTOR`** *(v1.04)* - Defector ability
- **`SPECIAL_TERROR_CELL`** *(v1.04)* - Terror cell deployment
- **`SPECIAL_AMBUSH`** *(v1.04)* - Ambush ability
- **`SPECIAL_BLACK_MARKET_NUKE`** *(v1.04)* - Black market nuke
- **`SPECIAL_ANTHRAX_BOMB`** *(v1.04)* - Anthrax bomb
- **`SPECIAL_SCUD_STORM`** *(v1.04)* - Scud storm
- **`SPECIAL_DEMORALIZE`** *(v1.04)* - Demoralization ability
- **`SPECIAL_CRATE_DROP`** *(v1.04)* - Supply crate drop
- **`SPECIAL_A10_THUNDERBOLT_STRIKE`** *(v1.04)* - A-10 Thunderbolt strike
- **`SPECIAL_DETONATE_DIRTY_NUKE`** *(v1.04)* - Dirty nuke detonation
- **`SPECIAL_ARTILLERY_BARRAGE`** *(v1.04)* - Artillery barrage

### Special Abilities *(v1.04)*
- **`SPECIAL_MISSILE_DEFENDER_LASER_GUIDED_MISSILES`** *(v1.04)* - Laser guided missiles
- **`SPECIAL_REMOTE_CHARGES`** *(v1.04)* - Remote charges
- **`SPECIAL_TIMED_CHARGES`** *(v1.04)* - Timed charges
- **`SPECIAL_HELIX_NAPALM_BOMB`** *(v1.04)* - Helix napalm bomb
- **`SPECIAL_HACKER_DISABLE_BUILDING`** *(v1.04)* - Building disable hack
- **`SPECIAL_TANKHUNTER_TNT_ATTACK`** *(v1.04)* - Tank hunter TNT attack
- **`SPECIAL_BLACKLOTUS_CAPTURE_BUILDING`** *(v1.04)* - Black Lotus building capture
- **`SPECIAL_BLACKLOTUS_DISABLE_VEHICLE_HACK`** *(v1.04)* - Black Lotus vehicle hack
- **`SPECIAL_BLACKLOTUS_STEAL_CASH_HACK`** *(v1.04)* - Black Lotus cash steal
- **`SPECIAL_INFANTRY_CAPTURE_BUILDING`** *(v1.04)* - Infantry building capture
- **`SPECIAL_RADAR_VAN_SCAN`** *(v1.04)* - Radar van scan
- **`SPECIAL_SPY_DRONE`** *(v1.04)* - Spy drone
- **`SPECIAL_DISGUISE_AS_VEHICLE`** *(v1.04)* - Vehicle disguise
- **`SPECIAL_BOOBY_TRAP`** *(v1.04)* - Booby trap
- **`SPECIAL_REPAIR_VEHICLES`** *(v1.04)* - Vehicle repair
- **`SPECIAL_PARTICLE_UPLINK_CANNON`** *(v1.04)* - Particle cannon uplink
- **`SPECIAL_CASH_BOUNTY`** *(v1.04)* - Cash bounty
- **`SPECIAL_CHANGE_BATTLE_PLANS`** *(v1.04)* - Battle plan change
- **`SPECIAL_CIA_INTELLIGENCE`** *(v1.04)* - CIA intelligence
- **`SPECIAL_CLEANUP_AREA`** *(v1.04)* - Area cleanup
- **`SPECIAL_LAUNCH_BAIKONUR_ROCKET`** *(v1.04)* - Baikonur rocket launch
- **`SPECIAL_SPECTRE_GUNSHIP`** *(v1.04)* - Spectre gunship
- **`SPECIAL_GPS_SCRAMBLER`** *(v1.04)* - GPS scrambler
- **`SPECIAL_FRENZY`** *(v1.04)* - Frenzy ability
- **`SPECIAL_SNEAK_ATTACK`** *(v1.04)* - Sneak attack

### Faction-Specific Variants *(v1.04)*
- **`SPECIAL_CHINA_CARPET_BOMB`** *(v1.04)* - China carpet bomb
- **`SPECIAL_LEAFLET_DROP`** *(v1.04)* - Leaflet drop
- **`SPECIAL_COMMUNICATIONS_DOWNLOAD`** *(v1.04)* - Communications download
- **`SPECIAL_TANK_PARADROP`** *(v1.04)* - Tank paradrop
- **`SPECIAL_BATTLESHIP_BOMBARDMENT`** *(v1.04)* - Battleship bombardment

## AcademyClassificationType Values *(v1.04)*

The AcademyClassificationType enum defines academy classifications:

- **`ACT_NONE`** *(v1.04)* - No academy classification
- **`ACT_UPGRADE_RADAR`** *(v1.04)* - Classified as radar upgrade for academy advice
- **`ACT_SUPERPOWER`** *(v1.04)* - Classified as superpower for academy advice

## Examples

### Basic Airstrike Power
```ini
SpecialPower SpecialPowerAmericaAirstrike
    Enum = SPECIAL_DAISY_CUTTER
    ReloadTime = 3000
    RequiredScience = SCIENCE_INVALID
    CostPerUse = 0
    PublicTimer = Yes
    ShortcutPower = Yes
    InitiateSound = EVAAmericaAirstrikeIncoming
    RadiusCursorRadius = 100.0
    AcademyClassify = ACT_SUPERPOWER
End
```

### Expensive Superweapon
```ini
SpecialPower SpecialPowerNeutronMissile
    Enum = SPECIAL_NEUTRON_MISSILE
    ReloadTime = 6000
    RequiredScience = SCIENCE_NEUTRON_MISSILES
    CostPerUse = 2000
    PublicTimer = Yes
    ShortcutPower = Yes
    InitiateSound = EVAAmericaNeutronMissileIncoming
    InitiateAtLocationSound = EVAAmericaNeutronMissileIncoming
    RadiusCursorRadius = 200.0
    AcademyClassify = ACT_SUPERPOWER
End
```

### Stealth Infiltration Power
```ini
SpecialPower SpecialPowerDefector
    Enum = SPECIAL_DEFECTOR
    ReloadTime = 4500
    RequiredScience = SCIENCE_INFILTRATION
    CostPerUse = 1000
    DetectionTime = 1800
    InitiateSound = EVAGLAInfiltrationComplete
    AcademyClassify = ACT_NONE
End
```

### Unit Special Ability
```ini
SpecialPower SpecialPowerRepairVehicles
    Enum = SPECIAL_REPAIR_VEHICLES
    ReloadTime = 1200
    RequiredScience = SCIENCE_INVALID
    CostPerUse = 0
    InitiateSound = EVAAmericaRepairComplete
    AcademyClassify = ACT_NONE
End
```

### Shared Command Center Power
```ini
SpecialPower SpecialPowerParadropAmerica
    Enum = SPECIAL_PARADROP_AMERICA
    ReloadTime = 2400
    RequiredScience = SCIENCE_INVALID
    CostPerUse = 0
    SharedSyncedTimer = Yes
    InitiateSound = EVAAmericaParadropIncoming
    AcademyClassify = ACT_SUPERPOWER
End
```

## Best Practices

### Power Balance Design

1. **Cooldown Timing**: Balance cooldown times to prevent spam while keeping powers useful
2. **Cost Management**: Use appropriate costs to prevent overuse of powerful abilities
3. **Science Requirements**: Require meaningful science prerequisites for advanced powers
4. **Power Progression**: Create logical progression from basic to advanced powers

### Audio-Visual Feedback

1. **Sound Design**: Use distinctive sounds for power activation and effects
2. **Visual Indicators**: Use radius cursors for area-effect powers
3. **Timer Display**: Show public timers for strategic powers
4. **Shortcut Access**: Enable shortcut access for frequently used powers

### Strategic Integration

1. **Faction Identity**: Create unique powers that reflect faction characteristics
2. **Counter-Play**: Design powers that can be countered by opponents
3. **Resource Management**: Balance power costs with resource availability
4. **Situational Use**: Create powers that are effective in specific situations

### Performance Optimization

1. **Shared Timers**: Use shared timers for command center powers
2. **Efficient Targeting**: Use appropriate targeting systems for different power types
3. **Effect Management**: Limit complex effects to prevent performance issues
4. **Memory Usage**: Minimize memory usage for frequently used powers

### Academy Integration

1. **Classification**: Use appropriate academy classifications for advice
2. **Learning Curve**: Design powers that help new players learn the game
3. **Strategic Depth**: Create powers that demonstrate advanced strategies
4. **Feedback Systems**: Use academy feedback to improve power design

## Template

```ini
SpecialPower SpecialPowerName
    ; Basic Configuration
    Enum = SPECIAL_INVALID                 ; // Special power type *(v1.04)*
    RequiredScience = SCIENCE_INVALID      ; // Science prerequisite *(v1.04)*
    CostPerUse = 0                        ; // Credit cost per use *(v1.04)*
    
    ; Timing Configuration
    ReloadTime = 0                        ; // Cooldown time (frames) *(v1.04)*
    SharedSyncedTimer = No                ; // Share timer across command centers *(v1.04)*
    DetectionTime = 0                     ; // Stealth detection delay (frames) *(v1.04)*
    
    ; Audio Configuration
    InitiateSound =                       ; // Activation sound *(v1.04)*
    InitiateAtLocationSound =             ; // Target location sound *(v1.04)*
    
    ; UI Configuration
    PublicTimer = No                      ; // Show public countdown *(v1.04)*
    ShortcutPower = No                    ; // Available in shortcut panel *(v1.04)*
    RadiusCursorRadius = 0                ; // Targeting cursor radius *(v1.04)*
    
    ; Advanced Configuration
    ViewObjectDuration = 0                ; // View object lifetime (frames) *(v1.04)*
    ViewObjectRange = 0                   ; // View object vision range *(v1.04)*
    AcademyClassify = ACT_NONE            ; // Academy classification *(v1.04)*
End
```

## Notes

- Special powers provide unique tactical abilities for different factions and units
- The configuration manages power types, timing, costs, and effects for balanced gameplay
- Special power operations create strategic opportunities and tactical depth
- Special power management ensures fair and engaging gameplay experiences
- This configuration is essential for creating diverse and interesting special abilities
- Special power coordination creates faction identity and strategic variety
- Powers can be balanced through cooldown times, costs, and science requirements
- The system supports both superweapons and unit-specific special abilities
- Special powers are shared between multiple objects to optimize memory usage
- Powers are activated through the command system and integrated with the UI
- Visual and audio effects provide clear feedback for power activation
- The system integrates with the science system for prerequisite checking
- Academy classification helps provide relevant advice to players
- Special power templates are defined in INI files and loaded by the special power system
- Power parameters can be adjusted to balance gameplay and prevent abuse
- The system supports complex power interactions and strategic depth
- Special powers enhance gameplay by providing unique tactical options
- Power timing and synchronization are crucial for balanced multiplayer gameplay
- The system can be optimized for different performance levels and hardware capabilities
- Special powers create memorable moments and strategic decision points

## Source Files

**Base Class:** [SpecialPowerTemplate](../../GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h)
- Header: [`GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h`](../../GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/Common/RTS/SpecialPower.cpp`](../../GeneralsMD/Code/GameEngine/Source/Common/RTS/SpecialPower.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet