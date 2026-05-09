# CashBountyPower

CashBountyPower provides cash bounty functionality for special powers and objects.

## Overview

The `CashBountyPower` class manages cash bounty systems that provide monetary rewards to players when they destroy specific objects. It automatically sets the player's cash bounty when the object is created or when the special power is activated, allowing for dynamic bounty systems based on upgrade states and science requirements. This behavior is commonly used for high-value targets, special objectives, and reward systems.

## Usage

Used by objects that should provide cash bounties when destroyed, such as high-value targets, special objectives, or reward systems. This is a **special power module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- CashBountyPower only sets bounties when the object is created or special power is activated
- Bounty amounts are limited by the specified Bounty value
- The behavior requires the controlling player to have the required science to set bounties
- Bounty amounts can only be increased, not decreased, by subsequent objects
- The behavior integrates with the special power system for activation timing

**Conditions**:
- CashBountyPower automatically sets the player's cash bounty when conditions are met
- The behavior checks science requirements before setting bounty amounts
- Bounty amounts are calculated based on the DefaultBounty value
- The behavior integrates with the upgrade system for conditional bounty amounts
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own bounty settings

**Dependencies**:
- Requires valid player and cash system integration to function correctly
- The behavior relies on science system for conditional activation

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Bounty Settings](#bounty-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

### Bounty Settings

#### `Bounty` *(v1.04)*
- **Type**: `Real` (percentage converted to decimal)
- **Description**: Default bounty amount to set when the object is created or special power is activated. Higher percentages increase the cash reward for destroying this object, making it a more valuable target. Values above 100% provide bonus rewards, while values below 100% reduce the standard reward
- **Default**: `0.0`
- **Example**: `Bounty = 150%`

## Examples

### High-Value Target Bounty
```ini
SpecialPower = CashBountyPower ModuleTag_Bounty
  Bounty = 200%
End
```

### Special Objective Bounty
```ini
SpecialPower = CashBountyPower ModuleTag_Objective
  Bounty = 500%
End
```

### Science-Required Bounty
```ini
SpecialPower = CashBountyPower ModuleTag_Science
  Bounty = 300%
  RequiredScience = SCIENCE_LEVEL_3
End
```

## Template

```ini
SpecialPower = CashBountyPower ModuleTag_XX
  Bounty = 0%                          ; // default bounty amount *(v1.04)*
End
```

## Notes

- CashBountyPower automatically sets the player's cash bounty when conditions are met
- The behavior checks science requirements before setting bounty amounts
- Bounty amounts are calculated based on the DefaultBounty value
- The behavior integrates with the upgrade system for conditional bounty amounts
- Bounty amounts can only be increased, not decreased, by subsequent objects

## Source Files

**Base Class:** [`SpecialPowerModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CashBountyPower.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CashBountyPower.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/SpecialPower/CashBountyPower.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/SpecialPower/CashBountyPower.cpp)