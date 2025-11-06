# ProductionPrerequisite

Status: AI-generated, 0/2 reviews

## Overview

The `ProductionPrerequisite` block defines checks used by production/build systems to gate whether a player may produce a unit/structure. It supports unit presence/absence, sciences, upgrades, and KindOf counts via simple key lines. Used as a child block inside features that validate production availability.

Available in:
*(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
  - [Limitations](#limitations)
  - [Conditions](#conditions)
  - [Dependencies](#dependencies)
- [Properties](#properties)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Document Log](#document-log)
- [Status](#status)
- [Reviewers](#reviewers)

## Usage

Place as a child block under systems that decide whether production is allowed (e.g., factories/build menus). Lines inside the block are evaluated according to their semantics (presence/absence requirements, OR grouping for repeated unit entries as noted by the parser).

**Limitations**:
- Requires a valid owning player context; neutral/world entities cannot validate production prerequisites.

**Conditions**:
- Multiple unit lines may form OR groups (subsequent units in the same parsed group act as alternatives).

**Dependencies**:
- References must match actual entity names: units/objects use [Object](../Object.md); upgrades use [Upgrade](../Upgrade.md); sciences use [Science](../Science.md).

## Properties

- `Object` (alias of: `PlayerObjectExist`)
  - Type: Object name or list of object names (see [Object](../Object.md))
  - Description: Player must own the listed object(s).
    - One line may contain multiple object names separated by spaces (OR logic on the same line).
    - Multiple lines create separate checks combined by AND.
  - Default: none
  - Example: `Object = AmericaWarFactory Barracks`

- `Science` (alias of: `PlayerScienceExist`)
  - Type: Science name or list of science names (see [Science](../Science.md))
  - Description: Player must own all listed sciences (AND logic across items on the same line).
  - Default: none
  - Example: `Science = SCIENCE_TechLevel2`

### GMX-only Additions
- `PlayerObjectNotExist` (GMX only)
  - Type: Object name or list of object names (see [Object](../Object.md))
  - Description: Player must NOT own any of the listed objects (OR within the same line).
  - Default: none
  - Example: `PlayerObjectNotExist = ChinaNuclearMissile`

- `PlayerScienceNotExist` (GMX only)
  - Type: Science name or list of science names (see [Science](../Science.md))
  - Description: Player must own none of the listed sciences (if any listed science is owned, the check fails).
  - Default: none
  - Example: `PlayerScienceNotExist = SCIENCE_SuperweaponGeneral`

- `PlayerUpgradeExist` (GMX only)
  - Type: Upgrade name or list of upgrade names (see [Upgrade](../Upgrade.md))
  - Description: Player must own all listed upgrades (AND logic across items on the same line).
  - Default: none
  - Example: `PlayerUpgradeExist = Upgrade_CompositeArmor`
- `PlayerUpgradeNotExist` (GMX only)
  - Type: Upgrade name or list of upgrade names (see [Upgrade](../Upgrade.md))
  - Description: Player must own none of the listed upgrades (if any listed upgrade is owned, the check fails).
  - Default: none
  - Example: `PlayerUpgradeNotExist = Upgrade_StealthComposites`

## Examples

```ini
ProductionPrerequisite
  Object = WarFactory
  Science = SCIENCE_TechLevel2 SCIENCE_StrategyCenter
End
```

```ini
ProductionPrerequisite
  PlayerUpgradeExist = Upgrade_CompositeArmor
  PlayerObjectNotExist = ChinaNuclearMissile
End
```
; GMX-only example above — in Retail, omit upgrade lines

## Template

```ini
ProductionPrerequisite
  Object = ObjectName
  Science = ScienceName
  ; GMX only
  ; PlayerObjectNotExist = ObjectName
  ; PlayerScienceNotExist = ScienceName
  ; PlayerUpgradeExist = UpgradeName
  ; PlayerUpgradeNotExist = UpgradeName
End
```

## Notes

- Where lines repeat, groups may be evaluated with OR semantics per parser behavior for sequential entries.
- Use exact names as defined in their respective docs.

## Source Files

- Header: [Common/ProductionPrerequisite.h](../../GeneralsMD/Code/GameEngine/Include/Common/ProductionPrerequisite.h)
- Source: [GeneralsMD/Code/GameEngine/Source/Common/RTS/ProductionPrerequisite.cpp](../../GeneralsMD/Code/GameEngine/Source/Common/RTS/ProductionPrerequisite.cpp)

## Changes History

- Retail 1.04 — ProductionPrerequisite (player production gating via objects/sciences/upgrades).
- GMX — Maintained and refactored with codebase modernization.

## Document Log

- 15/01/2025 — AI — Initial documentation created per authoring guide

## Status

- Documentation Status: AI-generated
- Last Updated: 15/01/2025 by AI
- Certification: 0/2 reviews

### Reviewers

- (pending)


