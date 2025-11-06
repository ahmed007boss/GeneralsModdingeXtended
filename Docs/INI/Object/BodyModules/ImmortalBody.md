# ImmortalBody

Status: AI-generated, 0/2 reviews

## Overview

The `ImmortalBody` module is a specialized body module that prevents objects from ever dying by ensuring their health never drops below 1 point. Unlike HighlanderBody which allows death from unresistable damage, ImmortalBody prevents all death regardless of damage type. Objects can still take damage and show damage states, but they can never be destroyed through health loss. This is a module added inside `Object` entries.

Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
  - [Limitations](#limitations)
  - [Conditions](#conditions)
  - [Dependencies](#dependencies)
- [Properties](#properties)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Modder Recommended Use Scenarios](#modder-recommended-use-scenarios)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Document Log](#document-log)
- [Status](#status)
- [Reviewers](#reviewers)

## Usage

Place under `Body = ImmortalBody ModuleTag_XX` inside `Object` entries. In GMX, ImmortalBody can also be added to `ObjectExtend` entries. See [Template](#template) for correct syntax.

**Placement**:
- **Retail**: ImmortalBody can only be added to `Object` entries.
- **GMX**: ImmortalBody can be added to both `Object` and `ObjectExtend` entries.

Only one body module (ActiveBody, ImmortalBody, StructureBody, etc.) can exist per object. If multiple body modules are added to the same object, the game will crash with a "Duplicate bodies" assertion error during object creation. This restriction applies regardless of `ModuleTag` names - the object can only have one body module total.

**Limitations**:
- Health is automatically clamped to minimum 1 point - objects can never die from any type of damage, regardless of how much damage is dealt.
- Objects can still take damage normally and show damage states ([BodyDamageType Values](#bodydamagetype-values)) based on health percentage thresholds defined in [GameData](../GameData.md). Damage states affect visual appearance and particle systems.
- If [InitialHealth](#initialhealth) exceeds [MaxHealth](#maxhealth), the health will be clamped to [MaxHealth](#maxhealth) during health operations. Health cannot go below `1.0` or above [MaxHealth](#maxhealth).
- [SubdualDamageCap](#subdualdamagecap) can disable objects without destroying them when subdual damage equals or exceeds [MaxHealth](#maxhealth). Subdual damage properties are available only in Zero Hour.

**Conditions**:
- Objects with ImmortalBody can be targeted by weapons (see [Weapon documentation](../Weapon.md)) and affected by damage types. Health is reduced when weapons deal damage, but cannot fall below 1 point. Damage states are updated based on health percentage.
- Veterancy levels can modify maximum health and healing rates through the veterancy bonus system (see [GameData](../GameData.md) for veterancy health bonuses).
- ImmortalBody integrates with armor systems (see [Armor documentation](../Armor.md)) and damage effects. Armor modifies incoming damage before it is applied to health, but the final health value is clamped to minimum 1.
- Damage states are calculated based on global thresholds defined in [GameData](../GameData.md) and affect visual appearance and particle systems.

**Dependencies**:
- Requires proper armor and damage type definitions to function correctly. ImmortalBody relies on armor systems to modify incoming damage before it is applied to health.
- Inherits all properties and functionality from ActiveBody while overriding the health change system to prevent death.
- Veterancy levels can modify maximum health and healing rates through the veterancy bonus system (see [GameData](../GameData.md) for veterancy health bonuses).
- Objects with ImmortalBody can be healed by [AutoHealBehavior](../ObjectBehaviorsModules/AutoHealBehavior.md). AutoHealBehavior heals main health and, when [ComponentHealingAmount](../ObjectBehaviorsModules/AutoHealBehavior.md#componenthealingamount) is set (GMX Zero Hour only), can also heal components. Component healing respects each component's [HealingType](ObjectComponents/Component.md#healingtype) setting. Even though ImmortalBody prevents death, healing still increases health up to [MaxHealth](#maxhealth).
- Compatible with healing and repair systems that restore health over time.
- **ObjectExtend (GMX only)**: When ImmortalBody is added to an `ObjectExtend` entry with the same `ModuleTag` name as the base object, the base object's ImmortalBody module is automatically replaced. ObjectExtend automatically clears modules with matching `ModuleTag` names when adding new modules.
- **ObjectReskin (both Retail and GMX)**: ObjectReskin uses the same module system as Object. Adding ImmortalBody to an ObjectReskin entry with the same `ModuleTag` name as the base object will cause a duplicate module tag error, as ObjectReskin does not support automatic module replacement like ObjectExtend.

## Properties

ImmortalBody inherits all properties from ActiveBody with no additional INI-parsable properties. See [ActiveBody documentation](ActiveBody.md) for complete property list.

## Examples

### Truly Immortal Hero Unit
```ini
Body = ImmortalBody ModuleTag_01
  MaxHealth = 1000.0
  InitialHealth = 1000.0
  SubdualDamageCap = 0.0
  SubdualDamageHealRate = 0
  SubdualDamageHealAmount = 0.0
  JammingDamageCap = 0.0
  JammingDamageHealRate = 0
  JammingDamageHealAmount = 0.0
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
  JammingDamageCap = 0.0
  JammingDamageHealRate = 0
  JammingDamageHealAmount = 0.0
End
```

## Template

```ini
Body = ImmortalBody ModuleTag_XX
  ; Inherits all ActiveBody properties
  MaxHealth = 100.0                  ; // maximum health points *(GMX, Retail 1.04)*
  InitialHealth = 100.0              ; // starting health points *(GMX, Retail 1.04)*

  ; Subdual Damage Settings (GMX Generals, GMX Zero Hour, Retail Zero Hour 1.04)
  SubdualDamageCap = 0.0             ; // maximum subdual damage before subdual *(GMX Zero Hour, Retail Zero Hour 1.04)*
  SubdualDamageHealRate = 0          ; // milliseconds between subdual damage healing *(GMX Zero Hour, Retail Zero Hour 1.04)*
  SubdualDamageHealAmount = 0.0      ; // amount of subdual damage healed per interval *(GMX Zero Hour, Retail Zero Hour 1.04)*

  ; Electronic Warfare Settings (GMX Zero Hour only)
  JammingDamageCap = 0.0                  ; // maximum jamming damage before jamming *(GMX Zero Hour only)*
  JammingDamageHealRate = 0               ; // milliseconds between jamming damage healing *(GMX Zero Hour only)*
  JammingDamageHealAmount = 0.0           ; // amount of jamming damage healed per interval *(GMX Zero Hour only)*
  CanBeJammedByDirectJammers = No        ; // whether object can be jammed by direct jammers *(GMX Zero Hour only)*
  CanBeJammedByAreaJammers = No          ; // whether object can be jammed by area jammers *(GMX Zero Hour only)*
End
```

## Notes

- Damage states are updated automatically when [MaxHealth](#maxhealth) changes. ImmortalBody uses the same damage state system as ActiveBody (see [ActiveBody documentation](ActiveBody.md#bodydamagetype-values) for complete damage state enum values).
- Health is automatically clamped to minimum 1 point for all damage types. Objects can take damage normally but cannot die from it, regardless of how much damage is dealt.
- All damage calculations, armor, and status effects work normally. Objects still show damage states and visual effects based on health percentage.
- Subdual damage types that affect this system: `SUBDUAL_MISSILE`, `SUBDUAL_VEHICLE`, `SUBDUAL_BUILDING`, and `SUBDUAL_UNRESISTABLE` (see [DamageType documentation](../DamageType.md)).
- Jamming damage types that affect this system: `ELECTRONIC_JAMMING` and `JAMMING_UNRESISTABLE` (see [DamageType documentation](../DamageType.md)).

## Modder Recommended Use Scenarios

- ImmortalBody is commonly used by neutral objects such as SupplyDock and SupplyPileSmall.

## Source Files

**Base Class:** [ActiveBody](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ActiveBody.h) (GMX Zero Hour), [ActiveBody](../../Generals/Code/GameEngine/Include/GameLogic/Module/ActiveBody.h) (GMX Generals)

- Header (GMX Zero Hour): [ImmortalBody.h](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ImmortalBody.h)
- Source (GMX Zero Hour): [ImmortalBody.cpp](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Body/ImmortalBody.cpp)
- Header (GMX Generals): [ImmortalBody.h](../../Generals/Code/GameEngine/Include/GameLogic/Module/ImmortalBody.h)
- Source (GMX Generals): [ImmortalBody.cpp](../../Generals/Code/GameEngine/Source/GameLogic/Object/Body/ImmortalBody.cpp)

## Changes History

- GMX Zero Hour — Inherits Electronic Warfare (Jamming) system and component system from ActiveBody.

## Document Log

- 16/12/2025 — AI — Initial document created.

## Status

- Documentation Status: AI-generated
- Last Updated: 16/12/2025 by AI
- Certification: 0/2 reviews

### Reviewers

- (pending)