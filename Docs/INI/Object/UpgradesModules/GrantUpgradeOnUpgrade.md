# GrantUpgradeOnUpgrade

GrantUpgradeOnUpgrade provides the ability to grant upgrades (player or object) to players or objects when another upgrade is applied, allowing for cascading upgrade chains and automatic upgrade distribution based on upgrade activation.

## Overview

The `GrantUpgradeOnUpgrade` class manages upgrade granting when specific upgrades are applied. This upgrade module allows objects to automatically grant upgrades to either the controlling player or the object itself when the module's trigger upgrade is activated, providing a way to create upgrade chains and cascading upgrade effects. The behavior supports both player upgrades and object upgrades, automatically detecting the upgrade type and granting it to the appropriate target.

## Usage

Used by objects that need to grant upgrades when other upgrades are applied. This is an **upgrade module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Only grants upgrades when the trigger upgrade is applied
- All upgrades to grant must exist in the game's upgrade system
- Upgrades are granted immediately when the trigger upgrade is activated
- Cannot grant upgrades during object construction
- Duplicate upgrades are automatically skipped (already granted upgrades are not re-granted)

**Conditions**:
- GrantUpgradeOnUpgrade grants upgrades when the specified trigger upgrade is applied
- The upgrade integrates with the upgrade system for conditional activation
- Upgrades can be granted to either the player or the object based on upgrade type
- The module automatically detects upgrade type (player vs object) and grants accordingly
- Upgrades are not granted if the object is under construction
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own upgrade granting

**Dependencies**:
- Requires an object with upgrade system integration
- All upgrades to grant must exist in the game's upgrade system
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

### Upgrade Granting Settings

#### `UpgradesToGrant` *(GMX Upcoming)*
- **Type**: `std::vector<AsciiString>` (space-separated list)
- **Description**: List of upgrade names to grant when this upgrade module is triggered. Multiple upgrade names can be specified as a space-separated list. Each upgrade will be granted to either the player or the object depending on the upgrade's type (`UPGRADE_TYPE_PLAYER` or `UPGRADE_TYPE_OBJECT`). The module automatically detects the upgrade type and grants it to the appropriate target. If an upgrade is already granted, it will be skipped to prevent duplicates. All upgrade names must reference valid `Upgrade` entries defined in the game's upgrade system.
- **Default**: Empty (no upgrades granted)
- **Example**: `UpgradesToGrant = Upgrade_EliteTraining Upgrade_WeaponTraining Upgrade_AdvancedTechnology`

#### `RemoveUpgradesOnDowngrade` *(GMX Upcoming)*
- **Type**: `Bool`
- **Description**: Controls whether the granted upgrades should be removed when this upgrade module is downgraded. When `Yes`, all upgrades that were granted by this module will be removed during downgrade operations. When `No`, downgrading this module will not affect the previously granted upgrades. This allows for flexible upgrade/downgrade behavior - upgrades can persist after downgrade, or they can be automatically cleaned up.
- **Default**: `No` (downgrade does not remove granted upgrades)
- **Example**: `RemoveUpgradesOnDowngrade = Yes`

### Upgrade Integration Settings

#### `TriggeredBy` *(v1.04)*
- **Type**: List of upgrade names (see [Upgrade documentation](../Upgrade.md))
- **Description**: List of upgrade names that must be active for this upgrade module to activate. When any of the listed upgrades (or all, if [RequiresAllTriggers](#requiresalltriggers) is `Yes`) become active, this upgrade module will activate and grant the specified upgrades. The upgrade names must reference valid `Upgrade` entries defined in the game. Multiple upgrade names can be specified as a space-separated list.
- **Default**: Empty (no trigger required)
- **Example**: `TriggeredBy = Upgrade_ResearchComplete`

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
- **Description**: FXList to play when this upgrade module is activated. This allows visual and audio effects to be triggered when upgrades are granted. The FXList must reference a valid FXList entry defined in the game.
- **Default**: `NULL` (no effects)
- **Example**: `FXListUpgrade = FX_UpgradeGranted`

## Examples

### Basic Single Upgrade Grant
```ini
Upgrade = GrantUpgradeOnUpgrade ModuleTag_GrantUpgrade
  UpgradesToGrant = Upgrade_EliteTraining
  TriggeredBy = Upgrade_ResearchComplete
End
```

### Multiple Upgrades Grant
```ini
Upgrade = GrantUpgradeOnUpgrade ModuleTag_GrantMultipleUpgrades
  UpgradesToGrant = Upgrade_EliteTraining Upgrade_WeaponTraining Upgrade_AdvancedTechnology
  TriggeredBy = Upgrade_MasterResearch
End
```

### Player and Object Upgrades Mixed
```ini
Upgrade = GrantUpgradeOnUpgrade ModuleTag_GrantMixedUpgrades
  UpgradesToGrant = Upgrade_PlayerTraining Upgrade_ObjectWeaponUpgrade Upgrade_PlayerTech
  TriggeredBy = Upgrade_CompleteResearch
End
```

### Conditional Upgrade Grant with Conflicts
```ini
Upgrade = GrantUpgradeOnUpgrade ModuleTag_ConditionalGrant
  UpgradesToGrant = Upgrade_AdvancedTraining Upgrade_EliteWeapons
  TriggeredBy = Upgrade_ResearchComplete
  ConflictsWith = Upgrade_BasicTraining
  RequiresAllTriggers = No
End
```

### Upgrade Chain (Cascading Upgrades)
```ini
Upgrade = GrantUpgradeOnUpgrade ModuleTag_UpgradeChain1
  UpgradesToGrant = Upgrade_IntermediateTraining
  TriggeredBy = Upgrade_BasicResearch
End

Upgrade = GrantUpgradeOnUpgrade ModuleTag_UpgradeChain2
  UpgradesToGrant = Upgrade_AdvancedTraining Upgrade_EliteTraining
  TriggeredBy = Upgrade_IntermediateTraining
End
```

### Upgrade Replacement
```ini
Upgrade = GrantUpgradeOnUpgrade ModuleTag_UpgradeReplacement
  UpgradesToGrant = Upgrade_NewTechnology
  TriggeredBy = Upgrade_ResearchBreakthrough
  RemovesUpgrades = Upgrade_OldTechnology Upgrade_OutdatedTech
End
```

### Upgrade Grant with Downgrade Removal
```ini
Upgrade = GrantUpgradeOnUpgrade ModuleTag_GrantWithDowngrade
  UpgradesToGrant = Upgrade_TemporaryBonus Upgrade_SpecialAbility
  TriggeredBy = Upgrade_SpecialResearch
  RemoveUpgradesOnDowngrade = Yes  ; Remove the bonus when the research is downgraded
End
```

### Persistent Upgrade Grant
```ini
Upgrade = GrantUpgradeOnUpgrade ModuleTag_GrantPersistent
  UpgradesToGrant = Upgrade_PermanentTech Upgrade_UnlockedFeature
  TriggeredBy = Upgrade_MasterResearch
  RemoveUpgradesOnDowngrade = No   ; Keep upgrades even after downgrade
End
```

## Template

```ini
Upgrade = GrantUpgradeOnUpgrade ModuleTag_XX
  ; Upgrade Granting Settings
  UpgradesToGrant =                    ; // space-separated list of upgrade names to grant *(GMX Upcoming)*
  RemoveUpgradesOnDowngrade = No       ; // remove granted upgrades on downgrade *(GMX Upcoming)*

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

- GrantUpgradeOnUpgrade grants upgrades when the specified trigger upgrade is applied
- The upgrade integrates with the upgrade system for conditional activation based on [TriggeredBy](#triggeredby), [ConflictsWith](#conflictswith), and other upgrade conditions
- Upgrades can be granted to either the player or the object based on the upgrade's type
- The module automatically detects upgrade type (`UPGRADE_TYPE_PLAYER` or `UPGRADE_TYPE_OBJECT`) and grants accordingly
- Multiple upgrades can be specified in [UpgradesToGrant](#upgradestogrant) as a space-separated list
- Upgrades are not granted if the object is under construction
- Already granted upgrades are automatically skipped to prevent duplicates
- Academy stats are recorded for granted upgrades (when object is not under construction)
- When [RemoveUpgradesOnDowngrade](#removeupgradesondowngrade) is enabled, granted upgrades are automatically removed during downgrade
- This module is useful for creating upgrade chains, cascading upgrades, and automatic upgrade distribution
- Can be used to create upgrade replacement systems where activating one upgrade removes others
- Downgrade behavior can be controlled to either maintain upgrades or clean them up when the trigger upgrade is removed

## Source Files

**Base Class:** [`UpgradeModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/GrantUpgradeOnUpgrade.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/GrantUpgradeOnUpgrade.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/GrantUpgradeOnUpgrade.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/GrantUpgradeOnUpgrade.cpp)

## Changes History

- **15/01/2025**: Initial implementation by TheSuperHackers - Added GrantUpgradeOnUpgrade module with support for multiple upgrades and automatic player/object upgrade detection
- **15/01/2025**: Added `RemoveUpgradesOnDowngrade` INI attribute and downgrade implementation - Allows controlling whether granted upgrades are removed when the module is downgraded

## Status

- **Documentation Status**: AI Generated Pending Reviews
- **Last Updated**: 15/01/2025 by @ahmed Salah using AI (added downgrade functionality)

### Modder Reviews
- No Reviews done yet
