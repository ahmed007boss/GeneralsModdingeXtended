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

// FILE: SalvageCrateCollide.cpp ///////////////////////////////////////////////////////////////////////
// Author: Graham Smallwood, March 2002
// Desc:   The Savlage system can give a Weaponset bonus, a level, or money.  Salvagers create them
//					by killing marked units, and only WeaponSalvagers can get the WeaponSet bonus
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file in the GameEngine
#include "GameLogic/Module/SalvageCrateCollide.h"

#include "Common/AudioEventRTS.h"
#include "Common/MiscAudio.h"
#include "Common/KindOf.h"
#include "Common/RandomValue.h"
#include "Common/Player.h"
#include "Common/ThingTemplate.h"
#include "Common/Xfer.h"
#include "GameClient/GameText.h"
#include "GameClient/InGameUI.h"
#include "GameLogic/ExperienceTracker.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/Module/BodyModule.h"

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
SalvageCrateCollide::SalvageCrateCollide( Thing *thing, const ModuleData* moduleData ) : CrateCollide( thing, moduleData )
{

}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
SalvageCrateCollide::~SalvageCrateCollide( void )
{

}

//-------------------------------------------------------------------------------------------------
Bool SalvageCrateCollide::isValidToExecute( const Object *other ) const
{
	if( ! CrateCollide::isValidToExecute( other ) )
		return FALSE;

	// Only salvage units can pick up a Salvage crate
	if( ! other->getTemplate()->isKindOf( KINDOF_SALVAGER ) )
		return FALSE;

	return TRUE;
}

//-------------------------------------------------------------------------------------------------
std::vector<Object*> SalvageCrateCollide::getObjectsInRange( Object *other, Real radius )
{
	std::vector<Object*> result;
	
	if( other == NULL || radius <= 0.0f )
		return result;

	// Get the controlling player for team filtering
	Player* controllingPlayer = other->getControllingPlayer();
	if( !controllingPlayer )
		return result;

	// Check nearby units within radius
	Coord3D centerPos = *getObject()->getPosition();
	ObjectIterator *iter = ThePartitionManager->iterateObjectsInRange( &centerPos, radius, FROM_CENTER_2D );
	MemoryPoolObjectHolder hold(iter);
	
	if( iter )
	{
		for( Object *nearbyObj = iter->first(); nearbyObj; nearbyObj = iter->next() )
		{
			// Filter out the original object
			if( nearbyObj == other )
				continue;
				
			// Filter by team - must be same controlling player
			if( nearbyObj->getControllingPlayer() != controllingPlayer )
				continue;
				
			// Filter by KINDOF_SALVAGER - must be able to pick up salvage crates
			if( !nearbyObj->getTemplate()->isKindOf( KINDOF_SALVAGER ) )
				continue;
				
			// Object passes all filters
			result.push_back( nearbyObj );
		}
	}
	
	return result;
}

//-------------------------------------------------------------------------------------------------
// Direct Full Restore 
// Direct Armor Upgrade 
// Direct Weapon Upgrade 
// Direct Inventory Fill 
// Shared Armor Upgrade 
// Shared Weapon Upgrade 
// Shared Full Repair 
// Shared Full Restore
// Direct Level Gain 
// Shared Level Gain 
// Shared Inventory Fill 
// Money Reward 
Bool SalvageCrateCollide::executeCrateBehavior( Object *other )
{
	const SalvageCrateCollideModuleData *md = getSalvageCrateCollideModuleData();
	Int crateValue = md->m_salvageCrateValue;
	
	// Ensure minimum value of 1
	if( crateValue < 1 )
		crateValue = 1;

	// Execute the crate behavior multiple times based on SalvageCrateValue
	for( Int i = 0; i < crateValue; i++ )
	{
		if( eligibleForFullRepair( other ) && testFullRepairChance() )
		{
			doFullRepair( other );

			//Play the salvage installation crate pickup sound.
			AudioEventRTS soundToPlay = TheAudio->getMiscAudio()->m_crateSalvage;
			soundToPlay.setObjectID( other->getID() );
			TheAudio->addAudioEvent( &soundToPlay );
		}
		else if( eligibleForFullRestore( other ) && testFullRestoreChance() )
		{
			doFullRestore( other );

			//Play the salvage installation crate pickup sound.
			AudioEventRTS soundToPlay = TheAudio->getMiscAudio()->m_crateSalvage;
			soundToPlay.setObjectID( other->getID() );
			TheAudio->addAudioEvent( &soundToPlay );
		}
		else if( eligibleForArmorSet(other) )// No percent chance on this one, if you can get it, you get it.
		{
			doArmorSet(other);

			//Play the salvage installation crate pickup sound.
			AudioEventRTS soundToPlay = TheAudio->getMiscAudio()->m_crateSalvage;
			soundToPlay.setObjectID( other->getID() );
			TheAudio->addAudioEvent( &soundToPlay );
		}
		else if( eligibleForWeaponSet( other ) && testWeaponChance() )
		{
			doWeaponSet( other );

			//Play the salvage installation crate pickup sound.
			AudioEventRTS soundToPlay = TheAudio->getMiscAudio()->m_crateSalvage;
			soundToPlay.setObjectID( other->getID() );
			TheAudio->addAudioEvent( &soundToPlay );

			//Play the unit voice acknowledgement for upgrading weapons.
			//Already handled by the "move order"
			//const AudioEventRTS *soundToPlayPtr = other->getTemplate()->getPerUnitSound( "VoiceSalvage" );
			//soundToPlay = *soundToPlayPtr;
			//soundToPlay.setObjectID( other->getID() );
			//TheAudio->addAudioEvent( &soundToPlay );
		}
		else if( eligibleForFillInventory( other ) && testFillInventoryChance() )
		{
			doFillInventory( other );

			//Play the salvage installation crate pickup sound.
			AudioEventRTS soundToPlay = TheAudio->getMiscAudio()->m_crateSalvage;
			soundToPlay.setObjectID( other->getID() );
			TheAudio->addAudioEvent( &soundToPlay );
		}
		else if( Object *eligibleForArmor = eligibleForArmorSetShare( other ) )// No percent chance on this one, if you can get it, you get it.
		{
			doArmorSet(eligibleForArmor);

			//Play the salvage installation crate pickup sound.
			AudioEventRTS soundToPlay = TheAudio->getMiscAudio()->m_crateSalvage;
			soundToPlay.setObjectID( other->getID() );
			TheAudio->addAudioEvent( &soundToPlay );
		}
		else if( Object *eligibleForWeapon = eligibleForWeaponSetShare( other ) )
		{
			if( testWeaponChance() )
			{
				doWeaponSet( eligibleForWeapon );

				//Play the salvage installation crate pickup sound.
				AudioEventRTS soundToPlay = TheAudio->getMiscAudio()->m_crateSalvage;
				soundToPlay.setObjectID( other->getID() );
				TheAudio->addAudioEvent( &soundToPlay );

				//Play the unit voice acknowledgement for upgrading weapons.
				//Already handled by the "move order"
				//const AudioEventRTS *soundToPlayPtr = other->getTemplate()->getPerUnitSound( "VoiceSalvage" );
				//soundToPlay = *soundToPlayPtr;
				//soundToPlay.setObjectID( other->getID() );
				//TheAudio->addAudioEvent( &soundToPlay );
			}
		}
		else if( Object *eligibleForFullRepair = eligibleForFullRepairShare( other ) )
		{
			if( testFullRepairChance() )
			{
				doFullRepair( eligibleForFullRepair );

				//Play the salvage installation crate pickup sound.
				AudioEventRTS soundToPlay = TheAudio->getMiscAudio()->m_crateSalvage;
				soundToPlay.setObjectID( other->getID() );
				TheAudio->addAudioEvent( &soundToPlay );
			}
		}
		else if( Object *eligibleForFullRestore = eligibleForFullRestoreShare( other ) )
		{
			if( testFullRestoreChance() )
			{
				doFullRestore( eligibleForFullRestore );

				//Play the salvage installation crate pickup sound.
				AudioEventRTS soundToPlay = TheAudio->getMiscAudio()->m_crateSalvage;
				soundToPlay.setObjectID( other->getID() );
				TheAudio->addAudioEvent( &soundToPlay );
			}
		}
		else if( eligibleForLevel( other ) && testLevelChance() )
		{
			doLevelGain( other );

			//Sound will play in
			//soundToPlay = TheAudio->getMiscAudio()->m_unitPromoted;
		}
		else if( Object *eligibleForLevel = eligibleForLevelShare( other ) )
		{
			if( testLevelChance() )
			{
				doLevelGain( eligibleForLevel );

				//Sound will play in
				//soundToPlay = TheAudio->getMiscAudio()->m_unitPromoted;
			}
		}
		else if( Object *eligibleForFillInventory = eligibleForFillInventoryShare( other ) )
		{
			if( testFillInventoryChance() )
			{
				doFillInventory( eligibleForFillInventory );

				//Play the salvage installation crate pickup sound.
				AudioEventRTS soundToPlay = TheAudio->getMiscAudio()->m_crateSalvage;
				soundToPlay.setObjectID( other->getID() );
				TheAudio->addAudioEvent( &soundToPlay );
			}
		}
		else // just assume the testMoneyChance
		{
			doMoney( other );
			AudioEventRTS soundToPlay = TheAudio->getMiscAudio()->m_crateMoney;
			soundToPlay.setObjectID( other->getID() );
			TheAudio->addAudioEvent(&soundToPlay);
		}
	}

	other->getControllingPlayer()->getAcademyStats()->recordSalvageCollected();

	return TRUE;
}

// ------------------------------------------------------------------------------------------------
Bool SalvageCrateCollide::eligibleForWeaponSet( Object *other )
{
	if( other == NULL )
		return FALSE;

	// A kindof marks eligibility, and you must not be fully upgraded
	if( !other->isKindOf(KINDOF_WEAPON_SALVAGER) )
		return FALSE;
	if( other->testWeaponSetFlag(WEAPONSET_CRATEUPGRADE_TWO) )
		return FALSE;

	return TRUE;
}

// ------------------------------------------------------------------------------------------------
Bool SalvageCrateCollide::eligibleForArmorSet( Object *other )
{
	if( other == NULL )
		return FALSE;

	// A kindof marks eligibility, and you must not be fully upgraded
	if( !other->isKindOf(KINDOF_ARMOR_SALVAGER) )
		return FALSE;
	if( other->testArmorSetFlag(ARMORSET_CRATE_UPGRADE_TWO) )
		return FALSE;

	return TRUE;
}

// ------------------------------------------------------------------------------------------------
Bool SalvageCrateCollide::eligibleForLevel( Object *other )
{
	if( other == NULL )
		return FALSE;

	// Sorry, you are max level
	if( other->getExperienceTracker()->getVeterancyLevel() == LEVEL_HEROIC )
		return FALSE;

	// Sorry, you can't gain levels
	if( !other->getExperienceTracker()->isTrainable() )
		return FALSE;

	return TRUE;
}

// ------------------------------------------------------------------------------------------------
Bool SalvageCrateCollide::eligibleForFullRestore( Object *other )
{
	if( other == NULL )
		return FALSE;

	// Get the body module to check for damaged components
	BodyModuleInterface* body = other->getBodyModule();
	if( !body )
		return FALSE;

	// Check if any components are damaged and can be restored
	std::vector<Component> components = body->getComponents();
	for( std::vector<Component>::const_iterator it = components.begin(); it != components.end(); ++it )
	{
		const Component& component = *it;
		if( !component.getName().isEmpty() )
		{
			// If component is damaged (health < max), it can be restored
			if( component.getCurrentHealth() < component.getCurrentMaxHealth() )
				return TRUE;
		}
	}

	return FALSE;
}

// ------------------------------------------------------------------------------------------------
Bool SalvageCrateCollide::eligibleForFillInventory( Object *other )
{
	if( other == NULL )
		return FALSE;

	// Get the inventory behavior to check for items that can be replenished
	InventoryBehavior* inventoryBehavior = other->getInventoryBehavior();
	if( !inventoryBehavior )
		return FALSE;

	// Check if any inventory items need replenishment - use instance data to respect upgrades
	const std::map<AsciiString, InventoryItemConfig>& inventoryItems = inventoryBehavior->getInventoryItems();
	for( std::map<AsciiString, InventoryItemConfig>::const_iterator it = inventoryItems.begin();
		 it != inventoryItems.end(); ++it )
	{
		const AsciiString& itemKey = it->first;
		
		// Check if this item needs replenishment
		Int currentAmount = inventoryBehavior->getItemCount( itemKey );
		Int maxStorage = inventoryBehavior->getMaxStorageCount( itemKey );
		
		// If current amount is less than max storage, it can be filled
		if( currentAmount < maxStorage )
			return TRUE;
	}

	return FALSE;
}

// ------------------------------------------------------------------------------------------------
Bool SalvageCrateCollide::eligibleForFullRepair( Object *other )
{
	if( other == NULL )
		return FALSE;

	// Check if unit is damaged and can be repaired
	BodyModuleInterface *body = other->getBodyModule();
	if( body == NULL )
		return FALSE;

	// Only eligible if the unit is damaged
	return body->getHealth() < body->getMaxHealth();
}

// ------------------------------------------------------------------------------------------------
Object* SalvageCrateCollide::eligibleForWeaponSetShare( Object *other )
{
	if( other == NULL )
		return NULL;

	const SalvageCrateCollideModuleData *md = getSalvageCrateCollideModuleData();
	if( md->m_shareRadius <= 0.0f )
		return NULL;

	// Get filtered objects in range
	std::vector<Object*> nearbyObjects = getObjectsInRange( other, md->m_shareRadius );
	
	// Check each nearby object for weapon upgrade eligibility
	for( std::vector<Object*>::const_iterator it = nearbyObjects.begin(); it != nearbyObjects.end(); ++it )
	{
		Object *nearbyObj = *it;
		if( eligibleForWeaponSet( nearbyObj ) )
			return nearbyObj;
	}

	return NULL;
}

// ------------------------------------------------------------------------------------------------
Object* SalvageCrateCollide::eligibleForArmorSetShare( Object *other )
{
	if( other == NULL )
		return NULL;

	const SalvageCrateCollideModuleData *md = getSalvageCrateCollideModuleData();
	if( md->m_shareRadius <= 0.0f )
		return NULL;

	// Get filtered objects in range
	std::vector<Object*> nearbyObjects = getObjectsInRange( other, md->m_shareRadius );
	
	// Check each nearby object for armor upgrade eligibility
	for( std::vector<Object*>::const_iterator it = nearbyObjects.begin(); it != nearbyObjects.end(); ++it )
	{
		Object *nearbyObj = *it;
		if( eligibleForArmorSet( nearbyObj ) )
			return nearbyObj;
	}

	return NULL;
}

// ------------------------------------------------------------------------------------------------
Object* SalvageCrateCollide::eligibleForLevelShare( Object *other )
{
	if( other == NULL )
		return NULL;

	const SalvageCrateCollideModuleData *md = getSalvageCrateCollideModuleData();
	if( md->m_shareRadius <= 0.0f )
		return NULL;

	// Get filtered objects in range
	std::vector<Object*> nearbyObjects = getObjectsInRange( other, md->m_shareRadius );
	
	// Check each nearby object for level gain eligibility
	for( std::vector<Object*>::const_iterator it = nearbyObjects.begin(); it != nearbyObjects.end(); ++it )
	{
		Object *nearbyObj = *it;
		if( eligibleForLevel( nearbyObj ) )
			return nearbyObj;
	}

	return NULL;
}

// ------------------------------------------------------------------------------------------------
Object* SalvageCrateCollide::eligibleForFullRestoreShare( Object *other )
{
	if( other == NULL )
		return NULL;

	const SalvageCrateCollideModuleData *md = getSalvageCrateCollideModuleData();
	if( md->m_shareRadius <= 0.0f )
		return NULL;

	// Get filtered objects in range
	std::vector<Object*> nearbyObjects = getObjectsInRange( other, md->m_shareRadius );
	
	// Check each nearby object for full restore eligibility
	for( std::vector<Object*>::const_iterator it = nearbyObjects.begin(); it != nearbyObjects.end(); ++it )
	{
		Object *nearbyObj = *it;
		if( eligibleForFullRestore( nearbyObj ) )
			return nearbyObj;
	}

	return NULL;
}

// ------------------------------------------------------------------------------------------------
Object* SalvageCrateCollide::eligibleForFillInventoryShare( Object *other )
{
	if( other == NULL )
		return NULL;

	const SalvageCrateCollideModuleData *md = getSalvageCrateCollideModuleData();
	if( md->m_shareRadius <= 0.0f )
		return NULL;

	// Get filtered objects in range
	std::vector<Object*> nearbyObjects = getObjectsInRange( other, md->m_shareRadius );
	
	// Check each nearby object for inventory fill eligibility
	for( std::vector<Object*>::const_iterator it = nearbyObjects.begin(); it != nearbyObjects.end(); ++it )
	{
		Object *nearbyObj = *it;
		if( eligibleForFillInventory( nearbyObj ) )
			return nearbyObj;
	}

	return NULL;
}

// ------------------------------------------------------------------------------------------------
Object* SalvageCrateCollide::eligibleForFullRepairShare( Object *other )
{
	if( other == NULL )
		return NULL;

	const SalvageCrateCollideModuleData *md = getSalvageCrateCollideModuleData();
	if( md->m_shareRadius <= 0.0f )
		return NULL;

	// Get filtered objects in range
	std::vector<Object*> nearbyObjects = getObjectsInRange( other, md->m_shareRadius );
	
	// Check each nearby object for full repair eligibility
	for( std::vector<Object*>::const_iterator it = nearbyObjects.begin(); it != nearbyObjects.end(); ++it )
	{
		Object *nearbyObj = *it;
		if( eligibleForFullRepair( nearbyObj ) )
			return nearbyObj;
	}

	return NULL;
}

// ------------------------------------------------------------------------------------------------
Bool SalvageCrateCollide::testWeaponChance()
{
	const SalvageCrateCollideModuleData *md = getSalvageCrateCollideModuleData();
	if( md->m_weaponChance == 1.0f )
		return TRUE; // don't waste a random number for a 100%

	Real randomNumber = GameLogicRandomValueReal( 0, 1 );
	if( randomNumber < md->m_weaponChance )
		return TRUE;

	return FALSE;
}

// ------------------------------------------------------------------------------------------------
Bool SalvageCrateCollide::testLevelChance()
{
	const SalvageCrateCollideModuleData *md = getSalvageCrateCollideModuleData();
	if( md->m_levelChance == 1.0f )
		return TRUE; // don't waste a random number for a 100%

	Real randomNumber = GameLogicRandomValueReal( 0, 1 );
	if( randomNumber < md->m_levelChance )
		return TRUE;

	return FALSE;
}

// ------------------------------------------------------------------------------------------------
Bool SalvageCrateCollide::testFullRestoreChance()
{
	const SalvageCrateCollideModuleData *md = getSalvageCrateCollideModuleData();
	if( md->m_fullRestoreChance == 1.0f )
		return TRUE; // don't waste a random number for a 100%

	Real randomNumber = GameLogicRandomValueReal( 0, 1 );
	if( randomNumber < md->m_fullRestoreChance )
		return TRUE;

	return FALSE;
}

// ------------------------------------------------------------------------------------------------
Bool SalvageCrateCollide::testFillInventoryChance()
{
	const SalvageCrateCollideModuleData *md = getSalvageCrateCollideModuleData();
	if( md->m_fillInventoryChance == 1.0f )
		return TRUE; // don't waste a random number for a 100%

	Real randomNumber = GameLogicRandomValueReal( 0, 1 );
	if( randomNumber < md->m_fillInventoryChance )
		return TRUE;

	return FALSE;
}

// ------------------------------------------------------------------------------------------------
Bool SalvageCrateCollide::testFullRepairChance()
{
	const SalvageCrateCollideModuleData *md = getSalvageCrateCollideModuleData();
	if( md->m_fullRepairChance == 1.0f )
		return TRUE; // don't waste a random number for a 100%

	Real randomNumber = GameLogicRandomValueReal( 0, 1 );
	if( randomNumber < md->m_fullRepairChance )
		return TRUE;

	return FALSE;
}

// ------------------------------------------------------------------------------------------------
void SalvageCrateCollide::doWeaponSet( Object *other )
{
	if( other->testWeaponSetFlag( WEAPONSET_CRATEUPGRADE_ONE ) )
	{
		other->clearWeaponSetFlag( WEAPONSET_CRATEUPGRADE_ONE );
		other->setWeaponSetFlag( WEAPONSET_CRATEUPGRADE_TWO );
	}
	else
	{
		other->setWeaponSetFlag( WEAPONSET_CRATEUPGRADE_ONE );
	}
}

// ------------------------------------------------------------------------------------------------
void SalvageCrateCollide::doArmorSet( Object *other )
{
	if( other->testArmorSetFlag( ARMORSET_CRATE_UPGRADE_ONE ) )
	{
		other->clearArmorSetFlag( ARMORSET_CRATE_UPGRADE_ONE );
		other->setArmorSetFlag( ARMORSET_CRATE_UPGRADE_TWO );

		other->clearAndSetModelConditionState(MODELCONDITION_ARMORSET_CRATEUPGRADE_ONE, MODELCONDITION_ARMORSET_CRATEUPGRADE_TWO);
	}
	else
	{
		other->setArmorSetFlag( ARMORSET_CRATE_UPGRADE_ONE );

		other->setModelConditionState(MODELCONDITION_ARMORSET_CRATEUPGRADE_ONE);
	}
}

// ------------------------------------------------------------------------------------------------
void SalvageCrateCollide::doLevelGain( Object *other )
{
	other->getExperienceTracker()->gainExpForLevel( 1 );
}

// ------------------------------------------------------------------------------------------------
void SalvageCrateCollide::doFullRestore( Object *other )
{
	if( other == NULL )
		return;

	// Get the body module to restore components
	BodyModuleInterface* body = other->getBodyModule();
	if( !body )
		return;

	// Restore all components to full health
	std::vector<Component> components = body->getComponents();
	for( std::vector<Component>::const_iterator it = components.begin(); it != components.end(); ++it )
	{
		const Component& component = *it;
		if( !component.getName().isEmpty() )
		{
			Component* comp = body->GetComponent<Component>(component.getName());
			if (comp)
			{
				comp->setCurrentHealth(comp->getCurrentMaxHealth());
			}
		}
	}

	// Update model state after component restoration
	body->setCorrectDamageState();
}

// ------------------------------------------------------------------------------------------------
void SalvageCrateCollide::doFillInventory( Object *other )
{
	if( other == NULL )
		return;

	// Get the inventory behavior to fill items
	InventoryBehavior* inventoryBehavior = other->getInventoryBehavior();
	if( !inventoryBehavior )
		return;

	// Fill all inventory items to maximum capacity - use instance data to respect upgrades
	const std::map<AsciiString, InventoryItemConfig>& inventoryItems = inventoryBehavior->getInventoryItems();
	for( std::map<AsciiString, InventoryItemConfig>::const_iterator it = inventoryItems.begin();
		 it != inventoryItems.end(); ++it )
	{
		const AsciiString& itemKey = it->first;
		
		// Get the current maximum storage capacity (which may be upgraded)
		Int maxStorage = inventoryBehavior->getMaxStorageCount( itemKey );
		
		// Set item count to maximum storage capacity
		inventoryBehavior->setItemCount( itemKey, maxStorage );
	}
}

// ------------------------------------------------------------------------------------------------
void SalvageCrateCollide::doFullRepair( Object *other )
{
	// Fully repair the unit
	BodyModuleInterface *body = other->getBodyModule();
	if( body )
	{
		// Restore to full health
		Real currentHealth = body->getHealth();
		Real maxHealth = body->getMaxHealth();
		Real healthDelta = maxHealth - currentHealth;
		if( healthDelta > 0.0f )
		{
			body->internalChangeHealth( healthDelta );
		}
	}
}

// ------------------------------------------------------------------------------------------------
void SalvageCrateCollide::doMoney( Object *other )
{
	const SalvageCrateCollideModuleData *md = getSalvageCrateCollideModuleData();

	Int money;
	if( md->m_minimumMoney != md->m_maximumMoney )// Random value doesn't like to get a constant range
		money = GameLogicRandomValue( md->m_minimumMoney, md->m_maximumMoney );
	else
		money = md->m_minimumMoney;

	if( money > 0 )
	{
		other->getControllingPlayer()->getMoney()->deposit( money );
		other->getControllingPlayer()->getScoreKeeper()->addMoneyEarned( money );

		//Display cash income floating over the crate.  Position is me, everything else is them.
		UnicodeString moneyString;
		moneyString.format( TheGameText->fetch( "GUI:AddCash" ), money );
		Coord3D pos;
		pos.set( getObject()->getPosition() );
		pos.z += 10.0f; //add a little z to make it show up above the unit.
		Color color = other->getControllingPlayer()->getPlayerColor() | GameMakeColor( 0, 0, 0, 230 );
		TheInGameUI->addFloatingText( moneyString, &pos, color );
	}
}

// ------------------------------------------------------------------------------------------------
/** CRC */
// ------------------------------------------------------------------------------------------------
void SalvageCrateCollide::crc( Xfer *xfer )
{

	// extend base class
	CrateCollide::crc( xfer );

}

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void SalvageCrateCollide::xfer( Xfer *xfer )
{

	// version
	XferVersion currentVersion = 1;
	XferVersion version = currentVersion;
	xfer->xferVersion( &version, currentVersion );

	// extend base class
	CrateCollide::xfer( xfer );

}

// ------------------------------------------------------------------------------------------------
/** Load post process */
// ------------------------------------------------------------------------------------------------
void SalvageCrateCollide::loadPostProcess( void )
{

	// extend base class
	CrateCollide::loadPostProcess();

}
