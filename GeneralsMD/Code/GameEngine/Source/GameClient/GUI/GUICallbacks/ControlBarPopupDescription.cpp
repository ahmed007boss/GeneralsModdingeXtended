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

// FILE: ControlBarPopupDescription.cpp /////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//
//                       Electronic Arts Pacific.
//
//                       Confidential Information
//                Copyright (C) 2002 - All Rights Reserved
//
//-----------------------------------------------------------------------------
//
//	created:	Sep 2002
//
//	Filename: 	ControlBarPopupDescription.cpp
//
//	author:		Chris Huybregts
//
//	purpose:
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// USER INCLUDES //////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// DEFINES ////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------


// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file in the GameEngine

#include "Common/GlobalData.h"
#include "Common/BuildAssistant.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/ProductionPrerequisite.h"
#include "Common/SpecialPower.h"
#include "Common/ThingTemplate.h"
#include "Common/Upgrade.h"
#include "GameClient/AnimateWindowManager.h"
#include "GameClient/DisconnectMenu.h"
#include "GameClient/GameWindow.h"
#include "GameClient/Gadget.h"
#include "GameClient/GadgetTextEntry.h"
#include "GameClient/GadgetPushButton.h"
#include "GameClient/GadgetStaticText.h"
#include "GameClient/GameClient.h"
#include "GameClient/GameText.h"
#include "GameClient/GUICallbacks.h"
#include "GameClient/InGameUI.h"
#include "GameClient/ControlBar.h"
#include "GameClient/DisplayStringManager.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/Module/OverchargeBehavior.h"
#include "GameLogic/Module/ProductionUpdate.h"
#include "GameLogic/Module/InventoryBehavior.h"
#include "GameLogic/Module/ActiveBody.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Components/Component.h"
#include "GameLogic/ScriptEngine.h"

#include "GameNetwork/NetworkInterface.h"

static WindowLayout* theLayout = NULL;
static GameWindow* theWindow = NULL;
static AnimateWindowManager* theAnimateWindowManager = NULL;
static GameWindow* prevWindow = NULL;
static Bool useAnimation = FALSE;
void ControlBarPopupDescriptionUpdateFunc(WindowLayout* layout, void* param)
{
	if (TheScriptEngine->isGameEnding())
		TheControlBar->hideBuildTooltipLayout();

	if (theAnimateWindowManager && !TheControlBar->getShowBuildTooltipLayout() && !theAnimateWindowManager->isReversed())
		theAnimateWindowManager->reverseAnimateWindow();
	else if (!TheControlBar->getShowBuildTooltipLayout() && (!TheGlobalData->m_animateWindows || !useAnimation))
		TheControlBar->deleteBuildTooltipLayout();


	if (useAnimation && theAnimateWindowManager && TheGlobalData->m_animateWindows)
	{
		Bool wasFinished = theAnimateWindowManager->isFinished();
		theAnimateWindowManager->update();
		if (theAnimateWindowManager->isFinished() && !wasFinished && theAnimateWindowManager->isReversed())
		{
			delete theAnimateWindowManager;
			theAnimateWindowManager = NULL;
			TheControlBar->deleteBuildTooltipLayout();
		}
	}

}

// ---------------------------------------------------------------------------------------
void ControlBar::showBuildTooltipLayout(GameWindow* cmdButton)
{
	if (TheInGameUI->areTooltipsDisabled() || TheScriptEngine->isGameEnding())
	{
		return;
	}

	Bool passedWaitTime = FALSE;
	static Bool isInitialized = FALSE;
	static UnsignedInt beginWaitTime;
	if (prevWindow == cmdButton)
	{
		m_showBuildToolTipLayout = TRUE;
		if (!isInitialized && beginWaitTime + cmdButton->getTooltipDelay() < timeGetTime())
		{
			//DEBUG_LOG(("%d beginwaittime, %d tooltipdelay, %dtimegettime", beginWaitTime, cmdButton->getTooltipDelay(), timeGetTime()));
			passedWaitTime = TRUE;
		}

		if (!passedWaitTime)
			return;
	}
	else if (!m_buildToolTipLayout->isHidden())
	{
		if (useAnimation && TheGlobalData->m_animateWindows && !theAnimateWindowManager->isReversed())
			theAnimateWindowManager->reverseAnimateWindow();
		else if (useAnimation && TheGlobalData->m_animateWindows && theAnimateWindowManager->isReversed())
		{
			return;
		}
		else
		{
			//			m_buildToolTipLayout->destroyWindows();
			//			deleteInstance(m_buildToolTipLayout);
			//			m_buildToolTipLayout = NULL;
			m_buildToolTipLayout->hide(TRUE);
			prevWindow = NULL;
		}
		return;
	}


	// will only get here the firsttime through the function through this window
	if (!passedWaitTime)
	{
		prevWindow = cmdButton;
		beginWaitTime = timeGetTime();
		isInitialized = FALSE;
		return;
	}
	isInitialized = TRUE;

	if (!cmdButton)
		return;
	if (BitIsSet(cmdButton->winGetStyle(), GWS_PUSH_BUTTON))
	{
		const CommandButton* commandButton = (const CommandButton*)GadgetButtonGetData(cmdButton);

		if (!commandButton)
			return;

		// note that, in this branch, ENABLE_SOLO_PLAY is ***NEVER*** defined...
		// this is so that we have a multiplayer build that cannot possibly be hacked
		// to work as a solo game!
		if (TheGameLogic->isInReplayGame())
			return;

		if (TheInGameUI->isQuitMenuVisible())
			return;

		if (TheDisconnectMenu && TheDisconnectMenu->isScreenVisible())
			return;

		//	if (m_buildToolTipLayout)
		//	{
		//		m_buildToolTipLayout->destroyWindows();
		//		deleteInstance(m_buildToolTipLayout);
		//
		//	}

		m_showBuildToolTipLayout = TRUE;
		//	m_buildToolTipLayout = TheWindowManager->winCreateLayout( "ControlBarPopupDescription.wnd" );
		//	m_buildToolTipLayout->setUpdate(ControlBarPopupDescriptionUpdateFunc);

		populateBuildTooltipLayout(commandButton);
	}
	else
	{
		// we're a generic window
		if (!BitIsSet(cmdButton->winGetStyle(), GWS_USER_WINDOW) && !BitIsSet(cmdButton->winGetStyle(), GWS_STATIC_TEXT))
			return;
		populateBuildTooltipLayout(NULL, cmdButton);
	}
	m_buildToolTipLayout->hide(FALSE);

	if (useAnimation && TheGlobalData->m_animateWindows)
	{
		theAnimateWindowManager = NEW AnimateWindowManager;
		theAnimateWindowManager->reset();
		theAnimateWindowManager->registerGameWindow(m_buildToolTipLayout->getFirstWindow(), WIN_ANIMATION_SLIDE_RIGHT_FAST, TRUE, 200);
	}


}


void ControlBar::repopulateBuildTooltipLayout(void)
{
	if (!prevWindow || !m_buildToolTipLayout)
		return;
	if (!BitIsSet(prevWindow->winGetStyle(), GWS_PUSH_BUTTON))
		return;
	const CommandButton* commandButton = (const CommandButton*)GadgetButtonGetData(prevWindow);
	populateBuildTooltipLayout(commandButton);
}

//-------------------------------------------------------------------------------------------------
/** Helper function to remove hotkey shortcuts like (&B) from button text */
//-------------------------------------------------------------------------------------------------
static UnicodeString removeHotkeyFromText(const UnicodeString& text)
{
	// TheSuperHackers @hotkey Ahmed Salah 27/06/2025 Remove hotkey shortcuts like (&B) from button text in tooltips for cleaner display
	// Convert to wide char string for processing
	const WideChar* str = text.str();
	Int len = text.getLength();
	
	// Create a new string without the hotkey patterns
	UnicodeString result;
	
	for (Int i = 0; i < len; i++)
	{
		// Check if we found the start of a hotkey pattern (&X)
		if (i + 3 < len && 
			str[i] == L'(' && str[i + 1] == L'&' && 
			str[i + 2] >= L'A' && str[i + 2] <= L'Z' && 
			str[i + 3] == L')')
		{
			// Skip the entire (&X) pattern
			i += 3; // Skip past the closing )
		}
		else
		{
			// Add this character to the result
			result.concat(str[i]);
		}
	}
	
	return result;
}

//-------------------------------------------------------------------------------------------------
/** Helper function to generate button alternatives text for tooltips */
//-------------------------------------------------------------------------------------------------
// TheSuperHackers @tooltip Ahmed Salah 27/06/2025 Generate tooltip text for alternative modifier-based command buttons with availability checking
static void appendAlternativesOrdered(const CommandButton* commandButton, const ControlBar* controlBar, Object* selectedObject, UnicodeString& alternativesText, Bool& hasAlternatives)
{
	// availability checker
	auto isButtonAvailable = [selectedObject, controlBar](const CommandButton* altButton) -> Bool {
		if (!altButton || !selectedObject || !controlBar) return false;
		CommandAvailability availability = controlBar->getCommandAvailability(altButton, selectedObject, theWindow);
		return (availability == COMMAND_AVAILABLE);
	};
	
	auto getButtonCostText = [selectedObject](const CommandButton* altButton) -> UnicodeString {
		if (!altButton || !selectedObject) return UnicodeString::TheEmptyString;
		Player* player = ThePlayerList->getLocalPlayer();
		if (!player) return UnicodeString::TheEmptyString;
		UnsignedInt buttonCost = altButton->getCostOfExecution(player, selectedObject);
		if (buttonCost > 0)
		{
			UnicodeString costText;
			costText.format(L" (%d$)", buttonCost);
			return costText;
		}
		return UnicodeString::TheEmptyString;
	};
	
	auto appendLine = [&](const char* key, const CommandButton* btn)
	{
		if (!btn || !isButtonAvailable(btn)) return;
		if (!hasAlternatives)
		{
			alternativesText = L"\n\n";
			hasAlternatives = true;
		}
		alternativesText.concat(TheGameText->fetch(key));
		alternativesText.concat(L" ");
		alternativesText.concat(removeHotkeyFromText(TheGameText->fetch(btn->getTextLabel().str())));
		alternativesText.concat(getButtonCostText(btn));
		alternativesText.concat(L"\n");
	};

	// Order required by user:
	// 1) RightClickTo first (base right-click)
	appendLine("ALTKEY:RightClickTo", commandButton->getRightClickButton());
	// 2) The rest of LEFT click alternatives
	//    Note: No LeftClickCtrlTo key exists, so skip it
	appendLine("ALTKEY:LeftClickAltTo", commandButton->getLeftClickAltButton());
	appendLine("ALTKEY:LeftClickShiftTo", commandButton->getLeftClickShiftButton());
	appendLine("ALTKEY:LeftClickCtrlAltTo", commandButton->getLeftClickCtrlAltButton());
	appendLine("ALTKEY:LeftClickCtrlShiftTo", commandButton->getLeftClickCtrlShiftButton());
	appendLine("ALTKEY:LeftClickAltShiftTo", commandButton->getLeftClickAltShiftButton());
	appendLine("ALTKEY:LeftClickCtrlAltShiftTo", commandButton->getLeftClickCtrlAltShiftButton());

	// 3) Then the rest of RIGHT click alternatives
	appendLine("ALTKEY:RightClickCtrlTo", commandButton->getRightClickCtrlButton());
	appendLine("ALTKEY:RightClickAltTo", commandButton->getRightClickAltButton());
	appendLine("ALTKEY:RightClickShiftTo", commandButton->getRightClickShiftButton());
	appendLine("ALTKEY:RightClickCtrlAltTo", commandButton->getRightClickCtrlAltButton());
	appendLine("ALTKEY:RightClickCtrlShiftTo", commandButton->getRightClickCtrlShiftButton());
	appendLine("ALTKEY:RightClickAltShiftTo", commandButton->getRightClickAltShiftButton());
	appendLine("ALTKEY:RightClickCtrlAltShiftTo", commandButton->getRightClickCtrlAltShiftButton());
}

static UnicodeString getButtonAlternativesText(const CommandButton* commandButton, const ControlBar* controlBar)
{
	UnicodeString alternativesText = UnicodeString::TheEmptyString;
	Bool hasAlternatives = false;
	
	// Get the current object for availability checking
	Drawable* draw = TheInGameUI->getFirstSelectedDrawable();
	Object* selectedObject = draw ? draw->getObject() : NULL;

	// Append alternatives in merged, specified order
	appendAlternativesOrdered(commandButton, controlBar, selectedObject, alternativesText, hasAlternatives);
	
	return alternativesText;
}

//-------------------------------------------------------------------------------------------------
void ControlBar::populateBuildTooltipLayout(const CommandButton* commandButton, GameWindow* tooltipWin)
{
	if (!m_buildToolTipLayout)
		return;

	Player* player = ThePlayerList->getLocalPlayer();
	UnicodeString name, cost, descrip;
	UnicodeString requiresFormat = UnicodeString::TheEmptyString, requiresList;
	UnicodeString conflictsFormat = UnicodeString::TheEmptyString, conflictsList;
	Bool firstRequirement = true;
	Bool firstConflicts = true;
	const PlayerPrerequisite* prereq;
	Bool fireScienceButton = false;
	UnsignedInt costToBuild = 0;

	if (commandButton)
	{
		const ThingTemplate* thingTemplate = commandButton->getThingTemplate();
		const UpgradeTemplate* upgradeTemplate = commandButton->getUpgradeTemplate();
		const SpecialPowerTemplate* specialPowerTemplate = commandButton->getSpecialPowerTemplate();

		



		ScienceType	st = SCIENCE_INVALID;
		if (commandButton->getCommandType() != GUI_COMMAND_PLAYER_UPGRADE &&
			commandButton->getCommandType() != GUI_COMMAND_OBJECT_UPGRADE)
		{
			if (commandButton->getScienceVec().size() > 1)
			{
				for (size_t j = 0; j < commandButton->getScienceVec().size(); ++j)
				{
					st = commandButton->getScienceVec()[j];

					if (commandButton->getCommandType() != GUI_COMMAND_PURCHASE_SCIENCE)
					{
						if (!player->hasScience(st) && j > 0)
						{
							//If we're not looking at a command button that purchases a science, then
							//it means we are looking at a command button that can USE the science. This
							//means we want to get the description for the previous science -- the one
							//we can use, not purchase!
							st = commandButton->getScienceVec()[j - 1];
						}

						//Now that we got the science for the button that executes the science, we need
						//to generate a simpler help text!
						fireScienceButton = TRUE;

						break;
					}
					else if (!player->hasScience(st))
					{
						//Purchase science case. The first science we run into that we don't have, that's the
						//one we'll want to show!
						break;
					}
				}
			}
			else if (commandButton->getScienceVec().size() == 1)
			{
				st = commandButton->getScienceVec()[0];
				if (commandButton->getCommandType() != GUI_COMMAND_PURCHASE_SCIENCE)
				{
					//Now that we got the science for the button that executes the science, we need
					//to generate a simpler help text!
					fireScienceButton = TRUE;
				}
			}
		}
		if (thingTemplate)
		{
			UnicodeString kindOfDesc = thingTemplate->getKindOfDescription();
			if (!kindOfDesc.isEmpty())
			{
				descrip = kindOfDesc + L"\n\n";
			}
		}
		if (commandButton->getDescriptionLabel().isNotEmpty())
		{

			descrip += TheGameText->fetch(commandButton->getDescriptionLabel());
		}
		else if (upgradeTemplate && upgradeTemplate->getDescriptionLabel().isNotEmpty())
		{
			// TheSuperHackers @feature Ahmed Salah - Use upgrade template description if command button has no description
			if (!descrip.isEmpty())
				descrip += L"\n\n";
			descrip += TheGameText->fetch(upgradeTemplate->getDescriptionLabel());
		}
		else if (thingTemplate)
		{
			// TheSuperHackers @feature Ahmed Salah - Description support: Use object description if command button and upgrade have no description (handles template fallback internally)
			Drawable* draw = TheInGameUI->getFirstSelectedDrawable();
			Object* selectedObject = draw ? draw->getObject() : NULL;
			if (selectedObject)
			{
				UnicodeString objectDesc = selectedObject->getDescription();
				if (!objectDesc.isEmpty())
				{
					if (!descrip.isEmpty())
						descrip += L"\n\n";
					descrip += objectDesc;
				}
			}
			if (selectedObject)
			{
				//Special case: Append status of overcharge on China power plant.
				if (commandButton->getCommandType() == GUI_COMMAND_TOGGLE_OVERCHARGE)
				{
					{
						OverchargeBehaviorInterface* obi;
						for (BehaviorModule** bmi = selectedObject->getBehaviorModules(); *bmi; ++bmi)
						{
							obi = (*bmi)->getOverchargeBehaviorInterface();
							if (obi)
							{
								descrip.concat(L"\n\n");
								if (obi->isOverchargeActive())
									descrip.concat(TheGameText->fetch("TOOLTIP:TooltipNukeReactorOverChargeIsOn"));
								else
									descrip.concat(TheGameText->fetch("TOOLTIP:TooltipNukeReactorOverChargeIsOff"));
							}
						}
					}
				}

				//Special case: When building units & buildings, the CanMakeType determines reasons for not being able to buy stuff.
				else if (thingTemplate)
				{
					CanMakeType makeType = TheBuildAssistant->canMakeUnit(selectedObject, commandButton->getThingTemplate());
					switch (makeType)
					{
					case CANMAKE_NO_MONEY:
						descrip.concat(L"\n\n");
						descrip.concat(TheGameText->fetch("TOOLTIP:TooltipNotEnoughMoneyToBuild"));
						break;
					case CANMAKE_QUEUE_FULL:
						descrip.concat(L"\n\n");
						descrip.concat(TheGameText->fetch("TOOLTIP:TooltipCannotPurchaseBecauseQueueFull"));
						break;
					case CANMAKE_PARKING_PLACES_FULL:
						descrip.concat(L"\n\n");
						descrip.concat(TheGameText->fetch("TOOLTIP:TooltipCannotBuildUnitBecauseParkingFull"));
						break;
					case CANMAKE_MAXED_OUT_FOR_PLAYER:
						descrip.concat(L"\n\n");
						if (thingTemplate->isKindOf(KINDOF_STRUCTURE))
						{
							descrip.concat(TheGameText->fetch("TOOLTIP:TooltipCannotBuildBuildingBecauseMaximumNumber"));
						}
						else
						{
							descrip.concat(TheGameText->fetch("TOOLTIP:TooltipCannotBuildUnitBecauseMaximumNumber"));
						}
						break;
						//case CANMAKE_NO_PREREQ:
						//	descrip.concat( L"\n\n" );
						//	descrip.concat( TheGameText->fetch( "TOOLTIP:TooltipCannotBuildDueToPrerequisites" ) );
						//	break;
					}
				}

				//Special case: When building upgrades
				else if (upgradeTemplate && !player->hasUpgradeInProduction(upgradeTemplate))
				{
					if (commandButton->getCommandType() == GUI_COMMAND_PLAYER_UPGRADE ||
						commandButton->getCommandType() == GUI_COMMAND_OBJECT_UPGRADE)
					{
						ProductionUpdateInterface* pui = selectedObject->getProductionUpdateInterface();
						if (pui && pui->getProductionCount() == MAX_BUILD_QUEUE_BUTTONS)
						{
							descrip.concat(L"\n\n");
							descrip.concat(TheGameText->fetch("TOOLTIP:TooltipCannotPurchaseBecauseQueueFull"));
						}
						else if (!TheUpgradeCenter->canAffordUpgrade(ThePlayerList->getLocalPlayer(), upgradeTemplate, FALSE))
						{
							descrip.concat(L"\n\n");
							descrip.concat(TheGameText->fetch("TOOLTIP:TooltipNotEnoughMoneyToBuild"));
						}
					}
				}

			}

		}


		// TheSuperHackers @feature Ahmed Salah 15/01/2025 Merged EnablePrerequisites and EnableCallerPrerequisites to ProductionPrerequisite
		// ask each prerequisite to give us a list of the non satisfied prerequisites
		Drawable* draw = TheInGameUI->getFirstSelectedDrawable();
		Object* selectedObject = draw ? draw->getObject() : NULL;
		for (Int i = 0; i < commandButton->getEnablePrereqCount(); i++)
		{
			const ProductionPrerequisite* prodPrereq = commandButton->getNthEnablePrereq(i);
			if (!prodPrereq->isSatisfied(player, selectedObject))
			{
				requiresList = prodPrereq->getRequiresList(player, selectedObject);
				conflictsList = prodPrereq->getConflictList(player, selectedObject);
				if (requiresList != UnicodeString::TheEmptyString)
				{
					// make sure to put in 'returns' to space things correctly
					if (firstRequirement)
						firstRequirement = false;
					else
						requiresFormat.concat(L", ");
				}
				requiresFormat.concat(requiresList);

				if (conflictsList != UnicodeString::TheEmptyString)
				{
					// make sure to put in 'returns' to space things correctly
					if (firstConflicts)
						firstConflicts = false;
					else
						conflictsFormat.concat(L", ");
				}
				conflictsFormat.concat(conflictsList);
			}
		}

	

		name = TheGameText->fetch(commandButton->getTextLabel().str());
		
		// TheSuperHackers @feature author 15/01/2025 Apply hotkey override to tooltip if present
		const AsciiString& hotkeyOverride = commandButton->getHotkeyOverride();
		if (!hotkeyOverride.isEmpty())
		{
			// Apply the hotkey override to the tooltip text
			AsciiString nameAscii;
			nameAscii.translate(name);
			AsciiString modifiedText = TheControlBar->updateHotkeyInLabel(nameAscii, hotkeyOverride);
			
			// Convert back to UnicodeString for display
			name.clear();
			name.translate(modifiedText);
		}

		// Add KindOf description if available
		// TheSuperHackers @tooltip author 15/01/2025 Add KindOf description to tooltip display
		if (thingTemplate)
		{
			UnicodeString kindOfDesc = thingTemplate->getKindOfDescription();
			if (!kindOfDesc.isEmpty())
			{			
				descrip += kindOfDesc;
			}
		}

		if (thingTemplate && commandButton->getCommandType() != GUI_COMMAND_PURCHASE_SCIENCE)
		{
			//We are either looking at building a unit or a structure that may or may not have any
			//prerequisites.

			//Format the cost only when we have to pay for it.
			costToBuild = thingTemplate->calcCostToBuild(player);
			if (costToBuild > 0)
			{
				cost.format(TheGameText->fetch("TOOLTIP:Cost"), costToBuild);
			}

			// ask each prerequisite to give us a list of the non satisfied prerequisites
			for (Int i = 0; i < thingTemplate->getPrereqCount(); i++)
			{
				prereq = thingTemplate->getNthPrereq(i);
				requiresList = prereq->getRequiresList(player);
				conflictsList = prereq->getConflictList(player);
				if (requiresList != UnicodeString::TheEmptyString)
				{
					// make sure to put in 'returns' to space things correctly
					if (firstRequirement)
						firstRequirement = false;
					else
						requiresFormat.concat(L", ");
				}
				requiresFormat.concat(requiresList);

				if (conflictsList != UnicodeString::TheEmptyString)
				{
					// make sure to put in 'returns' to space things correctly
					if (firstConflicts)
						firstConflicts = false;
					else
						conflictsFormat.concat(L", ");
				}
				conflictsFormat.concat(conflictsList);
			}
			
		}
		else if (upgradeTemplate)
		{
			//We are looking at an upgrade purchase icon. Maybe we already purchased it?

			Bool hasUpgradeAlready = player->hasUpgradeComplete(upgradeTemplate);
			Bool hasConflictingUpgrade = FALSE;
			Bool missingScience = FALSE;
			Bool playerUpgradeButton = commandButton->getCommandType() == GUI_COMMAND_PLAYER_UPGRADE;
			Bool objectUpgradeButton = commandButton->getCommandType() == GUI_COMMAND_OBJECT_UPGRADE;

			if (!hasUpgradeAlready)
			{
				//Check if the first selected object has the specified upgrade.
				Drawable* draw = TheInGameUI->getFirstSelectedDrawable();
				if (draw)
				{
					Object* object = draw->getObject();
					if (object)
					{
						hasUpgradeAlready = object->hasUpgrade(upgradeTemplate);
						if (objectUpgradeButton)
						{
							hasConflictingUpgrade = !object->affectedByUpgrade(upgradeTemplate);
						}
					}
				}
			}
			if (hasConflictingUpgrade && !hasUpgradeAlready)
			{
				if (commandButton->getConflictingLabel().isNotEmpty())
				{
					descrip = TheGameText->fetch(commandButton->getConflictingLabel());
				}
				else
				{
					descrip = TheGameText->fetch("TOOLTIP:HasConflictingUpgradeDefault");
				}
			}
			else if (hasUpgradeAlready && (playerUpgradeButton || objectUpgradeButton))
			{
				//See if we can fetch the "already upgraded" text for this upgrade. If not.... use the default "fill me in".
				if (commandButton->getPurchasedLabel().isNotEmpty())
				{
					descrip = TheGameText->fetch(commandButton->getPurchasedLabel());
				}
				else
				{
					descrip = TheGameText->fetch("TOOLTIP:AlreadyUpgradedDefault");
				}
			}
			else if (!hasUpgradeAlready)
			{

				//Do we have a prerequisite science?
				for (size_t i = 0; i < commandButton->getScienceVec().size(); i++)
				{
					ScienceType st = commandButton->getScienceVec()[i];
					if (!player->hasScience(st))
					{
						missingScience = TRUE;
						break;
					}
				}

				//Determine the cost of the upgrade.
				costToBuild = upgradeTemplate->calcCostToBuild(player);
				if (costToBuild > 0)
				{
					cost.format(TheGameText->fetch("TOOLTIP:Cost"), costToBuild);
				}

				if (missingScience)
				{
					if (!descrip.isEmpty())
						descrip.concat(L"\n");
					requiresFormat.format(TheGameText->fetch("CONTROLBAR:Requirements").str(), TheGameText->fetch("CONTROLBAR:GeneralsPromotion").str());
					descrip.concat(requiresFormat);
				}
			}
		}
		else if (st != SCIENCE_INVALID && !fireScienceButton)
		{
			TheScienceStore->getNameAndDescription(st, name, descrip);

			costToBuild = TheScienceStore->getSciencePurchaseCost(st);
			if (costToBuild > 0)
			{
				cost.format(TheGameText->fetch("TOOLTIP:ScienceCost"), costToBuild);
			}

			// ask each prerequisite to give us a list of the non satisfied prerequisites
			if (thingTemplate)
			{
				for (Int i = 0; i < thingTemplate->getPrereqCount(); i++)
				{
					prereq = thingTemplate->getNthPrereq(i);
					requiresList = prereq->getRequiresList(player);

					if (requiresList != UnicodeString::TheEmptyString)
					{
						// make sure to put in 'returns' to space things correctly
						if (firstRequirement)
							firstRequirement = false;
						else
							requiresFormat.concat(L", ");
					}
					requiresFormat.concat(requiresList);
				}
				if (!requiresFormat.isEmpty())
				{
					UnicodeString requireFormat = TheGameText->fetch("CONTROLBAR:Requirements");
					requiresFormat.format(requireFormat.str(), requiresFormat.str());
					if (!descrip.isEmpty())
						descrip.concat(L"\n");
					descrip.concat(requiresFormat);
				}
			}

		}
		if (specialPowerTemplate)
		{
			//We are looking at a special power button
			
			//Get the cost to use the special power
			costToBuild = specialPowerTemplate->getUsingCost();
			if (costToBuild > 0)
			{
				cost.format(TheGameText->fetch("TOOLTIP:Cost"), costToBuild);
			}

			if (!specialPowerTemplate->canAffordUsingPower(player, selectedObject))
			{
				descrip.concat(L"\n\n");
				descrip.concat(TheGameText->fetch("TOOLTIP:TooltipNotEnoughMoneyToBuild"));
			}
			
		}

		// TheSuperHackers @feature author 15/01/2025 Handle inventory replenishment cost using centralized method
		if (commandButton->getCommandType() == GUI_COMMAND_REPLENISH_INVENTORY_ITEM)
		{
			// Get the current object for inventory calculation
			Drawable* draw = TheInGameUI->getFirstSelectedDrawable();
			Object* selectedObject = draw ? draw->getObject() : NULL;
			
			if (selectedObject)
			{
				// Use centralized cost calculation method
				costToBuild = commandButton->getCostOfExecution(player, selectedObject);
				if (costToBuild > 0)
				{
					cost.format(TheGameText->fetch("TOOLTIP:Cost"), costToBuild);
				}

				if (costToBuild > 0 && player->getMoney()->countMoney() < costToBuild)
				{
					descrip.concat(L"\n\n");
					descrip.concat(TheGameText->fetch("TOOLTIP:TooltipNotEnoughMoneyToBuild"));
				}
			}
		}

		// TheSuperHackers @feature author 15/01/2025 Handle component replacement cost using centralized method
		if (commandButton->getCommandType() == GUI_COMMAND_REPLACE_COMPONENT)
		{
			// Get the current object for component calculation
			Drawable* draw = TheInGameUI->getFirstSelectedDrawable();
			Object* selectedObject = draw ? draw->getObject() : NULL;
			
			if (selectedObject)
			{
				// Use centralized cost calculation method
				costToBuild = commandButton->getCostOfExecution(player, selectedObject);
				if (costToBuild > 0)
				{
					cost.format(TheGameText->fetch("TOOLTIP:Cost"), costToBuild);
				}

				if (costToBuild > 0 && player->getMoney()->countMoney() < costToBuild)
				{
					descrip.concat(L"\n\n");
					descrip.concat(TheGameText->fetch("TOOLTIP:TooltipNotEnoughMoneyToBuild"));
				}
			}
		}

		// Add module descriptions from template
		// TheSuperHackers @tooltip author 01/01/2025 Append module descriptions to tooltip text
		if (thingTemplate)
		{
			UnicodeString modulesDesc = thingTemplate->getExtendedDescription();
			if (!modulesDesc.isEmpty())
			{
				if (!descrip.isEmpty())
					descrip += L"\n\n";
				descrip += modulesDesc;
			}
		}

		// Add command button description label
		if (commandButton->getDescriptionLabel().isNotEmpty())
		{
			if (!descrip.isEmpty())
				descrip += L"\n\n";
			descrip += TheGameText->fetch(commandButton->getDescriptionLabel());
		}
		else if (thingTemplate)
		{
			// TheSuperHackers @feature Ahmed Salah - Description support: Use object description if command button has no description (handles template fallback internally)
			Drawable* draw = TheInGameUI->getFirstSelectedDrawable();
			Object* selectedObject = draw ? draw->getObject() : NULL;
			if (selectedObject)
			{
				UnicodeString objectDesc = selectedObject->getDescription();
				if (!objectDesc.isEmpty())
				{
					if (!descrip.isEmpty())
						descrip += L"\n\n";
					descrip += objectDesc;
				}
			}
		}

		// Add button alternatives for right-click and modifier key combinations
		// TheSuperHackers @tooltip Ahmed Salah 27/06/2025 Append alternative command button descriptions to tooltip text
		UnicodeString alternativesText = getButtonAlternativesText(commandButton, this);
		if (!alternativesText.isEmpty())
		{
			descrip.concat(alternativesText);
		}

		if (!requiresFormat.isEmpty())
		{
			UnicodeString requireFormat = TheGameText->fetch("CONTROLBAR:Requirements");
			requiresFormat.format(requireFormat.str(), requiresFormat.str());
			if (!descrip.isEmpty())
				descrip.concat(L"\n\n");
			descrip.concat(requiresFormat);

		}

		if (!conflictsFormat.isEmpty())
		{
			UnicodeString conflictFormat = TheGameText->fetch("CONTROLBAR:Conflicts");
			conflictsFormat.format(conflictFormat.str(), conflictsFormat.str());
			if (!descrip.isEmpty()) {
				if (!requiresFormat.isEmpty())
				{
					descrip.concat(L"\n");
				}
				else
				{
					descrip.concat(L"\n\n");
				}
			}
				
			descrip.concat(conflictsFormat);
		}
	}
	else if (tooltipWin)
	{

		if (tooltipWin == TheWindowManager->winGetWindowFromId(m_buildToolTipLayout->getFirstWindow(), TheNameKeyGenerator->nameToKey("ControlBar.wnd:MoneyDisplay")))
		{
			name = TheGameText->fetch("CONTROLBAR:Money");
			descrip = TheGameText->fetch("CONTROLBAR:MoneyDescription");
		}
		else if (tooltipWin == TheWindowManager->winGetWindowFromId(m_buildToolTipLayout->getFirstWindow(), TheNameKeyGenerator->nameToKey("ControlBar.wnd:PowerWindow")))
		{
			name = TheGameText->fetch("CONTROLBAR:Power");
			descrip = TheGameText->fetch("CONTROLBAR:PowerDescription");

			Player* playerToDisplay = getCurrentlyViewedPlayer();

			if (playerToDisplay && playerToDisplay->getEnergy())
			{
				Energy* energy = playerToDisplay->getEnergy();
				descrip.format(descrip, energy->getProduction(), energy->getConsumption());
			}
			else
			{
				descrip.format(descrip, 0, 0);
			}
		}
		else if (tooltipWin == TheWindowManager->winGetWindowFromId(m_buildToolTipLayout->getFirstWindow(), TheNameKeyGenerator->nameToKey("ControlBar.wnd:GeneralsExp")))
		{
			name = TheGameText->fetch("CONTROLBAR:GeneralsExp");
			descrip = TheGameText->fetch("CONTROLBAR:GeneralsExpDescription");
		}
		else
		{
			DEBUG_ASSERTCRASH(FALSE, ("ControlBar::populateBuildTooltipLayout We attempted to call the popup tooltip on a game window that has yet to be hand coded in as this fuction was/is designed for only buttons but has been hacked to work with GameWindows."));
			return;
		}

	}
	GameWindow* win = TheWindowManager->winGetWindowFromId(m_buildToolTipLayout->getFirstWindow(), TheNameKeyGenerator->nameToKey("ControlBarPopupDescription.wnd:StaticTextName"));
	if (win)
	{
		GadgetStaticTextSetText(win, name);
	}

	win = TheWindowManager->winGetWindowFromId(m_buildToolTipLayout->getFirstWindow(), TheNameKeyGenerator->nameToKey("ControlBarPopupDescription.wnd:StaticTextCost"));
	if (win)
	{
		if (costToBuild > 0)
		{
			win->winHide(FALSE);
			GadgetStaticTextSetText(win, cost);
		}
		else
		{
			win->winHide(TRUE);
		}
	}


	win = TheWindowManager->winGetWindowFromId(m_buildToolTipLayout->getFirstWindow(), TheNameKeyGenerator->nameToKey("ControlBarPopupDescription.wnd:StaticTextDescription"));
	if (win)
	{

		static NameKeyType winNamekey = TheNameKeyGenerator->nameToKey(AsciiString("ControlBar.wnd:BackgroundMarker"));
		static ICoord2D lastOffset = { 0, 0 };

		ICoord2D size, newSize, pos;
		Int diffSize;

		DisplayString* tempDString = TheDisplayStringManager->newDisplayString();
		win->winGetSize(&size.x, &size.y);
		tempDString->setFont(win->winGetFont());
		tempDString->setWordWrap(size.x - 10);
		tempDString->setText(descrip);
		tempDString->getSize(&newSize.x, &newSize.y);
		TheDisplayStringManager->freeDisplayString(tempDString);
		tempDString = NULL;
		diffSize = newSize.y - size.y;
		GameWindow* parent = m_buildToolTipLayout->getFirstWindow();
		if (!parent)
			return;

		parent->winGetSize(&size.x, &size.y);
		if (size.y + diffSize < 102) {
			diffSize = 102 - size.y;
		}

		parent->winSetSize(size.x, size.y + diffSize);
		parent->winGetPosition(&pos.x, &pos.y);
		//		if(size.y + diffSize < 102)
		//		{
		//
		//			parent->winSetPosition(pos.x, pos.y -  (102 - (newSize.y + size.y + diffSize) ));
		//		}
		//		else

		//		heightChange = controlBarPos.y - m_defaultControlBarPosition.y;

		GameWindow* marker = TheWindowManager->winGetWindowFromId(NULL, winNamekey);
		static ICoord2D basePos;
		if (!marker)
		{
			return;
		}
		getBackgroundMarkerPos(&basePos.x, &basePos.y);
		ICoord2D curPos, offset;
		marker->winGetScreenPosition(&curPos.x, &curPos.y);

		offset.x = curPos.x - basePos.x;
		offset.y = curPos.y - basePos.y;

		parent->winSetPosition(pos.x, (pos.y - diffSize) + (offset.y - lastOffset.y));

		lastOffset.x = offset.x;
		lastOffset.y = offset.y;

		win->winGetSize(&size.x, &size.y);
		win->winSetSize(size.x, size.y + diffSize);

		GadgetStaticTextSetText(win, descrip);
	}
	m_buildToolTipLayout->hide(FALSE);

}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
void ControlBar::hideBuildTooltipLayout()
{
	if (theAnimateWindowManager && theAnimateWindowManager->isReversed())
		return;
	if (useAnimation && theAnimateWindowManager && TheGlobalData->m_animateWindows)
		theAnimateWindowManager->reverseAnimateWindow();
	else
		deleteBuildTooltipLayout();

}

void ControlBar::deleteBuildTooltipLayout(void)
{
	m_showBuildToolTipLayout = FALSE;
	prevWindow = NULL;
	m_buildToolTipLayout->hide(TRUE);
//	if(!m_buildToolTipLayout)
//		return;
//
//	m_buildToolTipLayout->destroyWindows();
//	deleteInstance(m_buildToolTipLayout);
//	m_buildToolTipLayout = NULL;

	delete theAnimateWindowManager;
	theAnimateWindowManager = NULL;

}

// ---------------------------------------------------------------------------------------
// TheSuperHackers @feature Ahmed Salah 01/01/2026 Unit tooltip support
// ---------------------------------------------------------------------------------------
static WindowLayout* theUnitTooltipLayout = NULL;
static AnimateWindowManager* theUnitTooltipAnimateWindowManager = NULL;
static GameWindow* prevUnitTooltipWindow = NULL;
static Bool useUnitTooltipAnimation = FALSE;

// ---------------------------------------------------------------------------------------
// TheSuperHackers @feature Ahmed Salah - Camo tooltip support
// ---------------------------------------------------------------------------------------
static WindowLayout* theUnitCamoTooltipLayout = NULL;
static AnimateWindowManager* theUnitCamoTooltipAnimateWindowManager = NULL;
static GameWindow* prevUnitCamoTooltipWindow = NULL;
static Bool useUnitCamoTooltipAnimation = FALSE;

void ControlBarUnitTooltipUpdateFunc(WindowLayout* layout, void* param)
{
	if (TheScriptEngine->isGameEnding())
		TheControlBar->hideUnitTooltipLayout();

	if (theUnitTooltipAnimateWindowManager && !TheControlBar->getShowUnitTooltipLayout() && !theUnitTooltipAnimateWindowManager->isReversed())
		theUnitTooltipAnimateWindowManager->reverseAnimateWindow();
	else if (!TheControlBar->getShowUnitTooltipLayout() && (!TheGlobalData->m_animateWindows || !useUnitTooltipAnimation))
		TheControlBar->deleteUnitTooltipLayout();

	if (useUnitTooltipAnimation && theUnitTooltipAnimateWindowManager && TheGlobalData->m_animateWindows)
	{
		Bool wasFinished = theUnitTooltipAnimateWindowManager->isFinished();
		theUnitTooltipAnimateWindowManager->update();
		if (theUnitTooltipAnimateWindowManager->isFinished() && !wasFinished && theUnitTooltipAnimateWindowManager->isReversed())
		{
			delete theUnitTooltipAnimateWindowManager;
			theUnitTooltipAnimateWindowManager = NULL;
			TheControlBar->deleteUnitTooltipLayout();
		}
	}
}

// ---------------------------------------------------------------------------------------
void ControlBar::showUnitTooltipLayout(GameWindow* portraitWindow)
{
	if (TheInGameUI->areTooltipsDisabled() || TheScriptEngine->isGameEnding())
	{
		return;
	}

	// Get the selected object
	Drawable* draw = TheInGameUI->getFirstSelectedDrawable();
	Object* obj = draw ? draw->getObject() : NULL;
	
	if (!obj)
	{
		hideUnitTooltipLayout();
		return;
	}

	Bool passedWaitTime = FALSE;
	static Bool isInitialized = FALSE;
	static UnsignedInt beginWaitTime;
	if (prevUnitTooltipWindow == portraitWindow)
	{
		m_showUnitToolTipLayout = TRUE;
		if (!isInitialized && beginWaitTime + 500 < timeGetTime()) // 500ms delay
		{
			passedWaitTime = TRUE;
		}

		if (!passedWaitTime)
			return;
	}
	else if (m_unitToolTipLayout && !m_unitToolTipLayout->isHidden())
	{
		if (useUnitTooltipAnimation && TheGlobalData->m_animateWindows && !theUnitTooltipAnimateWindowManager->isReversed())
			theUnitTooltipAnimateWindowManager->reverseAnimateWindow();
		else if (useUnitTooltipAnimation && TheGlobalData->m_animateWindows && theUnitTooltipAnimateWindowManager->isReversed())
		{
			return;
		}
		else
		{
			m_unitToolTipLayout->hide(TRUE);
			prevUnitTooltipWindow = NULL;
		}
		return;
	}

	// will only get here the first time through the function through this window
	if (!passedWaitTime)
	{
		prevUnitTooltipWindow = portraitWindow;
		beginWaitTime = timeGetTime();
		isInitialized = FALSE;
		return;
	}
	isInitialized = TRUE;

	if (TheInGameUI->isQuitMenuVisible())
		return;

	if (TheDisconnectMenu && TheDisconnectMenu->isScreenVisible())
		return;

	if (!m_unitToolTipLayout)
		return;

	m_showUnitToolTipLayout = TRUE;
	populateUnitTooltipLayout();
	m_unitToolTipLayout->hide(FALSE);

	if (useUnitTooltipAnimation && TheGlobalData->m_animateWindows)
	{
		theUnitTooltipAnimateWindowManager = NEW AnimateWindowManager;
		theUnitTooltipAnimateWindowManager->reset();
		theUnitTooltipAnimateWindowManager->registerGameWindow(m_unitToolTipLayout->getFirstWindow(), WIN_ANIMATION_SLIDE_RIGHT_FAST, TRUE, 200);
	}
}

// ---------------------------------------------------------------------------------------
void ControlBar::hideUnitTooltipLayout()
{
	if (theUnitTooltipAnimateWindowManager && theUnitTooltipAnimateWindowManager->isReversed())
		return;
	if (useUnitTooltipAnimation && theUnitTooltipAnimateWindowManager && TheGlobalData->m_animateWindows)
		theUnitTooltipAnimateWindowManager->reverseAnimateWindow();
	else
		deleteUnitTooltipLayout();
}

// ---------------------------------------------------------------------------------------
void ControlBar::deleteUnitTooltipLayout(void)
{
	m_showUnitToolTipLayout = FALSE;
	prevUnitTooltipWindow = NULL;
	if (m_unitToolTipLayout)
		m_unitToolTipLayout->hide(TRUE);

	delete theUnitTooltipAnimateWindowManager;
	theUnitTooltipAnimateWindowManager = NULL;
}

// ---------------------------------------------------------------------------------------
void ControlBar::populateUnitTooltipLayout(void)
{
	if (!m_unitToolTipLayout)
		return;

	// Get the selected object
	Drawable* draw = TheInGameUI->getFirstSelectedDrawable();
	Object* obj = draw ? draw->getObject() : NULL;
	
	if (!obj)
		return;

	const ThingTemplate* thingTemplate = obj->getTemplate();
	if (!thingTemplate)
		return;

	// Check if multiple units are selected
	const DrawableList* selectedDrawables = TheInGameUI->getAllSelectedDrawables();
	Int selectedCount = selectedDrawables ? (Int)selectedDrawables->size() : 1;

	UnicodeString name, descrip;
	
	// Check if all selected units have the same display name (for multiple selection)
	Bool allSameType = TRUE;
	UnicodeString firstDisplayName;
	if (selectedCount > 1 && selectedDrawables)
	{
		// Get the first unit's display name for comparison
		DrawableList::const_iterator it = selectedDrawables->begin();
		if (it != selectedDrawables->end())
		{
			const Drawable* firstDraw = *it;
			if (firstDraw)
			{
				const Object* firstObj = firstDraw->getObject();
				if (firstObj)
				{
					firstDisplayName = firstObj->getDisplayNameOverride();
					if (firstDisplayName.isEmpty() && firstDraw->getTemplate())
					{
						firstDisplayName = firstDraw->getTemplate()->getDisplayName();
					}
				}
				else if (firstDraw->getTemplate())
				{
					firstDisplayName = firstDraw->getTemplate()->getDisplayName();
				}
			}
		}
		
		// Compare all other units' display names with the first one
		for (it = selectedDrawables->begin(); it != selectedDrawables->end(); ++it)
		{
			const Drawable* d = *it;
			if (!d)
				continue;
				
			UnicodeString currentDisplayName;
			const Object* currentObj = d->getObject();
			if (currentObj)
			{
				currentDisplayName = currentObj->getDisplayNameOverride();
				if (currentDisplayName.isEmpty() && d->getTemplate())
				{
					currentDisplayName = d->getTemplate()->getDisplayName();
				}
			}
			else if (d->getTemplate())
			{
				currentDisplayName = d->getTemplate()->getDisplayName();
			}
			
			if (currentDisplayName != firstDisplayName)
			{
				allSameType = FALSE;
				break;
			}
		}
	}
	
	// Handle single vs multiple selection
	if (selectedCount > 1)
	{
		// Multiple units selected
		
		if (allSameType)
		{
			// All same type - use pluralized display name
			UnicodeString pluralName = obj->getDisplayPluralNameOverride();
			if (pluralName.isEmpty())
			{
				pluralName = thingTemplate->getDisplayPluralName();
			}
			if (!pluralName.isEmpty() && wcsstr(pluralName.str(), L"MISSING:") == NULL)
			{
				name.format(L"%d %ls", selectedCount, pluralName.str());
			}
			else
			{
				name.format(L"%d Units", selectedCount);
			}
		}
		else
		{
			// Different display names - show "Unit Group" and list each display name with count
			name = L"Unit Group";
			
			// Group units by display name and count them
			struct UnitDisplayNameInfo
			{
				UnicodeString displayName;
				Int count;
				const Object* sampleObj; // For getting plural name
				const ThingTemplate* sampleTemplate; // For getting plural name
			};
			
			// Simple list to store unique display names
			UnitDisplayNameInfo nameList[64]; // Max 64 different display names
			Int nameCount = 0;
			
			if (selectedDrawables)
			{
				for (DrawableList::const_iterator it = selectedDrawables->begin(); it != selectedDrawables->end(); ++it)
				{
					const Drawable* d = *it;
					if (!d)
						continue;
					
					// Get display name for this unit
					UnicodeString currentDisplayName;
					const Object* currentObj = d->getObject();
					if (currentObj)
					{
						currentDisplayName = currentObj->getDisplayNameOverride();
						if (currentDisplayName.isEmpty() && d->getTemplate())
						{
							currentDisplayName = d->getTemplate()->getDisplayName();
						}
					}
					else if (d->getTemplate())
					{
						currentDisplayName = d->getTemplate()->getDisplayName();
					}
					
					if (currentDisplayName.isEmpty() || wcsstr(currentDisplayName.str(), L"MISSING:") != NULL)
						continue;
					
					// Find if this display name already exists in our list
					Int foundIndex = -1;
					for (Int i = 0; i < nameCount; ++i)
					{
						if (nameList[i].displayName == currentDisplayName)
						{
							foundIndex = i;
							break;
						}
					}
					
					if (foundIndex >= 0)
					{
						// Increment count
						nameList[foundIndex].count++;
					}
					else if (nameCount < 64)
					{
						// Add new display name
						nameList[nameCount].displayName = currentDisplayName;
						nameList[nameCount].count = 1;
						nameList[nameCount].sampleObj = currentObj;
						nameList[nameCount].sampleTemplate = d->getTemplate();
						nameCount++;
					}
				}
			}
			
			// Build the list description
			for (Int i = 0; i < nameCount; ++i)
			{
				UnicodeString displayName = nameList[i].displayName;
				Int unitCount = nameList[i].count;
				const Object* sampleObj = nameList[i].sampleObj;
				const ThingTemplate* sampleTemplate = nameList[i].sampleTemplate;
				
				UnicodeString unitName;
				if (unitCount > 1)
				{
					// Use plural name
					if (sampleObj)
					{
						unitName = sampleObj->getDisplayPluralNameOverride();
					}
					if (unitName.isEmpty() && sampleTemplate)
					{
						unitName = sampleTemplate->getDisplayPluralName();
					}
					// Fallback to singular if plural not available
					if (unitName.isEmpty() || wcsstr(unitName.str(), L"MISSING:") != NULL)
					{
						unitName = displayName; // Use the display name we already have
					}
				}
				else
				{
					// Use singular name (the display name we already have)
					unitName = displayName;
				}
				
				if (!unitName.isEmpty() && wcsstr(unitName.str(), L"MISSING:") == NULL)
				{
					if (!descrip.isEmpty())
						descrip += L"\n";
					UnicodeString line;
					line.format(L" - %d %ls", unitCount, unitName.str());
					descrip += line;
				}
			}
		}
	}
	else
	{
		// Single unit selected - show name, HP and rank
		UnicodeString unitName = obj->getDisplayNameOverride();
		if (unitName.isEmpty())
		{
			unitName = thingTemplate->getDisplayName();
		}
		name = unitName;

		// Build health and rank information first (at the start of description)
		UnicodeString healthAndRankText;
		
		// Add health information
		BodyModuleInterface* bodyInterface = obj->getBodyModule();
		if (bodyInterface)
		{
			Real health = bodyInterface->getHealth();
			Real maxHealth = bodyInterface->getMaxHealth();
			if (maxHealth > 0.0f)
			{
				Int healthPercent = (Int)((health / maxHealth) * 100.0f);
				UnicodeString healthText;
				healthText.format(L"%s: %d/%d (%d%%)", 
					TheGameText->fetch("TOOLTIP:Health").str(),
					(Int)health, (Int)maxHealth, healthPercent);
				healthAndRankText = healthText;
			}
		}

		// Add veterancy level if applicable
		VeterancyLevel vetLevel = obj->getVeterancyLevel();
		if (vetLevel != LEVEL_REGULAR)
		{
			UnicodeString vetText;
			switch (vetLevel)
			{
			case LEVEL_VETERAN:
				vetText = TheGameText->fetch("TOOLTIP:Veteran");
				break;
			case LEVEL_ELITE:
				vetText = TheGameText->fetch("TOOLTIP:Elite");
				break;
			case LEVEL_HEROIC:
				vetText = TheGameText->fetch("TOOLTIP:Heroic");
				break;
			default:
				break;
			}
			if (!vetText.isEmpty())
			{
				if (!healthAndRankText.isEmpty())
					healthAndRankText += L"\n";
				healthAndRankText += vetText;
			}
		}

		// Add health and rank at the start of description
		if (!healthAndRankText.isEmpty())
		{
			descrip = healthAndRankText;
		}
	}

	// Get unit description
	// For single unit: show all descriptions including HP/rank (already added above)
	// For multiple same type: show descriptions but skip HP/rank
	// For multiple different types: descriptions already built as unit list above
	if (selectedCount == 1)
	{
		// Single unit - add descriptions after HP/rank
		UnicodeString kindOfDesc = thingTemplate->getKindOfDescription();
		if (!kindOfDesc.isEmpty())
		{
			if (!descrip.isEmpty())
				descrip += L"\n\n";
			descrip += kindOfDesc;
		}
		// TheSuperHackers @feature Ahmed Salah - Description support: Use object description (handles override internally)
		UnicodeString unitDesc = obj->getDescription();
		if (!unitDesc.isEmpty())
		{
			if (!descrip.isEmpty())
				descrip += L"\n\n";
			descrip += unitDesc;
		}
		// Get extended description from template (skip body modules since HP is already shown)
		UnicodeString extendedDesc = thingTemplate->getExtendedDescription(TRUE);
		if (!extendedDesc.isEmpty())
		{
			if (!descrip.isEmpty())
				descrip += L"\n";
			descrip += extendedDesc;
		}
	}
	else if (selectedCount > 1)
	{
		// Multiple units selected - use stored allSameType result
		if (allSameType)
		{
			// All same type - show descriptions (HP/rank already skipped)
			UnicodeString kindOfDesc = thingTemplate->getKindOfDescription();
			if (!kindOfDesc.isEmpty())
			{
				if (!descrip.isEmpty())
					descrip += L"\n\n";
				descrip += kindOfDesc;
			}
			// TheSuperHackers @feature Ahmed Salah - Description support: Use object description (handles override internally)
			UnicodeString unitDesc = obj->getDescription();
			if (!unitDesc.isEmpty())
			{
				if (!descrip.isEmpty())
					descrip += L"\n\n";
				descrip += unitDesc;
			}
			UnicodeString extendedDesc = thingTemplate->getExtendedDescription();
			if (!extendedDesc.isEmpty())
			{
				if (!descrip.isEmpty())
					descrip += L"\n";
				descrip += extendedDesc;
			}
		}
		// else: different types - descriptions already built as unit list above
	}

	// Set the tooltip text
	GameWindow* win = TheWindowManager->winGetWindowFromId(m_unitToolTipLayout->getFirstWindow(), TheNameKeyGenerator->nameToKey("ControlBarPopupDescription.wnd:StaticTextName"));
	if (win)
	{
		GadgetStaticTextSetText(win, name);
	}

	win = TheWindowManager->winGetWindowFromId(m_unitToolTipLayout->getFirstWindow(), TheNameKeyGenerator->nameToKey("ControlBarPopupDescription.wnd:StaticTextCost"));
	if (win)
	{
		win->winHide(TRUE); // Hide cost for unit tooltip
	}

	win = TheWindowManager->winGetWindowFromId(m_unitToolTipLayout->getFirstWindow(), TheNameKeyGenerator->nameToKey("ControlBarPopupDescription.wnd:StaticTextDescription"));
	if (win)
	{
		static NameKeyType winNamekey = TheNameKeyGenerator->nameToKey(AsciiString("ControlBar.wnd:BackgroundMarker"));
		static ICoord2D lastOffset = { 0, 0 };

		ICoord2D size, newSize, pos;
		Int diffSize;

		DisplayString* tempDString = TheDisplayStringManager->newDisplayString();
		win->winGetSize(&size.x, &size.y);
		tempDString->setFont(win->winGetFont());
		tempDString->setWordWrap(size.x - 10);
		tempDString->setText(descrip);
		tempDString->getSize(&newSize.x, &newSize.y);
		TheDisplayStringManager->freeDisplayString(tempDString);
		tempDString = NULL;
		diffSize = newSize.y - size.y;
		GameWindow* parent = m_unitToolTipLayout->getFirstWindow();
		if (!parent)
			return;

		parent->winGetSize(&size.x, &size.y);
		if (size.y + diffSize < 102) {
			diffSize = 102 - size.y;
		}

		parent->winSetSize(size.x, size.y + diffSize);
		parent->winGetPosition(&pos.x, &pos.y);

		GameWindow* marker = TheWindowManager->winGetWindowFromId(NULL, winNamekey);
		static ICoord2D basePos;
		if (!marker)
		{
			return;
		}
		getBackgroundMarkerPos(&basePos.x, &basePos.y);
		ICoord2D curPos, offset;
		marker->winGetScreenPosition(&curPos.x, &curPos.y);

		offset.x = curPos.x - basePos.x;
		offset.y = curPos.y - basePos.y;

		parent->winSetPosition(pos.x, (pos.y - diffSize) + (offset.y - lastOffset.y));

		lastOffset.x = offset.x;
		lastOffset.y = offset.y;

		win->winGetSize(&size.x, &size.y);
		win->winSetSize(size.x, size.y + diffSize);

		GadgetStaticTextSetText(win, descrip);
	}
	m_unitToolTipLayout->hide(FALSE);
}

// ---------------------------------------------------------------------------------------
// TheSuperHackers @feature Ahmed Salah - Camo tooltip update function
// ---------------------------------------------------------------------------------------
void ControlBarUnitCamoTooltipUpdateFunc(WindowLayout* layout, void* param)
{
	if (TheScriptEngine->isGameEnding())
		TheControlBar->hideUnitCamoTooltipLayout();

	if (theUnitCamoTooltipAnimateWindowManager && !TheControlBar->getShowUnitCamoTooltipLayout() && !theUnitCamoTooltipAnimateWindowManager->isReversed())
		theUnitCamoTooltipAnimateWindowManager->reverseAnimateWindow();
	else if (!TheControlBar->getShowUnitCamoTooltipLayout() && (!TheGlobalData->m_animateWindows || !useUnitCamoTooltipAnimation))
		TheControlBar->deleteUnitCamoTooltipLayout();

	if (useUnitCamoTooltipAnimation && theUnitCamoTooltipAnimateWindowManager && TheGlobalData->m_animateWindows)
	{
		Bool wasFinished = theUnitCamoTooltipAnimateWindowManager->isFinished();
		theUnitCamoTooltipAnimateWindowManager->update();
		if (theUnitCamoTooltipAnimateWindowManager->isFinished() && !wasFinished && theUnitCamoTooltipAnimateWindowManager->isReversed())
		{
			delete theUnitCamoTooltipAnimateWindowManager;
			theUnitCamoTooltipAnimateWindowManager = NULL;
			TheControlBar->deleteUnitCamoTooltipLayout();
		}
	}
}

// ---------------------------------------------------------------------------------------
void ControlBar::showUnitCamoTooltipLayout(GameWindow* camoWindow)
{
	if (TheInGameUI->areTooltipsDisabled() || TheScriptEngine->isGameEnding())
	{
		return;
	}

	// Get the selected object
	Drawable* draw = TheInGameUI->getFirstSelectedDrawable();
	Object* obj = draw ? draw->getObject() : NULL;
	
	if (!obj)
	{
		hideUnitCamoTooltipLayout();
		return;
	}

	Bool passedWaitTime = FALSE;
	static Bool isInitialized = FALSE;
	static UnsignedInt beginWaitTime;
	if (prevUnitCamoTooltipWindow == camoWindow)
	{
		m_showUnitCamoToolTipLayout = TRUE;
		if (!isInitialized && beginWaitTime + 500 < timeGetTime()) // 500ms delay
		{
			passedWaitTime = TRUE;
		}

		if (!passedWaitTime)
			return;
	}
	else if (m_unitCamoToolTipLayout && !m_unitCamoToolTipLayout->isHidden())
	{
		if (useUnitCamoTooltipAnimation && TheGlobalData->m_animateWindows && !theUnitCamoTooltipAnimateWindowManager->isReversed())
			theUnitCamoTooltipAnimateWindowManager->reverseAnimateWindow();
		else if (useUnitCamoTooltipAnimation && TheGlobalData->m_animateWindows && theUnitCamoTooltipAnimateWindowManager->isReversed())
		{
			return;
		}
		else
		{
			m_unitCamoToolTipLayout->hide(TRUE);
			prevUnitCamoTooltipWindow = NULL;
		}
		return;
	}

	// will only get here the first time through the function through this window
	if (!passedWaitTime)
	{
		prevUnitCamoTooltipWindow = camoWindow;
		beginWaitTime = timeGetTime();
		isInitialized = FALSE;
		return;
	}
	isInitialized = TRUE;

	if (TheInGameUI->isQuitMenuVisible())
		return;

	if (TheDisconnectMenu && TheDisconnectMenu->isScreenVisible())
		return;

	if (!m_unitCamoToolTipLayout)
		return;

	// Find which upgrade cameo was hovered by comparing the window pointer
	Int upgradeCameoIndex = -1;
	for (Int i = 0; i < MAX_RIGHT_HUD_UPGRADE_CAMEOS; ++i)
	{
		if (TheControlBar->m_rightHUDUpgradeCameos[i] == camoWindow)
		{
			upgradeCameoIndex = i;
			break;
		}
	}

	// Get the upgrade template from the selected object
	const UpgradeTemplate* upgradeTemplate = NULL;
	if (upgradeCameoIndex >= 0)
	{
		const ThingTemplate* thingTemplate = obj->getTemplate();
		if (thingTemplate)
		{
			AsciiString upgradeName = thingTemplate->getUpgradeCameoName(upgradeCameoIndex);
			if (!upgradeName.isEmpty())
			{
				upgradeTemplate = TheUpgradeCenter->findUpgrade(upgradeName);
			}
		}
	}

	m_showUnitCamoToolTipLayout = TRUE;
	populateUnitCamoTooltipLayout(upgradeTemplate);
	m_unitCamoToolTipLayout->hide(FALSE);

	if (useUnitCamoTooltipAnimation && TheGlobalData->m_animateWindows)
	{
		theUnitCamoTooltipAnimateWindowManager = NEW AnimateWindowManager;
		theUnitCamoTooltipAnimateWindowManager->reset();
		theUnitCamoTooltipAnimateWindowManager->registerGameWindow(m_unitCamoToolTipLayout->getFirstWindow(), WIN_ANIMATION_SLIDE_RIGHT_FAST, TRUE, 200);
	}
}

// ---------------------------------------------------------------------------------------
void ControlBar::hideUnitCamoTooltipLayout()
{
	if (theUnitCamoTooltipAnimateWindowManager && theUnitCamoTooltipAnimateWindowManager->isReversed())
		return;
	if (useUnitCamoTooltipAnimation && theUnitCamoTooltipAnimateWindowManager && TheGlobalData->m_animateWindows)
		theUnitCamoTooltipAnimateWindowManager->reverseAnimateWindow();
	else
		deleteUnitCamoTooltipLayout();
}

// ---------------------------------------------------------------------------------------
void ControlBar::deleteUnitCamoTooltipLayout(void)
{
	m_showUnitCamoToolTipLayout = FALSE;
	prevUnitCamoTooltipWindow = NULL;
	if (m_unitCamoToolTipLayout)
		m_unitCamoToolTipLayout->hide(TRUE);

	delete theUnitCamoTooltipAnimateWindowManager;
	theUnitCamoTooltipAnimateWindowManager = NULL;
}

// ---------------------------------------------------------------------------------------
void ControlBar::populateUnitCamoTooltipLayout(const UpgradeTemplate* upgradeTemplate)
{
	if (!m_unitCamoToolTipLayout)
		return;

	// Get the selected object
	Drawable* draw = TheInGameUI->getFirstSelectedDrawable();
	Object* obj = draw ? draw->getObject() : NULL;
	
	if (!obj || !upgradeTemplate)
		return;

	UnicodeString name, descrip;
	
	// Get upgrade display name from label
	const AsciiString& displayNameLabel = upgradeTemplate->getDisplayNameLabel();
	if (!displayNameLabel.isEmpty())
	{
		name = TheGameText->fetch(displayNameLabel);
	}
	if (name.isEmpty() || wcsstr(name.str(), L"MISSING:") != NULL)
	{
		// Fallback to upgrade name if display name is missing
		const AsciiString& upgradeName = upgradeTemplate->getUpgradeName();
		if (!upgradeName.isEmpty())
		{
			// Convert AsciiString to UnicodeString
			name.format(L"%hs", upgradeName.str());
		}
	}
	
	// Check if upgrade is active (owned by unit or player)
	Player* player = ThePlayerList->getLocalPlayer();
	Bool isUpgradeActive = FALSE;
	if (obj && upgradeTemplate)
	{
		// Check if object has the upgrade (object-level upgrade)
		if (obj->hasUpgrade(upgradeTemplate))
		{
			isUpgradeActive = TRUE;
		}
		// Check if player has the upgrade (player-level upgrade)
		else if (player && player->hasUpgradeComplete(upgradeTemplate))
		{
			isUpgradeActive = TRUE;
		}
	}
	
	// Append "(Active)" to name if upgrade is active
	if (isUpgradeActive && !name.isEmpty())
	{
		name.concat(L" (Active)");
	}
	
	// Get upgrade description from label - use active description if upgrade is active, otherwise use regular description
	const AsciiString& descriptionLabel = upgradeTemplate->getDescriptionLabel();
	if (isUpgradeActive)
	{
		const AsciiString& activeDescriptionLabel = upgradeTemplate->getActiveDescriptionLabel();
		if (!activeDescriptionLabel.isEmpty())
		{
			descrip = TheGameText->fetch(activeDescriptionLabel);
		}
		else if (!descriptionLabel.isEmpty())
		{
			// Fallback to regular description if active description is empty
			descrip = TheGameText->fetch(descriptionLabel);
		}
	}
	else if (!descriptionLabel.isEmpty())
	{
		// Use regular description when upgrade is not active
		descrip = TheGameText->fetch(descriptionLabel);
	}
	
	// Set the tooltip text
	GameWindow* win = TheWindowManager->winGetWindowFromId(m_unitCamoToolTipLayout->getFirstWindow(), TheNameKeyGenerator->nameToKey("ControlBarPopupDescription.wnd:StaticTextName"));
	if (win)
	{
		GadgetStaticTextSetText(win, name);
	}

	win = TheWindowManager->winGetWindowFromId(m_unitCamoToolTipLayout->getFirstWindow(), TheNameKeyGenerator->nameToKey("ControlBarPopupDescription.wnd:StaticTextCost"));
	if (win)
	{
		win->winHide(TRUE); // Hide cost for camo tooltip
	}

	win = TheWindowManager->winGetWindowFromId(m_unitCamoToolTipLayout->getFirstWindow(), TheNameKeyGenerator->nameToKey("ControlBarPopupDescription.wnd:StaticTextDescription"));
	if (win)
	{
		static NameKeyType winNamekey = TheNameKeyGenerator->nameToKey(AsciiString("ControlBar.wnd:BackgroundMarker"));
		static ICoord2D lastOffset = { 0, 0 };

		ICoord2D size, newSize, pos;
		Int diffSize;

		DisplayString* tempDString = TheDisplayStringManager->newDisplayString();
		win->winGetSize(&size.x, &size.y);
		tempDString->setFont(win->winGetFont());
		tempDString->setWordWrap(size.x - 10);
		tempDString->setText(descrip);
		tempDString->getSize(&newSize.x, &newSize.y);
		TheDisplayStringManager->freeDisplayString(tempDString);
		tempDString = NULL;
		diffSize = newSize.y - size.y;
		GameWindow* parent = m_unitCamoToolTipLayout->getFirstWindow();
		if (!parent)
			return;

		parent->winGetSize(&size.x, &size.y);
		if (size.y + diffSize < 102) {
			diffSize = 102 - size.y;
		}

		parent->winSetSize(size.x, size.y + diffSize);
		parent->winGetPosition(&pos.x, &pos.y);

		GameWindow* marker = TheWindowManager->winGetWindowFromId(NULL, winNamekey);
		static ICoord2D basePos;
		if (!marker)
		{
			return;
		}
		getBackgroundMarkerPos(&basePos.x, &basePos.y);
		ICoord2D curPos, offset;
		marker->winGetScreenPosition(&curPos.x, &curPos.y);

		offset.x = curPos.x - basePos.x;
		offset.y = curPos.y - basePos.y;

		parent->winSetPosition(pos.x, (pos.y - diffSize) + (offset.y - lastOffset.y));

		lastOffset.x = offset.x;
		lastOffset.y = offset.y;

		win->winGetSize(&size.x, &size.y);
		win->winSetSize(size.x, size.y + diffSize);

		GadgetStaticTextSetText(win, descrip);
	}
	m_unitCamoToolTipLayout->hide(FALSE);
}
