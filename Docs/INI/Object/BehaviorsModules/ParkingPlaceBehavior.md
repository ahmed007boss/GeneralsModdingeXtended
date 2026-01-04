# ParkingPlaceBehavior

Status: AI-generated, 0/2 reviews

## Overview

The `ParkingPlaceBehavior` module manages aircraft parking systems for aircraft carriers and airfields. It handles parking space allocation, runway management, aircraft healing, and exit coordination. The module supports configurable grid layouts with rows and columns, runway systems, healing mechanics for parked aircraft, and optional inventory item replenishment and component restoration. This creates realistic aircraft carrier and airfield operations with proper space management and maintenance capabilities.

Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
  - [Limitations](#limitations)
  - [Conditions](#conditions)
  - [Dependencies](#dependencies)
- [Properties](#properties)
  - [Parking Layout](#parking-layout)
  - [Aircraft Handling](#aircraft-handling)
  - [Runway Configuration](#runway-configuration)
  - [Parking Behavior](#parking-behavior)
  - [Healing System](#healing-system)
  - [Restoration System](#restoration-system) *(GMX Generals, GMX Zero Hour only)*
- [Enum Value Lists](#enum-value-lists)
  - [ValueType Values](#valuetype-values)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Document Log](#document-log)
- [Status](#status)
- [Reviewers](#reviewers)

## Usage

Place under `Update = ParkingPlaceBehavior ModuleTag_XX` inside [Object](../Object.md) entries. ParkingPlaceBehavior can only be added to [Object](../Object.md) entries in Retail (ObjectExtend does not exist in Retail). See [Template](#template) for correct syntax.

Multiple ParkingPlaceBehavior modules can exist independently on the same object, each managing different parking systems. Each instance operates independently with its own parking layout, runways, and healing settings.

**Limitations**:
- Requires objects with production capabilities for proper integration. ParkingPlaceBehavior interfaces with [ProductionUpdate](../ObjectModules/ProductionUpdate.md) systems to manage door states and exit coordination.
- Limited to configured parking space counts. The total number of parking spaces is determined by [NumRows](#numrows) multiplied by [NumCols](#numcols). If more aircraft attempt to park than spaces are available, the module cannot accommodate them.
- Cannot function without proper bone structure for parking positions. The module requires specific bone names in the object's model:
  - For each parking space: `Runway%dPark%dHan` (hangar start), `Runway%dParking%d` (parking location), `Runway%dPrep%d` (preparation point) where `%d` represents column and row numbers
  - For runways (if [HasRunways](#hasrunways) is `Yes`): `RunwayStart%d` and `RunwayEnd%d` for each column
  - For helipad functionality: `HeliPark01` bone
  - If required bones are missing, parking positions may be incorrectly placed or the module may not function properly.
- Requires proper aircraft AI systems for carrier operations. Aircraft must use [JetAIUpdate](../ObjectModules/JetAIUpdate.md) for proper runway and parking coordination.
- Healing only affects parked aircraft. Aircraft must be parked in a parking space to receive healing from [HealAmountPerSecond](#healamountpersecond).
- Inventory item replenishment and component restoration only work on vehicles that have [InventoryBehavior](../ObjectBehaviorsModules/InventoryBehavior.md) and [Component](../ObjectBody/Component.md) systems respectively. If vehicles do not have these systems, restoration is silently skipped.

**Conditions**:
- Objects with ParkingPlaceBehavior can be targeted by aircraft for landing and parking. The module manages parking space reservations, runway allocations, and exit coordination.
- ParkingPlaceBehavior integrates with [ProductionUpdate](../ObjectModules/ProductionUpdate.md) systems to manage door states and coordinate unit exits. Doors are automatically opened when spaces are reserved and closed when spaces are released.
- Aircraft with [JetAIUpdate](../ObjectModules/JetAIUpdate.md) coordinate with ParkingPlaceBehavior to reserve runways and parking spaces. The module provides runway reservation queuing for takeoff operations.
- Healing occurs automatically at regular intervals (every 0.2 seconds) for all parked aircraft. The healing amount per tick is calculated based on [HealAmountPerSecond](#healamountpersecond) and the time interval.
- Inventory item replenishment occurs once per second for parked vehicles that have the required systems (GMX only), using the [RepublishAmount](#republishamount) and [RepublishAmountValueType](#republishamountvaluetype) settings. Component restoration occurs during each healing tick. Invalid item names or component names are silently ignored - vehicles without [InventoryBehavior](../ObjectBehaviorsModules/InventoryBehavior.md) or missing components are skipped.
- Helipad aircraft (with `KINDOF_PRODUCED_AT_HELIPAD`) use special handling and do not require parking space reservations. They use the `HeliPark01` bone position instead.
- Runway reservations are managed per column. If [HasRunways](#hasrunways) is `Yes`, each column has its own runway that can be reserved for landing or takeoff. Aircraft queue for runway access when runways are busy.
- Parking space allocation uses a grid system based on [NumRows](#numrows) and [NumCols](#numcols). Each space is assigned to a specific runway (column) and can be reserved for parking or exit coordination.
- When the object with ParkingPlaceBehavior is destroyed, all parked aircraft are automatically killed via the DieModuleInterface. This prevents aircraft from being stranded in destroyed structures.

**Dependencies**:
- Requires objects with production capabilities. ParkingPlaceBehavior interfaces with [ProductionUpdate](../ObjectModules/ProductionUpdate.md) to manage door states and coordinate unit exits.
- Depends on bone structure for parking position calculations. The object's model must have the required bone names as described in Limitations.
- Requires proper aircraft AI systems. Aircraft should use [JetAIUpdate](../ObjectModules/JetAIUpdate.md) for proper runway and parking coordination.
- Inherits functionality from [UpdateModule](../ModuleBase/UpdateModule.md), DieModuleInterface, and ExitInterface.
- For inventory item replenishment (GMX only): Requires vehicles to have [InventoryBehavior](../ObjectBehaviorsModules/InventoryBehavior.md) with proper item definitions. Invalid item names are silently ignored.
- For component restoration (GMX only): Requires vehicles to have [Component](../ObjectBody/Component.md) systems with properly named components. Invalid component names are silently ignored.

## Properties

### Parking Layout

#### `NumRows` *(v1.04)*
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Int`
- **Description**: Number of rows in the parking grid layout. Higher values create more parking spaces vertically. The total number of parking spaces is determined by [NumRows](#numrows) multiplied by [NumCols](#numcols). When set to 0 (default), no parking rows are available and the module cannot function properly. Each row requires corresponding bone names in the model (`Runway%dPark%dHan`, `Runway%dParking%d`, `Runway%dPrep%d` for each column).
- **Default**: `0`
- **Example**: `NumRows = 3`

#### `NumCols` *(v1.04)*
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Int`
- **Description**: Number of columns in the parking grid layout. Higher values create more parking spaces horizontally and determine the number of runways (if [HasRunways](#hasrunways) is enabled). The total number of parking spaces is determined by [NumRows](#numrows) multiplied by [NumCols](#numcols). When set to 0 (default), no parking columns are available and the module cannot function properly. Each column requires corresponding bone names in the model.
- **Default**: `0`
- **Example**: `NumCols = 4`

### Aircraft Handling

#### `ApproachHeight` *(v1.04)*
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real` (distance)
- **Description**: Height at which aircraft approach the parking area from the runway end. Higher values make aircraft approach from greater heights, providing more clearance during landing approaches. Lower values make aircraft approach closer to the deck surface. When set to 0 (default), no specific approach height offset is applied beyond the runway end height. This value is added to the runway end height to calculate the final approach position.
- **Default**: `0.0`
- **Example**: `ApproachHeight = 50.0`

#### `LandingDeckHeightOffset` *(v1.04, Zero Hour only)*
Available only in: *(v1.04, Zero Hour only)*

- **Type**: `Real` (distance)
- **Description**: Height offset for the landing deck surface. Higher values raise the landing deck, affecting how aircraft are positioned when parked. This offset is applied to aircraft that park on the deck, setting the `OBJECT_STATUS_DECK_HEIGHT_OFFSET` status flag. When set to 0 (default), no height offset is applied and aircraft use the standard terrain height. This property is only available in Zero Hour versions (both GMX and Retail).
- **Default**: `0.0`
- **Example**: `LandingDeckHeightOffset = 10.0`

### Runway Configuration

#### `HasRunways` *(v1.04)*
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Determines if each column has a runway in front of it. When `Yes`, runways are available for each column, allowing aircraft to land and take off. Each runway requires `RunwayStart%d` and `RunwayEnd%d` bone names in the model (where `%d` is the column number). When `No` (default), no runways are available and aircraft cannot use runway-based landing or takeoff operations. Runways are used for approach coordination, landing sequences, and takeoff queuing.
- **Default**: `No`
- **Example**: `HasRunways = Yes`

### Parking Behavior

#### `ParkInHangars` *(v1.04)*
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Determines if aircraft park at hangar production spots instead of real parking places. When `Yes`, aircraft park at the hangar start positions (`Runway%dPark%dHan` bones) instead of the designated parking locations (`Runway%dParking%d` bones). This affects both the parking position and orientation used by aircraft. When `No` (default), aircraft park in the designated parking spaces. Hangar parking is typically used for aircraft that should appear inside structures rather than on deck.
- **Default**: `No`
- **Example**: `ParkInHangars = Yes`

### Healing System

#### `HealAmountPerSecond` *(v1.04)*
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real` (health per second)
- **Description**: Amount of health restored per second to parked aircraft. Higher values heal aircraft faster, providing quicker recovery from damage. Lower values heal more slowly, requiring more time for full healing. The healing occurs automatically at regular intervals (every 0.2 seconds) for all aircraft that are currently parked in a parking space. When set to 0 (default), no healing occurs. Healing only affects parked aircraft - aircraft must be in a reserved parking space to receive healing.
- **Default**: `0.0`
- **Example**: `HealAmountPerSecond = 10.0`

### Restoration System *(GMX Generals, GMX Zero Hour only)*

Available in: *(GMX Generals, GMX Zero Hour only)*

#### `RepublishAmount` *(GMX Generals, GMX Zero Hour only)*
Available in: *(GMX Generals, GMX Zero Hour only)*

- **Type**: `Real`
- **Description**: Amount of inventory items to restore per second for parked vehicles. The value interpretation depends on [RepublishAmountValueType](#republishamountvaluetype): if `RepublishAmountValueType` is `ABSOLUTE`, the value is added directly to the item count each second; if `RepublishAmountValueType` is `PERCENTAGE`, the value is treated as a percentage of the maximum storage capacity (e.g., `5.0%` means 5% of maximum storage per second). The value can be specified with a `%` suffix to automatically use percentage mode (e.g., `RepublishAmount = 5.0%`). Restoration occurs once per second for all parked vehicles that have items listed in [ReplenishItems](#replenishitems). The restoration amount is capped at the maximum storage capacity - vehicles will not exceed their maximum item storage. When set to 0, no restoration occurs.
- **Default**: `5.0`
- **Example**: `RepublishAmount = 5.0` or `RepublishAmount = 5.0%` (percentage mode)

#### `RepublishAmountValueType` *(GMX Generals, GMX Zero Hour only)*
Available in: *(GMX Generals, GMX Zero Hour only)*

- **Type**: `ValueType` (see [ValueType Values](#valuetype-values) section)
- **Description**: Controls how [RepublishAmount](#republishamount) is interpreted. When set to `ABSOLUTE`, the value is added directly to the item count each second. When set to `PERCENTAGE`, the value is treated as a percentage of the maximum storage capacity (e.g., `5.0` means 5% of maximum storage per second). This property is automatically set when [RepublishAmount](#republishamount) is specified with a `%` suffix. If [RepublishAmount](#republishamount) contains a `%` symbol, `RepublishAmountValueType` is automatically set to `PERCENTAGE`; otherwise, it defaults to `PERCENTAGE` (default value is 5.0 with PERCENTAGE type).
- **Default**: `PERCENTAGE`
- **Example**: `RepublishAmountValueType = PERCENTAGE`
- **Available Values**: see [ValueType Values](#valuetype-values)

#### `ReplenishItems` *(GMX Generals, GMX Zero Hour only)*
Available in: *(GMX Generals, GMX Zero Hour only)*

- **Type**: Space-separated list of `AsciiString` (inventory item names)
- **Description**: List of inventory items to replenish for parked vehicles. Each item name in the list is replenished using the [RepublishAmount](#republishamount) and [RepublishAmountValueType](#republishamountvaluetype) settings once per second for vehicles that have [InventoryBehavior](../ObjectBehaviorsModules/InventoryBehavior.md). Items are replenished gradually - the amount restored each second is determined by [RepublishAmount](#republishamount) (as a percentage of maximum storage or absolute value, depending on [RepublishAmountValueType](#republishamountvaluetype)). If a vehicle does not have [InventoryBehavior](../ObjectBehaviorsModules/InventoryBehavior.md), item replenishment is silently skipped. Invalid or non-existent item names are silently ignored - the system checks if the item exists in the vehicle's inventory system before attempting replenishment. Multiple items can be specified by separating them with spaces (e.g., `ReplenishItems = Fuel Rockets Bombs`).
- **Default**: Empty (no items replenished)
- **Example**: `ReplenishItems = Fuel Rockets`
- **Invalid Reference Handling**: If an item name does not exist in the vehicle's [InventoryBehavior](../ObjectBehaviorsModules/InventoryBehavior.md) system, the item is silently ignored. The system checks for item existence and maximum storage capacity - if the item doesn't exist or cannot be stored, replenishment is skipped without error. Vehicles without [InventoryBehavior](../ObjectBehaviorsModules/InventoryBehavior.md) are skipped entirely.

#### `RestoreComponents` *(GMX Generals, GMX Zero Hour only)*
Available in: *(GMX Generals, GMX Zero Hour only)*

- **Type**: Space-separated list of `AsciiString` (component names)
- **Description**: List of components to restore to maximum health for parked vehicles. Each component name in the list is restored to maximum health during each healing tick for vehicles that have the specified [Component](../ObjectBody/Component.md). Components are restored if their current health is less than their maximum health - the component's health is set to its maximum value and the vehicle's damage state is updated. If a vehicle does not have a body module with components, component restoration is silently skipped. Invalid or non-existent component names are silently ignored - the system checks if the component exists and only restores components that are found. Multiple components can be specified by separating them with spaces (e.g., `RestoreComponents = MainEngine FuelTank WeaponsSystem`).
- **Default**: Empty (no components restored)
- **Example**: `RestoreComponents = MainEngine FuelTank`
- **Invalid Reference Handling**: If a component name does not exist on the vehicle, the component is silently ignored. The system checks for component existence - if the component doesn't exist, restoration is skipped without error. Vehicles without a body module or without the component system are skipped entirely.

## Enum Value Lists

<a id="valuetype-values"></a>
#### `ValueType` Values

Available in: *(GMX Generals, GMX Zero Hour only)*

- **Source**: [GameType.h](../../GeneralsMD/Code/GameEngine/Include/Common/GameType.h) - `TheValueTypeNames[]` array definition

- **`ABSOLUTE`** *(GMX Generals, GMX Zero Hour only)* — The value is treated as an absolute amount. If `RepublishAmount = 10.0` and `RepublishAmountValueType = ABSOLUTE`, the item count is increased by exactly 10.0 per second, regardless of the maximum storage capacity.

- **`PERCENTAGE`** *(GMX Generals, GMX Zero Hour only)* — The value is treated as a percentage of the maximum storage capacity. If `RepublishAmount = 5.0` and `RepublishAmountValueType = PERCENTAGE`, and the item has a maximum storage of 100, the item count is increased by 5.0 per second (5% of 100). The value can also be specified with a `%` suffix in `RepublishAmount` (e.g., `RepublishAmount = 5.0%`), which automatically sets `RepublishAmountValueType` to `PERCENTAGE`.

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

### Aircraft Carrier with Restoration (GMX only)
```ini
Update = ParkingPlaceBehavior ModuleTag_04
  NumRows = 3
  NumCols = 4
  ApproachHeight = 75.0
  LandingDeckHeightOffset = 15.0
  HasRunways = Yes
  ParkInHangars = No
  HealAmountPerSecond = 10.0
  RepublishAmount = 5.0%
  RepublishAmountValueType = PERCENTAGE
  ReplenishItems = Fuel Rockets Bombs
  RestoreComponents = MainEngine FuelTank WeaponsSystem
End
```

## Template

```ini
Update = ParkingPlaceBehavior ModuleTag_XX
  ; Parking Layout
  NumRows = 0                        ; // number of parking rows *(v1.04)*
  NumCols = 0                        ; // number of parking columns *(v1.04)*
  
  ; Aircraft Handling
  ApproachHeight = 0.0               ; // aircraft approach height from runway end *(v1.04)*
  LandingDeckHeightOffset = 0.0      ; // landing deck height offset *(v1.04, Zero Hour only)*
  
  ; Runway Configuration
  HasRunways = No                    ; // enable runways for each column *(v1.04)*
  
  ; Parking Behavior
  ParkInHangars = No                 ; // park aircraft in hangars instead of parking spaces *(v1.04)*
  
  ; Healing System
  HealAmountPerSecond = 0.0          ; // health restored per second to parked aircraft *(v1.04)*
  
  ; Restoration System (GMX only)
  RepublishAmount = 5.0              ; // amount to restore per second (percentage or absolute) *(GMX Generals, GMX Zero Hour only)*
  RepublishAmountValueType = PERCENTAGE ; // how RepublishAmount is interpreted (ABSOLUTE or PERCENTAGE) *(GMX Generals, GMX Zero Hour only)*
  ReplenishItems =                   ; // space-separated list of inventory items to replenish *(GMX Generals, GMX Zero Hour only)*
  RestoreComponents =                ; // space-separated list of components to restore to max health *(GMX Generals, GMX Zero Hour only)*
End
```

## Notes

- ParkingPlaceBehavior manages comprehensive aircraft parking systems for carriers and airfields with configurable grid layouts, runway management, and healing capabilities.
- Supports configurable grid layouts with rows and columns. The total number of parking spaces is [NumRows](#numrows) multiplied by [NumCols](#numcols). Each space requires specific bone names in the object's model.
- Includes runway management for aircraft landing and takeoff operations. Runways are allocated per column when [HasRunways](#hasrunways) is enabled, with queuing support for multiple aircraft waiting to take off.
- Provides automatic healing for parked aircraft at regular intervals (every 0.2 seconds). Healing only affects aircraft that are currently parked in a reserved parking space.
- Inventory item replenishment occurs once per second for parked vehicles that have the required systems (GMX only), using the [RepublishAmount](#republishamount) and [RepublishAmountValueType](#republishamountvaluetype) settings. Component restoration occurs during each healing tick. Invalid item or component names are silently ignored.
- Requires proper bone structure in the object's model. Missing bones may cause parking positions to be incorrectly placed or the module may not function properly. The module expects bones named `Runway%dPark%dHan`, `Runway%dParking%d`, `Runway%dPrep%d` for parking spaces, `RunwayStart%d` and `RunwayEnd%d` for runways, and `HeliPark01` for helipad functionality.
- ParkingPlaceBehavior integrates with [ProductionUpdate](../ObjectModules/ProductionUpdate.md) to manage door states and coordinate unit exits. Doors are automatically opened when spaces are reserved and closed when spaces are released.
- Aircraft with [JetAIUpdate](../ObjectModules/JetAIUpdate.md) coordinate with ParkingPlaceBehavior to reserve runways and parking spaces. The module provides runway reservation queuing for takeoff operations.
- Helipad aircraft (with `KINDOF_PRODUCED_AT_HELIPAD`) use special handling and do not require parking space reservations. They use the `HeliPark01` bone position and can use rally points for positioning.
- When the object with ParkingPlaceBehavior is destroyed, all parked aircraft are automatically killed. This prevents aircraft from being stranded in destroyed structures.
- Commonly used for aircraft carriers, airfields, and aviation facilities that need realistic aircraft management with proper space allocation, runway coordination, and maintenance capabilities.
- The module handles parking space allocation, runway reservations, exit coordination, and continuous healing/restoration operations for parked aircraft.

## Source Files

**Base Class:** [UpdateModule](../ModuleBase/UpdateModule.md)

- Header (GMX Zero Hour): [ParkingPlaceBehavior.h](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ParkingPlaceBehavior.h)
- Source (GMX Zero Hour): [ParkingPlaceBehavior.cpp](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/ParkingPlaceBehavior.cpp)
- Header (GMX Generals): [ParkingPlaceBehavior.h](../../Generals/Code/GameEngine/Include/GameLogic/Module/ParkingPlaceBehavior.h)
- Source (GMX Generals): [ParkingPlaceBehavior.cpp](../../Generals/Code/GameEngine/Source/GameLogic/Object/Behavior/ParkingPlaceBehavior.cpp)

## Changes History

- v1.04 — Adds ParkingPlaceBehavior (aircraft parking systems with grid layouts, runways, and healing).
- v1.04 (Zero Hour only) — Adds [LandingDeckHeightOffset](#landingdeckheightoffset) for landing deck height offset support.
- GMX — Adds inventory item replenishment and component restoration properties ([RepublishAmount](#republishamount), [RepublishAmountValueType](#republishamountvaluetype), [ReplenishItems](#replenishitems), [RestoreComponents](#restorecomponents)) for parked vehicles.

## Document Log

- 16/12/2025 — AI — Initial document created.

## Status

- Documentation Status: AI-generated
- Last Updated: 16/12/2025 by AI
- Certification: 0/2 reviews

### Reviewers

- (pending)
