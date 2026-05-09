# DamageFX INI Documentation

## Overview

The `DamageFX` INI file contains damage effects configuration settings and parameters for visual and audio feedback when objects take damage. DamageFX defines how different damage types trigger appropriate visual effects, particle systems, and audio feedback based on damage amount and unit veterancy level.

## Usage

DamageFX templates are defined in INI files and specify the visual and audio effects that play when objects receive different types of damage. This is a **template configuration system** that defines damage response effects. The damage effects system provides appropriate feedback for different damage types and amounts.

**Limitations**:
- DamageFX only controls visual and audio effects, not actual damage logic
- Effects are limited to predefined FXList and particle system references
- Damage thresholds are fixed and cannot be dynamically modified
- Effects depend on proper FXList and particle system definitions

**Conditions**:
- DamageFX manages visual and audio feedback for damage events
- The configuration handles damage type effects, amount thresholds, and veterancy scaling
- Damage effects operations provide immersive combat feedback
- Damage effects management creates realistic and responsive damage visualization
- **Multiple instances behavior**: Multiple DamageFX templates can exist with different effect configurations

**Dependencies**:
- Uses FXList definitions for visual and audio effects
- Integrates with the damage system for triggering effects
- Uses veterancy levels for effect scaling
- Referenced by object Body modules for damage response

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Damage Effect Properties](#damage-effect-properties)
  - [Veterancy-Specific Properties](#veterancy-specific-properties)
- [Examples](#examples)
- [Best Practices](#best-practices)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Damage Effect Properties *(v1.04)*

#### `AmountForMajorFX` *(v1.04)*
- **Type**: `Real` (with damage type)
- **Description**: Damage amount threshold that determines when to use major effects instead of minor effects for specific damage types. When damage equals or exceeds this value, major effects are triggered.
- **Format**: `AmountForMajorFX = DAMAGE_TYPE Value`
- **Default**: `0.0`
- **Example**: `AmountForMajorFX = ARMOR_PIERCING 50.0` // Major armor piercing effects trigger at 50+ damage

#### `MajorFX` *(v1.04)*
- **Type**: `FXList` (with damage type, see [FXList documentation](FXList.md))
- **Description**: Visual and audio effects to play when damage amount exceeds the major threshold for specific damage types. Used for significant damage events.
- **Format**: `MajorFX = DAMAGE_TYPE FXListName`
- **Default**: None
- **Example**: `MajorFX = EXPLOSION FX_ExplosionMajor` // Major explosion effects

#### `MinorFX` *(v1.04)*
- **Type**: `FXList` (with damage type, see [FXList documentation](FXList.md))
- **Description**: Visual and audio effects to play when damage amount is below the major threshold for specific damage types. Used for light damage events.
- **Format**: `MinorFX = DAMAGE_TYPE FXListName`
- **Default**: None
- **Example**: `MinorFX = EXPLOSION FX_ExplosionMinor` // Minor explosion effects

#### `ThrottleTime` *(v1.04)*
- **Type**: `UnsignedInt` (with damage type or DEFAULT, milliseconds)
- **Description**: Minimum time between damage effects of the same type to prevent effect spam. Prevents rapid-fire effect triggering.
- **Format**: `ThrottleTime = DAMAGE_TYPE Value` or `ThrottleTime = DEFAULT Value`
- **Default**: `0`
- **Example**: `ThrottleTime = DEFAULT 300` // 300ms minimum between effects for all damage types

### Veterancy-Specific Properties *(v1.04)*

#### `VeterancyMajorFX` *(v1.04)*
- **Type**: `FXList` (with veterancy level and damage type)
- **Description**: Major effects specific to veterancy levels and damage types. Overrides general MajorFX for specific veterancy levels.
- **Format**: `VeterancyMajorFX = VETERANCY_LEVEL DAMAGE_TYPE FXListName`
- **Default**: Uses general MajorFX
- **Example**: `VeterancyMajorFX = HEROIC SMALL_ARMS FX_HeroicSmallArms` // Heroic-specific small arms effects

#### `VeterancyMinorFX` *(v1.04)*
- **Type**: `FXList` (with veterancy level and damage type)
- **Description**: Minor effects specific to veterancy levels and damage types. Overrides general MinorFX for specific veterancy levels.
- **Format**: `VeterancyMinorFX = VETERANCY_LEVEL DAMAGE_TYPE FXListName`
- **Default**: Uses general MinorFX
- **Example**: `VeterancyMinorFX = HEROIC SMALL_ARMS FX_HeroicSmallArms` // Heroic-specific minor effects

## DamageType Values *(v1.04)*

The damage type system accepts the following values for all damage effect properties:

- **`DEFAULT`** *(v1.04)* - Default damage type for general effects
- **`EXPLOSION`** *(v1.04)* - Explosive damage from bombs, missiles, etc.
- **`CRUSH`** *(v1.04)* - Crushing damage from vehicles running over units
- **`ARMOR_PIERCING`** *(v1.04)* - Armor-piercing damage from anti-tank weapons
- **`SMALL_ARMS`** *(v1.04)* - Small arms damage from rifles, pistols, etc.
- **`GATTLING`** *(v1.04)* - Gatling gun damage from rapid-fire weapons
- **`RADIATION`** *(v1.04)* - Radiation damage from nuclear weapons
- **`FLAME`** *(v1.04)* - Flame damage from flamethrowers, fire
- **`LASER`** *(v1.04)* - Laser damage from laser weapons
- **`SNIPER`** *(v1.04)* - Sniper rifle damage
- **`POISON`** *(v1.04)* - Poison damage from chemical weapons
- **`HEALING`** *(v1.04)* - Healing effects (usually set to None)
- **`UNRESISTABLE`** *(v1.04)* - Unresistable damage that ignores armor
- **`WATER`** *(v1.04)* - Water damage effects
- **`DEPLOY`** *(v1.04)* - Deployment damage effects
- **`SURRENDER`** *(v1.04)* - Surrender effects
- **`HACK`** *(v1.04)* - Hacking damage effects
- **`KILL_PILOT`** *(v1.04)* - Pilot killing effects
- **`PENALTY`** *(v1.04)* - Penalty damage effects
- **`FALLING`** *(v1.04)* - Falling damage effects
- **`MELEE`** *(v1.04)* - Melee combat damage
- **`DISARM`** *(v1.04)* - Disarming effects
- **`HAZARD_CLEANUP`** *(v1.04)* - Hazard cleanup effects
- **`INFANTRY_MISSILE`** *(v1.04)* - Infantry missile damage
- **`AURORA_BOMB`** *(v1.04)* - Aurora bomber damage
- **`LAND_MINE`** *(v1.04)* - Land mine damage
- **`JET_MISSILES`** *(v1.04)* - Jet missile damage
- **`STEALTHJET_MISSILES`** *(v1.04)* - Stealth jet missile damage
- **`MOLOTOV_COCKTAIL`** *(v1.04)* - Molotov cocktail damage
- **`COMANCHE_VULCAN`** *(v1.04)* - Comanche Vulcan cannon damage
- **`SUBDUAL_MISSILE`** *(v1.04)* - Subdual missile damage
- **`SUBDUAL_VEHICLE`** *(v1.04)* - Subdual vehicle damage
- **`SUBDUAL_BUILDING`** *(v1.04)* - Subdual building damage
- **`SUBDUAL_UNRESISTABLE`** *(v1.04)* - Subdual unresistable damage
- **`MICROWAVE`** *(v1.04)* - Microwave damage
- **`KILL_GARRISONED`** *(v1.04)* - Kill garrisoned unit damage
- **`STATUS`** *(v1.04)* - Status effect damage
- **`EXTRA_8`** *(v1.04)* - Extra damage type 8

## VeterancyLevel Values *(v1.04)*

The veterancy level system accepts the following values:

- **`DEFAULT`** *(v1.04)* - Default veterancy level (recruit)
- **`RECRUIT`** *(v1.04)* - Recruit level (basic units)
- **`VETERAN`** *(v1.04)* - Veteran level (experienced units)
- **`ELITE`** *(v1.04)* - Elite level (highly experienced units)
- **`HEROIC`** *(v1.04)* - Heroic level (legendary units)

## Examples

### Tank Damage Effects (Real Example)
```ini
DamageFX TankDamageFX
    ThrottleTime = DEFAULT 100
    
    AmountForMajorFX = DEFAULT 2.0
    MajorFX = DEFAULT FX_APFSDS30mmHitEffectSmallUnit
    VeterancyMajorFX = HEROIC DEFAULT FX_APFSDS30mmHitEffectSmallUnit
    MinorFX = DEFAULT FX_APFSDS30mmHitEffectSmallUnit
    VeterancyMinorFX = HEROIC DEFAULT FX_APFSDS30mmHitEffectSmallUnit

    MajorFX = KILL_PILOT FX_DamageDisableVehicle
    VeterancyMajorFX = HEROIC KILL_PILOT FX_HeroicDamageDisableVehicle
    MinorFX = KILL_PILOT FX_DamageDisableVehicle
    VeterancyMinorFX = HEROIC KILL_PILOT FX_HeroicDamageDisableVehicle

    MajorFX = SNIPER FX_DamageTankStruckSmallArms
    VeterancyMajorFX = HEROIC SNIPER FX_HeroicDamageTankStruckSmallArms
    MinorFX = SNIPER FX_DamageTankStruckSmallArms
    VeterancyMinorFX = HEROIC SNIPER FX_HeroicDamageTankStruckSmallArms

    MajorFX = GATTLING None
    VeterancyMajorFX = HEROIC GATTLING None
    MinorFX = GATTLING None
    VeterancyMinorFX = HEROIC GATTLING None

    MajorFX = SMALL_ARMS None
    VeterancyMajorFX = HEROIC SMALL_ARMS None
    MinorFX = SMALL_ARMS None
    VeterancyMinorFX = HEROIC SMALL_ARMS None

    AmountForMajorFX = ARMOR_PIERCING 50.0
    MajorFX = ARMOR_PIERCING FX_DamageMajorArmorPiercing
    MinorFX = ARMOR_PIERCING FX_DamageMinorArmorPiercing

    MajorFX = FLAME None
    MinorFX = FLAME None

    MajorFX = MOLOTOV_COCKTAIL FX_THEL_BeamHitsGround
    MinorFX = MOLOTOV_COCKTAIL FX_THEL_BeamHitsGround

    MajorFX = HEALING None
    MinorFX = HEALING None

    MajorFX = RADIATION None
    MinorFX = RADIATION None

    MajorFX = POISON None
    MinorFX = POISON None

    MajorFX = STATUS None
    MinorFX = STATUS None

    MajorFX = SUBDUAL_VEHICLE None
    MinorFX = SUBDUAL_VEHICLE None

    MajorFX = MELEE None
    MinorFX = MELEE None
End
```

### Infantry Damage Effects (Real Example)
```ini
DamageFX InfantryDamageFX
    ThrottleTime = DEFAULT 100
    
    MajorFX = SMALL_ARMS FX_DamageInfantry
    VeterancyMajorFX = HEROIC SMALL_ARMS FX_DamageInfantry
    MinorFX = SMALL_ARMS FX_DamageInfantry
    VeterancyMinorFX = HEROIC SMALL_ARMS FX_DamageInfantry

    MajorFX = COMANCHE_VULCAN FX_DamageInfantry
    VeterancyMajorFX = HEROIC COMANCHE_VULCAN FX_DamageInfantry
    MinorFX = COMANCHE_VULCAN FX_DamageInfantry
    VeterancyMinorFX = HEROIC COMANCHE_VULCAN FX_DamageInfantry
    
    MajorFX = SNIPER FX_DamageInfantry
    VeterancyMajorFX = HEROIC SNIPER FX_DamageInfantry
    MinorFX = SNIPER FX_DamageInfantry
    VeterancyMinorFX = HEROIC SNIPER FX_DamageInfantry

    MajorFX = FLAME None
    MinorFX = FLAME None

    MajorFX = MOLOTOV_COCKTAIL FX_THEL_BeamHitsGround
    MinorFX = MOLOTOV_COCKTAIL FX_THEL_BeamHitsGround

    MajorFX = HEALING None
    MinorFX = HEALING None

    MajorFX = RADIATION None
    MinorFX = RADIATION None

    MajorFX = POISON None
    MinorFX = POISON None

    MajorFX = WATER None
    MinorFX = WATER None

    MajorFX = MELEE None
    MinorFX = MELEE None
    
    MajorFX = UNRESISTABLE None
    MinorFX = UNRESISTABLE None

    MajorFX = STATUS None
    MinorFX = STATUS None

    MajorFX = MICROWAVE None
    MinorFX = MICROWAVE None
End
```

### Structure Damage Effects (Real Example)
```ini
DamageFX StructureDamageFX
    ThrottleTime = DEFAULT 300

    AmountForMajorFX = DEFAULT 1.0
    MajorFX = DEFAULT FX_StructureDamaged
    MinorFX = DEFAULT FX_StructureDamaged

    MajorFX = MOLOTOV_COCKTAIL FX_THEL_BeamHitsGround
    MinorFX = MOLOTOV_COCKTAIL FX_THEL_BeamHitsGround

    MajorFX = HEALING None
    MinorFX = HEALING None

    MajorFX = FLAME None
    MinorFX = FLAME None

    MajorFX = RADIATION None
    MinorFX = RADIATION None

    MajorFX = POISON None
    MinorFX = POISON None

    MajorFX = STATUS None
    MinorFX = STATUS None

    MajorFX = SUBDUAL_BUILDING None
    MinorFX = SUBDUAL_BUILDING None

    MajorFX = GATTLING None
    VeterancyMajorFX = HEROIC GATTLING None
    MinorFX = GATTLING None
    VeterancyMinorFX = HEROIC GATTLING None

    MajorFX = SMALL_ARMS None
    VeterancyMajorFX = HEROIC SMALL_ARMS None
    MinorFX = SMALL_ARMS None
    VeterancyMinorFX = HEROIC SMALL_ARMS None

    MajorFX = MELEE None
    MinorFX = MELEE None
End
```

## Best Practices

### Damage Effect Design

1. **Appropriate Thresholds**: Set damage thresholds that match the expected damage amounts for different weapons
2. **Balanced Effects**: Ensure major and minor effects provide appropriate visual feedback
3. **Performance Consideration**: Use throttle times to prevent effect spam and performance issues
4. **Veterancy Scaling**: Use veterancy-specific effects to enhance unit progression

### Effect Selection

1. **Damage Type Matching**: Choose effects that match the damage type (explosion, flame, bullet, etc.)
2. **Visual Consistency**: Ensure effects are visually consistent with the damage source
3. **Audio Integration**: Include appropriate audio effects for immersive feedback
4. **Performance Optimization**: Balance visual quality with performance impact

### Veterancy Integration

1. **Progressive Enhancement**: Higher veterancy levels should have more impressive effects
2. **Threshold Scaling**: Adjust damage thresholds for veterancy levels appropriately
3. **Effect Variety**: Create unique effects for different veterancy levels
4. **Balanced Throttling**: Adjust throttle times based on veterancy level

## Template

```ini
DamageFX DamageFXName
    ThrottleTime = DEFAULT 300           ; // Minimum time between effects (ms) *(v1.04)*
    
    ; General damage effects:
    AmountForMajorFX = DEFAULT 2.0       ; // Damage threshold for major effects *(v1.04)*
    MajorFX = DEFAULT FX_DefaultMajor    ; // Major damage effects *(v1.04)*
    MinorFX = DEFAULT FX_DefaultMinor    ; // Minor damage effects *(v1.04)*
    
    ; Specific damage type effects:
    MajorFX = EXPLOSION FX_ExplosionMajor    ; // Explosion damage effects *(v1.04)*
    MinorFX = EXPLOSION FX_ExplosionMinor    ; // Explosion damage effects *(v1.04)*
    
    MajorFX = ARMOR_PIERCING FX_ArmorPiercingMajor    ; // Armor piercing effects *(v1.04)*
    MinorFX = ARMOR_PIERCING FX_ArmorPiercingMinor    ; // Armor piercing effects *(v1.04)*
    
    MajorFX = SMALL_ARMS FX_SmallArmsMajor    ; // Small arms effects *(v1.04)*
    MinorFX = SMALL_ARMS FX_SmallArmsMinor    ; // Small arms effects *(v1.04)*
    
    MajorFX = FLAME None                   ; // No flame effects *(v1.04)*
    MinorFX = FLAME None                   ; // No flame effects *(v1.04)*
    
    MajorFX = HEALING None                 ; // No healing effects *(v1.04)*
    MinorFX = HEALING None                 ; // No healing effects *(v1.04)*
    
    MajorFX = STATUS None                  ; // No status effects *(v1.04)*
    MinorFX = STATUS None                  ; // No status effects *(v1.04)*
    
    MajorFX = MELEE None                   ; // No melee effects *(v1.04)*
    MinorFX = MELEE None                   ; // No melee effects *(v1.04)*
    
    ; Veterancy-specific overrides (optional):
    VeterancyMajorFX = HEROIC DEFAULT FX_HeroicDefaultMajor    ; // Heroic major effects *(v1.04)*
    VeterancyMinorFX = HEROIC DEFAULT FX_HeroicDefaultMinor    ; // Heroic minor effects *(v1.04)*
    
    VeterancyMajorFX = HEROIC SMALL_ARMS FX_HeroicSmallArmsMajor    ; // Heroic small arms *(v1.04)*
    VeterancyMinorFX = HEROIC SMALL_ARMS FX_HeroicSmallArmsMinor    ; // Heroic small arms *(v1.04)*
End
```

## Notes

- DamageFX provides visual and audio feedback for damage events in combat
- The configuration manages damage effect thresholds and veterancy scaling
- Damage effects operations create immersive and responsive combat feedback
- Damage effects management ensures appropriate visual and audio responses
- This configuration is essential for realistic combat visualization and feedback
- Damage effects coordination creates consistent feedback across different damage types
- Damage thresholds control when major vs minor effects are triggered
- Veterancy scaling allows for enhanced effects based on unit experience
- Throttle times prevent effect spam and maintain performance
- FXList integration provides rich visual and audio effect capabilities
- DamageFX templates are shared between multiple units for efficiency
- The system supports both general and veterancy-specific effect configurations
- Damage effects are triggered by the damage system when objects take damage
- Effects are purely visual/audio and do not affect actual damage calculations
- The system integrates with the Body module system for damage response
- DamageFX templates are defined in INI files and loaded by the DamageFXStore
- Effect triggering depends on proper damage type and amount calculations
- The system supports complex effect hierarchies with veterancy scaling

## Source Files

**Base Class:** [DamageFX](../../GeneralsMD/Code/GameEngine/Include/Common/DamageFX.h)
- Header: [`GeneralsMD/Code/GameEngine/Include/Common/DamageFX.h`](../../GeneralsMD/Code/GameEngine/Include/Common/DamageFX.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/Common/DamageFX.cpp`](../../GeneralsMD/Code/GameEngine/Source/Common/DamageFX.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet
