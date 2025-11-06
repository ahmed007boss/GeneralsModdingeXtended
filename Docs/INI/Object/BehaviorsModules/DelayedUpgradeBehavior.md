# DelayedUpgradeBehavior Module Documentation

## Overview
The `DelayedUpgradeBehavior` module is an update module that can trigger multiple upgrades and remove multiple upgrades after a specified delay time. It combines the functionality of both upgrade triggering and removal in a single, self-contained module.

## Usage
This module is used to create delayed upgrade effects that can both add and remove upgrades from objects or players after a specified time delay. It's more flexible than the original `DelayedUpgrade` module as it can handle multiple upgrades and removals in a single behavior.

## Source Files
- **Header**: [DelayedUpgradeBehavior.h](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DelayedUpgradeBehavior.h)
- **Source**: [DelayedUpgradeBehavior.cpp](../../GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Behavior/DelayedUpgradeBehavior.cpp)

## Properties

### `StartsActive` *(v1.04)*
- **Type**: `Bool`
- **Description**: If true, the behavior starts active and begins the delay countdown immediately when the object is created
- **Default**: `FALSE`
- **Example**: `StartsActive = true`

### `UpgradesToTrigger` *(v1.04)*
- **Type**: `std::vector<AsciiString>`
- **Description**: List of upgrade template names to apply when the delay timer expires. Can be both player upgrades and object upgrades
- **Default**: Empty vector
- **Example**: `UpgradesToTrigger = "UpgradeName1" "UpgradeName2" "UpgradeName3"`

### `UpgradesToRemove` *(v1.04)*
- **Type**: `std::vector<AsciiString>`
- **Description**: List of upgrade template names to remove when the delay timer expires. Can be both player upgrades and object upgrades
- **Default**: Empty vector
- **Example**: `UpgradesToRemove = "OldUpgrade1" "OldUpgrade2"`

### `TriggerAfterTime` *(v1.04)*
- **Type**: `UnsignedInt`
- **Description**: The delay time in game frames before the upgrades are triggered/removed
- **Default**: 0
- **Example**: `TriggerAfterTime = 300` (5 seconds at 60 FPS)

## UpgradeMux Integration

The module inherits from `UpgradeMux`, allowing it to be controlled by upgrade activation conditions:

### Upgrade Activation
- The behavior can be activated by applying specific upgrades to the object
- Uses standard `UpgradeMux` properties for activation conditions
- Can be configured to require all activation upgrades or just one

### Upgrade Removal
- When the controlling upgrade is removed, the behavior resets and can be triggered again
- The delay timer resets to 0 and the behavior goes back to sleep

## Template

```ini
Behavior = DelayedUpgradeBehavior ModuleTag_XX
    StartsActive = false                    ; // Start immediately or wait for upgrade *(v1.04)*
    UpgradesToTrigger = "Upgrade1" "Upgrade2" ; // Upgrades to apply after delay *(v1.04)*
    UpgradesToRemove = "OldUpgrade1"        ; // Upgrades to remove after delay *(v1.04)*
    TriggerAfterTime = 300                  ; // 5 second delay *(v1.04)*
    
    ; UpgradeMux properties
    RequiresAllTriggers = false             ; // Require all activation upgrades *(v1.04)*
    ; Add upgrade activation conditions here
End
```

## How It Works

1. **Initialization**: 
   - If `StartsActive = true`, the behavior immediately starts the delay countdown
   - If `StartsActive = false`, the behavior waits for upgrade activation

2. **Upgrade Activation**:
   - When the required upgrade(s) are applied, `upgradeImplementation()` is called
   - The delay timer is set based on `TriggerAfterTime`
   - The behavior starts updating every frame

3. **Countdown**:
   - The `update()` method checks if the delay time has expired
   - If not expired, continues sleeping until next frame
   - If expired, calls `triggerUpgrade()`

4. **Upgrade Execution**:
   - Applies all upgrades in `UpgradesToTrigger` list
   - Removes all upgrades in `UpgradesToRemove` list
   - Marks the trigger as completed and goes to sleep forever

5. **Reset**:
   - If the controlling upgrade is removed, the behavior resets
   - Can be triggered again if the upgrade is reapplied

## Differences from DelayedUpgrade

| Feature | DelayedUpgrade | DelayedUpgradeBehavior |
|---------|----------------|----------------------|
| **Purpose** | Triggers other DelayedUpgradeUpdate modules | Self-contained upgrade triggering/removal |
| **Upgrade Handling** | Broadcasts to other modules | Directly applies/removes upgrades |
| **Multiple Upgrades** | No | Yes, via vector |
| **Upgrade Removal** | No | Yes |
| **Self-Contained** | No, requires DelayedUpgradeUpdate modules | Yes |
| **UpgradeMux Integration** | No | Yes |
| **Version** | Generals (v1.08) | Generals Zero Hour (v1.04) |

## Examples

### Simple Delayed Upgrade
```ini
Behavior = DelayedUpgradeBehavior ModuleTag_01
    StartsActive = true
    UpgradesToTrigger = "WeaponUpgrade"
    TriggerAfterTime = 600  ; 10 second delay
End
```

### Complex Upgrade Chain
```ini
Behavior = DelayedUpgradeBehavior ModuleTag_02
    StartsActive = false
    UpgradesToTrigger = "AdvancedWeapon" "ArmorUpgrade"
    UpgradesToRemove = "BasicWeapon" "BasicArmor"
    TriggerAfterTime = 1200  ; 20 second delay
    
    ; Requires specific upgrade to activate
    RequiresAllTriggers = true
End
```

### Player Upgrade Trigger
```ini
Behavior = DelayedUpgradeBehavior ModuleTag_03
    StartsActive = false
    UpgradesToTrigger = "PlayerTechUpgrade"
    TriggerAfterTime = 1800  ; 30 second delay
End
```

## Notes

- This is a **Generals Zero Hour (v1.04)** module
- More flexible and powerful than the original `DelayedUpgrade` module
- Can handle both object upgrades and player upgrades
- Supports upgrade removal in addition to upgrade application
- Fully integrated with the upgrade system via `UpgradeMux`
- The delay is specified in game frames, not real-time seconds
- Once triggered, the behavior completes and goes to sleep forever
- Can be reset and retriggered if the controlling upgrade is removed and reapplied
