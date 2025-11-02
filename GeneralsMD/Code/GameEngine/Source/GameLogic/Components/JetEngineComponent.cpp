// JetEngineComponent.cpp ///////////////////////////////////////////////////////////////
// Jet-engine specific component inheriting engine behavior
// Author: TheSuperHackers
/////////////////////////////////////////////////////////////////////////////////////

#include "GameLogic/Components/JetEngineComponent.h"
#include "Common/INI.h"
#include "GameLogic/Module/ActiveBody.h"

// TheSuperHackers @feature Ahmed Salah 15/01/2025 Default jet engine component name constant definition
const char* JetEngineComponent::DEFAULT_JET_ENGINE_COMPONENT_NAME = "MainEngine";

void JetEngineComponent::parseJetEngineComponent(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	ActiveBodyModuleData* moduleData = (ActiveBodyModuleData*)instance;
	
	// Get component name from the first token (optional, defaults to "MainEngine")
	const char* token = ini->getNextTokenOrNull();
	AsciiString componentName;
	if (token == NULL || strlen(token) == 0)
		componentName = DEFAULT_JET_ENGINE_COMPONENT_NAME;
	else
		componentName = token;

	JetEngineComponent* component = new JetEngineComponent();
	component->setName(componentName);

	MultiIniFieldParse p;
	JetEngineComponent::buildFieldParse(p);
	ini->initFromINIMulti(component, p);
	moduleData->m_componentsData.push_back(component);
}

void JetEngineComponent::buildFieldParse(MultiIniFieldParse& p)
{
	// Include EngineComponent fields by default
	EngineComponent::buildFieldParse(p);

	// JetEngine-specific fields can be appended here later
	static const FieldParse jetEngineFields[] = {
		{ 0, 0, 0, 0 }
	};
	p.add(jetEngineFields);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Virtual clone method for polymorphic copying
//-------------------------------------------------------------------------------------------------
Component* JetEngineComponent::clone() const
{
	// Create a new JetEngineComponent (no additional members beyond EngineComponent)
	JetEngineComponent* copy = new JetEngineComponent();
	
	// Copy base Component members using helper method
	copyBaseComponentMembers(copy);
	
	// Copy EngineComponent-specific members
	const EngineComponent* baseSrc = this;
	copy->m_maxSpeedDamaged = baseSrc->m_maxSpeedDamaged;
	copy->m_maxSpeedDamagedValueType = baseSrc->m_maxSpeedDamagedValueType;
	copy->m_hasMaxSpeedDamaged = baseSrc->m_hasMaxSpeedDamaged;
	copy->m_maxTurnRateDamaged = baseSrc->m_maxTurnRateDamaged;
	copy->m_maxTurnRateDamagedValueType = baseSrc->m_maxTurnRateDamagedValueType;
	copy->m_hasMaxTurnRateDamaged = baseSrc->m_hasMaxTurnRateDamaged;
	copy->m_maxAccelerationDamaged = baseSrc->m_maxAccelerationDamaged;
	copy->m_maxAccelerationDamagedValueType = baseSrc->m_maxAccelerationDamagedValueType;
	copy->m_hasMaxAccelerationDamaged = baseSrc->m_hasMaxAccelerationDamaged;
	copy->m_maxLiftDamaged = baseSrc->m_maxLiftDamaged;
	copy->m_maxLiftDamagedValueType = baseSrc->m_maxLiftDamagedValueType;
	copy->m_hasMaxLiftDamaged = baseSrc->m_hasMaxLiftDamaged;
	copy->m_maxSpeedDestroyed = baseSrc->m_maxSpeedDestroyed;
	copy->m_maxSpeedDestroyedValueType = baseSrc->m_maxSpeedDestroyedValueType;
	copy->m_maxTurnRateDestroyed = baseSrc->m_maxTurnRateDestroyed;
	copy->m_maxTurnRateDestroyedValueType = baseSrc->m_maxTurnRateDestroyedValueType;
	copy->m_maxAccelerationDestroyed = baseSrc->m_maxAccelerationDestroyed;
	copy->m_maxAccelerationDestroyedValueType = baseSrc->m_maxAccelerationDestroyedValueType;
	copy->m_maxLiftDestroyed = baseSrc->m_maxLiftDestroyed;
	copy->m_maxLiftDestroyedValueType = baseSrc->m_maxLiftDestroyedValueType;
	
	return copy;
}

//-------------------------------------------------------------------------------------------------
void JetEngineComponent::crc( Xfer *xfer )
{
	Component::crc(xfer);
}

//-------------------------------------------------------------------------------------------------
void JetEngineComponent::xfer( Xfer *xfer )
{
	Component::xfer(xfer);
}

//-------------------------------------------------------------------------------------------------
void JetEngineComponent::loadPostProcess( void )
{
	Component::loadPostProcess();
}
