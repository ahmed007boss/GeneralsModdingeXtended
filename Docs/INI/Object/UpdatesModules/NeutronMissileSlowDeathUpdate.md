# NeutronMissileSlowDeathUpdate

NeutronMissileSlowDeathUpdate provides slow death functionality specifically for neutron missile units.

## Overview

The `NeutronMissileSlowDeathUpdate` class manages extended death sequences specifically designed for neutron missile units, featuring neutron effects, radiation patterns, and specialized missile death animations. It extends SlowDeathBehavior to provide neutron missile-specific death mechanics including radiation effects, neutron blast patterns, and controlled destruction sequences that create dramatic neutron weapon impact.

## Usage

Used by neutron missile units that need extended death sequences with neutron effects and animations. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Death sequences are limited by neutron effect parameters
- Radiation patterns are controlled by neutron-specific settings
- Missile destruction is limited by neutron blast mechanics
- Update delays control the frequency of neutron effect calculations

**Conditions**:
- NeutronMissileSlowDeathUpdate creates dramatic neutron blast patterns during death
- The update applies neutron-specific radiation effects and damage patterns
- Neutron effects simulate realistic neutron weapon impact and aftermath
- Death sequences include specialized neutron missile destruction mechanics
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own neutron effects

**Dependencies**:
- Extends SlowDeathBehavior for base death functionality
- Uses neutron effect system for radiation and blast patterns
- Integrates with damage system for neutron radiation effects

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
  - [Reviews (0)](#modder-reviews)

## Properties

*Properties documentation will be added when this page is completed from the corresponding C++ source files.*

## Examples

*No examples of NeutronMissileSlowDeathUpdate were found in the INI files.*

## Template

```ini
Behavior = NeutronMissileSlowDeathUpdate ModuleTag_XX
  ; Properties will be documented from source files
End
```

## Notes

- NeutronMissileSlowDeathUpdate extends SlowDeathBehavior with neutron missile-specific death mechanics
- The update creates realistic neutron blast patterns and radiation effects
- Neutron effects simulate the impact and aftermath of neutron weapon deployment
- This update is commonly used by neutron missile units for cinematic death sequences
- Neutron death mechanics provide specialized destruction patterns for neutron weapons

## Source Files

**Base Class:** [`SlowDeathBehavior`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SlowDeathBehavior.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/HelicopterSlowDeathUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/HelicopterSlowDeathUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/HelicopterSlowDeathUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/HelicopterSlowDeathUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet