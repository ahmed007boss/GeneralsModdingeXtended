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

// FILE: WeaponUpgrade.h ///////////////////////////////////////////////////////////////////
// TheSuperHackers @feature author DD/MM/YYYY Weapon upgrade module
// Desc:	 Weapon upgrade module that modifies weapon properties when triggered by upgrades
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef __WEAPON_UPGRADE_H_
#define __WEAPON_UPGRADE_H_

#include "Common/AsciiString.h"
#include "GameLogic/Module/UpgradeModule.h"
#include <vector>
#include <map>

// FORWARD DECLARATIONS ///////////////////////////////////////////////////////////////////////////
class WeaponTemplate;

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author DD/MM/YYYY Weapon upgrade module data
//-------------------------------------------------------------------------------------------------
class WeaponUpgradeModuleData : public UpgradeModuleData
{
public:
    std::vector<AsciiString> m_weaponNames;              ///< List of weapon names to affect (empty = all weapons)
    Real m_addPrimaryDamage;                               ///< Add to primary damage (default 0)
    Real m_addPrimaryDamageRadius;                         ///< Add to primary damage radius (default 0)
    Real m_addAttackRange;                                 ///< Add to attack range (default 0)
    Real m_addMinimumAttackRange;                          ///< Add to minimum attack range (default 0)
    Real m_addAcceptableAimDelta;                          ///< Add to acceptable aim delta (default 0)
    Real m_addWeaponSpeed;                                 ///< Add to weapon speed (default 0)
    Int m_addDelayBetweenShots;                            ///< Add to delay between shots (default 0)
    Int m_addClipSize;                                     ///< Add to clip size (default 0)
    Int m_addClipReloadTime;                               ///< Add to clip reload time (default 0)

    WeaponUpgradeModuleData();

    static void buildFieldParse(MultiIniFieldParse& p);
};

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author DD/MM/YYYY Weapon upgrade module
//-------------------------------------------------------------------------------------------------
class WeaponUpgrade : public UpgradeModule
{
    MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(WeaponUpgrade, "WeaponUpgrade")
    MAKE_STANDARD_MODULE_MACRO_WITH_MODULE_DATA(WeaponUpgrade, WeaponUpgradeModuleData)

public:
    WeaponUpgrade(Thing* thing, const ModuleData* moduleData);
    // virtual destructor prototype provided by memory pool declaration

    // Module methods
    static Int getInterfaceMask() { return MODULEINTERFACE_UPGRADE; }

    // BehaviorModule overrides
    virtual void onDelete();

protected:
    // UpgradeMux implementation
    virtual void upgradeImplementation();
    virtual void downgradeImplementation();
    virtual Bool isSubObjectsUpgrade() { return FALSE; }
    
    // UpgradeMux override
    virtual void forceRefreshUpgrade();  // TheSuperHackers @feature author DD/MM/YYYY Allow re-applying upgrade

private:
    // Apply upgrades to weapons (adds to modifier fields)
    void applyWeaponUpgrades();
    void removeWeaponUpgrades();
};

#endif // __WEAPON_UPGRADE_H_
