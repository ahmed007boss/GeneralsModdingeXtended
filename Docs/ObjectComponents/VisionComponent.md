# VisionComponent *(GMX)*

Status: AI-generated, 0/2 reviews

## Overview
`VisionComponent` models optics/vision hardware under `[ActiveBody](../ObjectModules/ActiveBody.md)`. Damaged vision can reduce detection effectiveness depending on game logic.

Available in: *(GMX)*

## Usage
Place under `Body = ActiveBody` to make vision systems damageable, healable, replaceable, and usable in detection systems.

**Limitations**:
- Requires `[ActiveBody](../ObjectModules/ActiveBody.md)`; components cannot exist outside an ActiveBody block.
- Component names must be unique within the same object. If multiple components share the same name, systems that look up components by name (weapons via `PrimaryComponentDamage`/`SecondaryComponentDamage`, locomotor via `AffectedByComponents`/`EngineComponentName`, GUI commands, prerequisites) will only find the first matching component, causing unpredictable behavior where the wrong component may be targeted.
- If the name token is omitted/empty, a default name is auto-assigned for this type (e.g., `Vision`).
- If `[MaxHealth](#maxhealth-gmx)` is 0 or negative, the component does not function and cannot be damaged, healed, or accessed by any systems.
- `[InitialHealth](#initialhealth-gmx)` is automatically clamped: if it exceeds `MaxHealth`, it is set to `MaxHealth`; if negative, it is set to `0.0`. This clamping occurs during component initialization.
- To receive damage from weapons, the weapon must list this component by name in `PrimaryComponentDamage` or `SecondaryComponentDamage` (see [Weapon](../Weapon.md)). If not listed, weapons will not damage this component.
- For `[AutoHealBehavior](../ObjectBehaviorsModules/AutoHealBehavior.md)` to heal this component, the behavior must have `ComponentHealingAmount` set. Component healing respects this component's `[HealingType](#healingtype-gmx)` setting.

**Conditions**:
- If this component's name is listed in `LocomotorTemplate.AffectedByComponents` (see Locomotor documentation), component status (damaged/destroyed) can reduce movement capabilities (speed/turn/accel). If not listed, component status has no effect on movement.
- Component status (damaged/destroyed) affects object visual appearance via `DamagedStatusType`/`DestroyedStatusType` settings, which control the body damage state displayed on the model.
- Component status icons are displayed in the GUI health bar area when the component is damaged, destroyed, or user-disabled (see component status system).
- If `ForceReturnOnDestroy = Yes`, aircraft will automatically return to base when this component is destroyed (checked by `[JetAIUpdate](../ObjectUpdates/JetAIUpdate.md)`).
- Component status can be checked by the prerequisite system for command button availability (e.g., requiring component to exist, be working, or be disabled) (see `ObjectPrerequisite` in docs when available).
- Components can be replaced via command buttons using `COMMAND_REPLACE_COMPONENT` (see `[CommandButton](../CommandButton.md)`), or toggled on/off via a component toggle command, if configured. Replacement requires `ReplacementCost > 0`.
- Components can be restored by `[ParkingPlaceBehavior](../ObjectBehaviorsModules/ParkingPlaceBehavior.md)` if the behavior's restore list includes this component's name, or by crate interactions that restore damaged components.
- Damaged/destroyed vision components can affect unit vision range and detection capabilities depending on game logic.

**Dependencies**:
- None. This component can function independently as a health-bearing part with replacement capabilities. All interactions with weapons, locomotor, healing systems, GUI commands, prerequisites, and behaviors are optional enhancements controlled by configuration, not hard requirements.

## Table of Contents
- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
- [Enum Value Lists](#enum-value-lists)
- [Examples](#examples)
- [Template](#template)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)

## Properties

### Health Settings *(GMX)*

#### `MaxHealth` *(GMX)*
- **Type**: `Real`
- **Description**: Maximum health points for this vision component. Higher values make the component more durable and resistant to damage. This determines the total damage capacity before the component is destroyed
- **Default**: `0.0`
- **Example**: `MaxHealth = 60.0`

#### `InitialHealth` *(GMX)*
- **Type**: `Real`
- **Description**: Starting health points for this vision component when the object is created. Higher values allow components to spawn with more health than their maximum, providing temporary damage buffer
- **Default**: `0.0`
- **Example**: `InitialHealth = 60.0`

### Healing Settings *(GMX)*

#### `HealingType` *(GMX)*
- **Type**: `ComponentHealingType` (see [ComponentHealingType Values](#componenthealingtype-values) section)
- **Description**: Defines how this vision component can be healed. Different healing types control whether components can be fully repaired, partially repaired, or require replacement
- **Default**: `NORMAL`
- **Example**: `HealingType = NORMAL`
- **Available Values**: see [ComponentHealingType Values](#componenthealingtype-values)

### Damage Settings *(GMX)*

#### `DamageOnSides` *(GMX)*
- **Type**: `HitSideFlags` (see [HitSide Values](#hitside-values) section)
- **Description**: Specifies which hit sides can damage this vision component. If not set (empty), the component can be damaged from any hit side. This allows for realistic damage modeling where certain components are only vulnerable from specific angles
- **Default**: Empty (damageable from all sides)
- **Example**: `DamageOnSides = HIT_SIDE_FRONT`
- **Available Values**: see [HitSide Values](#hitside-values)

#### `DamagedStatusType` *(GMX)*
- **Type**: `BodyDamageType` (see [BodyDamageType Values](#bodydamagetype-values) section)
- **Description**: Damage state the main object enters when this vision component is damaged (between 10% and 50% health). This affects visual appearance and model state
- **Default**: `0` (no change)
- **Example**: `DamagedStatusType = DAMAGED`
- **Available Values**: see [BodyDamageType Values](#bodydamagetype-values)

#### `DestroyedStatusType` *(GMX)*
- **Type**: `BodyDamageType` (see [BodyDamageType Values](#bodydamagetype-values) section)
- **Description**: Damage state the main object enters when this vision component is destroyed (0% health). This affects visual appearance and model state
- **Default**: `0` (no change)
- **Example**: `DestroyedStatusType = REALLYDAMAGED`
- **Available Values**: see [BodyDamageType Values](#bodydamagetype-values)

### Replacement Settings *(GMX)*

#### `ReplacementCost` *(GMX)*
- **Type**: `UnsignedInt`
- **Description**: Cost in money to fully replace this vision component when it's damaged. Higher values make component replacement more expensive. At 0 (default), the component cannot be replaced via the GUI command system
- **Default**: `0`
- **Example**: `ReplacementCost = 100`

#### `ForceReturnOnDestroy` *(GMX)*
- **Type**: `Bool`
- **Description**: Whether the unit should be forced to return to base when this vision component is destroyed. When `Yes`, aircraft and vehicles will automatically return when this component is destroyed. When `No`, component destruction does not trigger return behavior
- **Default**: `No`
- **Example**: `ForceReturnOnDestroy = No`

## Enum Value Lists

<a id="componenthealingtype-values"></a>
#### `ComponentHealingType` Values
Available in: *(GMX)*

**Source:** [Component.h](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Components/Component.h#63) - `ComponentHealingType` enum definition

Parsed via custom parser using string names: "NORMAL", "PARTIAL_ONLY", "PARTIAL_DESTROYED", "PARTIAL_LIMITED", "REPLACEMENT_ONLY". Used by component `HealingType` property.

- **`NORMAL`** *(GMX)* - Can be healed from destroyed to max normally
- **`PARTIAL_ONLY`** *(GMX)* - Can be healed if not destroyed to max normally
- **`PARTIAL_DESTROYED`** *(GMX)* - Can be healed from destroyed to partially working normally, but to max needs replacement
- **`PARTIAL_LIMITED`** *(GMX)* - Can be healed if not destroyed to partially working normally, but to max needs replacement
- **`REPLACEMENT_ONLY`** *(GMX)* - Cannot be healed normally, needs replacement

<a id="hitside-values"></a>
#### `HitSide` Values
Available in: *(GMX, v1.04)*

Source: `HitSide` (see [Damage.h](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h#188)); string names

- **`HIT_SIDE_FRONT`** *(GMX, v1.04)* - Front side of the object
- **`HIT_SIDE_BACK`** *(GMX, v1.04)* - Back side of the object
- **`HIT_SIDE_LEFT`** *(GMX, v1.04)* - Left side of the object
- **`HIT_SIDE_RIGHT`** *(GMX, v1.04)* - Right side of the object
- **`HIT_SIDE_TOP`** *(GMX, v1.04)* - Top side of the object
- **`HIT_SIDE_BOTTOM`** *(GMX, v1.04)* - Bottom side of the object
- **`HIT_SIDE_UNKNOWN`** *(GMX, v1.04)* - Used when hit side cannot be determined

<a id="bodydamagetype-values"></a>
#### `BodyDamageType` Values
Available in: *(GMX, v1.04)*

Source: `BodyDamageType` (see [BodyModule.h](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h#53)); string names from `TheBodyDamageTypeNames[]`

- **`PRISTINE`** *(GMX, v1.04)* - Unit should appear in pristine condition
- **`DAMAGED`** *(GMX, v1.04)* - Unit has been damaged
- **`REALLYDAMAGED`** *(GMX, v1.04)* - Unit is extremely damaged / nearly destroyed
- **`RUBBLE`** *(GMX, v1.04)* - Unit has been reduced to rubble/corpse/exploded-hulk, etc

## Examples
```ini
VisionComponent Optics
  MaxHealth = 60.0
  InitialHealth = 60.0
  ReplacementCost = 100
End
```

## Template
```ini
VisionComponent NAME
  MaxHealth = 0.0                 ; // maximum health points *(GMX)*
  InitialHealth = 0.0             ; // starting health points *(GMX)*
  HealingType = NORMAL            ; // how this component can be healed *(GMX)*
  DamageOnSides =                 ; // which hit sides can damage this component (empty = all sides) *(GMX)*
  ReplacementCost = 0             ; // cost to replace this component when damaged *(GMX)*
  ForceReturnOnDestroy = No       ; // force return to base when destroyed *(GMX)*
  DamagedStatusType =             ; // damage state when component is damaged *(GMX)*
  DestroyedStatusType =           ; // damage state when component is destroyed *(GMX)*
End
```

## Source Files

**Base Class:** [Component](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Components/Component.h)

- Header: `GeneralsMD/Code/GameEngine/Include/GameLogic/Components/VisionComponent.h`
- Source: `GeneralsMD/Code/GameEngine/Source/GameLogic/Components/VisionComponent.cpp`

## Changes History

- 15/12/2025 — AI — Initial documentation with full property details and enum values.

## Status

- Documentation Status: AI-generated
- Last Updated: 15/12/2025 by AI
- Certification: 0/2 reviews

### Reviewers

- (pending)
