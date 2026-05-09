# ObjectStatusTypes

Status: AI-generated, 0/2 reviews

## Overview

`ObjectStatusTypes` is a bit flag system used to represent various states and conditions of objects in the game. Object status flags are stackable, meaning multiple status flags can be active on an object simultaneously. These flags are used throughout the game to track object states, control behavior, enable/disable capabilities, and manage special conditions.

Object status flags are used for many purposes:
- **State tracking**: Track object states like destroyed, under construction, on fire, etc.
- **Behavior control**: Enable or disable object capabilities (e.g., `CAN_ATTACK`, `NO_ATTACK`, `UNSELECTABLE`)
- **Special conditions**: Track special states like stealth, disguise, hijacked, etc.
- **Combat states**: Track combat-related states like firing weapons, attacking, aiming
- **Movement states**: Track movement-related states like braking, immobile, etc.

**For modders**: Object status flags are set automatically by game systems based on object state and behavior. They are not directly set in INI files, but they can be referenced in various game systems and modules. Some modules allow you to require or forbid specific status flags for certain behaviors.

Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Enum Value Lists](#enum-value-lists)
  - [Basic States](#basic-states)
  - [Combat and Attack States](#combat-and-attack-states)
  - [Construction and Repair States](#construction-and-repair-states)
  - [Stealth and Detection States](#stealth-and-detection-states)
  - [Special Conditions](#special-conditions)
  - [Movement and Physics States](#movement-and-physics-states)
  - [Rider States](#rider-states)
  - [Locking States](#locking-states)
- [Examples](#examples)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Document Log](#document-log)
- [Status](#status)
- [Reviewers](#reviewers)

## Usage

**Limitations**:
- Object status flags are bit flags that can be combined. Multiple flags can be set on a single object simultaneously.
- Object status flags are set automatically by game systems based on object state, behavior, and conditions.
- Some object status flags are mutually exclusive or have specific activation conditions.
- Object status flags are used internally by the game engine; they are not directly set in INI files but can be referenced in module configurations.

**Conditions**:
- Object status flags are set automatically by game systems based on object state (e.g., construction, combat, movement, special abilities).
- Multiple object status flags can be active simultaneously (e.g., `STEALTHED` and `DETECTED` can both be active).
- Some modules allow you to require or forbid specific status flags for certain behaviors (e.g., `StealthUpdate`, `AdvancedCollide`).
- Object status flags are saved in game state and persist across save/load operations.

**Dependencies**:
- Object status flags are used by various game systems to control object behavior and state.
- Some modules reference object status flags to enable or disable behaviors (e.g., `StealthUpdate` uses `CAN_STEALTH`, `STEALTHED`, `DETECTED`).
- Object status flags can be checked by weapon systems, AI systems, and other game logic to determine object capabilities and states.

## Enum Value Lists

### ObjectStatusTypes Values

Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

### Basic States

- **`OBJECT_STATUS_NONE`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - No status bit. This is the default/empty status flag. Used to indicate no special status is set.

- **`OBJECT_STATUS_DESTROYED`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Object has been destroyed, pending delete. Set automatically when an object is destroyed. Used to mark objects that are in the process of being removed from the game. Objects with this flag are typically pending deletion and should not be interacted with.

- **`OBJECT_STATUS_UNDER_CONSTRUCTION`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Object is being constructed and is not yet complete. Set automatically by construction systems when a structure is being built. Used to indicate structures that are currently under construction. Objects with this flag are not yet fully functional.

### Combat and Attack States

- **`OBJECT_STATUS_CAN_ATTACK`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Object can attack. Used by garrisoned buildings - this flag is OR'ed with `KINDOF_CAN_ATTACK` in `isAbleToAttack()`. Allows garrisoned structures to attack even if they don't have the `CAN_ATTACK` KindOf flag. Used to enable attack capability for objects that normally cannot attack.

- **`OBJECT_STATUS_NO_ATTACK`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Absolute override to being able to attack. When set, the object cannot attack regardless of other flags or capabilities. Used to completely disable attack capability for objects.

- **`OBJECT_STATUS_IS_FIRING_WEAPON`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Object is firing a weapon, now. Not true for special attacks. Set automatically by weapon systems when a weapon is actively firing. Used to track when objects are in the process of firing weapons. Note: This does not apply to special attacks, only regular weapon fire.

- **`OBJECT_STATUS_IS_ATTACKING`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Object is in the general Attack state (including aim, approach, etc.). Note that `IS_FIRING_WEAPON` and `IS_AIMING_WEAPON` are subsets of this! Set automatically by AI systems when objects are in attack mode. Used to track when objects are actively engaging targets, including aiming and approaching phases.

- **`OBJECT_STATUS_IS_AIMING_WEAPON`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Object is aiming a weapon, now. Not true for special attacks. Set automatically by weapon systems when a weapon is being aimed at a target. Used to track when objects are in the aiming phase before firing. Note: This does not apply to special attacks, only regular weapon aiming.

- **`OBJECT_STATUS_IS_USING_ABILITY`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Object is in the process of preparing or firing a special ability. Set automatically by ability systems when objects are using special abilities. Used to track when objects are actively using special powers or abilities.

- **`OBJECT_STATUS_NO_ATTACK_FROM_AI`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Attacking this object may not be done from `commandSource == CMD_FROM_AI`. When set, AI-controlled units cannot attack this object. Used to prevent AI from targeting specific objects while still allowing player-controlled units to attack them.

- **`OBJECT_STATUS_FAERIE_FIRE`** *(GMX Generals, GMX Zero Hour only)* - Anyone shooting at you shoots faster than normal. Set automatically by special ability systems. Used to mark objects that are affected by abilities that increase attack speed against them. Objects with this flag take damage faster from all sources.

### Construction and Repair States

- **`OBJECT_STATUS_RECONSTRUCTING`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Object is reconstructing. Set automatically by reconstruction systems when objects are being rebuilt. Used to indicate objects that are in the process of being reconstructed after being destroyed or damaged.

- **`OBJECT_STATUS_UNDERGOING_REPAIR`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Object is awaiting/undergoing a repair order that has been issued. Set automatically by repair systems when objects are queued for or actively being repaired. Used to track objects that are in the repair queue or being repaired.

- **`OBJECT_STATUS_SOLD`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Object is being sold. Set automatically when a structure is sold by the player. Used to mark objects that are in the process of being sold and removed from the game.

### Stealth and Detection States

- **`OBJECT_STATUS_STEALTHED`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Object is currently "stealthed". Set automatically by `StealthUpdate` when objects enter stealth mode. Used to indicate objects that are currently invisible or hidden from enemies. Objects with this flag are not visible to enemies unless they are detected.

- **`OBJECT_STATUS_DETECTED`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Object is in range of a stealth-detector unit (meaningless if `STEALTHED` not set). Set automatically by detection systems when stealthed objects are detected by detector units. Used to indicate that a stealthed object has been detected. This flag only has meaning when combined with `STEALTHED`.

- **`OBJECT_STATUS_CAN_STEALTH`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Object has ability to stealth allowing the stealth update module to run. Set automatically by `StealthUpdate` for objects that have stealth capabilities. Used to enable the stealth update module for objects that can enter stealth mode.

- **`OBJECT_STATUS_IGNORING_STEALTH`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Temporarily ignoring all stealth bits. Used only for some special-case mine clearing stuff. Set automatically by special systems when objects need to temporarily ignore stealth mechanics. Used for special cases like mine clearing where stealth detection needs to be bypassed.

- **`OBJECT_STATUS_DISGUISED`** *(GMX Generals, GMX Zero Hour only)* - Object is disguised (a type of stealth). Set automatically by disguise systems when objects are disguised as other units. Used to indicate objects that are using disguise abilities to appear as different unit types. Disguised objects are treated as stealthed but may have different detection mechanics.

### Special Conditions

- **`OBJECT_STATUS_UNSELECTABLE`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Object cannot be selected. This is a negative condition since these statuses are overrides - their presence forces the condition, but their absence means nothing. Set automatically by various systems to prevent object selection. Used to make objects unselectable by players, typically for temporary states or special objects.

- **`OBJECT_STATUS_MASKED`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Masked objects are not selectable and targetable by players or AI. Set automatically by masking systems. Used to completely hide objects from player and AI interaction. Masked objects cannot be selected or targeted.

- **`OBJECT_STATUS_NO_COLLISIONS`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Object should be ignored for object-object collisions (but not object-ground). Used for things like collapsing parachutes that are intangible. Set automatically by physics systems for objects that should not collide with other objects. Used to make objects pass through other objects while still colliding with terrain.

- **`OBJECT_STATUS_AIRBORNE_TARGET`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - InTheAir as far as AntiAir weapons are concerned only. Set automatically by aircraft systems to mark objects that should be treated as airborne targets. Used by anti-aircraft weapons to identify valid targets. This flag is separate from actual flight state and is specifically for weapon targeting purposes.

- **`OBJECT_STATUS_PARACHUTING`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Object is on a parachute. Set automatically by parachute systems when objects are descending with parachutes. Used to track objects that are currently parachuting. Objects with this flag are typically in the air and descending.

- **`OBJECT_STATUS_REPULSOR`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Object repulses "KINDOF_CAN_BE_REPULSED" objects. Set automatically by repulsor systems. Used to mark objects that push away units with the `CAN_BE_REPULSED` KindOf flag. Objects with this flag create a repulsion field around them.

- **`OBJECT_STATUS_HIJACKED`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Unit is in the possession of an enemy criminal, call the authorities. Set automatically by hijack systems when units are hijacked. Used to mark vehicles that have been hijacked by enemy units. Hijacked units typically change ownership to the hijacker.

- **`OBJECT_STATUS_AFLAME`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - This object is on fire. Set automatically by fire systems when objects catch fire. Used to track objects that are currently burning. Objects with this flag take periodic fire damage.

- **`OBJECT_STATUS_BURNED`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - This object has already burned as much as it can. Set automatically by fire systems when objects finish burning. Used to mark objects that have been completely burned and cannot burn further.

- **`OBJECT_STATUS_WET`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Object has been soaked with water. Set automatically by water systems when objects are exposed to water. Used to track objects that have been affected by water, which may affect fire resistance or other properties.

- **`OBJECT_STATUS_IS_CARBOMB`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Object is now a carbomb. Set automatically by carbomb systems when vehicles are converted to carbombs. Used to mark vehicles that have been rigged as explosive devices. Carbomb vehicles explode when they reach their target.

- **`OBJECT_STATUS_BOOBY_TRAPPED`** *(GMX Generals, GMX Zero Hour only)* - We need to know we have a booby trap on us so we can detonate it from many different code segments. Set automatically by booby trap systems when objects are rigged with booby traps. Used to mark objects that have booby traps attached. Booby trapped objects can be detonated by various triggers.

- **`OBJECT_STATUS_DEPLOYED`** *(GMX Generals, GMX Zero Hour only)* - Object is deployed. Set automatically by deployment systems when objects enter deployed state. Used to track objects that have been deployed from their undeployed state. Deployed objects typically have different capabilities than undeployed objects.

- **`OBJECT_STATUS_MISSILE_KILLING_SELF`** *(GMX Generals, GMX Zero Hour only)* - Object (likely a missile or bomb) is *BUSTING* its way through the *BUNKER*, building or ground, awaiting death at the bottom. Set automatically by missile systems when projectiles are penetrating through structures. Used to mark projectiles that are in the process of penetrating through terrain or structures before detonating.

### Movement and Physics States

- **`OBJECT_STATUS_BRAKING`** *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)* - Object is braking, and subverts the physics. Set automatically by movement systems when objects are actively braking. Used to track when objects are slowing down. Objects with this flag may have modified physics behavior during braking.

- **`OBJECT_STATUS_IMMOBILE`** *(GMX Generals, GMX Zero Hour only)* - Do not move! Set automatically by movement systems to completely prevent object movement. Used to lock objects in place, preventing any movement regardless of other movement commands or AI behavior.

- **`OBJECT_STATUS_DECK_HEIGHT_OFFSET`** *(GMX Generals, GMX Zero Hour only)* - Object factors deck height on top of ground altitude. Set automatically by aircraft systems for aircraft that are parked on aircraft carriers or airfields. Used to adjust the height calculation for aircraft on carrier decks. Objects with this flag have their height calculated relative to the deck surface rather than ground level.

- **`OBJECT_STATUS_REASSIGN_PARKING`** *(GMX Generals, GMX Zero Hour only)* - Jet is trying to get a better parking assignment. Set automatically by aircraft AI systems when aircraft are seeking better parking positions. Used to indicate that aircraft are actively looking for improved parking spots. Cleared when aircraft find suitable parking or when parking is no longer needed.

### Rider States

- **`OBJECT_STATUS_RIDER1`** *(GMX Generals, GMX Zero Hour only)* - Object is rider 1. Set automatically by transport systems to mark objects that are passengers in multi-rider vehicles. Used to track which passenger slot an object occupies in vehicles that can carry multiple passengers.

- **`OBJECT_STATUS_RIDER2`** *(GMX Generals, GMX Zero Hour only)* - Object is rider 2. Set automatically by transport systems to mark objects that are passengers in multi-rider vehicles.

- **`OBJECT_STATUS_RIDER3`** *(GMX Generals, GMX Zero Hour only)* - Object is rider 3. Set automatically by transport systems to mark objects that are passengers in multi-rider vehicles.

- **`OBJECT_STATUS_RIDER4`** *(GMX Generals, GMX Zero Hour only)* - Object is rider 4. Set automatically by transport systems to mark objects that are passengers in multi-rider vehicles.

- **`OBJECT_STATUS_RIDER5`** *(GMX Generals, GMX Zero Hour only)* - Object is rider 5. Set automatically by transport systems to mark objects that are passengers in multi-rider vehicles.

- **`OBJECT_STATUS_RIDER6`** *(GMX Generals, GMX Zero Hour only)* - Object is rider 6. Set automatically by transport systems to mark objects that are passengers in multi-rider vehicles.

- **`OBJECT_STATUS_RIDER7`** *(GMX Generals, GMX Zero Hour only)* - Object is rider 7. Set automatically by transport systems to mark objects that are passengers in multi-rider vehicles.

- **`OBJECT_STATUS_RIDER8`** *(GMX Generals, GMX Zero Hour only)* - Object is rider 8. Set automatically by transport systems to mark objects that are passengers in multi-rider vehicles.

### Locking States

- **`OBJECT_STATUS_LASER_LOCKED`** *(GMX Generals, GMX Zero Hour only)* - Object is locked by laser. Set automatically by targeting systems when objects are locked by laser-guided weapons. Used to track objects that are being targeted by laser-guided missiles or weapons.

- **`OBJECT_STATUS_RADAR_LOCKED`** *(GMX Generals, GMX Zero Hour only)* - Object is locked by radar. Set automatically by targeting systems when objects are locked by radar-guided weapons. Used to track objects that are being targeted by radar-guided missiles or weapons.

- **`OBJECT_STATUS_IR_LOCKED`** *(GMX Generals, GMX Zero Hour only)* - Object is locked by IR (Infrared). Set automatically by targeting systems when objects are locked by infrared-guided weapons. Used to track objects that are being targeted by infrared-guided missiles or weapons.

- **`OBJECT_STATUS_GPS_LOCKED`** *(GMX Generals, GMX Zero Hour only)* - Object is locked by GPS. Set automatically by targeting systems when objects are locked by GPS-guided weapons. Used to track objects that are being targeted by GPS-guided missiles or weapons.

- **`OBJECT_STATUS_RF_LOCKED`** *(GMX Generals, GMX Zero Hour only)* - Object is locked by RF (Radio Frequency). Set automatically by targeting systems when objects are locked by radio frequency-guided weapons. Used to track objects that are being targeted by RF-guided missiles or weapons.

## Examples

### Status Flag Usage in Modules

Some modules allow you to require or forbid specific status flags:

```ini
Behavior = StealthUpdate ModuleTag_Stealth
  RequiredStatus = CAN_STEALTH
  ForbiddenStatus = DETECTED
End
```

In this example, the `StealthUpdate` behavior requires the `CAN_STEALTH` status flag to be set and forbids the `DETECTED` status flag.

### Status Flag Combinations

Multiple status flags can be active simultaneously:

- An object can be `STEALTHED` and `DETECTED` at the same time (stealthed but detected by enemy detectors)
- An object can be `IS_ATTACKING` and `IS_FIRING_WEAPON` at the same time (actively firing while in attack state)
- An object can be `UNDER_CONSTRUCTION` and `PARTIALLY_CONSTRUCTED` at the same time (being built and partially complete)

## Notes

- **Status Flag Persistence**: Object status flags are saved in game state and persist across save/load operations. The comment "These are saved. Do not insert or remove any!" in the enum definition indicates that the order and values of status flags must remain stable for save game compatibility.

- **Status Flag Combinations**: Multiple status flags can be active simultaneously. The game systems check for specific combinations of flags to determine object behavior.

- **Automatic Management**: Object status flags are set and cleared automatically by game systems. Modders typically do not need to manually manage these flags, but they can be referenced in module configurations.

- **Bit Flag System**: Object status flags use a bit flag system (`BitFlags<OBJECT_STATUS_COUNT>`), allowing efficient storage and checking of multiple flags simultaneously.

## Source Files

**Header (Generals):** [ObjectStatusTypes.h](../../../../Generals/Code/GameEngine/Include/Common/ObjectStatusTypes.h)
- `ObjectStatusTypes` enum definition (lines 40-99): Defines all available object status types for Retail Generals

**Header (Zero Hour):** [ObjectStatusTypes.h](../../../../GeneralsMD/Code/GameEngine/Include/Common/ObjectStatusTypes.h)
- `ObjectStatusTypes` enum definition (lines 40-99): Defines all available object status types for GMX Zero Hour

**Source (Generals):** [ObjectStatusTypes.cpp](../../../../Generals/Code/GameEngine/Source/Common/System/ObjectStatusTypes.cpp)
- Status flag name mapping: Maps status flag names to their values for INI file parsing

**Source (Zero Hour):** [ObjectStatusTypes.cpp](../../../../GeneralsMD/Code/GameEngine/Source/Common/System/ObjectStatusTypes.cpp)
- Status flag name mapping: Maps status flag names to their values for INI file parsing

## Changes History

### Retail Generals 1.04 → Retail Zero Hour 1.04

No new object status types were added (Retail Zero Hour has the same object status types as Retail Generals 1.04).

### Retail Zero Hour 1.04 → GMX Zero Hour

- In GMX Zero Hour, 19 new object status types were added including 8 rider states (RIDER1 through RIDER8), 5 locking states (LASER_LOCKED, RADAR_LOCKED, IR_LOCKED, GPS_LOCKED, RF_LOCKED), and 6 special condition states (DECK_HEIGHT_OFFSET, REASSIGN_PARKING, BOOBY_TRAPPED, IMMOBILE, DISGUISED, DEPLOYED, MISSILE_KILLING_SELF, FAERIE_FIRE).

### Retail Generals 1.04 → GMX Generals

- In GMX Generals, 19 new object status types were added including 8 rider states (RIDER1 through RIDER8), 5 locking states (LASER_LOCKED, RADAR_LOCKED, IR_LOCKED, GPS_LOCKED, RF_LOCKED), and 6 special condition states (DECK_HEIGHT_OFFSET, REASSIGN_PARKING, BOOBY_TRAPPED, IMMOBILE, DISGUISED, DEPLOYED, MISSILE_KILLING_SELF, FAERIE_FIRE).

## Document Log

- 16/12/2025 — AI — Initial document created.

## Status

AI-generated, 0/2 reviews

## Reviewers

- [ ] Reviewer 1
- [ ] Reviewer 2

