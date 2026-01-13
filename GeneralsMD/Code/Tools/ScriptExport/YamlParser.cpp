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

// TheSuperHackers @feature AhmedSalah 12/01/2026 YAML parser implementation

#include "StdAfx.h"
#include "YamlParser.h"

#ifdef _WIN32
#include <direct.h>
#include <io.h>
#define access _access
#define F_OK 0
#else
#include <unistd.h>
#include <dirent.h>
#endif

namespace ScriptExport
{

YamlParser::YamlParser()
{
}

YamlParser::~YamlParser()
{
}

bool YamlParser::read(const std::string& inputDir, ScriptsData& data)
{
    m_baseDir = inputDir;
    
    // Read manifest first
    std::string manifestPath = inputDir + "/manifest.yaml";
    std::vector<std::string> playerDirs;
    
    if (!readManifest(manifestPath, data, playerDirs))
        return false;
    
    // Read symbols if present
    std::string symbolsPath = inputDir + "/symbols.yaml";
    if (access(symbolsPath.c_str(), F_OK) == 0)
    {
        readSymbols(symbolsPath, data);
    }
    
    // Read each player's scripts
    for (const auto& playerDir : playerDirs)
    {
        ScriptList list;
        std::string fullPlayerDir = inputDir + "/" + playerDir;
        
        if (!readPlayerScripts(fullPlayerDir, list))
            return false;
        
        data.playerScripts.push_back(list);
    }
    
    // Read additional data files if present
    std::string objectsPath = inputDir + "/objects.yaml";
    if (access(objectsPath.c_str(), F_OK) == 0)
    {
        readObjects(objectsPath, data.objects);
    }
    
    std::string triggersPath = inputDir + "/triggers.yaml";
    if (access(triggersPath.c_str(), F_OK) == 0)
    {
        readPolygonTriggers(triggersPath, data.polygonTriggers);
    }
    
    std::string teamsPath = inputDir + "/teams.yaml";
    if (access(teamsPath.c_str(), F_OK) == 0)
    {
        readTeams(teamsPath, data.teams);
    }
    
    std::string waypointsPath = inputDir + "/waypoints.yaml";
    if (access(waypointsPath.c_str(), F_OK) == 0)
    {
        readWaypoints(waypointsPath, data.waypointLinks);
    }
    
    return true;
}

bool YamlParser::parseYamlFile(const std::string& path, std::vector<YamlNode>& nodes)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        m_error = "Failed to open file: " + path;
        return false;
    }
    
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line))
    {
        // Skip comments and empty lines for initial processing
        std::string trimmed = trim(line);
        if (trimmed.empty() || trimmed[0] == '#')
            continue;
        lines.push_back(line);
    }
    file.close();
    
    size_t lineIndex = 0;
    parseYamlLines(lines, nodes, lineIndex, -1);
    
    return true;
}

void YamlParser::parseYamlLines(const std::vector<std::string>& lines, std::vector<YamlNode>& nodes, size_t& lineIndex, int parentIndent)
{
    while (lineIndex < lines.size())
    {
        const std::string& line = lines[lineIndex];
        int indent = getIndentLevel(line);
        
        // If we're back to parent level or less, we're done with this block
        if (indent <= parentIndent)
            return;
        
        std::string trimmed = trim(line);
        
        YamlNode node;
        node.indent = indent;
        
        // Check if this is a list item
        if (trimmed[0] == '-')
        {
            node.isList = true;
            trimmed = trim(trimmed.substr(1));
        }
        
        // Parse key: value
        size_t colonPos = trimmed.find(':');
        if (colonPos != std::string::npos)
        {
            node.key = trim(trimmed.substr(0, colonPos));
            std::string valueStr = trim(trimmed.substr(colonPos + 1));
            
            if (!valueStr.empty())
            {
                node.value = unescapeYamlString(valueStr);
            }
        }
        else
        {
            // Just a value (in a list)
            node.value = unescapeYamlString(trimmed);
        }
        
        lineIndex++;
        
        // Check for children
        if (lineIndex < lines.size())
        {
            int nextIndent = getIndentLevel(lines[lineIndex]);
            if (nextIndent > indent)
            {
                parseYamlLines(lines, node.children, lineIndex, indent);
            }
        }
        
        nodes.push_back(node);
    }
}

int YamlParser::getIndentLevel(const std::string& line) const
{
    int indent = 0;
    for (char c : line)
    {
        if (c == ' ')
            indent++;
        else if (c == '\t')
            indent += 2;
        else
            break;
    }
    return indent;
}

std::string YamlParser::trim(const std::string& str) const
{
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos)
        return "";
    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}

std::string YamlParser::unescapeYamlString(const std::string& str) const
{
    if (str.empty())
        return str;
    
    std::string result = str;
    
    // Remove quotes if present
    if ((result[0] == '"' && result.back() == '"') ||
        (result[0] == '\'' && result.back() == '\''))
    {
        result = result.substr(1, result.size() - 2);
    }
    
    // Unescape sequences
    std::string unescaped;
    unescaped.reserve(result.size());
    
    for (size_t i = 0; i < result.size(); ++i)
    {
        if (result[i] == '\\' && i + 1 < result.size())
        {
            char next = result[i + 1];
            switch (next)
            {
                case 'n': unescaped += '\n'; i++; break;
                case 'r': unescaped += '\r'; i++; break;
                case 't': unescaped += '\t'; i++; break;
                case '"': unescaped += '"'; i++; break;
                case '\\': unescaped += '\\'; i++; break;
                default: unescaped += result[i]; break;
            }
        }
        else
        {
            unescaped += result[i];
        }
    }
    
    return unescaped;
}

const YamlParser::YamlNode* YamlParser::findChild(const std::vector<YamlNode>& nodes, const std::string& key) const
{
    for (const auto& node : nodes)
    {
        if (node.key == key)
            return &node;
    }
    return nullptr;
}

std::string YamlParser::getValue(const std::vector<YamlNode>& nodes, const std::string& key, const std::string& defaultValue) const
{
    const YamlNode* node = findChild(nodes, key);
    if (node && !node->value.empty())
        return node->value;
    return defaultValue;
}

int YamlParser::getIntValue(const std::vector<YamlNode>& nodes, const std::string& key, int defaultValue) const
{
    std::string val = getValue(nodes, key);
    if (val.empty())
        return defaultValue;
    try
    {
        return std::stoi(val);
    }
    catch (...)
    {
        return defaultValue;
    }
}

float YamlParser::getFloatValue(const std::vector<YamlNode>& nodes, const std::string& key, float defaultValue) const
{
    std::string val = getValue(nodes, key);
    if (val.empty())
        return defaultValue;
    try
    {
        return std::stof(val);
    }
    catch (...)
    {
        return defaultValue;
    }
}

bool YamlParser::getBoolValue(const std::vector<YamlNode>& nodes, const std::string& key, bool defaultValue) const
{
    std::string val = getValue(nodes, key);
    if (val.empty())
        return defaultValue;
    return val == "true" || val == "True" || val == "TRUE" || val == "yes" || val == "1";
}

bool YamlParser::readManifest(const std::string& path, ScriptsData& data, std::vector<std::string>& playerDirs)
{
    std::vector<YamlNode> nodes;
    if (!parseYamlFile(path, nodes))
        return false;
    
    // Read chunk versions
    const YamlNode* versionsNode = findChild(nodes, "chunk_versions");
    if (versionsNode)
    {
        data.playerScriptsListVersion = static_cast<uint16_t>(getIntValue(versionsNode->children, "PlayerScriptsList", 1));
        data.scriptsPlayersVersion = static_cast<uint16_t>(getIntValue(versionsNode->children, "ScriptsPlayers", 2));
        data.objectsListVersion = static_cast<uint16_t>(getIntValue(versionsNode->children, "ObjectsList", 3));
        data.polygonTriggersVersion = static_cast<uint16_t>(getIntValue(versionsNode->children, "PolygonTriggers", 3));
        data.scriptTeamsVersion = static_cast<uint16_t>(getIntValue(versionsNode->children, "ScriptTeams", 1));
        data.waypointsListVersion = static_cast<uint16_t>(getIntValue(versionsNode->children, "WaypointsList", 1));
    }
    
    data.hasSideDicts = getBoolValue(nodes, "has_side_dicts", false);
    
    // Read players list
    const YamlNode* playersNode = findChild(nodes, "players");
    if (playersNode)
    {
        for (const auto& playerNode : playersNode->children)
        {
            std::string playerName = getValue(playerNode.children, "name");
            std::string directory = getValue(playerNode.children, "directory");
            
            if (!directory.empty())
            {
                playerDirs.push_back(directory);
                data.playerNames.push_back(playerName);
            }
        }
    }
    
    return true;
}

bool YamlParser::readSymbols(const std::string& path, ScriptsData& data)
{
    std::vector<YamlNode> nodes;
    if (!parseYamlFile(path, nodes))
        return false;
    
    const YamlNode* symbolsNode = findChild(nodes, "symbols");
    if (symbolsNode)
    {
        // Preserve the order symbols appear in YAML file
        data.symbolOrder.clear();
        for (const auto& child : symbolsNode->children)
        {
            try
            {
                uint32_t id = static_cast<uint32_t>(std::stoul(child.key));
                data.symbolTable[id] = child.value;
                data.symbolToId[child.value] = id;
                data.idToSymbol[id] = child.value;
                data.symbolOrder.push_back({id, child.value}); // Preserve YAML order
            }
            catch (...) {}
        }
    }
    
    return true;
}

bool YamlParser::readPlayerScripts(const std::string& playerDir, ScriptList& list)
{
    // Read list.yaml
    std::string listPath = playerDir + "/list.yaml";
    std::vector<YamlNode> nodes;
    
    if (!parseYamlFile(listPath, nodes))
    {
        // If list.yaml doesn't exist, try to scan the directory structure
        m_error = "";
        return true; // Empty list is valid
    }
    
    // Read groups
    const YamlNode* groupsNode = findChild(nodes, "groups");
    if (groupsNode)
    {
        for (const auto& groupEntry : groupsNode->children)
        {
            std::string groupDir = getValue(groupEntry.children, "directory");
            if (!groupDir.empty())
            {
                ScriptGroup group;
                std::string fullGroupDir = playerDir + "/" + groupDir;
                
                if (!readScriptGroup(fullGroupDir, group))
                {
                    // Non-fatal - just skip this group
                    continue;
                }
                
                list.groups.push_back(group);
            }
        }
    }
    
    // Read ungrouped scripts
    const YamlNode* scriptsNode = findChild(nodes, "scripts");
    if (scriptsNode)
    {
        for (const auto& scriptEntry : scriptsNode->children)
        {
            std::string scriptFile = getValue(scriptEntry.children, "file");
            if (!scriptFile.empty())
            {
                Script script;
                std::string fullScriptPath = playerDir + "/" + scriptFile;
                
                if (!readScript(fullScriptPath, script))
                {
                    // Non-fatal - just skip this script
                    continue;
                }
                
                list.scripts.push_back(script);
            }
        }
    }
    
    return true;
}

bool YamlParser::readScriptGroup(const std::string& groupDir, ScriptGroup& group)
{
    // Read group.yaml
    std::string groupPath = groupDir + "/group.yaml";
    std::vector<YamlNode> nodes;
    
    if (!parseYamlFile(groupPath, nodes))
        return false;
    
    group.name = getValue(nodes, "name");
    group.version = static_cast<uint16_t>(getIntValue(nodes, "_version", 2));
    group.isActive = getBoolValue(nodes, "active", true);
    group.isSubroutine = getBoolValue(nodes, "subroutine", false);
    
    // Read scripts in group
    const YamlNode* scriptsNode = findChild(nodes, "scripts");
    if (scriptsNode)
    {
        for (const auto& scriptEntry : scriptsNode->children)
        {
            std::string scriptFile = getValue(scriptEntry.children, "file");
            if (scriptFile.empty() && !scriptEntry.value.empty())
            {
                // Might be a simple "- file: xxx" format
                scriptFile = scriptEntry.value;
            }
            
            if (!scriptFile.empty())
            {
                Script script;
                std::string fullScriptPath = groupDir + "/" + scriptFile;
                
                if (!readScript(fullScriptPath, script))
                {
                    continue;
                }
                
                group.scripts.push_back(script);
            }
        }
    }
    
    return true;
}

bool YamlParser::readScript(const std::string& scriptPath, Script& script)
{
    std::vector<YamlNode> nodes;
    if (!parseYamlFile(scriptPath, nodes))
        return false;
    
    script.name = getValue(nodes, "name");
    script.version = static_cast<uint16_t>(getIntValue(nodes, "_version", 2));
    script.comment = getValue(nodes, "comment");
    script.conditionComment = getValue(nodes, "condition_comment");
    script.actionComment = getValue(nodes, "action_comment");
    script.isActive = getBoolValue(nodes, "active", true);
    script.isOneShot = getBoolValue(nodes, "one_shot", true);
    script.isSubroutine = getBoolValue(nodes, "subroutine", false);
    script.delayEvaluationSeconds = getIntValue(nodes, "delay_seconds", 0);
    
    // Read difficulty
    const YamlNode* diffNode = findChild(nodes, "difficulty");
    if (diffNode)
    {
        script.easy = getBoolValue(diffNode->children, "easy", true);
        script.normal = getBoolValue(diffNode->children, "normal", true);
        script.hard = getBoolValue(diffNode->children, "hard", true);
    }
    
    // Read conditions
    const YamlNode* conditionsNode = findChild(nodes, "conditions");
    if (conditionsNode)
    {
        readConditions(conditionsNode->children, script.conditions);
    }
    
    // Read actions
    const YamlNode* actionsNode = findChild(nodes, "actions");
    if (actionsNode)
    {
        readActions(actionsNode->children, script.actions);
    }
    
    // Read else_actions
    const YamlNode* elseActionsNode = findChild(nodes, "else_actions");
    if (elseActionsNode)
    {
        readActions(elseActionsNode->children, script.falseActions);
    }
    
    return true;
}

bool YamlParser::readConditions(const std::vector<YamlNode>& conditionNodes, std::vector<OrCondition>& conditions)
{
    for (const auto& orNode : conditionNodes)
    {
        // Find or_clause
        const YamlNode* orClause = findChild(orNode.children, "or_clause");
        if (!orClause && orNode.key == "or_clause")
        {
            orClause = &orNode;
        }
        
        if (orClause || !orNode.children.empty())
        {
            OrCondition orCond;
            const std::vector<YamlNode>* children = orClause ? &orClause->children : &orNode.children;
            
            orCond.version = static_cast<uint16_t>(getIntValue(*children, "_version", 1));
            
            for (const auto& condNode : *children)
            {
                if (condNode.key == "condition" || condNode.key == "_version")
                {
                    if (condNode.key == "_version")
                        continue;
                    
                    Condition cond;
                    const std::vector<YamlNode>* condChildren = &condNode.children;
                    
                    // Handle "- condition:" format
                    const YamlNode* innerCond = findChild(condNode.children, "condition");
                    if (innerCond)
                    {
                        condChildren = &innerCond->children;
                    }
                    
                    cond.conditionType = getIntValue(*condChildren, "type", 0);
                    cond.version = static_cast<uint16_t>(getIntValue(*condChildren, "_version", 4));
                    cond.conditionName = getValue(*condChildren, "name");
                    
                    // Read parameters
                    const YamlNode* paramsNode = findChild(*condChildren, "parameters");
                    if (paramsNode)
                    {
                        for (const auto& paramNode : paramsNode->children)
                        {
                            Parameter param;
                            if (readParameter(paramNode, param))
                            {
                                cond.parameters.push_back(param);
                            }
                        }
                    }
                    
                    orCond.andConditions.push_back(cond);
                }
            }
            
            if (!orCond.andConditions.empty())
            {
                conditions.push_back(orCond);
            }
        }
    }
    
    return true;
}

bool YamlParser::readActions(const std::vector<YamlNode>& actionNodes, std::vector<ScriptAction>& actions)
{
    for (const auto& actionNode : actionNodes)
    {
        ScriptAction action;
        
        const std::vector<YamlNode>* children = &actionNode.children;
        
        // Handle "- action:" format
        const YamlNode* innerAction = findChild(actionNode.children, "action");
        if (innerAction)
        {
            children = &innerAction->children;
        }
        
        action.actionType = getIntValue(*children, "type", 0);
        action.version = static_cast<uint16_t>(getIntValue(*children, "_version", 2));
        action.actionName = getValue(*children, "name");
        
        // Read parameters
        const YamlNode* paramsNode = findChild(*children, "parameters");
        if (paramsNode)
        {
            for (const auto& paramNode : paramsNode->children)
            {
                Parameter param;
                if (readParameter(paramNode, param))
                {
                    action.parameters.push_back(param);
                }
            }
        }
        
        actions.push_back(action);
    }
    
    return true;
}

bool YamlParser::readParameter(const YamlNode& paramNode, Parameter& param)
{
    const std::vector<YamlNode>* children = &paramNode.children;
    
    std::string typeStr = getValue(*children, "type", "INT");
    param.type = parseParameterType(typeStr);
    
    if (param.type == ParameterType::COORD3D)
    {
        const YamlNode* coordNode = findChild(*children, "coord");
        if (coordNode)
        {
            param.coord.x = getFloatValue(coordNode->children, "x", 0.0f);
            param.coord.y = getFloatValue(coordNode->children, "y", 0.0f);
            param.coord.z = getFloatValue(coordNode->children, "z", 0.0f);
        }
    }
    else
    {
        // Read ALL three values - the SCB format stores all three
        param.intValue = getIntValue(*children, "int_value", 0);
        param.realValue = getFloatValue(*children, "real_value", 0.0f);
        param.stringValue = getValue(*children, "string_value");
    }
    
    return true;
}

bool YamlParser::readObjects(const std::string& path, std::vector<MapObject>& objects)
{
    std::vector<YamlNode> nodes;
    if (!parseYamlFile(path, nodes))
        return false;
    
    const YamlNode* objectsNode = findChild(nodes, "objects");
    if (objectsNode)
    {
        for (const auto& objNode : objectsNode->children)
        {
            MapObject obj;
            obj.name = getValue(objNode.children, "name");
            obj.version = static_cast<uint16_t>(getIntValue(objNode.children, "version", 3));
            obj.angle = getFloatValue(objNode.children, "angle", 0.0f);
            obj.flags = getIntValue(objNode.children, "flags", 0);
            
            const YamlNode* locNode = findChild(objNode.children, "location");
            if (locNode)
            {
                obj.location.x = getFloatValue(locNode->children, "x", 0.0f);
                obj.location.y = getFloatValue(locNode->children, "y", 0.0f);
                obj.location.z = getFloatValue(locNode->children, "z", 0.0f);
            }
            
            const YamlNode* propsNode = findChild(objNode.children, "properties");
            if (propsNode)
            {
                readDict(propsNode->children, obj.properties);
            }
            
            objects.push_back(obj);
        }
    }
    
    return true;
}

bool YamlParser::readPolygonTriggers(const std::string& path, std::vector<PolygonTrigger>& triggers)
{
    std::vector<YamlNode> nodes;
    if (!parseYamlFile(path, nodes))
        return false;
    
    const YamlNode* triggersNode = findChild(nodes, "triggers");
    if (triggersNode)
    {
        for (const auto& trigNode : triggersNode->children)
        {
            PolygonTrigger trigger;
            trigger.name = getValue(trigNode.children, "name");
            trigger.id = getIntValue(trigNode.children, "id", 0);
            trigger.isWaterArea = getBoolValue(trigNode.children, "is_water_area", false);
            trigger.isRiver = getBoolValue(trigNode.children, "is_river", false);
            trigger.riverStart = getIntValue(trigNode.children, "river_start", 0);
            
            const YamlNode* pointsNode = findChild(trigNode.children, "points");
            if (pointsNode)
            {
                for (const auto& pointNode : pointsNode->children)
                {
                    ICoord3D point;
                    point.x = getIntValue(pointNode.children, "x", 0);
                    point.y = getIntValue(pointNode.children, "y", 0);
                    point.z = getIntValue(pointNode.children, "z", 0);
                    trigger.points.push_back(point);
                }
            }
            
            triggers.push_back(trigger);
        }
    }
    
    return true;
}

bool YamlParser::readTeams(const std::string& path, std::vector<Dict>& teams)
{
    std::vector<YamlNode> nodes;
    if (!parseYamlFile(path, nodes))
        return false;
    
    const YamlNode* teamsNode = findChild(nodes, "teams");
    if (teamsNode)
    {
        for (const auto& teamNode : teamsNode->children)
        {
            Dict teamDict;
            
            // The teamNode is "- team_N:" and its children are the properties
            // Format: - team_N:
            //           teamName: ...
            //           teamOwner: ...
            // The properties are direct children of teamNode
            readDict(teamNode.children, teamDict);
            
            teams.push_back(teamDict);
        }
    }
    
    return true;
}

bool YamlParser::readWaypoints(const std::string& path, std::vector<WaypointLink>& links)
{
    std::vector<YamlNode> nodes;
    if (!parseYamlFile(path, nodes))
        return false;
    
    const YamlNode* linksNode = findChild(nodes, "waypoint_links");
    if (linksNode)
    {
        for (const auto& linkNode : linksNode->children)
        {
            WaypointLink link;
            link.waypointID1 = getIntValue(linkNode.children, "waypoint1", 0);
            link.waypointID2 = getIntValue(linkNode.children, "waypoint2", 0);
            links.push_back(link);
        }
    }
    
    return true;
}

bool YamlParser::readDict(const std::vector<YamlNode>& nodes, Dict& dict)
{
    for (const auto& node : nodes)
    {
        if (node.key.empty())
            continue;
        
        DictEntry entry;
        entry.key = node.key;
        
        // Check if this is the new structured format (has _type child)
        const YamlNode* typeNode = findChild(node.children, "_type");
        const YamlNode* valueNode = findChild(node.children, "value");
        
        if (typeNode && valueNode)
        {
            // New structured format with explicit type
            std::string typeStr = typeNode->value;
            std::string val = valueNode->value;
            
            if (typeStr == "BOOL")
            {
                entry.type = DictDataType::DICT_BOOL;
                entry.boolValue = (val == "true");
            }
            else if (typeStr == "INT")
            {
                entry.type = DictDataType::DICT_INT;
                try { entry.intValue = std::stoi(val); } catch (...) {}
            }
            else if (typeStr == "REAL")
            {
                entry.type = DictDataType::DICT_REAL;
                try { entry.realValue = std::stof(val); } catch (...) {}
            }
            else if (typeStr == "ASCIISTRING")
            {
                entry.type = DictDataType::DICT_ASCIISTRING;
                entry.asciiValue = unescapeYamlString(val);
            }
            else if (typeStr == "UNICODESTRING")
            {
                entry.type = DictDataType::DICT_UNICODESTRING;
                // Unicode not fully supported in YAML
            }
        }
        else
        {
            // Legacy format - try to determine type from value (for backward compatibility)
            const std::string& val = node.value;
            
            if (val == "true" || val == "false")
            {
                entry.type = DictDataType::DICT_BOOL;
                entry.boolValue = (val == "true");
            }
            else if (!val.empty() && (std::isdigit(val[0]) || val[0] == '-'))
            {
                // Check if it's a float or int
                if (val.find('.') != std::string::npos)
                {
                    entry.type = DictDataType::DICT_REAL;
                    try { entry.realValue = std::stof(val); } catch (...) {}
                }
                else
                {
                    entry.type = DictDataType::DICT_INT;
                    try { entry.intValue = std::stoi(val); } catch (...) {}
                }
            }
            else
            {
                entry.type = DictDataType::DICT_ASCIISTRING;
                entry.asciiValue = unescapeYamlString(val);
            }
        }
        
        dict.entries.push_back(entry);
    }
    
    return true;
}

} // namespace ScriptExport
