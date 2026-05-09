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

// FILE: CommandSetUpgrade.cpp /////////////////////////////////////////////////////////////////////////////
// Author: Graham Smallwood, September 2002
// Desc:	 UpgradeModule that sets a new override string for Command Set look ups
///////////////////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file in the GameEngine

#include "Common/Xfer.h"
#include "Common/Player.h"
#include "GameClient/ControlBar.h"
#include "GameLogic/Module/CommandSetUpgrade.h"
#include "GameLogic/Object.h"

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
void CommandSetUpgradeModuleData::buildFieldParse(MultiIniFieldParse& p)
{
  UpgradeModuleData::buildFieldParse(p);

	static const FieldParse dataFieldParse[] =
	{
		{ "CommandSet",			INI::parseAsciiString,	NULL, offsetof( CommandSetUpgradeModuleData, m_newCommandSet) },
		{ "CommandSetAlt",	INI::parseAsciiString,	NULL, offsetof( CommandSetUpgradeModuleData, m_newCommandSetAlt) },

		{ "CommandSet2",			INI::parseAsciiString,	NULL, offsetof(CommandSetUpgradeModuleData, m_newCommandSet2) },
		{ "CommandSet2Alt",	INI::parseAsciiString,	NULL, offsetof(CommandSetUpgradeModuleData, m_newCommandSet2Alt) },

		{ "CommandSet3",			INI::parseAsciiString,	NULL, offsetof(CommandSetUpgradeModuleData, m_newCommandSet3) },
		{ "CommandSet3Alt",	INI::parseAsciiString,	NULL, offsetof(CommandSetUpgradeModuleData, m_newCommandSet3Alt) },

		{ "CommandSet4",			INI::parseAsciiString,	NULL, offsetof(CommandSetUpgradeModuleData, m_newCommandSet4) },
		{ "CommandSet4Alt",	INI::parseAsciiString,	NULL, offsetof(CommandSetUpgradeModuleData, m_newCommandSet4Alt) },

		{ "TriggerAlt",			INI::parseAsciiString,	NULL, offsetof( CommandSetUpgradeModuleData, m_triggerAlt ) },
		{ 0, 0, 0, 0 }
	};
  p.add(dataFieldParse);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
CommandSetUpgrade::CommandSetUpgrade( Thing *thing, const ModuleData* moduleData ) : UpgradeModule( thing, moduleData )
{
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
CommandSetUpgrade::~CommandSetUpgrade( void )
{
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void CommandSetUpgrade::upgradeImplementation( )
{
	Object *obj = getObject();

	const AsciiString& upgradeAlt = getCommandSetUpgradeModuleData()->m_triggerAlt;
	const UpgradeTemplate *upgradeTemplate = TheUpgradeCenter->findUpgrade( upgradeAlt );

	if (upgradeTemplate)
	{
		UpgradeMaskType upgradeMask = upgradeTemplate->getUpgradeMask();

		// See if upgrade is found in the player completed upgrades
		Player *player = obj->getControllingPlayer();
		if (player)
		{
			UpgradeMaskType playerMask = player->getCompletedUpgradeMask();
			if (playerMask.testForAny(upgradeMask))
			{
				obj->setCommandSetStringOverride( getCommandSetUpgradeModuleData()->m_newCommandSetAlt , getCommandSetUpgradeModuleData()->m_newCommandSet2Alt, getCommandSetUpgradeModuleData()->m_newCommandSet3Alt, getCommandSetUpgradeModuleData()->m_newCommandSet4Alt);
				TheControlBar->markUIDirty();// Refresh the UI in case we are selected
				return;
			}
		}

		// See if upgrade is found in the object completed upgrades
		UpgradeMaskType objMask = obj->getObjectCompletedUpgradeMask();
		if (objMask.testForAny(upgradeMask))
		{
			obj->setCommandSetStringOverride( getCommandSetUpgradeModuleData()->m_newCommandSetAlt,  getCommandSetUpgradeModuleData()->m_newCommandSet2Alt, getCommandSetUpgradeModuleData()->m_newCommandSet3Alt, getCommandSetUpgradeModuleData()->m_newCommandSet4Alt);
			TheControlBar->markUIDirty();// Refresh the UI in case we are selected
			return;
		}
	}

	obj->setCommandSetStringOverride( getCommandSetUpgradeModuleData()->m_newCommandSet, getCommandSetUpgradeModuleData()->m_newCommandSet2, getCommandSetUpgradeModuleData()->m_newCommandSet3, getCommandSetUpgradeModuleData()->m_newCommandSet4);
	TheControlBar->markUIDirty();// Refresh the UI in case we are selected
}
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void CommandSetUpgrade::downgradeImplementation()
{
	Object* obj = getObject();

	const AsciiString& upgradeAlt = getCommandSetUpgradeModuleData()->m_triggerAlt;
	const UpgradeTemplate* upgradeTemplate = TheUpgradeCenter->findUpgrade(upgradeAlt);

	if (upgradeTemplate)
	{
		UpgradeMaskType upgradeMask = upgradeTemplate->getUpgradeMask();

		// See if upgrade is found in the player completed upgrades
		Player* player = obj->getControllingPlayer();
		if (player)
		{
			UpgradeMaskType playerMask = player->getCompletedUpgradeMask();
			if (playerMask.testForAny(upgradeMask))
			{
				obj->setCommandSetStringOverride("", "", "", "");
				TheControlBar->markUIDirty();// Refresh the UI in case we are selected
				return;
			}
		}

		// See if upgrade is found in the object completed upgrades
		UpgradeMaskType objMask = obj->getObjectCompletedUpgradeMask();
		if (objMask.testForAny(upgradeMask))
		{
			obj->setCommandSetStringOverride("", "", "", "");
			TheControlBar->markUIDirty();// Refresh the UI in case we are selected
			return;
		}
	}

	obj->setCommandSetStringOverride("", "", "", "");
	TheControlBar->markUIDirty();// Refresh the UI in case we are selected
}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
void CommandSetUpgrade::crc( Xfer *xfer )
{

	// extend base class
	UpgradeModule::crc( xfer );

}

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void CommandSetUpgrade::xfer( Xfer *xfer )
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
void CommandSetUpgrade::loadPostProcess( void )
{

	// extend base class
	UpgradeModule::loadPostProcess();

}
