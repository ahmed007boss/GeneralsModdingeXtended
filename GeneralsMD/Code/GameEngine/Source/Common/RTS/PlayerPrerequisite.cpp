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

// FILE: PlayerPrerequisite.cpp /////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//
//                       Westwood Studios Pacific.
//
//                       Confidential Information
//                Copyright (C) 2001 - All Rights Reserved
//
//-----------------------------------------------------------------------------
//
// Project:   RTS3
//
// File name: PlayerPrerequisite.cpp
//
// Created:   Steven Johnson, October 2001
//
// Desc:      @todo
//
//-----------------------------------------------------------------------------

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/PlayerPrerequisite.h"
#include "Common/Player.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/KindOf.h"
#include "GameLogic/Object.h"
#include "GameClient/Drawable.h"
#include "GameClient/GameText.h"


//-----------------------------------------------------------------------------
PlayerPrerequisite::PlayerPrerequisite() : m_namesResolved(false)
{
	init();
}

//-----------------------------------------------------------------------------
PlayerPrerequisite::~PlayerPrerequisite()
{
}

//-----------------------------------------------------------------------------
void PlayerPrerequisite::init()
{
	m_prereqUnits.clear();
	m_prereqSciences.clear();
	m_prereqUnitsConflict.clear();
	m_prereqSciencesConflict.clear();
	m_prereqUpgradesNames.clear();
	m_prereqUpgradesMask.clear();
	m_prereqUpgradesNamesConflict.clear();
	m_prereqUpgradesMaskConflict.clear();
	m_prereqKindOfUnitsNames.clear();
	m_prereqKindOfUnitsMask.clear();
	m_prereqKindOfUnitsNamesConflict.clear();
	m_prereqKindOfUnitsMaskConflict.clear();
	m_prereqMinCountKindOfUnitsNames.clear();
	m_prereqMaxCountKindOfUnitsNames.clear();
	m_prereqMinCountKindOfUnitsWithLevelNames.clear();
	m_prereqMaxCountKindOfUnitsWithLevelNames.clear();
	m_namesResolved = false;	// TheSuperHackers @feature Ahmed Salah 15/01/2025 Initialize resolution flag
}

//=============================================================================
void PlayerPrerequisite::resolveNames()
{
	// Resolve regular prerequisite units
	for (size_t i = 0; i < m_prereqUnits.size(); i++)
	{
		//
		// note that this will find the template at the "top most" level (not override
		// sub-temlates), which is what we want ... we conceptually only have one
		// template for any given thing, it's only the *data* that is overridden
		//
		if (m_prereqUnits[i].name.isNotEmpty())
		{
			m_prereqUnits[i].unit = TheThingFactory->findTemplate(m_prereqUnits[i].name);	// might be null

			/** @todo for now removing this assert until we can completely remove
			the GDF stuff, the problem is that some INI files refer to GDF names, and they
			aren't yet loaded in the world builder but will all go away later anyway etc */
			DEBUG_ASSERTCRASH(m_prereqUnits[i].unit, ("could not find prereq %s", m_prereqUnits[i].name.str()));

			m_prereqUnits[i].name.clear(); // we're done with it
		}
	}

	// Resolve conflict prerequisite units
	for (size_t i = 0; i < m_prereqUnitsConflict.size(); i++)
	{
		if (m_prereqUnitsConflict[i].name.isNotEmpty())
		{
			m_prereqUnitsConflict[i].unit = TheThingFactory->findTemplate(m_prereqUnitsConflict[i].name);	// might be null

			/** @todo for now removing this assert until we can completely remove
			the GDF stuff, the problem is that some INI files refer to GDF names, and they
			aren't yet loaded in the world builder but will all go away later anyway etc */
			DEBUG_ASSERTCRASH(m_prereqUnitsConflict[i].unit, ("could not find prereq %s", m_prereqUnitsConflict[i].name.str()));

			m_prereqUnitsConflict[i].name.clear(); // we're done with it
		}
	}


	// Resolve prerequisite upgrades
	std::vector<AsciiString>::const_iterator it;
	for (it = m_prereqUpgradesNames.begin(); it != m_prereqUpgradesNames.end(); ++it)
	{
		const UpgradeTemplate* theTemplate = TheUpgradeCenter->findUpgrade(*it);
		if (!theTemplate)
		{
			DEBUG_CRASH(("An upgrade module references '%s', which is not an Upgrade", it->str()));
			throw INI_INVALID_DATA;
		}
		m_prereqUpgradesMask.set(theTemplate->getUpgradeMask());
	}

	// Resolve conflict prerequisite upgrades
	for (it = m_prereqUpgradesNamesConflict.begin(); it != m_prereqUpgradesNamesConflict.end(); ++it)
	{
		const UpgradeTemplate* theTemplate = TheUpgradeCenter->findUpgrade(*it);
		if (!theTemplate)
		{
			DEBUG_CRASH(("An upgrade module references '%s', which is not an Upgrade", it->str()));
			throw INI_INVALID_DATA;
		}
		m_prereqUpgradesMaskConflict.set(theTemplate->getUpgradeMask());
	}

	// Resolve prerequisite KindOf units
	for (it = m_prereqKindOfUnitsNames.begin(); it != m_prereqKindOfUnitsNames.end(); ++it)
	{
		KindOfType kindOfType = (KindOfType)INI::scanIndexList(it->str(), KindOfMaskType::getBitNames());
		m_prereqKindOfUnitsMask.set(kindOfType);
	}

	// Resolve conflict prerequisite KindOf units
	for (it = m_prereqKindOfUnitsNamesConflict.begin(); it != m_prereqKindOfUnitsNamesConflict.end(); ++it)
	{
		KindOfType kindOfType = (KindOfType)INI::scanIndexList(it->str(), KindOfMaskType::getBitNames());
		m_prereqKindOfUnitsMaskConflict.set(kindOfType);
	}
}

//-----------------------------------------------------------------------------
Int PlayerPrerequisite::calcNumPrereqUnitsOwned(const Player* player, Int counts[MAX_PREREQ]) const
{
	const ThingTemplate* tmpls[MAX_PREREQ];
	Int cnt = m_prereqUnits.size();
	if (cnt > MAX_PREREQ)
		cnt = MAX_PREREQ;
	for (int i = 0; i < cnt; i++)
		tmpls[i] = m_prereqUnits[i].unit;
	player->countObjectsByThingTemplate(cnt, tmpls, false, counts);
	return cnt;
}

//-----------------------------------------------------------------------------
Int PlayerPrerequisite::getAllPossibleBuildFacilityTemplates(const ThingTemplate* tmpls[], Int maxtmpls) const
{
	Int count = 0;
	for (size_t i = 0; i < m_prereqUnits.size(); i++)
	{
		if (i > 0 && !(m_prereqUnits[i].flags & UNIT_OR_WITH_PREV))
			break;
		if (count >= maxtmpls)
			break;
		tmpls[count++] = m_prereqUnits[i].unit;
	}
	return count;
}

//-----------------------------------------------------------------------------
const ThingTemplate* PlayerPrerequisite::getExistingBuildFacilityTemplate(const Player* player) const
{
	DEBUG_ASSERTCRASH(player, ("player may not be null"));
	if (m_prereqUnits.size())
	{
		Int ownCount[MAX_PREREQ];
		Int cnt = calcNumPrereqUnitsOwned(player, ownCount);
		for (int i = 0; i < cnt; i++)
		{
			if (i > 0 && !(m_prereqUnits[i].flags & UNIT_OR_WITH_PREV))
				break;
			if (ownCount[i])
				return m_prereqUnits[i].unit;
		}
	}
	return NULL;
}

//-----------------------------------------------------------------------------
Bool PlayerPrerequisite::isSatisfied(const Player* player) const
{
	// TheSuperHackers @feature Ahmed Salah 15/01/2025 Lazy initialization: resolve names if not already resolved
	if (!m_namesResolved)
	{
		const_cast<PlayerPrerequisite*>(this)->resolveNames();
		m_namesResolved = true;
	}

	Int i;

	if (!player)
		return false;

	// gotta have all the prereq sciences.
	for (i = 0; i < m_prereqSciences.size(); i++)
	{
		if (!player->hasScience(m_prereqSciences[i]))
			return false;
	}

	// gotta have all the prereq sciences.
	for (i = 0; i < m_prereqSciencesConflict.size(); i++)
	{
		if (player->hasScience(m_prereqSciencesConflict[i]))
			return false;
	}

	// the player must have at least one instance of each prereq unit.
	Int ownCount[MAX_PREREQ];
	Int cnt = calcNumPrereqUnitsOwned(player, ownCount);

	// fix up the "or" cases. (start at 1!)
	handleOrLogic(ownCount, cnt, m_prereqUnits);

	for (i = 0; i < cnt; i++)
	{
		if (ownCount[i] == -1)	// the magic "ignore me" flag
			continue;
		if (ownCount[i] == 0)		// everything not ignored, is required
			return false;
	}


	// the player must NOT have any of the conflicting units
	Int ownCount2[MAX_PREREQ];
	Int cnt2 = m_prereqUnitsConflict.size();
	if (cnt2 > MAX_PREREQ)
		cnt2 = MAX_PREREQ;

	// Count owned conflicting units
	for (int j = 0; j < cnt2; j++)
	{
		ownCount2[j] = 0;
		if (m_prereqUnitsConflict[j].unit)
		{
			player->countObjectsByThingTemplate(1, &m_prereqUnitsConflict[j].unit, false, &ownCount2[j]);
		}
	}

	// fix up the "or" cases. (start at 1!)
	handleOrLogicConflict(ownCount2, cnt2, m_prereqUnitsConflict);

	for (i = 0; i < cnt2; i++)
	{
		if (ownCount2[i] == -1)	// the magic "ignore me" flag
			continue;
		if (ownCount2[i] > 0)		// player owns a conflicting unit
			return false;
	}

	// Check upgrade prerequisites
	UpgradeMaskType playerMask = player->getCompletedUpgradeMask();
	if (m_prereqUpgradesMask.any())
	{
		if (!playerMask.testForAll(m_prereqUpgradesMask))
			return false;
	}

	// Check conflicting upgrade prerequisites
	if (m_prereqUpgradesMaskConflict.any())
	{
		if (playerMask.testForAny(m_prereqUpgradesMaskConflict))
			return false;
	}

	// Check KindOf prerequisites
	if (m_prereqKindOfUnitsMask.any())
	{
		if (const_cast<Player*>(player)->countObjects(m_prereqKindOfUnitsMask, KindOfMaskType()) == 0)
			return false;
	}

	// Check conflicting KindOf prerequisites
	if (m_prereqKindOfUnitsMaskConflict.any())
	{
		if (const_cast<Player*>(player)->countObjects(m_prereqKindOfUnitsMaskConflict, KindOfMaskType()) > 0)
			return false;
	}

	// Check min count KindOf prerequisites
	for (size_t i = 0; i < m_prereqMinCountKindOfUnitsNames.size(); i++)
	{
		// Parse the string format: "KINDOFXXX 4 KINDOFYYY 3"
		AsciiString remaining = m_prereqMinCountKindOfUnitsNames[i];
		Bool hasEnough = false;
		
		while (!remaining.isEmpty())
		{
			AsciiString kindOfName;
			Int count;
			if (!parseKindOfCountPair(remaining, kindOfName, count))
				break;
			
			// Check if player has enough of this KindOf type
			KindOfType kindOfType = (KindOfType)INI::scanIndexList(kindOfName.str(), KindOfMaskType::getBitNames());
			KindOfMaskType kindOfMask = MAKE_KINDOF_MASK(kindOfType);
			Int playerCount = const_cast<Player*>(player)->countObjects(kindOfMask, KindOfMaskType());
			
			if (playerCount >= count)
			{
				hasEnough = true;
				break; // At least one KindOf requirement is satisfied
			}
		}
		
		if (!hasEnough)
			return false;
	}

	// Check max count KindOf prerequisites
	for (size_t i = 0; i < m_prereqMaxCountKindOfUnitsNames.size(); i++)
	{
		// Parse the string format: "KINDOFXXX 4 KINDOFYYY 3"
		AsciiString remaining = m_prereqMaxCountKindOfUnitsNames[i];
		Bool hasMaxCount = false;
		
		while (!remaining.isEmpty())
		{
			AsciiString kindOfName;
			Int count;
			if (!parseKindOfCountPair(remaining, kindOfName, count))
				break;
			
			// Check if player has the maximum count of this KindOf type
			KindOfType kindOfType = (KindOfType)INI::scanIndexList(kindOfName.str(), KindOfMaskType::getBitNames());
			KindOfMaskType kindOfMask = MAKE_KINDOF_MASK(kindOfType);
			Int playerCount = const_cast<Player*>(player)->countObjects(kindOfMask, KindOfMaskType());
			
			if (playerCount >= count)
			{
				hasMaxCount = true;
				break; // At least one max count requirement is satisfied
			}
		}
		
		if (hasMaxCount)
			return false; // Player doesn't have the required max count
	}

	// Check min count KindOf prerequisites with veterancy level
	for (size_t i = 0; i < m_prereqMinCountKindOfUnitsWithLevelNames.size(); i++)
	{
		// Parse the string format: "KINDOFXXX LEVEL_VETERAN 4 KINDOFYYY LEVEL_REGULAR 3"
		AsciiString remaining = m_prereqMinCountKindOfUnitsWithLevelNames[i];
		Bool hasEnough = false;
		
		while (!remaining.isEmpty())
		{
			AsciiString kindOfName;
			AsciiString levelStr;
			Int count;
			if (!parseKindOfLevelCountTriple(remaining, kindOfName, levelStr, count))
				break;
			
			// Get the veterancy level
			VeterancyLevel minLevel = (VeterancyLevel)INI::scanIndexList(levelStr.str(), TheVeterancyNames);
			
			// Check if player has the minimum count of this KindOf type with the specified veterancy level
			KindOfType kindOfType = (KindOfType)INI::scanIndexList(kindOfName.str(), KindOfMaskType::getBitNames());
			KindOfMaskType kindOfMask = MAKE_KINDOF_MASK(kindOfType);
			Int playerCount = const_cast<Player*>(player)->countObjects(kindOfMask, KindOfMaskType(), minLevel);
			
			if (playerCount >= count)
			{
				hasEnough = true;
				break; // At least one min count requirement is satisfied
			}
		}
		
		if (!hasEnough)
			return false; // Player doesn't have the required min count
	}

	// Check max count KindOf prerequisites with veterancy level
	for (size_t i = 0; i < m_prereqMaxCountKindOfUnitsWithLevelNames.size(); i++)
	{
		// Parse the string format: "KINDOFXXX LEVEL_VETERAN 4 KINDOFYYY LEVEL_REGULAR 3"
		AsciiString remaining = m_prereqMaxCountKindOfUnitsWithLevelNames[i];
		Bool hasMaxCount = false;
		
		while (!remaining.isEmpty())
		{
			AsciiString kindOfName;
			AsciiString levelStr;
			Int count;
			if (!parseKindOfLevelCountTriple(remaining, kindOfName, levelStr, count))
				break;
			
			// Get the veterancy level
			VeterancyLevel minLevel = (VeterancyLevel)INI::scanIndexList(levelStr.str(), TheVeterancyNames);
			
			// Check if player has the maximum count of this KindOf type with the specified veterancy level
			KindOfType kindOfType = (KindOfType)INI::scanIndexList(kindOfName.str(), KindOfMaskType::getBitNames());
			KindOfMaskType kindOfMask = MAKE_KINDOF_MASK(kindOfType);
			Int playerCount = const_cast<Player*>(player)->countObjects(kindOfMask, KindOfMaskType(), minLevel);
			
			if (playerCount >= count)
			{
				hasMaxCount = true;
				break; // At least one max count requirement is satisfied
			}
		}
		
		if (hasMaxCount)
			return false; // Player doesn't have the required max count
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
/** Add a unit prerequisite, if 'orWithPrevious' is set then this unit is said
	* to be an alternate prereq to the previously added unit, otherwise this becomes
	* a new 'block' and is required in ADDDITION to other entries.
	* Return FALSE if no space left to add unit */
	//-------------------------------------------------------------------------------------------------
void PlayerPrerequisite::addUnitPrereq(AsciiString unit, Bool orUnitWithPrevious)
{
	PrereqUnitRec info;
	info.name = unit;
	info.flags = orUnitWithPrevious ? UNIT_OR_WITH_PREV : 0;
	info.unit = NULL;
	m_prereqUnits.push_back(info);

}

//-------------------------------------------------------------------------------------------------
/** Add a unit prerequisite, if 'orWithPrevious' is set then this unit is said
	* to be an alternate prereq to the previously added unit, otherwise this becomes
	* a new 'block' and is required in ADDDITION to other entries.
	* Return FALSE if no space left to add unit */
	//-------------------------------------------------------------------------------------------------
void PlayerPrerequisite::addUnitPrereq(const std::vector<AsciiString>& units)
{
	Bool orWithPrevious = false;
	for (size_t i = 0; i < units.size(); ++i)
	{
		addUnitPrereq(units[i], orWithPrevious);
		orWithPrevious = true;
	}

}



//-------------------------------------------------------------------------------------------------
/** Add a unit prerequisite, if 'orWithPrevious' is set then this unit is said
	* to be an alternate prereq to the previously added unit, otherwise this becomes
	* a new 'block' and is required in ADDDITION to other entries.
	* Return FALSE if no space left to add unit */
	//-------------------------------------------------------------------------------------------------
void PlayerPrerequisite::addUnitPrereqConflict(AsciiString unit, Bool orUnitWithPrevious)
{
	PrereqUnitRec info;
	info.name = unit;
	info.flags = orUnitWithPrevious ? UNIT_OR_WITH_PREV : 0;
	info.unit = NULL;
	m_prereqUnitsConflict.push_back(info);

}  // end addUnitPrereqConflict

//-------------------------------------------------------------------------------------------------
/** Add a unit prerequisite, if 'orWithPrevious' is set then this unit is said
	* to be an alternate prereq to the previously added unit, otherwise this becomes
	* a new 'block' and is required in ADDDITION to other entries.
	* Return FALSE if no space left to add unit */
	//-------------------------------------------------------------------------------------------------
void PlayerPrerequisite::addUnitPrereqConflict(const std::vector<AsciiString>& units)
{
	Bool orWithPrevious = false;
	for (size_t i = 0; i < units.size(); ++i)
	{
		addUnitPrereqConflict(units[i], orWithPrevious);
		orWithPrevious = true;
	}

}  // end addUnitPrereq

//-------------------------------------------------------------------------------------------------
void PlayerPrerequisite::addUpgradePrereq(AsciiString upgrade)
{
	m_prereqUpgradesNames.push_back(upgrade);
}

//-------------------------------------------------------------------------------------------------
void PlayerPrerequisite::addUpgradePrereqConflict(AsciiString upgrade)
{
	m_prereqUpgradesNamesConflict.push_back(upgrade);
}

//-------------------------------------------------------------------------------------------------
void PlayerPrerequisite::addKindOfUnitPrereq(AsciiString kindOfName)
{
	m_prereqKindOfUnitsNames.push_back(kindOfName);
}

//-------------------------------------------------------------------------------------------------
void PlayerPrerequisite::addKindOfUnitPrereqConflict(AsciiString kindOfName)
{
	m_prereqKindOfUnitsNamesConflict.push_back(kindOfName);
}

//-------------------------------------------------------------------------------------------------
void PlayerPrerequisite::addMinCountKindOfUnitPrereq(AsciiString kindOfName)
{
	m_prereqMinCountKindOfUnitsNames.push_back(kindOfName);
}

//-------------------------------------------------------------------------------------------------
void PlayerPrerequisite::addMaxCountKindOfUnitPrereq(AsciiString kindOfName)
{
	m_prereqMaxCountKindOfUnitsNames.push_back(kindOfName);
}

//-------------------------------------------------------------------------------------------------
void PlayerPrerequisite::addMinCountKindOfUnitWithLevelPrereq(AsciiString kindOfName)
{
	m_prereqMinCountKindOfUnitsWithLevelNames.push_back(kindOfName);
}

//-------------------------------------------------------------------------------------------------
void PlayerPrerequisite::addMaxCountKindOfUnitWithLevelPrereq(AsciiString kindOfName)
{
	m_prereqMaxCountKindOfUnitsWithLevelNames.push_back(kindOfName);
}

//-------------------------------------------------------------------------------------------------
// returns an asciistring which is a list of all the prerequisites
// not satisfied yet
UnicodeString PlayerPrerequisite::getRequiresList(const Player* player) const
{

	// if player is invalid, return empty string
	if (!player)
		return UnicodeString::TheEmptyString;

	UnicodeString requiresList = UnicodeString::TheEmptyString;

	// check the prerequired units
	Int ownCount[MAX_PREREQ];
	Int cnt = calcNumPrereqUnitsOwned(player, ownCount);
	Int i;

	Bool orRequirements[MAX_PREREQ];
	//Added for fix below in getRequiresList
	//By Sadullah Nader
	//Initializes the OR_WITH_PREV structures
	for (i = 0; i < MAX_PREREQ; i++)
	{
		orRequirements[i] = FALSE;
	}
	//
	// account for the "or" unit cases, start for loop at 1
	handleOrLogic(ownCount, cnt, m_prereqUnits);
	
	// Set OR requirements flags for display purposes
	for (i = 1; i < cnt; i++)
	{
		if (m_prereqUnits[i].flags & UNIT_OR_WITH_PREV)
		{
			orRequirements[i] = TRUE;     // set the flag for this unit to be "ored" with previous
		}
	}

	// check to see if anything is required
	const ThingTemplate* unit;
	UnicodeString unitName;
	Bool firstRequirement = true;
	for (i = 0; i < cnt; i++)
	{
		// we have an unfulfilled requirement
		if (ownCount[i] == 0) {

			if (orRequirements[i])
			{
				unit = m_prereqUnits[i - 1].unit;
				// TheSuperHackers @bugfix Ahmed Salah 15/01/2025 Check unit not null before using
				if (unit)
				{
					unitName = unit->getDisplayName();
					unitName.concat(L" ");
					unitName.concat(TheGameText->fetch("CONTROLBAR:OrRequirement", NULL));
					unitName.concat(L" ");
					requiresList.concat(unitName);
				}
			}

			// get the requirement and then its name
			unit = m_prereqUnits[i].unit;
			// TheSuperHackers @bugfix Ahmed Salah 15/01/2025 Check unit not null before using
			if (unit)
			{
				unitName = unit->getDisplayName();

				// gets command button, and then modifies unitName
				//CommandButton *cmdButton = TheControlBar->findCommandButton(unit->getName());
				//if (cmdButton)
					//unitName.translate(TheGameText->fetch(cmdButton->m_textLabel.str()));

				// format name appropriately with 'returns' if necessary
				if (firstRequirement)
					firstRequirement = false;
				else
					unitName.concat(L"\n");

				// add it to the list
				requiresList.concat(unitName);
			}
		}
	}

	// gotta have all the prereq sciences.
	for (i = 0; i < m_prereqSciences.size(); i++)
	{
		if (!player->hasScience(m_prereqSciences[i]))
		{
			UnicodeString scienceName, scienceDesc;
			if (TheScienceStore->getNameAndDescription(m_prereqSciences[i], scienceName, scienceDesc))
			{
				// format name appropriately with 'returns' if necessary
				if (firstRequirement)
					firstRequirement = false;
				else
					scienceName.concat(L"\n");

				// add it to the list
				requiresList.concat(scienceName);
			}
		}
	}

	// Check upgrade prerequisites
	UpgradeMaskType playerMask = player->getCompletedUpgradeMask();
	if (m_prereqUpgradesMask.any())
	{
		if (!playerMask.testForAll(m_prereqUpgradesMask))
		{
			// Check each upgrade individually to show specific names
			for (std::vector<AsciiString>::const_iterator it = m_prereqUpgradesNames.begin(); it != m_prereqUpgradesNames.end(); ++it)
			{
				const UpgradeTemplate* upgradeTemplate = TheUpgradeCenter->findUpgrade(*it);
				if (upgradeTemplate)
				{
					UpgradeMaskType upgradeMask = upgradeTemplate->getUpgradeMask();
					if (!playerMask.testForAll(upgradeMask))
					{
						UnicodeString upgradeName = TheGameText->fetch(upgradeTemplate->getDisplayNameLabel().str());

						// format name appropriately with 'returns' if necessary
						if (firstRequirement)
							firstRequirement = false;
						else
							upgradeName.concat(L"\n");

						// add it to the list
						requiresList.concat(upgradeName);
					}
				}
			}
		}
	}

	// Check KindOf prerequisites
	if (m_prereqKindOfUnitsMask.any())
	{
		if (const_cast<Player*>(player)->countObjects(m_prereqKindOfUnitsMask, KindOfMaskType()) == 0)
		{
			// Check each KindOf individually to show specific names
			for (std::vector<AsciiString>::const_iterator it = m_prereqKindOfUnitsNames.begin(); it != m_prereqKindOfUnitsNames.end(); ++it)
			{
				KindOfType kindOfType = (KindOfType)INI::scanIndexList(it->str(), KindOfMaskType::getBitNames());
				KindOfMaskType kindOfMask = MAKE_KINDOF_MASK(kindOfType);
				if (const_cast<Player*>(player)->countObjects(kindOfMask, KindOfMaskType()) == 0)
				{
					AsciiString kindOfKey;
					kindOfKey.format("KINDOF:%s", it->str());
					UnicodeString kindOfName = TheGameText->fetch(kindOfKey.str());

					// format name appropriately with 'returns' if necessary
					if (firstRequirement)
						firstRequirement = false;
					else
						kindOfName.concat(L"\n");

					// add it to the list
					requiresList.concat(kindOfName);
				}
			}
		}
	}

	// Check min count KindOf prerequisites
	for (size_t i = 0; i < m_prereqMinCountKindOfUnitsNames.size(); i++)
	{
		// Parse the string format: "KINDOFXXX 4 KINDOFYYY 3"
		AsciiString remaining = m_prereqMinCountKindOfUnitsNames[i];
		Bool hasEnough = false;
		UnicodeString missingRequirements;
		
		while (!remaining.isEmpty())
		{
			// Get the next KindOf name
			AsciiString kindOfName;
			if (!remaining.nextToken(&kindOfName, " "))
				break;
			
			// Get the count
			AsciiString countStr;
			Int count = 1;
			if (remaining.nextToken(&countStr, " "))
			{
				count = atoi(countStr.str());
			}
			else
			{
				// Last token, use remaining string
				count = atoi(remaining.str());
				remaining.clear();
			}
			
			// Check if player has enough of this KindOf type
			KindOfType kindOfType = (KindOfType)INI::scanIndexList(kindOfName.str(), KindOfMaskType::getBitNames());
			KindOfMaskType kindOfMask = MAKE_KINDOF_MASK(kindOfType);
			Int playerCount = const_cast<Player*>(player)->countObjects(kindOfMask, KindOfMaskType());
			
			if (playerCount >= count)
			{
				hasEnough = true;
				break; // At least one KindOf requirement is satisfied
			}
			else
			{
				// Add to missing requirements
				if (!missingRequirements.isEmpty())
					missingRequirements.concat(L" or ");
				missingRequirements.concat(formatKindOfDisplayText(kindOfName, count));
			}
		}
		
		if (!hasEnough)
		{
			// format name appropriately with 'returns' if necessary
			if (firstRequirement)
				firstRequirement = false;
			else
				missingRequirements.concat(L"\n");

			// add it to the list
			requiresList.concat(missingRequirements);
		}
	}

	// Check min count KindOf prerequisites with veterancy level
	for (size_t i = 0; i < m_prereqMinCountKindOfUnitsWithLevelNames.size(); i++)
	{
		// Parse the string format: "KINDOFXXX LEVEL_VETERAN 4 KINDOFYYY LEVEL_REGULAR 3"
		AsciiString remaining = m_prereqMinCountKindOfUnitsWithLevelNames[i];
		Bool hasEnough = false;
		UnicodeString missingRequirements;
		
		while (!remaining.isEmpty())
		{
			// Get the next KindOf name
			AsciiString kindOfName;
			if (!remaining.nextToken(&kindOfName, " "))
				break;
			
			// Get the veterancy level
			AsciiString levelStr;
			VeterancyLevel minLevel = LEVEL_REGULAR;
			if (remaining.nextToken(&levelStr, " "))
			{
				minLevel = (VeterancyLevel)INI::scanIndexList(levelStr.str(), TheVeterancyNames);
			}
			else
			{
				break; // Invalid format
			}
			
			// Get the count
			AsciiString countStr;
			Int count = 1;
			if (remaining.nextToken(&countStr, " "))
			{
				count = atoi(countStr.str());
			}
			else
			{
				// Last token, use remaining string
				count = atoi(remaining.str());
				remaining.clear();
			}
			
			// Check if player has enough of this KindOf type with the specified veterancy level
			KindOfType kindOfType = (KindOfType)INI::scanIndexList(kindOfName.str(), KindOfMaskType::getBitNames());
			KindOfMaskType kindOfMask = MAKE_KINDOF_MASK(kindOfType);
			Int playerCount = const_cast<Player*>(player)->countObjects(kindOfMask, KindOfMaskType(), minLevel);
			
			if (playerCount >= count)
			{
				hasEnough = true;
				break; // At least one KindOf requirement is satisfied
			}
			else
			{
				// Add to missing requirements
				if (!missingRequirements.isEmpty())
					missingRequirements.concat(L" or ");
				missingRequirements.concat(formatKindOfWithLevelDisplayText(kindOfName, levelStr, count));
			}
		}
		
		if (!hasEnough)
		{
			// format name appropriately with 'returns' if necessary
			if (firstRequirement)
				firstRequirement = false;
			else
				missingRequirements.concat(L"\n");

			// add it to the list
			requiresList.concat(missingRequirements);
		}
	}

	// return final list
	return requiresList;
}

//-------------------------------------------------------------------------------------------------
// returns an asciistring which is a list of all the conflict prerequisites
// that are currently satisfied (and thus blocking this prerequisite)
UnicodeString PlayerPrerequisite::getConflictList(const Player* player) const
{
	// if player is invalid, return empty string
	if (!player)
		return UnicodeString::TheEmptyString;

	UnicodeString conflictList = UnicodeString::TheEmptyString;

	// check the conflicting units
	Int ownCount[MAX_PREREQ];
	Int cnt = m_prereqUnitsConflict.size();
	if (cnt > MAX_PREREQ)
		cnt = MAX_PREREQ;

	// Count owned conflicting units
	for (int i = 0; i < cnt; i++)
	{
		ownCount[i] = 0;
		if (m_prereqUnitsConflict[i].unit)
		{
			player->countObjectsByThingTemplate(1, &m_prereqUnitsConflict[i].unit, false, &ownCount[i]);
		}
	}

	Int i;
	Bool orRequirements[MAX_PREREQ];
	// Initialize the OR_WITH_PREV structures
	for (i = 0; i < MAX_PREREQ; i++)
	{
		orRequirements[i] = FALSE;
	}

	// account for the "or" unit cases, start for loop at 1
	handleOrLogicConflict(ownCount, cnt, m_prereqUnitsConflict);
	
	// Set OR requirements flags for display purposes
	for (i = 1; i < cnt; i++)
	{
		if (m_prereqUnitsConflict[i].flags & UNIT_OR_WITH_PREV)
		{
			orRequirements[i] = TRUE;     // set the flag for this unit to be "ored" with previous
		}
	}

	// check to see if anything is conflicting
	const ThingTemplate* unit;
	UnicodeString unitName;
	Bool firstConflict = true;
	for (i = 0; i < cnt; i++)
	{
		// we have a conflicting requirement (player owns this unit)
		if (ownCount[i] > 0) {

			if (orRequirements[i])
			{
				unit = m_prereqUnitsConflict[i - 1].unit;
				unitName = unit->getDisplayName();
				unitName.concat(L" ");
				unitName.concat(TheGameText->fetch("CONTROLBAR:OrRequirement", NULL));
				unitName.concat(L" ");
				conflictList.concat(unitName);
			}

			// get the conflicting unit and then its name
			unit = m_prereqUnitsConflict[i].unit;
			unitName = unit->getDisplayName();

			// format name appropriately with 'returns' if necessary
			if (firstConflict)
				firstConflict = false;
			else
				unitName.concat(L"\n");

			// add it to the list
			conflictList.concat(unitName);
		}
	}

	// check for conflicting sciences
	for (i = 0; i < m_prereqSciencesConflict.size(); i++)
	{
		if (player->hasScience(m_prereqSciencesConflict[i]))
		{
			UnicodeString scienceName, scienceDesc;
			if (TheScienceStore->getNameAndDescription(m_prereqSciencesConflict[i], scienceName, scienceDesc))
			{
				// format name appropriately with 'returns' if necessary
				if (firstConflict)
					firstConflict = false;
				else
					scienceName.concat(L"\n");

				// add it to the list
				conflictList.concat(scienceName);
			}
		}
	}

	// Check conflicting upgrade prerequisites
	UpgradeMaskType playerMask = player->getCompletedUpgradeMask();
	if (m_prereqUpgradesMaskConflict.any())
	{
		if (playerMask.testForAny(m_prereqUpgradesMaskConflict))
		{
			// Check each upgrade individually to show specific names
			for (std::vector<AsciiString>::const_iterator it = m_prereqUpgradesNamesConflict.begin(); it != m_prereqUpgradesNamesConflict.end(); ++it)
			{
				const UpgradeTemplate* upgradeTemplate = TheUpgradeCenter->findUpgrade(*it);
				if (upgradeTemplate)
				{
					UpgradeMaskType upgradeMask = upgradeTemplate->getUpgradeMask();
					if (playerMask.testForAny(upgradeMask))
					{
						UnicodeString upgradeName = TheGameText->fetch(upgradeTemplate->getDisplayNameLabel().str());

						// format name appropriately with 'returns' if necessary
						if (firstConflict)
							firstConflict = false;
						else
							upgradeName.concat(L"\n");

						// add it to the list
						conflictList.concat(upgradeName);
					}
				}
			}
		}
	}

	// Check conflicting KindOf prerequisites
	if (m_prereqKindOfUnitsMaskConflict.any())
	{
		if (const_cast<Player*>(player)->countObjects(m_prereqKindOfUnitsMaskConflict, KindOfMaskType()) > 0)
		{
			// Check each KindOf individually to show specific names
			for (std::vector<AsciiString>::const_iterator it = m_prereqKindOfUnitsNamesConflict.begin(); it != m_prereqKindOfUnitsNamesConflict.end(); ++it)
			{
				KindOfType kindOfType = (KindOfType)INI::scanIndexList(it->str(), KindOfMaskType::getBitNames());
				KindOfMaskType kindOfMask = MAKE_KINDOF_MASK(kindOfType);
				if (const_cast<Player*>(player)->countObjects(kindOfMask, KindOfMaskType()) > 0)
				{
					AsciiString kindOfKey;
					kindOfKey.format("KINDOF:%s", it->str());
					UnicodeString kindOfName = TheGameText->fetch(kindOfKey.str());

					// format name appropriately with 'returns' if necessary
					if (firstConflict)
						firstConflict = false;
					else
						kindOfName.concat(L"\n");

					// add it to the list
					conflictList.concat(kindOfName);
				}
			}
		}
	}

	// Check max count KindOf prerequisites
	for (size_t i = 0; i < m_prereqMaxCountKindOfUnitsNames.size(); i++)
	{
		// Parse the string format: "KINDOFXXX 4 KINDOFYYY 3"
		AsciiString remaining = m_prereqMaxCountKindOfUnitsNames[i];
		Bool hasMaxCount = false;
		UnicodeString missingRequirements;

		while (!remaining.isEmpty())
		{
			// Get the next KindOf name
			AsciiString kindOfName;
			if (!remaining.nextToken(&kindOfName, " "))
				break;

			// Get the count
			AsciiString countStr;
			Int count = 1;
			if (remaining.nextToken(&countStr, " "))
			{
				count = atoi(countStr.str());
			}
			else
			{
				// Last token, use remaining string
				count = atoi(remaining.str());
				remaining.clear();
			}

			// Check if player has the maximum count of this KindOf type
			KindOfType kindOfType = (KindOfType)INI::scanIndexList(kindOfName.str(), KindOfMaskType::getBitNames());
			KindOfMaskType kindOfMask = MAKE_KINDOF_MASK(kindOfType);
			Int playerCount = const_cast<Player*>(player)->countObjects(kindOfMask, KindOfMaskType());

			if (playerCount >= count)
			{
				hasMaxCount = true;
				// Add to missing requirements
				if (!missingRequirements.isEmpty())
					missingRequirements.concat(L" or ");
				missingRequirements.concat(formatKindOfDisplayText(kindOfName, count));
			}			
		}

		if (hasMaxCount)
		{
			conflictList.concat(missingRequirements);
			
		}
	}

	// Check max count KindOf prerequisites with veterancy level
	for (size_t i = 0; i < m_prereqMaxCountKindOfUnitsWithLevelNames.size(); i++)
	{
		// Parse the string format: "KINDOFXXX LEVEL_VETERAN 4 KINDOFYYY LEVEL_REGULAR 3"
		AsciiString remaining = m_prereqMaxCountKindOfUnitsWithLevelNames[i];
		Bool hasMaxCount = false;
		UnicodeString missingRequirements;
		
		while (!remaining.isEmpty())
		{
			// Get the next KindOf name
			AsciiString kindOfName;
			if (!remaining.nextToken(&kindOfName, " "))
				break;
			
			// Get the veterancy level
			AsciiString levelStr;
			VeterancyLevel minLevel = LEVEL_REGULAR;
			if (remaining.nextToken(&levelStr, " "))
			{
				minLevel = (VeterancyLevel)INI::scanIndexList(levelStr.str(), TheVeterancyNames);
			}
			else
			{
				break; // Invalid format
			}
			
			// Get the count
			AsciiString countStr;
			Int count = 1;
			if (remaining.nextToken(&countStr, " "))
			{
				count = atoi(countStr.str());
			}
			else
			{
				// Last token, use remaining string
				count = atoi(remaining.str());
				remaining.clear();
			}
			
			// Check if player has the maximum count of this KindOf type with the specified veterancy level
			KindOfType kindOfType = (KindOfType)INI::scanIndexList(kindOfName.str(), KindOfMaskType::getBitNames());
			KindOfMaskType kindOfMask = MAKE_KINDOF_MASK(kindOfType);
			Int playerCount = const_cast<Player*>(player)->countObjects(kindOfMask, KindOfMaskType(), minLevel);
			
			if (playerCount >= count)
			{
				hasMaxCount = true;
				// Add to missing requirements
				if (!missingRequirements.isEmpty())
					missingRequirements.concat(L" or ");
				missingRequirements.concat(formatKindOfWithLevelDisplayText(kindOfName, levelStr, count));
			}
		}
		
		if (hasMaxCount)
		{
			conflictList.concat(missingRequirements);
		}
	}

	// return final list
	return conflictList;
}



//-------------------------------------------------------------------------------------------------
// TheSuperHackers @refactor author 15/01/2025 Made parsePrerequisites generic with optional resolveNames parameter
void PlayerPrerequisite::parsePrerequisites(INI* ini, void* instance, void* store, const void* userData)
{
	// This function is designed to work with offsetof - instance points directly to the vector
	std::vector<PlayerPrerequisite>* prereqVector = (std::vector<PlayerPrerequisite>*)instance;

	static const FieldParse myFieldParse[] =
	{
		{ "Object", PlayerPrerequisite::parsePrerequisiteUnit, 0, 0 },// to support backward compatibility
		{ "Science", PlayerPrerequisite::parsePrerequisiteScience,	0, 0 },// to support backward compatibility

		{ "PlayerObjectExists", PlayerPrerequisite::parsePrerequisiteUnit, 0, 0 },
		{ "PlayerObjectNotExist", PlayerPrerequisite::parsePrerequisiteUnitConflict, 0, 0 },

		{ "PlayerScienceExists", PlayerPrerequisite::parsePrerequisiteScience,	0, 0 },
		{ "PlayerScienceNotExist", PlayerPrerequisite::parsePrerequisiteScienceConflict,	0, 0 },
		
		{ "PlayerUpgradeExist", PlayerPrerequisite::parsePrerequisiteUpgrade, 0, 0 },
		{ "PlayerUpgradeNotExist", PlayerPrerequisite::parsePrerequisiteUpgradeConflict, 0, 0 },

		{ "PlayerKindOfObjectExists", PlayerPrerequisite::parsePrerequisiteKindOfUnit, 	0, 0 },
		{ "PlayerObjectKindOfNotExist", PlayerPrerequisite::parsePrerequisiteKindOfUnitConflict, 	0, 0 },

		{ "PlayerMinCountKindOfObjectExist", PlayerPrerequisite::parsePrerequisiteMinCountKindOfUnit, 	0, 0 },
		{ "PlayerMaxCountKindOfObjectExist", PlayerPrerequisite::parsePrerequisiteMaxCountKindOfUnit, 	0, 0 },

		{ "PlayerMinCountKindOfObjectWithLevelExist", PlayerPrerequisite::parsePrerequisiteMinCountKindOfUnitWithLevel, 	0, 0 },
		{ "PlayerMaxCountKindOfObjectWithLevelExist", PlayerPrerequisite::parsePrerequisiteMaxCountKindOfUnitWithLevel, 	0, 0 },

		
		{ 0, 0, 0, 0 }
	};

	if (ini->getLoadType() == INI_LOAD_CREATE_OVERRIDES)
	{
		prereqVector->clear();
	}

	ini->initFromINI(prereqVector, myFieldParse);

}




void PlayerPrerequisite::parsePrerequisiteUnit(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<PlayerPrerequisite>* v = (std::vector<PlayerPrerequisite>*)instance;

	PlayerPrerequisite prereq;
	Bool orUnitWithPrevious = FALSE;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addUnitPrereq(AsciiString(token), orUnitWithPrevious);
		orUnitWithPrevious = TRUE;
	}

	v->push_back(prereq);
}
//-------------------------------------------------------------------------------------------------
void PlayerPrerequisite::parsePrerequisiteScience(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<PlayerPrerequisite>* v = (std::vector<PlayerPrerequisite>*)instance;

	PlayerPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addSciencePrereq(INI::scanScience(token));
	}

	v->push_back(prereq);
}


void PlayerPrerequisite::parsePrerequisiteUnitConflict(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<PlayerPrerequisite>* v = (std::vector<PlayerPrerequisite>*)instance;

	PlayerPrerequisite prereq;
	Bool orUnitWithPrevious = FALSE;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addUnitPrereqConflict(AsciiString(token), orUnitWithPrevious);
		orUnitWithPrevious = TRUE;
	}

	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void PlayerPrerequisite::parsePrerequisiteScienceConflict(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<PlayerPrerequisite>* v = (std::vector<PlayerPrerequisite>*)instance;

	PlayerPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addSciencePrereqConflict(INI::scanScience(token));
	}

	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void PlayerPrerequisite::parsePrerequisiteUpgrade(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<PlayerPrerequisite>* v = (std::vector<PlayerPrerequisite>*)instance;

	PlayerPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addUpgradePrereq(AsciiString(token));
	}

	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void PlayerPrerequisite::parsePrerequisiteUpgradeConflict(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<PlayerPrerequisite>* v = (std::vector<PlayerPrerequisite>*)instance;

	PlayerPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addUpgradePrereqConflict(AsciiString(token));
	}

	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void PlayerPrerequisite::parsePrerequisiteKindOfUnit(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<PlayerPrerequisite>* v = (std::vector<PlayerPrerequisite>*)instance;

	PlayerPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addKindOfUnitPrereq(AsciiString(token));
	}

	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void PlayerPrerequisite::parsePrerequisiteKindOfUnitConflict(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<PlayerPrerequisite>* v = (std::vector<PlayerPrerequisite>*)instance;

	PlayerPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addKindOfUnitPrereqConflict(AsciiString(token));
	}

	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void PlayerPrerequisite::parsePrerequisiteMinCountKindOfUnit(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<PlayerPrerequisite>* v = (std::vector<PlayerPrerequisite>*)instance;

	PlayerPrerequisite prereq;
	// Parse the entire line as one token (e.g., "TANK 4 STRUCTURE 3")
	AsciiString fullLine = parseFullLineFromINI(ini);
	prereq.addMinCountKindOfUnitPrereq(fullLine);

	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void PlayerPrerequisite::parsePrerequisiteMaxCountKindOfUnit(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<PlayerPrerequisite>* v = (std::vector<PlayerPrerequisite>*)instance;

	PlayerPrerequisite prereq;
	// Parse the entire line as one token (e.g., "TANK 4 STRUCTURE 3")
	AsciiString fullLine = parseFullLineFromINI(ini);
	prereq.addMaxCountKindOfUnitPrereq(fullLine);

	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void PlayerPrerequisite::parsePrerequisiteMinCountKindOfUnitWithLevel(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<PlayerPrerequisite>* v = (std::vector<PlayerPrerequisite>*)instance;

	PlayerPrerequisite prereq;
	// Parse the entire line as one token (e.g., "TANK LEVEL_VETERAN 4 STRUCTURE LEVEL_REGULAR 3")
	AsciiString fullLine = parseFullLineFromINI(ini);
	prereq.addMinCountKindOfUnitWithLevelPrereq(fullLine);

	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void PlayerPrerequisite::parsePrerequisiteMaxCountKindOfUnitWithLevel(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<PlayerPrerequisite>* v = (std::vector<PlayerPrerequisite>*)instance;

	PlayerPrerequisite prereq;
	// Parse the entire line as one token (e.g., "TANK LEVEL_VETERAN 4 STRUCTURE LEVEL_REGULAR 3")
	AsciiString fullLine = parseFullLineFromINI(ini);
	prereq.addMaxCountKindOfUnitWithLevelPrereq(fullLine);

	v->push_back(prereq);
}

//=============================================================================
// Helper methods for refactoring repeated code
//=============================================================================

//-------------------------------------------------------------------------------------------------
// Parse entire line from INI as a single token
AsciiString PlayerPrerequisite::parseFullLineFromINI(INI* ini)
{
	AsciiString fullLine;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		if (!fullLine.isEmpty())
			fullLine.concat(" ");
		fullLine.concat(token);
	}
	return fullLine;
}

//-------------------------------------------------------------------------------------------------
// Handle OR logic for regular prerequisites
void PlayerPrerequisite::handleOrLogic(Int ownCount[], Int cnt, const std::vector<PrereqUnitRec>& prereqUnits)
{
	// fix up the "or" cases. (start at 1!)
	for (Int i = 1; i < cnt; i++)
	{
		if (prereqUnits[i].flags & UNIT_OR_WITH_PREV)
		{
			ownCount[i] += ownCount[i - 1];	// lump 'em together for prereq purposes
			ownCount[i - 1] = -1;						// flag for "ignore me"
		}
	}
}

//-------------------------------------------------------------------------------------------------
// Handle OR logic for conflict prerequisites
void PlayerPrerequisite::handleOrLogicConflict(Int ownCount[], Int cnt, const std::vector<PrereqUnitRec>& prereqUnits)
{
	// fix up the "or" cases. (start at 1!)
	for (Int i = 1; i < cnt; i++)
	{
		if (prereqUnits[i].flags & UNIT_OR_WITH_PREV)
		{
			ownCount[i] += ownCount[i - 1];	// lump 'em together for conflict purposes
			ownCount[i - 1] = -1;						// flag for "ignore me"
		}
	}
}

//-------------------------------------------------------------------------------------------------
// Parse KindOf name and count pair from string
Bool PlayerPrerequisite::parseKindOfCountPair(AsciiString& remaining, AsciiString& kindOfName, Int& count)
{
	// Get the next KindOf name
	if (!remaining.nextToken(&kindOfName, " "))
		return false;
	
	// Get the count
	AsciiString countStr;
	count = 1;
	if (remaining.nextToken(&countStr, " "))
	{
		count = atoi(countStr.str());
	}
	else
	{
		// Last token, use remaining string
		count = atoi(remaining.str());
		remaining.clear();
	}
	return true;
}

//-------------------------------------------------------------------------------------------------
// Parse KindOf name, level, and count triple from string
Bool PlayerPrerequisite::parseKindOfLevelCountTriple(AsciiString& remaining, AsciiString& kindOfName, AsciiString& levelStr, Int& count)
{
	// Get the next KindOf name
	if (!remaining.nextToken(&kindOfName, " "))
		return false;
	
	// Get the veterancy level
	if (!remaining.nextToken(&levelStr, " "))
		return false;
	
	// Get the count
	AsciiString countStr;
	count = 1;
	if (remaining.nextToken(&countStr, " "))
	{
		count = atoi(countStr.str());
	}
	else
	{
		// Last token, use remaining string
		count = atoi(remaining.str());
		remaining.clear();
	}
	return true;
}

//-------------------------------------------------------------------------------------------------
// Format KindOf display text
UnicodeString PlayerPrerequisite::formatKindOfDisplayText(const AsciiString& kindOfName, Int count)
{
	UnicodeString result;
	// Convert count to UnicodeString using format
	UnicodeString countStr;
	countStr.format(L"%d", count);
	result.concat(countStr);
	result.concat(L" of ");
	
	// Add KindOf display name
	AsciiString kindOfKey;
	kindOfKey.format("KINDOF:%s", kindOfName.str());
	UnicodeString kindOfDisplayName = TheGameText->fetch(kindOfKey.str());
	kindOfDisplayName.toLower();
	result.concat(kindOfDisplayName);
	
	return result;
}

//-------------------------------------------------------------------------------------------------
// Format KindOf with level display text
UnicodeString PlayerPrerequisite::formatKindOfWithLevelDisplayText(const AsciiString& kindOfName, const AsciiString& levelStr, Int count)
{
	UnicodeString result;
	// Convert count to UnicodeString using format
	UnicodeString countStr;
	countStr.format(L"%d", count);
	result.concat(countStr);
	result.concat(L" of ");
	
	// Add KindOf display name
	AsciiString kindOfKey;
	kindOfKey.format("KINDOF:%s", kindOfName.str());
	UnicodeString kindOfDisplayName = TheGameText->fetch(kindOfKey.str());
	kindOfDisplayName.toLower();
	result.concat(kindOfDisplayName);
	
	// Add veterancy level display name in parentheses
	result.concat(L" (");
	AsciiString levelKey;
	levelKey.format("VETERANCY:%s", levelStr.str());
	UnicodeString levelDisplayName = TheGameText->fetch(levelKey.str());
	levelDisplayName.toLower();
	result.concat(levelDisplayName);
	result.concat(L")");
	
	return result;
}


