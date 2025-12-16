# GameData INI Documentation

Status: AI-generated, 0/2 reviews

## Overview

GameData is a one-per-game global configuration block that defines core game data settings and parameters for fundamental game systems. This includes rendering settings, camera controls, terrain configuration, lighting, audio, network settings, weapon bonuses, veterancy bonuses, and many other global gameplay parameters that affect the entire game experience.

Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

The GameData block is loaded from `Data\INI\Default\GameData` (default values) and `Data\INI\GameData` (user overrides) directories. Only one GameData block exists per game instance, and it affects all objects, weapons, special powers, and game systems globally.

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
  - [Display and Rendering Settings](#display-and-rendering-settings)
  - [Terrain Settings](#terrain-settings)
  - [Water Settings](#water-settings)
  - [Camera Settings](#camera-settings)
  - [Lighting Settings](#lighting-settings)
  - [Audio Settings](#audio-settings)
  - [Gameplay Settings](#gameplay-settings)
  - [Weapon and Veterancy Bonuses](#weapon-and-veterancy-bonuses)
  - [Network Settings](#network-settings)
  - [Debug Settings](#debug-settings)
- [Enum Value Lists](#enum-value-lists)
- [Template](#template)
- [Notes](#notes)
- [Modder Recommended Use Scenarios](#modder-recommended-use-scenarios)
- [Source Files](#source-files)
- [Changes History](#changes-history)
- [Status](#status)
- [Reviewers](#reviewers)
- [Document Log](#document-log)

## Usage

The GameData block is a one-per-game global configuration block. Only one GameData block can exist per game instance. The block is defined in INI files within the `Data\INI\Default\GameData` directory (for default values) and `Data\INI\GameData` directory (for user overrides). See [Template](#template) for correct syntax.

**Limitations**:
- Only one GameData block exists per game instance. Multiple GameData blocks in INI files will overwrite each other, with later-loaded files taking precedence.
- Some properties are only available in debug builds (marked with `#if defined(RTS_DEBUG)` in the source code) and will be ignored in release builds.

**Conditions**:
- Properties in the GameData block affect all game systems globally. Changes to properties like `UnitDamagedThreshold` affect all objects that use damage states.
- Default values are loaded first from `Data\INI\Default\GameData`, then user overrides are loaded from `Data\INI\GameData`, with user overrides taking precedence.

**Dependencies**:
- GameData affects all game systems, including [Object](Object.md) damage states, [Weapon](Weapon.md) bonuses, and special power systems. Many properties reference other game systems but do not require them to exist.

## Properties

### Display and Rendering Settings

#### `Windowed`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether the game runs in windowed mode instead of fullscreen. When set to `Yes`, the game runs in a window that can be resized and moved. When set to `No`, the game runs in fullscreen mode. Windowed mode is useful for debugging, streaming, or multitasking, but may have slightly different performance characteristics than fullscreen mode.
- **Default**: `No` (0)
- **Example**: `Windowed = No`

#### `XResolution`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Int`
- **Description**: Horizontal screen resolution in pixels for the game window or fullscreen display. This sets the width of the game's rendering area. Higher values provide more horizontal screen space but may impact performance. The resolution must be supported by the graphics hardware and driver.
- **Default**: `DEFAULT_DISPLAY_WIDTH` (typically 1024)
- **Example**: `XResolution = 1920`

#### `YResolution`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Int`
- **Description**: Vertical screen resolution in pixels for the game window or fullscreen display. This sets the height of the game's rendering area. Higher values provide more vertical screen space but may impact performance. The resolution must be supported by the graphics hardware and driver.
- **Default**: `DEFAULT_DISPLAY_HEIGHT` (typically 768)
- **Example**: `YResolution = 1080`

#### `ViewportHeightScale`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Scaling factor applied to the viewport height for rendering calculations. This affects how the game scales its rendering output relative to the screen resolution. Values greater than 1.0 increase the effective viewport height, while values less than 1.0 decrease it. This can be used to adjust the field of view or aspect ratio scaling.
- **Default**: `1.0`
- **Example**: `ViewportHeightScale = 1.0`

#### `UseFPSLimit`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether to enable frame rate limiting. When set to `Yes`, the game limits its frame rate to the value specified in [`FramesPerSecondLimit`](#framespersecondlimit). When set to `No`, the game runs at the maximum frame rate possible, which may cause high CPU/GPU usage and inconsistent performance. Frame rate limiting is useful for reducing power consumption, heat generation, and ensuring consistent performance.
- **Default**: `No` (FALSE)
- **Example**: `UseFPSLimit = Yes`

#### `FramesPerSecondLimit`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Int`
- **Description**: Maximum frame rate in frames per second when [`UseFPSLimit`](#usefpslimit) is enabled. The game will not exceed this frame rate, capping performance to reduce CPU/GPU usage. Common values are 30, 60, or 120 FPS. Lower values reduce system resource usage but may make the game feel less responsive. This property only has an effect when [`UseFPSLimit`](#usefpslimit) is set to `Yes`.
- **Default**: `0` (unlimited when FPS limit is disabled)
- **Example**: `FramesPerSecondLimit = 60`

#### `ChipsetType`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Int`
- **Description**: Graphics chipset type identifier used for shader and rendering path selection. This value determines which rendering features and shader paths are available. Different chipset types may have different capabilities, and the game may select different rendering techniques based on this value. See `W3DShaderManager::ChipsetType` for available options.
- **Default**: `0`
- **Example**: `ChipsetType = 0`

#### `MaxShellScreens`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Int`
- **Description**: Maximum number of shell (menu) screen layouts that can be loaded simultaneously. Shell screens are the menu and interface screens outside of gameplay. This limits memory usage by capping how many shell layouts are kept in memory at once. Higher values allow more shell screens to be preloaded but use more memory.
- **Default**: `0`
- **Example**: `MaxShellScreens = 8`

#### `ShellMapName`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `AsciiString`
- **Description**: Filename of the background texture image used for shell (menu) screens. This texture is displayed behind menu interfaces and provides the visual backdrop for the main menu, options screens, and other non-gameplay interfaces. The file must be a valid texture format supported by the game engine.
- **Default**: Empty string
- **Example**: `ShellMapName = mainmenubackdropuserinterface.tga`

#### `ShellMapOn`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether to display the shell map background texture on menu screens. When set to `Yes`, the texture specified in [`ShellMapName`](#shellmapname) is displayed as the background for shell screens. When set to `No`, shell screens use a default or no background. This allows disabling the shell map for performance or visual reasons.
- **Default**: `No` (FALSE)
- **Example**: `ShellMapOn = Yes`

#### `MapName`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `AsciiString`
- **Description**: Default map filename to load when starting the game. This is a temporary hack for map loading and may be overridden by other game systems. The map file must exist in the game's map directory and be a valid map format.
- **Default**: Empty string
- **Example**: `MapName = Assault.map`

#### `MoveHintName`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `AsciiString`
- **Description**: Name of the move hint system to use for pathfinding and movement visualization. Move hints provide visual or logical guidance for unit movement and pathfinding calculations. This property specifies which move hint configuration to use.
- **Default**: Empty string
- **Example**: `MoveHintName = SCMoveHint`

#### `DumpAssetUsage`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether to dump asset usage statistics to log files or console output. When set to `Yes`, the game tracks and outputs information about which assets (textures, models, sounds, etc.) are being used, how frequently they are accessed, and memory usage statistics. This is useful for performance analysis and identifying unused or overused assets. Asset usage dumps may impact performance slightly due to tracking overhead.
- **Default**: `No` (FALSE)
- **Example**: `DumpAssetUsage = No`

#### `UseTrees`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether to render trees and vegetation on the terrain. When set to `Yes`, trees and other vegetation objects are displayed on the map. When set to `No`, vegetation is not rendered, which can improve performance on lower-end systems but reduces visual detail and immersion.
- **Default**: `No` (0)
- **Example**: `UseTrees = Yes`

### Terrain Settings

#### `UseCloudMap`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether to use cloud map textures for terrain rendering. Cloud maps provide additional texture detail and visual variation to the terrain. When set to `Yes`, cloud map textures are applied to enhance terrain appearance. When set to `No`, cloud maps are not used, which may reduce visual quality but can improve performance.
- **Default**: `No` (FALSE)
- **Example**: `UseCloudMap = Yes`

#### `UseLightMap`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether to use light maps for terrain lighting. Light maps provide pre-calculated lighting information that enhances the visual quality of terrain by adding realistic shadows and lighting effects. When set to `Yes`, light maps are applied to terrain. When set to `No`, light maps are not used, which may reduce visual quality but can improve performance and reduce memory usage.
- **Default**: `No` (FALSE)
- **Example**: `UseLightMap = Yes`

#### `BilinearTerrainTex`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether to use bilinear filtering for terrain textures. Bilinear filtering smooths texture pixels when textures are scaled or viewed at angles, reducing pixelation and improving visual quality at the cost of slight blurring. When set to `Yes`, bilinear filtering is applied to terrain textures. When set to `No`, nearest-neighbor filtering is used, which may appear more pixelated but can be faster.
- **Default**: `No` (FALSE)
- **Example**: `BilinearTerrainTex = Yes`

#### `TrilinearTerrainTex`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether to use trilinear filtering for terrain textures. Trilinear filtering provides smoother texture transitions between mipmap levels compared to bilinear filtering, resulting in better visual quality especially when textures are viewed at various distances. When set to `Yes`, trilinear filtering is applied to terrain textures. When set to `No`, bilinear or nearest-neighbor filtering is used. Trilinear filtering may have a slight performance cost compared to bilinear filtering.
- **Default**: `No` (FALSE)
- **Example**: `TrilinearTerrainTex = Yes`

#### `MultiPassTerrain`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether to use multi-pass rendering for terrain. Multi-pass terrain rendering allows for more complex visual effects and better blending of terrain textures by rendering the terrain in multiple passes. When set to `Yes`, terrain is rendered using multiple passes, which can improve visual quality but may impact performance. When set to `No`, terrain is rendered in a single pass, which is faster but may have reduced visual quality.
- **Default**: `No` (FALSE)
- **Example**: `MultiPassTerrain = Yes`

#### `AdjustCliffTextures`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether to automatically adjust cliff textures based on terrain geometry. When set to `Yes`, the game automatically adjusts cliff and vertical surface textures to better match the terrain's geometry and orientation. When set to `No`, cliff textures are not automatically adjusted. This can improve visual consistency of cliffs and steep terrain features.
- **Default**: `No` (FALSE)
- **Example**: `AdjustCliffTextures = Yes`

#### `StretchTerrain`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether to stretch terrain textures to fit the terrain geometry. When set to `Yes`, terrain textures are stretched to match the terrain's shape, which can improve texture coverage but may cause distortion. When set to `No`, terrain textures maintain their aspect ratio, which may leave gaps but preserves texture quality.
- **Default**: `No` (FALSE)
- **Example**: `StretchTerrain = No`

#### `UseHalfHeightMap`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether to use half-resolution height maps for terrain geometry. When set to `Yes`, the terrain uses height maps at half the normal resolution, which reduces memory usage and can improve performance but may reduce terrain detail and smoothness. When set to `No`, full-resolution height maps are used for maximum terrain detail.
- **Default**: `No` (FALSE)
- **Example**: `UseHalfHeightMap = No`

#### `DrawEntireTerrain`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether to draw the entire terrain regardless of visibility or camera position. When set to `Yes`, the entire terrain is rendered even if parts are outside the camera's view, which ensures complete terrain coverage but may impact performance. When set to `No`, only visible portions of the terrain are rendered, which improves performance but may cause issues with certain rendering techniques.
- **Default**: `No` (FALSE)
- **Example**: `DrawEntireTerrain = Yes`

#### `TerrainLOD`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `TerrainLOD` (see [TerrainLOD Values](#terrainlod-values))
- **Description**: Level of detail (LOD) setting for terrain rendering. This controls how the terrain's level of detail is managed, affecting the balance between visual quality and performance. Different LOD modes adjust terrain detail based on distance, camera position, or disable LOD entirely. See the [TerrainLOD Values](#terrainlod-values) section for available options.
- **Default**: `TERRAIN_LOD_AUTOMATIC`
- **Example**: `TerrainLOD = DISABLE`
- **Available Values**: See [TerrainLOD Values](#terrainlod-values) section below

#### `TerrainLODTargetTimeMS`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Int` (milliseconds)
- **Description**: Target frame time in milliseconds for terrain LOD calculations when automatic LOD is enabled. This value helps the LOD system determine how aggressively to reduce terrain detail to maintain performance. Lower values cause more aggressive LOD reduction to meet the target frame time, while higher values allow more detail. This property only has an effect when [`TerrainLOD`](#terrainlod) is set to automatic mode.
- **Default**: `0`
- **Example**: `TerrainLODTargetTimeMS = 45`

#### `TextureReductionFactor`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Int`
- **Description**: Factor by which to reduce texture resolution. This value determines how much texture resolution is reduced to save memory and improve performance. A value of 0 means no reduction (full resolution), 1 means half resolution, 2 means quarter resolution, and so on. Higher values reduce texture quality more significantly but save more memory and can improve performance. Negative values disable texture reduction.
- **Default**: `-1` (disabled)
- **Example**: `TextureReductionFactor = 0`

#### `Use3WayTerrainBlends`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Int`
- **Description**: Whether to use 3-way terrain texture blending. This controls how terrain textures blend together at boundaries. A value of 0 disables 3-way blending, 1 enables normal 3-way blending for improved texture transitions, and 2 enables debug mode for 3-way blending. 3-way blending provides smoother and more natural transitions between different terrain textures compared to simple 2-way blending.
- **Default**: `1` (normal)
- **Example**: `Use3WayTerrainBlends = 1`

#### `ShowObjectHealth`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether to display health bars above objects. When set to `Yes`, health bars are shown above all objects that have health, providing visual feedback about their current health status. When set to `No`, health bars are not displayed, which reduces visual clutter but makes it harder to assess unit health at a glance.
- **Default**: `No` (FALSE)
- **Example**: `ShowObjectHealth = Yes`

#### `HideGarrisonFlags`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether to hide garrison flags that indicate when buildings or structures are garrisoned. When set to `Yes`, garrison flags are not displayed, reducing visual clutter. When set to `No`, garrison flags are shown above garrisoned structures to indicate their garrisoned status.
- **Default**: `No` (FALSE)
- **Example**: `HideGarrisonFlags = No`

#### `UseBehindBuildingMarker`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether to display markers behind buildings to indicate when units or objects are positioned behind structures. When set to `Yes`, markers are shown to help players identify objects that are behind buildings and may be partially or fully obscured. When set to `No`, these markers are not displayed.
- **Default**: `Yes` (TRUE)
- **Example**: `UseBehindBuildingMarker = Yes`

#### `DefaultOcclusionDelay`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Default delay in milliseconds before objects are occluded (hidden) when they are behind other objects or terrain. This delay prevents objects from flickering in and out of view when they are briefly occluded. Higher values keep objects visible longer when occluded, reducing flicker but potentially showing objects that should be hidden. Lower values hide objects more quickly when occluded, improving visual accuracy but potentially causing more flicker.
- **Default**: `3000`
- **Example**: `DefaultOcclusionDelay = 3000`

#### `OccludedColorLuminanceScale`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Scaling factor applied to the luminance (brightness) of occluded objects. This affects how bright or dark objects appear when they are behind other objects or terrain. Values less than 1.0 make occluded objects darker, while values greater than 1.0 make them brighter. A value of 0.5 makes occluded objects appear at half brightness, helping to distinguish them from fully visible objects.
- **Default**: `0.5`
- **Example**: `OccludedColorLuminanceScale = 0.5`

#### `RightMouseAlwaysScrolls`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether the right mouse button always scrolls the camera, regardless of context. When set to `Yes`, right-clicking always moves the camera, even when clicking on units or objects. When set to `No`, right-clicking may perform other actions (such as selecting or commanding units) depending on what is clicked, and camera scrolling requires dragging or using other controls.
- **Default**: `No` (FALSE)
- **Example**: `RightMouseAlwaysScrolls = Yes`

### Water Settings

#### `UseWaterPlane`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether to use a water plane for water rendering. When set to `Yes`, a flat water plane is rendered at the water level, providing a simple water surface. When set to `No`, water plane rendering is disabled. The water plane provides basic water visualization and can be combined with other water rendering techniques.
- **Default**: `No` (FALSE)
- **Example**: `UseWaterPlane = Yes`

#### `UseCloudPlane`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether to use a cloud plane for sky rendering. When set to `Yes`, a cloud plane is rendered in the sky to provide cloud visualization. When set to `No`, cloud plane rendering is disabled. Cloud planes provide simple sky and cloud effects.
- **Default**: `No` (FALSE)
- **Example**: `UseCloudPlane = Yes`

#### `DownwindAngle`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real` (radians)
- **Description**: Angle in radians that defines the downwind direction for particle effects and environmental systems. This angle determines the direction that wind-blown particles (such as smoke, fire, and other environmental effects) move. The angle is measured in radians, with 0 being east, positive values rotating counterclockwise. A value of -0.785 radians corresponds to northeast direction.
- **Default**: `-0.785` (northeast)
- **Example**: `DownwindAngle = -0.785`

#### `WaterPositionX`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: X coordinate (horizontal position) of the water plane center in world space. This defines where the water plane is positioned horizontally on the map. The water plane extends from this center position based on [`WaterExtentX`](#waterextentx) and [`WaterExtentY`](#waterextenty).
- **Default**: `0.0`
- **Example**: `WaterPositionX = 0.0`

#### `WaterPositionY`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Y coordinate (depth position) of the water plane center in world space. This defines where the water plane is positioned in the Y dimension on the map. The water plane extends from this center position based on [`WaterExtentX`](#waterextentx) and [`WaterExtentY`](#waterextenty).
- **Default**: `0.0`
- **Example**: `WaterPositionY = 0.0`

#### `WaterPositionZ`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Z coordinate (vertical height) of the water plane surface in world space. This defines the water level height. Objects below this Z coordinate are considered underwater, while objects above are above water. This is the primary property that controls the water level on the map.
- **Default**: `0.0`
- **Example**: `WaterPositionZ = 7.0`

#### `WaterExtentX`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Horizontal extent (width) of the water plane in world space units. This defines how far the water plane extends horizontally from its center position ([`WaterPositionX`](#waterpositionx)). The water plane covers an area from `WaterPositionX - WaterExtentX/2` to `WaterPositionX + WaterExtentX/2`.
- **Default**: `0.0`
- **Example**: `WaterExtentX = 2000.0`

#### `WaterExtentY`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Depth extent (length) of the water plane in world space units. This defines how far the water plane extends in the Y dimension from its center position ([`WaterPositionY`](#waterpositiony)). The water plane covers an area from `WaterPositionY - WaterExtentY/2` to `WaterPositionY + WaterExtentY/2`.
- **Default**: `0.0`
- **Example**: `WaterExtentY = 2000.0`

#### `WaterType`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Int`
- **Description**: Type identifier for water rendering style or behavior. This value selects which water rendering technique or visual style is used. Different water types may have different visual appearances, animation styles, or interaction behaviors. The specific meaning of each value depends on the water rendering system implementation.
- **Default**: `0`
- **Example**: `WaterType = 0`

#### `FeatherWater`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Int`
- **Description**: Whether to apply feathering (soft edges) to water boundaries. Feathering creates smooth transitions at water edges, making them appear more natural and less harsh. When set to a non-zero value, water edges are feathered. When set to 0, water edges are sharp. Higher values may create more pronounced feathering effects.
- **Default**: `0` (FALSE)
- **Example**: `FeatherWater = 0`

#### `ShowSoftWaterEdge`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether to display soft (feathered) edges for water boundaries. When set to `Yes`, water edges are rendered with soft, feathered transitions that create a more natural appearance. When set to `No`, water edges are rendered with sharp, hard boundaries. Soft water edges improve visual quality but may have a slight performance cost.
- **Default**: `Yes` (TRUE)
- **Example**: `ShowSoftWaterEdge = Yes`

#### `DefaultStructureRubbleHeight`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Default Z height (vertical position) for structure rubble when a structure is destroyed and reduced to rubble. If a structure's rubble height is not explicitly specified, this default value is used. This ensures that rubble appears at an appropriate height above or below the terrain. The rubble height is set relative to the terrain or structure's original position.
- **Default**: `10.0`
- **Example**: `DefaultStructureRubbleHeight = 10.0`

### Camera Settings

#### `CameraPitch`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real` (degrees)
- **Description**: Default pitch angle (vertical rotation) of the camera in degrees. This sets the initial vertical angle at which the camera views the game world. Positive values tilt the camera downward (looking down at the terrain), while negative values tilt it upward (looking up at the sky). This affects the default viewing angle when the game starts or when the camera resets.
- **Default**: `37.5`
- **Example**: `CameraPitch = 37.5`

#### `CameraYaw`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real` (degrees)
- **Description**: Default yaw angle (horizontal rotation) of the camera in degrees. This sets the initial horizontal direction the camera faces. A value of 0 typically faces north or a default direction, with positive values rotating clockwise and negative values rotating counterclockwise. This affects the default viewing direction when the game starts or when the camera resets.
- **Default**: `0.0`
- **Example**: `CameraYaw = 0.0`

#### `CameraHeight`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Default height of the camera above the terrain in world space units. This sets the initial vertical position of the camera. Higher values position the camera further above the terrain, providing a more zoomed-out view. Lower values position the camera closer to the terrain, providing a more zoomed-in view. The camera height is constrained by [`MinCameraHeight`](#mincameraheight) and [`MaxCameraHeight`](#maxcameraheight).
- **Default**: `400`
- **Example**: `CameraHeight = 400`

#### `MinCameraHeight`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Minimum allowed camera height above the terrain in world space units. The camera cannot be positioned below this height, preventing it from going too close to the ground. This sets the lower limit for camera zoom-in. Lower values allow the camera to get closer to the terrain, while higher values prevent close-up views.
- **Default**: `50`
- **Example**: `MinCameraHeight = 50`

#### `MaxCameraHeight`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Maximum allowed camera height above the terrain in world space units. The camera cannot be positioned above this height, preventing it from zooming out too far. This sets the upper limit for camera zoom-out. Higher values allow the camera to zoom out further, providing a wider view of the battlefield, while lower values limit the maximum zoom-out distance.
- **Default**: `690.0`
- **Example**: `MaxCameraHeight = 690.0`

#### `CameraAdjustSpeed`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real` (0.0 to 1.0)
- **Description**: Speed at which the camera adjusts to the desired height when scrolling or zooming. This value controls how quickly the camera snaps to the target height, with 0.0 being instant and 1.0 being very slow. Values between 0 and 1 provide smooth transitions: lower values (closer to 0) make the camera adjust more quickly, while higher values (closer to 1) make it adjust more slowly and smoothly. This affects the responsiveness and smoothness of camera height changes.
- **Default**: `0.3`
- **Example**: `CameraAdjustSpeed = 0.3`

#### `ScrollAmountCutoff`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Threshold value in arbitrary units above which camera height is not updated while scrolling. When the scroll amount exceeds this value, the camera height adjustment is paused to prevent unwanted height changes during rapid scrolling. This helps maintain camera stability when the player is quickly panning the camera. Lower values make the camera more sensitive to scroll input, while higher values require more scroll input before height adjustment is disabled.
- **Default**: `50.0`
- **Example**: `ScrollAmountCutoff = 50.0`

#### `EnforceMaxCameraHeight`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether to enforce the maximum camera height limit while scrolling. When set to `Yes`, the camera is prevented from exceeding [`MaxCameraHeight`](#maxcameraheight) even during scrolling operations. When set to `No`, the camera may temporarily exceed the maximum height during scrolling, allowing more flexible camera movement but potentially causing the camera to go too high.
- **Default**: `No` (FALSE)
- **Example**: `EnforceMaxCameraHeight = No`

#### `TerrainHeightAtEdgeOfMap`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Z height (vertical position) of the terrain at the edges of the map in world space units. This defines the height of the terrain boundary or map edge. This value is used for terrain rendering and collision detection at map boundaries, ensuring consistent terrain height at the edges of the playable area.
- **Default**: `100.0`
- **Example**: `TerrainHeightAtEdgeOfMap = 100.0`

#### `HorizontalScrollSpeedFactor`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Multiplier factor applied to the maximum horizontal (left-right) camera scroll speed. This controls how fast the camera can pan horizontally when using right mouse button scrolling or keyboard controls. Higher values allow faster horizontal scrolling, making camera movement more responsive. Lower values slow down horizontal scrolling, making camera movement more controlled. This factor is applied to account for aspect ratio and screen dimensions.
- **Default**: `1.0`
- **Example**: `HorizontalScrollSpeedFactor = 1.6`

#### `VerticalScrollSpeedFactor`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Multiplier factor applied to the maximum vertical (forward-backward) camera scroll speed. This controls how fast the camera can pan vertically when using right mouse button scrolling or keyboard controls. Higher values allow faster vertical scrolling, making camera movement more responsive. Lower values slow down vertical scrolling, making camera movement more controlled. This factor is split from horizontal scrolling to account for aspect ratio induced speed limits and provide room for mouse drag.
- **Default**: `1.0`
- **Example**: `VerticalScrollSpeedFactor = 2.0`

#### `KeyboardScrollSpeedFactor`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Multiplier factor applied to the maximum camera scroll speed when using keyboard controls (arrow keys, WASD, etc.). This controls how fast the camera moves when using keyboard input for camera panning. Higher values allow faster keyboard scrolling, making camera movement more responsive. Lower values slow down keyboard scrolling, making camera movement more controlled. This is separate from mouse scroll speed factors to allow independent control of keyboard and mouse camera movement speeds.
- **Default**: `2.0`
- **Example**: `KeyboardScrollSpeedFactor = 2.0`

#### `KeyboardDefaultScrollSpeedFactor`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Default multiplier factor for keyboard camera scrolling speed. This provides a baseline scroll speed for keyboard camera controls that can be adjusted by the player or other systems. This value is used as the default when no other scroll speed factor is specified or when resetting scroll speed settings.
- **Default**: *(needs verification from constructor)*
- **Example**: `KeyboardDefaultScrollSpeedFactor = 1.0`

#### `KeyboardCameraRotateSpeed`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Speed at which the camera rotates when using keyboard rotation controls. This controls how fast the camera rotates around its axis when keyboard rotation keys are pressed. Higher values make the camera rotate faster, providing more responsive rotation. Lower values make the camera rotate slower, providing more controlled and precise rotation.
- **Default**: `0.1`
- **Example**: `KeyboardCameraRotateSpeed = 0.1`

#### `DrawSkyBox`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether to render the skybox (background sky texture) behind the game world. When set to `Yes`, a skybox is rendered to provide a sky background, enhancing the visual environment. When set to `No`, the skybox is not rendered, which may improve performance but leaves the background empty or uses a default color.
- **Default**: `No` (FALSE)
- **Example**: `DrawSkyBox = Yes`

#### `SkyBoxPositionZ`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Z coordinate (vertical position) offset for the skybox center. This value lowers or raises the center of the skybox relative to the terrain. Negative values lower the skybox center below the terrain, which can help position the skybox correctly relative to the camera view. This is useful for adjusting the skybox position to match the camera's viewing angle and terrain height.
- **Default**: `0.0`
- **Example**: `SkyBoxPositionZ = -100.0`

#### `SkyBoxScale`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Scaling factor for the skybox size. This controls how large the skybox appears relative to the game world. Higher values make the skybox larger, which is useful for larger maps. Lower values make the skybox smaller, which is useful for smaller maps. A value of 8.4 is good for default 96x96 maps, while 17.5 is better for 256x256 maps. The scale should be adjusted to match the map size to ensure the skybox covers the entire visible area.
- **Default**: `4.5`
- **Example**: `SkyBoxScale = 8.4`

### Lighting Settings

#### `UseShadowVolumes`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether to use shadow volumes for dynamic shadow rendering. Shadow volumes create realistic shadows cast by objects onto the terrain and other objects. When set to `Yes`, shadow volumes are rendered, providing dynamic shadow effects that enhance visual realism. When set to `No`, shadow volumes are not rendered, which improves performance but removes dynamic shadow effects.
- **Default**: `No` (FALSE)
- **Example**: `UseShadowVolumes = Yes`

#### `UseShadowDecals`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether to use shadow decals for static shadow rendering. Shadow decals are texture-based shadows that are projected onto surfaces, providing static shadow effects. When set to `Yes`, shadow decals are rendered, adding shadow detail to the scene. When set to `No`, shadow decals are not rendered, which may improve performance but reduces shadow detail.
- **Default**: `No` (FALSE)
- **Example**: `UseShadowDecals = Yes`

#### `TimeOfDay`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `TimeOfDay` (see [TimeOfDay Values](#timeofday-values))
- **Description**: Default time of day setting that affects lighting, shadows, and visual atmosphere. The time of day determines the overall lighting conditions and color tone of the game world. Different times of day have different ambient and diffuse lighting settings, creating distinct visual moods. See the [TimeOfDay Values](#timeofday-values) section for available options.
- **Default**: `TIME_OF_DAY_AFTERNOON`
- **Example**: `TimeOfDay = AFTERNOON`
- **Available Values**: See [TimeOfDay Values](#timeofday-values) section below

#### `Weather`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Weather` (see [Weather Values](#weather-values))
- **Description**: Default weather condition that affects visual effects and atmosphere. The weather setting determines environmental conditions such as clear skies, rain, fog, or other weather effects. Different weather conditions may affect visibility, particle effects, and overall visual atmosphere. See the [Weather Values](#weather-values) section for available options.
- **Default**: `WEATHER_NORMAL`
- **Example**: `Weather = NORMAL`
- **Available Values**: See [Weather Values](#weather-values) section below

#### `ForceModelsToFollowTimeOfDay`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether to force all models to follow the global time of day lighting settings. When set to `Yes`, all unit and object models use the global time of day lighting, ensuring consistent lighting across all objects. When set to `No`, models may use their own lighting settings or ignore time of day, which can create inconsistent lighting but allows for more flexible per-object lighting control.
- **Default**: `Yes` (true)
- **Example**: `ForceModelsToFollowTimeOfDay = Yes`

#### `ForceModelsToFollowWeather`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether to force all models to follow the global weather settings. When set to `Yes`, all unit and object models are affected by the global weather conditions, ensuring consistent weather effects across all objects. When set to `No`, models may ignore weather effects or use their own weather settings, which can create inconsistent visual effects but allows for more flexible per-object weather control.
- **Default**: `Yes` (true)
- **Example**: `ForceModelsToFollowWeather = Yes`

#### `NumberGlobalLights`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Int`
- **Description**: Number of global lights to use for terrain and object lighting. Global lights provide directional lighting that affects the entire scene. This value determines how many light sources are active for global illumination. Higher values allow for more complex lighting setups with multiple light sources, while lower values use fewer lights. The maximum number of global lights is typically limited by the rendering system (see `MAX_GLOBAL_LIGHTS` constant).
- **Default**: `3`
- **Example**: `NumberGlobalLights = 3`

#### `InfantryLightMorningScale`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Scaling factor applied to map lighting during morning time of day to make infantry units easier to see. This value brightens or darkens the lighting specifically for infantry visibility during morning conditions. Higher values make infantry more visible by increasing lighting, while lower values make them less visible. This helps balance gameplay by ensuring infantry are visible during different times of day.
- **Default**: `1.5`
- **Example**: `InfantryLightMorningScale = 100.0`

#### `InfantryLightAfternoonScale`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Scaling factor applied to map lighting during afternoon time of day to make infantry units easier to see. This value brightens or darkens the lighting specifically for infantry visibility during afternoon conditions. Higher values make infantry more visible by increasing lighting, while lower values make them less visible. This helps balance gameplay by ensuring infantry are visible during different times of day.
- **Default**: `1.5`
- **Example**: `InfantryLightAfternoonScale = 100.0`

#### `InfantryLightEveningScale`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Scaling factor applied to map lighting during evening time of day to make infantry units easier to see. This value brightens or darkens the lighting specifically for infantry visibility during evening conditions. Higher values make infantry more visible by increasing lighting, while lower values make them less visible. Evening typically requires higher scaling values (e.g., 1.25) to compensate for darker lighting conditions.
- **Default**: `1.5`
- **Example**: `InfantryLightEveningScale = 125.0`

#### `InfantryLightNightScale`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Scaling factor applied to map lighting during night time of day to make infantry units easier to see. This value brightens or darkens the lighting specifically for infantry visibility during night conditions. Higher values make infantry more visible by increasing lighting, while lower values make them less visible. Night typically requires the highest scaling values (e.g., 1.5) to compensate for very dark lighting conditions.
- **Default**: `1.5`
- **Example**: `InfantryLightNightScale = 150.0`

### Audio Settings

#### `AudioOn`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Master switch for all audio output. When set to `Yes`, audio is enabled and all sound, music, and speech can play. When set to `No`, all audio is disabled, providing a silent game experience. This is the top-level audio control that affects all audio systems.
- **Default**: `Yes` (TRUE)
- **Example**: `AudioOn = Yes`

#### `MusicOn`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether background music is enabled. When set to `Yes`, background music tracks play during gameplay and menus. When set to `No`, background music is disabled, but other audio (sounds and speech) may still play if enabled. This allows players to disable music while keeping sound effects.
- **Default**: `Yes` (TRUE)
- **Example**: `MusicOn = Yes`

#### `SoundsOn`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether sound effects are enabled. When set to `Yes`, sound effects (weapon fire, explosions, unit sounds, etc.) play during gameplay. When set to `No`, sound effects are disabled, but music and speech may still play if enabled. This allows players to disable sound effects while keeping music.
- **Default**: `Yes` (TRUE)
- **Example**: `SoundsOn = Yes`

#### `Sounds3DOn`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether 3D positional audio is enabled for sound effects. When set to `Yes`, sounds are positioned in 3D space relative to the camera, creating a spatial audio experience where sounds appear to come from their source locations. When set to `No`, sounds play without 3D positioning, which may reduce immersion but can improve performance on some systems.
- **Default**: `Yes` (TRUE)
- **Example**: `Sounds3DOn = Yes`

#### `SpeechOn`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether unit speech and voice lines are enabled. When set to `Yes`, units speak their voice lines when selected, given orders, or in combat. When set to `No`, unit speech is disabled, but other audio (music and sound effects) may still play if enabled. This allows players to disable voice lines while keeping other audio.
- **Default**: `Yes` (TRUE)
- **Example**: `SpeechOn = Yes`

#### `VideoOn`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether video playback is enabled. When set to `Yes`, video cutscenes and movies can play. When set to `No`, video playback is disabled, which may skip intro videos, cutscenes, or other video content. This can improve loading times or allow skipping video content.
- **Default**: `Yes` (TRUE)
- **Example**: `VideoOn = Yes`

#### `DisableCameraMovements`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether to disable camera movement controls. When set to `Yes`, camera movement is disabled, preventing the player from panning, zooming, or rotating the camera. When set to `No`, camera movement is enabled normally. This can be useful for cinematics, screenshots, or debugging scenarios where camera control should be locked.
- **Default**: `No` (FALSE)
- **Example**: `DisableCameraMovements = No`

### Gameplay Settings

#### `UnitDamagedThreshold`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real` (0.0 to 1.0)
- **Description**: Health percentage threshold at which a unit is considered damaged. When a unit's health falls below this percentage of its maximum health, it enters the damaged state. This affects visual appearance, particle effects, and may trigger damage-related behaviors. For example, a value of 0.7 means units are considered damaged when their health drops below 70% of maximum. This threshold is used in conjunction with [`UnitReallyDamagedThreshold`](#unitreallydamagedthreshold) to define multiple damage states.
- **Default**: `0.7`
- **Example**: `UnitDamagedThreshold = 0.7`

#### `UnitReallyDamagedThreshold`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real` (0.0 to 1.0)
- **Description**: Health percentage threshold at which a unit is considered really damaged or heavily damaged. When a unit's health falls below this percentage of its maximum health, it enters the really damaged state. This typically shows more severe visual damage effects and may affect unit behavior. For example, a value of 0.35 means units are considered really damaged when their health drops below 35% of maximum. This threshold should be lower than [`UnitDamagedThreshold`](#unitdamagedthreshold).
- **Default**: `0.35`
- **Example**: `UnitReallyDamagedThreshold = 0.35`

#### `Gravity`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real` (acceleration in distance units per second squared)
- **Description**: Acceleration due to gravity applied to all objects in the game world. This value controls how fast objects fall when not supported. The game's distance units are roughly equivalent to feet, so a value of -32.0 corresponds to Earth-normal gravity (32 ft/sec²). Negative values are used because gravity acts downward. Higher absolute values create stronger gravity, making objects fall faster. Lower absolute values create weaker gravity, making objects fall slower. A value of -64.0 is commonly used as it "feels" better for gameplay.
- **Default**: `-64.0`
- **Example**: `Gravity = -64.0`

#### `GroundStiffness`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Stiffness factor for ground physics interactions. This affects how rigid or flexible the ground feels when units move over it or when objects interact with terrain. Higher values make the ground feel more rigid and solid, while lower values make it feel more flexible or soft. This can affect vehicle movement, unit positioning, and physics interactions with the terrain.
- **Default**: `0.8`
- **Example**: `GroundStiffness = 0.8`

#### `StructureStiffness`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Stiffness factor for structure physics interactions. This affects how rigid or flexible structures feel when units interact with them or when structures are damaged. Higher values make structures feel more rigid and solid, while lower values make them feel more flexible or soft. This can affect how structures respond to damage, collisions, and unit interactions.
- **Default**: `0.3`
- **Example**: `StructureStiffness = 0.3`

#### `PartitionCellSize`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Size of partition cells used for spatial partitioning and optimization. The game world is divided into cells for efficient object lookup, collision detection, and rendering culling. This value determines the size of each cell in world space units. Smaller values create more cells with finer granularity, improving accuracy but using more memory. Larger values create fewer cells with coarser granularity, using less memory but potentially reducing accuracy. A value of 40.0 is commonly used as a balance between performance and accuracy.
- **Default**: `0.0` (disabled or auto-calculated)
- **Example**: `PartitionCellSize = 40.0`

#### `MaxTerrainTracks`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Int`
- **Description**: Maximum number of terrain track marks (tread marks, tire tracks) that can exist simultaneously on the terrain. Vehicle units generate track marks as they move, and this value limits how many track marks are kept in memory and rendered. Higher values allow more track marks to persist, creating more detailed terrain wear patterns but using more memory. Lower values limit track mark persistence, using less memory but showing fewer track marks. When the limit is reached, older track marks are removed to make room for new ones.
- **Default**: `0` (disabled)
- **Example**: `MaxTerrainTracks = 100`

#### `MakeTrackMarks`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether vehicles generate track marks (tread marks, tire tracks) on the terrain as they move. When set to `Yes`, vehicles leave visible track marks on the terrain, creating realistic wear patterns and visual feedback of unit movement. When set to `No`, no track marks are generated, which improves performance but removes the visual effect of vehicle movement. Track marks are limited by [`MaxTerrainTracks`](#maxterraintracks).
- **Default**: `No` (FALSE)
- **Example**: `MakeTrackMarks = Yes`

#### `ParticleScale`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Global scaling factor applied to all particle effects. This value scales the size, intensity, or other visual properties of particle systems throughout the game. A value of 1.0 means normal size, values greater than 1.0 make particles larger or more intense, and values less than 1.0 make them smaller or less intense. This can be used to adjust particle effects for different screen resolutions or performance requirements.
- **Default**: `1.0`
- **Example**: `ParticleScale = 1.0`

#### `MaxParticleCount`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Int`
- **Description**: Maximum number of particles that can exist simultaneously in the game world. This limits the total particle count across all particle systems to prevent excessive memory usage and performance degradation. Higher values allow more particles to exist, creating more detailed effects but using more memory and potentially impacting performance. Lower values limit particle counts, improving performance but potentially reducing visual quality of particle effects. When the limit is reached, new particles may not be created or older particles may be removed.
- **Default**: `5000`
- **Example**: `MaxParticleCount = 5000`

#### `MaxFieldParticleCount`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Int`
- **Description**: Maximum number of field-type particles that can be rendered on screen simultaneously. Field particles are particles with Priority AREA_EFFECT and isGroundAligned = Yes, typically including puddles, toxic contamination, radiation, decontamination effects, and other ground-aligned area effects. When this limit is reached, the game begins skipping field particles to maintain performance. Higher values allow more field particles to be displayed, creating more detailed area effects but potentially impacting performance. Lower values limit field particle display, improving performance but potentially reducing visual quality of area effects.
- **Default**: `100`
- **Example**: `MaxFieldParticleCount = 100`

#### `HistoricDamageLimit`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Duration in milliseconds for which historical damage information is retained for weapons that require it. Some weapons use historical damage tracking to calculate bonuses or effects based on recent damage dealt. This value determines how long damage events are kept in memory before being discarded. Higher values retain damage history longer, allowing weapons to track damage over longer periods but using more memory. Lower values discard damage history sooner, using less memory but potentially affecting weapons that rely on recent damage tracking.
- **Default**: `0` (disabled)
- **Example**: `HistoricDamageLimit = 4000`

#### `ValuePerSupplyBox`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Int`
- **Description**: Base cash value provided by each supply box collected. When a unit collects a supply box (supply crate), the player receives this amount of cash. This is the base value before any multipliers or bonuses are applied. Higher values make supply boxes more valuable, providing more cash per collection. Lower values make supply boxes less valuable, providing less cash per collection. This affects the economic balance of the game.
- **Default**: `100`
- **Example**: `ValuePerSupplyBox = 75`

#### `BuildSpeed`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Global multiplier for construction and production speed. This value scales how fast all structures are built and units are produced. A value of 1.0 means normal speed, values greater than 1.0 make construction and production faster, and values less than 1.0 make them slower. This affects the pace of gameplay by controlling how quickly players can expand and build their forces. Higher values speed up the game, while lower values slow it down.
- **Default**: `1.5`
- **Example**: `BuildSpeed = 1.5`

#### `MinDistFromEdgeOfMapForBuild`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Minimum distance in world space units from the map edge where structures can be built. Buildings cannot be constructed within this distance of the map boundary, preventing construction too close to the edge. This ensures there is always a buffer zone at map edges. Higher values create larger buffer zones, preventing construction further from edges. Lower values allow construction closer to edges. A value of 0.0 allows construction at the very edge of the map.
- **Default**: `20.0`
- **Example**: `MinDistFromEdgeOfMapForBuild = 20.0`

#### `SupplyBuildBorder`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Minimum distance in world space units that supply centers must maintain from supply sources. This prevents supply centers from being built too close to existing supply sources, ensuring proper spacing. Higher values require supply centers to be built further from supply sources, creating more spread-out supply networks. Lower values allow supply centers to be built closer to supply sources. This affects the strategic placement of supply-generating structures.
- **Default**: `45.0`
- **Example**: `SupplyBuildBorder = 45.0`

#### `AllowedHeightVariationForBuilding`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Maximum allowed height variation in world space units for terrain to be considered flat enough for building construction. The terrain height at a structure's footprint must be within this range to be considered buildable. Higher values allow construction on more varied terrain, while lower values require flatter terrain. This ensures structures are built on relatively level ground. Terrain height variation is measured across the structure's footprint area.
- **Default**: `10.0`
- **Example**: `AllowedHeightVariationForBuilding = 10.0`

#### `MinLowEnergyProductionSpeed`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Minimum production speed multiplier when a player has low energy. When energy is insufficient, production and construction speeds are reduced. This value sets the minimum speed multiplier applied during low energy conditions. A value of 0.6 means production runs at 60% of normal speed when energy is low. This creates a penalty for operating without sufficient power, encouraging players to maintain adequate energy production.
- **Default**: `0.6`
- **Example**: `MinLowEnergyProductionSpeed = 0.6`

#### `MaxLowEnergyProductionSpeed`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Maximum production speed multiplier when a player has low energy. When energy is insufficient, production and construction speeds are reduced. This value sets the maximum speed multiplier applied during low energy conditions, representing the best-case scenario when energy is just barely insufficient. A value of 0.8 means production can run at up to 80% of normal speed when energy is low. The actual speed varies between [`MinLowEnergyProductionSpeed`](#minlowenergyproductionspeed) and this value based on energy levels.
- **Default**: `0.8`
- **Example**: `MaxLowEnergyProductionSpeed = 0.8`

#### `LowEnergyPenaltyModifier`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Modifier applied to low energy production speed penalties. This value scales the penalty effect of low energy on production speeds. A value of 1.0 means normal penalty strength, values greater than 1.0 increase the penalty (making low energy more impactful), and values less than 1.0 decrease the penalty (making low energy less impactful). This allows fine-tuning of the energy system's impact on gameplay.
- **Default**: `1.0`
- **Example**: `LowEnergyPenaltyModifier = 1.0`

#### `MultipleFactory`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Production speed bonus multiplier when multiple factories are producing the same unit type simultaneously. When multiple factories are building the same unit, they may receive a speed bonus. This value determines the strength of that bonus. A value of 0.0 means no bonus, while positive values provide a speed increase. Higher values create stronger bonuses for coordinated production across multiple factories.
- **Default**: `0.0`
- **Example**: `MultipleFactory = 0.0`

#### `RefundPercent`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Percent` (converted to Real, 0.0 to 1.0)
- **Description**: Percentage of construction cost refunded when a structure is sold or destroyed before completion. When a player cancels construction or a structure is destroyed during construction, they receive a refund of the construction cost. This value determines what percentage is refunded. A value of 50% means half the cost is refunded. Higher values provide better refunds, reducing the economic penalty of cancelled construction. Lower values provide smaller refunds, increasing the economic penalty.
- **Default**: `0.5` (50%)
- **Example**: `RefundPercent = 50%`

#### `StealthFriendlyOpacity`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Percent` (converted to Real, 0.0 to 1.0)
- **Description**: Opacity (visibility) level for friendly stealth units when viewed by the owning player. Stealth units are partially visible to their owner even when stealthed, allowing the player to see their own units. This value determines how visible they are: 0% is fully transparent (invisible), 100% is fully opaque (fully visible), and values in between create partial visibility. A value of 60% means friendly stealth units appear at 60% opacity to their owner. This helps players track their own stealth units while maintaining the stealth effect for enemies.
- **Default**: `0.6` (60%)
- **Example**: `StealthFriendlyOpacity = 60%`

#### `CommandCenterHealRange`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Range in world space units within which the command center automatically heals friendly units and structures. Units and structures within this distance of a command center receive automatic healing over time. Higher values create larger healing zones, allowing the command center to heal units further away. Lower values create smaller healing zones, requiring units to be closer to receive healing. This affects the strategic value and positioning of command centers.
- **Default**: `500.0`
- **Example**: `CommandCenterHealRange = 500.0`

#### `CommandCenterHealAmount`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Amount of health restored per logic frame to units and structures within the command center's healing range. This value determines how fast the command center heals nearby units. Higher values provide faster healing, making the command center more effective at restoring unit health. Lower values provide slower healing, making the healing effect more gradual. The healing is applied continuously while units remain within [`CommandCenterHealRange`](#commandcenterhealrange).
- **Default**: `0.01`
- **Example**: `CommandCenterHealAmount = 0.01`

#### `MaxLineBuildObjects`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Int`
- **Description**: Maximum number of objects that can be placed in a line when using line build style construction. Line build allows players to place multiple structures in a straight line. This value limits how many structures can be placed in a single line. Higher values allow longer lines of structures, while lower values limit line length. This prevents excessively long construction lines that might cause performance issues or gameplay problems.
- **Default**: `50`
- **Example**: `MaxLineBuildObjects = 50`

#### `MaxTunnelCapacity`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Int`
- **Description**: Maximum number of tunnel entrances that can exist in a player's tunnel network simultaneously. Tunnel networks allow units to travel underground between tunnel entrances. This value limits how many tunnel entrances a player can have active at once. Higher values allow larger tunnel networks, while lower values limit network size. The UI currently supports a maximum of 10 tunnel entrances, so values above 10 may not be fully supported by the interface.
- **Default**: `10`
- **Example**: `MaxTunnelCapacity = 10`

#### `StandardMinefieldDensity`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real` (mines per square unit)
- **Description**: Density of mines in standard minefields, measured in mines per square unit of area. This value determines how many mines are placed per unit area when generating standard minefields. Higher values create denser minefields with more mines packed into the same area, making them more dangerous but potentially more expensive. Lower values create sparser minefields with fewer mines, making them less dangerous but potentially more cost-effective. This affects the effectiveness and coverage of minefield-based defenses.
- **Default**: `0.004`
- **Example**: `StandardMinefieldDensity = 0.004`

#### `StandardMinefieldDistance`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real` (world space units)
- **Description**: Standard distance or spacing for minefield placement in world space units. This value determines the typical spacing or range for minefield generation. Higher values create larger minefield areas or greater spacing between mines. Lower values create smaller minefield areas or tighter spacing. This value should generally be larger than typical tank shot range to ensure minefields are effective at their intended range. This affects the tactical placement and effectiveness of minefields.
- **Default**: `40.0`
- **Example**: `StandardMinefieldDistance = 40.0`

#### `MovementPenaltyDamageState`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `BodyDamageType` (see [BodyDamageType Values](#bodydamagetype-values))
- **Description**: Damage state threshold at which units begin to experience movement speed penalties. When a unit reaches this damage state or worse, its movement speed is reduced to reflect the damage it has sustained. This creates gameplay consequences for damaged units, making them slower and less mobile. See the [BodyDamageType Values](#bodydamagetype-values) section for available damage states. Typically set to `REALLYDAMAGED` to apply movement penalties only to heavily damaged units.
- **Default**: `REALLYDAMAGED`
- **Example**: `MovementPenaltyDamageState = REALLYDAMAGED`
- **Available Values**: See [BodyDamageType Values](#bodydamagetype-values) section below

### Weapon and Veterancy Bonuses

#### `WeaponBonus`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `WeaponBonusSet` block (see [WeaponBonusSet documentation](WeaponBonusSet.md))
- **Description**: Weapon bonus configuration that defines damage multipliers for weapons against different target types. This block contains multiple weapon bonus entries that specify how much extra damage (or reduced damage) weapons deal against specific target categories. Weapon bonuses are applied multiplicatively to base weapon damage, allowing fine-tuning of combat effectiveness. For example, a weapon bonus of 150% against infantry means the weapon deals 1.5x its normal damage to infantry units. See the [WeaponBonusSet documentation](WeaponBonusSet.md) for complete details on the weapon bonus system.
- **Default**: Empty (no bonuses)
- **Example**: 
```ini
WeaponBonus = WeaponBonusSet
    WeaponBonus = WeaponBonus
        Against = INFANTRY
        Multiplier = 150%
    End
End
```

#### `HealthBonus_Veteran`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Percent` (converted to Real, 0.0 to 1.0)
- **Description**: Health bonus percentage for veteran-level units. When a unit reaches veteran status, it receives this percentage bonus to its maximum health. For example, a value of 25% means veteran units have 125% of their base maximum health. This bonus is applied multiplicatively with other health bonuses. Higher values make veteran units more durable, while lower values provide smaller health increases. Regular units have a 100% health bonus (no change), which cannot be modified.
- **Default**: `0.25` (25%)
- **Example**: `HealthBonus_Veteran = 25%`

#### `HealthBonus_Elite`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Percent` (converted to Real, 0.0 to 1.0)
- **Description**: Health bonus percentage for elite-level units. When a unit reaches elite status, it receives this percentage bonus to its maximum health. For example, a value of 50% means elite units have 150% of their base maximum health. This bonus is applied multiplicatively with other health bonuses and is typically higher than the veteran bonus. Higher values make elite units significantly more durable, while lower values provide smaller health increases.
- **Default**: `0.5` (50%)
- **Example**: `HealthBonus_Elite = 50%`

#### `HealthBonus_Heroic`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Percent` (converted to Real, 0.0 to 1.0)
- **Description**: Health bonus percentage for heroic-level units. When a unit reaches heroic status, it receives this percentage bonus to its maximum health. For example, a value of 100% means heroic units have 200% of their base maximum health. This bonus is applied multiplicatively with other health bonuses and is typically the highest veterancy bonus. Higher values make heroic units extremely durable, while lower values provide smaller health increases.
- **Default**: `1.0` (100%)
- **Example**: `HealthBonus_Heroic = 100%`

#### `HumanSoloPlayerHealthBonus_Easy`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Percent` (converted to Real, 0.0 to 1.0)
- **Description**: Health bonus percentage for human player units in single-player easy difficulty mode. This bonus is applied to all units owned by the human player in single-player campaigns or skirmish games set to easy difficulty. For example, a value of 25% means human player units have 125% of their base maximum health on easy difficulty. This makes the game easier by making player units more durable. Higher values provide more health, making the game easier, while lower values provide less health, making the game harder.
- **Default**: *(needs verification from constructor)*
- **Example**: `HumanSoloPlayerHealthBonus_Easy = 25%`

#### `HumanSoloPlayerHealthBonus_Normal`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Percent` (converted to Real, 0.0 to 1.0)
- **Description**: Health bonus percentage for human player units in single-player normal difficulty mode. This bonus is applied to all units owned by the human player in single-player campaigns or skirmish games set to normal difficulty. For example, a value of 0% means human player units have 100% of their base maximum health on normal difficulty (no bonus). This represents the baseline difficulty. Higher values provide more health, making the game easier, while lower values provide less health, making the game harder.
- **Default**: `0.0` (0%, no bonus)
- **Example**: `HumanSoloPlayerHealthBonus_Normal = 0%`

#### `HumanSoloPlayerHealthBonus_Hard`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Percent` (converted to Real, 0.0 to 1.0)
- **Description**: Health bonus percentage for human player units in single-player hard difficulty mode. This bonus is applied to all units owned by the human player in single-player campaigns or skirmish games set to hard difficulty. For example, a value of -25% means human player units have 75% of their base maximum health on hard difficulty (a penalty). This makes the game harder by making player units less durable. Negative values provide health penalties, making the game harder, while positive values provide health bonuses, making the game easier.
- **Default**: *(needs verification from constructor)*
- **Example**: `HumanSoloPlayerHealthBonus_Hard = -25%`

#### `AISoloPlayerHealthBonus_Easy`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Percent` (converted to Real, 0.0 to 1.0)
- **Description**: Health bonus percentage for AI player units in single-player easy difficulty mode. This bonus is applied to all units owned by AI players in single-player campaigns or skirmish games set to easy difficulty. For example, a value of -25% means AI units have 75% of their base maximum health on easy difficulty (a penalty). This makes the game easier by making AI units less durable. Negative values provide health penalties, making AI weaker, while positive values provide health bonuses, making AI stronger.
- **Default**: *(needs verification from constructor)*
- **Example**: `AISoloPlayerHealthBonus_Easy = -25%`

#### `AISoloPlayerHealthBonus_Normal`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Percent` (converted to Real, 0.0 to 1.0)
- **Description**: Health bonus percentage for AI player units in single-player normal difficulty mode. This bonus is applied to all units owned by AI players in single-player campaigns or skirmish games set to normal difficulty. For example, a value of 0% means AI units have 100% of their base maximum health on normal difficulty (no bonus). This represents the baseline difficulty. Higher values provide more health, making AI stronger, while lower values provide less health, making AI weaker.
- **Default**: `0.0` (0%, no bonus)
- **Example**: `AISoloPlayerHealthBonus_Normal = 0%`

#### `AISoloPlayerHealthBonus_Hard`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Percent` (converted to Real, 0.0 to 1.0)
- **Description**: Health bonus percentage for AI player units in single-player hard difficulty mode. This bonus is applied to all units owned by AI players in single-player campaigns or skirmish games set to hard difficulty. For example, a value of 25% means AI units have 125% of their base maximum health on hard difficulty. This makes the game harder by making AI units more durable. Higher values provide more health, making AI stronger and the game harder, while lower values provide less health, making AI weaker and the game easier.
- **Default**: *(needs verification from constructor)*
- **Example**: `AISoloPlayerHealthBonus_Hard = 25%`

### Network Settings

#### `NetworkFPSHistoryLength`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Int`
- **Description**: Number of frame rate samples to keep in the network frame rate history buffer. The game tracks frame rate history for network synchronization and performance monitoring. This value determines how many recent frame rate samples are stored. Higher values provide more historical data for analysis but use more memory. Lower values use less memory but provide less historical context. This is used for network performance analysis and synchronization calculations.
- **Default**: *(needs verification from constructor)*
- **Example**: `NetworkFPSHistoryLength = 60`

#### `NetworkLatencyHistoryLength`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Int`
- **Description**: Number of latency samples to keep in the network latency history buffer. The game tracks network latency (ping) history for synchronization and performance monitoring. This value determines how many recent latency samples are stored. Higher values provide more historical data for analysis but use more memory. Lower values use less memory but provide less historical context. This is used for network performance analysis and synchronization calculations.
- **Default**: *(needs verification from constructor)*
- **Example**: `NetworkLatencyHistoryLength = 60`

#### `NetworkRunAheadMetricsTime`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Int` (milliseconds)
- **Description**: Time window in milliseconds for calculating network run-ahead metrics. Run-ahead is a network synchronization technique that allows the game to simulate ahead of the network delay to maintain smooth gameplay. This value determines the time window used for calculating run-ahead metrics. Higher values use longer time windows for more stable metrics but may be less responsive to changes. Lower values use shorter time windows for more responsive metrics but may be less stable.
- **Default**: *(needs verification from constructor)*
- **Example**: `NetworkRunAheadMetricsTime = 1000`

#### `NetworkCushionHistoryLength`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Int`
- **Description**: Number of cushion samples to keep in the network cushion history buffer. The network cushion is a buffer that helps smooth out network timing variations. This value determines how many recent cushion samples are stored. Higher values provide more historical data for analysis but use more memory. Lower values use less memory but provide less historical context. This is used for network synchronization calculations.
- **Default**: *(needs verification from constructor)*
- **Example**: `NetworkCushionHistoryLength = 60`

#### `NetworkRunAheadSlack`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Int` (milliseconds)
- **Description**: Slack time in milliseconds for network run-ahead calculations. Run-ahead is a network synchronization technique that allows the game to simulate ahead of the network delay. This value provides a safety margin (slack) in the run-ahead calculations to account for network timing variations. Higher values provide more safety margin but may increase perceived latency. Lower values reduce safety margin but may cause synchronization issues if network timing varies.
- **Default**: *(needs verification from constructor)*
- **Example**: `NetworkRunAheadSlack = 50`

#### `NetworkKeepAliveDelay`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Int` (milliseconds)
- **Description**: Delay in milliseconds between network keep-alive packets. Keep-alive packets are sent periodically to maintain network connections and detect disconnections. This value determines how frequently keep-alive packets are sent. Higher values send keep-alive packets less frequently, reducing network traffic but potentially detecting disconnections more slowly. Lower values send keep-alive packets more frequently, detecting disconnections faster but increasing network traffic.
- **Default**: *(needs verification from constructor)*
- **Example**: `NetworkKeepAliveDelay = 5000`

#### `NetworkDisconnectTime`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Int` (milliseconds)
- **Description**: Time in milliseconds without network communication before a player is considered disconnected. If no network packets are received from a player within this time period, the game considers that player disconnected. Higher values wait longer before declaring a disconnection, potentially allowing recovery from temporary network issues but delaying disconnection detection. Lower values detect disconnections faster but may incorrectly disconnect players with temporary network hiccups.
- **Default**: *(needs verification from constructor)*
- **Example**: `NetworkDisconnectTime = 30000`

#### `NetworkPlayerTimeoutTime`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Int` (milliseconds)
- **Description**: Time in milliseconds without player activity before a player is considered timed out. If a player does not send any input or activity within this time period, the game may consider that player timed out. Higher values wait longer before timing out, allowing players more time to respond but potentially delaying timeout detection. Lower values timeout players faster but may incorrectly timeout players who are temporarily inactive.
- **Default**: *(needs verification from constructor)*
- **Example**: `NetworkPlayerTimeoutTime = 60000`

#### `NetworkDisconnectScreenNotifyTime`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Int` (milliseconds)
- **Description**: Time in milliseconds to display the disconnection notification screen when a player disconnects. When a player disconnects, a notification screen is shown to inform other players. This value determines how long the notification is displayed. Higher values show the notification longer, ensuring players see it but potentially delaying gameplay. Lower values show the notification briefly, minimizing gameplay interruption but potentially causing players to miss it.
- **Default**: *(needs verification from constructor)*
- **Example**: `NetworkDisconnectScreenNotifyTime = 5000`

#### `FirewallBehavior`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Int`
- **Description**: Firewall behavior mode for network connections. This value determines how the game handles firewall and NAT traversal for network multiplayer. Different values may enable or disable automatic port mapping, UPnP support, or other firewall-related features. The specific meaning of each value depends on the network implementation. This affects how the game establishes network connections through firewalls and routers.
- **Default**: `0`
- **Example**: `FirewallBehavior = 0`

#### `FirewallPortOverride`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Int` (port number)
- **Description**: Override port number for firewall port mapping. If set to a non-zero value, this port number is used for firewall port mapping instead of automatically assigned ports. This allows manual configuration of the network port used for multiplayer connections. A value of 0 means use automatic port assignment. This is useful for network configurations that require specific port numbers to be opened in firewalls or routers.
- **Default**: `0` (automatic)
- **Example**: `FirewallPortOverride = 12345`

#### `FirewallPortAllocationDelta`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Int` (port number offset)
- **Description**: Port number offset added to the base port for firewall port allocation. When multiple ports are needed for network connections, this value is added to the base port to calculate additional port numbers. For example, if the base port is 12345 and this value is 1, additional ports would be 12346, 12347, etc. This allows the game to allocate multiple consecutive ports for network communication. A value of 0 means no offset is applied.
- **Default**: `0`
- **Example**: `FirewallPortAllocationDelta = 1`

### UI and Selection Settings

#### `GroupSelectMinSelectSize`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Int`
- **Description**: Minimum number of units that must be selected before group selection sounds play. When selecting multiple units, group selection sounds (voice lines from selected units) only play if at least this many units are selected. Higher values require more units to be selected before group sounds play, reducing audio clutter with small selections. Lower values allow group sounds to play with fewer units selected, providing more audio feedback.
- **Default**: *(needs verification from constructor)*
- **Example**: `GroupSelectMinSelectSize = 3`

#### `GroupSelectVolumeBase`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Base volume level for group selection sounds. When multiple units are selected, group selection sounds play at a volume based on this base value. This sets the starting volume level for group selection audio. Higher values make group selection sounds louder, while lower values make them quieter. This is combined with [`GroupSelectVolumeIncrement`](#groupselectvolumeincrement) to calculate the final volume based on selection size.
- **Default**: *(needs verification from constructor)*
- **Example**: `GroupSelectVolumeBase = 0.5`

#### `GroupSelectVolumeIncrement`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Volume increment per unit added to group selection. When multiple units are selected, the volume of group selection sounds increases by this amount for each additional unit beyond the minimum. This creates a volume scaling effect where larger selections are louder. Higher values create more dramatic volume increases with larger selections, while lower values create more subtle volume changes. This is added to [`GroupSelectVolumeBase`](#groupselectvolumebase) to calculate the final volume.
- **Default**: *(needs verification from constructor)*
- **Example**: `GroupSelectVolumeIncrement = 0.1`

#### `MaxUnitSelectSounds`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Int`
- **Description**: Maximum number of unit selection sounds that can play simultaneously when selecting multiple units. When selecting a group of units, individual unit selection sounds are played, but only up to this limit. Higher values allow more unit sounds to play simultaneously, providing more audio feedback but potentially causing audio clutter. Lower values limit the number of simultaneous sounds, reducing clutter but providing less audio feedback.
- **Default**: *(needs verification from constructor)*
- **Example**: `MaxUnitSelectSounds = 5`

#### `SelectionFlashSaturationFactor`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Saturation factor applied to the selection flash effect when units are selected. When units are selected, they flash with a visual highlight effect. This value controls the color saturation of that flash effect. Higher values create more saturated (vivid) flash colors, making the selection more noticeable. Lower values create less saturated (more muted) flash colors, making the selection more subtle. A value of 1.0 means normal saturation, values greater than 1.0 increase saturation, and values less than 1.0 decrease saturation.
- **Default**: *(needs verification from constructor)*
- **Example**: `SelectionFlashSaturationFactor = 1.0`

#### `SelectionFlashHouseColor`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Bool`
- **Description**: Whether the selection flash effect uses the player's house color (team color). When set to `Yes`, selected units flash with the player's house color, making it easier to identify which player owns selected units. When set to `No`, selected units use a default flash color regardless of player ownership. This helps players quickly identify their own units in multi-player games.
- **Default**: *(needs verification from constructor)*
- **Example**: `SelectionFlashHouseColor = Yes`

#### `GroupMoveClickToGatherAreaFactor`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Factor that determines the size of the gathering area when giving a group move command. When multiple units are given a move order, they spread out into a formation. This value controls how large that formation area is relative to the number of units. Higher values create larger gathering areas, spreading units out more. Lower values create smaller gathering areas, keeping units more tightly grouped. This affects how units position themselves when moving as a group.
- **Default**: *(needs verification from constructor)*
- **Example**: `GroupMoveClickToGatherAreaFactor = 1.0`

#### `CameraAudibleRadius`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Radius in world space units around the camera position where sounds are audible. Sounds within this distance of the camera are played, while sounds outside this radius are not played or are played at reduced volume. This creates a sound culling system that only plays sounds near the camera, improving performance and reducing audio clutter. Higher values make sounds audible from further away, while lower values limit sound range to a smaller area around the camera.
- **Default**: *(needs verification from constructor)*
- **Example**: `CameraAudibleRadius = 1000.0`

#### `SellPercentage`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Percent` (converted to Real, 0.0 to 1.0)
- **Description**: Percentage of construction cost refunded when a structure is sold. When a player sells a completed structure, they receive a refund of the construction cost. This value determines what percentage is refunded. For example, a value of 75% means players receive 75% of the construction cost back when selling a structure. Higher values provide better refunds, making selling structures more economically viable. Lower values provide smaller refunds, making selling structures less economically attractive.
- **Default**: `0.75` (75%)
- **Example**: `SellPercentage = 75%`

#### `BaseRegenHealthPercentPerSecond`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Percent` (converted to Real, 0.0 to 1.0)
- **Description**: Base health regeneration rate as a percentage of maximum health per second. Some units and structures regenerate health over time. This value sets the base regeneration rate that is applied before any modifiers. For example, a value of 0.1% means units regenerate 0.1% of their maximum health per second. Higher values provide faster regeneration, making units more durable over time. Lower values provide slower regeneration, making regeneration less impactful.
- **Default**: `0.0` (0%, no regeneration)
- **Example**: `BaseRegenHealthPercentPerSecond = 0.1%`

#### `BaseRegenDelay`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `UnsignedInt` (milliseconds)
- **Description**: Delay in milliseconds after taking damage before health regeneration begins. When a unit takes damage, health regeneration is paused for this duration before resuming. This prevents units from regenerating health immediately after taking damage, making regeneration less effective during active combat. Higher values create longer delays, making regeneration less useful in combat. Lower values create shorter delays, making regeneration more useful in combat.
- **Default**: `0` (no delay)
- **Example**: `BaseRegenDelay = 5000`

#### `ShakeSubtleIntensity`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Camera shake intensity for subtle shake effects. Camera shake is applied during explosions, impacts, and other events to create visual feedback. This value sets the intensity for subtle shake effects. Higher values create stronger camera shake, making effects more noticeable but potentially disorienting. Lower values create weaker camera shake, making effects more subtle but potentially less noticeable.
- **Default**: *(needs verification from constructor)*
- **Example**: `ShakeSubtleIntensity = 0.1`

#### `ShakeNormalIntensity`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Camera shake intensity for normal shake effects. Camera shake is applied during explosions, impacts, and other events to create visual feedback. This value sets the intensity for normal shake effects. Higher values create stronger camera shake, making effects more noticeable but potentially disorienting. Lower values create weaker camera shake, making effects more subtle but potentially less noticeable. This is typically stronger than subtle shake but weaker than strong shake.
- **Default**: *(needs verification from constructor)*
- **Example**: `ShakeNormalIntensity = 0.2`

#### `ShakeStrongIntensity`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Camera shake intensity for strong shake effects. Camera shake is applied during explosions, impacts, and other events to create visual feedback. This value sets the intensity for strong shake effects. Higher values create stronger camera shake, making effects more noticeable but potentially disorienting. Lower values create weaker camera shake, making effects more subtle but potentially less noticeable. This is typically stronger than normal shake.
- **Default**: *(needs verification from constructor)*
- **Example**: `ShakeStrongIntensity = 0.4`

#### `ShakeSevereIntensity`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Camera shake intensity for severe shake effects. Camera shake is applied during explosions, impacts, and other events to create visual feedback. This value sets the intensity for severe shake effects. Higher values create stronger camera shake, making effects more noticeable but potentially disorienting. Lower values create weaker camera shake, making effects more subtle but potentially less noticeable. This is typically stronger than strong shake.
- **Default**: *(needs verification from constructor)*
- **Example**: `ShakeSevereIntensity = 0.6`

#### `ShakeCineExtremeIntensity`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Camera shake intensity for extreme cinematic shake effects. Camera shake is applied during explosions, impacts, and other events to create visual feedback. This value sets the intensity for extreme cinematic shake effects used in cutscenes or dramatic moments. Higher values create stronger camera shake, making effects more dramatic but potentially disorienting. Lower values create weaker camera shake, making effects more subtle.
- **Default**: *(needs verification from constructor)*
- **Example**: `ShakeCineExtremeIntensity = 0.8`

#### `ShakeCineInsaneIntensity`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Camera shake intensity for insane cinematic shake effects. Camera shake is applied during explosions, impacts, and other events to create visual feedback. This value sets the intensity for insane cinematic shake effects used in the most dramatic moments. Higher values create very strong camera shake, making effects extremely dramatic but potentially very disorienting. Lower values create weaker camera shake, making effects more subtle.
- **Default**: *(needs verification from constructor)*
- **Example**: `ShakeCineInsaneIntensity = 1.0`

#### `MaxShakeIntensity`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Maximum allowed camera shake intensity. This value caps the maximum camera shake intensity, preventing shake effects from exceeding this limit. This ensures camera shake never becomes too extreme, maintaining playability. Higher values allow stronger shake effects, while lower values limit shake intensity more strictly. All shake intensity values are clamped to this maximum.
- **Default**: *(needs verification from constructor)*
- **Example**: `MaxShakeIntensity = 1.0`

#### `MaxShakeRange`
Available in: *(GMX Generals, GMX Zero Hour, Retail Generals 1.04, Retail Zero Hour 1.04)*

- **Type**: `Real`
- **Description**: Maximum range in world space units at which camera shake effects are applied. Camera shake from explosions and impacts is only applied if the event occurs within this distance of the camera. Events beyond this range do not cause camera shake. Higher values make camera shake effective from further away, while lower values limit shake to nearby events only. This prevents distant explosions from causing camera shake.
- **Default**: *(needs verification from constructor)*
- **Example**: `MaxShakeRange = 500.0`

### Debug Settings

*Properties for debug and development settings will be documented here. Note: Many debug properties are only available in debug builds (marked with `#if defined(RTS_DEBUG)` in the source code) and will be ignored in release builds.*

## Enum Value Lists

### TerrainLOD Values *(v1.04)*

The `TerrainLOD` enum controls terrain level of detail rendering modes.

- **`NONE`** *(v1.04)* - Invalid value, not used.
- **`MIN`** *(v1.04)* - Minimum detail level for terrain rendering.
- **`STRETCH_NO_CLOUDS`** *(v1.04)* - Stretched terrain without cloud rendering.
- **`HALF_CLOUDS`** *(v1.04)* - Terrain with half-resolution cloud rendering.
- **`NO_CLOUDS`** *(v1.04)* - Terrain without cloud rendering.
- **`STRETCH_CLOUDS`** *(v1.04)* - Stretched terrain with cloud rendering.
- **`NO_WATER`** *(v1.04)* - Terrain without water rendering.
- **`MAX`** *(v1.04)* - Maximum detail level for terrain rendering.
- **`AUTOMATIC`** *(v1.04)* - Automatic LOD adjustment based on performance (default).
- **`DISABLE`** *(v1.04)* - Disable LOD system entirely.

**Source Files:**
- Enum definition: [TerrainVisual.h](../../GeneralsMD/Code/GameEngine/Include/GameClient/TerrainVisual.h#L170)
- String array: [TerrainVisual.h](../../GeneralsMD/Code/GameEngine/Include/GameClient/TerrainVisual.h#L187)

### TimeOfDay Values *(v1.04)*

The `TimeOfDay` enum controls the time of day lighting and atmosphere settings.

- **`NONE`** *(v1.04)* - Invalid value, not used.
- **`MORNING`** *(v1.04)* - Morning time of day with early morning lighting.
- **`AFTERNOON`** *(v1.04)* - Afternoon time of day with bright daylight (default).
- **`EVENING`** *(v1.04)* - Evening time of day with sunset lighting.
- **`NIGHT`** *(v1.04)* - Night time of day with dark nighttime lighting.

**Source Files:**
- Enum definition: [GameType.h](../../GeneralsMD/Code/GameEngine/Include/Common/GameType.h#L63)
- String array: [GameType.cpp](../../GeneralsMD/Code/GameEngine/Source/Common/System/GameType.cpp#L29)

### Weather Values *(v1.04)*

The `Weather` enum controls weather conditions and environmental effects.

- **`NORMAL`** *(v1.04)* - Normal clear weather conditions (default).
- **`SNOWY`** *(v1.04)* - Snowy weather conditions with snow effects.

**Source Files:**
- Enum definition: [GameType.h](../../GeneralsMD/Code/GameEngine/Include/Common/GameType.h#L81)
- String array: [GameType.cpp](../../GeneralsMD/Code/GameEngine/Source/Common/System/GameType.cpp#L41)

### BodyDamageType Values *(v1.04)*

The `BodyDamageType` enum represents different damage states for objects and their components. Used by [`MovementPenaltyDamageState`](#movementpenaltydamagestate) to determine when movement penalties apply.

**Main Damage States:**
- **`PRISTINE`** *(v1.04)* - Object is undamaged and in perfect condition.
- **`DAMAGED`** *(v1.04)* - Object has sustained light damage.
- **`REALLYDAMAGED`** *(v1.04)* - Object has sustained heavy damage.
- **`RUBBLE`** *(v1.04)* - Object is destroyed and reduced to rubble.

**Engine Component States:**
- **`COMPONENT_ENGINE_DESTROYED`** *(v1.04)* - Engine component is destroyed.
- **`COMPONENT_ENGINE_DAMAGED`** *(v1.04)* - Engine component is damaged.

**Turret Component States:**
- **`COMPONENT_TURRET_DESTROYED`** *(v1.04)* - Turret component is destroyed.
- **`COMPONENT_TURRET_DAMAGED`** *(v1.04)* - Turret component is damaged.

**Weapon Component Destroyed States:**
- **`COMPONENT_WEAPON_A_DESTROYED`** *(v1.04)* - Weapon A component is destroyed.
- **`COMPONENT_WEAPON_B_DESTROYED`** *(v1.04)* - Weapon B component is destroyed.
- **`COMPONENT_WEAPON_C_DESTROYED`** *(v1.04)* - Weapon C component is destroyed.
- **`COMPONENT_WEAPON_D_DESTROYED`** *(v1.04)* - Weapon D component is destroyed.
- **`COMPONENT_WEAPON_E_DESTROYED`** *(v1.04)* - Weapon E component is destroyed.
- **`COMPONENT_WEAPON_F_DESTROYED`** *(v1.04)* - Weapon F component is destroyed.
- **`COMPONENT_WEAPON_G_DESTROYED`** *(v1.04)* - Weapon G component is destroyed.
- **`COMPONENT_WEAPON_H_DESTROYED`** *(v1.04)* - Weapon H component is destroyed.

**Weapon Component Damaged States:**
- **`COMPONENT_WEAPON_A_DAMAGED`** *(v1.04)* - Weapon A component is damaged.
- **`COMPONENT_WEAPON_B_DAMAGED`** *(v1.04)* - Weapon B component is damaged.
- **`COMPONENT_WEAPON_C_DAMAGED`** *(v1.04)* - Weapon C component is damaged.
- **`COMPONENT_WEAPON_D_DAMAGED`** *(v1.04)* - Weapon D component is damaged.
- **`COMPONENT_WEAPON_E_DAMAGED`** *(v1.04)* - Weapon E component is damaged.
- **`COMPONENT_WEAPON_F_DAMAGED`** *(v1.04)* - Weapon F component is damaged.
- **`COMPONENT_WEAPON_G_DAMAGED`** *(v1.04)* - Weapon G component is damaged.
- **`COMPONENT_WEAPON_H_DAMAGED`** *(v1.04)* - Weapon H component is damaged.

**Generic Component Destroyed States:**
- **`COMPONENT_A_DESTROYED`** *(v1.04)* - Generic component A is destroyed.
- **`COMPONENT_B_DESTROYED`** *(v1.04)* - Generic component B is destroyed.
- **`COMPONENT_C_DESTROYED`** *(v1.04)* - Generic component C is destroyed.
- **`COMPONENT_D_DESTROYED`** *(v1.04)* - Generic component D is destroyed.
- **`COMPONENT_E_DESTROYED`** *(v1.04)* - Generic component E is destroyed.
- **`COMPONENT_F_DESTROYED`** *(v1.04)* - Generic component F is destroyed.
- **`COMPONENT_G_DESTROYED`** *(v1.04)* - Generic component G is destroyed.
- **`COMPONENT_H_DESTROYED`** *(v1.04)* - Generic component H is destroyed.

**Generic Component Damaged States:**
- **`COMPONENT_A_DAMAGED`** *(v1.04)* - Generic component A is damaged.
- **`COMPONENT_B_DAMAGED`** *(v1.04)* - Generic component B is damaged.
- **`COMPONENT_C_DAMAGED`** *(v1.04)* - Generic component C is damaged.
- **`COMPONENT_D_DAMAGED`** *(v1.04)* - Generic component D is damaged.
- **`COMPONENT_E_DAMAGED`** *(v1.04)* - Generic component E is damaged.
- **`COMPONENT_F_DAMAGED`** *(v1.04)* - Generic component F is damaged.
- **`COMPONENT_G_DAMAGED`** *(v1.04)* - Generic component G is damaged.
- **`COMPONENT_H_DAMAGED`** *(v1.04)* - Generic component H is damaged.

**Source Files:**
- Enum definition: [BodyModule.h](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h#L109)
- String array: [BodyModule.h](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h#L109)

## Template

```ini
GameData
    ; Display and Rendering Settings
    Windowed = No                                    ; // Whether to run in windowed mode *(v1.04)*
    XResolution = 1024                               ; // Horizontal screen resolution in pixels *(v1.04)*
    YResolution = 768                                ; // Vertical screen resolution in pixels *(v1.04)*
    ViewportHeightScale = 1.0                        ; // Viewport height scaling factor *(v1.04)*
    UseFPSLimit = No                                 ; // Whether to enable frame rate limiting *(v1.04)*
    FramesPerSecondLimit = 0                         ; // Maximum frame rate when FPS limit is enabled *(v1.04)*
    ChipsetType = 0                                  ; // Graphics chipset type identifier *(v1.04)*
    MaxShellScreens = 0                              ; // Maximum number of shell screen layouts *(v1.04)*
    ShellMapName = Maps\ShellMap1\ShellMap1.map      ; // Background texture for shell screens *(v1.04)*
    ShellMapOn = Yes                                 ; // Whether to display shell map background *(v1.04)*
    MapName =                                        ; // Default map filename to load *(v1.04)*
    MoveHintName =                                   ; // Move hint system name for pathfinding *(v1.04)*
    DumpAssetUsage = No                              ; // Whether to dump asset usage statistics *(v1.04)*
    UseTrees = No                                    ; // Whether to render trees and vegetation *(v1.04)*

    ; Terrain Settings
    UseCloudMap = No                                 ; // Whether to use cloud map textures *(v1.04)*
    UseLightMap = No                                 ; // Whether to use light maps for terrain *(v1.04)*
    BilinearTerrainTex = No                          ; // Whether to use bilinear filtering for terrain textures *(v1.04)*
    TrilinearTerrainTex = No                         ; // Whether to use trilinear filtering for terrain textures *(v1.04)*
    MultiPassTerrain = No                            ; // Whether to use multi-pass terrain rendering *(v1.04)*
    AdjustCliffTextures = No                         ; // Whether to automatically adjust cliff textures *(v1.04)*
    StretchTerrain = No                              ; // Whether to stretch terrain textures *(v1.04)*
    UseHalfHeightMap = No                            ; // Whether to use half-resolution height maps *(v1.04)*
    DrawEntireTerrain = No                           ; // Whether to draw entire terrain regardless of visibility *(v1.04)*
    TerrainLOD = AUTOMATIC                           ; // Terrain level of detail setting *(v1.04)*
    TerrainLODTargetTimeMS = 0                       ; // Target frame time for terrain LOD calculations *(v1.04)*
    TextureReductionFactor = -1                      ; // Factor by which to reduce texture resolution *(v1.04)*
    Use3WayTerrainBlends = 1                         ; // Whether to use 3-way terrain texture blending *(v1.04)*
    ShowObjectHealth = No                            ; // Whether to display health bars above objects *(v1.04)*
    HideGarrisonFlags = No                           ; // Whether to hide garrison flags *(v1.04)*
    UseBehindBuildingMarker = Yes                    ; // Whether to display markers behind buildings *(v1.04)*
    DefaultOcclusionDelay = 3000                     ; // Default delay before objects are occluded (ms) *(v1.04)*
    OccludedColorLuminanceScale = 0.5                ; // Luminance scaling factor for occluded objects *(v1.04)*
    RightMouseAlwaysScrolls = No                     ; // Whether right mouse button always scrolls camera *(v1.04)*

    ; Water Settings
    UseWaterPlane = No                               ; // Whether to use a water plane for water rendering *(v1.04)*
    UseCloudPlane = No                               ; // Whether to use a cloud plane for sky rendering *(v1.04)*
    DownwindAngle = -0.785                           ; // Downwind direction angle in radians *(v1.04)*
    WaterPositionX = 0.0                             ; // X coordinate of water plane center *(v1.04)*
    WaterPositionY = 0.0                             ; // Y coordinate of water plane center *(v1.04)*
    WaterPositionZ = 0.0                             ; // Z coordinate (height) of water plane surface *(v1.04)*
    WaterExtentX = 0.0                               ; // Horizontal extent (width) of water plane *(v1.04)*
    WaterExtentY = 0.0                               ; // Depth extent (length) of water plane *(v1.04)*
    WaterType = 0                                    ; // Type identifier for water rendering style *(v1.04)*
    FeatherWater = 0                                 ; // Whether to apply feathering to water boundaries *(v1.04)*
    ShowSoftWaterEdge = Yes                          ; // Whether to display soft edges for water boundaries *(v1.04)*
    DefaultStructureRubbleHeight = 10.0              ; // Default Z height for structure rubble *(v1.04)*

    ; Camera Settings
    CameraPitch = 37.5                               ; // Default pitch angle of camera in degrees *(v1.04)*
    CameraYaw = 0.0                                  ; // Default yaw angle of camera in degrees *(v1.04)*
    CameraHeight = 400                               ; // Default height of camera above terrain *(v1.04)*
    MinCameraHeight = 50                             ; // Minimum allowed camera height *(v1.04)*
    MaxCameraHeight = 690.0                          ; // Maximum allowed camera height *(v1.04)*
    CameraAdjustSpeed = 0.3                          ; // Speed at which camera adjusts to desired height *(v1.04)*
    ScrollAmountCutoff = 50.0                        ; // Threshold above which camera height is not updated while scrolling *(v1.04)*
    EnforceMaxCameraHeight = No                      ; // Whether to enforce maximum camera height while scrolling *(v1.04)*
    TerrainHeightAtEdgeOfMap = 100.0                 ; // Z height of terrain at map edges *(v1.04)*
    HorizontalScrollSpeedFactor = 1.0                ; // Multiplier for horizontal camera scroll speed *(v1.04)*
    VerticalScrollSpeedFactor = 1.0                  ; // Multiplier for vertical camera scroll speed *(v1.04)*
    KeyboardScrollSpeedFactor = 2.0                  ; // Multiplier for keyboard camera scroll speed *(v1.04)*
    KeyboardDefaultScrollSpeedFactor = 0.5           ; // Default multiplier for keyboard camera scrolling speed *(v1.04)*
    KeyboardCameraRotateSpeed = 0.1                  ; // Speed at which camera rotates with keyboard controls *(v1.04)*
    DrawSkyBox = No                                  ; // Whether to render the skybox *(v1.04)*
    SkyBoxPositionZ = 0.0                            ; // Z coordinate offset for skybox center *(v1.04)*
    SkyBoxScale = 4.5                                ; // Scaling factor for skybox size *(v1.04)*

    ; Lighting Settings
    UseShadowVolumes = No                            ; // Whether to use shadow volumes for dynamic shadows *(v1.04)*
    UseShadowDecals = No                             ; // Whether to use shadow decals for static shadows *(v1.04)*
    TimeOfDay = AFTERNOON                            ; // Default time of day setting *(v1.04)*
    Weather = NORMAL                                 ; // Default weather condition *(v1.04)*
    ForceModelsToFollowTimeOfDay = Yes               ; // Whether to force models to follow global time of day *(v1.04)*
    ForceModelsToFollowWeather = Yes                 ; // Whether to force models to follow global weather *(v1.04)*
    NumberGlobalLights = 3                           ; // Number of global lights for terrain and object lighting *(v1.04)*
    InfantryLightMorningScale = 1.5                  ; // Lighting scale for infantry visibility during morning *(v1.04)*
    InfantryLightAfternoonScale = 1.5                ; // Lighting scale for infantry visibility during afternoon *(v1.04)*
    InfantryLightEveningScale = 1.5                  ; // Lighting scale for infantry visibility during evening *(v1.04)*
    InfantryLightNightScale = 1.5                    ; // Lighting scale for infantry visibility during night *(v1.04)*

    ; Audio Settings
    AudioOn = Yes                                    ; // Master switch for all audio output *(v1.04)*
    MusicOn = Yes                                    ; // Whether background music is enabled *(v1.04)*
    SoundsOn = Yes                                   ; // Whether sound effects are enabled *(v1.04)*
    Sounds3DOn = Yes                                 ; // Whether 3D positional audio is enabled *(v1.04)*
    SpeechOn = Yes                                   ; // Whether unit speech and voice lines are enabled *(v1.04)*
    VideoOn = Yes                                    ; // Whether video playback is enabled *(v1.04)*
    DisableCameraMovements = No                      ; // Whether to disable camera movement controls *(v1.04)*

    ; Gameplay Settings
    UnitDamagedThreshold = 0.7                       ; // Health percentage threshold for damaged state *(v1.04)*
    UnitReallyDamagedThreshold = 0.35                ; // Health percentage threshold for really damaged state *(v1.04)*
    Gravity = -64.0                                  ; // Acceleration due to gravity *(v1.04)*
    GroundStiffness = 0.8                            ; // Stiffness factor for ground physics interactions *(v1.04)*
    StructureStiffness = 0.3                         ; // Stiffness factor for structure physics interactions *(v1.04)*
    PartitionCellSize = 0.0                          ; // Size of partition cells for spatial partitioning *(v1.04)*
    MaxTerrainTracks = 0                             ; // Maximum number of terrain track marks *(v1.04)*
    MakeTrackMarks = No                              ; // Whether vehicles generate track marks *(v1.04)*
    ParticleScale = 1.0                              ; // Global scaling factor for all particle effects *(v1.04)*
    MaxParticleCount = 5000                          ; // Maximum number of particles that can exist simultaneously *(v1.04)*
    MaxFieldParticleCount = 100                      ; // Maximum number of field-type particles on screen *(v1.04)*
    HistoricDamageLimit = 0                          ; // Duration for which historical damage information is retained (ms) *(v1.04)*
    ValuePerSupplyBox = 100                          ; // Base cash value provided by each supply box *(v1.04)*
    BuildSpeed = 1.5                                 ; // Global multiplier for construction and production speed *(v1.04)*
    MinDistFromEdgeOfMapForBuild = 20.0              ; // Minimum distance from map edge for building construction *(v1.04)*
    SupplyBuildBorder = 45.0                         ; // Minimum distance supply centers must maintain from supply sources *(v1.04)*
    AllowedHeightVariationForBuilding = 10.0         ; // Maximum allowed height variation for building construction *(v1.04)*
    MinLowEnergyProductionSpeed = 0.6                ; // Minimum production speed multiplier when energy is low *(v1.04)*
    MaxLowEnergyProductionSpeed = 0.8                ; // Maximum production speed multiplier when energy is low *(v1.04)*
    LowEnergyPenaltyModifier = 1.0                   ; // Modifier applied to low energy production speed penalties *(v1.04)*
    MultipleFactory = 0.0                            ; // Production speed bonus multiplier for multiple factories *(v1.04)*
    RefundPercent = 50%                              ; // Percentage of construction cost refunded when structure is sold/destroyed *(v1.04)*
    StealthFriendlyOpacity = 60%                     ; // Opacity level for friendly stealth units *(v1.04)*
    CommandCenterHealRange = 500.0                   ; // Range within which command center automatically heals units *(v1.04)*
    CommandCenterHealAmount = 0.01                   ; // Amount of health restored per logic frame by command center *(v1.04)*
    MaxLineBuildObjects = 50                         ; // Maximum number of objects in a line build *(v1.04)*
    MaxTunnelCapacity = 10                           ; // Maximum number of tunnel entrances in tunnel network *(v1.04)*
    StandardMinefieldDensity = 0.004                 ; // Density of mines in standard minefields *(v1.04)*
    StandardMinefieldDistance = 40.0                 ; // Standard distance or spacing for minefield placement *(v1.04)*
    MovementPenaltyDamageState = REALLYDAMAGED       ; // Damage state threshold for movement speed penalties *(v1.04)*

    ; Weapon and Veterancy Bonuses
    WeaponBonus = WeaponBonusSet                     ; // Weapon bonus configuration block *(v1.04)*
        ; WeaponBonus entries go here
    End
    HealthBonus_Veteran = 25%                        ; // Health bonus percentage for veteran-level units *(v1.04)*
    HealthBonus_Elite = 50%                          ; // Health bonus percentage for elite-level units *(v1.04)*
    HealthBonus_Heroic = 100%                        ; // Health bonus percentage for heroic-level units *(v1.04)*
    HumanSoloPlayerHealthBonus_Easy = 25%            ; // Health bonus for human player units on easy difficulty *(v1.04)*
    HumanSoloPlayerHealthBonus_Normal = 0%           ; // Health bonus for human player units on normal difficulty *(v1.04)*
    HumanSoloPlayerHealthBonus_Hard = -25%           ; // Health bonus for human player units on hard difficulty *(v1.04)*
    AISoloPlayerHealthBonus_Easy = -25%              ; // Health bonus for AI player units on easy difficulty *(v1.04)*
    AISoloPlayerHealthBonus_Normal = 0%              ; // Health bonus for AI player units on normal difficulty *(v1.04)*
    AISoloPlayerHealthBonus_Hard = 25%               ; // Health bonus for AI player units on hard difficulty *(v1.04)*

    ; Network Settings
    NetworkFPSHistoryLength = 30                     ; // Number of frame rate samples in network history buffer *(v1.04)*
    NetworkLatencyHistoryLength = 200                ; // Number of latency samples in network history buffer *(v1.04)*
    NetworkRunAheadMetricsTime = 500                 ; // Time window for calculating network run-ahead metrics (ms) *(v1.04)*
    NetworkCushionHistoryLength = 10                 ; // Number of cushion samples in network history buffer *(v1.04)*
    NetworkRunAheadSlack = 10                        ; // Slack time for network run-ahead calculations (ms) *(v1.04)*
    NetworkKeepAliveDelay = 20                       ; // Delay between network keep-alive packets (ms) *(v1.04)*
    NetworkDisconnectTime = 5000                     ; // Time without network communication before disconnection (ms) *(v1.04)*
    NetworkPlayerTimeoutTime = 60000                 ; // Time without player activity before timeout (ms) *(v1.04)*
    NetworkDisconnectScreenNotifyTime = 15000        ; // Time to display disconnection notification screen (ms) *(v1.04)*
    FirewallBehavior = 0                             ; // Firewall behavior mode for network connections *(v1.04)*
    FirewallPortOverride = 0                         ; // Override port number for firewall port mapping *(v1.04)*
    FirewallPortAllocationDelta = 0                  ; // Port number offset for firewall port allocation *(v1.04)*

    ; UI and Selection Settings
    GroupSelectMinSelectSize = 3                     ; // Minimum number of units for group selection sounds *(v1.04)*
    GroupSelectVolumeBase = 0.5                      ; // Base volume level for group selection sounds *(v1.04)*
    GroupSelectVolumeIncrement = 0.1                 ; // Volume increment per unit in group selection *(v1.04)*
    MaxUnitSelectSounds = 5                          ; // Maximum number of unit selection sounds that can play simultaneously *(v1.04)*
    SelectionFlashSaturationFactor = 1.0             ; // Saturation factor for selection flash effect *(v1.04)*
    SelectionFlashHouseColor = Yes                   ; // Whether selection flash uses player's house color *(v1.04)*
    GroupMoveClickToGatherAreaFactor = 1.0           ; // Factor determining size of gathering area for group move *(v1.04)*
    CameraAudibleRadius = 1000.0                     ; // Radius around camera where sounds are audible *(v1.04)*
    SellPercentage = 75%                             ; // Percentage of construction cost refunded when structure is sold *(v1.04)*
    BaseRegenHealthPercentPerSecond = 0.0%           ; // Base health regeneration rate per second *(v1.04)*
    BaseRegenDelay = 0                               ; // Delay after taking damage before regeneration begins (ms) *(v1.04)*
    ShakeSubtleIntensity = 0.5                       ; // Camera shake intensity for subtle shake effects *(v1.04)*
    ShakeNormalIntensity = 1.0                       ; // Camera shake intensity for normal shake effects *(v1.04)*
    ShakeStrongIntensity = 2.5                       ; // Camera shake intensity for strong shake effects *(v1.04)*
    ShakeSevereIntensity = 5.0                       ; // Camera shake intensity for severe shake effects *(v1.04)*
    ShakeCineExtremeIntensity = 8.0                  ; // Camera shake intensity for extreme cinematic shake effects *(v1.04)*
    ShakeCineInsaneIntensity = 12.0                  ; // Camera shake intensity for insane cinematic shake effects *(v1.04)*
    MaxShakeIntensity = 10.0                         ; // Maximum allowed camera shake intensity *(v1.04)*
    MaxShakeRange = 150.0                            ; // Maximum range at which camera shake effects are applied *(v1.04)*
End
```

## Notes

- The GameData block is a global configuration block that affects the entire game. Only one GameData block should exist per game instance, and it is loaded from `Data\INI\Default\GameData` (default values) and `Data\INI\GameData` (user overrides) directories.

- Properties in the GameData block are applied globally to all game systems. Changes to properties like `UnitDamagedThreshold` affect all objects that use damage states, while properties like `BuildSpeed` affect all construction and production systems.

- Many properties have default values that are set in the constructor. If a property is not specified in the INI file, the default value from the constructor is used.

- Some properties are only available in debug builds (marked with `#if defined(RTS_DEBUG)` in the source code) and will be ignored in release builds. These properties are documented in the Debug Settings section.

- The GameData block supports nested blocks for complex properties like `WeaponBonus`, which uses a `WeaponBonusSet` block structure.

- Properties that use percentage values (like `RefundPercent`, `HealthBonus_Veteran`) are parsed using `INI::parsePercentToReal`, which converts percentage values (e.g., "50%") to real values (e.g., 0.5).

- Color properties (like `ShroudColor`) use RGB color format, while some properties use color integers for specific color representations.

- Time-based properties use different units: milliseconds for delays and durations, seconds for some animation times, and frames for some internal timing values.

- The GameData block is loaded early in the game initialization process, before most other game systems are initialized. This ensures that global settings are available when other systems need them.

## Modder Recommended Use Scenarios

GameData is used to configure global game settings that affect the entire game experience. Common use scenarios include:

- **Performance Tuning**: Adjust rendering settings like `UseTrees`, `UseCloudMap`, `UseLightMap`, `TerrainLOD`, and `TextureReductionFactor` to optimize performance on lower-end systems or maximize visual quality on high-end systems.

- **Gameplay Balance**: Modify gameplay parameters like `BuildSpeed`, `ValuePerSupplyBox`, `RefundPercent`, `CommandCenterHealRange`, and `CommandCenterHealAmount` to adjust game balance and pacing.

- **Difficulty Adjustment**: Configure difficulty-specific health bonuses using `HumanSoloPlayerHealthBonus_*` and `AISoloPlayerHealthBonus_*` properties to fine-tune single-player difficulty levels.

- **Visual Customization**: Customize visual settings like `TimeOfDay`, `Weather`, lighting scales, camera settings, and particle effects to create specific visual atmospheres or match map themes.

- **Network Configuration**: Adjust network settings like `NetworkKeepAliveDelay`, `NetworkDisconnectTime`, and firewall behavior for optimal multiplayer performance.

- **UI Customization**: Modify UI and selection settings like `GroupSelectMinSelectSize`, `SelectionFlashSaturationFactor`, and camera shake intensities to customize the user interface experience.

- **Weapon Balance**: Configure weapon bonuses using the `WeaponBonus` block to adjust damage multipliers for weapons against different target types, allowing fine-tuning of combat effectiveness.

- **Veterancy System**: Adjust veterancy health bonuses using `HealthBonus_Veteran`, `HealthBonus_Elite`, and `HealthBonus_Heroic` to control how powerful units become as they gain experience.

## Source Files

- Header (GMX Zero Hour): [GlobalData.h](../../GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h)
- Source (GMX Zero Hour): [GlobalData.cpp](../../GeneralsMD/Code/GameEngine/Source/Common/GlobalData.cpp)
- Header (GMX Generals): [GlobalData.h](../../Generals/Code/GameEngine/Include/Common/GlobalData.h)
- Source (GMX Generals): [GlobalData.cpp](../../Generals/Code/GameEngine/Source/Common/GlobalData.cpp)

## Changes History

### Retail Generals 1.04 → Retail Zero Hour 1.04

No significant changes to GameData properties between Retail Generals 1.04 and Retail Zero Hour 1.04. All properties documented are available in both versions.

### Retail Zero Hour 1.04 → GMX Zero Hour

**Multiple new properties and features added** to expand GameData configuration capabilities:

- **`ObjectPlacementOpacity`**, **`ObjectPlacementShadows`** *(GMX Generals, GMX Zero Hour)*: Added properties for customizing build preview object opacity and shadows. See [`ObjectPlacementOpacity`](#objectplacementopacity) and [`ObjectPlacementShadows`](#objectplacementshadows) property documentation.

- **`DefaultStartingCash`** *(GMX Generals, GMX Zero Hour)*: Added property for configuring default starting cash amount. See [`DefaultStartingCash`](#defaultstartingcash) property documentation.

- **`StandardPublicBone`** *(GMX Generals, GMX Zero Hour)*: Added property for specifying standard public bones. See [`StandardPublicBone`](#standardpublicbone) property documentation.

- **`ShowMetrics`** *(GMX Generals, GMX Zero Hour)*: Added property for displaying performance metrics. See [`ShowMetrics`](#showmetrics) property documentation.

- **`DisableBuildPrerequisite`**, **`DisableBuildCost`**, **`DisableBuildTime`** *(GMX Zero Hour only)*: Added three debug properties for disabling build requirements. See Debug Settings section for details.

### Retail Generals 1.04 → GMX Generals

**Multiple new properties added** to expand GameData configuration capabilities:

- **`ObjectPlacementOpacity`**, **`ObjectPlacementShadows`** *(GMX Generals, GMX Zero Hour)*: Added properties for customizing build preview object opacity and shadows. See [`ObjectPlacementOpacity`](#objectplacementopacity) and [`ObjectPlacementShadows`](#objectplacementshadows) property documentation.

- **`DefaultStartingCash`** *(GMX Generals, GMX Zero Hour)*: Added property for configuring default starting cash amount. See [`DefaultStartingCash`](#defaultstartingcash) property documentation.

- **`StandardPublicBone`** *(GMX Generals, GMX Zero Hour)*: Added property for specifying standard public bones. See [`StandardPublicBone`](#standardpublicbone) property documentation.

- **`ShowMetrics`** *(GMX Generals, GMX Zero Hour)*: Added property for displaying performance metrics. See [`ShowMetrics`](#showmetrics) property documentation.

## Status

- **Documentation Status**: AI-generated
- **Last Updated**: 16/12/2025 by @AI
- **Certification**: 0/2 reviews

### Reviewers

- *(pending)*
- *(pending)*

## Document Log

- 16/12/2025 — AI — Initial document created.
