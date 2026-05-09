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

// ArmorSet.h

#pragma once

#include "Lib/BaseType.h"
#include "Common/GameType.h"
#include "GameLogic/Damage.h"
#include "Common/SparseMatchFinder.h"

//-------------------------------------------------------------------------------------------------
class ArmorTemplate;
class DamageFX;
class INI;

//-------------------------------------------------------------------------------------------------
// IMPORTANT NOTE: you should endeavor to set up states such that the most "normal"
// state is defined by the bit being off. That is, the typical "normal" condition
// has all condition flags set to zero.
enum ArmorSetType CPP_11(: Int)
{
	// The access and use of this enum has the bit shifting built in, so this is a 0,1,2,3,4,5 enum
	ARMORSET_VETERAN		= 0,
	ARMORSET_ELITE			= 1,
	ARMORSET_HERO				= 2,
	ARMORSET_PLAYER_UPGRADE = 3,
	ARMORSET_WEAK_VERSUS_BASEDEFENSES = 4,
	ARMORSET_SECOND_LIFE = 5,	///< Body Module has marked us as on our second life
	ARMORSET_CRATE_UPGRADE_ONE, ///< Just like weaponset type from salvage.
	ARMORSET_CRATE_UPGRADE_TWO,
	ARMORSET_PLAYER_UPGRADE2,
	ARMORSET_PLAYER_UPGRADE3,
	ARMORSET_PLAYER_UPGRADE4,

	ARMORSET_COUNT
};

//-------------------------------------------------------------------------------------------------
typedef BitFlags<ARMORSET_COUNT> ArmorSetFlags;

//-------------------------------------------------------------------------------------------------
class ArmorTemplateSet
{
private:
	ArmorSetFlags m_types;
	const ArmorTemplate* m_template;
	const ArmorTemplate* m_sideTemplates[HIT_SIDE_COUNT];	///< Side-specific armor templates
	const DamageFX* m_fx;
	mutable UnicodeString* m_description;	///< Cached description for UI display

public:
	ArmorTemplateSet()
	{
		clear();
	}

	void clear()
	{
		m_types.clear();
		m_template = NULL;
		for (int i = 0; i < HIT_SIDE_COUNT; i++)
		{
			m_sideTemplates[i] = NULL;
		}
		m_fx = NULL;
		m_description = NULL;
	}

	const ArmorTemplate* getArmorTemplate() const { return m_template; }
	const ArmorTemplate* getSideArmorTemplate(HitSide side) const 
	{ 
		if (side >= 0 && side < HIT_SIDE_COUNT && m_sideTemplates[side] != NULL)
			return m_sideTemplates[side];
		return m_template; // Fallback to default armor
	}
	const DamageFX* getDamageFX() const { return m_fx; }

	Int getConditionsYesCount() const { return 1; }
	const ArmorSetFlags& getNthConditionsYes(Int i) const { return m_types; }
#if defined(RTS_DEBUG)
	inline AsciiString getDescription() const { return "ArmorTemplateSet"; }
#endif

	void parseArmorTemplateSet( INI* ini );
	void setSideArmorTemplate(HitSide side, const ArmorTemplate* armorTemplate);
	UnicodeString getModuleDescription() const;
	UnicodeString buildSideSpecificDescription() const;
	static void parseDescription(INI* ini, void* instance, void* store, const void* userData);
};

//-------------------------------------------------------------------------------------------------
typedef std::vector<ArmorTemplateSet> ArmorTemplateSetVector;
