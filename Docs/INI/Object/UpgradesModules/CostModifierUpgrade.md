# CostModifierUpgrade

CostModifierUpgrade provides the ability to modify the production cost of objects by a percentage when an upgrade is applied, allowing for dynamic cost adjustments based on upgrade status.

## Overview

The `CostModifierUpgrade` class manages production cost modifications for objects when specific upgrades are applied. This upgrade module allows objects to have their build costs adjusted by a percentage, providing economic benefits or penalties based on upgrade state. The behavior is commonly used for buildings that provide economic bonuses, technology upgrades that reduce costs, or special conditions that affect production expenses.

## Usage

Used by objects that need to modify production costs when upgrades are applied. This is an **upgrade module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Only affects production costs, not other economic factors
- The cost modification is applied to all objects of the specified KindOf type
- Cost modifications are percentage-based, not absolute values
- The upgrade must be applied to a building or structure to affect production costs

**Conditions**:
- CostModifierUpgrade modifies production costs when the specified upgrade is applied
- The upgrade integrates with the upgrade system for conditional activation
- Cost modifications affect all objects of the specified KindOf type for the player
- The upgrade is properly cleaned up when the object is deleted or captured
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own cost modifications

**Dependencies**:
- Requires an object with upgrade system integration
- Objects must have proper KindOf classification to be affected
- The player system must be available for cost modification tracking
- The upgrade system must be properly configured for the object

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)

## Properties

### Cost Modification Settings

#### `EffectKindOf` *(v1.04)*
- **Type**: `KindOfMaskType` (bit flags) (see [KindOfMaskType Values](#kindofmasktype-values) section)
- **Description**: The object types that will have their production costs modified. When set, only objects with matching types will have their costs affected. When 0 (default), no object types are affected
- **Default**: `0` (no types)
- **Example**: `EffectKindOf = INFANTRY VEHICLE`

#### `Percentage` *(v1.04)*
- **Type**: `Real` (percentage)
- **Description**: The percentage by which to modify production costs. Positive values increase costs, negative values decrease costs. Values are expressed as percentages (e.g., 0.25 = 25% increase, -0.50 = 50% decrease)
- **Default**: `0.0` (no change)
- **Example**: `Percentage = -0.25` (25% cost reduction)

## Enum Value Lists

#### `KindOfMaskType` Values *(v1.04)*
**Source:** [KindOf.cpp](../../GeneralsMD/Code/GameEngine/Source/Common/System/KindOf.cpp#35) - `KindOfMaskType::s_bitNameList[]` array definition

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

### Basic Cost Reduction
```ini
Upgrade = CostModifierUpgrade ModuleTag_CostReduction
  EffectKindOf = INFANTRY
  Percentage = -0.25
  TriggeredBy = Upgrade_InfantryTraining
End
```

### Vehicle Cost Increase
```ini
Upgrade = CostModifierUpgrade ModuleTag_CostIncrease
  EffectKindOf = VEHICLE
  Percentage = 0.50
  TriggeredBy = Upgrade_ResourceShortage
End
```

### Multiple Object Types
```ini
Upgrade = CostModifierUpgrade ModuleTag_MultiCostMod
  EffectKindOf = INFANTRY VEHICLE AIRCRAFT
  Percentage = -0.15
  TriggeredBy = Upgrade_AdvancedTechnology
End
```

### Structure Cost Modification
```ini
Upgrade = CostModifierUpgrade ModuleTag_StructureCost
  EffectKindOf = STRUCTURE
  Percentage = -0.30
  TriggeredBy = Upgrade_ConstructionEfficiency
End
```

## Template

```ini
Upgrade = CostModifierUpgrade ModuleTag_XX
  ; Cost Modification Settings
  EffectKindOf =                   ; // object types to affect *(v1.04)*
  Percentage = 0.0                 ; // cost modification percentage *(v1.04)*
  
  ; Upgrade Integration (inherited from UpgradeModule)
  TriggeredBy =                    ; // required upgrade flags *(v1.04)*
  ConflictsWith =                  ; // conflicting upgrade flags *(v1.04)*
  RequiresAll = No                 ; // require all TriggeredBy upgrades *(v1.04)*
End
```

## Notes

- CostModifierUpgrade modifies production costs when the specified upgrade is applied
- The upgrade integrates with the upgrade system for conditional activation
- Cost modifications affect all objects of the specified KindOf type for the player
- The upgrade is properly cleaned up when the object is deleted or captured
- Only affects production costs, not other economic factors
- Cost modifications are percentage-based, not absolute values
- The upgrade must be applied to a building or structure to affect production costs
- Positive percentage values increase costs, negative values decrease costs

## Source Files

**Base Class:** [`UpgradeModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CostModifierUpgrade.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CostModifierUpgrade.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/CostModifierUpgrade.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/CostModifierUpgrade.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet
