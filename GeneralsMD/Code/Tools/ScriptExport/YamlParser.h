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

// TheSuperHackers @feature AhmedSalah 12/01/2026 YAML parser for ScriptExport tool

#pragma once

#include "StdAfx.h"
#include "ScriptTypes.h"
#include <map>

namespace ScriptExport
{

/**
 * Simple YAML parser for reading script YAML files back into ScriptsData
 * This is a specialized parser for the specific YAML format used by ScriptExportZH
 */
class YamlParser
{
public:
    YamlParser();
    ~YamlParser();

    /**
     * Read scripts from a directory containing YAML files
     * @param inputDir Path to the directory containing manifest.yaml
     * @param data Output scripts data
     * @return true on success, false on failure
     */
    bool read(const std::string& inputDir, ScriptsData& data);

    /**
     * Get the last error message
     */
    const std::string& getError() const { return m_error; }

private:
    // YAML node representation
    struct YamlNode
    {
        std::string key;
        std::string value;
        std::vector<YamlNode> children;
        int indent = 0;
        bool isList = false;
    };

    // Parse a YAML file into nodes
    bool parseYamlFile(const std::string& path, std::vector<YamlNode>& nodes);
    
    // Parse YAML content
    void parseYamlLines(const std::vector<std::string>& lines, std::vector<YamlNode>& nodes, size_t& lineIndex, int parentIndent);
    
    // Helper to get indent level
    int getIndentLevel(const std::string& line) const;
    
    // Helper to trim whitespace
    std::string trim(const std::string& str) const;
    
    // Helper to unescape YAML string
    std::string unescapeYamlString(const std::string& str) const;
    
    // Find a child node by key
    const YamlNode* findChild(const std::vector<YamlNode>& nodes, const std::string& key) const;
    
    // Get value as various types
    std::string getValue(const std::vector<YamlNode>& nodes, const std::string& key, const std::string& defaultValue = "") const;
    int getIntValue(const std::vector<YamlNode>& nodes, const std::string& key, int defaultValue = 0) const;
    float getFloatValue(const std::vector<YamlNode>& nodes, const std::string& key, float defaultValue = 0.0f) const;
    bool getBoolValue(const std::vector<YamlNode>& nodes, const std::string& key, bool defaultValue = false) const;
    
    // Read manifest
    bool readManifest(const std::string& path, ScriptsData& data, std::vector<std::string>& playerDirs);
    
    // Read symbols
    bool readSymbols(const std::string& path, ScriptsData& data);
    
    // Read player script list
    bool readPlayerScripts(const std::string& playerDir, ScriptList& list);
    
    // Read script group
    bool readScriptGroup(const std::string& groupDir, ScriptGroup& group);
    
    // Read single script
    bool readScript(const std::string& scriptPath, Script& script);
    
    // Read conditions from YAML nodes
    bool readConditions(const std::vector<YamlNode>& conditionNodes, std::vector<OrCondition>& conditions);
    
    // Read actions from YAML nodes
    bool readActions(const std::vector<YamlNode>& actionNodes, std::vector<ScriptAction>& actions);
    
    // Read parameter from YAML nodes
    bool readParameter(const YamlNode& paramNode, Parameter& param);
    
    // Read objects
    bool readObjects(const std::string& path, std::vector<MapObject>& objects);
    
    // Read triggers
    bool readPolygonTriggers(const std::string& path, std::vector<PolygonTrigger>& triggers);
    
    // Read teams
    bool readTeams(const std::string& path, std::vector<Dict>& teams);
    
    // Read waypoints
    bool readWaypoints(const std::string& path, std::vector<WaypointLink>& links);
    
    // Read dictionary from YAML nodes
    bool readDict(const std::vector<YamlNode>& nodes, Dict& dict);

    std::string m_error;
    std::string m_baseDir;
};

} // namespace ScriptExport
