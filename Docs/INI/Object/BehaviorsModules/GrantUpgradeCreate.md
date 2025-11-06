# GrantUpgradeCreate

Create module that grants upgrades to objects when they are created or when construction completes.

## Overview

GrantUpgradeCreate is a create module that automatically grants upgrades to objects during their creation process. It can grant both player-level upgrades (affecting the entire player) and object-level upgrades (affecting only the specific object). The module supports exemption status checking to prevent granting upgrades under certain conditions.

GrantUpgradeCreate must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that should automatically grant upgrades to themselves or their controlling player when created or when construction completes. This is a **create module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Requires valid upgrade templates to function
- Cannot grant upgrades when exempt status conditions are met
- Only functions during object creation or build completion phases
- Upgrade granting is subject to status condition checks

**Conditions**:
- Multiple instances behavior: Multiple GrantUpgradeCreate modules can exist independently, each granting different upgrades
- Always active once assigned to an object
- Triggers during onCreate and onBuildComplete events
- Creates automatic upgrade application for new objects and structures

**Dependencies**:
- Requires valid upgrade templates for upgrade granting
- Depends on the upgrade system for upgrade management
- Inherits all functionality from CreateModule

## Properties

### Upgrade Configuration

#### `UpgradeToGrant` *(v1.04)*
- **Type**: `AsciiString` (see [Upgrade documentation](../Upgrade.md))
- **Description**: Name of the upgrade template to grant to the object or player. When set, grants the specified upgrade. When empty (default), no upgrade is granted
- **Default**: `""` (empty)
- **Example**: `UpgradeToGrant = UpgradeAdvancedWeaponry`

### Status Control

#### `ExemptStatus` *(v1.04)*
- **Type**: `ObjectStatusMaskType` (see [ObjectStatusMaskType Values](#objectstatusmasktype-values) section)
- **Description**: Bitmask of object status flags that prevent upgrade granting. When the object has any of these status flags, the upgrade will not be granted. When set to 0 (default), no exemption status is checked
- **Default**: `0` (no exemption status)
- **Example**: `ExemptStatus = UNDER_CONSTRUCTION`

## Enum Value Lists

### ObjectStatusMaskType Values *(v1.04)*

- **`NONE`** *(v1.04)* - No status flags
- **`DESTROYED`** *(v1.04)* - Object is destroyed
- **`CAN_ATTACK`** *(v1.04)* - Object can attack
- **`UNDER_CONSTRUCTION`** *(v1.04)* - Object is under construction
- **`UNSELECTABLE`** *(v1.04)* - Object cannot be selected
- **`NO_COLLISIONS`** *(v1.04)* - Object has no collisions
- **`NO_ATTACK`** *(v1.04)* - Object cannot attack
- **`AIRBORNE_TARGET`** *(v1.04)* - Object is airborne target
- **`PARACHUTING`** *(v1.04)* - Object is parachuting
- **`REPULSOR`** *(v1.04)* - Object has repulsor effect
- **`HIJACKED`** *(v1.04)* - Object has been hijacked
- **`AFLAME`** *(v1.04)* - Object is on fire
- **`BURNED`** *(v1.04)* - Object is burned
- **`WET`** *(v1.04)* - Object is wet
- **`IS_FIRING_WEAPON`** *(v1.04)* - Object is currently firing weapon
- **`IS_BRAKING`** *(v1.04)* - Object is braking
- **`STEALTHED`** *(v1.04)* - Object is stealthed
- **`DETECTED`** *(v1.04)* - Object is detected
- **`CAN_STEALTH`** *(v1.04)* - Object can stealth
- **`SOLD`** *(v1.04)* - Object is being sold
- **`UNDERGOING_REPAIR`** *(v1.04)* - Object is being repaired
- **`RECONSTRUCTING`** *(v1.04)* - Object is reconstructing
- **`MASKED`** *(v1.04)* - Object is masked
- **`IS_ATTACKING`** *(v1.04)* - Object is attacking
- **`USING_ABILITY`** *(v1.04)* - Object is using ability
- **`IS_AIMING_WEAPON`** *(v1.04)* - Object is aiming weapon
- **`NO_ATTACK_FROM_AI`** *(v1.04)* - Object cannot be attacked by AI
- **`IGNORING_STEALTH`** *(v1.04)* - Object ignores stealth
- **`IS_CARBOMB`** *(v1.04)* - Object is a car bomb

## Examples

### Basic Upgrade Grant
```ini
Create = GrantUpgradeCreate ModuleTag_01
  UpgradeToGrant = UpgradeAdvancedArmor
End
```

### Construction-Exempt Upgrade
```ini
Create = GrantUpgradeCreate ModuleTag_02
  UpgradeToGrant = UpgradeWeaponBonus
  ExemptStatus = UNDER_CONSTRUCTION
End
```

### Player Upgrade Grant
```ini
Create = GrantUpgradeCreate ModuleTag_03
  UpgradeToGrant = UpgradePlayerExperience
End
```

## Template

```ini
Create = GrantUpgradeCreate ModuleTag_XX
  ; Upgrade Configuration
  UpgradeToGrant =                       ; // upgrade template to grant *(v1.04)*
  
  ; Status Control
  ExemptStatus = 0                       ; // status flags that prevent granting *(v1.04)*
End
```

## Notes

- GrantUpgradeCreate automatically grants upgrades during object creation and build completion
- Supports both player-level and object-level upgrades
- Can prevent upgrade granting based on object status conditions
- Commonly used for automatic upgrade application when objects are created
- The module handles upgrade type detection and appropriate granting methods
- Creates seamless upgrade integration for new objects and structures

## Source Files

**Base Class:** [`CreateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/GrantUpgradeCreate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/GrantUpgradeCreate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Create/GrantUpgradeCreate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Create/GrantUpgradeCreate.cpp)