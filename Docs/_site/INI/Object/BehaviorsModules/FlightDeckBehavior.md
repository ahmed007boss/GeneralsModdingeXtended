# FlightDeckBehavior

Complex behavior module that manages aircraft carrier flight deck operations including aircraft parking, takeoff, landing, and runway management.

## Overview

FlightDeckBehavior is a sophisticated behavior module that handles all aspects of aircraft carrier operations including aircraft parking, takeoff and landing sequences, runway management, and aircraft healing. It manages multiple runways, parking spaces, taxi routes, and coordinates complex aircraft movements with proper timing and sequencing. This module is essential for creating realistic aircraft carrier gameplay.

FlightDeckBehavior must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that should function as aircraft carriers with parking spaces, runways, and aircraft management capabilities. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Complex module with many interdependent properties
- Requires proper bone setup in 3D models for runways and parking spaces
- Limited to maximum 2 runways (MAX_RUNWAYS constant)
- Requires aircraft with compatible AI systems
- Cannot function without proper aircraft production system

**Conditions**:
- Multiple instances behavior: Multiple FlightDeckBehavior modules cannot exist - only one per object
- Always active once assigned to an object
- Requires proper aircraft templates and bone configurations
- Manages parking spaces, runways, and aircraft healing automatically

**Dependencies**:
- Requires compatible aircraft with JetAIUpdate or similar AI systems
- Depends on proper 3D model bone setup for runways and parking spaces
- Inherits all functionality from UpdateModule

## Properties

### Runway Configuration

#### `NumRunways` *(v1.04)*
- **Type**: `Int`
- **Description**: Number of runways on the aircraft carrier. Higher values provide more simultaneous takeoff/landing capacity. Maximum is 2 runways (MAX_RUNWAYS constant)
- **Default**: `0`
- **Example**: `NumRunways = 2`

#### `NumSpacesPerRunway` *(v1.04)*
- **Type**: `Int`
- **Description**: Number of parking spaces per runway. Higher values allow more aircraft to be parked simultaneously. Each space must have corresponding bone names defined
- **Default**: `0`
- **Example**: `NumSpacesPerRunway = 6`

### Runway 1 Configuration

#### `Runway1Spaces` *(v1.04)*
- **Type**: `AsciiStringVector` (multiple entries)
- **Description**: List of bone names for parking spaces on runway 1. Each entry corresponds to a parking space where aircraft can be stationed
- **Default**: `None`
- **Example**: 
```
Runway1Spaces = Runway1Space1
Runway1Spaces = Runway1Space2
Runway1Spaces = Runway1Space3
```

#### `Runway1Takeoff` *(v1.04)*
- **Type**: `runwayStrip` (two bone names)
- **Description**: Start and end bone names for runway 1 takeoff sequence. First bone is takeoff start, second bone is takeoff end
- **Default**: `None`
- **Example**: `Runway1Takeoff = Runway1Start Runway1End`

#### `Runway1Landing` *(v1.04)*
- **Type**: `runwayStrip` (two bone names)
- **Description**: Start and end bone names for runway 1 landing sequence. First bone is landing start, second bone is landing end
- **Default**: `None`
- **Example**: `Runway1Landing = Runway1LandStart Runway1LandEnd`

#### `Runway1Taxi` *(v1.04)*
- **Type**: `AsciiStringVector` (multiple entries)
- **Description**: List of bone names for taxi routes on runway 1. Aircraft use these bones to navigate between parking spaces and runways
- **Default**: `None`
- **Example**: 
```
Runway1Taxi = Runway1Taxi1
Runway1Taxi = Runway1Taxi2
Runway1Taxi = Runway1Taxi3
```

#### `Runway1Creation` *(v1.04)*
- **Type**: `AsciiStringVector` (multiple entries)
- **Description**: List of bone names for aircraft creation points on runway 1. New aircraft spawn at these locations
- **Default**: `None`
- **Example**: 
```
Runway1Creation = Runway1Create1
Runway1Creation = Runway1Create2
```

#### `Runway1CatapultSystem` *(v1.04)*
- **Type**: `ParticleSystemTemplate`
- **Description**: Particle system template for catapult launch effects on runway 1. When set, displays catapult effects during aircraft launches
- **Default**: `NULL` (none)
- **Example**: `Runway1CatapultSystem = PS_CatapultLaunch`

### Runway 2 Configuration

#### `Runway2Spaces` *(v1.04)*
- **Type**: `AsciiStringVector` (multiple entries)
- **Description**: List of bone names for parking spaces on runway 2. Each entry corresponds to a parking space where aircraft can be stationed
- **Default**: `None`
- **Example**: 
```
Runway2Spaces = Runway2Space1
Runway2Spaces = Runway2Space2
Runway2Spaces = Runway2Space3
```

#### `Runway2Takeoff` *(v1.04)*
- **Type**: `runwayStrip` (two bone names)
- **Description**: Start and end bone names for runway 2 takeoff sequence. First bone is takeoff start, second bone is takeoff end
- **Default**: `None`
- **Example**: `Runway2Takeoff = Runway2Start Runway2End`

#### `Runway2Landing` *(v1.04)*
- **Type**: `runwayStrip` (two bone names)
- **Description**: Start and end bone names for runway 2 landing sequence. First bone is landing start, second bone is landing end
- **Default**: `None`
- **Example**: `Runway2Landing = Runway2LandStart Runway2LandEnd`

#### `Runway2Taxi` *(v1.04)*
- **Type**: `AsciiStringVector` (multiple entries)
- **Description**: List of bone names for taxi routes on runway 2. Aircraft use these bones to navigate between parking spaces and runways
- **Default**: `None`
- **Example**: 
```
Runway2Taxi = Runway2Taxi1
Runway2Taxi = Runway2Taxi2
Runway2Taxi = Runway2Taxi3
```

#### `Runway2Creation` *(v1.04)*
- **Type**: `AsciiStringVector` (multiple entries)
- **Description**: List of bone names for aircraft creation points on runway 2. New aircraft spawn at these locations
- **Default**: `None`
- **Example**: 
```
Runway2Creation = Runway2Create1
Runway2Creation = Runway2Create2
```

#### `Runway2CatapultSystem` *(v1.04)*
- **Type**: `ParticleSystemTemplate`
- **Description**: Particle system template for catapult launch effects on runway 2. When set, displays catapult effects during aircraft launches
- **Default**: `NULL` (none)
- **Example**: `Runway2CatapultSystem = PS_CatapultLaunch`

### Flight Operations

#### `ApproachHeight` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Height above the carrier for aircraft approach and landing. Higher values create more dramatic landing approaches. When set to 0 (default), aircraft approach at ground level
- **Default**: `0.0`
- **Example**: `ApproachHeight = 50.0`

#### `LandingDeckHeightOffset` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Height offset for the landing deck relative to the carrier's base position. Higher values raise the landing deck. When set to 0 (default), landing deck is at base level
- **Default**: `0.0`
- **Example**: `LandingDeckHeightOffset = 10.0`

#### `HealAmountPerSecond` *(v1.04)*
- **Type**: `Real` (health per second)
- **Description**: Amount of health restored per second to parked aircraft. Higher values heal aircraft faster. When set to 0 (default), no healing occurs
- **Default**: `0.0`
- **Example**: `HealAmountPerSecond = 10.0`

### Timing and Delays

#### `ParkingCleanupPeriod` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time interval between parking space cleanup operations. Higher values reduce cleanup frequency. When set to 0 (default), cleanup occurs every frame
- **Default**: `0`
- **Example**: `ParkingCleanupPeriod = 1000`

#### `HumanFollowPeriod` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time interval for human player command following. Higher values reduce command update frequency. When set to 0 (default), commands are followed immediately
- **Default**: `0`
- **Example**: `HumanFollowPeriod = 500`

#### `ReplacementDelay` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Delay before replacing destroyed aircraft. Higher values make replacements take longer. When set to 0 (default), replacements are immediate
- **Default**: `0`
- **Example**: `ReplacementDelay = 5000`

#### `DockAnimationDelay` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Duration of docking animation when aircraft land. Higher values make docking animations longer. When set to 0 (default), no docking animation
- **Default**: `0`
- **Example**: `DockAnimationDelay = 2000`

#### `LaunchWaveDelay` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Delay between aircraft launch waves. Higher values space out launches more. When set to 0 (default), launches are immediate
- **Default**: `0`
- **Example**: `LaunchWaveDelay = 1000`

#### `LaunchRampDelay` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Delay before raising launch ramp. Higher values delay ramp raising. When set to 0 (default), ramp raises immediately
- **Default**: `0`
- **Example**: `LaunchRampDelay = 500`

#### `LowerRampDelay` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Delay before lowering launch ramp after takeoff. Higher values delay ramp lowering. When set to 0 (default), ramp lowers immediately
- **Default**: `0`
- **Example**: `LowerRampDelay = 1000`

#### `CatapultFireDelay` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Delay before firing catapult system. Higher values delay catapult activation. When set to 0 (default), catapult fires immediately
- **Default**: `0`
- **Example**: `CatapultFireDelay = 750`

### Aircraft Configuration

#### `PayloadTemplate` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Name of the aircraft template that this carrier can launch. When set, defines what type of aircraft the carrier operates
- **Default**: `""` (empty)
- **Example**: `PayloadTemplate = AircraftFighter`

## Examples

### Basic Aircraft Carrier
```ini
Behavior = FlightDeckBehavior ModuleTag_01
  NumRunways = 1
  NumSpacesPerRunway = 4
  
  Runway1Spaces = Runway1Space1
  Runway1Spaces = Runway1Space2
  Runway1Spaces = Runway1Space3
  Runway1Spaces = Runway1Space4
  
  Runway1Takeoff = Runway1Start Runway1End
  Runway1Landing = Runway1LandStart Runway1LandEnd
  
  Runway1Taxi = Runway1Taxi1
  Runway1Taxi = Runway1Taxi2
  
  Runway1Creation = Runway1Create1
  Runway1Creation = Runway1Create2
  
  ApproachHeight = 50.0
  LandingDeckHeightOffset = 10.0
  HealAmountPerSecond = 10.0
  
  PayloadTemplate = AircraftFighter
End
```

### Advanced Dual-Runway Carrier
```ini
Behavior = FlightDeckBehavior ModuleTag_02
  NumRunways = 2
  NumSpacesPerRunway = 6
  
  ; Runway 1 Configuration
  Runway1Spaces = Runway1Space1
  Runway1Spaces = Runway1Space2
  Runway1Spaces = Runway1Space3
  Runway1Spaces = Runway1Space4
  Runway1Spaces = Runway1Space5
  Runway1Spaces = Runway1Space6
  
  Runway1Takeoff = Runway1Start Runway1End
  Runway1Landing = Runway1LandStart Runway1LandEnd
  Runway1Taxi = Runway1Taxi1
  Runway1Taxi = Runway1Taxi2
  Runway1Taxi = Runway1Taxi3
  Runway1Creation = Runway1Create1
  Runway1Creation = Runway1Create2
  Runway1CatapultSystem = PS_CatapultLaunch
  
  ; Runway 2 Configuration
  Runway2Spaces = Runway2Space1
  Runway2Spaces = Runway2Space2
  Runway2Spaces = Runway2Space3
  Runway2Spaces = Runway2Space4
  Runway2Spaces = Runway2Space5
  Runway2Spaces = Runway2Space6
  
  Runway2Takeoff = Runway2Start Runway2End
  Runway2Landing = Runway2LandStart Runway2LandEnd
  Runway2Taxi = Runway2Taxi1
  Runway2Taxi = Runway2Taxi2
  Runway2Taxi = Runway2Taxi3
  Runway2Creation = Runway2Create1
  Runway2Creation = Runway2Create2
  Runway2CatapultSystem = PS_CatapultLaunch
  
  ApproachHeight = 75.0
  LandingDeckHeightOffset = 15.0
  HealAmountPerSecond = 15.0
  
  ParkingCleanupPeriod = 1000
  HumanFollowPeriod = 500
  ReplacementDelay = 5000
  DockAnimationDelay = 2000
  LaunchWaveDelay = 1000
  LaunchRampDelay = 500
  LowerRampDelay = 1000
  CatapultFireDelay = 750
  
  PayloadTemplate = AircraftFighter
End
```

## Template

```ini
Behavior = FlightDeckBehavior ModuleTag_XX
  ; Runway Configuration
  NumRunways = 0                       ; // number of runways *(v1.04)*
  NumSpacesPerRunway = 0               ; // parking spaces per runway *(v1.04)*
  
  ; Runway 1 Configuration
  Runway1Spaces =                      ; // runway 1 parking space bones *(v1.04)*
  Runway1Takeoff =                     ; // runway 1 takeoff bones *(v1.04)*
  Runway1Landing =                     ; // runway 1 landing bones *(v1.04)*
  Runway1Taxi =                        ; // runway 1 taxi route bones *(v1.04)*
  Runway1Creation =                    ; // runway 1 creation point bones *(v1.04)*
  Runway1CatapultSystem =              ; // runway 1 catapult effects *(v1.04)*
  
  ; Runway 2 Configuration
  Runway2Spaces =                      ; // runway 2 parking space bones *(v1.04)*
  Runway2Takeoff =                     ; // runway 2 takeoff bones *(v1.04)*
  Runway2Landing =                     ; // runway 2 landing bones *(v1.04)*
  Runway2Taxi =                        ; // runway 2 taxi route bones *(v1.04)*
  Runway2Creation =                    ; // runway 2 creation point bones *(v1.04)*
  Runway2CatapultSystem =              ; // runway 2 catapult effects *(v1.04)*
  
  ; Flight Operations
  ApproachHeight = 0.0                 ; // aircraft approach height *(v1.04)*
  LandingDeckHeightOffset = 0.0        ; // landing deck height offset *(v1.04)*
  HealAmountPerSecond = 0.0            ; // healing rate for parked aircraft *(v1.04)*
  
  ; Timing and Delays
  ParkingCleanupPeriod = 0             ; // parking cleanup interval *(v1.04)*
  HumanFollowPeriod = 0                ; // human command follow interval *(v1.04)*
  ReplacementDelay = 0                 ; // aircraft replacement delay *(v1.04)*
  DockAnimationDelay = 0               ; // docking animation duration *(v1.04)*
  LaunchWaveDelay = 0                  ; // launch wave interval *(v1.04)*
  LaunchRampDelay = 0                  ; // launch ramp raise delay *(v1.04)*
  LowerRampDelay = 0                   ; // launch ramp lower delay *(v1.04)*
  CatapultFireDelay = 0                ; // catapult fire delay *(v1.04)*
  
  ; Aircraft Configuration
  PayloadTemplate =                    ; // aircraft template to launch *(v1.04)*
End
```

## Notes

- FlightDeckBehavior manages complex aircraft carrier operations including parking, takeoff, landing, and runway management
- Requires proper 3D model setup with bone names for runways, parking spaces, taxi routes, and creation points
- Limited to maximum 2 runways (MAX_RUNWAYS constant)
- Manages aircraft healing, replacement, and complex movement sequences
- Includes catapult launch effects and ramp animations
- Coordinates multiple aircraft movements with proper timing and sequencing
- Essential for creating realistic aircraft carrier gameplay with proper flight deck operations

## Source Files

**Base Class:** [`AIUpdateInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FlightDeckBehavior.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FlightDeckBehavior.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/FlightDeckBehavior.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/FlightDeckBehavior.cpp)
