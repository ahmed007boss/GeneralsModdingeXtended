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

// FILE: ArmorTemplate.cpp ///////////////////////////////////////////////////////////////////////////////
// Author: Steven Johnson, November 2001
// Desc:   ArmorTemplate descriptions
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file in the GameEngine


#include "Common/INI.h"
#include "Common/ThingFactory.h"
#include "GameLogic/Armor.h"
#include "GameLogic/Damage.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC DATA ////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
ArmorStore* TheArmorStore = NULL;					///< the ArmorTemplate store definition

///////////////////////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA ///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
ArmorTemplate::ArmorTemplate()
	: m_displayName()
	, m_icon()
	, m_displayDescription()
{
	// Initialize damage coefficients
	for (int i = 0; i < DAMAGE_NUM_TYPES; i++)
	{
		m_damageCoefficient[i] = 1.0f;
	}
}

//-------------------------------------------------------------------------------------------------
void ArmorTemplate::clear()
{
	m_displayName = UnicodeString();
	// Explicitly re-initialize AsciiString members using placement new to ensure they're valid
	// This is necessary because when objects are created in hash_map, members might not be properly initialized
	m_icon.~AsciiString();
	new(&m_icon) AsciiString();
	m_displayDescription.~AsciiString();
	new(&m_displayDescription) AsciiString();
	for (int i = 0; i < DAMAGE_NUM_TYPES; i++)
	{
		m_damageCoefficient[i] = 1.0f;
	}
}

void ArmorTemplate::copyFrom(const ArmorTemplate* other) {
	m_displayName = other->m_displayName;
	m_icon = other->m_icon;
	m_displayDescription = other->m_displayDescription;
	for (int i = 0; i < DAMAGE_NUM_TYPES; i++)
	{
		m_damageCoefficient[i] = other->m_damageCoefficient[i];
	}
}

//-------------------------------------------------------------------------------------------------
Real ArmorTemplate::adjustDamage(DamageType t, Real damage) const
{
	if (t == DAMAGE_UNRESISTABLE)
		return damage;
	if (t == DAMAGE_SUBDUAL_UNRESISTABLE)
		return damage;
	if (t == DAMAGE_JAMMING_UNRESISTABLE)
		return damage;
	damage *= m_damageCoefficient[t];

	if (damage < 0.0f)
		damage = 0.0f;

	return damage;
}

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 01/01/2025 Get armor display name with fallback
//-------------------------------------------------------------------------------------------------
UnicodeString ArmorTemplate::getDisplayName() const
{
	if (!m_displayName.isEmpty())
	{
		return m_displayName;
	}
	else
	{
		// Fallback to empty string if display name is not set
		return UnicodeString();
	}
}

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 01/01/2025 Get armor display name with fallback
//-------------------------------------------------------------------------------------------------
UnicodeString Armor::getDisplayName() const
{
	if (m_template)
	{
		return m_template->getDisplayName();
	}
	else
	{
		return UnicodeString();
	}
}

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 01/01/2025 Get armor description
//-------------------------------------------------------------------------------------------------
UnicodeString ArmorTemplate::getModuleDescription() const
{
	UnicodeString result;
	
	// Get the display name (either override or translated name)
	UnicodeString armorName;
	if (!m_displayName.isEmpty())
	{
		armorName = m_displayName;
	}
	else
	{
		armorName = L"";
	}
	
	// Return in natural statement format
	if (!armorName.isEmpty())
	{
		result = L"Protected by ";
		result += armorName;
	}
	
	return result;
}

//-------------------------------------------------------------------------------------------Static
 void ArmorTemplate::parseArmorCoefficients( INI* ini, void *instance, void* /* store */, const void* userData )
{
	ArmorTemplate* self = (ArmorTemplate*) instance;

	const char* damageName = ini->getNextToken();
	Real pct = INI::scanPercentToReal(ini->getNextToken());

	if (stricmp(damageName, "Default") == 0)
	{
		for (Int i = 0; i < DAMAGE_NUM_TYPES; i++)
		{
			self->m_damageCoefficient[i] = pct;
		}
		return;
	}

	DamageType dt = (DamageType)DamageTypeFlags::getSingleBitFromName(damageName);
	self->m_damageCoefficient[dt] = pct;
}

void ArmorTemplate::parseArmorMultiplier(INI* ini, void* instance, void* /* store */, const void* userData)
{
	ArmorTemplate* self = (ArmorTemplate*)instance;

	const char* damageName = ini->getNextToken();
	Real mult = INI::scanPercentToReal(ini->getNextToken());

	if (stricmp(damageName, "All") == 0 || stricmp(damageName, "Default") == 0)
	{
		for (Int i = 0; i < DAMAGE_NUM_TYPES; i++)
		{
			self->m_damageCoefficient[i] = self->m_damageCoefficient[i] * mult;
		}
		return;
	}

	DamageType dt = (DamageType)DamageTypeFlags::getSingleBitFromName(damageName);
	self->m_damageCoefficient[dt] = self->m_damageCoefficient[dt] * mult;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
ArmorStore::ArmorStore()
{
	m_armorTemplates.clear();
}

//-------------------------------------------------------------------------------------------------
ArmorStore::~ArmorStore()
{
	m_armorTemplates.clear();
}

//-------------------------------------------------------------------------------------------------
const ArmorTemplate* ArmorStore::findArmorTemplate(NameKeyType namekey) const
{
	ArmorTemplateMap::const_iterator it = m_armorTemplates.find(namekey);
	if (it == m_armorTemplates.end())
	{
		return NULL;
	}
	else
	{
		return &(*it).second;
	}
}

//-------------------------------------------------------------------------------------------------
const ArmorTemplate* ArmorStore::findArmorTemplate(const AsciiString& name) const
{
	return findArmorTemplate(TheNameKeyGenerator->nameToKey(name));
}

//-------------------------------------------------------------------------------------------------
const ArmorTemplate* ArmorStore::findArmorTemplate(const char* name) const
{
	return findArmorTemplate(TheNameKeyGenerator->nameToKey(name));
}

//-------------------------------------------------------------------------------------------------
void ArmorStore::parseArmorDefinition(INI *ini)
{
	static const FieldParse myFieldParse[] =
	{
		{ "DisplayName", INI::parseAndTranslateLabel, NULL, offsetof(ArmorTemplate, m_displayName) },
		{ "InfoIcon", INI::parseAsciiString, NULL, offsetof(ArmorTemplate, m_icon) },
		{ "DisplayDescription", INI::parseAsciiString, NULL, offsetof(ArmorTemplate, m_displayDescription) },
		{ "Armor", ArmorTemplate::parseArmorCoefficients, NULL, 0 },
		{ "ArmorMultiplier", ArmorTemplate::parseArmorMultiplier, NULL, 0 },
		{ NULL, NULL, NULL, 0 }
	};

	const char *c = ini->getNextToken();
	NameKeyType key = TheNameKeyGenerator->nameToKey(c);
	ArmorTemplate& armorTmpl = TheArmorStore->m_armorTemplates[key];
	armorTmpl.clear();
	ini->initFromINI(&armorTmpl, myFieldParse);
}

//-------------------------------------------------------------------------------------------------
void ArmorStore::parseArmorExtendDefinition(INI* ini)
{
	static const FieldParse myFieldParse[] =
	{
		{ "DisplayName", INI::parseAndTranslateLabel, NULL, offsetof(ArmorTemplate, m_displayName) },
		{ "InfoIcon", INI::parseAsciiString, NULL, offsetof(ArmorTemplate, m_icon) },
		{ "DisplayDescription", INI::parseAsciiString, NULL, offsetof(ArmorTemplate, m_displayDescription) },
		{ "Armor", ArmorTemplate::parseArmorCoefficients, NULL, 0 },
		{ "ArmorMultiplier", ArmorTemplate::parseArmorMultiplier, NULL, 0 },
				{ NULL, NULL, NULL, 0 }
	};

	const char* new_armor_name = ini->getNextToken();

	const char* parent = ini->getNextToken();
	const ArmorTemplate* parentTemplate = TheArmorStore->findArmorTemplate(parent);
	if (parentTemplate == NULL) {
		DEBUG_CRASH(("ArmorExtend must extend a previously defined Armor (%s).\n", parent));
		throw INI_INVALID_DATA;
	}

	NameKeyType key = TheNameKeyGenerator->nameToKey(new_armor_name);
	ArmorTemplate& armorTmpl = TheArmorStore->m_armorTemplates[key];
	armorTmpl.clear();
	armorTmpl.copyFrom(parentTemplate);

	ini->initFromINI(&armorTmpl, myFieldParse);
}

//-------------------------------------------------------------------------------------------------
 void INI::parseArmorDefinition(INI *ini)
{
	ArmorStore::parseArmorDefinition(ini);
}

//-------------------------------------------------------------------------------------------------
 void INI::parseArmorExtendDefinition(INI* ini)
{
	ArmorStore::parseArmorExtendDefinition(ini);
}
