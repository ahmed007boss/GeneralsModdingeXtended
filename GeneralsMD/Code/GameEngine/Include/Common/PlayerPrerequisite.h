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

// FILE: PlayerPrerequisite.h //////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//
//                       Westwood Studios Pacific.
//
//                       Confidential Information
//                Copyright (C) 2001 - All Rights Reserved
//
//-----------------------------------------------------------------------------
//
// Project:    RTS3
//
// File name:  GameConditions.h
//
// Created:    Steven Johnson, October 2001
// Refactored: TheSuperHackers @refactor author 15/01/2025 Extracted base class from ProductionPrerequisite
//
//-----------------------------------------------------------------------------

#pragma once

#ifndef __PlayerPrerequisite_H_
#define __PlayerPrerequisite_H_

//-----------------------------------------------------------------------------
//           Includes
//-----------------------------------------------------------------------------
#include "Lib/BaseType.h"
#include "Common/GameMemory.h"
#include "Common/GameCommon.h"
#include "Common/Science.h"

//-----------------------------------------------------------------------------
class ThingTemplate;
class Player;

//-----------------------------------------------------------------------------
// TheSuperHackers @refactor author 15/01/2025 Base class for all player prerequisite checking (prerequisites, requirements, etc.)
class PlayerPrerequisite
{
public:

	PlayerPrerequisite();
	virtual ~PlayerPrerequisite();

	/// init to safe default values.
	void init();

	void resetSciences(void) { m_prereqSciences.clear(); }
	void addSciencePrereq(ScienceType science) { m_prereqSciences.push_back(science); }

	void resetUnits(void) { m_prereqUnits.clear(); }
	void addUnitPrereq(AsciiString units, Bool orUnitWithPrevious);
	void addUnitPrereq(const std::vector<AsciiString>& units);


	void resetSciencesConflict(void) { m_prereqSciencesConflict.clear(); }
	void addSciencePrereqConflict(ScienceType science) { m_prereqSciencesConflict.push_back(science); }

	void resetUnitsConflict(void) { m_prereqUnitsConflict.clear(); }
	void addUnitPrereqConflict(AsciiString units, Bool orUnitWithPrevious);
	void addUnitPrereqConflict(const std::vector<AsciiString>& units);

	void resetUpgrades(void) { m_prereqUpgradesNames.clear(); m_prereqUpgradesMask.clear(); }
	void addUpgradePrereq(AsciiString upgrade);

	void resetUpgradesConflict(void) { m_prereqUpgradesNamesConflict.clear(); m_prereqUpgradesMaskConflict.clear(); }
	void addUpgradePrereqConflict(AsciiString upgrade);

	void resetKindOfUnits(void) { m_prereqKindOfUnitsNames.clear(); m_prereqKindOfUnitsMask.clear(); }
	void addKindOfUnitPrereq(AsciiString kindOfName);

	void resetKindOfUnitsConflict(void) { m_prereqKindOfUnitsNamesConflict.clear(); m_prereqKindOfUnitsMaskConflict.clear(); }
	void addKindOfUnitPrereqConflict(AsciiString kindOfName);

	void resetMinCountKindOfUnits(void) { m_prereqMinCountKindOfUnitsNames.clear(); }
	void addMinCountKindOfUnitPrereq(AsciiString kindOfName);

	void resetMaxCountKindOfUnits(void) { m_prereqMaxCountKindOfUnitsNames.clear(); }
	void addMaxCountKindOfUnitPrereq(AsciiString kindOfName);

	void resetMinCountKindOfUnitsWithLevel(void) { m_prereqMinCountKindOfUnitsWithLevelNames.clear(); }
	void addMinCountKindOfUnitWithLevelPrereq(AsciiString kindOfName);

	void resetMaxCountKindOfUnitsWithLevel(void) { m_prereqMaxCountKindOfUnitsWithLevelNames.clear(); }
	void addMaxCountKindOfUnitWithLevelPrereq(AsciiString kindOfName);


	/// called after all ThingTemplates have been loaded.
	virtual void resolveNames();

	/// returns an asciistring which is a list of all the prerequisites
	/// not satisfied yet
	virtual UnicodeString getRequiresList(const Player *player) const;

	/// returns an asciistring which is a list of all the conflict prerequisites
	/// that are currently satisfied (and thus blocking this prerequisite)
	virtual UnicodeString getConflictList(const Player *player) const;

	/// return true iff the player satisfies our set of prerequisites
	virtual Bool isSatisfied(const Player *player) const;

	/**
		return the BuildFacilityTemplate, if any.

		if this template needs no build facility, null is returned.

		if the template needs a build facility but the given player doesn't have any in existence,
		null will be returned.

		you may not pass 'null' for player.
	*/
	const ThingTemplate *getExistingBuildFacilityTemplate( const Player *player ) const;

	Int getAllPossibleBuildFacilityTemplates(const ThingTemplate* tmpls[], Int maxtmpls) const;


	static void parsePrerequisites(INI* ini, void* instance, void* store, const void* userData);

protected:

	enum
	{
		UNIT_OR_WITH_PREV = 0x01	// if set, unit is "or-ed" with prev unit, so that either one's presence satisfies
	};

	struct PrereqUnitRec
	{
		const ThingTemplate*	unit;
		Int										flags;
		AsciiString						name;
	};

	enum { MAX_PREREQ = 32 };
	Int calcNumPrereqUnitsOwned(const Player *player, Int counts[MAX_PREREQ]) const;

	std::vector<PrereqUnitRec>	m_prereqUnits;
	ScienceVec									m_prereqSciences;

	std::vector<PrereqUnitRec>	m_prereqUnitsConflict;
	ScienceVec									m_prereqSciencesConflict;

	mutable std::vector<AsciiString>	m_prereqUpgradesNames;
	mutable UpgradeMaskType						m_prereqUpgradesMask;

	mutable std::vector<AsciiString>	m_prereqUpgradesNamesConflict;
	mutable UpgradeMaskType						m_prereqUpgradesMaskConflict;

	mutable std::vector<AsciiString>	m_prereqKindOfUnitsNames;
	mutable KindOfMaskType						m_prereqKindOfUnitsMask;

	mutable std::vector<AsciiString>	m_prereqKindOfUnitsNamesConflict;
	mutable KindOfMaskType						m_prereqKindOfUnitsMaskConflict;

	mutable std::vector<AsciiString>	m_prereqMinCountKindOfUnitsNames;
	mutable std::vector<AsciiString>	m_prereqMaxCountKindOfUnitsNames;

	mutable std::vector<AsciiString>	m_prereqMinCountKindOfUnitsWithLevelNames;
	mutable std::vector<AsciiString>	m_prereqMaxCountKindOfUnitsWithLevelNames;

	mutable Bool						m_namesResolved;	// TheSuperHackers @feature Ahmed Salah 15/01/2025 Track if names have been resolved for lazy initialization

private :
	static void parsePrerequisiteScience(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parsePrerequisiteUnit(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parsePrerequisiteScienceConflict(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parsePrerequisiteUnitConflict(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parsePrerequisiteUpgrade(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parsePrerequisiteUpgradeConflict(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parsePrerequisiteKindOfUnit(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parsePrerequisiteKindOfUnitConflict(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parsePrerequisiteMinCountKindOfUnit(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parsePrerequisiteMaxCountKindOfUnit(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parsePrerequisiteMinCountKindOfUnitWithLevel(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parsePrerequisiteMaxCountKindOfUnitWithLevel(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);

	// Helper methods for refactoring repeated code
	static AsciiString parseFullLineFromINI(INI* ini);
	static void handleOrLogic(Int ownCount[], Int cnt, const std::vector<PrereqUnitRec>& prereqUnits);
	static void handleOrLogicConflict(Int ownCount[], Int cnt, const std::vector<PrereqUnitRec>& prereqUnits);
	static Bool parseKindOfCountPair(AsciiString& remaining, AsciiString& kindOfName, Int& count);
	static Bool parseKindOfLevelCountTriple(AsciiString& remaining, AsciiString& kindOfName, AsciiString& levelStr, Int& count);
	static UnicodeString formatKindOfDisplayText(const AsciiString& kindOfName, Int count);
	static UnicodeString formatKindOfWithLevelDisplayText(const AsciiString& kindOfName, const AsciiString& levelStr, Int count);

};

//-----------------------------------------------------------------------------

#endif
