# RadiusDecalBehavior

## Overview

The `RadiusDecalBehavior` module creates visual radius indicators on the terrain that show various ranges and areas of effect for game objects. This module combines both `UpdateModule` and `UpgradeMux` functionality to provide dynamic, upgrade-controlled radius decals that can be activated/deactivated based on upgrade conditions.

## Usage

### Limitations
- Requires a valid `RadiusDecalTemplate` with proper texture configuration
- Decals are only visible when the upgrade is active
- Performance impact increases with the number of active decals
- Requires external texture files for visual appearance

### Conditions
- The object must have a valid `RadiusDecalTemplate` configured
- The upgrade must be active (either initially or through upgrade triggers)
- The object must not be effectively dead
- The game must be in a state where UI elements are drawn

### Dependencies
- `RadiusDecalTemplate` - Defines the visual appearance and behavior
- `UpgradeMuxData` - Controls upgrade activation/deactivation
- External texture files for decal appearance
- `TheProjectedShadowManager` - Handles actual rendering

## Properties

### `StartsActive` *(v1.04)*
- **Type**: `Bool`
- **Description**: Determines whether the radius decal is initially active when the object is created. When true, the decal appears immediately; when false, it requires an upgrade to become visible
- **Default**: `false`
- **Example**: `StartsActive = true`

### `RadiusDecal` *(v1.04)*
- **Type**: `RadiusDecalTemplate` (see [RadiusDecalTemplate documentation](../RadiusDecalTemplate.md))
- **Description**: Template that defines the visual appearance, animation, and behavior of the radius decal. Contains texture information, opacity settings, color, and visibility options
- **Default**: Empty template
- **Example**: 
  ```ini
  RadiusDecal = AttackRangeDecal
    Texture = "AttackRangeCircle"
    Style = "SHADOW_ALPHA_DECAL"
    OpacityMin = 51
    OpacityMax = 153
    OpacityThrobTime = 60
    Color = 0
    OnlyVisibleToOwningPlayer = Yes
  End
  ```

### `Radius` *(v1.04)*
- **Type**: `Real`
- **Description**: The radius of the decal in world units. This determines the size of the circular indicator displayed on the terrain. The decal will be twice this radius in diameter
- **Default**: `0.0`
- **Example**: `Radius = 50.0`

### `OpacityMin` *(v1.04)*
- **Type**: `Int`
- **Description**: Minimum opacity value for the decal when throbbing. This value is used as the lower bound for the opacity animation. Values range from 0 (completely transparent) to 255 (completely opaque). This property works in conjunction with `OpacityMax` to create a pulsing effect
- **Default**: `255`
- **Example**: `OpacityMin = 76` (30% opacity)

### `OpacityMax` *(v1.04)*
- **Type**: `Int`
- **Description**: Maximum opacity value for the decal when throbbing. This value is used as the upper bound for the opacity animation. Values range from 0 (completely transparent) to 255 (completely opaque). This property works in conjunction with `OpacityMin` to create a pulsing effect
- **Default**: `255`
- **Example**: `OpacityMax = 178` (70% opacity)

### `OpacityThrobTime` *(v1.04)*
- **Type**: `UnsignedInt`
- **Description**: Duration in logic frames for one complete opacity throbbing cycle. When set to 0, the decal uses static opacity (no throbbing). Higher values create slower throbbing effects. At 60 FPS, 60 frames = 1 second per cycle
- **Default**: `LOGICFRAMES_PER_SECOND` (60)
- **Example**: `OpacityThrobTime = 30` (0.5 second cycle)

## Examples

### Basic Attack Range Indicator
```ini
Behavior = RadiusDecalBehavior ModuleTag_AttackRange
  StartsActive = true
  Radius = 75.0
  RadiusDecal = AttackRangeDecal
    Texture = "AttackRangeCircle"
    Style = "SHADOW_ALPHA_DECAL"
    OpacityMin = 76
    OpacityMax = 178
    OpacityThrobTime = 60
    Color = 0
    OnlyVisibleToOwningPlayer = Yes
  End
  TriggeredBy = Upgrade_ShowRanges
End
```

### Upgrade-Controlled Detection Range
```ini
Behavior = RadiusDecalBehavior ModuleTag_DetectionRange
  StartsActive = false
  Radius = 100.0
  RadiusDecal = DetectionRangeDecal
    Texture = "DetectionRangeCircle"
    Style = "SHADOW_ALPHA_DECAL"
    OpacityMin = 25
    OpacityMax = 102
    OpacityThrobTime = 90
    Color = 0
    OnlyVisibleToOwningPlayer = Yes
  End
  TriggeredBy = Upgrade_AdvancedSensors
  ConflictsWith = Upgrade_StealthMode
End
```

### Build Range Indicator
```ini
Behavior = RadiusDecalBehavior ModuleTag_BuildRange
  StartsActive = true
  Radius = 25.0
  RadiusDecal = BuildRangeDecal
    Texture = "BuildRangeCircle"
    Style = "SHADOW_ALPHA_DECAL"
    OpacityMin = 102
    OpacityMax = 204
    OpacityThrobTime = 60
    Color = 0
    OnlyVisibleToOwningPlayer = Yes
  End
End
```

### Special Ability Area of Effect
```ini
Behavior = RadiusDecalBehavior ModuleTag_SpecialAbilityRange
  StartsActive = false
  Radius = 150.0
  RadiusDecal = SpecialAbilityDecal
    Texture = "SpecialAbilityCircle"
    Style = "SHADOW_ALPHA_DECAL"
    OpacityMin = 51
    OpacityMax = 153
    OpacityThrobTime = 30
    Color = 0
    OnlyVisibleToOwningPlayer = Yes
  End
  TriggeredBy = Upgrade_SpecialAbilities
  RequiresAll = No
End
```

## Template

```ini
Behavior = RadiusDecalBehavior ModuleTag_XX
  ; Activation Settings
  StartsActive = false                    ; // initially active when created *(v1.04)*
  
  ; Decal Configuration
  Radius = 0.0                           ; // radius in world units *(v1.04)*
  RadiusDecal = DecalName                ; // decal template configuration *(v1.04)*
    Texture = "TextureName"              ; // texture file name *(v1.04)*
    Style = "SHADOW_ALPHA_DECAL"         ; // shadow type *(v1.04)*
    OpacityMin = 0                       ; // minimum opacity (0-255) *(v1.04)*
    OpacityMax = 255                     ; // maximum opacity (0-255) *(v1.04)*
    OpacityThrobTime = 60                ; // pulsing speed in logic frames *(v1.04)*
    Color = 0                            ; // color (0 = use player color) *(v1.04)*
    OnlyVisibleToOwningPlayer = Yes      ; // visibility setting *(v1.04)*
  End
  
  ; Upgrade Integration (inherited from UpgradeMux)
  TriggeredBy =                          ; // required upgrade flags *(v1.04)*
  ConflictsWith =                        ; // conflicting upgrade flags *(v1.04)*
  RequiresAll = No                       ; // require all TriggeredBy upgrades *(v1.04)*
End
```

## Notes

- The decal automatically follows the object's position and updates each frame
- Opacity pulsing creates a "breathing" effect to draw attention
- Decals are automatically cleared when the object dies or the upgrade is deactivated
- The `OnlyVisibleToOwningPlayer` setting affects network synchronization
- Performance can be impacted by having many active decals simultaneously
- Texture files must be available in the game's texture directories
- The decal system integrates with the game's shadow/decals rendering system
- **Opacity values use integer scale (0-255)**, not decimal (0.0-1.0) as commonly expected
- **OpacityThrobTime uses logic frames**, not milliseconds (60 frames = 1 second at 60 FPS)

## Best Practices

- Use appropriate opacity values to ensure visibility without being overwhelming
- Consider performance implications when using multiple decals per object
- Use meaningful texture names that clearly indicate the decal's purpose
- Set appropriate throb times - too fast can be distracting, too slow may not be noticeable
- Use upgrade triggers to show decals only when relevant to the player
- Consider using different colors for different types of ranges (attack, detection, build, etc.)

## Source Files

**Base Class:** [UpdateModule](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h), [UpgradeMux](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h)

- Header: [GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RadiusDecalBehavior.h](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RadiusDecalBehavior.h) (line 56)
- Source: [GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/RadiusDecalBehavior.cpp](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/RadiusDecalBehavior.cpp) (line 40)
- Related: [GeneralsMD/Code/GameEngine/Include/GameClient/RadiusDecal.h](../../GeneralsMD/Code/GameEngine/Include/GameClient/RadiusDecal.h) (line 43)

## Changes History

- **v1.04**: Original implementation with upgrade-controlled radius decals

## Status

- **Documentation Status**: AI Generated Pending Reviews
- **Implementation Status**: Complete
- **Testing Status**: Pending
