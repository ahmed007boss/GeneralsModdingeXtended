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

// FILE: WeaponUpgrade.cpp /////////////////////////////////////////////////////////////////
// TheSuperHackers @feature author DD/MM/YYYY Weapon upgrade module
// Desc:	 Weapon upgrade module that modifies weapon properties when triggered by upgrades
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file in the GameEngine

#include "Common/Xfer.h"
#include "GameLogic/Object.h"
#include "GameLogic/Weapon.h"
#include "GameLogic/Module/WeaponUpgrade.h"

//-------------------------------------------------------------------------------------------------
// WeaponUpgradeModuleData
//-------------------------------------------------------------------------------------------------

WeaponUpgradeModuleData::WeaponUpgradeModuleData()
{
    m_weaponNames.clear();
    m_addPrimaryDamage = 0.0f;
    m_addPrimaryDamageRadius = 0.0f;
    m_addAttackRange = 0.0f;
    m_addMinimumAttackRange = 0.0f;
    m_addAcceptableAimDelta = 0.0f;
    m_addWeaponSpeed = 0.0f;
    m_addDelayBetweenShots = 0;
    m_addClipSize = 0;
    m_addClipReloadTime = 0;
}

//-------------------------------------------------------------------------------------------------
void WeaponUpgradeModuleData::buildFieldParse(MultiIniFieldParse& p)
{
    UpgradeModuleData::buildFieldParse(p);

    static const FieldParse dataFieldParse[] =
    {
        { "Weapons", INI::parseAsciiStringVector, NULL, offsetof(WeaponUpgradeModuleData, m_weaponNames) },
        { "AddPrimaryDamage", INI::parseReal, NULL, offsetof(WeaponUpgradeModuleData, m_addPrimaryDamage) },
        { "AddPrimaryDamageRadius", INI::parseReal, NULL, offsetof(WeaponUpgradeModuleData, m_addPrimaryDamageRadius) },
        { "AddAttackRange", INI::parseReal, NULL, offsetof(WeaponUpgradeModuleData, m_addAttackRange) },
        { "AddMinimumAttackRange", INI::parseReal, NULL, offsetof(WeaponUpgradeModuleData, m_addMinimumAttackRange) },
        { "AddAcceptableAimDelta", INI::parseReal, NULL, offsetof(WeaponUpgradeModuleData, m_addAcceptableAimDelta) },
        { "AddWeaponSpeed", INI::parseReal, NULL, offsetof(WeaponUpgradeModuleData, m_addWeaponSpeed) },
        { "AddDelayBetweenShots", INI::parseInt, NULL, offsetof(WeaponUpgradeModuleData, m_addDelayBetweenShots) },
        { "AddClipSize", INI::parseInt, NULL, offsetof(WeaponUpgradeModuleData, m_addClipSize) },
        { "AddClipReloadTime", INI::parseInt, NULL, offsetof(WeaponUpgradeModuleData, m_addClipReloadTime) },
        { 0, 0, 0, 0 }
    };
    p.add(dataFieldParse);
}

//-------------------------------------------------------------------------------------------------
// WeaponUpgrade
//-------------------------------------------------------------------------------------------------

WeaponUpgrade::WeaponUpgrade(Thing* thing, const ModuleData* moduleData) :
    UpgradeModule(thing, moduleData)
{
}

//-------------------------------------------------------------------------------------------------
WeaponUpgrade::~WeaponUpgrade(void)
{
}

//-------------------------------------------------------------------------------------------------
void WeaponUpgrade::onDelete()
{
    // If we haven't been upgraded there is nothing to clean up
    if (isAlreadyUpgraded() == FALSE)
        return;

    // If we're currently disabled, we shouldn't do anything, because we've already done it.
    if (getObject()->isDisabled() || getObject()->isElectronicallyDisabled())
        return;

    // Remove the weapon upgrades
    removeWeaponUpgrades();

    // This upgrade module is now "not upgraded"
    setUpgradeExecuted(FALSE);
}

//-------------------------------------------------------------------------------------------------
void WeaponUpgrade::upgradeImplementation()
{
    applyWeaponUpgrades();
}

//-------------------------------------------------------------------------------------------------
void WeaponUpgrade::downgradeImplementation()
{
    removeWeaponUpgrades();
}

//-------------------------------------------------------------------------------------------------
void WeaponUpgrade::forceRefreshUpgrade()
{
    // Re-apply upgrades (useful when upgrade needs to be refreshed)
    // This is safe because modifiers are additive - re-applying will just add again
    // But we should only do this if already upgraded to avoid double-application
    if (isAlreadyUpgraded() == TRUE)
    {
        // Remove current modifiers first to avoid double-application
        removeWeaponUpgrades();
        // Then re-apply them
        applyWeaponUpgrades();
    }
}

//-------------------------------------------------------------------------------------------------
void WeaponUpgrade::applyWeaponUpgrades()
{
    const WeaponUpgradeModuleData* data = getWeaponUpgradeModuleData();
    Object* obj = getObject();

    if (!obj || !data)
        return;

    // Iterate through all weapon slots
    for (Int i = 0; i < WEAPONSLOT_COUNT; ++i)
    {
        Weapon* weapon = obj->getWeaponInWeaponSlot((WeaponSlotType)i);
        if (!weapon)
            continue;

        const WeaponTemplate* template_ = weapon->getTemplate();
        if (!template_)
            continue;

        // Check if we should affect this weapon
        Bool shouldAffect = TRUE;
        if (!data->m_weaponNames.empty())
        {
            // Only affect weapons in the list
            shouldAffect = FALSE;
            AsciiString weaponName = template_->getName();
            for (std::vector<AsciiString>::const_iterator it = data->m_weaponNames.begin();
                 it != data->m_weaponNames.end(); ++it)
            {
                if (weaponName == *it)
                {
                    shouldAffect = TRUE;
                    break;
                }
            }
        }

        if (!shouldAffect)
            continue;

        // Apply modifications to weapon instance (per-unit, not per-template)
        weapon->addPrimaryDamage(data->m_addPrimaryDamage);
        weapon->addPrimaryDamageRadius(data->m_addPrimaryDamageRadius);
        weapon->addAttackRange(data->m_addAttackRange);
        weapon->addMinimumAttackRange(data->m_addMinimumAttackRange);
        weapon->addAcceptableAimDelta(data->m_addAcceptableAimDelta);
        weapon->addWeaponSpeed(data->m_addWeaponSpeed);
        weapon->addDelayBetweenShots(data->m_addDelayBetweenShots);
        weapon->addClipSize(data->m_addClipSize);
        weapon->addClipReloadTime(data->m_addClipReloadTime);
    }
}

//-------------------------------------------------------------------------------------------------
void WeaponUpgrade::removeWeaponUpgrades()
{
    const WeaponUpgradeModuleData* data = getWeaponUpgradeModuleData();
    Object* obj = getObject();

    if (!obj || !data)
        return;

    // Iterate through all weapon slots
    for (Int i = 0; i < WEAPONSLOT_COUNT; ++i)
    {
        Weapon* weapon = obj->getWeaponInWeaponSlot((WeaponSlotType)i);
        if (!weapon)
            continue;

        const WeaponTemplate* template_ = weapon->getTemplate();
        if (!template_)
            continue;

        // Check if we should affect this weapon
        Bool shouldAffect = TRUE;
        if (!data->m_weaponNames.empty())
        {
            // Only affect weapons in the list
            shouldAffect = FALSE;
            AsciiString weaponName = template_->getName();
            for (std::vector<AsciiString>::const_iterator it = data->m_weaponNames.begin();
                 it != data->m_weaponNames.end(); ++it)
            {
                if (weaponName == *it)
                {
                    shouldAffect = TRUE;
                    break;
                }
            }
        }

        if (!shouldAffect)
            continue;

        // Remove modifications from weapon instance (per-unit, not per-template)
        weapon->addPrimaryDamage(-data->m_addPrimaryDamage);
        weapon->addPrimaryDamageRadius(-data->m_addPrimaryDamageRadius);
        weapon->addAttackRange(-data->m_addAttackRange);
        weapon->addMinimumAttackRange(-data->m_addMinimumAttackRange);
        weapon->addAcceptableAimDelta(-data->m_addAcceptableAimDelta);
        weapon->addWeaponSpeed(-data->m_addWeaponSpeed);
        weapon->addDelayBetweenShots(-data->m_addDelayBetweenShots);
        weapon->addClipSize(-data->m_addClipSize);
        weapon->addClipReloadTime(-data->m_addClipReloadTime);
    }
}

//-------------------------------------------------------------------------------------------------
void WeaponUpgrade::crc(Xfer* xfer)
{
    // Extend base class
    UpgradeModule::crc(xfer);
}

//-------------------------------------------------------------------------------------------------
void WeaponUpgrade::xfer(Xfer* xfer)
{
    // Version
    XferVersion currentVersion = 1;
    XferVersion version = currentVersion;
    xfer->xferVersion(&version, currentVersion);

    // Extend base class
    UpgradeModule::xfer(xfer);
}

//-------------------------------------------------------------------------------------------------
void WeaponUpgrade::loadPostProcess()
{
    // Extend base class
    UpgradeModule::loadPostProcess();
}
