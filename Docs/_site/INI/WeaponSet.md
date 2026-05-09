# WeaponSet INI Documentation

## Overview

Weapon sets allow objects to have conditional collections of weapons (primary/secondary/tertiary), with auto-choose masks, preferred target kinds, and shared reload time. Conditions are expressed using `WeaponSetFlags` (e.g., veterancy, crate upgrades). Objects switch sets dynamically and the engine updates weapon instances accordingly.

## Source Files

- Header: `GeneralsMD/Code/GameEngine/Include/GameLogic/WeaponSet.h` – `WeaponSet`, `WeaponSet`
- Source: `Generals/Code/GameEngine/Source/GameLogic/Object/WeaponSet.cpp` – parse tables, behavior
- Related: `GeneralsMD/Code/GameEngine/Include/GameLogic/WeaponSetType.h`, `WeaponSetFlags.h`

## Usage

- Inside an `Object` template, define one or more `WeaponSet` blocks (via Object, not shown here). Each block uses `WeaponSet` fields to declare conditions and slot weapons.
- The object toggles `WeaponSetType` flags (e.g., by veterancy or modules), and the current set is chosen by matching flags.

## Properties (WeaponSet block)

### General Settings

#### Conditions (v1.04)
- Type: WeaponSetFlags
- Description: Flags that must be set on the object for this set to apply (e.g., `VETERAN`, `ELITE`, `HERO`, `PLAYER_UPGRADE`, `CRATEUPGRADE_ONE`, `CRATEUPGRADE_TWO`, `VEHICLE_HIJACK`, `CARBOMB`, `MINE_CLEARING_DETAIL`).

#### ShareWeaponReloadTime (v1.04)
- Type: Bool
- Description: If yes, weapon slots share a combined reload timer

#### WeaponLockSharedAcrossSets (v1.04)
- Type: Bool
- Description: Keep weapon lock status when switching to this set

### Slot Assignment

#### Weapon (v1.04)
- Type: Pair: `<SlotType> <Weapon>`
- Description: Assign a `Weapon` to a slot
- SlotType values: `PRIMARY`, `SECONDARY`, `TERTIARY`

#### AutoChooseSources (v1.04)
- Type: Bit flags (CommandSourceMask)
- Description: Allowed command sources to auto-choose this slot

#### PreferredAgainst (v1.04)
- Type: KindOfMaskType
- Description: Preferred targets; if victim matches, this slot is strongly preferred

## Enum Value Lists

#### WeaponSetType (v1.04)
- See `GameLogic/WeaponSetType.h` and names used by gameplay (mapped to model condition flags)

#### WeaponSlotType (v1.04)
- PRIMARY, SECONDARY, TERTIARY

## Examples

### Veterancy-based Sets
```
; Regular (implicit) has only primary
WeaponSet
  Conditions          = 
  Weapon              = PRIMARY RifleWeapon
  AutoChooseSources   = PRIMARY CMD_FROM_AI CMD_FROM_PLAYER
  PreferredAgainst    = PRIMARY INFANTRY
  ShareWeaponReloadTime = No
End

WeaponSet
  Conditions          = VETERAN
  Weapon              = PRIMARY RifleWeapon_Vet
  Weapon              = SECONDARY GrenadeWeapon
  PreferredAgainst    = SECONDARY STRUCTURE VEHICLE
  ShareWeaponReloadTime = Yes
End
```

### Car Bomb Set
```
WeaponSet
  Conditions                    = CARBOMB
  Weapon                        = PRIMARY CarbombExplosion
  AutoChooseSources             = PRIMARY CMD_FROM_PLAYER
  WeaponLockSharedAcrossSets    = Yes
End
```

## Notes

- `WeaponSet::updateWeaponSet` recreates weapon instances when switching sets and accumulates anti masks and damage type masks.
- PreferredAgainst magnifies damage/range for slot selection and treats reloading as usable (unless out of ammo).
- Use `Object.setWeaponSetFlag`/`clearWeaponSetFlag` to control active set at runtime.

## Template

```
WeaponSet
  Conditions                 = VETERAN                ; flags required
  Weapon                     = PRIMARY <WeaponNameA>  ; assign weapon to slot
  Weapon                     = SECONDARY <WeaponNameB>
  AutoChooseSources          = PRIMARY CMD_FROM_AI CMD_FROM_PLAYER ; allowed command sources
  PreferredAgainst           = PRIMARY INFANTRY       ; prefer slot vs kinds
  ShareWeaponReloadTime      = No                     ; share reload across slots
  WeaponLockSharedAcrossSets = No                     ; keep lock when swapping
End
```

