# AutoHealBehavior

Status: AI-generated, 0/2 reviews

## Overview

The `AutoHealBehavior` module manages automatic healing systems that can heal the object itself or nearby friendly units within a specified radius. It supports upgrade-based activation, area healing, particle effects, and selective healing based on object types. The behavior is commonly used for medical buildings, repair facilities, and units with regenerative abilities. This is a module added inside `Object` entries.

Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

## Table of Contents

- [Overview](#overview)
- [Properties](#properties)
  - [Basic Healing Settings](#basic-healing-settings)
  - [Area Healing Settings](#area-healing-settings)
  - [Component Healing Settings](#component-healing-settings)
  - [Upgrade Integration](#upgrade-integration)
  - [Particle Effects](#particle-effects)
  - [Target Selection](#target-selection)
- [Enum Value Lists](#enum-value-lists)
- [Examples](#examples)
- [Usage](#usage)
- [Template](#template)
- [Notes](#notes)
- [Modder Recommended Use Scenarios](#modder-recommended-use-scenarios)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Document Log](#document-log)
- [Status](#status)
- [Reviewers](#reviewers)

## Properties

### Basic Healing Settings

Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

#### `HealingAmount`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Int`
- **Description**: Amount of health points healed per healing pulse. Higher values heal more health per tick, providing faster recovery. Lower values heal less per tick, requiring more time for full healing. At 0 (default), no healing occurs and the behavior is effectively disabled.
- **Default**: `0`
- **Example**: `HealingAmount = 3`

#### `HealingDelay`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time interval between healing pulses. Lower values provide faster healing rates, while higher values slow down the healing process. This controls how frequently healing occurs. The value is parsed as milliseconds and converted to game frames. If not specified (defaults to UINT_MAX), the behavior will not heal regularly and must be activated manually or through upgrades.
- **Default**: `4294967295` (UINT_MAX, effectively disabled - must be set for healing to occur)
- **Example**: `HealingDelay = 1000`

#### `StartsActive`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether the healing behavior is active from the start. When `Yes`, healing begins immediately upon object creation. When `No` (default), healing must be activated by upgrades or other conditions.
- **Default**: `No`
- **Example**: `StartsActive = No`

#### `SingleBurst`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether to perform only a single healing burst instead of continuous healing. When `Yes`, healing occurs once then stops. When `No` (default), healing continues at regular intervals until disabled.
- **Default**: `No`
- **Example**: `SingleBurst = Yes`

#### `StartHealingDelay`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Delay after taking damage before auto-healing starts. Higher values require longer waiting periods after damage before healing begins. At 0 (default), healing starts immediately when conditions are met. This only applies when healing the object itself (radius = 0).
- **Default**: `0`
- **Example**: `StartHealingDelay = 5000`

### Area Healing Settings

Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

#### `Radius`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real` (distance)
- **Description**: Radius for area healing effect. Higher values extend the healing range to affect more nearby units. At 0.0 (default), only heals the object itself.
- **Default**: `0.0`
- **Example**: `Radius = 50.0`

#### `AffectsWholePlayer`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether to affect all objects owned by the player instead of just those in radius. When `Yes`, heals all player units regardless of distance. When `No` (default), only affects units within the specified [Radius](#radius).
- **Default**: `No`
- **Example**: `AffectsWholePlayer = Yes`

#### `SkipSelfForHealing`
Available in: *(GMX Zero Hour, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether to skip healing the object itself when doing area healing. When `Yes`, the healing object does not heal itself, only nearby units. When `No` (default), the object heals both itself and nearby units.
- **Default**: `No`
- **Example**: `SkipSelfForHealing = Yes`

### Component Healing Settings

Available only in: *(GMX Zero Hour)*

#### `ComponentHealingAmount`
Available only in: *(GMX Zero Hour)*

- **Type**: `Real`
- **Description**: Amount of healing applied to components per healing pulse. When set to -1.0 (default), component healing is proportional to main health healing (heals components by the same percentage as main health). When set to 0.0, no component healing occurs. When set to a positive value, components are healed by that amount multiplied by the healing needed (max health - current health). Component healing respects each component's [HealingType](../ObjectBody/ObjectComponents/Component.md#healingtype) setting, which may restrict healing based on component health state. For AutoHealBehavior to heal components, this property must be set to a non-zero value.
- **Default**: `-1.0` (proportional healing)
- **Example**: `ComponentHealingAmount = -1.0`

### Upgrade Integration

Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

These properties are inherited from `UpgradeMux` and allow AutoHealBehavior to be activated by upgrades.

#### `TriggeredBy`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: Upgrade name or list of upgrade names (see [Upgrade documentation](../Upgrade.md))
- **Description**: Required upgrade names to activate the healing behavior. When set, healing only occurs when at least one of the specified upgrades is active (unless [RequiresAllTriggers](#requiresalltriggers) is `Yes`). When empty (default), healing can occur without upgrade requirements. Multiple upgrade names can be specified as a space-separated list. This property accepts a list of upgrade names that are resolved to upgrade flags internally.
- **Default**: `""` (empty, no requirements)
- **Example**: `TriggeredBy = Upgrade_GLAJunkRepair`

#### `RequiredAnyUpgradeOf`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: Upgrade name or list of upgrade names (see [Upgrade documentation](../Upgrade.md))
- **Description**: Alternative upgrade names that can activate the healing behavior. When set, healing occurs when at least one of the specified upgrades is active (in addition to [TriggeredBy](#triggeredby) requirements). When empty (default), only [TriggeredBy](#triggeredby) upgrades are checked. Multiple upgrade names can be specified as a space-separated list. This property accepts a list of upgrade names that are resolved to upgrade flags internally.
- **Default**: `""` (empty)
- **Example**: `RequiredAnyUpgradeOf = Upgrade_MedicalUpgrade Upgrade_RepairUpgrade`

#### `RequiredAllUpgradesOf`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: Upgrade name or list of upgrade names (see [Upgrade documentation](../Upgrade.md))
- **Description**: Upgrade names that must all be active for the healing behavior to activate. When set, all specified upgrades must be active (in addition to [TriggeredBy](#triggeredby) requirements). When empty (default), only [TriggeredBy](#triggeredby) upgrades are checked. Multiple upgrade names can be specified as a space-separated list. This property accepts a list of upgrade names that are resolved to upgrade flags internally.
- **Default**: `""` (empty)
- **Example**: `RequiredAllUpgradesOf = Upgrade_MedicalUpgrade Upgrade_TechUpgrade`

#### `ConflictsWith`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: Upgrade name or list of upgrade names (see [Upgrade documentation](../Upgrade.md))
- **Description**: Upgrade names that conflict with this healing behavior. When any of the specified upgrades are active, healing is disabled. When empty (default), no upgrade conflicts prevent healing. Multiple upgrade names can be specified as a space-separated list. This property accepts a list of upgrade names that are resolved to upgrade flags internally.
- **Default**: `""` (empty, no conflicts)
- **Example**: `ConflictsWith = Upgrade_GLACamoNetting`

#### `RemovesUpgrades`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: Upgrade name or list of upgrade names (see [Upgrade documentation](../Upgrade.md))
- **Description**: Upgrade names that are removed when this healing behavior activates. When set, the specified upgrades are removed from the object when the healing behavior is activated. When empty (default), no upgrades are removed. Multiple upgrade names can be specified as a space-separated list. This property accepts a list of upgrade names that are resolved to upgrade flags internally.
- **Default**: `""` (empty)
- **Example**: `RemovesUpgrades = Upgrade_OldHealing`

#### `RequiresAllTriggers`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether all [TriggeredBy](#triggeredby) upgrades must be active (`Yes`) or just one (`No`). When `Yes`, all specified upgrades must be active for healing. When `No` (default), only one upgrade needs to be active.
- **Default**: `No`
- **Example**: `RequiresAllTriggers = Yes`

#### `FXListUpgrade`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `FXList` (see [FXList documentation](../FXList.md))
- **Description**: FXList played when the upgrade activates. When set, displays visual and audio effects when the healing behavior is activated by upgrades. When empty (default), no upgrade activation effects are shown.
- **Default**: `""` (empty)
- **Example**: `FXListUpgrade = FX_HealUpgrade`

### Particle Effects

Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

#### `RadiusParticleSystemName`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `ParticleSystemTemplate` (see [ParticleSystem documentation](../ParticleSystem.md))
- **Description**: Particle system played for the entire area healing effect duration. When set, displays visual effects during area healing. When empty (default), no particle effects are shown.
- **Default**: `""` (empty)
- **Example**: `RadiusParticleSystemName = FX_HealArea`

#### `UnitHealPulseParticleSystemName`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `ParticleSystemTemplate` (see [ParticleSystem documentation](../ParticleSystem.md))
- **Description**: Particle system played on each unit when it receives healing. When set, displays visual effects on individual units during healing. When empty (default), no pulse effects are shown.
- **Default**: `""` (empty)
- **Example**: `UnitHealPulseParticleSystemName = FX_HealPulse`

### Target Selection

Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

#### `KindOf`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `KindOfMaskType` (bit flags) (see [KindOf documentation](../enums/KindOf.md))
- **Description**: Object types that can be healed by this behavior. When set, only objects with matching types can be healed. When 0 (default, all bits set), all object types can be healed.
- **Default**: `0` (all types)
- **Example**: `KindOf = INFANTRY VEHICLE`

#### `ForbiddenKindOf`
Available in: *(GMX Zero Hour, Retail Zero Hour 1.04)*

- **Type**: `KindOfMaskType` (bit flags) (see [KindOf documentation](../enums/KindOf.md))
- **Description**: Object types that cannot be healed by this behavior. When set, objects with matching types are excluded from healing. When 0 (default), no object types are forbidden from healing.
- **Default**: `0` (no restrictions)
- **Example**: `ForbiddenKindOf = STRUCTURE`

## Examples

### Scout Van Auto Heal
```ini
Behavior = AutoHealBehavior ModuleTag_01
  HealingAmount = 3
  HealingDelay = 1000
  TriggeredBy = Upgrade_GLAJunkRepair
End
```

### Scrap Yard Auto Heal
```ini
Behavior = AutoHealBehavior ModuleTag_02
  HealingAmount = 2
  HealingDelay = 1000
  StartsActive = No
  TriggeredBy = Upgrade_GLAJunkRepair
End
```

### Medical Building Area Heal
```ini
Behavior = AutoHealBehavior ModuleTag_03
  HealingAmount = 5
  HealingDelay = 2000
  Radius = 100.0
  KindOf = INFANTRY VEHICLE
  ForbiddenKindOf = STRUCTURE
  RadiusParticleSystemName = FX_HealArea
  UnitHealPulseParticleSystemName = FX_HealPulse
  StartsActive = Yes
End
```

### Single Burst Heal
```ini
Behavior = AutoHealBehavior ModuleTag_04
  HealingAmount = 50
  SingleBurst = Yes
  KindOf = INFANTRY
  AffectsWholePlayer = Yes
  SkipSelfForHealing = Yes
End
```

### Component Healing Example (GMX Zero Hour only)
```ini
Behavior = AutoHealBehavior ModuleTag_05
  HealingAmount = 10
  HealingDelay = 1000
  ComponentHealingAmount = -1.0
  StartsActive = Yes
End
```

## Usage

Place under `Behavior = AutoHealBehavior ModuleTag_XX` inside [Object](../Object.md) entries. In GMX, AutoHealBehavior can also be added to [ObjectExtend](../ObjectExtend.md) entries. See [Template](#template) for correct syntax.

**Placement**:
- **Retail**: AutoHealBehavior can only be added to `Object` entries.
- **GMX**: AutoHealBehavior can be added to both `Object` and `ObjectExtend` entries.

Multiple instances of AutoHealBehavior can be added to the same object. Each instance operates independently with its own healing rates, conditions, and upgrade requirements.

**Limitations**:
- Healing only works on objects within the same team/player. Objects must be owned by the same player as the healing object.
- Area healing is limited by the specified [Radius](#radius) or player ownership ([AffectsWholePlayer](#affectswholeplayer)). Objects outside the radius (or not owned by the player when `AffectsWholePlayer` is `No`) cannot be healed.
- The behavior can be configured for single burst healing ([SingleBurst](#singleburst)) or continuous healing over time. When [SingleBurst](#singleburst) is `Yes`, healing occurs once then stops.
- Objects must have a health system (typically [ActiveBody](../ObjectBody/ActiveBody.md)) to receive healing. Objects without health systems cannot be healed.
- When [HealingAmount](#healingamount) is 0, no healing occurs and the behavior is effectively disabled.
- When [HealingDelay](#healingdelay) is not specified (defaults to UINT_MAX), the behavior will not heal regularly and must be activated manually or through upgrades.
- Component healing ([ComponentHealingAmount](#componenthealingamount)) only works on objects with components (GMX Zero Hour only). Component healing respects each component's healing type restrictions.

**Conditions**:
- AutoHealBehavior can heal individual objects (when [Radius](#radius) is 0.0) or provide area healing within a specified radius (when [Radius](#radius) > 0.0).
- The behavior integrates with the upgrade system for conditional activation. When [TriggeredBy](#triggeredby) is set, healing only occurs when the specified upgrades are active (see [Upgrade Integration](#upgrade-integration) properties).
- Area healing can target specific object types using [KindOf](#kindof) and [ForbiddenKindOf](#forbiddenkindof) filters (see [Target Selection](#target-selection) properties).
- Particle effects provide visual feedback for healing operations when [RadiusParticleSystemName](#radiusparticlesystemname) or [UnitHealPulseParticleSystemName](#unithealpulseparticlesystemname) are set.
- When [StartsActive](#startsactive) is `Yes`, healing begins immediately upon object creation. When `No`, healing must be activated by upgrades.
- When [SingleBurst](#singleburst) is `Yes`, healing occurs once then the behavior goes to sleep. When `No`, healing continues at regular intervals.
- When [StartHealingDelay](#starthealingdelay) is set, the object waits for the specified delay after taking damage before auto-healing starts. This only applies when healing the object itself ([Radius](#radius) = 0).
- AutoHealBehavior continues to heal even when objects are held (stunned/immobilized) or jammed (electronically disabled). Healing is not interrupted by these disabled states.
- **Multiple instances behavior**: Multiple instances of AutoHealBehavior can coexist on the same object. Each instance operates independently with its own healing rates, conditions, upgrade requirements, and target filters.
- **ObjectExtend (GMX only)**: When AutoHealBehavior is added to an `ObjectExtend` entry with the same `ModuleTag` name as the base object, the base object's AutoHealBehavior module is automatically replaced. ObjectExtend automatically clears modules with matching `ModuleTag` names when adding new modules.
- **ObjectReskin (both Retail and GMX)**: ObjectReskin uses the same module system as Object. Adding AutoHealBehavior to an ObjectReskin entry with the same `ModuleTag` name as the base object will cause a duplicate module tag error, as ObjectReskin does not support automatic module replacement like ObjectExtend.

**Dependencies**:
- Requires an object with a health system (typically [ActiveBody](../ObjectBody/ActiveBody.md)) to function. AutoHealBehavior works with all body types that implement `BodyModuleInterface`: [ActiveBody](../ObjectBody/ActiveBody.md), [StructureBody](../ObjectBody/StructureBody.md), [HighlanderBody](../ObjectBody/HighlanderBody.md), [ImmortalBody](../ObjectBody/ImmortalBody.md), [UndeadBody](../ObjectBody/UndeadBody.md) (both first and second life), and [HiveStructureBody](../ObjectBody/HiveStructureBody.md). AutoHealBehavior does not work with [InactiveBody](../ObjectBody/InactiveBody.md) because those objects are marked as "effectively dead" and are skipped by the healing system.
- Healing is affected by damage types and armor systems (see [Armor](../Armor.md)). Armor and damage type interactions apply to healing calculations.
- When [ComponentHealingAmount](#componenthealingamount) is set (GMX Zero Hour only), objects must have components (see [Component](../ObjectBody/ObjectComponents/Component.md)) for component healing to occur. Component healing respects each component's [HealingType](../ObjectBody/ObjectComponents/Component.md#healingtype) setting.

## Template

```ini
Behavior = AutoHealBehavior ModuleTag_XX
  ; Basic Healing Settings
  HealingAmount = 0                       ; // health points healed per pulse *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*
  HealingDelay = 4294967295               ; // milliseconds between healing pulses (must be set for healing) *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*
  StartsActive = No                       ; // whether healing starts active *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*
  SingleBurst = No                        ; // whether to perform single burst only *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*
  StartHealingDelay = 0                   ; // delay after damage before healing starts *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

  ; Area Healing Settings
  Radius = 0.0                            ; // healing radius (0 = self only) *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*
  AffectsWholePlayer = No                 ; // affect all player objects *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*
  SkipSelfForHealing = No                 ; // skip self when area healing *(GMX Zero Hour, Retail Zero Hour 1.04)*

  ; Component Healing Settings (GMX Zero Hour only)
  ComponentHealingAmount = -1.0           ; // component healing amount (-1 = proportional, 0 = none) *(GMX Zero Hour only)*

  ; Upgrade Integration
  TriggeredBy =                           ; // required upgrade names *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*
  RequiredAnyUpgradeOf =                  ; // alternative upgrade names (any required) *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*
  RequiredAllUpgradesOf =                 ; // upgrade names (all required) *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*
  ConflictsWith =                         ; // conflicting upgrade names *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*
  RemovesUpgrades =                       ; // upgrade names to remove on activation *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*
  RequiresAllTriggers = No                ; // require all TriggeredBy upgrades *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*
  FXListUpgrade =                         ; // upgrade activation FXList *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

  ; Particle Effects
  RadiusParticleSystemName =              ; // area healing particle system *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*
  UnitHealPulseParticleSystemName =       ; // unit healing particle system *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

  ; Target Selection
  KindOf =                                ; // allowed object types *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*
  ForbiddenKindOf =                       ; // forbidden object types *(GMX Zero Hour, Retail Zero Hour 1.04)*
End
```

## Notes

- AutoHealBehavior can heal individual objects or provide area healing within a specified radius. The behavior supports three modes: self-healing ([Radius](#radius) = 0), radius-based area healing, and player-wide healing ([AffectsWholePlayer](#affectswholeplayer) = Yes).
- The behavior integrates with the upgrade system for conditional activation. When [TriggeredBy](#triggeredby) is set, healing only occurs when the specified upgrades are active. Upgrade conflicts ([ConflictsWith](#conflictswith)) can disable healing when conflicting upgrades are active. Additional upgrade requirements can be specified using [RequiredAnyUpgradeOf](#requiredanyupgradeof) and [RequiredAllUpgradesOf](#requiredallupgradesof).
- Area healing can target specific object types using [KindOf](#kindof) and [ForbiddenKindOf](#forbiddenkindof) filters. Objects must match [KindOf](#kindof) types and not match [ForbiddenKindOf](#forbiddenkindof) types to be healed.
- Particle effects provide visual feedback for healing operations. [RadiusParticleSystemName](#radiusparticlesystemname) displays effects for the entire area healing duration, while [UnitHealPulseParticleSystemName](#unithealpulseparticlesystemname) displays effects on each unit when it receives healing.
- The behavior can be configured for single burst healing ([SingleBurst](#singleburst)) or continuous healing over time. When [SingleBurst](#singleburst) is `Yes`, healing occurs once then stops.
- Objects with [ActiveBody](../ObjectBody/ActiveBody.md) can be healed by AutoHealBehavior. Healing is affected by damage types and armor systems (see [Armor](../Armor.md)).
- Component healing ([ComponentHealingAmount](#componenthealingamount)) allows AutoHealBehavior to heal object components in addition to main health (GMX Zero Hour only). Component healing respects each component's healing type restrictions and can be proportional to main health healing or use a fixed amount.
- When [StartHealingDelay](#starthealingdelay) is set, the object waits for the specified delay after taking damage before auto-healing starts. This only applies when healing the object itself ([Radius](#radius) = 0).
- AutoHealBehavior continues to heal even when objects are held (stunned/immobilized) or jammed (electronically disabled). Healing is not interrupted by these disabled states.
- Multiple instances of AutoHealBehavior can coexist on the same object. Each instance operates independently with its own healing rates, conditions, upgrade requirements, and target filters.

## Modder Recommended Use Scenarios

(pending modder review)

## Source Files

**Base Class:** [UpdateModule](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h) (GMX Zero Hour), [UpdateModule](../../Generals/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h) (GMX Generals), [UpgradeMux](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h) (GMX Zero Hour), [UpgradeMux](../../Generals/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h) (GMX Generals), [DamageModuleInterface](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DamageModule.h) (GMX Zero Hour), [DamageModuleInterface](../../Generals/Code/GameEngine/Include/GameLogic/Module/DamageModule.h) (GMX Generals)

- Header (GMX Zero Hour): [AutoHealBehavior.h](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AutoHealBehavior.h)
- Source (GMX Zero Hour): [AutoHealBehavior.cpp](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/AutoHealBehavior.cpp)
- Header (GMX Generals): [AutoHealBehavior.h](../../Generals/Code/GameEngine/Include/GameLogic/Module/AutoHealBehavior.h)
- Source (GMX Generals): [AutoHealBehavior.cpp](../../Generals/Code/GameEngine/Source/GameLogic/Object/Behavior/AutoHealBehavior.cpp)

## Changes History

- GMX Zero Hour — Adds [ComponentHealingAmount](#componenthealingamount) property for component healing support.

## Document Log

- 16/12/2025 — AI — Initial document created.

## Status

- Documentation Status: AI-generated
- Last Updated: 16/12/2025 by AI
- Certification: 0/2 reviews

### Reviewers

- (pending)
