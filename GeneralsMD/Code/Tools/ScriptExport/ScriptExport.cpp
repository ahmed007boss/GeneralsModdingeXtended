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

// TheSuperHackers @feature AhmedSalah 12/01/2026 Command-line tool to decompile/compile SCB script files

#include "StdAfx.h"

#ifdef _WIN32
#define COLOR_RED     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY)
#define COLOR_GREEN   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define COLOR_YELLOW  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define COLOR_CYAN    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define COLOR_RESET   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#else
#define COLOR_RED     std::cout << "\033[31m"
#define COLOR_GREEN   std::cout << "\033[32m"
#define COLOR_YELLOW  std::cout << "\033[33m"
#define COLOR_CYAN    std::cout << "\033[36m"
#define COLOR_RESET   std::cout << "\033[0m"
#endif

#include "ScriptParser.h"
#include "ScriptWriter.h"
#include "YamlEmitter.h"
#include "YamlParser.h"

using namespace ScriptExport;
using namespace std;

void printUsage(const char* programName)
{
    cout << "\n";
    COLOR_CYAN;
    cout << "ScriptExportZH - SCB Script Decompiler/Compiler\n";
    COLOR_RESET;
    cout << "================================================\n\n";
    
    cout << "Usage:\n";
    cout << "  " << programName << " decompile <input.scb> <output_dir>\n";
    cout << "  " << programName << " compile <input_dir> <output.scb>\n";
    cout << "\n";
    
    cout << "Commands:\n";
    cout << "  decompile  Convert SCB binary to YAML folder structure\n";
    cout << "  compile    Convert YAML folder structure to SCB binary\n";
    cout << "\n";
    
    cout << "Examples:\n";
    COLOR_GREEN;
    cout << "  " << programName << " decompile SkirmishScripts.scb ./scripts\n";
    cout << "  " << programName << " compile ./scripts NewScripts.scb\n";
    COLOR_RESET;
    cout << "\n";
    
    cout << "Output Structure (decompile):\n";
    cout << "  <output_dir>/\n";
    cout << "    manifest.yaml           - File listing all players\n";
    cout << "    Player1/\n";
    cout << "      list.yaml             - Player script list manifest\n";
    cout << "      Scripts/              - Ungrouped scripts\n";
    cout << "        000_ScriptName.yaml\n";
    cout << "      Groups/               - Script groups\n";
    cout << "        000_GroupName/\n";
    cout << "          group.yaml        - Group manifest\n";
    cout << "          000_ScriptName.yaml\n";
    cout << "    Player2/\n";
    cout << "      ...\n";
    cout << "\n";
}

int decompile(const string& inputFile, const string& outputDir)
{
    cout << "Decompiling: " << inputFile << "\n";
    cout << "Output dir:  " << outputDir << "\n\n";
    
    ScriptParser parser;
    ScriptsData data;
    
    if (!parser.parse(inputFile, data))
    {
        COLOR_RED;
        cerr << "Error: " << parser.getError() << "\n";
        COLOR_RESET;
        return 1;
    }
    
    cout << "Parsed " << data.playerScripts.size() << " player script list(s)\n";
    
    // Show player names if available
    if (!data.playerNames.empty())
    {
        cout << "Players:\n";
        for (size_t i = 0; i < data.playerNames.size(); ++i)
        {
            cout << "  " << (i + 1) << ". " << data.playerNames[i] << "\n";
        }
    }
    
    // Count scripts
    int totalScripts = 0;
    int totalGroups = 0;
    for (const auto& list : data.playerScripts)
    {
        totalScripts += static_cast<int>(list.scripts.size());
        totalGroups += static_cast<int>(list.groups.size());
        for (const auto& group : list.groups)
        {
            totalScripts += static_cast<int>(group.scripts.size());
        }
    }
    cout << "\nFound " << totalGroups << " group(s), " << totalScripts << " script(s)\n";
    
    // Show additional data
    if (!data.objects.empty())
        cout << "Objects: " << data.objects.size() << "\n";
    if (!data.polygonTriggers.empty())
        cout << "Polygon Triggers: " << data.polygonTriggers.size() << "\n";
    if (!data.teams.empty())
        cout << "Teams: " << data.teams.size() << "\n";
    if (!data.waypointLinks.empty())
        cout << "Waypoint Links: " << data.waypointLinks.size() << "\n";
    cout << "Symbol Table: " << data.symbolTable.size() << " symbols\n\n";
    
    YamlEmitter emitter;
    if (!emitter.write(outputDir, data))
    {
        COLOR_RED;
        cerr << "Error: " << emitter.getError() << "\n";
        COLOR_RESET;
        return 1;
    }
    
    COLOR_GREEN;
    cout << "\nDecompilation complete!\n";
    COLOR_RESET;
    cout << "Output written to: " << outputDir << "\n";
    
    return 0;
}

int compile(const string& inputDir, const string& outputFile)
{
    cout << "Compiling:   " << inputDir << "\n";
    cout << "Output file: " << outputFile << "\n\n";
    
    YamlParser parser;
    ScriptsData data;
    
    if (!parser.read(inputDir, data))
    {
        COLOR_RED;
        cerr << "Error: " << parser.getError() << "\n";
        COLOR_RESET;
        return 1;
    }
    
    cout << "Loaded " << data.playerScripts.size() << " player script list(s)\n";
    
    // Count scripts
    int totalScripts = 0;
    int totalGroups = 0;
    for (const auto& list : data.playerScripts)
    {
        totalScripts += static_cast<int>(list.scripts.size());
        totalGroups += static_cast<int>(list.groups.size());
        for (const auto& group : list.groups)
        {
            totalScripts += static_cast<int>(group.scripts.size());
        }
    }
    cout << "Found " << totalGroups << " group(s), " << totalScripts << " script(s)\n";
    
    // Show additional data
    if (!data.objects.empty())
        cout << "Objects: " << data.objects.size() << "\n";
    if (!data.polygonTriggers.empty())
        cout << "Polygon Triggers: " << data.polygonTriggers.size() << "\n";
    if (!data.teams.empty())
        cout << "Teams: " << data.teams.size() << "\n";
    if (!data.waypointLinks.empty())
        cout << "Waypoint Links: " << data.waypointLinks.size() << "\n";
    cout << "\n";
    
    ScriptWriter writer;
    if (!writer.write(outputFile, data))
    {
        COLOR_RED;
        cerr << "Error: " << writer.getError() << "\n";
        COLOR_RESET;
        return 1;
    }
    
    COLOR_GREEN;
    cout << "\nCompilation complete!\n";
    COLOR_RESET;
    cout << "Output written to: " << outputFile << "\n";
    
    return 0;
}

int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        printUsage(argv[0]);
        return 1;
    }
    
    string command = argv[1];
    string input = argv[2];
    string output = argv[3];
    
    if (command == "decompile")
    {
        return decompile(input, output);
    }
    else if (command == "compile")
    {
        return compile(input, output);
    }
    else
    {
        COLOR_RED;
        cerr << "Error: Unknown command '" << command << "'\n";
        COLOR_RESET;
        printUsage(argv[0]);
        return 1;
    }
}
