// CommunicationComponent.cpp ///////////////////////////////////////////////////////////////////
// Communication-specific component with additional radio and communication properties
// Author: TheSuperHackers
///////////////////////////////////////////////////////////////////////////////////////////////////

#define DEFINE_HIT_SIDE_NAMES

#include "GameLogic/Components/CommunicationComponent.h"
#include "Common/INI.h"
#include "GameLogic/Components/Component.h"
#include "GameLogic/Damage.h"
#include "Common/GameType.h"
#include "GameLogic/Module/ActiveBody.h"

// TheSuperHackers @feature Ahmed Salah 15/01/2025 Default communication radio component name constant definition
const char* CommunicationComponent::DEFAULT_COMMUNICATION_RADIO_COMPONENT_NAME = "CommunicationRadio";

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Static parse method for CommunicationComponent inheritance support
//-------------------------------------------------------------------------------------------------
void CommunicationComponent::parseCommunicationComponent(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	// instance is actually ActiveBodyModuleData*
	ActiveBodyModuleData* moduleData = (ActiveBodyModuleData*)instance;
	
	// Get component name from the first token (optional, defaults to "CommunicationRadio")
	const char* token = ini->getNextTokenOrNull();
	AsciiString componentName;
	if (token == NULL || strlen(token) == 0)
		componentName = DEFAULT_COMMUNICATION_RADIO_COMPONENT_NAME;
	else
		componentName = token;
	
	CommunicationComponent* component = new CommunicationComponent();
	// Set component name using direct assignment
	component->setName(componentName);
	
	MultiIniFieldParse p;
	CommunicationComponent::buildFieldParse(p);

	// Parse the component block using the field parse table
	ini->initFromINIMulti(component, p);
	
	// Add the parsed component to the module data
	moduleData->m_componentsData.push_back(component);
}

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Build field parse method for CommunicationComponent inheritance support
//-------------------------------------------------------------------------------------------------
void CommunicationComponent::buildFieldParse(MultiIniFieldParse& p)
{
    // Add base Electronics (and Component) properties
    ElectronicsComponent::buildFieldParse(p);

	// Add CommunicationComponent-specific properties (empty for now, will be added later)
	static const FieldParse communicationComponentFieldParse[] = {
		{ 0, 0, 0, 0 }
	};

	p.add(communicationComponentFieldParse);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Virtual clone method for polymorphic copying
//-------------------------------------------------------------------------------------------------
Component* CommunicationComponent::clone() const
{
	// Create a new CommunicationComponent (no additional members beyond ElectronicsComponent)
	CommunicationComponent* copy = new CommunicationComponent();
	
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
void CommunicationComponent::crc( Xfer *xfer )
{
	Component::crc(xfer);
}

//-------------------------------------------------------------------------------------------------
void CommunicationComponent::xfer( Xfer *xfer )
{
	Component::xfer(xfer);
}

//-------------------------------------------------------------------------------------------------
void CommunicationComponent::loadPostProcess( void )
{
	Component::loadPostProcess();
}
