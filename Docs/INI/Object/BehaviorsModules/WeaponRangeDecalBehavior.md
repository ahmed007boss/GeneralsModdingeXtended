# WeaponRangeDecalBehavior

## Overview

The `WeaponRangeDecalBehavior` module displays visual range indicators for a weapon's minimum and maximum range. It automatically draws two circular decals on the terrain - one for the minimum range (if > 0) and one for the maximum range - based on the weapon's actual range values from the specified weapon slot.

The decals can be controlled in two ways:
1. **Command Button**: Using a `TOGGLE_RANGE_DECAL` command button that toggles the decals on/off
2. **Upgrade System**: Using the upgrade system with `TriggeredBy`, `ConflictsWith`, etc.

## Usage

This behavior is perfect for showing weapon ranges dynamically without hardcoding range values. It automatically adapts to weapon upgrades, different weapon types, and changing range values.

### Limitations
- Requires a valid weapon in the specified weapon slot
- Minimum range decal is only shown if the weapon's minimum range > 0
- Both decals follow the object's position automatically

### Conditions
- The object must have a weapon in the specified slot
- The weapon must have valid range values
- The range decal display must be activated via command button or upgrade system

### Dependencies
- Requires `RadiusDecalTemplate` configurations for both min and max range decals
- Integrates with the game's shadow/decals rendering system

### Weapon Selection Priority
The behavior uses the following priority order to determine which weapon to use for range values:
1. **`SpecificWeaponName`** (highest priority) - If set, uses the specified weapon template
2. **`UseSlavedObjectWeapon`** - If true, uses first slaved object's weapon from specified slot
3. **`WeaponSlot`** (lowest priority) - Uses own weapon from specified slot

## Properties

### `WeaponSlot` *(v1.04)*
- **Type**: `WeaponSlotType`
- **Description**: The weapon slot to use for range values. The behavior will get min/max range values from this weapon
- **Default**: `PRIMARY`
- **Example**: `WeaponSlot = PRIMARY`
- **Available Values**: 
  - `PRIMARY` - Primary weapon slot
  - `SECONDARY` - Secondary weapon slot  
  - `TERTIARY` - Tertiary weapon slot

### `UseSlavedObjectWeapon` *(v1.04)*
- **Type**: `Bool`
- **Description**: If true, the behavior will use the first slaved object's weapon instead of the master object's weapon. This is useful for objects like stinger sites that don't have weapons themselves but have slaved stinger soldiers that do
- **Default**: `FALSE`
- **Example**: `UseSlavedObjectWeapon = TRUE`
- **Available Values**:
  - `TRUE` - Use first slaved object's weapon for range values
  - `FALSE` - Use master object's own weapon for range values

### `SpecificWeaponName` *(v1.04)*
- **Type**: `AsciiString`
- **Description**: If set, the behavior will use this specific weapon template for range values, ignoring both the weapon slot and slaved object settings. This allows showing the range of any weapon regardless of what's actually equipped
- **Default**: Empty (not set)
- **Example**: `SpecificWeaponName = "StingerMissile"`
- **Available Values**: Any valid weapon template name from the game's weapon store

## WeaponSlotType Values *(v1.04)*

The `WeaponSlotType` enum defines the available weapon slots:

- **`PRIMARY`** *(v1.04)* - Primary weapon slot (first weapon)
- **`SECONDARY`** *(v1.04)* - Secondary weapon slot (second weapon)  
- **`TERTIARY`** *(v1.04)* - Tertiary weapon slot (third weapon)

### `MinRangeDecal` *(v1.04)*
- **Type**: `RadiusDecalTemplate`
- **Description**: Template configuration for the minimum range decal. This decal is only shown if the weapon's minimum range > 0. Uses the same properties as `RadiusDecalTemplate`
- **Default**: Empty template
- **Example**: 
  ```ini
  MinRangeDecal = MinRangeDecalTemplate
    Texture = "MinRangeCircle"
    Style = "SHADOW_ALPHA_DECAL"
    OpacityMin = 51
    OpacityMax = 153
    OpacityThrobTime = 60
    Color = 0
    OnlyVisibleToOwningPlayer = Yes
  End
  ```

### `MaxRangeDecal` *(v1.04)*
- **Type**: `RadiusDecalTemplate`
- **Description**: Template configuration for the maximum range decal. This decal shows the weapon's maximum range. Uses the same properties as `RadiusDecalTemplate`
- **Default**: Empty template
- **Example**: 
  ```ini
  MaxRangeDecal = MaxRangeDecalTemplate
    Texture = "MaxRangeCircle"
    Style = "SHADOW_ALPHA_DECAL"
    OpacityMin = 76
    OpacityMax = 178
    OpacityThrobTime = 60
    Color = 0
    OnlyVisibleToOwningPlayer = Yes
  End
  ```

## Examples

### Basic Weapon Range Display
```ini
Behavior = WeaponRangeDecalBehavior ModuleTag_WeaponRange
  WeaponSlot = PRIMARY
  MinRangeDecal = MinRangeDecalTemplate
    Texture = "MinRangeCircle"
    Style = "SHADOW_ALPHA_DECAL"
    OpacityMin = 51
    OpacityMax = 153
    OpacityThrobTime = 60
    Color = 0
    OnlyVisibleToOwningPlayer = Yes
  End
  MaxRangeDecal = MaxRangeDecalTemplate
    Texture = "MaxRangeCircle"
    Style = "SHADOW_ALPHA_DECAL"
    OpacityMin = 76
    OpacityMax = 178
    OpacityThrobTime = 60
    Color = 0
    OnlyVisibleToOwningPlayer = Yes
  End
End
```

### Secondary Weapon Range Display
```ini
Behavior = WeaponRangeDecalBehavior ModuleTag_SecondaryWeaponRange
  WeaponSlot = SECONDARY
  MinRangeDecal = SecondaryMinRangeDecalTemplate
    Texture = "SecondaryMinRange"
    Style = "SHADOW_ALPHA_DECAL"
    OpacityMin = 25
    OpacityMax = 102
    OpacityThrobTime = 90
    Color = 0
    OnlyVisibleToOwningPlayer = Yes
  End
  MaxRangeDecal = SecondaryMaxRangeDecalTemplate
    Texture = "SecondaryMaxRange"
    Style = "SHADOW_ALPHA_DECAL"
    OpacityMin = 102
    OpacityMax = 204
    OpacityThrobTime = 90
    Color = 0
    OnlyVisibleToOwningPlayer = Yes
  End
  TriggeredBy = Upgrade_ShowSecondaryRanges
End
```

### Artillery Range Display
```ini
Behavior = WeaponRangeDecalBehavior ModuleTag_ArtilleryRange
  WeaponSlot = PRIMARY
  MinRangeDecal = ArtilleryMinRangeDecalTemplate
    Texture = "ArtilleryMinRange"
    Style = "SHADOW_ALPHA_DECAL"
    OpacityMin = 38
    OpacityMax = 128
    OpacityThrobTime = 120
    Color = 0
    OnlyVisibleToOwningPlayer = Yes
  End
  MaxRangeDecal = ArtilleryMaxRangeDecalTemplate
    Texture = "ArtilleryMaxRange"
    Style = "SHADOW_ALPHA_DECAL"
    OpacityMin = 64
    OpacityMax = 192
    OpacityThrobTime = 120
    Color = 0
    OnlyVisibleToOwningPlayer = Yes
  End
  TriggeredBy = Upgrade_ArtilleryMode
  ConflictsWith = Upgrade_CloseCombatMode
End
```

## Template

```ini
Behavior = WeaponRangeDecalBehavior ModuleTag_XX
  ; Basic Settings
  WeaponSlot = PRIMARY                    ; // weapon slot to use (PRIMARY, SECONDARY, TERTIARY) *(v1.04)*
  UseSlavedObjectWeapon = FALSE           ; // use first slaved object's weapon instead of own weapon *(v1.04)*
  SpecificWeaponName = ""                 ; // specific weapon template name (overrides slot and slaved settings) *(v1.04)*
  
  ; Minimum Range Decal Configuration
  MinRangeDecal = MinRangeDecalTemplate   ; // minimum range decal template *(v1.04)*
    Texture = "MinRangeTexture"           ; // texture file name *(v1.04)*
    Style = "SHADOW_ALPHA_DECAL"         ; // shadow type *(v1.04)*
    OpacityMin = 0                       ; // minimum opacity (0-255) *(v1.04)*
    OpacityMax = 255                     ; // maximum opacity (0-255) *(v1.04)*
    OpacityThrobTime = 60                ; // pulsing speed in logic frames *(v1.04)*
    Color = 0                            ; // color (0 = use player color) *(v1.04)*
    OnlyVisibleToOwningPlayer = Yes      ; // visibility setting *(v1.04)*
  End
  
  ; Maximum Range Decal Configuration
  MaxRangeDecal = MaxRangeDecalTemplate   ; // maximum range decal template *(v1.04)*
    Texture = "MaxRangeTexture"           ; // texture file name *(v1.04)*
    Style = "SHADOW_ALPHA_DECAL"         ; // shadow type *(v1.04)*
    OpacityMin = 0                       ; // minimum opacity (0-255) *(v1.04)*
    OpacityMax = 255                     ; // maximum opacity (0-255) *(v1.04)*
    OpacityThrobTime = 60                ; // pulsing speed in logic frames *(v1.04)*
    Color = 0                            ; // color (0 = use player color) *(v1.04)*
    OnlyVisibleToOwningPlayer = Yes      ; // visibility setting *(v1.04)*
  End
  
  ; Upgrade Integration (inherited from UpgradeMux)
  TriggeredBy = Upgrade_ShowRanges       ; // upgrade that activates this behavior *(v1.04)*
  ConflictsWith = Upgrade_HideRanges     ; // upgrade that conflicts with this behavior *(v1.04)*
  RequiresAll = No                       ; // whether all triggers must be active *(v1.04)*
End
```

## Controlling Range Decals

The range decals can be controlled for different weapon slots:

- **`PRIMARY`** - Shows range decals for primary weapon slot
- **`SECONDARY`** - Shows range decals for secondary weapon slot  
- **`TERTIARY`** - Shows range decals for tertiary weapon slot


By default, no range decals are shown until activated.

### Command Button Control

You can create a command button to toggle range decals:

```ini
CommandButton = Command_TogglePrimaryRange
  Command = TOGGLE_RANGE_DECAL
  WeaponSlot = PRIMARY
  TextLabel = "TOGGLE:Show Primary Weapon Range"
  ButtonImage = "iRangePrimary"
  ButtonBorder = "BORDER_BUTTON_STANDARD"
  DescriptLabel = "TOGGLE:Show Primary Weapon Range"
  ToolTip = "TOOLTIP:Toggle Primary Weapon Range Display"
End
```

### Upgrade System Control

You can also use the upgrade system to control when decals are shown:

```ini
Behavior = WeaponRangeDecalBehavior ModuleTag_PrimaryRange
  WeaponSlot = PRIMARY
  TriggeredBy = Upgrade_ShowRanges
  ConflictsWith = Upgrade_HideRanges
  MinRangeDecal = MinRangeDecalTemplate
    Texture = "MinRangeCircle"
    Style = "SHADOW_ALPHA_DECAL"
    OpacityMin = 51
    OpacityMax = 153
    OpacityThrobTime = 60
    Color = 0
    OnlyVisibleToOwningPlayer = Yes
  End
  MaxRangeDecal = MaxRangeDecalTemplate
    Texture = "MaxRangeCircle"
    Style = "SHADOW_ALPHA_DECAL"
    OpacityMin = 76
    OpacityMax = 178
    OpacityThrobTime = 60
    Color = 0
    OnlyVisibleToOwningPlayer = Yes
  End
End
```

### How It Works
The system automatically manages the range decal display based on the object's internal state. When a command button is clicked or an upgrade is triggered, the system will:

1. Check if the range decal state equals the module's weapon slot
2. Show decals if the state matches, hide them if it's -1 or different
3. Update the display in real-time as the object moves or changes state

This provides seamless integration with the game's existing command and upgrade systems.

## Automatic Color Assignment

When the `Color` property is not set in the INI (default value of 0), the system automatically assigns colors based on weapon capabilities:

### Minimum Range Decal
- **Red** (`0xFF0000`) - Always red for minimum range indicators

### Maximum Range Decal
- **Grey** (`0x808080`) - Ground-only weapons (`AntiGround = Yes`)
- **Cyan** (`0x00FFFF`) - Air-only weapons (`AntiAirborneVehicle = Yes` or `AntiAirborneInfantry = Yes`)
- **Green** (`0x00FF00`) - Weapons that can attack both air and ground (both `AntiGround` and air properties)
- **Purple** (`0x800080`) - Weapons that don't do health damage (status effects, etc.)

### Custom Colors
To override automatic colors, set the `Color` property in the INI to any RGB value (e.g., `Color = 0xFF0000` for red).

## Notes

- The decals automatically follow the object's position and update each frame
- Minimum range decal is only created if the weapon's minimum range > 0
- Maximum range decal is always created if the weapon has a valid maximum range
- Both decals are automatically cleared when the object dies or the slot doesn't match
- The `OnlyVisibleToOwningPlayer` setting affects network synchronization
- Performance can be impacted by having many active decals simultaneously
- Texture files must be available in the game's texture directories
- The decal system integrates with the game's shadow/decals rendering system
- **Opacity values use integer scale (0-255)**, not decimal (0.0-1.0) as commonly expected
- **OpacityThrobTime uses logic frames**, not milliseconds (60 frames = 1 second at 60 FPS)
- Weapon slots use named constants: PRIMARY, SECONDARY, TERTIARY
- **Automatic color assignment** provides intuitive visual feedback based on weapon capabilities

## Best Practices

- Use different textures for min and max range decals to distinguish them visually
- Set appropriate opacity values to ensure visibility without being overwhelming
- Consider performance implications when using multiple decals per object
- Use different throbbing speeds for min/max decals to create visual distinction
- Test with different weapon types to ensure proper range detection
- Use upgrade system to control when range indicators are shown

## Source Files

**Base Class:** [UpdateModule](../../Core/GameEngine/Include/GameLogic/Module/UpdateModule.h), [UpgradeMux](../../Core/GameEngine/Include/GameLogic/Module/UpgradeModule.h)

- **Header**: [WeaponRangeDecalBehavior.h](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/WeaponRangeDecalBehavior.h)
- **Implementation**: [WeaponRangeDecalBehavior.cpp](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/WeaponRangeDecalBehavior.cpp)

## Changes History

- **v1.04**: Initial implementation of WeaponRangeDecalBehavior
- **GMX Upcoming**: Added dynamic weapon range detection and dual decal support
