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

// FILE: BodyModule.h /////////////////////////////////////////////////////////////////////////////////
// Author: Colin Day, September 2001
// Desc:
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Common/Module.h"
#include "GameLogic/Damage.h"
#include "GameLogic/ArmorSet.h"
#include "GameLogic/Module/BehaviorModule.h"
#include "Common/UnicodeString.h"
#include "GameLogic/Components/Component.h"
#include <map>
#include <type_traits>

//-------------------------------------------------------------------------------------------------
/** OBJECT BODY MODULE base class */
//-------------------------------------------------------------------------------------------------

class WeaponTemplate;

//-------------------------------------------------------------------------------------------------
/** Damage states for structures
	*
	* NOTE: the macros below for IS_CONDITION_WORSE and IS_CONDITION_BETTER depend on this
	* enumeration being in sequential order
	*/
//-------------------------------------------------------------------------------------------------
enum BodyDamageType CPP_11(: Int)
{
	BODY_PRISTINE,				///< unit should appear in pristine condition
	BODY_DAMAGED,					///< unit has been damaged
	BODY_REALLYDAMAGED,		///< unit is extremely damaged / nearly destroyed
	BODY_RUBBLE,					///< unit has been reduced to rubble/corpse/exploded-hulk, etc
	
	// TheSuperHackers @feature author 15/01/2025 Component-specific damage states
	BODY_COMPONENT_ENGINE_DESTROYED,	///< engine component has been destroyed
	BODY_COMPONENT_ENGINE_DAMAGED,	///< engine component has been damaged
	BODY_COMPONENT_TURRET_DESTROYED,	///< turret component has been destroyed
	BODY_COMPONENT_TURRET_DAMAGED,	///< turret component has been damaged
	
	// TheSuperHackers @feature author 15/01/2025 Specific weapon slot damage states
	BODY_COMPONENT_WEAPON_A_DESTROYED,	///< weapon slot A component has been destroyed
	BODY_COMPONENT_WEAPON_B_DESTROYED,	///< weapon slot B component has been destroyed
	BODY_COMPONENT_WEAPON_C_DESTROYED,	///< weapon slot C component has been destroyed
	BODY_COMPONENT_WEAPON_D_DESTROYED,	///< weapon slot D component has been destroyed
	BODY_COMPONENT_WEAPON_E_DESTROYED,	///< weapon slot E component has been destroyed
	BODY_COMPONENT_WEAPON_F_DESTROYED,	///< weapon slot F component has been destroyed
	BODY_COMPONENT_WEAPON_G_DESTROYED,	///< weapon slot G component has been destroyed
	BODY_COMPONENT_WEAPON_H_DESTROYED,	///< weapon slot H component has been destroyed

	BODY_COMPONENT_WEAPON_A_DAMAGED,	///< weapon slot A component has been damaged
	BODY_COMPONENT_WEAPON_B_DAMAGED,	///< weapon slot B component has been damaged
	BODY_COMPONENT_WEAPON_C_DAMAGED,	///< weapon slot C component has been damaged
	BODY_COMPONENT_WEAPON_D_DAMAGED,	///< weapon slot D component has been damaged
	BODY_COMPONENT_WEAPON_E_DAMAGED,	///< weapon slot E component has been damaged
	BODY_COMPONENT_WEAPON_F_DAMAGED,	///< weapon slot F component has been damaged
	BODY_COMPONENT_WEAPON_G_DAMAGED,	///< weapon slot G component has been damaged
	BODY_COMPONENT_WEAPON_H_DAMAGED,	///< weapon slot H component has been damaged

	BODY_COMPONENT_A_DESTROYED,	///< Component A component has been destroyed
	BODY_COMPONENT_B_DESTROYED,	///< Component B component has been destroyed
	BODY_COMPONENT_C_DESTROYED,	///< Component C component has been destroyed
	BODY_COMPONENT_D_DESTROYED,	///< Component D component has been destroyed
	BODY_COMPONENT_E_DESTROYED,	///< Component E component has been destroyed
	BODY_COMPONENT_F_DESTROYED,	///< Component F component has been destroyed
	BODY_COMPONENT_G_DESTROYED,	///< Component G component has been destroyed
	BODY_COMPONENT_H_DESTROYED,	///< Component H component has been destroyed

	BODY_COMPONENT_A_DAMAGED,	///< Component A component has been damaged
	BODY_COMPONENT_B_DAMAGED,	///< Component B component has been damaged
	BODY_COMPONENT_C_DAMAGED,	///< Component C component has been damaged
	BODY_COMPONENT_D_DAMAGED,	///< Component D component has been damaged
	BODY_COMPONENT_E_DAMAGED,	///< Component E component has been damaged
	BODY_COMPONENT_F_DAMAGED,	///< Component F component has been damaged
	BODY_COMPONENT_G_DAMAGED,	///< Component G component has been damaged
	BODY_COMPONENT_H_DAMAGED,	///< Component H component has been damaged


	BODYDAMAGETYPE_COUNT
};

#ifdef DEFINE_BODYDAMAGETYPE_NAMES
static const char* const TheBodyDamageTypeNames[] =
{
	"PRISTINE",
	"DAMAGED",
	"REALLYDAMAGED",
	"RUBBLE",


	"COMPONENT_ENGINE_DESTROYED",
	"COMPONENT_ENGINE_DAMAGED",
	"COMPONENT_TURRET_DESTROYED",
	"COMPONENT_TURRET_DAMAGED",

	"COMPONENT_WEAPON_A_DESTROYED",
	"COMPONENT_WEAPON_B_DESTROYED",
	"COMPONENT_WEAPON_C_DESTROYED",
	"COMPONENT_WEAPON_D_DESTROYED",
	"COMPONENT_WEAPON_E_DESTROYED",
	"COMPONENT_WEAPON_F_DESTROYED",
	"COMPONENT_WEAPON_G_DESTROYED",
	"COMPONENT_WEAPON_H_DESTROYED",

	"COMPONENT_WEAPON_A_DAMAGED",
	"COMPONENT_WEAPON_B_DAMAGED",
	"COMPONENT_WEAPON_C_DAMAGED",
	"COMPONENT_WEAPON_D_DAMAGED",
	"COMPONENT_WEAPON_E_DAMAGED",
	"COMPONENT_WEAPON_F_DAMAGED",
	"COMPONENT_WEAPON_G_DAMAGED",
	"COMPONENT_WEAPON_H_DAMAGED",

	"COMPONENT_A_DESTROYED",
	"COMPONENT_B_DESTROYED",
	"COMPONENT_C_DESTROYED",
	"COMPONENT_D_DESTROYED",
	"COMPONENT_E_DESTROYED",
	"COMPONENT_F_DESTROYED",
	"COMPONENT_G_DESTROYED",
	"COMPONENT_H_DESTROYED",

	"COMPONENT_A_DAMAGED",
	"COMPONENT_B_DAMAGED",
	"COMPONENT_C_DAMAGED",
	"COMPONENT_D_DAMAGED",
	"COMPONENT_E_DAMAGED",
	"COMPONENT_F_DAMAGED",
	"COMPONENT_G_DAMAGED",
	"COMPONENT_H_DAMAGED",

	NULL
};
static_assert(ARRAY_SIZE(TheBodyDamageTypeNames) == BODYDAMAGETYPE_COUNT + 1, "Incorrect array size");
#endif

enum MaxHealthChangeType CPP_11(: Int)
{
	SAME_CURRENTHEALTH,
	PRESERVE_RATIO,
	ADD_CURRENT_HEALTH_TOO,
	FULLY_HEAL,

	MAX_HEALTH_CHANGE_COUNT
};

#ifdef DEFINE_MAXHEALTHCHANGETYPE_NAMES
static const char* const TheMaxHealthChangeTypeNames[] =
{
	"SAME_CURRENTHEALTH",
	"PRESERVE_RATIO",
	"ADD_CURRENT_HEALTH_TOO",
	"FULLY_HEAL",
	NULL
};
static_assert(ARRAY_SIZE(TheMaxHealthChangeTypeNames) == MAX_HEALTH_CHANGE_COUNT + 1, "Incorrect array size");
#endif


//
// is condition A worse than condition B  ... NOTE: this assumes the conditions
// in BodyDamageType are in sequential order
//
// is a worse than b
#define IS_CONDITION_WORSE( a, b ) ( a > b )
// is a better than b
#define IS_CONDITION_BETTER( a, b ) ( a < b )

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
class BodyModuleData : public BehaviorModuleData
{
public:
	BodyModuleData()
	{
	}

	static void buildFieldParse(MultiIniFieldParse& p)
	{
    BehaviorModuleData::buildFieldParse(p);
	}

	// TheSuperHackers @feature author 01/01/2025 Override getModuleDescription for UI display
	virtual UnicodeString getModuleDescription() const;

	// TheSuperHackers @feature author 01/01/2025 Override getModuleOrder for display ordering
	virtual Int getModuleOrder() const { return 250; } // Third priority - shows after ActiveBody
};

//-------------------------------------------------------------------------------------------------
class BodyModuleInterface
{
public:
	/**
		Try to damage this Object. The module's Armor
		will be taken into account, so the actual damage done may vary
		considerably from what you requested. Also note that (if damage is done)
		the DamageFX will be invoked to provide a/v fx as appropriate.
	*/
	virtual void attemptDamage( DamageInfo *damageInfo ) = 0;

	/**
		Instead of having negative damage count as healing, or allowing access to the private
		changeHealth Method, we will use this parallel to attemptDamage to do healing without hack.
	*/
	virtual void attemptHealing( DamageInfo *healingInfo ) = 0;

	/**
		Estimate the (unclipped) damage that would be done to this object
		by the given damage (taking bonuses, armor, etc into account),
		but DO NOT alter the body in any way. (This is used by the AI system
		to choose weapons.)
	*/
	virtual Real estimateDamage( DamageInfoInput& damageInfo ) const = 0;

	virtual Real getHealth() const = 0;													///< get current health

	virtual Real getMaxHealth() const = 0;

	virtual Real getInitialHealth() const = 0;

	virtual Real getPreviousHealth() const = 0;

	virtual UnsignedInt getSubdualDamageHealRate() const = 0;
	virtual Real getSubdualDamageHealAmount() const = 0;
	virtual Bool hasAnySubdualDamage() const = 0;
	virtual Real getCurrentSubdualDamageAmount() const = 0;

	virtual UnsignedInt getJammingDamageHealRate() const = 0;
	virtual Real getJammingDamageHealAmount() const = 0;
	virtual Bool hasAnyJammingDamage() const = 0;
	virtual Real getCurrentJammingDamageAmount() const = 0;

	// TheSuperHackers @feature Ahmed Salah 15/01/2025 Component health management
	virtual void initializeComponentHealth() = 0;
	
	// TheSuperHackers @feature author 15/01/2025 Get component definitions
	virtual std::vector<Component> getComponents() const = 0;
	
	// TheSuperHackers @feature author 15/01/2025 Get icon to draw for component status
	// Iterates through components internally and returns the next component's status icon found (NULL when no more)
	virtual Anim2D* getComponentStatusIcon() const = 0;
	
	// TheSuperHackers @feature author 15/01/2025 Generic component getter method
	template<typename TComponent>
	TComponent* GetComponent(const AsciiString& componentName) const;
	
	// TheSuperHackers @feature Ahmed Salah 15/01/2025 User component toggle methods


	// TheSuperHackers @feature author 15/01/2025 Update visual damage state based on component health
	virtual void setCorrectDamageState() = 0;

	virtual BodyDamageType getDamageState() const = 0;
	virtual void setDamageState( BodyDamageType newState ) = 0;	///< control damage state directly.  Will adjust hitpoints.
	virtual void setAflame( Bool setting ) = 0;///< This is a major change like a damage state.

	virtual void onVeterancyLevelChanged( VeterancyLevel oldLevel, VeterancyLevel newLevel, Bool provideFeedback ) = 0;	///< I just achieved this level right this moment

	virtual void setArmorSetFlag(ArmorSetType ast) = 0;
	virtual void clearArmorSetFlag(ArmorSetType ast) = 0;
	virtual Bool testArmorSetFlag(ArmorSetType ast) = 0;

	virtual const DamageInfo *getLastDamageInfo() const = 0;
	virtual UnsignedInt getLastDamageTimestamp() const = 0;
	virtual UnsignedInt getLastHealingTimestamp() const = 0;
	virtual ObjectID getClearableLastAttacker() const = 0;
	virtual void clearLastAttacker() = 0;
	virtual Bool getFrontCrushed() const = 0;
	virtual Bool getBackCrushed() const = 0;

	virtual void setInitialHealth(Int initialPercent)  = 0;
	virtual void setMaxHealth( Real maxHealth, MaxHealthChangeType healthChangeType = SAME_CURRENTHEALTH )  = 0;

	virtual void setFrontCrushed(Bool v) = 0;
	virtual void setBackCrushed(Bool v) = 0;

	virtual void applyDamageScalar( Real scalar ) = 0;
	virtual Real getDamageScalar() const = 0;

	/**
		Change the module's health by the given delta. Note that
		the module's DamageFX and Armor are NOT taken into
		account, so you should think about what you're bypassing when you
		call this directly (especially when when decreasing health, since
		you probably want "attemptDamage" or "attemptHealing")
	*/
	virtual void internalChangeHealth( Real delta ) = 0;

	virtual void setIndestructible( Bool indestructible ) = 0;
	virtual Bool isIndestructible( void ) const = 0;

	virtual void evaluateVisualCondition() = 0;
	virtual void updateBodyParticleSystems() = 0; // made public for topple and building collapse updates -ML

};

//-------------------------------------------------------------------------------------------------
class BodyModule : public BehaviorModule, public BodyModuleInterface
{

	MEMORY_POOL_GLUE_ABC( BodyModule )

public:

	BodyModule( Thing *thing, const ModuleData* moduleData );
	// virtual destructor prototype defined by MemoryPoolObject

	static Int getInterfaceMask() { return MODULEINTERFACE_BODY; }

	// BehaviorModule
	virtual BodyModuleInterface* getBody() { return this; }

	/**
		Try to damage this Object. The module's Armor
		will be taken into account, so the actual damage done may vary
		considerably from what you requested. Also note that (if damage is done)
		the DamageFX will be invoked to provide a/v fx as appropriate.
	*/
	virtual void attemptDamage( DamageInfo *damageInfo ) = 0;

	/**
		Instead of having negative damage count as healing, or allowing access to the private
		changeHealth Method, we will use this parallel to attemptDamage to do healing without hack.
	*/
	virtual void attemptHealing( DamageInfo *healingInfo ) = 0;

	/**
		Estimate the (unclipped) damage that would be done to this object
		by the given damage (taking bonuses, armor, etc into account),
		but DO NOT alter the body in any way. (This is used by the AI system
		to choose weapons.)
	*/
	virtual Real estimateDamage( DamageInfoInput& damageInfo ) const = 0;

	virtual Real getHealth() const = 0;													///< get current health

	virtual Real getMaxHealth() const {return 0.0f;}  ///< return max health
	virtual Real getPreviousHealth() const { return 0.0f; } ///< return previous health

	virtual UnsignedInt getSubdualDamageHealRate() const {return 0;}
	virtual Real getSubdualDamageHealAmount() const {return 0.0f;}
	virtual Bool hasAnySubdualDamage() const{return FALSE;}
	virtual Real getCurrentSubdualDamageAmount() const { return 0.0f; }

	virtual UnsignedInt getJammingDamageHealRate() const { return 0; }
	virtual Real getJammingDamageHealAmount() const { return 0.0f; }
	virtual Bool hasAnyJammingDamage() const { return FALSE; }
	virtual Real getCurrentJammingDamageAmount() const { return 0.0f; }

	// TheSuperHackers @feature Ahmed Salah 15/01/2025 Component health management - default implementations
	virtual void initializeComponentHealth() { }
	
	// TheSuperHackers @feature author 15/01/2025 Get component definitions - must be implemented by derived classes
	virtual std::vector<Component> getComponents() const = 0;
	
	// TheSuperHackers @feature author 15/01/2025 Get icon to draw for component status - default implementation returns NULL
	virtual Anim2D* getComponentStatusIcon() const { return NULL; }

	// TheSuperHackers @feature author 15/01/2025 Update visual damage state based on component health - default implementation
	virtual void setCorrectDamageState() { }

	virtual Real getInitialHealth() const {return 0.0f;}  // return initial health

	virtual BodyDamageType getDamageState() const = 0;
	virtual void setDamageState( BodyDamageType newState ) = 0;	///< control damage state directly.  Will adjust hitpoints.
	virtual void setAflame( Bool setting ) = 0;///< This is a major change like a damage state.

	virtual void onVeterancyLevelChanged( VeterancyLevel oldLevel, VeterancyLevel newLevel, Bool provideFeedback = FALSE ) = 0;	///< I just achieved this level right this moment

	virtual void setArmorSetFlag(ArmorSetType ast) = 0;
	virtual void clearArmorSetFlag(ArmorSetType ast) = 0;
	virtual Bool testArmorSetFlag(ArmorSetType ast) = 0;

	virtual const DamageInfo *getLastDamageInfo() const { return NULL; }	///< return info on last damage dealt to this object
	virtual UnsignedInt getLastDamageTimestamp() const { return 0; }	///< return frame of last damage dealt
	virtual UnsignedInt getLastHealingTimestamp() const { return 0; }	///< return frame of last healing dealt
	virtual ObjectID getClearableLastAttacker() const { return INVALID_ID; }
	virtual void clearLastAttacker() { }
	virtual Bool getFrontCrushed() const { return false; }
	virtual Bool getBackCrushed() const { return false; }

	virtual void setInitialHealth(Int initialPercent)  {  } ///< Sets the inital load health %.
	virtual void setMaxHealth(Real maxHealth, MaxHealthChangeType healthChangeType = SAME_CURRENTHEALTH )  {  } ///< Sets the max health.

	virtual void setFrontCrushed(Bool v) { DEBUG_CRASH(("you should never call this for generic Bodys")); }
	virtual void setBackCrushed(Bool v) { DEBUG_CRASH(("you should never call this for generic Bodys")); }


	virtual void setIndestructible( Bool indestructible ) { }
	virtual Bool isIndestructible( void ) const { return TRUE; }

	//Allows outside systems to apply defensive bonuses or penalties (they all stack as a multiplier!)
	virtual void applyDamageScalar( Real scalar ) { m_damageScalar *= scalar; }
	virtual Real getDamageScalar() const { return m_damageScalar; }

	/**
		Change the module's health by the given delta. Note that
		the module's DamageFX and Armor are NOT taken into
		account, so you should think about what you're bypassing when you
		call this directly (especially when when decreasing health, since
		you probably want "attemptDamage" or "attemptHealing")
	*/
	virtual void internalChangeHealth( Real delta ) = 0;

	virtual void evaluateVisualCondition() { }
	virtual void updateBodyParticleSystems() { };// made public for topple anf building collapse updates -ML

	// TheSuperHackers @feature author 15/01/2025 Basic component name constants
	// static const AsciiString COMPONENT_ENGINE;
	// static const AsciiString COMPONENT_WHEELS;
	// static const AsciiString COMPONENT_TRACKS;
	// static const AsciiString COMPONENT_FUEL_TANK;
	// static const AsciiString COMPONENT_TURRET_A;
	// static const AsciiString COMPONENT_TURRET_B;
	// static const AsciiString COMPONENT_TURRET_C;
	// static const AsciiString COMPONENT_PRIMARY_WEAPON;
	// static const AsciiString COMPONENT_SECONDARY_WEAPON;
	// static const AsciiString COMPONENT_TERTIARY_WEAPON;
	// static const AsciiString COMPONENT_WEAPON_FOUR;
	// static const AsciiString COMPONENT_WEAPON_FIVE;
	// static const AsciiString COMPONENT_WEAPON_SIX;
	// static const AsciiString COMPONENT_WEAPON_SEVEN;
	// static const AsciiString COMPONENT_WEAPON_EIGHT;
	// static const AsciiString COMPONENT_RADAR;
	// static const AsciiString COMPONENT_VISION;
	// static const AsciiString COMPONENT_ELECTRONICS;
	// static const AsciiString COMPONENT_POWER;
	// static const AsciiString COMPONENT_COMMUNICATION_A;
	// static const AsciiString COMPONENT_COMMUNICATION_B;

	// TheSuperHackers @feature Ahmed Salah 15/01/2025 Default component toggle implementations
	void toggleComponentDisabled(const AsciiString& componentName);
	Bool isComponentUserDisabled(const AsciiString& componentName) const;
	void setComponentUserDisabled(const AsciiString& componentName, Bool disabled);

protected:

	// snapshot methods
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess( void );

	Real	m_damageScalar;

};
inline BodyModule::BodyModule( Thing *thing, const ModuleData* moduleData ) : BehaviorModule( thing, moduleData ), m_damageScalar(1.0f) { }
inline BodyModule::~BodyModule() { }
