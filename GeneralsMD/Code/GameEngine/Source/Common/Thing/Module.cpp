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

// FILE: Module.cpp ///////////////////////////////////////////////////////////////////////////////
// Author: Colin Day, September 2001
// Desc:	 Object and drawable modules and actions.  These are simply just class
//				 instances that we can assign to objects, drawables, and things to contain
//				 data and code for specific events, or just to hold data
///////////////////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file in the GameEngine

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "Common/Module.h"
#include "Common/Thing.h"
#include "Common/INI.h"
#include "Common/ThingTemplate.h"
#include "Common/Upgrade.h"
#include "Common/Xfer.h"
#include "Common/Player.h"
#include "GameLogic/Object.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/CollideModule.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/DamageModule.h"
#include "GameLogic/Module/DieModule.h"
#include "GameLogic/Module/UpdateModule.h"
#include "GameLogic/Module/UpgradeModule.h"


///////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// this method should NEVER be overridden by user code, only via the MAKE_STANDARD_MODULE_xxx macros!
// it should also NEVER be called directly; it's only for use by ModuleFactory!
 ModuleData* Module::friend_newModuleData(INI* ini)
{
	ModuleData* data = MSGNEW("Module::friend_newModuleData") ModuleData;	// no need to memorypool these since we never allocate more than one of each
	if (ini)
		ini->initFromINI(data, 0);	// this is just so that an "end" token is required
	return data;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
Module::~Module()
{

}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
void Module::crc( Xfer *xfer )
{

}

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void Module::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

}

// ------------------------------------------------------------------------------------------------
/** load post process */
// ------------------------------------------------------------------------------------------------
void Module::loadPostProcess( void )
{

}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
ObjectModule::ObjectModule( Thing *thing, const ModuleData* moduleData ) : Module(moduleData)
{
	if (!moduleData)
	{
		DEBUG_CRASH(("module data may not be null"));
		throw INI_INVALID_DATA;
	}

	DEBUG_ASSERTCRASH( thing, ("Thing passed to ObjectModule is NULL!") );
	m_object = AsObject(thing);
	DEBUG_ASSERTCRASH( m_object, ("Thing passed to ObjectModule is not an Object!") );

}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
ObjectModule::~ObjectModule( void )
{

}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
void ObjectModule::crc( Xfer *xfer )
{

	// extend base class
	Module::crc( xfer );

}

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void ObjectModule::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	Module::xfer( xfer );

}

// ------------------------------------------------------------------------------------------------
/** load post process */
// ------------------------------------------------------------------------------------------------
void ObjectModule::loadPostProcess( void )
{

	// extend base class
	Module::loadPostProcess();

}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
DrawableModule::DrawableModule( Thing *thing, const ModuleData* moduleData ) : Module(moduleData)
{
	if (!moduleData)
	{
		DEBUG_CRASH(("module data may not be null"));
		throw INI_INVALID_DATA;
	}

	DEBUG_ASSERTCRASH( thing, ("Thing passed to DrawableModule is NULL!") );
	m_drawable = AsDrawable(thing);
	DEBUG_ASSERTCRASH( m_drawable, ("Thing passed to DrawableModule is not a Drawable!") );

}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
DrawableModule::~DrawableModule( void )
{

}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
void DrawableModule::crc( Xfer *xfer )
{

	// extend base class
	Module::crc( xfer );

}

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void DrawableModule::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	Module::xfer( xfer );

}

// ------------------------------------------------------------------------------------------------
/** load post process */
// ------------------------------------------------------------------------------------------------
void DrawableModule::loadPostProcess( void )
{

	// extend base class
	Module::loadPostProcess();

}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
void UpgradeMuxData::performUpgradeFX(Object* obj) const
{
	if (m_fxListUpgrade)
	{
		FXList::doFXObj(m_fxListUpgrade, obj);
	}
}

//-------------------------------------------------------------------------------------------------
void UpgradeMuxData::muxDataProcessUpgradeRemoval(Object* obj) const
{
	if( !m_removalUpgradeNames.empty() )
	{
		std::vector<AsciiString>::const_iterator it;
		for( it = m_removalUpgradeNames.begin();
					it != m_removalUpgradeNames.end();
					it++)
		{
			const UpgradeTemplate* theTemplate = TheUpgradeCenter->findUpgrade( *it );
			if( !theTemplate )
			{
				DEBUG_CRASH(("An upgrade module references '%s', which is not an Upgrade", it->str()));
				throw INI_INVALID_DATA;
			}

			obj->removeUpgrade(theTemplate);
		}
	}
}

//-------------------------------------------------------------------------------------------------
Bool UpgradeMuxData::isTriggeredBy(const std::string &upgrade) const
{
	std::vector<AsciiString>::const_iterator it;
	for( it = m_triggerUpgradeNames.begin(); it != m_triggerUpgradeNames.end();	++it)
	{
		AsciiString trigger = *it;
		if (stricmp(trigger.str(), upgrade.c_str()) == 0)
		{
			return TRUE;
		}
	}

	return FALSE;
}

//-------------------------------------------------------------------------------------------------
void UpgradeMuxData::getUpgradeActivationMasks(UpgradeMaskType& activation, UpgradeMaskType& conflicting, UpgradeMaskType& requireAnyOf, UpgradeMaskType& requireAllOf) const
{
	// already computed.
	if (!m_activationUpgradeNames.empty() || !m_conflictingUpgradeNames.empty() ||
		!m_requireAllOfUpgradeNames.empty() || !m_requireAnyOfUpgradeNames.empty())
	{
		m_activationMask.clear();
		m_conflictingMask.clear();
		m_requireAllOfMask.clear();
		m_requireAnyOfMask.clear();

		std::vector<AsciiString>::const_iterator it;

		// Activation upgrades
		for (it = m_activationUpgradeNames.begin(); it != m_activationUpgradeNames.end(); ++it)
		{
			const UpgradeTemplate* theTemplate = TheUpgradeCenter->findUpgrade(*it);
			if (!theTemplate)
			{
				DEBUG_CRASH(("An upgrade module references '%s', which is not an Upgrade", it->str()));
				throw INI_INVALID_DATA;
			}
			m_activationMask.set(theTemplate->getUpgradeMask());
		}

		// Conflicting upgrades
		for (it = m_conflictingUpgradeNames.begin(); it != m_conflictingUpgradeNames.end(); ++it)
		{
			const UpgradeTemplate* theTemplate = TheUpgradeCenter->findUpgrade(*it);
			if (!theTemplate)
			{
				DEBUG_CRASH(("An upgrade module references '%s', which is not an Upgrade", it->str()));
				throw INI_INVALID_DATA;
			}
			m_conflictingMask.set(theTemplate->getUpgradeMask());
		}

		// Require ALL upgrades
		for (it = m_requireAllOfUpgradeNames.begin(); it != m_requireAllOfUpgradeNames.end(); ++it)
		{
			const UpgradeTemplate* theTemplate = TheUpgradeCenter->findUpgrade(*it);
			if (!theTemplate)
			{
				DEBUG_CRASH(("An upgrade module references '%s', which is not an Upgrade", it->str()));
				throw INI_INVALID_DATA;
			}
			m_requireAllOfMask.set(theTemplate->getUpgradeMask());
		}

		// Require ANY upgrades
		for (it = m_requireAnyOfUpgradeNames.begin(); it != m_requireAnyOfUpgradeNames.end(); ++it)
		{
			const UpgradeTemplate* theTemplate = TheUpgradeCenter->findUpgrade(*it);
			if (!theTemplate)
			{
				DEBUG_CRASH(("An upgrade module references '%s', which is not an Upgrade", it->str()));
				throw INI_INVALID_DATA;
			}
			m_requireAnyOfMask.set(theTemplate->getUpgradeMask());
		}

		// We set the trigger upgrade names with the activationUpgradeNames entries to be used later.
		m_triggerUpgradeNames = m_activationUpgradeNames;

		// Clear the names now that we've cached the values!
		m_activationUpgradeNames.clear();
		m_conflictingUpgradeNames.clear();
		m_requireAllOfUpgradeNames.clear();
		m_requireAnyOfUpgradeNames.clear();
	}

	 activation = m_activationMask;
	 conflicting = m_conflictingMask;
	 requireAllOf = m_requireAllOfMask;
	 requireAnyOf = m_requireAnyOfMask;
}

//-------------------------------------------------------------------------------------------------
Bool UpgradeMuxData::requiresAllActivationUpgrades() const
{
	return m_requiresAllTriggers;
}

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature Ahmed Salah 03/01/2026 Test if upgrade conditions are met for a given upgrade mask
//-------------------------------------------------------------------------------------------------
Bool UpgradeMuxData::testUpgradeConditions(const UpgradeMaskType& keyMask) const
{
	UpgradeMaskType activation, conflicting, requireAnyOf, requireAllOf;
	getUpgradeActivationMasks(activation, conflicting, requireAnyOf, requireAllOf);
	
	Bool anyCond = TRUE;
	if (requireAnyOf.any())
	{
		anyCond = keyMask.testForAny(requireAnyOf);
	}
	Bool allCond = TRUE;
	if (requireAllOf.any())
	{
		allCond = keyMask.testForAll(requireAllOf);
	}
	
	// Make sure we don't have any conflicting upgrades
	if (!keyMask.any() || !keyMask.testForAny(conflicting))
	{
		// Make sure we have activation conditions
		if (activation.any())
		{
			// Check if activation conditions match
			if (requiresAllActivationUpgrades())
			{
				// Make sure ALL triggers requirements are upgraded
				if (keyMask.testForAll(activation) && allCond && anyCond)
				{
					return TRUE;
				}
			}
			else
			{
				// Check if ANY trigger requirements are met
				if (keyMask.testForAny(activation) && allCond && anyCond)
				{
					return TRUE;
				}
			}
		}
		else
		{
			// This upgrade is relying only on not having conflicts
			return TRUE;
		}
	}
	
	return FALSE;
}

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature Ahmed Salah 03/01/2026 Test if upgrade conditions are met for a given object (overload)
//-------------------------------------------------------------------------------------------------
Bool UpgradeMuxData::testUpgradeConditions(const Object* obj) const
{
	if (!obj)
		return FALSE;
	
	// Get upgrade mask from object (object + player upgrades)
	UpgradeMaskType keyMask = obj->getObjectCompletedUpgradeMask();
	const Player* player = obj->getControllingPlayer();
	if (player)
	{
		UpgradeMaskType playerMask = player->getCompletedUpgradeMask();
		keyMask.set(playerMask);
	}
	
	// Call the existing testUpgradeConditions method with the combined mask
	return testUpgradeConditions(keyMask);
}