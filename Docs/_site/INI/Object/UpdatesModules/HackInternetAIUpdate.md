# HackInternetAIUpdate

HackInternetAIUpdate provides AI update functionality for internet hacking systems.

## Overview

The `HackInternetAIUpdate` class manages AI-driven internet hacking operations that allow objects to hack internet systems and generate cash income. It handles unpacking/packing animations, cash generation timing, and experience point rewards based on the object's veterancy level. This update is commonly used by hacker units and internet-based economic buildings that generate income through hacking operations.

## Usage

Used by objects that can hack internet systems with AI-driven hacking operations. This is an **update module** that must be embedded within object definitions. Use the [Template](#template) below by copying it into your object definition. Then, customize it as needed, making sure to review any limitations, conditions, or dependencies related to its usage.

**Limitations**:
- Hacking operations are limited by unpack/pack timing constraints
- Cash generation is controlled by delay parameters and veterancy levels
- Requires proper internet connectivity and hacking permissions
- Experience rewards are limited by specified XP amounts

**Conditions**:
- HackInternetAIUpdate manages unpacking and packing animations for hacking operations
- The update generates cash at regular intervals based on veterancy level
- Cash generation timing can be adjusted for regular and fast update modes
- Experience points are awarded for successful hacking operations
- **Multiple instances behavior**: Multiple instances can coexist; each operates independently with its own timing and cash generation

**Dependencies**:
- Requires AI system integration for autonomous hacking operations
- Uses veterancy system for determining cash generation amounts
- Integrates with economy system for cash distribution

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Timing Settings](#timing-settings)
  - [Cash Generation](#cash-generation)
  - [Experience Settings](#experience-settings)
- [Examples](#examples)
- [Template](#template)
- [Notes](#notes)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
  - [Reviews (0)](#modder-reviews)

## Properties

### Timing Settings

#### `UnpackTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time required to unpack and prepare for hacking operations. Higher values create longer setup times. Lower values allow faster hacking preparation
- **Default**: `0`
- **Example**: `UnpackTime = 1667`

#### `PackTime` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Time required to pack up after hacking operations. Higher values create longer shutdown times. Lower values allow faster packing
- **Default**: `0`
- **Example**: `PackTime = 1667`

#### `PackUnpackVariationFactor` *(v1.04)*
- **Type**: `Real`
- **Description**: Random variation factor for pack/unpack timing. Higher values create more timing variation. Lower values create more consistent timing
- **Default**: `0.0`
- **Example**: `PackUnpackVariationFactor = 0.2`

### Cash Generation

#### `CashUpdateDelay` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Standard delay between cash generation cycles. Higher values generate cash less frequently. Lower values generate cash more frequently
- **Default**: `0`
- **Example**: `CashUpdateDelay = 8000`

#### `CashUpdateDelayFast` *(v1.04)*
- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Fast delay between cash generation cycles for accelerated hacking. Higher values create longer fast cycles. Lower values create shorter fast cycles
- **Default**: `0`
- **Example**: `CashUpdateDelayFast = 4000`

#### `RegularCashAmount` *(v1.04)*
- **Type**: `UnsignedInt`
- **Description**: Cash amount generated per cycle for regular veterancy units. Higher values generate more cash. Lower values generate less cash
- **Default**: `0`
- **Example**: `RegularCashAmount = 100`

#### `VeteranCashAmount` *(v1.04)*
- **Type**: `UnsignedInt`
- **Description**: Cash amount generated per cycle for veteran units. Higher values generate more cash. Lower values generate less cash
- **Default**: `0`
- **Example**: `VeteranCashAmount = 150`

#### `EliteCashAmount` *(v1.04)*
- **Type**: `UnsignedInt`
- **Description**: Cash amount generated per cycle for elite units. Higher values generate more cash. Lower values generate less cash
- **Default**: `0`
- **Example**: `EliteCashAmount = 200`

#### `HeroicCashAmount` *(v1.04)*
- **Type**: `UnsignedInt`
- **Description**: Cash amount generated per cycle for heroic units. Higher values generate more cash. Lower values generate less cash
- **Default**: `0`
- **Example**: `HeroicCashAmount = 250`

### Experience Settings

#### `XpPerCashUpdate` *(v1.04)*
- **Type**: `UnsignedInt`
- **Description**: Experience points awarded per cash generation cycle. Higher values provide more XP per cycle. Lower values provide less XP per cycle
- **Default**: `0`
- **Example**: `XpPerCashUpdate = 5`

## Examples

### Basic Hacker Post
```ini
Behavior = HackInternetAIUpdate ModuleTag_Money
  UnpackTime = 1667
  PackTime = 1667
  CashUpdateDelay = 8000
End
```

### Advanced Hacker with Multiple Veterancy Levels
```ini
Behavior = HackInternetAIUpdate ModuleTag_Advanced
  UnpackTime = 2000
  PackTime = 2000
  CashUpdateDelay = 8000
  CashUpdateDelayFast = 4000
  RegularCashAmount = 100
  VeteranCashAmount = 150
  EliteCashAmount = 200
  HeroicCashAmount = 250
  XpPerCashUpdate = 5
  PackUnpackVariationFactor = 0.2
End
```

## Template

```ini
Behavior = HackInternetAIUpdate ModuleTag_XX
  ; Timing Settings
  UnpackTime = 0                     ; // time to unpack for hacking *(v1.04)*
  PackTime = 0                       ; // time to pack after hacking *(v1.04)*
  PackUnpackVariationFactor = 0.0    ; // random variation for timing *(v1.04)*
  
  ; Cash Generation
  CashUpdateDelay = 0                ; // standard cash generation delay *(v1.04)*
  CashUpdateDelayFast = 0            ; // fast cash generation delay *(v1.04)*
  RegularCashAmount = 0              ; // cash for regular veterancy *(v1.04)*
  VeteranCashAmount = 0              ; // cash for veteran units *(v1.04)*
  EliteCashAmount = 0                ; // cash for elite units *(v1.04)*
  HeroicCashAmount = 0               ; // cash for heroic units *(v1.04)*
  
  ; Experience Settings
  XpPerCashUpdate = 0                ; // XP awarded per cash cycle *(v1.04)*
End
```

## Notes

- HackInternetAIUpdate provides AI-driven internet hacking for economic generation
- The update manages unpacking/packing animations for realistic hacking operations
- Cash generation varies based on unit veterancy level for progressive income scaling
- Experience points are awarded for successful hacking operations
- This update is commonly used by hacker units and internet-based economic buildings
- Pack/unpack variation adds randomness to timing for more realistic behavior

## Source Files

**Base Class:** [`AIUpdateInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h), [`HackInternetAIInterface`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/HackInternetAIUpdate.h)

- Header: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Module/HackInternetAIUpdate.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/HackInternetAIUpdate.h)
- Source: [`GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/HackInternetAIUpdate.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/HackInternetAIUpdate.cpp)

## Changes History

- No Changes done since 1.04

## Status

- **Documentation Status**: AI Generated Pending Reviews 
- **Last Updated**: [Current Date] by @ahmed Salah using AI

### Modder Reviews 
- No Reviews done yet