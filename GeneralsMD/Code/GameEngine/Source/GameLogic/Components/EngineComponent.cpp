// EngineComponent.cpp ///////////////////////////////////////////////////////////////////
// Engine-specific component with additional engine-related properties
// Author: TheSuperHackers
///////////////////////////////////////////////////////////////////////////////////////////////////

#define DEFINE_HIT_SIDE_NAMES

#include "GameLogic/Components/EngineComponent.h"
#include "Common/INI.h"
#include "GameLogic/Components/Component.h"
#include "GameLogic/Damage.h"
#include "Common/GameType.h"
#include "GameLogic/Module/ActiveBody.h"

// TheSuperHackers @feature Ahmed Salah 15/01/2025 Default main engine component name constant definition
const char* EngineComponent::DEFAULT_MAIN_ENGINE_COMPONENT_NAME = "MainEngine";

//-------------------------------------------------------------------------------------------------
// Custom parsing functions to set the "has" flags when damaged properties are parsed
//-------------------------------------------------------------------------------------------------
static void parseMaxSpeedDamaged(INI* ini, void* instance, void* store, const void* userData)
{
	EngineComponent* component = (EngineComponent*)instance;
	const char* token = ini->getNextToken();
	if (!token) return;
	
	const char* percentPos = strchr(token, '%');
	if (percentPos != NULL)
	{
		// Contains % - treat as percentage
		char valueBuffer[256];
		strncpy(valueBuffer, token, percentPos - token);
		valueBuffer[percentPos - token] = '\0';
		Real value = 0.0f;
		if (sscanf(valueBuffer, "%f", &value) == 1)
		{
			component->m_maxSpeedDamaged = value;
			component->m_maxSpeedDamagedValueType = VALUE_TYPE_PERCENTAGE;
		}
	}
	else
	{
		// No % - use standard INI parser
		INI::parseVelocityReal(ini, instance, store, userData);
		component->m_maxSpeedDamagedValueType = VALUE_TYPE_ABSOLUTE;
	}
	component->m_hasMaxSpeedDamaged = TRUE;
}

static void parseMaxTurnRateDamaged(INI* ini, void* instance, void* store, const void* userData)
{
	EngineComponent* component = (EngineComponent*)instance;
	const char* token = ini->getNextToken();
	if (!token) return;
	
	const char* percentPos = strchr(token, '%');
	if (percentPos != NULL)
	{
		// Contains % - treat as percentage
		char valueBuffer[256];
		strncpy(valueBuffer, token, percentPos - token);
		valueBuffer[percentPos - token] = '\0';
		Real value = 0.0f;
		if (sscanf(valueBuffer, "%f", &value) == 1)
		{
			component->m_maxTurnRateDamaged = value;
			component->m_maxTurnRateDamagedValueType = VALUE_TYPE_PERCENTAGE;
		}
	}
	else
	{
		// No % - use standard INI parser
		INI::parseAngularVelocityReal(ini, instance, store, userData);
		component->m_maxTurnRateDamagedValueType = VALUE_TYPE_ABSOLUTE;
	}
	component->m_hasMaxTurnRateDamaged = TRUE;
}

static void parseMaxAccelerationDamaged(INI* ini, void* instance, void* store, const void* userData)
{
	EngineComponent* component = (EngineComponent*)instance;
	const char* token = ini->getNextToken();
	if (!token) return;
	
	const char* percentPos = strchr(token, '%');
	if (percentPos != NULL)
	{
		// Contains % - treat as percentage
		char valueBuffer[256];
		strncpy(valueBuffer, token, percentPos - token);
		valueBuffer[percentPos - token] = '\0';
		Real value = 0.0f;
		if (sscanf(valueBuffer, "%f", &value) == 1)
		{
			component->m_maxAccelerationDamaged = value;
			component->m_maxAccelerationDamagedValueType = VALUE_TYPE_PERCENTAGE;
		}
	}
	else
	{
		// No % - use standard INI parser
		INI::parseAccelerationReal(ini, instance, store, userData);
		component->m_maxAccelerationDamagedValueType = VALUE_TYPE_ABSOLUTE;
	}
	component->m_hasMaxAccelerationDamaged = TRUE;
}

static void parseMaxLiftDamaged(INI* ini, void* instance, void* store, const void* userData)
{
	EngineComponent* component = (EngineComponent*)instance;
	const char* token = ini->getNextToken();
	if (!token) return;
	
	const char* percentPos = strchr(token, '%');
	if (percentPos != NULL)
	{
		// Contains % - treat as percentage
		char valueBuffer[256];
		strncpy(valueBuffer, token, percentPos - token);
		valueBuffer[percentPos - token] = '\0';
		Real value = 0.0f;
		if (sscanf(valueBuffer, "%f", &value) == 1)
		{
			component->m_maxLiftDamaged = value;
			component->m_maxLiftDamagedValueType = VALUE_TYPE_PERCENTAGE;
		}
	}
	else
	{
		// No % - use standard INI parser
		INI::parseAccelerationReal(ini, instance, store, userData);
		component->m_maxLiftDamagedValueType = VALUE_TYPE_ABSOLUTE;
	}
	component->m_hasMaxLiftDamaged = TRUE;
}

//-------------------------------------------------------------------------------------------------
// Custom parsing functions for destroyed properties with automatic % detection
//-------------------------------------------------------------------------------------------------
static void parseMaxSpeedDestroyed(INI* ini, void* instance, void* store, const void* userData)
{
	EngineComponent* component = (EngineComponent*)instance;
	const char* token = ini->getNextToken();
	if (!token) return;
	
	const char* percentPos = strchr(token, '%');
	if (percentPos != NULL)
	{
		// Contains % - treat as percentage
		char valueBuffer[256];
		strncpy(valueBuffer, token, percentPos - token);
		valueBuffer[percentPos - token] = '\0';
		Real value = 0.0f;
		if (sscanf(valueBuffer, "%f", &value) == 1)
		{
			component->m_maxSpeedDestroyed = value;
			component->m_maxSpeedDestroyedValueType = VALUE_TYPE_PERCENTAGE;
		}
	}
	else
	{
		// No % - use standard INI parser
		INI::parseVelocityReal(ini, instance, store, userData);
		component->m_maxSpeedDestroyedValueType = VALUE_TYPE_ABSOLUTE;
	}
}

static void parseMaxTurnRateDestroyed(INI* ini, void* instance, void* store, const void* userData)
{
	EngineComponent* component = (EngineComponent*)instance;
	const char* token = ini->getNextToken();
	if (!token) return;
	
	const char* percentPos = strchr(token, '%');
	if (percentPos != NULL)
	{
		// Contains % - treat as percentage
		char valueBuffer[256];
		strncpy(valueBuffer, token, percentPos - token);
		valueBuffer[percentPos - token] = '\0';
		Real value = 0.0f;
		if (sscanf(valueBuffer, "%f", &value) == 1)
		{
			component->m_maxTurnRateDestroyed = value;
			component->m_maxTurnRateDestroyedValueType = VALUE_TYPE_PERCENTAGE;
		}
	}
	else
	{
		// No % - use standard INI parser
		INI::parseAngularVelocityReal(ini, instance, store, userData);
		component->m_maxTurnRateDestroyedValueType = VALUE_TYPE_ABSOLUTE;
	}
}

static void parseMaxAccelerationDestroyed(INI* ini, void* instance, void* store, const void* userData)
{
	EngineComponent* component = (EngineComponent*)instance;
	const char* token = ini->getNextToken();
	if (!token) return;
	
	const char* percentPos = strchr(token, '%');
	if (percentPos != NULL)
	{
		// Contains % - treat as percentage
		char valueBuffer[256];
		strncpy(valueBuffer, token, percentPos - token);
		valueBuffer[percentPos - token] = '\0';
		Real value = 0.0f;
		if (sscanf(valueBuffer, "%f", &value) == 1)
		{
			component->m_maxAccelerationDestroyed = value;
			component->m_maxAccelerationDestroyedValueType = VALUE_TYPE_PERCENTAGE;
		}
	}
	else
	{
		// No % - use standard INI parser
		INI::parseAccelerationReal(ini, instance, store, userData);
		component->m_maxAccelerationDestroyedValueType = VALUE_TYPE_ABSOLUTE;
	}
}

static void parseMaxLiftDestroyed(INI* ini, void* instance, void* store, const void* userData)
{
	EngineComponent* component = (EngineComponent*)instance;
	const char* token = ini->getNextToken();
	if (!token) return;
	
	const char* percentPos = strchr(token, '%');
	if (percentPos != NULL)
	{
		// Contains % - treat as percentage
		char valueBuffer[256];
		strncpy(valueBuffer, token, percentPos - token);
		valueBuffer[percentPos - token] = '\0';
		Real value = 0.0f;
		if (sscanf(valueBuffer, "%f", &value) == 1)
		{
			component->m_maxLiftDestroyed = value;
			component->m_maxLiftDestroyedValueType = VALUE_TYPE_PERCENTAGE;
		}
	}
	else
	{
		// No % - use standard INI parser
		INI::parseAccelerationReal(ini, instance, store, userData);
		component->m_maxLiftDestroyedValueType = VALUE_TYPE_ABSOLUTE;
	}
}

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature Ahmed Salah 30/10/2025 Adjust locomotor max speed based on engine status
//-------------------------------------------------------------------------------------------------
void EngineComponent::calculateComponentMaxSpeed(Real& speed, Real damagedSpeed) const
{
    const ComponentStatus status = getStatus();
    if (status == COMPONENT_STATUS_DOWNED || status == COMPONENT_STATUS_USER_DISABLED)
    {
        if (m_maxSpeedDestroyedValueType == VALUE_TYPE_PERCENTAGE)
        {
            speed = speed * (m_maxSpeedDestroyed / 100.0f);
        }
        else
        {
            speed = m_maxSpeedDestroyed;
        }
        return;
    }
    if (status == COMPONENT_STATUS_PARTIALLY_FUNCTIONAL)
    {
        if (m_hasMaxSpeedDamaged)
        {
            if (m_maxSpeedDamagedValueType == VALUE_TYPE_PERCENTAGE)
            {
                speed = speed * (m_maxSpeedDamaged / 100.0f);
            }
            else
            {
                speed = m_maxSpeedDamaged;
            }
        }
        else
        {
            speed = damagedSpeed;
        }
        return;
    }
    // Fully functional or none: leave speed unchanged
}

//-------------------------------------------------------------------------------------------------
void EngineComponent::calculateComponentMaxTurnRate(Real& turnRate, Real damagedTurnRate) const
{
    const ComponentStatus status = getStatus();
    if (status == COMPONENT_STATUS_DOWNED || status == COMPONENT_STATUS_USER_DISABLED)
    {
        if (m_maxTurnRateDestroyedValueType == VALUE_TYPE_PERCENTAGE)
        {
            turnRate = turnRate * (m_maxTurnRateDestroyed / 100.0f);
        }
        else
        {
            turnRate = m_maxTurnRateDestroyed;
        }
        return;
    }
    if (status == COMPONENT_STATUS_PARTIALLY_FUNCTIONAL)
    {
        if (m_hasMaxTurnRateDamaged)
        {
            if (m_maxTurnRateDamagedValueType == VALUE_TYPE_PERCENTAGE)
            {
                turnRate = turnRate * (m_maxTurnRateDamaged / 100.0f);
            }
            else
            {
                turnRate = m_maxTurnRateDamaged;
            }
        }
        else
        {
            turnRate = damagedTurnRate;
        }
        return;
    }
}

//-------------------------------------------------------------------------------------------------
void EngineComponent::calculateComponentMaxAcceleration(Real& acceleration, Real damagedAcceleration) const
{
    const ComponentStatus status = getStatus();
    if (status == COMPONENT_STATUS_DOWNED || status == COMPONENT_STATUS_USER_DISABLED)
    {
        if (m_maxAccelerationDestroyedValueType == VALUE_TYPE_PERCENTAGE)
        {
            acceleration = acceleration * (m_maxAccelerationDestroyed / 100.0f);
        }
        else
        {
            acceleration = m_maxAccelerationDestroyed;
        }
        return;
    }
    if (status == COMPONENT_STATUS_PARTIALLY_FUNCTIONAL)
    {
        if (m_hasMaxAccelerationDamaged)
        {
            if (m_maxAccelerationDamagedValueType == VALUE_TYPE_PERCENTAGE)
            {
                acceleration = acceleration * (m_maxAccelerationDamaged / 100.0f);
            }
            else
            {
                acceleration = m_maxAccelerationDamaged;
            }
        }
        else
        {
            acceleration = damagedAcceleration;
        }
        return;
    }
}

//-------------------------------------------------------------------------------------------------
void EngineComponent::calculateComponentMaxLift(Real& lift, Real damagedLift) const
{
    const ComponentStatus status = getStatus();
    if (status == COMPONENT_STATUS_DOWNED || status == COMPONENT_STATUS_USER_DISABLED)
    {
        if (m_maxLiftDestroyedValueType == VALUE_TYPE_PERCENTAGE)
        {
            lift = lift * (m_maxLiftDestroyed / 100.0f);
        }
        else
        {
            lift = m_maxLiftDestroyed;
        }
        return;
    }
    if (status == COMPONENT_STATUS_PARTIALLY_FUNCTIONAL)
    {
        if (m_hasMaxLiftDamaged)
        {
            if (m_maxLiftDamagedValueType == VALUE_TYPE_PERCENTAGE)
            {
                lift = lift * (m_maxLiftDamaged / 100.0f);
            }
            else
            {
                lift = m_maxLiftDamaged;
            }
        }
        else
        {
            lift = damagedLift;
        }
        return;
    }
}

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Static parse method for EngineComponent inheritance support
//-------------------------------------------------------------------------------------------------
void EngineComponent::parseEngineComponent(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	// instance is actually ActiveBodyModuleData*
	ActiveBodyModuleData* moduleData = (ActiveBodyModuleData*)instance;
	
	// Get component name from the first token (optional, defaults to "MainEngine")
	const char* token = ini->getNextTokenOrNull();
	AsciiString componentName;
	if (token == NULL || strlen(token) == 0)
		componentName = DEFAULT_MAIN_ENGINE_COMPONENT_NAME;
	else
		componentName = token;
	
	EngineComponent* component = new EngineComponent();
	// Set component name using direct assignment
	component->setName(componentName);
	
	MultiIniFieldParse p;
	EngineComponent::buildFieldParse(p);

	// Parse the component block using the field parse table
	ini->initFromINIMulti(component, p);
	
	// Add the parsed component to the module data
	moduleData->m_componentsData.push_back(component);
}

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Build field parse method for EngineComponent inheritance support
//-------------------------------------------------------------------------------------------------
void EngineComponent::buildFieldParse(MultiIniFieldParse& p)
{
	// Add base Component properties
	Component::buildFieldParse(p);

	// Add EngineComponent-specific properties
	static const FieldParse engineComponentFieldParse[] = {
		{ "MaxSpeedDamaged", parseMaxSpeedDamaged, NULL, offsetof(EngineComponent, m_maxSpeedDamaged) },
		{ "MaxSpeedDamagedValueType", INI::parseIndexList, TheValueTypeNames, offsetof(EngineComponent, m_maxSpeedDamagedValueType) },
		{ "MaxTurnRateDamaged", parseMaxTurnRateDamaged, NULL, offsetof(EngineComponent, m_maxTurnRateDamaged) },
		{ "MaxTurnRateDamagedValueType", INI::parseIndexList, TheValueTypeNames, offsetof(EngineComponent, m_maxTurnRateDamagedValueType) },
		{ "MaxAccelerationDamaged", parseMaxAccelerationDamaged, NULL, offsetof(EngineComponent, m_maxAccelerationDamaged) },
		{ "MaxAccelerationDamagedValueType", INI::parseIndexList, TheValueTypeNames, offsetof(EngineComponent, m_maxAccelerationDamagedValueType) },
		{ "MaxLiftDamaged", parseMaxLiftDamaged, NULL, offsetof(EngineComponent, m_maxLiftDamaged) },
		{ "MaxLiftDamagedValueType", INI::parseIndexList, TheValueTypeNames, offsetof(EngineComponent, m_maxLiftDamagedValueType) },
		{ "MaxSpeedDestroyed", parseMaxSpeedDestroyed, NULL, offsetof(EngineComponent, m_maxSpeedDestroyed) },
		{ "MaxTurnRateDestroyed", parseMaxTurnRateDestroyed, NULL, offsetof(EngineComponent, m_maxTurnRateDestroyed) },
		{ "MaxAccelerationDestroyed", parseMaxAccelerationDestroyed, NULL, offsetof(EngineComponent, m_maxAccelerationDestroyed) },
		{ "MaxLiftDestroyed", parseMaxLiftDestroyed, NULL, offsetof(EngineComponent, m_maxLiftDestroyed) },
		{ 0, 0, 0, 0 }
	};

	p.add(engineComponentFieldParse);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Virtual clone method for polymorphic copying
//-------------------------------------------------------------------------------------------------
Component* EngineComponent::clone() const
{
	// Create a new EngineComponent
	EngineComponent* copy = new EngineComponent();
	
	// Copy base Component members using helper method
	copyBaseComponentMembers(copy);
	
	// Copy EngineComponent-specific members
	copy->m_maxSpeedDamaged = m_maxSpeedDamaged;
	copy->m_maxSpeedDamagedValueType = m_maxSpeedDamagedValueType;
	copy->m_hasMaxSpeedDamaged = m_hasMaxSpeedDamaged;
	copy->m_maxTurnRateDamaged = m_maxTurnRateDamaged;
	copy->m_maxTurnRateDamagedValueType = m_maxTurnRateDamagedValueType;
	copy->m_hasMaxTurnRateDamaged = m_hasMaxTurnRateDamaged;
	copy->m_maxAccelerationDamaged = m_maxAccelerationDamaged;
	copy->m_maxAccelerationDamagedValueType = m_maxAccelerationDamagedValueType;
	copy->m_hasMaxAccelerationDamaged = m_hasMaxAccelerationDamaged;
	copy->m_maxLiftDamaged = m_maxLiftDamaged;
	copy->m_maxLiftDamagedValueType = m_maxLiftDamagedValueType;
	copy->m_hasMaxLiftDamaged = m_hasMaxLiftDamaged;
	copy->m_maxSpeedDestroyed = m_maxSpeedDestroyed;
	copy->m_maxSpeedDestroyedValueType = m_maxSpeedDestroyedValueType;
	copy->m_maxTurnRateDestroyed = m_maxTurnRateDestroyed;
	copy->m_maxTurnRateDestroyedValueType = m_maxTurnRateDestroyedValueType;
	copy->m_maxAccelerationDestroyed = m_maxAccelerationDestroyed;
	copy->m_maxAccelerationDestroyedValueType = m_maxAccelerationDestroyedValueType;
	copy->m_maxLiftDestroyed = m_maxLiftDestroyed;
	copy->m_maxLiftDestroyedValueType = m_maxLiftDestroyedValueType;
	
	return copy;
}

//-------------------------------------------------------------------------------------------------
void EngineComponent::crc( Xfer *xfer )
{
	Component::crc(xfer);
}

//-------------------------------------------------------------------------------------------------
void EngineComponent::xfer( Xfer *xfer )
{
	Component::xfer(xfer);
}

//-------------------------------------------------------------------------------------------------
void EngineComponent::loadPostProcess( void )
{
	Component::loadPostProcess();
}
