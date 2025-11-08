# BaikonurLaunchPower

Special power module that triggers the Baikonur launch tower sequence for the GLA end game scenario.

## Overview

BaikonurLaunchPower is a specialized special power module used exclusively for the GLA end game scenario. It triggers the launch sequence of the Baikonur launch tower, opening the tower doors and creating detonation effects at specified locations. This module is primarily used by scripts to initiate the climactic final mission sequence.

BaikonurLaunchPower must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that should trigger the Baikonur launch tower sequence for the GLA end game scenario. This is a **special power module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Primarily designed for script-controlled end game sequences
- Requires valid detonation object template to function
- Cannot be used when the object is disabled
- Limited to specific end game scenarios

**Conditions**:
- Multiple instances behavior: Multiple BaikonurLaunchPower modules can exist independently, each triggering different launch sequences
- Must be activated through special power system
- Object must not be disabled to function
- Opens tower doors (MODELCONDITION_DOOR_1_OPENING) when activated

**Dependencies**:
- Requires valid detonation object template reference
- Depends on the special power system for activation
- Inherits all functionality from SpecialPowerModule

## Properties

### Detonation Settings

#### `DetonationObject` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Name of the object template to create as a detonation effect at the target location. When set, creates the specified object at the power activation location. When empty (default), no detonation object is created
- **Default**: `""` (empty)
- **Example**: `DetonationObject = GLAAtomicBomb`

## Examples

### GLA End Game Launch Tower
```ini
SpecialPower = BaikonurLaunchPower ModuleTag_01
  DetonationObject = GLAAtomicBomb
End
```

### Launch Sequence Trigger
```ini
SpecialPower = BaikonurLaunchPower ModuleTag_02
  DetonationObject = GLAMissileExplosion
End
```

## Template

```ini
SpecialPower = BaikonurLaunchPower ModuleTag_XX
  ; Detonation Settings
  DetonationObject =                   ; // detonation object to create *(v1.04)*
End
```

## Notes

- BaikonurLaunchPower is specifically designed for the GLA end game scenario
- When activated, it opens the tower doors (MODELCONDITION_DOOR_1_OPENING)
- Creates detonation objects at the specified target location
- Primarily used by scripts rather than player activation
- The detonation object is created on the same team as the power source
- This module represents a unique end game mechanic rather than a general-purpose special power

## Source Files

**Base Class:** [`SpecialPowerModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BaikonurLaunchPower.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BaikonurLaunchPower.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/SpecialPower/BaikonurLaunchPower.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/SpecialPower/BaikonurLaunchPower.cpp)