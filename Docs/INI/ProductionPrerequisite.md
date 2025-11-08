# ProductionPrerequisite INI Documentation

## Overview

ProductionPrerequisite blocks define requirements for building objects or enabling commands. They can require specific object(s) (optionally in OR-groups) and sciences. Objects declare `Prerequisites` blocks that compile into one or more `ProductionPrerequisite` entries.

## Source Files

- Header: `GeneralsMD/Code/GameEngine/Include/Common/ProductionPrerequisite.h`
- Source: `GeneralsMD/Code/GameEngine/Source/Common/RTS/ProductionPrerequisite.cpp`
- Parsing within `Object`: `Generals/Code/GameEngine/Source/Common/Thing/Object.cpp` (`parsePrerequisites`)

## Usage

- Appears inside `Object` templates as a nested block:
  - `Prerequisites` → `Object` and/or `Science` lines
- `Object` entries listed on the same line are treated as OR with the previous within that prerequisite group.
- Multiple lines create multiple required groups (AND across groups, OR within a group).

## Block Format

### Prerequisites (v1.04)
- Type: Block with entries
- Description: Defines one or more prerequisite groups
- Entries:
  - `Object = <ObjA> <ObjB> ...` – A group; owning at least one of listed objects satisfies this group
  - `Science = <ScienceType>` – Requires the specified science

## Examples

### Single Building Requirement
```
Prerequisites
  Object = AmericaBarracks ChinaWarFactory
  Object = GLABarracks GLAWarFactory
End
```

### OR Building Group + Science
```
Prerequisites
  Object = AmericaWarFactory ChinaWarFactory
  Science = SCIENCE_AdvancedTraining
End
```

### Multiple AND Groups
```
Prerequisites
  Object = CommandCenter
  Object = StrategyCenter PropagandaCenter
End
```

## Notes

- Objects are resolved to templates after all templates load. Invalid names cause asserts during development.
- GUI builds a user-readable list via `getRequiresList`, combining OR groups as "A or B".
- Cheats or debug modes may allow ignoring prereqs; gameplay systems query satisfaction through `isSatisfied`.

## Template

```
; Within an Object = template
Prerequisites
  Object = <TemplateA> <TemplateB>      ; OR group: either satisfies the group
  Object = <TemplateC>                  ; AND with previous groups
  Science = SCIENCE_<Name>              ; requires specific science
End
```

