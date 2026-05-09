# FireWeaponWhenDeadBehavior

FireWeaponWhenDeadBehavior fires weapons when the object dies, with upgrade-based activation.

## Overview

The `FireWeaponWhenDeadBehavior` class manages weapon firing when an object dies. It can fire a specified weapon at the object's position when death occurs, but only when the behavior is upgrade-activated. This behavior is commonly used for explosive objects, self-destruct mechanisms, and death effects that involve weapon firing.

## Usage

Used by objects that need to fire weapons when they die, such as explosive units, self-destruct mechanisms, or objects with death effects. This is a **behavior module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- FireWeaponWhenDeadBehavior only fires weapons when the behavior is upgrade-activated
- The behavior only triggers when the object actually dies and is fully constructed
- Weapon firing is limited to the object's current position
- The behavior requires valid weapon template definitions to function
- The behavior does not fire weapons for objects under construction

**Conditions**:
- FireWeaponWhenDeadBehavior fires weapons based on upgrade activation state
- The behavior integrates with the upgrade system for conditional activation
- Death conditions can be filtered based on death types, veterancy levels, and status requirements
- The behavior supports upgrade conflicts and requirements for activation
- Weapon firing occurs at the object's current position when death conditions are met
- **Multiple instances behavior**: Multiple instances can exist but each manages its own weapons independently; no property conflicts occur

**Dependencies**:
- Requires valid weapon template definitions to function
- The behavior relies on the upgrade system for activation timing

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Behavior Settings](#behavior-settings)
  - [Weapon Settings](#weapon-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

### Behavior Settings

#### `StartsActive` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether the behavior starts in an active (upgraded) state. When true, the death weapon fires immediately upon object death. When false (default), the behavior must be activated by upgrades before firing
- **Default**: `No`
- **Example**: `StartsActive = No`

### Weapon Settings

#### `DeathWeapon` *(v1.04)*
- **Type**: `Weapon` (see [Weapon documentation](../Weapon.md))
- **Description**: Weapon template to fire when the object dies. When set, fires the specified weapon upon death. When NULL (default), no weapon is fired on death
- **Default**: `NULL` (none)
- **Example**: `DeathWeapon = WeaponExplosion`

## Examples

### Self-Destruct Behavior
```ini
Behavior = FireWeaponWhenDeadBehavior ModuleTag_SelfDestruct
  StartsActive = Yes
  DeathWeapon = WeaponSelfDestruct
End
```

### Upgrade-Activated Death Weapon
```ini
Behavior = FireWeaponWhenDeadBehavior ModuleTag_UpgradeDeath
  StartsActive = No
  DeathWeapon = WeaponDeathExplosion
  RequiredUpgrade = UPGRADE_SELF_DESTRUCT
End
```

### Conditional Death Weapon
```ini
Behavior = FireWeaponWhenDeadBehavior ModuleTag_Conditional
  StartsActive = No
  DeathWeapon = WeaponConditionalDeath
  DeathTypes = NONE +EXPLODED +BURNED
  VeterancyLevels = VETERAN +ELITE
End
```

## Template

```ini
Behavior = FireWeaponWhenDeadBehavior ModuleTag_XX
  ; Behavior Settings
  StartsActive = No                   ; // behavior starts in active state *(v1.04)*

  ; Weapon Settings
  DeathWeapon =                       ; // weapon to fire when object dies *(v1.04)*
End
```

## Notes

- FireWeaponWhenDeadBehavior fires weapons based on upgrade activation state
- The behavior integrates with the upgrade system for conditional activation
- Death conditions can be filtered based on death types, veterancy levels, and status requirements
- The behavior supports upgrade conflicts and requirements for activation
- Weapon firing occurs at the object's current position when death conditions are met
- The behavior does not fire weapons for objects under construction

## Source Files

**Base Class:** [`BehaviorModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h), [`UpgradeMux`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h), [`DieModuleInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FireWeaponWhenDeadBehavior.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FireWeaponWhenDeadBehavior.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/FireWeaponWhenDeadBehavior.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/FireWeaponWhenDeadBehavior.cpp)