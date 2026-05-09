# PrisonBehavior

Behavior module that manages prison functionality for containing and displaying surrendered units with visual representation in prison yards.

## Overview

PrisonBehavior is a behavior module that enables structures to function as prisons for containing surrendered units. It extends the OpenContain functionality to specifically handle prisoner management with visual representation. When units are contained in the prison, they can be displayed in designated prison yard areas with configurable visual positioning. This creates a specialized containment system for managing captured enemy units with visual feedback.

PrisonBehavior must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by structures that should function as prisons for containing and displaying surrendered units with visual representation in prison yards. This is a **behavior module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Only works with surrendered units
- Cannot function without the ALLOW_SURRENDER compilation flag
- Requires proper bone structure for prison yard positioning
- Requires proper surrender system integration

**Conditions**:
- Multiple instances behavior: Multiple PrisonBehavior modules can exist independently, each managing different prison systems
- Always active once assigned to an object
- Manages prisoner containment and visual representation
- Creates tactical advantages through prisoner containment and visual management

**Dependencies**:
- Requires bone structure for prison yard positioning
- Depends on the surrender system for unit state management
- Inherits all functionality from OpenContain

## Properties

### Visual Configuration

#### `ShowPrisoners` *(v1.04)*
- **Type**: `Bool`
- **Description**: Determines if contained prisoners are visually displayed in the prison yard. When `Yes`, prisoners are shown in the prison yard. When `No` (default), prisoners are not visually displayed
- **Default**: `No`
- **Example**: `ShowPrisoners = Yes`

#### `PrisonYardBonePrefix` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Bone prefix that identifies bones making up the prison yards for prisoner positioning. When set, prisoners are positioned at bones with this prefix. When empty (default), no specific bone prefix is used
- **Default**: `""` (empty)
- **Example**: `PrisonYardBonePrefix = PrisonYard`

## Examples

### Basic Prison
```ini
Behavior = PrisonBehavior ModuleTag_01
  ShowPrisoners = Yes
  PrisonYardBonePrefix = PrisonYard
End
```

### Hidden Prison
```ini
Behavior = PrisonBehavior ModuleTag_02
  ShowPrisoners = No
End
```

### Custom Prison Yard
```ini
Behavior = PrisonBehavior ModuleTag_03
  ShowPrisoners = Yes
  PrisonYardBonePrefix = CustomYard
End
```

## Template

```ini
Behavior = PrisonBehavior ModuleTag_XX
  ; Visual Configuration
  ShowPrisoners = No                  ; // display prisoners in prison yard *(v1.04)*
  PrisonYardBonePrefix =              ; // bone prefix for prison yard positioning *(v1.04)*
End
```

## Notes

- PrisonBehavior manages prison functionality for containing surrendered units
- Supports visual representation of prisoners in designated prison yard areas
- Includes configurable bone-based positioning for prisoner display
- Commonly used for prison buildings and containment facilities
- The module extends OpenContain functionality for prison-specific behavior
- Creates tactical advantages through prisoner containment and visual management

## Source Files

**Base Class:** [`OpenContain`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/OpenContain.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/PrisonBehavior.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/PrisonBehavior.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/PrisonBehavior.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/PrisonBehavior.cpp)