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

// FILE: InventoryUpgrade.h ///////////////////////////////////////////////////////////////////
// TheSuperHackers @feature author 15/01/2025 Inventory upgrade module
// Desc:	 Inventory upgrades - adds items or increases storage capacity
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __INVENTORY_UPGRADE_H_
#define __INVENTORY_UPGRADE_H_

#include "Common/AsciiString.h"
#include "Common/UnicodeString.h"
#include "GameLogic/Module/UpgradeModule.h"
#include <map>
#include <vector>

// FORWARD DECLARATIONS ///////////////////////////////////////////////////////////////////////////
class InventoryBehavior;

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Inventory item upgrade configuration
//-------------------------------------------------------------------------------------------------
struct InventoryItemUpgrade
{
    AsciiString itemName;                    ///< Name of the inventory item to upgrade
    Bool isNewItem;                          ///< True if this is a new item, false if modifying existing
    Int setMaxStorageCount;                  ///< Set max storage count (-1 = no change)
    Int addMaxStorageCount;                  ///< Add to max storage count (0 = no change)
    Int setInitialAvailableAmount;           ///< Set initial available amount (-1 = no change)
    Int addInitialAvailableAmount;           ///< Add to initial available amount (0 = no change)
    UnicodeString displayName;              ///< Display name for the inventory item (empty = no change)
    Int setCostPerItem;                     ///< Set cost per item (-1 = no change)
    
    InventoryItemUpgrade() : isNewItem(false), setMaxStorageCount(-1), addMaxStorageCount(0), 
                             setInitialAvailableAmount(-1), addInitialAvailableAmount(0), setCostPerItem(-1) {}
};

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Inventory upgrade module data
//-------------------------------------------------------------------------------------------------
class InventoryUpgradeModuleData : public UpgradeModuleData
{
public:
    std::vector<InventoryItemUpgrade> m_inventoryItemUpgrades;  ///< List of inventory upgrades to apply

    InventoryUpgradeModuleData();

    static void buildFieldParse(MultiIniFieldParse& p);

private:
    // INI parsing helper methods
    static void parseInventoryItemUpgrade(INI* ini, void* instance, void* store, const void* userData);
};

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Inventory upgrade module
//-------------------------------------------------------------------------------------------------
class InventoryUpgrade : public UpgradeModule
{
    MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(InventoryUpgrade, "InventoryUpgrade")
    MAKE_STANDARD_MODULE_MACRO_WITH_MODULE_DATA(InventoryUpgrade, InventoryUpgradeModuleData)

public:
    InventoryUpgrade(Thing* thing, const ModuleData* moduleData);
    // virtual destructor prototype provided by memory pool declaration

    // Module methods
    static Int getInterfaceMask() { return MODULEINTERFACE_UPGRADE; }

    // BehaviorModule overrides
    virtual void onDelete();
    virtual void onCapture(Player* oldOwner, Player* newOwner);

protected:
    // UpgradeMux implementation
    virtual void upgradeImplementation();
		virtual void downgradeImplementation();
    virtual Bool isSubObjectsUpgrade() { return FALSE; }

private:
    // Apply upgrades to the object's inventory behavior
    void applyInventoryUpgrades(InventoryBehavior* inventoryBehavior);
    void removeInventoryUpgrades(InventoryBehavior* inventoryBehavior);

    // Store original values for reverting upgrades
    std::map<AsciiString, Int> m_originalStorageCapacities;
    std::map<AsciiString, Int> m_originalInitialAmounts;
};

#endif // __INVENTORY_UPGRADE_H_
