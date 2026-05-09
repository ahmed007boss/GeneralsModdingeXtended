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

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: INIVideo.cpp /////////////////////////////////////////////////////////////////////////////
// Author: John McDonald, February 2002
// Desc:   Parsing Video INI entries
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file in the GameEngine

#include "Common/INI.h"
#include "GameClient/VideoPlayer.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA ///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
/** Extract object directory path from INI file path
 *  Returns the full path from start to the object directory (e.g., "Data\INI\Object\gla\defences\artillerybunker\")
 *  Returns empty string if the file is not in Data\INI\Object\ directory
 */
//-------------------------------------------------------------------------------------------------
static AsciiString extractObjectDirectoryFromPath(const AsciiString& iniFilename)
{
	AsciiString objectDirectory;
	
	if (iniFilename.getLength() == 0)
	{
		return objectDirectory;
	}
	
	const char* filenameStr = iniFilename.str();
	
	// Check if path contains the object directory marker (case-insensitive)
	AsciiString lowerPath = iniFilename;
	lowerPath.toLower();
	const char* lowerPathStr = lowerPath.str();
	const char* markerPos = strstr(lowerPathStr, "data\\ini\\object\\");
	const char* markerPosAlt = strstr(lowerPathStr, "data/ini/object/");
	
	// Use whichever marker is found (prefer backslash)
	const char* foundMarker = markerPos ? markerPos : markerPosAlt;
	
	if (foundMarker != NULL)
	{
		// Find the last separator (backslash or forward slash) before the filename
		// The filename starts after the last separator
		const char* lastSeparator = NULL;
		const char* end = filenameStr + iniFilename.getLength();
		
		// Search backwards from the end to find the last separator
		for (const char* p = end - 1; p >= filenameStr; p--)
		{
			if (*p == '\\' || *p == '/')
			{
				lastSeparator = p;
				break;
			}
		}
		
		// If we found a separator, extract the path from start to that separator (inclusive)
		if (lastSeparator != NULL)
		{
			int pathLen = (lastSeparator - filenameStr) + 1; // +1 to include the separator
			objectDirectory.set(filenameStr, pathLen);
		}
	}
	
	return objectDirectory;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
/** Parse Music entry */
//-------------------------------------------------------------------------------------------------
void INI::parseVideoDefinition( INI* ini )
{
	// read the name
	const char* c = ini->getNextToken();

	Video video;
	video.m_internalName.set( c );

	ini->initFromINI(&video, TheVideoPlayer->getFieldParse() );
	
	// Extract object directory from file path if video is in Data\INI\Object\{ObjectName}\ directory
	AsciiString filename = ini->getFilename();
	video.m_objectDirectory = extractObjectDirectoryFromPath(filename);
	
	TheVideoPlayer->addVideo(&video);


}


