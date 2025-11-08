# Campaign INI Documentation

## Overview

The `Campaign` class represents a single-player campaign structure containing a sequence of missions with progression logic, briefing information, and campaign metadata. Campaigns define the flow of single-player gameplay including mission chains, faction assignments, and victory conditions.


## Usage

Campaigns are defined as blocks in INI files with a campaign name followed by campaign properties and nested mission definitions. Each campaign contains a sequence of missions that players progress through sequentially.

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Campaign Properties](#campaign-properties)
  - [Mission Properties](#mission-properties)
- [Examples](#examples)
- [Best Practices](#best-practices)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Campaign Properties

#### `CampaignNameLabel` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Localized text key for the campaign display name
- **Format**: `CAMPAIGN:KeyName` (e.g., `CAMPAIGN:CHALLENGE_2`)
- **Example**: `CampaignNameLabel = CAMPAIGN:CHALLENGE_2`

#### `PlayerFaction` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Default faction name for the player in this campaign
- **Example**: `PlayerFaction = FactionChina`

#### `FirstMission` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Name of the first mission to load when campaign starts
- **Example**: `FirstMission = Mission01`

#### `IsChallengeCampaign` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether this campaign is a challenge mode campaign
- **Default**: `false`
- **Example**: `IsChallengeCampaign = yes`

#### `FinalVictoryMovie` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Movie to play when campaign is completed
- **Example**: `FinalVictoryMovie = CampaignVictoryMovie`

### Mission Properties

Mission properties are defined within `Mission` blocks inside the campaign:

#### `Map` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Path to the map file for this mission
- **Example**: `Map = Maps\GC_AirGeneral\GC_AirGeneral3.map`

#### `NextMission` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Name of the next mission to load after completing this one (empty for final mission)
- **Example**: `NextMission = Mission02`

#### `IntroMovie` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Movie to play before mission starts
- **Example**: `IntroMovie = GeneralsChallengeBackground`

#### `GeneralName` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Localized text key for the general/commander name in this mission
- **Format**: `GUI:KeyName` (e.g., `GUI:BioNameEntry_Pos0`)
- **Example**: `GeneralName = GUI:BioNameEntry_Pos0`

#### `LocationNameLabel` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Localized text key for the mission location name
- **Example**: `LocationNameLabel = GUI:LocationName_Pos0`

#### `BriefingVoice` *(v1.04)*
- **Type**: `AudioEventRTS`
- **Description**: Audio event for mission briefing voice-over
- **Example**: `BriefingVoice = Mission01Briefing`

#### `VoiceLength` *(v1.04)*
- **Type**: `Int`
- **Description**: Length of briefing voice in milliseconds
- **Example**: `VoiceLength = 45000`

#### `ObjectiveLine0` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: First mission objective text (localized key)
- **Example**: `ObjectiveLine0 = GUI:ObjectiveLine0_Mission01`

#### `ObjectiveLine1` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Second mission objective text (localized key)
- **Example**: `ObjectiveLine1 = GUI:ObjectiveLine1_Mission01`

#### `ObjectiveLine2` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Third mission objective text (localized key)
- **Example**: `ObjectiveLine2 = GUI:ObjectiveLine2_Mission01`

#### `ObjectiveLine3` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Fourth mission objective text (localized key)
- **Example**: `ObjectiveLine3 = GUI:ObjectiveLine3_Mission01`

#### `ObjectiveLine4` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Fifth mission objective text (localized key)
- **Example**: `ObjectiveLine4 = GUI:ObjectiveLine4_Mission01`

#### `UnitNames0` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: First unit name to display in mission briefing
- **Example**: `UnitNames0 = USAInfantry`

#### `UnitNames1` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Second unit name to display in mission briefing
- **Example**: `UnitNames1 = USATank`

#### `UnitNames2` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Third unit name to display in mission briefing
- **Example**: `UnitNames2 = USAHelicopter`

## Examples

### Challenge Campaign
```ini
Campaign CHALLENGE_2
  CampaignNameLabel = CAMPAIGN:CHALLENGE_2
  PlayerFaction = FactionChina
  FirstMission = Mission01
  IsChallengeCampaign = yes
  FinalVictoryMovie = ChallengeVictory
  
  Mission Mission01
    Map = Maps\GC_AirGeneral\GC_AirGeneral3.map
    GeneralName = GUI:BioNameEntry_Pos0
    IntroMovie = GeneralsChallengeBackground
    NextMission = Mission02
    LocationNameLabel = GUI:Location_AirGeneral
    BriefingVoice = Challenge01Briefing
    VoiceLength = 30000
    ObjectiveLine0 = GUI:Objective_AirGeneral_Line0
    ObjectiveLine1 = GUI:Objective_AirGeneral_Line1
    UnitNames0 = ChinaHelicopter
    UnitNames1 = ChinaJet
  End
  
  Mission Mission02
    Map = Maps\GC_SuperWeaponsGeneral\GC_SuperWeaponsGeneral3.map
    GeneralName = GUI:BioNameEntry_Pos3
    IntroMovie = GeneralsChallengeBackground
    NextMission = Mission03
    LocationNameLabel = GUI:Location_SuperWeaponsGeneral
    BriefingVoice = Challenge02Briefing
    VoiceLength = 35000
    ObjectiveLine0 = GUI:Objective_SuperWeapons_Line0
    ObjectiveLine1 = GUI:Objective_SuperWeapons_Line1
    UnitNames0 = ChinaNuclearCannon
    UnitNames1 = ChinaScudStorm
  End
  
  Mission Mission03
    Map = Maps\GC_LaserGeneral\GC_LaserGeneral3.map
    GeneralName = GUI:BioNameEntry_Pos5
    IntroMovie = GeneralsChallengeBackground
    NextMission = Mission04
    LocationNameLabel = GUI:Location_LaserGeneral
    BriefingVoice = Challenge03Briefing
    VoiceLength = 32000
    ObjectiveLine0 = GUI:Objective_LaserGeneral_Line0
    ObjectiveLine1 = GUI:Objective_LaserGeneral_Line1
    UnitNames0 = ChinaLaserTank
    UnitNames1 = ChinaLaserTurret
  End
  
  Mission Mission04
    Map = Maps\GC_Stealth\GC_Stealth3.map
    GeneralName = GUI:BioNameEntry_Pos6
    IntroMovie = GeneralsChallengeBackground
    NextMission = Mission05
    LocationNameLabel = GUI:Location_StealthGeneral
    BriefingVoice = Challenge04Briefing
    VoiceLength = 28000
    ObjectiveLine0 = GUI:Objective_Stealth_Line0
    ObjectiveLine1 = GUI:Objective_Stealth_Line1
    UnitNames0 = ChinaStealthFighter
    UnitNames1 = ChinaStealthTank
  End
  
  Mission Mission05
    Map = Maps\GC_DemolitionGeneral\GC_DemolitionGeneral3.map
    GeneralName = GUI:BioNameEntry_Pos8
    IntroMovie = GeneralsChallengeBackground
    NextMission = Mission06
    LocationNameLabel = GUI:Location_DemolitionGeneral
    BriefingVoice = Challenge05Briefing
    VoiceLength = 31000
    ObjectiveLine0 = GUI:Objective_Demolition_Line0
    ObjectiveLine1 = GUI:Objective_Demolition_Line1
    UnitNames0 = ChinaDemolitionTruck
    UnitNames1 = ChinaInfernoCannon
  End
  
  Mission Mission06
    Map = Maps\GC_ChemGeneral\GC_ChemGeneral3.map
    GeneralName = GUI:BioNameEntry_Pos1
    IntroMovie = GeneralsChallengeBackground
    NextMission = Mission07
    LocationNameLabel = GUI:Location_ChemGeneral
    BriefingVoice = Challenge06Briefing
    VoiceLength = 33000
    ObjectiveLine0 = GUI:Objective_ChemGeneral_Line0
    ObjectiveLine1 = GUI:Objective_ChemGeneral_Line1
    UnitNames0 = ChinaToxinTractor
    UnitNames1 = ChinaChemicalTank
  End
  
  Mission Mission07
    Map = Maps\GC_TankGeneral\GC_TankGeneral3.map
    GeneralName = GUI:BioNameEntry_Pos4
    IntroMovie = GeneralsChallengeBackground
    NextMission = Mission08
    LocationNameLabel = GUI:Location_TankGeneral
    BriefingVoice = Challenge07Briefing
    VoiceLength = 29000
    ObjectiveLine0 = GUI:Objective_TankGeneral_Line0
    ObjectiveLine1 = GUI:Objective_TankGeneral_Line1
    UnitNames0 = ChinaTank
    UnitNames1 = ChinaBattleMaster
  End
  
  Mission Mission08
    Map = Maps\GC_InfantryGeneral\GC_InfantryGeneral3.map
    GeneralName = GUI:BioNameEntry_Pos7
    IntroMovie = GeneralsChallengeBackground
    LocationNameLabel = GUI:Location_InfantryGeneral
    BriefingVoice = Challenge08Briefing
    VoiceLength = 27000
    ObjectiveLine0 = GUI:Objective_InfantryGeneral_Line0
    ObjectiveLine1 = GUI:Objective_InfantryGeneral_Line1
    UnitNames0 = ChinaRedguard
    UnitNames1 = ChinaTankHunter
  End
End
```

### Story Campaign
```ini
Campaign USA_STORY
  CampaignNameLabel = CAMPAIGN:USA_STORY
  PlayerFaction = FactionUSA
  FirstMission = Mission01
  IsChallengeCampaign = no
  FinalVictoryMovie = USAVictory
  
  Mission Mission01
    Map = Maps\USA_01\USA_01.map
    GeneralName = GUI:GeneralUSA01
    IntroMovie = USAIntro01
    NextMission = Mission02
    LocationNameLabel = GUI:Location_Alaska
    BriefingVoice = USA01Briefing
    VoiceLength = 45000
    ObjectiveLine0 = GUI:Objective_USA01_Line0
    ObjectiveLine1 = GUI:Objective_USA01_Line1
    ObjectiveLine2 = GUI:Objective_USA01_Line2
    UnitNames0 = USAInfantry
    UnitNames1 = USATank
    UnitNames2 = USAHelicopter
  End
  
  Mission Mission02
    Map = Maps\USA_02\USA_02.map
    GeneralName = GUI:GeneralUSA02
    IntroMovie = USAIntro02
    NextMission = Mission03
    LocationNameLabel = GUI:Location_Kazakhstan
    BriefingVoice = USA02Briefing
    VoiceLength = 50000
    ObjectiveLine0 = GUI:Objective_USA02_Line0
    ObjectiveLine1 = GUI:Objective_USA02_Line1
    ObjectiveLine2 = GUI:Objective_USA02_Line2
    UnitNames0 = USAComanche
    UnitNames1 = USACrusader
    UnitNames2 = USARanger
  End
  
  Mission Mission03
    Map = Maps\USA_03\USA_03.map
    GeneralName = GUI:GeneralUSA03
    IntroMovie = USAIntro03
    LocationNameLabel = GUI:Location_China
    BriefingVoice = USA03Briefing
    VoiceLength = 55000
    ObjectiveLine0 = GUI:Objective_USA03_Line0
    ObjectiveLine1 = GUI:Objective_USA03_Line1
    ObjectiveLine2 = GUI:Objective_USA03_Line2
    ObjectiveLine3 = GUI:Objective_USA03_Line3
    UnitNames0 = USAAurora
    UnitNames1 = USAPatriot
    UnitNames2 = USAStealthFighter
  End
End
```

### Simple Campaign
```ini
Campaign GLA_STORY
  CampaignNameLabel = CAMPAIGN:GLA_STORY
  PlayerFaction = FactionGLA
  FirstMission = Mission01
  IsChallengeCampaign = no
  
  Mission Mission01
    Map = Maps\GLA_01\GLA_01.map
    GeneralName = GUI:GeneralGLA01
    NextMission = Mission02
    ObjectiveLine0 = GUI:Objective_GLA01_Line0
  End
  
  Mission Mission02
    Map = Maps\GLA_02\GLA_02.map
    GeneralName = GUI:GeneralGLA02
    ObjectiveLine0 = GUI:Objective_GLA02_Line0
  End
End
```

## Best Practices

### Campaign Structure

1. **Logical Mission Flow**: Ensure missions progress in a logical sequence with clear objectives
2. **Consistent Naming**: Use consistent naming conventions for campaigns and missions
3. **Proper Mission Chains**: Always set `NextMission` except for the final mission
4. **Faction Consistency**: Use appropriate `PlayerFaction` for the campaign theme

### Mission Design

1. **Clear Objectives**: Provide clear, actionable objectives for each mission
2. **Appropriate Maps**: Use maps that match the mission theme and difficulty
3. **Briefing Content**: Include comprehensive briefing voice and text for immersion
4. **Unit Showcase**: Display relevant units in mission briefings

### Localization

1. **Text Keys**: Always use proper localization keys for all text (GUI:, CAMPAIGN:, etc.)
2. **Consistent Formatting**: Use consistent key naming patterns across missions
3. **Complete Coverage**: Ensure all display text has corresponding localization keys

### Challenge Campaigns

1. **IsChallengeCampaign**: Set to `yes` for challenge/general's challenge modes
2. **Progressive Difficulty**: Design missions with increasing difficulty
3. **Unique Content**: Provide unique generals, maps, and objectives for each challenge

### Story Campaigns

1. **Narrative Flow**: Create missions that tell a coherent story
2. **Character Development**: Use consistent general names and personalities
3. **Location Variety**: Use diverse locations to enhance the narrative

## Template

```ini
Campaign CampaignName
    CampaignNameLabel = CAMPAIGN:DisplayName       ; // Campaign display name *(v1.04)*
    PlayerFaction = FactionName                   ; // Default player faction *(v1.04)*
    FirstMission = MissionName                    ; // Starting mission *(v1.04)*
    IsChallengeCampaign = false                   ; // Challenge mode flag *(v1.04)*
    FinalVictoryMovie = MovieName                 ; // Victory movie *(v1.04)*
    
    Mission MissionName
        Map = Maps\MapName\MapName.map           ; // Mission map file *(v1.04)*
        NextMission = NextMissionName            ; // Next mission in chain *(v1.04)*
        IntroMovie = MovieName                   ; // Mission intro movie *(v1.04)*
        GeneralName = GUI:GeneralName            ; // General/commander name *(v1.04)*
        LocationNameLabel = GUI:LocationName     ; // Mission location *(v1.04)*
        BriefingVoice = AudioEvent               ; // Briefing voice-over *(v1.04)*
        VoiceLength = 30000                      ; // Voice duration in ms *(v1.04)*
        ObjectiveLine0 = GUI:Objective0          ; // First objective *(v1.04)*
        ObjectiveLine1 = GUI:Objective1          ; // Second objective *(v1.04)*
        ObjectiveLine2 = GUI:Objective2          ; // Third objective *(v1.04)*
        ObjectiveLine3 = GUI:Objective3          ; // Fourth objective *(v1.04)*
        ObjectiveLine4 = GUI:Objective4          ; // Fifth objective *(v1.04)*
        UnitNames0 = UnitName1                   ; // First unit name *(v1.04)*
        UnitNames1 = UnitName2                   ; // Second unit name *(v1.04)*
        UnitNames2 = UnitName3                   ; // Third unit name *(v1.04)*
    End
End
```

## Notes

- Campaigns provide structured single-player gameplay experiences with progressive mission chains
- The configuration manages campaign metadata, mission sequences, and narrative progression
- Campaign operations create immersive storytelling and strategic gameplay experiences
- Campaign management ensures logical mission flow and player progression
- This configuration is essential for single-player game design and narrative structure
- Campaign coordination creates consistent progression mechanics across different campaign types
- Campaign properties define overall campaign characteristics and player faction
- Mission properties control individual mission content, objectives, and progression
- Mission chains create sequential gameplay with automatic progression
- Briefing systems provide narrative context and mission information
- Objective systems communicate mission goals and success criteria
- Unit showcase systems highlight relevant units in mission briefings
- Campaigns are managed by the `CampaignManager` singleton
- Each campaign can contain multiple missions in a sequential chain
- Mission progression is handled automatically based on `NextMission` links
- Challenge campaigns have special behavior for general selection and progression
- All text content should be localized using the game's text system
- Mission objectives are limited to 5 lines maximum (ObjectiveLine0 through ObjectiveLine4)
- Unit names in briefings are limited to 3 units maximum (UnitNames0 through UnitNames2)
- Campaigns support victory movies and faction-specific content
- The campaign system handles mission completion and progression automatically
- Campaign difficulty and ranking systems are managed separately from mission definitions

## Source Files

- Header: [`GeneralsMD/Code/GameEngine/Include/GameClient/CampaignManager.h`](../../GeneralsMD/Code/GameEngine/Include/GameClient/CampaignManager.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameClient/System/CampaignManager.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameClient/System/CampaignManager.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet