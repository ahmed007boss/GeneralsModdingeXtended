# SpectreGunshipDeploymentUpdate

SpectreGunshipDeploymentUpdate provides deployment functionality specifically for Spectre gunship units.

## Overview

The `SpectreGunshipDeploymentUpdate` class manages deployment operations for Spectre gunship units that need specialized deployment mechanics and operations. It handles gunship deployment, attack area coordination, and special power integration for Spectre gunship operations. This update is commonly used by Spectre gunship units, aerial deployment systems, and units with specialized deployment capabilities.

## Usage

Used by Spectre gunship units that need specialized deployment mechanics and operations. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Spectre gunship deployment is limited by special power templates and deployment parameters
- Deployment operations depend on proper gunship template configuration
- Attack area coordination requires proper area radius parameters
- Deployment effectiveness varies based on gunship capabilities

**Conditions**:
- SpectreGunshipDeploymentUpdate manages Spectre gunship deployment and attack coordination
- The update handles gunship deployment, attack area management, and special power integration
- Deployment operations provide specialized aerial deployment capabilities
- Attack area coordination creates realistic gunship attack operations
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own deployment parameters

**Dependencies**:
- Uses special power system for deployment activation
- Integrates with gunship system for deployment operations
- Uses attack system for area coordination

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Deployment Settings](#deployment-settings)
  - [Attack Settings](#attack-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Deployment Settings

#### `SpecialPowerTemplate` *(v1.04)*
- **Type**: `SpecialPowerTemplate`
- **Description**: Template defining the special power for deployment. When set, provides special power functionality. When empty, no special power is available
- **Default**: `""`
- **Example**: `SpecialPowerTemplate = SuperweaponSpectreGunship`

#### `GunshipTemplateName` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Name of the gunship template to deploy. When set, deploys specified gunship template. When empty, uses default gunship template
- **Default**: `""`
- **Example**: `GunshipTemplateName = AmericaJetSpectreGunship`

### Attack Settings

#### `AttackAreaRadius` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Radius of the attack area for gunship operations. Higher values create larger attack areas. Lower values create smaller attack areas
- **Default**: `0.0`
- **Example**: `AttackAreaRadius = 200`

## Examples

### Basic Spectre Gunship Deployment
```ini
Behavior           = SpectreGunshipDeploymentUpdate ModuleTag_08
  SpecialPowerTemplate = SuperweaponSpectreGunship
  GunshipTemplateName  = AmericaJetSpectreGunship
  AttackAreaRadius     = 200
End
```

### AWACS Deployment
```ini
Behavior           = SpectreGunshipDeploymentUpdate ModuleSpectre_25
  SpecialPowerTemplate = SuperweaponAWACS
  RequiredScience      = SCIENCE_AWACS_L3
  GunshipTemplateName  = AmericaJetAWACS_L3
End
```

### Advanced Spectre Gunship Deployment
```ini
Behavior           = SpectreGunshipDeploymentUpdate ModuleTag_83
  SpecialPowerTemplate = SuperweaponSpectreGunship
  GunshipTemplateName  = AmericaJetSpectreGunship
  AttackAreaRadius     = 200
End
```

## Template

```ini
Behavior = SpectreGunshipDeploymentUpdate ModuleTag_XX
  ; Deployment Settings
  SpecialPowerTemplate =                   ; // special power template for deployment *(v1.04)*
  GunshipTemplateName =                    ; // name of gunship template to deploy *(v1.04)*
  
  ; Attack Settings
  AttackAreaRadius = 0.0                   ; // radius of attack area for gunship operations *(v1.04)*
End
```

## Notes

- SpectreGunshipDeploymentUpdate provides specialized deployment capabilities for Spectre gunship units
- The update manages gunship deployment, attack area coordination, and special power integration
- Deployment operations provide specialized aerial deployment capabilities for tactical advantage
- Attack area coordination creates realistic gunship attack operations and area control
- This update is commonly used by Spectre gunship units, aerial deployment systems, and specialized deployment units
- Gunship deployment creates powerful aerial support capabilities for tactical operations

## Source Files

**Base Class:** [`SpecialPowerUpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerUpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpectreGunshipDeploymentUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpectreGunshipDeploymentUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/SpectreGunshipDeploymentUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/SpectreGunshipDeploymentUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet