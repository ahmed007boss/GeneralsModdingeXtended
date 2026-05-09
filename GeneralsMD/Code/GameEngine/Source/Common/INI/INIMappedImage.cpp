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

// FILE: INIMappedImage.cpp ///////////////////////////////////////////////////////////////////////
// Author: Colin Day, December 2001
// Desc:   Mapped image INI parsing
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file in the GameEngine

#include "Common/INI.h"
#include "GameClient/Image.h"

// PRIVATE FUNCTIONS ///////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------------------------------
/** Extract directory path from INI filename and append Art/UI */
//-------------------------------------------------------------------------------------------------
static AsciiString extractDirectoryPath(const AsciiString& iniFilename)
{
	AsciiString directoryPath;
	
	if (iniFilename.getLength() > 0)
	{
		// Find the last directory separator using reverseFind
		const char* lastSlash = iniFilename.reverseFind('\\');
		const char* lastForwardSlash = iniFilename.reverseFind('/');
		const char* lastSeparator = (lastSlash > lastForwardSlash) ? lastSlash : lastForwardSlash;
		
		if (lastSeparator != NULL)
		{
			// Extract directory path and append Art/UI
			int separatorPos = lastSeparator - iniFilename.str();
			directoryPath = iniFilename;
			directoryPath.truncateTo(separatorPos + 1);
			directoryPath += "Art/UI/";
		}
		else
		{
			// No directory separator found, use current directory
			directoryPath = "Art/UI/";
		}
	}
	else
	{
		// No filename available, use default
		directoryPath = "Art/UI/";
	}
	
	return directoryPath;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
/** Parse mapped image entry */
//-------------------------------------------------------------------------------------------------
void INI::parseMappedImageDefinition( INI* ini )
{
	// read the name
	const char* name = ini->getNextToken();
	//
	// find existing item if present, note that we do not support overrides
	// in the images like we do in systems that are more "design" oriented, images
	// are assets as they are
	//
	if( !TheMappedImageCollection )
	{
		//We don't need it if we're in the builder... which doesn't have this.
		return;
	}
	Image *image = const_cast<Image*>(TheMappedImageCollection->findImageByName( name ));
	if(image && ini->getFilename().startsWithNoCase("Data\\INI\\MappedImages\\"))
		DEBUG_ASSERTCRASH(!image->getRawTextureData(), ("We are trying to parse over an existing image that contains a non-null rawTextureData, you should fix that"));

	if( image == NULL || !ini->getFilename().startsWithNoCase("Data\\INI\\MappedImages\\"))
	{

		// image not found, create a new one
  		image = newInstance(Image);
		image->setName( name );
		
		// TheSuperHackers @feature author 15/01/2025 Extract directory from INI filename and append Art/UI
		AsciiString iniFilename = ini->getFilename();
		AsciiString iniDirectoryPath = extractDirectoryPath(iniFilename);
		image->setIniDirectory(iniDirectoryPath);
		
		TheMappedImageCollection->addImage(image);
		DEBUG_ASSERTCRASH( image, ("parseMappedImage: unable to allocate image for '%s'", name) );

	}

	// parse the ini definition
	ini->initFromINI( image, image->getFieldParse());

}
