# MaxHealthUpgrade

Status: AI-generated, 0/2 reviews

## Overview

The `MaxHealthUpgrade` upgrade module increases an object's maximum health when specific upgrades are applied. This upgrade allows objects to gain enhanced durability and survivability by adding a specified amount to their maximum health. The behavior supports different health change types to control how the current health is affected when the maximum health is increased, and in GMX Zero Hour, supports both absolute and percentage-based health increases.

Available in: *(GMX, Retail 1.04)* (Generals, Zero Hour)

## Table of Contents

- [Overview](#overview)
- [Properties](#properties)
  - [Health Modification Settings](#health-modification-settings)
  - [Upgrade Integration Settings](#upgrade-integration-settings)
- [Enum Value Lists](#enum-value-lists)
  - [MaxHealthChangeType Values](#maxhealthchangetype-values)
  - [ValueType Values](#valuetype-values)
- [Examples](#examples)
- [Usage](#usage)
  - [Limitations](#limitations)
  - [Conditions](#conditions)
  - [Dependencies](#dependencies)
- [Template](#template)
- [Notes](#notes)
- [Modder Recommended Use Scenarios](#modder-recommended-use-scenarios)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviewers](#reviewers)

## Properties

### Health Modification Settings

#### `AddMaxHealth`

Available in: *(GMX, Retail 1.04)* (Generals, Zero Hour)

- **Type**: `Real`
- **Description**: The amount of maximum health to add to the object. Positive values increase maximum health, providing enhanced durability. The value interpretation depends on `ValueType` (GMX Zero Hour only): if `ValueType` is `ABSOLUTE`, the value is added directly to maximum health; if `ValueType` is `PERCENTAGE`, the value is treated as a percentage (e.g., `50.0%` means 50% of current maximum health). In Retail versions and GMX Generals, the value is always treated as absolute. The value can be specified with a `%` suffix in GMX Zero Hour to automatically use percentage mode (e.g., `AddMaxHealth = 50.0%`). The health increase is applied when the upgrade is activated and remains until the upgrade is removed.
- **Default**: `0.0`
- **Example**: `AddMaxHealth = 100.0` or `AddMaxHealth = 50.0%` (GMX Zero Hour only)

#### `ChangeType`

Available in: *(GMX, Retail 1.04)* (Generals, Zero Hour)

- **Type**: `MaxHealthChangeType` (see [MaxHealthChangeType Values](#maxhealthchangetype-values) section)
- **Description**: Controls how the current health is affected when maximum health is increased. Different types provide different behaviors for health management: `SAME_CURRENTHEALTH` keeps current health unchanged, `PRESERVE_RATIO` maintains the same health percentage, `ADD_CURRENT_HEALTH_TOO` adds the same amount to current health as maximum health, and `FULLY_HEAL` fully heals the object. This property works in conjunction with [AddMaxHealth](#addmaxhealth) to determine the final health state after the upgrade is applied.
- **Default**: `SAME_CURRENTHEALTH`
- **Example**: `ChangeType = PRESERVE_RATIO`
- **Available Values**: see [MaxHealthChangeType Values](#maxhealthchangetype-values)

#### `ValueType`

Available only in: *(GMX Zero Hour)*

- **Type**: `ValueType` (see [ValueType Values](#valuetype-values) section)
- **Description**: Controls how `AddMaxHealth` is interpreted. When set to `ABSOLUTE`, the value is added directly to maximum health. When set to `PERCENTAGE`, the value is treated as a percentage of the current maximum health (e.g., `50.0` means 50% of current maximum health). This property is automatically set when `AddMaxHealth` is specified with a `%` suffix. If `AddMaxHealth` contains a `%` symbol, `ValueType` is automatically set to `PERCENTAGE`; otherwise, it defaults to `ABSOLUTE`. This property is only available in GMX Zero Hour.
- **Default**: `ABSOLUTE`
- **Example**: `ValueType = PERCENTAGE`
- **Available Values**: see [ValueType Values](#valuetype-values)

### Upgrade Integration Settings

#### `TriggeredBy`

Available in: *(GMX, Retail 1.04)* (Generals, Zero Hour)

- **Type**: List of upgrade names (see [Upgrade documentation](../Upgrade.md))
- **Description**: List of upgrade names that must be active for this upgrade module to activate. When any of the listed upgrades (or all, if [RequiresAllTriggers](#requiresalltriggers) is `Yes`) become active, this upgrade module will activate and increase the object's maximum health. The upgrade names must reference valid `Upgrade` entries defined in the game. Multiple upgrade names can be specified by listing them multiple times or using a space-separated list, depending on the parser implementation.
- **Default**: Empty (no trigger required)
- **Example**: `TriggeredBy = Upgrade_HealthTraining`

#### `ConflictsWith`

Available in: *(GMX, Retail 1.04)* (Generals, Zero Hour)

- **Type**: List of upgrade names (see [Upgrade documentation](../Upgrade.md))
- **Description**: List of upgrade names that conflict with this upgrade module. If any of the conflicting upgrades are active, this upgrade module will not activate, even if [TriggeredBy](#triggeredby) conditions are met. This allows modders to create mutually exclusive upgrade paths. The upgrade names must reference valid `Upgrade` entries. Multiple conflicting upgrades can be specified.
- **Default**: Empty (no conflicts)
- **Example**: `ConflictsWith = Upgrade_BasicTraining`

#### `RequiresAllTriggers`

Available in: *(GMX, Retail 1.04)* (Generals, Zero Hour)

- **Type**: `Bool`
- **Description**: Controls whether all [TriggeredBy](#triggeredby) upgrades must be active, or if any one is sufficient. When `Yes`, all listed `TriggeredBy` upgrades must be active for this upgrade module to activate. When `No`, any one of the `TriggeredBy` upgrades being active is sufficient. This provides fine-grained control over upgrade activation conditions.
- **Default**: `No`
- **Example**: `RequiresAllTriggers = Yes`

#### `RequiredAnyUpgradeOf`

Available only in: *(GMX Zero Hour)*

- **Type**: List of upgrade names (see [Upgrade documentation](../Upgrade.md))
- **Description**: List of upgrade names where at least one must be active for this upgrade module to activate, in addition to [TriggeredBy](#triggeredby) conditions. This provides an OR condition: the upgrade module activates if `TriggeredBy` conditions are met AND at least one of the `RequiredAnyUpgradeOf` upgrades is active. The upgrade names must reference valid `Upgrade` entries. This property is only available in GMX Zero Hour.
- **Default**: Empty (no requirement)
- **Example**: `RequiredAnyUpgradeOf = Upgrade_Option1 Upgrade_Option2`

#### `RequiredAllUpgradesOf`

Available only in: *(GMX Zero Hour)*

- **Type**: List of upgrade names (see [Upgrade documentation](../Upgrade.md))
- **Description**: List of upgrade names where all must be active for this upgrade module to activate, in addition to [TriggeredBy](#triggeredby) conditions. This provides an AND condition: the upgrade module activates if `TriggeredBy` conditions are met AND all of the `RequiredAllUpgradesOf` upgrades are active. The upgrade names must reference valid `Upgrade` entries. This property is only available in GMX Zero Hour.
- **Default**: Empty (no requirement)
- **Example**: `RequiredAllUpgradesOf = Upgrade_Prerequisite1 Upgrade_Prerequisite2`

#### `RemovesUpgrades`

Available only in: *(GMX Zero Hour)*

- **Type**: List of upgrade names (see [Upgrade documentation](../Upgrade.md))
- **Description**: List of upgrade names that are automatically removed when this upgrade module activates. This allows creating upgrade paths where activating one upgrade removes others, useful for creating upgrade replacement systems or preventing conflicting upgrades from coexisting. The upgrade names must reference valid `Upgrade` entries. This property is only available in GMX Zero Hour.
- **Default**: Empty (no removals)
- **Example**: `RemovesUpgrades = Upgrade_OldVersion`

#### `FXListUpgrade`

Available in: *(GMX, Retail 1.04)* (Generals, Zero Hour)

- **Type**: `FXList` (see [FXList documentation](../FXList.md))
- **Description**: FXList to play when this upgrade module activates. The FXList is played once when the upgrade is applied, providing visual and audio feedback for the upgrade activation. The FXList must reference a valid `FXList` entry defined in the game. If not specified, no effects are played when the upgrade activates.
- **Default**: `NULL` (no effects)
- **Example**: `FXListUpgrade = FX_HealthUpgradeActivation`

## Enum Value Lists

<a id="maxhealthchangetype-values"></a>
#### `MaxHealthChangeType` Values

Available in: *(GMX, Retail 1.04)* (Generals, Zero Hour)

- **Source**: [BodyModule.h](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h) - `TheMaxHealthChangeTypeNames[]` array definition

- **`SAME_CURRENTHEALTH`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* — Keeps current health unchanged when maximum health is increased. If the object has 80 health out of 100 maximum, and maximum health is increased by 50, the object will have 80 health out of 150 maximum.
- **`PRESERVE_RATIO`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* — Maintains the same health percentage when maximum health is increased. If the object has 80 health out of 100 maximum (80% health), and maximum health is increased by 50, the object will have 120 health out of 150 maximum (maintaining 80%).
- **`ADD_CURRENT_HEALTH_TOO`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* — Adds the same amount to current health as is added to maximum health. If maximum health is increased by 50, current health is also increased by 50 (unless it would exceed the new maximum, in which case it is clamped to maximum).
- **`FULLY_HEAL`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* — Fully heals the object when maximum health is increased. Regardless of current health, the object's health is set to the new maximum health value.

<a id="valuetype-values"></a>
#### `ValueType` Values

Available only in: *(GMX Zero Hour)*

- **Source**: [GameType.h](../../GeneralsMD/Code/GameEngine/Include/Common/GameType.h) - `TheValueTypeNames[]` array definition

- **`ABSOLUTE`** *(GMX Zero Hour)* — The value is treated as an absolute amount. If `AddMaxHealth = 100.0` and `ValueType = ABSOLUTE`, the object's maximum health is increased by exactly 100.0, regardless of the current maximum health value.
- **`PERCENTAGE`** *(GMX Zero Hour)* — The value is treated as a percentage of the current maximum health. If `AddMaxHealth = 50.0` and `ValueType = PERCENTAGE`, and the object currently has 200 maximum health, the maximum health is increased by 100.0 (50% of 200). The value can also be specified with a `%` suffix in `AddMaxHealth` (e.g., `AddMaxHealth = 50.0%`), which automatically sets `ValueType` to `PERCENTAGE`.

## Examples

### Basic Health Increase

```ini
Upgrade = MaxHealthUpgrade ModuleTag_HealthBoost
  AddMaxHealth = 100.0
  ChangeType = SAME_CURRENTHEALTH
  TriggeredBy = Upgrade_HealthTraining
End
```

### Health Increase with Ratio Preservation

```ini
Upgrade = MaxHealthUpgrade ModuleTag_HealthUpgrade
  AddMaxHealth = 50.0
  ChangeType = PRESERVE_RATIO
  TriggeredBy = Upgrade_AdvancedTraining
End
```

### Health Increase with Current Health Boost

```ini
Upgrade = MaxHealthUpgrade ModuleTag_HealthBoost
  AddMaxHealth = 75.0
  ChangeType = ADD_CURRENT_HEALTH_TOO
  TriggeredBy = Upgrade_MedicalTraining
End
```

### Full Heal with Health Increase

```ini
Upgrade = MaxHealthUpgrade ModuleTag_HealthRestore
  AddMaxHealth = 200.0
  ChangeType = FULLY_HEAL
  TriggeredBy = Upgrade_EmergencyHealing
End
```

### Percentage-Based Health Increase (GMX Zero Hour Only)

```ini
Upgrade = MaxHealthUpgrade ModuleTag_PercentageHealth
  AddMaxHealth = 50.0%
  ChangeType = PRESERVE_RATIO
  TriggeredBy = Upgrade_PercentageBoost
End
```

### Conditional Upgrade with Conflicts

```ini
Upgrade = MaxHealthUpgrade ModuleTag_ConditionalHealth
  AddMaxHealth = 150.0
  ChangeType = ADD_CURRENT_HEALTH_TOO
  TriggeredBy = Upgrade_EliteTraining
  ConflictsWith = Upgrade_BasicTraining
  RequiresAllTriggers = Yes
End
```

## Usage

Place under `Upgrade = MaxHealthUpgrade ModuleTag_XX` inside [Object](../Object.md) entries. In GMX, `MaxHealthUpgrade` can also be added to `ObjectExtend` entries. See [Template](#template) for correct syntax.

**Placement**:
- **Retail**: `MaxHealthUpgrade` can only be added to [Object](../Object.md) entries .
- **GMX**: `MaxHealthUpgrade` can be added to both [Object](../Object.md) and `ObjectExtend` entries.

**Limitations**:
- Objects must have a body module (such as [ActiveBody](../ObjectBody/ActiveBody.md)) to function properly. If no body module exists, the upgrade will not affect health.
- Health increases are additive, not multiplicative. Multiple `MaxHealthUpgrade` instances will each add their `AddMaxHealth` value to the maximum health.
- The health increase is permanent until the upgrade is removed. Removing the triggering upgrade will not automatically revert the health increase unless the upgrade system is configured to handle removal.
- In GMX Zero Hour, when using percentage values, the percentage is calculated based on the maximum health at the time the upgrade is applied, not the original maximum health. If multiple percentage-based upgrades are applied, each calculates its percentage from the current maximum health at that moment.

**Conditions**:
- `MaxHealthUpgrade` increases the object's maximum health when the specified upgrade in [TriggeredBy](#triggeredby) is applied.
- The upgrade integrates with the upgrade system for conditional activation based on [TriggeredBy](#triggeredby), [ConflictsWith](#conflictswith), and other upgrade conditions.
- Different health change types control how current health is affected when maximum health is increased. The [ChangeType](#changetype) property determines whether current health remains unchanged, maintains ratio, is boosted, or is fully healed.
- The upgrade works with objects that have body modules (such as [ActiveBody](../ObjectBody/ActiveBody.md)).
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own health increases and conditions. Each instance will add its `AddMaxHealth` value when its [TriggeredBy](#triggeredby) conditions are met.
- **ObjectExtend (GMX only)**: When `MaxHealthUpgrade` is added to an `ObjectExtend` entry with the same `ModuleTag` name as the base object, the base object's `MaxHealthUpgrade` module is automatically replaced. ObjectExtend automatically clears modules with matching `ModuleTag` names when adding new modules.
- **ObjectReskin (both Retail and GMX)**: ObjectReskin uses the same module system as Object. Adding `MaxHealthUpgrade` to an ObjectReskin entry with the same `ModuleTag` name as the base object will cause a duplicate module tag error, as ObjectReskin does not support automatic module replacement like ObjectExtend.

**Dependencies**:
- Requires an object with a body module (such as [ActiveBody](../ObjectBody/ActiveBody.md)) to function properly. The upgrade calls `BodyModuleInterface::setMaxHealth()` to modify health, so without a body module, the upgrade has no effect.
- Requires the upgrade system to be properly configured. The [TriggeredBy](#triggeredby) property must reference valid [Upgrade](../Upgrade.md) entries defined in the game. If the referenced upgrades do not exist, the upgrade module will not activate.
- In GMX Zero Hour, when using percentage-based health increases, the upgrade system calculates the percentage based on the body module's current maximum health at the time of activation.

## Template

```ini
Upgrade = MaxHealthUpgrade ModuleTag_XX
  ; Health Modification Settings
  AddMaxHealth = 0.0               ; // amount of maximum health to add (absolute or percentage with % suffix in GMX Zero Hour) *(GMX, Retail 1.04)*
  ChangeType = SAME_CURRENTHEALTH  ; // how current health is affected *(GMX, Retail 1.04)*
  ValueType = ABSOLUTE             ; // how AddMaxHealth is interpreted (GMX Zero Hour only) *(GMX Zero Hour)*
  
  ; Upgrade Integration Settings
  TriggeredBy =                    ; // required upgrade flags *(GMX, Retail 1.04)*
  ConflictsWith =                  ; // conflicting upgrade flags *(GMX, Retail 1.04)*
  RequiresAllTriggers = No         ; // require all TriggeredBy upgrades *(GMX, Retail 1.04)*
  RequiredAnyUpgradeOf =           ; // require any of these upgrades (GMX Zero Hour only) *(GMX Zero Hour)*
  RequiredAllUpgradesOf =          ; // require all of these upgrades (GMX Zero Hour only) *(GMX Zero Hour)*
  RemovesUpgrades =                ; // upgrades to remove when activated (GMX Zero Hour only) *(GMX Zero Hour)*
  FXListUpgrade =                  ; // effects to play when activated *(GMX, Retail 1.04)*
End
```

## Notes

- `MaxHealthUpgrade` increases the object's maximum health when the specified upgrade is applied, providing enhanced durability and survivability.
- The upgrade integrates with the upgrade system for conditional activation, allowing complex upgrade trees and dependencies.
- Different health change types (`ChangeType`) control how current health is affected, providing flexibility in health management strategies.
- Health increases are additive: if multiple `MaxHealthUpgrade` instances are active, each adds its `AddMaxHealth` value to the maximum health.
- In GMX Zero Hour, percentage-based health increases allow scaling health boosts relative to the object's current maximum health, making upgrades more balanced across different unit types.
- The upgrade works with objects that have body modules (such as [ActiveBody](../ObjectBody/ActiveBody.md)). Objects without body modules will not be affected.
- The health increase is permanent until the upgrade is removed. Removing the triggering upgrade does not automatically revert the health increase unless the upgrade system handles removal explicitly.
- In GMX Zero Hour, when `AddMaxHealth` is specified with a `%` suffix (e.g., `AddMaxHealth = 50.0%`), `ValueType` is automatically set to `PERCENTAGE` and the value is parsed accordingly.

## Modder Recommended Use Scenarios

(pending modder review)

## Source Files

**Base Class:** [UpgradeModule](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h)

- Header (GMX Zero Hour): [MaxHealthUpgrade.h](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/MaxHealthUpgrade.h)
- Source (GMX Zero Hour): [MaxHealthUpgrade.cpp](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/MaxHealthUpgrade.cpp)
- Header (GMX Generals): [MaxHealthUpgrade.h](../../Generals/Code/GameEngine/Include/GameLogic/Module/MaxHealthUpgrade.h)
- Source (GMX Generals): [MaxHealthUpgrade.cpp](../../Generals/Code/GameEngine/Source/GameLogic/Object/Upgrade/MaxHealthUpgrade.cpp)

## Changes History

- 03/01/2025 — AI — Reconstructs documentation following DocAuthoringGuide with complete property documentation, versioning, enum lists, and examples

## Status

- **Documentation Status**: AI-generated
- **Last Updated**: 03/01/2025 by @AI
- **Certification**: 0/2 reviews

### Reviewers

- No reviews yet
