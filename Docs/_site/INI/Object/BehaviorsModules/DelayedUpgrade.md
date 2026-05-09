# DelayedUpgrade Module Documentation

## Overview
The `DelayedUpgrade` module is an upgrade module that broadcasts to all `DelayedUpgradeUpdate` modules to start counting down to execution after a specified delay time.

## Usage
This module is used to trigger delayed upgrade effects on objects. When the upgrade is applied, it searches for all `DelayedUpgradeUpdate` modules on the same object and sets their delay timers.

## Source Files
- **Header**: [DelayedUpgrade.h](../../Generals/Code/GameEngine/Include/GameLogic/Module/DelayedUpgrade.h)
- **Source**: [DelayedUpgrade.cpp](../../Generals/Code/GameEngine/Source/GameLogic/Object/Upgrade/DelayedUpgrade.cpp)

## Properties

### `DelayTime` *(v1.08)*
- **Type**: `UnsignedInt`
- **Description**: The delay time in game frames before the upgrade effect is triggered
- **Default**: 0
- **Example**: `DelayTime = 300` (5 seconds at 60 FPS)

## Template

```ini
Behavior = DelayedUpgrade ModuleTag_XX
    DelayTime = 300      ; // 5 second delay *(v1.08)*
End
```

## How It Works

1. **Upgrade Applied**: When the `DelayedUpgrade` upgrade is applied to an object
2. **Broadcast Delay**: The module searches through all behavior modules on the object
3. **Find DelayedUpgradeUpdate**: Looks for modules that implement `DelayedUpgradeUpdateInterface`
4. **Set Delay**: If the module is triggered by the upgrade's activation mask, it sets the delay timer
5. **Countdown**: The `DelayedUpgradeUpdate` modules then count down and execute their effects

## Integration with DelayedUpgradeUpdate

This module works in conjunction with `DelayedUpgradeUpdate` modules that implement the `DelayedUpgradeUpdateInterface`. The `DelayedUpgrade` module acts as a trigger that starts the countdown for these update modules.

## Notes

- This is a **Generals (v1.08)** module
- Requires compatible `DelayedUpgradeUpdate` modules to function
- The delay is specified in game frames, not real-time seconds
- The module uses upgrade activation masks to determine which update modules to trigger
