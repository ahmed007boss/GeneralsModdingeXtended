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

// TheSuperHackers @feature AhmedSalah 12/01/2026 SCB file parser implementation

#include "StdAfx.h"
#include "ScriptParser.h"

namespace ScriptExport
{

// Chunk version constants - must match the game
static const uint16_t K_SCRIPT_LIST_DATA_VERSION_1 = 1;
static const uint16_t K_SCRIPT_GROUP_DATA_VERSION_1 = 1;
static const uint16_t K_SCRIPT_GROUP_DATA_VERSION_2 = 2;
static const uint16_t K_SCRIPT_DATA_VERSION_1 = 1;
static const uint16_t K_SCRIPT_DATA_VERSION_2 = 2;
static const uint16_t K_SCRIPT_OR_CONDITION_DATA_VERSION_1 = 1;
static const uint16_t K_SCRIPT_ACTION_VERSION_1 = 1;
static const uint16_t K_SCRIPT_ACTION_VERSION_2 = 2;
static const uint16_t K_SCRIPT_CONDITION_VERSION_1 = 1;
static const uint16_t K_SCRIPT_CONDITION_VERSION_2 = 2;
static const uint16_t K_SCRIPT_CONDITION_VERSION_3 = 3;
static const uint16_t K_SCRIPT_CONDITION_VERSION_4 = 4;
static const uint16_t K_SCRIPTS_DATA_VERSION_1 = 12;

ScriptParser::ScriptParser()
{
}

ScriptParser::~ScriptParser()
{
    if (m_file.is_open())
        m_file.close();
}

bool ScriptParser::parse(const std::string& filePath, ScriptsData& outData)
{
    m_file.open(filePath, std::ios::binary);
    if (!m_file.is_open())
    {
        m_error = "Failed to open file: " + filePath;
        return false;
    }

    // Read and validate header
    if (!readSymbolTable())
    {
        m_file.close();
        return false;
    }

    // Copy symbol table to output
    outData.symbolTable = m_symbolTable;

    // Parse the script data chunks
    if (!parseScriptsData(outData))
    {
        m_file.close();
        return false;
    }

    m_file.close();
    return true;
}

// Decrement dataLeft in ALL chunks in the stack (like the game engine does)
void ScriptParser::decrementDataLeft(int32_t size)
{
    for (auto& chunk : m_chunkStack)
    {
        chunk.dataLeft -= size;
    }
}

bool ScriptParser::readByte(uint8_t& value)
{
    m_file.read(reinterpret_cast<char*>(&value), sizeof(uint8_t));
    decrementDataLeft(sizeof(uint8_t));
    return m_file.good();
}

bool ScriptParser::readShort(uint16_t& value)
{
    m_file.read(reinterpret_cast<char*>(&value), sizeof(uint16_t));
    decrementDataLeft(sizeof(uint16_t));
    return m_file.good();
}

bool ScriptParser::readInt(int32_t& value)
{
    m_file.read(reinterpret_cast<char*>(&value), sizeof(int32_t));
    decrementDataLeft(sizeof(int32_t));
    return m_file.good();
}

bool ScriptParser::readUInt(uint32_t& value)
{
    m_file.read(reinterpret_cast<char*>(&value), sizeof(uint32_t));
    decrementDataLeft(sizeof(uint32_t));
    return m_file.good();
}

bool ScriptParser::readFloat(float& value)
{
    m_file.read(reinterpret_cast<char*>(&value), sizeof(float));
    decrementDataLeft(sizeof(float));
    return m_file.good();
}

bool ScriptParser::readString(std::string& value)
{
    uint16_t len;
    if (!readShort(len))
        return false;

    if (len > 0)
    {
        value.resize(len);
        m_file.read(&value[0], len);
        decrementDataLeft(len);
    }
    else
    {
        value.clear();
    }
    return m_file.good();
}

bool ScriptParser::skipDict()
{
    // Read pair count
    uint16_t pairCount;
    if (!readShort(pairCount))
        return false;
    
    // Skip each key-value pair
    for (uint16_t i = 0; i < pairCount; ++i)
    {
        // Read key and type (combined as int32)
        int32_t keyAndType;
        if (!readInt(keyAndType))
            return false;
        
        int32_t dataType = keyAndType & 0xFF;
        
        switch (static_cast<DictDataType>(dataType))
        {
            case DictDataType::DICT_BOOL:
            {
                uint8_t dummy;
                if (!readByte(dummy))
                    return false;
                break;
            }
            case DictDataType::DICT_INT:
            {
                int32_t dummy;
                if (!readInt(dummy))
                    return false;
                break;
            }
            case DictDataType::DICT_REAL:
            {
                float dummy;
                if (!readFloat(dummy))
                    return false;
                break;
            }
            case DictDataType::DICT_ASCIISTRING:
            {
                std::string dummy;
                if (!readString(dummy))
                    return false;
                break;
            }
            case DictDataType::DICT_UNICODESTRING:
            {
                // Unicode string: 2-byte length, then len*2 bytes
                uint16_t len;
                if (!readShort(len))
                    return false;
                if (len > 0)
                {
                    // Skip len * 2 bytes (wide chars)
                    m_file.seekg(len * 2, std::ios::cur);
                    decrementDataLeft(len * 2);
                }
                break;
            }
            default:
                // Unknown type, can't skip properly
                return false;
        }
    }
    
    return m_file.good();
}

bool ScriptParser::readSymbolTable()
{
    // Read header tag
    char tag[4];
    m_file.read(tag, 4);
    if (std::memcmp(tag, "CkMp", 4) != 0)
    {
        m_error = "Invalid file header - expected 'CkMp'";
        return false;
    }

    // Read symbol count
    int32_t count;
    m_file.read(reinterpret_cast<char*>(&count), sizeof(int32_t));
    if (!m_file.good())
    {
        m_error = "Failed to read symbol table count";
        return false;
    }

    // Read symbols
    m_symbolTable.clear();
    m_symbolOrder.clear();
    for (int32_t i = 0; i < count; ++i)
    {
        // Read string length (1 byte)
        uint8_t len;
        m_file.read(reinterpret_cast<char*>(&len), 1);
        if (!m_file.good())
        {
            m_error = "Failed to read symbol name length";
            return false;
        }

        // Read string
        std::string name;
        if (len > 0)
        {
            name.resize(len);
            m_file.read(&name[0], len);
        }

        // Read ID
        uint32_t id;
        m_file.read(reinterpret_cast<char*>(&id), sizeof(uint32_t));
        if (!m_file.good())
        {
            m_error = "Failed to read symbol ID";
            return false;
        }

        m_symbolTable[id] = name;
        m_symbolOrder.push_back({id, name}); // Preserve read order
    }

    return true;
}

std::string ScriptParser::getSymbolName(uint32_t id) const
{
    auto it = m_symbolTable.find(id);
    if (it != m_symbolTable.end())
        return it->second;
    return "";
}

bool ScriptParser::openChunk(ChunkInfo& chunk)
{
    // Check if parent chunk has enough data for a chunk header (10 bytes: 4+2+4)
    if (!m_chunkStack.empty() && m_chunkStack.back().dataLeft < 10)
        return false;

    // Read chunk ID (4 bytes)
    m_file.read(reinterpret_cast<char*>(&chunk.id), sizeof(uint32_t));
    if (!m_file.good())
        return false;
    decrementDataLeft(sizeof(uint32_t));

    chunk.name = getSymbolName(chunk.id);

    // Read version (2 bytes)
    m_file.read(reinterpret_cast<char*>(&chunk.version), sizeof(uint16_t));
    if (!m_file.good())
        return false;
    decrementDataLeft(sizeof(uint16_t));

    // Read data size (4 bytes)
    m_file.read(reinterpret_cast<char*>(&chunk.dataSize), sizeof(int32_t));
    if (!m_file.good())
        return false;
    decrementDataLeft(sizeof(int32_t));

    chunk.dataStart = m_file.tellg();
    chunk.dataLeft = chunk.dataSize;

    m_chunkStack.push_back(chunk);
    return true;
}

void ScriptParser::closeChunk(ChunkInfo& chunk)
{
    if (m_chunkStack.empty())
        return;
    
    // Get the ACTUAL chunk from the stack (not the copy passed in)
    ChunkInfo& actualChunk = m_chunkStack.back();
    
    // Skip any remaining data in this chunk
    if (actualChunk.dataLeft > 0)
    {
        // Seek to the end of this chunk's data
        std::streampos endPos = actualChunk.dataStart;
        endPos += actualChunk.dataSize;
        m_file.seekg(endPos);
        
        // Pop the chunk FIRST so decrementDataLeft doesn't decrement it
        m_chunkStack.pop_back();
        
        // Update parent chunks' dataLeft values for the skipped data
        decrementDataLeft(actualChunk.dataLeft);
    }
    else
    {
        m_chunkStack.pop_back();
    }
}

bool ScriptParser::atEndOfChunk() const
{
    if (m_chunkStack.empty())
        return true;
    return m_chunkStack.back().dataLeft <= 0;
}

bool ScriptParser::readDict(Dict& dict)
{
    // Read pair count
    uint16_t pairCount;
    if (!readShort(pairCount))
        return false;
    
    dict.entries.clear();
    dict.entries.reserve(pairCount);
    
    // Read each key-value pair
    for (uint16_t i = 0; i < pairCount; ++i)
    {
        DictEntry entry;
        
        // Read key and type (combined as int32)
        int32_t keyAndType;
        if (!readInt(keyAndType))
            return false;
        
        int32_t keyId = keyAndType >> 8;
        entry.type = static_cast<DictDataType>(keyAndType & 0xFF);
        entry.key = getSymbolName(keyId);
        
        switch (entry.type)
        {
            case DictDataType::DICT_BOOL:
            {
                uint8_t val;
                if (!readByte(val))
                    return false;
                entry.boolValue = (val != 0);
                break;
            }
            case DictDataType::DICT_INT:
            {
                if (!readInt(entry.intValue))
                    return false;
                break;
            }
            case DictDataType::DICT_REAL:
            {
                if (!readFloat(entry.realValue))
                    return false;
                break;
            }
            case DictDataType::DICT_ASCIISTRING:
            {
                if (!readString(entry.asciiValue))
                    return false;
                break;
            }
            case DictDataType::DICT_UNICODESTRING:
            {
                // Unicode string: 2-byte length, then len*2 bytes
                uint16_t len;
                if (!readShort(len))
                    return false;
                if (len > 0)
                {
                    entry.unicodeValue.resize(len);
                    m_file.read(reinterpret_cast<char*>(&entry.unicodeValue[0]), len * 2);
                    decrementDataLeft(len * 2);
                }
                break;
            }
            default:
                return false;
        }
        
        dict.entries.push_back(entry);
    }
    
    return m_file.good();
}

bool ScriptParser::parseScriptsData(ScriptsData& data)
{
    // Copy symbol table to data for round-trip support
    data.symbolList.clear();
    data.symbolToId.clear();
    data.idToSymbol = m_symbolTable;
    
    // Build ordered list and reverse mapping
    for (const auto& pair : m_symbolTable)
    {
        data.idToSymbol[pair.first] = pair.second;
        data.symbolToId[pair.second] = pair.first;
    }
    // Build ordered list (IDs are sequential starting from some base)
    if (!m_symbolTable.empty())
    {
        uint32_t maxId = 0;
        for (const auto& pair : m_symbolTable)
        {
            if (pair.first > maxId)
                maxId = pair.first;
        }
        data.symbolList.resize(maxId + 1);
        for (const auto& pair : m_symbolTable)
        {
            data.symbolList[pair.first] = pair.second;
        }
    }
    data.symbolTable = m_symbolTable;
    data.symbolOrder = m_symbolOrder; // Preserve original read order
    
    // Log chunk order for debugging
    std::vector<std::string> chunkOrder;
    
    while (!m_file.eof())
    {
        ChunkInfo chunk;
        if (!openChunk(chunk))
            break;

        // Log the order in which chunks are read
        chunkOrder.push_back(chunk.name);
        std::cout << "[CHUNK_ORDER] Found chunk: " << chunk.name << " (version " << chunk.version << ")" << std::endl;

        if (chunk.name == "PlayerScriptsList")
        {
            data.playerScriptsListVersion = chunk.version;
            
            // Parse script lists
            while (!atEndOfChunk() && !m_file.eof())
            {
                ChunkInfo listChunk;
                if (!openChunk(listChunk))
                    break;

                if (listChunk.name == "ScriptList")
                {
                    ScriptList list;
                    list.version = listChunk.version;
                    if (!parseScriptList(list))
                    {
                        closeChunk(listChunk);
                        closeChunk(chunk);
                        return false;
                    }
                    data.playerScripts.push_back(list);
                }
                closeChunk(listChunk);
            }
        }
        else if (chunk.name == "ScriptsPlayers")
        {
            data.scriptsPlayersVersion = chunk.version;
            
            // Parse player info
            int32_t doSides = 0;
            if (chunk.version >= 2)
            {
                readInt(doSides);
            }
            data.hasSideDicts = (doSides != 0);
            
            int32_t numPlayers = 0;
            readInt(numPlayers);
            
            for (int32_t i = 0; i < numPlayers; ++i)
            {
                PlayerInfo player;
                readString(player.name);
                data.playerNames.push_back(player.name);
                
                if (doSides)
                {
                    player.hasSideDict = true;
                    readDict(player.sideDict);
                }
                
                data.players.push_back(player);
            }
        }
        else if (chunk.name == "ObjectsList")
        {
            data.objectsListVersion = chunk.version;
            
            // Parse objects
            while (!atEndOfChunk() && !m_file.eof())
            {
                ChunkInfo objChunk;
                if (!openChunk(objChunk))
                    break;
                
                if (objChunk.name == "Object")
                {
                    MapObject obj;
                    obj.version = objChunk.version;
                    
                    readFloat(obj.location.x);
                    readFloat(obj.location.y);
                    readFloat(obj.location.z);
                    readFloat(obj.angle);
                    readInt(obj.flags);
                    readString(obj.name);
                    readDict(obj.properties);
                    
                    data.objects.push_back(obj);
                }
                closeChunk(objChunk);
            }
        }
        else if (chunk.name == "PolygonTriggers")
        {
            data.polygonTriggersVersion = chunk.version;
            
            int32_t count;
            readInt(count);
            
            for (int32_t i = 0; i < count; ++i)
            {
                PolygonTrigger trigger;
                readString(trigger.name);
                readInt(trigger.id);
                
                uint8_t isWater, isRiver;
                readByte(isWater);
                readByte(isRiver);
                trigger.isWaterArea = (isWater != 0);
                trigger.isRiver = (isRiver != 0);
                
                readInt(trigger.riverStart);
                
                int32_t numPoints;
                readInt(numPoints);
                
                for (int32_t j = 0; j < numPoints; ++j)
                {
                    ICoord3D point;
                    readInt(point.x);
                    readInt(point.y);
                    readInt(point.z);
                    trigger.points.push_back(point);
                }
                
                data.polygonTriggers.push_back(trigger);
            }
        }
        else if (chunk.name == "ScriptTeams")
        {
            data.scriptTeamsVersion = chunk.version;
            
            // Read team dicts until end of chunk
            while (!atEndOfChunk() && !m_file.eof())
            {
                Dict teamDict;
                if (!readDict(teamDict))
                    break;
                data.teams.push_back(teamDict);
            }
        }
        else if (chunk.name == "WaypointsList")
        {
            data.waypointsListVersion = chunk.version;
            
            int32_t count;
            readInt(count);
            
            for (int32_t i = 0; i < count; ++i)
            {
                WaypointLink link;
                readInt(link.waypointID1);
                readInt(link.waypointID2);
                data.waypointLinks.push_back(link);
            }
        }
        // If unknown chunk, closeChunk will skip its data
        
        closeChunk(chunk);
    }

    // Log the complete chunk order
    std::cout << "[CHUNK_ORDER] Complete order: ";
    for (size_t i = 0; i < chunkOrder.size(); ++i)
    {
        std::cout << chunkOrder[i];
        if (i < chunkOrder.size() - 1)
            std::cout << " -> ";
    }
    std::cout << std::endl;

    return true;
}

bool ScriptParser::parseScriptList(ScriptList& list)
{
    while (!atEndOfChunk() && !m_file.eof())
    {
        ChunkInfo chunk;
        if (!openChunk(chunk))
            break;

        if (chunk.name == "Script")
        {
            Script script;
            if (!parseScript(script, chunk.version))
            {
                closeChunk(chunk);
                return false;
            }
            list.scripts.push_back(script);
        }
        else if (chunk.name == "ScriptGroup")
        {
            ScriptGroup group;
            if (!parseScriptGroup(group))
            {
                closeChunk(chunk);
                return false;
            }
            list.groups.push_back(group);
        }
        closeChunk(chunk);
    }

    return true;
}

bool ScriptParser::parseScriptGroup(ScriptGroup& group)
{
    // Get the version of the current chunk (ScriptGroup)
    uint16_t chunkVersion = m_chunkStack.back().version;
    group.version = chunkVersion;

    // Read group name
    if (!readString(group.name))
        return false;

    // Read active flag
    uint8_t active;
    if (!readByte(active))
        return false;
    group.isActive = (active != 0);

    // Read subroutine flag (version 2+)
    if (chunkVersion >= K_SCRIPT_GROUP_DATA_VERSION_2)
    {
        uint8_t subroutine;
        if (!readByte(subroutine))
            return false;
        group.isSubroutine = (subroutine != 0);
    }

    // Parse scripts in group
    while (!atEndOfChunk() && !m_file.eof())
    {
        ChunkInfo chunk;
        if (!openChunk(chunk))
            break;

        if (chunk.name == "Script")
        {
            Script script;
            if (!parseScript(script, chunk.version))
            {
                closeChunk(chunk);
                return false;
            }
            group.scripts.push_back(script);
        }
        closeChunk(chunk);
    }

    return true;
}

bool ScriptParser::parseScript(Script& script, uint16_t version)
{
    script.version = version;
    
    // Read script properties
    if (!readString(script.name))
        return false;
    if (!readString(script.comment))
        return false;
    if (!readString(script.conditionComment))
        return false;
    if (!readString(script.actionComment))
        return false;

    uint8_t flags[6];
    for (int i = 0; i < 6; ++i)
    {
        if (!readByte(flags[i]))
            return false;
    }
    script.isActive = (flags[0] != 0);
    script.isOneShot = (flags[1] != 0);
    script.easy = (flags[2] != 0);
    script.normal = (flags[3] != 0);
    script.hard = (flags[4] != 0);
    script.isSubroutine = (flags[5] != 0);

    // Read delay (version 2+)
    if (version >= K_SCRIPT_DATA_VERSION_2)
    {
        if (!readInt(script.delayEvaluationSeconds))
            return false;
    }

    // Parse conditions, actions, and false actions
    while (!atEndOfChunk() && !m_file.eof())
    {
        ChunkInfo chunk;
        if (!openChunk(chunk))
            break;

        if (chunk.name == "OrCondition")
        {
            OrCondition orCond;
            if (!parseOrCondition(orCond))
            {
                closeChunk(chunk);
                return false;
            }
            script.conditions.push_back(orCond);
        }
        else if (chunk.name == "ScriptAction")
        {
            ScriptAction action;
            if (!parseAction(action, chunk.version))
            {
                closeChunk(chunk);
                return false;
            }
            script.actions.push_back(action);
        }
        else if (chunk.name == "ScriptActionFalse")
        {
            ScriptAction action;
            if (!parseAction(action, chunk.version))
            {
                closeChunk(chunk);
                return false;
            }
            script.falseActions.push_back(action);
        }
        closeChunk(chunk);
    }

    return true;
}

bool ScriptParser::parseOrCondition(OrCondition& orCond)
{
    // Store version from current chunk
    orCond.version = m_chunkStack.back().version;
    
    while (!atEndOfChunk() && !m_file.eof())
    {
        ChunkInfo chunk;
        if (!openChunk(chunk))
            break;

        if (chunk.name == "Condition")
        {
            Condition cond;
            if (!parseCondition(cond, chunk.version))
            {
                closeChunk(chunk);
                return false;
            }
            orCond.andConditions.push_back(cond);
        }
        closeChunk(chunk);
    }

    return true;
}

bool ScriptParser::parseCondition(Condition& cond, uint16_t version)
{
    cond.version = version;
    
    // Read condition type
    if (!readInt(cond.conditionType))
        return false;

    // Read name key (version 4+)
    if (version >= K_SCRIPT_CONDITION_VERSION_4)
    {
        if (!readNameKey(cond.conditionName))
            return false;
    }

    // Read parameter count
    int32_t numParams;
    if (!readInt(numParams))
        return false;

    // Read parameters
    for (int32_t i = 0; i < numParams; ++i)
    {
        Parameter param;
        if (!parseParameter(param))
            return false;
        cond.parameters.push_back(param);
    }

    return true;
}

bool ScriptParser::parseAction(ScriptAction& action, uint16_t version)
{
    action.version = version;
    
    // Read action type
    if (!readInt(action.actionType))
        return false;

    // Read name key (version 2+)
    if (version >= K_SCRIPT_ACTION_VERSION_2)
    {
        if (!readNameKey(action.actionName))
            return false;
    }

    // Read parameter count
    int32_t numParams;
    if (!readInt(numParams))
        return false;

    // Read parameters
    for (int32_t i = 0; i < numParams; ++i)
    {
        Parameter param;
        if (!parseParameter(param))
            return false;
        action.parameters.push_back(param);
    }

    return true;
}

bool ScriptParser::parseParameter(Parameter& param)
{
    // Read parameter type
    int32_t typeVal;
    if (!readInt(typeVal))
        return false;
    param.type = static_cast<ParameterType>(typeVal);

    if (param.type == ParameterType::COORD3D)
    {
        // Read coordinate
        if (!readFloat(param.coord.x))
            return false;
        if (!readFloat(param.coord.y))
            return false;
        if (!readFloat(param.coord.z))
            return false;
    }
    else
    {
        // Read int, real, string
        if (!readInt(param.intValue))
            return false;
        if (!readFloat(param.realValue))
            return false;
        if (!readString(param.stringValue))
            return false;
    }

    return true;
}

bool ScriptParser::readNameKey(std::string& name)
{
    int32_t keyAndType;
    if (!readInt(keyAndType))
        return false;

    // Extract key ID (upper 24 bits)
    uint32_t keyId = keyAndType >> 8;
    name = getSymbolName(keyId);
    return true;
}

} // namespace ScriptExport
