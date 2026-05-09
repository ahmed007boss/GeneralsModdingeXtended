# UnpauseSpecialPowerUpgrade

UnpauseSpecialPowerUpgrade provides the ability to start the timer on a special power when an upgrade is applied, allowing for upgrade-dependent special power activation.

## Overview

The `UnpauseSpecialPowerUpgrade` class manages special power timer activation when specific upgrades are applied. This upgrade module allows objects to start the timer on a special power when the upgrade is activated, providing a way to make special powers dependent on upgrades. The behavior is commonly used for special powers that are initially paused and need to be activated through upgrades, similar to how NEED_UPGRADE works on the client side by disabling buttons.

## Usage

Used by objects that need to activate special power timers when upgrades are applied. This is an **upgrade module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Only affects special power timers, not other special power properties
- The special power must exist and be properly defined
- Timer activation occurs immediately when the upgrade is activated
- Objects must have special power systems to function properly

**Conditions**:
- UnpauseSpecialPowerUpgrade starts the special power timer when the specified upgrade is applied
- The upgrade integrates with the upgrade system for conditional activation
- The special power timer begins counting down when the upgrade is activated
- Objects must have the specified special power to function properly
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own special power timer activation

**Dependencies**:
- Requires an object with upgrade system integration
- The special power must exist and be properly defined
- Objects must have special power systems to function properly
- The special power module must be available

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

### Special Power Settings

#### `SpecialPowerTemplate` *(v1.04)*
- **Type**: `SpecialPowerTemplate`
- **Description**: The special power template to start the timer for when this upgrade is applied. This special power must exist and be properly defined. The timer will begin counting down when the upgrade is activated
- **Default**: `NULL` (none)
- **Example**: `SpecialPowerTemplate = "SpecialPower_EliteAttack"`

## Examples

### Basic Special Power Activation
```ini
Upgrade = UnpauseSpecialPowerUpgrade ModuleTag_SpecialPowerActivation
  SpecialPowerTemplate = "SpecialPower_EliteAttack"
  TriggeredBy = Upgrade_EliteTraining
End
```

### Advanced Special Power Unpause
```ini
Upgrade = UnpauseSpecialPowerUpgrade ModuleTag_AdvancedSpecialPower
  SpecialPowerTemplate = "SpecialPower_AdvancedAttack"
  TriggeredBy = Upgrade_AdvancedTraining
End
```

### Conditional Special Power Activation
```ini
Upgrade = UnpauseSpecialPowerUpgrade ModuleTag_ConditionalSpecialPower
  SpecialPowerTemplate = "SpecialPower_ConditionalAttack"
  TriggeredBy = Upgrade_ConditionalTraining
  ConflictsWith = Upgrade_BasicTraining
End
```

### Multiple Special Power Activations
```ini
Upgrade = UnpauseSpecialPowerUpgrade ModuleTag_SpecialPower1
  SpecialPowerTemplate = "SpecialPower_Attack1"
  TriggeredBy = Upgrade_Training1
End

Upgrade = UnpauseSpecialPowerUpgrade ModuleTag_SpecialPower2
  SpecialPowerTemplate = "SpecialPower_Attack2"
  TriggeredBy = Upgrade_Training2
End
```

## Template

```ini
Upgrade = UnpauseSpecialPowerUpgrade ModuleTag_XX
  ; Special Power Settings
  SpecialPowerTemplate =             ; // special power to start timer for *(v1.04)*
  
  ; Upgrade Integration (inherited from UpgradeModule)
  TriggeredBy =                      ; // required upgrade flags *(v1.04)*
  ConflictsWith =                    ; // conflicting upgrade flags *(v1.04)*
  RequiresAll = No                   ; // require all TriggeredBy upgrades *(v1.04)*
End
```

## Notes

- UnpauseSpecialPowerUpgrade starts the special power timer when the specified upgrade is applied
- The upgrade integrates with the upgrade system for conditional activation
- The special power timer begins counting down when the upgrade is activated
- Objects must have the specified special power to function properly
- Only affects special power timers, not other special power properties
- The special power must exist and be properly defined
- Timer activation occurs immediately when the upgrade is activated
- Objects must have special power systems to function properly
- This provides upgrade-dependent special power activation on the logic side, similar to NEED_UPGRADE on the client side

## Source Files

**Base Class:** [`UpgradeModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UnpauseSpecialPowerUpgrade.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UnpauseSpecialPowerUpgrade.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/UnpauseSpecialPowerUpgrade.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/UnpauseSpecialPowerUpgrade.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet
