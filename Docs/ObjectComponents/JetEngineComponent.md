# JetEngineComponent *(GMX)*

Status: AI-generated, 0/2 reviews

## Overview
JetEngineComponent models jet engine subsystems attached via body modules. It supports movement performance penalties when damaged or destroyed, affecting locomotor speed, turn rate, acceleration, and lift for aircraft. JetEngineComponent inherits all properties from [EngineComponent](EngineComponent.md) (which includes all properties from [Component](Component.md)) and adds no additional properties. This is a module added inside `Object` entries.

Available only in: *(GMX Zero Hour)*

## Table of Contents
- [Overview](#overview)
- [Properties](#properties)
  - [Health Settings](#health-settings)
  - [Healing and Damage Settings](#healing-and-damage-settings)
  - [Replacement Settings](#replacement-settings)
  - [Visual Appearance Settings](#visual-appearance-settings)
  - [Status Icon Settings](#status-icon-settings)
  - [Movement Performance Settings](#movement-performance-settings)
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
- **Description**: Maximum health for this jet engine component. Higher values increase durability. Can be specified as absolute value (e.g., `100.0`) or percentage of main object's max health (e.g., `50%`). If percentage is used (contains `%` suffix), [MaxHealthValueType](#maxhealthvaluetype) is automatically set to `PERCENTAGE` during parsing. At initialization, percentage values are calculated as a percentage of the main object's max health.
- **Default**: `0.0`
- **Example**: `MaxHealth = 100.0` or `MaxHealth = 50%`

<a id="initialhealth"></a>
#### `InitialHealth`
Available only in: *(GMX Zero Hour)*

- **Type**: `Real` (can include `%` suffix for percentage of main object health)
- **Description**: Starting health for this jet engine component when the object is created. Can be specified as absolute value or percentage of main object's max health. If percentage is used (contains `%` suffix), [InitialHealthValueType](#initialhealthvaluetype) is automatically set to `PERCENTAGE` during parsing. At initialization, percentage values are calculated as a percentage of the main object's max health. Automatically clamped to [MaxHealth](#maxhealth) and `0.0` during component initialization when the object is created.
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
- **Description**: Controls how the jet engine component can be healed. Different types restrict healing to specific health ranges or require replacement for full healing. `NORMAL` allows full healing from destroyed to max. `PARTIAL_ONLY` prevents healing when destroyed. `PARTIAL_DESTROYED` allows healing from destroyed only to partially working (50%). `PARTIAL_LIMITED` allows healing only to partially working (50%) when not destroyed, and prevents healing when destroyed. `REPLACEMENT_ONLY` prevents all normal healing and requires GUI replacement.
- **Default**: `NORMAL`
- **Example**: `HealingType = NORMAL`
- **Available Values**: see [ComponentHealingType Values](#componenthealingtype-values)

<a id="damageonsides"></a>
#### `DamageOnSides`
Available only in: *(GMX Zero Hour)*

- **Type**: `HitSideFlags` (list of [HitSide Values](#hitside-values))
- **Description**: Which hit sides can damage this jet engine component. If empty, all sides can damage the component. If specified, only listed sides can cause damage. Used for side-specific armor on components. Parsed using full hit side names with "HIT_SIDE_" prefix: `HIT_SIDE_FRONT`, `HIT_SIDE_BACK`, `HIT_SIDE_LEFT`, `HIT_SIDE_RIGHT`, `HIT_SIDE_TOP`, `HIT_SIDE_BOTTOM`. Note: `HIT_SIDE_UNKNOWN` exists in the enum but is not parseable for this property.
- **Default**: Empty (all sides)
- **Example**: `DamageOnSides = HIT_SIDE_BACK` or `DamageOnSides = HIT_SIDE_LEFT HIT_SIDE_RIGHT`
- **Available Values**: `HIT_SIDE_FRONT`, `HIT_SIDE_BACK`, `HIT_SIDE_LEFT`, `HIT_SIDE_RIGHT`, `HIT_SIDE_TOP`, `HIT_SIDE_BOTTOM` (see [HitSide Values](#hitside-values) for full enum list)

### Replacement Settings
Available only in: *(GMX Zero Hour)*

<a id="replacementcost"></a>
#### `ReplacementCost`
Available only in: *(GMX Zero Hour)*

- **Type**: `UnsignedInt`
- **Description**: Money cost to fully replace this jet engine component via GUI command system. At 0 (default), the component cannot be replaced via GUI commands. Replacement fully restores component health to maximum.
- **Default**: `0`
- **Example**: `ReplacementCost = 400`

<a id="forcereturnondestroy"></a>
#### `ForceReturnOnDestroy`
Available only in: *(GMX Zero Hour)*

- **Type**: `Bool`
- **Description**: Whether the unit should be forced to return to base when this jet engine component is destroyed. When `Yes`, aircraft will automatically return to base when this component is destroyed (checked by [JetAIUpdate](../ObjectUpdates/JetAIUpdate.md)). When `No`, component destruction does not trigger return behavior. Typically set to `Yes` for jet engines to force return when engine is destroyed.
- **Default**: `No`
- **Example**: `ForceReturnOnDestroy = Yes`

### Visual Appearance Settings
Available only in: *(GMX Zero Hour)*

<a id="damagedstatustype"></a>
#### `DamagedStatusType`
Available only in: *(GMX Zero Hour)*

- **Type**: `BodyDamageType` (see [BodyDamageType Values](#bodydamagetype-values))
- **Description**: Body damage state to set when the jet engine component is damaged (10% - 50% health, which corresponds to partially functional status). Controls visual appearance of the object model. Set to one of the [BodyDamageType Values](#bodydamagetype-values) or leave empty/unset (0) for no visual change. The damage state is applied to the main object's body when component health falls within this range. If not set, defaults to `COMPONENT_ENGINE_DAMAGED` (set in constructor).
- **Default**: `COMPONENT_ENGINE_DAMAGED`
- **Example**: `DamagedStatusType = DAMAGED` or `DamagedStatusType = COMPONENT_ENGINE_DAMAGED`
- **Available Values**: see [BodyDamageType Values](#bodydamagetype-values)

<a id="destroyedstatustype"></a>
#### `DestroyedStatusType`
Available only in: *(GMX Zero Hour)*

- **Type**: `BodyDamageType` (see [BodyDamageType Values](#bodydamagetype-values))
- **Description**: Body damage state to set when the jet engine component is destroyed (0% - 10% health, which corresponds to downed status). Controls visual appearance of the object model. Set to one of the [BodyDamageType Values](#bodydamagetype-values) or leave empty/unset (0) for no visual change. The damage state is applied to the main object's body when component health falls within this range. If not set, defaults to `COMPONENT_ENGINE_DESTROYED` (set in constructor).
- **Default**: `COMPONENT_ENGINE_DESTROYED`
- **Example**: `DestroyedStatusType = REALLYDAMAGED` or `DestroyedStatusType = COMPONENT_ENGINE_DESTROYED`
- **Available Values**: see [BodyDamageType Values](#bodydamagetype-values)

### Status Icon Settings
Available only in: *(GMX Zero Hour)*

<a id="partiallyfunctionalicon"></a>
#### `PartiallyFunctionalIcon`
Available only in: *(GMX Zero Hour)*

- **Type**: `AsciiString` (see [Animation2d](../Animation2d.md))
- **Description**: Animation icon template name displayed in GUI when jet engine component is partially functional (10% - 50% health). References an animation template defined in [Animation2d](../Animation2d.md) configuration.
- **Default**: Empty (no icon)
- **Example**: `PartiallyFunctionalIcon = JetEngineDamagedIcon`

<a id="downedicon"></a>
#### `DownedIcon`
Available only in: *(GMX Zero Hour)*

- **Type**: `AsciiString` (see [Animation2d](../Animation2d.md))
- **Description**: Animation icon template name displayed in GUI when jet engine component is downed (0% - 10% health). References an animation template defined in [Animation2d](../Animation2d.md) configuration.
- **Default**: Empty (no icon)
- **Example**: `DownedIcon = JetEngineDestroyedIcon`

<a id="userdisabledicon"></a>
#### `UserDisabledIcon`
Available only in: *(GMX Zero Hour)*

- **Type**: `AsciiString` (see [Animation2d](../Animation2d.md))
- **Description**: Animation icon template name displayed in GUI when jet engine component is user-disabled. References an animation template defined in [Animation2d](../Animation2d.md) configuration.
- **Default**: Empty (no icon)
- **Example**: `UserDisabledIcon = JetEngineDisabledIcon`

### Movement Performance Settings
Available only in: *(GMX Zero Hour)*

These properties control how the jet engine component affects movement when damaged or destroyed. When the locomotor references this component via `EngineComponentName` (see [Locomotor](../Locomotor.md) documentation), these values are used to adjust movement performance based on component status.

<a id="maxspeeddamaged"></a>
#### `MaxSpeedDamaged`
Available only in: *(GMX Zero Hour)*

- **Type**: `Real` (can include `%` suffix for percentage of locomotor speed)
- **Description**: Maximum speed when the jet engine component is damaged (10% - 50% health, partially functional status). Can be specified as absolute value (e.g., `50.0`) or percentage of locomotor's `MaxSpeedDamaged` (e.g., `80%`). If percentage is used (contains `%` suffix), [MaxSpeedDamagedValueType](#maxspeeddamagedvaluetype) is automatically set to `PERCENTAGE` during parsing. If not set, the locomotor uses its own `MaxSpeedDamaged` value. This property is optional - if omitted, the locomotor's default damaged speed is used.
- **Default**: `0.0` (not set, uses locomotor default)
- **Example**: `MaxSpeedDamaged = 50.0` or `MaxSpeedDamaged = 80%`

<a id="maxspeeddamagedvaluetype"></a>
#### `MaxSpeedDamagedValueType`
Available only in: *(GMX Zero Hour)*

- **Type**: `ValueType` (see ValueType documentation)
- **Description**: How [MaxSpeedDamaged](#maxspeeddamaged) is calculated — `ABSOLUTE` for fixed values or `PERCENTAGE` for percentage of locomotor's `MaxSpeedDamaged`. Automatically set when [MaxSpeedDamaged](#maxspeeddamaged) includes `%` suffix during parsing. If not explicitly set and [MaxSpeedDamaged](#maxspeeddamaged) has no `%` suffix, defaults to `ABSOLUTE`.
- **Default**: `ABSOLUTE`
- **Example**: `MaxSpeedDamagedValueType = PERCENTAGE`

<a id="maxturnratedamaged"></a>
#### `MaxTurnRateDamaged`
Available only in: *(GMX Zero Hour)*

- **Type**: `Real` (can include `%` suffix for percentage of locomotor turn rate)
- **Description**: Maximum turn rate when the jet engine component is damaged (10% - 50% health, partially functional status). Can be specified as absolute value (e.g., `90.0`) or percentage of locomotor's `MaxTurnRateDamaged` (e.g., `75%`). If percentage is used (contains `%` suffix), [MaxTurnRateDamagedValueType](#maxturnratedamagedvaluetype) is automatically set to `PERCENTAGE` during parsing. If not set, the locomotor uses its own `MaxTurnRateDamaged` value. This property is optional - if omitted, the locomotor's default damaged turn rate is used.
- **Default**: `0.0` (not set, uses locomotor default)
- **Example**: `MaxTurnRateDamaged = 90.0` or `MaxTurnRateDamaged = 75%`

<a id="maxturnratedamagedvaluetype"></a>
#### `MaxTurnRateDamagedValueType`
Available only in: *(GMX Zero Hour)*

- **Type**: `ValueType` (see ValueType documentation)
- **Description**: How [MaxTurnRateDamaged](#maxturnratedamaged) is calculated — `ABSOLUTE` for fixed values or `PERCENTAGE` for percentage of locomotor's `MaxTurnRateDamaged`. Automatically set when [MaxTurnRateDamaged](#maxturnratedamaged) includes `%` suffix during parsing. If not explicitly set and [MaxTurnRateDamaged](#maxturnratedamaged) has no `%` suffix, defaults to `ABSOLUTE`.
- **Default**: `ABSOLUTE`
- **Example**: `MaxTurnRateDamagedValueType = PERCENTAGE`

<a id="maxaccelerationdamaged"></a>
#### `MaxAccelerationDamaged`
Available only in: *(GMX Zero Hour)*

- **Type**: `Real` (can include `%` suffix for percentage of locomotor acceleration)
- **Description**: Maximum acceleration when the jet engine component is damaged (10% - 50% health, partially functional status). Can be specified as absolute value (e.g., `0.5`) or percentage of locomotor's `AccelerationDamaged` (e.g., `60%`). If percentage is used (contains `%` suffix), [MaxAccelerationDamagedValueType](#maxaccelerationdamagedvaluetype) is automatically set to `PERCENTAGE` during parsing. If not set, the locomotor uses its own `AccelerationDamaged` value. This property is optional - if omitted, the locomotor's default damaged acceleration is used.
- **Default**: `0.0` (not set, uses locomotor default)
- **Example**: `MaxAccelerationDamaged = 0.5` or `MaxAccelerationDamaged = 60%`

<a id="maxaccelerationdamagedvaluetype"></a>
#### `MaxAccelerationDamagedValueType`
Available only in: *(GMX Zero Hour)*

- **Type**: `ValueType` (see ValueType documentation)
- **Description**: How [MaxAccelerationDamaged](#maxaccelerationdamaged) is calculated — `ABSOLUTE` for fixed values or `PERCENTAGE` for percentage of locomotor's `AccelerationDamaged`. Automatically set when [MaxAccelerationDamaged](#maxaccelerationdamaged) includes `%` suffix during parsing. If not explicitly set and [MaxAccelerationDamaged](#maxaccelerationdamaged) has no `%` suffix, defaults to `ABSOLUTE`.
- **Default**: `ABSOLUTE`
- **Example**: `MaxAccelerationDamagedValueType = PERCENTAGE`

<a id="maxliftdamaged"></a>
#### `MaxLiftDamaged`
Available only in: *(GMX Zero Hour)*

- **Type**: `Real` (can include `%` suffix for percentage of locomotor lift)
- **Description**: Maximum lift when the jet engine component is damaged (10% - 50% health, partially functional status). Can be specified as absolute value (e.g., `0.3`) or percentage of locomotor's `LiftDamaged` (e.g., `70%`). If percentage is used (contains `%` suffix), [MaxLiftDamagedValueType](#maxliftdamagedvaluetype) is automatically set to `PERCENTAGE` during parsing. If not set, the locomotor uses its own `LiftDamaged` value. This property is optional - if omitted, the locomotor's default damaged lift is used. Only applicable for aircraft locomotor types.
- **Default**: `0.0` (not set, uses locomotor default)
- **Example**: `MaxLiftDamaged = 0.3` or `MaxLiftDamaged = 70%`

<a id="maxliftdamagedvaluetype"></a>
#### `MaxLiftDamagedValueType`
Available only in: *(GMX Zero Hour)*

- **Type**: `ValueType` (see ValueType documentation)
- **Description**: How [MaxLiftDamaged](#maxliftdamaged) is calculated — `ABSOLUTE` for fixed values or `PERCENTAGE` for percentage of locomotor's `LiftDamaged`. Automatically set when [MaxLiftDamaged](#maxliftdamaged) includes `%` suffix during parsing. If not explicitly set and [MaxLiftDamaged](#maxliftdamaged) has no `%` suffix, defaults to `ABSOLUTE`.
- **Default**: `ABSOLUTE`
- **Example**: `MaxLiftDamagedValueType = PERCENTAGE`

<a id="maxspeeddestroyed"></a>
#### `MaxSpeedDestroyed`
Available only in: *(GMX Zero Hour)*

- **Type**: `Real` (can include `%` suffix for percentage of locomotor speed)
- **Description**: Maximum speed when the jet engine component is destroyed (0% - 10% health, downed status). Can be specified as absolute value (e.g., `10.0`) or percentage of locomotor's `MaxSpeed` (e.g., `20%`). If percentage is used (contains `%` suffix), [MaxSpeedDestroyedValueType](#maxspeeddestroyedvaluetype) is automatically set to `PERCENTAGE` during parsing. When the engine is destroyed, movement speed is reduced to this value. This property is required for jet engine components that affect movement.
- **Default**: `0.0`
- **Example**: `MaxSpeedDestroyed = 10.0` or `MaxSpeedDestroyed = 20%`

<a id="maxspeeddestroyedvaluetype"></a>
#### `MaxSpeedDestroyedValueType`
Available only in: *(GMX Zero Hour)*

- **Type**: `ValueType` (see ValueType documentation)
- **Description**: How [MaxSpeedDestroyed](#maxspeeddestroyed) is calculated — `ABSOLUTE` for fixed values or `PERCENTAGE` for percentage of locomotor's `MaxSpeed`. Automatically set when [MaxSpeedDestroyed](#maxspeeddestroyed) includes `%` suffix during parsing. If not explicitly set and [MaxSpeedDestroyed](#maxspeeddestroyed) has no `%` suffix, defaults to `ABSOLUTE`.
- **Default**: `ABSOLUTE`
- **Example**: `MaxSpeedDestroyedValueType = PERCENTAGE`

<a id="maxturnratedestroyed"></a>
#### `MaxTurnRateDestroyed`
Available only in: *(GMX Zero Hour)*

- **Type**: `Real` (can include `%` suffix for percentage of locomotor turn rate)
- **Description**: Maximum turn rate when the jet engine component is destroyed (0% - 10% health, downed status). Can be specified as absolute value (e.g., `30.0`) or percentage of locomotor's `MaxTurnRate` (e.g., `25%`). If percentage is used (contains `%` suffix), [MaxTurnRateDestroyedValueType](#maxturnratedestroyedvaluetype) is automatically set to `PERCENTAGE` during parsing. When the engine is destroyed, turn rate is reduced to this value. This property is required for jet engine components that affect movement.
- **Default**: `0.0`
- **Example**: `MaxTurnRateDestroyed = 30.0` or `MaxTurnRateDestroyed = 25%`

<a id="maxturnratedestroyedvaluetype"></a>
#### `MaxTurnRateDestroyedValueType`
Available only in: *(GMX Zero Hour)*

- **Type**: `ValueType` (see ValueType documentation)
- **Description**: How [MaxTurnRateDestroyed](#maxturnratedestroyed) is calculated — `ABSOLUTE` for fixed values or `PERCENTAGE` for percentage of locomotor's `MaxTurnRate`. Automatically set when [MaxTurnRateDestroyed](#maxturnratedestroyed) includes `%` suffix during parsing. If not explicitly set and [MaxTurnRateDestroyed](#maxturnratedestroyed) has no `%` suffix, defaults to `ABSOLUTE`.
- **Default**: `ABSOLUTE`
- **Example**: `MaxTurnRateDestroyedValueType = PERCENTAGE`

<a id="maxaccelerationdestroyed"></a>
#### `MaxAccelerationDestroyed`
Available only in: *(GMX Zero Hour)*

- **Type**: `Real` (can include `%` suffix for percentage of locomotor acceleration)
- **Description**: Maximum acceleration when the jet engine component is destroyed (0% - 10% health, downed status). Can be specified as absolute value (e.g., `0.1`) or percentage of locomotor's `Acceleration` (e.g., `15%`). If percentage is used (contains `%` suffix), [MaxAccelerationDestroyedValueType](#maxaccelerationdestroyedvaluetype) is automatically set to `PERCENTAGE` during parsing. When the engine is destroyed, acceleration is reduced to this value. This property is required for jet engine components that affect movement.
- **Default**: `0.0`
- **Example**: `MaxAccelerationDestroyed = 0.1` or `MaxAccelerationDestroyed = 15%`

<a id="maxaccelerationdestroyedvaluetype"></a>
#### `MaxAccelerationDestroyedValueType`
Available only in: *(GMX Zero Hour)*

- **Type**: `ValueType` (see ValueType documentation)
- **Description**: How [MaxAccelerationDestroyed](#maxaccelerationdestroyed) is calculated — `ABSOLUTE` for fixed values or `PERCENTAGE` for percentage of locomotor's `Acceleration`. Automatically set when [MaxAccelerationDestroyed](#maxaccelerationdestroyed) includes `%` suffix during parsing. If not explicitly set and [MaxAccelerationDestroyed](#maxaccelerationdestroyed) has no `%` suffix, defaults to `ABSOLUTE`.
- **Default**: `ABSOLUTE`
- **Example**: `MaxAccelerationDestroyedValueType = PERCENTAGE`

<a id="maxliftdestroyed"></a>
#### `MaxLiftDestroyed`
Available only in: *(GMX Zero Hour)*

- **Type**: `Real` (can include `%` suffix for percentage of locomotor lift)
- **Description**: Maximum lift when the jet engine component is destroyed (0% - 10% health, downed status). Can be specified as absolute value (e.g., `0.05`) or percentage of locomotor's `Lift` (e.g., `10%`). If percentage is used (contains `%` suffix), [MaxLiftDestroyedValueType](#maxliftdestroyedvaluetype) is automatically set to `PERCENTAGE` during parsing. When the engine is destroyed, lift is reduced to this value. This property is required for jet engine components that affect movement. Only applicable for aircraft locomotor types.
- **Default**: `0.0`
- **Example**: `MaxLiftDestroyed = 0.05` or `MaxLiftDestroyed = 10%`

<a id="maxliftdestroyedvaluetype"></a>
#### `MaxLiftDestroyedValueType`
Available only in: *(GMX Zero Hour)*

- **Type**: `ValueType` (see ValueType documentation)
- **Description**: How [MaxLiftDestroyed](#maxliftdestroyed) is calculated — `ABSOLUTE` for fixed values or `PERCENTAGE` for percentage of locomotor's `Lift`. Automatically set when [MaxLiftDestroyed](#maxliftdestroyed) includes `%` suffix during parsing. If not explicitly set and [MaxLiftDestroyed](#maxliftdestroyed) has no `%` suffix, defaults to `ABSOLUTE`.
- **Default**: `ABSOLUTE`
- **Example**: `MaxLiftDestroyedValueType = PERCENTAGE`

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
JetEngineComponent
  MaxHealth = 100.0
  InitialHealth = 100.0
  HealingType = NORMAL
  ReplacementCost = 400
  ForceReturnOnDestroy = Yes
  MaxSpeedDestroyed = 10.0
  MaxTurnRateDestroyed = 30.0
  MaxAccelerationDestroyed = 0.1
  MaxLiftDestroyed = 0.05
End
```

```ini
JetEngineComponent MainEngine
  MaxHealth = 120.0
  InitialHealth = 120.0
  HealingType = PARTIAL_ONLY
  DamageOnSides = HIT_SIDE_BACK
  ReplacementCost = 500
  ForceReturnOnDestroy = Yes
  MaxSpeedDamaged = 80%
  MaxTurnRateDamaged = 75%
  MaxAccelerationDamaged = 70%
  MaxLiftDamaged = 75%
  MaxSpeedDestroyed = 15%
  MaxTurnRateDestroyed = 25%
  MaxAccelerationDestroyed = 20%
  MaxLiftDestroyed = 10%
End
```

```ini
JetEngineComponent LeftEngine
  MaxHealth = 100.0
  InitialHealth = 100.0
  HealingType = NORMAL
  ReplacementCost = 400
  ForceReturnOnDestroy = Yes
  PartiallyFunctionalIcon = EngineDamagedIcon
  DownedIcon = EngineDestroyedIcon
  MaxSpeedDamaged = 60.0
  MaxSpeedDamagedValueType = ABSOLUTE
  MaxTurnRateDamaged = 90.0
  MaxAccelerationDamaged = 0.5
  MaxLiftDamaged = 0.3
  MaxSpeedDestroyed = 15.0
  MaxTurnRateDestroyed = 45.0
  MaxAccelerationDestroyed = 0.2
  MaxLiftDestroyed = 0.1
End
```

```ini
JetEngineComponent JetEngine
  MaxHealth = 50%
  InitialHealth = 50%
  HealingType = REPLACEMENT_ONLY
  ReplacementCost = 600
  ForceReturnOnDestroy = Yes
  MaxSpeedDamaged = 70%
  MaxTurnRateDamaged = 80%
  MaxAccelerationDamaged = 65%
  MaxLiftDamaged = 70%
  MaxSpeedDestroyed = 10%
  MaxTurnRateDestroyed = 20%
  MaxAccelerationDestroyed = 10%
  MaxLiftDestroyed = 10%
End
```

```ini
JetEngineComponent PrimaryJet
  MaxHealth = 150.0
  InitialHealth = 150.0
  HealingType = NORMAL
  DamageOnSides = HIT_SIDE_BACK HIT_SIDE_LEFT HIT_SIDE_RIGHT
  ReplacementCost = 800
  ForceReturnOnDestroy = Yes
  DamagedStatusType = COMPONENT_ENGINE_DAMAGED
  DestroyedStatusType = COMPONENT_ENGINE_DESTROYED
  PartiallyFunctionalIcon = JetEngineDamagedIcon
  DownedIcon = JetEngineDestroyedIcon
  UserDisabledIcon = JetEngineDisabledIcon
  MaxSpeedDestroyed = 5.0
  MaxTurnRateDestroyed = 20.0
  MaxAccelerationDestroyed = 0.05
  MaxLiftDestroyed = 0.05
End
```

## Usage
Place under a body module (e.g., `Body = ActiveBody`, `Body = StructureBody`) to make jet engine systems damageable, healable, replaceable, and affect movement performance for aircraft. See Template for correct syntax.

Multiple component instances can be added to the same body. Each component operates independently with its own health tracking and movement performance effects. Component names must be unique within the same body.

**Placement**:
- Components can only be added to `Body` entries. The following body modules support components: [ActiveBody](../ObjectModules/ActiveBody.md), [StructureBody](../ObjectModules/StructureBody.md), [UndeadBody](../ObjectModules/UndeadBody.md), [ImmortalBody](../ObjectModules/ImmortalBody.md), [HighlanderBody](../ObjectModules/HighlanderBody.md), [HiveStructureBody](../ObjectModules/HiveStructureBody.md).

**Limitations**:
- Requires one of the following body modules: [ActiveBody](../ObjectModules/ActiveBody.md), [StructureBody](../ObjectModules/StructureBody.md), [UndeadBody](../ObjectModules/UndeadBody.md), [ImmortalBody](../ObjectModules/ImmortalBody.md), [HighlanderBody](../ObjectModules/HighlanderBody.md), or [HiveStructureBody](../ObjectModules/HiveStructureBody.md); components cannot exist outside a body module block.
- Component names must be unique within the same body. If multiple components share the same name, systems that look up components by name (weapons via `PrimaryComponentDamage`/`SecondaryComponentDamage`, locomotor via `AffectedByComponents`/`EngineComponentName`, GUI commands, prerequisites) will only find the first matching component, causing unpredictable behavior where the wrong component may be targeted.
- Name is optional for this type. If the name token is omitted/empty, a default name of `MainEngine` is automatically assigned. If a name is explicitly provided, it must be unique within the same body.
- If [MaxHealth](#maxhealth) is 0 or negative, the component does not function and cannot be damaged, healed, or accessed by any systems.
- [InitialHealth](#initialhealth) is automatically clamped during component initialization: if it exceeds [MaxHealth](#maxhealth), it is set to [MaxHealth](#maxhealth); if negative, it is set to `0.0`. This clamping occurs when the object is created.
- Movement performance properties ([MaxSpeedDestroyed](#maxspeeddestroyed), [MaxTurnRateDestroyed](#maxturnratedestroyed), [MaxAccelerationDestroyed](#maxaccelerationdestroyed), [MaxLiftDestroyed](#maxliftdestroyed)) must be set for the jet engine component to affect movement when destroyed. If not set, destroyed jet engine components do not affect movement performance.
- Movement performance properties for damaged state ([MaxSpeedDamaged](#maxspeeddamaged), [MaxTurnRateDamaged](#maxturnratedamaged), [MaxAccelerationDamaged](#maxaccelerationdamaged), [MaxLiftDamaged](#maxliftdamaged)) are optional - if not set, the locomotor uses its own default damaged performance values.

**Conditions**:
- To receive damage from weapons, the weapon must list this component by name in `PrimaryComponentDamage` or `SecondaryComponentDamage` (see [Weapon](../Weapon.md)). If not listed, weapons will not damage this component.
- For [AutoHealBehavior](../ObjectBehaviorsModules/AutoHealBehavior.md) to heal this component, the behavior must have `ComponentHealingAmount` set. Component healing respects this component's [HealingType](#healingtype) setting, which may restrict healing based on component health state.
- If this component's name is listed in `LocomotorTemplate.AffectedByComponents` (see [Locomotor](../Locomotor.md) documentation), component status (damaged/destroyed) can reduce movement capabilities (speed/turn/accel). If not listed, component status has no effect on movement.
- If this component's name is set as `LocomotorTemplate.EngineComponentName` (see [Locomotor](../Locomotor.md) documentation), the locomotor will check this component's status and use the component's movement performance properties ([MaxSpeedDamaged](#maxspeeddamaged), [MaxSpeedDestroyed](#maxspeeddestroyed), etc.) to adjust movement capabilities. If `EngineComponentName` is empty, the locomotor defaults to looking for a component named `MainEngine`. If the component is not found, movement performance is not affected.
- When the jet engine component is damaged (10% - 50% health), the locomotor uses [MaxSpeedDamaged](#maxspeeddamaged), [MaxTurnRateDamaged](#maxturnratedamaged), [MaxAccelerationDamaged](#maxaccelerationdamaged), and [MaxLiftDamaged](#maxliftdamaged) if set. If not set, the locomotor uses its own default damaged performance values.
- When the jet engine component is destroyed (0% - 10% health) or user-disabled, the locomotor uses [MaxSpeedDestroyed](#maxspeeddestroyed), [MaxTurnRateDestroyed](#maxturnratedestroyed), [MaxAccelerationDestroyed](#maxaccelerationdestroyed), and [MaxLiftDestroyed](#maxliftdestroyed). These values must be set for the jet engine component to affect movement when destroyed.
- Component status (damaged/destroyed) affects object visual appearance via [DamagedStatusType](#damagedstatustype)/[DestroyedStatusType](#destroyedstatustype) settings, which control the body damage state displayed on the model. The damage state is determined based on component health ratio. By default, [DamagedStatusType](#damagedstatustype) is set to `COMPONENT_ENGINE_DAMAGED` and [DestroyedStatusType](#destroyedstatustype) is set to `COMPONENT_ENGINE_DESTROYED` (set in constructor).
- Component status icons are displayed in the GUI health bar area when the component is damaged, destroyed, or user-disabled. Icons reference animation templates defined in [Animation2d](../Animation2d.md) configuration.
- If [ForceReturnOnDestroy](#forcereturnondestroy) is `Yes`, aircraft will automatically return to base when this component is destroyed (checked by [JetAIUpdate](../ObjectUpdates/JetAIUpdate.md)). This is typically set to `Yes` for jet engines to force return when engine is destroyed.
- Component status can be checked by the prerequisite system for command button availability (e.g., requiring component to exist, be working, or be disabled) (see `ObjectPrerequisite` in docs when available).
- Components can be replaced via command buttons using `COMMAND_REPLACE_COMPONENT` (see [CommandButton](../CommandButton.md)), or toggled on/off via a component toggle command, if configured. Replacement requires [ReplacementCost](#replacementcost) > 0.
- Components can be restored by [ParkingPlaceBehavior](../ObjectBehaviorsModules/ParkingPlaceBehavior.md) if the behavior's restore list includes this component's name, or by crate interactions that restore damaged components.
- For aircraft, the locomotor checks if the jet engine component is destroyed or user-disabled before allowing takeoff (see `LocomotorTemplate.canTakeoff`). If the engine is destroyed or disabled, the aircraft cannot take off.

**Dependencies**:
- None. This component can function independently as a health-bearing part with replacement capabilities and movement performance effects. All interactions with weapons, locomotor, healing systems, GUI commands, prerequisites, and behaviors are optional enhancements controlled by configuration, not hard requirements. However, for the jet engine component to affect movement performance, the locomotor must reference this component via `LocomotorTemplate.EngineComponentName` (see [Locomotor](../Locomotor.md) documentation).

## Template

```ini
JetEngineComponent NAME
  MaxHealth = 0.0                 ; // maximum health (absolute or percentage with %) *(GMX Zero Hour)*
  InitialHealth = 0.0             ; // starting health (absolute or percentage with %) *(GMX Zero Hour)*
  MaxHealthValueType = ABSOLUTE   ; // how MaxHealth is calculated *(GMX Zero Hour)*
  InitialHealthValueType = ABSOLUTE ; // how InitialHealth is calculated *(GMX Zero Hour)*
  HealingType = NORMAL            ; // healing behavior type *(GMX Zero Hour)*
  DamageOnSides =                 ; // hit sides that can damage this component (HIT_SIDE_FRONT HIT_SIDE_BACK etc, empty = all sides) *(GMX Zero Hour)*
  ReplacementCost = 0             ; // cost to replace via GUI *(GMX Zero Hour)*
  ForceReturnOnDestroy = No       ; // force return to base when destroyed *(GMX Zero Hour)*
  DamagedStatusType =             ; // body damage state when damaged (defaults to COMPONENT_ENGINE_DAMAGED) *(GMX Zero Hour)*
  DestroyedStatusType =           ; // body damage state when destroyed (defaults to COMPONENT_ENGINE_DESTROYED) *(GMX Zero Hour)*
  PartiallyFunctionalIcon =       ; // icon template name for partially functional status *(GMX Zero Hour)*
  DownedIcon =                    ; // icon template name for downed status *(GMX Zero Hour)*
  UserDisabledIcon =              ; // icon template name for user disabled status *(GMX Zero Hour)*
  MaxSpeedDamaged = 0.0           ; // max speed when damaged (absolute or percentage with %, optional) *(GMX Zero Hour)*
  MaxSpeedDamagedValueType = ABSOLUTE ; // how MaxSpeedDamaged is calculated *(GMX Zero Hour)*
  MaxTurnRateDamaged = 0.0        ; // max turn rate when damaged (absolute or percentage with %, optional) *(GMX Zero Hour)*
  MaxTurnRateDamagedValueType = ABSOLUTE ; // how MaxTurnRateDamaged is calculated *(GMX Zero Hour)*
  MaxAccelerationDamaged = 0.0    ; // max acceleration when damaged (absolute or percentage with %, optional) *(GMX Zero Hour)*
  MaxAccelerationDamagedValueType = ABSOLUTE ; // how MaxAccelerationDamaged is calculated *(GMX Zero Hour)*
  MaxLiftDamaged = 0.0            ; // max lift when damaged (absolute or percentage with %, optional, aircraft only) *(GMX Zero Hour)*
  MaxLiftDamagedValueType = ABSOLUTE ; // how MaxLiftDamaged is calculated *(GMX Zero Hour)*
  MaxSpeedDestroyed = 0.0         ; // max speed when destroyed (absolute or percentage with %) *(GMX Zero Hour)*
  MaxSpeedDestroyedValueType = ABSOLUTE ; // how MaxSpeedDestroyed is calculated *(GMX Zero Hour)*
  MaxTurnRateDestroyed = 0.0      ; // max turn rate when destroyed (absolute or percentage with %) *(GMX Zero Hour)*
  MaxTurnRateDestroyedValueType = ABSOLUTE ; // how MaxTurnRateDestroyed is calculated *(GMX Zero Hour)*
  MaxAccelerationDestroyed = 0.0  ; // max acceleration when destroyed (absolute or percentage with %) *(GMX Zero Hour)*
  MaxAccelerationDestroyedValueType = ABSOLUTE ; // how MaxAccelerationDestroyed is calculated *(GMX Zero Hour)*
  MaxLiftDestroyed = 0.0          ; // max lift when destroyed (absolute or percentage with %, aircraft only) *(GMX Zero Hour)*
  MaxLiftDestroyedValueType = ABSOLUTE ; // how MaxLiftDestroyed is calculated *(GMX Zero Hour)*
End
```

**Note**: If `NAME` is omitted, the component is automatically assigned the default name `MainEngine`.

## Notes
- Jet engine components are specialized engine components for aircraft propulsion systems that affect movement performance when damaged or destroyed.
- Movement performance properties use percentage values relative to the locomotor's base performance values. For example, `MaxSpeedDestroyed = 20%` means the aircraft moves at 20% of the locomotor's `MaxSpeed` when the engine is destroyed.
- The damaged performance properties ([MaxSpeedDamaged](#maxspeeddamaged), etc.) are optional - if not set, the locomotor uses its own default damaged performance values (`LocomotorTemplate.MaxSpeedDamaged`, etc.).
- The destroyed performance properties ([MaxSpeedDestroyed](#maxspeeddestroyed), etc.) are required for the jet engine component to affect movement when destroyed. If not set (0.0), destroyed jet engine components do not affect movement performance.
- [MaxLiftDamaged](#maxliftdamaged) and [MaxLiftDestroyed](#maxliftdestroyed) are only applicable for aircraft locomotor types (e.g., `JetLocomotor`, `HelicopterLocomotor`).
- For the jet engine component to affect movement performance, the locomotor must reference this component via `LocomotorTemplate.EngineComponentName` (see [Locomotor](../Locomotor.md) documentation). If `EngineComponentName` is empty, the locomotor defaults to looking for a component named `MainEngine`.
- If the name token is omitted, the component is automatically assigned the default name `MainEngine`. This makes it easy to add a default jet engine component without specifying a name, and the locomotor will automatically find it if `EngineComponentName` is empty.
- By default, [DamagedStatusType](#damagedstatustype) is set to `COMPONENT_ENGINE_DAMAGED` and [DestroyedStatusType](#destroyedstatustype) is set to `COMPONENT_ENGINE_DESTROYED` in the constructor. These defaults can be overridden by explicitly setting the properties.
- Use multiple jet engine components for multi-engine aircraft to model partial failures (e.g., one engine destroyed reduces performance, but aircraft can still fly with remaining engines).

## Modder Recommended Use Scenarios

(pending modder review)

## Source Files

**Base Class:** [EngineComponent](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Components/EngineComponent.h)

- Header: [JetEngineComponent.h](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Components/JetEngineComponent.h)
- Source: [JetEngineComponent.cpp](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Components/JetEngineComponent.cpp)

## Changes History

- 16/12/2025 — AI — Complete reconstruction based on updated instruction file with all inherited Component and EngineComponent properties, proper version flags, complete enum lists (48 BodyDamageType values), movement performance properties documentation, module placement rules, correct linking, and default name handling.

## Status

- Documentation Status: AI-generated
- Last Updated: 16/12/2025 by AI
- Certification: 0/2 reviews

### Reviewers

- (pending)
