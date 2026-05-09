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

// FILE: InventoryBehavior.cpp ///////////////////////////////////////////////////////////////////////
// Created: TheSuperHackers, January 2025
// Desc:    Inventory behavior module for managing limited resources
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/INI.h"
#include "Common/Xfer.h"
#include "GameLogic/Module/InventoryBehavior.h"
#include "GameLogic/Object.h"
#include "GameClient/GameText.h"
#include "GameClient/Anim2D.h"

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

InventoryBehaviorModuleData::InventoryBehaviorModuleData()
{
	m_inventoryItems.clear();
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Parse Item sub-region
//-------------------------------------------------------------------------------------------------
static void parseItem(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	InventoryBehaviorModuleData* data = static_cast<InventoryBehaviorModuleData*>(instance);
	
	// Get the item key from the INI token (e.g., "Item = Ammo" -> "Ammo")
	AsciiString itemKey = ini->getNextToken();
	
	if (itemKey.isEmpty())
		return;

	// Parse directly into InventoryItemConfig
	InventoryItemConfig config;
	
	static const FieldParse itemFieldParse[] =
            {
		{ "DisplayName", INI::parseAndTranslateLabel, NULL, offsetof(InventoryItemConfig, displayName) },
		{ "MaxStorageCount", INI::parseReal, NULL, offsetof(InventoryItemConfig, maxStorageCount) },
		{ "InitialAvailableAmount", INI::parseReal, NULL, offsetof(InventoryItemConfig, initialAvailableAmount) },
		{ "CostPerItem", INI::parseInt, NULL, offsetof(InventoryItemConfig, costPerItem) },
		{ "EmptyIconAnimation", INI::parseAsciiString, NULL, offsetof(InventoryItemConfig, emptyIconAnimationName) },
		{ "EmptyThreshold", INI::parseReal, NULL, offsetof(InventoryItemConfig, emptyThreshold) },
                { 0, 0, 0, 0 }
            };
	
	ini->initFromINI(&config, itemFieldParse);
	
            // Store the parsed data in the module data
                data->m_inventoryItems[itemKey] = config;
}

//-------------------------------------------------------------------------------------------------
void InventoryBehaviorModuleData::buildFieldParse(MultiIniFieldParse& p)
{
	ModuleData::buildFieldParse(p);
	static const FieldParse inventoryFieldParse[] =
	{
		{ "Item", parseItem, NULL, 0 },
		{ 0, 0, 0, 0 }
	};

	p.add(inventoryFieldParse);
}

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Helper methods for InventoryBehaviorModuleData
//-------------------------------------------------------------------------------------------------
Real InventoryBehaviorModuleData::getMaxStorageCount(const AsciiString& itemKey) const
{
	std::map<AsciiString, InventoryItemConfig>::const_iterator it = m_inventoryItems.find(itemKey);
	return (it != m_inventoryItems.end()) ? it->second.maxStorageCount : 0;
}

Real InventoryBehaviorModuleData::getInitialAvailableAmount(const AsciiString& itemKey) const
{
	std::map<AsciiString, InventoryItemConfig>::const_iterator it = m_inventoryItems.find(itemKey);
	return (it != m_inventoryItems.end()) ? it->second.initialAvailableAmount : 0;
}

const UnicodeString& InventoryBehaviorModuleData::getDisplayName(const AsciiString& itemKey) const
{
    static UnicodeString emptyString;
    std::map<AsciiString, InventoryItemConfig>::const_iterator it = m_inventoryItems.find(itemKey);
    return (it != m_inventoryItems.end()) ? it->second.displayName : emptyString;
}

Int InventoryBehaviorModuleData::getCostPerItem(const AsciiString& itemKey) const
{
    std::map<AsciiString, InventoryItemConfig>::const_iterator it = m_inventoryItems.find(itemKey);
    return (it != m_inventoryItems.end()) ? it->second.costPerItem : 0;
}

Anim2DTemplate* InventoryBehaviorModuleData::getEmptyIconAnimation(const AsciiString& itemKey) const
{
    std::map<AsciiString, InventoryItemConfig>::const_iterator it = m_inventoryItems.find(itemKey);
    if (it == m_inventoryItems.end())
        return NULL;
    
    const InventoryItemConfig& config = it->second;
    
    // Lazy resolution: if not resolved yet, resolve it now
    if (config.emptyIconAnimation == NULL && !config.emptyIconAnimationName.isEmpty() && TheAnim2DCollection)
    {
        // Need non-const access to resolve, so cast away const (safe here as we're just caching)
        InventoryItemConfig& nonConstConfig = const_cast<InventoryItemConfig&>(config);
        nonConstConfig.emptyIconAnimation = TheAnim2DCollection->findTemplate(config.emptyIconAnimationName);
        if (nonConstConfig.emptyIconAnimation)
        {
            nonConstConfig.emptyIconAnimationName = AsciiString(); // Clear name after successful resolution
        }
    }
    
    return config.emptyIconAnimation;
}

//-------------------------------------------------------------------------------------------------
UnicodeString InventoryBehaviorModuleData::getModuleDescription() const
{
	if (m_inventoryItems.empty())
		return L"";

	UnicodeString result;
	bool first = true;
	bool hasAnyItems = false;
	
	for (std::map<AsciiString, InventoryItemConfig>::const_iterator it = m_inventoryItems.begin(); 
		 it != m_inventoryItems.end(); ++it)
	{
		const InventoryItemConfig& config = it->second;
		
		// Only include items with initialAvailableAmount > 0
		if (config.initialAvailableAmount > 0.0f)
		{
			if (!first)
				result += L" and ";
			
			// Use += to append instead of format which overwrites
			UnicodeString itemText;
			itemText.format(L"%.1f %s", config.initialAvailableAmount, config.displayName.str());
			result += itemText;
			first = false;
			hasAnyItems = true;
		}
	}
	
	// Return empty string if no items have initial amounts > 0
	if (!hasAnyItems)
		return L"";
	
	// Add "Comes with" prefix
	UnicodeString finalResult;
	finalResult.format(L"Comes with %s", result.str());
	return finalResult;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

InventoryBehavior::InventoryBehavior(Thing* thing, const ModuleData* moduleData) : BehaviorModule(thing, moduleData)
{
	// Initialize inventory items from module data (each instance gets its own copy)
	const InventoryBehaviorModuleData* data = static_cast<const InventoryBehaviorModuleData*>(getModuleData());
	if (data)
	{
		m_inventoryItems = data->m_inventoryItems;  // Copy the inventory configuration
	}
	else
	{
		m_inventoryItems.clear();
	}

	m_currentAmounts.clear();
}

//-------------------------------------------------------------------------------------------------
InventoryBehavior::~InventoryBehavior()
{
}

//-------------------------------------------------------------------------------------------------
void InventoryBehavior::onObjectCreated()
{
	// Initialize runtime state from instance inventory items
	// Each object instance has its own inventory configuration
	for (std::map<AsciiString, InventoryItemConfig>::const_iterator it = m_inventoryItems.begin();
		 it != m_inventoryItems.end(); ++it)
	{
		const AsciiString& itemKey = it->first;
		Real initialAmount = it->second.initialAvailableAmount;
		if (!itemKey.isEmpty() && initialAmount > 0.0f)
		{
			// Use setter method to ensure proper validation
			setItemCount(itemKey, initialAmount);
		}
	}
}

//-------------------------------------------------------------------------------------------------
void InventoryBehavior::update(Object* object)
{
	// Inventory behavior doesn't need per-frame updates
	// Consumption is handled by command buttons and weapons
}

//-------------------------------------------------------------------------------------------------
void InventoryBehavior::destroy(Object* object)
{
	m_currentAmounts.clear();
}

//-------------------------------------------------------------------------------------------------
Bool InventoryBehavior::consumeItem(const AsciiString& itemKey, Real amount)
{
	if (itemKey.isEmpty() || amount <= 0.0f)
		return false;

	std::map<AsciiString, Real>::iterator it = m_currentAmounts.find(itemKey);
	if (it == m_currentAmounts.end())
		return false;

	if (it->second < amount)
		return false;

	it->second -= amount;
	if (it->second <= 0.0f)
	{
		m_currentAmounts.erase(it);
	}
	return true;
}

Bool InventoryBehavior::hasItem(const AsciiString& itemKey, Real amount) const
{
	if (itemKey.isEmpty() || amount <= 0.0f)
		return false;

	std::map<AsciiString, Real>::const_iterator it = m_currentAmounts.find(itemKey);
	if (it == m_currentAmounts.end())
		return false;

	return it->second >= amount;
}

Real InventoryBehavior::getItemCount(const AsciiString& itemKey) const
{
	if (itemKey.isEmpty())
		return 0.0f;

	std::map<AsciiString, Real>::const_iterator it = m_currentAmounts.find(itemKey);
	if (it == m_currentAmounts.end())
		return 0.0f;

	return it->second;
}

Bool InventoryBehavior::addItem(const AsciiString& itemKey, Real amount)
{
	if (itemKey.isEmpty() || amount <= 0.0f)
		return false;

	// Get current amount and add to it
	Real currentAmount = getItemCount(itemKey);
	Real newAmount = currentAmount + amount;
	
	// Use setter method to ensure proper validation against max storage
	return setItemCount(itemKey, newAmount);
}

Bool InventoryBehavior::setItemCount(const AsciiString& itemKey, Real count)
{
	if (itemKey.isEmpty() || count < 0.0f)
		return false;

	// Get max storage from instance data (not module data) to respect upgrades
	Real maxStorage = getMaxStorageCount(itemKey);

	if (count == 0.0f)
	{
		m_currentAmounts.erase(itemKey);
		return true;
	}

	m_currentAmounts[itemKey] = count;
	
	// Cap at max storage
	if (maxStorage > 0.0f && m_currentAmounts[itemKey] > maxStorage)
		m_currentAmounts[itemKey] = maxStorage;
	
	return true;
}

Bool InventoryBehavior::isEmpty() const
{
	return m_currentAmounts.empty();
}

Real InventoryBehavior::getTotalItems() const
{
	Real total = 0.0f;
	for (std::map<AsciiString, Real>::const_iterator it = m_currentAmounts.begin(); 
		 it != m_currentAmounts.end(); ++it)
	{
		total += it->second;
	}
	return total;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 CRC method for save/load compatibility
//-------------------------------------------------------------------------------------------------
void InventoryBehavior::crc( Xfer *xfer )
{
	// extend base class
	BehaviorModule::crc( xfer );
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Xfer method for save/load compatibility
//-------------------------------------------------------------------------------------------------
void InventoryBehavior::xfer( Xfer *xfer )
{
	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	if (version >= 1)
	{
		// Serialize current amounts map
		Int inventorySize = static_cast<Int>(m_currentAmounts.size());
		xfer->xferInt( &inventorySize );

		if (xfer->getXferMode() == XFER_LOAD)
		{
			m_currentAmounts.clear();
			for (Int i = 0; i < inventorySize; ++i)
			{
				AsciiString itemKey;
				Real itemCount;
				xfer->xferAsciiString( &itemKey );
				xfer->xferReal( &itemCount );
				m_currentAmounts[itemKey] = itemCount;
			}
		}
		else
		{
			for (std::map<AsciiString, Real>::const_iterator it = m_currentAmounts.begin(); 
				 it != m_currentAmounts.end(); ++it)
			{
				AsciiString itemKey = it->first;
				Real itemCount = it->second;
				xfer->xferAsciiString( &itemKey );
				xfer->xferReal( &itemCount );
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Load post-process method
//-------------------------------------------------------------------------------------------------
void InventoryBehavior::loadPostProcess( void )
{
	// extend base class
	BehaviorModule::loadPostProcess();

	// Loop over m_inventoryItems and resolve Anim2DTemplate from names
	InventoryBehaviorModuleData* moduleData = const_cast<InventoryBehaviorModuleData*>(getInventoryModuleData());
	if (!moduleData)
		return;

	// Resolution happens lazily when emptyIconAnimation is first accessed
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Interface method for external access
//-------------------------------------------------------------------------------------------------
InventoryBehavior* InventoryBehavior::getInventoryBehavior(BehaviorModule* module)
{
	// Simple type check - if it's an InventoryBehavior, return it
	InventoryBehavior* inventoryBehavior = dynamic_cast<InventoryBehavior*>(module);
	return inventoryBehavior;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Getter for module data
//-------------------------------------------------------------------------------------------------
const InventoryBehaviorModuleData* InventoryBehavior::getInventoryModuleData() const
{
	return static_cast<const InventoryBehaviorModuleData*>(getModuleData());
}

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Inventory item configuration access methods
//-------------------------------------------------------------------------------------------------
Real InventoryBehavior::getMaxStorageCount(const AsciiString& itemKey) const
{
	std::map<AsciiString, InventoryItemConfig>::const_iterator it = m_inventoryItems.find(itemKey);
	if (it != m_inventoryItems.end())
	{
		// Total = base (or overridden) + additional (sum of all upgrades)
		return it->second.maxStorageCount + it->second.additionalMaxStorageCount;
	}
	return 0;
}

Real InventoryBehavior::getInitialAvailableAmount(const AsciiString& itemKey) const
{
	std::map<AsciiString, InventoryItemConfig>::const_iterator it = m_inventoryItems.find(itemKey);
	return (it != m_inventoryItems.end()) ? it->second.initialAvailableAmount : 0;
}

const UnicodeString& InventoryBehavior::getDisplayName(const AsciiString& itemKey) const
{
    static UnicodeString emptyString;
    std::map<AsciiString, InventoryItemConfig>::const_iterator it = m_inventoryItems.find(itemKey);
    return (it != m_inventoryItems.end()) ? it->second.displayName : emptyString;
}

Int InventoryBehavior::getCostPerItem(const AsciiString& itemKey) const
{
    std::map<AsciiString, InventoryItemConfig>::const_iterator it = m_inventoryItems.find(itemKey);
    return (it != m_inventoryItems.end()) ? it->second.costPerItem : 0;
}

Anim2DTemplate* InventoryBehavior::getEmptyIconAnimation(const AsciiString& itemKey) const
{
    std::map<AsciiString, InventoryItemConfig>::const_iterator it = m_inventoryItems.find(itemKey);
    if (it == m_inventoryItems.end())
        return NULL;

    const InventoryItemConfig& config = it->second;

    // Lazy resolution: if not resolved yet, resolve it now
    if (config.emptyIconAnimation == NULL && !config.emptyIconAnimationName.isEmpty() && TheAnim2DCollection)
    {
        // Need non-const access to resolve, so cast away const (safe here as we're just caching)
        InventoryItemConfig& nonConstConfig = const_cast<InventoryItemConfig&>(config);
        nonConstConfig.emptyIconAnimation = TheAnim2DCollection->findTemplate(config.emptyIconAnimationName);
        if (nonConstConfig.emptyIconAnimation)
        {
            nonConstConfig.emptyIconAnimationName = AsciiString(); // Clear name after successful resolution
        }
    }

    return config.emptyIconAnimation;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Get icon to draw for empty inventory items
//-------------------------------------------------------------------------------------------------
Anim2D* InventoryBehavior::getEmptyItemIcon()
{
	// Iterate through items and find the first empty one with an icon configured
	for (std::map<AsciiString, InventoryItemConfig>::const_iterator it = m_inventoryItems.begin();
		 it != m_inventoryItems.end(); ++it)
	{
		const AsciiString& itemKey = it->first;
		const InventoryItemConfig& config = it->second;

		// Check if item is empty (amount <= threshold or not in m_currentAmounts)
		std::map<AsciiString, Real>::const_iterator amountIt = m_currentAmounts.find(itemKey);
		if (amountIt != m_currentAmounts.end() && amountIt->second > config.emptyThreshold)
		{
			// Item is not empty, continue to next
			continue;
		}

		// Get icon template (lazy loading handled in getEmptyIconAnimation)
		Anim2DTemplate* iconTemplate = getEmptyIconAnimation(itemKey);
		
		// Check if we have icon template configured
		if (!iconTemplate)
		{
			// No icon configured, continue to next
			continue;
		}

		// Found empty item with icon - create Anim2D from template
		if (TheAnim2DCollection)
		{
			Anim2D* icon = newInstance(Anim2D)(iconTemplate, TheAnim2DCollection);
			return icon;
		}
	}

	// No more empty items with icons found
	return NULL;
}
