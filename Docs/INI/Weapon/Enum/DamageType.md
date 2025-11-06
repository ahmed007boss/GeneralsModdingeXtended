# DamageType

Status: AI-generated, 0/2 reviews

## Overview

`DamageType` is an enum that defines the different types of damage that can be dealt to objects in the game. Damage types are used to determine how damage interacts with armor, what visual and audio effects are played, and what special behaviors are triggered. Different damage types can have different effectiveness against different armor types, and some damage types have special mechanics (e.g., subdual damage, jamming damage, status damage).

Damage types are used throughout the game for:
- **Weapon damage**: Weapons specify their damage type to determine how they interact with targets
- **Armor resistance**: Armor types can have different resistances to different damage types
- **Visual effects**: Different damage types trigger different visual and audio effects
- **Special mechanics**: Some damage types have special behaviors (e.g., subdual damage disables without killing, jamming damage jams electronics, status damage applies status conditions)

**For modders**: In INI files, you specify the damage type for weapons using the `DamageType` property. Damage types interact with armor types defined in [Armor](../Armor.md) templates to determine final damage amounts. Some damage types have special mechanics that affect how they interact with objects.

Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Enum Value Lists](#enum-value-lists)
  - [Standard Damage Types](#standard-damage-types)
  - [Special Damage Types](#special-damage-types)
  - [Subdual Damage Types](#subdual-damage-types)
  - [Electronic Warfare Damage Types](#electronic-warfare-damage-types)
  - [Generic Damage Types](#generic-damage-types)
- [Examples](#examples)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Document Log](#document-log)
- [Status](#status)
- [Reviewers](#reviewers)

## Usage

**Limitations**:
- Damage types are assigned to weapons in the [Weapon](../Weapon.md) template using the `DamageType` property.
- Damage types interact with armor types to determine final damage amounts through damage multipliers.
- Some damage types have special mechanics that bypass normal health damage (e.g., subdual damage, jamming damage, status damage).
- Damage types are used by visual effect systems to determine which effects to play when damage is dealt.

**Conditions**:
- Damage types are specified in weapon templates to define how weapons deal damage.
- Armor templates define resistance multipliers for each damage type.
- Some damage types have special behaviors that trigger when they are dealt (e.g., `DAMAGE_SURRENDER` causes units to surrender instead of die).
- Damage types can be combined in damage type flags for systems that need to check for multiple damage types.

**Dependencies**:
- Damage types are used by [Weapon](../Weapon.md) templates to define weapon damage characteristics.
- Damage types interact with [Armor](../Armor.md) templates to determine damage multipliers.
- Some damage types require specific body modules or behaviors to function (e.g., subdual damage requires body modules that support subdual mechanics).

## Enum Value Lists

### DamageType Values

Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

### Standard Damage Types

- **`DAMAGE_EXPLOSION`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Explosive damage. Standard explosive damage type used by most explosive weapons like grenades, rockets, and bombs. Used for weapons that deal damage through explosive force. Typically effective against structures and vehicles.

- **`DAMAGE_CRUSH`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Crush damage. Damage type used when objects are crushed by heavier units or objects. Used for vehicles running over lighter units or objects. Typically very effective against infantry and light vehicles.

- **`DAMAGE_ARMOR_PIERCING`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Armor-piercing damage. Damage type designed to penetrate armor. Used by anti-tank weapons and armor-piercing rounds. Typically very effective against heavily armored targets.

- **`DAMAGE_SMALL_ARMS`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Small arms damage. Damage type used by small firearms like pistols and rifles. Used for infantry weapons and light firearms. Typically effective against infantry and light targets.

- **`DAMAGE_GATTLING`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Gatling gun damage. Damage type used by rapid-fire weapons like gatling guns and miniguns. Used for high-rate-of-fire weapons. Typically effective against infantry and light vehicles.

- **`DAMAGE_RADIATION`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Radiation damage. Damage type used by radiation-based weapons. Used for weapons that deal damage through radiation exposure. May have special effects on certain unit types.

- **`DAMAGE_FLAME`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Flame damage. Damage type used by flamethrowers and fire-based weapons. Used for weapons that deal damage through fire. Can set objects on fire and cause burning effects.

- **`DAMAGE_LASER`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Laser damage. Damage type used by laser weapons. Used for precision energy weapons. Typically very accurate and effective against various targets.

- **`DAMAGE_SNIPER`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Sniper damage. Damage type used by sniper rifles. Used for long-range precision weapons. Typically very effective against infantry and can kill pilots in vehicles.

- **`DAMAGE_POISON`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Poison damage. Damage type used by poison-based weapons. Used for weapons that deal damage through toxic effects. May have special effects on biological targets.

- **`DAMAGE_HEALING`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Healing damage (negative damage). Special damage type that heals instead of damages. Used by healing systems to restore health. Negative damage values heal the target.

- **`DAMAGE_UNRESISTABLE`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Unresistable damage. Damage type that bypasses all armor resistances. Used for scripting to cause 'armorproof' damage. This damage type ignores all armor multipliers and deals full damage.

- **`DAMAGE_WATER`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Water damage. Damage type used by water-based attacks. Used for weapons that deal damage through water or flooding. May have special effects on certain unit types.

- **`DAMAGE_DEPLOY`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Deploy damage. Special damage type for transports to deploy units and order them to all attack. Used by transport systems to deploy passengers. Does not deal actual damage but triggers deployment behavior.

- **`DAMAGE_SURRENDER`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Surrender damage. If something "dies" to surrender damage, they surrender instead of being destroyed. Used by surrender systems to force units to surrender. Units with the `CAN_SURRENDER` KindOf flag will surrender instead of die when killed by this damage type.

- **`DAMAGE_HACK`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Hack damage. Damage type used by hacking attacks. Used for weapons that hack or disable electronic systems. May have special effects on electronic targets.

- **`DAMAGE_KILLPILOT`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Kill pilot damage. Special snipe attack that kills the pilot and renders a vehicle unmanned. Used by sniper weapons to kill vehicle pilots. Vehicles affected by this damage type become unmanned and can be hijacked.

- **`DAMAGE_PENALTY`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Penalty damage. Damage from game penalty (you won't receive radar warnings BTW). Used by penalty systems to deal damage as a penalty. Does not trigger radar warnings.

- **`DAMAGE_FALLING`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Falling damage. Damage type used when objects fall from heights. Used by physics systems when objects take fall damage. Typically results in `DEATH_SPLATTED` death type.

- **`DAMAGE_MELEE`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Melee damage. Blades, clubs, and other melee weapons. Used for close-combat weapons. Typically effective against infantry.

- **`DAMAGE_DISARM`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Disarm damage. "Special" damage type used for disarming mines, bombs, etc. (NOT for "disarming" an opponent!). Used by mine clearing systems to disarm explosive devices. Does not deal health damage but disarms explosive objects.

- **`DAMAGE_HAZARD_CLEANUP`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Hazard cleanup damage. Special damage type for cleaning up hazards like radiation or bio-poison. Used by cleanup systems to remove environmental hazards. Does not deal health damage but removes hazard effects.

- **`DAMAGE_PARTICLE_BEAM`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Particle beam damage. Incinerates virtually everything (insanely powerful orbital beam). Used by superweapon systems. Extremely powerful damage type that can destroy almost anything.

- **`DAMAGE_TOPPLING`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Toppling damage. Damage from getting toppled. Used by topple systems when structures fall over. Results in toppled state rather than destruction.

- **`DAMAGE_INFANTRY_MISSILE`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Infantry missile damage. Damage type used by infantry-carried missile weapons. Used for portable missile launchers. Typically effective against vehicles and structures.

- **`DAMAGE_AURORA_BOMB`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Aurora bomb damage. Damage type used by Aurora bomber weapons. Used for specialized bomber weapons. Typically very effective against structures.

- **`DAMAGE_LAND_MINE`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Land mine damage. Damage type used by land mines. Used for explosive traps. Typically very effective against vehicles and infantry.

- **`DAMAGE_JET_MISSILES`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Jet missile damage. Damage type used by jet aircraft missiles. Used for air-to-ground and air-to-air missiles from jet aircraft. Typically effective against various targets.

- **`DAMAGE_STEALTHJET_MISSILES`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Stealth jet missile damage. Damage type used by stealth jet aircraft missiles. Used for specialized stealth aircraft weapons. Typically effective against various targets.

- **`DAMAGE_MOLOTOV_COCKTAIL`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Molotov cocktail damage. Damage type used by molotov cocktail weapons. Used for incendiary thrown weapons. Sets targets on fire.

- **`DAMAGE_COMANCHE_VULCAN`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Comanche Vulcan damage. Damage type used by Comanche helicopter Vulcan cannon. Used for specialized helicopter weapons. Typically very effective against infantry and light vehicles.

### Special Damage Types

- **`DAMAGE_MICROWAVE`** *(GMX Generals, GMX Zero Hour only)* - Microwave damage. Radiation that only affects infantry. Used by microwave weapons that specifically target infantry. Only deals damage to infantry units, vehicles are immune.

- **`DAMAGE_KILL_GARRISONED`** *(GMX Generals, GMX Zero Hour only)* - Kill garrisoned damage. Kills passengers up to the number specified in Damage. Used by weapons that can kill garrisoned units inside structures. Does not damage the structure itself but kills garrisoned units.

- **`DAMAGE_STATUS`** *(GMX Generals, GMX Zero Hour only)* - Status damage. Damage that gives a status condition, not hitpoint damage. Used by weapons that apply status effects instead of health damage. Does not reduce health but applies status conditions to targets.

### Subdual Damage Types

- **`DAMAGE_SUBDUAL_MISSILE`** *(GMX Generals, GMX Zero Hour only)* - Subdual missile damage. Damage that does not kill you, but produces some special effect based on your Body Module. Separate HP from normal damage. Used by subdual weapons to disable targets without killing them. Does not reduce normal health but applies subdual effects.

- **`DAMAGE_SUBDUAL_VEHICLE`** *(GMX Generals, GMX Zero Hour only)* - Subdual vehicle damage. Subdual damage specifically for vehicles. Used by subdual weapons to disable vehicles without destroying them. Vehicles affected by this damage type are disabled but not destroyed.

- **`DAMAGE_SUBDUAL_BUILDING`** *(GMX Generals, GMX Zero Hour only)* - Subdual building damage. Subdual damage specifically for buildings. Used by subdual weapons to disable structures without destroying them. Structures affected by this damage type are disabled but not destroyed.

- **`DAMAGE_SUBDUAL_UNRESISTABLE`** *(GMX Generals, GMX Zero Hour only)* - Subdual unresistable damage. Subdual damage that bypasses all resistances. Used by subdual weapons that cannot be resisted. Applies subdual effects regardless of armor or resistances.

### Electronic Warfare Damage Types

- **`DAMAGE_ELECTRONIC_JAMMING`** *(GMX Generals, GMX Zero Hour only)* - Electronic jamming damage. Damage type used by electronic warfare systems to jam enemy electronics. Used by jamming weapons to disable electronic systems. Does not reduce health but applies jamming effects.

- **`DAMAGE_JAMMING_UNRESISTABLE`** *(GMX Generals, GMX Zero Hour only)* - Jamming unresistable damage. Jamming damage that bypasses all resistances. Used by jamming weapons that cannot be resisted. Applies jamming effects regardless of armor or resistances.

### Generic Damage Types

- **`DAMAGE_ACID`** *(GMX Generals, GMX Zero Hour only)* - Acid damage. Generic damage type for acid-based weapons. Used for weapons that deal damage through acid or corrosive effects. No special logic, uses standard damage mechanics.

- **`DAMAGE_JET_BOMB`** *(GMX Generals, GMX Zero Hour only)* - Jet bomb damage. Generic damage type for jet aircraft bombs. Used for specialized bomber weapons. No special logic, uses standard damage mechanics.

- **`DAMAGE_ANTI_TANK_GUN`** *(GMX Generals, GMX Zero Hour only)* - Anti-tank gun damage. Generic damage type for anti-tank gun weapons. Used for specialized anti-tank weapons. No special logic, uses standard damage mechanics.

- **`DAMAGE_ANTI_TANK_MISSILE`** *(GMX Generals, GMX Zero Hour only)* - Anti-tank missile damage. Generic damage type for anti-tank missile weapons. Used for specialized anti-tank missiles. No special logic, uses standard damage mechanics.

- **`DAMAGE_ANTI_AIR_GUN`** *(GMX Generals, GMX Zero Hour only)* - Anti-air gun damage. Generic damage type for anti-aircraft gun weapons. Used for specialized anti-aircraft weapons. No special logic, uses standard damage mechanics.

- **`DAMAGE_ANTI_AIR_MISSILE`** *(GMX Generals, GMX Zero Hour only)* - Anti-air missile damage. Generic damage type for anti-aircraft missile weapons. Used for specialized anti-aircraft missiles. No special logic, uses standard damage mechanics.

- **`DAMAGE_ARTILLERY`** *(GMX Generals, GMX Zero Hour only)* - Artillery damage. Generic damage type for artillery weapons. Used for long-range artillery weapons. No special logic, uses standard damage mechanics.

## Examples

### Basic Damage Type Usage

```ini
Weapon = TankCannon WeaponSlot_PRIMARY
  DamageType = ARMOR_PIERCING
  Damage = 150
  Range = 200
End
```

In this example, the weapon uses `ARMOR_PIERCING` damage type, which is effective against armored targets.

### Special Damage Type Usage

```ini
Weapon = SubdualMissile WeaponSlot_PRIMARY
  DamageType = SUBDUAL_MISSILE
  Damage = 100
  Range = 300
End
```

In this GMX example, the weapon uses `SUBDUAL_MISSILE` damage type, which disables targets without killing them.

## Notes

- **Damage Type and Armor Interaction**: Damage types interact with armor types through damage multipliers defined in [Armor](../Armor.md) templates. The final damage is calculated as: `finalDamage = baseDamage * armorMultiplier[damageType]`.

- **Special Damage Types**: Some damage types have special mechanics that bypass normal health damage:
  - **Subdual damage types** (`DAMAGE_SUBDUAL_*`): Do not reduce normal health but apply subdual effects
  - **Jamming damage types** (`DAMAGE_ELECTRONIC_JAMMING`, `DAMAGE_JAMMING_UNRESISTABLE`): Do not reduce health but apply jamming effects
  - **Status damage** (`DAMAGE_STATUS`): Does not reduce health but applies status conditions
  - **Deploy damage** (`DAMAGE_DEPLOY`): Does not deal damage but triggers deployment behavior
  - **Disarm damage** (`DAMAGE_DISARM`): Does not deal health damage but disarms explosive devices

- **Health Damaging Damage Types**: The function `IsHealthDamagingDamage()` determines which damage types actually reduce health. Damage types that do not reduce health include: `DAMAGE_STATUS`, `DAMAGE_SUBDUAL_*`, `DAMAGE_KILLPILOT`, `DAMAGE_KILL_GARRISONED`, `DAMAGE_ELECTRONIC_JAMMING`, and `DAMAGE_JAMMING_UNRESISTABLE`.

- **Subdual Damage**: Subdual damage types are checked by the `IsSubdualDamage()` function. Subdual damage does not reduce normal health but applies special effects based on the target's body module.

- **Jamming Damage**: Jamming damage types are checked by the `IsJammingDamage()` function. Jamming damage does not reduce health but applies electronic jamming effects.

- **Damage Type Flags**: Damage types can be combined in `DamageTypeFlags` (bit flags) for systems that need to check for multiple damage types simultaneously.

## Source Files

**Header (Generals):** [Damage.h](../../../../Generals/Code/GameEngine/Include/GameLogic/Damage.h)
- `DamageType` enum definition (lines 43-97): Defines all available damage types for Retail Generals

**Header (Zero Hour):** [Damage.h](../../../../GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h)
- `DamageType` enum definition (lines 48-99): Defines all available damage types for GMX Zero Hour

**Source (Generals):** [Damage.cpp](../../../../Generals/Code/GameEngine/Source/GameLogic/Damage.cpp)
- Damage type name mapping: Maps damage type names to their values for INI file parsing

**Source (Zero Hour):** [Damage.cpp](../../../../GeneralsMD/Code/GameEngine/Source/GameLogic/Damage.cpp)
- Damage type name mapping: Maps damage type names to their values for INI file parsing

## Changes History

### Retail Generals 1.04 → Retail Zero Hour 1.04

- In Retail Zero Hour, 1 new damage type was added: `DAMAGE_FLESHY_SNIPER` (like `DAMAGE_SNIPER`, but generally does no damage to vehicles).

### Retail Zero Hour 1.04 → GMX Zero Hour

- In GMX Zero Hour, 16 new damage types were added including 4 subdual damage types, 2 electronic warfare damage types, 1 special damage type (`DAMAGE_MICROWAVE`), 1 status damage type, 1 kill garrisoned damage type, and 7 generic damage types.

### Retail Generals 1.04 → GMX Generals

- In GMX Generals, 16 new damage types were added including 4 subdual damage types, 2 electronic warfare damage types, 1 special damage type (`DAMAGE_MICROWAVE`), 1 status damage type, 1 kill garrisoned damage type, and 7 generic damage types.

## Document Log

- 16/12/2025 — AI — Initial document created.

## Status

AI-generated, 0/2 reviews

## Reviewers

- [ ] Reviewer 1
- [ ] Reviewer 2

