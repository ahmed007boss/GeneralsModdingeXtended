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

// FILE: WeaponRangeDecalBehavior.h /////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __WeaponRangeDecalBehavior_H_
#define __WeaponRangeDecalBehavior_H_

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "GameLogic/Module/BehaviorModule.h"
#include "GameLogic/Module/UpgradeModule.h"
#include "GameLogic/Module/UpdateModule.h"
#include "GameClient/RadiusDecal.h"
#include "GameLogic/WeaponSet.h"

//-------------------------------------------------------------------------------------------------
class WeaponRangeDecalBehaviorModuleData : public UpdateModuleData
{
public:
	UpgradeMuxData				m_upgradeMuxData;
	WeaponSlotType				m_weaponSlot;					// Which weapon slot to use for range values
	Bool						m_useSlavedObjectWeapon;		// If true, use first slaved object's weapon instead of own weapon
	AsciiString					m_specificWeaponName;			// If set, use this specific weapon for range values (overrides slot and slaved settings)

	RadiusDecalTemplate	        m_minRangeDecalTemplate;		// Template for minimum range decal
	RadiusDecalTemplate	        m_maxRangeDecalTemplate;		// Template for maximum range decal

	WeaponRangeDecalBehaviorModuleData();

	static void buildFieldParse(MultiIniFieldParse& p);
};

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
class WeaponRangeDecalBehavior : public UpdateModule, public UpgradeMux
{

	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE( WeaponRangeDecalBehavior, "WeaponRangeDecalBehavior" )
	MAKE_STANDARD_MODULE_MACRO_WITH_MODULE_DATA( WeaponRangeDecalBehavior, WeaponRangeDecalBehaviorModuleData )

public:

	WeaponRangeDecalBehavior( Thing *thing, const ModuleData* moduleData );
	// virtual destructor prototype provided by memory pool declaration

	// module methods
	static Int getInterfaceMask() { return UpdateModule::getInterfaceMask() | (MODULEINTERFACE_UPGRADE); }

	// BehaviorModule
	virtual UpgradeModuleInterface* getUpgrade() { return this; }

	void createWeaponRangeDecals( void );
	void killWeaponRangeDecals( void );
	void refreshDecalState( void );		// Call this when object's range decal slot changes

	// UpdateModuleInterface
	virtual UpdateSleepTime update();

protected:

	virtual void upgradeImplementation()
	{
		createWeaponRangeDecals();
		setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
	}

	virtual void downgradeImplementation()
	{
		killWeaponRangeDecals();
		setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
	}

	virtual void getUpgradeActivationMasks(UpgradeMaskType& activation, UpgradeMaskType& conflicting, UpgradeMaskType& requireAnyOf, UpgradeMaskType& requireAllOf) const
	{
		getWeaponRangeDecalBehaviorModuleData()->m_upgradeMuxData.getUpgradeActivationMasks(activation, conflicting, requireAnyOf, requireAllOf);
	}

	virtual void performUpgradeFX()
	{
		getWeaponRangeDecalBehaviorModuleData()->m_upgradeMuxData.performUpgradeFX(getObject());
	}

	virtual void processUpgradeRemoval()
	{
		// I can't take it any more.  Let the record show that I think the UpgradeMux multiple inheritence is CRAP.
		getWeaponRangeDecalBehaviorModuleData()->m_upgradeMuxData.muxDataProcessUpgradeRemoval(getObject());
	}

	virtual Bool requiresAllActivationUpgrades() const
	{
		return getWeaponRangeDecalBehaviorModuleData()->m_upgradeMuxData.m_requiresAllTriggers;
	}

	inline Bool isUpgradeActive() const { return isAlreadyUpgraded(); }

	virtual Bool isSubObjectsUpgrade() { return false; }

	// Additional required virtual methods from UpgradeMux
	virtual Bool isAlreadyUpgraded() const { return UpgradeMux::isAlreadyUpgraded(); }
	virtual Bool attemptUpgrade( UpgradeMaskType keyMask ) { return UpgradeMux::attemptUpgrade(keyMask); }
	virtual Bool wouldUpgrade( UpgradeMaskType keyMask ) const { return UpgradeMux::wouldUpgrade(keyMask); }
	virtual Bool resetUpgrade( UpgradeMaskType keyMask ) { return UpgradeMux::resetUpgrade(keyMask); }
	virtual void forceRefreshUpgrade() { UpgradeMux::forceRefreshUpgrade(); }
	virtual Bool testUpgradeConditions( UpgradeMaskType keyMask ) const { return UpgradeMux::testUpgradeConditions(keyMask); }

private:

	RadiusDecal m_minRangeDecal;		// Minimum range decal instance
	RadiusDecal m_maxRangeDecal;		// Maximum range decal instance

	void clearDecals( void );
};

#endif // __WeaponRangeDecalBehavior_H_
