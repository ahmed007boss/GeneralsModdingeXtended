# Crate INI Documentation

## Overview

The `Crate` INI file contains crate template configuration settings and parameters for supply crates, power-ups, and special items that can be spawned when units are destroyed. Crates provide random rewards and benefits to players when collected, adding strategic elements to gameplay through resource management and tactical positioning.

## Usage

Crate templates are defined in INI files and specify the conditions under which crates are spawned when units are destroyed. This is a **template configuration system** that defines crate spawning behavior and contents. The crate system determines what types of crates can appear based on unit veterancy, killer type, and other conditions.

**Limitations**:
- Crates can only be spawned when units are destroyed under specific conditions
- Crate spawning is limited by the creation chance percentage
- Crate contents are predefined and cannot be dynamically modified during gameplay
- Crate spawning depends on proper unit destruction and condition matching

**Conditions**:
- Crate templates manage spawning conditions and crate contents
- The configuration handles creation chances, veterancy requirements, and killer type conditions
- Crate operations provide random rewards and strategic gameplay elements
- Crate management creates dynamic battlefield rewards and tactical opportunities
- **Multiple instances behavior**: Multiple crate templates can be active simultaneously with different spawning conditions

**Dependencies**:
- Uses unit veterancy levels for spawning conditions
- Integrates with the unit destruction system for triggering
- Uses KindOfMaskType for killer type requirements
- Referenced by crate collide modules for actual crate behavior

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Crate Spawning Properties](#crate-spawning-properties)
- [Examples](#examples)
- [Best Practices](#best-practices)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Crate Spawning Properties *(v1.04)*

#### `CreationChance` *(v1.04)*
- **Type**: `Real` (percentage)
- **Description**: Random percentage chance (0.0 to 1.0) that a crate will be created when the spawning conditions are met. 1.0 = 100% chance, 0.5 = 50% chance.
- **Default**: `0.0`
- **Example**: `CreationChance = 0.25` // 25% chance to spawn crate

#### `VeterancyLevel` *(v1.04)*
- **Type**: `VeterancyLevel` (see [VeterancyLevel Values](#veterancylevel-values) section)
- **Description**: Minimum veterancy level required for the killed unit to spawn this crate. Higher veterancy units have better crate spawning chances.
- **Default**: `LEVEL_INVALID`
- **Example**: `VeterancyLevel = VETERAN` // Only veteran+ units can spawn this crate

#### `KilledByType` *(v1.04)*
- **Type**: `KindOfMaskType`
- **Description**: KindOf mask specifying what type of unit must kill the target to spawn this crate. Uses KindOf flags to specify unit categories.
- **Default**: `None`
- **Example**: `KilledByType = INFANTRY` // Only infantry kills spawn this crate

#### `CrateObject` *(v1.04)*
- **Type**: `crateCreationEntry` block
- **Description**: Defines the actual crate object to spawn and its spawn chance. Multiple CrateObject entries can be defined for different crate types.
- **Format**: `CrateObject = CrateName Chance`
- **Example**: 
  ```
  CrateObject = SupplyCrate 0.7
  CrateObject = WeaponCrate 0.3
  ```

#### `KillerScience` *(v1.04)*
- **Type**: `ScienceType`
- **Description**: Science requirement that the killer unit must possess to spawn this crate. Used for faction-specific or upgrade-specific crate spawning.
- **Default**: `SCIENCE_INVALID`
- **Example**: `KillerScience = SCIENCE_AdvancedWeapons` // Only advanced weapon kills spawn this crate

#### `OwnedByMaker` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether the spawned crate is owned by the unit that created it (the killer) or remains neutral. Affects who can collect the crate.
- **Default**: `No`
- **Example**: `OwnedByMaker = Yes` // Crate is owned by the killer's player

## VeterancyLevel Values *(v1.04)*

The VeterancyLevel property accepts the following values:

- **`LEVEL_INVALID`** *(v1.04)* - Invalid or no veterancy requirement
- **`RECRUIT`** *(v1.04)* - Recruit level (basic units)
- **`VETERAN`** *(v1.04)* - Veteran level (experienced units)
- **`ELITE`** *(v1.04)* - Elite level (highly experienced units)
- **`HEROIC`** *(v1.04)* - Heroic level (legendary units)

## Examples

### Basic Supply Crate
```ini
CrateTemplate SupplyCrateTemplate
    CreationChance = 0.15
    VeterancyLevel = RECRUIT
    CrateObject = SupplyCrate 1.0
End
```

### Veteran Weapon Crate
```ini
CrateTemplate VeteranWeaponCrateTemplate
    CreationChance = 0.25
    VeterancyLevel = VETERAN
    KilledByType = INFANTRY
    CrateObject = WeaponCrate 0.6
    CrateObject = AmmoCrate 0.4
    OwnedByMaker = Yes
End
```

### Elite Special Crate
```ini
CrateTemplate EliteSpecialCrateTemplate
    CreationChance = 0.35
    VeterancyLevel = ELITE
    KillerScience = SCIENCE_AdvancedWeapons
    CrateObject = SpecialWeaponCrate 0.8
    CrateObject = UpgradeCrate 0.2
End
```

### Faction-Specific Crate
```ini
CrateTemplate ChinaTechCrateTemplate
    CreationChance = 0.20
    VeterancyLevel = VETERAN
    KilledByType = VEHICLE
    KillerScience = SCIENCE_ChinaNationalism
    CrateObject = ChinaTechCrate 1.0
End
```

## Best Practices

### Crate Design

1. **Balanced Creation Chances**: Use appropriate creation chances to avoid flooding the battlefield with crates
2. **Meaningful Conditions**: Design spawning conditions that make tactical sense
3. **Progressive Rewards**: Higher veterancy units should spawn better crates
4. **Faction Variety**: Create faction-specific crates for unique gameplay

### Spawning Conditions

1. **Veterancy Scaling**: Use veterancy levels to control crate quality and rarity
2. **Killer Type Logic**: Use KilledByType to create tactical crate spawning
3. **Science Requirements**: Use KillerScience for faction-specific or upgrade-specific crates
4. **Ownership Logic**: Consider whether crates should be owned by the killer or remain neutral

### Crate Contents

1. **Multiple Options**: Use multiple CrateObject entries for variety
2. **Balanced Chances**: Ensure crate object spawn chances add up logically
3. **Strategic Value**: Design crate contents that provide meaningful tactical benefits
4. **Progression Flow**: Create crates that support different stages of gameplay

## Template

```ini
CrateTemplate CrateTemplateName
    CreationChance = 0.25               ; // Random chance to spawn (0.0-1.0) *(v1.04)*
    VeterancyLevel = VETERAN            ; // Minimum veterancy level *(v1.04)*
    KilledByType = INFANTRY             ; // Killer unit type requirement *(v1.04)*
    KillerScience = SCIENCE_INVALID     ; // Killer science requirement *(v1.04)*
    OwnedByMaker = No                   ; // Whether killer owns the crate *(v1.04)*
    CrateObject = CrateName1 0.7        ; // First crate option with chance *(v1.04)*
    CrateObject = CrateName2 0.3        ; // Second crate option with chance *(v1.04)*
End
```

## Notes

- Crates provide dynamic battlefield rewards and strategic gameplay elements
- The configuration manages spawning conditions and crate contents for tactical variety
- Crate operations create random rewards that enhance gameplay unpredictability
- Crate management ensures balanced reward distribution across different game scenarios
- This configuration is essential for creating dynamic battlefield rewards
- Crate coordination creates strategic opportunities through random reward systems
- Spawning conditions control when and how crates appear on the battlefield
- Crate contents determine the tactical value and strategic impact of rewards
- Veterancy systems create progressive reward scaling based on unit experience
- Killer type conditions create tactical crate spawning based on combat outcomes
- Science requirements enable faction-specific and upgrade-specific crate spawning
- Ownership systems control crate collection rights and strategic positioning
- Crates are spawned by the CrateSystem when units are destroyed under specific conditions
- Multiple crate templates can be active simultaneously with different spawning conditions
- Crate spawning is probabilistic and adds unpredictability to battlefield rewards
- Crate contents are predefined and cannot be modified during gameplay
- The crate system integrates with unit destruction and veterancy systems
- Crate templates are defined in INI files and loaded by the CrateSystem
- Crate spawning conditions must be carefully balanced to avoid gameplay disruption
- The system supports both neutral and player-owned crates for different strategic scenarios

## Source Files

**Base Class:** [CrateTemplate](../../GeneralsMD/Code/GameEngine/Include/GameLogic/CrateSystem.h)
- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/CrateSystem.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/CrateSystem.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/System/CrateSystem.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/System/CrateSystem.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet
