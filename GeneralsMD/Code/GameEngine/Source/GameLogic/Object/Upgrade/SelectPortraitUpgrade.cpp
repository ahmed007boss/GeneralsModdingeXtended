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

// FILE: SelectPortraitUpgrade.cpp /////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//
//	Created:	January 2026
//
//	Filename: SelectPortraitUpgrade.cpp
//
//	Author:		Ahmed Salah
//
//	Purpose:	Changes an object's select portrait image and/or video when
//            an upgrade is applied.
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/Player.h"
#include "Common/Xfer.h"
#include "GameClient/Drawable.h"
#include "GameLogic/Object.h"
#include "GameLogic/Module/SelectPortraitUpgrade.h"

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void SelectPortraitUpgradeModuleData::buildFieldParse(MultiIniFieldParse& p)
{
	UpgradeModuleData::buildFieldParse(p);

	static const FieldParse dataFieldParse[] =
	{
		{ "SelectPortrait",			INI::parseAsciiString, NULL, offsetof(SelectPortraitUpgradeModuleData, m_selectPortrait) },
		{ "SelectPortraitVideo",	INI::parseAsciiString, NULL, offsetof(SelectPortraitUpgradeModuleData, m_selectPortraitVideo) },
		{ 0, 0, 0, 0 }
	};
	p.add(dataFieldParse);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
SelectPortraitUpgrade::SelectPortraitUpgrade(Thing* thing, const ModuleData* moduleData) : UpgradeModule(thing, moduleData)
{
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
SelectPortraitUpgrade::~SelectPortraitUpgrade(void)
{
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void SelectPortraitUpgrade::upgradeImplementation()
{
	const SelectPortraitUpgradeModuleData* data = getSelectPortraitUpgradeModuleData();
	
	if (data->m_selectPortrait.isNotEmpty())
	{
		getObject()->setSelectPortrait(data->m_selectPortrait);
	}
	
	if (data->m_selectPortraitVideo.isNotEmpty())
	{
		getObject()->setSelectPortraitVideo(data->m_selectPortraitVideo);
	}
}
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void SelectPortraitUpgrade::downgradeImplementation()
{
	const SelectPortraitUpgradeModuleData* data = getSelectPortraitUpgradeModuleData();

	if (data->m_selectPortrait.isNotEmpty())
	{
		getObject()->setSelectPortrait("");
	}

	if (data->m_selectPortraitVideo.isNotEmpty())
	{
		getObject()->setSelectPortraitVideo("");
	}
}
//------------------------------------------------------------------------------------------------
void SelectPortraitUpgrade::crc(Xfer* xfer)
{
	// extend base class
	UpgradeModule::crc(xfer);
}

//------------------------------------------------------------------------------------------------
// Xfer method
// Version Info:
// 1: Initial version
//------------------------------------------------------------------------------------------------
void SelectPortraitUpgrade::xfer(Xfer* xfer)
{
	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion(&version, currentVersion);

	// extend base class
	UpgradeModule::xfer(xfer);
}

//------------------------------------------------------------------------------------------------
void SelectPortraitUpgrade::loadPostProcess(void)
{
	// extend base class
	UpgradeModule::loadPostProcess();
}
