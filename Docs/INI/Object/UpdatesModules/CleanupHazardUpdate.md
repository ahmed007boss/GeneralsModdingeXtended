# CleanupHazardUpdate

Update module that provides hazard cleanup functionality for objects that can clean up environmental hazards with weapon-based scanning and cleanup operations.

## Overview

CleanupHazardUpdate is an update module that provides hazard cleanup functionality for objects that can clean up environmental hazards such as chemical spills, radiation, or other environmental dangers. It manages scanning for hazards within a specified range and uses weapon systems to clean up detected hazards. The module supports configurable scan rates and ranges for effective hazard management.

CleanupHazardUpdate must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that need to clean up hazards, such as chemical spills, radiation, or other environmental dangers. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Requires valid weapon templates for hazard cleanup operations
- Cannot function without proper update and weapon systems
- Hazard cleanup is limited by weapon range and capabilities
- Requires proper hazard detection system integration

**Conditions**:
- Multiple instances behavior: Multiple CleanupHazardUpdate modules can exist independently, each managing different hazard cleanup systems
- Always active once assigned to an object
- Continuously scans for hazards and performs cleanup operations
- Creates automated environmental hazard management capabilities

**Dependencies**:
- Depends on the weapon system for hazard cleanup operations
- Requires proper update system for continuous scanning
- Inherits all functionality from UpdateModule

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Weapon Configuration](#weapon-configuration)
  - [Scan Configuration](#scan-configuration)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

### Weapon Configuration

#### `WeaponSlot` *(v1.04)*
- **Type**: `WeaponSlotType` (see [WeaponSlotType Values](#weaponslottype-values) section)
- **Description**: Weapon slot used for hazard cleanup operations. When set, the specified weapon slot is used for cleaning up detected hazards. When empty (default), no weapon slot is specified
- **Default**: `PRIMARY`
- **Example**: `WeaponSlot = PRIMARY`

### Scan Configuration

#### `ScanRate` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time interval between hazard scans. Higher values scan less frequently but use fewer resources. Lower values scan more frequently for faster hazard detection. At 1000 (default), scans occur every 1000 milliseconds
- **Default**: `1000`
- **Example**: `ScanRate = 1000`

#### `ScanRange` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Maximum distance to scan for hazards. Higher values extend the scan range to detect hazards farther away. Lower values create smaller, more focused scan areas. At 100.0 (default), scans within 100 units
- **Default**: `100.0`
- **Example**: `ScanRange = 100.0`

### WeaponSlotType Values *(v1.04)*

- **`PRIMARY`** *(v1.04)* - Primary weapon slot
- **`SECONDARY`** *(v1.04)* - Secondary weapon slot
- **`TERTIARY`** *(v1.04)* - Tertiary weapon slot

## Examples

### Basic Hazard Cleanup
```ini
Behavior = CleanupHazardUpdate ModuleTag_03
  WeaponSlot = PRIMARY
  ScanRate = 1000
  ScanRange = 100.0
End
```

### Enhanced Hazard Cleanup
```ini
Behavior = CleanupHazardUpdate ModuleTag_03
  WeaponSlot = PRIMARY
  ScanRate = 500
  ScanRange = 175.0
End
```

### Extended Range Hazard Cleanup
```ini
Behavior = CleanupHazardUpdate ModuleTag_03
  WeaponSlot = PRIMARY
  ScanRate = 500
  ScanRange = 200.0
End
```

## Template

```ini
Behavior = CleanupHazardUpdate ModuleTag_XX
  ; Weapon Configuration
  WeaponSlot = PRIMARY                    ; // weapon slot for hazard cleanup *(v1.04)*
  
  ; Scan Configuration
  ScanRate = 1000                         ; // milliseconds between hazard scans *(v1.04)*
  ScanRange = 100.0                       ; // maximum scan distance for hazards *(v1.04)*
End
```

## Notes

- CleanupHazardUpdate provides automated environmental hazard cleanup capabilities
- The module continuously scans for hazards and uses weapon systems for cleanup operations
- Configurable scan rates and ranges allow for efficient hazard management
- This creates realistic environmental cleanup mechanics for specialized units

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/CleanupHazardUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/CleanupHazardUpdate.cpp)
