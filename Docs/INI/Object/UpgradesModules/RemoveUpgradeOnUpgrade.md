# RemoveUpgradeOnUpgrade

RemoveUpgradeOnUpgrade provides the ability to remove upgrades (player or object) from players or objects when another upgrade is applied, allowing for upgrade replacement systems and automatic upgrade removal based on upgrade activation.

## Overview

The `RemoveUpgradeOnUpgrade` class manages upgrade removal when specific upgrades are applied. This upgrade module allows objects to automatically remove upgrades from either the controlling player or the object itself when the module's trigger upgrade is activated, providing a way to create upgrade replacement chains and remove conflicting or outdated upgrades. The behavior supports both player upgrades and object upgrades, automatically detecting the upgrade type and removing it from the appropriate target.

## Usage

Used by objects that need to remove upgrades when other upgrades are applied. This is an **upgrade module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Only removes upgrades when the trigger upgrade is applied
- All upgrades to remove must exist in the game's upgrade system
- Upgrades are removed immediately when the trigger upgrade is activated
- Cannot remove upgrades during object construction
- Removing an upgrade resets it so it may be run again (does not undo effects permanently)

**Conditions**:
- RemoveUpgradeOnUpgrade removes upgrades when the specified trigger upgrade is applied
- The upgrade integrates with the upgrade system for conditional activation
- Upgrades can be removed from either the player or the object based on upgrade type
- The module automatically detects upgrade type (`UPGRADE_TYPE_PLAYER` or `UPGRADE_TYPE_OBJECT`) and removes accordingly
- Upgrades are not removed if the object is under construction
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own upgrade removal

**Dependencies**:
- Requires an object with upgrade system integration
- All upgrades to remove must exist in the game's upgrade system
- Objects must have proper player or upgrade system integration
- The upgrade center must be available for upgrade lookup

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)

## Properties

### Upgrade Removal Settings

#### `UpgradesToRemove` *(GMX Upcoming)*
- **Type**: `std::vector<AsciiString>` (space-separated list)
- **Description**: List of upgrade names to remove when this upgrade module is triggered. Multiple upgrade names can be specified as a space-separated list. Each upgrade will be removed from either the player or the object depending on the upgrade's type (`UPGRADE_TYPE_PLAYER` or `UPGRADE_TYPE_OBJECT`). The module automatically detects the upgrade type and removes it from the appropriate target. All upgrade names must reference valid `Upgrade` entries defined in the game's upgrade system. Note: Removing an upgrade resets it so it may be run again, but does not permanently undo its effects.
- **Default**: Empty (no upgrades removed)
- **Example**: `UpgradesToRemove = Upgrade_OldTraining Upgrade_OutdatedTechnology Upgrade_BasicWeapons`

#### `RegrantUpgradesOnDowngrade` *(GMX Upcoming)*
- **Type**: `Bool`
- **Description**: Controls whether the removed upgrades should be re-granted when this upgrade module is downgraded. When `Yes`, all upgrades that were removed by this module will be re-granted during downgrade operations. When `No`, downgrading this module will not affect the previously removed upgrades. This allows for flexible upgrade/downgrade behavior - removed upgrades can be restored after downgrade, or they can remain removed.
- **Default**: `No` (downgrade does not re-grant removed upgrades)
- **Example**: `RegrantUpgradesOnDowngrade = Yes`

### Upgrade Integration Settings

#### `TriggeredBy` *(v1.04)*
- **Type**: List of upgrade names (see [Upgrade documentation](../Upgrade.md))
- **Description**: List of upgrade names that must be active for this upgrade module to activate. When any of the listed upgrades (or all, if [RequiresAllTriggers](#requiresalltriggers) is `Yes`) become active, this upgrade module will activate and remove the specified upgrades. The upgrade names must reference valid `Upgrade` entries defined in the game. Multiple upgrade names can be specified as a space-separated list.
- **Default**: Empty (no trigger required)
- **Example**: `TriggeredBy = Upgrade_NewTechnology`

#### `ConflictsWith` *(v1.04)*
- **Type**: List of upgrade names (see [Upgrade documentation](../Upgrade.md))
- **Description**: List of upgrade names that conflict with this upgrade module. If any of the conflicting upgrades are active, this upgrade module will not activate, even if [TriggeredBy](#triggeredby) conditions are met. This allows modders to create mutually exclusive upgrade paths. The upgrade names must reference valid `Upgrade` entries. Multiple conflicting upgrades can be specified as a space-separated list.
- **Default**: Empty (no conflicts)
- **Example**: `ConflictsWith = Upgrade_BasicTraining`

#### `RequiresAllTriggers` *(v1.04)*
- **Type**: `Bool`
- **Description**: Controls whether all [TriggeredBy](#triggeredby) upgrades must be active, or if any one is sufficient. When `Yes`, all listed `TriggeredBy` upgrades must be active for this upgrade module to activate. When `No`, any one of the `TriggeredBy` upgrades being active is sufficient. This provides fine-grained control over upgrade activation conditions.
- **Default**: `No`
- **Example**: `RequiresAllTriggers = Yes`

#### `RequiredAnyUpgradeOf` *(v1.04)*
- **Type**: List of upgrade names (see [Upgrade documentation](../Upgrade.md))
- **Description**: List of upgrade names where at least one must be active for this upgrade module to activate, in addition to [TriggeredBy](#triggeredby) conditions. This provides an OR condition: the upgrade module activates if `TriggeredBy` conditions are met AND at least one of the `RequiredAnyUpgradeOf` upgrades is active. The upgrade names must reference valid `Upgrade` entries. Multiple upgrade names can be specified as a space-separated list.
- **Default**: Empty (no additional requirements)
- **Example**: `RequiredAnyUpgradeOf = Upgrade_AdvancedTraining Upgrade_EliteTraining`

#### `RequiredAllUpgradesOf` *(v1.04)*
- **Type**: List of upgrade names (see [Upgrade documentation](../Upgrade.md))
- **Description**: List of upgrade names that must all be active for this upgrade module to activate, in addition to [TriggeredBy](#triggeredby) conditions. This provides an AND condition: the upgrade module activates if `TriggeredBy` conditions are met AND all of the `RequiredAllUpgradesOf` upgrades are active. The upgrade names must reference valid `Upgrade` entries. Multiple upgrade names can be specified as a space-separated list.
- **Default**: Empty (no additional requirements)
- **Example**: `RequiredAllUpgradesOf = Upgrade_BasicTraining Upgrade_AdvancedTraining`

#### `RemovesUpgrades` *(v1.04)*
- **Type**: List of upgrade names (see [Upgrade documentation](../Upgrade.md))
- **Description**: List of upgrade names that will be removed when this upgrade module is activated. This allows creating upgrade replacement chains where activating one upgrade removes others. The upgrade names must reference valid `Upgrade` entries. Multiple upgrade names can be specified as a space-separated list.
- **Default**: Empty (no upgrades removed)
- **Example**: `RemovesUpgrades = Upgrade_OldTraining Upgrade_OutdatedTechnology`

#### `FXListUpgrade` *(v1.04)*
- **Type**: `FXList` (see [FXList documentation](../../FXList.md))
- **Description**: FXList to play when this upgrade module is activated. This allows visual and audio effects to be triggered when upgrades are removed. The FXList must reference a valid FXList entry defined in the game.
- **Default**: `NULL` (no effects)
- **Example**: `FXListUpgrade = FX_UpgradeRemoved`

## Examples

### Basic Single Upgrade Removal
```ini
Upgrade = RemoveUpgradeOnUpgrade ModuleTag_RemoveUpgrade
  UpgradesToRemove = Upgrade_OldTraining
  TriggeredBy = Upgrade_NewTechnology
End
```

### Multiple Upgrades Removal
```ini
Upgrade = RemoveUpgradeOnUpgrade ModuleTag_RemoveMultipleUpgrades
  UpgradesToRemove = Upgrade_OldTraining Upgrade_OutdatedTechnology Upgrade_BasicWeapons
  TriggeredBy = Upgrade_TechnologyBreakthrough
End
```

### Player and Object Upgrades Mixed
```ini
Upgrade = RemoveUpgradeOnUpgrade ModuleTag_RemoveMixedUpgrades
  UpgradesToRemove = Upgrade_PlayerOldTraining Upgrade_ObjectOldWeapon Upgrade_PlayerOutdatedTech
  TriggeredBy = Upgrade_CompleteUpgrade
End
```

### Upgrade Replacement System
```ini
Upgrade = RemoveUpgradeOnUpgrade ModuleTag_UpgradeReplacement
  UpgradesToRemove = Upgrade_OldTechnology Upgrade_OutdatedTraining
  TriggeredBy = Upgrade_NewTechnology
  ConflictsWith = Upgrade_OldTechnology
End
```

### Upgrade Chain with Removal
```ini
Upgrade = GrantUpgradeOnUpgrade ModuleTag_GrantNew
  UpgradesToGrant = Upgrade_IntermediateTraining
  TriggeredBy = Upgrade_BasicResearch
End

Upgrade = RemoveUpgradeOnUpgrade ModuleTag_RemoveOld
  UpgradesToRemove = Upgrade_BasicTraining
  TriggeredBy = Upgrade_IntermediateTraining
End
```

### Conditional Upgrade Removal
```ini
Upgrade = RemoveUpgradeOnUpgrade ModuleTag_ConditionalRemoval
  UpgradesToRemove = Upgrade_OutdatedTraining Upgrade_OldWeapons
  TriggeredBy = Upgrade_ResearchComplete
  RequiredAllUpgradesOf = Upgrade_AdvancedResearch Upgrade_EliteResearch
End
```

### Upgrade Removal with Downgrade Re-grant
```ini
Upgrade = RemoveUpgradeOnUpgrade ModuleTag_RemoveWithRegrant
  UpgradesToRemove = Upgrade_TemporaryBuff Upgrade_SpecialEffect
  TriggeredBy = Upgrade_DebuffResearch
  RegrantUpgradesOnDowngrade = Yes  ; Restore buffs when research is downgraded
End
```

### Permanent Upgrade Removal
```ini
Upgrade = RemoveUpgradeOnUpgrade ModuleTag_RemovePermanent
  UpgradesToRemove = Upgrade_ObsoleteTech Upgrade_OutdatedAbility
  TriggeredBy = Upgrade_RevolutionaryTech
  RegrantUpgradesOnDowngrade = No   ; Keep old tech removed even after downgrade
End
```

## Template

```ini
Upgrade = RemoveUpgradeOnUpgrade ModuleTag_XX
  ; Upgrade Removal Settings
  UpgradesToRemove =                    ; // space-separated list of upgrade names to remove *(GMX Upcoming)*
  RegrantUpgradesOnDowngrade = No      ; // re-grant removed upgrades on downgrade *(GMX Upcoming)*

  ; Upgrade Integration (inherited from UpgradeModule)
  TriggeredBy =                        ; // required upgrade flags *(v1.04)*
  ConflictsWith =                      ; // conflicting upgrade flags *(v1.04)*
  RequiredAnyUpgradeOf =               ; // any of these upgrades required *(v1.04)*
  RequiredAllUpgradesOf =              ; // all of these upgrades required *(v1.04)*
  RemovesUpgrades =                    ; // upgrades to remove on activation *(v1.04)*
  FXListUpgrade =                      ; // effects to play on activation *(v1.04)*
  RequiresAllTriggers = No             ; // require all TriggeredBy upgrades *(v1.04)*
End
```

## Notes

- RemoveUpgradeOnUpgrade removes upgrades when the specified trigger upgrade is applied
- The upgrade integrates with the upgrade system for conditional activation based on [TriggeredBy](#triggeredby), [ConflictsWith](#conflictswith), and other upgrade conditions
- Upgrades can be removed from either the player or the object based on the upgrade's type
- The module automatically detects upgrade type (`UPGRADE_TYPE_PLAYER` or `UPGRADE_TYPE_OBJECT`) and removes accordingly
- Multiple upgrades can be specified in [UpgradesToRemove](#upgradestoremove) as a space-separated list
- Upgrades are not removed if the object is under construction
- Removing an upgrade resets it so it may be run again, but does not permanently undo its effects
- When [RegrantUpgradesOnDowngrade](#regrantupgradesondowngrade) is enabled, removed upgrades are automatically re-granted during downgrade
- This module is useful for creating upgrade replacement systems, removing conflicting upgrades, and cleaning up outdated upgrades
- Can be combined with `GrantUpgradeOnUpgrade` to create upgrade replacement chains where old upgrades are removed and new ones are granted
- Downgrade behavior can be controlled to either restore removed upgrades or keep them permanently removed
- Note: Object upgrade removal calls `resetUpgrade()` which allows the upgrade to be triggered again, but does not undo the upgrade's effects

## Source Files

**Base Class:** [`UpgradeModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RemoveUpgradeOnUpgrade.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RemoveUpgradeOnUpgrade.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/RemoveUpgradeOnUpgrade.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/RemoveUpgradeOnUpgrade.cpp)

## Changes History

- **15/01/2025**: Initial implementation by TheSuperHackers - Added RemoveUpgradeOnUpgrade module with support for multiple upgrades and automatic player/object upgrade detection
- **15/01/2025**: Added `RegrantUpgradesOnDowngrade` INI attribute and downgrade implementation - Allows controlling whether removed upgrades are re-granted when the module is downgraded

## Status

- **Documentation Status**: AI Generated Pending Reviews
- **Last Updated**: 15/01/2025 by @ahmed Salah using AI (added downgrade functionality)

### Modder Reviews
- No Reviews done yet
