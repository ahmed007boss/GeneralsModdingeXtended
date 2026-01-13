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

// TheSuperHackers @feature AhmedSalah 12/01/2026 SCB file writer implementation

#include "StdAfx.h"
#include "ScriptWriter.h"

namespace ScriptExport
{

// Chunk version constants - must match the game
static const uint16_t K_SCRIPT_LIST_DATA_VERSION_1 = 1;
static const uint16_t K_SCRIPT_GROUP_DATA_VERSION_2 = 2;
static const uint16_t K_SCRIPT_DATA_VERSION_2 = 2;
static const uint16_t K_SCRIPT_OR_CONDITION_DATA_VERSION_1 = 1;
static const uint16_t K_SCRIPT_ACTION_VERSION_2 = 2;
static const uint16_t K_SCRIPT_CONDITION_VERSION_4 = 4;
static const uint16_t K_SCRIPTS_DATA_VERSION_1 = 12;

ScriptWriter::ScriptWriter() : m_nextSymbolId(1)
{
}

ScriptWriter::~ScriptWriter()
{
}

bool ScriptWriter::write(const std::string& filePath, const ScriptsData& data)
{
    m_buffer.clear();
    m_symbolTable.clear();
    m_chunkStack.clear();
    m_sourceData = &data;
    
    // If we have a loaded symbol table, use it
    if (!data.symbolTable.empty())
    {
        m_preserveSymbols = true;
        // Copy the symbol table (ID -> name, we need name -> ID)
        for (const auto& pair : data.symbolTable)
        {
            m_symbolTable[pair.second] = pair.first;
        }
        // Also use symbolToId if available
        if (!data.symbolToId.empty())
        {
            m_symbolTable = data.symbolToId;
        }
        // Find the highest ID to set next ID
        m_nextSymbolId = 1;
        for (const auto& pair : m_symbolTable)
        {
            if (pair.second >= m_nextSymbolId)
                m_nextSymbolId = pair.second + 1;
        }
    }
    else
    {
        m_preserveSymbols = false;
        m_nextSymbolId = 1;
    }

    // Write scripts data to buffer
    writeScriptsData(data);

    // Finalize and write to file
    return finalize(filePath);
}

void ScriptWriter::writeByte(uint8_t value)
{
    m_buffer.push_back(static_cast<char>(value));
}

void ScriptWriter::writeShort(uint16_t value)
{
    m_buffer.push_back(static_cast<char>(value & 0xFF));
    m_buffer.push_back(static_cast<char>((value >> 8) & 0xFF));
}

void ScriptWriter::writeInt(int32_t value)
{
    m_buffer.push_back(static_cast<char>(value & 0xFF));
    m_buffer.push_back(static_cast<char>((value >> 8) & 0xFF));
    m_buffer.push_back(static_cast<char>((value >> 16) & 0xFF));
    m_buffer.push_back(static_cast<char>((value >> 24) & 0xFF));
}

void ScriptWriter::writeUInt(uint32_t value)
{
    writeInt(static_cast<int32_t>(value));
}

void ScriptWriter::writeFloat(float value)
{
    uint32_t intVal;
    std::memcpy(&intVal, &value, sizeof(float));
    writeUInt(intVal);
}

void ScriptWriter::writeString(const std::string& value)
{
    uint16_t len = static_cast<uint16_t>(value.length());
    writeShort(len);
    for (char c : value)
    {
        m_buffer.push_back(c);
    }
}

void ScriptWriter::writeNameKey(const std::string& name)
{
    uint32_t id = allocateSymbol(name);
    int32_t keyAndType = (id << 8) | 3; // 3 = DICT_ASCIISTRING
    writeInt(keyAndType);
}

uint32_t ScriptWriter::allocateSymbol(const std::string& name)
{
    // First check our cached table
    auto it = m_symbolTable.find(name);
    if (it != m_symbolTable.end())
        return it->second;

    // If preserving symbols, check source data
    if (m_preserveSymbols && m_sourceData)
    {
        auto srcIt = m_sourceData->symbolToId.find(name);
        if (srcIt != m_sourceData->symbolToId.end())
        {
            uint32_t id = srcIt->second;
            m_symbolTable[name] = id; // Cache it
            return id;
        }
    }

    // Create new symbol (only if not preserving, or symbol genuinely new)
    uint32_t id = m_nextSymbolId++;
    m_symbolTable[name] = id;
    return id;
}

void ScriptWriter::openChunk(const std::string& name, uint16_t version)
{
    ChunkState state;
    state.id = allocateSymbol(name);
    
    // Write chunk ID
    writeUInt(state.id);
    
    // Write version
    writeShort(version);
    
    // Remember position for size
    state.sizePosition = m_buffer.size();
    
    // Write placeholder for size
    writeInt(0);
    
    state.dataStart = m_buffer.size();
    m_chunkStack.push_back(state);
}

void ScriptWriter::closeChunk()
{
    if (m_chunkStack.empty())
        return;

    ChunkState& state = m_chunkStack.back();
    
    // Calculate size
    int32_t size = static_cast<int32_t>(m_buffer.size() - state.dataStart);
    
    // Write size at saved position
    m_buffer[state.sizePosition] = static_cast<char>(size & 0xFF);
    m_buffer[state.sizePosition + 1] = static_cast<char>((size >> 8) & 0xFF);
    m_buffer[state.sizePosition + 2] = static_cast<char>((size >> 16) & 0xFF);
    m_buffer[state.sizePosition + 3] = static_cast<char>((size >> 24) & 0xFF);
    
    m_chunkStack.pop_back();
}

void ScriptWriter::writeScriptsData(const ScriptsData& data)
{
    // Write PlayerScriptsList chunk FIRST (matches WorldBuilder ScriptDialog.cpp order)
    openChunk("PlayerScriptsList", data.playerScriptsListVersion);
    
    for (const auto& list : data.playerScripts)
    {
        openChunk("ScriptList", list.version > 0 ? list.version : K_SCRIPT_LIST_DATA_VERSION_1);
        writeScriptList(list);
        closeChunk();
    }
    
    closeChunk();
    
    // Write ScriptsPlayers chunk (player names)
    if (!data.playerNames.empty())
    {
        openChunk("ScriptsPlayers", data.scriptsPlayersVersion);
        
        // Version 2+ writes doSides flag first
        if (data.scriptsPlayersVersion >= 2)
        {
            writeInt(data.hasSideDicts ? 1 : 0);
        }
        
        // Write number of players
        writeInt(static_cast<int32_t>(data.playerNames.size()));
        
        for (size_t i = 0; i < data.playerNames.size(); ++i)
        {
            writeString(data.playerNames[i]);
            
            // Write side dict if doSides flag is set
            if (data.hasSideDicts)
            {
                if (i < data.players.size() && data.players[i].hasSideDict)
                {
                    writeDict(data.players[i].sideDict);
                }
                else
                {
                    // Write empty dict (count = 0 as uint16_t)
                    Dict emptyDict;
                    writeDict(emptyDict);
                }
            }
        }
        
        closeChunk();
    }
    
    // Write ObjectsList chunk - always write it (even if empty), matching WorldBuilder
    openChunk("ObjectsList", data.objectsListVersion);
    
    for (const auto& obj : data.objects)
    {
        openChunk("Object", obj.version > 0 ? obj.version : 3);
        writeFloat(obj.location.x);
        writeFloat(obj.location.y);
        writeFloat(obj.location.z);
        writeFloat(obj.angle);
        writeInt(obj.flags);
        writeString(obj.name);
        writeDict(obj.properties);
        closeChunk();
    }
    
    closeChunk();
    
    // Write PolygonTriggers chunk - always write it, matching WorldBuilder
    openChunk("PolygonTriggers", data.polygonTriggersVersion);
    writeInt(static_cast<int32_t>(data.polygonTriggers.size()));
    
    for (const auto& trigger : data.polygonTriggers)
    {
        writeString(trigger.name);
        writeInt(trigger.id);
        writeByte(trigger.isWaterArea ? 1 : 0);
        writeByte(trigger.isRiver ? 1 : 0);
        writeInt(trigger.riverStart);
        
        writeInt(static_cast<int32_t>(trigger.points.size()));
        for (const auto& point : trigger.points)
        {
            writeInt(point.x);
            writeInt(point.y);
            writeInt(point.z);
        }
    }
    
    closeChunk();
    
    // Write ScriptTeams chunk - always write it, matching WorldBuilder (no count prefix, just dicts until end)
    openChunk("ScriptTeams", data.scriptTeamsVersion);
    
    for (const auto& team : data.teams)
    {
        writeDict(team);
    }
    
    closeChunk();
    
    // Write WaypointsList chunk LAST - always write it, matching WorldBuilder
    openChunk("WaypointsList", data.waypointsListVersion);
    writeInt(static_cast<int32_t>(data.waypointLinks.size()));
    
    for (const auto& link : data.waypointLinks)
    {
        writeInt(link.waypointID1);
        writeInt(link.waypointID2);
    }
    
    closeChunk();
}

void ScriptWriter::writeScriptList(const ScriptList& list)
{
    // Write ungrouped scripts
    for (const auto& script : list.scripts)
    {
        writeScript(script);
    }
    
    // Write groups
    for (const auto& group : list.groups)
    {
        writeScriptGroup(group);
    }
}

void ScriptWriter::writeScriptGroup(const ScriptGroup& group)
{
    openChunk("ScriptGroup", group.version > 0 ? group.version : K_SCRIPT_GROUP_DATA_VERSION_2);
    
    writeString(group.name);
    writeByte(group.isActive ? 1 : 0);
    writeByte(group.isSubroutine ? 1 : 0);
    
    for (const auto& script : group.scripts)
    {
        writeScript(script);
    }
    
    closeChunk();
}

void ScriptWriter::writeScript(const Script& script)
{
    uint16_t version = script.version > 0 ? script.version : K_SCRIPT_DATA_VERSION_2;
    openChunk("Script", version);
    
    writeString(script.name);
    writeString(script.comment);
    writeString(script.conditionComment);
    writeString(script.actionComment);
    
    writeByte(script.isActive ? 1 : 0);
    writeByte(script.isOneShot ? 1 : 0);
    writeByte(script.easy ? 1 : 0);
    writeByte(script.normal ? 1 : 0);
    writeByte(script.hard ? 1 : 0);
    writeByte(script.isSubroutine ? 1 : 0);
    
    // Delay only written for version 2+
    if (version >= K_SCRIPT_DATA_VERSION_2)
    {
        writeInt(script.delayEvaluationSeconds);
    }
    
    // Write conditions
    for (const auto& orCond : script.conditions)
    {
        writeOrCondition(orCond);
    }
    
    // Write actions
    for (const auto& action : script.actions)
    {
        writeAction(action, false);
    }
    
    // Write false actions
    for (const auto& action : script.falseActions)
    {
        writeAction(action, true);
    }
    
    closeChunk();
}

void ScriptWriter::writeOrCondition(const OrCondition& orCond)
{
    openChunk("OrCondition", orCond.version > 0 ? orCond.version : K_SCRIPT_OR_CONDITION_DATA_VERSION_1);
    
    for (const auto& cond : orCond.andConditions)
    {
        writeCondition(cond);
    }
    
    closeChunk();
}

void ScriptWriter::writeCondition(const Condition& cond)
{
    openChunk("Condition", cond.version > 0 ? cond.version : K_SCRIPT_CONDITION_VERSION_4);
    
    writeInt(cond.conditionType);
    writeNameKey(cond.conditionName.empty() ? "Unknown" : cond.conditionName);
    writeInt(static_cast<int32_t>(cond.parameters.size()));
    
    for (const auto& param : cond.parameters)
    {
        writeParameter(param);
    }
    
    closeChunk();
}

void ScriptWriter::writeAction(const ScriptAction& action, bool isFalse)
{
    openChunk(isFalse ? "ScriptActionFalse" : "ScriptAction", action.version > 0 ? action.version : K_SCRIPT_ACTION_VERSION_2);
    
    writeInt(action.actionType);
    writeNameKey(action.actionName.empty() ? "Unknown" : action.actionName);
    writeInt(static_cast<int32_t>(action.parameters.size()));
    
    for (const auto& param : action.parameters)
    {
        writeParameter(param);
    }
    
    closeChunk();
}

void ScriptWriter::writeParameter(const Parameter& param)
{
    writeInt(static_cast<int32_t>(param.type));
    
    if (param.type == ParameterType::COORD3D)
    {
        writeFloat(param.coord.x);
        writeFloat(param.coord.y);
        writeFloat(param.coord.z);
    }
    else
    {
        writeInt(param.intValue);
        writeFloat(param.realValue);
        writeString(param.stringValue);
    }
}

void ScriptWriter::writeDict(const Dict& dict)
{
    // Dict count is uint16_t (2 bytes), not int32_t!
    writeShort(static_cast<uint16_t>(dict.entries.size()));
    
    for (const auto& entry : dict.entries)
    {
        // Write key and type combined (same format as game)
        uint32_t keyId = allocateSymbol(entry.key);
        int32_t keyAndType = (keyId << 8) | static_cast<int32_t>(entry.type);
        writeInt(keyAndType);
        
        // Write value based on type
        switch (entry.type)
        {
            case DictDataType::DICT_BOOL:
                writeByte(entry.boolValue ? 1 : 0);
                break;
            case DictDataType::DICT_INT:
                writeInt(entry.intValue);
                break;
            case DictDataType::DICT_REAL:
                writeFloat(entry.realValue);
                break;
            case DictDataType::DICT_ASCIISTRING:
                writeString(entry.asciiValue);
                break;
            case DictDataType::DICT_UNICODESTRING:
                {
                    // Write as UTF-16LE
                    uint16_t len = static_cast<uint16_t>(entry.unicodeValue.length());
                    writeShort(len);
                    for (wchar_t wc : entry.unicodeValue)
                    {
                        writeShort(static_cast<uint16_t>(wc));
                    }
                }
                break;
        }
    }
}

bool ScriptWriter::finalize(const std::string& filePath)
{
    std::ofstream file(filePath, std::ios::binary);
    if (!file.is_open())
    {
        m_error = "Failed to create output file: " + filePath;
        return false;
    }
    
    // Write header tag
    file.write("CkMp", 4);
    
    // Write symbol table - must be in ID order for compatibility
    // CRITICAL: Write the COMPLETE original symbol table, not just symbols we used
    // The game may have internal references to symbol IDs that aren't in the scripts
    const std::map<uint32_t, std::string>* symbolTableToWrite = nullptr;
    std::map<uint32_t, std::string> idToName;
    
    if (m_preserveSymbols && m_sourceData)
    {
        // Use the complete original symbol table in original read order
        if (!m_sourceData->symbolOrder.empty())
        {
            // Write symbols in original read order
            int32_t symbolCount = static_cast<int32_t>(m_sourceData->symbolOrder.size());
            file.write(reinterpret_cast<const char*>(&symbolCount), sizeof(int32_t));
            
            for (const auto& pair : m_sourceData->symbolOrder)
            {
                uint8_t len = static_cast<uint8_t>(pair.second.length());
                file.write(reinterpret_cast<const char*>(&len), 1);
                file.write(pair.second.c_str(), len);
                uint32_t id = pair.first;
                file.write(reinterpret_cast<const char*>(&id), sizeof(uint32_t));
            }
            
            // Write chunk data
            file.write(m_buffer.data(), m_buffer.size());
            file.close();
            return true;
        }
        
        if (!m_sourceData->idToSymbol.empty())
        {
            symbolTableToWrite = &m_sourceData->idToSymbol;
        }
        else if (!m_sourceData->symbolTable.empty())
        {
            symbolTableToWrite = &m_sourceData->symbolTable;
        }
    }
    
    if (!symbolTableToWrite)
    {
        // Build ID -> name map from what we allocated (new file, no preservation)
        for (const auto& pair : m_symbolTable)
        {
            idToName[pair.second] = pair.first;
        }
        symbolTableToWrite = &idToName;
    }
    
    int32_t symbolCount = static_cast<int32_t>(symbolTableToWrite->size());
    file.write(reinterpret_cast<const char*>(&symbolCount), sizeof(int32_t));
    
    // Write symbols in ID order
    for (const auto& pair : *symbolTableToWrite)
    {
        uint8_t len = static_cast<uint8_t>(pair.second.length());
        file.write(reinterpret_cast<const char*>(&len), 1);
        file.write(pair.second.c_str(), len);
        uint32_t id = pair.first;
        file.write(reinterpret_cast<const char*>(&id), sizeof(uint32_t));
    }
    
    // Write chunk data
    file.write(m_buffer.data(), m_buffer.size());
    
    file.close();
    return true;
}

} // namespace ScriptExport
