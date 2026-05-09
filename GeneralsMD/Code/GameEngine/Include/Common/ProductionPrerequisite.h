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

// FILE: ProductionPrerequisite.h //////////////////////////////////////////////////////
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
// File name:  ProductionPrerequisite.h
//
// Created:    Steven Johnson, October 2001
//
//-----------------------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------------------
//           Includes
//-----------------------------------------------------------------------------
#include "Lib/BaseType.h"
#include "Common/GameMemory.h"
#include "Common/GameCommon.h"
#include "Common/Science.h"
#include "Common/PlayerPrerequisite.h"
#include "Common/ObjectPrerequisite.h"
//#include "GameClient/ControlBar.h"

//-----------------------------------------------------------------------------
class ThingTemplate;
class Player;
class Object;

//-----------------------------------------------------------------------------
// TheSuperHackers @feature Ahmed Salah 15/01/2025 ProductionPrerequisite now inherits from both PlayerPrerequisite and ObjectPrerequisite
class ProductionPrerequisite : public PlayerPrerequisite, public ObjectPrerequisite
{
public:

	ProductionPrerequisite();
	~ProductionPrerequisite();

	// TheSuperHackers @feature Ahmed Salah 15/01/2025 Override resolveNames to call both base classes
	virtual void resolveNames();

	// TheSuperHackers @feature Ahmed Salah 15/01/2025 Combined methods that check both player and object prerequisites
	UnicodeString getRequiresList(const Player* player, const Object* object) const;
	UnicodeString getConflictList(const Player* player, const Object* object) const;
	Bool isSatisfied(const Player* player, const Object* object) const;

	// All functionality is now inherited from PlayerPrerequisite and ObjectPrerequisite base classes
	// Static parsing functions delegate to base class
	static void parsePrerequisites(INI* ini, void* instance, void* store, const void* userData);

private:
	static void parsePrerequisiteScience(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parsePrerequisiteUnit(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parsePrerequisiteScienceConflict(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parsePrerequisiteUnitConflict(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parsePrerequisiteUpgrade(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	static void parsePrerequisiteUpgradeConflict(INI* ini, void* instance, void* /*store*/, const void* /*userData*/);
	
	// TheSuperHackers @feature Ahmed Salah 15/01/2025 Wrapper methods for PlayerPrerequisite parsing methods
	static void parsePrerequisiteKindOfUnit(INI* ini, void* instance, void* store, const void* userData);
	static void parsePrerequisiteKindOfUnitConflict(INI* ini, void* instance, void* store, const void* userData);
	static void parsePrerequisiteMinCountKindOfUnit(INI* ini, void* instance, void* store, const void* userData);
	static void parsePrerequisiteMaxCountKindOfUnit(INI* ini, void* instance, void* store, const void* userData);
	static void parsePrerequisiteMinCountKindOfUnitWithLevel(INI* ini, void* instance, void* store, const void* userData);
	static void parsePrerequisiteMaxCountKindOfUnitWithLevel(INI* ini, void* instance, void* store, const void* userData);
	
	// TheSuperHackers @feature Ahmed Salah 15/01/2025 Wrapper methods for ObjectPrerequisite parsing methods
	static void parseObjectIs(INI* ini, void* instance, void* store, const void* userData);
	static void parseObjectIsNot(INI* ini, void* instance, void* store, const void* userData);
	static void parseObjectIsKindOf(INI* ini, void* instance, void* store, const void* userData);
	static void parseObjectIsNoKindOf(INI* ini, void* instance, void* store, const void* userData);
	static void parseObjectHasUpgrade(INI* ini, void* instance, void* store, const void* userData);
	static void parseObjectHasNotUpgrade(INI* ini, void* instance, void* store, const void* userData);
	static void parseObjectLevelMoreThan(INI* ini, void* instance, void* store, const void* userData);
	static void parseObjectLevelLessThan(INI* ini, void* instance, void* store, const void* userData);
	static void parseObjectHasNearbyObject(INI* ini, void* instance, void* store, const void* userData);
	static void parseObjectHasNearbyKindOf(INI* ini, void* instance, void* store, const void* userData);
	static void parseObjectHasNoNearbyObject(INI* ini, void* instance, void* store, const void* userData);
	static void parseObjectHasNoNearbyKindOf(INI* ini, void* instance, void* store, const void* userData);
	static void parseObjectHasModelConditionFlag(INI* ini, void* instance, void* store, const void* userData);
	static void parseObjectHasNoModelConditionFlag(INI* ini, void* instance, void* store, const void* userData);
	static void parseObjectHasStatusFlag(INI* ini, void* instance, void* store, const void* userData);
	static void parseObjectHasNoStatusFlag(INI* ini, void* instance, void* store, const void* userData);
	static void parseObjectHasComponent(INI* ini, void* instance, void* store, const void* userData);
	static void parseObjectHasNoComponent(INI* ini, void* instance, void* store, const void* userData);
	static void parseObjectHasWorkingComponent(INI* ini, void* instance, void* store, const void* userData);
	static void parseObjectHasNoWorkingComponent(INI* ini, void* instance, void* store, const void* userData);
	static void parseHasAtLeastItem(INI* ini, void* instance, void* store, const void* userData);
	static void parseHasAtMostItem(INI* ini, void* instance, void* store, const void* userData);
	static void parseItemStorageFull(INI* ini, void* instance, void* store, const void* userData);
	static void parseItemStorageNotFull(INI* ini, void* instance, void* store, const void* userData);
	static void parseItemStorageEmpty(INI* ini, void* instance, void* store, const void* userData);
};

//-----------------------------------------------------------------------------
