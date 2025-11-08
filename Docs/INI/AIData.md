# AIData INI Documentation

## Overview

The `AIData` INI file contains comprehensive AI configuration settings and parameters for game artificial intelligence systems. It controls AI behavior patterns, build orders, resource management, combat tactics, and strategic decision-making for computer-controlled opponents. This configuration file is essential for defining how AI players behave in both campaign and skirmish modes.

## Usage

The AIData configuration is used by the game engine to control AI player behavior across all game modes. This is a **global configuration file** that affects all AI-controlled players. The settings in this file determine AI strategy, resource allocation, unit production, and tactical decision-making.

**Limitations**:
- AI behavior is limited by the parameters defined in this configuration
- AI capabilities depend on proper faction-specific settings
- AI performance varies based on difficulty settings and skill configurations
- AI effectiveness is constrained by game balance parameters

**Conditions**:
- AIData manages AI behavior across all game modes and factions
- The configuration handles AI strategy, resource management, and tactical decision-making
- AI operations provide computer-controlled opponent capabilities
- AI management creates realistic and challenging gameplay experiences
- **Multiple instances behavior**: Different AI players can have different configurations through faction-specific settings

**Dependencies**:
- Uses faction-specific AI configurations for different play styles
- Integrates with game engine AI systems for behavior implementation
- Uses build order systems for structure and unit production

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [General AI Settings](#general-ai-settings)
  - [Resource Management](#resource-management)
  - [Build Order Settings](#build-order-settings)
  - [Combat Behavior](#combat-behavior)
  - [Guard Behavior](#guard-behavior)
  - [Retaliation Settings](#retaliation-settings)
  - [Faction-Specific Settings](#faction-specific-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### General AI Settings *(v1.04)*

#### `StructureSeconds` *(v1.04)*
- **Type**: `Float`
- **Description**: AI tries to build a new structure every N seconds. Controls the frequency of structure construction by AI players.
- **Default**: `5.0`
- **Example**: `StructureSeconds = 3.0` // AI builds structures more frequently

#### `TeamSeconds` *(v1.04)*
- **Type**: `Int`
- **Description**: AI tries to build a new team every N seconds. Controls the frequency of team formation by AI players.
- **Default**: `15`
- **Example**: `TeamSeconds = 10` // AI forms teams more frequently

#### `ForceSkirmishAI` *(v1.04)*
- **Type**: `Bool`
- **Description**: Use skirmish instead of solo AI. For development until the skirmish UI is finished.
- **Default**: `No`
- **Example**: `ForceSkirmishAI = Yes` // Forces AI to use skirmish behavior

#### `RotateSkirmishBases` *(v1.04)*
- **Type**: `Bool`
- **Description**: If yes, rotate base layout so same side of base faces center of map.
- **Default**: `Yes`
- **Example**: `RotateSkirmishBases = No` // Bases maintain original orientation

#### `AttackUsesLineOfSight` *(v1.04)*
- **Type**: `Bool`
- **Description**: If yes, attack for ALL UNITS (player and AI) uses line of sight.
- **Default**: `Yes`
- **Example**: `AttackUsesLineOfSight = No` // Units can attack without line of sight

#### `EnableRepulsors` *(v1.04)*
- **Type**: `Bool`
- **Description**: If yes, KINDOF_CAN_BE_REPULSED will run from enemies & repulsors.
- **Default**: `Yes`
- **Example**: `EnableRepulsors = No` // Disables repulsor behavior

#### `AttackIgnoreInsignificantBuildings` *(v1.04)*
- **Type**: `Bool`
- **Description**: If yes, units will ignore enemy-owned buildings that are not faction buildings.
- **Default**: `Yes`
- **Example**: `AttackIgnoreInsignificantBuildings = No` // Units attack all buildings

#### `AICrushesInfantry` *(v1.04)*
- **Type**: `Bool`
- **Description**: If yes, AI will attempt to crush infantry with vehicles.
- **Default**: `No`
- **Example**: `AICrushesInfantry = Yes` // AI vehicles actively crush infantry

### Resource Management *(v1.04)*

#### `Wealthy` *(v1.04)*
- **Type**: `Int`
- **Description**: Number of resources for the AI to consider itself wealthy.
- **Default**: `7000`
- **Example**: `Wealthy = 10000` // AI considers itself wealthy at higher resource levels

#### `Poor` *(v1.04)*
- **Type**: `Int`
- **Description**: Number of resources for the AI to consider itself poor.
- **Default**: `2000`
- **Example**: `Poor = 1000` // AI considers itself poor at lower resource levels

#### `StructuresWealthyRate` *(v1.04)*
- **Type**: `Float`
- **Description**: (2=twice as fast) Rate modifier for structure building when wealthy.
- **Default**: `2.0`
- **Example**: `StructuresWealthyRate = 3.0` // AI builds structures 3x faster when wealthy

#### `StructuresPoorRate` *(v1.04)*
- **Type**: `Float`
- **Description**: (0.5=half as fast) Rate modifier for structures when poor.
- **Default**: `0.6`
- **Example**: `StructuresPoorRate = 0.3` // AI builds structures much slower when poor

#### `TeamsWealthyRate` *(v1.04)*
- **Type**: `Float`
- **Description**: (2=twice as fast) Rate modifier for teams building when wealthy.
- **Default**: `2.0`
- **Example**: `TeamsWealthyRate = 2.5` // AI forms teams faster when wealthy

#### `TeamsPoorRate` *(v1.04)*
- **Type**: `Float`
- **Description**: (0.5=half as fast) Rate modifier for teams when poor.
- **Default**: `0.6`
- **Example**: `TeamsPoorRate = 0.4` // AI forms teams slower when poor

#### `TeamResourcesToStart` *(v1.04)*
- **Type**: `Float`
- **Description**: (1.0=100%) Amount of resources required to start building a team.
- **Default**: `0.2`
- **Example**: `TeamResourcesToStart = 0.5` // AI needs 50% of resources to start team

### Build Order Settings *(v1.04)*

#### `SkirmishBaseDefenseExtraDistance` *(v1.04)*
- **Type**: `Float`
- **Description**: Instead of placing base defenses on the template edge, bump it this much farther out.
- **Default**: `150.0`
- **Example**: `SkirmishBaseDefenseExtraDistance = 200.0` // Base defenses placed further out

#### `SkirmishGroupFudgeDistance` *(v1.04)*
- **Type**: `Float`
- **Description**: Distance multiplied by number of units to determine waypoint proximity.
- **Default**: `10.0`
- **Example**: `SkirmishGroupFudgeDistance = 15.0` // Larger groups need more distance

#### `InfantryPathfindDiameter` *(v1.04)*
- **Type**: `Int`
- **Description**: Number of pathfind cells wide group path is for infantry.
- **Default**: `6`
- **Example**: `InfantryPathfindDiameter = 8` // Wider paths for infantry groups

#### `VehiclePathfindDiameter` *(v1.04)*
- **Type**: `Int`
- **Description**: Number of pathfind cells wide group path is for vehicles.
- **Default**: `7`
- **Example**: `VehiclePathfindDiameter = 9` // Wider paths for vehicle groups

#### `SupplyCenterSafeRadius` *(v1.04)*
- **Type**: `Float`
- **Description**: Radius to scan for enemies to determine if a supply center is safe.
- **Default**: `300.0`
- **Example**: `SupplyCenterSafeRadius = 400.0` // Larger safe radius for supply centers

#### `RebuildDelayTimeSeconds` *(v1.04)*
- **Type**: `Int`
- **Description**: Delay this many seconds when a base building is destroyed before attempting rebuild.
- **Default**: `30`
- **Example**: `RebuildDelayTimeSeconds = 60` // Longer delay before rebuilding

### Combat Behavior *(v1.04)*

#### `ForceIdleMSEC` *(v1.04)*
- **Type**: `Int`
- **Description**: The number of milliseconds a unit must be idle before looking for an enemy.
- **Default**: `67`
- **Example**: `ForceIdleMSEC = 100` // Units wait longer before seeking enemies

#### `AlertRangeModifier` *(v1.04)*
- **Type**: `Float`
- **Description**: The adjustment applied when a unit is alert and doing various scans for enemies (AI units only).
- **Default**: `1.1`
- **Example**: `AlertRangeModifier = 1.5` // Alert units have longer detection range

#### `AggressiveRangeModifier` *(v1.04)*
- **Type**: `Float`
- **Description**: The adjustment applied when a unit is aggressive and doing various scans for enemies (AI units only).
- **Default**: `1.5`
- **Example**: `AggressiveRangeModifier = 2.0` // Aggressive units have much longer detection range

#### `AttackPriorityDistanceModifier` *(v1.04)*
- **Type**: `Float`
- **Description**: The distance required to reduce attack priority by 1.
- **Default**: `100.0`
- **Example**: `AttackPriorityDistanceModifier = 150.0` // Distance affects priority more

#### `MaxRecruitRadius` *(v1.04)*
- **Type**: `Float`
- **Description**: The maximum distance a unit will be from a unit that recruits it.
- **Default**: `500.0`
- **Example**: `MaxRecruitRadius = 750.0` // Units can recruit from further away

#### `RepulsedDistance` *(v1.04)*
- **Type**: `Float`
- **Description**: How far beyond vision range a repulsed civilian will run before stopping.
- **Default**: `150.0`
- **Example**: `RepulsedDistance = 200.0` // Civilians run further when repulsed

#### `WallHeight` *(v1.04)*
- **Type**: `Int`
- **Description**: Height of the "Wall", made of KIND WALK_ON_TOP pieces.
- **Default**: `43`
- **Example**: `WallHeight = 50` // Taller walls for better defense

#### `AIDozerBoredRadiusModifier` *(v1.04)*
- **Type**: `Float`
- **Description**: Multiplier to dozer scan radius for repair & mine clearing. 2.0 means AI uses twice the radius as human dozers.
- **Default**: `2.0`
- **Example**: `AIDozerBoredRadiusModifier = 3.0` // AI dozers have even larger scan radius

### Guard Behavior *(v1.04)*

#### `GuardInnerModifierAI` *(v1.04)*
- **Type**: `Float`
- **Description**: The radius modifier to vision which a guarding (AI Controlled) unit will aggressively attack.
- **Default**: `1.4`
- **Example**: `GuardInnerModifierAI = 1.6` // AI guards attack at longer range

#### `GuardOuterModifierAI` *(v1.04)*
- **Type**: `Float`
- **Description**: The radius modifier to vision which a guarding (AI Controlled) unit will chase after.
- **Default**: `1.6`
- **Example**: `GuardOuterModifierAI = 1.8` // AI guards chase at longer range

#### `GuardInnerModifierHuman` *(v1.04)*
- **Type**: `Float`
- **Description**: The radius modifier to vision which a guarding (Human Controlled) unit will aggressively attack.
- **Default**: `1.8`
- **Example**: `GuardInnerModifierHuman = 2.0` // Human guards attack at longer range

#### `GuardOuterModifierHuman` *(v1.04)*
- **Type**: `Float`
- **Description**: The radius modifier to vision which a guarding (Human Controlled) unit will chase after.
- **Default**: `2.2`
- **Example**: `GuardOuterModifierHuman = 2.5` // Human guards chase at longer range

#### `GuardChaseUnitsDuration` *(v1.04)*
- **Type**: `Int`
- **Description**: The number of milliseconds for which a guarding unit will chase attackers before giving up.
- **Default**: `10000`
- **Example**: `GuardChaseUnitsDuration = 15000` // Guards chase for longer

#### `GuardEnemyScanRate` *(v1.04)*
- **Type**: `Int`
- **Description**: When actively guarding, how often to scan for enemies (milliseconds).
- **Default**: `500`
- **Example**: `GuardEnemyScanRate = 250` // Guards scan more frequently

#### `GuardEnemyReturnScanRate` *(v1.04)*
- **Type**: `Int`
- **Description**: When returning to "active" guarding, how often to scan for enemies (milliseconds).
- **Default**: `1000`
- **Example**: `GuardEnemyReturnScanRate = 750` // Guards scan more frequently when returning

### Retaliation Settings *(v1.04)*

#### `MaxRetaliationDistance` *(v1.04)*
- **Type**: `Float`
- **Description**: If the attacker is more than this far away, won't chase. Keeps from chasing artillery.
- **Default**: `200.0`
- **Example**: `MaxRetaliationDistance = 300.0` // Units chase further for retaliation

#### `RetaliationFriendsRadius` *(v1.04)*
- **Type**: `Float`
- **Description**: Retaliator gathers allies within this distance & attacks.
- **Default**: `120.0`
- **Example**: `RetaliationFriendsRadius = 150.0` // Larger radius for gathering allies

### Faction-Specific Settings *(v1.04)*

#### `SideInfo` *(v1.04)*
- **Type**: `Block`
- **Description**: Faction-specific AI configuration including resource gatherers and base defense structures.
- **Default**: Varies by faction
- **Example**: 
  ```ini
  SideInfo America
      ResourceGatherersEasy     = 1
      ResourceGatherersNormal   = 1
      ResourceGatherersHard     = 1 
      BaseDefenseStructure1     = AmericaPatriotBattery
      SkillSet1
      End
  End
  ```

#### `SkirmishBuildList` *(v1.04)*
- **Type**: `Block`
- **Description**: Defines the base layout and structure placement for AI skirmish bases.
- **Default**: Varies by faction
- **Example**:
  ```ini
  SkirmishBuildList America
      Structure AmericaCommandCenter
          Location = X:1797.84 Y:1734.92
          Rebuilds = 0
          Angle = -135.00
          InitiallyBuilt = No
          AutomaticallyBuild = No
      END
  END
  ```

## Examples

### Basic AI Configuration
```ini
AIData
    StructureSeconds = 3.0
    TeamSeconds = 10
    Wealthy = 8000
    Poor = 1500
    StructuresWealthyRate = 2.5
    TeamsWealthyRate = 2.5
End
```

### Aggressive AI Setup
```ini
AIData
    AlertRangeModifier = 1.5
    AggressiveRangeModifier = 2.0
    GuardInnerModifierAI = 1.6
    GuardOuterModifierAI = 1.8
    MaxRetaliationDistance = 300.0
    RetaliationFriendsRadius = 150.0
End
```

### Defensive AI Configuration
```ini
AIData
    SkirmishBaseDefenseExtraDistance = 200.0
    SupplyCenterSafeRadius = 400.0
    RebuildDelayTimeSeconds = 60
    WallHeight = 50
End
```

## Template

```ini
AIData
    StructureSeconds                    = 5.0     ; // AI tries to build a new structure every N seconds *(v1.04)*
    TeamSeconds                         = 15      ; // AI tries to build a new team every N seconds *(v1.04)*
    Wealthy                             = 7000    ; // Number of resources for the AI to consider itself wealthy *(v1.04)*
    Poor                                = 2000    ; // Number of resources for the AI to consider itself poor *(v1.04)*
    StructuresWealthyRate               = 2.0     ; // (2=twice as fast) Rate modifier for structure building when wealthy *(v1.04)*
    StructuresPoorRate                  = 0.6     ; // (0.5=half as fast) Rate modifier for structures when poor *(v1.04)*
    TeamsWealthyRate                    = 2.0     ; // (2=twice as fast) Rate modifier for teams building when wealthy *(v1.04)*
    TeamsPoorRate                       = 0.6     ; // (0.5=half as fast) Rate modifier for teams when poor *(v1.04)*
    TeamResourcesToStart                = 0.2     ; // (1.0=100%) Amount of resources required to start building a team *(v1.04)*
    GuardInnerModifierAI                = 1.4     ; // The radius modifier to vision which a guarding (AI Controlled) unit will aggressively attack *(v1.04)*
    GuardOuterModifierAI                = 1.6     ; // The radius modifier to vision which a guarding (AI Controlled) unit will chase after *(v1.04)*
    GuardInnerModifierHuman             = 1.8     ; // The radius modifier to vision which a guarding (Human Controlled) unit will aggressively attack *(v1.04)*
    GuardOuterModifierHuman             = 2.2     ; // The radius modifier to vision which a guarding (Human Controlled) unit will chase after *(v1.04)*
    GuardChaseUnitsDuration             = 10000   ; // The number of msec for which a guarding unit will chase attackers before giving up *(v1.04)*
    GuardEnemyScanRate                  = 500     ; // When actively guarding, how often to scan for enemies (msec) *(v1.04)*
    GuardEnemyReturnScanRate            = 1000    ; // When returning to "active" guarding, how often to scan for enemies (msec) *(v1.04)*
    AlertRangeModifier                  = 1.1     ; // The adjustment applied when a unit is alert and doing various scans for enemies (AI units only) *(v1.04)*
    AggressiveRangeModifier             = 1.5     ; // The adjustment applied when a unit is aggressive and doing various scans for enemies (AI units only) *(v1.04)*
    AttackPriorityDistanceModifier      = 100.0   ; // The distance required to reduce attack priority by 1 *(v1.04)*
    MaxRecruitRadius                    = 500.0   ; // The maximum distance a unit will be from a unit that recruits it *(v1.04)*
    SkirmishBaseDefenseExtraDistance    = 150.0   ; // Instead of placing base defenses on the template edge, bump it this much farther out *(v1.04)*
    ForceIdleMSEC                       = 67      ; // The number of milisec a unit must be idle before looking for an enemy *(v1.04)*
    ForceSkirmishAI                     = No      ; // Use skirmish instead of solo AI *(v1.04)*
    RotateSkirmishBases                 = Yes     ; // If yes, rotate base layout so same side of base faces center of map *(v1.04)*
    AttackUsesLineOfSight               = Yes     ; // If yes, attack for ALL UNITS (player and AI) uses line of sight *(v1.04)*
    EnableRepulsors                     = Yes     ; // If yes, KINDOF_CAN_BE_REPULSED will run from enemies & repulsors *(v1.04)*
    RepulsedDistance                    = 150.0   ; // How far beyond vision range a repulsed civilian will run before stopping *(v1.04)*
    WallHeight                          = 43      ; // Height of the "Wall", made of KIND WALK_ON_TOP pieces *(v1.04)*
    AttackIgnoreInsignificantBuildings  = Yes     ; // If yes, units will ignore enemy-owned buildings that are not faction buildings *(v1.04)*
    SkirmishGroupFudgeDistance          = 10.0    ; // Distance multiplied by number of units to determine waypoint proximity *(v1.04)*
    InfantryPathfindDiameter            = 6       ; // Number of pathfind cells wide group path is for infantry *(v1.04)*
    VehiclePathfindDiameter             = 7       ; // Number of pathfind cells wide group path is for vehicles *(v1.04)*
    SupplyCenterSafeRadius              = 300.0   ; // Radius to scan for enemies to determine if a supply center is safe *(v1.04)*
    RebuildDelayTimeSeconds             = 30      ; // Delay this many seconds when a base building is destroyed before attempting rebuild *(v1.04)*
    AIDozerBoredRadiusModifier          = 2.0     ; // Multiplier to dozer scan radius for repair & mine clearing *(v1.04)*
    AICrushesInfantry                   = No      ; // If yes, AI will attempt to crush infantry with vehicles *(v1.04)*
    MaxRetaliationDistance              = 200.0   ; // If the attacker is more than this far away, won't chase *(v1.04)*
    RetaliationFriendsRadius            = 120.0   ; // Retaliator gathers allies within this distance & attacks *(v1.04)*

    SideInfo America
        ResourceGatherersEasy     = 1
        ResourceGatherersNormal   = 1
        ResourceGatherersHard     = 1 
        BaseDefenseStructure1     = AmericaPatriotBattery
        SkillSet1
        End
    End

    SideInfo China
        ResourceGatherersEasy     = 1
        ResourceGatherersNormal   = 1
        ResourceGatherersHard     = 1     
        BaseDefenseStructure1     = ChinaGattlingCannon
        SkillSet1
        End
    End

    SideInfo GLA
        ResourceGatherersEasy     = 5
        ResourceGatherersNormal   = 5
        ResourceGatherersHard     = 6     
        BaseDefenseStructure1     = GLAStingerSite
        SkillSet1
        End
    End

    SideInfo ChinaNukeGeneral
        ResourceGatherersEasy     = 1
        ResourceGatherersNormal   = 1
        ResourceGatherersHard     = 1     
        BaseDefenseStructure1     = Russia_Kashtan
        SkillSet1
        End
    End
End
```

## Notes

- AIData provides comprehensive AI behavior configuration for all computer-controlled opponents
- The configuration manages AI strategy, resource allocation, and tactical decision-making
- AI operations provide challenging and realistic gameplay experiences
- AI management creates balanced and engaging computer opponents
- This configuration is essential for both campaign and skirmish game modes
- AI coordination ensures proper faction-specific behavior and strategic variety
- Resource management settings directly affect AI economic behavior and decision-making
- Combat behavior parameters control AI tactical responses and engagement strategies
- Guard behavior settings determine defensive positioning and response patterns
- Retaliation settings control AI response to attacks and counter-attack behavior
- Faction-specific settings allow for unique AI characteristics per side

## Source Files

- Source: [`GeneralsMD/Code/GameEngine/Source/Common/INI/INIAiData.cpp`](../../GeneralsMD/Code/GameEngine/Source/Common/INI/INIAiData.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet
