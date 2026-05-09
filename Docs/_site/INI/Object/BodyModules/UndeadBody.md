# UndeadBody

Status: AI-generated, 0/2 reviews

## Overview

The `UndeadBody` module extends ActiveBody with a "second life" mechanic that intercepts the first death and grants the object a second life instead of dying. When the object would normally die from health-damaging damage, it instead survives with 1 health point, then immediately transitions to its second life with new maximum health, fully healed, and a different armor set. This creates a "zombie" or "undead" effect where objects appear to die but continue fighting. The second death is permanent and cannot be prevented. UndeadBody manages health, damage states, healing, subdual damage, and visual damage effects like ActiveBody, but adds the second life transition mechanic. This is a module added inside `Object` entries.

Available in: *(GMX Zero Hour, Retail Zero Hour 1.04)*

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

Place under `Body = UndeadBody ModuleTag_XX` inside `Object` entries. In GMX, UndeadBody can also be added to `ObjectExtend` entries. See [Template](#template) for correct syntax.

**Placement**:
- **Retail**: UndeadBody can only be added to `Object` entries.
- **GMX**: UndeadBody can be added to both `Object` and `ObjectExtend` entries.

Only one body module (ActiveBody, InactiveBody, StructureBody, UndeadBody, etc.) can exist per object. If multiple body modules are added to the same object, the game will crash with a "Duplicate bodies" assertion error during object creation. This restriction applies regardless of `ModuleTag` names - the object can only have one body module total.

**Limitations**:
- UndeadBody automatically manages damage states ([BodyDamageType Values](#bodydamagetype-values)) based on health percentage thresholds defined in [GameData](../GameData.md). Damage states affect visual appearance and particle systems.
- The second life mechanic only works once per object lifetime. After the first death is intercepted, the object enters its second life and cannot use the mechanic again.
- The second death is permanent and cannot be prevented. Once in second life, the object will die normally when health reaches 0.
- Unresistable damage (`DAMAGE_UNRESISTABLE`) bypasses the second life mechanic entirely and causes immediate death, even on the first life.
- Requires SlowDeathBehavior module to function properly. The game will crash with an assertion if UndeadBody is used without SlowDeathBehavior: `"Hmm, this is wrong"`.
- If [InitialHealth](#initialhealth) exceeds [MaxHealth](#maxhealth), the health will be clamped to [MaxHealth](#maxhealth) during health operations. Health cannot go below `0.0` or above [MaxHealth](#maxhealth) during first life.
- [SubdualDamageCap](#subdualdamagecap) can disable objects without destroying them when subdual damage equals or exceeds [MaxHealth](#maxhealth). Subdual damage properties are available only in Zero Hour.

**Conditions**:
- Objects with UndeadBody can be targeted by weapons (see [Weapon documentation](../Weapon.md)) and affected by damage types. Health is reduced when weapons deal damage, and damage states are updated based on health percentage thresholds (see [BodyDamageType Values](#bodydamagetype-values) for percentage ranges).
- Veterancy levels can modify maximum health and healing rates through the veterancy bonus system (see [GameData](../GameData.md) for veterancy health bonuses). Veterancy bonuses apply to both first and second life.
- **Second life activation**: When the object would die from health-damaging damage (excluding unresistable damage), the death is intercepted. The damage amount is clamped to leave exactly 1 health point, then the object transitions to second life. The transition occurs after damage is applied but before death modules are processed, allowing damage effects to play normally.
- **Second life transition**: When second life activates, the object:
  - Sets maximum health to [SecondLifeMaxHealth](#secondlifemaxhealth) and fully heals to the new maximum.
  - Sets armor set flag to `ARMORSET_SECOND_LIFE`, allowing different damage resistance for second life.
  - Triggers SlowDeathBehavior module to play death animations and effects without actually dying.
  - Sets `MODELCONDITION_SECOND_LIFE` model condition for visual effects.
  - Marks the object as in second life, preventing further second life activations.
- **Second life behavior**: Once in second life, the object behaves like a normal ActiveBody object. It can take damage, be healed, and die normally. The second death is permanent and cannot be prevented.
- **Unresistable damage bypass**: Unresistable damage (`DAMAGE_UNRESISTABLE`) bypasses the second life mechanic entirely. If unresistable damage would kill the object, it dies immediately regardless of whether it's on first or second life.
- UndeadBody integrates with armor systems (see [Armor documentation](../Armor.md)) and damage effects. Armor modifies incoming damage before it is applied to health. Second life uses `ARMORSET_SECOND_LIFE` armor set for different damage resistance.
- Damage states are calculated based on global thresholds defined in [GameData](../GameData.md) and affect visual appearance and particle systems.
- **SlowDeathBehavior requirement**: UndeadBody requires at least one SlowDeathBehavior module to function. When second life activates, UndeadBody selects a SlowDeathBehavior module using probability modifiers and triggers it. The SlowDeathBehavior plays death animations and effects without actually killing the object.

**Dependencies**:
- Requires proper armor and damage type definitions to function correctly. UndeadBody relies on armor systems to modify incoming damage before it is applied to health. Second life uses `ARMORSET_SECOND_LIFE` armor set.
- Requires SlowDeathBehavior module to function properly. UndeadBody triggers SlowDeathBehavior when second life activates to play death animations and effects.
- Inherits all properties and functionality from ActiveBody.
- Objects with UndeadBody can be healed by [AutoHealBehavior](../ObjectBehaviorsModules/AutoHealBehavior.md). AutoHealBehavior heals main health for both first life and second life. When an object transitions to second life, AutoHealBehavior continues to work normally using the new [SecondLifeMaxHealth](#secondlifemaxhealth) value. When [ComponentHealingAmount](../ObjectBehaviorsModules/AutoHealBehavior.md#componenthealingamount) is set (GMX Zero Hour only), AutoHealBehavior can also heal components in both first and second life. Component healing respects each component's [HealingType](ObjectComponents/Component.md#healingtype) setting.
- **ObjectExtend (GMX only)**: When UndeadBody is added to an `ObjectExtend` entry with the same `ModuleTag` name as the base object, the base object's UndeadBody module is automatically replaced. ObjectExtend automatically clears modules with matching `ModuleTag` names when adding new modules.
- **ObjectReskin (both Retail and GMX)**: ObjectReskin uses the same module system as Object. Adding UndeadBody to an ObjectReskin entry with the same `ModuleTag` name as the base object will cause a duplicate module tag error, as ObjectReskin does not support automatic module replacement like ObjectExtend.

## Properties

### Second Life Settings

#### `SecondLifeMaxHealth`
Available in: *(GMX Zero Hour, Retail Zero Hour 1.04)*
- **Type**: `Real`
- **Description**: Maximum health points for the object's second life. When the object "dies" the first time, it transitions to this new maximum health. Higher values make the second life more durable. When set to 1 (default), the second life is very fragile
- **Default**: `1.0`
- **Example**: `SecondLifeMaxHealth = 50.0`

## Examples

### Zombie Infantry Unit
```ini
Body = UndeadBody ModuleTag_01
  ; First Life Settings
  MaxHealth = 100.0
  InitialHealth = 100.0
  
  ; Second Life Settings
  SecondLifeMaxHealth = 50.0
  
  ; Subdual Damage Settings (Generals Zero Hour only)
  SubdualDamageCap = 0.0
  SubdualDamageHealRate = 0
  SubdualDamageHealAmount = 0.0
  
  ; Electronic Warfare Settings (Generals Zero Hour only)
  JammingDamageCap = 0.0
  JammingDamageHealRate = 0
  JammingDamageHealAmount = 0.0
End

Behavior = SlowDeathBehavior ModuleTag_02
  DeathTypes = NORMAL
  MinDamage = 0.0
  MaxDamage = 1000.0
  Probability = 100
  ; ... other SlowDeathBehavior properties
End
```

### Undead Vehicle
```ini
Body = UndeadBody ModuleTag_03
  ; First Life Settings
  MaxHealth = 500.0
  InitialHealth = 500.0
  
  ; Second Life Settings
  SecondLifeMaxHealth = 200.0
  
  ; Subdual Damage Settings (Generals Zero Hour only)
  SubdualDamageCap = 0.0
  SubdualDamageHealRate = 0
  SubdualDamageHealAmount = 0.0
  
  ; Electronic Warfare Settings (Generals Zero Hour only)
  JammingDamageCap = 0.0
  JammingDamageHealRate = 0
  JammingDamageHealAmount = 0.0
End
```

## Template

```ini
Body = UndeadBody ModuleTag_XX
  ; First Life Settings (inherited from ActiveBody)
  MaxHealth = 100.0                  ; // maximum health points *(GMX Zero Hour, Retail Zero Hour 1.04)*
  InitialHealth = 100.0              ; // starting health points *(GMX Zero Hour, Retail Zero Hour 1.04)*

  ; Subdual Damage Settings (GMX Zero Hour, Retail Zero Hour 1.04)
  SubdualDamageCap = 0.0             ; // maximum subdual damage before subdual *(GMX Zero Hour, Retail Zero Hour 1.04)*
  SubdualDamageHealRate = 0          ; // milliseconds between subdual damage healing *(GMX Zero Hour, Retail Zero Hour 1.04)*
  SubdualDamageHealAmount = 0.0      ; // amount of subdual damage healed per interval *(GMX Zero Hour, Retail Zero Hour 1.04)*

  ; Electronic Warfare Settings (GMX Zero Hour only)
  JammingDamageCap = 0.0                  ; // maximum jamming damage before jamming *(GMX Zero Hour only)*
  JammingDamageHealRate = 0               ; // milliseconds between jamming damage healing *(GMX Zero Hour only)*
  JammingDamageHealAmount = 0.0           ; // amount of jamming damage healed per interval *(GMX Zero Hour only)*
  CanBeJammedByDirectJammers = No        ; // whether object can be jammed by direct jammers *(GMX Zero Hour only)*
  CanBeJammedByAreaJammers = No          ; // whether object can be jammed by area jammers *(GMX Zero Hour only)*

  ; Second Life Settings
  SecondLifeMaxHealth = 1.0          ; // maximum health for second life *(GMX Zero Hour, Retail Zero Hour 1.04)*
End
```

## Notes

- Damage states are updated automatically when [MaxHealth](#maxhealth) changes. UndeadBody uses the same damage state system as ActiveBody (see [ActiveBody documentation](ActiveBody.md#bodydamagetype-values) for complete damage state enum values).
- UndeadBody provides a "second life" mechanic where objects survive their first death. When the object would die, it instead transitions to second life with new maximum health, fully healed, and the `ARMORSET_SECOND_LIFE` armor set for different damage resistance.
- Requires SlowDeathBehavior module to properly trigger the second life transition. The game will crash with an assertion if UndeadBody is used without SlowDeathBehavior.
- Unresistable damage (`DAMAGE_UNRESISTABLE`) bypasses the second life mechanic entirely and causes immediate death, even on the first life.
- Second death is permanent and cannot be prevented. Once in second life, the object behaves like a normal ActiveBody object and will die normally when health reaches 0.
- Subdual damage types that affect this system: `SUBDUAL_MISSILE`, `SUBDUAL_VEHICLE`, `SUBDUAL_BUILDING`, and `SUBDUAL_UNRESISTABLE` (see [DamageType documentation](../DamageType.md)).
- Jamming damage types that affect this system: `ELECTRONIC_JAMMING` and `JAMMING_UNRESISTABLE` (see [DamageType documentation](../DamageType.md)).

## Modder Recommended Use Scenarios

- UndeadBody is used by objects such as Battle Bus.

## Source Files

**Base Class:** [ActiveBody](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ActiveBody.h) (GMX Zero Hour)

- Header (GMX Zero Hour): [UndeadBody.h](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UndeadBody.h)
- Source (GMX Zero Hour): [UndeadBody.cpp](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Body/UndeadBody.cpp)

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