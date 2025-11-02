// RemoteControlComponent.h ///////////////////////////////////////////////////////////////
// Remote control-specific component inheriting communication behavior
// Author: TheSuperHackers
/////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __REMOTE_CONTROL_COMPONENT_H_
#define __REMOTE_CONTROL_COMPONENT_H_

#include "GameLogic/Damage.h"
#include "CommunicationComponent.h"
#include "Common/INI.h"

class MultiIniFieldParse;

class RemoteControlComponent : public CommunicationComponent
{
public:
    // Static parse for INI
    static void parseRemoteControlComponent(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);

    // Build field parse: include CommunicationComponent fields, then RC-specific (none for now)
    static void buildFieldParse(MultiIniFieldParse& p);

	// TheSuperHackers @feature Ahmed Salah 15/01/2025 Default remote controller component name constant
	static const char* DEFAULT_REMOTE_CONTROLLER_COMPONENT_NAME;

    // TheSuperHackers @feature author 15/01/2025 Virtual clone method for polymorphic copying
    virtual Component* clone() const;

    // Save/Load/CRC hooks
    virtual void crc( Xfer *xfer );
    virtual void xfer( Xfer *xfer );
    virtual void loadPostProcess( void );
};

#endif // __REMOTE_CONTROL_COMPONENT_H_


