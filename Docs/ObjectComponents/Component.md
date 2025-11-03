# Component *(GMX)*

Status: AI-generated, 0/2 reviews

## Overview
The base `Component` defines shared health and behavior for parts attached to an [Object](../Object.md) via [ActiveBody](../ObjectModules/ActiveBody.md). Components enable per-part health, visuals, and effects that integrate with the main object's body. Components can be damaged, healed, replaced, and their status affects gameplay systems like movement, weapons, and visual appearance. This is a module added inside `Object` entries.

Available only in: *(GMX Zero Hour)*

## Table of Contents
- [Overview](#overview)
- [Properties](#properties)
  - [Health Settings](#health-settings)
  - [Healing and Damage Settings](#healing-and-damage-settings)
  - [Replacement Settings](#replacement-settings)
  - [Visual Appearance Settings](#visual-appearance-settings)
  - [Status Icon Settings](#status-icon-settings)
- [Enum Value Lists](#enum-value-lists)
- [Examples](#examples)
- [Usage](#usage)
- [Template](#template)
- [Notes](#notes)
- [Modder Recommended Use Scenarios](#modder-recommended-use-scenarios)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
- [Reviewers](#reviewers)

## Properties

### Health Settings
Available only in: *(GMX Zero Hour)*

<a id="maxhealth"></a>
#### `MaxHealth`
Available only in: *(GMX Zero Hour)*

- **Type**: `Real` (can include `%` suffix for percentage of main object health)
- **Description**: Maximum health for this component. Higher values increase durability. Can be specified as absolute value (e.g., `100.0`) or percentage of main object's max health (e.g., `50%`). If percentage is used (contains `%` suffix), [MaxHealthValueType](#maxhealthvaluetype) is automatically set to `PERCENTAGE` during parsing. At initialization, percentage values are calculated as a percentage of the main object's max health.
- **Default**: `0.0`
- **Example**: `MaxHealth = 100.0` or `MaxHealth = 50%`

<a id="initialhealth"></a>
#### `InitialHealth`
Available only in: *(GMX Zero Hour)*

- **Type**: `Real` (can include `%` suffix for percentage of main object health)
- **Description**: Starting health for this component when the object is created. Can be specified as absolute value or percentage of main object's max health. If percentage is used (contains `%` suffix), [InitialHealthValueType](#initialhealthvaluetype) is automatically set to `PERCENTAGE` during parsing. At initialization, percentage values are calculated as a percentage of the main object's max health. Automatically clamped to [MaxHealth](#maxhealth) and `0.0` during component initialization when the object is created.
- **Default**: `0.0`
- **Example**: `InitialHealth = 100.0` or `InitialHealth = 50%`

<a id="maxhealthvaluetype"></a>
#### `MaxHealthValueType`
Available only in: *(GMX Zero Hour)*

- **Type**: `ValueType` (see ValueType documentation)
- **Description**: How [MaxHealth](#maxhealth) is calculated — `ABSOLUTE` for fixed values or `PERCENTAGE` for percentage of main object health. Automatically set when [MaxHealth](#maxhealth) includes `%` suffix during parsing. If not explicitly set and [MaxHealth](#maxhealth) has no `%` suffix, defaults to `ABSOLUTE`.
- **Default**: `ABSOLUTE`
- **Example**: `MaxHealthValueType = PERCENTAGE`

<a id="initialhealthvaluetype"></a>
#### `InitialHealthValueType`
Available only in: *(GMX Zero Hour)*

- **Type**: `ValueType` (see ValueType documentation)
- **Description**: How [InitialHealth](#initialhealth) is calculated — `ABSOLUTE` for fixed values or `PERCENTAGE` for percentage of main object health. Automatically set when [InitialHealth](#initialhealth) includes `%` suffix during parsing. If not explicitly set and [InitialHealth](#initialhealth) has no `%` suffix, defaults to `ABSOLUTE`.
- **Default**: `ABSOLUTE`
- **Example**: `InitialHealthValueType = PERCENTAGE`

### Healing and Damage Settings
Available only in: *(GMX Zero Hour)*

<a id="healingtype"></a>
#### `HealingType`
Available only in: *(GMX Zero Hour)*

- **Type**: `ComponentHealingType` (see [ComponentHealingType Values](#componenthealingtype-values))
- **Description**: Controls how the component can be healed. Different types restrict healing to specific health ranges or require replacement for full healing. `NORMAL` allows full healing from destroyed to max. `PARTIAL_ONLY` prevents healing when destroyed. `PARTIAL_DESTROYED` allows healing from destroyed only to partially working (50%). `PARTIAL_LIMITED` allows healing only to partially working (50%) when not destroyed, and prevents healing when destroyed. `REPLACEMENT_ONLY` prevents all normal healing and requires GUI replacement.
- **Default**: `NORMAL`
- **Example**: `HealingType = NORMAL`
- **Available Values**: see [ComponentHealingType Values](#componenthealingtype-values)

<a id="damageonsides"></a>
#### `DamageOnSides`
Available only in: *(GMX Zero Hour)*

- **Type**: `HitSideFlags` (list of [HitSide Values](#hitside-values))
- **Description**: Which hit sides can damage this component. If empty, all sides can damage the component. If specified, only listed sides can cause damage. Used for side-specific armor on components. Parsed using full hit side names with "HIT_SIDE_" prefix: `HIT_SIDE_FRONT`, `HIT_SIDE_BACK`, `HIT_SIDE_LEFT`, `HIT_SIDE_RIGHT`, `HIT_SIDE_TOP`, `HIT_SIDE_BOTTOM`. Note: `HIT_SIDE_UNKNOWN` exists in the enum but is not parseable for this property.
- **Default**: Empty (all sides)
- **Example**: `DamageOnSides = HIT_SIDE_FRONT HIT_SIDE_TOP` or `DamageOnSides = HIT_SIDE_BACK HIT_SIDE_LEFT HIT_SIDE_RIGHT`
- **Available Values**: `HIT_SIDE_FRONT`, `HIT_SIDE_BACK`, `HIT_SIDE_LEFT`, `HIT_SIDE_RIGHT`, `HIT_SIDE_TOP`, `HIT_SIDE_BOTTOM` (see [HitSide Values](#hitside-values) for full enum list)

### Replacement Settings
Available only in: *(GMX Zero Hour)*

<a id="replacementcost"></a>
#### `ReplacementCost`
Available only in: *(GMX Zero Hour)*

- **Type**: `UnsignedInt`
- **Description**: Money cost to fully replace this component via GUI command system. At 0 (default), the component cannot be replaced via GUI commands. Replacement fully restores component health to maximum.
- **Default**: `0`
- **Example**: `ReplacementCost = 300`

<a id="forcereturnondestroy"></a>
#### `ForceReturnOnDestroy`
Available only in: *(GMX Zero Hour)*

- **Type**: `Bool`
- **Description**: Whether the unit should be forced to return to base when this component is destroyed. When `Yes`, aircraft will automatically return to base when this component is destroyed (checked by [JetAIUpdate](../ObjectUpdates/JetAIUpdate.md)). When `No`, component destruction does not trigger return behavior.
- **Default**: `No`
- **Example**: `ForceReturnOnDestroy = Yes`

### Visual Appearance Settings
Available only in: *(GMX Zero Hour)*

<a id="damagedstatustype"></a>
#### `DamagedStatusType`
Available only in: *(GMX Zero Hour)*

- **Type**: `BodyDamageType` (see [BodyDamageType Values](#bodydamagetype-values))
- **Description**: Body damage state to set when the component is damaged (10% - 50% health, which corresponds to partially functional status). Controls visual appearance of the object model. Set to one of the [BodyDamageType Values](#bodydamagetype-values) or leave empty/unset (0) for no visual change. The damage state is applied to the main object's body when component health falls within this range.
- **Default**: `0` (no change)
- **Example**: `DamagedStatusType = DAMAGED` or `DamagedStatusType = COMPONENT_ENGINE_DAMAGED`
- **Available Values**: see [BodyDamageType Values](#bodydamagetype-values)

<a id="destroyedstatustype"></a>
#### `DestroyedStatusType`
Available only in: *(GMX Zero Hour)*

- **Type**: `BodyDamageType` (see [BodyDamageType Values](#bodydamagetype-values))
- **Description**: Body damage state to set when the component is destroyed (0% - 10% health, which corresponds to downed status). Controls visual appearance of the object model. Set to one of the [BodyDamageType Values](#bodydamagetype-values) or leave empty/unset (0) for no visual change. The damage state is applied to the main object's body when component health falls within this range.
- **Default**: `0` (no change)
- **Example**: `DestroyedStatusType = REALLYDAMAGED` or `DestroyedStatusType = COMPONENT_ENGINE_DESTROYED`
- **Available Values**: see [BodyDamageType Values](#bodydamagetype-values)

### Status Icon Settings
Available only in: *(GMX Zero Hour)*

<a id="partiallyfunctionalicon"></a>
#### `PartiallyFunctionalIcon`
Available only in: *(GMX Zero Hour)*

- **Type**: `AsciiString` (see [Animation2d](../Animation2d.md))
- **Description**: Animation icon template name displayed in GUI when component is partially functional (10% - 50% health). References an animation template defined in [Animation2d](../Animation2d.md) configuration.
- **Default**: Empty (no icon)
- **Example**: `PartiallyFunctionalIcon = ComponentDamagedIcon`

<a id="downedicon"></a>
#### `DownedIcon`
Available only in: *(GMX Zero Hour)*

- **Type**: `AsciiString` (see [Animation2d](../Animation2d.md))
- **Description**: Animation icon template name displayed in GUI when component is downed (0% - 10% health). References an animation template defined in [Animation2d](../Animation2d.md) configuration.
- **Default**: Empty (no icon)
- **Example**: `DownedIcon = ComponentDestroyedIcon`

<a id="userdisabledicon"></a>
#### `UserDisabledIcon`
Available only in: *(GMX Zero Hour)*

- **Type**: `AsciiString` (see [Animation2d](../Animation2d.md))
- **Description**: Animation icon template name displayed in GUI when component is user-disabled. References an animation template defined in [Animation2d](../Animation2d.md) configuration.
- **Default**: Empty (no icon)
- **Example**: `UserDisabledIcon = ComponentDisabledIcon`

## Enum Value Lists

<a id="componenthealingtype-values"></a>
#### `ComponentHealingType` Values
Available only in: *(GMX Zero Hour)*

**Source:** [Component.h](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Components/Component.h#63) - `ComponentHealingType` enum definition

- **`NORMAL`** *(GMX Zero Hour)* - Can be healed from destroyed to max normally
- **`PARTIAL_ONLY`** *(GMX Zero Hour)* - Can be healed if not destroyed to max normally, but cannot be healed from destroyed state
- **`PARTIAL_DESTROYED`** *(GMX Zero Hour)* - Can be healed from destroyed to partially working (50% health) normally, but to max needs replacement
- **`PARTIAL_LIMITED`** *(GMX Zero Hour)* - Can be healed if not destroyed to partially working (50% health) normally, but to max needs replacement, and cannot be healed when destroyed
- **`REPLACEMENT_ONLY`** *(GMX Zero Hour)* - Cannot be healed normally, needs replacement via GUI command

<a id="hitside-values"></a>
#### `HitSide` Values
Available only in: *(GMX Zero Hour)*

**Source:** [Damage.h](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h#186) - `HitSide` enum definition; string names from `TheHitSideNames[]`

- **`HIT_SIDE_FRONT`** *(GMX Zero Hour)* - Front side of the object
- **`HIT_SIDE_BACK`** *(GMX Zero Hour)* - Back side of the object
- **`HIT_SIDE_LEFT`** *(GMX Zero Hour)* - Left side of the object
- **`HIT_SIDE_RIGHT`** *(GMX Zero Hour)* - Right side of the object
- **`HIT_SIDE_TOP`** *(GMX Zero Hour)* - Top side of the object
- **`HIT_SIDE_BOTTOM`** *(GMX Zero Hour)* - Bottom side of the object
- **`HIT_SIDE_UNKNOWN`** *(GMX Zero Hour)* - Used when hit side cannot be determined

<a id="bodydamagetype-values"></a>
#### `BodyDamageType` Values
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

**Source:** [BodyModule.h](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h#54) - `BodyDamageType` enum definition; string names from `TheBodyDamageTypeNames[]`

**Retail 1.04 Values** *(available in GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*:

- **`PRISTINE`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Unit should appear in pristine condition
- **`DAMAGED`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Unit has been damaged
- **`REALLYDAMAGED`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Unit is extremely damaged / nearly destroyed
- **`RUBBLE`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Unit has been reduced to rubble/corpse/exploded-hulk, etc

**GMX Component-Specific Values** *(available only in GMX Zero Hour)*:

- **`COMPONENT_ENGINE_DESTROYED`** *(GMX Zero Hour)* - Engine component has been destroyed
- **`COMPONENT_ENGINE_DAMAGED`** *(GMX Zero Hour)* - Engine component has been damaged
- **`COMPONENT_TURRET_DESTROYED`** *(GMX Zero Hour)* - Turret component has been destroyed
- **`COMPONENT_TURRET_DAMAGED`** *(GMX Zero Hour)* - Turret component has been damaged

- **`COMPONENT_WEAPON_A_DESTROYED`** *(GMX Zero Hour)* - Weapon slot A component has been destroyed
- **`COMPONENT_WEAPON_B_DESTROYED`** *(GMX Zero Hour)* - Weapon slot B component has been destroyed
- **`COMPONENT_WEAPON_C_DESTROYED`** *(GMX Zero Hour)* - Weapon slot C component has been destroyed
- **`COMPONENT_WEAPON_D_DESTROYED`** *(GMX Zero Hour)* - Weapon slot D component has been destroyed
- **`COMPONENT_WEAPON_E_DESTROYED`** *(GMX Zero Hour)* - Weapon slot E component has been destroyed
- **`COMPONENT_WEAPON_F_DESTROYED`** *(GMX Zero Hour)* - Weapon slot F component has been destroyed
- **`COMPONENT_WEAPON_G_DESTROYED`** *(GMX Zero Hour)* - Weapon slot G component has been destroyed
- **`COMPONENT_WEAPON_H_DESTROYED`** *(GMX Zero Hour)* - Weapon slot H component has been destroyed

- **`COMPONENT_WEAPON_A_DAMAGED`** *(GMX Zero Hour)* - Weapon slot A component has been damaged
- **`COMPONENT_WEAPON_B_DAMAGED`** *(GMX Zero Hour)* - Weapon slot B component has been damaged
- **`COMPONENT_WEAPON_C_DAMAGED`** *(GMX Zero Hour)* - Weapon slot C component has been damaged
- **`COMPONENT_WEAPON_D_DAMAGED`** *(GMX Zero Hour)* - Weapon slot D component has been damaged
- **`COMPONENT_WEAPON_E_DAMAGED`** *(GMX Zero Hour)* - Weapon slot E component has been damaged
- **`COMPONENT_WEAPON_F_DAMAGED`** *(GMX Zero Hour)* - Weapon slot F component has been damaged
- **`COMPONENT_WEAPON_G_DAMAGED`** *(GMX Zero Hour)* - Weapon slot G component has been damaged
- **`COMPONENT_WEAPON_H_DAMAGED`** *(GMX Zero Hour)* - Weapon slot H component has been damaged

- **`COMPONENT_A_DESTROYED`** *(GMX Zero Hour)* - Component A has been destroyed
- **`COMPONENT_B_DESTROYED`** *(GMX Zero Hour)* - Component B has been destroyed
- **`COMPONENT_C_DESTROYED`** *(GMX Zero Hour)* - Component C has been destroyed
- **`COMPONENT_D_DESTROYED`** *(GMX Zero Hour)* - Component D has been destroyed
- **`COMPONENT_E_DESTROYED`** *(GMX Zero Hour)* - Component E has been destroyed
- **`COMPONENT_F_DESTROYED`** *(GMX Zero Hour)* - Component F has been destroyed
- **`COMPONENT_G_DESTROYED`** *(GMX Zero Hour)* - Component G has been destroyed
- **`COMPONENT_H_DESTROYED`** *(GMX Zero Hour)* - Component H has been destroyed

- **`COMPONENT_A_DAMAGED`** *(GMX Zero Hour)* - Component A has been damaged
- **`COMPONENT_B_DAMAGED`** *(GMX Zero Hour)* - Component B has been damaged
- **`COMPONENT_C_DAMAGED`** *(GMX Zero Hour)* - Component C has been damaged
- **`COMPONENT_D_DAMAGED`** *(GMX Zero Hour)* - Component D has been damaged
- **`COMPONENT_E_DAMAGED`** *(GMX Zero Hour)* - Component E has been damaged
- **`COMPONENT_F_DAMAGED`** *(GMX Zero Hour)* - Component F has been damaged
- **`COMPONENT_G_DAMAGED`** *(GMX Zero Hour)* - Component G has been damaged
- **`COMPONENT_H_DAMAGED`** *(GMX Zero Hour)* - Component H has been damaged

## Examples

```ini
Component PRIMARY_WEAPON
  MaxHealth = 100.0
  InitialHealth = 100.0
  HealingType = NORMAL
  DamageOnSides = HIT_SIDE_FRONT HIT_SIDE_TOP
  ReplacementCost = 300
  ForceReturnOnDestroy = No
  DamagedStatusType = DAMAGED
  DestroyedStatusType = REALLYDAMAGED
End
```

```ini
Component MainEngine
  MaxHealth = 50%
  InitialHealth = 50%
  HealingType = PARTIAL_ONLY
  ReplacementCost = 500
  ForceReturnOnDestroy = Yes
  DamagedStatusType = COMPONENT_ENGINE_DAMAGED
  DestroyedStatusType = COMPONENT_ENGINE_DESTROYED
End
```

```ini
Component Turret
  MaxHealth = 80.0
  InitialHealth = 80.0
  HealingType = REPLACEMENT_ONLY
  DamageOnSides = HIT_SIDE_BACK HIT_SIDE_LEFT HIT_SIDE_RIGHT
  ReplacementCost = 400
  DamagedStatusType = COMPONENT_TURRET_DAMAGED
  DestroyedStatusType = COMPONENT_TURRET_DESTROYED
End
```

```ini
Component Radar
  MaxHealth = 25.0
  InitialHealth = 25.0
  HealingType = NORMAL
  ReplacementCost = 200
  PartiallyFunctionalIcon = RadarDamagedIcon
  DownedIcon = RadarDestroyedIcon
End
```

```ini
Component FuelTank
  MaxHealth = 60.0
  InitialHealth = 100.0
  HealingType = NORMAL
  ReplacementCost = 150
  ForceReturnOnDestroy = Yes
End
```

## Usage
Place under a body module (e.g., `Body = ActiveBody`, `Body = StructureBody`) to make components damageable, healable, replaceable, and usable in various gameplay systems. See Template for correct syntax.

Multiple component instances can be added to the same body. Each component operates independently with its own health tracking. Component names must be unique within the same body.

**Placement**:
- Components can only be added to `Body` entries. The following body modules support components: [ActiveBody](../ObjectModules/ActiveBody.md), [StructureBody](../ObjectModules/StructureBody.md), [UndeadBody](../ObjectModules/UndeadBody.md), [ImmortalBody](../ObjectModules/ImmortalBody.md), [HighlanderBody](../ObjectModules/HighlanderBody.md), [HiveStructureBody](../ObjectModules/HiveStructureBody.md).

**Limitations**:
- Requires one of the following body modules: [ActiveBody](../ObjectModules/ActiveBody.md), [StructureBody](../ObjectModules/StructureBody.md), [UndeadBody](../ObjectModules/UndeadBody.md), [ImmortalBody](../ObjectModules/ImmortalBody.md), [HighlanderBody](../ObjectModules/HighlanderBody.md), or [HiveStructureBody](../ObjectModules/HiveStructureBody.md); components cannot exist outside a body module block.
- Component names must be unique within the same body. If multiple components share the same name, systems that look up components by name (weapons via `PrimaryComponentDamage`/`SecondaryComponentDamage`, locomotor via `AffectedByComponents`/`EngineComponentName`, GUI commands, prerequisites) will only find the first matching component, causing unpredictable behavior where the wrong component may be targeted.
- Name is required for this type. If the name token is omitted/empty, the component is skipped during parsing and not added to the body.
- If [MaxHealth](#maxhealth) is 0 or negative, the component does not function and cannot be damaged, healed, or accessed by any systems.
- [InitialHealth](#initialhealth) is automatically clamped during component initialization: if it exceeds [MaxHealth](#maxhealth), it is set to [MaxHealth](#maxhealth); if negative, it is set to `0.0`. This clamping occurs when the object is created.

**Conditions**:
- To receive damage from weapons, the weapon must list this component by name in `PrimaryComponentDamage` or `SecondaryComponentDamage` (see [Weapon](../Weapon.md)). If not listed, weapons will not damage this component.
- For [AutoHealBehavior](../ObjectBehaviorsModules/AutoHealBehavior.md) to heal this component, the behavior must have `ComponentHealingAmount` set. Component healing respects this component's [HealingType](#healingtype) setting, which may restrict healing based on component health state.
- If this component's name is listed in `LocomotorTemplate.AffectedByComponents` (see [Locomotor](../Locomotor.md) documentation), component status (damaged/destroyed) can reduce movement capabilities (speed/turn/accel). If not listed, component status has no effect on movement.
- Component status (damaged/destroyed) affects object visual appearance via [DamagedStatusType](#damagedstatustype)/[DestroyedStatusType](#destroyedstatustype) settings, which control the body damage state displayed on the model. The damage state is determined based on component health ratio.
- Component status icons are displayed in the GUI health bar area when the component is damaged, destroyed, or user-disabled. Icons reference animation templates defined in [Animation2d](../Animation2d.md) configuration.
- If [ForceReturnOnDestroy](#forcereturnondestroy) is `Yes`, aircraft will automatically return to base when this component is destroyed (checked by [JetAIUpdate](../ObjectUpdates/JetAIUpdate.md)).
- Component status can be checked by the prerequisite system for command button availability (e.g., requiring component to exist, be working, or be disabled) (see `ObjectPrerequisite` in docs when available).
- Components can be replaced via command buttons using `COMMAND_REPLACE_COMPONENT` (see [CommandButton](../CommandButton.md)), or toggled on/off via a component toggle command, if configured. Replacement requires [ReplacementCost](#replacementcost) > 0.
- Components can be restored by [ParkingPlaceBehavior](../ObjectBehaviorsModules/ParkingPlaceBehavior.md) if the behavior's restore list includes this component's name, or by crate interactions that restore damaged components.

**Dependencies**:
- None. This component can function independently as a health-bearing part with replacement capabilities. All interactions with weapons, locomotor, healing systems, GUI commands, prerequisites, and behaviors are optional enhancements controlled by configuration, not hard requirements.

## Template

```ini
Component NAME
  MaxHealth = 0.0                 ; // maximum health (absolute or percentage with %) *(GMX Zero Hour)*
  InitialHealth = 0.0             ; // starting health (absolute or percentage with %) *(GMX Zero Hour)*
  MaxHealthValueType = ABSOLUTE   ; // how MaxHealth is calculated *(GMX Zero Hour)*
  InitialHealthValueType = ABSOLUTE ; // how InitialHealth is calculated *(GMX Zero Hour)*
  HealingType = NORMAL            ; // healing behavior type *(GMX Zero Hour)*
  DamageOnSides =                 ; // hit sides that can damage this component (HIT_SIDE_FRONT HIT_SIDE_BACK etc, empty = all sides) *(GMX Zero Hour)*
  ReplacementCost = 0             ; // cost to replace via GUI *(GMX Zero Hour)*
  ForceReturnOnDestroy = No       ; // force return to base when destroyed *(GMX Zero Hour)*
  DamagedStatusType =             ; // body damage state when damaged *(GMX Zero Hour)*
  DestroyedStatusType =           ; // body damage state when destroyed *(GMX Zero Hour)*
  PartiallyFunctionalIcon =       ; // icon template name for partially functional status *(GMX Zero Hour)*
  DownedIcon =                    ; // icon template name for downed status *(GMX Zero Hour)*
  UserDisabledIcon =              ; // icon template name for user disabled status *(GMX Zero Hour)*
End
```

## Notes
- Use descriptive component names (e.g., `Engine`, `PrimaryWeapon`, `Radar`, `FuelTank`).
- Combine with component-specific docs for specialized properties (e.g., `EngineComponent`, `WeaponComponent`, `SensorComponent`).
- Percentage health values are relative to the main object's [MaxHealth](#maxhealth) at initialization time.
- Component status icons are displayed in the GUI health bar area when components are damaged, destroyed, or disabled. Icons reference animation templates defined in [Animation2d](../Animation2d.md) configuration.
- [DamageOnSides](#damageonsides) allows side-specific armor for components — only hits from specified sides will damage the component. Use full hit side names with "HIT_SIDE_" prefix.
- Component status is determined by health percentage: fully functional (50% - 100%), partially functional (10% - 50%), or downed (0% - 10%).
- Component names must be unique within the same body to avoid lookup conflicts in systems that reference components by name.

## Modder Recommended Use Scenarios

(pending modder review)

## Source Files

**Base Class:** None (base class for all component types)

- Header: [Component.h](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Components/Component.h)
- Source: [Component.cpp](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Components/Component.cpp)

## Changes History

- 16/12/2025 — AI — Complete reconstruction based on updated instruction file with proper version flags, cross-usage research, and accurate property documentation.

## Status

- Documentation Status: AI-generated
- Last Updated: 16/12/2025 by AI
- Certification: 0/2 reviews

### Reviewers

- (pending)
