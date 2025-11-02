// JetEngineComponent.h ///////////////////////////////////////////////////////////////
// Jet-engine specific component inheriting engine behavior
// Author: TheSuperHackers
/////////////////////////////////////////////////////////////////////////////////////

#ifndef JET_ENGINE_COMPONENT_H
#define JET_ENGINE_COMPONENT_H

#include "EngineComponent.h"

class MultiIniFieldParse;

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature Ahmed Salah 30/10/2025 Jet engine component based on EngineComponent
//-------------------------------------------------------------------------------------------------
class JetEngineComponent : public EngineComponent
{
public:
	JetEngineComponent() {}

	static void parseJetEngineComponent(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void buildFieldParse(MultiIniFieldParse& p);

	// TheSuperHackers @feature Ahmed Salah 15/01/2025 Default jet engine component name constant
	static const char* DEFAULT_JET_ENGINE_COMPONENT_NAME;

	// TheSuperHackers @feature author 15/01/2025 Virtual clone method for polymorphic copying
	virtual Component* clone() const;

	// Save/Load/CRC hooks
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess( void );
};

#endif // JET_ENGINE_COMPONENT_H
