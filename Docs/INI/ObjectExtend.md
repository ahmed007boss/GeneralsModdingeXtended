# ObjectExtend INI Documentation

## Overview

**⚠️ Work In Progress (WIP) ⚠️**

The `ObjectExtend` class represents a mechanism for creating extended versions of existing game objects. Unlike `ObjectReskin` which creates visual variants, `ObjectExtend` creates functional extensions that inherit all properties from a base object and allow selective modification of modules, weapons, armor, and other properties.

**ObjectExtend** is an INI-based configuration system that allows modders to create new objects by extending existing ones, providing a powerful way to create variants without duplicating entire object definitions. This is particularly useful for creating enhanced versions, faction-specific variants, or objects with modified behaviors.

## Source Files

- Header: [`GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h`](../GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h) - `ThingTemplate` class definition
- Source: [`GeneralsMD/Code/GameEngine/Source/Common/Thing/ThingFactory.cpp`](../GeneralsMD/Code/GameEngine/Source/Common/Thing/ThingFactory.cpp) - `parseObjectExtendDefinition` implementation
- INI Parser: [`GeneralsMD/Code/GameEngine/Source/Common/INI/INIObject.cpp`](../GeneralsMD/Code/GameEngine/Source/Common/INI/INIObject.cpp) - `parseObjectExtendDefinition` entry point

## Usage

An ObjectExtend definition creates a new object that inherits all properties from an existing object, then allows selective modification of specific aspects. This is different from `ObjectReskin` which only changes visual appearance.

### Basic Syntax
```ini
ObjectExtend <NewObjectName> <BaseObjectName>
    ; Properties to modify or add
    ; Modules to remove or replace or overriding
    ; New weapons, armor, or behaviors
End
```

### Key Features
- **Full Inheritance**: Copies all properties from the base object
- **Selective Modification**: Allows modification of specific modules, weapons, armor
- **Module Replacement**: Can remove existing modules and add new ones
- **Extension Object Flag**: Marks the object as an extension for special handling

## Table of Contents

- [Overview](#overview)
- [Usage](#usage)
- [Properties](#properties)
- [Module Handling](#module-handling)
- [Examples](#examples)
- [Best Practices](#best-practices)
- [Notes](#notes)

## Properties




### Inherited Properties

All properties from the base object are inherited and can be overridden:

- **Basic Properties**: Name, display name, cost, build time
- **Combat Properties**: Weapons, armor, health, damage
- **Behavior Properties**: Modules, AI behavior, special powers
- **Visual Properties**: Models, textures, animations
- **Gameplay Properties**: Prerequisites, upgrades, abilities



### Module Operations

#### Removing Modules
```ini
ObjectExtend MyEnhancedUnit BaseUnit
    RemoveModule ModuleTag_DefaultBehavior
    RemoveModule ModuleTag_DefaultDraw
End
```

#### Adding or overriding New Modules
- As in a normal object definition, new tags may be added to extend the base module.
- If a tag with the same name already exists in the base module, the new definition will override the original.

## Examples

### Basic Extension
```ini
ObjectExtend ChinaAdvancedTank ChinaTank
    ; Inherits all properties from ChinaTank
    ; Can modify specific aspects
    BuildCost = 1200
    BuildTime = 45
End
```



## Best Practices

### 1. Clear Naming Convention
- Use descriptive names that indicate the relationship to the base object
- Examples: `ChinaAdvancedTank`, `USAStealthSoldier`, `GLATankDestroyer`

### 2. Minimal Modifications
- Only specify properties that differ from the base object
- Let inheritance handle unchanged properties

### 3. Module Management
- Use `RemoveModule` before adding replacement modules with the same tag
- Group related module changes together

### 4. Documentation
- Comment complex extensions to explain the modifications
- Document the purpose and differences from the base object

### 5. Testing
- Test extensions thoroughly to ensure all inherited properties work correctly
- Verify that module replacements function as expected

## Notes

### Differences from ObjectReskin
- **ObjectReskin**: Creates visual variants with different models/textures
- **ObjectExtend**: Creates functional variants with different behaviors/properties

### Module System Integration
- Extension objects have special module handling that allows replacement
- Non-extension objects will crash if duplicate module tags are found
- Use `RemoveModule` to cleanly replace existing modules

### Inheritance Behavior
- All properties are copied from the base object
- Properties specified in the extension override inherited values
- Modules can be selectively removed and replaced

### Error Handling
- Base object must exist and be defined before the extension
- Missing base objects will cause crashes with debug assertions
- Duplicate object names are not allowed (except in override mode)

### Performance Considerations
- Extensions are processed during INI loading
- No runtime performance impact compared to regular objects
- Memory usage is similar to regular objects

## Related Documentation

- [Object](Object.md) - Base object template system
- [ObjectReskin](ObjectReskin.md) - Visual variant system
- [Weapon](Weapon.md) - Weapon system for extended objects
- [Armor](Armor.md) - Armor system for extended objects
- [SpecialPower](SpecialPower.md) - Special powers for extended objects

---

**Note**: This documentation is part of the GMX (Generals Modding eXtended) system. ObjectExtend provides a powerful way to create object variants while maintaining code reusability and reducing duplication.

## Status

- **Documentation Status**: Work In Progress
- **Completion**: ~60%
- **Last Updated**: [Current Date]
- **Implementation Status**: Fully functional in GMX
