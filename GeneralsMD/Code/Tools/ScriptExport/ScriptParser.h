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

// TheSuperHackers @feature AhmedSalah 12/01/2026 SCB file parser for ScriptExport tool

#pragma once

#include "StdAfx.h"
#include "ScriptTypes.h"

namespace ScriptExport
{

/**
 * Parser for SCB (Script Binary) files
 * 
 * SCB file format:
 * - Header: "CkMp" (4 bytes)
 * - Symbol table length (4 bytes)
 * - Symbol table entries: [length(1), name(length), id(4)] * count
 * - Data chunks: [id(4), version(2), size(4), data(size)] * count
 */
class ScriptParser
{
public:
    ScriptParser();
    ~ScriptParser();

    /**
     * Parse an SCB file and return the scripts data
     * @param filePath Path to the SCB file
     * @param outData Output scripts data
     * @return true on success, false on failure
     */
    bool parse(const std::string& filePath, ScriptsData& outData);

    /**
     * Get the last error message
     */
    const std::string& getError() const { return m_error; }

private:
    // Decrement dataLeft in all chunks in the stack
    void decrementDataLeft(int32_t size);

    // Read primitives from file
    bool readByte(uint8_t& value);
    bool readShort(uint16_t& value);
    bool readInt(int32_t& value);
    bool readUInt(uint32_t& value);
    bool readFloat(float& value);
    bool readString(std::string& value);
    bool skipDict(); // Skip over a Dict structure
    bool readDict(Dict& dict); // Read a Dict structure

    // Read symbol table
    bool readSymbolTable();

    // Get symbol name by ID
    std::string getSymbolName(uint32_t id) const;

    // Chunk parsing
    struct ChunkInfo
    {
        uint32_t id;
        std::string name;
        uint16_t version;
        int32_t dataSize;
        std::streampos dataStart;
        int32_t dataLeft;
    };

    bool openChunk(ChunkInfo& chunk);
    void closeChunk(ChunkInfo& chunk);
    bool atEndOfChunk() const;

    // Script element parsing
    bool parseScriptsData(ScriptsData& data);
    bool parseScriptList(ScriptList& list);
    bool parseScriptGroup(ScriptGroup& group);
    bool parseScript(Script& script, uint16_t version);
    bool parseOrCondition(OrCondition& orCond);
    bool parseCondition(Condition& cond, uint16_t version);
    bool parseAction(ScriptAction& action, uint16_t version);
    bool parseParameter(Parameter& param);

    // Parse name key from symbol table
    bool readNameKey(std::string& name);

    std::ifstream m_file;
    std::string m_error;
    std::map<uint32_t, std::string> m_symbolTable;
    std::vector<ChunkInfo> m_chunkStack;
};

} // namespace ScriptExport
