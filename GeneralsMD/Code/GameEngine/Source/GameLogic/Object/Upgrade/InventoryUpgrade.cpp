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

// FILE: InventoryUpgrade.cpp /////////////////////////////////////////////////////////////////
// TheSuperHackers @feature author 15/01/2025 Inventory upgrade module
// Desc:	 Inventory upgrades - adds items or increases storage capacity
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/Xfer.h"
#include "GameLogic/Object.h"
#include "GameLogic/Module/InventoryBehavior.h"
#include "GameLogic/Module/InventoryUpgrade.h"

//-------------------------------------------------------------------------------------------------
// InventoryUpgradeModuleData
//-------------------------------------------------------------------------------------------------

InventoryUpgradeModuleData::InventoryUpgradeModuleData()
{
    m_inventoryItemUpgrades.clear();
}

//-------------------------------------------------------------------------------------------------
void InventoryUpgradeModuleData::buildFieldParse(MultiIniFieldParse& p)
{
    UpgradeModuleData::buildFieldParse(p);

    static const FieldParse dataFieldParse[] =
    {
        { "Item", InventoryUpgradeModuleData::parseInventoryItemUpgrade, 0, 0 },
        { 0, 0, 0, 0 }
    };
    p.add(dataFieldParse);
}

//-------------------------------------------------------------------------------------------------
void InventoryUpgradeModuleData::parseInventoryItemUpgrade(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
    InventoryUpgradeModuleData* data = static_cast<InventoryUpgradeModuleData*>(instance);
    
    // Get the item name from the INI token (e.g., "Item = Ammo" -> "Ammo")
    AsciiString itemName = ini->getNextToken();
    
    if (itemName.isEmpty())
        return;
    
    // Create a temporary structure to hold the parsed values
    struct TempItemUpgrade {
        Int m_setMaxStorageCount;
        Int m_addMaxStorageCount;
        Int m_setInitialAvailableAmount;
        Int m_addInitialAvailableAmount;
        UnicodeString m_displayName;
        Int m_setCostPerItem;
    } tempData;
    
    // Initialize defaults
    tempData.m_setMaxStorageCount = -1;
    tempData.m_addMaxStorageCount = 0;
    tempData.m_setInitialAvailableAmount = -1;
    tempData.m_addInitialAvailableAmount = 0;
    tempData.m_setCostPerItem = -1;
    
    static const FieldParse tempItemFieldParse[] =
    {
        { "MaxStorageCount", INI::parseInt, NULL, offsetof(TempItemUpgrade, m_setMaxStorageCount) },
        { "AddMaxStorageCount", INI::parseInt, NULL, offsetof(TempItemUpgrade, m_addMaxStorageCount) },
        { "InitialAvailableAmount", INI::parseInt, NULL, offsetof(TempItemUpgrade, m_setInitialAvailableAmount) },
        { "AddInitialAvailableAmount", INI::parseInt, NULL, offsetof(TempItemUpgrade, m_addInitialAvailableAmount) },
        { "DisplayName", INI::parseAndTranslateLabel, NULL, offsetof(TempItemUpgrade, m_displayName) },
        { "CostPerItem", INI::parseInt, NULL, offsetof(TempItemUpgrade, m_setCostPerItem) },
        { 0, 0, 0, 0 }
    };
    
    ini->initFromINI(&tempData, tempItemFieldParse);
    
    // Create the upgrade structure
    InventoryItemUpgrade upgrade;
    upgrade.itemName = itemName;
    upgrade.setMaxStorageCount = tempData.m_setMaxStorageCount;
    upgrade.addMaxStorageCount = tempData.m_addMaxStorageCount;
    upgrade.setInitialAvailableAmount = tempData.m_setInitialAvailableAmount;
    upgrade.addInitialAvailableAmount = tempData.m_addInitialAvailableAmount;
    upgrade.displayName = tempData.m_displayName;
    upgrade.setCostPerItem = tempData.m_setCostPerItem;
    
    // Determine if this is a new item (has DisplayName or CostPerItem set)
    upgrade.isNewItem = (!upgrade.displayName.isEmpty() || upgrade.setCostPerItem >= 0);
    
    data->m_inventoryItemUpgrades.push_back(upgrade);
}

//-------------------------------------------------------------------------------------------------
// InventoryUpgrade
//-------------------------------------------------------------------------------------------------

InventoryUpgrade::InventoryUpgrade(Thing* thing, const ModuleData* moduleData) :
    UpgradeModule(thing, moduleData)
{
}

//-------------------------------------------------------------------------------------------------
InventoryUpgrade::~InventoryUpgrade( void )
{

}

//-------------------------------------------------------------------------------------------------
void InventoryUpgrade::onDelete()
{
    // If we haven't been upgraded there is nothing to clean up
    if (isAlreadyUpgraded() == FALSE)
        return;

    // If we're currently disabled, we shouldn't do anything, because we've already done it.
    if (getObject()->isDisabled() || getObject()->isElectronicallyDisabled())
        return;

    // Remove the inventory upgrades
    InventoryBehavior* inventoryBehavior = getObject()->getInventoryBehavior();
    if (inventoryBehavior)
    {
        removeInventoryUpgrades(inventoryBehavior);
    }

    // This upgrade module is now "not upgraded"
    setUpgradeExecuted(FALSE);
}

//-------------------------------------------------------------------------------------------------
void InventoryUpgrade::onCapture(Player* oldOwner, Player* newOwner)
{
    // Do nothing if we haven't upgraded yet
    if (isAlreadyUpgraded() == FALSE)
        return;

    // If we're currently disabled, we shouldn't do anything, because we've already done it.
    if (getObject()->isDisabled() || getObject()->isElectronicallyDisabled())
        return;

    // Inventory upgrades are tied to the object, not the player, so they persist through capture
    // No action needed for inventory upgrades on capture
}

//-------------------------------------------------------------------------------------------------
void InventoryUpgrade::upgradeImplementation()
{
    // Find the inventory behavior module of this object
    InventoryBehavior* inventoryBehavior = getObject()->getInventoryBehavior();
    if (inventoryBehavior)
    {
        applyInventoryUpgrades(inventoryBehavior);
    }
}
//-------------------------------------------------------------------------------------------------
void InventoryUpgrade::downgradeImplementation()
{
  // Find the inventory behavior module of this object
  InventoryBehavior* inventoryBehavior = getObject()->getInventoryBehavior();
  if (inventoryBehavior)
  {
    removeInventoryUpgrades(inventoryBehavior);
  }
}

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature Ahmed Salah 07/01/2026 Remove inventory upgrades - reverse applyInventoryUpgrades
//-------------------------------------------------------------------------------------------------
void InventoryUpgrade::removeInventoryUpgrades(InventoryBehavior* inventoryBehavior)
{
    const InventoryUpgradeModuleData* data = getInventoryUpgradeModuleData();
    const InventoryBehaviorModuleData* inventoryData = inventoryBehavior->getInventoryModuleData();

    if (!inventoryData)
        return;

    // Remove each inventory item upgrade
    for (std::vector<InventoryItemUpgrade>::const_iterator it = data->m_inventoryItemUpgrades.begin();
         it != data->m_inventoryItemUpgrades.end(); ++it)
    {
        const InventoryItemUpgrade& upgrade = *it;

        if (upgrade.itemName.isEmpty())
            continue;

        const AsciiString& itemName = upgrade.itemName;

        // Find the item in the inventory data
        std::map<AsciiString, InventoryItemConfig>& inventoryItems =
            const_cast<std::map<AsciiString, InventoryItemConfig>&>(inventoryData->m_inventoryItems);

        std::map<AsciiString, InventoryItemConfig>::iterator itemIt = inventoryItems.find(itemName);

        if (itemIt != inventoryItems.end())
        {
            if (upgrade.isNewItem)
            {
                // Item was created by this upgrade, remove it entirely
                inventoryBehavior->setItemCount(itemName, 0.0f);
                inventoryItems.erase(itemIt);
            }
            else
            {
                // Item existed before, restore original values
                InventoryItemConfig& itemConfig = itemIt->second;

                // Restore original max storage count
                std::map<AsciiString, Int>::iterator storageIt = m_originalStorageCapacities.find(itemName);
                if (storageIt != m_originalStorageCapacities.end())
                {
                    itemConfig.maxStorageCount = storageIt->second;
                }

                // Restore original initial available amount
                std::map<AsciiString, Int>::iterator amountIt = m_originalInitialAmounts.find(itemName);
                if (amountIt != m_originalInitialAmounts.end())
                {
                    itemConfig.initialAvailableAmount = amountIt->second;
                }

                // Restore display name to default (item name)
                itemConfig.displayName.format(L"%s", itemName.str());

                // Restore cost per item to default (0)
                itemConfig.costPerItem = 0;

                // Remove items that were added to current inventory
                if (upgrade.addInitialAvailableAmount > 0)
                {
                    Real currentAmount = inventoryBehavior->getItemCount(itemName);
                    Real amountToRemove = upgrade.addInitialAvailableAmount;
                    if (currentAmount >= amountToRemove)
                    {
                        // Consume the items that were added
                        inventoryBehavior->consumeItem(itemName, amountToRemove);
                    }
                    else
                    {
                        // Remove all items if we somehow have fewer than expected
                        inventoryBehavior->setItemCount(itemName, 0.0f);
                    }
                }
            }
        }
    }

    // Clear stored original values
    m_originalStorageCapacities.clear();
    m_originalInitialAmounts.clear();
}

//-------------------------------------------------------------------------------------------------
void InventoryUpgrade::applyInventoryUpgrades(InventoryBehavior* inventoryBehavior)
{
    const InventoryUpgradeModuleData* data = getInventoryUpgradeModuleData();
    const InventoryBehaviorModuleData* inventoryData = inventoryBehavior->getInventoryModuleData();
    
    if (!inventoryData)
        return;

    // Apply each inventory item upgrade
    for (std::vector<InventoryItemUpgrade>::const_iterator it = data->m_inventoryItemUpgrades.begin();
         it != data->m_inventoryItemUpgrades.end(); ++it)
    {
        const InventoryItemUpgrade& upgrade = *it;
        
        if (upgrade.itemName.isEmpty())
            continue;

        const AsciiString& itemName = upgrade.itemName;

        // Store original values for potential reverting
        m_originalStorageCapacities[itemName] = inventoryData->getMaxStorageCount(itemName);
        m_originalInitialAmounts[itemName] = inventoryData->getInitialAvailableAmount(itemName);

        // Find the item in the inventory data
        std::map<AsciiString, InventoryItemConfig>& inventoryItems = 
            const_cast<std::map<AsciiString, InventoryItemConfig>&>(inventoryData->m_inventoryItems);
        
        std::map<AsciiString, InventoryItemConfig>::iterator itemIt = inventoryItems.find(itemName);
        
        if (itemIt != inventoryItems.end())
        {
            // Item exists, modify it
            InventoryItemConfig& itemConfig = itemIt->second;
            
            // Handle max storage count changes
            if (upgrade.setMaxStorageCount >= 0)
            {
                itemConfig.maxStorageCount = upgrade.setMaxStorageCount;
            }
            else if (upgrade.addMaxStorageCount > 0)
            {
                itemConfig.maxStorageCount += upgrade.addMaxStorageCount;
            }
            
            // Handle initial available amount changes
            if (upgrade.setInitialAvailableAmount >= 0)
            {
                itemConfig.initialAvailableAmount = upgrade.setInitialAvailableAmount;
            }
            else if (upgrade.addInitialAvailableAmount > 0)
            {
                itemConfig.initialAvailableAmount += upgrade.addInitialAvailableAmount;
            }
            
            // Handle display name changes
            if (!upgrade.displayName.isEmpty())
            {
                itemConfig.displayName = upgrade.displayName;
            }
            
            // Handle cost per item changes
            if (upgrade.setCostPerItem >= 0)
            {
                itemConfig.costPerItem = upgrade.setCostPerItem;
            }
            
            // Add items to current inventory if specified
            if (upgrade.addInitialAvailableAmount > 0)
            {
                inventoryBehavior->addItem(itemName, upgrade.addInitialAvailableAmount);
            }
        }
        else
        {
            // Item doesn't exist, create it
            InventoryItemConfig newItem;
            
            // Set max storage count
            if (upgrade.setMaxStorageCount >= 0)
            {
                newItem.maxStorageCount = upgrade.setMaxStorageCount;
            }
            else
            {
                newItem.maxStorageCount = upgrade.addMaxStorageCount;
            }
            
            // Set initial available amount
            if (upgrade.setInitialAvailableAmount >= 0)
            {
                newItem.initialAvailableAmount = upgrade.setInitialAvailableAmount;
            }
            else
            {
                newItem.initialAvailableAmount = upgrade.addInitialAvailableAmount;
            }
            
            // Set display name
            if (!upgrade.displayName.isEmpty())
            {
                newItem.displayName = upgrade.displayName;
            }
            else
            {
                newItem.displayName.format(L"%s", itemName.str());
            }
            
            // Set cost per item
            if (upgrade.setCostPerItem >= 0)
            {
                newItem.costPerItem = upgrade.setCostPerItem;
            }
            else
            {
                newItem.costPerItem = 0;
            }
            
            inventoryItems[itemName] = newItem;
            
            // Add initial amount to current inventory
            if (upgrade.addInitialAvailableAmount > 0)
            {
                inventoryBehavior->addItem(itemName, upgrade.addInitialAvailableAmount);
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------
void InventoryUpgrade::crc(Xfer* xfer)
{
    // Extend base class
    UpgradeModule::crc(xfer);
}

//-------------------------------------------------------------------------------------------------
void InventoryUpgrade::xfer(Xfer* xfer)
{
    // Version
    XferVersion currentVersion = 1;
    XferVersion version = currentVersion;
    xfer->xferVersion(&version, currentVersion);

    // Extend base class
    UpgradeModule::xfer(xfer);

    // Note: Original values are stored temporarily during upgrade process
    // They don't need to be saved/loaded as they're only used during upgrade execution
}

//-------------------------------------------------------------------------------------------------
void InventoryUpgrade::loadPostProcess()
{
    // Extend base class
    UpgradeModule::loadPostProcess();
}
