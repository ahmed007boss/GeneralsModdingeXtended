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

// FILE: DisplayNameUpgrade.cpp /////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//
//                       Electronic Arts Pacific.
//
//                       Confidential Information
//                Copyright (C) 2002 - All Rights Reserved
//
//-----------------------------------------------------------------------------
//
//	Created:	September 2002
//
//	Filename: DisplayNameUpgrade.cpp
//
//	Author:		Kris Morness
//
//	Purpose:	Shows or hides a list of subobjects based on upgrade statii. It
//            will override any animation subobjects states.
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#define DEFINE_OBJECT_STATUS_NAMES
#include "Common/Player.h"
#include "Common/Xfer.h"
#include "GameClient/Drawable.h"
#include "GameLogic/Object.h"
#include "GameLogic/Module/DisplayNameUpgrade.h"

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void DisplayNameUpgradeModuleData::buildFieldParse(MultiIniFieldParse& p)
{
	UpgradeModuleData::buildFieldParse(p);

	static const FieldParse dataFieldParse[] =
	{
		{ "DisplayName",		INI::parseAndTranslateLabel , NULL ,offsetof(DisplayNameUpgradeModuleData, m_displayName) },
		{ "DisplayPluralName",	INI::parseAndTranslateLabel , NULL ,offsetof(DisplayNameUpgradeModuleData, m_displayPluralName) }, // TheSuperHackers @feature Ahmed Salah 03/01/2026
		{ "Description",		INI::parseAndTranslateLabel , NULL ,offsetof(DisplayNameUpgradeModuleData, m_description) }, // TheSuperHackers @feature Ahmed Salah - Description support
		{ 0, 0, 0, 0 }
	};
	p.add(dataFieldParse);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
DisplayNameUpgrade::DisplayNameUpgrade(Thing* thing, const ModuleData* moduleData) : UpgradeModule(thing, moduleData)
{
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
DisplayNameUpgrade::~DisplayNameUpgrade(void)
{
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void DisplayNameUpgrade::upgradeImplementation()
{
	const DisplayNameUpgradeModuleData* data = getDisplayNameUpgradeModuleData();
	getObject()->setDisplayName(data->m_displayName);
	// TheSuperHackers @feature Ahmed Salah 03/01/2026 Also set plural name if specified
	if (!data->m_displayPluralName.isEmpty())
	{
		getObject()->setDisplayPluralName(data->m_displayPluralName);
	}
	// TheSuperHackers @feature Ahmed Salah - Description support
	if (!data->m_description.isEmpty())
	{
		getObject()->setDescription(data->m_description);
	}
}

//------------------------------------------------------------------------------------------------
void DisplayNameUpgrade::crc(Xfer* xfer)
{

	// extend base class
	UpgradeModule::crc(xfer);

}  // end crc

//------------------------------------------------------------------------------------------------
// Xfer method
// Version Info:
// 1: Initial version
//------------------------------------------------------------------------------------------------
void DisplayNameUpgrade::xfer(Xfer* xfer)
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion(&version, currentVersion);

	// extend base class
	UpgradeModule::xfer(xfer);

}  // end xfer

//------------------------------------------------------------------------------------------------
void DisplayNameUpgrade::loadPostProcess(void)
{

	// extend base class
	UpgradeModule::loadPostProcess();

}  // end loadPostProcess
