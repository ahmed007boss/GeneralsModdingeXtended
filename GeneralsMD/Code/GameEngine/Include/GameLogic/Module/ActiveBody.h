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

// FILE: ActiveBody.h /////////////////////////////////////////////////////////////////////////////
// Author: Colin Day, November 2001
// Desc:   Active bodies have health, they can die and are affected by health
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "Common/DamageFX.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Damage.h"
#include "GameLogic/Armor.h"
#include "GameLogic/Components/Component.h"
#include <set>
#include "GameLogic/ArmorSet.h"
#include "Common/UnicodeString.h"
#include <map>
#include <type_traits>

// FORWARD REFERENCES /////////////////////////////////////////////////////////////////////////////
class BodyParticleSystem;
class ParticleSystemTemplate;

//-------------------------------------------------------------------------------------------------
/** Active body module */
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
class ActiveBodyModuleData : public BodyModuleData
{
public:
	Real m_maxHealth;
	Real m_initialHealth;

	Real m_subdualDamageCap;								///< Subdual damage will never accumulate past this
	UnsignedInt m_subdualDamageHealRate;		///< Every this often, we drop subdual damage...
	Real m_subdualDamageHealAmount;					///< by this much.

	Real m_jammingDamageCap;								///< Subdual damage will never accumulate past this
	UnsignedInt m_jammingDamageHealRate;		///< Every this often, we drop subdual damage...
	Real m_jammingDamageHealAmount;					///< by this much.

	// TheSuperHackers @feature Ahmed Salah 30/10/2025 Jamming capability flags parsed from INI
	Bool m_canBeJammedByDirectJammers;
	Bool m_canBeJammedByAreaJammers;

	std::vector<Component*> m_componentsData;		///< TheSuperHackers @feature author 15/01/2025 Template component data (copied to instances on construction)

	ActiveBodyModuleData();
	virtual ~ActiveBodyModuleData();

	static void buildFieldParse(MultiIniFieldParse& p);

	// TheSuperHackers @feature author 01/01/2025 Override getModuleDescription for UI display
	virtual UnicodeString getModuleDescription() const;

	// TheSuperHackers @feature author 01/01/2025 Override getModuleOrder for display ordering
	virtual Int getModuleOrder() const { return 150; } // Second priority - shows after RebuildHoleBehavior
};

//-------------------------------------------------------------------------------------------------
class ActiveBody : public BodyModule
{

	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE( ActiveBody, "ActiveBody" )
	MAKE_STANDARD_MODULE_MACRO_WITH_MODULE_DATA( ActiveBody, ActiveBodyModuleData )

public:

	ActiveBody( Thing *thing, const ModuleData* moduleData );
	// virtual destructor prototype provided by memory pool declaration

	virtual void onDelete( void );

	virtual void attemptDamage( DamageInfo *damageInfo );		///< try to damage this object
	virtual Real estimateDamage( DamageInfoInput& damageInfo ) const;
	virtual void attemptHealing( DamageInfo *damageInfo );		///< try to heal this object
	virtual Real getHealth() const;													///< get current health
	virtual BodyDamageType getDamageState() const;
	virtual void setDamageState( BodyDamageType newState );	///< control damage state directly.  Will adjust hitpoints.
	virtual void setAflame( Bool setting );///< This is a major change like a damage state.

	virtual UnsignedInt getSubdualDamageHealRate() const;
	virtual Real getSubdualDamageHealAmount() const;
	virtual Bool hasAnySubdualDamage() const;
	virtual Real getCurrentSubdualDamageAmount() const { return m_currentSubdualDamage; }

	virtual UnsignedInt getJammingDamageHealRate() const;
	virtual Real getJammingDamageHealAmount() const;
	virtual Bool hasAnyJammingDamage() const;
	virtual Real getCurrentJammingDamageAmount() const { return m_currentJammingDamage; }
	
	// TheSuperHackers @feature Ahmed Salah 15/01/2025 Component-aware Jamming damage methods
	virtual Real getTotalJammingDamage() const;									///< Get total Jamming damage (global + components)
	virtual Real getJammingDamagePercentage() const;							///< Get Jamming damage as percentage of total capacity
	

	virtual const DamageInfo *getLastDamageInfo() const { return &m_lastDamageInfo; }	///< return info on last damage dealt to this object
	virtual UnsignedInt getLastDamageTimestamp() const { return m_lastDamageTimestamp; }	///< return frame of last damage dealt
	virtual UnsignedInt getLastHealingTimestamp() const { return m_lastHealingTimestamp; }	///< return frame of last damage dealt
	virtual ObjectID getClearableLastAttacker() const { return (m_lastDamageCleared ? INVALID_ID : m_lastDamageInfo.in.m_sourceID); }
	virtual void clearLastAttacker() { m_lastDamageCleared = true; }

	virtual void onVeterancyLevelChanged( VeterancyLevel oldLevel, VeterancyLevel newLevel, Bool provideFeedback = TRUE );

	virtual void setArmorSetFlag(ArmorSetType ast) { m_curArmorSetFlags.set(ast, 1); }
	virtual void clearArmorSetFlag(ArmorSetType ast) { m_curArmorSetFlags.set(ast, 0); }
	virtual Bool testArmorSetFlag(ArmorSetType ast) { return m_curArmorSetFlags.test(ast); }

	virtual void setInitialHealth(Int initialPercent); ///< Sets the initial load health %.
	virtual void setMaxHealth( Real maxHealth, MaxHealthChangeType healthChangeType = SAME_CURRENTHEALTH ); ///< Sets the initial max health

	virtual Bool getFrontCrushed() const { return m_frontCrushed; }
	virtual Bool getBackCrushed() const { return m_backCrushed; }

	virtual void setFrontCrushed(Bool v) { m_frontCrushed = v; }
	virtual void setBackCrushed(Bool v) { m_backCrushed = v; }

	virtual Real getMaxHealth() const;  ///< return max health
	virtual Real getInitialHealth() const;  // return initial health

	virtual Real getPreviousHealth() const { return m_prevHealth; }

	virtual void setIndestructible( Bool indestructible );
	virtual Bool isIndestructible( void ) const { return m_indestructible; }

	virtual void internalChangeHealth( Real delta );								///< change health

	virtual void evaluateVisualCondition();
	virtual void updateBodyParticleSystems( void );// made public for topple anf building collapse updates -ML

	// Subdual Damage
	virtual Bool isSubdued() const;
	virtual Bool canBeSubdued() const;
	virtual void onSubdualChange( Bool isNowSubdued );///< Override this if you want a totally different effect than DISABLED_SUBDUED

	virtual Bool isJammingJammed() const;
	virtual Bool canBeJammed() const;
	virtual Bool canBeJammedWithDirectJammers(const std::map<AsciiString, Real>& componentNames = std::map<AsciiString, Real>()) const;
	virtual Bool canBeJammedWithAreaJammers(const std::map<AsciiString, Real>& componentNames = std::map<AsciiString, Real>()) const;
	virtual void onJammingChange( Bool isNowJammingJammed );///< Override this if you want a totally different effect than DISABLED_SUBDUED

	// TheSuperHackers @feature author 15/01/2025 Component health management - now inherited from BodyModule
	virtual void initializeComponentHealth();
	
	// TheSuperHackers @feature author 15/01/2025 Get component definitions - now inherited from BodyModule
	virtual std::vector<Component> getComponents() const;
	
	// TheSuperHackers @feature author 15/01/2025 Get icon to draw for component status
	// Call repeatedly to get all component icons (returns NULL when no more)
	virtual Anim2D* getComponentStatusIcon() const;
	
	// TheSuperHackers @feature author 15/01/2025 Generic component getter method
	template<typename TComponent>
	TComponent* GetComponent(const AsciiString& componentName) const
	{
		static_assert(std::is_base_of<Component, TComponent>::value, "TComponent must inherit from Component");
		
		// Find the component by name in instance component list
		for (std::vector<Component*>::const_iterator it = m_components.begin();
			 it != m_components.end(); ++it)
		{
			if (*it && (*it)->getName() == componentName)
			{
				// Safe downcast
				return dynamic_cast<TComponent*>(*it);
			}
		}
		
		return nullptr;
	}
	
	// TheSuperHackers @feature Ahmed Salah 30/10/2025 Get all components of a specific type
	template<typename TComponent>
	std::vector<TComponent*> GetComponentsOfType() const
	{
		static_assert(std::is_base_of<Component, TComponent>::value, "TComponent must inherit from Component");
		std::vector<TComponent*> results;
		for (std::vector<Component*>::const_iterator it = m_components.begin();
			 it != m_components.end(); ++it)
		{
			if (!*it)
				continue;
			// Use dynamic_cast for safety when RTTI is available
			TComponent* derived = dynamic_cast<TComponent*>(*it);
			if (derived)
			{
				results.push_back(derived);
			}
		}
		return results;
	}
	
	
	// TheSuperHackers @feature author 15/01/2025 Update model state based on current damage
	virtual void setCorrectDamageState();

	// TheSuperHackers @feature author 15/01/2025 Basic component name constants - now inherited from BodyModule

protected:

	void validateArmorAndDamageFX() const;
	void doDamageFX( const DamageInfo *damageInfo );

	void createParticleSystems( const AsciiString &boneBaseName,
															const ParticleSystemTemplate *systemTemplate,
															Int maxSystems );
	void deleteAllParticleSystems( void );

	Bool shouldRetaliate(Object *obj);
	Bool shouldRetaliateAgainstAggressor(Object *obj, Object *damager);

	virtual void internalAddSubdualDamage( Real delta );								///< change health

	virtual void internalAddJammingDamage( Real delta );								///< change health

private:

	Real									m_currentHealth;				///< health of the object
	Real									m_prevHealth;						///< previous health value before current health change op
  	Real									m_maxHealth;						///< max health this object can have
  	Real									m_initialHealth;				///< starting health for this object
	Real									m_currentSubdualDamage;	///< Starts at zero and goes up.  Inherited modules will do something when "subdued".
	Real									m_currentJammingDamage;	///< Starts at zero and goes up.  Inherited modules will do something when "subdued".

	BodyDamageType				m_curDamageState;				///< last known damage state
	UnsignedInt						m_nextDamageFXTime;
	DamageType						m_lastDamageFXDone;
	DamageInfo						m_lastDamageInfo;				///< store the last DamageInfo object that we received
	UnsignedInt						m_lastDamageTimestamp; 	///< frame of last damage dealt
	UnsignedInt						m_lastHealingTimestamp; ///< frame of last healing dealt
	Bool									m_frontCrushed;
	Bool									m_backCrushed;
	Bool									m_lastDamageCleared;
	Bool									m_indestructible;			///< is this object indestructible?


	BodyParticleSystem *m_particleSystems;				///< particle systems created and attached to this object

	/*
		Note, you MUST call validateArmorAndDamageFX() before accessing these fields.
	*/
	ArmorSetFlags											m_curArmorSetFlags;
	mutable const ArmorTemplateSet*		m_curArmorSet;
	mutable Armor											m_curArmor;
	mutable const DamageFX*						m_curDamageFX;

	// TheSuperHackers @feature author 15/01/2025 Per-instance component list (copied from ModuleData on construction)
	std::vector<Component*> m_components;		///< Instance-specific component copies with runtime state

};
