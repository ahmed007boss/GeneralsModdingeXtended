# CashHackSpecialPower

Special power module that steals money from enemy players when activated on their objects.

## Overview

CashHackSpecialPower is a special power module that allows the user to steal money from enemy players by targeting their objects. When activated on an enemy object, it transfers a specified amount of money from the target player to the power user. The amount stolen can be modified by upgrades and is limited by the target player's available funds.

CashHackSpecialPower must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that should steal money from enemy players when activated on their objects. This is a **special power module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Can only be used on enemy objects, not empty locations
- Cannot steal more money than the target player has available
- Requires valid target object to function
- Cannot be used when the power source is disabled
- Amount stolen is limited by target player's available funds

**Conditions**:
- Multiple instances behavior: Multiple CashHackSpecialPower modules can exist independently, each stealing different amounts
- Must be activated through special power system on enemy objects
- Target player must have sufficient funds to steal from
- Floating text displays money gained over the power source and money lost over the target

**Dependencies**:
- Requires enemy objects as targets
- Depends on the money system for fund transfers
- Inherits all functionality from SpecialPowerModule

## Properties

### Money Settings

#### `MoneyAmount` *(v1.04)*
- **Type**: `Int`
- **Description**: Default amount of money to steal from enemy players when no upgrades are active. Higher values steal more money per activation, while lower values steal less. When set to 0 (default), no money is stolen
- **Default**: `0`
- **Example**: `MoneyAmount = 1000`

### Upgrade Modifications

#### `UpgradeMoneyAmount` *(v1.04)*
- **Type**: `upgradePair` (multiple entries)
- **Description**: Additional money amounts to steal when specific upgrades are active. When upgrades are completed, the corresponding amount is stolen instead of the default. Higher values provide more money per activation with upgrades
- **Default**: `None`
- **Example**: 
```
UpgradeMoneyAmount = UpgradeType AdvancedHacking Amount 2000
UpgradeMoneyAmount = UpgradeType EliteHacking Amount 3000
```

## Examples

### Basic Cash Hack
```ini
SpecialPower = CashHackSpecialPower ModuleTag_01
  MoneyAmount = 1000
End
```

### Advanced Cash Hack with Upgrades
```ini
SpecialPower = CashHackSpecialPower ModuleTag_02
  MoneyAmount = 1000
  UpgradeMoneyAmount = UpgradeType AdvancedHacking Amount 2000
  UpgradeMoneyAmount = UpgradeType EliteHacking Amount 3000
End
```

## Template

```ini
SpecialPower = CashHackSpecialPower ModuleTag_XX
  ; Money Settings
  MoneyAmount = 0                     ; // default money amount to steal *(v1.04)*
  
  ; Upgrade Modifications
  UpgradeMoneyAmount =                ; // upgrade-based money amounts *(v1.04)*
End
```

## Notes

- CashHackSpecialPower steals money from enemy players when activated on their objects
- The amount stolen is limited by the target player's available funds
- Floating text displays money gained over the power source and money lost over the target
- Upgrade system allows different amounts based on completed research
- Money stolen is added to the power user's score as "money earned"
- Only works on enemy objects, not allied or neutral targets
- Commonly used by stealth units or special agents for economic warfare

## Source Files

**Base Class:** [`SpecialPowerModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CashHackSpecialPower.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CashHackSpecialPower.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/SpecialPower/CashHackSpecialPower.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/SpecialPower/CashHackSpecialPower.cpp)