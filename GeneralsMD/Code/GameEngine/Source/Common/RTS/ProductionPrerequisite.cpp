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

// FILE: ProductionPrerequisite.cpp /////////////////////////////////////////////////////////
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
// File name: ProductionPrerequisite.cpp
//
// Created:   Steven Johnson, October 2001
// Refactored: TheSuperHackers @refactor author 15/01/2025 Now inherits from ProductionPrerequisite base class
//
// Desc:      ProductionPrerequisite now delegates all functionality to ProductionPrerequisite base class
//
//-----------------------------------------------------------------------------

#include "PreRTS.h"	// This must go first in EVERY cpp file in the GameEngine

#include "Common/ProductionPrerequisite.h"
#include "Common/Player.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "GameLogic/Object.h"
#include "GameClient/Drawable.h"
#include "GameClient/GameText.h"


//-----------------------------------------------------------------------------
// TheSuperHackers @feature Ahmed Salah 15/01/2025 ProductionPrerequisite now inherits from both PlayerPrerequisite and ObjectPrerequisite
ProductionPrerequisite::ProductionPrerequisite() : PlayerPrerequisite(), ObjectPrerequisite()
{
	// Both base class constructors handle initialization
}

//-----------------------------------------------------------------------------
ProductionPrerequisite::~ProductionPrerequisite()
{
	// Both base class destructors handle cleanup
}

//-----------------------------------------------------------------------------
// TheSuperHackers @feature Ahmed Salah 15/01/2025 Override resolveNames to call both base classes
void ProductionPrerequisite::resolveNames()
{
	PlayerPrerequisite::resolveNames();
	ObjectPrerequisite::resolveNames();
}

//-----------------------------------------------------------------------------
// TheSuperHackers @feature Ahmed Salah 15/01/2025 Combined method that checks both player and object prerequisites
Bool ProductionPrerequisite::isSatisfied(const Player* player, const Object* object) const
{
	// Check player prerequisites
	if (!PlayerPrerequisite::isSatisfied(player))
		return false;

	// Check object prerequisites
	if (!ObjectPrerequisite::isSatisfied(object))
		return false;

	return true;
}

//-----------------------------------------------------------------------------
// TheSuperHackers @feature Ahmed Salah 15/01/2025 Combined method that gets requirements list from both player and object prerequisites
UnicodeString ProductionPrerequisite::getRequiresList(const Player* player, const Object* object) const
{
	UnicodeString requiresList = UnicodeString::TheEmptyString;
	Bool firstRequirement = true;

	// Get player requirements
	UnicodeString playerRequires = PlayerPrerequisite::getRequiresList(player);
	if (!playerRequires.isEmpty())
	{
		requiresList.concat(playerRequires);
		firstRequirement = false;
	}

	// Get object requirements
	UnicodeString objectRequires = ObjectPrerequisite::getRequiresList(object);
	if (!objectRequires.isEmpty())
	{
		if (!firstRequirement)
			requiresList.concat(L"\n");
		requiresList.concat(objectRequires);
	}

	return requiresList;
}

//-----------------------------------------------------------------------------
// TheSuperHackers @feature Ahmed Salah 15/01/2025 Combined method that gets conflict list from both player and object prerequisites
UnicodeString ProductionPrerequisite::getConflictList(const Player* player, const Object* object) const
{
	UnicodeString conflictList = UnicodeString::TheEmptyString;
	Bool firstConflict = true;

	// Get player conflicts
	UnicodeString playerConflicts = PlayerPrerequisite::getConflictList(player);
	if (!playerConflicts.isEmpty())
	{
		conflictList.concat(playerConflicts);
		firstConflict = false;
	}

	// Get object conflicts
	UnicodeString objectConflicts = ObjectPrerequisite::getConflictList(object);
	if (!objectConflicts.isEmpty())
	{
		if (!firstConflict)
			conflictList.concat(L"\n");
		conflictList.concat(objectConflicts);
	}

	return conflictList;
}

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature Ahmed Salah 15/01/2025 ProductionPrerequisite now uses combined FieldParse table for both player and object prerequisites
void ProductionPrerequisite::parsePrerequisites(INI* ini, void* instance, void* store, const void* userData)
{
	// This function is designed to work with offsetof - instance points directly to the vector
	std::vector<ProductionPrerequisite>* prereqVector = (std::vector<ProductionPrerequisite>*)instance;

	// TheSuperHackers @feature Ahmed Salah 15/01/2025 Combined FieldParse table that includes both PlayerPrerequisite and ObjectPrerequisite fields
	static const FieldParse myFieldParse[] =
	{
		// Player prerequisite fields (backward compatibility)
		{ "Object", ProductionPrerequisite::parsePrerequisiteUnit, 0, 0 },// to support backward compatibility
		{ "Science", ProductionPrerequisite::parsePrerequisiteScience,	0, 0 },// to support backward compatibility
		{ "Upgrade", ProductionPrerequisite::parsePrerequisiteUpgrade,	0, 0 },// to support backward compatibility

		// Player prerequisite fields
		{ "PlayerObjectExists", ProductionPrerequisite::parsePrerequisiteUnit, 0, 0 },
		{ "PlayerObjectNotExist", ProductionPrerequisite::parsePrerequisiteUnitConflict, 0, 0 },
		{ "PlayerScienceExists", ProductionPrerequisite::parsePrerequisiteScience,	0, 0 },
		{ "PlayerScienceNotExist", ProductionPrerequisite::parsePrerequisiteScienceConflict,	0, 0 },
		{ "PlayerUpgradeExist", ProductionPrerequisite::parsePrerequisiteUpgrade, 0, 0 },
		{ "PlayerUpgradeNotExist", ProductionPrerequisite::parsePrerequisiteUpgradeConflict, 0, 0 },
		{ "PlayerKindOfObjectExists", ProductionPrerequisite::parsePrerequisiteKindOfUnit, 	0, 0 },
		{ "PlayerObjectKindOfNotExist", ProductionPrerequisite::parsePrerequisiteKindOfUnitConflict, 	0, 0 },
		{ "PlayerMinCountKindOfObjectExist", ProductionPrerequisite::parsePrerequisiteMinCountKindOfUnit, 	0, 0 },
		{ "PlayerMaxCountKindOfObjectExist", ProductionPrerequisite::parsePrerequisiteMaxCountKindOfUnit, 	0, 0 },
		{ "PlayerMinCountKindOfObjectWithLevelExist", ProductionPrerequisite::parsePrerequisiteMinCountKindOfUnitWithLevel, 	0, 0 },
		{ "PlayerMaxCountKindOfObjectWithLevelExist", ProductionPrerequisite::parsePrerequisiteMaxCountKindOfUnitWithLevel, 	0, 0 },

		// Object prerequisite fields
		{ "ObjectIs", ProductionPrerequisite::parseObjectIs, 0, 0 },
		{ "ObjectIsNot", ProductionPrerequisite::parseObjectIsNot, 0, 0 },
		{ "ObjectIsKindOf", ProductionPrerequisite::parseObjectIsKindOf, 0, 0 },
		{ "ObjectIsNoKindOf", ProductionPrerequisite::parseObjectIsNoKindOf, 0, 0 },
		{ "ObjectHasUpgrade", ProductionPrerequisite::parseObjectHasUpgrade, 0, 0 },
		{ "ObjectHasNotUpgrade", ProductionPrerequisite::parseObjectHasNotUpgrade, 0, 0 },
		{ "ObjectLevelMoreThan", ProductionPrerequisite::parseObjectLevelMoreThan, 0, 0 },
		{ "ObjectLevelLessThan", ProductionPrerequisite::parseObjectLevelLessThan, 0, 0 },
		{ "ObjectHasNearbyObject", ProductionPrerequisite::parseObjectHasNearbyObject, 0, 0 },
		{ "ObjectHasNearbyKindOf", ProductionPrerequisite::parseObjectHasNearbyKindOf, 0, 0 },
		{ "ObjectHasNoNearbyObject", ProductionPrerequisite::parseObjectHasNoNearbyObject, 0, 0 },
		{ "ObjectHasNoNearbyKindOf", ProductionPrerequisite::parseObjectHasNoNearbyKindOf, 0, 0 },
		{ "ObjectHasModelCondition", ProductionPrerequisite::parseObjectHasModelConditionFlag, 0, 0 },
		{ "ObjectHasNoModelCondition", ProductionPrerequisite::parseObjectHasNoModelConditionFlag, 0, 0 },
		{ "ObjectHasStatus", ProductionPrerequisite::parseObjectHasStatusFlag, 0, 0 },
		{ "ObjectHasNoStatus", ProductionPrerequisite::parseObjectHasNoStatusFlag, 0, 0 },
		{ "ObjectHasComponent", ProductionPrerequisite::parseObjectHasComponent, 0, 0 },
		{ "ObjectHasNoComponent", ProductionPrerequisite::parseObjectHasNoComponent, 0, 0 },
		{ "ObjectHasWorkingComponent", ProductionPrerequisite::parseObjectHasWorkingComponent, 0, 0 },
		{ "ObjectHasNoWorkingComponent", ProductionPrerequisite::parseObjectHasNoWorkingComponent, 0, 0 },
		{ "HasAtLeastItem", ProductionPrerequisite::parseHasAtLeastItem, 0, 0 },     // True if the unit has ≥ a given number of a specific item
		{ "HasAtMostItem", ProductionPrerequisite::parseHasAtMostItem, 0, 0 },       // True if the unit has ≤ a given number of a specific item
		{ "ItemStorageFull", ProductionPrerequisite::parseItemStorageFull, 0, 0 },   // True if storage for a specific item is completely full
		{ "ItemStorageNotFull", ProductionPrerequisite::parseItemStorageNotFull, 0, 0 }, // True if storage for a specific item is not full
		{ "ItemStorageEmpty", ProductionPrerequisite::parseItemStorageEmpty, 0, 0 }, // True if storage for a specific item is completely empty

		{ 0, 0, 0, 0 }
	};

	if (ini->getLoadType() == INI_LOAD_CREATE_OVERRIDES)
	{
		prereqVector->clear();
	}

	ini->initFromINI(prereqVector, myFieldParse);

}


void ProductionPrerequisite::parsePrerequisiteUnit(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;

	ProductionPrerequisite prereq;
	Bool orUnitWithPrevious = FALSE;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addUnitPrereq(AsciiString(token), orUnitWithPrevious);
		orUnitWithPrevious = TRUE;
	}

	v->push_back(prereq);
}
//-------------------------------------------------------------------------------------------------
void ProductionPrerequisite::parsePrerequisiteScience(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;

	ProductionPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addSciencePrereq(INI::scanScience(token));
	}

	v->push_back(prereq);
}


void ProductionPrerequisite::parsePrerequisiteUnitConflict(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;

	ProductionPrerequisite prereq;
	Bool orUnitWithPrevious = FALSE;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addUnitPrereqConflict(AsciiString(token), orUnitWithPrevious);
		orUnitWithPrevious = TRUE;
	}

	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ProductionPrerequisite::parsePrerequisiteScienceConflict(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;

	ProductionPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addSciencePrereqConflict(INI::scanScience(token));
	}

	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ProductionPrerequisite::parsePrerequisiteUpgrade(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;

	ProductionPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addUpgradePrereq(AsciiString(token));
	}

	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ProductionPrerequisite::parsePrerequisiteUpgradeConflict(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;

	ProductionPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addUpgradePrereqConflict(AsciiString(token));
	}

	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature Ahmed Salah 15/01/2025 Wrapper methods for PlayerPrerequisite parsing methods
void ProductionPrerequisite::parsePrerequisiteKindOfUnit(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;
	ProductionPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addKindOfUnitPrereq(AsciiString(token));
	}
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ProductionPrerequisite::parsePrerequisiteKindOfUnitConflict(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;
	ProductionPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addKindOfUnitPrereqConflict(AsciiString(token));
	}
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ProductionPrerequisite::parsePrerequisiteMinCountKindOfUnit(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;
	ProductionPrerequisite prereq;
	// Parse the entire line as one token (e.g., "TANK 4 STRUCTURE 3")
	AsciiString fullLine;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		if (!fullLine.isEmpty())
			fullLine.concat(" ");
		fullLine.concat(token);
	}
	prereq.addMinCountKindOfUnitPrereq(fullLine);
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ProductionPrerequisite::parsePrerequisiteMaxCountKindOfUnit(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;
	ProductionPrerequisite prereq;
	// Parse the entire line as one token (e.g., "TANK 4 STRUCTURE 3")
	AsciiString fullLine;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		if (!fullLine.isEmpty())
			fullLine.concat(" ");
		fullLine.concat(token);
	}
	prereq.addMaxCountKindOfUnitPrereq(fullLine);
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ProductionPrerequisite::parsePrerequisiteMinCountKindOfUnitWithLevel(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;
	ProductionPrerequisite prereq;
	// Parse the entire line as one token (e.g., "TANK LEVEL_VETERAN 4 STRUCTURE LEVEL_REGULAR 3")
	AsciiString fullLine;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		if (!fullLine.isEmpty())
			fullLine.concat(" ");
		fullLine.concat(token);
	}
	prereq.addMinCountKindOfUnitWithLevelPrereq(fullLine);
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ProductionPrerequisite::parsePrerequisiteMaxCountKindOfUnitWithLevel(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;
	ProductionPrerequisite prereq;
	// Parse the entire line as one token (e.g., "TANK LEVEL_VETERAN 4 STRUCTURE LEVEL_REGULAR 3")
	AsciiString fullLine;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		if (!fullLine.isEmpty())
			fullLine.concat(" ");
		fullLine.concat(token);
	}
	prereq.addMaxCountKindOfUnitWithLevelPrereq(fullLine);
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature Ahmed Salah 15/01/2025 Wrapper methods for ObjectPrerequisite parsing methods
void ProductionPrerequisite::parseObjectIs(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;
	ProductionPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addObjectIsPrereq(AsciiString(token));
	}
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ProductionPrerequisite::parseObjectIsNot(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;
	ProductionPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addObjectIsNotPrereq(AsciiString(token));
	}
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ProductionPrerequisite::parseObjectIsKindOf(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;
	ProductionPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addObjectIsKindOfPrereq(AsciiString(token));
	}
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ProductionPrerequisite::parseObjectIsNoKindOf(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;
	ProductionPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addObjectIsNoKindOfPrereq(AsciiString(token));
	}
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ProductionPrerequisite::parseObjectHasUpgrade(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;
	ProductionPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addObjectHasUpgradePrereq(AsciiString(token));
	}
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ProductionPrerequisite::parseObjectHasNotUpgrade(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;
	ProductionPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addObjectHasNotUpgradePrereq(AsciiString(token));
	}
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ProductionPrerequisite::parseObjectLevelMoreThan(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;
	ProductionPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addObjectLevelMoreThanPrereq(atoi(token));
	}
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ProductionPrerequisite::parseObjectLevelLessThan(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;
	ProductionPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addObjectLevelLessThanPrereq(atoi(token));
	}
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ProductionPrerequisite::parseObjectHasNearbyObject(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;
	ProductionPrerequisite prereq;
	AsciiString fullLine;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		if (!fullLine.isEmpty())
			fullLine.concat(" ");
		fullLine.concat(token);
	}
	AsciiString remaining = fullLine;
	AsciiString objectName;
	Real distance;
	
	// Parse all object-distance pairs (OR logic)
	while (remaining.nextToken(&objectName, " "))
	{
		AsciiString distanceStr;
		if (remaining.nextToken(&distanceStr, " "))
		{
			distance = (Real)atof(distanceStr.str());
			prereq.addObjectHasNearbyObjectPrereq(objectName, distance);
		}
		else
		{
			break;
		}
	}
	
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ProductionPrerequisite::parseObjectHasNearbyKindOf(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;
	ProductionPrerequisite prereq;
	AsciiString fullLine;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		if (!fullLine.isEmpty())
			fullLine.concat(" ");
		fullLine.concat(token);
	}
	AsciiString remaining = fullLine;
	AsciiString kindOfName;
	Real distance;
	
	// Parse all KindOf-distance pairs (OR logic)
	while (remaining.nextToken(&kindOfName, " "))
	{
		AsciiString distanceStr;
		if (remaining.nextToken(&distanceStr, " "))
		{
			distance = (Real)atof(distanceStr.str());
			prereq.addObjectHasNearbyKindOfPrereq(kindOfName, distance);
		}
		else
		{
			break;
		}
	}
	
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ProductionPrerequisite::parseObjectHasNoNearbyObject(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;
	ProductionPrerequisite prereq;
	AsciiString fullLine;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		if (!fullLine.isEmpty())
			fullLine.concat(" ");
		fullLine.concat(token);
	}
	AsciiString remaining = fullLine;
	AsciiString objectName;
	Real distance;
	
	// Parse all object-distance pairs (OR logic)
	while (remaining.nextToken(&objectName, " "))
	{
		AsciiString distanceStr;
		if (remaining.nextToken(&distanceStr, " "))
		{
			distance = (Real)atof(distanceStr.str());
			prereq.addObjectHasNoNearbyObjectPrereq(objectName, distance);
		}
		else
		{
			break;
		}
	}
	
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ProductionPrerequisite::parseObjectHasNoNearbyKindOf(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;
	ProductionPrerequisite prereq;
	AsciiString fullLine;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		if (!fullLine.isEmpty())
			fullLine.concat(" ");
		fullLine.concat(token);
	}
	AsciiString remaining = fullLine;
	AsciiString kindOfName;
	Real distance;
	
	// Parse all KindOf-distance pairs (OR logic)
	while (remaining.nextToken(&kindOfName, " "))
	{
		AsciiString distanceStr;
		if (remaining.nextToken(&distanceStr, " "))
		{
			distance = (Real)atof(distanceStr.str());
			prereq.addObjectHasNoNearbyKindOfPrereq(kindOfName, distance);
		}
		else
		{
			break;
		}
	}
	
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ProductionPrerequisite::parseObjectHasModelConditionFlag(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;
	ProductionPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addObjectHasModelConditionFlagPrereq(AsciiString(token));
	}
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ProductionPrerequisite::parseObjectHasNoModelConditionFlag(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;
	ProductionPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addObjectHasNoModelConditionFlagPrereq(AsciiString(token));
	}
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ProductionPrerequisite::parseObjectHasStatusFlag(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;
	ProductionPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addObjectHasStatusFlagPrereq(AsciiString(token));
	}
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ProductionPrerequisite::parseObjectHasNoStatusFlag(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;
	ProductionPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addObjectHasNoStatusFlagPrereq(AsciiString(token));
	}
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ProductionPrerequisite::parseObjectHasComponent(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;
	ProductionPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addObjectHasComponentPrereq(AsciiString(token));
	}
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ProductionPrerequisite::parseObjectHasNoComponent(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;
	ProductionPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addObjectHasNoComponentPrereq(AsciiString(token));
	}
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ProductionPrerequisite::parseObjectHasWorkingComponent(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;
	ProductionPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addObjectHasWorkingComponentPrereq(AsciiString(token));
	}
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ProductionPrerequisite::parseObjectHasNoWorkingComponent(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;
	ProductionPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addObjectHasNoWorkingComponentPrereq(AsciiString(token));
	}
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ProductionPrerequisite::parseHasAtLeastItem(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;
	ProductionPrerequisite prereq;
	AsciiString fullLine;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		if (!fullLine.isEmpty())
			fullLine.concat(" ");
		fullLine.concat(token);
	}
	AsciiString remaining = fullLine;
	AsciiString itemName;
	Int count;
	
	// Parse all item-count pairs (OR logic)
	while (remaining.nextToken(&itemName, " "))
	{
		AsciiString countStr;
		if (remaining.nextToken(&countStr, " "))
		{
			count = atoi(countStr.str());
			prereq.addObjectHasAtLeastItemPrereq(itemName, count);
		}
		else
		{
			break;
		}
	}
	
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ProductionPrerequisite::parseHasAtMostItem(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;
	ProductionPrerequisite prereq;
	AsciiString fullLine;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		if (!fullLine.isEmpty())
			fullLine.concat(" ");
		fullLine.concat(token);
	}
	AsciiString remaining = fullLine;
	AsciiString itemName;
	Int count;
	
	// Parse all item-count pairs (OR logic)
	while (remaining.nextToken(&itemName, " "))
	{
		AsciiString countStr;
		if (remaining.nextToken(&countStr, " "))
		{
			count = atoi(countStr.str());
			prereq.addObjectHasAtMostItemPrereq(itemName, count);
		}
		else
		{
			break;
		}
	}
	
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ProductionPrerequisite::parseItemStorageFull(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;
	ProductionPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addObjectItemStorageFullPrereq(AsciiString(token));
	}
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ProductionPrerequisite::parseItemStorageNotFull(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;
	ProductionPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addObjectItemStorageNotFullPrereq(AsciiString(token));
	}
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ProductionPrerequisite::parseItemStorageEmpty(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;
	ProductionPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addObjectItemStorageEmptyPrereq(AsciiString(token));
	}
	v->push_back(prereq);
}
