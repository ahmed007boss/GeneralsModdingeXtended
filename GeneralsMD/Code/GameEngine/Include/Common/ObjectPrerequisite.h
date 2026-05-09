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

// FILE: ObjectPrerequisite.h /////////////////////////////////////////////////////////
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
// File name: ObjectPrerequisite.h
//
// Created:   Steven Johnson, October 2001
//
// Desc:      Object-based prerequisite system for checking conditions on specific objects
//
//-----------------------------------------------------------------------------

#ifndef OBJECTPREREQUISITE_H
#define OBJECTPREREQUISITE_H

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

#include "Lib/BaseType.h"
#include "Common/ThingTemplate.h"
#include "Common/KindOf.h"
#include "Common/Upgrade.h"
#include "GameLogic/Object.h"

//-----------------------------------------------------------------------------
// forward declarations
//-----------------------------------------------------------------------------

class INI;
class Player;
class ThingTemplate;
class UpgradeTemplate;

//-----------------------------------------------------------------------------
// ObjectPrerequisite class
//-----------------------------------------------------------------------------

class ObjectPrerequisite
{
public:
	ObjectPrerequisite();
	~ObjectPrerequisite();

	void init();
	void resolveNames();

	Bool isSatisfied(const Object* object) const;

	UnicodeString getRequiresList(const Object* object) const;
	UnicodeString getConflictList(const Object* object) const;

	// Object type prerequisites
	void addObjectIsPrereq(AsciiString objectName);
	void addObjectIsNotPrereq(AsciiString objectName);

	// KindOf prerequisites
	void addObjectIsKindOfPrereq(AsciiString kindOfName);
	void addObjectIsNoKindOfPrereq(AsciiString kindOfName);

	// Upgrade prerequisites
	void addObjectHasUpgradePrereq(AsciiString upgradeName);
	void addObjectHasNotUpgradePrereq(AsciiString upgradeName);

	// Level prerequisites
	void addObjectLevelMoreThanPrereq(Int level);
	void addObjectLevelLessThanPrereq(Int level);

	// Nearby object prerequisites
	void addObjectHasNearbyObjectPrereq(AsciiString objectName, Real distance);
	void addObjectHasNearbyKindOfPrereq(AsciiString kindOfName, Real distance);
	void addObjectHasNoNearbyObjectPrereq(AsciiString objectName, Real distance);
	void addObjectHasNoNearbyKindOfPrereq(AsciiString kindOfName, Real distance);

	// Model condition flag prerequisites
	void addObjectHasModelConditionFlagPrereq(AsciiString modelConditionFlagName);
	void addObjectHasNoModelConditionFlagPrereq(AsciiString modelConditionFlagName);

	// Status flag prerequisites
	void addObjectHasStatusFlagPrereq(AsciiString statusFlagName);
	void addObjectHasNoStatusFlagPrereq(AsciiString statusFlagName);

	// Component prerequisites
	void addObjectHasComponentPrereq(AsciiString componentName);
	void addObjectHasNoComponentPrereq(AsciiString componentName);
	void addObjectHasWorkingComponentPrereq(AsciiString componentName);
	void addObjectHasNoWorkingComponentPrereq(AsciiString componentName);

	// Inventory item prerequisites
	void addObjectHasAtLeastItemPrereq(AsciiString itemName, Int count);
	void addObjectHasAtMostItemPrereq(AsciiString itemName, Int count);
	void addObjectItemStorageFullPrereq(AsciiString itemName);
	void addObjectItemStorageNotFullPrereq(AsciiString itemName);
	void addObjectItemStorageEmptyPrereq(AsciiString itemName);

	// Static parsing function
	static void parseObjectPrerequisites(INI* ini, void* instance, void* store, const void* userData);

private:
	// Object type prerequisites
	mutable std::vector<AsciiString>	m_objectIsNames;
	mutable std::vector<const ThingTemplate*>	m_objectIsTemplates;
	mutable std::vector<AsciiString>	m_objectIsNotNames;
	mutable std::vector<const ThingTemplate*>	m_objectIsNotTemplates;

	// KindOf prerequisites
	mutable std::vector<AsciiString>	m_objectIsKindOfNames;
	mutable KindOfMaskType				m_objectIsKindOfMask;
	mutable std::vector<AsciiString>	m_objectIsNoKindOfNames;
	mutable KindOfMaskType				m_objectIsNoKindOfMask;

	// Upgrade prerequisites
	mutable std::vector<AsciiString>	m_objectHasUpgradeNames;
	mutable UpgradeMaskType				m_objectHasUpgradeMask;
	mutable std::vector<AsciiString>	m_objectHasNotUpgradeNames;
	mutable UpgradeMaskType				m_objectHasNotUpgradeMask;

	// Level prerequisites
	mutable Int							m_objectLevelMoreThan;
	mutable Int							m_objectLevelLessThan;

	// Model condition flag prerequisites
	mutable std::vector<AsciiString>	m_objectHasModelConditionFlagNames;
	mutable std::vector<AsciiString>	m_objectHasNoModelConditionFlagNames;
	mutable ModelConditionFlags	m_objectHasModelConditionFlags;
	mutable ModelConditionFlags	m_objectHasNoModelConditionFlags;

	// Status flag prerequisites
	mutable std::vector<AsciiString>	m_objectHasStatusFlagNames;
	mutable std::vector<AsciiString>	m_objectHasNoStatusFlagNames;
	mutable ObjectStatusMaskType	m_objectHasStatusFlags;
	mutable ObjectStatusMaskType	m_objectHasNoStatusFlags;

	// Component prerequisites
	mutable std::vector<AsciiString>	m_objectHasComponentNames;
	mutable std::vector<AsciiString>	m_objectHasNoComponentNames;
	mutable std::vector<AsciiString>	m_objectHasWorkingComponentNames;
	mutable std::vector<AsciiString>	m_objectHasNoWorkingComponentNames;

	// Nearby object prerequisites
	struct NearbyObjectPrereq
	{
		AsciiString objectName;
		const ThingTemplate* objectTemplate;
		Real distance;
		Bool isKindOf;
		AsciiString kindOfName;
		KindOfMaskType kindOfMask;
	};

	mutable std::vector<NearbyObjectPrereq>	m_objectHasNearbyObjects;
	mutable std::vector<NearbyObjectPrereq>	m_objectHasNoNearbyObjects;

	// Inventory item prerequisites
	struct ItemCountPrereq
	{
		AsciiString itemName;
		Int requiredCount;
	};

	mutable std::vector<ItemCountPrereq>	m_objectHasAtLeastItems;
	mutable std::vector<ItemCountPrereq>	m_objectHasAtMostItems;
	mutable std::vector<AsciiString>		m_objectItemStorageFull;
	mutable std::vector<AsciiString>		m_objectItemStorageNotFull;
	mutable std::vector<AsciiString>		m_objectItemStorageEmpty;

	mutable Bool							m_namesResolved;	// TheSuperHackers @feature Ahmed Salah 15/01/2025 Track if names have been resolved for lazy initialization

	// Helper methods
	static void parseObjectIs(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parseObjectIsNot(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parseObjectIsKindOf(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parseObjectIsNoKindOf(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parseObjectHasUpgrade(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parseObjectHasNotUpgrade(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parseObjectLevelMoreThan(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parseObjectLevelLessThan(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parseObjectHasNearbyObject(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parseObjectHasNearbyKindOf(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parseObjectHasNoNearbyObject(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parseObjectHasNoNearbyKindOf(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parseObjectHasModelConditionFlag(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parseObjectHasNoModelConditionFlag(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parseObjectHasStatusFlag(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parseObjectHasNoStatusFlag(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parseObjectHasComponent(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parseObjectHasNoComponent(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parseObjectHasWorkingComponent(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parseObjectHasNoWorkingComponent(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parseHasAtLeastItem(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parseHasAtMostItem(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parseItemStorageFull(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parseItemStorageNotFull(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parseItemStorageEmpty(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);

	// Helper methods for refactoring repeated code
	static AsciiString parseFullLineFromINI(INI* ini);
	static Bool parseObjectDistancePair(AsciiString& remaining, AsciiString& objectName, Real& distance);
	static Bool parseKindOfDistancePair(AsciiString& remaining, AsciiString& kindOfName, Real& distance);
	static Bool parseItemCountPair(AsciiString& remaining, AsciiString& itemName, Int& count);
	static UnicodeString formatObjectDisplayText(const AsciiString& objectName);
	static UnicodeString formatKindOfDisplayText(const AsciiString& kindOfName);
	static UnicodeString formatDistanceDisplayText(Real distance);
	static UnicodeString formatModelConditionFlagDisplayText(const AsciiString& modelConditionFlagName);
	static UnicodeString formatStatusFlagDisplayText(const AsciiString& statusFlagName);
};

//-----------------------------------------------------------------------------

#endif
