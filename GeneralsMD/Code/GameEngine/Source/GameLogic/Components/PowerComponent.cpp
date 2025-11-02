// PowerComponent.cpp ///////////////////////////////////////////////////////////////////
// Power-specific component with additional electrical power generation properties
// Author: TheSuperHackers
///////////////////////////////////////////////////////////////////////////////////////////////////

#define DEFINE_HIT_SIDE_NAMES

#include "GameLogic/Components/PowerComponent.h"
#include "Common/INI.h"
#include "GameLogic/Components/Component.h"
#include "GameLogic/Damage.h"
#include "Common/GameType.h"
#include "GameLogic/Module/ActiveBody.h"

// TheSuperHackers @feature Ahmed Salah 15/01/2025 Default power supply component name constant definition
const char* PowerComponent::DEFAULT_POWER_SUPPLY_COMPONENT_NAME = "PowerSupply";

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Static parse method for PowerComponent inheritance support
//-------------------------------------------------------------------------------------------------
void PowerComponent::parsePowerComponent(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	// instance is actually ActiveBodyModuleData*
	ActiveBodyModuleData* moduleData = (ActiveBodyModuleData*)instance;
	
	// Get component name from the first token (optional, defaults to "PowerSupply")
	const char* token = ini->getNextTokenOrNull();
	AsciiString componentName;
	if (token == NULL || strlen(token) == 0)
		componentName = DEFAULT_POWER_SUPPLY_COMPONENT_NAME;
	else
		componentName = token;
	
	PowerComponent* component = new PowerComponent();
	// Set component name using direct assignment
	component->setName(componentName);
	
	MultiIniFieldParse p;
	PowerComponent::buildFieldParse(p);

	// Parse the component block using the field parse table
	ini->initFromINIMulti(component, p);
	
	// Add the parsed component to the module data
	moduleData->m_componentsData.push_back(component);
}

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Build field parse method for PowerComponent inheritance support
//-------------------------------------------------------------------------------------------------
void PowerComponent::buildFieldParse(MultiIniFieldParse& p)
{
	// Add base ElectronicsComponent (and Component) properties
	ElectronicsComponent::buildFieldParse(p);

	// Add PowerComponent-specific properties (empty for now, will be added later)
	static const FieldParse powerComponentFieldParse[] = {
		{ 0, 0, 0, 0 }
	};

	p.add(powerComponentFieldParse);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Virtual clone method for polymorphic copying
//-------------------------------------------------------------------------------------------------
Component* PowerComponent::clone() const
{
	// Create a new PowerComponent (no additional members beyond ElectronicsComponent)
	PowerComponent* copy = new PowerComponent();
	
	// Copy base Component members using helper method
	copyBaseComponentMembers(copy);
	
	// Copy ElectronicsComponent-specific members
	const ElectronicsComponent* baseSrc = this;
	copy->m_jammingDamageCap = baseSrc->m_jammingDamageCap;
	copy->m_jammingDamageHealRate = baseSrc->m_jammingDamageHealRate;
	copy->m_jammingDamageHealAmount = baseSrc->m_jammingDamageHealAmount;
	copy->m_currentJammingDamage = baseSrc->m_currentJammingDamage;
	copy->m_jammingHealCountdown = baseSrc->m_jammingHealCountdown;
	copy->m_canBeJammedByDirectJammers = baseSrc->m_canBeJammedByDirectJammers;
	copy->m_canBeJammedByAreaJammers = baseSrc->m_canBeJammedByAreaJammers;
	
	return copy;
}

//-------------------------------------------------------------------------------------------------
void PowerComponent::crc( Xfer *xfer )
{
	Component::crc(xfer);
}

//-------------------------------------------------------------------------------------------------
void PowerComponent::xfer( Xfer *xfer )
{
	Component::xfer(xfer);
}

//-------------------------------------------------------------------------------------------------
void PowerComponent::loadPostProcess( void )
{
	Component::loadPostProcess();
}
