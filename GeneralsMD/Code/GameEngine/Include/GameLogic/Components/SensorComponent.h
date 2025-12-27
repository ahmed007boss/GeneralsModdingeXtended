// SensorComponent.h ///////////////////////////////////////////////////////////////
// Sensor component combining vision and electronics
// Author: TheSuperHackers
/////////////////////////////////////////////////////////////////////////////////////

#ifndef SENSOR_COMPONENT_H
#define SENSOR_COMPONENT_H

#include "GameLogic/Damage.h"
#include "Component.h"
#include "VisionComponentInterface.h"
#include "ElectronicsComponentInterface.h"

class MultiIniFieldParse;

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature Ahmed Salah 30/10/2025 Sensor component (Vision + Electronics)
//-------------------------------------------------------------------------------------------------
class SensorComponent : public Component, public IVisionComponent, public IElectronicsComponent
{
public:
	SensorComponent()
		: m_shroudClearingRange(0.0f)
		, m_shroudClearingRangePartial(-1.0f)
		, m_shroudClearingRangeDisabled(0.0f)
		, m_visionRange(0.0f)
		, m_visionRangePartial(-1.0f)
		, m_visionRangeDisabled(0.0f)
		, m_jammingDamageCap(0.0f)
		, m_jammingDamageHealRate(0)
		, m_jammingDamageHealAmount(0.0f)
		, m_currentJammingDamage(0.0f)
		, m_jammingHealCountdown(0)
		, m_canBeJammedByDirectJammers(FALSE)
		, m_canBeJammedByAreaJammers(FALSE)
	{}

	// IVisionComponent
	virtual Real getShroudClearingRange() const;
	virtual Real getVisionRange() const;

	// IElectronicsComponent
	virtual Real getCurrentJammingDamage() const { return m_currentJammingDamage; }
	virtual Real getJammingDamageCap() const { return m_jammingDamageCap; }
	virtual UnsignedInt getJammingDamageHealRate() const { return m_jammingDamageHealRate; }
	virtual Real getJammingDamageHealAmount() const { return m_jammingDamageHealAmount; }
	virtual Bool setCurrentJammingDamage(Real damage);
	virtual Bool addJammingDamage(Real damage);
	virtual Bool hasAnyJammingDamage() const { return m_currentJammingDamage > 0.0f; }
	virtual void healJammingDamage(Real healing);
	virtual void updateJammingDamageHealing();
	virtual Bool isJammableByDirect() const { return m_canBeJammedByDirectJammers; }
	virtual void setJammableByDirect(Bool v) { m_canBeJammedByDirectJammers = v; }
	virtual Bool isJammableByArea() const { return m_canBeJammedByAreaJammers; }
	virtual void setJammableByArea(Bool v) { m_canBeJammedByAreaJammers = v; }

	// TheSuperHackers @feature Ahmed Salah 15/01/2025 Override getStatus to include jamming damage
	virtual ComponentStatus getStatus() const;

	static void parseSensorComponent(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void buildFieldParse(MultiIniFieldParse& p);

	// TheSuperHackers @feature Ahmed Salah 15/01/2025 Default radar component name constant
	static const char* DEFAULT_RADAR_COMPONENT_NAME;

	// TheSuperHackers @feature author 15/01/2025 Virtual clone method for polymorphic copying
	virtual Component* clone() const;

	// Save/Load/CRC hooks
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess( void );

private:
	// Vision data
	Real m_shroudClearingRange;
	Real m_shroudClearingRangePartial;
	Real m_shroudClearingRangeDisabled;
	Real m_visionRange;
	Real m_visionRangePartial;
	Real m_visionRangeDisabled;

	// Electronics data
	Real m_jammingDamageCap;
	UnsignedInt m_jammingDamageHealRate;
	Real m_jammingDamageHealAmount;
	Real m_currentJammingDamage;
	UnsignedInt m_jammingHealCountdown;
	Bool m_canBeJammedByDirectJammers;
	Bool m_canBeJammedByAreaJammers;
};

#endif // SENSOR_COMPONENT_H
