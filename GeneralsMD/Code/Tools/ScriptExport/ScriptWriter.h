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

// TheSuperHackers @feature AhmedSalah 12/01/2026 SCB file writer for ScriptExport tool

#pragma once

#include "StdAfx.h"
#include "ScriptTypes.h"

namespace ScriptExport
{

/**
 * Writer for SCB (Script Binary) files
 * Compiles YAML scripts back to binary format
 */
class ScriptWriter
{
public:
    ScriptWriter();
    ~ScriptWriter();

    /**
     * Write scripts data to an SCB file
     * @param filePath Path to the output SCB file
     * @param data Scripts data to write (symbolTable used if available)
     * @return true on success, false on failure
     */
    bool write(const std::string& filePath, const ScriptsData& data);
    
    /**
     * Set whether to preserve the original symbol table
     * When true, uses IDs from data.symbolTable instead of generating new ones
     */
    void setPreserveSymbols(bool preserve) { m_preserveSymbols = preserve; }

    /**
     * Get the last error message
     */
    const std::string& getError() const { return m_error; }

private:
    // Write primitives
    void writeByte(uint8_t value);
    void writeShort(uint16_t value);
    void writeInt(int32_t value);
    void writeUInt(uint32_t value);
    void writeFloat(float value);
    void writeString(const std::string& value);
    void writeNameKey(const std::string& name);

    // Symbol table management
    uint32_t allocateSymbol(const std::string& name);

    // Open/close chunks
    void openChunk(const std::string& name, uint16_t version);
    void closeChunk();

    // Write script elements
    void writeScriptsData(const ScriptsData& data);
    void writeScriptList(const ScriptList& list);
    void writeScriptGroup(const ScriptGroup& group);
    void writeScript(const Script& script);
    void writeOrCondition(const OrCondition& orCond);
    void writeCondition(const Condition& cond);
    void writeAction(const ScriptAction& action, bool isFalse);
    void writeParameter(const Parameter& param);
    void writeDict(const Dict& dict);

    // Finalize and write to file
    bool finalize(const std::string& filePath);

    std::string m_error;
    std::vector<char> m_buffer; // Temporary buffer for chunk data
    std::map<std::string, uint32_t> m_symbolTable;
    uint32_t m_nextSymbolId;
    bool m_preserveSymbols = false;
    const ScriptsData* m_sourceData = nullptr;
    
    struct ChunkState
    {
        uint32_t id;
        size_t sizePosition; // Position where size needs to be written
        size_t dataStart;
    };
    std::vector<ChunkState> m_chunkStack;
};

} // namespace ScriptExport
