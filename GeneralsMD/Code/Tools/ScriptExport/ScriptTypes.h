/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// TheSuperHackers @feature AhmedSalah 12/01/2026 ScriptExport types for SCB decompilation/compilation

#pragma once

#include "StdAfx.h"

namespace ScriptExport
{

// Parameter types - must match the game's Parameter::ParameterType enum
enum class ParameterType : int32_t
{
    INT = 0,
    REAL,
    SCRIPT,
    TEAM,
    COUNTER,
    FLAG,
    COMPARISON,
    WAYPOINT,
    BOOLEAN,
    TRIGGER_AREA,
    TEXT_STRING,
    SIDE,
    SOUND,
    SCRIPT_SUBROUTINE,
    UNIT,
    OBJECT_TYPE,
    COORD3D,
    ANGLE,
    TEAM_STATE,
    RELATION,
    AI_MOOD,
    DIALOG,
    MUSIC,
    MOVIE,
    WAYPOINT_PATH,
    LOCALIZED_TEXT,
    BRIDGE,
    KIND_OF_PARAM,
    ATTACK_PRIORITY_SET,
    RADAR_EVENT_TYPE,
    SPECIAL_POWER,
    SCIENCE,
    UPGRADE,
    COMMANDBUTTON_ABILITY,
    BOUNDARY,
    BUILDABLE,
    SURFACES_ALLOWED,
    SHAKE_INTENSITY,
    COMMAND_BUTTON,
    FONT_NAME,
    OBJECT_STATUS,
    COMMANDBUTTON_ALL_ABILITIES,
    SKIRMISH_WAYPOINT_PATH,
    COLOR,
    EMOTICON,
    OBJECT_PANEL_FLAG,
    FACTION_NAME,
    OBJECT_TYPE_LIST,
    REVEALNAME,
    SCIENCE_AVAILABILITY,
    LEFT_OR_RIGHT,
    PERCENT,
    NUM_ITEMS
};

// Get the name of a parameter type
inline const char* getParameterTypeName(ParameterType type)
{
    static const char* names[] = {
        "INT", "REAL", "SCRIPT", "TEAM", "COUNTER", "FLAG", "COMPARISON",
        "WAYPOINT", "BOOLEAN", "TRIGGER_AREA", "TEXT_STRING", "SIDE", "SOUND",
        "SCRIPT_SUBROUTINE", "UNIT", "OBJECT_TYPE", "COORD3D", "ANGLE",
        "TEAM_STATE", "RELATION", "AI_MOOD", "DIALOG", "MUSIC", "MOVIE",
        "WAYPOINT_PATH", "LOCALIZED_TEXT", "BRIDGE", "KIND_OF_PARAM",
        "ATTACK_PRIORITY_SET", "RADAR_EVENT_TYPE", "SPECIAL_POWER", "SCIENCE",
        "UPGRADE", "COMMANDBUTTON_ABILITY", "BOUNDARY", "BUILDABLE",
        "SURFACES_ALLOWED", "SHAKE_INTENSITY", "COMMAND_BUTTON", "FONT_NAME",
        "OBJECT_STATUS", "COMMANDBUTTON_ALL_ABILITIES", "SKIRMISH_WAYPOINT_PATH",
        "COLOR", "EMOTICON", "OBJECT_PANEL_FLAG", "FACTION_NAME",
        "OBJECT_TYPE_LIST", "REVEALNAME", "SCIENCE_AVAILABILITY", "LEFT_OR_RIGHT",
        "PERCENT"
    };
    int index = static_cast<int>(type);
    if (index >= 0 && index < static_cast<int>(ParameterType::NUM_ITEMS))
        return names[index];
    return "UNKNOWN";
}

// Parse parameter type from name
inline ParameterType parseParameterType(const std::string& name)
{
    static const std::map<std::string, ParameterType> typeMap = {
        {"INT", ParameterType::INT},
        {"REAL", ParameterType::REAL},
        {"SCRIPT", ParameterType::SCRIPT},
        {"TEAM", ParameterType::TEAM},
        {"COUNTER", ParameterType::COUNTER},
        {"FLAG", ParameterType::FLAG},
        {"COMPARISON", ParameterType::COMPARISON},
        {"WAYPOINT", ParameterType::WAYPOINT},
        {"BOOLEAN", ParameterType::BOOLEAN},
        {"TRIGGER_AREA", ParameterType::TRIGGER_AREA},
        {"TEXT_STRING", ParameterType::TEXT_STRING},
        {"SIDE", ParameterType::SIDE},
        {"SOUND", ParameterType::SOUND},
        {"SCRIPT_SUBROUTINE", ParameterType::SCRIPT_SUBROUTINE},
        {"UNIT", ParameterType::UNIT},
        {"OBJECT_TYPE", ParameterType::OBJECT_TYPE},
        {"COORD3D", ParameterType::COORD3D},
        {"ANGLE", ParameterType::ANGLE},
        {"TEAM_STATE", ParameterType::TEAM_STATE},
        {"RELATION", ParameterType::RELATION},
        {"AI_MOOD", ParameterType::AI_MOOD},
        {"DIALOG", ParameterType::DIALOG},
        {"MUSIC", ParameterType::MUSIC},
        {"MOVIE", ParameterType::MOVIE},
        {"WAYPOINT_PATH", ParameterType::WAYPOINT_PATH},
        {"LOCALIZED_TEXT", ParameterType::LOCALIZED_TEXT},
        {"BRIDGE", ParameterType::BRIDGE},
        {"KIND_OF_PARAM", ParameterType::KIND_OF_PARAM},
        {"ATTACK_PRIORITY_SET", ParameterType::ATTACK_PRIORITY_SET},
        {"RADAR_EVENT_TYPE", ParameterType::RADAR_EVENT_TYPE},
        {"SPECIAL_POWER", ParameterType::SPECIAL_POWER},
        {"SCIENCE", ParameterType::SCIENCE},
        {"UPGRADE", ParameterType::UPGRADE},
        {"COMMANDBUTTON_ABILITY", ParameterType::COMMANDBUTTON_ABILITY},
        {"BOUNDARY", ParameterType::BOUNDARY},
        {"BUILDABLE", ParameterType::BUILDABLE},
        {"SURFACES_ALLOWED", ParameterType::SURFACES_ALLOWED},
        {"SHAKE_INTENSITY", ParameterType::SHAKE_INTENSITY},
        {"COMMAND_BUTTON", ParameterType::COMMAND_BUTTON},
        {"FONT_NAME", ParameterType::FONT_NAME},
        {"OBJECT_STATUS", ParameterType::OBJECT_STATUS},
        {"COMMANDBUTTON_ALL_ABILITIES", ParameterType::COMMANDBUTTON_ALL_ABILITIES},
        {"SKIRMISH_WAYPOINT_PATH", ParameterType::SKIRMISH_WAYPOINT_PATH},
        {"COLOR", ParameterType::COLOR},
        {"EMOTICON", ParameterType::EMOTICON},
        {"OBJECT_PANEL_FLAG", ParameterType::OBJECT_PANEL_FLAG},
        {"FACTION_NAME", ParameterType::FACTION_NAME},
        {"OBJECT_TYPE_LIST", ParameterType::OBJECT_TYPE_LIST},
        {"REVEALNAME", ParameterType::REVEALNAME},
        {"SCIENCE_AVAILABILITY", ParameterType::SCIENCE_AVAILABILITY},
        {"LEFT_OR_RIGHT", ParameterType::LEFT_OR_RIGHT},
        {"PERCENT", ParameterType::PERCENT}
    };
    auto it = typeMap.find(name);
    if (it != typeMap.end())
        return it->second;
    return ParameterType::INT;
}

// Dict data types - must match game's Dict::DataType
enum class DictDataType : int32_t
{
    DICT_BOOL = 0,
    DICT_INT = 1,
    DICT_REAL = 2,
    DICT_ASCIISTRING = 3,
    DICT_UNICODESTRING = 4
};

// Dictionary entry - stores a key-value pair
struct DictEntry
{
    std::string key;           // Key name (will be stored in symbol table)
    DictDataType type;
    bool boolValue = false;
    int32_t intValue = 0;
    float realValue = 0.0f;
    std::string asciiValue;
    std::wstring unicodeValue;
};

// Dictionary - collection of key-value pairs
struct Dict
{
    std::vector<DictEntry> entries;
};

// 3D coordinate structure (float)
struct Coord3D
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

// 3D coordinate structure (integer)
struct ICoord3D
{
    int32_t x = 0;
    int32_t y = 0;
    int32_t z = 0;
};

// Parameter data
struct Parameter
{
    ParameterType type = ParameterType::INT;
    int32_t intValue = 0;
    float realValue = 0.0f;
    std::string stringValue;
    Coord3D coord;
};

// Condition data
struct Condition
{
    int32_t conditionType = 0;
    std::string conditionName; // Internal name key
    std::vector<Parameter> parameters;
    uint16_t version = 0;      // Chunk version for round-trip
};

// OrCondition - contains AND'd conditions
struct OrCondition
{
    std::vector<Condition> andConditions;
    uint16_t version = 0;      // Chunk version for round-trip
};

// Script action data  
struct ScriptAction
{
    int32_t actionType = 0;
    std::string actionName; // Internal name key
    std::vector<Parameter> parameters;
    uint16_t version = 0;      // Chunk version for round-trip
};

// Script data
struct Script
{
    std::string name;
    std::string comment;
    std::string conditionComment;
    std::string actionComment;
    bool isActive = true;
    bool isOneShot = true;
    bool easy = true;
    bool normal = true;
    bool hard = true;
    bool isSubroutine = false;
    int32_t delayEvaluationSeconds = 0;
    std::vector<OrCondition> conditions; // OR'd conditions
    std::vector<ScriptAction> actions;
    std::vector<ScriptAction> falseActions;
    uint16_t version = 0;      // Chunk version for round-trip
};

// Script group data
struct ScriptGroup
{
    std::string name;
    bool isActive = true;
    bool isSubroutine = false;
    std::vector<Script> scripts;
    uint16_t version = 0;      // Chunk version for round-trip
};

// Script list data - contains scripts for one player
struct ScriptList
{
    std::vector<ScriptGroup> groups;
    std::vector<Script> scripts; // Ungrouped scripts
    uint16_t version = 0;      // Chunk version for round-trip
};

// Player info from ScriptsPlayers chunk
struct PlayerInfo
{
    std::string name;
    Dict sideDict;             // Optional side dictionary
    bool hasSideDict = false;
};

// Map object data
struct MapObject
{
    Coord3D location;
    float angle = 0.0f;
    int32_t flags = 0;
    std::string name;
    Dict properties;
    uint16_t version = 0;      // Chunk version for round-trip
};

// Polygon trigger data
struct PolygonTrigger
{
    std::string name;
    int32_t id = 0;
    bool isWaterArea = false;
    bool isRiver = false;
    int32_t riverStart = 0;
    std::vector<ICoord3D> points;
};

// Waypoint link data
struct WaypointLink
{
    int32_t waypointID1 = 0;
    int32_t waypointID2 = 0;
};

// Complete scripts data from an SCB file - stores EVERYTHING for perfect round-trip
struct ScriptsData
{
    // Symbol table - ordered list to preserve IDs
    std::vector<std::string> symbolList;       // Symbols in order (index = ID)
    std::map<std::string, uint32_t> symbolToId; // Name to ID lookup
    std::map<uint32_t, std::string> idToSymbol; // ID to name lookup
    
    // PlayerScriptsList chunk
    std::vector<ScriptList> playerScripts;     // One list per player
    uint16_t playerScriptsListVersion = 1;     // Chunk version
    
    // ScriptsPlayers chunk
    std::vector<PlayerInfo> players;           // Player names and optional dicts
    uint16_t scriptsPlayersVersion = 2;        // Chunk version
    bool hasSideDicts = false;                 // doSides flag
    
    // ObjectsList chunk
    std::vector<MapObject> objects;
    uint16_t objectsListVersion = 3;           // Chunk version
    
    // PolygonTriggers chunk
    std::vector<PolygonTrigger> polygonTriggers;
    uint16_t polygonTriggersVersion = 3;       // Chunk version
    
    // ScriptTeams chunk
    std::vector<Dict> teams;                   // Team dictionaries
    uint16_t scriptTeamsVersion = 1;           // Chunk version
    
    // WaypointsList chunk
    std::vector<WaypointLink> waypointLinks;
    uint16_t waypointsListVersion = 1;         // Chunk version
    
    // Legacy compatibility fields
    std::vector<std::string> playerNames;      // Simple player names list
    std::map<uint32_t, std::string> symbolTable; // Legacy ID to name mapping
};

} // namespace ScriptExport
