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

// FILE: AutoSupplyItemBehavior.cpp ////////////////////////////////////////////
// Created: TheSuperHackers, January 2025
// Desc:    Auto supply item behavior for automatically supplying items to nearby units
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/INI.h"
#include "Common/Xfer.h"
#include "GameLogic/Module/AutoSupplyItemBehavior.h"
#include "GameLogic/Module/InventoryBehavior.h"
#include "Common/ObjectPrerequisite.h"
#include "GameLogic/PartitionManager.h"
// #include "GameLogic/Player.h" // Not needed for now
// #include "GameLogic/PlayerList.h" // Not needed for now
#include "GameClient/GameText.h"
// #include "GameLogic/ThingTemplate.h" // Not needed for now
// #include "GameLogic/Coord.h" // Not needed for now
#include "GameLogic/GameLogic.h"

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

AutoSupplyItemBehaviorModuleData::AutoSupplyItemBehaviorModuleData()
{
	m_supplyItemKey = "";
	m_supplyAmount = 1.0f;
	m_supplyRadius = 100.0f;
	m_supplyDelay = 1000; // 1 second in milliseconds
	m_supplyAllUnits = false; // Default to best match only
	m_targetPrerequisite = new ObjectPrerequisite();
	m_targetPrerequisite->init();
}

//-------------------------------------------------------------------------------------------------
void AutoSupplyItemBehaviorModuleData::buildFieldParse(MultiIniFieldParse& p)
{
	UpdateModuleData::buildFieldParse(p);
	static const FieldParse autoSupplyFieldParse[] =
	{
		{ "SupplyItemKey", INI::parseAsciiString, NULL, offsetof(AutoSupplyItemBehaviorModuleData, m_supplyItemKey) },
		{ "SupplyAmount", INI::parseReal, NULL, offsetof(AutoSupplyItemBehaviorModuleData, m_supplyAmount) },
		{ "SupplyRadius", INI::parseReal, NULL, offsetof(AutoSupplyItemBehaviorModuleData, m_supplyRadius) },
		{ "SupplyDelay", INI::parseDurationUnsignedInt, NULL, offsetof(AutoSupplyItemBehaviorModuleData, m_supplyDelay) },
		{ "SupplyAllUnits", INI::parseBool, NULL, offsetof(AutoSupplyItemBehaviorModuleData, m_supplyAllUnits) },
		{ "TargetPrerequisite", ObjectPrerequisite::parseObjectPrerequisites, NULL, offsetof(AutoSupplyItemBehaviorModuleData, m_targetPrerequisite) },
		{ 0, 0, 0, 0 }
	};

	p.add(autoSupplyFieldParse);
}

//-------------------------------------------------------------------------------------------------
UnicodeString AutoSupplyItemBehaviorModuleData::getModuleDescription() const
{
	if (m_supplyItemKey.isEmpty())
		return L"";

	UnicodeString result;
	result.format(L"Auto-supplies %s (%.1f every %.1fs within %.1f range)", 
		m_supplyItemKey.str(), m_supplyAmount, m_supplyDelay / 1000.0f, m_supplyRadius);
	
	return result;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

AutoSupplyItemBehavior::AutoSupplyItemBehavior(Thing* thing, const ModuleData* moduleData) : UpdateModule(thing, moduleData)
{
	m_lastSupplyFrame = 0;
	m_lastSuppliedUnit = NULL;
}

//-------------------------------------------------------------------------------------------------
AutoSupplyItemBehavior::~AutoSupplyItemBehavior()
{
}

//-------------------------------------------------------------------------------------------------
UpdateSleepTime AutoSupplyItemBehavior::update()
{
	Object* object = getObject();
	if (!object)
		return UPDATE_SLEEP_FOREVER;

	const AutoSupplyItemBehaviorModuleData* data = static_cast<const AutoSupplyItemBehaviorModuleData*>(getModuleData());
	if (!data || data->m_supplyItemKey.isEmpty())
		return UPDATE_SLEEP_FOREVER;

	// TheSuperHackers @feature Ahmed Salah 15/01/2025 Check if replenishment is restricted by destroyed components
	if (object->isInventoryReplenishmentRestricted(data->m_supplyItemKey))
	{
		return UPDATE_SLEEP(data->m_supplyDelay); // Don't supply if restricted
	}

	// Check if it's time to supply
	UnsignedInt currentFrame = TheGameLogic->getFrame();
	if (currentFrame - m_lastSupplyFrame < data->m_supplyDelay)
	{
		return UPDATE_SLEEP(1); // Check again next frame
	}


	// Find nearby units to supply using partition manager
	Object* bestTarget = NULL;

	// Setup scan filters
	PartitionFilterRelationship relationship(object, PartitionFilterRelationship::ALLOW_ALLIES);
	PartitionFilterSameMapStatus filterMapStatus(object);
	PartitionFilterAlive filterAlive;
	PartitionFilter *filters[] = { &relationship, &filterAlive, &filterMapStatus, NULL };

	// Scan objects in our region
	ObjectIterator *iter = ThePartitionManager->iterateObjectsInRange(object->getPosition(), data->m_supplyRadius, FROM_CENTER_2D, filters);
	MemoryPoolObjectHolder hold(iter);
	
	if (data->m_supplyAllUnits)
	{
		// Supply all units in range
		Bool anySupplied = false;
		for (Object* target = iter->first(); target; target = iter->next())
		{
			// Skip self
			if (target == object)
				continue;

			// Check if target can be supplied
			if (!canSupplyUnit(target))
				continue;

			// Supply this target
			if (supplyUnit(target))
			{
				anySupplied = true;
			}
		}
		
		if (anySupplied)
		{
			m_lastSupplyFrame = currentFrame;
		}
	}
	else
	{
		// Supply only the best match (unit with lowest amount of the item)
		Real lowestAmount = -1.0f;
		for (Object* target = iter->first(); target; target = iter->next())
		{
			// Skip self
			if (target == object)
				continue;

			// Check if target can be supplied
			if (!canSupplyUnit(target))
				continue;

			// Get target's current amount of the item
			InventoryBehavior* targetInventory = target->getInventoryBehavior();
			if (!targetInventory)
				continue;

			Real currentAmount = targetInventory->getItemCount(data->m_supplyItemKey);
			
			// Check if this is the best target (lowest amount)
			if (lowestAmount < 0.0f || currentAmount < lowestAmount)
			{
				bestTarget = target;
				lowestAmount = currentAmount;
			}
		}

		// Supply the best target if found
		if (bestTarget)
		{
			if (supplyUnit(bestTarget))
			{
				m_lastSupplyFrame = currentFrame;
				m_lastSuppliedUnit = bestTarget;
			}
		}
	}

	return UPDATE_SLEEP(data->m_supplyDelay);
}

//-------------------------------------------------------------------------------------------------
Bool AutoSupplyItemBehavior::canSupplyUnit(Object* targetUnit) const
{
	if (!targetUnit)
		return false;

	const AutoSupplyItemBehaviorModuleData* data = static_cast<const AutoSupplyItemBehaviorModuleData*>(getModuleData());
	if (!data)
		return false;

	const Object* object = getObject();
	if (!object)
		return false;

	// TheSuperHackers @feature Ahmed Salah 15/01/2025 Check if replenishment is restricted by destroyed components
	if (object->isInventoryReplenishmentRestricted(data->m_supplyItemKey))
		return false;

	// Check if target has inventory behavior
	InventoryBehavior* targetInventory = NULL;
	for (BehaviorModule** i = targetUnit->getBehaviorModules(); *i; ++i)
	{
		BehaviorModule* behavior = *i;
		if (behavior)
		{
			targetInventory = InventoryBehavior::getInventoryBehavior(behavior);
			if (targetInventory)
				break;
		}
	}

	if (!targetInventory)
		return false;

	// Check if target needs the item (has space for it) - use instance data to respect upgrades
	Real currentAmount = targetInventory->getItemCount(data->m_supplyItemKey);
	Real maxStorage = targetInventory->getMaxStorageCount(data->m_supplyItemKey);
	
	if (maxStorage > 0.0f && currentAmount >= maxStorage)
		return false; // Target is at max capacity

	// Check target prerequisites
	if (!data->m_targetPrerequisite->isSatisfied(targetUnit))
		return false;

	return true;
}

//-------------------------------------------------------------------------------------------------
Bool AutoSupplyItemBehavior::supplyUnit(Object* targetUnit)
{
	if (!targetUnit)
		return false;

	Object* object = getObject();
	if (!object)
		return false;

	const AutoSupplyItemBehaviorModuleData* data = static_cast<const AutoSupplyItemBehaviorModuleData*>(getModuleData());
	if (!data)
		return false;

	// TheSuperHackers @feature Ahmed Salah 15/01/2025 Check if replenishment is restricted by destroyed components
	if (object->isInventoryReplenishmentRestricted(data->m_supplyItemKey))
		return false;

	// Get target inventory
	InventoryBehavior* targetInventory = targetUnit->getInventoryBehavior();

	if (!targetInventory)
		return false;

	// Add to target inventory
	if (!targetInventory->addItem(data->m_supplyItemKey, data->m_supplyAmount))
		return false;

	// Supply operation completed successfully
	// TODO: Add visual/audio feedback if needed

	return true;
}

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 CRC method for save/load compatibility
//-------------------------------------------------------------------------------------------------
void AutoSupplyItemBehavior::crc( Xfer *xfer )
{
	// extend base class
	UpdateModule::crc( xfer );
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Xfer method for save/load compatibility
//-------------------------------------------------------------------------------------------------
void AutoSupplyItemBehavior::xfer( Xfer *xfer )
{
	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	if (version >= 1)
	{
		xfer->xferUnsignedInt( &m_lastSupplyFrame );
		// Note: m_lastSuppliedUnit is not serialized as it's just a cache
	}
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Load post-process method
//-------------------------------------------------------------------------------------------------
void AutoSupplyItemBehavior::loadPostProcess( void )
{
	// extend base class
	UpdateModule::loadPostProcess();
}
