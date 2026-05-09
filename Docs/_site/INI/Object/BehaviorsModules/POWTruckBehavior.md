# POWTruckBehavior

Behavior module that manages POW (Prisoner of War) truck functionality for collecting and transporting surrendered units.

## Overview

POWTruckBehavior is a behavior module that enables vehicles to function as POW trucks, capable of collecting and transporting surrendered units. It extends the OpenContain functionality to specifically handle surrendered units through collision detection. When the truck collides with a surrendered unit, it automatically loads the prisoner into the vehicle. This creates a specialized transport system for managing captured enemy units.

POWTruckBehavior must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by vehicles that should function as POW (Prisoner of War) trucks for collecting and transporting surrendered units. This is a **behavior module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Only works with surrendered units
- Requires POWTruckAIUpdateInterface for proper functionality
- Cannot function without the ALLOW_SURRENDER compilation flag
- Requires proper surrender system integration

**Conditions**:
- Multiple instances behavior: Multiple POWTruckBehavior modules can exist independently, each managing different POW truck systems
- Always active once assigned to an object
- Activates when colliding with surrendered units
- Creates tactical advantages through prisoner collection and transport

**Dependencies**:
- Requires POWTruckAIUpdateInterface for prisoner loading
- Depends on the surrender system for unit state management
- Inherits all functionality from OpenContain

## Properties

This module does not expose any additional INI-parsable properties beyond those inherited from OpenContainModuleData.

## Examples

### Basic POW Truck
```ini
Behavior = POWTruckBehavior ModuleTag_01
End
```

### Advanced POW Truck
```ini
Behavior = POWTruckBehavior ModuleTag_02
End
```

## Template

```ini
Behavior = POWTruckBehavior ModuleTag_XX
  ; No additional properties - inherits from OpenContain
End
```

## Notes

- POWTruckBehavior manages POW truck functionality for collecting surrendered units
- Automatically loads surrendered units when the truck collides with them
- Requires POWTruckAIUpdateInterface for proper prisoner management
- Commonly used for specialized transport vehicles that handle captured units
- The module extends OpenContain functionality for POW-specific behavior
- Creates tactical advantages through prisoner collection and transport

## Source Files

**Base Class:** [`OpenContain`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/OpenContain.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/POWTruckBehavior.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/POWTruckBehavior.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/POWTruckBehavior.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/POWTruckBehavior.cpp)