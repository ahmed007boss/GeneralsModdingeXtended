# DefectorSpecialPower

Special power module that converts enemy units to the user's team when activated on them.

## Overview

DefectorSpecialPower is a special power module that allows the user to convert enemy units to their own team when activated on them. The power causes the target unit to defect to the user's team for a specified duration, effectively turning enemy units into allies. This creates powerful tactical opportunities by converting enemy forces.

DefectorSpecialPower must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that should convert enemy units to the user's team when activated on them. This is a **special power module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Can only be used on enemy objects, not empty locations
- Requires valid target object to function
- Cannot be used when the power source is disabled
- Defection duration is controlled by the special power template's detection time
- Only works on enemy objects, not allied or neutral targets

**Conditions**:
- Multiple instances behavior: Multiple DefectorSpecialPower modules can exist independently, each providing different defection capabilities
- Must be activated through special power system on enemy objects
- Target object must be defection-capable
- Creates powerful tactical opportunities by turning enemy forces into allies

**Dependencies**:
- Requires enemy objects as targets
- Depends on the object defection system
- Inherits all functionality from SpecialPowerModule

## Properties

### Targeting Settings

#### `FatCursorRadius` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Radius around the target object that affects the defection area. Higher values create larger defection zones around the target. At 0 (default), only the exact target object is affected
- **Default**: `0.0`
- **Example**: `FatCursorRadius = 50.0`

## Examples

### Basic Unit Defection
```ini
SpecialPower = DefectorSpecialPower ModuleTag_01
  FatCursorRadius = 0.0
End
```

### Area Defection Power
```ini
SpecialPower = DefectorSpecialPower ModuleTag_02
  FatCursorRadius = 100.0
End
```

### Elite Defection Ability
```ini
SpecialPower = DefectorSpecialPower ModuleTag_03
  FatCursorRadius = 75.0
End
```

## Template

```ini
SpecialPower = DefectorSpecialPower ModuleTag_XX
  ; Targeting Settings
  FatCursorRadius = 0.0              ; // defection area radius *(v1.04)*
End
```

## Notes

- DefectorSpecialPower converts enemy units to the user's team when activated
- The defection duration is controlled by the special power template's detection time
- Only works on enemy objects, not allied or neutral targets
- The FatCursorRadius creates an area effect around the target for defection
- Creates powerful tactical opportunities by turning enemy forces into allies
- Commonly used by special agents or generals with defection abilities
- The power requires careful timing and targeting to be effective

## Source Files

**Base Class:** [`SpecialPowerModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DefectorSpecialPower.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DefectorSpecialPower.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/SpecialPower/DefectorSpecialPower.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/SpecialPower/DefectorSpecialPower.cpp)