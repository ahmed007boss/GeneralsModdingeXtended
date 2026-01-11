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

// FILE: InventoryBehavior.h ////////////////////////////////////////////////////////////////////////
// Created: TheSuperHackers, January 2025
// Desc:    Inventory behavior module for managing limited resources
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "GameLogic/Module/BehaviorModule.h"
#include "Common/AsciiString.h"
#include "Common/UnicodeString.h"
#include <map>

// FORWARD DECLARATIONS ///////////////////////////////////////////////////////////////////////////
class Object;
class INI;
class Anim2DTemplate;
class Anim2D;

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Inventory item structure
//-------------------------------------------------------------------------------------------------
struct InventoryItemConfig
{
    UnicodeString displayName;        ///< Display name for the inventory item
    Real maxStorageCount;              ///< Base maximum storage capacity (from module data, can be overridden by upgrades)
    Real additionalMaxStorageCount;    ///< Additional storage capacity added/subtracted by upgrades (total of all additions)
    Real initialAvailableAmount;       ///< Initial available amount
    Int costPerItem;                  ///< TheSuperHackers @feature author 15/01/2025 Cost per item for replenishment
    AsciiString emptyIconAnimationName;   ///< TheSuperHackers @feature author 15/01/2025 Animation icon template name (resolved in loadPostProcess)
    Anim2DTemplate* emptyIconAnimation;   ///< TheSuperHackers @feature author 15/01/2025 Animation icon template to display when item is empty (NULL = no icon)
    Real emptyThreshold;               ///< TheSuperHackers @feature author 15/01/2025 Threshold value for considering this item empty (default 0.0)
    
    InventoryItemConfig() : maxStorageCount(0.0f), additionalMaxStorageCount(0.0f), initialAvailableAmount(0.0f), costPerItem(0), emptyIconAnimation(NULL), emptyThreshold(0.0f) {}
};

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Inventory module data for managing limited resources
//-------------------------------------------------------------------------------------------------
class InventoryBehaviorModuleData : public ModuleData
{
public:
	std::map<AsciiString, InventoryItemConfig> m_inventoryItems;     ///< List of inventory item configurations (template data)

	InventoryBehaviorModuleData();

    // Helper methods for accessing template data
    Real getMaxStorageCount(const AsciiString& itemKey) const;
    Real getInitialAvailableAmount(const AsciiString& itemKey) const;
    const UnicodeString& getDisplayName(const AsciiString& itemKey) const;
    Int getCostPerItem(const AsciiString& itemKey) const;
    Anim2DTemplate* getEmptyIconAnimation(const AsciiString& itemKey) const;

	virtual UnicodeString getModuleDescription() const;
	virtual Int getModuleOrder() const { return 1000; } // High priority for display

	static void buildFieldParse(MultiIniFieldParse& p);
};

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Inventory behavior for managing limited resources
//-------------------------------------------------------------------------------------------------
class InventoryBehavior : public BehaviorModule
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE( InventoryBehavior, "InventoryBehavior" )
	MAKE_STANDARD_MODULE_MACRO_WITH_MODULE_DATA( InventoryBehavior, InventoryBehaviorModuleData )

public:

	InventoryBehavior( Thing *thing, const ModuleData* moduleData );
	// virtual destructor prototype provided by memory pool declaration

	// module methods
	static Int getInterfaceMask() { return 0; }

	// BehaviorModule
	virtual void update(Object* object);
	virtual void onObjectCreated();
	virtual void destroy(Object* object);

	// Inventory management
	Bool consumeItem(const AsciiString& itemKey, Real amount = 1.0f);
	Bool hasItem(const AsciiString& itemKey, Real amount = 1.0f) const;
	Real getItemCount(const AsciiString& itemKey) const;
	Bool addItem(const AsciiString& itemKey, Real amount);
	Bool setItemCount(const AsciiString& itemKey, Real count);

	// Inventory queries
	Bool isEmpty() const;
	Real getTotalItems() const;

	// Inventory item configuration access
	Real getMaxStorageCount(const AsciiString& itemKey) const;
	Real getInitialAvailableAmount(const AsciiString& itemKey) const;
	const UnicodeString& getDisplayName(const AsciiString& itemKey) const;
	Int getCostPerItem(const AsciiString& itemKey) const;
	Anim2DTemplate* getEmptyIconAnimation(const AsciiString& itemKey) const;

  // Interface method for external access
  static InventoryBehavior* getInventoryBehavior(BehaviorModule* module);

  // Getter for module data
  const InventoryBehaviorModuleData* getInventoryModuleData() const;

	// TheSuperHackers @feature author 15/01/2025 Get icon to draw for empty inventory items
	// Iterates through items internally and returns the first empty item's icon found (NULL when no more)
	Anim2D* getEmptyItemIcon();

	// Allow upgrade modules to modify inventory item configurations
	std::map<AsciiString, InventoryItemConfig>& getInventoryItems() { return m_inventoryItems; }


private:
	std::map<AsciiString, InventoryItemConfig> m_inventoryItems;  ///< Inventory item configurations (per-instance)
	std::map<AsciiString, Real> m_currentAmounts;  ///< Current amounts for each item (runtime state)
};
