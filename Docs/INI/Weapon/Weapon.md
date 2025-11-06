# Weapon INI Documentation

## Overview
The `Weapon` class defines the properties and behavior of weapons in the game. Weapons are used by units, buildings, and special powers to deal damage, apply status effects, or trigger other game mechanics. Each weapon template specifies damage values, range, firing mechanics, visual effects, and targeting rules.

## Source Files

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h`](../GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h#338) - `Weapon` class definition
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Weapon.cpp`](../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Weapon.cpp#162) - `TheWeaponFieldParseTable` parsing logic

## Usage
Weapons are defined in `.ini` files within the game's data directories in a root folder called "Weapon". They are referenced by units, buildings, and special powers to define their combat capabilities and special abilities.

## Table of Contents
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
- [Best Practices](#best-practices)
- [Notes](#notes)

## Properties

### Basic Damage Properties

#### `PrimaryDamage` *(v1.04)*
- **Type**: `Real`
- **Description**: The main damage amount dealt by this weapon
- **Example**: `PrimaryDamage = 350.0`

#### `PrimaryDamageRadius` *(v1.04)*
- **Type**: `Real`
- **Description**: The radius of the primary damage area
- **Example**: `PrimaryDamageRadius = 40.0`

#### `SecondaryDamage` *(v1.04)*
- **Type**: `Real`
- **Description**: Additional damage dealt in a secondary radius (optional)
- **Example**: `SecondaryDamage = 200.0`

#### `SecondaryDamageRadius` *(v1.04)*
- **Type**: `Real`
- **Description**: The radius of the secondary damage area
- **Example**: `SecondaryDamageRadius = 60.0`

#### `DamageType` *(v1.04)*
- **Type**: `DamageType`
- **Description**: The type of damage this weapon deals
- **Example**: `DamageType = EXPLOSION`
- **Available Values**: See [DamageType Values](#damagetype-values) section below

#### `DeathType` *(v1.04)*
- **Type**: `DeathType`
- **Description**: The type of death animation/effect when this weapon kills a target
- **Example**: `DeathType = EXPLODED`
- **Available Values**: See [DeathType Values](#deathtype-values) section below

#### `DamageStatusType` *(v1.04, Generals Zero Hour only)*
- **Type**: `ObjectStatusTypes`
- **Description**: If the damage type is STATUS, this specifies which status effect to apply
- **Example**: `DamageStatusType = CAN_ATTACK`
- **Available Values**: See [ObjectStatusTypes Values](#objectstatustypes-values) section below

### Range and Targeting

#### `AttackRange` *(v1.04)*
- **Type**: `Real`
- **Description**: Maximum distance the weapon can attack targets
- **Example**: `AttackRange = 450.0`

#### `MinimumAttackRange` *(v1.04)*
- **Type**: `Real`
- **Description**: Minimum distance required to attack (prevents close-range attacks)
- **Example**: `MinimumAttackRange = 5.0`

#### `AcceptableAimDelta` *(v1.04)*
- **Type**: `Real` (angle)
- **Description**: How accurately the weapon must aim before firing (in degrees)
- **Example**: `AcceptableAimDelta = 1`

#### `RequestAssistRange` *(v1.04)*
- **Type**: `Real`
- **Description**: Range within which other units will be called to assist in attacks
- **Example**: `RequestAssistRange = 100.0`

### Firing Mechanics

#### `DelayBetweenShots` *(v1.04)*
- **Type**: `Int` (milliseconds)
- **Description**: Time between individual shots
- **Example**: `DelayBetweenShots = 1000`

#### `ClipSize` *(v1.04)*
- **Type**: `Int`
- **Description**: Number of shots in a clip (0 = infinite)
- **Example**: `ClipSize = 30`

#### `ClipReloadTime` *(v1.04)*
- **Type**: `Int` (milliseconds)
- **Description**: Time required to reload an empty clip
- **Example**: `ClipReloadTime = 3000`

#### `AutoReloadsClip` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether the weapon automatically reloads when clip is empty
- **Example**: `AutoReloadsClip = Yes`

#### `AutoReloadWhenIdle` *(v1.04)*
- **Type**: `Int` (milliseconds)
- **Description**: Time of inactivity before weapon automatically reloads
- **Example**: `AutoReloadWhenIdle = 5000`

#### `PreAttackDelay` *(v1.04)*
- **Type**: `Int` (milliseconds)
- **Description**: Delay before weapon fires (for aiming, charging, etc.)
- **Example**: `PreAttackDelay = 2000`

#### `PreAttackType` *(v1.04)*
- **Type**: `WeaponPrefireType`
- **Description**: When the pre-attack delay is applied
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
- **Description**: Visual effects played when weapon fires
- **Example**: `FireFX = FX_TankCannonFire`

#### `ProjectileDetonationFX` *(v1.04)*
- **Type**: `FXList` (per veterancy level)
- **Description**: Visual effects played when projectile hits target
- **Example**: `ProjectileDetonationFX = FX_ExplosionLarge`

#### `FireSound` *(v1.04)*
- **Type**: `AudioEventRTS`
- **Description**: Sound played when weapon fires
- **Example**: `FireSound = TankCannonFire`

#### `FireSoundLoopTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Duration for looping fire sounds
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

### Targeting and Collision

#### `RadiusDamageAffects` *(v1.04)*
- **Type**: `WeaponAffectsMaskType` (bit flags)
- **Description**: What types of objects are affected by radius damage
- **Example**: `RadiusDamageAffects = ALLIES ENEMIES NEUTRALS`
- **Available Values**: See [WeaponAffectsMaskType Values](#weaponaffectsmasktype-values) section below

#### `RadiusDamageAffectsMaxSimultaneous` *(GMX Upcoming)*
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

#### `TargetAllowedKindOf` *(v1.04, Generals Zero Hour only)*
- **Type**: `KindOfMaskType` (bit flags)
- **Description**: Objects must have at least one of these KindOf bits to be targeted
- **Example**: `TargetAllowedKindOf = VEHICLE BUILDING`
- **Available Values**: See [KindOfMaskType Values](#kindofmasktype-values) section below

#### `TargetForbidKindOf` *(v1.04, Generals Zero Hour only)*
- **Type**: `KindOfMaskType` (bit flags)
- **Description**: Objects must have NONE of these KindOf bits to be targeted
- **Example**: `TargetForbidKindOf = FRIENDLY_INFANTRY`
- **Available Values**: See [KindOfMaskType Values](#kindofmasktype-values) section below

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
- **Description**: Random scatter radius for inaccurate weapons
- **Example**: `ScatterRadius = 5.0`

#### `ScatterTargetScalar` *(v1.04)*
- **Type**: `Real`
- **Description**: Scalar for scatter target coordinates
- **Example**: `ScatterTargetScalar = 1.0`

#### `ScatterRadiusVsInfantry` *(v1.04)*
- **Type**: `Real`
- **Description**: Additional scatter when targeting infantry
- **Example**: `ScatterRadiusVsInfantry = 10.0`

#### `DamageDealtAtSelfPosition` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether damage is dealt at the firing unit's position (for suicide weapons)
- **Example**: `DamageDealtAtSelfPosition = Yes`

#### `ContinueAttackRange` *(v1.04)*
- **Type**: `Real`
- **Description**: Range to search for similar targets after destroying one
- **Example**: `ContinueAttackRange = 50.0`

#### `MinTargetPitch` *(v1.04)*
- **Type**: `Real` (angle)
- **Description**: Minimum pitch angle required to target
- **Example**: `MinTargetPitch = -30.0`

#### `MaxTargetPitch` *(v1.04)*
- **Type**: `Real` (angle)
- **Description**: Maximum pitch angle allowed to target
- **Example**: `MaxTargetPitch = 30.0`

#### `RadiusDamageAngle` *(v1.04, Generals Zero Hour only)*
- **Type**: `Real` (angle)
- **Description**: Cone angle for directional radius damage
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

#### `CanAttackWithoutTarget` *(v1.04, Generals Zero Hour only)*
- **Type**: `Bool`
- **Description**: Whether weapon can attack ground positions without a specific target
- **Example**: `CanAttackWithoutTarget = Yes`

#### `LeechRangeWeapon` *(v1.04)*
- **Type**: `Bool`
- **Description**: Once fired at proper range, gains unlimited range for remainder of attack cycle
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

## Enum Value Lists

#### `DamageType` Values *(v1.04)*
**Source:** [Damage.h](../GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h) - `DamageType` enum definition

- **`EXPLOSION`** *(v1.04)* - Standard explosive damage
- **`FLAME`** *(v1.04)* - Fire damage
- **`LASER`** *(v1.04)* - Laser/energy damage
- **`BULLET`** *(v1.04)* - Bullet/kinetic damage
- **`STATUS`** *(v1.04)* - Status effect damage (uses DamageStatusType)
- **`PENALTY`** *(v1.04)* - Penalty damage (reduces effectiveness)
- **`AURORA_BOMB`** *(v1.04)* - Aurora bomb damage
- **`SUBDUAL`** *(v1.04)* - Subdual damage (disables without destroying)
- **`POISON`** *(v1.04)* - Poison damage
- **`SNIPER`** *(v1.04)* - Sniper damage
- **`GATLING`** *(v1.04)* - Gatling gun damage
- **`CANNON`** *(v1.04)* - Cannon damage
- **`ROCKET`** *(v1.04)* - Rocket damage
- **`MISSILE`** *(v1.04)* - Missile damage
- **`BOMB`** *(v1.04)* - Bomb damage
- **`GRENADE`** *(v1.04)* - Grenade damage
- **`MINE`** *(v1.04)* - Mine damage
- **`SUICIDE`** *(v1.04)* - Suicide attack damage
- **`CRUSH`** *(v1.04)* - Crushing damage
- **`DEPLOY`** *(v1.04)* - Deploy damage
- **`DETONATE`** *(v1.04)* - Detonation damage
- **`KINETIC`** *(v1.04)* - Kinetic energy damage
- **`PLASMA`** *(v1.04)* - Plasma damage
- **`ELECTRIC`** *(v1.04)* - Electric damage
- **`ACID`** *(v1.04)* - Acid damage
- **`FREEZE`** *(v1.04)* - Freeze damage
- **`EMP`** *(v1.04)* - EMP damage
- **`RADIATION`** *(v1.04)* - Radiation damage
- **`SONIC`** *(v1.04)* - Sonic damage
- **`PSYCHIC`** *(v1.04)* - Psychic damage
- **`MAGIC`** *(v1.04)* - Magic damage
- **`DIVINE`** *(v1.04)* - Divine damage
- **`CHAOS`** *(v1.04)* - Chaos damage
- **`VOID`** *(v1.04)* - Void damage
- **`EXTRA_1`** through **`EXTRA_10`** *(v1.04)* - Custom damage types

#### `DeathType` Values *(v1.04)*
**Source:** [Damage.h](../GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h) - `DeathType` enum definition

- **`NORMAL`** *(v1.04)* - Standard death animation
- **`EXPLODED`** *(v1.04)* - Explosion death
- **`BURNED`** *(v1.04)* - Fire death
- **`LASERED`** *(v1.04)* - Laser death
- **`SUICIDED`** *(v1.04)* - Suicide death
- **`CRUSHED`** *(v1.04)* - Crushed death
- **`DETONATED`** *(v1.04)* - Detonation death
- **`EXTRA_1`** through **`EXTRA_10`** *(v1.04)* - Custom death types

#### `WeaponPrefireType` Values *(v1.04)*
**Source:** [Weapon.h](../GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h#77) - `WeaponPrefireType` enum definition

- **`PER_SHOT`** *(v1.04)* - Prefire delay for every shot
- **`PER_ATTACK`** *(v1.04)* - Prefire delay for each new target
- **`PER_CLIP`** *(v1.04)* - Prefire delay for each new clip

#### `WeaponAffectsMaskType` Values *(v1.04)*
**Source:** [Weapon.h](../GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h#110) - `WeaponAffectsMaskType` enum definition

- **`SELF`** *(v1.04)* - Affects the firing unit
- **`ALLIES`** *(v1.04)* - Affects allied units
- **`ENEMIES`** *(v1.04)* - Affects enemy units
- **`NEUTRALS`** *(v1.04)* - Affects neutral units
- **`SUICIDE`** *(v1.04)* - Ensures firing unit cannot survive self-damage
- **`NOT_SIMILAR`** *(v1.04)* - Doesn't affect similar units (prevents chain reactions)
- **`NOT_AIRBORNE`** *(v1.04)* - Doesn't affect airborne units (unless primary target)

#### `WeaponCollideMaskType` Values *(v1.04)*
**Source:** [Weapon.h](../GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h#136) - `WeaponCollideMaskType` enum definition

- **`ALLIES`** *(v1.04)* - Projectiles collide with allied units
- **`ENEMIES`** *(v1.04)* - Projectiles collide with enemy units
- **`STRUCTURES`** *(v1.04)* - Projectiles collide with structures
- **`SHRUBBERY`** *(v1.04)* - Projectiles collide with shrubbery
- **`PROJECTILES`** *(v1.04)* - Projectiles collide with other projectiles
- **`WALLS`** *(v1.04)* - Projectiles collide with walls
- **`SMALL_MISSILES`** *(v1.04)* - Projectiles collide with small missiles
- **`BALLISTIC_MISSILES`** *(v1.04)* - Projectiles collide with ballistic missiles
- **`CONTROLLED_STRUCTURES`** *(v1.04)* - Projectiles collide with structures controlled by the same player

#### `ObjectStatusTypes` Values *(v1.04)*
**Source:** [ObjectStatusTypes.h](../GeneralsMD/Code/GameEngine/Include/Common/ObjectStatusTypes.h) - `ObjectStatusTypes` enum definition

- **`CAN_ATTACK`** *(v1.04)* - Can attack status
- **`CAN_MOVE`** *(v1.04)* - Can move status
- **`CAN_FIRE_WEAPON`** *(v1.04)* - Can fire weapon status
- **`CAN_RECEIVE_COMMANDS`** *(v1.04)* - Can receive commands status
- **`CAN_BE_REPAIRED`** *(v1.04)* - Can be repaired status
- **`CAN_BE_HEALED`** *(v1.04)* - Can be healed status
- **`CAN_BE_UPGRADED`** *(v1.04)* - Can be upgraded status
- **`CAN_BE_CONVERTED`** *(v1.04)* - Can be converted status
- **`CAN_BE_CAPTURED`** *(v1.04)* - Can be captured status
- **`CAN_BE_DESTROYED`** *(v1.04)* - Can be destroyed status
- **`CAN_BE_DISABLED`** *(v1.04)* - Can be disabled status
- **`CAN_BE_STUNNED`** *(v1.04)* - Can be stunned status
- **`CAN_BE_SUBDUED`** *(v1.04)* - Can be subdued status
- **`CAN_BE_ELECTRONICALLY_DISABLED`** *(v1.04)* - Can be electronically disabled status
- **`CAN_BE_EMPED`** *(v1.04)* - Can be EMPed status
- **`CAN_BE_POISONED`** *(v1.04)* - Can be poisoned status
- **`CAN_BE_FROZEN`** *(v1.04)* - Can be frozen status
- **`CAN_BE_BURNED`** *(v1.04)* - Can be burned status
- **`CAN_BE_SHOCKED`** *(v1.04)* - Can be shocked status
- **`CAN_BE_ACIDED`** *(v1.04)* - Can be acid damaged status
- **`CAN_BE_RADIATED`** *(v1.04)* - Can be radiated status
- **`CAN_BE_SONICED`** *(v1.04)* - Can be sonic damaged status
- **`CAN_BE_PSYCHICED`** *(v1.04)* - Can be psychic damaged status
- **`CAN_BE_MAGICED`** *(v1.04)* - Can be magic damaged status
- **`CAN_BE_DIVINED`** *(v1.04)* - Can be divine damaged status
- **`CAN_BE_CHAOSED`** *(v1.04)* - Can be chaos damaged status
- **`CAN_BE_VOIDED`** *(v1.04)* - Can be void damaged status
- **`EXTRA_1`** through **`EXTRA_10`** *(v1.04)* - Custom status types

#### `KindOfMaskType` Values *(v1.04)*
**Source:** [KindOf.cpp](../GeneralsMD/Code/GameEngine/Source/Common/System/KindOf.cpp#35) - `KindOfMaskType::s_bitNameList[]` array definition

- **`OBSTACLE`** *(v1.04)* - Obstacle objects
- **`SELECTABLE`** *(v1.04)* - Selectable objects
- **`IMMOBILE`** *(v1.04)* - Immobile objects
- **`CAN_ATTACK`** *(v1.04)* - Objects that can attack
- **`STICK_TO_TERRAIN_SLOPE`** *(v1.04)* - Objects that stick to terrain slopes
- **`CAN_CAST_REFLECTIONS`** *(v1.04)* - Objects that can cast reflections
- **`SHRUBBERY`** *(v1.04)* - Shrubbery/vegetation
- **`STRUCTURE`** *(v1.04)* - Building structures
- **`INFANTRY`** *(v1.04)* - Infantry units
- **`VEHICLE`** *(v1.04)* - Vehicle units
- **`AIRCRAFT`** *(v1.04)* - Aircraft units
- **`HUGE_VEHICLE`** *(v1.04)* - Large vehicle units
- **`DOZER`** *(v1.04)* - Dozer vehicles
- **`HARVESTER`** *(v1.04)* - Harvester vehicles
- **`COMMANDCENTER`** *(v1.04)* - Command center buildings
- **`PRISON`** *(v1.04)* - Prison buildings *(if ALLOW_SURRENDER enabled)*
- **`COLLECTS_PRISON_BOUNTY`** *(v1.04)* - Objects that collect prison bounty *(if ALLOW_SURRENDER enabled)*
- **`POW_TRUCK`** *(v1.04)* - Prisoner of War trucks *(if ALLOW_SURRENDER enabled)*
- **`LINEBUILD`** *(v1.04)* - Line building structures
- **`SALVAGER`** *(v1.04)* - Salvager units
- **`WEAPON_SALVAGER`** *(v1.04)* - Weapon salvager units
- **`TRANSPORT`** *(v1.04)* - Transport units
- **`BRIDGE`** *(v1.04)* - Bridge structures
- **`LANDMARK_BRIDGE`** *(v1.04)* - Landmark bridge structures
- **`BRIDGE_TOWER`** *(v1.04)* - Bridge tower structures
- **`PROJECTILE`** *(v1.04)* - Projectile objects
- **`PRELOAD`** *(v1.04)* - Preloaded objects
- **`NO_GARRISON`** *(v1.04)* - Objects that cannot be garrisoned
- **`WAVEGUIDE`** *(v1.04)* - Wave guide objects
- **`WAVE_EFFECT`** *(v1.04)* - Wave effect objects
- **`NO_COLLIDE`** *(v1.04)* - Objects that don't collide
- **`REPAIR_PAD`** *(v1.04)* - Repair pad structures
- **`HEAL_PAD`** *(v1.04)* - Heal pad structures
- **`STEALTH_GARRISON`** *(v1.04)* - Stealth garrison structures
- **`CASH_GENERATOR`** *(v1.04)* - Cash generator structures
- **`DRAWABLE_ONLY`** *(v1.04)* - Drawable only objects
- **`MP_COUNT_FOR_VICTORY`** *(v1.04)* - Multiplayer victory count objects
- **`REBUILD_HOLE`** *(v1.04)* - Rebuild hole structures
- **`SCORE`** *(v1.04)* - Score objects
- **`SCORE_CREATE`** *(v1.04)* - Score creation objects
- **`SCORE_DESTROY`** *(v1.04)* - Score destruction objects
- **`NO_HEAL_ICON`** *(v1.04)* - Objects without heal icon
- **`CAN_RAPPEL`** *(v1.04)* - Objects that can rappel
- **`PARACHUTABLE`** *(v1.04)* - Parachutable objects
- **`CAN_SURRENDER`** *(v1.04)* - Objects that can surrender *(if ALLOW_SURRENDER enabled)*
- **`CAN_BE_REPULSED`** *(v1.04)* - Objects that can be repulsed
- **`MOB_NEXUS`** *(v1.04)* - Mob nexus objects
- **`IGNORED_IN_GUI`** *(v1.04)* - Objects ignored in GUI
- **`CRATE`** *(v1.04)* - Crate objects
- **`CAPTURABLE`** *(v1.04)* - Capturable objects
- **`CLEARED_BY_BUILD`** *(v1.04)* - Objects cleared by building
- **`SMALL_MISSILE`** *(v1.04)* - Small missile projectiles
- **`ALWAYS_VISIBLE`** *(v1.04)* - Always visible objects
- **`UNATTACKABLE`** *(v1.04)* - Unattackable objects
- **`MINE`** *(v1.04)* - Mine objects
- **`CLEANUP_HAZARD`** *(v1.04)* - Cleanup hazard objects
- **`PORTABLE_STRUCTURE`** *(v1.04)* - Portable structure objects
- **`ALWAYS_SELECTABLE`** *(v1.04)* - Always selectable objects
- **`ATTACK_NEEDS_LINE_OF_SIGHT`** *(v1.04)* - Objects requiring line of sight to attack
- **`WALK_ON_TOP_OF_WALL`** *(v1.04)* - Objects that walk on top of walls
- **`DEFENSIVE_WALL`** *(v1.04)* - Defensive wall structures
- **`FS_POWER`** *(v1.04)* - Firestorm power structures
- **`FS_FACTORY`** *(v1.04)* - Firestorm factory structures
- **`FS_BASE_DEFENSE`** *(v1.04)* - Firestorm base defense structures
- **`FS_TECHNOLOGY`** *(v1.04)* - Firestorm technology structures
- **`AIRCRAFT_PATH_AROUND`** *(v1.04)* - Objects aircraft path around
- **`LOW_OVERLAPPABLE`** *(v1.04)* - Low overlappable objects
- **`FORCEATTACKABLE`** *(v1.04)* - Force attackable objects
- **`AUTO_RALLYPOINT`** *(v1.04)* - Auto rally point objects
- **`TECH_BUILDING`** *(v1.04)* - Technology buildings
- **`POWERED`** *(v1.04)* - Powered structures
- **`PRODUCED_AT_HELIPAD`** *(v1.04)* - Objects produced at helipad
- **`DRONE`** *(v1.04)* - Drone objects
- **`CAN_SEE_THROUGH_STRUCTURE`** *(v1.04)* - Objects that can see through structures
- **`BALLISTIC_MISSILE`** *(v1.04)* - Ballistic missile projectiles
- **`CLICK_THROUGH`** *(v1.04)* - Click through objects
- **`SUPPLY_SOURCE_ON_PREVIEW`** *(v1.04)* - Supply source on preview objects
- **`PARACHUTE`** *(v1.04)* - Parachute objects
- **`GARRISONABLE_UNTIL_DESTROYED`** *(v1.04)* - Garrisonable until destroyed objects
- **`BOAT`** *(v1.04)* - Boat objects
- **`IMMUNE_TO_CAPTURE`** *(v1.04)* - Immune to capture objects
- **`HULK`** *(v1.04)* - Hulk objects
- **`SHOW_PORTRAIT_WHEN_CONTROLLED`** *(v1.04)* - Show portrait when controlled objects
- **`SPAWNS_ARE_THE_WEAPONS`** *(v1.04)* - Spawns are the weapons objects
- **`CANNOT_BUILD_NEAR_SUPPLIES`** *(v1.04)* - Cannot build near supplies objects
- **`SUPPLY_SOURCE`** *(v1.04)* - Supply source objects
- **`REVEAL_TO_ALL`** *(v1.04)* - Reveal to all objects
- **`DISGUISER`** *(v1.04)* - Disguiser objects
- **`INERT`** *(v1.04)* - Inert objects
- **`HERO`** *(v1.04)* - Hero objects
- **`IGNORES_SELECT_ALL`** *(v1.04)* - Ignores select all objects
- **`DONT_AUTO_CRUSH_INFANTRY`** *(v1.04)* - Don't auto crush infantry objects
- **`CLIFF_JUMPER`** *(v1.04)* - Cliff jumper objects
- **`FS_SUPPLY_DROPZONE`** *(v1.04)* - Firestorm supply dropzone structures
- **`FS_SUPERWEAPON`** *(v1.04)* - Firestorm superweapon structures
- **`FS_BLACK_MARKET`** *(v1.04)* - Firestorm black market structures
- **`FS_SUPPLY_CENTER`** *(v1.04)* - Firestorm supply center structures
- **`FS_STRATEGY_CENTER`** *(v1.04)* - Firestorm strategy center structures
- **`MONEY_HACKER`** *(v1.04)* - Money hacker objects
- **`ARMOR_SALVAGER`** *(v1.04)* - Armor salvager objects
- **`REVEALS_ENEMY_PATHS`** *(v1.04)* - Reveals enemy paths objects
- **`BOOBY_TRAP`** *(v1.04)* - Booby trap objects
- **`FS_FAKE`** *(v1.04)* - Firestorm fake structures
- **`FS_INTERNET_CENTER`** *(v1.04)* - Firestorm internet center structures
- **`BLAST_CRATER`** *(v1.04)* - Blast crater objects
- **`PROP`** *(v1.04)* - Prop objects
- **`OPTIMIZED_TREE`** *(v1.04)* - Optimized tree objects
- **`FS_ADVANCED_TECH`** *(v1.04)* - Firestorm advanced tech structures
- **`FS_BARRACKS`** *(v1.04)* - Firestorm barracks structures
- **`FS_WARFACTORY`** *(v1.04)* - Firestorm war factory structures
- **`FS_AIRFIELD`** *(v1.04)* - Firestorm airfield structures
- **`AIRCRAFT_CARRIER`** *(v1.04)* - Aircraft carrier objects
- **`NO_SELECT`** *(v1.04)* - No select objects
- **`REJECT_UNMANNED`** *(v1.04)* - Reject unmanned objects
- **`CANNOT_RETALIATE`** *(v1.04)* - Cannot retaliate objects
- **`TECH_BASE_DEFENSE`** *(v1.04)* - Tech base defense objects
- **`EMP_HARDENED`** *(v1.04)* - EMP hardened objects
- **`DEMOTRAP`** *(v1.04)* - Demo trap objects
- **`CONSERVATIVE_BUILDING`** *(v1.04)* - Conservative building objects
- **`IGNORE_DOCKING_BONES`** *(v1.04)* - Ignore docking bones objects
- **`TANK`** *(v1.04)* - Tank vehicles
- **`APC`** *(v1.04)* - Armored Personnel Carrier vehicles
- **`IFV`** *(v1.04)* - Infantry Fighting Vehicle vehicles
- **`TRUCK`** *(v1.04)* - Truck vehicles
- **`VTOL`** *(v1.04)* - Vertical Take-Off and Landing aircraft
- **`JET`** *(v1.04)* - Jet aircraft
- **`HELICOPTER`** *(v1.04)* - Helicopter aircraft
- **`HOT_AIR_BALLOON`** *(v1.04)* - Hot air balloon aircraft
- **`BLIMP`** *(v1.04)* - Blimp aircraft
- **`LARGE_AIRCRAFT`** *(v1.04)* - Large aircraft
- **`MEDIUM_AIRCRAFT`** *(v1.04)* - Medium aircraft
- **`SMALL_AIRCRAFT`** *(v1.04)* - Small aircraft
- **`ARTILLERY`** *(v1.04)* - Artillery units
- **`HEAVY_ARTILLERY`** *(v1.04)* - Heavy artillery units
- **`ANTI_AIR`** *(v1.04)* - Anti-air units
- **`SAM`** *(v1.04)* - Surface-to-Air Missile units
- **`SCOUT`** *(v1.04)* - Scout units
- **`COMMANDO`** *(v1.04)* - Commando units
- **`HEAVY_INFANTRY`** *(v1.04)* - Heavy infantry units
- **`SUPERHEAVY_VEHICLE`** *(v1.04)* - Super heavy vehicle units
- **`EW_RADAR`** *(v1.04)* - Electronic Warfare radar units
- **`EW_RADAR_JAMMER`** *(v1.04)* - Electronic Warfare radar jammer units
- **`EW_RADIO_JAMMER`** *(v1.04)* - Electronic Warfare radio jammer units
- **`EW_JAMMABLE`** *(v1.04)* - Electronic Warfare jammable units
- **`EW_DIRECT_JAMMABLE`** *(v1.04)* - Electronic Warfare directly jammable units
- **`EW_AREA_JAMMABLE`** *(v1.04)* - Electronic Warfare area jammable units
- **`EW_RADIO_JAMMABLE`** *(v1.04)* - Electronic Warfare radio jammable units
- **`EXTRA1`** through **`EXTRA16`** *(v1.04)* - Custom KindOf types

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
  TargetAllowedKindOf         = VEHICLE BUILDING
  TargetForbidKindOf          = INFANTRY
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

## Best Practices

### Weapon Design
1. **Balanced damage values** - Ensure primary and secondary damage are appropriate for the weapon type
2. **Realistic ranges** - Set attack ranges that make sense for the weapon type
3. **Appropriate reload times** - Balance clip size and reload time for gameplay
4. **Clear targeting rules** - Use anti-mask flags to define what the weapon can target

### Performance Considerations
1. **Efficient projectile use** - Only use projectiles when necessary
2. **Reasonable effect ranges** - Keep radius damage areas reasonable
3. **Optimized sound loops** - Use FireSoundLoopTime for continuous weapons
4. **Appropriate pre-attack delays** - Don't make delays too long for player experience

### Visual and Audio Design
1. **Matching effects** - Ensure FireFX and ProjectileDetonationFX match the weapon type
2. **Appropriate sounds** - Use FireSound that matches the weapon's power and type
3. **Veterancy effects** - Use per-veterancy level effects for visual progression
4. **Consistent theming** - Match effects to the faction and weapon type

### Targeting and Collision
1. **Logical targeting** - Set anti-mask flags that make sense for the weapon
2. **Appropriate collision** - Use ProjectileCollidesWith to prevent unrealistic behavior
3. **Radius damage rules** - Use RadiusDamageAffects to control area effect behavior
4. **Friendly fire consideration** - Be careful with radius damage affecting allies

### Advanced Features
1. **Shockwave effects** - Use for powerful explosive weapons
2. **Scatter mechanics** - Use for inaccurate or area-effect weapons
3. **Status effects** - Use DamageType = STATUS for non-damaging effects
4. **Special mechanics** - Use DamageDealtAtSelfPosition for suicide weapons

## Notes
- Weapons are defined in `.ini` files within the game's data directories in a root folder called "Weapon"
- Each weapon must have a unique name - no two weapons can share the same name even across multiple files
- Weapons can be referenced by units, buildings, and special powers
- Veterancy levels affect visual effects and object creation lists
- Projectile weapons create separate objects that handle their own movement and collision
- Status effect weapons use DamageType = STATUS and specify the effect in DamageStatusType
- Area effect weapons use radius damage properties to affect multiple targets
- Anti-air weapons should target airborne units and projectiles appropriately
- Point defense weapons typically have very short ranges but high damage and fast firing rates
