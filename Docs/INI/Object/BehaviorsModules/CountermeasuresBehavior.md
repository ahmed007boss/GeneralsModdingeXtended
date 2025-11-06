# CountermeasuresBehavior

CountermeasuresBehavior provides countermeasure functionality for aircraft, allowing them to deploy flares and other defensive measures against incoming missile threats.

## Overview

The `CountermeasuresBehavior` class manages automatic countermeasure deployment for aircraft under missile threat. It handles flare launching, missile diversion, volley patterns, reloading mechanics, and evasion rates. The behavior is commonly used by aircraft that need defensive capabilities against guided missiles and other precision weapons.

## Usage

Used by aircraft units that can deploy countermeasures such as flares, chaff, or other defensive systems to evade or counter incoming weapons. This is a **behavior module** that must be embedded within object definitions.Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Only works on airborne targets
- Countermeasures only function when the behavior is upgrade-activated
- Aircraft must land at airfields to reload if MustReloadAtAirfield is enabled
- CountermeasuresBehavior is exclusive to Generals Zero Hour (v1.04)
- Countermeasures are tracked individually and cleaned up when they expire

**Conditions**:
- The behavior automatically detects incoming missiles and determines evasion based on EvasionRate
- Flares are launched in volleys with configurable spread patterns and timing
- Missile diversion occurs after a delay to allow countermeasures to be deployed first
- Aircraft can auto-reload countermeasures or require landing at airfields
- The behavior integrates with the upgrade system for conditional activation
- Multiple volleys can be fired with different timing and spread patterns
- The behavior handles both reactive (threat-based) and continuous countermeasure deployment
- **Multiple instances behavior**: Only one instance should be used per object; multiple instances may cause conflicts in countermeasure management

**Dependencies**:
- Requires valid flare template definitions to function

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Flare Configuration](#flare-configuration)
  - [Volley Settings](#volley-settings)
  - [Timing Settings](#timing-settings)
  - [Evasion Settings](#evasion-settings)
  - [Upgrade Integration](#upgrade-integration)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)

## Properties

### Flare Configuration

#### `FlareTemplateName` *(v1.04, Generals Zero Hour only)*
- **Type**: `AsciiString`
- **Description**: Template name of the flare object to create
- **Example**: `FlareTemplateName = CountermeasureFlare`

#### `FlareBoneBaseName` *(v1.04, Generals Zero Hour only)*
- **Type**: `AsciiString`
- **Description**: Base name for flare launch bones (Flare01, Flare02, Flare03, etc.)
- **Example**: `FlareBoneBaseName = Flare`

### Volley Settings

#### `VolleySize` *(v1.04, Generals Zero Hour only)*
- **Type**: `UnsignedInt`
- **Description**: Number of flares launched per volley
- **Example**: `VolleySize = 2`

#### `VolleyArcAngle` *(v1.04, Generals Zero Hour only)*
- **Type**: `Real` (angle)
- **Description**: Maximum angle of flare spread relative to forward direction
- **Example**: `VolleyArcAngle = 60.0`

#### `VolleyVelocityFactor` *(v1.04, Generals Zero Hour only)*
- **Type**: `Real`
- **Description**: Multiplier for flare launch velocity
- **Example**: `VolleyVelocityFactor = 2.0`

#### `NumberOfVolleys` *(v1.04, Generals Zero Hour only)*
- **Type**: `UnsignedInt`
- **Description**: Total number of volleys available before reloading
- **Example**: `NumberOfVolleys = 4`

### Timing Settings

#### `DelayBetweenVolleys` *(v1.04, Generals Zero Hour only)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time delay between consecutive volley launches
- **Example**: `DelayBetweenVolleys = 650`

#### `ReloadTime` *(v1.04, Generals Zero Hour only)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time required to reload countermeasures (0 = no auto-reload)
- **Example**: `ReloadTime = 30000`

#### `MissileDecoyDelay` *(v1.04, Generals Zero Hour only)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Delay before missiles divert to countermeasures
- **Example**: `MissileDecoyDelay = 1000`

#### `ReactionLaunchLatency` *(v1.04, Generals Zero Hour only)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Delay before launching first countermeasure volley after threat detection
- **Example**: `ReactionLaunchLatency = 500`

### Evasion Settings

#### `EvasionRate` *(v1.04, Generals Zero Hour only)*
- **Type**: `Real` (percentage)
- **Description**: Percentage chance that incoming missiles will be diverted to countermeasures
- **Example**: `EvasionRate = 75.0`

#### `MustReloadAtAirfield` *(v1.04, Generals Zero Hour only)*
- **Type**: `Bool`
- **Description**: Whether countermeasures can only be reloaded at airfields
- **Example**: `MustReloadAtAirfield = Yes`

### Upgrade Integration

#### `TriggeredBy` *(v1.04, Generals Zero Hour only)*
- **Type**: `UpgradeMaskType` (bit flags)
- **Description**: Required upgrade flags to activate the countermeasures behavior
- **Example**: `TriggeredBy = Upgrade_AmericaCountermeasures`

#### `ConflictsWith` *(v1.04, Generals Zero Hour only)*
- **Type**: `UpgradeMaskType` (bit flags)
- **Description**: Upgrade flags that conflict with this countermeasures behavior
- **Example**: `ConflictsWith = Upgrade_StealthMode`

#### `RequiresAll` *(v1.04, Generals Zero Hour only)*
- **Type**: `Bool`
- **Description**: Whether all TriggeredBy upgrades must be active (true) or just one (false)
- **Example**: `RequiresAll = Yes`

## Examples

### China H20 Countermeasures
```ini
Behavior = CountermeasuresBehavior Upgrade_05
  TriggeredBy = Upgrade_AmericaCountermeasures
  FlareTemplateName = CountermeasureFlare
  FlareBoneBaseName = Flare
  VolleySize = 2
  VolleyArcAngle = 60.0
  VolleyVelocityFactor = 2.0
  DelayBetweenVolleys = 650
  NumberOfVolleys = 3
  EvasionRate = 80.0
  ReloadTime = 45000
  MustReloadAtAirfield = No
End
```

### Russia Tu22M3 Countermeasures
```ini
Behavior = CountermeasuresBehavior Upgrade_02
  TriggeredBy = Upgrade_AmericaCountermeasures
  FlareTemplateName = RuCountermeasureECMJet
  FlareBoneBaseName = Flare
  VolleySize = 1
  VolleyArcAngle = 0.0
  VolleyVelocityFactor = 1.0
  DelayBetweenVolleys = 100
  NumberOfVolleys = 4
  EvasionRate = 70.0
  ReloadTime = 0
  MustReloadAtAirfield = Yes
  MissileDecoyDelay = 800
  ReactionLaunchLatency = 300
End
```

### Advanced Countermeasures System
```ini
Behavior = CountermeasuresBehavior ModuleTag_AdvancedCountermeasures
  TriggeredBy = Upgrade_AdvancedCountermeasures
  FlareTemplateName = AdvancedCountermeasureFlare
  FlareBoneBaseName = Countermeasure
  VolleySize = 3
  VolleyArcAngle = 90.0
  VolleyVelocityFactor = 3.0
  DelayBetweenVolleys = 500
  NumberOfVolleys = 5
  EvasionRate = 90.0
  ReloadTime = 60000
  MustReloadAtAirfield = No
  MissileDecoyDelay = 1200
  ReactionLaunchLatency = 200
End
```

### Stealth Aircraft Countermeasures
```ini
Behavior = CountermeasuresBehavior ModuleTag_StealthCountermeasures
  TriggeredBy = Upgrade_StealthCountermeasures
  ConflictsWith = Upgrade_ActiveRadar
  FlareTemplateName = StealthCountermeasureFlare
  FlareBoneBaseName = StealthFlare
  VolleySize = 4
  VolleyArcAngle = 120.0
  VolleyVelocityFactor = 1.5
  DelayBetweenVolleys = 800
  NumberOfVolleys = 2
  EvasionRate = 95.0
  ReloadTime = 0
  MustReloadAtAirfield = Yes
End
```

## Template

```ini
Behavior = CountermeasuresBehavior ModuleTag_XX
  ; Flare Configuration
  FlareTemplateName =               ; // template name of flare object *(v1.04, Generals Zero Hour only)*
  FlareBoneBaseName = Flare         ; // base name for flare launch bones *(v1.04, Generals Zero Hour only)*

  ; Volley Settings
  VolleySize = 1                    ; // number of flares per volley *(v1.04, Generals Zero Hour only)*
  VolleyArcAngle = 0.0              ; // maximum flare spread angle *(v1.04, Generals Zero Hour only)*
  VolleyVelocityFactor = 1.0        ; // flare launch velocity multiplier *(v1.04, Generals Zero Hour only)*
  NumberOfVolleys = 1               ; // total volleys before reload *(v1.04, Generals Zero Hour only)*

  ; Timing Settings
  DelayBetweenVolleys = 1000        ; // milliseconds between volleys *(v1.04, Generals Zero Hour only)*
  ReloadTime = 0                    ; // auto-reload time (0 = no auto-reload) *(v1.04, Generals Zero Hour only)*
  MissileDecoyDelay = 1000          ; // delay before missile diversion *(v1.04, Generals Zero Hour only)*
  ReactionLaunchLatency = 500       ; // delay before first volley *(v1.04, Generals Zero Hour only)*

  ; Evasion Settings
  EvasionRate = 75.0                ; // percentage chance of missile diversion *(v1.04, Generals Zero Hour only)*
  MustReloadAtAirfield = No         ; // require airfield for reloading *(v1.04, Generals Zero Hour only)*

  ; Upgrade Integration
  TriggeredBy =                     ; // required upgrade flags *(v1.04, Generals Zero Hour only)*
  ConflictsWith =                   ; // conflicting upgrade flags *(v1.04, Generals Zero Hour only)*
  RequiresAll = No                  ; // require all TriggeredBy upgrades *(v1.04, Generals Zero Hour only)*
End
```

## Notes

- CountermeasuresBehavior is exclusive to Generals Zero Hour (v1.04)
- Countermeasures only function on airborne targets
- The behavior automatically detects incoming missiles and determines evasion based on EvasionRate
- Flares are launched in volleys with configurable spread patterns and timing
- Missile diversion occurs after a delay to allow countermeasures to be deployed first
- Aircraft can auto-reload countermeasures or require landing at airfields
- The behavior integrates with the upgrade system for conditional activation
- Countermeasures are tracked individually and cleaned up when they expire
- Multiple volleys can be fired with different timing and spread patterns
- The behavior handles both reactive (threat-based) and continuous countermeasure deployment

## Source Files

**Base Class:** [`UpdateModule`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h), [`UpgradeMux`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h), [`CountermeasuresBehaviorInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CountermeasuresBehavior.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CountermeasuresBehavior.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CountermeasuresBehavior.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/CountermeasuresBehavior.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/CountermeasuresBehavior.cpp)