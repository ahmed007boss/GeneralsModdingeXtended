// VisionComponent.h ///////////////////////////////////////////////////////////////
// Vision-specific component with sight and detection properties
// Author: TheSuperHackers
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef VISION_COMPONENT_H
#define VISION_COMPONENT_H

#include "Common/GameType.h"
#include "Common/AsciiString.h"
#include "Common/INI.h"
#include "GameLogic/Damage.h"
#include "Component.h"

// Forward declarations
class MultiIniFieldParse;

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Vision component for detection and sight systems
//-------------------------------------------------------------------------------------------------
class VisionComponent : public Component
{
public:
	VisionComponent() : m_shroudClearingRange(0.0f), m_shroudClearingRangePartial(-1.0f), m_shroudClearingRangeDisabled(0.0f), m_visionRange(0.0f), m_visionRangePartial(-1.0f), m_visionRangeDisabled(0.0f) {}

	// Shroud clearing ranges per health state
	Real m_shroudClearingRange;             ///< Range when fully functional
	Real m_shroudClearingRangePartial;      ///< Range when partially functional
	Real m_shroudClearingRangeDisabled;     ///< Range when downed or user-disabled

	// Vision ranges per health state
	Real m_visionRange;                     ///< Range when fully functional
	Real m_visionRangePartial;              ///< Range when partially functional
	Real m_visionRangeDisabled;             ///< Range when downed or user-disabled

	// Returns appropriate shroud clearing range based on current component status
	Real getShroudClearingRange() const;
	// Returns appropriate vision range based on current component status
	Real getVisionRange() const;

	static void parseVisionComponent(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void buildFieldParse(MultiIniFieldParse& p);

	// TheSuperHackers @feature Ahmed Salah 15/01/2025 Default vision component name constant
	static const char* DEFAULT_VISION_COMPONENT_NAME;

	// TheSuperHackers @feature author 15/01/2025 Virtual clone method for polymorphic copying
	virtual Component* clone() const;

	// Save/Load/CRC hooks
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess( void );
};

#endif // VISION_COMPONENT_H
