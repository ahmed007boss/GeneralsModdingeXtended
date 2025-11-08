# <span style="color:#5bbcff; font-weight:bold;">PlayerPrerequisite</span>

Status: AI-generated, 0/2 reviews

## Overview

The `PlayerPrerequisite` block defines checks about the owning player: required/conflicting units, sciences, upgrades, KindOf groups, and counts (optionally with veterancy levels). Used as a child block inside systems that must verify player state before enabling actions.

Available only in:
*(GMX Zero Hour)*

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
  - [Limitations](#limitations)
  - [Conditions](#conditions)
  - [Dependencies](#dependencies)
- [Properties](#properties)
  - [Units and OR Groups](#units-and-or-groups)
  - [Sciences and Upgrades](#sciences-and-upgrades)
  - [KindOf Groups and Counts](#kindof-groups-and-counts)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
- [Reviewers](#reviewers)

## Usage

Place as a child block in features that need to check player inventory/tech progression. Supports legacy aliases (`Object`, `Science`) and explicit forms (`PlayerObjectExists`, etc.).

**Limitations**:
- Requires a valid owning player context; in neutral contexts results may be undefined.

**Conditions**:
- OR-grouping of units is supported via sequential entries marked internally by the parser; the first unit is required, subsequent units with the same group are alternatives.

**Dependencies**:
- References to units/objects should match [Object](../Object.md) names; upgrades/sciences should match their respective definitions.

## Properties

### Units and OR Groups

- `PlayerObjectExists` (alias of: `Object`)
  - Type: Object name or list of object names (see [Object](../Object.md))
  - Description: Player must own the listed object(s). Multiple names on the same line are OR; repeating this line creates additional checks combined by AND. If an object name is misspelled or doesn't exist, results are unpredictable — always use exact object names.
  - Default: none
  - Example: `PlayerObjectExists = WarFactory Barracks`
- `PlayerObjectNotExist`
  - Type: List of [Object](../Object.md) names
  - Description: Player must NOT own any of the listed units (with OR grouping applied to conflict groups). If an object name is misspelled or doesn't exist, results are unpredictable — always use exact object names.
  - Default: none
  - Example: `PlayerObjectNotExist = ChinaNuclearMissile`

### Sciences and Upgrades

- `PlayerScienceExists` (alias of: `Science`)
  - Type: Science name or list of science names (see [Science documentation](../Science.md))
  - Description: All listed sciences must be owned. If a science name is wrong or doesn't exist, the game will stop at load with an error — use exact science names.
  - Default: none
  - Example: `PlayerScienceExists = SCIENCE_TechLevel2`
- `PlayerScienceNotExist`
  - Type: Science name or list (see [Science documentation](../Science.md))
  - Description: None of the listed sciences may be owned. If a science name is wrong or doesn't exist, the game will stop at load with an error — use exact science names.
  - Default: none
  - Example: `PlayerScienceNotExist = SCIENCE_SuperweaponGeneral`
- `PlayerUpgradeExist`
  - Type: Upgrade name or list (see [Upgrade](../Upgrade.md))
  - Description: All listed upgrades must be owned. If an upgrade name is wrong or doesn't exist, the game will stop at load with an error — use exact upgrade names.
  - Default: none
  - Example: `PlayerUpgradeExist = Upgrade_CompositeArmor`
- `PlayerUpgradeNotExist`
  - Type: Upgrade name or list (see [Upgrade](../Upgrade.md))
  - Description: None of the listed upgrades may be owned. If an upgrade name is wrong or doesn't exist, the game will stop at load with an error — use exact upgrade names.
  - Default: none
  - Example: `PlayerUpgradeNotExist = Upgrade_StealthComposites`

### KindOf Groups and Counts

- `PlayerKindOfObjectExists`
  - Type: KindOf name
  - Description: Player must own at least one object of this KindOf.
  - Default: none
  - Example: `PlayerKindOfObjectExists = STRUCTURE`
- `PlayerObjectKindOfNotExist`
  - Type: KindOf name
  - Description: Player must own zero objects of this KindOf.
  - Default: none
  - Example: `PlayerObjectKindOfNotExist = SUPERWEAPON`
- `PlayerMinCountKindOfObjectExist`
  - Type: Sequence: `KINDOF_A countA KINDOF_B countB ...`
  - Description: Passes if the player meets at least one of the pairs (OR) with the required counts.
  - Default: none
  - Example: `PlayerMinCountKindOfObjectExist = TANK 4 STRUCTURE 3`
- `PlayerMaxCountKindOfObjectExist`
  - Type: Sequence: `KINDOF_A countA KINDOF_B countB ...`
  - Description: Fails if the player meets any of the pairs (interpreted as a max-threshold block).
  - Default: none
  - Example: `PlayerMaxCountKindOfObjectExist = AIRCRAFT 8`
- `PlayerMinCountKindOfObjectWithLevelExist`
  - Type: Sequence: `KINDOF_A LEVEL_NAME countA [KINDOF_B LEVEL_NAME countB] ...`
  - Description: Passes if the player meets at least one (OR) KindOf with the specified minimum veterancy.
  - Default: none
  - Example: `PlayerMinCountKindOfObjectWithLevelExist = HERO LEVEL_VETERAN 1`
- `PlayerMaxCountKindOfObjectWithLevelExist`
  - Type: Sequence: `KINDOF_A LEVEL_NAME countA [KINDOF_B LEVEL_NAME countB] ...`
  - Description: Fails if the player meets any (interpreted as a max-threshold block) at the specified veterancy.
  - Default: none
  - Example: `PlayerMaxCountKindOfObjectWithLevelExist = AIRCRAFT LEVEL_ELITE 2`

## Examples

```ini
; Require either WarFactory OR Barracks owned by the player
PlayerPrerequisite
  PlayerObjectExists = WarFactory
  PlayerObjectExists = Barracks     ; grouped as OR with previous internally
End
```

```ini
; Require SCIENCE_TechLevel2 and UPGRADE_AdvancedArmor, and forbid owning SUPERWEAPON KindOf
PlayerPrerequisite
  PlayerScienceExists = SCIENCE_TechLevel2
  PlayerUpgradeExist = UPGRADE_AdvancedArmor
  PlayerObjectKindOfNotExist = SUPERWEAPON
End
```

```ini
; Pass if player owns at least 4 tanks OR at least 3 structures
PlayerPrerequisite
  PlayerMinCountKindOfObjectExist = TANK 4 STRUCTURE 3
End
```

```ini
; Forbid if player owns 2 or more HERO units at Veteran or above
PlayerPrerequisite
  PlayerMaxCountKindOfObjectWithLevelExist = HERO LEVEL_VETERAN 2
End
```

## Template

```ini
PlayerPrerequisite
  ; Units and OR groups
  PlayerObjectExists = ObjectName           ; player must own (OR within line)
  PlayerObjectNotExist = ObjectName         ; player must NOT own (OR within line)

  ; Sciences and Upgrades
  PlayerScienceExists = ScienceName         ; player must own these sciences
  PlayerScienceNotExist = ScienceName       ; player must NOT own these sciences
  PlayerUpgradeExist = UpgradeName          ; player must own these upgrades
  PlayerUpgradeNotExist = UpgradeName       ; player must NOT own these upgrades

  ; KindOf
  PlayerKindOfObjectExists = KINDOF_NAME    ; must own at least one of KindOf
  PlayerObjectKindOfNotExist = KINDOF_NAME  ; must own none of KindOf

  ; KindOf counts
  PlayerMinCountKindOfObjectExist = KINDOF_A 4 KINDOF_B 3            ; ≥ count for any pair
  PlayerMaxCountKindOfObjectExist = KINDOF_A 10                      ; fail if ≥ count for any
  PlayerMinCountKindOfObjectWithLevelExist = KINDOF LEVEL 2          ; ≥ count with level
  PlayerMaxCountKindOfObjectWithLevelExist = KINDOF LEVEL 1          ; fail if ≥ count with level
End
```

## Notes

- Where sequences are provided (e.g., `KINDOF count`), pairs are evaluated with OR logic unless stated as conflict/max-blocks.
- Use correct KindOf names supported by the engine.

## Source Files

- Header: [Common/PlayerPrerequisite.h](../../GeneralsMD/Code/GameEngine/Include/Common/PlayerPrerequisite.h)
- Source: [GeneralsMD/Code/GameEngine/Source/Common/RTS/PlayerPrerequisite.cpp](../../GeneralsMD/Code/GameEngine/Source/Common/RTS/PlayerPrerequisite.cpp)

## Changes History

- GMX Zero Hour — Adds PlayerPrerequisite system (child prerequisite block for player-state checks).

## Document Log

- 16/01/2025 — AI — Initial documentation created per authoring guide

## Status

- Documentation Status: AI-generated
- Last Updated: 16/01/2025 by AI
- Certification: 0/2 reviews

### Reviewers

- (pending)


