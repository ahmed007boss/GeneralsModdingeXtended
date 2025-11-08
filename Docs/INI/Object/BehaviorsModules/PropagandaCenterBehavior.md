# PropagandaCenterBehavior

Behavior module that extends prison functionality to include brainwashing capabilities for converting captured enemy units to allied units.

## Overview

PropagandaCenterBehavior is a behavior module that extends prison functionality to include brainwashing capabilities. It manages the conversion of captured enemy units into allied units through a time-based brainwashing process. The module tracks brainwashing progress and maintains a list of successfully brainwashed units. This creates a specialized facility that can convert enemy units to serve the controlling player's faction.

PropagandaCenterBehavior must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by structures that should function as propaganda centers with brainwashing capabilities for converting captured enemy units to allied units. This is a **behavior module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Only works with surrendered units
- Cannot function without the ALLOW_SURRENDER compilation flag
- Requires proper bone structure for prison yard positioning
- Requires proper surrender system integration

**Conditions**:
- Multiple instances behavior: Multiple PropagandaCenterBehavior modules can exist independently, each managing different brainwashing systems
- Always active once assigned to an object
- Manages prisoner containment and brainwashing conversion
- Creates tactical advantages through enemy unit conversion

**Dependencies**:
- Requires bone structure for prison yard positioning
- Depends on the surrender system for unit state management
- Inherits all functionality from PrisonBehavior

## Properties

### Brainwashing Configuration

#### `BrainwashDuration` *(v1.04)*
- **Type**: `UnsignedInt` (frames)
- **Description**: Duration in frames required to complete the brainwashing process. Higher values make brainwashing take longer. When set to 0 (default), no brainwashing duration is applied
- **Default**: `0`
- **Example**: `BrainwashDuration = 600`

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

### Basic Propaganda Center
```ini
Behavior = PropagandaCenterBehavior ModuleTag_01
  BrainwashDuration = 300
  ShowPrisoners = Yes
  PrisonYardBonePrefix = PrisonYard
End
```

### Quick Brainwashing Center
```ini
Behavior = PropagandaCenterBehavior ModuleTag_02
  BrainwashDuration = 180
  ShowPrisoners = No
End
```

### Slow Brainwashing Center
```ini
Behavior = PropagandaCenterBehavior ModuleTag_03
  BrainwashDuration = 900
  ShowPrisoners = Yes
  PrisonYardBonePrefix = PropagandaYard
End
```

## Template

```ini
Behavior = PropagandaCenterBehavior ModuleTag_XX
  ; Brainwashing Configuration
  BrainwashDuration = 0               ; // frames required for brainwashing completion *(v1.04)*
  
  ; Visual Configuration
  ShowPrisoners = No                  ; // display prisoners in prison yard *(v1.04)*
  PrisonYardBonePrefix =              ; // bone prefix for prison yard positioning *(v1.04)*
End
```

## Notes

- PropagandaCenterBehavior extends prison functionality with brainwashing capabilities
- Converts captured enemy units into allied units through time-based processing
- Tracks brainwashing progress and maintains lists of converted units
- Commonly used for propaganda centers and conversion facilities
- The module extends PrisonBehavior functionality for brainwashing-specific behavior
- Creates tactical advantages through enemy unit conversion

## Source Files

**Base Class:** [`PrisonBehavior`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/PrisonBehavior.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/PropagandaCenterBehavior.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/PropagandaCenterBehavior.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/PropagandaCenterBehavior.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/PropagandaCenterBehavior.cpp)