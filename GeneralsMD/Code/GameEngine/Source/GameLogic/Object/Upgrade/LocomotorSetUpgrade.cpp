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

// FILE: LocomotorSetUpgrade.cpp /////////////////////////////////////////////////////////////////////////////
// Author: Graham Smallwood, March 2002
// Desc:	 UpgradeModule that sets a weapon set bit for the Best Fit weapon set chooser to discover
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file in the GameEngine

#define DEFINE_LOCOMOTORSET_NAMES

#include "Common/Xfer.h"
#include "Common/INI.h"
#include "GameLogic/Object.h"
#include "GameLogic/Module/LocomotorSetUpgrade.h"
#include "GameLogic/Module/AIUpdate.h"

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
LocomotorSetUpgradeModuleData::LocomotorSetUpgradeModuleData(void)
{
	m_upgradeLevel = LOCOMOTORSET_NORMAL_UPGRADED;
}

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature Ahmed Salah 15/01/2025 Parse and validate locomotor upgrade level from INI
//-------------------------------------------------------------------------------------------------
void LocomotorSetUpgradeModuleData::parseUpgradeLevel(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	LocomotorSetUpgradeModuleData* data = static_cast<LocomotorSetUpgradeModuleData*>(instance);
	
	// Parse the locomotor set type using the standard name list
	LocomotorSetType set = (LocomotorSetType)INI::scanIndexList(ini->getNextToken(), TheLocomotorSetNames);
	
	// Validate that it's one of the allowed values
	if (set != LOCOMOTORSET_NORMAL &&
	    set != LOCOMOTORSET_NORMAL_UPGRADED &&
	    !(set >= LOCOMOTORSET_NORMAL_UPGRADED1 && set <= LOCOMOTORSET_NORMAL_UPGRADED8))
	{
		DEBUG_CRASH(("LocomotorSetUpgrade: UpgradeLevel must be LOCOMOTORSET_NORMAL, LOCOMOTORSET_NORMAL_UPGRADED, or LOCOMOTORSET_NORMAL_UPGRADED1-8"));
		throw INI_INVALID_DATA;
	}
	
	data->m_upgradeLevel = set;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void LocomotorSetUpgradeModuleData::buildFieldParse(MultiIniFieldParse& p)
{
	UpgradeModuleData::buildFieldParse(p);
	
	static const FieldParse dataFieldParse[] =
	{
		{ "UpgradeLevel", LocomotorSetUpgradeModuleData::parseUpgradeLevel, NULL, 0 },
		{ 0, 0, 0, 0 }
	};
	
	p.add(dataFieldParse);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
LocomotorSetUpgrade::LocomotorSetUpgrade( Thing *thing, const ModuleData* moduleData ) : UpgradeModule( thing, moduleData )
{
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
LocomotorSetUpgrade::~LocomotorSetUpgrade( void )
{
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void LocomotorSetUpgrade::upgradeImplementation( )
{
	const LocomotorSetUpgradeModuleData* data = getLocomotorSetUpgradeModuleData();
	AIUpdateInterface* ai = getObject()->getAIUpdateInterface();
	if (ai)
		ai->setLocomotorUpgrade(data->m_upgradeLevel);
}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
void LocomotorSetUpgrade::crc( Xfer *xfer )
{

	// extend base class
	UpgradeModule::crc( xfer );

}

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void LocomotorSetUpgrade::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	UpgradeModule::xfer( xfer );

}

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
void LocomotorSetUpgrade::loadPostProcess( void )
{

	// extend base class
	UpgradeModule::loadPostProcess();

}
