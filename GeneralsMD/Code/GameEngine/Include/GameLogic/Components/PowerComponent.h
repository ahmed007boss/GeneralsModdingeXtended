// PowerComponent.h ///////////////////////////////////////////////////////////////
// Power-specific component with electrical power generation properties
// Author: TheSuperHackers
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef POWER_COMPONENT_H
#define POWER_COMPONENT_H

#include "Common/GameType.h"
#include "Common/AsciiString.h"
#include "Common/INI.h"
#include "GameLogic/Damage.h"
#include "ElectronicsComponent.h"

// Forward declarations
class MultiIniFieldParse;

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Power component for electrical power generation
//-------------------------------------------------------------------------------------------------
class PowerComponent : public ElectronicsComponent
{
public:
	PowerComponent() {}

	static void parsePowerComponent(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void buildFieldParse(MultiIniFieldParse& p);

	// TheSuperHackers @feature Ahmed Salah 15/01/2025 Default power supply component name constant
	static const char* DEFAULT_POWER_SUPPLY_COMPONENT_NAME;

	// TheSuperHackers @feature author 15/01/2025 Virtual clone method for polymorphic copying
	virtual Component* clone() const;

	// Save/Load/CRC hooks
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess( void );
};

#endif // POWER_COMPONENT_H
