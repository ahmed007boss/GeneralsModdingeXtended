// ElectronicsComponent.h ///////////////////////////////////////////////////////////////
// Electronics-specific component with electronic systems properties
// Author: TheSuperHackers
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef ELECTRONICS_COMPONENT_H
#define ELECTRONICS_COMPONENT_H

#include "Common/GameType.h"
#include "Common/AsciiString.h"
#include "Common/INI.h"
#include "GameLogic/Damage.h"
#include "Component.h"
#include "ElectronicsComponentInterface.h"

// Forward declarations
class MultiIniFieldParse;

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Electronics component for electronic systems
//-------------------------------------------------------------------------------------------------
class ElectronicsComponent : public Component, public IElectronicsComponent
{
public:
	Real m_jammingDamageCap;
	UnsignedInt m_jammingDamageHealRate;
	Real m_jammingDamageHealAmount;
	Real m_currentJammingDamage;
	UnsignedInt m_jammingHealCountdown;
	Bool m_canBeJammedByDirectJammers;
	Bool m_canBeJammedByAreaJammers;
	
	ElectronicsComponent()
		: m_jammingDamageCap(0.0f)
		, m_jammingDamageHealRate(0)
		, m_jammingDamageHealAmount(0.0f)
		, m_currentJammingDamage(0.0f)
		, m_jammingHealCountdown(0)
		, m_canBeJammedByDirectJammers(TRUE)
		, m_canBeJammedByAreaJammers(TRUE)

	{}

	// Override Jamming logic
	virtual Real getCurrentJammingDamage() const { return m_currentJammingDamage; }
	virtual Real getJammingDamageCap() const { return m_jammingDamageCap; }
	virtual UnsignedInt getJammingDamageHealRate() const { return m_jammingDamageHealRate; }
	virtual Real getJammingDamageHealAmount() const { return m_jammingDamageHealAmount; }
	virtual Bool setCurrentJammingDamage(Real damage)
	{
		if (damage < 0.0f) damage = 0.0f;
		if (damage > m_jammingDamageCap) damage = m_jammingDamageCap;
		m_currentJammingDamage = damage;
		return TRUE;
	}
	virtual Bool addJammingDamage(Real damage)
	{
		if (damage <= 0.0f) return FALSE;
		return setCurrentJammingDamage(m_currentJammingDamage + damage);
	}
	virtual Bool hasAnyJammingDamage() const { return m_currentJammingDamage > 0.0f; }
	virtual void healJammingDamage(Real healing)
	{
		if (healing <= 0.0f) return;
		Real newDamage = m_currentJammingDamage - healing;
		if (newDamage < 0.0f) newDamage = 0.0f;
		m_currentJammingDamage = newDamage;
	}
	virtual void updateJammingDamageHealing()
	{
		if (m_jammingDamageHealRate <= 0 || m_jammingDamageHealAmount <= 0.0f)
			return;
		if (m_jammingHealCountdown > 0)
		{
			m_jammingHealCountdown--;
			return;
		}
		m_jammingHealCountdown = m_jammingDamageHealRate;
		healJammingDamage(m_jammingDamageHealAmount);
	}

	// IElectronicsComponent flags
	virtual Bool isJammableByDirect() const { return m_canBeJammedByDirectJammers; }
	virtual void setJammableByDirect(Bool v) { m_canBeJammedByDirectJammers = v; }
	virtual Bool isJammableByArea() const { return m_canBeJammedByAreaJammers; }
	virtual void setJammableByArea(Bool v) { m_canBeJammedByAreaJammers = v; }

	// TheSuperHackers @feature Ahmed Salah 15/01/2025 Override getStatus to include jamming damage
	virtual ComponentStatus getStatus() const;

	static void parseElectronicsComponent(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void buildFieldParse(MultiIniFieldParse& p);

	// TheSuperHackers @feature author 15/01/2025 Virtual clone method for polymorphic copying
	virtual Component* clone() const;

	// Save/Load/CRC hooks
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess( void );
};

#endif // ELECTRONICS_COMPONENT_H
