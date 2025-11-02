// SensorComponent.cpp ///////////////////////////////////////////////////////////////////
// Sensor component combining vision and electronics
// Author: TheSuperHackers
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "GameLogic/Components/SensorComponent.h"
#include "Common/INI.h"
#include "GameLogic/Module/ActiveBody.h"
#include "GameLogic/Components/VisionComponent.h"
#include "GameLogic/Components/ElectronicsComponent.h"

// TheSuperHackers @feature Ahmed Salah 15/01/2025 Default radar component name constant definition
const char* SensorComponent::DEFAULT_RADAR_COMPONENT_NAME = "Radar";

Real SensorComponent::getShroudClearingRange() const
{
	const ComponentStatus status = getStatus();
	if (status == COMPONENT_STATUS_DOWNED || status == COMPONENT_STATUS_USER_DISABLED)
	{
		return m_shroudClearingRangeDisabled;
	}
	if (status == COMPONENT_STATUS_PARTIALLY_FUNCTIONAL)
	{
		return (m_shroudClearingRangePartial >= 0.0f) ? m_shroudClearingRangePartial : m_shroudClearingRange;
	}
	return m_shroudClearingRange;
}

Bool SensorComponent::setCurrentJammingDamage(Real damage)
{
	if (damage < 0.0f) damage = 0.0f;
	if (damage > m_jammingDamageCap) damage = m_jammingDamageCap;
	m_currentJammingDamage = damage;
	return TRUE;
}

Bool SensorComponent::addJammingDamage(Real damage)
{
	if (damage <= 0.0f) return FALSE;
	return setCurrentJammingDamage(m_currentJammingDamage + damage);
}

void SensorComponent::healJammingDamage(Real healing)
{
	if (healing <= 0.0f) return;
	Real newDamage = m_currentJammingDamage - healing;
	if (newDamage < 0.0f) newDamage = 0.0f;
	m_currentJammingDamage = newDamage;
}

void SensorComponent::updateJammingDamageHealing()
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

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature Ahmed Salah 15/01/2025 Override getStatus to include jamming damage
//-------------------------------------------------------------------------------------------------
ComponentStatus SensorComponent::getStatus() const
{
	// Get base status first
	ComponentStatus baseStatus = Component::getStatus();
	
	// If user disabled or already downed, jamming doesn't change that
	if (baseStatus == COMPONENT_STATUS_USER_DISABLED || baseStatus == COMPONENT_STATUS_DOWNED)
		return baseStatus;
	
	// Check jamming damage against max health
	Real maxHealth = getCurrentMaxHealth();
	if (maxHealth > 0.0f && m_currentJammingDamage > 0.0f)
	{
		// Component is fully jammed if jamming damage >= max health
		if (m_currentJammingDamage >= maxHealth)
			return COMPONENT_STATUS_DOWNED;
		
		// Component is partially jammed if jamming damage >= 50% of max health
		if (m_currentJammingDamage >= (maxHealth * 0.5f))
		{
			// Downgrade to partially functional if base status was fully functional
			if (baseStatus == COMPONENT_STATUS_FULLY_FUNCTIONAL)
				return COMPONENT_STATUS_PARTIALLY_FUNCTIONAL;
		}
	}
	
	// Return base status (jamming didn't affect it)
	return baseStatus;
}

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature Ahmed Salah 30/10/2025 Static parse method for SensorComponent
//-------------------------------------------------------------------------------------------------
void SensorComponent::parseSensorComponent(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	// instance is actually ActiveBodyModuleData*
	ActiveBodyModuleData* moduleData = (ActiveBodyModuleData*)instance;
	
	// Get component name from the first token (e.g., "SensorSuite", "ReconPackage", etc.)
	const char* token = ini->getNextTokenOrNull();
	AsciiString componentName;
	if (token == NULL || strlen(token) == 0)
		componentName = DEFAULT_RADAR_COMPONENT_NAME;
	else
		componentName = token;
	
	SensorComponent* sensor = new SensorComponent();
	sensor->setName(componentName);
	
	MultiIniFieldParse p;
	SensorComponent::buildFieldParse(p);

	// Parse the component block using the field parse table
	ini->initFromINIMulti(sensor, p);
	
	// Add the parsed component to the module data
	moduleData->m_componentsData.push_back(sensor);
}

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature Ahmed Salah 30/10/2025 Build field parse for SensorComponent
//-------------------------------------------------------------------------------------------------
void SensorComponent::buildFieldParse(MultiIniFieldParse& p)
{
	// Base Component properties
	Component::buildFieldParse(p);
	
	// Vision-equivalent fields
	static const FieldParse sensorVisionFieldParse[] = {
		{ "ShroudClearingRange", INI::parseReal, NULL, offsetof(SensorComponent, m_shroudClearingRange) },
		{ "PartiallyFunctionalShroudClearingRange", INI::parseReal, NULL, offsetof(SensorComponent, m_shroudClearingRangePartial) },
		{ "DisabledShroudClearingRange", INI::parseReal, NULL, offsetof(SensorComponent, m_shroudClearingRangeDisabled) },
		{ 0, 0, 0, 0 }
	};
	p.add(sensorVisionFieldParse);

	// Electronics-equivalent fields
	static const FieldParse sensorElectronicsFieldParse[] = {
		{ "JammingDamageCap", INI::parseReal, NULL, offsetof(SensorComponent, m_jammingDamageCap) },
		{ "JammingDamageHealRate", INI::parseDurationUnsignedInt, NULL, offsetof(SensorComponent, m_jammingDamageHealRate) },
		{ "JammingDamageHealAmount", INI::parseReal, NULL, offsetof(SensorComponent, m_jammingDamageHealAmount) },
		{ "CanBeJammedByDirectJammers", INI::parseBool, NULL, offsetof(SensorComponent, m_canBeJammedByDirectJammers) },
		{ "CanBeJammedByAreaJammers", INI::parseBool, NULL, offsetof(SensorComponent, m_canBeJammedByAreaJammers) },
		{ 0, 0, 0, 0 }
	};
	p.add(sensorElectronicsFieldParse);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Virtual clone method for polymorphic copying
//-------------------------------------------------------------------------------------------------
Component* SensorComponent::clone() const
{
	// Create a new SensorComponent
	SensorComponent* copy = new SensorComponent();
	
	// Copy base Component members using helper method
	copyBaseComponentMembers(copy);
	
	// Copy SensorComponent-specific members (vision and electronics data)
	copy->m_shroudClearingRange = m_shroudClearingRange;
	copy->m_shroudClearingRangePartial = m_shroudClearingRangePartial;
	copy->m_shroudClearingRangeDisabled = m_shroudClearingRangeDisabled;
	copy->m_jammingDamageCap = m_jammingDamageCap;
	copy->m_jammingDamageHealRate = m_jammingDamageHealRate;
	copy->m_jammingDamageHealAmount = m_jammingDamageHealAmount;
	copy->m_currentJammingDamage = m_currentJammingDamage;
	copy->m_jammingHealCountdown = m_jammingHealCountdown;
	copy->m_canBeJammedByDirectJammers = m_canBeJammedByDirectJammers;
	copy->m_canBeJammedByAreaJammers = m_canBeJammedByAreaJammers;
	
	return copy;
}

//-------------------------------------------------------------------------------------------------
void SensorComponent::crc( Xfer *xfer )
{
	Component::crc(xfer);
}

//-------------------------------------------------------------------------------------------------
void SensorComponent::xfer( Xfer *xfer )
{
	Component::xfer(xfer);
}

//-------------------------------------------------------------------------------------------------
void SensorComponent::loadPostProcess( void )
{
	Component::loadPostProcess();
}
