# MinefieldBehavior

Update module that manages minefield behavior including detonation, regeneration, and virtual mine tracking for defensive mine systems.

## Overview

MinefieldBehavior is a complex update module that manages the behavior of minefields in the game. It handles mine detonation when objects collide with the minefield, supports regeneration of destroyed mines, and manages virtual mine counts for representing multiple mines in a single object. The module includes collision detection, damage handling, and death management for comprehensive minefield functionality.

MinefieldBehavior must be embedded within object definitions and cannot be used as a standalone object template.

## Usage

Used by objects that should function as minefields with collision detection, regeneration capabilities, and virtual mine management. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Requires valid weapon templates for detonation effects
- Limited to maximum immunity tracking for performance
- Cannot function without proper collision and damage systems
- Requires proper minefield configuration for functionality

**Conditions**:
- Multiple instances behavior: Multiple MinefieldBehavior modules can exist independently, each managing different minefield areas
- Always active once assigned to an object
- Continuously monitors for collisions and manages minefield state
- Creates tactical defensive positions with automatic mine management

**Dependencies**:
- Requires valid weapon templates for detonation effects
- Depends on collision detection and damage systems
- Inherits functionality from UpdateModule, CollideModuleInterface, DamageModuleInterface, and DieModuleInterface

## Properties

### Detonation Configuration

#### `DetonationWeapon` *(v1.04)*
- **Type**: `Weapon` (see [Weapon documentation](../Weapon.md))
- **Description**: Weapon template fired when the minefield detonates. When set, creates the specified weapon effect on detonation. When NULL (default), no detonation weapon is fired
- **Default**: `NULL` (none)
- **Example**: `DetonationWeapon = WeaponMineExplosion`

#### `DetonatedBy` *(v1.04)*
- **Type**: `Int` (bit flags)
- **Description**: Bitmask of relationship types that can trigger minefield detonation. When set to ENEMIES NEUTRAL (default), enemies and neutral units can detonate mines. When set to 0, no units can detonate mines
- **Default**: `ENEMIES NEUTRAL`
- **Example**: `DetonatedBy = ENEMIES`

### Regeneration Settings

#### `Regenerates` *(v1.04)*
- **Type**: `Bool`
- **Description**: Determines if the minefield can regenerate destroyed mines. When `Yes`, mines can be regenerated. When `No` (default), mines cannot be regenerated
- **Default**: `No`
- **Example**: `Regenerates = Yes`

#### `StopsRegenAfterCreatorDies` *(v1.04)*
- **Type**: `Bool`
- **Description**: Determines if regeneration stops when the minefield creator dies. When `Yes` (default), regeneration stops after creator death. When `No`, regeneration continues regardless of creator status
- **Default**: `Yes`
- **Example**: `StopsRegenAfterCreatorDies = No`

#### `CreatorDeathCheckRate` *(v1.04)*
- **Type**: `UnsignedInt` (frames)
- **Description**: Frequency in frames for checking if the minefield creator is still alive. Higher values check less frequently. When set to LOGICFRAMES_PER_SECOND (default), checks once per second
- **Default**: `LOGICFRAMES_PER_SECOND`
- **Example**: `CreatorDeathCheckRate = 60`

### Worker Interaction

#### `WorkersDetonate` *(v1.04)*
- **Type**: `Bool`
- **Description**: Determines if worker units can detonate mines. When `Yes`, workers can trigger mine detonation. When `No` (default), workers cannot detonate mines
- **Default**: `No`
- **Example**: `WorkersDetonate = Yes`

### Virtual Mine Management

#### `NumVirtualMines` *(v1.04)*
- **Type**: `UnsignedInt`
- **Description**: Number of virtual mines represented by this minefield object. Higher values represent more mines in a single object. When set to 1 (default), represents a single mine
- **Default**: `1`
- **Example**: `NumVirtualMines = 5`

#### `RepeatDetonateMoveThresh` *(v1.04)*
- **Type**: `Real` (distance)
- **Description**: Distance threshold for allowing repeated detonation by the same unit. Higher values allow repeated detonation at greater distances. When set to 1.0 (default), allows detonation when units move 1 unit away
- **Default**: `1.0`
- **Example**: `RepeatDetonateMoveThresh = 2.0`

### Movement and Positioning

#### `ScootFromStartingPointTime` *(v1.04)*
- **Type**: `UnsignedInt` (frames)
- **Description**: Time in frames for the minefield to gradually move from its starting point to a destination. Higher values make movement slower. When set to 0 (default), no movement occurs
- **Default**: `0`
- **Example**: `ScootFromStartingPointTime = 120`

### Health Management

#### `DegenPercentPerSecondAfterCreatorDies` *(v1.04)*
- **Type**: `Real` (percentage)
- **Description**: Health percentage drained per second after the minefield creator dies. Higher values cause faster health drain. When set to 0 (default), no health drain occurs
- **Default**: `0.0`
- **Example**: `DegenPercentPerSecondAfterCreatorDies = 0.1`

### Object Creation

#### `CreationList` *(v1.04)*
- **Type**: `ObjectCreationList`
- **Description**: Objects created when the minefield is activated or detonates. When set, spawns the specified objects. When NULL (default), no objects are created
- **Default**: `NULL` (none)
- **Example**: `CreationList = OCL_MinefieldDebris`

## Examples

### Basic Minefield
```ini
Update = MinefieldBehavior ModuleTag_01
  DetonationWeapon = WeaponMineExplosion
  DetonatedBy = ENEMIES NEUTRAL
  Regenerates = No
  WorkersDetonate = No
  NumVirtualMines = 1
End
```

### Regenerating Minefield
```ini
Update = MinefieldBehavior ModuleTag_02
  DetonationWeapon = WeaponAdvancedMineExplosion
  DetonatedBy = ENEMIES
  Regenerates = Yes
  StopsRegenAfterCreatorDies = Yes
  CreatorDeathCheckRate = 60
  NumVirtualMines = 3
  DegenPercentPerSecondAfterCreatorDies = 0.05
End
```

### Worker-Safe Minefield
```ini
Update = MinefieldBehavior ModuleTag_03
  DetonationWeapon = WeaponMineExplosion
  DetonatedBy = ENEMIES
  WorkersDetonate = Yes
  NumVirtualMines = 2
  RepeatDetonateMoveThresh = 1.5
End
```

## Template

```ini
Update = MinefieldBehavior ModuleTag_XX
  ; Detonation Configuration
  DetonationWeapon =                     ; // weapon fired on detonation *(v1.04)*
  DetonatedBy = ENEMIES NEUTRAL ; // relationship types that trigger detonation *(v1.04)*
  
  ; Regeneration Settings
  Regenerates = No                       ; // enable mine regeneration *(v1.04)*
  StopsRegenAfterCreatorDies = Yes       ; // stop regeneration after creator death *(v1.04)*
  CreatorDeathCheckRate = LOGICFRAMES_PER_SECOND ; // frequency to check creator status *(v1.04)*
  
  ; Worker Interaction
  WorkersDetonate = No                   ; // allow workers to detonate mines *(v1.04)*
  
  ; Virtual Mine Management
  NumVirtualMines = 1                    ; // number of virtual mines represented *(v1.04)*
  RepeatDetonateMoveThresh = 1.0         ; // distance threshold for repeated detonation *(v1.04)*
  
  ; Movement and Positioning
  ScootFromStartingPointTime = 0         ; // time to move from start to destination *(v1.04)*
  
  ; Health Management
  DegenPercentPerSecondAfterCreatorDies = 0.0 ; // health drain rate after creator death *(v1.04)*
  
  ; Object Creation
  CreationList =                         ; // objects created on activation *(v1.04)*
End
```

## Notes

- MinefieldBehavior manages comprehensive minefield functionality including detonation, regeneration, and virtual mine tracking
- Supports different relationship types for detonation triggering
- Includes immunity tracking to prevent repeated detonation by the same unit
- Commonly used for defensive minefield systems and area denial weapons
- The module handles collision detection, damage application, and death management
- Creates tactical defensive positions with automatic mine management

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/MinefieldBehavior.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/MinefieldBehavior.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/MinefieldBehavior.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/MinefieldBehavior.cpp)