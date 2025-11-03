/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// Component.cpp ///////////////////////////////////////////////////////////////////
// Component health system for detailed damage modeling
// Author: TheSuperHackers
///////////////////////////////////////////////////////////////////////////////////////////////////
#define DEFINE_BODYDAMAGETYPE_NAMES

#include "GameLogic/Components/Component.h"
#include "Common/Xfer.h"
#include "Common/INI.h"
#include "Common/GameType.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/ActiveBody.h"
#include "GameLogic/Components/ElectronicsComponent.h"
#include "GameClient/Anim2D.h"
#include "GameLogic/Object.h"

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Parse Component max health from INI
//-------------------------------------------------------------------------------------------------
static void parseComponentMaxHealth(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	Component* component = (Component*)instance;
	
	// Get the token and check if it contains a percentage symbol
	const char* token = ini->getNextToken();
	if (!token) return;
	
	// Check if the token contains a percentage symbol
	const char* percentPos = strchr(token, '%');
	if (percentPos != NULL)
	{
		// Extract the numeric value (copy everything before the %)
		char valueBuffer[256];
		strncpy(valueBuffer, token, percentPos - token);
		valueBuffer[percentPos - token] = '\0';
		
		// Parse the numeric value
		Real value = 0.0f;
		if (sscanf(valueBuffer, "%f", &value) == 1)
		{
			component->setMaxHealthConfig(value);
			component->setMaxHealthValueType(VALUE_TYPE_PERCENTAGE);
		}
	}
	else
	{
		// Parse as absolute value
		Real value = 0.0f;
		if (sscanf(token, "%f", &value) == 1)
		{
			component->setMaxHealthConfig(value);
			component->setMaxHealthValueType(VALUE_TYPE_ABSOLUTE);
		}
	}
}

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Parse Component initial health data from INI
//-------------------------------------------------------------------------------------------------
static void parseComponentInitialHealth(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	Component* component = (Component*)instance;
	
	// Get the token and check if it contains a percentage symbol
	const char* token = ini->getNextToken();
	if (!token) return;
	
	// Check if the token contains a percentage symbol
	const char* percentPos = strchr(token, '%');
	if (percentPos != NULL)
	{
		// Extract the numeric value (copy everything before the %)
		char valueBuffer[256];
		strncpy(valueBuffer, token, percentPos - token);
		valueBuffer[percentPos - token] = '\0';
		
		// Parse the numeric value
		Real value = 0.0f;
		if (sscanf(valueBuffer, "%f", &value) == 1)
		{
			component->setInitialHealthConfig(value);
			component->setInitialHealthValueType(VALUE_TYPE_PERCENTAGE);
		}
	}
	else
	{
		// Parse as absolute value
		Real value = 0.0f;
		if (sscanf(token, "%f", &value) == 1)
		{
			component->setInitialHealthConfig(value);
			component->setInitialHealthValueType(VALUE_TYPE_ABSOLUTE);
		}
	}
}

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Parse Component healing type from INI
//-------------------------------------------------------------------------------------------------
static void parseComponentHealingType(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	Component* component = (Component*)instance;
	const char* token = ini->getNextToken();
	if (!token) return;
	
	// Parse healing type
	if (strcmp(token, "NORMAL") == 0)
		component->setHealingType(COMPONENT_HEALING_NORMAL);
	else if (strcmp(token, "PARTIAL_ONLY") == 0)
		component->setHealingType(COMPONENT_HEALING_PARTIAL_ONLY);
	else if (strcmp(token, "PARTIAL_DESTROYED") == 0)
		component->setHealingType(COMPONENT_HEALING_PARTIAL_DESTROYED);
	else if (strcmp(token, "PARTIAL_LIMITED") == 0)
		component->setHealingType(COMPONENT_HEALING_PARTIAL_LIMITED);
	else if (strcmp(token, "REPLACEMENT_ONLY") == 0)
		component->setHealingType(COMPONENT_HEALING_REPLACEMENT_ONLY);
	else
	{
		DEBUG_CRASH(("Unknown ComponentHealingType: %s", token));
		throw INI_INVALID_DATA;
	}
}

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Parse Component damage on sides from INI
//-------------------------------------------------------------------------------------------------
static void parseComponentDamageOnSides(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	Component* component = (Component*)instance;
	component->setDamageOnSides(HitSideFlags());
	
	const char* token = ini->getNextToken();
	while (token)
	{
		if (strcmp(token, "HIT_SIDE_FRONT") == 0)
			{ HitSideFlags f = component->getDamageOnSides(); f.set(HIT_SIDE_FRONT); component->setDamageOnSides(f); }
		else if (strcmp(token, "HIT_SIDE_BACK") == 0)
			{ HitSideFlags f = component->getDamageOnSides(); f.set(HIT_SIDE_BACK); component->setDamageOnSides(f); }
		else if (strcmp(token, "HIT_SIDE_LEFT") == 0)
			{ HitSideFlags f = component->getDamageOnSides(); f.set(HIT_SIDE_LEFT); component->setDamageOnSides(f); }
		else if (strcmp(token, "HIT_SIDE_RIGHT") == 0)
			{ HitSideFlags f = component->getDamageOnSides(); f.set(HIT_SIDE_RIGHT); component->setDamageOnSides(f); }
		else if (strcmp(token, "HIT_SIDE_TOP") == 0)
			{ HitSideFlags f = component->getDamageOnSides(); f.set(HIT_SIDE_TOP); component->setDamageOnSides(f); }
		else if (strcmp(token, "HIT_SIDE_BOTTOM") == 0)
			{ HitSideFlags f = component->getDamageOnSides(); f.set(HIT_SIDE_BOTTOM); component->setDamageOnSides(f); }
		else
		{
			DEBUG_CRASH(("Unknown HitSide: %s", token));
			throw INI_INVALID_DATA;
		}
		
		token = ini->getNextTokenOrNull();
	}
}

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Static parse method for Component inheritance support
//-------------------------------------------------------------------------------------------------
void Component::parseComponent(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	// instance is actually ActiveBodyModuleData*
	ActiveBodyModuleData* moduleData = (ActiveBodyModuleData*)instance;
	
	// Create a new Component object
	
	
	// Get component name from the first token (e.g., "MainEngine", "Turret", etc.)
	AsciiString componentName = ini->getNextToken();
	if (componentName.isEmpty()) return;
	
	Component* component = new Component();
	// Set component name
	component->setName(componentName);
	MultiIniFieldParse p;
	Component::buildFieldParse(p);

	// Parse the component block using the field parse table
	ini->initFromINIMulti(component, p);
	
	// Add the parsed component to the module data
	moduleData->m_componentsData.push_back(component);
}

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Build field parse method for Component inheritance support
//-------------------------------------------------------------------------------------------------
void Component::buildFieldParse(MultiIniFieldParse& p)
{
	static const FieldParse componentFieldParse[] = {
		{ "MaxHealth", parseComponentMaxHealth, NULL, 0 },
		{ "InitialHealth", parseComponentInitialHealth, NULL, 0 },
		{ "HealingType", parseComponentHealingType, NULL, 0 },
		{ "DamageOnSides", parseComponentDamageOnSides, NULL, 0 },
		{ "ReplacementCost", INI::parseUnsignedInt, NULL, offsetof(Component, m_replacementCost) },
		{ "ForceReturnOnDestroy", INI::parseBool, NULL, offsetof(Component, m_forceReturnOnDestroy) },
		{ "DamagedStatusType", INI::parseIndexList, TheBodyDamageTypeNames, offsetof(Component, m_damagedDamageType) },
		{ "DestroyedStatusType", INI::parseIndexList, TheBodyDamageTypeNames, offsetof(Component, m_destroyedDamageType) },
		{ "MaxHealthValueType", INI::parseIndexList, TheValueTypeNames, offsetof(Component, m_maxHealthValueType) },
		{ "InitialHealthValueType", INI::parseIndexList, TheValueTypeNames, offsetof(Component, m_initialHealthValueType) },
		{ "PartiallyFunctionalIcon", INI::parseAsciiString, NULL, offsetof(Component, m_partiallyFunctionalIconName) },
		{ "DownedIcon", INI::parseAsciiString, NULL, offsetof(Component, m_downedIconName) },
		{ "UserDisabledIcon", INI::parseAsciiString, NULL, offsetof(Component, m_userDisabledIconName) },
		
		{ 0, 0, 0, 0 }
	};
	
	p.add(componentFieldParse);
}

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Component status and user control methods
//-------------------------------------------------------------------------------------------------
ComponentStatus Component::getStatus() const
{
	// Check if component is user disabled first
	if (m_userDisabled)
		return COMPONENT_STATUS_USER_DISABLED;
	
	// Check if component has no health defined
	if (m_currentMaxHealth <= 0.0f)
		return COMPONENT_STATUS_NONE;
	
	// Get current health percentage
	Real healthPercentage = (getCurrentHealth() / m_currentMaxHealth) * 100.0f;
	
	// Determine status based on health percentage
	if (healthPercentage >= 50.0f)
		return COMPONENT_STATUS_FULLY_FUNCTIONAL;
	else if (healthPercentage >= 10.0f)
		return COMPONENT_STATUS_PARTIALLY_FUNCTIONAL;
	else
		return COMPONENT_STATUS_DOWNED;
}

void Component::toggleDisabled()
{
	m_userDisabled = !m_userDisabled;
}

Bool Component::isUserDisabled() const
{
	return m_userDisabled;
}

void Component::setUserDisabled(Bool disabled)
{
	m_userDisabled = disabled;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Lazy loading helper for partially functional icon
//-------------------------------------------------------------------------------------------------
Anim2DTemplate* Component::getPartiallyFunctionalIcon() const
{
	// Lazy resolution: if not resolved yet, resolve it now
	if (m_partiallyFunctionalIcon == NULL && !m_partiallyFunctionalIconName.isEmpty() && TheAnim2DCollection)
	{
		// Need non-const access to resolve, so cast away const (safe here as we're just caching)
		Component* nonConstThis = const_cast<Component*>(this);
		nonConstThis->m_partiallyFunctionalIcon = TheAnim2DCollection->findTemplate(m_partiallyFunctionalIconName);
		if (nonConstThis->m_partiallyFunctionalIcon)
		{
			nonConstThis->m_partiallyFunctionalIconName = AsciiString(); // Clear name after successful resolution
		}
	}
	
	return m_partiallyFunctionalIcon;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Lazy loading helper for downed icon
//-------------------------------------------------------------------------------------------------
Anim2DTemplate* Component::getDownedIcon() const
{
	// Lazy resolution: if not resolved yet, resolve it now
	if (m_downedIcon == NULL && !m_downedIconName.isEmpty() && TheAnim2DCollection)
	{
		// Need non-const access to resolve, so cast away const (safe here as we're just caching)
		Component* nonConstThis = const_cast<Component*>(this);
		nonConstThis->m_downedIcon = TheAnim2DCollection->findTemplate(m_downedIconName);
		if (nonConstThis->m_downedIcon)
		{
			nonConstThis->m_downedIconName = AsciiString(); // Clear name after successful resolution
		}
	}
	
	return m_downedIcon;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Lazy loading helper for user disabled icon
//-------------------------------------------------------------------------------------------------
Anim2DTemplate* Component::getUserDisabledIcon() const
{
	// Lazy resolution: if not resolved yet, resolve it now
	if (m_userDisabledIcon == NULL && !m_userDisabledIconName.isEmpty() && TheAnim2DCollection)
	{
		// Need non-const access to resolve, so cast away const (safe here as we're just caching)
		Component* nonConstThis = const_cast<Component*>(this);
		nonConstThis->m_userDisabledIcon = TheAnim2DCollection->findTemplate(m_userDisabledIconName);
		if (nonConstThis->m_userDisabledIcon)
		{
			nonConstThis->m_userDisabledIconName = AsciiString(); // Clear name after successful resolution
		}
	}
	
	return m_userDisabledIcon;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Helper method to copy base Component members
//-------------------------------------------------------------------------------------------------
void Component::copyBaseComponentMembers(Component* dest) const
{
	if (!dest)
		return;
	
	dest->m_name = m_name;
	dest->m_maxHealth = m_maxHealth;
	dest->m_initialHealth = m_initialHealth;
	dest->m_healingType = m_healingType;
	dest->m_damageOnSides = m_damageOnSides;
	dest->m_replacementCost = m_replacementCost;
	dest->m_forceReturnOnDestroy = m_forceReturnOnDestroy;
	dest->m_maxHealthValueType = m_maxHealthValueType;
	dest->m_initialHealthValueType = m_initialHealthValueType;
	dest->m_damagedDamageType = m_damagedDamageType;
	dest->m_destroyedDamageType = m_destroyedDamageType;
	dest->m_currentHealth = m_currentHealth;
	dest->m_currentMaxHealth = m_currentMaxHealth;
	dest->m_partiallyFunctionalIconName = m_partiallyFunctionalIconName;
	dest->m_downedIconName = m_downedIconName;
	dest->m_userDisabledIconName = m_userDisabledIconName;
	dest->m_partiallyFunctionalIcon = m_partiallyFunctionalIcon;
	dest->m_downedIcon = m_downedIcon;
	dest->m_userDisabledIcon = m_userDisabledIcon;
	dest->setUserDisabled(isUserDisabled());
	dest->m_object = m_object; // Copy object reference
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Virtual clone method for polymorphic copying
//-------------------------------------------------------------------------------------------------
Component* Component::clone() const
{
	// Create a new Component with the same data
	Component* copy = new Component();
	copyBaseComponentMembers(copy);
	return copy;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Get icon template for component status (lazy loading)
//-------------------------------------------------------------------------------------------------
Anim2DTemplate* Component::getStatusIcon() const
{
	ComponentStatus status = getStatus();
	
	// Get the appropriate icon based on status (lazy loading handled in helper methods)
	switch (status)
	{
		case COMPONENT_STATUS_USER_DISABLED:
			return getUserDisabledIcon();
		case COMPONENT_STATUS_DOWNED:
			return getDownedIcon();
		case COMPONENT_STATUS_PARTIALLY_FUNCTIONAL:
			return getPartiallyFunctionalIcon();
		default:
			return NULL; // No icon for other statuses
	}
}

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Component health management methods
//-------------------------------------------------------------------------------------------------
Bool Component::setCurrentHealth(Real health)
{
	if (health < 0.0f) health = 0.0f;
	if (health > m_currentMaxHealth) health = m_currentMaxHealth;
	
	// TheSuperHackers @feature Ahmed Salah 15/01/2025 Check if component is transitioning to destroyed state
	Bool wasDestroyed = isDestroyed();
	
	m_currentHealth = health;
	
	// Call onComponentDestroyed if component just became destroyed (wasn't destroyed before, but is now)
	if (!wasDestroyed && isDestroyed())
	{
		onComponentDestroyed();
	}
	
	return true;
}

Bool Component::damage(Real damage)
{
	if (damage <= 0.0f) return false;
	
	Real newHealth = m_currentHealth - damage;
	return setCurrentHealth(newHealth);
}

Bool Component::heal(Real healing)
{
	if (healing <= 0.0f) return false;
	
	// Apply healing restrictions based on healing type
	Real newHealth = m_currentHealth + healing;
	Bool isDestroyed = (m_currentHealth <= 0.1f * m_currentMaxHealth); // 10% threshold for destroyed
	
	switch (m_healingType)
	{
		case COMPONENT_HEALING_NORMAL:
			// Can be healed from destroyed to max normally
			break;
			
		case COMPONENT_HEALING_PARTIAL_ONLY:
			// Can be healed if not destroyed to max normally
			if (isDestroyed)
				return false; // Cannot heal if destroyed
			break;
			
		case COMPONENT_HEALING_PARTIAL_DESTROYED:
			// Can be healed from destroyed to partially working normally, but to max needs replacement
			if (isDestroyed)
			{
				// Can only heal to 50% (partially working)
				Real partialHealth = 0.5f * m_currentMaxHealth;
				newHealth = min(newHealth, partialHealth);
			}
			break;
			
		case COMPONENT_HEALING_PARTIAL_LIMITED:
			// Can be healed if not destroyed to partially working normally, but to max needs replacement
			if (isDestroyed)
				return false; // Cannot heal if destroyed
			else
			{
				// Can only heal to 50% (partially working)
				Real partialHealth = 0.5f * m_currentMaxHealth;
				newHealth = min(newHealth, partialHealth);
			}
			break;
			
		case COMPONENT_HEALING_REPLACEMENT_ONLY:
			// Cannot be healed normally, needs replacement
			return false;
			
		default:
			break;
	}
	
	return setCurrentHealth(newHealth);
}

Bool Component::isDestroyed() const
{
	return m_currentHealth <= 0.0f;
}

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature Ahmed Salah 15/01/2025 Virtual callback when component is destroyed
//-------------------------------------------------------------------------------------------------
void Component::onComponentDestroyed()
{
	// Default implementation does nothing
	// Derived classes can override this to perform custom logic when component is destroyed
}

void Component::initializeHealth(Real mainObjectMaxHealth)
{
	// Calculate max health based on its value type
	if (m_maxHealthValueType == VALUE_TYPE_PERCENTAGE)
	{
		// Percentage: calculate as percentage of main object's max health
		m_currentMaxHealth = mainObjectMaxHealth * (m_maxHealth / 100.0f);
	}
	else
	{
		// For VALUE_TYPE_ABSOLUTE, use the value directly
		m_currentMaxHealth = m_maxHealth;
	}
	
	// Calculate initial health based on its value type
	Real initialHealthValue;
	if (m_initialHealthValueType == VALUE_TYPE_PERCENTAGE)
	{
		// Percentage: calculate as percentage of main object's max health
		initialHealthValue = mainObjectMaxHealth * (m_initialHealth / 100.0f);
	}
	else
	{
		// For VALUE_TYPE_ABSOLUTE, use the value directly
		initialHealthValue = m_initialHealth;
	}
	
	// Set initial health
	m_currentHealth = initialHealthValue;
	if (m_currentHealth > m_currentMaxHealth) m_currentHealth = m_currentMaxHealth;
	if (m_currentHealth < 0.0f) m_currentHealth = 0.0f;
}

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature Ahmed Salah 15/01/2025 Determine component-specific damage state by health ratio
//-------------------------------------------------------------------------------------------------
BodyDamageType Component::calcDamageState(Real componentHealth, Real componentMaxHealth) const
{
    if (componentMaxHealth <= 0.0f)
        return BODY_PRISTINE; // No component defined

    const Real ratio = componentHealth / componentMaxHealth;

    // Consider destroyed if health <= 10%
    if (ratio <= 0.1f)
        return m_destroyedDamageType;

    // Consider damaged if health <= 99% but > 10%
    if (ratio <= 0.99f)
        return m_damagedDamageType;

    return BODY_PRISTINE;
}

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature Ahmed Salah 15/01/2025 Aggregate Jamming helpers
//-------------------------------------------------------------------------------------------------
Real Component::getTotalComponentJammingDamageCap(const std::vector<Component>& components)
{
    Real totalCap = 0.0f;
    for (std::vector<Component>::const_iterator it = components.begin(); it != components.end(); ++it)
    {
        const ElectronicsComponent* ec = dynamic_cast<const ElectronicsComponent*>(&(*it));
        if (ec)
        {
            Real cap = ec->getJammingDamageCap();
            if (cap > 0.0f)
            {
                totalCap += cap;
            }
        }
    }
    return totalCap;
}

Real Component::getEffectiveJammingDamageCap(Real globalCap, const std::vector<Component>& components)
{
    const Real componentCap = getTotalComponentJammingDamageCap(components);
    if (globalCap > 0.0f && componentCap > 0.0f)
    {
        return min(globalCap, componentCap);
    }
    else if (globalCap > 0.0f)
    {
        return globalCap;
    }
    else if (componentCap > 0.0f)
    {
        return componentCap;
    }
    return 0.0f;
}

UnsignedInt Component::getFastestComponentJammingHealRate(const std::vector<Component>& components, UnsignedInt globalRate)
{
    UnsignedInt fastestRate = 0;
    for (std::vector<Component>::const_iterator it = components.begin(); it != components.end(); ++it)
    {
        const ElectronicsComponent* ec = dynamic_cast<const ElectronicsComponent*>(&(*it));
        if (ec)
        {
            UnsignedInt rate = ec->getJammingDamageHealRate();
            if (rate > 0)
            {
                if (fastestRate == 0 || rate < fastestRate)
                {
                    fastestRate = rate;
                }
            }
        }
    }
    return fastestRate == 0 ? globalRate : fastestRate;
}

Real Component::getTotalComponentJammingHealAmount(const std::vector<Component>& components, Real globalAmount)
{
    Real totalAmount = 0.0f;
    for (std::vector<Component>::const_iterator it = components.begin(); it != components.end(); ++it)
    {
        const ElectronicsComponent* ec = dynamic_cast<const ElectronicsComponent*>(&(*it));
        if (ec)
        {
            Real amt = ec->getJammingDamageHealAmount();
            if (amt > 0.0f)
            {
                totalAmount += amt;
            }
        }
    }
    return totalAmount <= 0.0f ? globalAmount : totalAmount;
}

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature Ahmed Salah 31/10/2025 Component save/load/CRC hooks
//-------------------------------------------------------------------------------------------------
void Component::crc( Xfer *xfer )
{
	// Include a marker and key fields so CRC changes when state/config changes
	AsciiString marker = "MARKER:Component";
	xfer->xferAsciiString(&marker);
	xfer->xferAsciiString(const_cast<AsciiString*>(&m_name));

	// Runtime state
	xfer->xferReal(&m_currentHealth);
	xfer->xferReal(&m_currentMaxHealth);
	// User toggles influence behavior
	xfer->xferBool(&m_userDisabled);

	// Config affecting behavior (keep CRC stable across save/load)
	xfer->xferUser(&m_healingType, sizeof(ComponentHealingType));
	xfer->xferUser(&m_damagedDamageType, sizeof(BodyDamageType));
	xfer->xferUser(&m_destroyedDamageType, sizeof(BodyDamageType));
}

void Component::xfer( Xfer *xfer )
{
	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion(&version, currentVersion);

	// Store minimal runtime state; config is owned by INI
	xfer->xferAsciiString(&m_name);
	xfer->xferReal(&m_currentHealth);
	xfer->xferReal(&m_currentMaxHealth);
	xfer->xferBool(&m_userDisabled);
}

void Component::loadPostProcess( void )
{
	// No pointer fixups needed currently
}
