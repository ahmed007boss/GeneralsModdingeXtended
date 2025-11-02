// EngineComponent.h ///////////////////////////////////////////////////////////////
// Engine-specific component with engine-related properties
// Author: TheSuperHackers
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef ENGINE_COMPONENT_H
#define ENGINE_COMPONENT_H

#include "Common/GameType.h"
#include "Common/AsciiString.h"
#include "Common/INI.h"
#include "GameLogic/Damage.h"
#include "GameLogic/Module/BodyModule.h"
#include "Component.h"

// Forward declarations
class MultiIniFieldParse; 

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Engine component for vehicle propulsion systems
//-------------------------------------------------------------------------------------------------
class EngineComponent : public Component
{
public:
	// Engine performance values when damaged (optional - if not set, use parameter)
	Real m_maxSpeedDamaged;					///< Max speed when engine is damaged (optional)
	ValueType m_maxSpeedDamagedValueType;	///< How maxSpeedDamaged is calculated (absolute or percentage)
	Bool m_hasMaxSpeedDamaged;				///< Whether maxSpeedDamaged is set in INI
	Real m_maxTurnRateDamaged;				///< Max turn rate when engine is damaged (optional)
	ValueType m_maxTurnRateDamagedValueType; ///< How maxTurnRateDamaged is calculated (absolute or percentage)
	Bool m_hasMaxTurnRateDamaged;			///< Whether maxTurnRateDamaged is set in INI
	Real m_maxAccelerationDamaged;			///< Max acceleration when engine is damaged (optional)
	ValueType m_maxAccelerationDamagedValueType; ///< How maxAccelerationDamaged is calculated (absolute or percentage)
	Bool m_hasMaxAccelerationDamaged;		///< Whether maxAccelerationDamaged is set in INI
	Real m_maxLiftDamaged;					///< Max lift when engine is damaged (optional)
	ValueType m_maxLiftDamagedValueType;	///< How maxLiftDamaged is calculated (absolute or percentage)
	Bool m_hasMaxLiftDamaged;				///< Whether maxLiftDamaged is set in INI

	// Engine performance values when destroyed
	Real m_maxSpeedDestroyed;				///< Max speed when engine is destroyed
	ValueType m_maxSpeedDestroyedValueType;	///< How maxSpeedDestroyed is calculated (absolute or percentage)
	Real m_maxTurnRateDestroyed;			///< Max turn rate when engine is destroyed
	ValueType m_maxTurnRateDestroyedValueType; ///< How maxTurnRateDestroyed is calculated (absolute or percentage)
	Real m_maxAccelerationDestroyed;		///< Max acceleration when engine is destroyed
	ValueType m_maxAccelerationDestroyedValueType; ///< How maxAccelerationDestroyed is calculated (absolute or percentage)
	Real m_maxLiftDestroyed;				///< Max lift when engine is destroyed
	ValueType m_maxLiftDestroyedValueType;	///< How maxLiftDestroyed is calculated (absolute or percentage)

	EngineComponent() : m_maxSpeedDamaged(0.0f), m_maxSpeedDamagedValueType(VALUE_TYPE_ABSOLUTE), m_hasMaxSpeedDamaged(FALSE),
						m_maxTurnRateDamaged(0.0f), m_maxTurnRateDamagedValueType(VALUE_TYPE_ABSOLUTE), m_hasMaxTurnRateDamaged(FALSE),
						m_maxAccelerationDamaged(0.0f), m_maxAccelerationDamagedValueType(VALUE_TYPE_ABSOLUTE), m_hasMaxAccelerationDamaged(FALSE),
						m_maxLiftDamaged(0.0f), m_maxLiftDamagedValueType(VALUE_TYPE_ABSOLUTE), m_hasMaxLiftDamaged(FALSE),
						m_maxSpeedDestroyed(0.0f), m_maxSpeedDestroyedValueType(VALUE_TYPE_ABSOLUTE),
						m_maxTurnRateDestroyed(0.0f), m_maxTurnRateDestroyedValueType(VALUE_TYPE_ABSOLUTE),
						m_maxAccelerationDestroyed(0.0f), m_maxAccelerationDestroyedValueType(VALUE_TYPE_ABSOLUTE),
						m_maxLiftDestroyed(0.0f), m_maxLiftDestroyedValueType(VALUE_TYPE_ABSOLUTE)
	{
		// TheSuperHackers @feature Ahmed Salah 15/01/2025 Set default damage status types for engine components
		m_damagedDamageType = BODY_COMPONENT_ENGINE_DAMAGED;
		m_destroyedDamageType = BODY_COMPONENT_ENGINE_DESTROYED;
	}

	// TheSuperHackers @feature Ahmed Salah 30/10/2025 Adjust locomotor max speed based on engine status
	void calculateComponentMaxSpeed(Real& speed, Real damagedSpeed) const;
	// TheSuperHackers @feature Ahmed Salah 30/10/2025 Adjust locomotor max turn rate based on engine status
	void calculateComponentMaxTurnRate(Real& turnRate, Real damagedTurnRate) const;
	// TheSuperHackers @feature Ahmed Salah 30/10/2025 Adjust locomotor max acceleration based on engine status
	void calculateComponentMaxAcceleration(Real& acceleration, Real damagedAcceleration) const;
	// TheSuperHackers @feature Ahmed Salah 30/10/2025 Adjust locomotor max lift based on engine status
	void calculateComponentMaxLift(Real& lift, Real damagedLift) const;

	static void parseEngineComponent(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void buildFieldParse(MultiIniFieldParse& p);

	// TheSuperHackers @feature Ahmed Salah 15/01/2025 Default main engine component name constant
	static const char* DEFAULT_MAIN_ENGINE_COMPONENT_NAME;

	// TheSuperHackers @feature author 15/01/2025 Virtual clone method for polymorphic copying
	virtual Component* clone() const;

	// Save/Load/CRC hooks
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess( void );
};

#endif // ENGINE_COMPONENT_H
