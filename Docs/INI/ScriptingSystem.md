# Scripting System Documentation

## Overview

The scripting system in Command & Conquer Generals / Zero Hour allows map creators to define game logic using scripts. Scripts are created in WorldBuilder and saved as `.scb` (Script Binary) files.

The **ScriptExportZH** tool allows you to decompile `.scb` files into human-readable YAML format for easier editing, and compile them back to binary format.

## File Format

### SCB Binary Format

SCB files use a chunk-based binary format:

1. **Header**: `CkMp` (4 bytes) - identifies the file type
2. **Symbol Table**: Maps string names to numeric IDs
3. **Data Chunks**: Nested chunks containing script data

### YAML Output Structure

When decompiled, scripts are organized as:

```
output_dir/
├── manifest.yaml           # Root manifest listing all players
├── Player1/
│   ├── list.yaml           # Player script list manifest
│   ├── Scripts/            # Ungrouped scripts
│   │   └── 000_ScriptName.yaml
│   └── Groups/             # Script groups
│       └── 000_GroupName/
│           ├── group.yaml  # Group manifest
│           └── 000_ScriptName.yaml
├── Player2/
│   └── ...
```

---

## Script Structure

### Script Properties *(v1.04)*

| Property | Type | Description | Default |
|----------|------|-------------|---------|
| `name` | String | Unique identifier for the script | Required |
| `comment` | String | General comment/description | Empty |
| `condition_comment` | String | Comment about conditions | Empty |
| `action_comment` | String | Comment about actions | Empty |
| `active` | Boolean | Whether script is enabled | `true` |
| `one_shot` | Boolean | Deactivate after first execution | `true` |
| `subroutine` | Boolean | Script is callable as subroutine | `false` |
| `delay_seconds` | Integer | Seconds to wait before evaluating | `0` |
| `difficulty.easy` | Boolean | Active on Easy difficulty | `true` |
| `difficulty.normal` | Boolean | Active on Normal difficulty | `true` |
| `difficulty.hard` | Boolean | Active on Hard difficulty | `true` |

### Script Group Properties *(v1.04)*

| Property | Type | Description | Default |
|----------|------|-------------|---------|
| `name` | String | Group name | Required |
| `active` | Boolean | Whether group is enabled | `true` |
| `subroutine` | Boolean | Group contains subroutines | `false` |

---

## Conditions

Conditions determine when a script's actions execute. Multiple conditions are combined with AND/OR logic.

### Condition Structure *(v1.04)*

```yaml
conditions:
  - or_clause:
    - condition:
        type: 4           # Condition type ID
        name: "CONDITION_TRUE"  # Internal name
        parameters:
          - type: BOOLEAN
            int_value: 1
```

### Condition Types *(v1.04)*

| ID | Name | Description |
|----|------|-------------|
| 0 | `CONDITION_FALSE` | Always false |
| 1 | `COUNTER` | Compare a counter value |
| 2 | `FLAG` | Check a flag's value |
| 3 | `CONDITION_TRUE` | Always true |
| 4 | `TIMER_EXPIRED` | Timer has finished |
| 5 | `PLAYER_ALL_DESTROYED` | Player has no units |
| 6 | `PLAYER_ALL_BUILDFACILITIES_DESTROYED` | Player has no production buildings |
| 7 | `TEAM_INSIDE_AREA_PARTIALLY` | Some team members in area |
| 8 | `TEAM_DESTROYED` | Team has no members |
| 9 | `CAMERA_MOVEMENT_FINISHED` | Camera path complete |
| 10 | `TEAM_HAS_UNITS` | Team has living members |
| 11 | `TEAM_STATE_IS` | Team is in specific state |
| 12 | `TEAM_STATE_IS_NOT` | Team is not in state |
| 13 | `NAMED_INSIDE_AREA` | Named unit is in area |
| 14 | `NAMED_OUTSIDE_AREA` | Named unit is outside area |
| 15 | `NAMED_DESTROYED` | Named unit is dead |
| 16 | `NAMED_NOT_DESTROYED` | Named unit is alive |
| 17 | `TEAM_INSIDE_AREA_ENTIRELY` | All team members in area |
| 18 | `TEAM_OUTSIDE_AREA_ENTIRELY` | All team members outside area |
| 19 | `NAMED_ATTACKED_BY_OBJECTTYPE` | Unit attacked by type |
| 20 | `TEAM_ATTACKED_BY_OBJECTTYPE` | Team attacked by type |
| 21 | `NAMED_ATTACKED_BY_PLAYER` | Unit attacked by player |
| 22 | `TEAM_ATTACKED_BY_PLAYER` | Team attacked by player |
| 23 | `BUILT_BY_PLAYER` | Player built object type |
| 24 | `NAMED_CREATED` | Named unit exists |
| 25 | `TEAM_CREATED` | Team exists |
| 26 | `PLAYER_HAS_CREDITS` | Compare player money |
| 27 | `NAMED_DISCOVERED` | Unit seen by player |
| 28 | `TEAM_DISCOVERED` | Team seen by player |
| 29 | `MISSION_ATTEMPTS` | Mission attempt count |
| 30 | `NAMED_OWNED_BY_PLAYER` | Unit owned by player |
| 31 | `TEAM_OWNED_BY_PLAYER` | Team owned by player |
| 32 | `PLAYER_HAS_N_OR_FEWER_BUILDINGS` | Player building count |
| 33 | `PLAYER_HAS_POWER` | Player has power |
| 34 | `NAMED_REACHED_WAYPOINTS_END` | Unit finished path |
| 35 | `TEAM_REACHED_WAYPOINTS_END` | Team finished path |
| 36 | `NAMED_SELECTED` | Unit is selected |
| 37 | `NAMED_ENTERED_AREA` | Unit entered area |
| 38 | `NAMED_EXITED_AREA` | Unit left area |
| 39-44 | Team area events | Various team area checks |
| 45-47 | Multiplayer victory/defeat | MP game end conditions |
| 48 | `PLAYER_HAS_NO_POWER` | Player lacks power |
| 49 | `HAS_FINISHED_VIDEO` | Video playback complete |
| 50 | `HAS_FINISHED_SPEECH` | Speech playback complete |
| 51 | `HAS_FINISHED_AUDIO` | Audio playback complete |
| 52-60 | Building/garrison conditions | Various building checks |
| 61-70 | Special power conditions | Power-related checks |
| 71-90 | Skirmish conditions | AI-specific conditions |

---

## Actions

Actions are commands executed when conditions are met.

### Action Structure *(v1.04)*

```yaml
actions:
  - action:
      type: 0           # Action type ID
      name: "DEBUG_MESSAGE_BOX"  # Internal name
      parameters:
        - type: TEXT_STRING
          string_value: "Hello World"
```

### Common Action Types *(v1.04)*

| ID | Name | Description |
|----|------|-------------|
| 0 | `DEBUG_MESSAGE_BOX` | Show debug message |
| 1 | `SET_FLAG` | Set flag true/false |
| 2 | `SET_COUNTER` | Set counter value |
| 3 | `VICTORY` | Announce victory |
| 4 | `DEFEAT` | Announce defeat |
| 5 | `NO_OP` | Do nothing |
| 6 | `SET_TIMER` | Start frame timer |
| 7 | `PLAY_SOUND_EFFECT` | Play sound |
| 8 | `ENABLE_SCRIPT` | Enable a script |
| 9 | `DISABLE_SCRIPT` | Disable a script |
| 10 | `CALL_SUBROUTINE` | Call subroutine script |
| 11 | `PLAY_SOUND_EFFECT_AT` | Play sound at location |
| 12 | `DAMAGE_MEMBERS_OF_TEAM` | Damage team members |
| 13 | `MOVE_TEAM_TO` | Move team to waypoint |
| 14 | `MOVE_CAMERA_TO` | Move camera to waypoint |
| 15-16 | Counter operations | Increment/decrement |
| 17-21 | Camera movement | Various camera controls |
| 22 | `SET_MILLISECOND_TIMER` | Start time-based timer |
| 23-25 | Camera modifiers | Camera effects |
| 26 | `CREATE_OBJECT` | Spawn object |
| 27-28 | Background sounds | Suspend/resume |
| 29-35 | Camera modifications | Zoom, pitch, etc. |
| 36-60 | Team/unit commands | Movement, attack, etc. |
| 61-100 | Game state | Player, building, UI |
| 100+ | Advanced actions | Special powers, AI, etc. |

---

## Parameter Types *(v1.04)*

Parameters define values for conditions and actions.

| Type | Description | YAML Format |
|------|-------------|-------------|
| `INT` | Integer value | `int_value: 42` |
| `REAL` | Floating point | `real_value: 3.14` |
| `BOOLEAN` | True/false | `int_value: 1` (1=true, 0=false) |
| `SCRIPT` | Script name | `string_value: "MyScript"` |
| `TEAM` | Team name | `string_value: "teamPlayer1"` |
| `COUNTER` | Counter name | `string_value: "MyCounter"` |
| `FLAG` | Flag name | `string_value: "MyFlag"` |
| `WAYPOINT` | Waypoint name | `string_value: "Waypoint1"` |
| `WAYPOINT_PATH` | Path name | `string_value: "Path1"` |
| `TRIGGER_AREA` | Trigger area name | `string_value: "Area1"` |
| `UNIT` | Named unit | `string_value: "Unit1"` |
| `OBJECT_TYPE` | Object template | `string_value: "AmericaTank"` |
| `SIDE` | Player/faction | `string_value: "Player1"` |
| `SOUND` | Sound event | `string_value: "GUIClick"` |
| `MUSIC` | Music track | `string_value: "Track01"` |
| `MOVIE` | Video file | `string_value: "Intro.bik"` |
| `DIALOG` | Speech dialog | `string_value: "EVA_01"` |
| `COORD3D` | 3D coordinate | See below |
| `ANGLE` | Angle in radians | `real_value: 1.5708` |
| `PERCENT` | Percentage | `real_value: 0.5` (50%) |
| `COMPARISON` | Comparison operator | `int_value: 2` (see below) |
| `RELATION` | Player relation | `int_value: 1` (see below) |
| `AI_MOOD` | AI attitude | `int_value: 2` (see below) |
| `COLOR` | ARGB color | `int_value: 0xFF0000` (red) |

### Coord3D Format

```yaml
- type: COORD3D
  coord:
    x: 100.0
    y: 200.0
    z: 0.0
```

### Comparison Values *(v1.04)*

| Value | Meaning |
|-------|---------|
| 0 | Less Than |
| 1 | Less Than or Equal |
| 2 | Equal |
| 3 | Greater Than or Equal |
| 4 | Greater Than |
| 5 | Not Equal |

### Relation Values *(v1.04)*

| Value | Meaning |
|-------|---------|
| 1 | Enemy |
| 0 | Neutral |
| 2 | Ally/Friend |

### AI Mood Values *(v1.04)*

| Value | Meaning |
|-------|---------|
| 0 | Sleep |
| 1 | Passive |
| 2 | Normal |
| 3 | Alert |
| 4 | Aggressive |

---

## Special Constants

### Team Names *(v1.04)*

| Constant | Meaning |
|----------|---------|
| `<This Team>` | Current team context |
| `<Any Team>` | Any available team |

### Player Names *(v1.04)*

| Constant | Meaning |
|----------|---------|
| `<This Player>` | Current player context |
| `<Local Player>` | Human player |
| `ThePlayer` | Main player |
| `<This Player's Enemy>` | Enemy of current player |

### Object Names *(v1.04)*

| Constant | Meaning |
|----------|---------|
| `<This Object>` | Current object context |
| `<Any Object>` | Any available object |

---

## Examples

### Simple Script

```yaml
name: "Victory Check"
comment: "Check if player has won"
active: true
one_shot: true
difficulty:
  easy: true
  normal: true
  hard: true

conditions:
  - or_clause:
    - condition:
        type: 5    # PLAYER_ALL_DESTROYED
        name: PLAYER_ALL_DESTROYED
        parameters:
          - type: SIDE
            string_value: "Player2"

actions:
  - action:
      type: 3    # VICTORY
      name: VICTORY
      parameters: []
```

### Timer Script

```yaml
name: "Countdown Timer"
active: true
one_shot: false
delay_seconds: 0

conditions:
  - or_clause:
    - condition:
        type: 4    # TIMER_EXPIRED
        name: TIMER_EXPIRED
        parameters:
          - type: COUNTER
            string_value: "MainTimer"

actions:
  - action:
      type: 6    # SET_TIMER
      name: SET_TIMER
      parameters:
        - type: COUNTER
          string_value: "MainTimer"
        - type: INT
          int_value: 300    # 10 seconds at 30 FPS
```

---

## Source Files

- **Header**: [`GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h)
- **Implementation**: [`GeneralsMD/Code/GameEngine/Source/GameLogic/ScriptEngine/Scripts.cpp`](../../GeneralsMD/Code/GameEngine/Source/GameLogic/ScriptEngine/Scripts.cpp)
- **Conditions**: [`GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptConditions.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptConditions.h)
- **Actions**: [`GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h`](../../GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h)

---

## Tool Usage

### Decompile SCB to YAML

```bash
ScriptExportZH decompile SkirmishScripts.scb ./output_folder
```

### Compile YAML to SCB

```bash
ScriptExportZH compile ./input_folder NewScripts.scb
```

---

## Notes

- Scripts are evaluated every frame
- Use `delay_seconds` to reduce evaluation frequency
- Subroutines can be called from other scripts using `CALL_SUBROUTINE`
- Scripts marked as `one_shot` are disabled after first execution
- Group organization is purely for editor convenience - all scripts run the same
