# HighlanderBody

Status: AI-generated, 0/2 reviews

## Overview

The `HighlanderBody` module is a specialized body module that makes objects nearly invulnerable to normal damage while still allowing them to be destroyed by unresistable damage types. Objects with HighlanderBody can take damage normally according to their armor, but their health is clamped to never go below 1 point unless the damage is unresistable. This creates "immortal" objects that can only be destroyed by special weapons or abilities. HighlanderBody inherits all properties from ActiveBody and adds no additional properties. This is a module added inside `Object` entries.

Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

## Table of Contents

- [Overview](#overview)
- [Properties](#properties)
  - [Health Settings](#health-settings)
  - [Subdual Damage Settings](#subdual-damage-settings)
  - [Electronic Warfare Settings](#electronic-warfare-settings)
  - [Component Settings](#component-settings)
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

Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

#### `MaxHealth`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Maximum health points the object can have. Higher values make objects more durable and resistant to damage. This determines the total damage capacity before destruction. If `InitialHealth` exceeds `MaxHealth`, the current health will be clamped to `MaxHealth` when the first health change occurs. Health is automatically clamped to `MaxHealth` as the upper limit and `0.0` as the lower limit during damage and healing operations.
- **Default**: `0.0`
- **Example**: `MaxHealth = 500.0`

#### `InitialHealth`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Starting health points when the object is created. Higher values allow objects to spawn with more health than their maximum, providing temporary damage buffer. Lower values spawn objects at reduced health. The initial health value is set directly during object creation; if it exceeds `MaxHealth`, it will be clamped to `MaxHealth` when the first health change occurs. Health cannot go below `0.0`.
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
- **Description**: Amount of jamming damage healed per healing interval. Higher values heal more jamming damage per tick, while lower values heal less. At 0 (default), no jamming healing occurs. This amount is subtracted from the current jamming damage each time the healing interval elapses. If electronic components have their own healing amounts, the system sums all component healing amounts instead of using this global value.
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

HighlanderBody supports multiple component types that can be added to objects for detailed damage modeling. Each component type has its own specialized properties while inheriting base component functionality. Components allow for realistic damage simulation where different parts of an object can be damaged independently. Components are parsed from INI and copied to each object instance during construction.

#### `Component`
Available only in: *(GMX Zero Hour)*

- **Type**: `Component` block (see [Component documentation](ObjectComponents/Component.md))
- **Description**: Base component type for generic component health systems. Use this for components that don't require specialized functionality. Components can be damaged, healed, replaced, and their status affects gameplay systems like movement, weapons, and visual appearance. See [Component documentation](ObjectComponents/Component.md) for complete details, limitations, and usage.
- **Default**: No components defined

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
- **Description**: Specialized component for vision/sensor systems. When damaged or destroyed, affects unit vision range. See [VisionComponent documentation](ObjectComponents/VisionComponent.md) for complete details, limitations, and usage.
- **Default**: No components defined
- **Example**: 
```ini
VisionComponent Optics
  MaxHealth = 50.0
  InitialHealth = 50.0
  ReplacementCost = 300
  ShroudClearingRange = 400.0
End
```

#### `WeaponComponent`
Available only in: *(GMX Zero Hour)*

- **Type**: `WeaponComponent` block (see [WeaponComponent documentation](ObjectComponents/WeaponComponent.md))
- **Description**: Specialized component for weapon systems. When damaged or destroyed, affects weapon functionality. See [WeaponComponent documentation](ObjectComponents/WeaponComponent.md) for complete details, limitations, and usage.
- **Default**: No components defined
- **Example**: 
```ini
WeaponComponent MainGun
  MaxHealth = 200.0
  InitialHealth = 200.0
  ReplacementCost = 600
End
```

#### `TurretComponent`
Available only in: *(GMX Zero Hour)*

- **Type**: `TurretComponent` block (see [TurretComponent documentation](ObjectComponents/TurretComponent.md))
- **Description**: Specialized component for turret systems. When damaged or destroyed, affects turret rotation and weapon aiming. See [TurretComponent documentation](ObjectComponents/TurretComponent.md) for complete details, limitations, and usage.
- **Default**: No components defined
- **Example**: 
```ini
TurretComponent Turret
  MaxHealth = 150.0
  InitialHealth = 150.0
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

```ini
Body = HighlanderBody ModuleTag_01
  MaxHealth = 1000.0
  InitialHealth = 1000.0
  SubdualDamageCap = 0.0
  SubdualDamageHealRate = 0
  SubdualDamageHealAmount = 0.0
End
```

```ini
Body = HighlanderBody ModuleTag_02
  MaxHealth = 5000.0
  InitialHealth = 5000.0
  SubdualDamageCap = 350.0
  SubdualDamageHealRate = 500
  SubdualDamageHealAmount = 50.0
End
```

```ini
Body = HighlanderBody ModuleTag_03
  MaxHealth = 400.0
  InitialHealth = 400.0
  JammingDamageCap = 350.0
  JammingDamageHealRate = 500
  JammingDamageHealAmount = 100.0
  CanBeJammedByDirectJammers = Yes
End
```

```ini
Body = HighlanderBody ModuleTag_04
  MaxHealth = 200.0
  InitialHealth = 200.0
  SubdualDamageCap = 700.0
  SubdualDamageHealRate = 500
  SubdualDamageHealAmount = 50.0
  JammingDamageCap = 350.0
  JammingDamageHealRate = 500
  JammingDamageHealAmount = 100.0
  CanBeJammedByDirectJammers = Yes
  CanBeJammedByAreaJammers = Yes
End
```

```ini
Body = HighlanderBody ModuleTag_05
  MaxHealth = 750.0
  InitialHealth = 750.0
  Component MainEngine
    MaxHealth = 100.0
    InitialHealth = 100.0
    ReplacementCost = 400
    ForceReturnOnDestroy = Yes
  End
End
```

## Usage

Place under `Body = HighlanderBody ModuleTag_XX` inside `Object` entries. In GMX, HighlanderBody can also be added to `ObjectExtend` entries. See Template for correct syntax.

**Placement**:
- **Retail**: HighlanderBody can only be added to `Object` entries (ObjectExtend does not exist in Retail).
- **GMX**: HighlanderBody can be added to both `Object` and `ObjectExtend` entries.

Only one body module (ActiveBody, InactiveBody, StructureBody, HighlanderBody, etc.) can exist per object. If multiple body modules are added to the same object, the game will crash with a "Duplicate bodies" assertion error during object creation. This restriction applies regardless of `ModuleTag` names - the object can only have one body module total.

**Limitations**:
- HighlanderBody prevents death from normal damage types by clamping health to a minimum of 1 point. Only unresistable damage can reduce health below 1 point and cause death.
- ActiveBody automatically manages damage states ([BodyDamageType Values](#bodydamagetype-values) such as PRISTINE, DAMAGED, REALLYDAMAGED, RUBBLE) based on health percentage thresholds defined in game data. Damage states affect visual appearance and particle systems.
- If [InitialHealth](#initialhealth) exceeds [MaxHealth](#maxhealth), the current health will be clamped to [MaxHealth](#maxhealth) when the first health change occurs. Health cannot go below `1.0` for normal damage (or `0.0` for unresistable damage).
- [SubdualDamageCap](#subdualdamagecap) can disable objects without destroying them when subdual damage equals or exceeds [MaxHealth](#maxhealth). Subdual damage properties are exclusive to Generals Zero Hour (Retail Zero Hour 1.04) and GMX (both Generals and Zero Hour).
- [JammingDamageCap](#jammingdamagecap) can jam electronic systems and components when jamming damage equals or exceeds [MaxHealth](#maxhealth). Jamming damage properties are GMX Zero Hour only.
- Objects automatically heal subdual and jamming damage over time if [SubdualDamageHealRate](#subdualdamagehealrate), [SubdualDamageHealAmount](#subdualdamagehealamount), [JammingDamageHealRate](#jammingdamagehealrate), and [JammingDamageHealAmount](#jammingdamagehealamount) are set. The healing is handled by helper systems that run at the specified intervals.
- Components can be added to HighlanderBody for detailed damage modeling (GMX Zero Hour only). See [Component documentation](ObjectComponents/Component.md) for component-specific limitations and requirements.

**Conditions**:
- Objects with HighlanderBody can be targeted by weapons (see [Weapon documentation](../Weapon.md)) and affected by damage types. Health is reduced when weapons deal damage, but normal damage cannot reduce health below 1 point. Only unresistable damage can kill HighlanderBody objects.
- Veterancy levels can modify maximum health and healing rates through upgrade systems.
- HighlanderBody integrates with armor systems (see [Armor documentation](../Armor.md)) and damage effects. Armor modifies incoming damage before it is applied to health.
- Damage states are calculated based on global thresholds defined in game data and affect visual appearance and particle systems. Objects can still show damage states even though they cannot die from normal damage.
- Components can be added to HighlanderBody for detailed damage modeling (GMX Zero Hour only). Components interact with weapons, locomotor (see [Locomotor](../Locomotor.md)), healing systems, GUI commands, prerequisites, and behaviors. See [Component documentation](ObjectComponents/Component.md) for component-specific conditions and interactions.
- **ObjectExtend (GMX only)**: When HighlanderBody is added to an `ObjectExtend` entry with the same `ModuleTag` name as the base object, the base object's HighlanderBody module is automatically replaced. ObjectExtend automatically clears modules with matching `ModuleTag` names when adding new modules.
- **ObjectReskin (both Retail and GMX)**: ObjectReskin uses the same module system as Object. Adding HighlanderBody to an ObjectReskin entry with the same `ModuleTag` name as the base object will cause a duplicate module tag error, as ObjectReskin does not support automatic module replacement like ObjectExtend.

**Dependencies**:
- Requires proper armor and damage type definitions to function correctly. HighlanderBody relies on armor systems to modify incoming damage before it is applied to health. The unresistable damage type must be properly defined for the death mechanism to work.

## Template

```ini
Body = HighlanderBody ModuleTag_XX
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

- HighlanderBody objects can take damage normally but cannot die from normal damage types. Health is automatically clamped to minimum 1 point for normal damage.
- Only unresistable damage can reduce health below 1 point and cause death. This creates "immortal" objects that can only be destroyed by special weapons or abilities.
- All damage calculations, armor, and status effects work normally. Objects still show damage states ([BodyDamageType Values](#bodydamagetype-values)) and visual effects even though they cannot die from normal damage.
- Useful for creating hero units, special objectives, or indestructible objects that require special weapons to destroy.
- The name references the "Highlander" concept of near-immortality ("there can be only one").
- Components can be added to HighlanderBody for detailed damage modeling (GMX Zero Hour only). See [Component documentation](ObjectComponents/Component.md) and individual component documentation files for component-specific notes and details.

## Modder Recommended Use Scenarios

(pending modder review)

## Source Files

**Base Class:** [ActiveBody](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ActiveBody.h) (GMX Zero Hour), [ActiveBody](../../Generals/Code/GameEngine/Include/GameLogic/Module/ActiveBody.h) (GMX Generals)

- Header (GMX Zero Hour): [HighlanderBody.h](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/HighlanderBody.h)
- Source (GMX Zero Hour): [HighlanderBody.cpp](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Body/HighlanderBody.cpp)
- Header (GMX Generals): [HighlanderBody.h](../../Generals/Code/GameEngine/Include/GameLogic/Module/HighlanderBody.h)
- Source (GMX Generals): [HighlanderBody.cpp](../../Generals/Code/GameEngine/Source/GameLogic/Object/Body/HighlanderBody.cpp)

## Changes History

- GMX Zero Hour — Adds Electronic Warfare (Jamming) options and component system support to HighlanderBody.

## Document Log

- 16/12/2025 — AI — Initial document created.

## Status

- Documentation Status: AI-generated
- Last Updated: 16/12/2025 by AI
- Certification: 0/2 reviews

### Reviewers

- (pending)