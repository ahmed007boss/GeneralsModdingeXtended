# DemoTrapUpdate

Update module that provides demolition trap functionality for objects that can create explosive traps with configurable proximity modes and weapon slot management.

## Overview

DemoTrapUpdate is an update module that provides demolition trap functionality for objects that can create explosive traps such as explosive devices or booby traps. It manages proximity detection modes, detonation weapon systems, and trap activation mechanics. The module supports both manual and automatic proximity-based detonation modes.

DemoTrapUpdate must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that can create demolition traps, such as explosive devices or booby traps. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Requires valid weapon templates for detonation operations
- Cannot function without proper update and weapon systems
- Trap functionality is limited by proximity detection capabilities
- Requires proper weapon slot configuration for detonation

**Conditions**:
- Multiple instances behavior: Multiple DemoTrapUpdate modules can exist independently, each managing different trap systems
- Always active once assigned to an object
- Continuously monitors for proximity triggers and manages detonation
- Creates explosive trap capabilities with configurable activation modes

**Dependencies**:
- Depends on the weapon system for detonation operations
- Requires proper update system for proximity monitoring
- Inherits all functionality from UpdateModule

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Trap Configuration](#trap-configuration)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

### Trap Configuration

#### `DefaultProximityMode` *(v1.04)*
- **Type**: `Bool`
- **Description**: Whether the trap defaults to proximity mode activation. When true, the trap automatically triggers when enemies approach. When false (default), the trap requires manual detonation
- **Default**: `No`
- **Example**: `DefaultProximityMode = Yes`

#### `DetonationWeaponSlot` *(v1.04)*
- **Type**: `WeaponSlotType` (see [WeaponSlotType Values](#weaponslottype-values) section)
- **Description**: Weapon slot used for trap detonation. When set, the specified weapon slot is used for explosive detonation. When empty (default), no weapon slot is specified
- **Default**: `PRIMARY`
- **Example**: `DetonationWeaponSlot = PRIMARY`

#### `ProximityModeWeaponSlot` *(v1.04)*
- **Type**: `WeaponSlotType` (see [WeaponSlotType Values](#weaponslottype-values) section)
- **Description**: Weapon slot used to determine proximity mode activation. When set, the specified weapon slot determines proximity detection. When empty (default), no proximity weapon slot is specified
- **Default**: `SECONDARY`
- **Example**: `ProximityModeWeaponSlot = SECONDARY`

### WeaponSlotType Values *(v1.04)*

- **`PRIMARY`** *(v1.04)* - Primary weapon slot
- **`SECONDARY`** *(v1.04)* - Secondary weapon slot
- **`TERTIARY`** *(v1.04)* - Tertiary weapon slot

## Examples

### Proximity Demo Trap
```ini
Behavior = DemoTrapUpdate ModuleTag_04
  DefaultProximityMode = Yes
  DetonationWeaponSlot = PRIMARY
  ProximityModeWeaponSlot = SECONDARY
End
```

### Manual Demo Trap
```ini
Behavior = DemoTrapUpdate ModuleTag_05
  DefaultProximityMode = No
  DetonationWeaponSlot = PRIMARY
  ProximityModeWeaponSlot = SECONDARY
End
```

### Advanced Demo Trap
```ini
Behavior = DemoTrapUpdate ModuleTag_06
  DefaultProximityMode = Yes
  DetonationWeaponSlot = TERTIARY
  ProximityModeWeaponSlot = SECONDARY
End
```

## Template

```ini
Behavior = DemoTrapUpdate ModuleTag_XX
  ; Trap Configuration
  DefaultProximityMode = No              ; // whether trap defaults to proximity mode *(v1.04)*
  DetonationWeaponSlot = PRIMARY         ; // weapon slot for trap detonation *(v1.04)*
  ProximityModeWeaponSlot = SECONDARY    ; // weapon slot for proximity detection *(v1.04)*
End
```

## Notes

- DemoTrapUpdate creates explosive trap capabilities with flexible activation modes
- Proximity mode enables automatic detonation when enemies approach
- Manual mode requires player-controlled detonation for tactical timing
- Multiple weapon slots allow for complex trap and detection configurations
- This provides realistic demolition trap mechanics for strategic gameplay

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/DemoTrapUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/DemoTrapUpdate.cpp)
