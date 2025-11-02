// VisionComponent.cpp ///////////////////////////////////////////////////////////////////
// Vision-specific component with additional sight and detection properties
// Author: TheSuperHackers
///////////////////////////////////////////////////////////////////////////////////////////////////

#define DEFINE_HIT_SIDE_NAMES

#include "GameLogic/Components/VisionComponent.h"
#include "Common/INI.h"
#include "GameLogic/Components/Component.h"
#include "GameLogic/Damage.h"
#include "Common/GameType.h"
#include "GameLogic/Module/ActiveBody.h"

// TheSuperHackers @feature Ahmed Salah 15/01/2025 Default vision component name constant definition
const char* VisionComponent::DEFAULT_VISION_COMPONENT_NAME = "Vision";

Real VisionComponent::getShroudClearingRange() const
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
//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Static parse method for VisionComponent inheritance support
//-------------------------------------------------------------------------------------------------
void VisionComponent::parseVisionComponent(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	// instance is actually ActiveBodyModuleData*
	ActiveBodyModuleData* moduleData = (ActiveBodyModuleData*)instance;
	
	// Get component name from the first token (optional, defaults to "Vision")
	const char* token = ini->getNextTokenOrNull();
	AsciiString componentName;
	if (token == NULL || strlen(token) == 0)
		componentName = DEFAULT_VISION_COMPONENT_NAME;
	else
		componentName = token;
	
	VisionComponent* component = new VisionComponent();
	// Set component name using direct assignment
	component->setName(componentName);
	
	MultiIniFieldParse p;
	VisionComponent::buildFieldParse(p);

	// Parse the component block using the field parse table
	ini->initFromINIMulti(component, p);
	
	// Add the parsed component to the module data
	moduleData->m_componentsData.push_back(component);
}

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Build field parse method for VisionComponent inheritance support
//-------------------------------------------------------------------------------------------------
void VisionComponent::buildFieldParse(MultiIniFieldParse& p)
{
	// Add base Component properties
	Component::buildFieldParse(p);

	// Add VisionComponent-specific properties (empty for now, will be added later)
	static const FieldParse visionComponentFieldParse[] = {
		{ "ShroudClearingRange", INI::parseReal, NULL, offsetof(VisionComponent, m_shroudClearingRange) },
		{ "PartiallyFunctionalShroudClearingRange", INI::parseReal, NULL, offsetof(VisionComponent, m_shroudClearingRangePartial) },
		{ "DisabledShroudClearingRange", INI::parseReal, NULL, offsetof(VisionComponent, m_shroudClearingRangeDisabled) },
		{ 0, 0, 0, 0 }
	};

	p.add(visionComponentFieldParse);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Virtual clone method for polymorphic copying
//-------------------------------------------------------------------------------------------------
Component* VisionComponent::clone() const
{
	// Create a new VisionComponent
	VisionComponent* copy = new VisionComponent();
	
	// Copy base Component members using helper method
	copyBaseComponentMembers(copy);
	
	// Copy VisionComponent-specific members
	copy->m_shroudClearingRange = m_shroudClearingRange;
	copy->m_shroudClearingRangePartial = m_shroudClearingRangePartial;
	copy->m_shroudClearingRangeDisabled = m_shroudClearingRangeDisabled;
	
	return copy;
}

//-------------------------------------------------------------------------------------------------
void VisionComponent::crc( Xfer *xfer )
{
	Component::crc(xfer);
}

//-------------------------------------------------------------------------------------------------
void VisionComponent::xfer( Xfer *xfer )
{
	Component::xfer(xfer);
}

//-------------------------------------------------------------------------------------------------
void VisionComponent::loadPostProcess( void )
{
	Component::loadPostProcess();
}
