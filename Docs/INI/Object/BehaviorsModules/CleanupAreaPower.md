# CleanupAreaPower

Special power module that enhances cleanup units to clean hazards in a specified area around a target location.

## Overview

CleanupAreaPower is a special power module that augments cleanup units (like ambulances) to clean hazards in a designated area. When activated at a location, it sets cleanup parameters for the CleanupHazardUpdate module, allowing the unit to move around and clean hazards until the area is clear. This is commonly used for medical units to clean up contamination or hazard areas.

CleanupAreaPower must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that should enhance cleanup units to clean hazards in a specified area around a target location. This is a **special power module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Requires CleanupHazardUpdate module to function
- Only works when the object is not disabled
- Limited to the specified movement range from target location
- Cannot function without proper cleanup hazard system integration

**Conditions**:
- Multiple instances behavior: Multiple CleanupAreaPower modules can exist independently, each managing different cleanup areas
- Must be activated through special power system at target locations
- Requires valid CleanupHazardUpdate module for cleanup functionality
- Sets cleanup parameters for the CleanupHazardUpdate module

**Dependencies**:
- Requires CleanupHazardUpdate module for actual cleanup operations
- Depends on the cleanup hazard system for area cleaning
- Inherits all functionality from SpecialPowerModule

## Properties

### Movement Settings

#### `MaxMoveDistanceFromLocation` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Maximum distance the cleanup unit can move from the target location while performing cleanup operations. Higher values allow the unit to clean larger areas around the target point. At 0 (default), the unit cannot move from the target location
- **Default**: `0.0`
- **Example**: `MaxMoveDistanceFromLocation = 100.0`

## Examples

### Ambulance Area Cleanup
```ini
SpecialPower = CleanupAreaPower ModuleTag_01
  MaxMoveDistanceFromLocation = 150.0
End

Update = CleanupHazardUpdate ModuleTag_02
  ; ... cleanup update properties
End
```

### Mobile Hazard Cleaner
```ini
SpecialPower = CleanupAreaPower ModuleTag_03
  MaxMoveDistanceFromLocation = 200.0
End

Update = CleanupHazardUpdate ModuleTag_04
  ; ... cleanup update properties
End
```

## Template

```ini
SpecialPower = CleanupAreaPower ModuleTag_XX
  ; Movement Settings
  MaxMoveDistanceFromLocation = 0.0    ; // maximum cleanup range from target *(v1.04)*
End
```

## Notes

- CleanupAreaPower enhances cleanup units to work in designated areas
- The power sets cleanup parameters for the CleanupHazardUpdate module
- Units will move around the target location within the specified range to clean hazards
- Cleanup continues until no more hazards are found in the area
- Commonly used by medical units to clean contamination areas
- The power requires both CleanupAreaPower and CleanupHazardUpdate modules to function properly
- Creates a mobile cleanup zone around the target location rather than a fixed point

## Source Files

**Base Class:** [`SpecialPowerModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CleanupAreaPower.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CleanupAreaPower.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/SpecialPower/CleanupAreaPower.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/SpecialPower/CleanupAreaPower.cpp)