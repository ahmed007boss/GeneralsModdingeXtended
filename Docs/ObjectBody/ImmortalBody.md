# ImmortalBody

Status: AI-generated, 0/2 reviews

## Overview

The `ImmortalBody` module is a specialized body module that prevents objects from ever dying by ensuring their health never drops below 1 point. Unlike [ActiveBody](./ActiveBody.md) which allows objects to die when health reaches 0, ImmortalBody overrides the health change system to prevent health from falling below 1, making objects truly immortal. Objects can still take damage, show damage states, and be affected by all other body systems, but they can never be destroyed through health loss. This is a module added inside `Object` entries.

Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
  - [Limitations](#limitations)
  - [Conditions](#conditions)
  - [Dependencies](#dependencies)
- [Properties](#properties)
  - [Health Settings](#health-settings)
  - [Subdual Damage Settings](#subdual-damage-settings)
  - [Electronic Warfare Settings](#electronic-warfare-settings)
  - [Component Settings](#component-settings)
- [Enum Value Lists](#enum-value-lists)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Document Log](#document-log)
- [Status](#status)
- [Reviewers](#reviewers)

## Usage

Place under `Body = ImmortalBody ModuleTag_XX` inside [Object](../Object.md) entries. In GMX, ImmortalBody can also be added to `ObjectExtend` entries. See [Template](#template) for correct syntax.

**Placement**:
- **Retail**: ImmortalBody can only be added to `Object` entries (ObjectExtend does not exist in Retail).
- **GMX**: ImmortalBody can be added to both `Object` and `ObjectExtend` entries.

Only one body module (ActiveBody, ImmortalBody, StructureBody, etc.) can exist per object. If multiple body modules are added to the same object, the game will crash with a "Duplicate bodies" assertion error during object creation. This restriction applies regardless of `ModuleTag` names - the object can only have one body module total.

**Limitations**:
- Health is automatically clamped to minimum 1 point - objects can never die from any type of damage, regardless of how much damage is dealt.
- Objects can still take damage normally and show damage states ([BodyDamageType Values](#bodydamagetype-values) such as PRISTINE, DAMAGED, REALLYDAMAGED, RUBBLE) based on health percentage thresholds defined in game data. Damage states affect visual appearance and particle systems.
- If [InitialHealth](#initialhealth) exceeds [MaxHealth](#maxhealth), the current health will be clamped to [MaxHealth](#maxhealth) when the first health change occurs. Health cannot go below `1.0` or above [MaxHealth](#maxhealth).
- [SubdualDamageCap](#subdualdamagecap) can disable objects without destroying them when subdual damage equals or exceeds [MaxHealth](#maxhealth). Subdual damage properties are exclusive to Generals Zero Hour (Retail Zero Hour 1.04) and GMX (both Generals and Zero Hour).
- [JammingDamageCap](#jammingdamagecap) can jam electronic systems and components when jamming damage equals or exceeds [MaxHealth](#maxhealth). Jamming damage properties are GMX Zero Hour only.
- Objects automatically heal subdual and jamming damage over time if [SubdualDamageHealRate](#subdualdamagehealrate), [SubdualDamageHealAmount](#subdualdamagehealamount), [JammingDamageHealRate](#jammingdamagehealrate), and [JammingDamageHealAmount](#jammingdamagehealamount) are set. The healing is handled by helper systems that run at the specified intervals.
- Components can be added to ImmortalBody for detailed damage modeling (GMX Zero Hour only). See [Component documentation](ObjectComponents/Component.md) for component-specific limitations and requirements.

**Conditions**:
- Objects with ImmortalBody can be targeted by weapons (see [Weapon documentation](../Weapon.md)) and affected by damage types. Health is reduced when weapons deal damage, but cannot fall below 1 point. Damage states are updated based on health percentage.
- **MaxHealthUpgrade** (see [MaxHealthUpgrade documentation](../ObjectUpgrades/MaxHealthUpgrade.md)): When upgrades are applied that increase maximum health, `MaxHealthUpgrade` calls `setMaxHealth()`, which internally calls `internalChangeHealth()`. ImmortalBody's override ensures health never drops below 1, even when health changes occur during upgrade application. The health change type (PRESERVE_RATIO, ADD_CURRENT_HEALTH_TOO, FULLY_HEAL, SAME_CURRENTHEALTH) determines how current health is adjusted when maximum health changes.
- **Veterancy system**: When objects gain veterancy levels (Veteran, Elite, Heroic), the system calls `onVeterancyLevelChanged()`, which modifies maximum health using `setMaxHealth()` with `PRESERVE_RATIO` to scale health proportionally. ImmortalBody's health protection ensures objects remain at minimum 1 health even after veterancy changes.
- **Player difficulty scaling**: In single-player games, difficulty settings modify object maximum health via `setMaxHealth()` with `PRESERVE_RATIO`. ImmortalBody's protection applies during these scaling operations.
- **BattlePlanUpdate (GMX Zero Hour only)**: Strategy Center "Hold The Line" battle plan can modify maximum health using `setMaxHealth()`. ImmortalBody ensures health protection during these plan-based health changes.
- **Healing systems**: Healing behaviors (see [AutoHealBehavior documentation](../ObjectBehaviorsModules/AutoHealBehavior.md)) and repair systems call `attemptHealing()`, which uses `internalChangeHealth()`. ImmortalBody allows healing to work normally, but ensures health never goes below 1.
- **Script actions**: Scripts can damage objects using `doNamedDamage()` and `doDamageTeamMembers()`, which call `attemptDamage()` and eventually `internalChangeHealth()`. ImmortalBody prevents script-based damage from killing objects. Scripts can also set maximum health via object properties (`objectMaxHPs`), which calls `setMaxHealth()`.
- ImmortalBody integrates with armor systems (see [Armor documentation](../Armor.md)) and damage effects. Armor modifies incoming damage before it is applied to health, but the final health value is clamped to minimum 1.
- Damage states are calculated based on global thresholds defined in game data and affect visual appearance and particle systems.
- Components can be added to ImmortalBody for detailed damage modeling (GMX Zero Hour only). Components interact with weapons, locomotor (see [Locomotor](../Locomotor.md)), healing systems, GUI commands, prerequisites, and behaviors. Component health is initialized based on main body maximum health via `initializeComponentHealth()`. See [Component documentation](ObjectComponents/Component.md) for component-specific conditions and interactions.
- **ObjectExtend (GMX only)**: When ImmortalBody is added to an `ObjectExtend` entry with the same `ModuleTag` name as the base object, the base object's body module is automatically replaced. ObjectExtend automatically clears modules with matching `ModuleTag` names when adding new modules.
- **ObjectReskin (both Retail and GMX)**: ObjectReskin uses the same module system as Object. Adding ImmortalBody to an ObjectReskin entry with the same `ModuleTag` name as the base object will cause a duplicate module tag error, as ObjectReskin does not support automatic module replacement like ObjectExtend.

**Dependencies**:
- Requires proper armor and damage type definitions to function correctly. ImmortalBody relies on armor systems to modify incoming damage before it is applied to health.
- Inherits all properties and functionality from [ActiveBody](./ActiveBody.md) while overriding the health change system to prevent death.
- Works with upgrade systems (see [MaxHealthUpgrade documentation](../ObjectUpgrades/MaxHealthUpgrade.md)) that modify maximum health.
- Compatible with veterancy system health scaling through global data health bonuses.
- Compatible with healing and repair systems that restore health over time.

## Properties

ImmortalBody inherits all properties from [ActiveBody](./ActiveBody.md) with no additional INI-parsable properties. All properties listed below are inherited from ActiveBody and function identically, except that health is prevented from dropping below 1 point.

### Health Settings

Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

#### `MaxHealth`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Maximum health points the object can have. Higher values make objects more durable and resistant to damage. This determines the total damage capacity before destruction. If `InitialHealth` exceeds `MaxHealth`, the current health will be clamped to `MaxHealth` when the first health change occurs. Health is automatically clamped to `MaxHealth` as the upper limit and `1.0` as the lower limit (instead of `0.0` for ActiveBody) during damage and healing operations.
- **Default**: `0.0`
- **Example**: `MaxHealth = 500.0`

#### `InitialHealth`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Starting health points when the object is created. Higher values allow objects to spawn with more health than their maximum, providing temporary damage buffer. Lower values spawn objects at reduced health. The initial health value is set directly during object creation; if it exceeds `MaxHealth`, it will be clamped to `MaxHealth` when the first health change occurs. Health cannot go below `1.0` (instead of `0.0` for ActiveBody).
- **Default**: `0.0`
- **Example**: `InitialHealth = 500.0`

### Subdual Damage Settings

Available in: *(GMX Generals, GMX Zero Hour, Retail Zero Hour 1.04)*

#### `SubdualDamageCap`
Available in: *(GMX Generals, GMX Zero Hour, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Maximum subdual damage that can accumulate before the object is subdued (disabled). Higher values allow objects to absorb more subdual damage before becoming incapacitated. At 0 (default), objects cannot be subdued (disabled). Subdual damage accumulates separately from normal health damage and can disable objects without destroying them. When subdual damage equals or exceeds `MaxHealth`, the object becomes subdued (disabled).
- **Default**: `0.0`
- **Example**: `SubdualDamageCap = 350.0`

#### `SubdualDamageHealRate`
Available in: *(GMX Generals, GMX Zero Hour, Retail Zero Hour 1.04)*

- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time interval between subdual damage healing attempts. Lower values heal subdual damage more frequently, while higher values heal less often. At 0 (default), no automatic subdual healing occurs. Subdual damage is healed automatically by the `SubdualDamageHelper` system at the specified interval.
- **Default**: `0`
- **Example**: `SubdualDamageHealRate = 500`

#### `SubdualDamageHealAmount`
Available in: *(GMX Generals, GMX Zero Hour, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Amount of subdual damage healed per healing interval. Higher values heal more subdual damage per tick, while lower values heal less. At 0 (default), no subdual healing occurs. This amount is subtracted from the current subdual damage each time the healing interval elapses.
- **Default**: `0.0`
- **Example**: `SubdualDamageHealAmount = 50.0`

### <span style="color:#5bbcff; font-weight:bold;">Electronic Warfare Settings</span>

Available only in: *(GMX Zero Hour)*

#### `JammingDamageCap`
Available only in: *(GMX Zero Hour)*

- **Type**: `Real`
- **Description**: Maximum jamming damage that can accumulate before the object is jammed (electronically disabled). Higher values allow objects to absorb more jamming damage before becoming electronically disabled. At 0 (default), objects cannot be jammed. Jamming damage accumulates separately from normal health damage and subdual damage. When jamming damage equals or exceeds `MaxHealth`, the object becomes jammed. Electronic components (ElectronicsComponent, SensorComponent) can also have their own jamming damage caps that contribute to the total effective jamming capacity.
- **Default**: `0.0`
- **Example**: `JammingDamageCap = 350.0`

#### `JammingDamageHealRate`
Available only in: *(GMX Zero Hour)*

- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time interval between jamming damage healing attempts. Lower values heal jamming damage more frequently, while higher values heal less often. At 0 (default), no automatic jamming healing occurs. Jamming damage is healed automatically by the `JammingDamageHelper` system at the specified interval. If electronic components have their own healing rates, the system uses the component-based healing rates when components are present.
- **Default**: `0`
- **Example**: `JammingDamageHealRate = 500`

#### `JammingDamageHealAmount`
Available only in: *(GMX Zero Hour)*

- **Type**: `Real`
- **Description**: Amount of jamming damage healed per healing interval. Higher values heal more jamming damage per tick, while lower values heal less. At 0 (default), no jamming healing occurs. This amount is subtracted from the current jamming damage each time the healing interval elapses.
- **Default**: `0.0`
- **Example**: `JammingDamageHealAmount = 100.0`

#### `CanBeJammedByDirectJammers`
Available only in: *(GMX Zero Hour)*

- **Type**: `Bool`
- **Description**: Whether this object can be affected by direct jamming weapons. When `Yes`, the object can be jammed by weapons that apply jamming damage directly to the target. When `No`, the object is immune to direct jamming attacks. This flag is checked along with component jamming flags when determining if jamming damage can be applied.
- **Default**: `No`
- **Example**: `CanBeJammedByDirectJammers = Yes`

#### `CanBeJammedByAreaJammers`
Available only in: *(GMX Zero Hour)*

- **Type**: `Bool`
- **Description**: Whether this object can be affected by area jamming weapons. When `Yes`, the object can be jammed by weapons that apply jamming damage in an area effect. When `No`, the object is immune to area jamming attacks. This flag is checked along with component jamming flags when determining if jamming damage can be applied.
- **Default**: `No`
- **Example**: `CanBeJammedByAreaJammers = Yes`

### <span style="color:#5bbcff; font-weight:bold;">Component Settings</span>

Available only in: *(GMX Zero Hour)*

ImmortalBody supports multiple component types that can be added to objects for detailed damage modeling. Each component type has its own specialized properties while inheriting base component functionality. Components allow for realistic damage simulation where different parts of an object can be damaged independently. Components are parsed from INI and copied to each object instance during construction.

#### `Component`
Available only in: *(GMX Zero Hour)*

- **Type**: `Component` block (see [Component documentation](ObjectComponents/Component.md))
- **Description**: Base component type for generic component health systems. Use this for components that don't require specialized functionality. Components can be damaged, healed, replaced, and their status affects gameplay systems like movement, weapons, and visual appearance. See [Component documentation](ObjectComponents/Component.md) for complete details, limitations, and usage.
- **Default**: No components defined
- **Example**: 
```ini
Component PRIMARY_WEAPON
  MaxHealth = 100.0
  InitialHealth = 100.0
  HealingType = NORMAL
  DamageOnSides = HIT_SIDE_FRONT HIT_SIDE_TOP
End
```

#### `EngineComponent`
Available only in: *(GMX Zero Hour)*

- **Type**: `EngineComponent` block (see [EngineComponent documentation](ObjectComponents/EngineComponent.md))
- **Description**: Specialized component for engine systems. When destroyed, typically disables vehicle movement. See [EngineComponent documentation](ObjectComponents/EngineComponent.md) for complete details, limitations, and usage.
- **Default**: No components defined
- **Example**: 
```ini
EngineComponent MainEngine
  MaxHealth = 150.0
  InitialHealth = 150.0
  ReplacementCost = 500
End
```

#### `VisionComponent`
Available only in: *(GMX Zero Hour)*

- **Type**: `VisionComponent` block (see [VisionComponent documentation](ObjectComponents/VisionComponent.md))
- **Description**: Specialized component for vision/sensor systems. When destroyed, typically disables vision range and detection. See [VisionComponent documentation](ObjectComponents/VisionComponent.md) for complete details, limitations, and usage.
- **Default**: No components defined
- **Example**: 
```ini
VisionComponent VisionSensor
  MaxHealth = 10.0
  InitialHealth = 10.0
  ReplacementCost = 100
  VisionRange = 400.0
End
```

#### `WeaponComponent`
Available only in: *(GMX Zero Hour)*

- **Type**: `WeaponComponent` block (see [WeaponComponent documentation](ObjectComponents/WeaponComponent.md))
- **Description**: Specialized component for weapon systems. When destroyed, disables the associated weapon slot. See [WeaponComponent documentation](ObjectComponents/WeaponComponent.md) for complete details, limitations, and usage.
- **Default**: No components defined
- **Example**: 
```ini
WeaponComponent MainGun
  MaxHealth = 100.0
  InitialHealth = 100.0
  ReplacementCost = 400
  WeaponSlot = PRIMARY
End
```

#### `TurretComponent`
Available only in: *(GMX Zero Hour)*

- **Type**: `TurretComponent` block (see [TurretComponent documentation](ObjectComponents/TurretComponent.md))
- **Description**: Specialized component for turret systems. When destroyed, typically disables turret rotation and weapon firing. See [TurretComponent documentation](ObjectComponents/TurretComponent.md) for complete details, limitations, and usage.
- **Default**: No components defined
- **Example**: 
```ini
TurretComponent MainTurret
  MaxHealth = 120.0
  InitialHealth = 120.0
  ReplacementCost = 450
End
```

#### `ElectronicsComponent`
Available only in: *(GMX Zero Hour)*

- **Type**: `ElectronicsComponent` block (see [ElectronicsComponent documentation](ObjectComponents/ElectronicsComponent.md))
- **Description**: Specialized component for electronic systems. Supports jamming damage and electronic warfare effects. See [ElectronicsComponent documentation](ObjectComponents/ElectronicsComponent.md) for complete details, limitations, and usage.
- **Default**: No components defined
- **Example**: 
```ini
ElectronicsComponent Jammer
  MaxHealth = 20.0
  InitialHealth = 20.0
  ReplacementCost = 200
  JammingDamageCap = 350
  JammingDamageHealRate = 500
  JammingDamageHealAmount = 100
  CanBeJammedByDirectJammers = Yes
End
```

#### `InventoryStorageComponent`
Available only in: *(GMX Zero Hour)*

- **Type**: `InventoryStorageComponent` block (see [InventoryStorageComponent documentation](ObjectComponents/InventoryStorageComponent.md))
- **Description**: Specialized component for inventory storage systems. When destroyed, may affect unit's ability to carry inventory items. See [InventoryStorageComponent documentation](ObjectComponents/InventoryStorageComponent.md) for complete details, limitations, and usage.
- **Default**: No components defined
- **Example**: 
```ini
InventoryStorageComponent FuelTank
  MaxHealth = 60.0
  InitialHealth = 60.0
  ReplacementCost = 150
  ForceReturnOnDestroy = Yes
  InventoryItem = JetFuel
End
```

#### `PowerComponent`
Available only in: *(GMX Zero Hour)*

- **Type**: `PowerComponent` block (see [PowerComponent documentation](ObjectComponents/PowerComponent.md))
- **Description**: Specialized component for power generation systems. When damaged or destroyed, affects power-dependent systems. See [PowerComponent documentation](ObjectComponents/PowerComponent.md) for complete details, limitations, and usage.
- **Default**: No components defined
- **Example**: 
```ini
PowerComponent PowerSupply
  MaxHealth = 80.0
  InitialHealth = 80.0
  ReplacementCost = 350
  JammingDamageCap = 400.0
  JammingDamageHealRate = 500
  JammingDamageHealAmount = 75.0
End
```

#### `CommunicationComponent`
Available only in: *(GMX Zero Hour)*

- **Type**: `CommunicationComponent` block (see [CommunicationComponent documentation](ObjectComponents/CommunicationComponent.md))
- **Description**: Specialized component for communication systems. When damaged or destroyed, affects unit communication and coordination abilities. See [CommunicationComponent documentation](ObjectComponents/CommunicationComponent.md) for complete details, limitations, and usage.
- **Default**: No components defined
- **Example**: 
```ini
CommunicationComponent CommunicationRadio
  MaxHealth = 40.0
  InitialHealth = 40.0
  ReplacementCost = 250
  JammingDamageCap = 400.0
  JammingDamageHealRate = 500
  JammingDamageHealAmount = 80.0
End
```

#### `RemoteControlComponent`
Available only in: *(GMX Zero Hour)*

- **Type**: `RemoteControlComponent` block (see [RemoteControlComponent documentation](ObjectComponents/RemoteControlComponent.md))
- **Description**: Specialized component for remote control systems. When damaged or destroyed, affects remote control functionality. See [RemoteControlComponent documentation](ObjectComponents/RemoteControlComponent.md) for complete details, limitations, and usage.
- **Default**: No components defined
- **Example**: 
```ini
RemoteControlComponent RemoteController
  MaxHealth = 30.0
  InitialHealth = 30.0
  ReplacementCost = 200
  JammingDamageCap = 500.0
  JammingDamageHealRate = 500
  JammingDamageHealAmount = 100.0
End
```

#### `JetEngineComponent`
Available only in: *(GMX Zero Hour)*

- **Type**: `JetEngineComponent` block (see [JetEngineComponent documentation](ObjectComponents/JetEngineComponent.md))
- **Description**: Specialized component for jet engine systems. When destroyed, typically forces aircraft to return to base. See [JetEngineComponent documentation](ObjectComponents/JetEngineComponent.md) for complete details, limitations, and usage.
- **Default**: No components defined
- **Example**: 
```ini
JetEngineComponent ENGINE
  MaxHealth = 100.0
  InitialHealth = 100.0
  ReplacementCost = 400
  ForceReturnOnDestroy = Yes
End
```

#### `SensorComponent`
Available only in: *(GMX Zero Hour)*

- **Type**: `SensorComponent` block (see [SensorComponent documentation](ObjectComponents/SensorComponent.md))
- **Description**: Specialized component for sensor/radar systems. When damaged or destroyed, affects detection range and shroud clearing. See [SensorComponent documentation](ObjectComponents/SensorComponent.md) for complete details, limitations, and usage.
- **Default**: No components defined
- **Example**: 
```ini
SensorComponent Radar
  MaxHealth = 10.0
  InitialHealth = 10.0
  ReplacementCost = 200
  JammingDamageCap = 350
  JammingDamageHealRate = 500
  JammingDamageHealAmount = 50
  CanBeJammedByDirectJammers = Yes
  ShroudClearingRange = 330.0
End
```

## Enum Value Lists

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

### Truly Immortal Hero Unit
```ini
Body = ImmortalBody ModuleTag_01
  MaxHealth = 1000.0
  InitialHealth = 1000.0
  SubdualDamageCap = 0.0
  SubdualDamageHealRate = 0
  SubdualDamageHealAmount = 0.0
End
```

### Indestructible Objective Marker
```ini
Body = ImmortalBody ModuleTag_02
  MaxHealth = 500.0
  InitialHealth = 500.0
  SubdualDamageCap = 0.0
  SubdualDamageHealRate = 0
  SubdualDamageHealAmount = 0.0
End
```

### Immortal Unit with Electronic Warfare (GMX Zero Hour only)
```ini
Body = ImmortalBody ModuleTag_03
  MaxHealth = 800.0
  InitialHealth = 800.0
  SubdualDamageCap = 700.0
  SubdualDamageHealRate = 500
  SubdualDamageHealAmount = 50.0
  JammingDamageCap = 350.0
  JammingDamageHealRate = 500
  JammingDamageHealAmount = 100.0
  CanBeJammedByDirectJammers = Yes
  CanBeJammedByAreaJammers = No
End
```

### Immortal Unit with Components (GMX Zero Hour only)
```ini
Body = ImmortalBody ModuleTag_04
  MaxHealth = 600.0
  InitialHealth = 600.0
  Component MainEngine
    MaxHealth = 100.0
    InitialHealth = 100.0
    ReplacementCost = 400
    ForceReturnOnDestroy = Yes
  End
  WeaponComponent MainGun
    MaxHealth = 80.0
    InitialHealth = 80.0
    ReplacementCost = 350
    WeaponSlot = PRIMARY
  End
End
```

## Template

```ini
Body = ImmortalBody ModuleTag_XX
  MaxHealth = 0.0                 ; // maximum health points *(GMX, Retail 1.04)*
  InitialHealth = 0.0             ; // starting health points *(GMX, Retail 1.04)*

  SubdualDamageCap = 0.0          ; // maximum subdual damage before subdual *(GMX Zero Hour, Retail Zero Hour 1.04)*
  SubdualDamageHealRate = 0       ; // milliseconds between subdual damage healing *(GMX Zero Hour, Retail Zero Hour 1.04)*
  SubdualDamageHealAmount = 0.0   ; // amount of subdual damage healed per interval *(GMX Zero Hour, Retail Zero Hour 1.04)*

  JammingDamageCap = 0.0          ; // maximum jamming damage before jamming *(GMX Zero Hour only)*
  JammingDamageHealRate = 0       ; // milliseconds between jamming damage healing *(GMX Zero Hour only)*
  JammingDamageHealAmount = 0.0   ; // amount of jamming damage healed per interval *(GMX Zero Hour only)*
  CanBeJammedByDirectJammers = No ; // whether object can be jammed by direct jammers *(GMX Zero Hour only)*
  CanBeJammedByAreaJammers = No   ; // whether object can be jammed by area jammers *(GMX Zero Hour only)*

  ; Components can be added here (GMX Zero Hour only, see Component documentation)
End
```

## Notes

- ImmortalBody automatically manages damage states ([BodyDamageType Values](#bodydamagetype-values) such as PRISTINE, DAMAGED, REALLYDAMAGED, RUBBLE) based on health percentage thresholds defined in game data. Damage states affect visual appearance and particle systems.
- Health is automatically clamped to minimum 1 point - objects can never die from any type of damage, regardless of how much damage is dealt. This is the key difference from [ActiveBody](./ActiveBody.md).
- Damage states are calculated based on global thresholds and updated automatically when [MaxHealth](#maxhealth) changes.
- Subdual damage can disable objects without destroying them (Zero Hour only). Subdual damage accumulates separately from normal health damage and is limited by [SubdualDamageCap](#subdualdamagecap). Even when subdued, objects with ImmortalBody cannot die.
- Jamming damage can jam electronic systems and components (GMX Zero Hour only). Jamming damage accumulates separately from normal health damage and subdual damage and is limited by [JammingDamageCap](#jammingdamagecap).
- Objects automatically heal subdual and jamming damage over time if [SubdualDamageHealRate](#subdualdamagehealrate), [SubdualDamageHealAmount](#subdualdamagehealamount), [JammingDamageHealRate](#jammingdamagehealrate), and [JammingDamageHealAmount](#jammingdamagehealamount) are set. The healing is handled by helper systems that run at the specified intervals.
- Objects with ImmortalBody can be targeted by weapons (see [Weapon documentation](../Weapon.md)) and affected by damage types. Armor modifies incoming damage before it is applied to health, but the final health value is clamped to minimum 1.
- **MaxHealthUpgrade interactions**: When [MaxHealthUpgrade](../ObjectUpgrades/MaxHealthUpgrade.md) modules are applied, they call `setMaxHealth()` which internally uses `internalChangeHealth()`. ImmortalBody's override ensures health never drops below 1 during upgrade application, regardless of the health change type (PRESERVE_RATIO, ADD_CURRENT_HEALTH_TOO, FULLY_HEAL, SAME_CURRENTHEALTH).
- **Veterancy interactions**: Veterancy level changes modify maximum health using `setMaxHealth()` with `PRESERVE_RATIO`, scaling health proportionally based on global veterancy health bonuses. ImmortalBody ensures objects remain at minimum 1 health even after veterancy scaling.
- **Healing and repair interactions**: Healing behaviors (see [AutoHealBehavior documentation](../ObjectBehaviorsModules/AutoHealBehavior.md)) and repair systems call `attemptHealing()`, which uses `internalChangeHealth()`. ImmortalBody allows healing to restore health normally, but prevents health from ever falling below 1.
- **Script interactions**: Script actions can damage objects via `doNamedDamage()` and `doDamageTeamMembers()`, which eventually call `internalChangeHealth()`. ImmortalBody prevents script-based damage from killing objects. Scripts can also modify maximum health via object properties, which calls `setMaxHealth()`.
- **Player difficulty interactions**: Single-player difficulty settings modify object maximum health via `setMaxHealth()` with `PRESERVE_RATIO`. ImmortalBody's protection applies during difficulty-based health scaling.
- **BattlePlanUpdate interactions (GMX Zero Hour only)**: Strategy Center "Hold The Line" battle plan can modify maximum health. ImmortalBody ensures health protection during plan-based health changes.
- ImmortalBody integrates with armor systems (see [Armor documentation](../Armor.md)) and damage effects.
- Components can be added to ImmortalBody for detailed damage modeling (GMX Zero Hour only). Component health is initialized based on main body maximum health, and components interact with all the same systems (weapons, healing, upgrades, veterancy). See [Component documentation](ObjectComponents/Component.md) and individual component documentation files for component-specific notes and details.
- Objects can still be removed through other means (like special powers or script commands that directly remove objects), but they cannot die from health loss through any damage, healing, upgrade, or veterancy system.
- Recommended for creating truly indestructible objectives, markers, or special hero units that must never die from combat damage, regardless of upgrades, veterancy, healing, or script interactions.

## Source Files

**Base Class:** [ActiveBody](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ActiveBody.h) (GMX Zero Hour), [ActiveBody](../../Generals/Code/GameEngine/Include/GameLogic/Module/ActiveBody.h) (GMX Generals)

- Header (GMX Zero Hour): [ImmortalBody.h](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ImmortalBody.h)
- Source (GMX Zero Hour): [ImmortalBody.cpp](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Body/ImmortalBody.cpp)
- Header (GMX Generals): [ImmortalBody.h](../../Generals/Code/GameEngine/Include/GameLogic/Module/ImmortalBody.h)
- Source (GMX Generals): [ImmortalBody.cpp](../../Generals/Code/GameEngine/Source/GameLogic/Object/Body/ImmortalBody.cpp)

## Changes History

- GMX Zero Hour — Inherits Electronic Warfare (Jamming) system from ActiveBody: `JammingDamageCap`, `JammingDamageHealRate`, `JammingDamageHealAmount`, `CanBeJammedByDirectJammers`, `CanBeJammedByAreaJammers`.
- GMX Zero Hour — Inherits component system from ActiveBody: `Component`, `EngineComponent`, `VisionComponent`, `WeaponComponent`, `TurretComponent`, `ElectronicsComponent`, `InventoryStorageComponent`, `PowerComponent`, `CommunicationComponent`, `RemoteControlComponent`, `JetEngineComponent`, `SensorComponent`.
- GMX Zero Hour — Inherits extended `BodyDamageType` values from ActiveBody (component-specific values).

## Document Log

- 16/12/2025 — AI — Initial document created.

## Status

- Documentation Status: AI-generated
- Last Updated: 16/12/2025 by AI
- Certification: 0/2 reviews

### Reviewers

- (pending)
