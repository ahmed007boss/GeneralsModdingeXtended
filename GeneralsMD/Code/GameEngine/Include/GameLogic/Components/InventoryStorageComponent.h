// InventoryStorageComponent.h ///////////////////////////////////////////////////////////////
// Inventory storage-specific component with storage and cargo properties
// Author: TheSuperHackers
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef INVENTORY_STORAGE_COMPONENT_H
#define INVENTORY_STORAGE_COMPONENT_H

#include "Common/GameType.h"
#include "Common/AsciiString.h"
#include "Common/INI.h"
#include "GameLogic/Damage.h"
#include "Component.h"

// Forward declarations
class MultiIniFieldParse;

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Inventory storage component for cargo and storage systems
//-------------------------------------------------------------------------------------------------
class InventoryStorageComponent : public Component
{
protected:
	AsciiString m_inventoryItem;	///< TheSuperHackers @feature Ahmed Salah 15/01/2025 Inventory item key (empty = affects all items)

public:
	InventoryStorageComponent() : m_inventoryItem() {}

	static void parseInventoryStorageComponent(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void buildFieldParse(MultiIniFieldParse& p);

	// TheSuperHackers @feature Ahmed Salah 15/01/2025 Accessors for inventory item
	const AsciiString& getInventoryItem() const { return m_inventoryItem; }
	void setInventoryItem(const AsciiString& item) { m_inventoryItem = item; }
	
	// TheSuperHackers @feature Ahmed Salah 15/01/2025 Check if this component restricts replenishment for a specific item
	Bool restrictsReplenishmentForItem(const AsciiString& itemKey) const;

	// TheSuperHackers @feature author 15/01/2025 Virtual clone method for polymorphic copying
	virtual Component* clone() const;
	
	// TheSuperHackers @feature Ahmed Salah 15/01/2025 Override onComponentDestroyed to clear inventory items
	virtual void onComponentDestroyed();

	// Save/Load/CRC hooks
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess( void );
};

#endif // INVENTORY_STORAGE_COMPONENT_H
