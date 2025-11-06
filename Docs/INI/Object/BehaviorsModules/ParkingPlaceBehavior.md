# ParkingPlaceBehavior

Update module that manages aircraft parking spaces, runways, and healing for aircraft carriers and airfields with configurable layouts.

## Overview

ParkingPlaceBehavior is a complex update module that manages aircraft parking systems for aircraft carriers and airfields. It handles parking space allocation, runway management, aircraft healing, and exit coordination. The module supports configurable grid layouts, runway systems, and healing mechanics for parked aircraft. This creates realistic aircraft carrier and airfield operations with proper space management.

ParkingPlaceBehavior must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that should function as aircraft carriers or airfields with parking spaces, runways, and aircraft management capabilities. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Requires objects with production capabilities for proper integration
- Limited to configured parking space counts
- Cannot function without proper bone structure for parking positions
- Requires proper aircraft AI systems for carrier operations

**Conditions**:
- Multiple instances behavior: Multiple ParkingPlaceBehavior modules can exist independently, each managing different parking systems
- Always active once assigned to an object
- Continuously manages parking spaces and aircraft healing
- Creates realistic aircraft carrier and airfield operations with proper space management

**Dependencies**:
- Requires objects with production capabilities
- Depends on bone structure for parking position calculations
- Inherits functionality from UpdateModule, DieModuleInterface, and ExitInterface

## Properties

### Parking Layout

#### `NumRows` *(v1.04)*
- **Type**: `Int`
- **Description**: Number of rows in the parking grid layout. Higher values create more parking spaces. When set to 0 (default), no parking rows are available
- **Default**: `0`
- **Example**: `NumRows = 3`

#### `NumCols` *(v1.04)*
- **Type**: `Int`
- **Description**: Number of columns in the parking grid layout. Higher values create more parking spaces. When set to 0 (default), no parking columns are available
- **Default**: `0`
- **Example**: `NumCols = 4`

### Aircraft Handling

#### `ApproachHeight` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Height at which aircraft approach the parking area. Higher values make aircraft approach from greater heights. When set to 0 (default), no specific approach height is used
- **Default**: `0.0`
- **Example**: `ApproachHeight = 50.0`

#### `LandingDeckHeightOffset` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Height offset for the landing deck surface. Higher values raise the landing deck. When set to 0 (default), no height offset is applied
- **Default**: `0.0`
- **Example**: `LandingDeckHeightOffset = 10.0`

### Runway Configuration

#### `HasRunways` *(v1.04)*
- **Type**: `Bool`
- **Description**: Determines if each column has a runway in front of it. When `Yes`, runways are available for each column. When `No` (default), no runways are available
- **Default**: `No`
- **Example**: `HasRunways = Yes`

### Parking Behavior

#### `ParkInHangars` *(v1.04)*
- **Type**: `Bool`
- **Description**: Determines if aircraft park at hangar production spots instead of real parking places. When `Yes`, aircraft park in hangars. When `No` (default), aircraft park in designated parking spaces
- **Default**: `No`
- **Example**: `ParkInHangars = Yes`

### Healing System

#### `HealAmountPerSecond` *(v1.04)*
- **Type**: `Real` (health per second)
- **Description**: Amount of health restored per second to parked aircraft. Higher values heal aircraft faster. When set to 0 (default), no healing occurs
- **Default**: `0.0`
- **Example**: `HealAmountPerSecond = 10.0`

## Examples

### Basic Aircraft Carrier
```ini
Update = ParkingPlaceBehavior ModuleTag_01
  NumRows = 2
  NumCols = 3
  ApproachHeight = 75.0
  LandingDeckHeightOffset = 15.0
  HasRunways = Yes
  ParkInHangars = No
  HealAmountPerSecond = 5.0
End
```

### Large Airfield
```ini
Update = ParkingPlaceBehavior ModuleTag_02
  NumRows = 4
  NumCols = 6
  ApproachHeight = 100.0
  LandingDeckHeightOffset = 0.0
  HasRunways = Yes
  ParkInHangars = No
  HealAmountPerSecond = 15.0
End
```

### Hangar-Based Parking
```ini
Update = ParkingPlaceBehavior ModuleTag_03
  NumRows = 1
  NumCols = 2
  ApproachHeight = 50.0
  LandingDeckHeightOffset = 5.0
  HasRunways = No
  ParkInHangars = Yes
  HealAmountPerSecond = 8.0
End
```

## Template

```ini
Update = ParkingPlaceBehavior ModuleTag_XX
  ; Parking Layout
  NumRows = 0                        ; // number of parking rows *(v1.04)*
  NumCols = 0                        ; // number of parking columns *(v1.04)*
  
  ; Aircraft Handling
  ApproachHeight = 0.0               ; // aircraft approach height *(v1.04)*
  LandingDeckHeightOffset = 0.0      ; // landing deck height offset *(v1.04)*
  
  ; Runway Configuration
  HasRunways = No                    ; // enable runways for each column *(v1.04)*
  
  ; Parking Behavior
  ParkInHangars = No                 ; // park aircraft in hangars *(v1.04)*
  
  ; Healing System
  HealAmountPerSecond = 0.0          ; // health restored per second *(v1.04)*
End
```

## Notes

- ParkingPlaceBehavior manages comprehensive aircraft parking systems for carriers and airfields
- Supports configurable grid layouts with rows and columns
- Includes runway management and aircraft healing capabilities
- Commonly used for aircraft carriers, airfields, and aviation facilities
- The module handles parking space allocation, runway reservations, and exit coordination
- Creates realistic aircraft carrier and airfield operations with proper space management

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ParkingPlaceBehavior.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ParkingPlaceBehavior.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/ParkingPlaceBehavior.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/ParkingPlaceBehavior.cpp)