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

// FILE: GrantUpgradeOnUpgrade.cpp /////////////////////////////////////////////////////////////////////////////
// Author: TheSuperHackers @feature author 15/01/2025
// Desc:	 UpgradeModule that grants another upgrade (player or object) when triggered by an upgrade.
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file in the GameEngine

#define DEFINE_OBJECT_STATUS_NAMES
#include "Common/Player.h"
#include "Common/Upgrade.h"
#include "Common/Xfer.h"
#include "GameLogic/Object.h"
#include "GameLogic/Module/GrantUpgradeOnUpgrade.h"


//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void GrantUpgradeOnUpgradeModuleData::buildFieldParse(MultiIniFieldParse& p)
{
  UpgradeModuleData::buildFieldParse( p );

	static const FieldParse dataFieldParse[] =
	{
		{ "UpgradesToGrant",	INI::parseAsciiStringVectorAppend, NULL, offsetof( GrantUpgradeOnUpgradeModuleData, m_upgradesToGrant ) },
		{ "RemoveUpgradesOnDowngrade", INI::parseBool, NULL, offsetof( GrantUpgradeOnUpgradeModuleData, m_removeUpgradesOnDowngrade ) },
		{ 0, 0, 0, 0 }
	};

  p.add(dataFieldParse);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
GrantUpgradeOnUpgrade::GrantUpgradeOnUpgrade( Thing *thing, const ModuleData* moduleData ) : UpgradeModule( thing, moduleData )
{
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
GrantUpgradeOnUpgrade::~GrantUpgradeOnUpgrade( void )
{
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void GrantUpgradeOnUpgrade::upgradeImplementation( )
{
	const GrantUpgradeOnUpgradeModuleData *data = getGrantUpgradeOnUpgradeModuleData();
	if( !data )
	{
		return;
	}

	if( data->m_upgradesToGrant.empty() )
	{
		return;
	}

	Object *obj = getObject();
	if( !obj || obj->isEffectivelyDead() )
	{
		return;
	}

	// TheSuperHackers @feature author 15/01/2025 Don't grant upgrades during object construction (matches GrantUpgradeCreate pattern)
	if( obj->getStatusBits().test( OBJECT_STATUS_UNDER_CONSTRUCTION ) )
	{
		return;
	}

	Player *player = obj->getControllingPlayer();
	if( !player )
	{
		return;
	}

	// TheSuperHackers @feature author 15/01/2025 Grant all specified upgrades
	std::vector<AsciiString>::const_iterator upgradeName;
	for( upgradeName = data->m_upgradesToGrant.begin(); upgradeName != data->m_upgradesToGrant.end(); ++upgradeName )
	{
		const UpgradeTemplate *upgradeTemplate = TheUpgradeCenter->findUpgrade( *upgradeName );
		if( !upgradeTemplate )
		{
			continue;
		}

		// Check if upgrade is already granted to prevent unnecessary work
		UpgradeMaskType upgradeMask = upgradeTemplate->getUpgradeMask();
		if( upgradeTemplate->getUpgradeType() == UPGRADE_TYPE_PLAYER )
		{
			// Check if player already has this upgrade
			if( player->getCompletedUpgradeMask().testForAny( upgradeMask ) )
			{
				continue;
			}
			// Grant player upgrade
			player->addUpgrade( upgradeTemplate, UPGRADE_STATUS_COMPLETE );
			// Only record in academy stats if object is not under construction (matches GrantUpgradeCreate pattern)
			if( !obj->getStatusBits().test( OBJECT_STATUS_UNDER_CONSTRUCTION ) )
			{
				player->getAcademyStats()->recordUpgrade( upgradeTemplate, TRUE );
			}
		}
		else
		{
			// Check if object already has this upgrade
			if( obj->getObjectCompletedUpgradeMask().testForAny( upgradeMask ) )
			{
				continue;
			}
			// Grant object upgrade
			obj->giveUpgrade( upgradeTemplate );
			// Only record in academy stats if object is not under construction (matches GrantUpgradeCreate pattern)
			if( !obj->getStatusBits().test( OBJECT_STATUS_UNDER_CONSTRUCTION ) )
			{
				player->getAcademyStats()->recordUpgrade( upgradeTemplate, TRUE );
			}
		}
	}
}
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void GrantUpgradeOnUpgrade::downgradeImplementation()
{
	const GrantUpgradeOnUpgradeModuleData *data = getGrantUpgradeOnUpgradeModuleData();
	if( !data )
	{
		return;
	}

	// Only remove upgrades if the INI attribute is enabled
	if( !data->m_removeUpgradesOnDowngrade )
	{
		return;
	}

	if( data->m_upgradesToGrant.empty() )
	{
		return;
	}

	Object *obj = getObject();
	if( !obj || obj->isEffectivelyDead() )
	{
		return;
	}

	// TheSuperHackers @feature author 15/01/2025 Don't remove upgrades during object destruction
	if( obj->getStatusBits().test( OBJECT_STATUS_UNDER_CONSTRUCTION ) )
	{
		return;
	}

	Player *player = obj->getControllingPlayer();
	if( !player )
	{
		return;
	}

	// TheSuperHackers @feature author 15/01/2025 Remove all previously granted upgrades
	std::vector<AsciiString>::const_iterator upgradeName;
	for( upgradeName = data->m_upgradesToGrant.begin(); upgradeName != data->m_upgradesToGrant.end(); ++upgradeName )
	{
		const UpgradeTemplate *upgradeTemplate = TheUpgradeCenter->findUpgrade( *upgradeName );
		if( !upgradeTemplate )
		{
			continue;
		}

		// TheSuperHackers @feature author 15/01/2025 Handle both player and object upgrades
		if( upgradeTemplate->getUpgradeType() == UPGRADE_TYPE_PLAYER )
		{
			// Remove player upgrade
			player->removeUpgrade( upgradeTemplate );
		}
		else
		{
			// Remove object upgrade
			obj->removeUpgrade( upgradeTemplate );
		}
	}
}
// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
void GrantUpgradeOnUpgrade::crc( Xfer *xfer )
{

	// extend base class
	UpgradeModule::crc( xfer );

}

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void GrantUpgradeOnUpgrade::xfer( Xfer *xfer )
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
void GrantUpgradeOnUpgrade::loadPostProcess( void )
{

	// extend base class
	UpgradeModule::loadPostProcess();

}
