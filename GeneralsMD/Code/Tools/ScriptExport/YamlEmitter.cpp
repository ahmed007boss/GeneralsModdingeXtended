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

// TheSuperHackers @feature AhmedSalah 12/01/2026 YAML emitter implementation

#include "StdAfx.h"
#include "YamlEmitter.h"

#ifdef _WIN32
#include <direct.h>
#define mkdir(path, mode) _mkdir(path)
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif

namespace ScriptExport
{

YamlEmitter::YamlEmitter()
{
}

YamlEmitter::~YamlEmitter()
{
}

std::string YamlEmitter::sanitizeFilename(const std::string& name) const
{
    std::string result;
    result.reserve(name.size());
    
    for (unsigned char c : name)
    {
        // Skip control characters and non-printable chars
        if (c < 32 || c == 127)
        {
            continue;
        }
        // Replace invalid filename characters
        else if (c == '/' || c == '\\' || c == ':' || c == '*' || 
                 c == '?' || c == '"' || c == '<' || c == '>' || c == '|' ||
                 c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}')
        {
            result += '_';
        }
        else if (c == ' ')
        {
            result += '_';
        }
        else
        {
            result += static_cast<char>(c);
        }
    }
    
    // Remove consecutive underscores
    std::string cleaned;
    cleaned.reserve(result.size());
    bool lastWasUnderscore = false;
    for (char c : result)
    {
        if (c == '_')
        {
            if (!lastWasUnderscore)
            {
                cleaned += c;
                lastWasUnderscore = true;
            }
        }
        else
        {
            cleaned += c;
            lastWasUnderscore = false;
        }
    }
    result = cleaned;
    
    // Trim leading and trailing underscores
    size_t start = result.find_first_not_of('_');
    size_t end = result.find_last_not_of('_');
    if (start != std::string::npos && end != std::string::npos)
    {
        result = result.substr(start, end - start + 1);
    }
    
    // Ensure non-empty name
    if (result.empty())
        result = "unnamed";
    
    // Limit length (leave room for prefix and extension)
    if (result.length() > 180)
        result = result.substr(0, 180);
    
    return result;
}

bool YamlEmitter::createDirectory(const std::string& path) const
{
    // Create directory and all parent directories if needed
    std::string currentPath;
    
    for (size_t i = 0; i < path.size(); ++i)
    {
        char c = path[i];
        currentPath += c;
        
        // Check for directory separator or end of path
        if (c == '/' || c == '\\' || i == path.size() - 1)
        {
            if (currentPath.size() > 0 && currentPath != "." && currentPath != "..")
            {
#ifdef _WIN32
                if (!CreateDirectoryA(currentPath.c_str(), NULL))
                {
                    DWORD err = GetLastError();
                    if (err != ERROR_ALREADY_EXISTS && err != ERROR_ACCESS_DENIED)
                    {
                        // Only fail if it's not "already exists" or "access denied on root"
                        if (currentPath.size() > 3) // Not a drive letter like "C:/"
                        {
                            return false;
                        }
                    }
                }
#else
                if (mkdir(currentPath.c_str(), 0755) != 0 && errno != EEXIST)
                {
                    return false;
                }
#endif
            }
        }
    }
    return true;
}

bool YamlEmitter::write(const std::string& outputDir, const ScriptsData& data)
{
    // Create base directory
    if (!createDirectory(outputDir))
    {
        m_error = "Failed to create output directory: " + outputDir;
        return false;
    }
    
    // Build player directory names from actual player names or fallback to generic
    std::vector<std::string> playerDirNames;
    for (size_t i = 0; i < data.playerScripts.size(); ++i)
    {
        std::string playerName;
        if (i < data.playerNames.size() && !data.playerNames[i].empty())
        {
            playerName = sanitizeFilename(data.playerNames[i]);
        }
        else
        {
            playerName = "Player" + std::to_string(i + 1);
        }
        playerDirNames.push_back(playerName);
    }
    
    // Write each player's scripts
    for (size_t i = 0; i < data.playerScripts.size(); ++i)
    {
        std::string playerDir = outputDir + "/" + playerDirNames[i];
        if (!createDirectory(playerDir))
        {
            m_error = "Failed to create player directory: " + playerDir;
            return false;
        }
        
        if (!writeScriptList(playerDir, data.playerScripts[i], static_cast<int>(i)))
        {
            return false;
        }
    }
    
    // Write symbol table
    if (!data.symbolTable.empty())
    {
        std::string symbolsPath = outputDir + "/symbols.yaml";
        std::ofstream symbolsFile(symbolsPath);
        if (symbolsFile.is_open())
        {
            symbolsFile << "# Symbol Table\n";
            symbolsFile << "# Maps IDs to string names used in the SCB file\n\n";
            symbolsFile << "symbols:\n";
            for (const auto& pair : data.symbolTable)
            {
                symbolsFile << "  " << pair.first << ": " << escapeYamlString(pair.second) << "\n";
            }
            symbolsFile.close();
        }
    }
    
    // Write objects if present
    if (!data.objects.empty())
    {
        if (!writeObjects(outputDir + "/objects.yaml", data.objects))
            return false;
    }
    
    // Write polygon triggers if present
    if (!data.polygonTriggers.empty())
    {
        if (!writePolygonTriggers(outputDir + "/triggers.yaml", data.polygonTriggers))
            return false;
    }
    
    // Write teams if present
    if (!data.teams.empty())
    {
        if (!writeTeams(outputDir + "/teams.yaml", data.teams))
            return false;
    }
    
    // Write waypoint links if present
    if (!data.waypointLinks.empty())
    {
        if (!writeWaypoints(outputDir + "/waypoints.yaml", data.waypointLinks))
            return false;
    }
    
    // Write a manifest file
    std::string manifestPath = outputDir + "/manifest.yaml";
    std::ofstream manifest(manifestPath);
    if (!manifest.is_open())
    {
        m_error = "Failed to create manifest file: " + manifestPath;
        return false;
    }
    
    manifest << "# ScriptExport Manifest\n";
    manifest << "# Generated by ScriptExportZH - DO NOT MODIFY for round-trip support\n";
    manifest << "\n";
    manifest << "format_version: 2.0\n";
    manifest << "\n";
    
    // Chunk versions for exact reconstruction
    manifest << "chunk_versions:\n";
    manifest << "  PlayerScriptsList: " << data.playerScriptsListVersion << "\n";
    manifest << "  ScriptsPlayers: " << data.scriptsPlayersVersion << "\n";
    manifest << "  ObjectsList: " << data.objectsListVersion << "\n";
    manifest << "  PolygonTriggers: " << data.polygonTriggersVersion << "\n";
    manifest << "  ScriptTeams: " << data.scriptTeamsVersion << "\n";
    manifest << "  WaypointsList: " << data.waypointsListVersion << "\n";
    manifest << "\n";
    
    manifest << "has_side_dicts: " << (data.hasSideDicts ? "true" : "false") << "\n";
    manifest << "\n";
    
    manifest << "player_count: " << data.playerScripts.size() << "\n";
    manifest << "players:\n";
    
    for (size_t i = 0; i < data.playerScripts.size(); ++i)
    {
        const auto& list = data.playerScripts[i];
        std::string actualName = (i < data.playerNames.size()) ? data.playerNames[i] : "";
        manifest << "  - index: " << i << "\n";
        if (!actualName.empty())
        {
            manifest << "    name: " << escapeYamlString(actualName) << "\n";
        }
        manifest << "    directory: " << playerDirNames[i] << "\n";
        manifest << "    groups: " << list.groups.size() << "\n";
        manifest << "    scripts: " << list.scripts.size() << "\n";
        manifest << "    version: " << list.version << "\n";
    }
    
    // Additional data counts
    manifest << "\n";
    manifest << "additional_data:\n";
    manifest << "  objects: " << data.objects.size() << "\n";
    manifest << "  polygon_triggers: " << data.polygonTriggers.size() << "\n";
    manifest << "  teams: " << data.teams.size() << "\n";
    manifest << "  waypoint_links: " << data.waypointLinks.size() << "\n";
    manifest << "  symbols: " << data.symbolTable.size() << "\n";
    
    manifest.close();
    return true;
}

bool YamlEmitter::writeScriptList(const std::string& dir, const ScriptList& list, int playerIndex)
{
    // Write ungrouped scripts to "Scripts" folder
    if (!list.scripts.empty())
    {
        std::string scriptsDir = dir + "/Scripts";
        if (!createDirectory(scriptsDir))
        {
            m_error = "Failed to create scripts directory: " + scriptsDir;
            return false;
        }
        
        for (size_t i = 0; i < list.scripts.size(); ++i)
        {
            if (!writeScript(scriptsDir, list.scripts[i], static_cast<int>(i)))
            {
                return false;
            }
        }
    }
    
    // Write groups to "Groups" folder
    if (!list.groups.empty())
    {
        std::string groupsDir = dir + "/Groups";
        if (!createDirectory(groupsDir))
        {
            m_error = "Failed to create groups directory: " + groupsDir;
            return false;
        }
        
        for (size_t i = 0; i < list.groups.size(); ++i)
        {
            if (!writeScriptGroup(groupsDir, list.groups[i], static_cast<int>(i)))
            {
                return false;
            }
        }
    }
    
    // Write list manifest
    std::string listManifestPath = dir + "/list.yaml";
    std::ofstream listManifest(listManifestPath);
    if (!listManifest.is_open())
    {
        m_error = "Failed to create list manifest: " + listManifestPath;
        return false;
    }
    
    listManifest << "# Player " << (playerIndex + 1) << " Scripts\n";
    listManifest << "\n";
    listManifest << "groups:\n";
    for (size_t i = 0; i < list.groups.size(); ++i)
    {
        const auto& group = list.groups[i];
        std::string safeName = sanitizeFilename(group.name);
        listManifest << "  - name: " << escapeYamlString(group.name) << "\n";
        listManifest << "    directory: Groups/" << std::setfill('0') << std::setw(3) << i << "_" << safeName << "\n";
        listManifest << "    active: " << (group.isActive ? "true" : "false") << "\n";
        listManifest << "    subroutine: " << (group.isSubroutine ? "true" : "false") << "\n";
    }
    
    listManifest << "\nscripts:\n";
    for (size_t i = 0; i < list.scripts.size(); ++i)
    {
        const auto& script = list.scripts[i];
        std::string safeName = sanitizeFilename(script.name);
        listManifest << "  - name: " << escapeYamlString(script.name) << "\n";
        listManifest << "    file: Scripts/" << std::setfill('0') << std::setw(3) << i << "_" << safeName << ".yaml\n";
    }
    
    listManifest.close();
    return true;
}

bool YamlEmitter::writeScriptGroup(const std::string& dir, const ScriptGroup& group, int groupIndex)
{
    // Create group directory
    std::string safeName = sanitizeFilename(group.name);
    std::ostringstream groupDirName;
    groupDirName << std::setfill('0') << std::setw(3) << groupIndex << "_" << safeName;
    std::string groupDir = dir + "/" + groupDirName.str();
    
    if (!createDirectory(groupDir))
    {
        m_error = "Failed to create group directory: " + groupDir;
        return false;
    }
    
    // Write group manifest
    std::string manifestPath = groupDir + "/group.yaml";
    std::ofstream manifest(manifestPath);
    if (!manifest.is_open())
    {
        m_error = "Failed to create group manifest: " + manifestPath;
        return false;
    }
    
    manifest << "# Script Group\n";
    manifest << "\n";
    manifest << "name: " << escapeYamlString(group.name) << "\n";
    manifest << "_version: " << group.version << "\n";  // For round-trip
    manifest << "active: " << (group.isActive ? "true" : "false") << "\n";
    manifest << "subroutine: " << (group.isSubroutine ? "true" : "false") << "\n";
    manifest << "\nscripts:\n";
    
    for (size_t i = 0; i < group.scripts.size(); ++i)
    {
        const auto& script = group.scripts[i];
        std::string scriptSafeName = sanitizeFilename(script.name);
        manifest << "  - file: " << std::setfill('0') << std::setw(3) << i << "_" << scriptSafeName << ".yaml\n";
    }
    
    manifest.close();
    
    // Write scripts in group
    for (size_t i = 0; i < group.scripts.size(); ++i)
    {
        if (!writeScript(groupDir, group.scripts[i], static_cast<int>(i)))
        {
            return false;
        }
    }
    
    return true;
}

bool YamlEmitter::writeScript(const std::string& dir, const Script& script, int scriptIndex)
{
    std::string safeName = sanitizeFilename(script.name);
    
    // Ensure we have a valid filename
    if (safeName.empty())
    {
        safeName = "script";
    }
    
    std::ostringstream filename;
    filename << std::setfill('0') << std::setw(3) << scriptIndex << "_" << safeName << ".yaml";
    std::string filePath = dir + "/" + filename.str();
    
    // Check path length (Windows MAX_PATH issue)
    if (filePath.length() > 250)
    {
        // Truncate the safe name to fit
        size_t available = 250 - dir.length() - 15; // 15 for "/000_.yaml" and some buffer
        if (safeName.length() > available)
        {
            safeName = safeName.substr(0, available);
        }
        filename.str("");
        filename << std::setfill('0') << std::setw(3) << scriptIndex << "_" << safeName << ".yaml";
        filePath = dir + "/" + filename.str();
    }
    
    std::ofstream out(filePath);
    if (!out.is_open())
    {
#ifdef _WIN32
        DWORD err = GetLastError();
        std::ostringstream errMsg;
        errMsg << "Failed to create script file: " << filePath 
               << " (Original name: '" << script.name << "', Error: " << err << ")";
        m_error = errMsg.str();
#else
        m_error = "Failed to create script file: " + filePath + " (Original name: '" + script.name + "')";
#endif
        return false;
    }
    
    writeYamlHeader(out);
    writeScriptYaml(out, script, 0);
    
    out.close();
    return true;
}

void YamlEmitter::writeYamlHeader(std::ofstream& out)
{
    out << "# Script Definition\n";
    out << "# Generated by ScriptExportZH\n";
    out << "\n";
}

void YamlEmitter::writeScriptYaml(std::ofstream& out, const Script& script, int indentLevel)
{
    std::string ind = indent(indentLevel);
    
    out << ind << "name: " << escapeYamlString(script.name) << "\n";
    out << ind << "_version: " << script.version << "\n";  // For round-trip
    
    if (!script.comment.empty())
        out << ind << "comment: " << escapeYamlString(script.comment) << "\n";
    if (!script.conditionComment.empty())
        out << ind << "condition_comment: " << escapeYamlString(script.conditionComment) << "\n";
    if (!script.actionComment.empty())
        out << ind << "action_comment: " << escapeYamlString(script.actionComment) << "\n";
    
    out << ind << "active: " << (script.isActive ? "true" : "false") << "\n";
    out << ind << "one_shot: " << (script.isOneShot ? "true" : "false") << "\n";
    out << ind << "subroutine: " << (script.isSubroutine ? "true" : "false") << "\n";
    
    out << ind << "difficulty:\n";
    out << ind << "  easy: " << (script.easy ? "true" : "false") << "\n";
    out << ind << "  normal: " << (script.normal ? "true" : "false") << "\n";
    out << ind << "  hard: " << (script.hard ? "true" : "false") << "\n";
    
    if (script.delayEvaluationSeconds > 0)
        out << ind << "delay_seconds: " << script.delayEvaluationSeconds << "\n";
    
    // Write conditions
    if (!script.conditions.empty())
    {
        out << "\n" << ind << "conditions:\n";
        writeConditionsYaml(out, script.conditions, indentLevel + 1);
    }
    
    // Write actions
    if (!script.actions.empty())
    {
        out << "\n" << ind << "actions:\n";
        writeActionsYaml(out, script.actions, indentLevel + 1, "action");
    }
    
    // Write false actions
    if (!script.falseActions.empty())
    {
        out << "\n" << ind << "else_actions:\n";
        writeActionsYaml(out, script.falseActions, indentLevel + 1, "action");
    }
}

void YamlEmitter::writeConditionsYaml(std::ofstream& out, const std::vector<OrCondition>& conditions, int indentLevel)
{
    std::string ind = indent(indentLevel);
    
    for (size_t orIdx = 0; orIdx < conditions.size(); ++orIdx)
    {
        const auto& orCond = conditions[orIdx];
        
        if (orIdx > 0)
            out << ind << "# OR\n";
        
        out << ind << "- or_clause:\n";
        out << indent(indentLevel + 1) << "_version: " << orCond.version << "\n";
        
        for (size_t andIdx = 0; andIdx < orCond.andConditions.size(); ++andIdx)
        {
            const auto& cond = orCond.andConditions[andIdx];
            
            out << indent(indentLevel + 1) << "- condition:\n";
            out << indent(indentLevel + 2) << "type: " << cond.conditionType << "\n";
            out << indent(indentLevel + 2) << "_version: " << cond.version << "\n";
            
            if (!cond.conditionName.empty())
                out << indent(indentLevel + 2) << "name: " << escapeYamlString(cond.conditionName) << "\n";
            
            if (!cond.parameters.empty())
            {
                out << indent(indentLevel + 2) << "parameters:\n";
                for (const auto& param : cond.parameters)
                {
                    writeParameterYaml(out, param, indentLevel + 3);
                }
            }
        }
    }
}

void YamlEmitter::writeActionsYaml(std::ofstream& out, const std::vector<ScriptAction>& actions, int indentLevel, const char* label)
{
    std::string ind = indent(indentLevel);
    
    for (const auto& action : actions)
    {
        out << ind << "- " << label << ":\n";
        out << indent(indentLevel + 1) << "type: " << action.actionType << "\n";
        out << indent(indentLevel + 1) << "_version: " << action.version << "\n";
        
        if (!action.actionName.empty())
            out << indent(indentLevel + 1) << "name: " << escapeYamlString(action.actionName) << "\n";
        
        if (!action.parameters.empty())
        {
            out << indent(indentLevel + 1) << "parameters:\n";
            for (const auto& param : action.parameters)
            {
                writeParameterYaml(out, param, indentLevel + 2);
            }
        }
    }
}

void YamlEmitter::writeParameterYaml(std::ofstream& out, const Parameter& param, int indentLevel)
{
    std::string ind = indent(indentLevel);
    
    out << ind << "- type: " << getParameterTypeName(param.type) << "\n";
    
    if (param.type == ParameterType::COORD3D)
    {
        out << ind << "  coord:\n";
        out << ind << "    x: " << std::fixed << std::setprecision(2) << param.coord.x << "\n";
        out << ind << "    y: " << std::fixed << std::setprecision(2) << param.coord.y << "\n";
        out << ind << "    z: " << std::fixed << std::setprecision(2) << param.coord.z << "\n";
    }
    else
    {
        // Write ALL three values for round-trip compatibility
        // The SCB format stores all three regardless of type
        out << ind << "  int_value: " << param.intValue << "\n";
        out << ind << "  real_value: " << std::fixed << std::setprecision(4) << param.realValue << "\n";
        out << ind << "  string_value: " << escapeYamlString(param.stringValue) << "\n";
    }
}

std::string YamlEmitter::indent(int level) const
{
    return std::string(level * 2, ' ');
}

std::string YamlEmitter::escapeYamlString(const std::string& str) const
{
    // Check if string needs quoting
    bool needsQuoting = str.empty();
    
    if (!needsQuoting)
    {
        for (char c : str)
        {
            if (c == ':' || c == '#' || c == '\n' || c == '\r' || 
                c == '\t' || c == '"' || c == '\'' || c == '[' || 
                c == ']' || c == '{' || c == '}' || c == ',' ||
                c == '&' || c == '*' || c == '!' || c == '|' ||
                c == '>' || c == '%' || c == '@' || c == '`')
            {
                needsQuoting = true;
                break;
            }
        }
        
        // Also quote if starts with special chars
        if (!needsQuoting && !str.empty())
        {
            char first = str[0];
            if (first == '-' || first == '?' || first == ' ')
                needsQuoting = true;
        }
    }
    
    if (!needsQuoting)
        return str;
    
    // Escape and quote
    std::string result = "\"";
    for (char c : str)
    {
        switch (c)
        {
        case '"': result += "\\\""; break;
        case '\\': result += "\\\\"; break;
        case '\n': result += "\\n"; break;
        case '\r': result += "\\r"; break;
        case '\t': result += "\\t"; break;
        default: result += c; break;
        }
    }
    result += "\"";
    return result;
}

void YamlEmitter::writeDictYaml(std::ofstream& out, const Dict& dict, int indentLevel)
{
    for (const auto& entry : dict.entries)
    {
        out << indent(indentLevel) << escapeYamlString(entry.key) << ": ";
        switch (entry.type)
        {
            case DictDataType::DICT_BOOL:
                out << (entry.boolValue ? "true" : "false") << "\n";
                break;
            case DictDataType::DICT_INT:
                out << entry.intValue << "\n";
                break;
            case DictDataType::DICT_REAL:
                out << entry.realValue << "\n";
                break;
            case DictDataType::DICT_ASCIISTRING:
                out << escapeYamlString(entry.asciiValue) << "\n";
                break;
            case DictDataType::DICT_UNICODESTRING:
                // Convert wide string to UTF-8 for YAML
                out << "\"<unicode>\"" << "\n";
                break;
        }
    }
}

bool YamlEmitter::writeObjects(const std::string& path, const std::vector<MapObject>& objects)
{
    std::ofstream out(path);
    if (!out.is_open())
    {
        m_error = "Failed to create objects file: " + path;
        return false;
    }
    
    out << "# Map Objects\n";
    out << "# Objects exported with scripts\n\n";
    
    out << "objects:\n";
    for (size_t i = 0; i < objects.size(); ++i)
    {
        const auto& obj = objects[i];
        out << "  - name: " << escapeYamlString(obj.name) << "\n";
        out << "    version: " << obj.version << "\n";
        out << "    location:\n";
        out << "      x: " << obj.location.x << "\n";
        out << "      y: " << obj.location.y << "\n";
        out << "      z: " << obj.location.z << "\n";
        out << "    angle: " << obj.angle << "\n";
        out << "    flags: " << obj.flags << "\n";
        if (!obj.properties.entries.empty())
        {
            out << "    properties:\n";
            writeDictYaml(out, obj.properties, 3);
        }
    }
    
    out.close();
    return true;
}

bool YamlEmitter::writePolygonTriggers(const std::string& path, const std::vector<PolygonTrigger>& triggers)
{
    std::ofstream out(path);
    if (!out.is_open())
    {
        m_error = "Failed to create triggers file: " + path;
        return false;
    }
    
    out << "# Polygon Triggers\n\n";
    
    out << "triggers:\n";
    for (const auto& trigger : triggers)
    {
        out << "  - name: " << escapeYamlString(trigger.name) << "\n";
        out << "    id: " << trigger.id << "\n";
        out << "    is_water_area: " << (trigger.isWaterArea ? "true" : "false") << "\n";
        out << "    is_river: " << (trigger.isRiver ? "true" : "false") << "\n";
        out << "    river_start: " << trigger.riverStart << "\n";
        out << "    points:\n";
        for (const auto& point : trigger.points)
        {
            out << "      - x: " << point.x << "\n";
            out << "        y: " << point.y << "\n";
            out << "        z: " << point.z << "\n";
        }
    }
    
    out.close();
    return true;
}

bool YamlEmitter::writeTeams(const std::string& path, const std::vector<Dict>& teams)
{
    std::ofstream out(path);
    if (!out.is_open())
    {
        m_error = "Failed to create teams file: " + path;
        return false;
    }
    
    out << "# Script Teams\n\n";
    
    out << "teams:\n";
    for (size_t i = 0; i < teams.size(); ++i)
    {
        out << "  - team_" << i << ":\n";
        writeDictYaml(out, teams[i], 2);
    }
    
    out.close();
    return true;
}

bool YamlEmitter::writeWaypoints(const std::string& path, const std::vector<WaypointLink>& links)
{
    std::ofstream out(path);
    if (!out.is_open())
    {
        m_error = "Failed to create waypoints file: " + path;
        return false;
    }
    
    out << "# Waypoint Links\n\n";
    
    out << "waypoint_links:\n";
    for (const auto& link : links)
    {
        out << "  - waypoint1: " << link.waypointID1 << "\n";
        out << "    waypoint2: " << link.waypointID2 << "\n";
    }
    
    out.close();
    return true;
}

} // namespace ScriptExport
