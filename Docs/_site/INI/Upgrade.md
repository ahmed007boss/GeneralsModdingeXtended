# Upgrade INI Documentation

## Overview

Upgrades are researchable items that apply to players or individual objects. Each `Upgrade` template specifies display name, type, cost, time, button image, and research sounds. Objects and modules use upgrade masks to unlock behaviors, weapon sets, abilities, etc.

## Source Files

- Header: `GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h` – `Upgrade`, `UpgradeCenter`
- Source: `GeneralsMD/Code/GameEngine/Source/Common/System/Upgrade.cpp` – parse table and behavior
- INI entry point: `Generals/Code/GameEngine/Source/Common/INI/INIUpgrade.cpp`

## Usage

- INI root: `Upgrade` blocks define templates: `Upgrade <Name> ... End`.
- Type controls scope: `PLAYER` or `OBJECT`.
- Research queues use `ButtonImage`, sounds, cost and time for UI and logic.

## Properties

### General Settings

#### DisplayName (v1.04)
- Type: AsciiString (label key)
- Description: UI string label key for upgrade name

#### Type (v1.04)
- Type: UpgradeType
- Description: Scope of upgrade (`PLAYER` or `OBJECT`)

#### BuildTime (v1.04)
- Type: Real (seconds)
- Description: Time to research; converted to frames internally

#### BuildCost (v1.04)
- Type: Int
- Description: Cost to research

#### ButtonImage (v1.04)
- Type: AsciiString
- Description: Image name for build queue icon

### Sound

#### ResearchSound (v1.04)
- Type: AudioEventRTS
- Description: Sound when research completes

#### UnitSpecificSound (v1.04)
- Type: AudioEventRTS
- Description: Secondary sound (unit-specific) when research completes

## Enum Value Lists

#### UpgradeType (v1.04)
- UPGRADE_TYPE_PLAYER (0)
- UPGRADE_TYPE_OBJECT (1)

## Examples

### Player Upgrade
```
Upgrade Upgrade_ArmorPiercingRounds
  DisplayName    = NAME:ArmorPiercingRounds
  Type           = PLAYER
  BuildTime      = 30.0
  BuildCost      = 1500
  ButtonImage    = SSArmorPiercing
  ResearchSound  = ResearchComplete
End
```

### Object Upgrade
```
Upgrade Upgrade_Veterancy_Heroic
  DisplayName      = NONE
  Type             = OBJECT
  BuildTime        = 0.0
  BuildCost        = 0
  ButtonImage      = None
  UnitSpecificSound= PromotionHeroic
End
```

## Notes

- `UpgradeCenter` assigns unique mask bits per upgrade; modules query masks to trigger effects.
- Veterancy upgrades are generated internally; they are `OBJECT` type and have zero time and cost.

## Template

```
Upgrade <Name>
  DisplayName       = NAME:<Key>      ; UI string label key
  Type              = PLAYER          ; PLAYER or OBJECT
  BuildTime         = 30.0            ; seconds
  BuildCost         = 1000            ; money
  ButtonImage       = <ImageName>     ; build queue icon
  ResearchSound     = <AudioEvent>    ; on complete
  UnitSpecificSound = <AudioEvent>    ; optional extra sound
End
```

