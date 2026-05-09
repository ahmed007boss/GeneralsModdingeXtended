# LocomotorSetUpgrade

LocomotorSetUpgrade provides the ability to enable locomotor upgrades for objects when an upgrade is applied, allowing for enhanced movement capabilities and pathfinding improvements.

## Overview

The `LocomotorSetUpgrade` class manages locomotor upgrade activation for objects when specific upgrades are applied. This upgrade module allows objects to have enhanced movement capabilities by enabling locomotor upgrades in their AI system. The behavior is commonly used for units that gain improved movement, pathfinding, or navigation abilities through upgrades.

## Usage

Used by objects that need enhanced movement capabilities when upgrades are applied. This is an **upgrade module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Only affects objects with AIUpdateInterface
- The locomotor upgrade is a simple boolean flag
- No additional configuration options are available
- Objects must have AI systems to function properly

**Conditions**:
- LocomotorSetUpgrade enables locomotor upgrades when the specified upgrade is applied
- The upgrade integrates with the upgrade system for conditional activation
- The locomotor upgrade affects the object's AI movement system
- Objects must have AIUpdateInterface to receive the upgrade
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own locomotor upgrades

**Dependencies**:
- Requires an object with upgrade system integration
- Objects must have AIUpdateInterface to function properly
- The AI system must be available for locomotor upgrade activation

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

This upgrade module has no configurable properties. It simply enables the locomotor upgrade flag when the upgrade is applied.

## Examples

### Basic Locomotor Upgrade
```ini
Upgrade = LocomotorSetUpgrade ModuleTag_LocomotorUpgrade
  TriggeredBy = Upgrade_MovementTraining
End
```

### Advanced Movement Upgrade
```ini
Upgrade = LocomotorSetUpgrade ModuleTag_AdvancedMovement
  TriggeredBy = Upgrade_AdvancedMovementTraining
  ConflictsWith = Upgrade_BasicMovementTraining
End
```

### Elite Movement Enhancement
```ini
Upgrade = LocomotorSetUpgrade ModuleTag_EliteMovement
  TriggeredBy = Upgrade_EliteTraining
  RequiresAll = Yes
End
```

### Conditional Movement Upgrade
```ini
Upgrade = LocomotorSetUpgrade ModuleTag_ConditionalMovement
  TriggeredBy = Upgrade_MovementResearch
  ConflictsWith = Upgrade_DisabledMovement
End
```

## Template

```ini
Upgrade = LocomotorSetUpgrade ModuleTag_XX
  ; Upgrade Integration (inherited from UpgradeModule)
  TriggeredBy =                    ; // required upgrade flags *(v1.04)*
  ConflictsWith =                  ; // conflicting upgrade flags *(v1.04)*
  RequiresAll = No                 ; // require all TriggeredBy upgrades *(v1.04)*
End
```

## Notes

- LocomotorSetUpgrade enables locomotor upgrades when the specified upgrade is applied
- The upgrade integrates with the upgrade system for conditional activation
- The locomotor upgrade affects the object's AI movement system
- Objects must have AIUpdateInterface to receive the upgrade
- Only affects objects with AIUpdateInterface
- The locomotor upgrade is a simple boolean flag
- No additional configuration options are available
- Objects must have AI systems to function properly
- The upgrade enables enhanced movement capabilities in the AI system

## Source Files

**Base Class:** [`UpgradeModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/LocomotorSetUpgrade.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/LocomotorSetUpgrade.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/LocomotorSetUpgrade.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Upgrade/LocomotorSetUpgrade.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet
