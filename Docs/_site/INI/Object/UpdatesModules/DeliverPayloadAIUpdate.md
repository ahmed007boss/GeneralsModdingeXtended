# DeliverPayloadAIUpdate

AI update module that provides AI functionality for payload delivery systems with configurable door delays, drop attempts, and drop offsets.

## Overview

DeliverPayloadAIUpdate is an AI update module that provides AI functionality for payload delivery systems. It handles AI-driven navigation to target locations, payload deployment operations, and delivery coordination. The module manages door opening delays, maximum delivery attempts, and drop positioning offsets for precise payload placement.

DeliverPayloadAIUpdate must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that need to deliver payloads to specific locations with AI-driven navigation. This is an **AI update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Designed specifically for payload delivery systems
- Requires proper AI and payload systems for functionality
- Cannot function without proper update and AI systems
- Delivery operations are limited by aircraft capacity and navigation

**Conditions**:
- Multiple instances behavior: Multiple DeliverPayloadAIUpdate modules can exist independently, each managing different payload delivery systems
- Always active once assigned to an object
- Continuously manages AI-driven payload delivery operations
- Creates specialized AI behaviors for payload delivery aircraft

**Dependencies**:
- Depends on the AI system for navigation and delivery decisions
- Requires proper payload system for delivery operations
- Inherits functionality from AIUpdateInterface

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Delivery Configuration](#delivery-configuration)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

### Delivery Configuration

#### `DoorDelay` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time delay for door opening operations during payload delivery. Higher values create slower door operations. Lower values create faster door operations. At 500 (default), doors take 500 milliseconds to open
- **Default**: `500`
- **Example**: `DoorDelay = 500`

#### `MaxAttempts` *(v1.04)*
- **Type**: `UnsignedInt`
- **Description**: Maximum number of delivery attempts before giving up. Higher values allow more retry attempts for difficult deliveries. Lower values limit retry attempts. At 4 (default), allows up to 4 delivery attempts
- **Default**: `4`
- **Example**: `MaxAttempts = 4`

#### `DropOffset` *(v1.04)*
- **Type**: `Coord3D` (coordinate)
- **Description**: Offset coordinates for payload drop positioning relative to target location. When set, adjusts drop position by the specified offset. When zero (default), drops directly at target location
- **Default**: `X:0 Y:0 Z:0`
- **Example**: `DropOffset = X:0 Y:0 Z:-10`

## Examples

### Basic Payload Delivery
```ini
Behavior = DeliverPayloadAIUpdate ModuleTag_08
  DoorDelay = 500
  MaxAttempts = 4
  DropOffset = X:0 Y:0 Z:-10
End
```

### Fast Payload Delivery
```ini
Behavior = DeliverPayloadAIUpdate ModuleTag_05
  DoorDelay = 250
  MaxAttempts = 4
  DropOffset = X:0 Y:0 Z:-10
End
```

### Persistent Payload Delivery
```ini
Behavior = DeliverPayloadAIUpdate ModuleTag_05
  DoorDelay = 500
  MaxAttempts = 8
  DropOffset = X:0 Y:0 Z:-10
End
```

## Template

```ini
Behavior = DeliverPayloadAIUpdate ModuleTag_XX
  ; Delivery Configuration
  DoorDelay = 500                        ; // milliseconds for door opening *(v1.04)*
  MaxAttempts = 4                        ; // maximum delivery attempts *(v1.04)*
  DropOffset = X:0 Y:0 Z:0               ; // coordinates offset for drop positioning *(v1.04)*
End
```

## Notes

- DeliverPayloadAIUpdate provides specialized AI behaviors for payload delivery aircraft
- The module manages door operations, delivery attempts, and drop positioning
- Configurable parameters allow for flexible payload delivery mechanics
- This creates realistic payload delivery operations with proper timing and positioning

## Source Files

**Base Class:** [`AIUpdateInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DeliverPayloadAIUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DeliverPayloadAIUpdate.cpp)
