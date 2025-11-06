# DemoralizeSpecialPower

Special power module that demoralizes enemy infantry units in an area, with enhanced effects based on captured prisoners.

## Overview

DemoralizeSpecialPower is a special power module that demoralizes enemy infantry units within a specified range, reducing their combat effectiveness. The power's range and duration are enhanced by the number of prisoners captured by the power source. This creates a psychological warfare effect where captured enemies amplify the demoralization power.

DemoralizeSpecialPower must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that should demoralize enemy infantry units in an area, with enhanced effects based on captured prisoners. This is a **special power module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Only affects infantry units with AI
- Cannot be used when the power source is disabled
- Requires valid target location to function
- Effects are limited to the calculated range and duration
- Requires ContainModule for prisoner counting functionality

**Conditions**:
- Multiple instances behavior: Multiple DemoralizeSpecialPower modules can exist independently, each providing different demoralization effects
- Must be activated through special power system at target locations
- Range and duration scale with captured prisoner count
- Creates psychological warfare effects by weakening enemy morale

**Dependencies**:
- Requires ContainModule for prisoner counting
- Depends on the AI system for demoralization effects
- Inherits all functionality from SpecialPowerModule

## Properties

### Range Settings

#### `BaseRange` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Base range for the demoralization effect. Higher values affect more units in a larger area. This is the minimum range regardless of prisoner count
- **Default**: `0.0`
- **Example**: `BaseRange = 100.0`

#### `BonusRangePerCaptured` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Additional range added for each captured prisoner. Higher values provide more range bonus per prisoner. When set to 0 (default), prisoners don't increase range
- **Default**: `0.0`
- **Example**: `BonusRangePerCaptured = 25.0`

#### `MaxRange` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Maximum range for the demoralization effect regardless of prisoner count. Higher values allow larger maximum areas. When set to 0 (default), no range limit is applied
- **Default**: `0.0`
- **Example**: `MaxRange = 500.0`

### Duration Settings

#### `BaseDuration` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Base duration for the demoralization effect. Higher values make the effect last longer. This is the minimum duration regardless of prisoner count
- **Default**: `0`
- **Example**: `BaseDuration = 10000`

#### `BonusDurationPerCaptured` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Additional duration added for each captured prisoner. Higher values provide more duration bonus per prisoner. When set to 0 (default), prisoners don't increase duration
- **Default**: `0`
- **Example**: `BonusDurationPerCaptured = 5000`

#### `MaxDuration` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Maximum duration for the demoralization effect regardless of prisoner count. Higher values allow longer maximum effects. When set to 0 (default), no duration limit is applied
- **Default**: `0`
- **Example**: `MaxDuration = 60000`

### Visual Effects

#### `FXList` *(v1.04)*
- **Type**: `FXList` (see [FXList documentation](../FXList.md))
- **Description**: Visual effects played at the target location when the power is activated. When set, displays the specified effects. When NULL (default), no visual effects are shown
- **Default**: `NULL` (none)
- **Example**: `FXList = FX_DemoralizeEffect`

## Examples

### Basic Demoralization Power
```ini
SpecialPower = DemoralizeSpecialPower ModuleTag_01
  BaseRange = 100.0
  BonusRangePerCaptured = 25.0
  MaxRange = 300.0
  BaseDuration = 10000
  BonusDurationPerCaptured = 5000
  MaxDuration = 30000
  FXList = FX_DemoralizeEffect
End
```

### Enhanced Prisoner-Based Power
```ini
SpecialPower = DemoralizeSpecialPower ModuleTag_02
  BaseRange = 150.0
  BonusRangePerCaptured = 50.0
  MaxRange = 500.0
  BaseDuration = 15000
  BonusDurationPerCaptured = 10000
  MaxDuration = 60000
  FXList = FX_EnhancedDemoralize
End
```

## Template

```ini
SpecialPower = DemoralizeSpecialPower ModuleTag_XX
  ; Range Settings
  BaseRange = 0.0                     ; // base demoralization range *(v1.04)*
  BonusRangePerCaptured = 0.0         ; // range bonus per prisoner *(v1.04)*
  MaxRange = 0.0                      ; // maximum demoralization range *(v1.04)*
  
  ; Duration Settings
  BaseDuration = 0                    ; // base demoralization duration *(v1.04)*
  BonusDurationPerCaptured = 0        ; // duration bonus per prisoner *(v1.04)*
  MaxDuration = 0                     ; // maximum demoralization duration *(v1.04)*
  
  ; Visual Effects
  FXList =                            ; // demoralization visual effects *(v1.04)*
End
```

## Notes

- DemoralizeSpecialPower affects enemy infantry units within the calculated range
- Range and duration scale with the number of captured prisoners
- Only affects units with AI (infantry units)
- Creates psychological warfare effects by demoralizing enemy forces
- Visual effects are played at the target location
- The power encourages capturing prisoners to enhance effectiveness
- Commonly used by special units or generals with psychological warfare capabilities
- Demoralized units have reduced combat effectiveness

## Source Files

**Base Class:** [`SpecialPowerModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DemoralizeSpecialPower.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DemoralizeSpecialPower.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/SpecialPower/DemoralizeSpecialPower.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/SpecialPower/DemoralizeSpecialPower.cpp)