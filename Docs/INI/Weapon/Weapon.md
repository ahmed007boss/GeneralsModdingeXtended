# Weapon

Status: AI-generated, 0/2 reviews

## Overview

The `Weapon` class defines the properties and behavior of weapons in the game. Weapons are used by units, buildings, and special powers to deal damage, apply status effects, or trigger other game mechanics. Each weapon template specifies damage values, range, firing mechanics, visual effects, and targeting rules.

Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

**File Location**: Weapon definitions are stored in `.ini` files within the game's data directories. The file location, naming convention, and loading behavior differs significantly between versions:

- **GMX Zero Hour**: Weapons are loaded from multiple sources in a specific order:
  1. `Data\INI\Weapon\weapon.ini` (if it exists)
  2. All other `.ini` files from `Data\INI\Weapon\` directory in alphabetical order
  3. Files with `.weapon.ini` or `.weapons.ini` extension from `Data\INI\Object\` directory and its subdirectories (e.g., `tanks.weapon.ini`, `scorpion.weapon.ini`)

  Files are processed in alphabetical order within each directory. When multiple files contain a weapon with the same name, the later-loaded file completely overwrites the earlier one. Each weapon must have a unique name across all files, or the engine will crash when parsing duplicate names.

  Files from different sources (archives and game directory) are loaded in this order:
  1. Files inside archives (`.big`, `.gib` files) are loaded first, in descending alphabetical order (Z to A)
  2. Loose files in the game directory are loaded last

  Since loose files are loaded last, they take precedence over archive files. Unlike some other subsystems, weapons do not use a default folder structure (e.g., `Data\INI\Default\Weapon\`).

- **GMX Generals**: Weapons are loaded from the `Data\INI\Weapon\` directory in this order:
  1. `Data\INI\Weapon\weapon.ini` (if it exists)
  2. All other `.ini` files from `Data\INI\Weapon\` directory in alphabetical order

  Files are processed in alphabetical order. When multiple files contain a weapon with the same name, the later-loaded file completely overwrites the earlier one. Each weapon must have a unique name across all files, or the engine will crash when parsing duplicate names.

  Files from different sources (archives and game directory) are loaded in this order:
  1. Files inside archives (`.big`, `.gib` files) are loaded first, in descending alphabetical order (Z to A)
  2. Loose files in the game directory are loaded last

  Since loose files are loaded last, they take precedence over archive files. Unlike some other subsystems, weapons do not use a default folder structure (e.g., `Data\INI\Default\Weapon\`).

- **Retail Zero Hour 1.04 / Retail Generals 1.04**: Weapons are loaded from the file `Data\INI\Weapon\weapon.ini` only. This file can exist in multiple locations: inside archives (`.big`, `.gib` files) and as a loose file in the game directory. Only `weapon.ini` is loaded from these locations.

  When multiple `weapon.ini` files are found, they are loaded in this order:
  1. Files inside archives are loaded first, in descending alphabetical order (Z to A)
  2. Loose files in the game directory are loaded last

  Since loose files are loaded last, they take precedence over archive files. If the same weapon name appears in multiple `weapon.ini` files, the later-loaded file completely overwrites the earlier one. Each weapon must have a unique name within each file, or the engine will crash when parsing duplicate names.

  Unlike some other subsystems, weapons do not use a default folder structure (e.g., `Data\INI\Default\Weapon\`).

Weapons are defined as a list of entries (many entries allowed) in these `.ini` files. They are referenced by units, buildings, and special powers to define their combat capabilities and special abilities.

**WeaponExtend** *(GMX Zero Hour only)*: Allows creating new weapons that inherit all properties from a parent weapon, then override only the properties you want to change. This eliminates the need to duplicate all properties when creating weapon variants, making modding more efficient and maintainable.


## Table of Contents

- [Overview](#overview)
- [Properties](#properties)
  - [Basic Damage Properties](#basic-damage-properties)
  - [Range and Targeting](#range-and-targeting)
  - [Firing Mechanics](#firing-mechanics)
  - [Projectile Properties](#projectile-properties)
  - [Visual and Audio Effects](#visual-and-audio-effects)
  - [Targeting and Collision](#targeting-and-collision)
  - [Continuous Fire Properties](#continuous-fire-properties)
  - [Laser and Stream Properties](#laser-and-stream-properties)
  - [Weapon Bonus Properties](#weapon-bonus-properties)
  - [Historic Bonus Properties](#historic-bonus-properties)
  - [Scatter and Accuracy Properties](#scatter-and-accuracy-properties)
  - [Advanced Properties](#advanced-properties)
- [Enum Value Lists](#enum-value-lists)
- [Examples](#examples)
- [Usage](#usage)
- [Template](#template)
- [Notes](#notes)
- [Modder Recommended Use Scenarios](#modder-recommended-use-scenarios)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Document Log](#document-log)
- [Status](#status)
- [Reviewers](#reviewers)

## Properties

### Basic Damage Properties

#### `DisplayName`
Available in: *(GMX Zero Hour only)*

- **Type**: `Label`
- **Description**: Localized UI name label for this weapon. The label is translated at runtime.
- **Default**: Empty (falls back to weapon name)
- **Example**: `DisplayName = CONTROLBAR:Weapon_TankCannon`

#### `PrimaryDamage`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: The damage amount applied to objects within the primary damage radius. When a weapon deals damage, objects at or closer than [`PrimaryDamageRadius`](#primarydamageradius) from the impact point receive this damage amount. The primary target (if any) always receives primary damage regardless of distance. This damage is modified by weapon bonuses, armor types, and damage multipliers. If [`PrimaryDamageRadius`](#primarydamageradius) is 0, only the direct target receives this damage (no area effect).
- **Default**: `0.0`
- **Example**: `PrimaryDamage = 350.0`

#### `PrimaryDamageRadius`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: The radius (in world units) from the impact point within which objects receive [`PrimaryDamage`](#primarydamage). Objects at a distance squared less than or equal to this radius squared take primary damage. If this is 0, the weapon only affects the direct target (no area effect). [`SecondaryDamageRadius`](#secondarydamageradius) must be greater than or equal to [`PrimaryDamageRadius`](#primarydamageradius) (or zero). This radius is modified by weapon bonuses that affect radius.
- **Default**: `0.0`
- **Example**: `PrimaryDamageRadius = 40.0`

#### `SecondaryDamage`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: The damage amount applied to objects beyond the primary damage radius but within the secondary damage radius. Objects farther than [`PrimaryDamageRadius`](#primarydamageradius) but at or within [`SecondaryDamageRadius`](#secondarydamageradius) from the impact point receive this damage amount instead of primary damage. This allows creating weapons with a high-damage core area and a lower-damage outer area. If [`SecondaryDamageRadius`](#secondarydamageradius) is 0 or equal to [`PrimaryDamageRadius`](#primarydamageradius), secondary damage is never applied. This damage is modified by weapon bonuses, armor types, and damage multipliers.
- **Default**: `0.0`
- **Example**: `SecondaryDamage = 200.0`

#### `SecondaryDamageRadius`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: The radius (in world units) from the impact point within which objects can receive [`SecondaryDamage`](#secondarydamage). Objects beyond [`PrimaryDamageRadius`](#primarydamageradius) but at or within this radius take secondary damage. This value must be greater than or equal to [`PrimaryDamageRadius`](#primarydamageradius) (or zero). If this is 0 or equal to [`PrimaryDamageRadius`](#primarydamageradius), only primary damage is applied. If this is greater than [`PrimaryDamageRadius`](#primarydamageradius), objects in the ring between the two radii receive secondary damage. This radius is modified by weapon bonuses that affect radius.
- **Default**: `0.0`
- **Example**: `SecondaryDamageRadius = 60.0`

#### `DamageType`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `DamageType` (see [DamageType documentation](Enum/DamageType.md))
- **Description**: The type of damage this weapon deals. Different damage types interact differently with armor types and can trigger special behaviors.
- **Default**: `EXPLOSION`
- **Example**: `DamageType = EXPLOSION`

#### `DeathType`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `DeathType`
- **Description**: The type of death animation/effect when this weapon kills a target
- **Default**: `NORMAL`
- **Example**: `DeathType = EXPLODED`
- **Available Values**: See [`DeathType` Values](#deathtype-values) section below

<a id="damagestatustype"></a>
#### `DamageStatusType`
Available in: *(GMX Zero Hour, Retail Zero Hour 1.04 only)*

- **Type**: `ObjectStatusTypes` (see [ObjectStatusTypes documentation](../Object/Enums/ObjectStatusTypes.md))
- **Description**: If the damage type is [`DAMAGE_STATUS`](Enum/DamageType.md#damage_status) (see [DamageType documentation](Enum/DamageType.md)), this specifies which status effect to apply to the target. The status effect is applied when the weapon deals damage.
- **Default**: [`OBJECT_STATUS_NONE`](../Object/Enums/ObjectStatusTypes.md) (see [ObjectStatusTypes documentation](../Object/Enums/ObjectStatusTypes.md))
- **Example**: `DamageStatusType = CAN_ATTACK`

### Range and Targeting

#### `AttackRange` *(v1.04)*
- **Type**: `Real`
- **Description**: Maximum distance (in world units) at which this weapon will consider targets valid for acquisition and firing. Targets beyond this range are ignored for both targeting and firing. A small margin is applied to prevent targets from teetering on the edge of range. For projectile weapons, this works in combination with [`WeaponSpeed`](#weaponspeed)/[`MinWeaponSpeed`](#minweaponspeed) and accuracy properties. The effective range may be modified by weapon bonuses that affect range. If this is 0, the weapon cannot acquire targets (contact weapons may still function differently).
- **Default**: `0.0`
- **Example**: `AttackRange = 450.0`

#### `MinimumAttackRange` *(v1.04)*
- **Type**: `Real`
- **Description**: Minimum distance (in world units) required before this weapon may fire. If a target is closer than this value (with a small margin applied), the weapon will not fire even if it is otherwise valid and acquired. This prevents self-damage from area effect weapons, enforces standoff behavior for artillery, and prevents units from firing point-blank when that would be undesirable. A small margin is applied to this value to ensure consistent behavior. If this is 0, there is no minimum range restriction.
- **Default**: `0.0`
- **Example**: `MinimumAttackRange = 5.0`

#### `AcceptableAimDelta` *(v1.04)*
- **Type**: `Real` (angle in degrees)
- **Description**: Maximum allowed angular error (in degrees) between the weapon's current aim direction and the ideal direction to the target before a shot can be released. The weapon will wait until the aim error is within this tolerance before firing. Smaller values (e.g., 1-2 degrees) enforce very precise aiming, requiring the weapon to be nearly perfectly aligned before firing - useful for sniper weapons or high-accuracy weapons. Larger values (e.g., 10-15 degrees) allow the weapon to fire while still tracking or moving, creating a more "spray and pray" behavior. A value of 0 means the weapon must be perfectly aimed (may cause issues with moving targets). Very large values (e.g., 999) effectively disable aim checking, allowing immediate firing.
- **Default**: `0.0`
- **Example**: `AcceptableAimDelta = 1`

#### `RequestAssistRange` *(v1.04)*
- **Type**: `Real`
- **Description**: Range within which other units will be called to assist in attacks
- **Example**: `RequestAssistRange = 100.0`

### Firing Mechanics

#### `DelayBetweenShots` *(v1.04)*
- **Type**: `Int` (milliseconds) or `Min:Max` range
- **Description**: Time delay between consecutive shots fired by this weapon. This property accepts two formats: (1) A single integer value (e.g., `1000`) which creates a constant delay between all shots, or (2) A labeled range format `Min:1000 Max:2000` which creates a variable delay where a random value between min and max (inclusive) is selected for each shot. The values are specified in milliseconds but are converted to game frames. If both min and max are 0, there is no enforced delay between shots (weapon fires as fast as possible). Variable delays add unpredictability to weapon firing patterns.
- **Default**: `0` (no enforced delay)
- **Example**: `DelayBetweenShots = 1000` or `DelayBetweenShots = Min:800 Max:1200`

#### `ClipSize` *(v1.04)*
- **Type**: `Int`
- **Description**: Number of shots that can be fired before the weapon must reload. When the weapon fires, it consumes one shot from the clip. Once the clip is empty (all shots fired), the weapon must reload using [`ClipReloadTime`](#clipreloadtime) before it can fire again. If set to 0, the weapon has infinite ammo and never needs to reload. Higher values allow more shots before reloading, but also increase the time required to reload. This property works in combination with [`AutoReloadsClip`](#autoreloadsclip) and [`AutoReloadWhenIdle`](#autoreloadwhenidle) to control reload behavior.
- **Example**: `ClipSize = 30`

#### `ClipReloadTime` *(v1.04)*
- **Type**: `Int` (milliseconds)
- **Description**: Time (in milliseconds) required to reload the weapon when the clip is empty. This delay is applied after the weapon has fired all shots in the [`ClipSize`](#clipsize) and needs to reload before it can fire again. The reload time prevents the weapon from firing during this period. If [`AutoReloadsClip`](#autoreloadsclip) is enabled, the reload happens automatically when the clip is empty. Higher values create longer reload times, balancing weapons with large clip sizes. If [`ClipSize`](#clipsize) is 0 (infinite ammo), this property has no effect.
- **Example**: `ClipReloadTime = 3000`

#### `AutoReloadsClip` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether the weapon automatically begins reloading when the [`ClipSize`](#clipsize) is exhausted. When enabled, the weapon automatically starts the reload process (using [`ClipReloadTime`](#clipreloadtime)) as soon as the last shot in the clip is fired. When disabled, the weapon will not reload automatically and must be manually reloaded or will reload when [`AutoReloadWhenIdle`](#autoreloadwhenidle) triggers. This property only has an effect if [`ClipSize`](#clipsize) is greater than 0.
- **Example**: `AutoReloadsClip = Yes`

#### `AutoReloadWhenIdle` *(v1.04)*
- **Type**: `Int` (milliseconds)
- **Description**: Time (in milliseconds) of inactivity (not firing) before the weapon automatically reloads if the clip is not full. If the weapon has not fired for this duration and the current clip has fewer shots than [`ClipSize`](#clipsize), the weapon will automatically reload to fill the clip. This allows weapons to reload during lulls in combat without manual intervention. If set to 0, the weapon will not automatically reload when idle. This property only has an effect if [`ClipSize`](#clipsize) is greater than 0.
- **Example**: `AutoReloadWhenIdle = 5000`

#### `PreAttackDelay` *(v1.04)*
- **Type**: `Int` (milliseconds)
- **Description**: Delay (in milliseconds) before the weapon fires after acquiring a target. This delay is applied based on the [`PreAttackType`](#preattacktype) setting, which determines when the delay occurs (before each shot, before each new target, or before each new clip). The delay allows time for aiming, charging, or other preparation before firing. Higher values create longer preparation times, useful for weapons that need to lock on, charge up, or aim precisely before firing. If set to 0, there is no pre-attack delay and the weapon fires immediately when ready.
- **Example**: `PreAttackDelay = 2000`

#### `PreAttackType` *(v1.04)*
- **Type**: `WeaponPrefireType`
- **Description**: Determines when the [`PreAttackDelay`](#preattackdelay) is applied. This controls the timing of the pre-attack delay relative to the weapon's firing cycle. The delay can be applied before every shot, only when starting to attack a new target, or only when starting a new clip. This allows fine-tuning when the weapon needs preparation time versus when it can fire immediately.
- **Example**: `PreAttackType = PER_SHOT`
- **Available Values**: See [WeaponPrefireType Values](#weaponprefiretype-values) section below

### Projectile Properties

#### `ProjectileObject` *(v1.04)*
- **Type**: `object` (see [Object documentation](Object.md))
- **Description**: The projectile object to create when firing
- **Example**: `ProjectileObject = TankShell`

#### `WeaponSpeed` *(v1.04)*
- **Type**: `Real` (distance per second)
- **Description**: Speed of the projectile or damage travel
- **Example**: `WeaponSpeed = 1000.0`

#### `MinWeaponSpeed` *(v1.04)*
- **Type**: `Real` (distance per second)
- **Description**: Minimum speed for variable-speed weapons
- **Example**: `MinWeaponSpeed = 500.0`

#### `ScaleWeaponSpeed` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether weapon speed scales with range (for lobbed projectiles)
- **Example**: `ScaleWeaponSpeed = Yes`

#### `WeaponRecoil` *(v1.04)*
- **Type**: `Real` (radians)
- **Description**: Amount of recoil imparted to the firing unit
- **Example**: `WeaponRecoil = 0.1`

### Visual and Audio Effects

#### `FireFX` *(v1.04)*
- **Type**: `FXList` (per veterancy level)
- **Description**: Visual effects (FXList) that are played at the weapon's firing point when the weapon fires. These effects are displayed at the muzzle or firing location and provide visual feedback for weapon discharge. The effects are played every time the weapon fires, synchronized with the firing animation. If you need different effects for different veterancy levels, use [`VeterancyFireFX`](#veterancyfirefx) instead. The FXList can contain multiple effects that play simultaneously or in sequence.
- **Example**: `FireFX = FX_TankCannonFire`

#### `ProjectileDetonationFX` *(v1.04)*
- **Type**: `FXList` (per veterancy level)
- **Description**: Visual effects played when projectile hits target
- **Example**: `ProjectileDetonationFX = FX_ExplosionLarge`

#### `FireSound` *(v1.04)*
- **Type**: `AudioEventRTS`
- **Description**: Audio event (AudioEventRTS) that is played when the weapon fires. This sound is triggered at the weapon's firing point and provides audio feedback for weapon discharge. The sound plays every time the weapon fires, synchronized with the firing animation. For continuous-fire weapons, you can use [`FireSoundLoopTime`](#firesoundlooptime) to loop the sound for a specified duration. The audio event must be defined in the game's audio system and can include 3D positional audio that varies based on the listener's position relative to the firing unit.
- **Example**: `FireSound = TankCannonFire`

#### `FireSoundLoopTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Duration (in milliseconds) that the [`FireSound`](#firesound) will loop when the weapon fires. When set to a value greater than 0, the fire sound will loop for this duration, creating a continuous sound effect for rapid-fire or continuous-fire weapons. This is useful for weapons like machine guns or flamethrowers that have a sustained firing sound. If set to 0, the fire sound plays once per shot without looping. The looping sound stops when the duration expires or when the weapon stops firing.
- **Example**: `FireSoundLoopTime = 1000`

#### `FireOCL` *(v1.04)*
- **Type**: `ObjectCreationList` (per veterancy level)
- **Description**: Objects created when weapon fires
- **Example**: `FireOCL = OCL_MuzzleFlash`

#### `ProjectileDetonationOCL` *(v1.04)*
- **Type**: `ObjectCreationList` (per veterancy level)
- **Description**: Objects created when projectile detonates
- **Example**: `ProjectileDetonationOCL = OCL_ExplosionDebris`

#### `ProjectileExhaust` *(v1.04)*
- **Type**: `ParticleSystemTemplate` (per veterancy level)
- **Description**: Particle effects for projectile exhaust trail
- **Example**: `ProjectileExhaust = PS_TankShellTrail`

#### `VeterancyFireFX` *(v1.04)*
- **Type**: `FXList` (per veterancy level)
- **Description**: Visual effects (FXList) played when the weapon fires, with different effects specified for each veterancy level (Veteran, Elite, Heroic). This property allows you to create more impressive visual effects as units gain veterancy. The format allows specifying different FXList entries for each veterancy level. Use this instead of [`FireFX`](#firefx) when you need different effects for each veterancy level. If both [`FireFX`](#firefx) and this property are specified, this property takes precedence for veteran units.
- **Example**: `VeterancyFireFX = VETERAN FX_TankCannonFireVeteran`

#### `VeterancyProjectileDetonationFX` *(v1.04)*
- **Type**: `FXList` (per veterancy level)
- **Description**: Visual effects (FXList) played when the projectile impacts its target, with different effects specified for each veterancy level (Veteran, Elite, Heroic). This property allows you to create more impressive impact effects as units gain veterancy. The format allows specifying different FXList entries for each veterancy level. Use this instead of [`ProjectileDetonationFX`](#projectiledetonationfx) when you need different effects for each veterancy level. If both [`ProjectileDetonationFX`](#projectiledetonationfx) and this property are specified, this property takes precedence for veteran units.
- **Example**: `VeterancyProjectileDetonationFX = VETERAN FX_ExplosionLargeVeteran`

#### `VeterancyFireOCL` *(v1.04)*
- **Type**: `ObjectCreationList` (per veterancy level)
- **Description**: ObjectCreationList that creates objects when the weapon fires, with different objects specified for each veterancy level (Veteran, Elite, Heroic). This property allows you to create more impressive firing effects as units gain veterancy. The format allows specifying different ObjectCreationList entries for each veterancy level. Use this instead of [`FireOCL`](#fireocl) when you need different objects for each veterancy level. If both [`FireOCL`](#fireocl) and this property are specified, this property takes precedence for veteran units.
- **Example**: `VeterancyFireOCL = VETERAN OCL_MuzzleFlashVeteran`

#### `VeterancyProjectileDetonationOCL` *(v1.04)*
- **Type**: `ObjectCreationList` (per veterancy level)
- **Description**: ObjectCreationList that creates objects when the projectile impacts its target, with different objects specified for each veterancy level (Veteran, Elite, Heroic). This property allows you to create more impressive impact effects as units gain veterancy. The format allows specifying different ObjectCreationList entries for each veterancy level. Use this instead of [`ProjectileDetonationOCL`](#projectiledetonationocl) when you need different objects for each veterancy level. If both [`ProjectileDetonationOCL`](#projectiledetonationocl) and this property are specified, this property takes precedence for veteran units.
- **Example**: `VeterancyProjectileDetonationOCL = VETERAN OCL_ExplosionDebrisVeteran`

#### `VeterancyProjectileExhaust` *(v1.04)*
- **Type**: `ParticleSystemTemplate` (per veterancy level)
- **Description**: Particle system template that creates a visual trail behind the projectile, with different effects specified for each veterancy level (Veteran, Elite, Heroic). This property allows you to create more impressive trail effects as units gain veterancy. The format allows specifying different particle system templates for each veterancy level. Use this instead of [`ProjectileExhaust`](#projectileexhaust) when you need different effects for each veterancy level. If both [`ProjectileExhaust`](#projectileexhaust) and this property are specified, this property takes precedence for veteran units.
- **Example**: `VeterancyProjectileExhaust = VETERAN PS_TankShellTrailVeteran`

### Targeting and Collision

#### `RadiusDamageAffects` *(v1.04)*
- **Type**: `WeaponAffectsMaskType` (bit flags)
- **Description**: What types of objects are affected by radius damage
- **Example**: `RadiusDamageAffects = ALLIES ENEMIES NEUTRALS`
- **Available Values**: See [WeaponAffectsMaskType Values](#weaponaffectsmasktype-values) section below

#### `RadiusDamageAffectsMaxSimultaneous` *(GMX Zero Hour only)*
- **Type**: `Int`
- **Description**: Maximum number of objects that can be affected by radius damage simultaneously. When set to 0 (default), there is no limit. When set to a positive value, the weapon will only affect the first N objects that pass all other targeting checks.
- **Default**: `0` (no limit)
- **Example**: `RadiusDamageAffectsMaxSimultaneous = 5`

#### `ProjectileCollidesWith` *(v1.04)*
- **Type**: `WeaponCollideMaskType` (bit flags)
- **Description**: What objects projectiles can collide with
- **Example**: `ProjectileCollidesWith = STRUCTURES WALLS`
- **Available Values**: See [WeaponCollideMaskType Values](#weaponcollidemasktype-values) section below

#### `AntiGround` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether weapon can target ground units
- **Example**: `AntiGround = Yes`

#### `AntiAirborneVehicle` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether weapon can target airborne vehicles
- **Example**: `AntiAirborneVehicle = Yes`

#### `AntiAirborneInfantry` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether weapon can target airborne infantry
- **Example**: `AntiAirborneInfantry = No`

#### `AntiProjectile` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether weapon can target projectiles
- **Example**: `AntiProjectile = Yes`

#### `AntiSmallMissile` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether weapon can target small missiles
- **Example**: `AntiSmallMissile = Yes`

#### `AntiBallisticMissile` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether weapon can target ballistic missiles
- **Example**: `AntiBallisticMissile = Yes`

#### `AntiMine` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether weapon can target mines
- **Example**: `AntiMine = Yes`

#### `AntiParachute` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether weapon can target parachutes
- **Example**: `AntiParachute = Yes`

#### `TargetPrerequisite` *(GMX Zero Hour only)*
- **Type**: `ObjectPrerequisite` block (see [ObjectPrerequisite documentation](../Object/Prerequisites/ObjectPrerequisite.md))
- **Description**: Prerequisites that the target must meet for this weapon to be effective. The weapon will only deal damage if the target meets all specified prerequisites within this block. Multiple prerequisite properties can be combined using AND logic (all must pass). See [ObjectPrerequisite documentation](../Object/Prerequisites/ObjectPrerequisite.md) for all available prerequisite properties.
- **Example**: 
```ini
TargetPrerequisite
  ObjectIsKindOf = VEHICLE
  ObjectIsNoKindOf = INFANTRY
End
```

#### `ShooterPrerequisite` *(GMX Zero Hour only)*
- **Type**: `ObjectPrerequisite` block (see [ObjectPrerequisite documentation](../Object/Prerequisites/ObjectPrerequisite.md))
- **Description**: Prerequisites that the firing unit must meet for this weapon to be used. The weapon will only fire if the shooter meets all specified prerequisites within this block. Multiple prerequisite properties can be combined using AND logic (all must pass). See [ObjectPrerequisite documentation](../Object/Prerequisites/ObjectPrerequisite.md) for all available prerequisite properties.
- **Example**: 
```ini
ShooterPrerequisite
  ObjectIsKindOf = VEHICLE
  ObjectHasUpgrade = Upgrade_WeaponUpgrade
End
```

#### `RadiusDamageAffectsPrerequisite` *(GMX Zero Hour only)*
- **Type**: `ObjectPrerequisite` block (see [ObjectPrerequisite documentation](../Object/Prerequisites/ObjectPrerequisite.md))
- **Description**: Prerequisites that objects must meet to be affected by radius damage. Only objects that meet all specified prerequisites within this block will be affected by area damage. Multiple prerequisite properties can be combined using AND logic (all must pass). See [ObjectPrerequisite documentation](../Object/Prerequisites/ObjectPrerequisite.md) for all available prerequisite properties.
- **Example**: 
```ini
RadiusDamageAffectsPrerequisite
  ObjectIsKindOf = VEHICLE
  ObjectIsNoKindOf = STRUCTURE
End
```

### Advanced Properties

#### `ShockWaveAmount` *(v1.04, Generals Zero Hour only)*
- **Type**: `Real`
- **Description**: Amount of shockwave effect generated
- **Example**: `ShockWaveAmount = 25.0`

#### `ShockWaveRadius` *(v1.04, Generals Zero Hour only)*
- **Type**: `Real`
- **Description**: Radius of shockwave effect
- **Example**: `ShockWaveRadius = 70.0`

#### `ShockWaveTaperOff` *(v1.04, Generals Zero Hour only)*
- **Type**: `Real`
- **Description**: How much shockwave effect remains at the edge of radius
- **Example**: `ShockWaveTaperOff = 0.50`

#### `ScatterRadius` *(v1.04)*
- **Type**: `Real`
- **Description**: Maximum random offset radius (in world units) applied to the intended impact point to simulate weapon inaccuracy. When the weapon fires, the actual impact point is randomly offset from the target position by up to this radius in any direction. This creates a circular area of potential impact. This scatter is applied to all targets. If this is 0, there is no random scatter (weapon is perfectly accurate). Scatter is useful for simulating artillery, mortars, or low-accuracy weapons. The scatter is applied in addition to any `ScatterRadiusVsInfantry` when targeting infantry.
- **Default**: `0.0`
- **Example**: `ScatterRadius = 5.0`

#### `ScatterTargetScalar` *(v1.04)*
- **Type**: `Real`
- **Description**: Multiplier applied to the coordinates specified in `ScatterTarget` entries. This allows you to scale preset scatter target offsets without redefining all the coordinates. A value of 1.0 uses the scatter targets at their defined scale. Values greater than 1.0 increase the scatter spread, values less than 1.0 decrease it. This only affects weapons that use `ScatterTarget` entries; it has no effect if `ScatterTarget` is not used.
- **Default**: `0.0`
- **Example**: `ScatterTargetScalar = 1.0`

#### `ScatterRadiusVsInfantry` *(v1.04)*
- **Type**: `Real`
- **Description**: Additional random scatter radius (in world units) applied specifically when the target is infantry. This extra inaccuracy is added to the base `ScatterRadius` when targeting infantry units, simulating the difficulty of hitting small, mobile targets. If the target is not infantry, only `ScatterRadius` applies. This allows weapons to be more accurate against vehicles/buildings but less accurate against infantry. If this is 0, there is no extra scatter against infantry (only base `ScatterRadius` applies).
- **Default**: `0.0`
- **Example**: `ScatterRadiusVsInfantry = 10.0`

#### `DamageDealtAtSelfPosition` *(v1.04)*
- **Type**: `Bool`
- **Description**: When enabled, the damage epicenter is the firing unit's current position rather than the target's position. This causes all radius damage calculations to originate from the shooter, not the impact point. This is essential for suicide weapons (like car bombs) where the explosion should occur at the attacker's location. When disabled (default), damage originates from the target position (for direct hits) or the projectile impact point (for projectile weapons). This property affects both primary and secondary damage radius calculations.
- **Default**: `No`
- **Example**: `DamageDealtAtSelfPosition = Yes`

#### `ContinueAttackRange` *(v1.04)*
- **Type**: `Real`
- **Description**: Radius (in world units) within which the weapon will automatically search for and acquire new similar targets after destroying the current target, without requiring manual reacquisition. When a target is destroyed, becomes effectively dead, or is a mine that becomes masked, the weapon automatically looks for another valid target of the same type within this range. This allows weapons to chain attacks across multiple targets without player intervention. The weapon temporarily sets the `IGNORING_STEALTH` status flag to find stealthed targets during this search. If this is 0, the weapon does not automatically continue attacking after destroying a target (normal behavior).
- **Default**: `0.0`
- **Example**: `ContinueAttackRange = 50.0`

#### `MinTargetPitch` *(v1.04)*
- **Type**: `Real` (angle in radians)
- **Description**: Lowest vertical aim angle (pitch) allowed when acquiring and firing at targets. This restricts the weapon's ability to aim downward. Values are in radians, where negative values allow aiming below horizontal (downward) and positive values restrict downward aiming. The default of -PI allows aiming in any downward direction. This is useful for weapons that should not be able to fire straight down (e.g., certain artillery) or for balancing purposes.
- **Default**: `-PI` (can aim straight down)
- **Example**: `MinTargetPitch = -30.0`

#### `MaxTargetPitch` *(v1.04)*
- **Type**: `Real` (angle in radians)
- **Description**: Highest vertical aim angle (pitch) allowed when acquiring and firing at targets. This restricts the weapon's ability to aim upward. Values are in radians, where positive values allow aiming above horizontal (upward) and negative values restrict upward aiming. The default of PI allows aiming in any upward direction. This is useful for ground-based weapons that should not be able to fire straight up (e.g., certain cannons) or for balancing purposes.
- **Default**: `PI` (can aim straight up)
- **Example**: `MaxTargetPitch = 30.0`

#### `RadiusDamageAngle` *(v1.04, Generals Zero Hour only)*
- **Type**: `Real` (angle in radians)
- **Description**: Limits radius damage to a directional cone centered on the firing unit's forward orientation. When this value is less than PI (180 degrees), radius damage only affects objects within a cone extending from the firing unit in its facing direction. The cone angle is measured from the center line (half-angle). Objects outside this cone are not affected by radius damage even if they are within the damage radius. When this is PI or greater, radius damage applies in all directions (full 360 degrees). This allows creating directional blasts, flamethrowers, or forward-facing area weapons. The angle between the firing unit's forward direction and the direction to each potential victim is checked; if the victim is outside the allowed cone angle, the victim is skipped.
- **Default**: `PI` (full 360° coverage)
- **Example**: `RadiusDamageAngle = 45.0`

### Continuous Fire Properties

#### `ContinuousFireOne` *(v1.04)*
- **Type**: `Int`
- **Description**: Number of consecutive shots needed to gain ContinuousFire property
- **Example**: `ContinuousFireOne = 5`

#### `ContinuousFireTwo` *(v1.04)*
- **Type**: `Int`
- **Description**: Number of consecutive shots needed to gain ContinuousFireTwo property
- **Example**: `ContinuousFireTwo = 10`

#### `ContinuousFireCoast` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time after stopping fire before continuous fire mode ends
- **Example**: `ContinuousFireCoast = 1000`

### Laser and Stream Properties

#### `LaserName` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Name of the laser object that persists during firing
- **Example**: `LaserName = LaserBeam`

#### `LaserBoneName` *(v1.04, Generals Zero Hour only)*
- **Type**: `AsciiString`
- **Description**: Bone name where the laser object is attached
- **Example**: `LaserBoneName = Muzzle`

#### `ProjectileStreamName` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Name of object that tracks the projectile stream
- **Example**: `ProjectileStreamName = MissileTrail`

### Weapon Bonus Properties

#### `WeaponBonus` *(v1.04)*
- **Type**: `WeaponBonusSet`
- **Description**: Additional bonuses that apply to this weapon
- **Example**: `WeaponBonus = PLAYER_UPGRADE DAMAGE 125%`

### Historic Bonus Properties

#### `HistoricBonusTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time window for historic bonus activation
- **Example**: `HistoricBonusTime = 5000`

#### `HistoricBonusRadius` *(v1.04)*
- **Type**: `Real`
- **Description**: Radius within which historic bonus can be triggered
- **Example**: `HistoricBonusRadius = 100.0`

#### `HistoricBonusCount` *(v1.04)*
- **Type**: `Int`
- **Description**: Number of weapon instances needed to trigger historic bonus
- **Example**: `HistoricBonusCount = 3`

#### `HistoricBonusWeapon` *(v1.04)*
- **Type**: `weapon` (see [Weapon documentation](Weapon.md))
- **Description**: Weapon to fire when historic bonus conditions are met
- **Example**: `HistoricBonusWeapon = NuclearStrike`

### Scatter and Accuracy Properties

#### `ScatterTarget` *(v1.04)*
- **Type**: `Coord2D` (multiple entries)
- **Description**: Specific coordinates for scatter targeting instead of random scatter
- **Example**: 
```
ScatterTarget = 10.0, 5.0
ScatterTarget = -5.0, 15.0
```

#### `ShotsPerBarrel` *(v1.04)*
- **Type**: `Int`
- **Description**: Number of shots per barrel before cycling to next launch point
- **Example**: `ShotsPerBarrel = 3`

### Additional Advanced Properties

#### `CanAttackWithoutTarget` *(GMX Zero Hour only)*
- **Type**: `Bool`
- **Description**: Whether weapon can attack ground positions without a specific target
- **Example**: `CanAttackWithoutTarget = Yes`

#### `LeechRangeWeapon` *(v1.04)*
- **Type**: `Bool`
- **Description**: When enabled, once the weapon fires at a target within its normal [`AttackRange`](#attackrange), it gains unlimited range for the remainder of that attack cycle. This allows the weapon to continue tracking and hitting the target even if it moves beyond the normal attack range. The "leech range" is activated when the weapon fires and remains active until the attack cycle completes (e.g., projectile hits or misses, or the attack is cancelled). This is useful for weapons like homing missiles that should maintain lock-on regardless of range after launch. If disabled, the weapon respects normal range limits throughout the entire attack.
- **Default**: `No`
- **Example**: `LeechRangeWeapon = Yes`

#### `CapableOfFollowingWaypoints` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether projectiles from this weapon can follow waypoint paths
- **Example**: `CapableOfFollowingWaypoints = Yes`

#### `ShowsAmmoPips` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether weapon displays ammo pips in UI
- **Example**: `ShowsAmmoPips = Yes`

#### `AllowAttackGarrisonedBldgs` *(v1.04)*
- **Type**: `Bool`
- **Description**: Allow attacks on garrisoned buildings even if estimated damage would be zero
- **Example**: `AllowAttackGarrisonedBldgs = No`

#### `PlayFXWhenStealthed` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether to play visual effects even when the firing unit is stealthed
- **Example**: `PlayFXWhenStealthed = No`

#### `SuspendFXDelay` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Delay before visual effects are suspended
- **Example**: `SuspendFXDelay = 2000`

#### `MissileCallsOnDie` *(v1.04, Generals Zero Hour only)*
- **Type**: `Bool`
- **Description**: Whether missile calls OnDie when it detonates
- **Example**: `MissileCallsOnDie = Yes`

#### `ConsumeInventory` *(GMX Zero Hour only)*
- **Type**: `AsciiString`
- **Description**: Name of inventory item that is consumed when this weapon fires. The firing unit must have this inventory item to use the weapon.
- **Default**: Empty (no inventory consumption)
- **Example**: `ConsumeInventory = AmmoCrate`

#### `PrimaryHitSideOverride` *(GMX Zero Hour only)*
- **Type**: `HitSide`
- **Description**: Override which side of the target is considered hit for primary damage. Used for side-specific armor calculations.
- **Default**: `UNKNOWN` (auto-detect)
- **Example**: `PrimaryHitSideOverride = FRONT`
- **Available Values**: `FRONT`, `BACK`, `LEFT`, `RIGHT`, `TOP`, `BOTTOM`, `UNKNOWN`

#### `SecondaryHitSideOverride` *(GMX Zero Hour only)*
- **Type**: `HitSide`
- **Description**: Override which side of the target is considered hit for secondary damage. Used for side-specific armor calculations.
- **Default**: `UNKNOWN` (auto-detect)
- **Example**: `SecondaryHitSideOverride = BACK`
- **Available Values**: `FRONT`, `BACK`, `LEFT`, `RIGHT`, `TOP`, `BOTTOM`, `UNKNOWN`

#### `DirectHitSideOverride` *(GMX Zero Hour only)*
- **Type**: `HitSide`
- **Description**: Override which side of the target is considered hit for direct hits. Used for side-specific armor calculations.
- **Default**: `UNKNOWN` (auto-detect)
- **Example**: `DirectHitSideOverride = TOP`
- **Available Values**: `FRONT`, `BACK`, `LEFT`, `RIGHT`, `TOP`, `BOTTOM`, `UNKNOWN`

#### `PrimaryComponentDamage` *(GMX Zero Hour only)*
- **Type**: `ComponentDamageMap` (space-separated pairs on single line)
- **Description**: Component-specific damage amounts for primary damage. Allows targeting specific components on vehicles and structures. Each entry consists of a component name followed by a damage value. Multiple component-damage pairs can be specified on a single line, separated by spaces. Only components with positive damage values are added to the damage map.
- **Default**: Empty (no component-specific damage)
- **Example**: `PrimaryComponentDamage = Engine 50.0 Turret 30.0 Wheels 20.0`

#### `SecondaryComponentDamage` *(GMX Zero Hour only)*
- **Type**: `ComponentDamageMap` (space-separated pairs on single line)
- **Description**: Component-specific damage amounts for secondary damage. Allows targeting specific components on vehicles and structures. Each entry consists of a component name followed by a damage value. Multiple component-damage pairs can be specified on a single line, separated by spaces. Only components with positive damage values are added to the damage map.
- **Default**: Empty (no component-specific damage)
- **Example**: `SecondaryComponentDamage = Engine 25.0 Turret 15.0 Wheels 10.0`

#### `AffectedByComponents` *(GMX Zero Hour only)*
- **Type**: `AsciiString` (space-separated list on single line)
- **Description**: List of component names that this weapon can affect. Only components listed here will take damage from this weapon. Multiple component names can be specified on a single line, separated by spaces. This property clears any previously set components and replaces them with the new list.
- **Default**: Empty (weapon can affect all components)
- **Example**: `AffectedByComponents = Engine Turret Wheels`

#### `ComponentName` *(GMX Zero Hour only)*
- **Type**: `AsciiString`
- **Description**: Name of the component that this weapon is associated with. Used for component-specific weapon systems.
- **Default**: Empty
- **Example**: `ComponentName = MainTurret`

## Enum Value Lists

**Note**: Some enums used by Weapon have their own dedicated documentation files and their details are not listed here:
- **`DamageType`** - See [DamageType documentation](Enum/DamageType.md)
- **`ObjectStatusTypes`** - See [ObjectStatusTypes documentation](../Object/Enums/ObjectStatusTypes.md)
- **`KindOfMaskType`** - See [KindOf documentation](../enums/KindOf.md)

<a id="deathtype-values"></a>
#### `DeathType` Values *(v1.04)*
**Source:** [Damage.h](../GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h) - `DeathType` enum definition

- **`NORMAL`** *(v1.04)* - Standard death animation. The default death type used for most weapons. Units killed with this death type use their standard death animation and visual effects. This is the most common death type and is used when no specific death animation is required. Used by default for most weapons and scripted damage.
- **`EXPLODED`** *(v1.04)* - Explosion death. Used when units are killed by explosive weapons. This death type typically triggers explosion visual effects and animations. Commonly used with explosive damage types like [`DAMAGE_EXPLOSION`](Enum/DamageType.md) (see [DamageType documentation](Enum/DamageType.md)) to create appropriate death visuals that match the weapon type.
- **`BURNED`** *(v1.04)* - Fire death. Used when units are killed by fire-based weapons. This death type triggers fire-related death animations and visual effects. Special handling: when a weapon with [`DEATH_BURNED`](#deathtype-values) targets shrubbery ([`SHRUBBERY`](../Object/Enums/KindOf.md) (see [KindOf documentation](../Object/Enums/KindOf.md))), it always returns a valid damage estimate (1.0) regardless of other factors, allowing flame weapons to target and destroy vegetation. Commonly used with [`DAMAGE_FLAME`](Enum/DamageType.md) (see [DamageType documentation](Enum/DamageType.md)) damage type.
- **`LASERED`** *(v1.04)* - Laser death. Used when units are killed by laser weapons. This death type triggers laser-specific death animations and visual effects. Used with precision energy weapons to create appropriate death visuals. Commonly paired with [`DAMAGE_LASER`](Enum/DamageType.md) (see [DamageType documentation](Enum/DamageType.md)) damage type.
- **`SUICIDED`** *(v1.04)* - Suicide death. Used when units kill themselves, typically through self-destruct mechanisms or suicide attacks. This death type is used for scripted suicides and self-destruct behaviors. The death animation and effects reflect a self-inflicted death rather than being killed by an external source.
- **`CRUSHED`** *(v1.04)* - Crushed death. Used when units are crushed by heavier units or objects. This death type is automatically applied when units are run over by vehicles or crushed by falling objects. Applied during collision detection when a unit is crushed. Death animations show the unit being flattened or crushed. Used with [`DAMAGE_CRUSH`](Enum/DamageType.md) (see [DamageType documentation](Enum/DamageType.md)) damage type.
- **`DETONATED`** *(v1.04)* - Detonation death. Used when projectiles, missiles, or explosive objects detonate normally (as opposed to being shot down or destroyed). This death type represents the normal detonation of an explosive object rather than its destruction. Used to distinguish between normal detonations and other forms of destruction.
- **`TOPPLED`** *(v1.04)* - Toppled death. Used when structures fall over or are toppled. This death type is used for structures that collapse rather than explode. The death animation shows the structure falling over. Used with [`DAMAGE_TOPPLING`](Enum/DamageType.md) (see [DamageType documentation](Enum/DamageType.md)) damage type.
- **`FLOODED`** *(v1.04)* - Flooded death. Used when units are killed by water or flooding. This death type is used by wave guide systems and water-based damage. Units killed by flooding use this death type to show appropriate death visuals. Used with [`DAMAGE_WATER`](Enum/DamageType.md) (see [DamageType documentation](Enum/DamageType.md)) damage type.
- **`SPLATTED`** *(v1.04)* - Splatted death. Used when units fall from heights and are killed by fall damage. This death type is automatically applied by the physics system when units take fatal fall damage. The death animation shows the unit being flattened from impact. Used with [`DAMAGE_FALLING`](Enum/DamageType.md) (see [DamageType documentation](Enum/DamageType.md)) damage type.
- **`POISONED`** *(v1.04)* - Poisoned death. Used when units are killed by poison. This death type is used by poison-based weapons and behaviors. Units killed by poison use this death type to show appropriate death visuals. Used with [`DAMAGE_POISON`](Enum/DamageType.md) (see [DamageType documentation](Enum/DamageType.md)) damage type and `PoisonedBehavior` module.
- **`POISONED_BETA`** *(v1.04)* - Alternative poisoned death. A variant of poisoned death used for different poison effects or visual styles. Used as an alternative to `POISONED` when a different poison death animation is desired.
- **`EXTRA_1`** through **`EXTRA_10`** *(v1.04)* - Custom death types. Reserved death types for modders to define custom death animations and behaviors. These death types can be used to create unique death effects that don't fit into the standard categories. Each extra death type can be assigned custom visual effects and animations through the object's death modules.

<a id="weaponprefiretype-values"></a>
#### `WeaponPrefireType` Values *(v1.04)*
**Source:** [Weapon.h](../GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h#77) - `WeaponPrefireType` enum definition

- **`PER_SHOT`** *(v1.04)* - Prefire delay for every shot. The [`PreAttackDelay`](#preattackdelay) is applied before every single shot fired by this weapon, regardless of target or clip status. This creates a consistent delay between each shot, useful for weapons that need time to aim, charge, or prepare before each individual shot. This is the default behavior and provides the most predictable firing pattern. Useful for weapons that require precise aiming before each shot, such as sniper rifles or charged weapons.
- **`PER_ATTACK`** *(v1.04)* - Prefire delay for each new target. The [`PreAttackDelay`](#preattackdelay) is only applied when starting to attack a new target. Once the weapon has fired at least one shot at a target, subsequent shots at the same target do not apply the prefire delay. The game tracks how many shots have been fired at the current target, and if any shots have already been fired, the prefire delay is skipped. This allows weapons to have an initial aiming/charging delay when acquiring a new target, but then fire rapidly at the same target. Useful for weapons that need time to lock onto a new target but can then fire quickly at that target, such as missile launchers or weapons with target acquisition systems.
- **`PER_CLIP`** *(v1.04)* - Prefire delay for each new clip. The [`PreAttackDelay`](#preattackdelay) is only applied when firing the first shot from a new clip. If the weapon has a [`ClipSize`](#clipsize) greater than 0 and the current ammo in clip is less than the clip size (meaning it's not the first shot in the clip), the prefire delay is skipped. This allows weapons to have a delay when starting a new clip but then fire rapidly for the rest of the clip. Useful for weapons that need time to prepare or charge when loading a new clip, such as weapons with clip-based charging mechanisms or weapons that need to stabilize after reloading.

<a id="weaponaffectsmasktype-values"></a>
#### `WeaponAffectsMaskType` Values *(v1.04)*
**Source:** [Weapon.h](../GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h#110) - `WeaponAffectsMaskType` enum definition

- **`SELF`** *(v1.04)* - Affects the firing unit. When set, the weapon's radius damage can affect the unit that fired it. By default, the firing unit is excluded from radius damage to prevent self-damage. When this flag is set, the firing unit can be damaged by its own weapon's area effect. If the potential victim is the same unit that fired the weapon (or the unit that created the projectile), the victim is included only if this flag is set. Useful for suicide weapons or weapons where self-damage is intentional, such as car bombs or area-effect weapons that should damage the user.
- **`ALLIES`** *(v1.04)* - Affects allied units. When set, the weapon's radius damage affects units that are allied to the firing unit. Allied units are those with an `ALLIES` relationship to the source. This flag controls whether friendly fire is enabled for area damage. If the potential victim is allied to the firing unit, the victim is included only if this flag is set. By default, most weapons include this flag to allow area damage to affect allies. Useful for weapons where friendly fire is acceptable or desired, such as artillery or area-effect weapons.
- **`ENEMIES`** *(v1.04)* - Affects enemy units. When set, the weapon's radius damage affects units that are enemies of the firing unit. Enemy units are those with an `ENEMIES` relationship to the source. This flag controls whether the weapon can damage enemy units within the radius (excluding the primary target, which is always affected). If the potential victim is an enemy of the firing unit, the victim is included only if this flag is set. This is the most common flag and is typically included for offensive weapons. Note: The primary target is always affected regardless of this flag - this flag only affects secondary targets within the radius.
- **`NEUTRALS`** *(v1.04)* - Affects neutral units. When set, the weapon's radius damage affects units that are neutral to the firing unit. Neutral units are those with a `NEUTRAL` relationship to the source. This flag controls whether the weapon can damage neutral units (such as civilians or neutral structures) within the radius. If the potential victim is neutral to the firing unit, the victim is included only if this flag is set. Useful for weapons that should affect neutral units, such as area-effect weapons that don't distinguish between friend and foe, or weapons designed to clear neutral obstacles.
- **`SUICIDE`** *(v1.04)* - Ensures firing unit cannot survive self-damage. When set, this flag guarantees that the firing unit will be killed by its own weapon, even if the calculated damage would not normally be fatal. If this flag is set and the potential victim is the source unit itself, the unit is forced to die. This ensures that suicide weapons always kill the user, regardless of health, armor, or damage calculations. Enough damage is dealt to guarantee death when this flag is active. Used for suicide weapons like car bombs, terrorist attacks, or self-destruct mechanisms where the user must die when the weapon is used.
- **`NOT_SIMILAR`** *(v1.04)* - Doesn't affect similar units (prevents chain reactions). When set, the weapon's radius damage will not affect units that are the same type as the firing unit and are allied to it. If the potential victim is the same unit type as the firing unit and is allied to it, the victim is excluded from damage. This prevents chain reactions where one unit's explosion kills nearby units of the same type, which then explode and kill more, creating a domino effect. Useful for weapons used by groups of similar units (like terrorist bombs) where you want to prevent all units in a group from exploding simultaneously. The primary target is still affected - this only applies to secondary targets within the radius.
- **`NOT_AIRBORNE`** *(v1.04)* - Doesn't affect airborne units (unless primary target). When set, the weapon's radius damage will not affect units that are significantly above the terrain (airborne units), unless the airborne unit is the primary target. If a potential victim is airborne and is not the primary target, the victim is excluded from damage. This allows weapons to affect ground units while ignoring aircraft or paratroopers in the area. Useful for ground-based area weapons like poison fields, radiation zones, or ground explosions that should not affect aircraft. The primary target is always affected regardless of this flag - this only applies to secondary targets within the radius.

<a id="weaponcollidemasktype-values"></a>
#### `WeaponCollideMaskType` Values *(v1.04)*
**Source:** [Weapon.h](../GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h#136) - `WeaponCollideMaskType` enum definition

- **`ALLIES`** *(v1.04)* - Projectiles collide with allied units. When set, projectiles from this weapon will collide with and detonate when hitting units that are allied to the firing unit. If the potential collision target is allied to the firing unit, a collision occurs only if this flag is set. This allows projectiles to pass through friendly units (when not set) or collide with them (when set). Useful for weapons that should not be blocked by friendly units, or weapons where friendly collisions are desired for gameplay reasons. Note: The primary target is always collided with regardless of this flag - this only applies to non-targeted units that get in the way.
- **`ENEMIES`** *(v1.04)* - Projectiles collide with enemy units. When set, projectiles from this weapon will collide with and detonate when hitting enemy units that are not the primary target. If the potential collision target is an enemy of the firing unit, a collision occurs only if this flag is set. This allows projectiles to pass through enemy units (when not set) or collide with them (when set). Useful for weapons that should only hit their intended target, or weapons where hitting any enemy is desired. Note: The primary target is always collided with regardless of this flag - this only applies to non-targeted units that get in the way.
- **`STRUCTURES`** *(v1.04)* - Projectiles collide with structures. When set, projectiles from this weapon will collide with and detonate when hitting structures that are not controlled by the projectile's owner. If the potential collision target is a structure (has the [`STRUCTURE`](../Object/Enums/KindOf.md) (see [KindOf documentation](../Object/Enums/KindOf.md)) flag) and is not controlled by the same player as the projectile, a collision occurs only if this flag is set. This flag specifically excludes structures controlled by the projectile's owner - use `CONTROLLED_STRUCTURES` to collide with owner's structures. Useful for weapons that should be blocked by enemy or neutral structures, such as most projectile weapons. This is the default collision flag for most weapons.
- **`SHRUBBERY`** *(v1.04)* - Projectiles collide with shrubbery. When set, projectiles from this weapon will collide with and detonate when hitting vegetation, trees, or other shrubbery objects. If the potential collision target is shrubbery (has the [`SHRUBBERY`](../Object/Enums/KindOf.md) (see [KindOf documentation](../Object/Enums/KindOf.md)) flag), a collision occurs only if this flag is set. This allows projectiles to pass through vegetation (when not set) or be blocked by it (when set). Useful for weapons that should interact with terrain features, or weapons that should ignore vegetation for gameplay reasons.
- **`PROJECTILES`** *(v1.04)* - Projectiles collide with other projectiles. When set, projectiles from this weapon will collide with and detonate when hitting other projectiles in flight. If the potential collision target is a projectile (has the [`PROJECTILE`](../Object/Enums/KindOf.md) (see [KindOf documentation](../Object/Enums/KindOf.md)) flag), a collision occurs only if this flag is set. This enables projectile interception mechanics, allowing weapons to shoot down incoming projectiles. Useful for point defense weapons, anti-missile systems, or weapons designed to intercept other projectiles. Note: All missiles are also projectiles, so this flag affects missiles as well.
- **`WALLS`** *(v1.04)* - Projectiles collide with walls. When set, projectiles from this weapon will collide with and detonate when hitting walls or fences. If the potential collision target is a wall or fence, a collision occurs only if this flag is set. This allows projectiles to pass through walls (when not set) or be blocked by them (when set). Useful for weapons that should interact with map geometry, or weapons that should ignore walls for gameplay reasons.
- **`SMALL_MISSILES`** *(v1.04)* - Projectiles collide with small missiles. When set, projectiles from this weapon will collide with and detonate when hitting small missiles. If the potential collision target is a small missile (has the [`SMALL_MISSILE`](../Object/Enums/KindOf.md) (see [KindOf documentation](../Object/Enums/KindOf.md)) flag), a collision occurs only if this flag is set. Note that all missiles are also projectiles, so the `PROJECTILES` flag also affects missiles. This flag provides specific targeting for small missiles, allowing weapons to specifically target this missile type. Useful for point defense weapons that need to distinguish between different missile types, or weapons designed specifically to intercept small missiles.
- **`BALLISTIC_MISSILES`** *(v1.04)* - Projectiles collide with ballistic missiles. When set, projectiles from this weapon will collide with and detonate when hitting ballistic missiles (large missiles typically used by superweapons). If the potential collision target is a ballistic missile (has the [`BALLISTIC_MISSILE`](../Object/Enums/KindOf.md) (see [KindOf documentation](../Object/Enums/KindOf.md)) flag), a collision occurs only if this flag is set. Note that all missiles are also projectiles, so the `PROJECTILES` flag also affects missiles. This flag provides specific targeting for ballistic missiles, allowing weapons to specifically target this missile type. Useful for base defense weapons, anti-missile systems, or weapons designed specifically to intercept large ballistic missiles from superweapons.
- **`CONTROLLED_STRUCTURES`** *(v1.04)* - Projectiles collide with structures controlled by the same player. When set, projectiles from this weapon will collide with and detonate when hitting structures that are controlled by the same player as the projectile's owner. If the potential collision target is a structure and is controlled by the same player, a collision occurs only if this flag is set. This is separate from the `STRUCTURES` flag, which only affects structures not controlled by the owner. This allows fine-grained control over whether projectiles can pass through the owner's own structures. Useful for weapons that should be blocked by friendly structures, or weapons that should ignore friendly structures to prevent accidental friendly fire on your own buildings.


## Examples

### Basic Infantry Weapon
```
Weapon USAInfantryRifle
  PrimaryDamage               = 25.0
  PrimaryDamageRadius         = 0.0
  AttackRange                 = 200.0
  MinimumAttackRange          = 0.0
  AcceptableAimDelta          = 5.0
  DamageType                  = BULLET
  DeathType                   = NORMAL
  WeaponSpeed                 = 1000.0
  DelayBetweenShots           = 1000
  ClipSize                    = 30
  ClipReloadTime              = 3000
  AutoReloadsClip             = Yes
  RadiusDamageAffects         = ENEMIES
  AntiGround                  = Yes
  AntiAirborneInfantry        = Yes
  FireSound                   = RifleFire
  FireFX                      = FX_RifleMuzzleFlash
End
```

### Tank Cannon Weapon
```
Weapon USATankCannon
  PrimaryDamage               = 150.0
  PrimaryDamageRadius         = 5.0
  SecondaryDamage             = 75.0
  SecondaryDamageRadius       = 15.0
  AttackRange                 = 300.0
  MinimumAttackRange          = 10.0
  AcceptableAimDelta          = 2.0
  DamageType                  = EXPLOSION
  DeathType                   = EXPLODED
  WeaponSpeed                 = 800.0
  ProjectileObject            = TankShell
  DelayBetweenShots           = 3000
  ClipSize                    = 1
  ClipReloadTime              = 3000
  AutoReloadsClip             = Yes
  RadiusDamageAffects         = ALLIES ENEMIES NEUTRALS
  AntiGround                  = Yes
  AntiAirborneVehicle         = Yes
  FireSound                   = TankCannonFire
  FireFX                      = FX_TankCannonMuzzleFlash
  ProjectileDetonationFX      = FX_ExplosionLarge
  ProjectileCollidesWith      = STRUCTURES WALLS
  ShockWaveAmount             = 10.0
  ShockWaveRadius             = 20.0
  ShockWaveTaperOff           = 0.5
End
```

### Missile Weapon
```
Weapon USAMissileLauncher
  PrimaryDamage               = 200.0
  PrimaryDamageRadius         = 10.0
  SecondaryDamage             = 100.0
  SecondaryDamageRadius       = 25.0
  AttackRange                 = 400.0
  MinimumAttackRange          = 50.0
  AcceptableAimDelta          = 1.0
  DamageType                  = EXPLOSION
  DeathType                   = EXPLODED
  WeaponSpeed                 = 600.0
  ProjectileObject            = AntiTankMissile
  DelayBetweenShots           = 5000
  ClipSize                    = 1
  ClipReloadTime              = 5000
  AutoReloadsClip             = Yes
  RadiusDamageAffects         = ALLIES ENEMIES NEUTRALS
  AntiGround                  = Yes
  AntiAirborneVehicle         = Yes
  FireSound                   = MissileLaunch
  FireFX                      = FX_MissileLaunch
  ProjectileDetonationFX      = FX_MissileExplosion
  ProjectileCollidesWith      = STRUCTURES WALLS PROJECTILES
  ShockWaveAmount             = 15.0
  ShockWaveRadius             = 30.0
  ShockWaveTaperOff           = 0.4
End
```

### Status Effect Weapon
```
Weapon StealthHawkTargetDesignator
  PrimaryDamage               = 10.0
  PrimaryDamageRadius         = 10.0
  AcceptableAimDelta          = 1.0
  AttackRange                 = 450.0
  MinimumAttackRange          = 5.0
  PreAttackDelay              = 5000
  PreAttackType               = PER_SHOT
  DamageType                  = STATUS
  DamageStatusType            = CAN_ATTACK
  ProjectileObject            = S300Fakemissile
  ClipSize                    = 1
  ClipReloadTime              = 60000
  AutoReloadsClip             = Yes
  AutoReloadWhenIdle          = 60000
  FireFX                      = FX_StealthHawkAttackAirstrike
End
```

### Area Effect Weapon
```
Weapon SCUDMissileDetonation
  PrimaryDamage               = 350.0
  PrimaryDamageRadius         = 40.0
  SecondaryDamage             = 200.0
  SecondaryDamageRadius       = 60.0
  AttackRange                 = 100.0
  DamageType                  = FLAME
  DeathType                   = EXPLODED
  RadiusDamageAffects         = ALLIES ENEMIES NEUTRALS NOT_SIMILAR
  FireSound                   = ScudLauncherWeapon
  DelayBetweenShots           = 30000
  ClipSize                    = 1
  ClipReloadTime              = 30000
  ProjectileCollidesWith      = STRUCTURES
  ShockWaveAmount             = 25.0
  ShockWaveRadius             = 70.0
  ShockWaveTaperOff           = 0.50
End
```

### Anti-Air Weapon
```
Weapon AntiAirMissile
  PrimaryDamage               = 100.0
  PrimaryDamageRadius         = 5.0
  AttackRange                 = 350.0
  MinimumAttackRange          = 20.0
  AcceptableAimDelta          = 3.0
  DamageType                  = EXPLOSION
  DeathType                   = EXPLODED
  WeaponSpeed                 = 1200.0
  ProjectileObject            = AntiAirMissile
  DelayBetweenShots           = 2000
  ClipSize                    = 4
  ClipReloadTime              = 8000
  AutoReloadsClip             = Yes
  RadiusDamageAffects         = ENEMIES
  AntiAirborneVehicle         = Yes
  AntiAirborneInfantry        = Yes
  AntiProjectile              = Yes
  AntiSmallMissile            = Yes
  FireSound                   = AntiAirMissileLaunch
  FireFX                      = FX_AntiAirLaunch
  ProjectileDetonationFX      = FX_AntiAirExplosion
End
```

### Point Defense Weapon
```
Weapon PointDefenseLaser
  PrimaryDamage               = 350.0
  PrimaryDamageRadius         = 22.5
  SecondaryDamage             = 85.0
  SecondaryDamageRadius       = 35.0
  AttackRange                 = 15.0
  DamageType                  = PENALTY
  DeathType                   = LASERED
  RadiusDamageAffects         = SELF ALLIES ENEMIES NEUTRALS
  WeaponSpeed                 = 999999.0
  DelayBetweenShots           = 1
  ClipSize                    = 0
  ClipReloadTime              = 0
  AcceptableAimDelta          = 999
  AntiSmallMissile            = No
  AntiProjectile              = No
  AntiAirborneVehicle         = No
  AntiAirborneInfantry        = No
  AntiBallisticMissile        = Yes
End
```

### Suicide Weapon
```
Weapon CarbombExplosion
  PrimaryDamage               = 500.0
  PrimaryDamageRadius         = 20.0
  AttackRange                 = 1.0
  DamageType                  = EXPLOSION
  DeathType                   = EXPLODED
  RadiusDamageAffects         = ALLIES ENEMIES NEUTRALS NOT_SIMILAR
  DamageDealtAtSelfPosition   = Yes
  WeaponSpeed                 = 999999.0
  ClipSize                    = 1
  ClipReloadTime              = 999999
  AutoReloadsClip             = No
  FireFX                      = FX_CarbombExplosion
  ShockWaveAmount             = 20.0
  ShockWaveRadius             = 25.0
  ShockWaveTaperOff           = 0.3
End
```

### Continuous Fire Weapon
```
Weapon MinigunWeapon
  PrimaryDamage               = 15.0
  PrimaryDamageRadius         = 0.0
  AttackRange                 = 250.0
  MinimumAttackRange          = 0.0
  AcceptableAimDelta          = 10.0
  DamageType                  = BULLET
  DeathType                   = NORMAL
  WeaponSpeed                 = 999999.0
  DelayBetweenShots           = 100
  ClipSize                    = 200
  ClipReloadTime              = 5000
  AutoReloadsClip             = Yes
  ContinuousFireOne           = 10
  ContinuousFireTwo           = 20
  ContinuousFireCoast         = 500
  FireSoundLoopTime           = 1000
  RadiusDamageAffects         = ENEMIES
  AntiGround                  = Yes
  AntiAirborneInfantry        = Yes
  FireSound                   = MinigunFire
  FireFX                      = FX_MinigunMuzzleFlash
  ShowsAmmoPips               = Yes
End
```

### Laser Weapon with Targeting Restrictions
```
Weapon LaserCannon
  PrimaryDamage               = 100.0
  PrimaryDamageRadius         = 2.0
  AttackRange                 = 400.0
  MinimumAttackRange          = 20.0
  AcceptableAimDelta          = 1.0
  DamageType                  = LASER
  DeathType                   = LASERED
  WeaponSpeed                 = 999999.0
  DelayBetweenShots           = 2000
  ClipSize                    = 10
  ClipReloadTime              = 8000
  AutoReloadsClip             = Yes
  LaserName                   = LaserBeam
  LaserBoneName               = Muzzle
  RadiusDamageAffects         = ENEMIES
  AntiGround                  = Yes
  AntiAirborneVehicle         = Yes
  FireSound                   = LaserCannonFire
  FireFX                      = FX_LaserCannonFire
  ProjectileDetonationFX      = FX_LaserImpact
End
```

### Scatter Weapon with Historic Bonus
```
Weapon ArtilleryCannon
  PrimaryDamage               = 200.0
  PrimaryDamageRadius         = 25.0
  SecondaryDamage             = 100.0
  SecondaryDamageRadius       = 40.0
  AttackRange                 = 500.0
  MinimumAttackRange          = 100.0
  AcceptableAimDelta          = 5.0
  DamageType                  = EXPLOSION
  DeathType                   = EXPLODED
  WeaponSpeed                 = 400.0
  ScaleWeaponSpeed            = Yes
  ProjectileObject            = ArtilleryShell
  DelayBetweenShots           = 8000
  ClipSize                    = 1
  ClipReloadTime              = 8000
  AutoReloadsClip             = Yes
  ScatterRadius               = 10.0
  ScatterTargetScalar         = 1.0
  ScatterTarget               = 5.0, 0.0
  ScatterTarget               = -5.0, 0.0
  ScatterTarget               = 0.0, 5.0
  ScatterTarget               = 0.0, -5.0
  HistoricBonusTime           = 10000
  HistoricBonusRadius         = 150.0
  HistoricBonusCount          = 3
  HistoricBonusWeapon         = NuclearStrike
  RadiusDamageAffects         = ALLIES ENEMIES NEUTRALS
  AntiGround                  = Yes
  FireSound                   = ArtilleryFire
  FireFX                      = FX_ArtilleryMuzzleFlash
  ProjectileDetonationFX      = FX_ArtilleryExplosion
  ProjectileCollidesWith      = STRUCTURES WALLS
  ShockWaveAmount             = 15.0
  ShockWaveRadius             = 35.0
  ShockWaveTaperOff           = 0.4
End
```

### Limited Area Effect Weapon
```
Weapon PrecisionStrike
  PrimaryDamage               = 500.0
  PrimaryDamageRadius         = 30.0
  AttackRange                 = 300.0
  DamageType                  = EXPLOSION
  DeathType                   = EXPLODED
  WeaponSpeed                 = 999999.0
  DelayBetweenShots           = 15000
  ClipSize                    = 1
  ClipReloadTime              = 15000
  AutoReloadsClip             = Yes
  RadiusDamageAffects         = ENEMIES
  RadiusDamageAffectsMaxSimultaneous = 3
  AntiGround                  = Yes
  FireSound                   = PrecisionStrikeLaunch
  FireFX                      = FX_PrecisionStrikeLaunch
  ProjectileDetonationFX      = FX_PrecisionStrikeExplosion
  ShockWaveAmount             = 20.0
  ShockWaveRadius             = 25.0
  ShockWaveTaperOff           = 0.3
End
```

### WeaponExtend Example *(GMX Zero Hour only)*

**Base Weapon:**
```
Weapon BaseTankCannon
  PrimaryDamage               = 150.0
  PrimaryDamageRadius         = 5.0
  SecondaryDamage             = 75.0
  SecondaryDamageRadius       = 15.0
  AttackRange                 = 300.0
  MinimumAttackRange          = 10.0
  AcceptableAimDelta          = 2.0
  DamageType                  = EXPLOSION
  DeathType                   = EXPLODED
  WeaponSpeed                 = 800.0
  ProjectileObject            = TankShell
  DelayBetweenShots           = 3000
  ClipSize                    = 1
  ClipReloadTime              = 3000
  AutoReloadsClip             = Yes
  RadiusDamageAffects         = ALLIES ENEMIES NEUTRALS
  AntiGround                  = Yes
  AntiAirborneVehicle         = Yes
  FireSound                   = TankCannonFire
  FireFX                      = FX_TankCannonMuzzleFlash
  ProjectileDetonationFX      = FX_ExplosionLarge
  ProjectileCollidesWith      = STRUCTURES WALLS
  ShockWaveAmount             = 10.0
  ShockWaveRadius             = 20.0
  ShockWaveTaperOff           = 0.5
End
```

**Extended Weapon (Veteran Variant):**
```
WeaponExtend VeteranTankCannon BaseTankCannon
  PrimaryDamage               = 200.0
  PrimaryDamageRadius         = 7.0
  AttackRange                 = 350.0
  FireFX                      = FX_TankCannonMuzzleFlashVeteran
  ProjectileDetonationFX      = FX_ExplosionLargeVeteran
End
```

**Extended Weapon (Elite Variant):**
```
WeaponExtend EliteTankCannon BaseTankCannon
  PrimaryDamage               = 250.0
  PrimaryDamageRadius         = 10.0
  SecondaryDamage             = 100.0
  AttackRange                 = 400.0
  WeaponSpeed                 = 1000.0
  FireFX                      = FX_TankCannonMuzzleFlashElite
  ProjectileDetonationFX      = FX_ExplosionLargeElite
End
```

In these examples, `VeteranTankCannon` and `EliteTankCannon` inherit all properties from `BaseTankCannon` and only override the properties that differ. This eliminates the need to duplicate 20+ properties for each variant.

## Usage

Weapons are defined in `.ini` files within the game's data directories in a root folder called "Weapon". Multiple weapon entries can exist in the same file or across multiple files. Each weapon must have a unique name. See Template for correct syntax.

**Limitations**:
- Each weapon must have a unique name - no two weapons can share the same name even across multiple files.
- Weapons are templates that are referenced by objects, not directly instantiated.
- Weapon slot assignment is handled by [WeaponSet](../WeaponSet.md), not by the Weapon template itself.
- **WeaponExtend** *(GMX Zero Hour only)*: The parent weapon must be defined before the `WeaponExtend` entry that references it. The parent weapon must exist in the same or a previously loaded INI file.

**Conditions**:
- Weapons are referenced by units, buildings, and special powers through [WeaponSet](../WeaponSet.md) to define their combat capabilities.
- When a weapon is assigned to a weapon slot, it becomes available for that object to use in combat.
- The game automatically selects the appropriate weapon slot based on target type, range, and weapon preferences.
- **WeaponExtend** *(GMX Zero Hour only)*: When using `WeaponExtend`, the new weapon inherits all properties from the parent weapon. You can then override any properties you want to change. Properties not specified in the `WeaponExtend` block retain their values from the parent weapon.

**Dependencies**:
- Weapons are assigned to objects through [WeaponSet](../WeaponSet.md) which manages multiple weapons on an object.
- Weapons that use projectiles require a valid [Object](../Object.md) template for the `ProjectileObject` property.
- Weapons that use visual effects require valid [FXList](../FXList.md) templates for `FireFX` and `ProjectileDetonationFX` properties.
- Weapons that use status effects require [`DamageType = STATUS`](Enum/DamageType.md) (see [DamageType documentation](Enum/DamageType.md)) and a valid `DamageStatusType` value.
- **WeaponExtend** *(GMX Zero Hour only)*: The parent weapon must exist and be fully defined before the `WeaponExtend` entry is processed.

## Template

```ini
Weapon WeaponName
  PrimaryDamage = 0.0                    ; // Main damage amount *(v1.04)*
  PrimaryDamageRadius = 0.0              ; // Primary damage radius *(v1.04)*
  SecondaryDamage = 0.0                  ; // Secondary damage amount *(v1.04)*
  SecondaryDamageRadius = 0.0            ; // Secondary damage radius *(v1.04)*
  DamageType = EXPLOSION                 ; // Damage type (see DamageType documentation) *(v1.04)*
  DeathType = NORMAL                     ; // Death animation type *(v1.04)*
  AttackRange = 0.0                      ; // Maximum attack range *(v1.04)*
  MinimumAttackRange = 0.0               ; // Minimum attack range *(v1.04)*
  AcceptableAimDelta = 0.0               ; // Aim accuracy requirement (degrees) *(v1.04)*
  WeaponSpeed = 999999.0                 ; // Projectile speed (distance per second) *(v1.04)*
  DelayBetweenShots = 0                  ; // Time between shots (milliseconds) *(v1.04)*
  ClipSize = 0                           ; // Shots per clip (0 = infinite) *(v1.04)*
  ClipReloadTime = 0                     ; // Reload time (milliseconds) *(v1.04)*
  AutoReloadsClip = YES                  ; // Auto-reload when clip empty *(v1.04)*
  RadiusDamageAffects = ALLIES ENEMIES NEUTRALS ; // What is affected by radius damage *(v1.04)*
  AntiGround = YES                       ; // Can target ground units *(v1.04)*
End
```

## Notes

- Weapons are defined in `.ini` files within the game's data directories in a root folder called "Weapon".
- Each weapon must have a unique name - no two weapons can share the same name even across multiple files.
- Weapons can be referenced by units, buildings, and special powers.
- Veterancy levels affect visual effects and object creation lists.
- Projectile weapons create separate objects that handle their own movement and collision.
- Status effect weapons use [`DamageType = STATUS`](Enum/DamageType.md) (see [DamageType documentation](Enum/DamageType.md)) and specify the effect in [DamageStatusType](#damagestatustype).
- Area effect weapons use radius damage properties to affect multiple targets.
- Anti-air weapons should target airborne units and projectiles appropriately.
- Point defense weapons typically have very short ranges but high damage and fast firing rates.

### WeaponExtend Feature *(GMX Zero Hour only)*

**What is WeaponExtend?**

`WeaponExtend` is a powerful feature that allows you to create new weapons by inheriting all properties from an existing parent weapon, then overriding only the properties you want to change. This eliminates the need to duplicate dozens of properties when creating weapon variants, making your mods more maintainable and easier to update.

**How It Works:**

1. **Syntax**: `WeaponExtend NewWeaponName ParentWeaponName`
   - `NewWeaponName`: The name of the new weapon you're creating
   - `ParentWeaponName`: The name of an existing weapon to inherit from

2. **Inheritance**: All properties from the parent weapon are copied to the new weapon, including damage values, range, firing mechanics, visual effects, targeting rules, and all other properties.

3. **Override**: After inheritance, you can specify any properties you want to change. Only the properties you explicitly set will override the inherited values.

4. **Order Dependency**: The parent weapon must be defined before the `WeaponExtend` entry. This means the parent weapon must appear earlier in the same INI file, or in a file that was loaded earlier.

**Use Cases:**

1. **Veteran/Elite Variants**: Create upgraded versions of weapons for veteran or elite units by extending the base weapon and only changing damage, range, or visual effects.

2. **Faction Variants**: Create faction-specific versions of similar weapons (e.g., USA, China, and GLA versions of a tank cannon) that share most properties but differ in damage, range, or visual style.

3. **Upgrade Paths**: Create weapon upgrade chains where each tier extends the previous tier, making it easy to maintain consistency across upgrade levels.

4. **Modular Weapon Design**: Define base weapon templates with common properties, then create specific variants for different units without duplicating code.

5. **Balancing**: When balancing weapons, you can update the base weapon and all extended weapons will automatically inherit the changes (except for properties they explicitly override).

**Benefits:**

- **Reduced Code Duplication**: Instead of copying 30+ properties for each variant, you only specify the differences (often just 3-5 properties).

- **Easier Maintenance**: When you need to update shared properties (like sound effects or projectile types), you only update the parent weapon and all extended weapons automatically inherit the changes.

- **Consistency**: Ensures that related weapons share the same base properties, reducing the chance of inconsistencies or bugs.

- **Readability**: Makes it immediately clear which properties differ between variants, improving code readability and understanding.

- **Scalability**: Makes it easy to create many weapon variants without exponentially increasing file size and complexity.

**Example Use Case - Weapon Upgrade Chain:**

```
Weapon BasicRifle
  PrimaryDamage = 25.0
  AttackRange = 200.0
  DelayBetweenShots = 1000
  ClipSize = 30
  FireSound = RifleFire
  FireFX = FX_RifleMuzzleFlash
  ; ... 20+ more properties ...
End

WeaponExtend AdvancedRifle BasicRifle
  PrimaryDamage = 35.0
  AttackRange = 250.0
  FireSound = AdvancedRifleFire
End

WeaponExtend EliteRifle AdvancedRifle
  PrimaryDamage = 45.0
  AttackRange = 300.0
  ClipSize = 40
  FireFX = FX_EliteRifleMuzzleFlash
End
```

In this example, `AdvancedRifle` inherits all properties from `BasicRifle` and only changes damage, range, and sound. `EliteRifle` then inherits from `AdvancedRifle` (which already has the advanced properties), creating a clear upgrade chain. If you need to change a shared property like `ProjectileObject`, you only update `BasicRifle` and all variants inherit the change automatically.

## Modder Recommended Use Scenarios

(pending modder review)

## Source Files

**Header (GMX Zero Hour):** [Weapon.h](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h)
- `WeaponTemplate` class definition and related enums

**Source (GMX Zero Hour):** [Weapon.cpp](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Weapon.cpp)

**Header (GMX Generals):** [Weapon.h](../../Generals/Code/GameEngine/Include/GameLogic/Weapon.h)
- `WeaponTemplate` class definition and related enums

**Source (GMX Generals):** [Weapon.cpp](../../Generals/Code/GameEngine/Source/GameLogic/Object/Weapon.cpp)

## Changes History

### GMX Zero Hour

- **Directory-Based File Loading** *(GMX Generals, GMX Zero Hour)*: Changed from loading weapons from a single `weapon.ini` file to loading from the entire `Data\INI\Weapon\` directory. This allows modders to organize weapon definitions across multiple files for better maintainability. In GMX Zero Hour, files named `Weapon.ini` or files with the `.weapon.ini` extension (e.g., `tanks.weapon.ini`, `scorpion.weapon.ini`) are loaded, while GMX Generals loads any `.ini` files in the directory. This is a significant improvement over Retail versions which only load from the single `weapon.ini` file.

- **WeaponExtend Feature** *(GMX Zero Hour only)*: Added `WeaponExtend` support allowing weapons to inherit properties from parent weapons. This feature enables creating weapon variants by extending existing weapons and overriding only the properties that need to change, significantly reducing code duplication and improving maintainability. The parent weapon must be defined before the `WeaponExtend` entry. All properties from the parent are copied, then any properties specified in the `WeaponExtend` block override the inherited values.

## Document Log

- 16/12/2025 — AI — Initial document created.

## Status

- Documentation Status: AI-generated
- Last Updated: 16/12/2025 by @AI
- Certification: 0/2 reviews

## Reviewers

- [ ] Reviewer 1
- [ ] Reviewer 2
