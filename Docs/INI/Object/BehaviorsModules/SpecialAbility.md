# SpecialAbility

SpecialAbility provides basic special power functionality without additional features.

## Overview

The `SpecialAbility` class is a basic special power module that extends the functionality of SpecialPowerModule without adding any additional properties or behaviors. It serves as a simple special power implementation that can be used when no special features are needed beyond the base special power functionality. This behavior is commonly used for simple special powers that only need basic activation without additional parameters.

## Usage

Used by objects that need basic special power functionality without additional features, such as simple special abilities or basic superweapons. This is a **special power module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- SpecialAbility only provides basic special power functionality
- The behavior has no additional properties or special features
- Special power activation is limited by the base SpecialPowerModule functionality
- The behavior only works when the object is not disabled

**Conditions**:
- SpecialAbility extends SpecialPowerModule with no additional functionality
- The behavior can be activated at specific objects, locations, or without a target
- Special power timing and cooldown systems control when the behavior can activate
- The behavior integrates with the special power system for activation
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own special power settings

**Dependencies**:
- Requires the special power system to function correctly
- The behavior relies on SpecialPowerModule base functionality for all features

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

SpecialAbility has no additional properties beyond those inherited from SpecialPowerModule (special power timing, cooldown, science requirements, etc.).

## Examples

### Basic Special Power
```ini
SpecialPower = SpecialAbility ModuleTag_Basic
End
```

### Object-Targeted Special Power
```ini
SpecialPower = SpecialAbility ModuleTag_Target
End
```

### Location-Targeted Special Power
```ini
SpecialPower = SpecialAbility ModuleTag_Location
End
```

## Template

```ini
SpecialPower = SpecialAbility ModuleTag_XX
  ; No additional properties - uses base SpecialPowerModule properties
End
```

## Notes

- SpecialAbility extends SpecialPowerModule with no additional functionality
- The behavior can be activated at specific objects, locations, or without a target
- Special power timing and cooldown systems control when the behavior can activate
- The behavior integrates with the special power system for activation
- This is the simplest special power implementation and requires no additional configuration

## Source Files

**Base Class:** [`SpecialPowerModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialAbility.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialAbility.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/SpecialPower/SpecialAbility.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/SpecialPower/SpecialAbility.cpp)