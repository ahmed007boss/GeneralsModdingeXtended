// RemoteControlComponent.cpp ///////////////////////////////////////////////////////////////
// Remote control-specific component inheriting communication behavior
// Author: TheSuperHackers
/////////////////////////////////////////////////////////////////////////////////////

#include "GameLogic/Components/RemoteControlComponent.h"
#include "Common/INI.h"
#include "GameLogic/Module/ActiveBody.h"

// TheSuperHackers @feature Ahmed Salah 15/01/2025 Default remote controller component name constant definition
const char* RemoteControlComponent::DEFAULT_REMOTE_CONTROLLER_COMPONENT_NAME = "RemoteController";

void RemoteControlComponent::parseRemoteControlComponent(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
    ActiveBodyModuleData* moduleData = (ActiveBodyModuleData*)instance;
	
	// Get component name from the first token (optional, defaults to "RemoteController")
	const char* token = ini->getNextTokenOrNull();
	AsciiString componentName;
	if (token == NULL || strlen(token) == 0)
		componentName = DEFAULT_REMOTE_CONTROLLER_COMPONENT_NAME;
	else
		componentName = token;

    RemoteControlComponent* component = new RemoteControlComponent();
    component->setName(componentName);

    MultiIniFieldParse p;
    RemoteControlComponent::buildFieldParse(p);
    ini->initFromINIMulti(component, p);
    moduleData->m_componentsData.push_back(component);
}

void RemoteControlComponent::buildFieldParse(MultiIniFieldParse& p)
{
    // Include CommunicationComponent (and base Component) fields
    CommunicationComponent::buildFieldParse(p);

    // Remote-control-specific fields can be appended here later
    static const FieldParse rcFields[] = {
        { 0, 0, 0, 0 }
    };
    p.add(rcFields);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Virtual clone method for polymorphic copying
//-------------------------------------------------------------------------------------------------
Component* RemoteControlComponent::clone() const
{
	// Create a new RemoteControlComponent (no additional members beyond CommunicationComponent)
	RemoteControlComponent* copy = new RemoteControlComponent();
	
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
void RemoteControlComponent::crc( Xfer *xfer )
{
	Component::crc(xfer);
}

//-------------------------------------------------------------------------------------------------
void RemoteControlComponent::xfer( Xfer *xfer )
{
	Component::xfer(xfer);
}

//-------------------------------------------------------------------------------------------------
void RemoteControlComponent::loadPostProcess( void )
{
	Component::loadPostProcess();
}


