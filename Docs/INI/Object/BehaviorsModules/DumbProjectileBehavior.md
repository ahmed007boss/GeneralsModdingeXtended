# DumbProjectileBehavior

DumbProjectileBehavior provides ballistic trajectory behavior for unguided projectiles that follow curved flight paths without active guidance systems.

## Overview

The `DumbProjectileBehavior` class manages unguided projectiles that follow ballistic trajectories using Bezier curves. These projectiles cannot actively track targets but can adjust their flight path within limited parameters. The behavior is commonly used for artillery shells, grenades, and other ballistic weapons that follow predictable arc trajectories.

## Usage

Used by projectile objects that need to follow simple ballistic physics without homing or guidance capabilities. This is a **behavior module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Requires valid target objects or coordinates to function
- Projectile flight path is determined by Bezier curve control points
- Collision detection works with terrain and objects
- Projectile behavior is limited by flight time and distance constraints
- Projectiles automatically clean up when they reach their destination or collide

**Conditions**:
- DumbProjectileBehavior provides automatic projectile flight paths using Bezier curves
- The behavior handles collision detection with terrain and objects during flight
- Projectiles can be configured with different flight patterns and collision behaviors
- Flight paths are calculated using first and second height control points
- Collision detection can trigger different behaviors based on what is hit
- The behavior supports both direct targeting and area effect projectiles
- **Multiple instances behavior**: Only one instance should be used per projectile object; multiple instances may cause conflicts in flight path calculations

**Dependencies**:
- The behavior integrates with the weapon system for projectile creation and management

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Flight Path Control](#flight-path-control)
  - [Behavior Settings](#behavior-settings)
  - [Garrison Hit Settings](#garrison-hit-settings)
  - [Target Tracking](#target-tracking)
- [Enum Value Lists](#enum-value-lists)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

### Flight Path Control

#### `FirstHeight` *(v1.04)*
- **Type**: `Real`
- **Description**: Height of the first Bezier control point above the highest intervening terrain
- **Example**: `FirstHeight = 10.0`

#### `SecondHeight` *(v1.04)*
- **Type**: `Real`
- **Description**: Height of the second Bezier control point above the highest intervening terrain
- **Example**: `SecondHeight = 33.0`

#### `FirstPercentIndent` *(v1.04)*
- **Type**: `Real` (percentage)
- **Description**: Percentage of shot distance where the first control point is placed along the target line
- **Example**: `FirstPercentIndent = 50%`

#### `SecondPercentIndent` *(v1.04)*
- **Type**: `Real` (percentage)
- **Description**: Percentage of shot distance where the second control point is placed along the target line
- **Example**: `SecondPercentIndent = 75%`

### Behavior Settings

#### `MaxLifespan` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Maximum time the projectile can exist before being destroyed
- **Example**: `MaxLifespan = 10000`

#### `TumbleRandomly` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether the projectile should tumble randomly during flight
- **Example**: `TumbleRandomly = Yes`

#### `DetonateCallsKill` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether detonation should call the kill method instead of just destroying the object
- **Example**: `DetonateCallsKill = Yes`

#### `OrientToFlightPath` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether the projectile should orient itself to face the direction of flight
- **Example**: `OrientToFlightPath = Yes`

### Garrison Hit Settings

#### `GarrisonHitKillRequiredKindOf` *(v1.04)*
- **Type**: `KindOfMaskType` (bit flags) (see [KindOfMaskType Values](#kindofmasktype-values) section)
- **Description**: Units must have at least one of these KindOf bits to be killed when hitting garrisoned buildings
- **Example**: `GarrisonHitKillRequiredKindOf = INFANTRY VEHICLE`

#### `GarrisonHitKillForbiddenKindOf` *(v1.04)*
- **Type**: `KindOfMaskType` (bit flags) (see [KindOfMaskType Values](#kindofmasktype-values) section)
- **Description**: Units must have NONE of these KindOf bits to be killed when hitting garrisoned buildings
- **Example**: `GarrisonHitKillForbiddenKindOf = STRUCTURE`
- **Available Values**: See [KindOfMaskType Values](#kindofmasktype-values) section

#### `GarrisonHitKillCount` *(v1.04)*
- **Type**: `Int`
- **Description**: Maximum number of garrisoned units to kill when hitting a building
- **Example**: `GarrisonHitKillCount = 3`

#### `GarrisonHitKillFX` *(v1.04)*
- **Type**: `FXList` (see [FXList documentation](../FXList.md))
- **Description**: Visual effects played when killing garrisoned units
- **Example**: `GarrisonHitKillFX = FX_FlashBang`

### Target Tracking

#### `FlightPathAdjustDistPerSecond` *(v1.04)*
- **Type**: `Real` (distance per second)
- **Description**: Maximum speed at which the projectile can adjust its flight path to follow a moving target
- **Example**: `FlightPathAdjustDistPerSecond = 99.0`

## Enum Value Lists

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

### Basic Artillery Shell
```ini
Behavior = DumbProjectileBehavior ModuleTag_06
  DetonateCallsKill = Yes
  FirstHeight = 10.0
  SecondHeight = 33.0
  FirstPercentIndent = 50%
  SecondPercentIndent = 75%
  FlightPathAdjustDistPerSecond = 99.0
  MaxLifespan = 10000
  OrientToFlightPath = Yes
End
```

### Grenade with Garrison Clearing
```ini
Behavior = DumbProjectileBehavior ModuleTag_04
  DetonateCallsKill = Yes
  FirstHeight = 33.0
  SecondHeight = 133.0
  FirstPercentIndent = 50%
  SecondPercentIndent = 75%
  FlightPathAdjustDistPerSecond = 99.0
  GarrisonHitKillCount = 2
  GarrisonHitKillRequiredKindOf = INFANTRY
  GarrisonHitKillFX = FX_FlashBang
  TumbleRandomly = Yes
End
```

### High-Arc Mortar Round
```ini
Behavior = DumbProjectileBehavior ModuleTag_03
  DetonateCallsKill = Yes
  FirstHeight = 50.0
  SecondHeight = 100.0
  FirstPercentIndent = 30%
  SecondPercentIndent = 60%
  FlightPathAdjustDistPerSecond = 50.0
  MaxLifespan = 15000
  OrientToFlightPath = No
End
```

## Template

```ini
Behavior = DumbProjectileBehavior ModuleTag_XX
  ; Flight Path Control
  FirstHeight = 10.0              ; // height of first Bezier control point above terrain *(v1.04)*
  SecondHeight = 33.0             ; // height of second Bezier control point above terrain *(v1.04)*
  FirstPercentIndent = 50%        ; // percentage of distance for first control point *(v1.04)*
  SecondPercentIndent = 75%       ; // percentage of distance for second control point *(v1.04)*

  ; Behavior Settings
  MaxLifespan = 10000             ; // maximum projectile lifetime in milliseconds *(v1.04)*
  TumbleRandomly = No             ; // whether projectile tumbles randomly during flight *(v1.04)*
  DetonateCallsKill = Yes         ; // whether detonation calls kill method *(v1.04)*
  OrientToFlightPath = Yes        ; // whether projectile orients to flight direction *(v1.04)*

  ; Garrison Hit Settings
  GarrisonHitKillCount = 0        ; // max garrisoned units to kill on building hit *(v1.04)*
  GarrisonHitKillRequiredKindOf = ; // required KindOf bits for garrison kills *(v1.04)*
  GarrisonHitKillForbiddenKindOf = ; // forbidden KindOf bits for garrison kills *(v1.04)*
  GarrisonHitKillFX =             ; // effects when killing garrisoned units *(v1.04)*

  ; Target Tracking
  FlightPathAdjustDistPerSecond = 99.0 ; // max speed to adjust flight path for moving targets *(v1.04)*
End
```

## Notes

- DumbProjectileBehavior uses Bezier curves with four control points to define flight paths
- The first and last control points are automatically set to the launcher and target positions
- The middle two control points are calculated based on FirstHeight, SecondHeight, and the percentage indents
- Projectiles can only adjust their flight path within the limits set by FlightPathAdjustDistPerSecond
- Garrison hit settings allow projectiles to clear garrisoned units from buildings on impact
- This behavior is commonly used for artillery, mortars, grenades, and other ballistic weapons
- Projectiles use detonation weapons (see [Weapon documentation](../Weapon.md)) for explosion effects

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h), [`ProjectileUpdateInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DumbProjectileBehavior.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DumbProjectileBehavior.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DumbProjectileBehavior.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/DumbProjectileBehavior.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/DumbProjectileBehavior.cpp)
