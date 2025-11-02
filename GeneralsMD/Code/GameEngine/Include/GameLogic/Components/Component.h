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

// Component.h ///////////////////////////////////////////////////////////////////
// Component health system for detailed damage modeling
// Author: TheSuperHackers
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "Lib/BaseType.h"
#include "Common/AsciiString.h"
#include "Common/GameType.h"
#include "GameLogic/ArmorSet.h"
#include "GameLogic/Damage.h"
#include "Common/INI.h"
class Xfer;
class Anim2DTemplate;
class Anim2D;
#include <map>
#include <vector>

// Forward declaration to match definition in BodyModule.h
enum BodyDamageType CPP_11(: Int);


// TheSuperHackers @feature author 15/01/2025 Component functionality status
enum ComponentStatus
{
	COMPONENT_STATUS_NONE = 0,           // Component does not exist
	COMPONENT_STATUS_FULLY_FUNCTIONAL,   // 50% - 100% health
	COMPONENT_STATUS_PARTIALLY_FUNCTIONAL, // 10% - 50% health  
	COMPONENT_STATUS_DOWNED,             // 0% - 10% health
	COMPONENT_STATUS_USER_DISABLED       // User disabled component
};
//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Component healing behavior types
//-------------------------------------------------------------------------------------------------
enum ComponentHealingType CPP_11(: Int)
{
	COMPONENT_HEALING_NORMAL,					///< Can be healed from destroyed to max normally
	COMPONENT_HEALING_PARTIAL_ONLY,				///< Can be healed if not destroyed to max normally
	COMPONENT_HEALING_PARTIAL_DESTROYED,		///< Can be healed from destroyed to partially working normally, but to max needs replacement
	COMPONENT_HEALING_PARTIAL_LIMITED,			///< Can be healed if not destroyed to partially working normally, but to max needs replacement
	COMPONENT_HEALING_REPLACEMENT_ONLY,		///< Cannot be healed normally, needs replacement
	
	COMPONENT_HEALING_COUNT
};

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Component health system for detailed damage modeling
//-------------------------------------------------------------------------------------------------
class Component
{
public:
	virtual ~Component() {}

protected:
	AsciiString m_name;						///< Component name (Engine, Turret, Wheels, Gun, etc.)
	Real m_maxHealth;						///< Maximum health for this component
	Real m_initialHealth;					///< Initial health for this component
	ComponentHealingType m_healingType;		///< How this component can be healed
	HitSideFlags m_damageOnSides;				///< Which hit sides can damage this component (empty = all sides)
	UnsignedInt m_replacementCost;			///< Cost to replace this component (0 = cannot be replaced)
	Bool m_forceReturnOnDestroy;				///< Force jet to return to parking when this component is destroyed
	ValueType m_maxHealthValueType;			///< How maxHealth is calculated (absolute or percentage of main object health)
	ValueType m_initialHealthValueType;		///< How initialHealth is calculated (absolute or percentage of main object health)
	BodyDamageType m_damagedDamageType;		///< Damage state to return when damaged (10% - 50% health)
	BodyDamageType m_destroyedDamageType; 		///< Damage state to return when destroyed

	// Runtime component health tracking
	Real m_currentHealth;						///< Current health of this component
	Real m_currentMaxHealth;					///< Current maximum health of this component (calculated from maxHealth)
	Bool m_userDisabled;

	// TheSuperHackers @feature author 15/01/2025 Component status icons
	AsciiString m_partiallyFunctionalIconName;	///< Animation icon template name for partially functional status (resolved lazily)
	AsciiString m_downedIconName;				///< Animation icon template name for downed status (resolved lazily)
	AsciiString m_userDisabledIconName;			///< Animation icon template name for user disabled status (resolved lazily)
	Anim2DTemplate* m_partiallyFunctionalIcon;	///< Animation icon template for partially functional status (lazy loaded)
	Anim2DTemplate* m_downedIcon;				///< Animation icon template for downed status (lazy loaded)
	Anim2DTemplate* m_userDisabledIcon;			///< Animation icon template for user disabled status (lazy loaded)
	

public:
	Component() : m_maxHealth(0.0f), m_initialHealth(0.0f), m_healingType(COMPONENT_HEALING_NORMAL), m_damageOnSides(), m_replacementCost(0), m_forceReturnOnDestroy(FALSE), m_maxHealthValueType(VALUE_TYPE_ABSOLUTE), m_initialHealthValueType(VALUE_TYPE_ABSOLUTE), m_damagedDamageType((BodyDamageType)0), m_destroyedDamageType((BodyDamageType)0), m_currentHealth(0.0f), m_currentMaxHealth(0.0f), m_partiallyFunctionalIcon(NULL), m_downedIcon(NULL), m_userDisabledIcon(NULL), m_userDisabled(FALSE) {}

	// Accessors for configuration/state
	const AsciiString& getName() const { return m_name; }
	void setName(const AsciiString& n) { m_name = n; }
	Real getMaxHealthConfig() const { return m_maxHealth; }
	void setMaxHealthConfig(Real v) { m_maxHealth = v; }
	ValueType getMaxHealthValueType() const { return m_maxHealthValueType; }
	void setMaxHealthValueType(ValueType t) { m_maxHealthValueType = t; }
	Real getInitialHealthConfig() const { return m_initialHealth; }
	void setInitialHealthConfig(Real v) { m_initialHealth = v; }
	ValueType getInitialHealthValueType() const { return m_initialHealthValueType; }
	void setInitialHealthValueType(ValueType t) { m_initialHealthValueType = t; }
	ComponentHealingType getHealingType() const { return m_healingType; }
	void setHealingType(ComponentHealingType t) { m_healingType = t; }
	HitSideFlags getDamageOnSides() const { return m_damageOnSides; }
	void setDamageOnSides(const HitSideFlags& f) { m_damageOnSides = f; }
	UnsignedInt getReplacementCost() const { return m_replacementCost; }
	void setReplacementCost(UnsignedInt c) { m_replacementCost = c; }
	Bool getForceReturnOnDestroy() const { return m_forceReturnOnDestroy; }
	void setForceReturnOnDestroy(Bool b) { m_forceReturnOnDestroy = b; }
	BodyDamageType getDamagedDamageType() const { return m_damagedDamageType; }
	void setDamagedDamageType(BodyDamageType t) { m_damagedDamageType = t; }
	BodyDamageType getDestroyedDamageType() const { return m_destroyedDamageType; }
	void setDestroyedDamageType(BodyDamageType t) { m_destroyedDamageType = t; }
	
	// TheSuperHackers @feature author 15/01/2025 Static parse method for Component inheritance support
	static void parseComponent(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	
	// TheSuperHackers @feature author 15/01/2025 Build field parse method for Component inheritance support
	static void buildFieldParse(MultiIniFieldParse& p);
	
	// TheSuperHackers @feature author 15/01/2025 Component status and user control methods
	ComponentStatus getStatus() const;
	void toggleDisabled();
	Bool isUserDisabled() const;
	void setUserDisabled(Bool disabled);
	
	// TheSuperHackers @feature author 15/01/2025 Component health management methods
	Real getCurrentHealth() const { return m_currentHealth; }
	Real getCurrentMaxHealth() const { return m_currentMaxHealth; }
	Bool setCurrentHealth(Real health);
	Bool damage(Real damage);
	Bool heal(Real healing);
	Bool isDestroyed() const;
	void initializeHealth(Real mainObjectMaxHealth);
	
	// TheSuperHackers @feature Ahmed Salah 15/01/2025 Determine component-specific damage state by health ratio
	BodyDamageType calcDamageState(Real componentHealth, Real componentMaxHealth) const;
	
	// TheSuperHackers @feature author 15/01/2025 Get icon template for component status (lazy loading)
	Anim2DTemplate* getStatusIcon() const;
	
	// TheSuperHackers @feature author 15/01/2025 Lazy loading helper methods for icon templates
	Anim2DTemplate* getPartiallyFunctionalIcon() const;
	Anim2DTemplate* getDownedIcon() const;
	Anim2DTemplate* getUserDisabledIcon() const;

	// TheSuperHackers @feature author 15/01/2025 Virtual clone method for polymorphic copying
	virtual Component* clone() const;
	
	// TheSuperHackers @feature author 15/01/2025 Helper method to copy base Component members to another Component instance
	// Used by derived classes in their clone() implementations to avoid code duplication
	void copyBaseComponentMembers(Component* dest) const;
	
	// TheSuperHackers @feature Ahmed Salah 31/10/2025 Component save/load/CRC hooks
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess( void );

	// TheSuperHackers @feature Ahmed Salah 15/01/2025 Aggregate Jamming helpers (operate on lists of components)
	static Real getTotalComponentJammingDamageCap(const std::vector<Component>& components);
	static Real getEffectiveJammingDamageCap(Real globalCap, const std::vector<Component>& components);
	static UnsignedInt getFastestComponentJammingHealRate(const std::vector<Component>& components, UnsignedInt globalRate);
  static Real getTotalComponentJammingHealAmount(const std::vector<Component>& components, Real globalAmount);

};

#endif
