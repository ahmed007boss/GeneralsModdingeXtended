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

// FILE: ObjectPrerequisite.cpp /////////////////////////////////////////////////////////
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
// File name: ObjectPrerequisite.cpp
//
// Created:   Steven Johnson, October 2001
//
// Desc:      Object-based prerequisite system for checking conditions on specific objects
//
//-----------------------------------------------------------------------------

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/ObjectPrerequisite.h"
#include "Common/Player.h"
#include "Common/ThingFactory.h"
#include "Common/ThingTemplate.h"
#include "Common/KindOf.h"
#include "GameLogic/Object.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Components/Component.h"
#include "GameClient/Drawable.h"
#include "GameClient/GameText.h"

//-----------------------------------------------------------------------------
ObjectPrerequisite::ObjectPrerequisite() : m_namesResolved(false)
{
	init();
}

//-----------------------------------------------------------------------------
ObjectPrerequisite::~ObjectPrerequisite()
{
}

//-----------------------------------------------------------------------------
void ObjectPrerequisite::init()
{
	m_objectIsNames.clear();
	m_objectIsTemplates.clear();
	m_objectIsNotNames.clear();
	m_objectIsNotTemplates.clear();
	
	m_objectIsKindOfNames.clear();
	m_objectIsKindOfMask.clear();
	m_objectIsNoKindOfNames.clear();
	m_objectIsNoKindOfMask.clear();
	
	m_objectHasUpgradeNames.clear();
	m_objectHasUpgradeMask.clear();
	m_objectHasNotUpgradeNames.clear();
	m_objectHasNotUpgradeMask.clear();
	
	m_objectLevelMoreThan = -1;
	m_objectLevelLessThan = -1;
	
	m_objectHasModelConditionFlagNames.clear();
	m_objectHasNoModelConditionFlagNames.clear();
	m_objectHasModelConditionFlags.clear();
	m_objectHasNoModelConditionFlags.clear();
	
	m_objectHasStatusFlagNames.clear();
	m_objectHasNoStatusFlagNames.clear();
	m_objectHasStatusFlags.clear();
	m_objectHasNoStatusFlags.clear();
	
	m_objectHasComponentNames.clear();
	m_objectHasNoComponentNames.clear();
	m_objectHasWorkingComponentNames.clear();
	m_objectHasNoWorkingComponentNames.clear();
	
	m_objectHasNearbyObjects.clear();
	m_objectHasNoNearbyObjects.clear();
	
	m_objectHasAtLeastItems.clear();
	m_objectHasAtMostItems.clear();
	m_objectItemStorageFull.clear();
	m_objectItemStorageNotFull.clear();
	m_objectItemStorageEmpty.clear();
	
	m_namesResolved = false;	// TheSuperHackers @feature Ahmed Salah 15/01/2025 Initialize resolution flag
}

//=============================================================================
void ObjectPrerequisite::resolveNames()
{
	// Resolve object type prerequisites
	for (size_t i = 0; i < m_objectIsNames.size(); i++)
	{
		if (m_objectIsNames[i].isNotEmpty())
		{
			m_objectIsTemplates[i] = TheThingFactory->findTemplate(m_objectIsNames[i]);
			DEBUG_ASSERTCRASH(m_objectIsTemplates[i], ("could not find object prereq %s", m_objectIsNames[i].str()));
			m_objectIsNames[i].clear();
		}
	}

	for (size_t i = 0; i < m_objectIsNotNames.size(); i++)
	{
		if (m_objectIsNotNames[i].isNotEmpty())
		{
			m_objectIsNotTemplates[i] = TheThingFactory->findTemplate(m_objectIsNotNames[i]);
			DEBUG_ASSERTCRASH(m_objectIsNotTemplates[i], ("could not find object prereq %s", m_objectIsNotNames[i].str()));
			m_objectIsNotNames[i].clear();
		}
	}

	// Resolve KindOf prerequisites
	for (size_t i = 0; i < m_objectIsKindOfNames.size(); i++)
	{
		KindOfType kindOfType = (KindOfType)INI::scanIndexList(m_objectIsKindOfNames[i].str(), KindOfMaskType::getBitNames());
		m_objectIsKindOfMask.set(kindOfType);
	}

	for (size_t i = 0; i < m_objectIsNoKindOfNames.size(); i++)
	{
		KindOfType kindOfType = (KindOfType)INI::scanIndexList(m_objectIsNoKindOfNames[i].str(), KindOfMaskType::getBitNames());
		m_objectIsNoKindOfMask.set(kindOfType);
	}

	// Resolve upgrade prerequisites
	for (size_t i = 0; i < m_objectHasUpgradeNames.size(); i++)
	{
		const UpgradeTemplate* theTemplate = TheUpgradeCenter->findUpgrade(m_objectHasUpgradeNames[i]);
		if (!theTemplate)
		{
			DEBUG_CRASH(("An upgrade module references '%s', which is not an Upgrade", m_objectHasUpgradeNames[i].str()));
			throw INI_INVALID_DATA;
		}
		m_objectHasUpgradeMask.set(theTemplate->getUpgradeMask());
	}

	for (size_t i = 0; i < m_objectHasNotUpgradeNames.size(); i++)
	{
		const UpgradeTemplate* theTemplate = TheUpgradeCenter->findUpgrade(m_objectHasNotUpgradeNames[i]);
		if (!theTemplate)
		{
			DEBUG_CRASH(("An upgrade module references '%s', which is not an Upgrade", m_objectHasNotUpgradeNames[i].str()));
			throw INI_INVALID_DATA;
		}
		m_objectHasNotUpgradeMask.set(theTemplate->getUpgradeMask());
	}

	// Resolve model condition flag prerequisites
	for (size_t i = 0; i < m_objectHasModelConditionFlagNames.size(); i++)
	{
		m_objectHasModelConditionFlags.setBitByName(m_objectHasModelConditionFlagNames[i].str());
	}

	for (size_t i = 0; i < m_objectHasNoModelConditionFlagNames.size(); i++)
	{
		m_objectHasNoModelConditionFlags.setBitByName(m_objectHasNoModelConditionFlagNames[i].str());
	}

	// Resolve status flag prerequisites
	for (size_t i = 0; i < m_objectHasStatusFlagNames.size(); i++)
	{
		m_objectHasStatusFlags.setBitByName(m_objectHasStatusFlagNames[i].str());
	}

	for (size_t i = 0; i < m_objectHasNoStatusFlagNames.size(); i++)
	{
		m_objectHasNoStatusFlags.setBitByName(m_objectHasNoStatusFlagNames[i].str());
	}

	// Resolve nearby object prerequisites
	for (size_t i = 0; i < m_objectHasNearbyObjects.size(); i++)
	{
		NearbyObjectPrereq& prereq = m_objectHasNearbyObjects[i];
		if (!prereq.isKindOf && prereq.objectName.isNotEmpty())
		{
			prereq.objectTemplate = TheThingFactory->findTemplate(prereq.objectName);
			DEBUG_ASSERTCRASH(prereq.objectTemplate, ("could not find nearby object prereq %s", prereq.objectName.str()));
			prereq.objectName.clear();
		}
		else if (prereq.isKindOf && prereq.kindOfName.isNotEmpty())
		{
			KindOfType kindOfType = (KindOfType)INI::scanIndexList(prereq.kindOfName.str(), KindOfMaskType::getBitNames());
			prereq.kindOfMask = MAKE_KINDOF_MASK(kindOfType);
			prereq.kindOfName.clear();
		}
	}

	for (size_t i = 0; i < m_objectHasNoNearbyObjects.size(); i++)
	{
		NearbyObjectPrereq& prereq = m_objectHasNoNearbyObjects[i];
		if (!prereq.isKindOf && prereq.objectName.isNotEmpty())
		{
			prereq.objectTemplate = TheThingFactory->findTemplate(prereq.objectName);
			DEBUG_ASSERTCRASH(prereq.objectTemplate, ("could not find nearby object prereq %s", prereq.objectName.str()));
			prereq.objectName.clear();
		}
		else if (prereq.isKindOf && prereq.kindOfName.isNotEmpty())
		{
			KindOfType kindOfType = (KindOfType)INI::scanIndexList(prereq.kindOfName.str(), KindOfMaskType::getBitNames());
			prereq.kindOfMask = MAKE_KINDOF_MASK(kindOfType);
			prereq.kindOfName.clear();
		}
	}
}

//-----------------------------------------------------------------------------
Bool ObjectPrerequisite::isSatisfied(const Object* object) const
{
	// TheSuperHackers @feature Ahmed Salah 15/01/2025 Lazy initialization: resolve names if not already resolved
	if (!m_namesResolved)
	{
		const_cast<ObjectPrerequisite*>(this)->resolveNames();
		m_namesResolved = true;
	}
	
	if (!object)
		return false;

	// Check object type prerequisites
	for (size_t i = 0; i < m_objectIsTemplates.size(); i++)
	{
		if (object->getTemplate() != m_objectIsTemplates[i])
			return false;
	}

	for (size_t i = 0; i < m_objectIsNotTemplates.size(); i++)
	{
		if (object->getTemplate() == m_objectIsNotTemplates[i])
			return false;
	}

	// Check KindOf prerequisites
	if (m_objectIsKindOfMask.any())
	{
		if (!object->isAnyKindOf(m_objectIsKindOfMask))
			return false;
	}

	if (m_objectIsNoKindOfMask.any())
	{
		if (object->isAnyKindOf( m_objectIsNoKindOfMask))
			return false;
	}

	// Check upgrade prerequisites
	if (m_objectHasUpgradeMask.any())
	{
		if (!object->getObjectCompletedUpgradeMask().testForAny(m_objectHasUpgradeMask))
			return false;
	}

	if (m_objectHasNotUpgradeMask.any())
	{
		if (object->getObjectCompletedUpgradeMask().testForAll(m_objectHasNotUpgradeMask))
			return false;
	}

	// Check level prerequisites
	if (m_objectLevelMoreThan >= 0)
	{
		if (object->getVeterancyLevel() <= m_objectLevelMoreThan)
			return false;
	}

	if (m_objectLevelLessThan >= 0)
	{
		if (object->getVeterancyLevel() >= m_objectLevelLessThan)
			return false;
	}

	// Check model condition flag prerequisites
	Drawable* drawable = object->getDrawable();
	if (drawable)
	{
		ModelConditionFlags modelConditionFlags = drawable->getModelConditionFlags();
		
		// Check for required model condition flags
		if (m_objectHasModelConditionFlags.any())
		{
			if (modelConditionFlags.testForAny(m_objectHasModelConditionFlags) == FALSE)
				return false;
		}
		
		// Check for forbidden model condition flags
		if (m_objectHasNoModelConditionFlags.any())
		{
			if (modelConditionFlags.testForAny(m_objectHasNoModelConditionFlags) == TRUE)
				return false;
		}
	}
	else
	{
		// If object has no drawable, it can't have model condition flags
		// So if any model condition flags are required, this fails
		if (m_objectHasModelConditionFlags.any())
			return false;
	}

	// Check status flag prerequisites
	ObjectStatusMaskType objectStatusFlags = object->getStatusBits();
	
	// Check for required status flags
	if (m_objectHasStatusFlags.any())
	{
		if (objectStatusFlags.testForAny(m_objectHasStatusFlags) == FALSE)
			return false;
	}
	
	// Check for forbidden status flags
	if (m_objectHasNoStatusFlags.any())
	{
		if (objectStatusFlags.testForAny(m_objectHasNoStatusFlags) == TRUE)
			return false;
	}

	// Check component prerequisites
	BodyModuleInterface* bodyModule = object->getBodyModule();
	if (bodyModule)
	{
		// Check for required components
		for (size_t i = 0; i < m_objectHasComponentNames.size(); i++)
		{
			const AsciiString& componentName = m_objectHasComponentNames[i];
			Component* component = bodyModule->GetComponent<Component>(componentName);
			if (!component || component->getCurrentMaxHealth() <= 0.0f)
				return false; // Component doesn't exist
		}
		
		// Check for forbidden components
		for (size_t i = 0; i < m_objectHasNoComponentNames.size(); i++)
		{
			const AsciiString& componentName = m_objectHasNoComponentNames[i];
			Component* component = bodyModule->GetComponent<Component>(componentName);
			if (component && component->getCurrentMaxHealth() > 0.0f)
				return false; // Component exists
		}
		
		// Check for working components
		for (size_t i = 0; i < m_objectHasWorkingComponentNames.size(); i++)
		{
			const AsciiString& componentName = m_objectHasWorkingComponentNames[i];
			Component* component = bodyModule->GetComponent<Component>(componentName);
			if (!component || component->getStatus() == COMPONENT_STATUS_DOWNED || component->getStatus() == COMPONENT_STATUS_USER_DISABLED)
				return false; // Component doesn't exist or is not working
		}
		
		// Check for non-working components
		for (size_t i = 0; i < m_objectHasNoWorkingComponentNames.size(); i++)
		{
			const AsciiString& componentName = m_objectHasNoWorkingComponentNames[i];
			Component* component = bodyModule->GetComponent<Component>(componentName);
			if (component && component->getStatus() != COMPONENT_STATUS_DOWNED && component->getStatus() != COMPONENT_STATUS_USER_DISABLED)
				return false; // Component exists and is working
		}
	}
	else
	{
		// If object has no body module, it can't have components
		// So if any components are required, this fails
		if (!m_objectHasComponentNames.empty() || !m_objectHasWorkingComponentNames.empty())
			return false;
	}

	// Check nearby object prerequisites (OR logic - any nearby object found is sufficient)
	if (!m_objectHasNearbyObjects.empty())
	{
		Bool foundAnyNearby = false;
		for (size_t i = 0; i < m_objectHasNearbyObjects.size(); i++)
		{
			const NearbyObjectPrereq& prereq = m_objectHasNearbyObjects[i];
			Object* nearbyObject = NULL;
			
			if (!prereq.isKindOf)
			{
				// Find specific object type
				PartitionFilterThing filter(prereq.objectTemplate, true);
				PartitionFilter* filters[] = { &filter, NULL };
				nearbyObject = ThePartitionManager->getClosestObject(object->getPosition(), prereq.distance, FROM_CENTER_2D, filters);
			}
			else
			{
				// Find KindOf type
				PartitionFilterAcceptByKindOf filter(prereq.kindOfMask, KindOfMaskType());
				PartitionFilter* filters[] = { &filter, NULL };
				nearbyObject = ThePartitionManager->getClosestObject(object->getPosition(), prereq.distance, FROM_CENTER_2D, filters);
			}
			
			if (nearbyObject)
			{
				foundAnyNearby = true;
				break; // Found at least one, that's sufficient for OR logic
			}
		}
		
		if (!foundAnyNearby)
			return false;
	}

	// Check no nearby object prerequisites (AND logic - none of the specified objects should be nearby)
	for (size_t i = 0; i < m_objectHasNoNearbyObjects.size(); i++)
	{
		const NearbyObjectPrereq& prereq = m_objectHasNoNearbyObjects[i];
		Object* nearbyObject = NULL;
		
		if (!prereq.isKindOf)
		{
			// Find specific object type
			PartitionFilterThing filter(prereq.objectTemplate, true);
			PartitionFilter* filters[] = { &filter, NULL };
			nearbyObject = ThePartitionManager->getClosestObject(object->getPosition(), prereq.distance, FROM_CENTER_2D, filters);
		}
		else
		{
			// Find KindOf type
			PartitionFilterAcceptByKindOf filter(prereq.kindOfMask, KindOfMaskType());
			PartitionFilter* filters[] = { &filter, NULL };
			nearbyObject = ThePartitionManager->getClosestObject(object->getPosition(), prereq.distance, FROM_CENTER_2D, filters);
		}
		
		if (nearbyObject)
			return false;
	}

	// Check inventory item prerequisites
	// HasAtLeastItem prerequisites (OR logic - any item count condition met is sufficient)
	if (!m_objectHasAtLeastItems.empty())
	{
		Bool foundAnyAtLeast = false;
		for (size_t i = 0; i < m_objectHasAtLeastItems.size(); i++)
		{
			const ItemCountPrereq& prereq = m_objectHasAtLeastItems[i];
			Int currentCount = object->getTotalInventoryItemCount(prereq.itemName);
			if (currentCount >= prereq.requiredCount)
			{
				foundAnyAtLeast = true;
				break; // Found at least one, that's sufficient for OR logic
			}
		}
		
		if (!foundAnyAtLeast)
			return false;
	}

	// HasAtMostItem prerequisites (OR logic - any item count condition met is sufficient)
	if (!m_objectHasAtMostItems.empty())
	{
		Bool foundAnyAtMost = false;
		for (size_t i = 0; i < m_objectHasAtMostItems.size(); i++)
		{
			const ItemCountPrereq& prereq = m_objectHasAtMostItems[i];
			Int currentCount = object->getTotalInventoryItemCount(prereq.itemName);
			if (currentCount <= prereq.requiredCount)
			{
				foundAnyAtMost = true;
				break; // Found at least one, that's sufficient for OR logic
			}
		}
		
		if (!foundAnyAtMost)
			return false;
	}

	// ItemStorageFull prerequisites (OR logic - any item storage full is sufficient)
	if (!m_objectItemStorageFull.empty())
	{
		Bool foundAnyFull = false;
		for (size_t i = 0; i < m_objectItemStorageFull.size(); i++)
		{
			const AsciiString& itemName = m_objectItemStorageFull[i];
			Int currentCount = object->getTotalInventoryItemCount(itemName);
			Int maxStorage = 0;
			InventoryBehavior* inventoryBehavior = object->getInventoryBehavior();
			if (inventoryBehavior)
			{
				// Use instance data to respect upgrades
				maxStorage = inventoryBehavior->getMaxStorageCount(itemName);
			}
			if (maxStorage > 0 && currentCount >= maxStorage)
			{
				foundAnyFull = true;
				break; // Found at least one, that's sufficient for OR logic
			}
		}
		
		if (!foundAnyFull)
			return false;
	}

	// ItemStorageNotFull prerequisites (OR logic - any item storage not full is sufficient)
	if (!m_objectItemStorageNotFull.empty())
	{
		Bool foundAnyNotFull = false;
		for (size_t i = 0; i < m_objectItemStorageNotFull.size(); i++)
		{
			const AsciiString& itemName = m_objectItemStorageNotFull[i];
			Int currentCount = object->getTotalInventoryItemCount(itemName);
			Int maxStorage = 0;
			InventoryBehavior* inventoryBehavior = object->getInventoryBehavior();
			if (inventoryBehavior)
			{
				// Use instance data to respect upgrades
				maxStorage = inventoryBehavior->getMaxStorageCount(itemName);
			}
			if (maxStorage > 0 && currentCount < maxStorage)
			{
				foundAnyNotFull = true;
				break; // Found at least one, that's sufficient for OR logic
			}
		}
		
		if (!foundAnyNotFull)
			return false;
	}

	// ItemStorageEmpty prerequisites (OR logic - any item storage empty is sufficient)
	if (!m_objectItemStorageEmpty.empty())
	{
		Bool foundAnyEmpty = false;
		for (size_t i = 0; i < m_objectItemStorageEmpty.size(); i++)
		{
			const AsciiString& itemName = m_objectItemStorageEmpty[i];
			Int currentCount = object->getTotalInventoryItemCount(itemName);
			if (currentCount == 0)
			{
				foundAnyEmpty = true;
				break; // Found at least one, that's sufficient for OR logic
			}
		}
		
		if (!foundAnyEmpty)
			return false;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
UnicodeString ObjectPrerequisite::getRequiresList(const Object* object) const
{
	if (!object)
		return UnicodeString::TheEmptyString;

	UnicodeString requiresList = UnicodeString::TheEmptyString;
	Bool firstRequirement = true;

	// Check object type prerequisites
	for (size_t i = 0; i < m_objectIsTemplates.size(); i++)
	{
		if (object->getTemplate() != m_objectIsTemplates[i])
		{
			UnicodeString objectName = m_objectIsTemplates[i]->getDisplayName();
			if (firstRequirement)
				firstRequirement = false;
			else
				objectName.concat(L"\n");
			requiresList.concat(objectName);
		}
	}

	// Check KindOf prerequisites
	if (m_objectIsKindOfMask.any())
	{
		if (!object->isAnyKindOf(m_objectIsKindOfMask))
		{
			for (size_t i = 0; i < m_objectIsKindOfNames.size(); i++)
			{
				AsciiString kindOfKey;
				kindOfKey.format("KINDOF:%s", m_objectIsKindOfNames[i].str());
				UnicodeString kindOfName = TheGameText->fetch(kindOfKey.str());
				if (firstRequirement)
					firstRequirement = false;
				else
					kindOfName.concat(L"\n");
				requiresList.concat(kindOfName);
			}
		}
	}

	// Check upgrade prerequisites
	if (m_objectHasUpgradeMask.any())
	{
		if (!object->getObjectCompletedUpgradeMask().testForAll(m_objectHasUpgradeMask))
		{
			for (size_t i = 0; i < m_objectHasUpgradeNames.size(); i++)
			{
				const UpgradeTemplate* upgradeTemplate = TheUpgradeCenter->findUpgrade(m_objectHasUpgradeNames[i]);
				if (upgradeTemplate)
				{
					UpgradeMaskType upgradeMask = upgradeTemplate->getUpgradeMask();
					if (!object->getObjectCompletedUpgradeMask().testForAll(upgradeMask))
					{
						UnicodeString upgradeName = TheGameText->fetch(upgradeTemplate->getDisplayNameLabel().str());
						if (firstRequirement)
							firstRequirement = false;
						else
							upgradeName.concat(L"\n");
						requiresList.concat(upgradeName);
					}
				}
			}
		}
	}

	// Check level prerequisites
	if (m_objectLevelMoreThan >= 0)
	{
		if (object->getVeterancyLevel() <= m_objectLevelMoreThan)
		{
			UnicodeString levelReq;
			levelReq.format(L"Level > %d", m_objectLevelMoreThan);
			if (firstRequirement)
				firstRequirement = false;
			else
				levelReq.concat(L"\n");
			requiresList.concat(levelReq);
		}
	}

	if (m_objectLevelLessThan >= 0)
	{
		if (object->getVeterancyLevel() >= m_objectLevelLessThan)
		{
			UnicodeString levelReq;
			levelReq.format(L"Level < %d", m_objectLevelLessThan);
			if (firstRequirement)
				firstRequirement = false;
			else
				levelReq.concat(L"\n");
			requiresList.concat(levelReq);
		}
	}

	// Check condition flag prerequisites
	Drawable* drawable = object->getDrawable();
	if (drawable)
	{
		ModelConditionFlags modelConditionFlags = drawable->getModelConditionFlags();
		
		// Check for required model condition flags
		if (m_objectHasModelConditionFlags.any())
		{
			if (!modelConditionFlags.testForAll(m_objectHasModelConditionFlags))
			{
				// Add all required model condition flags to requirements list
				for (size_t i = 0; i < m_objectHasModelConditionFlagNames.size(); i++)
				{
					UnicodeString modelConditionFlagName = formatModelConditionFlagDisplayText(m_objectHasModelConditionFlagNames[i]);
					if (firstRequirement)
						firstRequirement = false;
					else
						modelConditionFlagName.concat(L"\n");
					requiresList.concat(modelConditionFlagName);
				}
			}
		}
	}
	else
	{
		// If object has no drawable, it can't have model condition flags
		// So if any model condition flags are required, add them to requirements
		if (m_objectHasModelConditionFlags.any())
		{
			for (size_t i = 0; i < m_objectHasModelConditionFlagNames.size(); i++)
			{
				UnicodeString modelConditionFlagName = formatModelConditionFlagDisplayText(m_objectHasModelConditionFlagNames[i]);
				if (firstRequirement)
					firstRequirement = false;
				else
					modelConditionFlagName.concat(L"\n");
				requiresList.concat(modelConditionFlagName);
			}
		}
	}

	// Check status flag prerequisites
	ObjectStatusMaskType objectStatusFlags = object->getStatusBits();
	
	// Check for required status flags
	if (m_objectHasStatusFlags.any())
	{
		if (objectStatusFlags.testForAny(m_objectHasStatusFlags) == FALSE)
		{
			// Add all required status flags to requirements list
			for (size_t i = 0; i < m_objectHasStatusFlagNames.size(); i++)
			{
				UnicodeString statusFlagName = formatStatusFlagDisplayText(m_objectHasStatusFlagNames[i]);
				if (firstRequirement)
					firstRequirement = false;
				else
					statusFlagName.concat(L"\n");
				requiresList.concat(statusFlagName);
			}
		}
	}

	// Check component prerequisites
	BodyModuleInterface* bodyModule = object->getBodyModule();
	if (bodyModule)
	{
		// Check for required components
		for (size_t i = 0; i < m_objectHasComponentNames.size(); i++)
		{
			const AsciiString& componentName = m_objectHasComponentNames[i];
			Component* component = bodyModule->GetComponent<Component>(componentName);
			if (!component || component->getCurrentMaxHealth() <= 0.0f)
			{
				UnicodeString componentName = formatObjectDisplayText(m_objectHasComponentNames[i]);
				if (firstRequirement)
					firstRequirement = false;
				else
					componentName.concat(L"\n");
				requiresList.concat(componentName);
			}
		}
		
		// Check for working components
		for (size_t i = 0; i < m_objectHasWorkingComponentNames.size(); i++)
		{
			const AsciiString& componentName = m_objectHasWorkingComponentNames[i];
			Component* component = bodyModule->GetComponent<Component>(componentName);
			if (!component || component->getStatus() == COMPONENT_STATUS_DOWNED || component->getStatus() == COMPONENT_STATUS_USER_DISABLED)
			{
				UnicodeString componentName = formatObjectDisplayText(m_objectHasWorkingComponentNames[i]);
				componentName.concat(L" (working)");
				if (firstRequirement)
					firstRequirement = false;
				else
					componentName.concat(L"\n");
				requiresList.concat(componentName);
			}
		}
	}
	else
	{
		// If object has no body module, it can't have components
		// So if any components are required, add them to requirements
		for (size_t i = 0; i < m_objectHasComponentNames.size(); i++)
		{
			UnicodeString componentName = formatObjectDisplayText(m_objectHasComponentNames[i]);
			if (firstRequirement)
				firstRequirement = false;
			else
				componentName.concat(L"\n");
			requiresList.concat(componentName);
		}
		
		for (size_t i = 0; i < m_objectHasWorkingComponentNames.size(); i++)
		{
			UnicodeString componentName = formatObjectDisplayText(m_objectHasWorkingComponentNames[i]);
			componentName.concat(L" (working)");
			if (firstRequirement)
				firstRequirement = false;
			else
				componentName.concat(L"\n");
			requiresList.concat(componentName);
		}
	}

	// Check nearby object prerequisites (OR logic - show all missing objects with "or" between them)
	if (!m_objectHasNearbyObjects.empty())
	{
		Bool foundAnyNearby = false;
		for (size_t i = 0; i < m_objectHasNearbyObjects.size(); i++)
		{
			const NearbyObjectPrereq& prereq = m_objectHasNearbyObjects[i];
			Object* nearbyObject = NULL;
			
			if (!prereq.isKindOf)
			{
				PartitionFilterThing filter(prereq.objectTemplate, true);
				PartitionFilter* filters[] = { &filter, NULL };
				nearbyObject = ThePartitionManager->getClosestObject(object->getPosition(), prereq.distance, FROM_CENTER_2D, filters);
			}
			else
			{
				PartitionFilterAcceptByKindOf filter(prereq.kindOfMask, KindOfMaskType());
				PartitionFilter* filters[] = { &filter, NULL };
				nearbyObject = ThePartitionManager->getClosestObject(object->getPosition(), prereq.distance, FROM_CENTER_2D, filters);
			}
			
			if (nearbyObject)
			{
				foundAnyNearby = true;
				break; // Found at least one, that's sufficient for OR logic
			}
		}
		
		// If no nearby objects found, show all missing ones with "or" between them
		if (!foundAnyNearby)
		{
			for (size_t i = 0; i < m_objectHasNearbyObjects.size(); i++)
			{
				const NearbyObjectPrereq& prereq = m_objectHasNearbyObjects[i];
				UnicodeString nearbyReq;
				
				if (!prereq.isKindOf)
				{
					nearbyReq = formatObjectDisplayText(prereq.objectTemplate->getName());
				}
				else
				{
					// Find the KindOf name from the original names
					for (size_t j = 0; j < m_objectIsKindOfNames.size(); j++)
					{
						KindOfType kindOfType = (KindOfType)INI::scanIndexList(m_objectIsKindOfNames[j].str(), KindOfMaskType::getBitNames());
						if (MAKE_KINDOF_MASK(kindOfType) == prereq.kindOfMask)
						{
							nearbyReq = formatKindOfDisplayText(m_objectIsKindOfNames[j]);
							break;
						}
					}
				}
				nearbyReq.concat(L" ");
				nearbyReq.concat(TheGameText->fetch("PREREQ:Within"));
				nearbyReq.concat(L" ");
				nearbyReq.concat(formatDistanceDisplayText(prereq.distance));
				nearbyReq.concat(TheGameText->fetch("PREREQ:Meter"));
				// Add "or" before each item except the first
				if (i > 0)
				{
					nearbyReq = TheGameText->fetch("PREREQ:Or") + L" " + nearbyReq;
				}

				if (firstRequirement)
					firstRequirement = false;
				else
					nearbyReq.concat(L"\n");

				requiresList.concat(nearbyReq);
			}
		}
	}

	// Check inventory item prerequisites
	// HasAtLeastItem prerequisites (OR logic - show all missing items with "or" between them)
	if (!m_objectHasAtLeastItems.empty())
	{
		Bool foundAnyAtLeast = false;
		for (size_t i = 0; i < m_objectHasAtLeastItems.size(); i++)
		{
			const ItemCountPrereq& prereq = m_objectHasAtLeastItems[i];
			Int currentCount = object->getTotalInventoryItemCount(prereq.itemName);
			if (currentCount >= prereq.requiredCount)
			{
				foundAnyAtLeast = true;
				break; // Found at least one, that's sufficient for OR logic
			}
		}
		
		// If no items meet the requirement, show all missing ones with "or" between them
		if (!foundAnyAtLeast)
		{
			for (size_t i = 0; i < m_objectHasAtLeastItems.size(); i++)
			{
				const ItemCountPrereq& prereq = m_objectHasAtLeastItems[i];
				UnicodeString itemReq;
				itemReq.format(L"%s ≥ %d", formatObjectDisplayText(prereq.itemName).str(), prereq.requiredCount);
				
				// Add "or" before each item except the first
				if (i > 0)
				{
					itemReq = TheGameText->fetch("PREREQ:Or") + L" " + itemReq;
				}

				if (firstRequirement)
					firstRequirement = false;
				else
					itemReq.concat(L"\n");

				requiresList.concat(itemReq);
			}
		}
	}

	// HasAtMostItem prerequisites (OR logic - show all missing items with "or" between them)
	if (!m_objectHasAtMostItems.empty())
	{
		Bool foundAnyAtMost = false;
		for (size_t i = 0; i < m_objectHasAtMostItems.size(); i++)
		{
			const ItemCountPrereq& prereq = m_objectHasAtMostItems[i];
			Int currentCount = object->getTotalInventoryItemCount(prereq.itemName);
			if (currentCount <= prereq.requiredCount)
			{
				foundAnyAtMost = true;
				break; // Found at least one, that's sufficient for OR logic
			}
		}
		
		// If no items meet the requirement, show all missing ones with "or" between them
		if (!foundAnyAtMost)
		{
			for (size_t i = 0; i < m_objectHasAtMostItems.size(); i++)
			{
				const ItemCountPrereq& prereq = m_objectHasAtMostItems[i];
				UnicodeString itemReq;
				itemReq.format(L"%s ≤ %d", formatObjectDisplayText(prereq.itemName).str(), prereq.requiredCount);
				
				// Add "or" before each item except the first
				if (i > 0)
				{
					itemReq = TheGameText->fetch("PREREQ:Or") + L" " + itemReq;
				}

				if (firstRequirement)
					firstRequirement = false;
				else
					itemReq.concat(L"\n");

				requiresList.concat(itemReq);
			}
		}
	}

	// ItemStorageFull prerequisites (OR logic - show all missing items with "or" between them)
	if (!m_objectItemStorageFull.empty())
	{
		Bool foundAnyFull = false;
		for (size_t i = 0; i < m_objectItemStorageFull.size(); i++)
		{
			const AsciiString& itemName = m_objectItemStorageFull[i];
			Int currentCount = object->getTotalInventoryItemCount(itemName);
			Int maxStorage = 0;
			InventoryBehavior* inventoryBehavior = object->getInventoryBehavior();
			if (inventoryBehavior)
			{
				// Use instance data to respect upgrades
				maxStorage = inventoryBehavior->getMaxStorageCount(itemName);
			}
			if (maxStorage > 0 && currentCount >= maxStorage)
			{
				foundAnyFull = true;
				break; // Found at least one, that's sufficient for OR logic
			}
		}
		
		// If no items are full, show all missing ones with "or" between them
		if (!foundAnyFull)
		{
			for (size_t i = 0; i < m_objectItemStorageFull.size(); i++)
			{
				const AsciiString& itemName = m_objectItemStorageFull[i];
				UnicodeString itemReq;
				itemReq.format(L"%s storage full", formatObjectDisplayText(itemName).str());
				
				// Add "or" before each item except the first
				if (i > 0)
				{
					itemReq = TheGameText->fetch("PREREQ:Or") + L" " + itemReq;
				}

				if (firstRequirement)
					firstRequirement = false;
				else
					itemReq.concat(L"\n");

				requiresList.concat(itemReq);
			}
		}
	}

	// ItemStorageNotFull prerequisites (OR logic - show all missing items with "or" between them)
	if (!m_objectItemStorageNotFull.empty())
	{
		Bool foundAnyNotFull = false;
		for (size_t i = 0; i < m_objectItemStorageNotFull.size(); i++)
		{
			const AsciiString& itemName = m_objectItemStorageNotFull[i];
			Int currentCount = object->getTotalInventoryItemCount(itemName);
			Int maxStorage = 0;
			InventoryBehavior* inventoryBehavior = object->getInventoryBehavior();
			if (inventoryBehavior)
			{
				// Use instance data to respect upgrades
				maxStorage = inventoryBehavior->getMaxStorageCount(itemName);
			}
			if (maxStorage > 0 && currentCount < maxStorage)
			{
				foundAnyNotFull = true;
				break; // Found at least one, that's sufficient for OR logic
			}
		}
		
		// If no items are not full, show all missing ones with "or" between them
		if (!foundAnyNotFull)
		{
			for (size_t i = 0; i < m_objectItemStorageNotFull.size(); i++)
			{
				const AsciiString& itemName = m_objectItemStorageNotFull[i];
				UnicodeString itemReq;
				itemReq.format(L"%s storage not full", formatObjectDisplayText(itemName).str());
				
				// Add "or" before each item except the first
				if (i > 0)
				{
					itemReq = TheGameText->fetch("PREREQ:Or") + L" " + itemReq;
				}

				if (firstRequirement)
					firstRequirement = false;
				else
					itemReq.concat(L"\n");

				requiresList.concat(itemReq);
			}
		}
	}

	// ItemStorageEmpty prerequisites (OR logic - show all missing items with "or" between them)
	if (!m_objectItemStorageEmpty.empty())
	{
		Bool foundAnyEmpty = false;
		for (size_t i = 0; i < m_objectItemStorageEmpty.size(); i++)
		{
			const AsciiString& itemName = m_objectItemStorageEmpty[i];
			Int currentCount = object->getTotalInventoryItemCount(itemName);
			if (currentCount == 0)
			{
				foundAnyEmpty = true;
				break; // Found at least one, that's sufficient for OR logic
			}
		}
		
		// If no items are empty, show all missing ones with "or" between them
		if (!foundAnyEmpty)
		{
			for (size_t i = 0; i < m_objectItemStorageEmpty.size(); i++)
			{
				const AsciiString& itemName = m_objectItemStorageEmpty[i];
				UnicodeString itemReq;
				itemReq.format(L"%s storage empty", formatObjectDisplayText(itemName).str());
				
				// Add "or" before each item except the first
				if (i > 0)
				{
					itemReq = TheGameText->fetch("PREREQ:Or") + L" " + itemReq;
				}

				if (firstRequirement)
					firstRequirement = false;
				else
					itemReq.concat(L"\n");

				requiresList.concat(itemReq);
			}
		}
	}

	return requiresList;
}

//-------------------------------------------------------------------------------------------------
UnicodeString ObjectPrerequisite::getConflictList(const Object* object) const
{
	if (!object)
		return UnicodeString::TheEmptyString;

	UnicodeString conflictList = UnicodeString::TheEmptyString;
	Bool firstConflict = true;

	// Check object type conflicts
	for (size_t i = 0; i < m_objectIsNotTemplates.size(); i++)
	{
		if (object->getTemplate() == m_objectIsNotTemplates[i])
		{
			UnicodeString objectName = m_objectIsNotTemplates[i]->getDisplayName();
			if (firstConflict)
				firstConflict = false;
			else
				objectName.concat(L"\n");
			conflictList.concat(objectName);
		}
	}

	// Check KindOf conflicts
	if (m_objectIsNoKindOfMask.any())
	{
		if (object->isAnyKindOf(m_objectIsNoKindOfMask))
		{
			for (size_t i = 0; i < m_objectIsNoKindOfNames.size(); i++)
			{
				AsciiString kindOfKey;
				kindOfKey.format("KINDOF:%s", m_objectIsNoKindOfNames[i].str());
				UnicodeString kindOfName = TheGameText->fetch(kindOfKey.str());
				if (firstConflict)
					firstConflict = false;
				else
					kindOfName.concat(L"\n");
				conflictList.concat(kindOfName);
			}
		}
	}

	// Check upgrade conflicts
	if (m_objectHasNotUpgradeMask.any())
	{
		if (object->getObjectCompletedUpgradeMask().testForAny(m_objectHasNotUpgradeMask))
		{
			for (size_t i = 0; i < m_objectHasNotUpgradeNames.size(); i++)
			{
				const UpgradeTemplate* upgradeTemplate = TheUpgradeCenter->findUpgrade(m_objectHasNotUpgradeNames[i]);
				if (upgradeTemplate)
				{
					UpgradeMaskType upgradeMask = upgradeTemplate->getUpgradeMask();
					if (object->getObjectCompletedUpgradeMask().testForAny(upgradeMask))
					{
						UnicodeString upgradeName = TheGameText->fetch(upgradeTemplate->getDisplayNameLabel().str());
						if (firstConflict)
							firstConflict = false;
						else
							upgradeName.concat(L"\n");
						conflictList.concat(upgradeName);
					}
				}
			}
		}
	}

	// Check condition flag conflicts
	Drawable* drawable = object->getDrawable();
	if (drawable)
	{
		ModelConditionFlags modelConditionFlags = drawable->getModelConditionFlags();
		
		// Check for forbidden model condition flags
		if (m_objectHasNoModelConditionFlags.any())
		{
			if (modelConditionFlags.testForAny(m_objectHasNoModelConditionFlags))
			{
				// Add all forbidden model condition flags to conflict list
				for (size_t i = 0; i < m_objectHasNoModelConditionFlagNames.size(); i++)
				{
					UnicodeString modelConditionFlagName = formatModelConditionFlagDisplayText(m_objectHasNoModelConditionFlagNames[i]);
					if (firstConflict)
						firstConflict = false;
					else
						modelConditionFlagName.concat(L"\n");
					conflictList.concat(modelConditionFlagName);
				}
			}
		}
	}

	// Check status flag conflicts
	ObjectStatusMaskType objectStatusFlags = object->getStatusBits();
	
	// Check for forbidden status flags
	if (m_objectHasNoStatusFlags.any())
	{
		if (objectStatusFlags.testForAny(m_objectHasNoStatusFlags) == TRUE)
		{
			// Add all forbidden status flags to conflict list
			for (size_t i = 0; i < m_objectHasNoStatusFlagNames.size(); i++)
			{
				UnicodeString statusFlagName = formatStatusFlagDisplayText(m_objectHasNoStatusFlagNames[i]);
				if (firstConflict)
					firstConflict = false;
				else
					statusFlagName.concat(L"\n");
				conflictList.concat(statusFlagName);
			}
		}
	}

	// Check component conflicts
	BodyModuleInterface* bodyModule = object->getBodyModule();
	if (bodyModule)
	{
		// Check for forbidden components
		for (size_t i = 0; i < m_objectHasNoComponentNames.size(); i++)
		{
			const AsciiString& componentName = m_objectHasNoComponentNames[i];
			Component* component = bodyModule->GetComponent<Component>(componentName);
			if (component && component->getCurrentMaxHealth() > 0.0f)
			{
				UnicodeString componentName = formatObjectDisplayText(m_objectHasNoComponentNames[i]);
				if (firstConflict)
					firstConflict = false;
				else
					componentName.concat(L"\n");
				conflictList.concat(componentName);
			}
		}
		
		// Check for forbidden working components
		for (size_t i = 0; i < m_objectHasNoWorkingComponentNames.size(); i++)
		{
			const AsciiString& componentName = m_objectHasNoWorkingComponentNames[i];
			Component* component = bodyModule->GetComponent<Component>(componentName);
			if (component && component->getStatus() != COMPONENT_STATUS_DOWNED && component->getStatus() != COMPONENT_STATUS_USER_DISABLED)
			{
				UnicodeString componentName = formatObjectDisplayText(m_objectHasNoWorkingComponentNames[i]);
				componentName.concat(L" (working)");
				if (firstConflict)
					firstConflict = false;
				else
					componentName.concat(L"\n");
				conflictList.concat(componentName);
			}
		}
	}

	// Check nearby object conflicts
	for (size_t i = 0; i < m_objectHasNoNearbyObjects.size(); i++)
	{
		const NearbyObjectPrereq& prereq = m_objectHasNoNearbyObjects[i];
		Object* nearbyObject = NULL;
		
		if (!prereq.isKindOf)
		{
			PartitionFilterThing filter(prereq.objectTemplate, true);
			PartitionFilter* filters[] = { &filter, NULL };
			nearbyObject = ThePartitionManager->getClosestObject(object->getPosition(), prereq.distance, FROM_CENTER_2D, filters);
		}
		else
		{
			PartitionFilterAcceptByKindOf filter(prereq.kindOfMask, KindOfMaskType());
			PartitionFilter* filters[] = { &filter, NULL };
			nearbyObject = ThePartitionManager->getClosestObject(object->getPosition(), prereq.distance, FROM_CENTER_2D, filters);
		}
		
		if (nearbyObject)
		{
			UnicodeString nearbyConflict;
			if (!prereq.isKindOf)
			{
				nearbyConflict = formatObjectDisplayText(prereq.objectTemplate->getName());
			}
			else
			{
				// Find the KindOf name from the original names
				for (size_t j = 0; j < m_objectIsNoKindOfNames.size(); j++)
				{
					KindOfType kindOfType = (KindOfType)INI::scanIndexList(m_objectIsNoKindOfNames[j].str(), KindOfMaskType::getBitNames());
					if (MAKE_KINDOF_MASK(kindOfType) == prereq.kindOfMask)
					{
						nearbyConflict = formatKindOfDisplayText(m_objectIsNoKindOfNames[j]);
						break;
					}
				}
			}
			nearbyConflict.concat(L" within ");
			nearbyConflict.concat(formatDistanceDisplayText(prereq.distance));
			
			if (firstConflict)
				firstConflict = false;
			else
				nearbyConflict.concat(L"\n");
			conflictList.concat(nearbyConflict);
		}
	}

	return conflictList;
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::addObjectIsPrereq(AsciiString objectName)
{
	m_objectIsNames.push_back(objectName);
	m_objectIsTemplates.push_back(NULL);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::addObjectIsNotPrereq(AsciiString objectName)
{
	m_objectIsNotNames.push_back(objectName);
	m_objectIsNotTemplates.push_back(NULL);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::addObjectIsKindOfPrereq(AsciiString kindOfName)
{
	m_objectIsKindOfNames.push_back(kindOfName);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::addObjectIsNoKindOfPrereq(AsciiString kindOfName)
{
	m_objectIsNoKindOfNames.push_back(kindOfName);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::addObjectHasUpgradePrereq(AsciiString upgradeName)
{
	m_objectHasUpgradeNames.push_back(upgradeName);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::addObjectHasNotUpgradePrereq(AsciiString upgradeName)
{
	m_objectHasNotUpgradeNames.push_back(upgradeName);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::addObjectLevelMoreThanPrereq(Int level)
{
	m_objectLevelMoreThan = level;
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::addObjectLevelLessThanPrereq(Int level)
{
	m_objectLevelLessThan = level;
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::addObjectHasNearbyObjectPrereq(AsciiString objectName, Real distance)
{
	NearbyObjectPrereq prereq;
	prereq.objectName = objectName;
	prereq.objectTemplate = NULL;
	prereq.distance = distance;
	prereq.isKindOf = false;
	prereq.kindOfName.clear();
	prereq.kindOfMask.clear();
	m_objectHasNearbyObjects.push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::addObjectHasNearbyKindOfPrereq(AsciiString kindOfName, Real distance)
{
	NearbyObjectPrereq prereq;
	prereq.objectName.clear();
	prereq.objectTemplate = NULL;
	prereq.distance = distance;
	prereq.isKindOf = true;
	prereq.kindOfName = kindOfName;
	prereq.kindOfMask.clear();
	m_objectHasNearbyObjects.push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::addObjectHasNoNearbyObjectPrereq(AsciiString objectName, Real distance)
{
	NearbyObjectPrereq prereq;
	prereq.objectName = objectName;
	prereq.objectTemplate = NULL;
	prereq.distance = distance;
	prereq.isKindOf = false;
	prereq.kindOfName.clear();
	prereq.kindOfMask.clear();
	m_objectHasNoNearbyObjects.push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::addObjectHasNoNearbyKindOfPrereq(AsciiString kindOfName, Real distance)
{
	NearbyObjectPrereq prereq;
	prereq.objectName.clear();
	prereq.objectTemplate = NULL;
	prereq.distance = distance;
	prereq.isKindOf = true;
	prereq.kindOfName = kindOfName;
	prereq.kindOfMask.clear();
	m_objectHasNoNearbyObjects.push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::addObjectHasModelConditionFlagPrereq(AsciiString modelConditionFlagName)
{
	m_objectHasModelConditionFlagNames.push_back(modelConditionFlagName);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::addObjectHasNoModelConditionFlagPrereq(AsciiString modelConditionFlagName)
{
	m_objectHasNoModelConditionFlagNames.push_back(modelConditionFlagName);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::addObjectHasStatusFlagPrereq(AsciiString statusFlagName)
{
	m_objectHasStatusFlagNames.push_back(statusFlagName);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::addObjectHasNoStatusFlagPrereq(AsciiString statusFlagName)
{
	m_objectHasNoStatusFlagNames.push_back(statusFlagName);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::addObjectHasComponentPrereq(AsciiString componentName)
{
	m_objectHasComponentNames.push_back(componentName);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::addObjectHasNoComponentPrereq(AsciiString componentName)
{
	m_objectHasNoComponentNames.push_back(componentName);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::addObjectHasWorkingComponentPrereq(AsciiString componentName)
{
	m_objectHasWorkingComponentNames.push_back(componentName);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::addObjectHasNoWorkingComponentPrereq(AsciiString componentName)
{
	m_objectHasNoWorkingComponentNames.push_back(componentName);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::addObjectHasAtLeastItemPrereq(AsciiString itemName, Int count)
{
	ItemCountPrereq prereq;
	prereq.itemName = itemName;
	prereq.requiredCount = count;
	m_objectHasAtLeastItems.push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::addObjectHasAtMostItemPrereq(AsciiString itemName, Int count)
{
	ItemCountPrereq prereq;
	prereq.itemName = itemName;
	prereq.requiredCount = count;
	m_objectHasAtMostItems.push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::addObjectItemStorageFullPrereq(AsciiString itemName)
{
	m_objectItemStorageFull.push_back(itemName);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::addObjectItemStorageNotFullPrereq(AsciiString itemName)
{
	m_objectItemStorageNotFull.push_back(itemName);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::addObjectItemStorageEmptyPrereq(AsciiString itemName)
{
	m_objectItemStorageEmpty.push_back(itemName);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::parseObjectPrerequisites(INI* ini, void* instance, void* store, const void* userData)
{
	std::vector<ObjectPrerequisite>* prereqVector = (std::vector<ObjectPrerequisite>*)instance;

	static const FieldParse myFieldParse[] =
	{
		{ "ObjectIs", ObjectPrerequisite::parseObjectIs, 0, 0 },
		{ "ObjectIsNot", ObjectPrerequisite::parseObjectIsNot, 0, 0 },
		{ "ObjectIsKindOf", ObjectPrerequisite::parseObjectIsKindOf, 0, 0 },
		{ "ObjectIsNoKindOf", ObjectPrerequisite::parseObjectIsNoKindOf, 0, 0 },
		{ "ObjectHasUpgrade", ObjectPrerequisite::parseObjectHasUpgrade, 0, 0 },
		{ "ObjectHasNotUpgrade", ObjectPrerequisite::parseObjectHasNotUpgrade, 0, 0 },
		{ "ObjectLevelMoreThan", ObjectPrerequisite::parseObjectLevelMoreThan, 0, 0 },
		{ "ObjectLevelLessThan", ObjectPrerequisite::parseObjectLevelLessThan, 0, 0 },
		{ "ObjectHasNearbyObject", ObjectPrerequisite::parseObjectHasNearbyObject, 0, 0 },
		{ "ObjectHasNearbyKindOf", ObjectPrerequisite::parseObjectHasNearbyKindOf, 0, 0 },
		{ "ObjectHasNoNearbyObject", ObjectPrerequisite::parseObjectHasNoNearbyObject, 0, 0 },
		{ "ObjectHasNoNearbyKindOf", ObjectPrerequisite::parseObjectHasNoNearbyKindOf, 0, 0 },
		{ "ObjectHasModelCondition", ObjectPrerequisite::parseObjectHasModelConditionFlag, 0, 0 },
		{ "ObjectHasNoModelCondition", ObjectPrerequisite::parseObjectHasNoModelConditionFlag, 0, 0 },
		{ "ObjectHasStatus", ObjectPrerequisite::parseObjectHasStatusFlag, 0, 0 },
		{ "ObjectHasNoStatus", ObjectPrerequisite::parseObjectHasNoStatusFlag, 0, 0 },
		{ "ObjectHasComponent", ObjectPrerequisite::parseObjectHasComponent, 0, 0 },
		{ "ObjectHasNoComponent", ObjectPrerequisite::parseObjectHasNoComponent, 0, 0 },
		{ "ObjectHasWorkingComponent", ObjectPrerequisite::parseObjectHasWorkingComponent, 0, 0 },
		{ "ObjectHasNoWorkingComponent", ObjectPrerequisite::parseObjectHasNoWorkingComponent, 0, 0 },
		{ "HasAtLeastItem", ObjectPrerequisite::parseHasAtLeastItem, 0, 0 },     // True if the unit has ≥ a given number of a specific item
		{ "HasAtMostItem", ObjectPrerequisite::parseHasAtMostItem, 0, 0 },       // True if the unit has ≤ a given number of a specific item
		{ "ItemStorageFull", ObjectPrerequisite::parseItemStorageFull, 0, 0 },   // True if storage for a specific item is completely full
		{ "ItemStorageNotFull", ObjectPrerequisite::parseItemStorageNotFull, 0, 0 }, // True if storage for a specific item is not full
		{ "ItemStorageEmpty", ObjectPrerequisite::parseItemStorageEmpty, 0, 0 }, // True if storage for a specific item is completely empty
		{ 0, 0, 0, 0 }
	};

	if (ini->getLoadType() == INI_LOAD_CREATE_OVERRIDES)
	{
		prereqVector->clear();
	}

	ini->initFromINI(prereqVector, myFieldParse);

}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::parseObjectIs(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ObjectPrerequisite>* v = (std::vector<ObjectPrerequisite>*)instance;
	ObjectPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addObjectIsPrereq(AsciiString(token));
	}
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::parseObjectIsNot(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ObjectPrerequisite>* v = (std::vector<ObjectPrerequisite>*)instance;
	ObjectPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addObjectIsNotPrereq(AsciiString(token));
	}
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::parseObjectIsKindOf(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ObjectPrerequisite>* v = (std::vector<ObjectPrerequisite>*)instance;
	ObjectPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addObjectIsKindOfPrereq(AsciiString(token));
	}
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::parseObjectIsNoKindOf(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ObjectPrerequisite>* v = (std::vector<ObjectPrerequisite>*)instance;
	ObjectPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addObjectIsNoKindOfPrereq(AsciiString(token));
	}
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::parseObjectHasUpgrade(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ObjectPrerequisite>* v = (std::vector<ObjectPrerequisite>*)instance;
	ObjectPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addObjectHasUpgradePrereq(AsciiString(token));
	}
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::parseObjectHasNotUpgrade(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ObjectPrerequisite>* v = (std::vector<ObjectPrerequisite>*)instance;
	ObjectPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addObjectHasNotUpgradePrereq(AsciiString(token));
	}
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::parseObjectLevelMoreThan(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ObjectPrerequisite>* v = (std::vector<ObjectPrerequisite>*)instance;
	ObjectPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addObjectLevelMoreThanPrereq(atoi(token));
	}
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::parseObjectLevelLessThan(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ObjectPrerequisite>* v = (std::vector<ObjectPrerequisite>*)instance;
	ObjectPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addObjectLevelLessThanPrereq(atoi(token));
	}
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::parseObjectHasNearbyObject(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ObjectPrerequisite>* v = (std::vector<ObjectPrerequisite>*)instance;
	ObjectPrerequisite prereq;
	AsciiString fullLine = parseFullLineFromINI(ini);
	AsciiString remaining = fullLine;
	AsciiString objectName;
	Real distance;
	
	// Parse all object-distance pairs (OR logic)
	while (parseObjectDistancePair(remaining, objectName, distance))
	{
		prereq.addObjectHasNearbyObjectPrereq(objectName, distance);
	}
	
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::parseObjectHasNearbyKindOf(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ObjectPrerequisite>* v = (std::vector<ObjectPrerequisite>*)instance;
	ObjectPrerequisite prereq;
	AsciiString fullLine = parseFullLineFromINI(ini);
	AsciiString remaining = fullLine;
	AsciiString kindOfName;
	Real distance;
	
	// Parse all KindOf-distance pairs (OR logic)
	while (parseKindOfDistancePair(remaining, kindOfName, distance))
	{
		prereq.addObjectHasNearbyKindOfPrereq(kindOfName, distance);
	}
	
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::parseObjectHasNoNearbyObject(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ObjectPrerequisite>* v = (std::vector<ObjectPrerequisite>*)instance;
	ObjectPrerequisite prereq;
	AsciiString fullLine = parseFullLineFromINI(ini);
	AsciiString remaining = fullLine;
	AsciiString objectName;
	Real distance;
	
	// Parse all object-distance pairs (OR logic)
	while (parseObjectDistancePair(remaining, objectName, distance))
	{
		prereq.addObjectHasNoNearbyObjectPrereq(objectName, distance);
	}
	
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::parseObjectHasNoNearbyKindOf(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ObjectPrerequisite>* v = (std::vector<ObjectPrerequisite>*)instance;
	ObjectPrerequisite prereq;
	AsciiString fullLine = parseFullLineFromINI(ini);
	AsciiString remaining = fullLine;
	AsciiString kindOfName;
	Real distance;
	
	// Parse all KindOf-distance pairs (OR logic)
	while (parseKindOfDistancePair(remaining, kindOfName, distance))
	{
		prereq.addObjectHasNoNearbyKindOfPrereq(kindOfName, distance);
	}
	
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::parseObjectHasModelConditionFlag(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ObjectPrerequisite>* v = (std::vector<ObjectPrerequisite>*)instance;
	ObjectPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addObjectHasModelConditionFlagPrereq(AsciiString(token));
	}
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::parseObjectHasNoModelConditionFlag(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ObjectPrerequisite>* v = (std::vector<ObjectPrerequisite>*)instance;
	ObjectPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addObjectHasNoModelConditionFlagPrereq(AsciiString(token));
	}
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::parseObjectHasStatusFlag(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ObjectPrerequisite>* v = (std::vector<ObjectPrerequisite>*)instance;
	ObjectPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addObjectHasStatusFlagPrereq(AsciiString(token));
	}
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::parseObjectHasNoStatusFlag(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ObjectPrerequisite>* v = (std::vector<ObjectPrerequisite>*)instance;
	ObjectPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addObjectHasNoStatusFlagPrereq(AsciiString(token));
	}
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::parseObjectHasComponent(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ObjectPrerequisite>* v = (std::vector<ObjectPrerequisite>*)instance;
	ObjectPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addObjectHasComponentPrereq(AsciiString(token));
	}
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::parseObjectHasNoComponent(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ObjectPrerequisite>* v = (std::vector<ObjectPrerequisite>*)instance;
	ObjectPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addObjectHasNoComponentPrereq(AsciiString(token));
	}
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::parseObjectHasWorkingComponent(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ObjectPrerequisite>* v = (std::vector<ObjectPrerequisite>*)instance;
	ObjectPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addObjectHasWorkingComponentPrereq(AsciiString(token));
	}
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::parseObjectHasNoWorkingComponent(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ObjectPrerequisite>* v = (std::vector<ObjectPrerequisite>*)instance;
	ObjectPrerequisite prereq;
	for (const char* token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		prereq.addObjectHasNoWorkingComponentPrereq(AsciiString(token));
	}
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::parseHasAtLeastItem(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ObjectPrerequisite>* v = (std::vector<ObjectPrerequisite>*)instance;
	ObjectPrerequisite prereq;
	AsciiString fullLine = parseFullLineFromINI(ini);
	AsciiString remaining = fullLine;
	AsciiString itemName;
	Int count;
	
	// Parse all item-count pairs (OR logic)
	while (parseItemCountPair(remaining, itemName, count))
	{
		prereq.addObjectHasAtLeastItemPrereq(itemName, count);
	}
	
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::parseHasAtMostItem(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ObjectPrerequisite>* v = (std::vector<ObjectPrerequisite>*)instance;
	ObjectPrerequisite prereq;
	AsciiString fullLine = parseFullLineFromINI(ini);
	AsciiString remaining = fullLine;
	AsciiString itemName;
	Int count;
	
	// Parse all item-count pairs (OR logic)
	while (parseItemCountPair(remaining, itemName, count))
	{
		prereq.addObjectHasAtMostItemPrereq(itemName, count);
	}
	
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::parseItemStorageFull(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ObjectPrerequisite>* v = (std::vector<ObjectPrerequisite>*)instance;
	ObjectPrerequisite prereq;
	AsciiString fullLine = parseFullLineFromINI(ini);
	AsciiString remaining = fullLine;
	AsciiString itemName;
	
	// Parse all item names (OR logic)
	while (remaining.nextToken(&itemName, " "))
	{
		if (!itemName.isEmpty())
		{
			prereq.addObjectItemStorageFullPrereq(itemName);
		}
	}
	
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::parseItemStorageNotFull(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ObjectPrerequisite>* v = (std::vector<ObjectPrerequisite>*)instance;
	ObjectPrerequisite prereq;
	AsciiString fullLine = parseFullLineFromINI(ini);
	AsciiString remaining = fullLine;
	AsciiString itemName;
	
	// Parse all item names (OR logic)
	while (remaining.nextToken(&itemName, " "))
	{
		if (!itemName.isEmpty())
		{
			prereq.addObjectItemStorageNotFullPrereq(itemName);
		}
	}
	
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------
void ObjectPrerequisite::parseItemStorageEmpty(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	std::vector<ObjectPrerequisite>* v = (std::vector<ObjectPrerequisite>*)instance;
	ObjectPrerequisite prereq;
	AsciiString fullLine = parseFullLineFromINI(ini);
	AsciiString remaining = fullLine;
	AsciiString itemName;
	
	// Parse all item names (OR logic)
	while (remaining.nextToken(&itemName, " "))
	{
		if (!itemName.isEmpty())
		{
			prereq.addObjectItemStorageEmptyPrereq(itemName);
		}
	}
	
	v->push_back(prereq);
}

//-------------------------------------------------------------------------------------------------

//=============================================================================
// Helper methods for refactoring repeated code
//=============================================================================

//-------------------------------------------------------------------------------------------------
// Parse entire line from INI as a single token
AsciiString ObjectPrerequisite::parseFullLineFromINI(INI* ini)
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
// Parse object name and distance pair from string
Bool ObjectPrerequisite::parseObjectDistancePair(AsciiString& remaining, AsciiString& objectName, Real& distance)
{
	// Get the object name
	if (!remaining.nextToken(&objectName, " "))
		return false;
	
	// Get the distance
	AsciiString distanceStr;
	if (!remaining.nextToken(&distanceStr, " "))
		return false;
	
	distance = (Real)atof(distanceStr.str());
	return true;
}

//-------------------------------------------------------------------------------------------------
// Parse KindOf name and distance pair from string
Bool ObjectPrerequisite::parseKindOfDistancePair(AsciiString& remaining, AsciiString& kindOfName, Real& distance)
{
	// Get the KindOf name
	if (!remaining.nextToken(&kindOfName, " "))
		return false;
	
	// Get the distance
	AsciiString distanceStr;
	if (!remaining.nextToken(&distanceStr, " "))
		return false;
	
	distance = (Real)atof(distanceStr.str());
	return true;
}

//-------------------------------------------------------------------------------------------------
// Parse item name and count pair from string
Bool ObjectPrerequisite::parseItemCountPair(AsciiString& remaining, AsciiString& itemName, Int& count)
{
	// Get the item name
	if (!remaining.nextToken(&itemName, " "))
		return false;
	
	// Get the count
	AsciiString countStr;
	if (!remaining.nextToken(&countStr, " "))
		return false;
	
	count = atoi(countStr.str());
	return true;
}

//-------------------------------------------------------------------------------------------------
// Format object display text
UnicodeString ObjectPrerequisite::formatObjectDisplayText(const AsciiString& objectName)
{
	UnicodeString result;
	const ThingTemplate* objectTemplate = TheThingFactory->findTemplate(objectName);
	if (objectTemplate)
	{
		UnicodeString objectDisplayName = objectTemplate->getDisplayName();
		result.concat(objectDisplayName);
	}
	else
	{
		// Fallback to object name if template not found
		AsciiString objectKey;
		objectKey.format("OBJECT:%s", objectName.str());
		UnicodeString objectDisplayName = TheGameText->fetch(objectKey.str());
		objectDisplayName.toLower();
		result.concat(objectDisplayName);
	}
	return result;
}

//-------------------------------------------------------------------------------------------------
// Format KindOf display text
UnicodeString ObjectPrerequisite::formatKindOfDisplayText(const AsciiString& kindOfName)
{
	UnicodeString result;
	AsciiString kindOfKey;
	kindOfKey.format("KINDOF:%s", kindOfName.str());
	UnicodeString kindOfDisplayName = TheGameText->fetch(kindOfKey.str());
	kindOfDisplayName.toLower();
	result.concat(kindOfDisplayName);
	return result;
}

//-------------------------------------------------------------------------------------------------
// Format distance display text
UnicodeString ObjectPrerequisite::formatDistanceDisplayText(Real distance)
{
	UnicodeString result;
	result.format(L"%.0f", distance);
	return result;
}

//-------------------------------------------------------------------------------------------------
// Format condition flag display text
UnicodeString ObjectPrerequisite::formatModelConditionFlagDisplayText(const AsciiString& modelConditionFlagName)
{
	UnicodeString result;
	AsciiString modelConditionFlagKey;
	modelConditionFlagKey.format("CONDITION:%s", modelConditionFlagName.str());
	UnicodeString modelConditionFlagDisplayName = TheGameText->fetch(modelConditionFlagKey.str());
	modelConditionFlagDisplayName.toLower();
	result.concat(modelConditionFlagDisplayName);
	return result;
}

//-------------------------------------------------------------------------------------------------
// Format status flag display text
UnicodeString ObjectPrerequisite::formatStatusFlagDisplayText(const AsciiString& statusFlagName)
{
	UnicodeString result;
	AsciiString statusFlagKey;
	statusFlagKey.format("STATUS:%s", statusFlagName.str());
	UnicodeString statusFlagDisplayName = TheGameText->fetch(statusFlagKey.str());
	statusFlagDisplayName.toLower();
	result.concat(statusFlagDisplayName);
	return result;
}
