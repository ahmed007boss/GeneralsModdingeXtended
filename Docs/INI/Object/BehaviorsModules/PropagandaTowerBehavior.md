# PropagandaTowerBehavior

Update module that provides propaganda tower functionality for structures that can broadcast propaganda effects over a radius with area healing and visual effects.

## Overview

PropagandaTowerBehavior is an update module that provides propaganda tower functionality for structures that can broadcast propaganda effects over a specified radius. It provides area-of-effect healing to nearby friendly units, supports upgrade-based activation with enhanced effects, and includes visual pulse effects. The module continuously scans for nearby objects and applies healing effects to those within its influence radius.

PropagandaTowerBehavior must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by propaganda tower structures to provide area-of-effect propaganda benefits and healing effects. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Requires proper update and damage systems for functionality
- Cannot function without proper FX templates for visual effects
- Healing effects are limited by the specified radius
- Requires proper upgrade system for conditional activation

**Conditions**:
- Multiple instances behavior: Multiple PropagandaTowerBehavior modules can exist independently, each managing different propaganda systems
- Always active once assigned to an object
- Continuously scans for nearby objects and applies healing effects
- Creates area-of-effect propaganda benefits with visual feedback

**Dependencies**:
- Depends on the update system for continuous scanning and healing
- Requires proper FX templates for visual pulse effects
- Inherits functionality from UpdateModule and DieModuleInterface

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Scan Configuration](#scan-configuration)
  - [Healing Settings](#healing-settings)
  - [Visual Effects](#visual-effects)
  - [Upgrade Integration](#upgrade-integration)
  - [Target Selection](#target-selection)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

### Scan Configuration

#### `Radius` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Radius of the propaganda tower's area of effect. Higher values extend the healing range to affect more nearby units. Lower values create smaller, more focused influence areas
- **Default**: `1.0`
- **Example**: `Radius = 150.0`

#### `DelayBetweenUpdates` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time interval between propaganda tower scans and healing pulses. Lower values provide more frequent healing updates. Higher values slow down the healing process. At 100 (default), scans occur every 100 milliseconds
- **Default**: `100`
- **Example**: `DelayBetweenUpdates = 2000`

### Healing Settings

#### `HealPercentEachSecond` *(v1.04)*
- **Type**: `Real` (percentage)
- **Description**: Percentage of maximum health healed per second to objects within the radius. Higher values provide faster healing rates. Lower values provide slower, more gradual healing. At 1% (default), objects heal 1% of their max health per second
- **Default**: `0.01` (1%)
- **Example**: `HealPercentEachSecond = 1%`

#### `UpgradedHealPercentEachSecond` *(v1.04)*
- **Type**: `Real` (percentage)
- **Description**: Enhanced percentage of maximum health healed per second when the required upgrade is active. Higher values provide faster healing rates when upgraded. Lower values provide slower enhanced healing. At 2% (default), objects heal 2% of their max health per second when upgraded
- **Default**: `0.02` (2%)
- **Example**: `UpgradedHealPercentEachSecond = 2%`

### Visual Effects

#### `PulseFX` *(v1.04)*
- **Type**: `FXList` (see [FXList documentation](../FXList.md))
- **Description**: FX list played during each propaganda pulse update. When set, displays visual effects during healing pulses. When empty (default), no pulse effects are shown
- **Default**: `""` (empty)
- **Example**: `PulseFX = FX_PropagandaTowerPropagandaPulse`

#### `UpgradedPulseFX` *(v1.04)*
- **Type**: `FXList` (see [FXList documentation](../FXList.md))
- **Description**: Enhanced FX list played during propaganda pulses when the required upgrade is active. When set, displays upgraded visual effects during healing pulses. When empty (default), no upgraded pulse effects are shown
- **Default**: `""` (empty)
- **Example**: `UpgradedPulseFX = FX_HelixPropagandaTowerPropagandaPulse`

### Upgrade Integration

#### `UpgradeRequired` *(v1.04)*
- **Type**: `AsciiString` (see [Upgrade documentation](../Upgrade.md))
- **Description**: Name of the upgrade required to activate enhanced propaganda effects. When set, enhanced healing and visual effects only occur when the specified upgrade is active. When empty (default), no upgrade is required
- **Default**: `""` (empty)
- **Example**: `UpgradeRequired = Upgrade_ChinaSubliminalMessaging`

### Target Selection

#### `AffectsSelf` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether the propaganda tower can affect itself with healing effects. When true, the tower heals itself along with nearby units. When false (default), the tower only heals nearby units, not itself
- **Default**: `No`
- **Example**: `AffectsSelf = Yes`

## Examples

### Basic Propaganda Tower
```ini
Behavior = PropagandaTowerBehavior ModuleTag_04
  Radius = 150.0
  DelayBetweenUpdates = 2000
  HealPercentEachSecond = 1%
  PulseFX = FX_PropagandaTowerPropagandaPulse
End
```

### Enhanced Propaganda Tower with Upgrades
```ini
Behavior = PropagandaTowerBehavior ModuleTag_10
  Radius = 150.0
  DelayBetweenUpdates = 2000
  HealPercentEachSecond = 1%
  PulseFX = FX_PropagandaTowerPropagandaPulse
  UpgradeRequired = Upgrade_ChinaSubliminalMessaging
  UpgradedHealPercentEachSecond = 2%
  UpgradedPulseFX = FX_HelixPropagandaTowerPropagandaPulse
End
```

### Self-Healing Propaganda Tower
```ini
Behavior = PropagandaTowerBehavior ModuleTag_04
  Radius = 150.0
  DelayBetweenUpdates = 2000
  HealPercentEachSecond = 1%
  PulseFX = FX_PropagandaTowerPropagandaPulse
  AffectsSelf = Yes
End
```

## Template

```ini
Behavior = PropagandaTowerBehavior ModuleTag_XX
  ; Scan Configuration
  Radius = 1.0                     ; // propaganda tower area of effect radius *(v1.04)*
  DelayBetweenUpdates = 100        ; // milliseconds between scans *(v1.04)*
  
  ; Healing Settings
  HealPercentEachSecond = 0.01     ; // percentage of max health healed per second *(v1.04)*
  UpgradedHealPercentEachSecond = 0.02 ; // enhanced healing percentage when upgraded *(v1.04)*
  
  ; Visual Effects
  PulseFX =                        ; // FX list for propaganda pulses *(v1.04)*
  UpgradedPulseFX =                ; // enhanced FX list when upgraded *(v1.04)*
  
  ; Upgrade Integration
  UpgradeRequired =                ; // required upgrade for enhanced effects *(v1.04)*
  
  ; Target Selection
  AffectsSelf = No                 ; // whether tower affects itself *(v1.04)*
End
```

## Notes

- PropagandaTowerBehavior provides area-of-effect healing and propaganda benefits to nearby friendly units
- The module continuously scans for nearby objects and applies healing effects within its radius
- Upgrade-based activation provides enhanced healing rates and visual effects
- Visual pulse effects provide feedback during healing operations
- The tower can optionally heal itself along with nearby units
- This creates powerful area support capabilities for propaganda tower structures

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h), [`DieModuleInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/PropagandaTowerBehavior.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/PropagandaTowerBehavior.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/PropagandaTowerBehavior.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/PropagandaTowerBehavior.cpp)
