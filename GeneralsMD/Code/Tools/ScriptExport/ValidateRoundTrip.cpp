/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
*/

// TheSuperHackers @feature AhmedSalah 12/01/2026 Validation tool to compare SCB files

#include "StdAfx.h"
#include "ScriptParser.h"
#include <iomanip>

using namespace ScriptExport;
using namespace std;

void compareSymbolTables(const ScriptsData& original, const ScriptsData& compiled)
{
    cout << "\n=== Symbol Table Comparison ===\n";
    cout << "Original symbols: " << original.symbolTable.size() << "\n";
    cout << "Compiled symbols: " << compiled.symbolTable.size() << "\n";
    
    if (original.symbolTable.size() != compiled.symbolTable.size())
    {
        cout << "WARNING: Symbol count mismatch!\n";
    }
    
    // Check for missing symbols
    for (const auto& pair : original.symbolTable)
    {
        auto it = compiled.symbolTable.find(pair.first);
        if (it == compiled.symbolTable.end())
        {
            cout << "MISSING symbol ID " << pair.first << ": " << pair.second << "\n";
        }
        else if (it->second != pair.second)
        {
            cout << "DIFFERENT symbol ID " << pair.first << ": original='" << pair.second 
                 << "' compiled='" << it->second << "'\n";
        }
    }
    
    // Check for extra symbols
    for (const auto& pair : compiled.symbolTable)
    {
        if (original.symbolTable.find(pair.first) == original.symbolTable.end())
        {
            cout << "EXTRA symbol ID " << pair.first << ": " << pair.second << "\n";
        }
    }
}

void compareScriptCounts(const ScriptsData& original, const ScriptsData& compiled)
{
    cout << "\n=== Script Count Comparison ===\n";
    
    if (original.playerScripts.size() != compiled.playerScripts.size())
    {
        cout << "WARNING: Player count mismatch: " << original.playerScripts.size() 
             << " vs " << compiled.playerScripts.size() << "\n";
    }
    
    size_t maxPlayers = min(original.playerScripts.size(), compiled.playerScripts.size());
    for (size_t i = 0; i < maxPlayers; ++i)
    {
        const auto& origList = original.playerScripts[i];
        const auto& compList = compiled.playerScripts[i];
        
        size_t origScripts = origList.scripts.size();
        size_t compScripts = compList.scripts.size();
        size_t origGroups = origList.groups.size();
        size_t compGroups = compList.groups.size();
        
        for (const auto& group : origList.groups)
            origScripts += group.scripts.size();
        for (const auto& group : compList.groups)
            compScripts += group.scripts.size();
        
        if (origScripts != compScripts || origGroups != compGroups)
        {
            cout << "Player " << i << ": scripts " << origScripts << "->" << compScripts 
                 << ", groups " << origGroups << "->" << compGroups << "\n";
        }
    }
}

void compareTeams(const ScriptsData& original, const ScriptsData& compiled)
{
    cout << "\n=== Teams Comparison ===\n";
    cout << "Original teams: " << original.teams.size() << "\n";
    cout << "Compiled teams: " << compiled.teams.size() << "\n";
    
    if (original.teams.size() != compiled.teams.size())
    {
        cout << "WARNING: Team count mismatch!\n";
    }
    
    size_t maxTeams = min(original.teams.size(), compiled.teams.size());
    for (size_t i = 0; i < maxTeams && i < 10; ++i) // Check first 10 teams
    {
        const auto& origTeam = original.teams[i];
        const auto& compTeam = compiled.teams[i];
        
        if (origTeam.entries.size() != compTeam.entries.size())
        {
            cout << "Team " << i << ": entry count " << origTeam.entries.size() 
                 << "->" << compTeam.entries.size() << "\n";
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        cout << "Usage: ValidateRoundTrip <original.scb> <compiled.scb>\n";
        cout << "Compares two SCB files and reports differences\n";
        return 1;
    }
    
    string originalPath = argv[1];
    string compiledPath = argv[2];
    
    ScriptParser parser;
    ScriptsData original, compiled;
    
    cout << "Parsing original file: " << originalPath << "\n";
    if (!parser.parse(originalPath, original))
    {
        cerr << "Error parsing original: " << parser.getError() << "\n";
        return 1;
    }
    
    cout << "Parsing compiled file: " << compiledPath << "\n";
    if (!parser.parse(compiledPath, compiled))
    {
        cerr << "Error parsing compiled: " << parser.getError() << "\n";
        return 1;
    }
    
    compareSymbolTables(original, compiled);
    compareScriptCounts(original, compiled);
    compareTeams(original, compiled);
    
    cout << "\n=== Summary ===\n";
    cout << "Comparison complete. Review differences above.\n";
    
    return 0;
}
