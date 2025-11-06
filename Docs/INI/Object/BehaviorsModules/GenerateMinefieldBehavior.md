# GenerateMinefieldBehavior

Behavior module that creates minefields around objects with configurable patterns, densities, and upgrade support.

## Overview

GenerateMinefieldBehavior is a complex behavior module that automatically generates minefields around objects with various placement patterns, densities, and upgrade capabilities. It can create circular or rectangular minefields, place mines only on borders or fill areas, and support upgrades that change mine types or placement patterns. This module is commonly used for defensive structures and special units that deploy minefields.

GenerateMinefieldBehavior must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that should generate minefields around themselves with configurable patterns, densities, and placement logic. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Requires valid mine templates to function
- Mine placement depends on terrain and structure detection
- Cannot generate mines when disabled or destroyed (unless on death is enabled)
- Limited by terrain accessibility and structure overlap
- Requires proper mine templates and placement logic

**Conditions**:
- Multiple instances behavior: Multiple GenerateMinefieldBehavior modules can exist independently, each creating different minefields
- Always active once assigned to an object
- Can be triggered by death, upgrades, or manual activation
- Creates tactical defensive positions around the object

**Dependencies**:
- Requires valid mine templates for mine creation
- Depends on terrain system for placement validation
- Inherits all functionality from UpdateModule and UpgradeMux

## Properties

### Mine Configuration

#### `MineName` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Name of the mine template to create in the minefield. When set, defines what type of mines are placed. When empty (default), no mines are created
- **Default**: `""` (empty)
- **Example**: `MineName = MineAntiTank`

#### `UpgradedMineName` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Name of the upgraded mine template to create when upgrades are active. When set, replaces the base mine type with upgraded mines. When empty (default), no upgraded mines are used
- **Default**: `""` (empty)
- **Example**: `UpgradedMineName = MineAntiTankAdvanced`

#### `UpgradedTriggeredBy` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: Name of the upgrade that triggers the use of upgraded mines. When set, activates upgraded mine placement when the specified upgrade is completed. When empty (default), no upgrade trigger is used
- **Default**: `""` (empty)
- **Example**: `UpgradedTriggeredBy = UpgradeAdvancedMining`

### Placement Settings

#### `DistanceAroundObject` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Radius around the object where mines are placed. Higher values create larger minefields. When set to 0 (default), uses standard minefield distance from global data
- **Default**: `TheGlobalData->m_standardMinefieldDistance` (from global data)
- **Example**: `DistanceAroundObject = 100.0`

#### `MinesPerSquareFoot` *(v1.04)*
- **Type**: `Real` (density)
- **Description**: Density of mines per square foot of area. Higher values create denser minefields with more mines. When set to 0 (default), uses standard minefield density from global data
- **Default**: `TheGlobalData->m_standardMinefieldDensity` (from global data)
- **Example**: `MinesPerSquareFoot = 0.1`

#### `RandomJitter` *(v1.04)*
- **Type**: `Real` (percentage)
- **Description**: Random offset percentage for mine placement positions. Higher values create more scattered mine placement. When set to 0 (default), mines are placed in exact grid positions
- **Default**: `0.0`
- **Example**: `RandomJitter = 0.25`

### Placement Patterns

#### `BorderOnly` *(v1.04)*
- **Type**: `Bool`
- **Description**: Determines if mines are placed only on the border of the minefield. When `Yes` (default), mines are placed only around the perimeter. When `No`, mines fill the entire area
- **Default**: `Yes`
- **Example**: `BorderOnly = No`

#### `AlwaysCircular` *(v1.04)*
- **Type**: `Bool`
- **Description**: Forces circular minefield pattern regardless of object shape. When `Yes`, creates circular minefields. When `No` (default), uses object's actual geometry for minefield shape
- **Default**: `No`
- **Example**: `AlwaysCircular = Yes`

#### `SmartBorder` *(v1.04)*
- **Type**: `Bool`
- **Description**: Enables intelligent border detection that follows terrain features. When `Yes`, mines are placed along smart-detected borders. When `No` (default), uses simple geometric borders
- **Default**: `No`
- **Example**: `SmartBorder = Yes`

#### `SmartBorderSkipInterior` *(v1.04)*
- **Type**: `Bool`
- **Description**: Skips placing mines in interior areas when using smart border detection. When `Yes` (default), only border areas get mines. When `No`, mines can be placed in interior areas
- **Default**: `Yes`
- **Example**: `SmartBorderSkipInterior = No`

### Timing and Triggers

#### `GenerateOnlyOnDeath` *(v1.04)*
- **Type**: `Bool`
- **Description**: Determines if mines are generated only when the object dies. When `Yes`, mines are created only on death. When `No` (default), mines are generated during normal operation
- **Default**: `No`
- **Example**: `GenerateOnlyOnDeath = Yes`

#### `Upgradable` *(v1.04)*
- **Type**: `Bool`
- **Description**: Enables upgrade support for the minefield behavior. When `Yes`, the behavior can be upgraded to change mine types or patterns. When `No` (default), no upgrade support is available
- **Default**: `No`
- **Example**: `Upgradable = Yes`

### Structure Detection

#### `SkipIfThisMuchUnderStructure` *(v1.04)*
- **Type**: `Real` (percentage)
- **Description**: Percentage threshold for skipping mine placement under structures. When mine placement would be this much under a structure, the mine is skipped. Higher values are more tolerant of structure overlap
- **Default**: `0.33` (33%)
- **Example**: `SkipIfThisMuchUnderStructure = 0.5`

### Visual Effects

#### `GenerationFX` *(v1.04)*
- **Type**: `FXList` (see [FXList documentation](../FXList.md))
- **Description**: Visual effects played when mines are generated. When set, displays the specified effects during mine placement. When NULL (default), no visual effects are shown
- **Default**: `NULL` (none)
- **Example**: `GenerationFX = FX_MinefieldGeneration`

## Examples

### Basic Minefield Generator
```ini
Behavior = GenerateMinefieldBehavior ModuleTag_01
  MineName = MineAntiTank
  DistanceAroundObject = 75.0
  MinesPerSquareFoot = 0.05
  BorderOnly = Yes
  GenerationFX = FX_MinefieldGeneration
End
```

### Advanced Upgradable Minefield
```ini
Behavior = GenerateMinefieldBehavior ModuleTag_02
  MineName = MineAntiTank
  UpgradedMineName = MineAntiTankAdvanced
  UpgradedTriggeredBy = UpgradeAdvancedMining
  DistanceAroundObject = 100.0
  MinesPerSquareFoot = 0.08
  BorderOnly = No
  AlwaysCircular = Yes
  RandomJitter = 0.15
  Upgradable = Yes
  GenerationFX = FX_AdvancedMinefieldGeneration
End
```

### Death-Triggered Minefield
```ini
Behavior = GenerateMinefieldBehavior ModuleTag_03
  MineName = MineAntiPersonnel
  DistanceAroundObject = 50.0
  MinesPerSquareFoot = 0.1
  GenerateOnlyOnDeath = Yes
  BorderOnly = Yes
  GenerationFX = FX_DeathMinefield
End
```

## Template

```ini
Behavior = GenerateMinefieldBehavior ModuleTag_XX
  ; Mine Configuration
  MineName =                         ; // base mine template to create *(v1.04)*
  UpgradedMineName =                 ; // upgraded mine template *(v1.04)*
  UpgradedTriggeredBy =              ; // upgrade trigger name *(v1.04)*
  
  ; Placement Settings
  DistanceAroundObject = 0.0         ; // minefield radius *(v1.04)*
  MinesPerSquareFoot = 0.0           ; // mine density per square foot *(v1.04)*
  RandomJitter = 0.0                 ; // random placement offset *(v1.04)*
  
  ; Placement Patterns
  BorderOnly = Yes                   ; // place mines only on border *(v1.04)*
  AlwaysCircular = No                ; // force circular minefield *(v1.04)*
  SmartBorder = No                   ; // enable smart border detection *(v1.04)*
  SmartBorderSkipInterior = Yes      ; // skip interior with smart border *(v1.04)*
  
  ; Timing and Triggers
  GenerateOnlyOnDeath = No           ; // generate mines only on death *(v1.04)*
  Upgradable = No                    ; // enable upgrade support *(v1.04)*
  
  ; Structure Detection
  SkipIfThisMuchUnderStructure = 0.33 ; // structure overlap threshold *(v1.04)*
  
  ; Visual Effects
  GenerationFX =                     ; // mine generation visual effects *(v1.04)*
End
```

## Notes

- GenerateMinefieldBehavior creates minefields around objects with various placement patterns and densities
- Supports upgrades that can change mine types or placement patterns
- Can generate mines during operation or only on death
- Includes smart border detection and structure overlap avoidance
- Creates tactical defensive positions with automatic mine placement
- Commonly used by defensive structures, special units, and mine-laying vehicles
- The module manages mine placement patterns, densities, and upgrade integration

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/GenerateMinefieldBehavior.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/GenerateMinefieldBehavior.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/GenerateMinefieldBehavior.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/GenerateMinefieldBehavior.cpp)