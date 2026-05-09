# LockWeaponCreate

Create module that permanently locks a specific weapon slot to prevent weapon switching when objects are created.

## Overview

LockWeaponCreate is a create module that automatically locks a specific weapon slot when objects are created or when construction completes. This prevents players from switching to different weapons in that slot, effectively forcing the object to use only the weapon assigned to that slot. This is commonly used for specialized units or structures that should only use specific weapons.

LockWeaponCreate must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that should permanently lock specific weapon slots to prevent weapon switching when they are created. This is a **create module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Only affects weapon slots that exist on the object
- Cannot unlock weapons that are already locked by other means
- Permanent lock cannot be removed during gameplay
- Requires valid weapon slots to function

**Conditions**:
- Multiple instances behavior: Multiple LockWeaponCreate modules can exist independently, each locking different weapon slots
- Always active once assigned to an object
- Triggers during onCreate and onBuildComplete events
- Creates consistent weapon behavior for specialized units

**Dependencies**:
- Requires valid weapon slots on the target object
- Depends on the weapon system for weapon slot management
- Inherits all functionality from CreateModule

## Properties

### Weapon Slot Configuration

#### `SlotToLock` *(v1.04)*
- **Type**: `WeaponSlotType` (enum)
- **Description**: The weapon slot to permanently lock. When set, prevents weapon switching for this slot. When set to PRIMARY_WEAPON (default), locks the primary weapon slot
- **Default**: `PRIMARY_WEAPON`
- **Example**: `SlotToLock = SECONDARY_WEAPON`

## Enum Value Lists

#### `WeaponSlotType` Values *(v1.04)*
**Source:** [WeaponSet.h](../../GeneralsMD/Code/GameEngine/Include/GameLogic/WeaponSet.h) - `WeaponSlotType` enum definition

- **`PRIMARY_WEAPON`** *(v1.04)* - Primary weapon slot (main weapon)
- **`SECONDARY_WEAPON`** *(v1.04)* - Secondary weapon slot (backup weapon)
- **`TERTIARY_WEAPON`** *(v1.04)* - Tertiary weapon slot (third weapon)

## Examples

### Lock Primary Weapon
```ini
Create = LockWeaponCreate ModuleTag_01
  SlotToLock = PRIMARY_WEAPON
End
```

### Lock Secondary Weapon
```ini
Create = LockWeaponCreate ModuleTag_02
  SlotToLock = SECONDARY_WEAPON
End
```

### Lock Tertiary Weapon
```ini
Create = LockWeaponCreate ModuleTag_03
  SlotToLock = TERTIARY_WEAPON
End
```

## Template

```ini
Create = LockWeaponCreate ModuleTag_XX
  ; Weapon Slot Configuration
  SlotToLock = PRIMARY_WEAPON           ; // weapon slot to permanently lock *(v1.04)*
End
```

## Notes

- LockWeaponCreate permanently locks weapon slots to prevent weapon switching
- Commonly used for specialized units that should only use specific weapons
- The lock is permanent and cannot be removed during gameplay
- Creates consistent weapon behavior for specific unit types
- The module ensures objects use only their designated weapons

## Source Files

**Base Class:** [`CreateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/LockWeaponCreate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/LockWeaponCreate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Create/LockWeaponCreate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Create/LockWeaponCreate.cpp)