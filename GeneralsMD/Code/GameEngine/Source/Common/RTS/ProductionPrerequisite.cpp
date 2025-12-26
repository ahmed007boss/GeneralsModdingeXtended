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
#include "Common/ProductionPrerequisite.h"
#include "Common/Player.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "GameLogic/Object.h"
#include "GameClient/Drawable.h"
#include "GameClient/GameText.h"


//-----------------------------------------------------------------------------
// TheSuperHackers @refactor author 15/01/2025 ProductionPrerequisite now delegates to ProductionPrerequisite base class
ProductionPrerequisite::ProductionPrerequisite()
{
	// Base class constructor handles initialization
}

//-----------------------------------------------------------------------------
ProductionPrerequisite::~ProductionPrerequisite()
{
	// Base class destructor handles cleanup
}

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @refactor author 15/01/2025 ProductionPrerequisite delegates parsing to ProductionPrerequisite base class
void ProductionPrerequisite::parsePrerequisites(INI* ini, void* instance, void* store, const void* userData)
{
	// This function is designed to work with offsetof - instance points directly to the vector
	std::vector<ProductionPrerequisite>* prereqVector = (std::vector<ProductionPrerequisite>*)instance;

	static const FieldParse myFieldParse[] =
	{
		{ "Object", ProductionPrerequisite::parsePrerequisiteUnit, 0, 0 },// to support backward compatibility
		{ "Science", ProductionPrerequisite::parsePrerequisiteScience,	0, 0 },// to support backward compatibility

		{ "PlayerObjectExist", ProductionPrerequisite::parsePrerequisiteUnit, 0, 0 },
		{ "PlayerScienceExist", ProductionPrerequisite::parsePrerequisiteScience,	0, 0 },
		{ "PlayerObjectNotExist", ProductionPrerequisite::parsePrerequisiteUnitConflict, 0, 0 },
		{ "PlayerScienceNotExist", ProductionPrerequisite::parsePrerequisiteScienceConflict,	0, 0 },
		{ "PlayerUpgradeExist", ProductionPrerequisite::parsePrerequisiteUpgrade, 0, 0 },
		{ "PlayerUpgradeNotExist", ProductionPrerequisite::parsePrerequisiteUpgradeConflict, 0, 0 },

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
	prereq.addSciencePrereq(INI::scanScience(ini->getNextToken()));

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
	prereq.addSciencePrereqConflict(INI::scanScience(ini->getNextToken()));

	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ProductionPrerequisite::parsePrerequisiteUpgrade(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;

	ProductionPrerequisite prereq;
	prereq.addUpgradePrereq(AsciiString(ini->getNextToken()));

	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ProductionPrerequisite::parsePrerequisiteUpgradeConflict(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ProductionPrerequisite>* v = (std::vector<ProductionPrerequisite>*)instance;

	ProductionPrerequisite prereq;
	prereq.addUpgradePrereqConflict(AsciiString(ini->getNextToken()));

	v->push_back(prereq);
}
