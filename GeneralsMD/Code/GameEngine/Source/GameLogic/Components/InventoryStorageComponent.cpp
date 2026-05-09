// InventoryStorageComponent.cpp ///////////////////////////////////////////////////////////////////
// Inventory storage-specific component with additional storage and cargo properties
// Author: TheSuperHackers
///////////////////////////////////////////////////////////////////////////////////////////////////

#define DEFINE_HIT_SIDE_NAMES

#include "GameLogic/Components/InventoryStorageComponent.h"
#include "Common/INI.h"
#include "GameLogic/Components/Component.h"
#include "GameLogic/Damage.h"
#include "Common/GameType.h"
#include "GameLogic/Module/ActiveBody.h"
#include "GameLogic/Object.h"
#include "GameLogic/Module/InventoryBehavior.h"

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Static parse method for InventoryStorageComponent inheritance support
//-------------------------------------------------------------------------------------------------
void InventoryStorageComponent::parseInventoryStorageComponent(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	// instance is actually ActiveBodyModuleData*
	ActiveBodyModuleData* moduleData = (ActiveBodyModuleData*)instance;
	
	// Get component name from the first token (e.g., "CargoBay", "AmmoStorage", etc.)
	AsciiString componentName = ini->getNextToken();
	if (componentName.isEmpty()) return;
	
	InventoryStorageComponent* component = new InventoryStorageComponent();
	// Set component name using direct assignment
	component->setName(componentName);
	
	MultiIniFieldParse p;
	InventoryStorageComponent::buildFieldParse(p);

	// Parse the component block using the field parse table
	ini->initFromINIMulti(component, p);
	
	// Add the parsed component to the module data
	moduleData->m_componentsData.push_back(component);
}

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Build field parse method for InventoryStorageComponent inheritance support
//-------------------------------------------------------------------------------------------------
void InventoryStorageComponent::buildFieldParse(MultiIniFieldParse& p)
{
	// Add base Component properties
	Component::buildFieldParse(p);

	// Add InventoryStorageComponent-specific properties
	static const FieldParse inventoryStorageComponentFieldParse[] = {
		{ "InventoryItem", INI::parseAsciiString, NULL, offsetof(InventoryStorageComponent, m_inventoryItem) },
		{ 0, 0, 0, 0 }
	};

	p.add(inventoryStorageComponentFieldParse);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Virtual clone method for polymorphic copying
//-------------------------------------------------------------------------------------------------
Component* InventoryStorageComponent::clone() const
{
	// Create a new InventoryStorageComponent
	InventoryStorageComponent* copy = new InventoryStorageComponent();
	
	// Copy base Component members using helper method
	copyBaseComponentMembers(copy);
	
	// Copy InventoryStorageComponent-specific members
	copy->m_inventoryItem = m_inventoryItem;
	
	return copy;
}

//-------------------------------------------------------------------------------------------------
void InventoryStorageComponent::crc( Xfer *xfer )
{
	Component::crc(xfer);
}

//-------------------------------------------------------------------------------------------------
void InventoryStorageComponent::xfer( Xfer *xfer )
{
	Component::xfer(xfer);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature Ahmed Salah 15/01/2025 Check if this component restricts replenishment for a specific item
//-------------------------------------------------------------------------------------------------
Bool InventoryStorageComponent::restrictsReplenishmentForItem(const AsciiString& itemKey) const
{
	// If component is not destroyed, it doesn't restrict anything
	if (!isDestroyed())
		return FALSE;
	
	// If InventoryItem is empty, this component restricts ALL items
	if (m_inventoryItem.isEmpty())
		return TRUE;
	
	// Otherwise, only restrict if the item key matches
	return (m_inventoryItem == itemKey);
}

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature Ahmed Salah 15/01/2025 Override onComponentDestroyed to clear inventory items
//-------------------------------------------------------------------------------------------------
void InventoryStorageComponent::onComponentDestroyed()
{
	// Call base implementation
	Component::onComponentDestroyed();
	
	// Get the owning object
	Object* obj = getObject();
	if (!obj)
		return;
	
	// Get InventoryBehavior from the object
	InventoryBehavior* inventoryBehavior = obj->getInventoryBehavior();
	if (!inventoryBehavior)
		return;
	
	// Clear inventory items based on InventoryItem field
	if (m_inventoryItem.isEmpty())
	{
		// If InventoryItem is empty, clear ALL items - use instance data
		const std::map<AsciiString, InventoryItemConfig>& inventoryItems = inventoryBehavior->getInventoryItems();
		for (std::map<AsciiString, InventoryItemConfig>::const_iterator it = inventoryItems.begin();
			 it != inventoryItems.end(); ++it)
		{
			const AsciiString& itemKey = it->first;
			inventoryBehavior->setItemCount(itemKey, 0.0f);
		}
	}
	else
	{
		// If InventoryItem has a value, clear only that specific item (if it exists)
		inventoryBehavior->setItemCount(m_inventoryItem, 0.0f);
	}
}

//-------------------------------------------------------------------------------------------------
void InventoryStorageComponent::loadPostProcess( void )
{
	Component::loadPostProcess();
}
