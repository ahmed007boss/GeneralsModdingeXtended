# AutoDepositUpdate

AutoDepositUpdate provides automatic resource generation and deposit functionality for objects that can generate income over time.

## Overview

The `AutoDepositUpdate` class manages automatic resource generation for objects that produce income at regular intervals. It handles periodic cash deposits, initial capture bonuses, upgrade-based income boosts, and visual feedback for resource generation. This update is commonly used for supply centers, cash generators, and other income-producing structures.

## Usage

Used by objects that need to automatically generate and deposit resources at regular intervals. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- AutoDepositUpdate automatically deposits resources at the specified timing intervals
- Resources are only deposited if the object is not neutral-controlled and construction is complete
- Initial capture bonus is awarded once when the object is first captured
- Objects must be fully constructed before they begin generating resources
- The update continues running as long as the object exists and is not neutral-controlled

**Conditions**:
- Upgrade boosts are additive and applied to the base deposit amount
- Floating text displays the deposit amount above the object (hidden for stealthed objects unless detected)
- Deposit amounts are added to the player's money and recorded in score statistics
- Visual feedback includes floating text with the deposit amount in the player's color
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own resource types and deposit rates

**Dependencies**:
- Requires proper resource system integration to function correctly

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Basic Settings](#basic-settings)
  - [Capture Bonus Settings](#capture-bonus-settings)
  - [Upgrade Settings](#upgrade-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

### Basic Settings

#### `DepositTiming` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time interval between automatic resource deposits. Lower values provide more frequent resource generation, while higher values slow down the deposit rate
- **Default**: `60000`
- **Example**: `DepositTiming = 60000`

#### `DepositAmount` *(v1.04)*
- **Type**: `Int`
- **Description**: Base amount of resources deposited each cycle. Higher values generate more resources per deposit, while lower values provide less income
- **Default**: `800`
- **Example**: `DepositAmount = 800`

#### `ActualMoney` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether the deposited resources are actual money (affects scoring). When true, deposits count toward player score and statistics. When false, deposits are internal only and do not affect scoring
- **Default**: `Yes`
- **Example**: `ActualMoney = Yes`

### Capture Bonus Settings

#### `InitialCaptureBonus` *(v1.04)*
- **Type**: `Int`
- **Description**: One-time bonus resources awarded when the object is captured. Higher values provide larger immediate rewards for capturing the structure. At 0 (default), no capture bonus is awarded
- **Default**: `0`
- **Example**: `InitialCaptureBonus = 1000`

### Upgrade Settings

#### `UpgradedBoost` *(v1.04)*
- **Type**: `upgradePair` (multiple entries)
- **Description**: Additional resource boost when specific upgrades are completed
- **Default**: `None`
- **Example**: 
```
UpgradedBoost = UpgradeType SupplyBoost Boost 200
UpgradedBoost = UpgradeType AdvancedMining Boost 150
```

## Examples

### Supply Center with Upgrade Boost
```ini
Behavior = AutoDepositUpdate ModuleTag_05
  DepositTiming = 60000
  DepositAmount = 800
  InitialCaptureBonus = 0
  ActualMoney = Yes
  UpgradedBoost = UpgradeType SupplyBoost Boost 200
End
```

### Quick Income Generator
```ini
Behavior = AutoDepositUpdate ModuleTag_05
  DepositTiming = 20000
  DepositAmount = 200
  InitialCaptureBonus = 500
  ActualMoney = Yes
End
```

### Money Hack Building
```ini
Behavior = AutoDepositUpdate ModuleTag_Money
  DepositTiming = 15000
  DepositAmount = 100
  InitialCaptureBonus = 1000
  ActualMoney = Yes
  UpgradedBoost = UpgradeType InternetHack Boost 300
  UpgradedBoost = UpgradeType AdvancedHacking Boost 500
End
```

### Neutral Resource Node
```ini
Behavior = AutoDepositUpdate ModuleTag_Resources
  DepositTiming = 30000
  DepositAmount = 150
  InitialCaptureBonus = 750
  ActualMoney = No
End
```

## Template

```ini
Behavior = AutoDepositUpdate ModuleTag_XX
  ; Basic Settings
  DepositTiming = 60000           ; // milliseconds between deposits *(v1.04)*
  DepositAmount = 800             ; // base resources per deposit cycle *(v1.04)*
  ActualMoney = Yes               ; // whether deposits count as actual money *(v1.04)*

  ; Capture Bonus Settings
  InitialCaptureBonus = 0         ; // one-time bonus on capture *(v1.04)*

  ; Upgrade Settings
  UpgradedBoost = UpgradeType SupplyBoost Boost 200 ; // upgrade boost *(v1.04)*
  UpgradedBoost = UpgradeType AdvancedMining Boost 150 ; // additional upgrade boost *(v1.04)*
End
```

## Notes

- AutoDepositUpdate automatically deposits resources at the specified timing intervals
- Resources are only deposited if the object is not neutral-controlled and construction is complete
- Initial capture bonus is awarded once when the object is first captured
- Upgrade boosts are additive and applied to the base deposit amount
- Floating text displays the deposit amount above the object (hidden for stealthed objects unless detected)
- Deposit amounts are added to the player's money and recorded in score statistics
- Objects must be fully constructed before they begin generating resources
- The update continues running as long as the object exists and is not neutral-controlled
- Visual feedback includes floating text with the deposit amount in the player's color

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AutoDepositUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AutoDepositUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/AutoDepositUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/AutoDepositUpdate.cpp)