// CommunicationComponent.h ///////////////////////////////////////////////////////////////
// Communication-specific component with radio and communication properties
// Author: TheSuperHackers
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef COMMUNICATION_COMPONENT_H
#define COMMUNICATION_COMPONENT_H

#include "Common/GameType.h"
#include "Common/AsciiString.h"
#include "Common/INI.h"
#include "GameLogic/Damage.h"
#include "ElectronicsComponent.h"

// Forward declarations
class MultiIniFieldParse;

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Communication component for radio and comm systems
//-------------------------------------------------------------------------------------------------
class CommunicationComponent : public ElectronicsComponent
{
public:
	CommunicationComponent() {}

	static void parseCommunicationComponent(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void buildFieldParse(MultiIniFieldParse& p);

	// TheSuperHackers @feature Ahmed Salah 15/01/2025 Default communication radio component name constant
	static const char* DEFAULT_COMMUNICATION_RADIO_COMPONENT_NAME;

	// TheSuperHackers @feature author 15/01/2025 Virtual clone method for polymorphic copying
	virtual Component* clone() const;

	// Save/Load/CRC hooks
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess( void );
};

#endif // COMMUNICATION_COMPONENT_H
