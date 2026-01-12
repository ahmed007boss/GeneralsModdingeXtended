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

// TheSuperHackers @feature AhmedSalah 12/01/2026 YAML emitter for ScriptExport tool

#pragma once

#include "StdAfx.h"
#include "ScriptTypes.h"

namespace ScriptExport
{

/**
 * YAML emitter for scripts
 * Outputs scripts in a structured folder/file format
 */
class YamlEmitter
{
public:
    YamlEmitter();
    ~YamlEmitter();

    /**
     * Write scripts data to a directory structure
     * @param outputDir Base output directory
     * @param data Scripts data to write
     * @return true on success, false on failure
     */
    bool write(const std::string& outputDir, const ScriptsData& data);

    /**
     * Get the last error message
     */
    const std::string& getError() const { return m_error; }

private:
    // Sanitize a string to be a valid filename
    std::string sanitizeFilename(const std::string& name) const;

    // Create directory (cross-platform)
    bool createDirectory(const std::string& path) const;

    // Write a single script list
    bool writeScriptList(const std::string& dir, const ScriptList& list, int playerIndex);

    // Write a script group folder
    bool writeScriptGroup(const std::string& dir, const ScriptGroup& group, int groupIndex);

    // Write a single script file
    bool writeScript(const std::string& dir, const Script& script, int scriptIndex);

    // Write additional data files
    bool writeObjects(const std::string& path, const std::vector<MapObject>& objects);
    bool writePolygonTriggers(const std::string& path, const std::vector<PolygonTrigger>& triggers);
    bool writeTeams(const std::string& path, const std::vector<Dict>& teams);
    bool writeWaypoints(const std::string& path, const std::vector<WaypointLink>& links);
    void writeDictYaml(std::ofstream& out, const Dict& dict, int indent);

    // YAML formatting helpers
    void writeYamlHeader(std::ofstream& out);
    void writeScriptYaml(std::ofstream& out, const Script& script, int indent);
    void writeConditionsYaml(std::ofstream& out, const std::vector<OrCondition>& conditions, int indent);
    void writeActionsYaml(std::ofstream& out, const std::vector<ScriptAction>& actions, int indent, const char* label);
    void writeParameterYaml(std::ofstream& out, const Parameter& param, int indent);

    std::string indent(int level) const;
    std::string escapeYamlString(const std::string& str) const;

    std::string m_error;
};

} // namespace ScriptExport
