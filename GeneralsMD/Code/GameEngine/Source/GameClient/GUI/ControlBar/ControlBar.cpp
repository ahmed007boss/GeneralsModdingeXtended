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

// FILE: ControlBar.cpp ///////////////////////////////////////////////////////////////////////////
// Author: Colin Day, March 2002
// Desc:   Context sensitive command interface
///////////////////////////////////////////////////////////////////////////////////////////////////

// USER INCLUDES //////////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"	// This must go first in EVERY cpp file in the GameEngine
#define DEFINE_GUI_COMMMAND_NAMES
#define DEFINE_COMMAND_OPTION_NAMES
#define DEFINE_WEAPONSLOTTYPE_NAMES
#define DEFINE_RADIUSCURSOR_NAMES

#include "Common/ActionManager.h"
#include "Common/GameType.h"
#include "Common/MultiplayerSettings.h"
#include "Common/NameKeyGenerator.h"
#include "Common/Override.h"
#include "Common/PlayerTemplate.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/ProductionPrerequisite.h"
#include "Common/SpecialPower.h"
#include "Common/ThingTemplate.h"
#include "Common/ThingFactory.h"
#include "Common/Upgrade.h"
#include "Common/Recorder.h"
#include "Common/ProductionPrerequisite.h"

#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/Module/ProductionUpdate.h"
#include "GameLogic/Module/OCLUpdate.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/SpecialPowerModule.h"
#include "GameLogic/Module/StealthUpdate.h"
#include "GameLogic/Module/RebuildHoleBehavior.h"
#include "GameLogic/Module/InventoryBehavior.h"
#include "GameLogic/Module/ActiveBody.h"
#include "GameLogic/Components/Component.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/Weapon.h"

#include "GameClient/AnimateWindowManager.h"
#include "GameClient/ControlBar.h"
#include "GameClient/ControlBarScheme.h"
#include "GameClient/Drawable.h"
#include "GameClient/Display.h"
#include "GameClient/DisplayStringManager.h"
#include "GameClient/GameClient.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GameText.h"
#include "GameClient/GadgetPushButton.h"
#include "GameClient/GadgetProgressBar.h"
#include "GameClient/GadgetStaticText.h"
#include "GameClient/GadgetTextEntry.h"
#include "GameClient/InGameUI.h"
#include "GameClient/WindowVideoManager.h"
#include "GameClient/ControlBarResizer.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/HotKey.h"
#include "GameClient/GameWindowTransitions.h"
#include "GameClient/GUICallbacks.h"

#include "GameNetwork/GameInfo.h"


// PUBLIC /////////////////////////////////////////////////////////////////////////////////////////
ControlBar *TheControlBar = NULL;

const Image* ControlBar::m_rankVeteranIcon	= NULL;
const Image* ControlBar::m_rankEliteIcon		= NULL;
const Image* ControlBar::m_rankHeroicIcon		= NULL;

///////////////////////////////////////////////////////////////////////////////////////////////////
// CommandButton //////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
const FieldParse CommandButton::s_commandButtonFieldParseTable[] =
{

	{ "Command",							CommandButton::parseCommand, NULL, offsetof( CommandButton, m_command ) },
	{ "Options",							INI::parseBitString32,		   TheCommandOptionNames, offsetof( CommandButton, m_options ) },
	{ "Object",								INI::parseThingTemplate,		 NULL, offsetof( CommandButton, m_thingTemplate ) },
	{ "Upgrade",							INI::parseUpgradeTemplate,	 NULL, offsetof( CommandButton, m_upgradeTemplate ) },
	{ "WeaponSlot",						INI::parseLookupList,				 TheWeaponSlotTypeNamesLookupList, offsetof( CommandButton, m_weaponSlot ) },
	{ "MaxShotsToFire",				INI::parseInt,							 NULL, offsetof( CommandButton, m_maxShotsToFire ) },
	{ "Science",							INI::parseScienceVector,					 NULL, offsetof( CommandButton, m_science ) },
	{ "SpecialPower",					INI::parseSpecialPowerTemplate,			 NULL, offsetof( CommandButton, m_specialPower ) },
	{ "TextLabel",						INI::parseAsciiString,			 NULL, offsetof( CommandButton, m_textLabel ) },
	{ "DescriptLabel",				INI::parseAsciiString,			 NULL, offsetof( CommandButton, m_descriptionLabel ) },
	{ "PurchasedLabel",				INI::parseAsciiString,			 NULL, offsetof( CommandButton, m_purchasedLabel ) },
	{ "ConflictingLabel",			INI::parseAsciiString,			 NULL, offsetof( CommandButton, m_conflictingLabel ) },
	{ "ButtonImage",					INI::parseAsciiString,			 NULL, offsetof( CommandButton, m_buttonImageName ) },
	{ "OverlayImage",					INI::parseAsciiString,			 NULL, offsetof( CommandButton, m_overlayImageName ) },
	{ "OverlayImage2",					INI::parseAsciiString,			 NULL, offsetof( CommandButton, m_overlayImage2Name ) },
	{ "ItemToReplenish",				INI::parseAsciiString,			 NULL, offsetof( CommandButton, m_itemToReplenish ) },
	{ "ComponentName",					INI::parseAsciiString,			 NULL, offsetof( CommandButton, m_componentName ) },
	{ "Amount",							INI::parseInt,							 NULL, offsetof( CommandButton, m_amount ) },
	{ "EnableMassProduction",			INI::parseBool,							 NULL, offsetof( CommandButton, m_enableMassProduction ) },
	{ "CursorName",						INI::parseAsciiString,			 NULL, offsetof( CommandButton, m_cursorName ) },
	{ "InvalidCursorName",		INI::parseAsciiString,       NULL, offsetof( CommandButton, m_invalidCursorName ) },
	{ "ButtonBorderType",			INI::parseLookupList,				 CommandButtonMappedBorderTypeNames, offsetof( CommandButton, m_commandButtonBorder ) },
	{ "RadiusCursorType",			INI::parseIndexList,				 TheRadiusCursorNames, offsetof( CommandButton, m_radiusCursor ) },
	{ "UnitSpecificSound",		INI::parseAudioEventRTS,		 NULL, offsetof( CommandButton, m_unitSpecificSound ) },
	{ "RequireElectronics",		INI::parseBool,							 NULL, offsetof( CommandButton, m_isRequireElectronics) },
	{ "TargetKindOf",				CommandButton::parseTargetKindOf,	NULL, 0 },
	{ "EnablePrerequisites",				CommandButton::parseEnablePrerequisites,	0, 0 },
	{ "VisiblePrerequisites",				CommandButton::parseVisiblePrerequisites,	0, 0 },
	{ "EnableCallerPrerequisites",				CommandButton::parseEnableCallerUnitPrerequisites,	0, 0 },
	{ "VisibleCallerPrerequisites",				CommandButton::parseVisibleCallerUnitPrerequisites,	0, 0 },

	// Modifier key and click type button name strings
	{ "ClickCtrlButton",					INI::parseAsciiString, NULL, offsetof( CommandButton, m_leftClickCtrlButtonName ) },
	{ "ClickAltButton",						INI::parseAsciiString, NULL, offsetof( CommandButton, m_leftClickAltButtonName ) },
	{ "ClickShiftButton",					INI::parseAsciiString, NULL, offsetof( CommandButton, m_leftClickShiftButtonName ) },
	{ "ClickCtrlAltButton",				INI::parseAsciiString, NULL, offsetof( CommandButton, m_leftClickCtrlAltButtonName ) },
	{ "ClickCtrlShiftButton",			INI::parseAsciiString, NULL, offsetof( CommandButton, m_leftClickCtrlShiftButtonName ) },
	{ "ClickAltShiftButton",			INI::parseAsciiString, NULL, offsetof( CommandButton, m_leftClickAltShiftButtonName ) },
	{ "ClickCtrlAltShiftButton",	INI::parseAsciiString, NULL, offsetof( CommandButton, m_leftClickCtrlAltShiftButtonName ) },

	{ "RightClickButton",							INI::parseAsciiString, NULL, offsetof( CommandButton, m_rightClickButtonName ) },
	{ "RightClickCtrlButton",					INI::parseAsciiString, NULL, offsetof( CommandButton, m_rightClickCtrlButtonName ) },
	{ "RightClickAltButton",					INI::parseAsciiString, NULL, offsetof( CommandButton, m_rightClickAltButtonName ) },
	{ "RightClickShiftButton",				INI::parseAsciiString, NULL, offsetof( CommandButton, m_rightClickShiftButtonName ) },
	{ "RightClickCtrlAltButton",			INI::parseAsciiString, NULL, offsetof( CommandButton, m_rightClickCtrlAltButtonName ) },
	{ "RightClickCtrlShiftButton",		INI::parseAsciiString, NULL, offsetof( CommandButton, m_rightClickCtrlShiftButtonName ) },
	{ "RightClickAltShiftButton",			INI::parseAsciiString, NULL, offsetof( CommandButton, m_rightClickAltShiftButtonName ) },
	{ "RightClickCtrlAltShiftButton",	INI::parseAsciiString, NULL, offsetof( CommandButton, m_rightClickCtrlAltShiftButtonName ) },

	// Alternative command buttons (completely replace original button when prerequisites are satisfied)
	{ "AlternativeButton1",				INI::parseAsciiString, NULL, offsetof( CommandButton, m_alternativeButton1Name ) },
	{ "AlternativeButton2",				INI::parseAsciiString, NULL, offsetof( CommandButton, m_alternativeButton2Name ) },
	{ "AlternativeButton3",				INI::parseAsciiString, NULL, offsetof( CommandButton, m_alternativeButton3Name ) },
	{ "AlternativeButton4",				INI::parseAsciiString, NULL, offsetof( CommandButton, m_alternativeButton4Name ) },
	{ "AlternativeButton1Prerequisites",	CommandButton::parseAlternativeButton1Prerequisites,	0, 0 },
	{ "AlternativeButton2Prerequisites",	CommandButton::parseAlternativeButton2Prerequisites,	0, 0 },
	{ "AlternativeButton3Prerequisites",	CommandButton::parseAlternativeButton3Prerequisites,	0, 0 },
	{ "AlternativeButton4Prerequisites",	CommandButton::parseAlternativeButton4Prerequisites,	0, 0 },
	{ "AlternativeButton1ObjectPrerequisites",	CommandButton::parseAlternativeButton1ObjectPrerequisites,	0, 0 },
	{ "AlternativeButton2ObjectPrerequisites",	CommandButton::parseAlternativeButton2ObjectPrerequisites,	0, 0 },
	{ "AlternativeButton3ObjectPrerequisites",	CommandButton::parseAlternativeButton3ObjectPrerequisites,	0, 0 },
	{ "AlternativeButton4ObjectPrerequisites",	CommandButton::parseAlternativeButton4ObjectPrerequisites,	0, 0 },

	{ NULL,						NULL,												 NULL, 0 }  // keep this last

};

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @alternative Ahmed Salah 27/06/2025 Helper function to get alternative button by index
//-------------------------------------------------------------------------------------------------
const CommandButton* CommandButton::getAlternativeButtonByIndex(Int index) const
{
	switch(index)
	{
		case 0:  return getAlternativeButton1();
		case 1:  return getAlternativeButton2();
		case 2:  return getAlternativeButton3();
		case 3:  return getAlternativeButton4();
		case 4:  return getRightClickCtrlAltShiftButton();
		case 5:  return getRightClickCtrlAltButton();
		case 6:  return getRightClickCtrlShiftButton();
		case 7:  return getRightClickCtrlButton();
		case 8:  return getRightClickAltShiftButton();
		case 9:  return getRightClickAltButton();
		case 10: return getRightClickShiftButton();
		case 11: return getRightClickButton();
		case 12: return getLeftClickCtrlAltShiftButton();
		case 13: return getLeftClickCtrlAltButton();
		case 14: return getLeftClickCtrlShiftButton();
		case 15: return getLeftClickCtrlButton();
		case 16: return getLeftClickAltShiftButton();
		case 17: return getLeftClickAltButton();
		case 18: return getLeftClickShiftButton();
		default: return NULL;
	}
}
static void commandButtonTooltip(GameWindow *window,
													WinInstanceData *instData,
													UnsignedInt mouse)
{
	TheControlBar->showBuildTooltipLayout(window);
}

/// mark the UI as dirty so the context of everything is re-evaluated
void ControlBar::markUIDirty( void )
{
  m_UIDirty = TRUE;

#if defined(RTS_DEBUG)
	UnsignedInt now = TheGameLogic->getFrame();
	if( now == m_lastFrameMarkedDirty )
	{
		//Do nothing.
	}
	else if( now == m_lastFrameMarkedDirty + 1 )
	{
		m_consecutiveDirtyFrames++;
	}
	else
	{
		m_consecutiveDirtyFrames = 1;
	}
	m_lastFrameMarkedDirty = now;

	if( m_consecutiveDirtyFrames > 20 )
	{
		DEBUG_CRASH( ("Serious flaw in interface system! Either new code or INI has caused the interface to be marked dirty every frame. This problem actually causes the interface to completely lockup not allowing you to click normal game buttons.") );
	}

#endif
}

Player* ControlBar::getCurrentlyViewedPlayer()
{
	if (isObserverControlBarOn())
		return getObserverLookAtPlayer();

	return ThePlayerList->getLocalPlayer();
}

Relationship ControlBar::getCurrentlyViewedPlayerRelationship(const Team* team)
{
	if (Player* player = getCurrentlyViewedPlayer())
		return player->getRelationship(team);

	return NEUTRAL;
}

void ControlBar::populatePurchaseScience( Player* player )
{
//	TheInGameUI->deselectAllDrawables();

	const CommandSet *commandSet1;
	const CommandSet *commandSet3;
	const CommandSet *commandSet8;
	Int i;
	if(TheScriptEngine->isGameEnding())
		return;
	// get command set
	if(!player ||!player->getPlayerTemplate() || player->getPlayerTemplate()->getPurchaseScienceCommandSetRank1().isEmpty() ||
			player->getPlayerTemplate()->getPurchaseScienceCommandSetRank3().isEmpty() ||
			player->getPlayerTemplate()->getPurchaseScienceCommandSetRank8().isEmpty())
		return;
	commandSet1 = findCommandSet(player->getPlayerTemplate()->getPurchaseScienceCommandSetRank1()); // TEMP WILL CHANGE TO PROPER WAY ONCE WORKING
	commandSet3 = findCommandSet(player->getPlayerTemplate()->getPurchaseScienceCommandSetRank3()); // TEMP WILL CHANGE TO PROPER WAY ONCE WORKING
	commandSet8 = findCommandSet(player->getPlayerTemplate()->getPurchaseScienceCommandSetRank8()); // TEMP WILL CHANGE TO PROPER WAY ONCE WORKING

	for( i = 0; i < MAX_PURCHASE_SCIENCE_RANK_1; i++ )
		if (m_sciencePurchaseWindowsRank1[i]!=nullptr)
			m_sciencePurchaseWindowsRank1[i]->winHide(TRUE);
	for( i = 0; i < MAX_PURCHASE_SCIENCE_RANK_3; i++ )
		if (m_sciencePurchaseWindowsRank3[i] != nullptr)
			m_sciencePurchaseWindowsRank3[i]->winHide(TRUE);
	for( i = 0; i < MAX_PURCHASE_SCIENCE_RANK_8; i++ )
		if (m_sciencePurchaseWindowsRank8[i] != nullptr)
			m_sciencePurchaseWindowsRank8[i]->winHide(TRUE);


	// if no command set match is found hide all the buttons
	if( commandSet1 == NULL ||
			commandSet3 == NULL ||
			commandSet8 == NULL )
		return;

	// populate the button with commands defined
	const CommandButton *commandButton;
	for( i = 0; i < MAX_PURCHASE_SCIENCE_RANK_1; i++ )
	{

		// get command button
		commandButton = commandSet1->getCommandButton(i);

		// if button is not present, just hide the window
		if( commandButton == NULL || BitIsSet( commandButton->getOptions(), SCRIPT_ONLY ) )
		{
			// hide window on interface
			if(m_sciencePurchaseWindowsRank1[ i ] != nullptr) 
				m_sciencePurchaseWindowsRank1[ i ]->winHide( TRUE );
		}
		else
		{
			// make sure the window is not hidden
			m_sciencePurchaseWindowsRank1[ i ]->winHide( FALSE );

			// Disable by default
			m_sciencePurchaseWindowsRank1[ i ]->winEnable( FALSE );

			// populate the visible button with data from the command button

			setControlCommand( m_sciencePurchaseWindowsRank1[ i ], commandButton, NULL, -1 );
			if (!commandButton->getScienceVec().empty())
			{
				ScienceType	st = commandButton->getScienceVec()[ 0 ];

				if( player->isScienceDisabled( st ) )
				{
					//A script has deemed this science disabled.
					m_sciencePurchaseWindowsRank1[ i ]->winEnable( FALSE );
				}
				else if( player->isScienceHidden( st ) )
				{
					//A script has deemed this science unavailable, thus hidden
					m_sciencePurchaseWindowsRank1[ i ]->winHide( TRUE );
				}
				else
				{
					//Handle normal game logic cases!
					if(!player->hasScience(st) && TheScienceStore->playerHasPrereqsForScience(player, st) && TheScienceStore->getSciencePurchaseCost(st) <= player->getSciencePurchasePoints())
					{
						m_sciencePurchaseWindowsRank1[ i ]->winEnable( TRUE );
					}
					if(player->hasScience(st))
					{
						m_sciencePurchaseWindowsRank1[ i ]->winSetStatus(WIN_STATUS_ALWAYS_COLOR);
					}
					else
					{
						m_sciencePurchaseWindowsRank1[ i ]->winClearStatus(WIN_STATUS_ALWAYS_COLOR);
					}
					if(!TheScienceStore->playerHasRootPrereqsForScience(player, st))
						m_sciencePurchaseWindowsRank1[ i ]->winHide(TRUE);
				}
			}
		}

	}

	for( i = 0; i < MAX_PURCHASE_SCIENCE_RANK_3; i++ )
	{

		// get command button
		commandButton = commandSet3->getCommandButton(i);

		// if button is not present, just hide the window
		if( commandButton == NULL || BitIsSet( commandButton->getOptions(), SCRIPT_ONLY ) )
		{
			// hide window on interface
			if (m_sciencePurchaseWindowsRank3[ i ] != nullptr)
				m_sciencePurchaseWindowsRank3[ i ]->winHide( TRUE );
		} 
		else
		{
			// make sure the window is not hidden
			m_sciencePurchaseWindowsRank3[ i ]->winHide( FALSE );

			// Disable by default
			m_sciencePurchaseWindowsRank3[ i ]->winEnable( FALSE );

			// populate the visible button with data from the command button

			setControlCommand( m_sciencePurchaseWindowsRank3[ i ], commandButton, NULL, -1 );
			ScienceType	st = SCIENCE_INVALID;
			ScienceVec sv = commandButton->getScienceVec();
			if (! sv.empty())
			{
				st = sv[ 0 ];
			}

			if( player->isScienceDisabled( st ) )
			{
				//A script has deemed this science disabled.
				m_sciencePurchaseWindowsRank3[ i ]->winEnable( FALSE );
			}
			else if( player->isScienceHidden( st ) )
			{
				//A script has deemed this science unavailable, thus hidden
				m_sciencePurchaseWindowsRank3[ i ]->winHide( TRUE );
			}
			else
			{
				//Handle normal game logic cases!
				if(!player->hasScience(st) && TheScienceStore->playerHasPrereqsForScience(player, st) && TheScienceStore->getSciencePurchaseCost(st) <= player->getSciencePurchasePoints())
				{
					m_sciencePurchaseWindowsRank3[ i ]->winEnable( TRUE );
				}
				if(player->hasScience(st))
				{
					m_sciencePurchaseWindowsRank3[ i ]->winSetStatus(WIN_STATUS_ALWAYS_COLOR);
				}
				else
				{
					m_sciencePurchaseWindowsRank3[ i ]->winClearStatus(WIN_STATUS_ALWAYS_COLOR);
				}
				if(!TheScienceStore->playerHasRootPrereqsForScience(player, st))
					m_sciencePurchaseWindowsRank3[ i ]->winHide(TRUE);
			}

		}

	}

	for( i = 0; i < MAX_PURCHASE_SCIENCE_RANK_8; i++ )
	{

		// get command button
		commandButton = commandSet8->getCommandButton(i);

		// if button is not present, just hide the window
		if( commandButton == NULL || BitIsSet( commandButton->getOptions(), SCRIPT_ONLY ) )
		{
			// hide window on interface
			if (m_sciencePurchaseWindowsRank8[ i ] != nullptr)
				m_sciencePurchaseWindowsRank8[ i ]->winHide( TRUE );
		}
		else
		{
			// make sure the window is not hidden
			m_sciencePurchaseWindowsRank8[ i ]->winHide( FALSE );

			// Disable by default
			m_sciencePurchaseWindowsRank8[ i ]->winEnable( FALSE );

			// populate the visible button with data from the command button

			setControlCommand( m_sciencePurchaseWindowsRank8[ i ], commandButton, NULL, -1 );
			ScienceType	st = SCIENCE_INVALID;
			st = commandButton->getScienceVec()[ 0 ];
			if( player->isScienceDisabled( st ) )
			{
				//A script has deemed this science disabled.
				m_sciencePurchaseWindowsRank8[ i ]->winEnable( FALSE );
			}
			else if( player->isScienceHidden( st ) )
			{
				//A script has deemed this science unavailable, thus hidden
				m_sciencePurchaseWindowsRank8[ i ]->winHide( TRUE );
			}
			else
			{
				//Handle normal game logic cases!
				if(!player->hasScience(st) && TheScienceStore->playerHasPrereqsForScience(player, st) && TheScienceStore->getSciencePurchaseCost(st) <= player->getSciencePurchasePoints())
				{
					m_sciencePurchaseWindowsRank8[ i ]->winEnable( TRUE );
				}
				if(player->hasScience(st))
				{
					m_sciencePurchaseWindowsRank8[ i ]->winSetStatus(WIN_STATUS_ALWAYS_COLOR);
				}
				else
				{
					m_sciencePurchaseWindowsRank8[ i ]->winClearStatus(WIN_STATUS_ALWAYS_COLOR);
				}
				if(!TheScienceStore->playerHasRootPrereqsForScience(player, st))
					m_sciencePurchaseWindowsRank8[ i ]->winHide(TRUE);
			}

		}

	}


	GameWindow *win = NULL;
	UnicodeString tempUS;
	win = TheWindowManager->winGetWindowFromId( m_contextParent[ CP_PURCHASE_SCIENCE ], TheNameKeyGenerator->nameToKey( "GeneralsExpPoints.wnd:StaticTextRankPointsAvailable" ) );
	if(win)
	{
		tempUS.format(L"%d", player->getSciencePurchasePoints());
		GadgetStaticTextSetText(win, tempUS);
	}

// redundant to StaticTextTitle in the Zero Hour context
/*
	win = TheWindowManager->winGetWindowFromId( m_contextParent[ CP_PURCHASE_SCIENCE ], TheNameKeyGenerator->nameToKey( "GeneralsExpPoints.wnd:StaticTextLevel" ) );
	if(win)
	{
		tempUS.format(TheGameText->fetch("SCIENCE:Rank"), player->getRankLevel());
		GadgetStaticTextSetText(win, tempUS);
	}
*/

	win = TheWindowManager->winGetWindowFromId( m_contextParent[ CP_PURCHASE_SCIENCE ], TheNameKeyGenerator->nameToKey( "GeneralsExpPoints.wnd:ProgressBarExperience" ) );
	if(win)
	{
		Int progress;
		progress = ((player->getSkillPoints() - player->getSkillPointsLevelDown()) * 100) /(player->getSkillPointsLevelUp() - player->getSkillPointsLevelDown());
		GadgetProgressBarSetProgress(win, progress);
	}

	win = TheWindowManager->winGetWindowFromId( m_contextParent[ CP_PURCHASE_SCIENCE ], TheNameKeyGenerator->nameToKey( "GeneralsExpPoints.wnd:StaticTextTitle" ) );
	if(win)
	{
		AsciiString tempAs;

		tempAs.format("SCIENCE:Rank%d", player->getRankLevel());
		GadgetStaticTextSetText(win, TheGameText->fetch(tempAs));
	}


	//
	// to avoid a one frame delay where windows may become enabled/disabled, run the update
	// at once to get it all in the correct state immediately
	//
	updateContextPurchaseScience();
/*
	// get the side select buttons
	GameWindow* win = m_contextParent[ CP_PURCHASE_SCIENCE ];

	Color color = GameMakeColor(255, 255, 255, 255);

	/// @todo srj -- evil hack testing code. do not imitate.
	ScienceVec purchasable, potential;
	TheScienceStore->getPurchasableSciences(player, purchasable, potential);
	GadgetListBoxReset(win);
	for (ScienceVec::const_iterator it = purchasable.begin(); it != purchasable.end(); ++it)
	{
		ScienceType st = *it;
		UnicodeString u;
		u.translate(TheScienceStore->getInternalNameForScience(st));
		GadgetListBoxAddEntryText(win, u, color, -1, -1);
	}
	for (ScienceVec::const_iterator it2 = potential.begin(); it2 != potential.end(); ++it2)
	{
		ScienceType st = *it2;
		AsciiString foo = "(Not Yet)";
		foo.concat(TheScienceStore->getInternalNameForScience(st));
		UnicodeString u;
		u.translate(foo);
		GadgetListBoxAddEntryText(win, u, color, -1, -1);
	}
	GadgetListBoxAddEntryText(win, L"Cancel", color, -1, -1);*/

}




//-------------------------------------------------------------------------------------------------
/** Alternative button prerequisite parsing functions */
//-------------------------------------------------------------------------------------------------
void CommandButton::parseAlternativeButton1Prerequisites(INI* ini, void* instance, void* store, const void* userData)
{
	// TheSuperHackers @refactor author 15/01/2025 Wrapper function for generic parsePrerequisites with resolveNames=TRUE
	CommandButton* self = (CommandButton*)instance;
	PlayerPrerequisite::parsePrerequisites(ini, &self->m_alternativeButton1Prereq, store, userData);
}

void CommandButton::parseAlternativeButton2Prerequisites(INI* ini, void* instance, void* store, const void* userData)
{
	// TheSuperHackers @refactor author 15/01/2025 Wrapper function for generic parsePrerequisites with resolveNames=TRUE
	CommandButton* self = (CommandButton*)instance;
	PlayerPrerequisite::parsePrerequisites(ini, &self->m_alternativeButton2Prereq, store, userData);
}

void CommandButton::parseAlternativeButton3Prerequisites(INI* ini, void* instance, void* store, const void* userData)
{
	// TheSuperHackers @refactor author 15/01/2025 Wrapper function for generic parsePrerequisites with resolveNames=TRUE
	CommandButton* self = (CommandButton*)instance;
	PlayerPrerequisite::parsePrerequisites(ini, &self->m_alternativeButton3Prereq, store, userData);
}

void CommandButton::parseAlternativeButton4Prerequisites(INI* ini, void* instance, void* store, const void* userData)
{
	// TheSuperHackers @alternative Ahmed Salah 27/06/2025 Parse prerequisites for alternative button 4
	CommandButton* self = (CommandButton*)instance;
	PlayerPrerequisite::parsePrerequisites(ini, &self->m_alternativeButton4Prereq, store, userData);
}

//-------------------------------------------------------------------------------------------------
/** Alternative button object prerequisite parsing functions */
//-------------------------------------------------------------------------------------------------
void CommandButton::parseAlternativeButton1ObjectPrerequisites(INI* ini, void* instance, void* store, const void* userData)
{
	// TheSuperHackers @feature author 15/01/2025 Wrapper function for generic parseObjectPrerequisites
	CommandButton* self = (CommandButton*)instance;
	ObjectPrerequisite::parseObjectPrerequisites(ini, &self->m_alternativeButton1ObjectPrereq, store, userData);
}

void CommandButton::parseAlternativeButton2ObjectPrerequisites(INI* ini, void* instance, void* store, const void* userData)
{
	// TheSuperHackers @feature author 15/01/2025 Wrapper function for generic parseObjectPrerequisites
	CommandButton* self = (CommandButton*)instance;
	ObjectPrerequisite::parseObjectPrerequisites(ini, &self->m_alternativeButton2ObjectPrereq, store, userData);
}

void CommandButton::parseAlternativeButton3ObjectPrerequisites(INI* ini, void* instance, void* store, const void* userData)
{
	// TheSuperHackers @feature author 15/01/2025 Wrapper function for generic parseObjectPrerequisites
	CommandButton* self = (CommandButton*)instance;
	ObjectPrerequisite::parseObjectPrerequisites(ini, &self->m_alternativeButton3ObjectPrereq, store, userData);
}

void CommandButton::parseAlternativeButton4ObjectPrerequisites(INI* ini, void* instance, void* store, const void* userData)
{
	// TheSuperHackers @feature author 15/01/2025 Wrapper function for generic parseObjectPrerequisites
	CommandButton* self = (CommandButton*)instance;
	ObjectPrerequisite::parseObjectPrerequisites(ini, &self->m_alternativeButton4ObjectPrereq, store, userData);
}

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @refactor author 15/01/2025 Implement missing prerequisite parsing methods
void CommandButton::parseEnablePrerequisites(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	CommandButton* button = (CommandButton*)instance;
	PlayerPrerequisite::parsePrerequisites(ini, &button->m_enablePrereqInfo, NULL, NULL);
}

//-------------------------------------------------------------------------------------------------
void CommandButton::parseVisiblePrerequisites(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	CommandButton* button = (CommandButton*)instance;
	PlayerPrerequisite::parsePrerequisites(ini, &button->m_visiblePrereqInfo, NULL, NULL);
}

//-------------------------------------------------------------------------------------------------
void CommandButton::parseEnableCallerUnitPrerequisites(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	CommandButton* button = (CommandButton*)instance;
	ObjectPrerequisite::parseObjectPrerequisites(ini, &button->m_enableCallerUnitPrereqInfo, NULL, NULL);
}

//-------------------------------------------------------------------------------------------------
void CommandButton::parseVisibleCallerUnitPrerequisites(INI* ini, void* instance, void* /*store*/, const void* /*userData*/)
{
	CommandButton* button = (CommandButton*)instance;
	ObjectPrerequisite::parseObjectPrerequisites(ini, &button->m_visibleCallerUnitPrereqInfo, NULL, NULL);
}


//---------------------------------------------
//       Prerequisite
//---------------------------------------------



//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void ControlBar::updateContextPurchaseScience( void )
{
	GameWindow *win =NULL;
	Player *player = ThePlayerList->getLocalPlayer();
	win = TheWindowManager->winGetWindowFromId( m_contextParent[ CP_PURCHASE_SCIENCE ], TheNameKeyGenerator->nameToKey( "GeneralsExpPoints.wnd:ProgressBarExperience" ) );
	if(win)
	{
		Int progress;
		progress = ((player->getSkillPoints() - player->getSkillPointsLevelDown()) * 100) /(player->getSkillPointsLevelUp() - player->getSkillPointsLevelDown());
		GadgetProgressBarSetProgress(win, progress);
	}

//	win = TheWindowManager->winGetWindowFromId( m_contextParent[ CP_PURCHASE_SCIENCE ], TheNameKeyGenerator->nameToKey( "ControlBar.wnd:TextEntryGeneralName" ) );
//	if(win)
//	{
//		UnicodeString temp = GadgetTextEntryGetText(win);
//		if(temp.compare(player->getGeneralName()) != 0)
//			player->setGeneralName(temp);
//	}
/*
	/// @todo srj -- evil hack testing code. do not imitate.
	Object *obj = m_currentSelectedDrawable->getObject();

	if( obj == NULL )
		return;

	// sanity
	if( obj->isKindOf( KINDOF_COMMANDCENTER ) == FALSE )
		switchToContext( CB_CONTEXT_NONE, NULL );

	GameWindow* win = m_contextParent[ CP_PURCHASE_SCIENCE ];

	Int selected;
	GadgetListBoxGetSelected( win, &selected );
	if( selected != -1 )
	{
		UnicodeString usci = GadgetListBoxGetText( win, selected, 0 );
		AsciiString sci;
		sci.translate(usci);
		ScienceType st = usci.getCharAt(0) == '(' ? SCIENCE_INVALID : TheScienceStore->getScienceFromInternalName(sci);

		if (st != SCIENCE_INVALID)
		{
			GameMessage *msg = TheMessageStream->appendMessage( GameMessage::MSG_PURCHASE_SCIENCE );
			msg->appendIntegerArgument( st );
		}

		switchToContext( CB_CONTEXT_NONE, NULL );
	}
*/

}

//-------------------------------------------------------------------------------------------------
/** parse command definition */
//-------------------------------------------------------------------------------------------------
void CommandButton::parseCommand( INI* ini, void *instance, void *store, const void *userData )
{
	const char *token = ini->getNextToken();
	Int i;

	for( i = 0; TheGuiCommandNames[ i ]; i++ )
	{

		if( stricmp( TheGuiCommandNames[ i ], token ) == 0 )
		{

			GUICommandType *command = (GUICommandType *)store;
			*command = (GUICommandType)i;
			return;

		}

	}

	// if we're here the command was not found
	throw INI_INVALID_DATA;

}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
CommandButton::CommandButton( void )
{

	m_command = GUI_COMMAND_NONE;
	m_thingTemplate = NULL;
	m_upgradeTemplate = NULL;
	m_weaponSlot = NONE_WEAPON;
	m_maxShotsToFire = 0x7fffffff;	// huge number
	m_science.clear();
	m_specialPower = NULL;
	m_buttonImage = NULL;
	m_prereqInfoResloved = false;
	//Code renderer handles these states now.
	//m_disabledImage = NULL;
	//m_hiliteImage = NULL;
	//m_pushedImage = NULL;

	m_flashCount = 0;
	m_conflictingLabel.clear();
	m_cursorName.clear();
	m_descriptionLabel.clear();
	m_invalidCursorName.clear();
	m_name.clear();
	m_options = 0;
	m_purchasedLabel.clear();
	m_textLabel.clear();
	m_overlayImageName.clear();
	m_overlayImage2Name.clear();
	m_itemToReplenish.clear();
	m_amount = 1;  // Default amount is 1
	m_enableMassProduction = true;  // Default mass production is enabled
	m_isRequireElectronics = false;
	// End Add

	m_window = NULL;
	m_commandButtonBorder = COMMAND_BUTTON_BORDER_NONE;
	//m_prev = NULL;
	m_next = NULL;
	m_radiusCursor = RADIUSCURSOR_NONE;

	// Initialize modifier key button name strings
	m_leftClickCtrlButtonName.clear();
	m_leftClickAltButtonName.clear();
	m_leftClickShiftButtonName.clear();
	m_leftClickCtrlAltButtonName.clear();
	m_leftClickCtrlShiftButtonName.clear();
	m_leftClickAltShiftButtonName.clear();
	m_leftClickCtrlAltShiftButtonName.clear();

	m_rightClickButtonName.clear();
	m_rightClickCtrlButtonName.clear();
	m_rightClickAltButtonName.clear();
	m_rightClickShiftButtonName.clear();
	m_rightClickCtrlAltButtonName.clear();
	m_rightClickCtrlShiftButtonName.clear();
	m_rightClickAltShiftButtonName.clear();
	m_rightClickCtrlAltShiftButtonName.clear();

	// Initialize alternative button name strings
	m_alternativeButton1Name.clear();
	m_alternativeButton2Name.clear();
	m_alternativeButton3Name.clear();
	m_alternativeButton4Name.clear();

	// Initialize alternative button object prerequisite vectors
	m_alternativeButton1ObjectPrereq.clear();
	m_alternativeButton2ObjectPrereq.clear();
	m_alternativeButton3ObjectPrereq.clear();
	m_alternativeButton4ObjectPrereq.clear();

	// Initialize cached button references to NULL
	m_leftClickCtrlButton = NULL;
	m_leftClickAltButton = NULL;
	m_leftClickShiftButton = NULL;
	m_leftClickCtrlAltButton = NULL;
	m_leftClickCtrlShiftButton = NULL;
	m_leftClickAltShiftButton = NULL;
	m_leftClickCtrlAltShiftButton = NULL;

	m_rightClickButton = NULL;
	m_rightClickCtrlButton = NULL;
	m_rightClickAltButton = NULL;
	m_rightClickShiftButton = NULL;
	m_rightClickCtrlAltButton = NULL;
	m_rightClickCtrlShiftButton = NULL;
	m_rightClickAltShiftButton = NULL;
	m_rightClickCtrlAltShiftButton = NULL;

	// Initialize cached alternative button references to NULL
	m_alternativeButton1 = NULL;
	m_alternativeButton2 = NULL;
	m_alternativeButton3 = NULL;
	m_alternativeButton4 = NULL;

	// TheSuperHackers @feature Ahmed Salah 28/10/2025 Initialize target kind filter to invalid
	m_targetKindOfType = KINDOF_INVALID;

}

//-------------------------------------------------------------------------------------------------
/** Getter functions with caching mechanism for modifier button combinations */
//-------------------------------------------------------------------------------------------------
const CommandButton* CommandButton::getLeftClickCtrlButton() const
{
	if (!m_leftClickCtrlButton && !m_leftClickCtrlButtonName.isEmpty())
	{
		m_leftClickCtrlButton = TheControlBar->findCommandButton(m_leftClickCtrlButtonName);
	}
	return m_leftClickCtrlButton;
}

const CommandButton* CommandButton::getLeftClickAltButton() const
{
	if (!m_leftClickAltButton && !m_leftClickAltButtonName.isEmpty())
	{
		m_leftClickAltButton = TheControlBar->findCommandButton(m_leftClickAltButtonName);
	}
	return m_leftClickAltButton;
}

const CommandButton* CommandButton::getLeftClickShiftButton() const
{
	if (!m_leftClickShiftButton && !m_leftClickShiftButtonName.isEmpty())
	{
		m_leftClickShiftButton = TheControlBar->findCommandButton(m_leftClickShiftButtonName);
	}
	return m_leftClickShiftButton;
}

const CommandButton* CommandButton::getLeftClickCtrlAltButton() const
{
	if (!m_leftClickCtrlAltButton && !m_leftClickCtrlAltButtonName.isEmpty())
	{
		m_leftClickCtrlAltButton = TheControlBar->findCommandButton(m_leftClickCtrlAltButtonName);
	}
	return m_leftClickCtrlAltButton;
}

const CommandButton* CommandButton::getLeftClickCtrlShiftButton() const
{
	if (!m_leftClickCtrlShiftButton && !m_leftClickCtrlShiftButtonName.isEmpty())
	{
		m_leftClickCtrlShiftButton = TheControlBar->findCommandButton(m_leftClickCtrlShiftButtonName);
	}
	return m_leftClickCtrlShiftButton;
}

const CommandButton* CommandButton::getLeftClickAltShiftButton() const
{
	if (!m_leftClickAltShiftButton && !m_leftClickAltShiftButtonName.isEmpty())
	{
		m_leftClickAltShiftButton = TheControlBar->findCommandButton(m_leftClickAltShiftButtonName);
	}
	return m_leftClickAltShiftButton;
}

const CommandButton* CommandButton::getLeftClickCtrlAltShiftButton() const
{
	if (!m_leftClickCtrlAltShiftButton && !m_leftClickCtrlAltShiftButtonName.isEmpty())
	{
		m_leftClickCtrlAltShiftButton = TheControlBar->findCommandButton(m_leftClickCtrlAltShiftButtonName);
	}
	return m_leftClickCtrlAltShiftButton;
}

const CommandButton* CommandButton::getRightClickButton() const
{
	if (!m_rightClickButton && !m_rightClickButtonName.isEmpty())
	{
		m_rightClickButton = TheControlBar->findCommandButton(m_rightClickButtonName);
	}
	return m_rightClickButton;
}

const CommandButton* CommandButton::getRightClickCtrlButton() const
{
	if (!m_rightClickCtrlButton && !m_rightClickCtrlButtonName.isEmpty())
	{
		m_rightClickCtrlButton = TheControlBar->findCommandButton(m_rightClickCtrlButtonName);
	}
	return m_rightClickCtrlButton;
}

const CommandButton* CommandButton::getRightClickAltButton() const
{
	if (!m_rightClickAltButton && !m_rightClickAltButtonName.isEmpty())
	{
		m_rightClickAltButton = TheControlBar->findCommandButton(m_rightClickAltButtonName);
	}
	return m_rightClickAltButton;
}

const CommandButton* CommandButton::getRightClickShiftButton() const
{
	if (!m_rightClickShiftButton && !m_rightClickShiftButtonName.isEmpty())
	{
		m_rightClickShiftButton = TheControlBar->findCommandButton(m_rightClickShiftButtonName);
	}
	return m_rightClickShiftButton;
}

const CommandButton* CommandButton::getRightClickCtrlAltButton() const
{
	if (!m_rightClickCtrlAltButton && !m_rightClickCtrlAltButtonName.isEmpty())
	{
		m_rightClickCtrlAltButton = TheControlBar->findCommandButton(m_rightClickCtrlAltButtonName);
	}
	return m_rightClickCtrlAltButton;
}

const CommandButton* CommandButton::getRightClickCtrlShiftButton() const
{
	if (!m_rightClickCtrlShiftButton && !m_rightClickCtrlShiftButtonName.isEmpty())
	{
		m_rightClickCtrlShiftButton = TheControlBar->findCommandButton(m_rightClickCtrlShiftButtonName);
	}
	return m_rightClickCtrlShiftButton;
}

const CommandButton* CommandButton::getRightClickAltShiftButton() const
{
	if (!m_rightClickAltShiftButton && !m_rightClickAltShiftButtonName.isEmpty())
	{
		m_rightClickAltShiftButton = TheControlBar->findCommandButton(m_rightClickAltShiftButtonName);
	}
	return m_rightClickAltShiftButton;
}

const CommandButton* CommandButton::getRightClickCtrlAltShiftButton() const
{
	if (!m_rightClickCtrlAltShiftButton && !m_rightClickCtrlAltShiftButtonName.isEmpty())
	{
		m_rightClickCtrlAltShiftButton = TheControlBar->findCommandButton(m_rightClickCtrlAltShiftButtonName);
	}
	return m_rightClickCtrlAltShiftButton;
}

//-------------------------------------------------------------------------------------------------
/** Alternative button getters (completely replace original button when prerequisites are satisfied) */
//-------------------------------------------------------------------------------------------------
const CommandButton* CommandButton::getAlternativeButton1() const
{
	if (!m_alternativeButton1 && !m_alternativeButton1Name.isEmpty())
	{
		m_alternativeButton1 = TheControlBar->findCommandButton(m_alternativeButton1Name);
	}
	return m_alternativeButton1;
}

const CommandButton* CommandButton::getAlternativeButton2() const
{
	if (!m_alternativeButton2 && !m_alternativeButton2Name.isEmpty())
	{
		m_alternativeButton2 = TheControlBar->findCommandButton(m_alternativeButton2Name);
	}
	return m_alternativeButton2;
}

const CommandButton* CommandButton::getAlternativeButton3() const
{
	if (!m_alternativeButton3 && !m_alternativeButton3Name.isEmpty())
	{
		m_alternativeButton3 = TheControlBar->findCommandButton(m_alternativeButton3Name);
	}
	return m_alternativeButton3;
}

const CommandButton* CommandButton::getAlternativeButton4() const
{
	if (!m_alternativeButton4 && !m_alternativeButton4Name.isEmpty())
	{
		m_alternativeButton4 = TheControlBar->findCommandButton(m_alternativeButton4Name);
	}
	return m_alternativeButton4;
}

//-------------------------------------------------------------------------------------------------
/** Get the appropriate alternative button based on prerequisites (replaces original button completely) */
//-------------------------------------------------------------------------------------------------
const CommandButton* CommandButton::getAlternativeButtonForPrerequisites(const Player* player, const Object* object) const
{
	// TheSuperHackers @alternative Ahmed Salah 27/06/2025 Check alternative buttons in order of priority (1-4) and return first one with satisfied prerequisites
	
	// Check alternative button 1
	if (!m_alternativeButton1Name.isEmpty())
	{
		const CommandButton* altButton1 = getAlternativeButton1();
		if (altButton1)
		{
			Bool allPrereqsSatisfied = true;
			
			// Check player prerequisites
			for (size_t i = 0; i < m_alternativeButton1Prereq.size(); ++i)
			{
				if (!m_alternativeButton1Prereq[i].isSatisfied(player))
				{
					allPrereqsSatisfied = false;
					break;
				}
			}
			
			// Check object prerequisites (OR logic - if player prereqs are empty, check object prereqs)
			if (allPrereqsSatisfied || m_alternativeButton1Prereq.empty())
			{
				if (!m_alternativeButton1ObjectPrereq.empty())
				{
					Bool objectPrereqsSatisfied = true;
					for (size_t i = 0; i < m_alternativeButton1ObjectPrereq.size(); ++i)
					{
						if (!m_alternativeButton1ObjectPrereq[i].isSatisfied(object))
						{
							objectPrereqsSatisfied = false;
							break;
						}
					}
					allPrereqsSatisfied = objectPrereqsSatisfied;
				}
			}
			
			if (allPrereqsSatisfied)
			{
				// TheSuperHackers @alternative Ahmed Salah 15/01/2025 Recursively check if this alternative button has its own alternatives
				const CommandButton* recursiveAlt = altButton1->getAlternativeButtonForPrerequisites(player, object);
				return recursiveAlt ? recursiveAlt : altButton1;
			}
		}
	}

	// Check alternative button 2
	if (!m_alternativeButton2Name.isEmpty())
	{
		const CommandButton* altButton2 = getAlternativeButton2();
		if (altButton2)
		{
			Bool allPrereqsSatisfied = true;
			
			// Check player prerequisites
			for (size_t i = 0; i < m_alternativeButton2Prereq.size(); ++i)
			{
				if (!m_alternativeButton2Prereq[i].isSatisfied(player))
				{
					allPrereqsSatisfied = false;
					break;
				}
			}
			
			// Check object prerequisites (OR logic - if player prereqs are empty, check object prereqs)
			if (allPrereqsSatisfied || m_alternativeButton2Prereq.empty())
			{
				if (!m_alternativeButton2ObjectPrereq.empty())
				{
					Bool objectPrereqsSatisfied = true;
					for (size_t i = 0; i < m_alternativeButton2ObjectPrereq.size(); ++i)
					{
						if (!m_alternativeButton2ObjectPrereq[i].isSatisfied(object))
						{
							objectPrereqsSatisfied = false;
							break;
						}
					}
					allPrereqsSatisfied = objectPrereqsSatisfied;
				}
			}
			
			if (allPrereqsSatisfied)
			{
				// TheSuperHackers @alternative Ahmed Salah 15/01/2025 Recursively check if this alternative button has its own alternatives
				const CommandButton* recursiveAlt = altButton2->getAlternativeButtonForPrerequisites(player, object);
				return recursiveAlt ? recursiveAlt : altButton2;
			}
		}
	}

	// Check alternative button 3
	if (!m_alternativeButton3Name.isEmpty())
	{
		const CommandButton* altButton3 = getAlternativeButton3();
		if (altButton3)
		{
			Bool allPrereqsSatisfied = true;
			
			// Check player prerequisites
			for (size_t i = 0; i < m_alternativeButton3Prereq.size(); ++i)
			{
				if (!m_alternativeButton3Prereq[i].isSatisfied(player))
				{
					allPrereqsSatisfied = false;
					break;
				}
			}
			
			// Check object prerequisites (OR logic - if player prereqs are empty, check object prereqs)
			if (allPrereqsSatisfied || m_alternativeButton3Prereq.empty())
			{
				if (!m_alternativeButton3ObjectPrereq.empty())
				{
					Bool objectPrereqsSatisfied = true;
					for (size_t i = 0; i < m_alternativeButton3ObjectPrereq.size(); ++i)
					{
						if (!m_alternativeButton3ObjectPrereq[i].isSatisfied(object))
						{
							objectPrereqsSatisfied = false;
							break;
						}
					}
					allPrereqsSatisfied = objectPrereqsSatisfied;
				}
			}
			
			if (allPrereqsSatisfied)
			{
				// TheSuperHackers @alternative Ahmed Salah 15/01/2025 Recursively check if this alternative button has its own alternatives
				const CommandButton* recursiveAlt = altButton3->getAlternativeButtonForPrerequisites(player, object);
				return recursiveAlt ? recursiveAlt : altButton3;
			}
		}
	}

	// Check alternative button 4
	if (!m_alternativeButton4Name.isEmpty())
	{
		const CommandButton* altButton4 = getAlternativeButton4();
		if (altButton4)
		{
			Bool allPrereqsSatisfied = true;
			
			// Check player prerequisites
			for (size_t i = 0; i < m_alternativeButton4Prereq.size(); ++i)
			{
				if (!m_alternativeButton4Prereq[i].isSatisfied(player))
				{
					allPrereqsSatisfied = false;
					break;
				}
			}
			
			// Check object prerequisites (OR logic - if player prereqs are empty, check object prereqs)
			if (allPrereqsSatisfied || m_alternativeButton4Prereq.empty())
			{
				if (!m_alternativeButton4ObjectPrereq.empty())
				{
					Bool objectPrereqsSatisfied = true;
					for (size_t i = 0; i < m_alternativeButton4ObjectPrereq.size(); ++i)
					{
						if (!m_alternativeButton4ObjectPrereq[i].isSatisfied(object))
						{
							objectPrereqsSatisfied = false;
							break;
						}
					}
					allPrereqsSatisfied = objectPrereqsSatisfied;
				}
			}
			
			if (allPrereqsSatisfied)
			{
				// TheSuperHackers @alternative Ahmed Salah 15/01/2025 Recursively check if this alternative button has its own alternatives
				const CommandButton* recursiveAlt = altButton4->getAlternativeButtonForPrerequisites(player, object);
				return recursiveAlt ? recursiveAlt : altButton4;
			}
		}
	}

	// No alternative button prerequisites satisfied, return NULL (use original button)
	return NULL;
}

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature author 15/01/2025 Get the cost of executing this command button
//-------------------------------------------------------------------------------------------------
UnsignedInt CommandButton::getCostOfExecution(const Player* player, const Object* object) const
{
	if (!player || !object)
		return 0;

	switch (m_command)
	{
		case GUI_COMMAND_UNIT_BUILD:
		{
			const ThingTemplate* thingTemplate = getThingTemplate();
			if (thingTemplate)
			{
				// TheSuperHackers @feature author 15/01/2025 Multiply cost by amount for multiple units
				Int amount = getAmount();
				
				// Check for mass production with modifier keys (if enabled)
				if (getEnableMassProduction()) {
					// Note: We can't detect modifier keys here, so we use the base amount
					// The actual mass production logic is handled in ControlBarCommandProcessing.cpp
				}
				
				return thingTemplate->friend_getBuildCost() * amount;
			}
			break;
		}

		case GUI_COMMAND_DOZER_CONSTRUCT:
		{
			const ThingTemplate* thingTemplate = getThingTemplate();
			if (thingTemplate)
			{
				// TheSuperHackers @feature author 15/01/2025 Multiply cost by amount for multiple units
				return thingTemplate->friend_getBuildCost() * getAmount();
			}
			break;
		}

		case GUI_COMMAND_PLAYER_UPGRADE:
		{
			const UpgradeTemplate* upgradeTemplate = getUpgradeTemplate();
			if (upgradeTemplate)
			{
				return upgradeTemplate->calcCostToBuild(const_cast<Player*>(player));
			}
			break;
		}

		case GUI_COMMAND_OBJECT_UPGRADE:
		{
			const UpgradeTemplate* upgradeTemplate = getUpgradeTemplate();
			if (upgradeTemplate)
			{
				return upgradeTemplate->calcCostToBuild(const_cast<Player*>(player));
			}
			break;
		}

		case GUI_COMMAND_SPECIAL_POWER:
		case GUI_COMMAND_SPECIAL_POWER_FROM_SHORTCUT:
		case GUI_COMMAND_SPECIAL_POWER_CONSTRUCT:
		case GUI_COMMAND_SPECIAL_POWER_CONSTRUCT_FROM_SHORTCUT:
		{
			const SpecialPowerTemplate* specialPowerTemplate = getSpecialPowerTemplate();
			if (specialPowerTemplate)
			{
				return specialPowerTemplate->getUsingCost();
			}
			break;
		}

		case GUI_COMMAND_REPLENISH_INVENTORY_ITEM:
		{
			// TheSuperHackers @feature author 15/01/2025 Calculate cost for inventory replenishment
			InventoryBehavior* inventoryBehavior = object->getInventoryBehavior();
			if (!inventoryBehavior)
				return 0;

			const InventoryBehaviorModuleData* moduleData = inventoryBehavior->getInventoryModuleData();
			if (!moduleData)
				return 0;

			const AsciiString& itemToReplenish = getItemToReplenish();
			UnsignedInt totalCost = 0;

			if (itemToReplenish.isEmpty())
			{
				// Calculate cost for all items
				for (std::map<AsciiString, InventoryItemConfig>::const_iterator it = moduleData->m_inventoryItems.begin();
					 it != moduleData->m_inventoryItems.end(); ++it)
				{
					const AsciiString& itemKey = it->first;
					const InventoryItemConfig& config = it->second;
					
					Int neededAmount = object->getInventoryReplenishAmount(itemKey);
					
					if (neededAmount > 0)
					{
						totalCost += neededAmount * config.costPerItem;
					}
				}
			}
			else
			{
				// Calculate cost for specific item
				Int neededAmount = object->getInventoryReplenishAmount(itemToReplenish);
				
				if (neededAmount > 0)
				{
					Int costPerItem = moduleData->getCostPerItem(itemToReplenish);
					totalCost = neededAmount * costPerItem;
				}
			}

			return totalCost;
		}

		case GUI_COMMAND_PURCHASE_SCIENCE:
		{
			// Calculate cost for science purchase
			ScienceType st = SCIENCE_INVALID;
			for (size_t i = 0; i < getScienceVec().size(); ++i)
			{
				st = getScienceVec()[i];
				if (!player->hasScience(st) && TheScienceStore->playerHasPrereqsForScience(player, st))
				{
					return TheScienceStore->getSciencePurchaseCost(st);
				}
			}
			break;
		}

		case GUI_COMMAND_REPLACE_COMPONENT:
		{
			// TheSuperHackers @feature author 15/01/2025 Calculate cost for component replacement
			BodyModuleInterface* body = object->getBodyModule();
			if (!body)
				return 0;

			const AsciiString& componentName = getComponentName();
			UnsignedInt totalCost = 0;

			if (componentName.isEmpty())
			{
				// Calculate cost for all damaged components
				std::vector<Component> components = body->getComponents();
				for (std::vector<Component>::const_iterator it = components.begin();
					 it != components.end(); ++it)
				{
					const Component& component = *it;
					if (component.getReplacementCost() > 0)
					{
						// Only include cost if component is damaged
						if (component.getCurrentHealth() < component.getCurrentMaxHealth())
						{
							totalCost += component.getReplacementCost();
						}
					}
				}
			}
			else
			{
				// Calculate cost for specific component
				Component* component = body->GetComponent<Component>(componentName);
				if (component)
				{
				// Only include cost if component is damaged
					if (component->getCurrentHealth() < component->getCurrentMaxHealth())
						{
						totalCost += component->getReplacementCost();
					}
				}
			}

			return totalCost;
		}

		default:
			// Most commands don't have a cost
			return 0;
	}

	return 0;
}

//-------------------------------------------------------------------------------------------------
/** Get the appropriate button based on modifier keys and click type */
//-------------------------------------------------------------------------------------------------
const CommandButton* CommandButton::getButtonForModifiers(Bool ctrlPressed, Bool altPressed, Bool shiftPressed, Bool isRightClick) const
{
	if (isRightClick)
	{
		// Right-click combinations
		if (ctrlPressed && altPressed && shiftPressed)
			return getRightClickCtrlAltShiftButton();
		else if (ctrlPressed && altPressed)
			return getRightClickCtrlAltButton();
		else if (ctrlPressed && shiftPressed)
			return getRightClickCtrlShiftButton();
		else if (altPressed && shiftPressed)
			return getRightClickAltShiftButton();
		else if (ctrlPressed)
			return getRightClickCtrlButton();
		else if (altPressed)
			return getRightClickAltButton();
		else if (shiftPressed)
			return getRightClickShiftButton();
		else
			return getRightClickButton(); 
	}
	else
	{
		// Left-click combinations
		if (ctrlPressed && altPressed && shiftPressed)
			return getLeftClickCtrlAltShiftButton();
		else if (ctrlPressed && altPressed)
			return getLeftClickCtrlAltButton();
		else if (ctrlPressed && shiftPressed)
			return getLeftClickCtrlShiftButton();
		else if (altPressed && shiftPressed)
			return getLeftClickAltShiftButton();
		else if (ctrlPressed)
			return getLeftClickCtrlButton();
		else if (altPressed)
			return getLeftClickAltButton();
		else if (shiftPressed)
			return getLeftClickShiftButton();
		else
			return NULL; // No modifier-specific left-click button, use the button itself
	}
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
CommandButton::~CommandButton( void )
{

}

//-------------------------------------------------------------------------------------------------
Bool CommandButton::isValidRelationshipTarget(Relationship r) const
{
	UnsignedInt mask = 0;
	if (r == ENEMIES) mask |= NEED_TARGET_ENEMY_OBJECT;
	else if (r == ALLIES) mask |= NEED_TARGET_ALLY_OBJECT;
	else if (r == NEUTRAL) mask |= NEED_TARGET_NEUTRAL_OBJECT;

	return (m_options & mask) != 0;
}

//-------------------------------------------------------------------------------------------------
Bool CommandButton::isValidObjectTarget(const Player* sourcePlayer, const Object* targetObj) const
{
	if (!sourcePlayer || !targetObj)
		return false;

	Relationship r = sourcePlayer->getRelationship(targetObj->getTeam());

	return isValidRelationshipTarget(r);
}

//-------------------------------------------------------------------------------------------------
Bool CommandButton::isValidObjectTarget(const Object* sourceObj, const Object* targetObj) const
{
	if (!sourceObj || !targetObj)
		return false;

	Relationship r = sourceObj->getRelationship(targetObj);

	return isValidRelationshipTarget(r);
}

//-------------------------------------------------------------------------------------------------
Bool CommandButton::isValidToUseOn(const Object *sourceObj, const Object *targetObj, const Coord3D *targetLocation, CommandSourceType commandSource) const
{
	if (m_upgradeTemplate) {
		// @todo: Make a const version of pui. We're not altering the production queue, so this const-cast
		// is okay.
		ProductionUpdateInterface *pui = const_cast<Object*>(sourceObj)->getProductionUpdateInterface();
		if (pui) {
			const ProductionEntry *pe = pui->firstProduction();
			while (pe) {
				if (pe->getProductionUpgrade() != NULL)
					return false;
				pe = pui->nextProduction(pe);
			}
			return sourceObj->affectedByUpgrade(m_upgradeTemplate) && !sourceObj->hasUpgrade(m_upgradeTemplate);
		}
		// No ProductionUpdateInterface means we can't do this.
		return false;
	}

	if( BitIsSet( m_options, COMMAND_OPTION_NEED_OBJECT_TARGET ) && !targetObj )
	{
		return false;
	}

	Coord3D pos;
	if( targetLocation )
	{
		pos.set( targetLocation );
	}

	if( BitIsSet( m_options, NEED_TARGET_POS ) && !targetLocation )
	{
		if( targetObj )
		{
			pos.set( targetObj->getPosition() );
		}
		else
		{
			return false;
		}
	}

	if( BitIsSet( m_options, COMMAND_OPTION_NEED_OBJECT_TARGET ) )
	{
		return TheActionManager->canDoSpecialPowerAtObject( sourceObj, targetObj, commandSource, m_specialPower, m_options, false );
	}

	if( BitIsSet( m_options, NEED_TARGET_POS ) )
	{
		return TheActionManager->canDoSpecialPowerAtLocation( sourceObj, &pos, commandSource, m_specialPower, NULL, m_options, false );
	}

	return TheActionManager->canDoSpecialPower( sourceObj, m_specialPower, commandSource, m_options, false );
}

//-------------------------------------------------------------------------------------------------
Bool CommandButton::isReady(const Object *sourceObj) const
{
	SpecialPowerModuleInterface *mod = sourceObj->getSpecialPowerModule( m_specialPower );
	if( mod && mod->getPercentReady() == 1.0f )
		return true;

	if (m_upgradeTemplate && sourceObj->affectedByUpgrade(m_upgradeTemplate) && !sourceObj->hasUpgrade(m_upgradeTemplate))
		return true;

	return false;
}

//-------------------------------------------------------------------------------------------------
Bool CommandButton::isValidObjectTarget(const Drawable* source, const Drawable* target) const
{
	return isValidObjectTarget(source ? source->getObject() : NULL, target ? target->getObject() : NULL);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// CommandSet /////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
/** These are the fields you can define in a command set, they correspond to physical
	* buttons in the GUI */
//-------------------------------------------------------------------------------------------------
const FieldParse CommandSet::m_commandSetFieldParseTable[] =
{

	{ "1",			CommandSet::parseCommandButton, (void *)0,		offsetof( CommandSet, m_command ) },
	{ "2",			CommandSet::parseCommandButton, (void *)1,		offsetof( CommandSet, m_command ) },
	{ "3",			CommandSet::parseCommandButton, (void *)2,		offsetof( CommandSet, m_command ) },
	{ "4",			CommandSet::parseCommandButton, (void *)3,		offsetof( CommandSet, m_command ) },
	{ "5",			CommandSet::parseCommandButton, (void *)4,		offsetof( CommandSet, m_command ) },
	{ "6",			CommandSet::parseCommandButton, (void *)5,		offsetof( CommandSet, m_command ) },
	{ "7",			CommandSet::parseCommandButton, (void *)6,		offsetof( CommandSet, m_command ) },
	{ "8",			CommandSet::parseCommandButton, (void *)7,		offsetof( CommandSet, m_command ) },
	{ "9",			CommandSet::parseCommandButton, (void *)8,		offsetof( CommandSet, m_command ) },
	{ "10",			CommandSet::parseCommandButton, (void *)9,		offsetof( CommandSet, m_command ) },
	{ "11",			CommandSet::parseCommandButton, (void *)10,		offsetof( CommandSet, m_command ) },
	{ "12",			CommandSet::parseCommandButton, (void *)11,		offsetof( CommandSet, m_command ) },
	{ "13",			CommandSet::parseCommandButton, (void *)12,		offsetof( CommandSet, m_command ) },
	{ "14",			CommandSet::parseCommandButton, (void *)13,		offsetof( CommandSet, m_command ) },
	{ "15",			CommandSet::parseCommandButton, (void *)14,		offsetof( CommandSet, m_command ) },
	{ "16",			CommandSet::parseCommandButton, (void *)15,		offsetof( CommandSet, m_command ) },
	{ "17",			CommandSet::parseCommandButton, (void *)16,		offsetof( CommandSet, m_command ) },
	{ "18",			CommandSet::parseCommandButton, (void *)17,		offsetof( CommandSet, m_command ) },
	{ "19",			CommandSet::parseCommandButton, (void *)18,		offsetof( CommandSet, m_command ) },
	{ "20",			CommandSet::parseCommandButton, (void *)19,		offsetof( CommandSet, m_command ) },
	{ "21",			CommandSet::parseCommandButton, (void *)20,		offsetof( CommandSet, m_command ) },
	{ "22",			CommandSet::parseCommandButton, (void *)21,		offsetof( CommandSet, m_command ) },
	{ "23",			CommandSet::parseCommandButton, (void *)22,		offsetof( CommandSet, m_command ) },
	{ "24",			CommandSet::parseCommandButton, (void *)23,		offsetof( CommandSet, m_command ) },
	{ "25",			CommandSet::parseCommandButton, (void *)24,		offsetof( CommandSet, m_command ) },
	{ "26",			CommandSet::parseCommandButton, (void *)25,		offsetof( CommandSet, m_command ) },
	{ "27",			CommandSet::parseCommandButton, (void *)26,		offsetof( CommandSet, m_command ) },
	{ "28",			CommandSet::parseCommandButton, (void *)27,		offsetof( CommandSet, m_command ) },
	{ "29",			CommandSet::parseCommandButton, (void *)28,		offsetof( CommandSet, m_command ) },
	{ "30",			CommandSet::parseCommandButton, (void *)29,		offsetof( CommandSet, m_command ) },
	{ "31",			CommandSet::parseCommandButton, (void *)30,		offsetof( CommandSet, m_command ) },
	{ "32",			CommandSet::parseCommandButton, (void *)31,		offsetof( CommandSet, m_command ) },
	{ NULL,			NULL,														 NULL,				0	}  // keep this last

};

//-------------------------------------------------------------------------------------------------
Bool CommandButton::isContextCommand() const
{
	return BitIsSet( m_options, CONTEXTMODE_COMMAND );
}

//-------------------------------------------------------------------------------------------------
// bleah. shouldn't be const, but is. sue me. (srj)
void CommandButton::copyImagesFrom( const CommandButton *button, Bool markUIDirtyIfChanged ) const
{
	if( m_buttonImage != button->getButtonImage() )
	{
		m_buttonImage = button->getButtonImage();

		//Code renderer handles these states now.
		//m_disabledImage = button->getDisabledImage();
		//m_hiliteImage = button->getHiliteImage();
		//m_pushedImage = button->getPushedImage();

		if( markUIDirtyIfChanged )
		{
			TheControlBar->markUIDirty();
		}
	}
}

//-------------------------------------------------------------------------------------------------
// bleah. shouldn't be const, but is. sue me. (Kris) -snork!
void CommandButton::copyButtonTextFrom( const CommandButton *button, Bool shortcutButton, Bool markUIDirtyIfChanged ) const
{
	//This function was added to change the strings when you upgrade from a DaisyCutter to a MOAB. All other special
	//powers are the same.
	Bool change = FALSE;
	if( shortcutButton )
	{
		//Not the best code, but conflicting label means shortcut label (most won't have any string specified).
		if( button->getConflictingLabel().isNotEmpty() && m_textLabel.compare( button->getConflictingLabel() ) )
		{
			m_textLabel = button->getConflictingLabel();
			change = TRUE;
		}
	}
	else
	{
		//Copy the text from the purchase science button if it exists (most won't).
		if( button->getTextLabel().isNotEmpty() && m_textLabel.compare( button->getTextLabel() ) )
		{
			m_textLabel = button->getTextLabel();
			change = TRUE;
		}
	}
	if( button->getDescriptionLabel().isNotEmpty() && m_descriptionLabel.compare( button->getDescriptionLabel() ) )
	{
		m_descriptionLabel = button->getDescriptionLabel();
		change = TRUE;
	}
	if( markUIDirtyIfChanged && change )
	{
		TheControlBar->markUIDirty();
	}
}

//-------------------------------------------------------------------------------------------------
/** Parse a single command button definition */
//-------------------------------------------------------------------------------------------------
void CommandSet::parseCommandButton( INI* ini, void *instance, void *store, const void *userData )
{
	const char *token = ini->getNextToken();

	// get find the command button from this name
	const CommandButton *commandButton = TheControlBar->findCommandButton( AsciiString( token ) );
	if( commandButton == NULL )
	{

		DEBUG_CRASH(( "[LINE: %d - FILE: '%s'] Unknown command '%s' found in command set",
								  ini->getLineNum(), ini->getFilename().str(), token ));
		throw INI_INVALID_DATA;

	}

	// get the index to store the command at, and the command array itself
	const CommandButton **buttonArray = (const CommandButton **)store;
	Int buttonIndex = (Int)userData;

	// sanity
	DEBUG_ASSERTCRASH( buttonIndex < MAX_COMMANDS_PER_SET, ("parseCommandButton: button index '%d' out of range",
										 buttonIndex) );

	// save it
	buttonArray[ buttonIndex ] = commandButton;
	
	// TheSuperHackers @feature author 15/01/2025 Parse optional hotkey override as second token
	// Check if there's a second token (hotkey override)
	const char *hotkeyToken = ini->getNextTokenOrNull();
	if (hotkeyToken != NULL)
	{
		// Get the CommandSet instance to store the hotkey override
		CommandSet *commandSet = (CommandSet *)instance;
		
		// Extract just the character from KEY_X format (e.g., "KEY_Q" -> "Q") or use as-is (e.g., "Q" -> "Q")
		AsciiString hotkeyOverride = AsciiString(hotkeyToken);
		if (hotkeyOverride.startsWith("KEY_"))
		{
			hotkeyOverride = AsciiString(hotkeyOverride.str() + 4); // Skip "KEY_" prefix
		}
		// If it doesn't start with "KEY_", use it as-is (e.g., "Q" stays "Q")
		
		commandSet->m_hotkeyOverrides[buttonIndex].set(hotkeyOverride);
	}
	else
	{
		// No hotkey override provided, clear any existing override
		CommandSet *commandSet = (CommandSet *)instance;
		commandSet->m_hotkeyOverrides[buttonIndex].clear();
	}

}


//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
CommandSet::CommandSet(const AsciiString& name) :
	m_name(name),
	m_next(NULL)
{
	for( Int i = 0; i < MAX_COMMANDS_PER_SET; i++ )
	{
		m_command[ i ] = NULL;
		m_hotkeyOverrides[ i ].clear();
	}
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
const CommandButton* CommandSet::getCommandButton(Int i) const
{
	const CommandButton* button;
  // Check for TheGameLogic == null, cause it is in Worldbuilder, and wb gets command bar info. jba.
	if (TheGameLogic && TheGameLogic->findControlBarOverride(m_name, i, button))
		return button;

	return m_command[i];
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void CommandSet::friend_addToList(CommandSet** listHead)
{
	m_next = *listHead;
	*listHead = this;
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
CommandSet::~CommandSet( void )
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////
// ControlBar /////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
ControlBar::ControlBar( void )
{
	Int i;
	m_commandButtons = NULL;
	m_commandSets = NULL;
	m_controlBarSchemeManager = NULL;
	m_isObserverCommandBar = FALSE;
	m_observerLookAtPlayer = NULL;
	m_observedPlayer = NULL;
	m_buildToolTipLayout = NULL;
	m_showBuildToolTipLayout = FALSE;

	m_animateDownWin1Pos.x = m_animateDownWin1Pos.y = 0;
	m_animateDownWin1Size.x = m_animateDownWin1Size.y = 0;
	m_animateDownWin2Pos.x = m_animateDownWin2Pos.y = 0;
	m_animateDownWin2Size.x = m_animateDownWin2Size.y = 0;

	m_animateDownWindow = NULL;
	m_animTime = 0;

	for( i = 0; i < MAX_COMMANDS_PER_SET; i++)
	{
		m_commonCommands[i] = 0;
	}

	m_currContext = CB_CONTEXT_NONE;
	m_defaultControlBarPosition.x = m_defaultControlBarPosition.y = 0;
	m_genStarFlash = FALSE;
	m_genStarOff = NULL;
	m_genStarOn  = NULL;
	m_UIDirty    = FALSE;
	//	m_controlBarResizer = NULL;
	m_buildUpClockColor = GameMakeColor(0,0,0,100);
	m_commandBarBorderColor = GameMakeColor(0,0,0,100);
	for( i = 0; i < NUM_CONTEXT_PARENTS; i++ )
		m_contextParent[ i ] = NULL;
	for( i = 0; i < MAX_COMMANDS_PER_SET; i++ )
	{
		m_commandWindows[ i ] = NULL;
	// removed from multiplayer branch
		//m_commandMarkers[ i ] = NULL;
	}

	for( i = 0; i < MAX_PURCHASE_SCIENCE_RANK_1; i++ )
		m_sciencePurchaseWindowsRank1[i] = NULL;
	for( i = 0; i < MAX_PURCHASE_SCIENCE_RANK_3; i++ )
		m_sciencePurchaseWindowsRank3[i] = NULL;
	for( i = 0; i < MAX_PURCHASE_SCIENCE_RANK_8; i++ )
		m_sciencePurchaseWindowsRank8[i] = NULL;

	for( i = 0; i < MAX_SPECIAL_POWER_SHORTCUTS; i++ )
	{
		m_specialPowerShortcutButtons[i] = NULL;
		m_specialPowerShortcutButtonParents[i] = NULL;
	}

	m_specialPowerShortcutParent = NULL;
	m_specialPowerLayout = NULL;
	m_scienceLayout = NULL;
	m_rightHUDWindow = NULL;
	m_rightHUDCameoWindow = NULL;
	for( i = 0; i < MAX_RIGHT_HUD_UPGRADE_CAMEOS; i++ )
		m_rightHUDUpgradeCameos[i];
	m_rightHUDUnitSelectParent = NULL;
	m_communicatorButton = NULL;
	m_currentSelectedDrawable = NULL;
	m_currContext = CB_CONTEXT_NONE;
	m_rallyPointDrawableID = INVALID_DRAWABLE_ID;
	m_displayedConstructPercent = -1.0f;
	m_displayedOCLTimerSeconds = 0;
	m_displayedQueueCount = 0;
	resetBuildQueueData();
	resetContainData();
	m_lastRecordedInventoryCount = 0;

	m_videoManager = NULL;
	m_animateWindowManager = NULL;
	m_generalsScreenAnimate = NULL;
	m_animateWindowManagerForGenShortcuts = NULL;
	m_flash = FALSE;
	m_toggleButtonUpIn = NULL;
	m_toggleButtonUpOn = NULL;
	m_toggleButtonUpPushed = NULL;
	m_toggleButtonDownIn = NULL;
	m_toggleButtonDownOn = NULL;
	m_toggleButtonDownPushed = NULL;

	m_generalButtonEnable = NULL;
	m_generalButtonHighlight = NULL;
	m_genArrow = NULL;
	m_sideSelectAnimateDown = FALSE;
	updateCommanBarBorderColors(GAME_COLOR_UNDEFINED,GAME_COLOR_UNDEFINED,GAME_COLOR_UNDEFINED,GAME_COLOR_UNDEFINED);

	m_radarAttackGlowOn = FALSE;
	m_remainingRadarAttackGlowFrames = 0;
	m_radarAttackGlowWindow = NULL;

#if defined(RTS_DEBUG)
	m_lastFrameMarkedDirty = 0;
	m_consecutiveDirtyFrames = 0;
#endif

}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
ControlBar::~ControlBar( void )
{

	if(m_scienceLayout)
	{
		m_scienceLayout->destroyWindows();
		deleteInstance(m_scienceLayout);
		m_scienceLayout = NULL;
	}
	m_genArrow = NULL;

	delete m_videoManager;
	m_videoManager = NULL;

	delete m_animateWindowManagerForGenShortcuts;
	m_animateWindowManagerForGenShortcuts = NULL;

	delete m_animateWindowManager;
	m_animateWindowManager = NULL;

	delete m_generalsScreenAnimate;
	m_generalsScreenAnimate = NULL;

	delete m_controlBarSchemeManager;
	m_controlBarSchemeManager = NULL;

//	delete m_controlBarResizer;
//	m_controlBarResizer = NULL;

	// destroy all the command set definitions
	CommandSet *set;
	while( m_commandSets )
	{
		set = m_commandSets->friend_getNext();
		deleteInstance(m_commandSets);
		m_commandSets = set;

	}

	// destroy all our command button definitions
	CommandButton *button;
	while( m_commandButtons )
	{
		button = m_commandButtons->friend_getNext();
		deleteInstance(m_commandButtons);
		m_commandButtons = button;

	}
	if(m_buildToolTipLayout)
	{
		m_buildToolTipLayout->destroyWindows();
		deleteInstance(m_buildToolTipLayout);
		m_buildToolTipLayout = NULL;
	}

	if(m_specialPowerLayout)
	{
		m_specialPowerLayout->destroyWindows();
		deleteInstance(m_specialPowerLayout);
		m_specialPowerLayout = NULL;
	}

	m_radarAttackGlowWindow = NULL;

	if (m_rightHUDCameoWindow && m_rightHUDCameoWindow->winGetUserData())
	{
		delete m_rightHUDCameoWindow->winGetUserData();
		m_rightHUDCameoWindow->winSetUserData(NULL);
	}

}
void ControlBarPopupDescriptionUpdateFunc( WindowLayout *layout, void *param );

//-------------------------------------------------------------------------------------------------
/** Initialzie the control bar, this is our interface to the context sinsitive GUI */
//-------------------------------------------------------------------------------------------------
void ControlBar::init( void )
{
	INI ini;
	m_sideSelectAnimateDown = FALSE;
	// load the command buttons
	ini.loadFileDirectory( "Data\\INI\\Default\\CommandButton" , INI_LOAD_OVERWRITE, NULL );
	ini.loadFileDirectory( "Data\\INI\\CommandButton" , INI_LOAD_OVERWRITE, NULL );
	ini.loadDirectory(  "Data\\INI\\Object" ,  "CommandButton.ini" , INI_LOAD_MULTIFILE, NULL );
	// load the command sets
	ini.loadFileDirectory(  "Data\\INI\\CommandSet" , INI_LOAD_OVERWRITE, NULL );
	ini.loadDirectory(  "Data\\INI\\Object" ,  "CommandSet.ini", INI_LOAD_MULTIFILE, NULL );
	// post process step after loading the command buttons and command sets
	postProcessCommands();

	// Programmatic command buttons would be created here if needed

	// Init the scheme manager, this will call it's won INI init funciton.
	m_controlBarSchemeManager = NEW ControlBarSchemeManager;
	m_controlBarSchemeManager->init();

	//Added this check because the builder uses the ControlBar, but doesn't care about
	//the GUI.
	if( TheWindowManager )
	{
		//
		// the control bar has several windows that make up our context sensitive interface, we
		// want those parent windows so that we can easily hide and show them to make the
		// interface context sensitive
		//
		NameKeyType id;
		id = TheNameKeyGenerator->nameToKey( "ControlBar.wnd:ControlBarParent" );
		m_contextParent[ CP_MASTER ] = TheWindowManager->winGetWindowFromId( NULL, id );
	m_contextParent[ CP_MASTER ]->winGetPosition(&m_defaultControlBarPosition.x, &m_defaultControlBarPosition.y);

		m_scienceLayout = TheWindowManager->winCreateLayout("GeneralsExpPoints.wnd");
		m_scienceLayout->hide(TRUE);
		id = TheNameKeyGenerator->nameToKey( "GeneralsExpPoints.wnd:GenExpParent" );

		m_contextParent[ CP_PURCHASE_SCIENCE ] = TheWindowManager->winGetWindowFromId( NULL, id );//m_scienceLayout->getFirstWindow();

		id = TheNameKeyGenerator->nameToKey( "ControlBar.wnd:UnderConstructionWindow" );
		m_contextParent[ CP_UNDER_CONSTRUCTION ] = TheWindowManager->winGetWindowFromId( NULL, id );

		id = TheNameKeyGenerator->nameToKey( "ControlBar.wnd:OCLTimerWindow" );
		m_contextParent[ CP_OCL_TIMER ] = TheWindowManager->winGetWindowFromId( NULL, id );

		id = TheNameKeyGenerator->nameToKey( "ControlBar.wnd:BeaconWindow" );
		m_contextParent[ CP_BEACON ] = TheWindowManager->winGetWindowFromId( NULL, id );

		id = TheNameKeyGenerator->nameToKey( "ControlBar.wnd:CommandWindow" );
		m_contextParent[ CP_COMMAND ] = TheWindowManager->winGetWindowFromId( NULL, id );

		id = TheNameKeyGenerator->nameToKey( "ControlBar.wnd:ProductionQueueWindow" );
		m_contextParent[ CP_BUILD_QUEUE ] = TheWindowManager->winGetWindowFromId( NULL, id );

		id = TheNameKeyGenerator->nameToKey( "ControlBar.wnd:ObserverPlayerListWindow" );
		m_contextParent[ CP_OBSERVER_LIST ] = TheWindowManager->winGetWindowFromId( NULL, id );

		id = TheNameKeyGenerator->nameToKey( "ControlBar.wnd:ObserverPlayerInfoWindow" );
		m_contextParent[ CP_OBSERVER_INFO ] = TheWindowManager->winGetWindowFromId( NULL, id );


		// get the command windows and save for easy access later
		Int i;
		ICoord2D commandSize, commandPos;
		AsciiString windowName;
		for( i = 0; i < MAX_COMMANDS_PER_SET; i++ )
		{

			windowName.format( "ControlBar.wnd:ButtonCommand%02d", i + 1 );
			id = TheNameKeyGenerator->nameToKey( windowName.str() );
			m_commandWindows[ i ] =
				TheWindowManager->winGetWindowFromId( m_contextParent[ CP_COMMAND ], id );
			if (m_commandWindows[ i ])
			{
				m_commandWindows[ i ]->winGetPosition(&commandPos.x, &commandPos.y);
				m_commandWindows[ i ]->winGetSize(&commandSize.x, &commandSize.y);
				m_commandWindows[ i ]->winSetStatus( WIN_STATUS_USE_OVERLAY_STATES );
				// Enable right-click support for command buttons
				// TheSuperHackers @rightclick Ahmed Salah 27/06/2025 Enable right-click support for command buttons by setting WIN_STATUS_RIGHT_CLICK on both window and instance data
				m_commandWindows[ i ]->winSetStatus( WIN_STATUS_RIGHT_CLICK );
				// Also set it on the instance data since that's what the input handler checks
				WinInstanceData *instData = m_commandWindows[ i ]->winGetInstanceData();
				if (instData)
					instData->m_status |= WIN_STATUS_RIGHT_CLICK;
			}

	// removed from multiplayer branch
//			windowName.format( "ControlBar.wnd:CommandMarker%02d", i + 1 );
//			id = TheNameKeyGenerator->nameToKey( windowName.str() );
//			m_commandMarkers[ i ] =
//				TheWindowManager->winGetWindowFromId( m_contextParent[ CP_COMMAND ], id );
//			// set the size and position to make sure their in the same place as the buttons.
//			m_commandMarkers[i]->winSetPosition(commandPos.x -2, commandPos.y - 2);
//			m_commandMarkers[i]->winSetSize(commandSize.x + 2, commandSize.y + 2);



		}


		for( i = 0; i < MAX_PURCHASE_SCIENCE_RANK_1; i++ )
		{
			windowName.format( "GeneralsExpPoints.wnd:ButtonRank1Number%d", i );
			id = TheNameKeyGenerator->nameToKey( windowName.str() );
			m_sciencePurchaseWindowsRank1[ i ] =
				TheWindowManager->winGetWindowFromId( m_contextParent[ CP_PURCHASE_SCIENCE ], id );
			if (m_sciencePurchaseWindowsRank1[i] != nullptr) {
				m_sciencePurchaseWindowsRank1[i]->winSetStatus(WIN_STATUS_USE_OVERLAY_STATES);
			}
		}
		for( i = 0; i < MAX_PURCHASE_SCIENCE_RANK_3; i++ )
		{
			windowName.format( "GeneralsExpPoints.wnd:ButtonRank3Number%d", i );
			id = TheNameKeyGenerator->nameToKey( windowName.str() );
			m_sciencePurchaseWindowsRank3[ i ] =
				TheWindowManager->winGetWindowFromId( m_contextParent[ CP_PURCHASE_SCIENCE ], id );
			if (m_sciencePurchaseWindowsRank3[i] != nullptr) {
				m_sciencePurchaseWindowsRank3[i]->winSetStatus(WIN_STATUS_USE_OVERLAY_STATES);
			}
		}

		for( i = 0; i < MAX_PURCHASE_SCIENCE_RANK_8; i++ )
		{
			windowName.format( "GeneralsExpPoints.wnd:ButtonRank8Number%d", i );
			id = TheNameKeyGenerator->nameToKey( windowName.str() );
			m_sciencePurchaseWindowsRank8[ i ] =
				TheWindowManager->winGetWindowFromId( m_contextParent[ CP_PURCHASE_SCIENCE ], id );
			if (m_sciencePurchaseWindowsRank8[i] != nullptr) {
				m_sciencePurchaseWindowsRank8[i]->winSetStatus(WIN_STATUS_USE_OVERLAY_STATES);
			}
		}

		// keep a pointer to the window making up the right HUD display
		id = TheNameKeyGenerator->nameToKey( "ControlBar.wnd:RightHUD" );
		m_rightHUDWindow = TheWindowManager->winGetWindowFromId( NULL, id );

		id = TheNameKeyGenerator->nameToKey( "ControlBar.wnd:WinUnitSelected" );
		m_rightHUDUnitSelectParent = TheWindowManager->winGetWindowFromId( NULL, id );

		id = TheNameKeyGenerator->nameToKey( "ControlBar.wnd:CameoWindow" );
		m_rightHUDCameoWindow = TheWindowManager->winGetWindowFromId( NULL, id );
		for( i = 0; i < MAX_RIGHT_HUD_UPGRADE_CAMEOS; i++ )
		{
			windowName.format( "ControlBar.wnd:UnitUpgrade%d", i+1 );
			id = TheNameKeyGenerator->nameToKey( windowName.str() );
			m_rightHUDUpgradeCameos[ i ] =
				TheWindowManager->winGetWindowFromId( m_rightHUDWindow, id );
			if (m_rightHUDUpgradeCameos[i] != nullptr) {
				m_rightHUDUpgradeCameos[i]->winSetStatus(WIN_STATUS_USE_OVERLAY_STATES);
			}
		}

//		m_transitionHandler = NEW GameWindowTransitionsHandler;
//		m_transitionHandler->load();
//		m_transitionHandler->init();

		// don't forget about the communicator button CCB
		id = TheNameKeyGenerator->nameToKey( "ControlBar.wnd:PopupCommunicator" );
		m_communicatorButton = TheWindowManager->winGetWindowFromId( NULL, id );
		setControlCommand(m_communicatorButton, findCommandButton("NonCommand_Communicator") );
		m_communicatorButton->winSetTooltipFunc(commandButtonTooltip);

		GameWindow *win = TheWindowManager->winGetWindowFromId(NULL,TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonOptions"));
		if(win)
		{
			setControlCommand(win, findCommandButton("NonCommand_Options") );
			win->winSetTooltipFunc(commandButtonTooltip);
		}
		win = TheWindowManager->winGetWindowFromId(NULL,TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonIdleWorker"));
		if(win)
		{
			setControlCommand(win, findCommandButton("NonCommand_IdleWorker") );
			win->winSetTooltipFunc(commandButtonTooltip);
		}
		win = TheWindowManager->winGetWindowFromId(NULL,TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonPlaceBeacon"));
		if(win)
		{
			setControlCommand(win, findCommandButton("NonCommand_Beacon") );
			win->winSetTooltipFunc(commandButtonTooltip);
		}
		win = TheWindowManager->winGetWindowFromId(NULL,TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonGeneral"));
		if(win)
		{
			setControlCommand(win, findCommandButton("NonCommand_GeneralsExperience") );
			win->winSetTooltipFunc(commandButtonTooltip);
		}
		win = TheWindowManager->winGetWindowFromId(NULL,TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonLarge"));
		if(win)
		{
			setControlCommand(win, findCommandButton("NonCommand_UpDown") );
			win->winSetTooltipFunc(commandButtonTooltip);
		}

		win = TheWindowManager->winGetWindowFromId(NULL,TheNameKeyGenerator->nameToKey("ControlBar.wnd:PowerWindow"));
		if(win)
		{
			win->winSetTooltipFunc(commandButtonTooltip);
		}
		win = TheWindowManager->winGetWindowFromId(NULL,TheNameKeyGenerator->nameToKey("ControlBar.wnd:MoneyDisplay"));
		if(win)
		{
			win->winSetTooltipFunc(commandButtonTooltip);
		}
		win = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:GeneralsExp"));
		if(win)
		{
			win->winSetTooltipFunc(commandButtonTooltip);
		}

		m_radarAttackGlowWindow = TheWindowManager->winGetWindowFromId(NULL, TheNameKeyGenerator->nameToKey("ControlBar.wnd:WinUAttack"));


		win = TheWindowManager->winGetWindowFromId(NULL,TheNameKeyGenerator->nameToKey( "ControlBar.wnd:BackgroundMarker" ));
		win->winGetScreenPosition(&m_controlBarForegroundMarkerPos.x, &m_controlBarForegroundMarkerPos.y);
		win = TheWindowManager->winGetWindowFromId(NULL,TheNameKeyGenerator->nameToKey( "ControlBar.wnd:BackgroundMarker" ));
		win->winGetScreenPosition(&m_controlBarBackgroundMarkerPos.x,&m_controlBarBackgroundMarkerPos.y);

		if(!m_videoManager)
			m_videoManager = NEW WindowVideoManager;
		if(!m_animateWindowManager)
			m_animateWindowManager = NEW AnimateWindowManager;
		if(!m_generalsScreenAnimate)
			m_generalsScreenAnimate = NEW AnimateWindowManager;
		if(!m_animateWindowManagerForGenShortcuts)
			m_animateWindowManagerForGenShortcuts = NEW AnimateWindowManager;
		m_buildToolTipLayout = TheWindowManager->winCreateLayout( "ControlBarPopupDescription.wnd" );
		if(m_buildToolTipLayout)
		{
			m_buildToolTipLayout->hide(TRUE);
			m_buildToolTipLayout->setUpdate(ControlBarPopupDescriptionUpdateFunc);
		}

		m_genStarOn = TheMappedImageCollection ? (Image *)TheMappedImageCollection->findImageByName("BarButtonGenStarON") : NULL;
		m_genStarOff = TheMappedImageCollection ? (Image *)TheMappedImageCollection->findImageByName("BarButtonGenStarOFF") : NULL;
		m_genStarFlash = TRUE;
		m_lastFlashedAtPointValue = -1;

		m_rankVeteranIcon = TheMappedImageCollection ? TheMappedImageCollection->findImageByName( "SSChevron1L" ) : NULL;
		m_rankEliteIcon		= TheMappedImageCollection ? TheMappedImageCollection->findImageByName( "SSChevron2L" ) : NULL;
		m_rankHeroicIcon	= TheMappedImageCollection ? TheMappedImageCollection->findImageByName( "SSChevron3L" ) : NULL;


//		if(!m_controlBarResizer)
//			m_controlBarResizer = NEW ControlBarResizer;
//		m_controlBarResizer->init();



		// Initialize the Observer controls
		initObserverControls();

		// by default switch to the none context
		switchToContext( CB_CONTEXT_NONE, NULL );
	}

}

//-------------------------------------------------------------------------------------------------
/** Reset the context sensitive control bar GUI */
//-------------------------------------------------------------------------------------------------
void ControlBar::reset( void )
{
	hideSpecialPowerShortcut();
	// do not destroy the rally drawable, it will get destroyed with everythign else during a reset
	m_rallyPointDrawableID = INVALID_DRAWABLE_ID;
	if(m_radarAttackGlowWindow)
		m_radarAttackGlowWindow->winEnable(TRUE);
	m_radarAttackGlowOn = FALSE;
	m_remainingRadarAttackGlowFrames = 0;

	m_displayedConstructPercent = -1.0f;
	m_displayedOCLTimerSeconds = 0;

	m_isObserverCommandBar = FALSE; // reset us to use a normal command bar
	m_observerLookAtPlayer = NULL;
	m_observedPlayer = NULL;

	if(m_buildToolTipLayout)
		m_buildToolTipLayout->hide(TRUE);
	m_showBuildToolTipLayout = FALSE;

	if(m_animateWindowManager)
		m_animateWindowManager->reset();

	if(m_animateWindowManagerForGenShortcuts)
		m_animateWindowManagerForGenShortcuts->reset();

	if(m_generalsScreenAnimate)
		m_generalsScreenAnimate->reset();


	if(m_videoManager)
		m_videoManager->reset();

	// go back to default context
	switchToContext( CB_CONTEXT_NONE, NULL );
	m_sideSelectAnimateDown = FALSE;
	if(m_animateDownWindow)
	{
		TheWindowManager->winDestroy( m_animateDownWindow );
		m_animateDownWindow = NULL;
	}

	// Remove any overridden sets.
	CommandSet *set, *nextSet;
	set = m_commandSets;
	while (set) {
		Bool possibleAdjustment = FALSE;
		nextSet = set->friend_getNext();
		if (set == m_commandSets) {
			possibleAdjustment = TRUE;
		}

		Overridable *stillValid = set->deleteOverrides();
		if (stillValid == NULL && possibleAdjustment) {
			m_commandSets = nextSet;
		}

		set = nextSet;
	}

	// Remove any overridden command buttons.
	CommandButton *button, *nextButton;
	button = m_commandButtons;
	while (button) {
		Bool possibleAdjustment = FALSE;
		nextButton = button->friend_getNext();
		if (button == m_commandButtons) {
			possibleAdjustment = TRUE;
		}

		Overridable *stillValid = button->deleteOverrides();
		if (stillValid == NULL && possibleAdjustment) {
			m_commandButtons = nextButton;
		}

		button = nextButton;
	}
	if(TheTransitionHandler)
		TheTransitionHandler->remove("ControlBarArrow");
	m_genArrow = NULL;

	m_lastFlashedAtPointValue = -1;
	m_genStarFlash = TRUE;
}

//-------------------------------------------------------------------------------------------------
/** Update phase, we can track if our selected object is destroyed, update button
	* percentages, status, enabled status etc */
//-------------------------------------------------------------------------------------------------
void ControlBar::update( void )
{
	if (TheGlobalData->m_headless)
		return;
	getStarImage();
	updateRadarAttackGlow();
	if(m_controlBarSchemeManager)
		m_controlBarSchemeManager->update();

	// Update our video manager
	if( m_videoManager )
		m_videoManager->update();

	if (m_animateWindowManager)
		m_animateWindowManager->update();

	if (m_animateWindowManager)
		{
			if (m_animateWindowManager->isFinished() && m_animateWindowManager->isReversed())
			{
				Int id = (Int)TheNameKeyGenerator->nameToKey("ControlBar.wnd:ControlBarParent");
				GameWindow *window = TheWindowManager->winGetWindowFromId(NULL, id);
				if (window && !window->winIsHidden())
					window->winHide(TRUE);
			}
		}

	if(m_animateWindowManagerForGenShortcuts)
		m_animateWindowManagerForGenShortcuts->update();
	if (m_animateWindowManagerForGenShortcuts && m_specialPowerShortcutParent)
		{
			if (m_animateWindowManagerForGenShortcuts->isFinished() && m_animateWindowManagerForGenShortcuts->isReversed())
			{
				if (m_specialPowerShortcutParent && !m_specialPowerShortcutParent->winIsHidden())
					m_specialPowerShortcutParent->winHide(TRUE);
			}
		}



	if( !m_buildToolTipLayout->isHidden())
	{
		m_buildToolTipLayout->runUpdate();
		m_showBuildToolTipLayout = FALSE;
	}
/*
	else if( m_buildToolTipLayout )
	{
		hideBuildTooltipLayout();
	}*/

	updateSpecialPowerShortcut();
	// if we're an observer, don't do the complete update
	if( m_isObserverCommandBar)
	{
		if((TheGameLogic->getFrame() % (LOGICFRAMES_PER_SECOND/2)) == 0)
			populateObserverInfoWindow();

		Drawable *drawToEvaluateFor = NULL;
		if( TheInGameUI->getSelectCount() > 1 )
		{
			// Attempt to isolate a Drawable here to evaluate
			// The need arises when selected is an AngryMob,
			// whose selection actually consists of varied units
			// but is represented in the UI as a single unit,
			// so we must isolate and evaluate only the Nexus
			drawToEvaluateFor = TheGameClient->findDrawableByID( TheInGameUI->getSoloNexusSelectedDrawableID() ) ;
		}
		else // get the first and only drawble in the selection list
			// TheSuperHackers @fix Mauller 07/04/2025 The first access to this can return an empty list
			if (!TheInGameUI->getAllSelectedDrawables()->empty()) {
				drawToEvaluateFor = TheInGameUI->getAllSelectedDrawables()->front();
			}

		Object* obj = drawToEvaluateFor ? drawToEvaluateFor->getObject() : NULL;
		setPortraitByObject(obj);

		const Coord3D* exitPosition = NULL;
		if (obj && obj->getControllingPlayer() == getCurrentlyViewedPlayer() && obj->getObjectExitInterface())
			exitPosition = obj->getObjectExitInterface()->getRallyPoint();

		showRallyPoint(exitPosition);
		return;
	}


	// check flashing
	if( m_flash )
	{
		// go through all the command buttons to see which one needs to flash
		for( Int i = 0; i < MAX_COMMANDS_PER_SET; ++i )
		{
			GameWindow *button = m_commandWindows[ i ];
			if( button != NULL)
			{
				const CommandButton *commandButton = getCommandButtonFromUserData(button);
				if( commandButton != NULL )
				{
					if( commandButton->getFlashCount() > 0 && TheGameClient->getFrame() % 10 == 0 )
					{
						if( commandButton->getFlashCount() % 2 == 0 )
						{
							commandButton->setFlashCount(commandButton->getFlashCount() - 1);
							button->winSetStatus( WIN_STATUS_FLASHING );
						}
						else
						{
							commandButton->setFlashCount(commandButton->getFlashCount() - 1);
							button->winClearStatus( WIN_STATUS_FLASHING );
							if( commandButton->getFlashCount() == 0 )
							{
								setFlash( FALSE );
							}
						}
					}
				}
			}
		}
	}

	if(!m_contextParent[ CP_PURCHASE_SCIENCE ]->winIsHidden())
		updateContextPurchaseScience();

	//
	// first, if the UI is dirty repopulate the UI with what the user should see for all the
	// selected drawables
	//
	if( m_UIDirty )
	{
		evaluateContextUI();
		populateSpecialPowerShortcut(ThePlayerList->getLocalPlayer());
		// if we have a build tooltip layout, update it with the new data.
		repopulateBuildTooltipLayout();
	}

	// enable/disable the beacon button depending on if the max has been reached
	if (ThePlayerList && ThePlayerList->getLocalPlayer() && ThePlayerList->getLocalPlayer()->getPlayerTemplate())
	{
		Int count;
		const ThingTemplate *thing = TheThingFactory->findTemplate( ThePlayerList->getLocalPlayer()->getPlayerTemplate()->getBeaconTemplate() );
		ThePlayerList->getLocalPlayer()->countObjectsByThingTemplate( 1, &thing, false, &count );
		static NameKeyType beaconPlacementButtonID = NAMEKEY("ControlBar.wnd:ButtonPlaceBeacon");
		GameWindow *win = TheWindowManager->winGetWindowFromId(NULL, beaconPlacementButtonID);
		if (win)
		{
			if (count < TheMultiplayerSettings->getMaxBeaconsPerPlayer())
			{
				win->winEnable(TRUE);
			}
			else
			{
				win->winEnable(FALSE);
			}
		}
	}

	//
	// most control bar contexts have one selected thing that we switch on and update
	// based on if that thing changed in some way ... the exception is when multi selected
	//
	if( m_currContext == CB_CONTEXT_MULTI_SELECT )
	{

		updateContextMultiSelect();
		return;

	}

	// if nothing is selected get out of here except if we're in the Purchase science context... that requires
	// us to not have anything selected
	if( m_currentSelectedDrawable == NULL )
	{

		// we better be in the default none context
		DEBUG_ASSERTCRASH( m_currContext == CB_CONTEXT_NONE, ("ControlBar::update no selection, but not we're not showing the default NONE context") );
		return;

	}



	// if our selected drawable has no object get out of here
	Object *obj = NULL;
	if(m_currentSelectedDrawable)
		obj = m_currentSelectedDrawable->getObject();
	if( obj == NULL )
	{

		switchToContext( CB_CONTEXT_NONE, NULL );
		return;

	}

	switch( m_currContext )
	{

		//---------------------------------------------------------------------------------------------
		case CB_CONTEXT_NONE:
			break;

		//---------------------------------------------------------------------------------------------
		case CB_CONTEXT_COMMAND:
			updateContextCommand();
			break;

		//---------------------------------------------------------------------------------------------
		case CB_CONTEXT_STRUCTURE_INVENTORY:
			updateContextStructureInventory();
			break;

		//---------------------------------------------------------------------------------------------
		case CB_CONTEXT_BEACON:
			updateContextBeacon();
			break;

		//---------------------------------------------------------------------------------------------
		case CB_CONTEXT_UNDER_CONSTRUCTION:
			updateContextUnderConstruction();
			break;

		//---------------------------------------------------------------------------------------------
		case CB_CONTEXT_OCL_TIMER:
			updateContextOCLTimer();
			break;

	}



}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void ControlBar::onDrawableSelected( Drawable *draw )
{

	// set a dirty flag so next time we update we can reconstruct the UI
	markUIDirty();

	// cancel any pending GUI commands
	TheInGameUI->setGUICommand( NULL );


}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void ControlBar::onDrawableDeselected( Drawable *draw )
{

	// set a dirty flag so next time we update we can reconstruct the UI
	markUIDirty();

	if (TheInGameUI->getSelectCount() == 0)
	{
		// we just deselected everything - cancel any pending GUI commands
		TheInGameUI->setGUICommand( NULL );
	}

	//
	// always when becoming unselected should we remove any build placement icons because if
	// we have some and are in the middle of a build process, it must obiously be over now
	// because we are no longer selecting the dozer or worker
	//
	TheInGameUI->placeBuildAvailable( NULL, NULL );

}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
Bool ControlBar::isObjectSelected( const Object *obj ) const
{
	// TheSuperHackers @feature author 15/01/2025 Check if object is currently selected
	if (!obj || !m_currentSelectedDrawable)
		return FALSE;
	
	// Check if the currently selected drawable's object matches the given object
	const Object *selectedObj = m_currentSelectedDrawable->getObject();
	return (selectedObj == obj);
}

//-------------------------------------------------------------------------------------------------

const Image *ControlBar::getStarImage(void )
{
	if(m_lastFlashedAtPointValue > ThePlayerList->getLocalPlayer()->getSciencePurchasePoints() || ThePlayerList->getLocalPlayer()->getSciencePurchasePoints() <= 0)
		m_genStarFlash = FALSE;
	else
		m_lastFlashedAtPointValue = ThePlayerList->getLocalPlayer()->getSciencePurchasePoints();

	GameWindow *win= TheWindowManager->winGetWindowFromId( NULL, TheNameKeyGenerator->nameToKey( "ControlBar.wnd:ButtonGeneral" ) );
	if(!win)
		return NULL;
	if(!m_genStarFlash)
	{
		GadgetButtonSetEnabledImage(win, m_generalButtonEnable);
		return NULL;
	}

	if(TheGameLogic->getFrame()% LOGICFRAMES_PER_SECOND > LOGICFRAMES_PER_SECOND/2)
	{
		GadgetButtonSetEnabledImage(win, m_generalButtonHighlight);
		return NULL;
	}

	GadgetButtonSetEnabledImage(win, m_generalButtonEnable);

	return NULL;

}


//-------------------------------------------------------------------------------------------------
void ControlBar::onPlayerRankChanged(const Player *p)
{
	if (!p->isLocalPlayer())
		return;

	if(!(m_lastFlashedAtPointValue > ThePlayerList->getLocalPlayer()->getSciencePurchasePoints()))
	{
		if(TheTransitionHandler && TheInGameUI->getInputEnabled())
			TheTransitionHandler->setGroup("ControlBarArrow");
	}
//	populateSpecialPowerShortcut((Player *)p);
	m_genStarFlash = TRUE;
	/// @todo implement me
	markUIDirty();
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
void ControlBar::onPlayerSciencePurchasePointsChanged(const Player *p)
{
	if (!p->isLocalPlayer())
		return;
	if(!(m_lastFlashedAtPointValue > ThePlayerList->getLocalPlayer()->getSciencePurchasePoints()))
	{
		if(TheTransitionHandler && TheInGameUI->getInputEnabled())
			TheTransitionHandler->setGroup("ControlBarArrow");
	}
//	populateSpecialPowerShortcut((Player *)p);
	m_genStarFlash = TRUE;
	/// @todo implement me
	markUIDirty();
}

//-------------------------------------------------------------------------------------------------
/** Given the drawables that we have selected into our context sensitive UI, evaluate
	* and perform all UI manipulations to make the GUI show to the user what we want them
	* to see */
//-------------------------------------------------------------------------------------------------
void ControlBar::evaluateContextUI( void )
{

	//
	// the UI has been "evaluated" and is now displaying the most current and correct
	// information to the player
	//
	m_UIDirty = FALSE;

	// if our purchase science window is up, we will want to update it by repopulating it.
	if(!m_contextParent[ CP_PURCHASE_SCIENCE ]->winIsHidden())
		showPurchaseScience();

	// erase any current state of the GUI by switching out to the empty context
	switchToContext( CB_CONTEXT_NONE, NULL );

	// sanity, nothing selected
	if( TheInGameUI->getSelectCount() == 0 )
		return;

	// get the list of drawable IDs from the in game UI
	const DrawableList *selectedDrawables = TheInGameUI->getAllSelectedDrawables();

	// sanity
	if( selectedDrawables->empty() == TRUE )
		return;

	//Make sure the selected objects are in fact, controllable! If not, then
	//we don't show any GUI commands for them!!!
	//This is used when we select enemy objects or objects on another team.
	//@todo we may want to show their portrait
	if( !TheInGameUI->areSelectedObjectsControllable() )
	{
		//Also make sure the unit isn't a garrisonable neutral civ team building!
		Drawable *draw = selectedDrawables->front();

		//sanity
		if( !draw )
		{
			return;
		}
		Object *obj = draw->getObject();
		if( !obj )
		{
			return;
		}

		if (obj->getControllingPlayer()
			&& obj->getControllingPlayer()->getPlayerTemplate()
			&& obj->getControllingPlayer()->getPlayerTemplate()->getBeaconTemplate().compare(obj->getTemplate()->getName()) == 0
			)
		{
			switchToContext( CB_CONTEXT_BEACON, draw );
		}
		else
		{
			switchToContext( CB_CONTEXT_NONE, draw );
		}

		//Check for a contain interface and a enemy relationship and reject that!
		ContainModuleInterface *contain = obj->getContain();
		if( contain && contain->getContainMax() > 0 )
		{

			const Player *otherPlayer = contain->getApparentControllingPlayer(ThePlayerList->getLocalPlayer());
			if (!otherPlayer)
				otherPlayer = obj->getControllingPlayer();
			Player *player = ThePlayerList->getLocalPlayer();

			if( !player || !otherPlayer )
			{
				//Sanity.
				return;
			}
			Relationship relation = player->getRelationship( otherPlayer->getDefaultTeam() );

			//Note: All following checks already account for the fact that this object
			//isn't ours.

			//The only case we can actually see a non-controlled controlbar is a neutral garrisonable structure.
			if( !contain->isGarrisonable() || relation != NEUTRAL )
			{
				//Can't peek inside enemy/allied containers period!
				return;
			}
		}
		else
		{
			return;
		}
	}

	//
	// when we have multiple things selected, we will only display the common commands
	// in the center command bar that can be displayed with multi-units selected
	//


	Drawable *drawToEvaluateFor = NULL;
	Bool multiSelect = FALSE;


	if( TheInGameUI->getSelectCount() > 1 )
	{
		// Attempt to isolate a Drawable here to evaluate
		// The need arises when selected is an AngryMob,
		// whose selection actually consists of varied units
		// but is represented in the UI as a single unit,
		// so we must isolate and evaluate only the Nexus
		drawToEvaluateFor = TheGameClient->findDrawableByID( TheInGameUI->getSoloNexusSelectedDrawableID() ) ;
		multiSelect = ( drawToEvaluateFor == NULL );

	}
	else // get the first and only drawble in the selection list
		drawToEvaluateFor = selectedDrawables->front();



	if( multiSelect )
	{
		switchToContext( CB_CONTEXT_MULTI_SELECT, NULL );
	}
	else if ( drawToEvaluateFor )// either we have exactly one drawable, or we have isolated one to evaluate for...
	{

		// get the first and only drawble in the selection list
		//Drawable *draw = selectedDrawables->front();

		// sanity
		//if( draw == NULL )
		//	return;

		// get object
		Object *obj = drawToEvaluateFor->getObject();
		if( obj == NULL )
			return;

		// we show no interface for objects being sold
		if( obj->getStatusBits().test( OBJECT_STATUS_SOLD ) )
			return;

		static const NameKeyType key_OCLUpdate = NAMEKEY( "OCLUpdate" );
		OCLUpdate *update = (OCLUpdate*)obj->findUpdateModule( key_OCLUpdate );

		//
		// a command center is context sensitive itself, if a side has *NOT* been chosen we display
		// the side select interface for command centers only, but note how under construction is
		// more important than anything
		//
		Bool contextSelected = FALSE;
		if( obj->getStatusBits().test( OBJECT_STATUS_UNDER_CONSTRUCTION ) )
		{

			switchToContext( CB_CONTEXT_UNDER_CONSTRUCTION, drawToEvaluateFor );
			contextSelected = TRUE;

		}

		// check for a regular switch to the appropriate context
		if( contextSelected == FALSE )
		{
			ContainModuleInterface *cmi = obj->getContain();

			if( cmi && cmi->isGarrisonable() && obj->getCommandSetString().isEmpty() )
			{
				//Kris: This is a convenient section to graft an inventory commandset for
				//garrisoned troops. However, we only want to use this if we DON'T have
				//a commandset defined. If we do, then trust that the commandset will
				//handle it!

				Player *localPlayer = ThePlayerList->getLocalPlayer();
				Relationship relationship;

				// we cannot select objects that are controlled by our enemies
				relationship = localPlayer->getRelationship( obj->getTeam() );
				if( obj->isLocallyControlled() == TRUE || relationship == NEUTRAL )
					switchToContext( CB_CONTEXT_STRUCTURE_INVENTORY, drawToEvaluateFor );

			}
			else if( update )
			{
				switchToContext( CB_CONTEXT_OCL_TIMER, drawToEvaluateFor );
			}
			else if( obj->getCommandSetString().isEmpty() == FALSE )
			{

				switchToContext( CB_CONTEXT_COMMAND, drawToEvaluateFor );

			}
			else if (obj->getControllingPlayer()->getPlayerTemplate()->getBeaconTemplate().compare(obj->getTemplate()->getName()) == 0)
			{
				switchToContext( CB_CONTEXT_BEACON, drawToEvaluateFor );
			}
			else
				switchToContext( CB_CONTEXT_NONE, drawToEvaluateFor );
		}

	}

}

//-------------------------------------------------------------------------------------------------
/** Find a command button of the given name if present */
//-------------------------------------------------------------------------------------------------
CommandButton *ControlBar::findNonConstCommandButton( const AsciiString& name )
{

	for( const CommandButton *command = m_commandButtons; command; command = command->getNext() )
		if( command->getName() == name )
			return const_cast<CommandButton*>((const CommandButton*)command->getFinalOverride());

	return NULL;  // not found

}

//-------------------------------------------------------------------------------------------------
/** Allocate a new command button, assign name, and tie to list */
//-------------------------------------------------------------------------------------------------
CommandButton *ControlBar::newCommandButton( const AsciiString& name )
{
	CommandButton *newButton;

	// allocate new button
	newButton = newInstance(CommandButton);

	// assign name
	newButton->setName(name);

	// link to list
	newButton->friend_addToList(&m_commandButtons);

	// return the new button
	return newButton;

}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
CommandButton *ControlBar::newCommandButtonOverride( CommandButton *buttonToOverride )
{
	if (!buttonToOverride) {
		return NULL;
	}

	CommandButton *newOverride;

	// allocate new button
	newOverride = newInstance(CommandButton);

	*newOverride = *buttonToOverride;

	newOverride->markAsOverride();
	buttonToOverride->setNextOverride(newOverride);

	return newOverride;
}

//-------------------------------------------------------------------------------------------------
/** Parse a command set */
//-------------------------------------------------------------------------------------------------
 void ControlBar::parseCommandSetDefinition( INI *ini )
{
	AsciiString name;
	CommandSet *commandSet;

	// read the name
	const char* c = ini->getNextToken();
	name.set( c );

	// find existing item if present
	commandSet = TheControlBar->findNonConstCommandSet( name );
	if( commandSet == NULL )
	{

		// allocate a new item
		commandSet = TheControlBar->newCommandSet( name );
		if (ini->getLoadType() == INI_LOAD_CREATE_OVERRIDES) {
			commandSet->markAsOverride();
		}
	}
	else if( ini->getLoadType() != INI_LOAD_CREATE_OVERRIDES )
	{
		//Holy crap, this sucks to debug!!!
		//If you have two different command sets, the previous
		//code would simply allow you to define multiple command set
		//with the same name, and just nuke the old button with the new one.
		//So, I (KM) have added this assert to notify in case of two same-name
		//command set.
		DEBUG_CRASH(( "[LINE: %d in '%s'] Duplicate commandset %s found!", ini->getLineNum(), ini->getFilename().str(), name.str() ));
		throw INI_INVALID_DATA;

		//@todo SUPPORT OVERRIDES -- JM
	} else {
		commandSet = TheControlBar->newCommandSetOverride(commandSet);
	}

	// sanity
	DEBUG_ASSERTCRASH( commandSet, ("parseCommandSetDefinition: Unable to allocate set '%s'", name.str()) );

	// parse the ini definition
	ini->initFromINI( commandSet, commandSet->friend_getFieldParse() );

}

//-------------------------------------------------------------------------------------------------
/** Parse a command set extend definition */
//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature AhmedSalah 02/02/2025 CommandSetExtend - allow CommandSet templates to inherit from parent
void ControlBar::parseCommandSetExtendDefinition( INI *ini )
{
	const char* new_commandset_name = ini->getNextToken();
	
	const char* parent = ini->getNextToken();
	const CommandSet* parentCommandSet = TheControlBar->findCommandSet(parent);
	if (parentCommandSet == NULL) {
		DEBUG_CRASH(("CommandSetExtend must extend a previously defined CommandSet (%s).\n", parent));
		throw INI_INVALID_DATA;
	}

	// Check if command set already exists
	CommandSet* commandSet = TheControlBar->findNonConstCommandSet(new_commandset_name);
	if (commandSet)
	{
		if (ini->getLoadType() == INI_LOAD_CREATE_OVERRIDES)
			commandSet = TheControlBar->newCommandSetOverride(commandSet);
		else
		{
			DEBUG_CRASH(("CommandSet '%s' already exists, but OVERRIDE not specified", new_commandset_name));
			return;
		}
	}
	else
	{
		// Create new command set
		commandSet = TheControlBar->newCommandSet(new_commandset_name);
	}

	// Save the new command set's name and next pointer before copying
	AsciiString new_commandset_name_saved = commandSet->getName();
	CommandSet* new_commandset_next_saved = commandSet->friend_getNext();

	// Copy from parent command set
	(*commandSet) = (*parentCommandSet);

	// Restore the new command set's name and next pointer (should not be copied from parent)
	commandSet->friend_setName(new_commandset_name_saved);
	commandSet->friend_setNext(new_commandset_next_saved);

	// Reset override chain since this is not an override (unless it was explicitly marked)
	if (ini->getLoadType() != INI_LOAD_CREATE_OVERRIDES)
	{
		commandSet->setNextOverride(NULL);
	}

	// Parse the ini command set definition (allows all fields to be overridden)
	ini->initFromINI( commandSet, commandSet->friend_getFieldParse() );
}

//-------------------------------------------------------------------------------------------------
/** Find existing command set by name */
//-------------------------------------------------------------------------------------------------
CommandSet* ControlBar::findNonConstCommandSet( const AsciiString& name )
{
	CommandSet* set;

	for( set = m_commandSets; set != NULL; set = set->friend_getNext() )
		if( set->getName() == name )
			return const_cast<CommandSet*>((const CommandSet *) set);

	return NULL;  // set not found

}
//-------------------------------------------------------------------------------------------------
/** find existing command button if present	*/
//-------------------------------------------------------------------------------------------------
const CommandButton *ControlBar::findCommandButton( const AsciiString& name )
{
	CommandButton *btn =  findNonConstCommandButton(name);
	if( btn )
	{
		btn = (CommandButton *)btn->friend_getFinalOverride();
	}
	return btn;
}

//-------------------------------------------------------------------------------------------------
/** Find existing command set by name */
//-------------------------------------------------------------------------------------------------
const CommandSet *ControlBar::findCommandSet( const AsciiString& name )
{
	CommandSet *set = findNonConstCommandSet(name);
	if (set)
		set = (CommandSet*)set->friend_getFinalOverride();
	return set;
}

//-------------------------------------------------------------------------------------------------
/** Allocate a new command set, link to list, initialize to default, and return it */
//-------------------------------------------------------------------------------------------------
CommandSet *ControlBar::newCommandSet( const AsciiString& name )
{
	// allocate a new set
	CommandSet* set = newInstance(CommandSet)(name);
	// add it to the list.
	set->friend_addToList(&m_commandSets);
	// return the newly created set
	return set;

}

//-------------------------------------------------------------------------------------------------
/** Create an overridden command set. */
//-------------------------------------------------------------------------------------------------
CommandSet *ControlBar::newCommandSetOverride( CommandSet *setToOverride )
{
	if (!setToOverride) {
		return NULL;
	}

	// allocate a new set
	CommandSet* set = newInstance(CommandSet)(setToOverride->getName());

	// it's an override; DON'T add it to the main list.
	// !!! DO NOT DO THIS !!! -- > set->friend_addToList(&m_commandSets); <-- !!! DO NOT DO THIS !!!

	*set = *setToOverride;
	set->markAsOverride();

	setToOverride->setNextOverride(set);

	return set;
}

//-------------------------------------------------------------------------------------------------
/** Process a button click for the context sensitive GUI */
//-------------------------------------------------------------------------------------------------
CBCommandStatus ControlBar::processContextSensitiveButtonClick( GameWindow *button,
																																GadgetGameMessage gadgetMessage,
																																Bool ctrlPressed,
																																Bool altPressed,
																																Bool shiftPressed,
																																Bool isRightClick )
{

	// call command processing method
	return processCommandUI( button, gadgetMessage, ctrlPressed, altPressed, shiftPressed, isRightClick );

}

//-------------------------------------------------------------------------------------------------
/** Process a button click for the context sensitive GUI */
//-------------------------------------------------------------------------------------------------
CBCommandStatus ControlBar::processContextSensitiveButtonTransition( GameWindow *button,
																																GadgetGameMessage gadgetMessage )
{

	// call command processing method
	return processCommandTransitionUI( button, gadgetMessage );

}


//-------------------------------------------------------------------------------------------------
/** Switch the user interface to the new context specified and fill out any of the
	* art and/or buttons that we need to for the new context using data from the object
	* passed in */
//-------------------------------------------------------------------------------------------------
void ControlBar::switchToContext( ControlBarContext context, Drawable *draw )
{

	// restore the right hud to a plain window
	setPortraitByObject( NULL );

	Object *obj = draw ? draw->getObject() : NULL;
	setPortraitByObject( obj );

	// if we're switching context, we have to repopulate the hotkey manager
	if(TheHotKeyManager)
		TheHotKeyManager->reset();

	// ... and also remove any radius cursor that is active.
	TheInGameUI->setRadiusCursorNone();

	// save a pointer for the currently selected drawable
	m_currentSelectedDrawable = draw;

	if (IsInGameChatActive() == FALSE && TheGameLogic && !TheGameLogic->isInShellGame()) {
		TheWindowManager->winSetFocus( NULL );
	}

	// hide/un-hide the appropriate windows for the context
	switch( context )
	{

		//-------------------------------------------------------------------------------------------------
		case CB_CONTEXT_NONE:
		{

			// show or hide the right window groups
			//m_contextParent[ CP_PURCHASE_SCIENCE ]->winHide( TRUE );
			m_contextParent[ CP_COMMAND ]->winHide( TRUE );
			m_contextParent[ CP_BUILD_QUEUE ]->winHide( TRUE );
			m_contextParent[ CP_BEACON ]->winHide( TRUE );
			m_contextParent[ CP_UNDER_CONSTRUCTION ]->winHide( TRUE );
			m_contextParent[ CP_OCL_TIMER ]->winHide( TRUE );
			m_contextParent[ CP_OBSERVER_INFO ]->winHide( TRUE );
			m_contextParent[ CP_OBSERVER_LIST ]->winHide( TRUE );

			//Clear any potentially flashing buttons!
			for( int i = 0; i < MAX_COMMANDS_PER_SET; i++ )
			{
				// the implementation won't necessarily use the max number of windows possible
				if (m_commandWindows[ i ])
				{
					m_commandWindows[ i ]->winClearStatus( WIN_STATUS_FLASHING );
				}
			}
			// if there is a current selected drawable then we wil display a selection portrait if present
			if( draw )
			{
				//Get the current thing template.
				const ThingTemplate *thing = draw->getTemplate();

				//Special case -- if we are a GLA hole, then get the rebuild building template
				Object *obj = draw->getObject();
				if( obj && obj->isKindOf( KINDOF_REBUILD_HOLE ) )
				{
					RebuildHoleBehaviorInterface *rhbi = RebuildHoleBehavior::getRebuildHoleBehaviorInterfaceFromObject( obj );
					if( rhbi )
					{
						thing = rhbi->getRebuildTemplate();
					}
				}

				//Set the correct portrait.
				setPortraitByObject( obj );
			}

			// do not show any rally point marker
			showRallyPoint( NULL );

			break;

		}

		//---------------------------------------------------------------------------------------------
		case CB_CONTEXT_COMMAND:
		{

			// show or hide the right window groups
			//m_contextParent[ CP_PURCHASE_SCIENCE ]->winHide( TRUE );
			m_contextParent[ CP_COMMAND ]->winHide( FALSE );
			m_contextParent[ CP_BUILD_QUEUE ]->winHide( TRUE );
			m_contextParent[ CP_BEACON ]->winHide( TRUE );
			m_contextParent[ CP_UNDER_CONSTRUCTION ]->winHide( TRUE );
			m_contextParent[ CP_OCL_TIMER ]->winHide( TRUE );
			m_contextParent[ CP_OBSERVER_INFO ]->winHide( TRUE );
			m_contextParent[ CP_OBSERVER_LIST ]->winHide( TRUE );

			// fill the specific UI info
			populateCommand( draw->getObject() );

			//
			// for objects that are able to create units, we show a build queue if we actually
			// actually have something in production, otherwise we show the selection portrait
			//
			if( obj )
			{
				ProductionUpdateInterface *pu = obj->getProductionUpdateInterface();

				if( pu && pu->firstProduction() != NULL )
				{

					m_contextParent[ CP_BUILD_QUEUE ]->winHide( FALSE );
					populateBuildQueue( obj );
					setPortraitByObject( NULL );
				}
				else
				{
					setPortraitByObject( obj );
				}

			}

			break;

		}

		//---------------------------------------------------------------------------------------------
		case CB_CONTEXT_STRUCTURE_INVENTORY:
		{

			// show or hide the right window groups
			//m_contextParent[ CP_PURCHASE_SCIENCE ]->winHide( TRUE );
			m_contextParent[ CP_COMMAND ]->winHide( FALSE );
			m_contextParent[ CP_BUILD_QUEUE ]->winHide( TRUE );
			m_contextParent[ CP_BEACON ]->winHide( TRUE );
			m_contextParent[ CP_UNDER_CONSTRUCTION ]->winHide( TRUE );
			m_contextParent[ CP_OCL_TIMER ]->winHide( TRUE );
			m_contextParent[ CP_OBSERVER_INFO ]->winHide( TRUE );
			m_contextParent[ CP_OBSERVER_LIST ]->winHide( TRUE );

			// fill the specific UI info
			populateStructureInventory( draw->getObject() );

			break;

		}

		//---------------------------------------------------------------------------------------------
		case CB_CONTEXT_BEACON:
		{

			// show or hide the right window groups
			//m_contextParent[ CP_PURCHASE_SCIENCE ]->winHide( TRUE );
			m_contextParent[ CP_COMMAND ]->winHide( TRUE );
			m_contextParent[ CP_BUILD_QUEUE ]->winHide( TRUE );
			m_contextParent[ CP_BEACON ]->winHide( FALSE );
			m_contextParent[ CP_UNDER_CONSTRUCTION ]->winHide( TRUE );
			m_contextParent[ CP_OCL_TIMER ]->winHide( TRUE );
			m_contextParent[ CP_OBSERVER_INFO ]->winHide( TRUE );
			m_contextParent[ CP_OBSERVER_LIST ]->winHide( TRUE );


			// fill the specific UI info
			populateBeacon( draw->getObject() );

			break;

		}

		//---------------------------------------------------------------------------------------------
		case CB_CONTEXT_UNDER_CONSTRUCTION:
		{

			// show or hide the right window groups
			//m_contextParent[ CP_PURCHASE_SCIENCE ]->winHide( TRUE );
			m_contextParent[ CP_COMMAND ]->winHide( TRUE );
			m_contextParent[ CP_BUILD_QUEUE ]->winHide( TRUE );
			m_contextParent[ CP_BEACON ]->winHide( TRUE );
			m_contextParent[ CP_UNDER_CONSTRUCTION ]->winHide( FALSE );
			m_contextParent[ CP_OCL_TIMER ]->winHide( TRUE );
			m_contextParent[ CP_OBSERVER_INFO ]->winHide( TRUE );
			m_contextParent[ CP_OBSERVER_LIST ]->winHide( TRUE );

			// fill the specific UI info
			populateUnderConstruction( draw->getObject() );

			break;

		}

		//---------------------------------------------------------------------------------------------
		case CB_CONTEXT_OCL_TIMER:
		{

			// show or hide the right window groups
//			m_contextParent[ CP_PURCHASE_SCIENCE ]->winHide( TRUE );
			m_contextParent[ CP_COMMAND ]->winHide( TRUE );
			m_contextParent[ CP_BUILD_QUEUE ]->winHide( TRUE );
			m_contextParent[ CP_BEACON ]->winHide( TRUE );
			m_contextParent[ CP_UNDER_CONSTRUCTION ]->winHide( TRUE );
			m_contextParent[ CP_OCL_TIMER ]->winHide( FALSE );
			m_contextParent[ CP_OBSERVER_INFO ]->winHide( TRUE );
			m_contextParent[ CP_OBSERVER_LIST ]->winHide( TRUE );

			// fill the specific UI info
			populateOCLTimer( draw->getObject() );

			break;

		}

		//---------------------------------------------------------------------------------------------
		case CB_CONTEXT_MULTI_SELECT:
		{

			// show or hide the right window groups
//			m_contextParent[ CP_PURCHASE_SCIENCE ]->winHide( TRUE );
			m_contextParent[ CP_COMMAND ]->winHide( FALSE );		// multi select shows common commands
			m_contextParent[ CP_BUILD_QUEUE ]->winHide( TRUE );
			m_contextParent[ CP_BEACON ]->winHide( TRUE );
			m_contextParent[ CP_UNDER_CONSTRUCTION ]->winHide( TRUE );
			m_contextParent[ CP_OCL_TIMER ]->winHide( TRUE );
			m_contextParent[ CP_OBSERVER_INFO ]->winHide( TRUE );
			m_contextParent[ CP_OBSERVER_LIST ]->winHide( TRUE );


			// fill the specific UI info
			populateMultiSelect();

			break;

		}
		case CB_CONTEXT_OBSERVER_LIST:
		{

			// show or hide the right window groups
//			m_contextParent[ CP_PURCHASE_SCIENCE ]->winHide( TRUE );
			m_contextParent[ CP_COMMAND ]->winHide( TRUE );
			m_contextParent[ CP_BUILD_QUEUE ]->winHide( TRUE );
			m_contextParent[ CP_BEACON ]->winHide( TRUE );
			m_contextParent[ CP_UNDER_CONSTRUCTION ]->winHide( TRUE );
			m_contextParent[ CP_OCL_TIMER ]->winHide( TRUE );
			m_contextParent[ CP_OBSERVER_INFO ]->winHide( TRUE );
			m_contextParent[ CP_OBSERVER_LIST ]->winHide( FALSE );


			// fill the specific UI info
			populateObserverList();
			break;

		}

		//---------------------------------------------------------------------------------------------
		default:
		{

			DEBUG_ASSERTCRASH( 0, ("ControlBar::switchToContext, unknown context '%d'", context) );
			break;

		}

	}

	// save our context
	m_currContext = context;

}

void ControlBar::setCommandBarBorder( GameWindow *button, CommandButtonMappedBorderType type)
{
	if(!button)
		return;

	switch( type )
	{
		case COMMAND_BUTTON_BORDER_BUILD:
		{
			GadgetButtonSetBorder(button, m_commandButtonBorderBuildColor);
			break;
		}
		//-------------------------------------------------------------------------------------------------
		case COMMAND_BUTTON_BORDER_UPGRADE:
		{
			GadgetButtonSetBorder(button, m_commandButtonBorderUpgradeColor );
			break;
		}
		//-------------------------------------------------------------------------------------------------
		case COMMAND_BUTTON_BORDER_ACTION:
		{
			GadgetButtonSetBorder(button, m_commandButtonBorderActionColor);
			break;
		}
		//-------------------------------------------------------------------------------------------------
		case COMMAND_BUTTON_BORDER_SYSTEM:
		{
			GadgetButtonSetBorder(button, m_commandButtonBorderSystemColor);
			break;
		}

		//-------------------------------------------------------------------------------------------------
		case COMMAND_BUTTON_BORDER_NONE:
		default:
			GadgetButtonSetBorder(button, GAME_COLOR_UNDEFINED, FALSE);
	}
}

//-------------------------------------------------------------------------------------------------
/** Update hotkey in button label - replace existing &X or add if not present */
//-------------------------------------------------------------------------------------------------
AsciiString ControlBar::updateHotkeyInLabel(const AsciiString& originalLabel, const AsciiString& newKey)
{
	AsciiString result = originalLabel;
	
	// Find existing &X pattern and replace, or add if not present
	const char *str = result.str();
	Bool foundAmpersand = FALSE;
	
	// Search for &X pattern
	for (int i = 0; i < result.getLength() - 1; i++)
	{
		if (str[i] == '&')
		{
			// Found ampersand, replace the next character
			AsciiString before = AsciiString(str, i + 1);  // Everything up to and including &
			AsciiString after = AsciiString(str + i + 2); // Everything after the character to replace
			
			result = before;
			result.concat(newKey);
			result.concat(after);
			foundAmpersand = TRUE;
			break;
		}
	}
	
	// If no &X found, add &X at the end
	if (!foundAmpersand)
	{
		result.concat(" (&");
		result.concat(newKey);
		result.concat(")");
	}
	
	return result;
}

// TheSuperHackers @feature author 15/01/2025 Helper function to get CommandButton from user data
const CommandButton* ControlBar::getCommandButtonFromUserData(GameWindow* button)
{
	void* userData = GadgetButtonGetData(button);
	if (!userData)
		return NULL;
		
	// Return the CommandButton pointer directly
	return (const CommandButton*)userData;
}

//-------------------------------------------------------------------------------------------------
/** Set the command data into the control */
//-------------------------------------------------------------------------------------------------
void ControlBar::setControlCommand( GameWindow *button, const CommandButton *commandButton, const CommandSet *commandSet, Int buttonIndex )
{

	// the window must be a gadget button
	if( button->winGetInputFunc() != GadgetPushButtonInput )
	{

		DEBUG_ASSERTCRASH( 0, ("setControlCommand: Window is not a button") );
		return;

	}

	// sanity
	if( commandButton == NULL )
	{

		DEBUG_ASSERTCRASH( 0, ("setControlCommand: NULL commandButton passed in") );
		return;

	}

	// TheSuperHackers @feature author 15/01/2025 Clear button text before setting new command
	GadgetButtonSetText( button, UnicodeString( L"" ) );

	//
	// set the button gadget control to be a normal button or a check like button if
	// the command says it needs one
	//
	if( BitIsSet( commandButton->getOptions(), CHECK_LIKE ))
		GadgetButtonEnableCheckLike( button, TRUE, FALSE );
	else
		GadgetButtonEnableCheckLike( button, FALSE, FALSE );

	//
	// set the imagry ... note that for 99% of the command buttons it's sufficient to specify
	// only the disabled, enabled, hilite, and hilite pushed images.  For push-like buttons
	// we actually utilize all the state available to a GameWindow.  We will replicate the
	// hilite pushed image to be the enabled pushed image ... and we will also replicate
	// the disabled image to be the disabled pushed image.  For complete control over all
	// the states of these buttons we would add additional lines to the INI for a command
	// button and store those additional images in the command button
	//
	if( commandButton->getButtonImage() )
		GadgetButtonSetEnabledImage( button, commandButton->getButtonImage() );

	//if( commandButton->getDisabledImage() )
	//{
	//	GadgetButtonSetDisabledImage( button, commandButton->getDisabledImage() );
	//	GadgetButtonSetDisabledSelectedImage( button, commandButton->getDisabledImage() );
	//}  //end if
	//if( commandButton->getHiliteImage() )
	//	GadgetButtonSetHiliteImage( button, commandButton->getHiliteImage() );
	//if( commandButton->getPushedImage() )
	//{
	//	GadgetButtonSetHiliteSelectedImage( button, commandButton->getPushedImage() );
	//	GadgetButtonSetEnabledSelectedImage( button, commandButton->getPushedImage() );
	//}  // end if

	// set the text
	if( commandButton->getTextLabel().isEmpty() == FALSE || !commandButton->getScienceVec().empty())
	{
		button->winSetTooltipFunc(commandButtonTooltip);
	}
	else
		GadgetButtonSetText( button, L"" );

	// TheSuperHackers @feature author 15/01/2025 Add inventory count to button text for weapon commands
	if (commandButton->getCommandType() == GUI_COMMAND_FIRE_WEAPON || commandButton->getCommandType() == GUI_COMMAND_SWITCH_WEAPON)
	{
		// Get the current selected object to check its inventory
		Object* currentObj = NULL;
		if (m_currentSelectedDrawable)
			currentObj = m_currentSelectedDrawable->getObject();
		if (currentObj)
		{
			const Weapon* weapon = NULL;
			
			// Get the appropriate weapon based on command type
			if (commandButton->getCommandType() == GUI_COMMAND_FIRE_WEAPON) {
				weapon = currentObj->getCurrentWeapon();
			}
			else if (commandButton->getCommandType() == GUI_COMMAND_SWITCH_WEAPON) {
				weapon = currentObj->getWeaponInWeaponSlot(commandButton->getWeaponSlot());
			}
			
			if (weapon && weapon->getTemplate() && !weapon->getTemplate()->getConsumeInventory().isEmpty())
			{
				// Get inventory behavior using cached method
				InventoryBehavior* inventoryBehavior = currentObj->getInventoryBehavior();
				
				if (inventoryBehavior)
				{
					const AsciiString& consumeInventory = weapon->getTemplate()->getConsumeInventory();
					Int itemCount = inventoryBehavior->getItemCount(consumeInventory);					
					itemCount += weapon->getRemainingAmmoIncludingReload();
													
					// Get display name and max storage count from module data
					const InventoryBehaviorModuleData* moduleData = inventoryBehavior->getInventoryModuleData();
					if (moduleData) {
						const UnicodeString& displayName = moduleData->getDisplayName(consumeInventory);
						Int maxStorageCount = moduleData->getMaxStorageCount(consumeInventory);
						
						// Format text with display name and count (current/max)
						UnicodeString newText;
						newText.format(L"%s (%d/%d)", displayName.str(), itemCount, maxStorageCount);
						
						// Set the modified text
						GadgetButtonSetText(button, newText);
					}
				}
			}
			else
			{
				// TheSuperHackers @feature author 15/01/2025 Reset to original text if weapon doesn't consume inventory
				GadgetButtonSetText(button, L"");
			}
		}
	}

	// TheSuperHackers @feature author 15/01/2025 Add inventory count to button text for special power commands
	if (commandButton->getCommandType() == GUI_COMMAND_SPECIAL_POWER || 
		commandButton->getCommandType() == GUI_COMMAND_SPECIAL_POWER_FROM_SHORTCUT ||
		commandButton->getCommandType() == GUI_COMMAND_SPECIAL_POWER_CONSTRUCT ||
		commandButton->getCommandType() == GUI_COMMAND_SPECIAL_POWER_CONSTRUCT_FROM_SHORTCUT)
	{
		// Get the current selected object to check its inventory
		Object* currentObj = NULL;
		if (m_currentSelectedDrawable)
			currentObj = m_currentSelectedDrawable->getObject();
		if (currentObj)
		{
			const SpecialPowerTemplate* specialPowerTemplate = commandButton->getSpecialPowerTemplate();
			
			if (specialPowerTemplate && !specialPowerTemplate->getConsumeInventory().isEmpty())
			{
				// Get inventory behavior using cached method
				InventoryBehavior* inventoryBehavior = currentObj->getInventoryBehavior();
				
				if (inventoryBehavior)
				{
					const AsciiString& consumeInventory = specialPowerTemplate->getConsumeInventory();
					Int itemCount = currentObj->getTotalInventoryItemCount(consumeInventory);
					
					// Get display name and max storage count from module data
					const InventoryBehaviorModuleData* moduleData = inventoryBehavior->getInventoryModuleData();
					if (moduleData) {
						const UnicodeString& displayName = moduleData->getDisplayName(consumeInventory);
						Int maxStorageCount = moduleData->getMaxStorageCount(consumeInventory);
						
						// Format text with display name and count (current/max)
						UnicodeString newText;
						newText.format(L"%s (%d/%d)", displayName.str(), itemCount, maxStorageCount);
						
						// Set the modified text
						GadgetButtonSetText(button, newText);
					}
				}
			}
			else
			{
				// TheSuperHackers @feature author 15/01/2025 Reset to original text if special power doesn't consume inventory
				GadgetButtonSetText(button, L"");
			}
		}
	}

	// save the command in the user data of the window
	GadgetButtonSetData(button, (void*)commandButton);
	
	// TheSuperHackers @feature author 15/01/2025 Set hotkey override if present
	if (commandSet && buttonIndex >= 0 && commandSet->hasHotkeyOverride(buttonIndex))
	{
		AsciiString overrideKey = commandSet->getHotkeyOverride(buttonIndex);
		commandButton->setHotkeyOverride(overrideKey);
	}
	else
	{
		// Clear any existing override
		commandButton->clearHotkeyOverride();
	}

	setCommandBarBorder(button, commandButton->getCommandButtonMappedBorderType());

	if (TheHotKeyManager)
	{
		AsciiString hotKey;
		
		// Check if this CommandSet has a hotkey override for this button
		if (commandSet && buttonIndex >= 0 && commandSet->hasHotkeyOverride(buttonIndex))
		{
			hotKey = commandSet->getHotkeyOverride(buttonIndex);
			hotKey.toLower(); // HotKeyManager expects lowercase
		}
		else
		{
			// Use original CommandButton hotkey
			hotKey = TheHotKeyManager->searchHotKey(commandButton->getTextLabel());
		}
		
		if(hotKey.isNotEmpty())
			TheHotKeyManager->addHotKey(button, hotKey);
	}
	GadgetButtonSetAltSound(button, "GUICommandBarClick");

}

//-------------------------------------------------------------------------------------------------
void CommandButton::cacheButtonImage()
{
	if (!TheMappedImageCollection) {
		return;
	}
	if( m_buttonImageName.isNotEmpty() )
	{
		m_buttonImage = TheMappedImageCollection->findImageByName( m_buttonImageName );
		DEBUG_ASSERTCRASH( m_buttonImage, ("CommandButton: %s is looking for button image %s but can't find it. Skipping...", m_name.str(), m_buttonImageName.str() ) );
		m_buttonImageName.clear();	// we're done with this, so nuke it
	}
}

//-------------------------------------------------------------------------------------------------
/** post process step, after all commands and command sets are loaded */
//-------------------------------------------------------------------------------------------------
void ControlBar::postProcessCommands( void )
{
	for ( CommandButton *button = m_commandButtons; button; button = button->friend_getNext() )
	{
		button->cacheButtonImage();
	}
}

//-------------------------------------------------------------------------------------------------
/** set the command for the button identified by the window name
	* NOTE that parent may be NULL, it only helps to speed up the search for a particular
	* window ID */
//-------------------------------------------------------------------------------------------------
void ControlBar::setControlCommand( const AsciiString& buttonWindowName, GameWindow *parent,
																		const CommandButton *commandButton )
{
	UnsignedInt winID = TheNameKeyGenerator->nameToKey( buttonWindowName );
	GameWindow *win = TheWindowManager->winGetWindowFromId( parent, winID );

	if( win == NULL )
	{

		DEBUG_ASSERTCRASH( 0, ("setControlCommand: Unable to find window '%s'", buttonWindowName.str()) );
		return;

	}

	// call the workhorse
	setControlCommand( win, commandButton, NULL, -1 );

}

//-------------------------------------------------------------------------------------------------
/** show/hide the portrait window image */
//-------------------------------------------------------------------------------------------------
void ControlBar::setPortraitByImage( const Image *image )
{

	if( image )
	{
		m_rightHUDUnitSelectParent->winHide(FALSE);
		m_rightHUDCameoWindow->winSetEnabledImage( 0, image );
		//m_rightHUDWindow->winSetEnabledImage( 0, image );
		m_rightHUDWindow->winClearStatus( WIN_STATUS_IMAGE );
		m_rightHUDCameoWindow->winSetStatus( WIN_STATUS_IMAGE );
		for(Int i = 0; i < MAX_UPGRADE_CAMEO_UPGRADES; ++i)
			m_rightHUDUpgradeCameos[i]->winHide(TRUE);

	}
	else
	{
		m_rightHUDWindow->winSetStatus( WIN_STATUS_IMAGE );
		m_rightHUDCameoWindow->winClearStatus( WIN_STATUS_IMAGE );
		m_rightHUDUnitSelectParent->winHide(TRUE);
		for(Int i = 0; i < MAX_UPGRADE_CAMEO_UPGRADES; ++i)
			m_rightHUDUpgradeCameos[i]->winHide(TRUE);
		//m_rightHUDWindow->winSetEnabledImage( 0, image );
		//m_rightHUDWindow->winSetStatus( WIN_STATUS_IMAGE );

	}

}

//-------------------------------------------------------------------------------------------------
/** show/hide the portrait image by object.  We like to use this method as opposed to the
	* plain image one above so that we can build more intelligence into what portrait to
	* show for an object given its current state or object type */
//-------------------------------------------------------------------------------------------------
void ControlBar::setPortraitByObject( Object *obj )
{

	if( obj )
	{
		if( obj->isKindOf( KINDOF_SHOW_PORTRAIT_WHEN_CONTROLLED ) && !obj->isLocallyControlled() )
		{
			//Handles civ vehicles without terrorists in them
			setPortraitByObject( NULL );
			return;
		}

		const ThingTemplate *thing = obj->getTemplate();
		Player *player = obj->getControllingPlayer();

		//If we have an enemy stealth disguised unit, swap portraits!
		Drawable *draw = obj->getDrawable();
		if( draw && draw->getStealthLook() == STEALTHLOOK_DISGUISED_ENEMY )
		{
			thing = draw->getTemplate();
			if( thing->isKindOf( KINDOF_SHOW_PORTRAIT_WHEN_CONTROLLED ) )
			{
				//If a bomb truck disguises as a civ vehicle, don't use it's portrait (or else you'll see the terrorist).
				setPortraitByObject( NULL );
				return;
			}
      StealthUpdate *stealth = obj->getStealth();
			if( stealth && stealth->isDisguised() )
			{
				//Fake player upgrades too!
				player = ThePlayerList->getNthPlayer( stealth->getDisguisedPlayerIndex() );
			}
		}

		const Image* portrait = thing->getSelectedPortraitImage();

		m_rightHUDUnitSelectParent->winHide(FALSE);
		// enable the window window as an image window and set the image
		m_rightHUDCameoWindow->winSetEnabledImage( 0, portrait );

		//Display the veterancy rank of the object on the portrait.
		const Image *image = calculateVeterancyOverlayForObject( obj );
		GadgetButtonDrawOverlayImage( m_rightHUDCameoWindow, image );

		//m_rightHUDWindow->winSetEnabledImage( 0, portrait );
		m_rightHUDWindow->winClearStatus( WIN_STATUS_IMAGE );
		m_rightHUDCameoWindow->winSetStatus( WIN_STATUS_IMAGE );

		for(Int i = 0; i < MAX_UPGRADE_CAMEO_UPGRADES; ++i)
		{
			if (m_rightHUDUpgradeCameos[i] == nullptr)
				continue;

			AsciiString upgradeName = thing->getUpgradeCameoName(i);
			if(upgradeName.isEmpty())
			{
				m_rightHUDUpgradeCameos[i]->winHide(TRUE);
				continue;
			}
			const UpgradeTemplate *ut =  TheUpgradeCenter->findUpgrade(upgradeName);
			if(!ut)
			{
				m_rightHUDUpgradeCameos[i]->winHide(TRUE);
				continue;
			}

			m_rightHUDUpgradeCameos[i]->winHide(FALSE);
			m_rightHUDUpgradeCameos[i]->winSetEnabledImage( 0, ut->getButtonImage() );
			if( obj->hasUpgrade(ut) )
			{
				//Object level upgrades
				m_rightHUDUpgradeCameos[i]->winEnable( TRUE );
			}
			else if( player && player->hasUpgradeComplete( ut ) )
			{
				//Player level upgrades
				m_rightHUDUpgradeCameos[i]->winEnable( TRUE );
			}
			else
			{
				//Failure
				m_rightHUDUpgradeCameos[i]->winEnable( FALSE );
			}
		}


	}
	else
	{
		m_rightHUDUnitSelectParent->winHide(TRUE);
		m_rightHUDWindow->winSetStatus( WIN_STATUS_IMAGE );
		m_rightHUDCameoWindow->winClearStatus( WIN_STATUS_IMAGE );
		for(Int i = 0; i < MAX_UPGRADE_CAMEO_UPGRADES; ++i)
			if (m_rightHUDUpgradeCameos[i] != nullptr)
				m_rightHUDUpgradeCameos[i]->winHide(TRUE);

		//Clear any overlay the portrait had on it.
		GadgetButtonDrawOverlayImage( m_rightHUDCameoWindow, NULL );
		//TheSuperHackers @overlay Ahmed Salah 27/06/2025 Clear all overlay images when clearing portrait overlay
		GadgetButtonDrawOverlayImage2( m_rightHUDCameoWindow, NULL );
		GadgetButtonDrawOverlayImage3( m_rightHUDCameoWindow, NULL );
	}

}

// ------------------------------------------------------------------------------------------------
/** Show a rally point marker at the world location specified.  If no location is specified
	* any marker that we might have visible is hidden */
// ------------------------------------------------------------------------------------------------
void ControlBar::showRallyPoint(const Coord3D* loc)
{
	// if loc is NULL, destroy any rally point drawble we have shown
	if (loc == NULL)
	{
		// destroy rally point drawable if present
		if (m_rallyPointDrawableID != INVALID_DRAWABLE_ID)
			TheGameClient->destroyDrawable(TheGameClient->findDrawableByID(m_rallyPointDrawableID));

		m_rallyPointDrawableID = INVALID_DRAWABLE_ID;
		return;
	}

	Drawable* marker = NULL;

	// create a rally point drawble if necessary
	if (m_rallyPointDrawableID == INVALID_DRAWABLE_ID)
	{
		const ThingTemplate* ttn = TheThingFactory->findTemplate("RallyPointMarker");
		marker = TheThingFactory->newDrawable(ttn);
		DEBUG_ASSERTCRASH(marker, ("showRallyPoint: Unable to create rally point drawable"));
		if (marker)
		{
			marker->setDrawableStatus(DRAWABLE_STATUS_NO_SAVE);
			m_rallyPointDrawableID = marker->getID();
		}
	}
	else
		marker = TheGameClient->findDrawableByID(m_rallyPointDrawableID);

	// sanity
	DEBUG_ASSERTCRASH(marker, ("showRallyPoint: No rally point marker found"));

	// set the position of the rally point drawble to the position passed in
	marker->setPosition(loc);
	marker->setOrientation(TheGlobalData->m_downwindAngle); // To blow down wind -- ML

	// set the marker colors to that of the local player
	Player* player = getCurrentlyViewedPlayer();
	if (player)
	{
		if (TheGlobalData->m_timeOfDay == TIME_OF_DAY_NIGHT)
			marker->setIndicatorColor(player->getPlayerNightColor());
		else
			marker->setIndicatorColor(player->getPlayerColor());
	}
}

// ------------------------------------------------------------------------------------------------
/** Show a rally point marker at the world location specified.  If no location is specified
	* any marker that we might have visible is hidden */
// ------------------------------------------------------------------------------------------------
void ControlBar::setControlBarSchemeByPlayer(Player *p)
{
	if(m_controlBarSchemeManager)
		m_controlBarSchemeManager->setControlBarSchemeByPlayer(p);

	static NameKeyType buttonPlaceBeaconID = NAMEKEY( "ControlBar.wnd:ButtonPlaceBeacon" );
	static NameKeyType buttonIdleWorkerID = NAMEKEY("ControlBar.wnd:ButtonIdleWorker");
	static NameKeyType buttonGeneralID = NAMEKEY("ControlBar.wnd:ButtonGeneral");
	GameWindow *buttonPlaceBeacon = TheWindowManager->winGetWindowFromId( NULL, buttonPlaceBeaconID );
	GameWindow *buttonIdleWorker = TheWindowManager->winGetWindowFromId( NULL, buttonIdleWorkerID );
	GameWindow *buttonGeneral = TheWindowManager->winGetWindowFromId( NULL, buttonGeneralID );

	if( !p->isPlayerActive() )
	{
		m_isObserverCommandBar = TRUE;
		switchToContext( CB_CONTEXT_OBSERVER_LIST, NULL );
		DEBUG_LOG(("We're loading the Observer Command Bar"));

		if (buttonPlaceBeacon)
			buttonPlaceBeacon->winHide(TRUE);
		if (buttonIdleWorker)
			buttonIdleWorker->winHide(TRUE);
		if (buttonGeneral)
			buttonGeneral->winEnable(FALSE);
	}
	else
	{
		switchToContext( CB_CONTEXT_NONE, NULL );
		m_isObserverCommandBar = FALSE;

		if (buttonPlaceBeacon)
			buttonPlaceBeacon->winHide(
			(TheGameLogic->getGameMode() != GAME_LAN && TheGameLogic->getGameMode() != GAME_INTERNET) ||
			!TheGameInfo->isMultiPlayer());
		if (buttonIdleWorker)
			buttonIdleWorker->winHide(FALSE);
		if (buttonGeneral)
		{
			buttonGeneral->winHide(FALSE);
			buttonGeneral->winEnable(TRUE);
		}
	}
	switchControlBarStage(CONTROL_BAR_STAGE_DEFAULT);
}

void ControlBar::setControlBarSchemeByPlayerTemplate( const PlayerTemplate *pt)
{
	if(m_controlBarSchemeManager)
		m_controlBarSchemeManager->setControlBarSchemeByPlayerTemplate(pt);

	static NameKeyType buttonPlaceBeaconID = NAMEKEY( "ControlBar.wnd:ButtonPlaceBeacon" );
	static NameKeyType buttonIdleWorkerID = NAMEKEY("ControlBar.wnd:ButtonIdleWorker");
	static NameKeyType buttonGeneralID = NAMEKEY("ControlBar.wnd:ButtonGeneral");
	GameWindow *buttonPlaceBeacon = TheWindowManager->winGetWindowFromId( NULL, buttonPlaceBeaconID );
	GameWindow *buttonIdleWorker = TheWindowManager->winGetWindowFromId( NULL, buttonIdleWorkerID );
	GameWindow *buttonGeneral = TheWindowManager->winGetWindowFromId( NULL, buttonGeneralID );

	if(pt == ThePlayerTemplateStore->findPlayerTemplate(TheNameKeyGenerator->nameToKey("FactionObserver")))
	{
		m_isObserverCommandBar = TRUE;
		switchToContext( CB_CONTEXT_OBSERVER_LIST, NULL );
		DEBUG_LOG(("We're loading the Observer Command Bar"));

		if (buttonPlaceBeacon)
			buttonPlaceBeacon->winHide(TRUE);
		if (buttonIdleWorker)
			buttonIdleWorker->winHide(TRUE);
		if (buttonGeneral)
			buttonGeneral->winEnable(FALSE);
	}
	else
	{
		switchToContext( CB_CONTEXT_NONE, NULL );
		m_isObserverCommandBar = FALSE;

		if (buttonPlaceBeacon)
			buttonPlaceBeacon->winHide(
			(TheGameLogic->getGameMode() != GAME_LAN && TheGameLogic->getGameMode() != GAME_INTERNET) ||
			!TheGameInfo->isMultiPlayer());
		if (buttonIdleWorker)
			buttonIdleWorker->winHide(FALSE);
		if (buttonGeneral)
		{
			buttonGeneral->winHide(FALSE);
			buttonGeneral->winEnable(TRUE);
		}
	}
	switchControlBarStage(CONTROL_BAR_STAGE_DEFAULT);

	hidePurchaseScience();
}

void ControlBar::setControlBarSchemeByName(const AsciiString& name)
{
	if(m_controlBarSchemeManager)
		m_controlBarSchemeManager->setControlBarScheme( name );
		switchControlBarStage(CONTROL_BAR_STAGE_DEFAULT);

}

void ControlBar::preloadAssets( TimeOfDay timeOfDay )
{
	if (m_controlBarSchemeManager)
		m_controlBarSchemeManager->preloadAssets( timeOfDay );
}

void ControlBar::updateBuildQueueDisabledImages( const Image *image )
{
	if(!image)
		return;
	// We have to do this because the build queue data might have been reset
	static NameKeyType buildQueueIDs[ MAX_BUILD_QUEUE_BUTTONS ];
	static Bool idsInitialized = FALSE;
	Int i;

	// get name key ids for the build queue buttons
	if( idsInitialized == FALSE )
	{
		AsciiString buttonName;

		for( i = 0; i < MAX_BUILD_QUEUE_BUTTONS; i++ )
		{

			buttonName.format( "ControlBar.wnd:ButtonQueue%02d", i + 1 );
			buildQueueIDs[ i ] = TheNameKeyGenerator->nameToKey( buttonName );

		}

		idsInitialized = TRUE;

	}

	// get window pointers to all the buttons for the build queue
	for( i = 0; i < MAX_BUILD_QUEUE_BUTTONS; i++ )
	{

		// get window commented out cause I believe we already set this.  We'll see in a few minutes
		m_queueData[ i ].control = TheWindowManager->winGetWindowFromId( m_contextParent[ CP_BUILD_QUEUE ],
																																		 buildQueueIDs[ i ] );

		GadgetButtonSetDisabledImage( m_queueData[ i ].control, image );

	}

}

void ControlBar::updateRightHUDImage( const Image *image )
{
	if(!m_rightHUDWindow || !image)
		return;
	m_rightHUDWindow->winSetEnabledImage(0, image);

}

void ControlBar::updateBuildUpClockColor( Color color)
{
	m_buildUpClockColor = color;
}



void ControlBar::updateCommanBarBorderColors(Color build, Color action, Color upgrade, Color system )
{
	m_commandButtonBorderBuildColor = build;
	m_commandButtonBorderActionColor = action;
	m_commandButtonBorderUpgradeColor = upgrade;
	m_commandButtonBorderSystemColor = system;
}

// ---------------------------------------------------------------------------------------
// hides the communicator button
void ControlBar::hideCommunicator( Bool b )
{
	//sanity
	if( m_communicatorButton != NULL )
		m_communicatorButton->winHide( b );
}

// ---------------------------------------------------------------------------------------
// Outside hook so when the genera's head is pushed, we can switch to the purchase science
// context
void ControlBar::updatePurchaseScience( void )
{
//	if(m_generalsScreenAnimate && TheGlobalData->m_animateWindows)
//	{
//		Bool wasFinished = m_generalsScreenAnimate->isFinished();
//		m_generalsScreenAnimate->update();
//		if (m_generalsScreenAnimate->isFinished() && !wasFinished && m_generalsScreenAnimate->isReversed())
//			m_contextParent[ CP_PURCHASE_SCIENCE ]->winHide(TRUE);
//	}
}

void ControlBar::showPurchaseScience( void )
{

	if(TheScriptEngine->isGameEnding())
		return;
	populatePurchaseScience(ThePlayerList->getLocalPlayer());
	m_genStarFlash = FALSE;
	if(!m_contextParent[ CP_PURCHASE_SCIENCE ]->winIsHidden())
		return;
	//switchToContext(CB_CONTEXT_PURCHASE_SCIENCE, NULL);
	m_contextParent[ CP_PURCHASE_SCIENCE ]->winHide(FALSE);
	if (TheGlobalData->m_animateWindows)
		TheTransitionHandler->setGroup("GenExpFade");
		//m_generalsScreenAnimate->registerGameWindow( m_contextParent[ CP_PURCHASE_SCIENCE ], WIN_ANIMATION_SLIDE_TOP, TRUE, 200 );

}

void ControlBar::hidePurchaseScience( void )
{
	if(m_contextParent[ CP_PURCHASE_SCIENCE ]->winIsHidden())
		return;

	if( m_contextParent[ CP_PURCHASE_SCIENCE ] )
	{
		m_contextParent[ CP_PURCHASE_SCIENCE ]->winHide( TRUE );
	}
//	if (!TheGlobalData->m_animateWindows)
//		{
//			if( m_contextParent[ CP_PURCHASE_SCIENCE ] )
//			{
//				m_contextParent[ CP_PURCHASE_SCIENCE ]->winHide( TRUE );
//			}
//		}
//		else
//		{
//			//if (m_generalsScreenAnimate->isFinished())
//			if(TheTransitionHandler->isFinished())
//				TheTransitionHandler->reverse("GenExpFade");
//				//m_generalsScreenAnimate->reverseAnimateWindow();
//		}
}

void ControlBar::togglePurchaseScience( void )
{
	if(m_contextParent[ CP_PURCHASE_SCIENCE ]->winIsHidden())
		showPurchaseScience();
	else
		hidePurchaseScience();
}

void ControlBar::toggleControlBarStage( void )
{
	if(m_currentControlBarStage == CONTROL_BAR_STAGE_DEFAULT )
		switchControlBarStage(CONTROL_BAR_STAGE_LOW);
	else
		switchControlBarStage(CONTROL_BAR_STAGE_DEFAULT);
}

// Functions for repositioning/resizing the control bar
void ControlBar::switchControlBarStage( ControlBarStages stage )
{
	if(stage < CONTROL_BAR_STAGE_DEFAULT || stage >= MAX_CONTROL_BAR_STAGES)
		return;
	switch (stage) {
	case CONTROL_BAR_STAGE_DEFAULT:
		setDefaultControlBarConfig();
		break;
//	case CONTROL_BAR_STAGE_SQUISHED:
//		setSquishedControlBarConfig();
//		break;
	case CONTROL_BAR_STAGE_LOW:
		setLowControlBarConfig();
		break;
	case CONTROL_BAR_STAGE_HIDDEN:
		setHiddenControlBar();
		break;
	default:
		DEBUG_ASSERTCRASH(FALSE,("ControlBar::switchControlBarStage we were passed in a stage that's not supported %d", stage));
	}

}
void ControlBar::setDefaultControlBarConfig( void )
{
//	if(m_currentControlBarStage == CONTROL_BAR_STAGE_SQUISHED)
//	{
//		m_controlBarResizer->sizeWindowsDefault();
//		m_controlBarSchemeManager->setControlBarSchemeByPlayerTemplate(ThePlayerList->getLocalPlayer()->getPlayerTemplate(), FALSE);
//	}
	m_currentControlBarStage = CONTROL_BAR_STAGE_DEFAULT;
	setScaledViewportHeight();
	m_contextParent[ CP_MASTER ]->winSetPosition(m_defaultControlBarPosition.x, m_defaultControlBarPosition.y);
	m_contextParent[ CP_MASTER ]->winHide(FALSE);
	repopulateBuildTooltipLayout();
	setUpDownImages();

}

void ControlBar::setSquishedControlBarConfig( void )
{
	if(m_currentControlBarStage == CONTROL_BAR_STAGE_SQUISHED)
		return;
	m_currentControlBarStage = CONTROL_BAR_STAGE_SQUISHED;
	m_contextParent[ CP_MASTER ]->winSetPosition(m_defaultControlBarPosition.x, m_defaultControlBarPosition.y);

//	m_controlBarResizer->sizeWindowsAlt();
	repopulateBuildTooltipLayout();
	setFullViewportHeight();
	m_controlBarSchemeManager->setControlBarSchemeByPlayerTemplate(ThePlayerList->getLocalPlayer()->getPlayerTemplate(), TRUE);
}

void ControlBar::setLowControlBarConfig( void )
{
//	if(m_currentControlBarStage == CONTROL_BAR_STAGE_SQUISHED)
//	{
//		m_controlBarResizer->sizeWindowsDefault();
//		m_controlBarSchemeManager->setControlBarSchemeByPlayerTemplate(ThePlayerList->getLocalPlayer()->getPlayerTemplate(), FALSE);
//	}

	m_currentControlBarStage = CONTROL_BAR_STAGE_LOW;
	ICoord2D pos;
	pos.x = m_defaultControlBarPosition.x;
	pos.y = TheDisplay->getHeight() - .1 * TheDisplay->getHeight();
	setFullViewportHeight();
	m_contextParent[ CP_MASTER ]->winSetPosition(pos.x, pos.y);
	m_contextParent[ CP_MASTER ]->winHide(FALSE);
	setUpDownImages();

}

void ControlBar::setHiddenControlBar( void )
{
	m_currentControlBarStage = CONTROL_BAR_STAGE_HIDDEN;
	m_contextParent[ CP_MASTER ]->winHide(TRUE);
}
// removed from multiplayer test
//void ControlBar::showCommandMarkers( void )
//{
//	for(Int i =0; i < MAX_COMMANDS_PER_SET; ++i)
//	{
//		if(m_commandWindows[i]->winIsHidden())
//			m_commandMarkers[i]->winHide(FALSE);
//		else
//			m_commandMarkers[i]->winHide(TRUE);
//	}
//}
//
void ControlBar::updateCommandMarkerImage( const Image *image )
{
	// removed from multiplayer branch

//	// we don't mind if the image is null, that way we can not draw anything
	//	for(Int i =0; i < MAX_COMMANDS_PER_SET; ++i)
	//	{
	//		m_commandMarkers[i]->winSetEnabledImage(0, image);
	//	}

}
void ControlBar::updateSlotExitImage( const Image *image )
{
	//Hardcoding values here Not a good thing but there's no other way right now.
	if(!image)
		return;

	//Kris:
	//Other than this being a completely ridiculously retarded idea, I'm not inclined
	//to recode this in a better way, yikes! Btw, I DID NOT CODE THIS! But this is
	//what this does: The button images are overridden by a faction specific icon.
	//The proper way to fix this would be to make a commandbutton option and loop
	//through all buttons on init to replace the icon. We need a system like this
	//for neutral buildings which can have a different empty inventory icon based
	//on the faction player.

	CommandButton *cmdButton = findNonConstCommandButton( "Command_StructureExit" );
	if(cmdButton)
		cmdButton->setButtonImage(image);

	cmdButton = findNonConstCommandButton( "Command_TransportExit" );
	if(cmdButton)
		cmdButton->setButtonImage(image);

	cmdButton = findNonConstCommandButton( "Command_BunkerExit" );
	if(cmdButton)
		cmdButton->setButtonImage(image);

	cmdButton = findNonConstCommandButton( "Command_FireBaseExit" );
	if(cmdButton)
		cmdButton->setButtonImage(image);

}

void ControlBar::updateUpDownImages( const Image *toggleButtonUpIn, const Image *toggleButtonUpOn, const Image *toggleButtonUpPushed,
																		 const Image *toggleButtonDownIn, const Image *toggleButtonDownOn, const Image *toggleButtonDownPushed,
																		 const Image *generalButtonEnable, const Image *generalButtonHighlight  )
{
	m_toggleButtonUpIn = toggleButtonUpIn;
	m_toggleButtonUpOn = toggleButtonUpOn;
	m_toggleButtonUpPushed = toggleButtonUpPushed;
	m_toggleButtonDownIn = toggleButtonDownIn;
	m_toggleButtonDownOn = toggleButtonDownOn;
	m_toggleButtonDownPushed = toggleButtonDownPushed;


	m_generalButtonEnable = generalButtonEnable;
	m_generalButtonHighlight = generalButtonHighlight;

	setUpDownImages();
}

void ControlBar::setUpDownImages( void )
{
	GameWindow *win= TheWindowManager->winGetWindowFromId( NULL, TheNameKeyGenerator->nameToKey( "ControlBar.wnd:ButtonLarge" ) );
	if(!win)
		return;
	// we only care if it's in it's low state, else we put the default images up
	if(m_currentControlBarStage == CONTROL_BAR_STAGE_LOW)
	{
		GadgetButtonSetEnabledImage(win, m_toggleButtonUpOn);
		GadgetButtonSetHiliteImage(win, m_toggleButtonUpIn);
		GadgetButtonSetHiliteSelectedImage(win, m_toggleButtonUpPushed);
		return;
	}

	GadgetButtonSetEnabledImage(win, m_toggleButtonDownOn);
	GadgetButtonSetHiliteImage(win, m_toggleButtonDownIn);
	GadgetButtonSetHiliteSelectedImage(win, m_toggleButtonDownPushed);

}

void ControlBar::getForegroundMarkerPos(Int *x, Int *y)
{
	*x = m_controlBarForegroundMarkerPos.x;
	*y = m_controlBarForegroundMarkerPos.y;
}
void ControlBar::getBackgroundMarkerPos(Int *x, Int *y)
{
	*x = m_controlBarBackgroundMarkerPos.x;
	*y = m_controlBarBackgroundMarkerPos.y;
}

void ControlBar::drawTransitionHandler( void )
{
//	if(m_transitionHandler)
//		m_transitionHandler->draw();
}
enum{
	RADAR_ATTACK_GLOW_FRAMES = 150,
	RADAR_ATTACK_GLOW_NUM_TIMES = 15  ///< number of times we'll flash
};

void ControlBar::triggerRadarAttackGlow( void )
{
	if(!m_radarAttackGlowWindow)
		return;
	m_radarAttackGlowOn = TRUE;
	m_remainingRadarAttackGlowFrames = RADAR_ATTACK_GLOW_FRAMES;
	if(BitIsSet(m_radarAttackGlowWindow->winGetStatus(),WIN_STATUS_ENABLED) == TRUE)
		m_radarAttackGlowWindow->winEnable(FALSE);
}

void ControlBar::updateRadarAttackGlow ( void )
{
	if(!m_radarAttackGlowOn || !m_radarAttackGlowWindow)
		return;
	m_remainingRadarAttackGlowFrames--;
	if(m_remainingRadarAttackGlowFrames <= 0)
	{
		m_radarAttackGlowOn = FALSE;
		m_radarAttackGlowWindow->winEnable(TRUE);
		return;
	}

	if(m_remainingRadarAttackGlowFrames % RADAR_ATTACK_GLOW_NUM_TIMES == 0)
	{
		m_radarAttackGlowWindow->winEnable(!BitIsSet(m_radarAttackGlowWindow->winGetStatus(),WIN_STATUS_ENABLED));
	}


}
void ControlBar::initSpecialPowershortcutBar( Player *player)
{
	Int i = 0;
	for( ; i < MAX_SPECIAL_POWER_SHORTCUTS; ++i )
	{
		m_specialPowerShortcutButtonParents[i] = NULL;
		m_specialPowerShortcutButtons[i] = NULL;
	}

	if(m_specialPowerLayout)
	{
		m_specialPowerLayout->destroyWindows();
		deleteInstance(m_specialPowerLayout);
		m_specialPowerLayout = NULL;
	}
	m_specialPowerShortcutParent = NULL;
	m_currentlyUsedSpecialPowersButtons = 0;
	const PlayerTemplate *pt = player->getPlayerTemplate();

	if(!player || !pt|| !player->isLocalPlayer()
			|| pt->getSpecialPowerShortcutButtonCount() == 0
			|| pt->getSpecialPowerShortcutWinName().isEmpty()
			|| !player->isPlayerActive())
		return;
	m_currentlyUsedSpecialPowersButtons = pt->getSpecialPowerShortcutButtonCount();
	AsciiString layoutName, tempName, windowName, parentName;
	layoutName = pt->getSpecialPowerShortcutWinName();
	m_specialPowerLayout = TheWindowManager->winCreateLayout(layoutName);
	m_specialPowerLayout->hide(TRUE);

	tempName = layoutName;
	tempName.concat(":GenPowersShortcutBarParent");
	NameKeyType id = TheNameKeyGenerator->nameToKey( tempName );
	m_specialPowerShortcutParent = TheWindowManager->winGetWindowFromId( NULL, id );//m_scienceLayout->getFirstWindow();

	tempName = layoutName;
	tempName.concat(":ButtonCommand%d");
	parentName = layoutName;
	parentName.concat(":ButtonParent%d");
	m_currentlyUsedSpecialPowersButtons = MIN(pt->getSpecialPowerShortcutButtonCount(), MAX_SPECIAL_POWER_SHORTCUTS);
	for( i = 0; i < MAX_SPECIAL_POWER_SHORTCUTS; i++ )
	{
		windowName.format( tempName, i+1 );
		id = TheNameKeyGenerator->nameToKey( windowName.str() );
		m_specialPowerShortcutButtons[ i ] =
			TheWindowManager->winGetWindowFromId( m_specialPowerShortcutParent, id );

		if (m_specialPowerShortcutButtons[i] != nullptr) {

			m_specialPowerShortcutButtons[i]->winSetStatus(WIN_STATUS_USE_OVERLAY_STATES);
			// Oh god... this is a total hack for shortcut buttons to handle rendering text top left corner...
			m_specialPowerShortcutButtons[i]->winSetStatus(WIN_STATUS_SHORTCUT_BUTTON);

			windowName.format(parentName, i + 1);
			id = TheNameKeyGenerator->nameToKey(windowName.str());
			m_specialPowerShortcutButtonParents[i] =
				TheWindowManager->winGetWindowFromId(m_specialPowerShortcutParent, id);
		}
	}

}

void ControlBar::populateSpecialPowerShortcut( Player *player)
{
	const CommandSet *commandSet;
	Int i;
	if(!player || !player->getPlayerTemplate()
			|| !player->isLocalPlayer() || m_currentlyUsedSpecialPowersButtons == 0
			|| m_specialPowerShortcutButtons == NULL || m_specialPowerShortcutButtonParents == NULL)
		return;
	for( i = 0; i < MAX_SPECIAL_POWER_SHORTCUTS; ++i )
	{
		if (m_specialPowerShortcutButtons[i])
			m_specialPowerShortcutButtons[i]->winHide(TRUE);
		if (m_specialPowerShortcutButtonParents[i])
			m_specialPowerShortcutButtonParents[i]->winHide(TRUE);

	}

	// get command set
	if(player->getPlayerTemplate()->getSpecialPowerShortcutCommandSet().isEmpty() )
		return;
	commandSet = findCommandSet(player->getPlayerTemplate()->getSpecialPowerShortcutCommandSet()); // TEMP WILL CHANGE TO PROPER WAY ONCE WORKING
	if(!commandSet)
		return;
	// populate the button with commands defined
	Int currentButton = 0;
	const CommandButton *commandButton;
	for( i = 0; i < m_currentlyUsedSpecialPowersButtons; i++ )
	{

		// get command button
		commandButton = commandSet->getCommandButton(i);

		// if button is not present, just hide the window
		if( commandButton == NULL )
		{
			continue;
			// hide window on interface
			//m_specialPowerShortcutButtons[ i ]->winHide( TRUE );

		}
		else
		{

			if( BitIsSet( commandButton->getOptions(), NEED_UPGRADE ) )
			{
				const UpgradeTemplate *upgrade = commandButton->getUpgradeTemplate();
				if( upgrade && !ThePlayerList->getLocalPlayer()->hasUpgradeComplete( upgrade->getUpgradeMask() ) )
				{
					//Kris: 8/13/03 - Don't show shortcut buttons that require upgrades we don't have. As far as
					//I know, only the radar van scan has this. The MOAB is handled differently (sciences).
					continue;
				}
			}

			//
			// commands that require sciences we don't have are hidden so they never show up
			// cause we can never pick "another" general technology throughout the game
			//
			if( BitIsSet( commandButton->getOptions(), NEED_SPECIAL_POWER_SCIENCE ) )
			{
				const SpecialPowerTemplate *power = commandButton->getSpecialPowerTemplate();

				if( !power )
				{
					//Should have the power.. button is probably missing the SpecialPower = xxx entry.
					DEBUG_CRASH( ("CommandButton %s needs a SpecialPower entry, but it's either incorrect or missing.", commandButton->getName().str()) );
					continue;
				}

				//We just need to find something that has the power.
				Object *obj = ThePlayerList->getLocalPlayer()->findMostReadyShortcutSpecialPowerOfType( commandButton->getSpecialPowerTemplate()->getSpecialPowerType() );
				if( !obj )
				{
					continue;
				}

				if( power->getRequiredScience() != SCIENCE_INVALID )
				{
					if( player->hasScience( power->getRequiredScience() ) == FALSE )
					{
						//Hide the power
						//m_specialPowerShortcutButtons[ i ]->winHide( TRUE );
						continue;
					}
					else
					{
						//The player does have the special power! Now determine if the images require
						//enhancement based on upgraded versions. This is determined by the command
						//button specifying a vector of sciences in the command button.
						Int bestIndex = -1;
						ScienceType science;
						for( size_t scienceIndex = 0; scienceIndex < commandButton->getScienceVec().size(); ++scienceIndex )
						{
							science = commandButton->getScienceVec()[ scienceIndex ];

							//Keep going until we reach the end or don't have the required science!
							if( player->hasScience( science ) )
							{
								bestIndex = scienceIndex;
							}
							else
							{
								break;
							}
						}

						if( bestIndex != -1 )
						{
							//Now get the best sciencetype.
							science = commandButton->getScienceVec()[ bestIndex ];

							const CommandSet *commandSet1;
							const CommandSet *commandSet3;
							const CommandSet *commandSet8;
							Int i;

							// get command set
							if( !player || !player->getPlayerTemplate()
									|| player->getPlayerTemplate()->getPurchaseScienceCommandSetRank1().isEmpty()
									|| player->getPlayerTemplate()->getPurchaseScienceCommandSetRank3().isEmpty()
									|| player->getPlayerTemplate()->getPurchaseScienceCommandSetRank8().isEmpty() )
							{
								continue;
							}
							commandSet1 = findCommandSet( player->getPlayerTemplate()->getPurchaseScienceCommandSetRank1() );
							commandSet3 = findCommandSet( player->getPlayerTemplate()->getPurchaseScienceCommandSetRank3() );
							commandSet8 = findCommandSet( player->getPlayerTemplate()->getPurchaseScienceCommandSetRank8() );

							if( !commandSet1 || !commandSet3 || !commandSet8 )
							{
								continue;
							}

							Bool found = FALSE;
							for( i = 0; !found && i < MAX_PURCHASE_SCIENCE_RANK_1; i++ )
							{
								const CommandButton *command = commandSet1->getCommandButton( i );
								if( command && command->getCommandType() == GUI_COMMAND_PURCHASE_SCIENCE )
								{
									//All purchase sciences specify a single science.
									if( command->getScienceVec().empty() )
									{
										DEBUG_CRASH( ("Commandbutton %s is a purchase science button without any science! Please add it.", command->getName().str() ) );
									}
									else if( command->getScienceVec()[0] == science )
									{
										commandButton->copyImagesFrom( command, TRUE );
										commandButton->copyButtonTextFrom( command, TRUE, TRUE );
										found = TRUE;
										break;
									}
								}
							}
							for( i = 0; !found && i < MAX_PURCHASE_SCIENCE_RANK_3; i++ )
							{
								const CommandButton *command = commandSet3->getCommandButton( i );
								if( command && command->getCommandType() == GUI_COMMAND_PURCHASE_SCIENCE )
								{
									//All purchase sciences specify a single science.
									if( command->getScienceVec().empty() )
									{
										DEBUG_CRASH( ("Commandbutton %s is a purchase science button without any science! Please add it.", command->getName().str() ) );
									}
									else if( command->getScienceVec()[0] == science )
									{
										commandButton->copyImagesFrom( command, TRUE );
										commandButton->copyButtonTextFrom( command, TRUE, TRUE );
										found = TRUE;
										break;
									}
								}
							}
							for( i = 0; !found && i < MAX_PURCHASE_SCIENCE_RANK_8; i++ )
							{
								const CommandButton *command = commandSet8->getCommandButton( i );
								if( command && command->getCommandType() == GUI_COMMAND_PURCHASE_SCIENCE )
								{
									//All purchase sciences specify a single science.
									if( command->getScienceVec().empty() )
									{
										DEBUG_CRASH( ("Commandbutton %s is a purchase science button without any science! Please add it.", command->getName().str() ) );
									}
									else if( command->getScienceVec()[0] == science )
									{
										commandButton->copyImagesFrom( command, TRUE );
										commandButton->copyButtonTextFrom( command, TRUE, TRUE );
										found = TRUE;
										break;
									}
								}
							}
						}
					}
				}
			}
			else if( commandButton->getCommandType() == GUI_COMMAND_SELECT_ALL_UNITS_OF_TYPE )
			{
				//Make sure we actually have an object of type that we want to be able to select.
				Object *obj = ThePlayerList->getLocalPlayer()->findAnyExistingObjectWithThingTemplate( commandButton->getThingTemplate() );
				if( !obj )
				{
					continue;
				}
			}

			if (m_specialPowerShortcutButtons[currentButton] != nullptr) {
				// make sure the window is not hidden
				m_specialPowerShortcutButtons[currentButton]->winHide(FALSE);
				m_specialPowerShortcutButtonParents[currentButton]->winHide(FALSE);
				// enable by default
				m_specialPowerShortcutButtons[currentButton]->winEnable(TRUE);
				m_specialPowerShortcutButtonParents[currentButton]->winEnable(TRUE);

				// populate the visible button with data from the command button
				setControlCommand(m_specialPowerShortcutButtons[currentButton], commandButton, NULL, -1);
				GadgetButtonSetAltSound(m_specialPowerShortcutButtons[currentButton], "GUIGenShortcutClick");
			}
			currentButton++;

		}

	}
	if(m_contextParent[ CP_MASTER ] && !m_contextParent[ CP_MASTER ]->winIsHidden() && m_specialPowerShortcutParent->winIsHidden())
	{
		showSpecialPowerShortcut();
		animateSpecialPowerShortcut(TRUE);
	}
	updateSpecialPowerShortcut();
}

//-------------------------------------------------------------------------------------------------
Bool ControlBar::hasAnyShortcutSelection() const
{
	for( Int i = 0; i < m_currentlyUsedSpecialPowersButtons; i++ )
	{
		GameWindow *win;
		const CommandButton *command;

		win = m_specialPowerShortcutButtons[ i ];
		if( win == nullptr || win->winIsHidden() == TRUE )
			continue;

		// get the command from the control
		command = getCommandButtonFromUserData(win);
		if( !command )
			continue;

		if( command->getCommandType() == GUI_COMMAND_SELECT_ALL_UNITS_OF_TYPE )
		{
			//We found one, so we'll always show shortcuts!
			return TRUE;
		}
	}
	return FALSE;
}

//-------------------------------------------------------------------------------------------------
void ControlBar::updateSpecialPowerShortcut( void )
{
	if(!m_specialPowerShortcutParent || !m_specialPowerShortcutButtons
	   || !ThePlayerList || !ThePlayerList->getLocalPlayer())
		return;

	Bool hasShortcutSelectionButtons = hasAnyShortcutSelection();
	Bool hasAnyShortcutSpecialPower = ThePlayerList->getLocalPlayer()->hasAnyShortcutSpecialPower();

	Bool hasValidShortcutButton = hasShortcutSelectionButtons || hasAnyShortcutSpecialPower;

	if( hasValidShortcutButton
		  && m_specialPowerShortcutParent->winIsHidden()
			&& m_contextParent[ CP_MASTER ]
			&& !m_contextParent[ CP_MASTER ]->winIsHidden() )
	{
		showSpecialPowerShortcut();
		animateSpecialPowerShortcut(TRUE);
	}
	else if( !hasValidShortcutButton
					 && !m_specialPowerShortcutParent->winIsHidden()
					 && m_animateWindowManagerForGenShortcuts->isFinished() )
	{
		animateSpecialPowerShortcut(FALSE);
	}

	if(m_specialPowerShortcutParent->winIsHidden())
		return;

	if(!ThePlayerList->getLocalPlayer()->isPlayerActive())
	{
		hideSpecialPowerShortcut();
		return;
	}
	if(m_contextParent[ CP_MASTER ] && !m_contextParent[ CP_MASTER ]->winIsHidden() && m_specialPowerShortcutParent->winIsHidden())
		showSpecialPowerShortcut();

	for( Int i = 0; i < m_currentlyUsedSpecialPowersButtons; i++ )
	{
		GameWindow *win;
		const CommandButton *command;
		// get the window
		win = m_specialPowerShortcutButtons[ i ];

		if( win==nullptr || win->winIsHidden() == TRUE )
			continue;
		// get the command from the control
		command = getCommandButtonFromUserData(win);
		//command = (const CommandButton *)win->winGetUserData();
		if( command == NULL )
			continue;


		win->winClearStatus( WIN_STATUS_NOT_READY );
		win->winClearStatus( WIN_STATUS_ALWAYS_COLOR );


		// is the command available

		CommandAvailability availability = COMMAND_RESTRICTED;

		const SpecialPowerTemplate *spTemplate = command->getSpecialPowerTemplate();
		Object *obj = NULL;
		if( spTemplate )
		{
			obj = ThePlayerList->getLocalPlayer()->findMostReadyShortcutSpecialPowerOfType( command->getSpecialPowerTemplate()->getSpecialPowerType() );
			availability = getCommandAvailability( command, obj, win );
		}
		else if( command->getCommandType() == GUI_COMMAND_SELECT_ALL_UNITS_OF_TYPE )
		{
			availability = COMMAND_HIDDEN;
			Object *obj = ThePlayerList->getLocalPlayer()->findAnyExistingObjectWithThingTemplate( command->getThingTemplate() );
			if( obj )
			{
				//Make command available if it isn't a special power template shortcut power.
				availability = COMMAND_AVAILABLE;

				UnsignedInt mostReadyPercentage;
				obj = ThePlayerList->getLocalPlayer()->findMostReadyShortcutSpecialPowerForThing( command->getThingTemplate(), mostReadyPercentage );
				// TheSuperHackers @feature Ahmed Salah 27/06/2025 Check if select-all button should be enabled when special powers are available
				Bool enableButtonIfAnyPowerAvailable = BitIsSet(command->getOptions(), ENABLE_SELECT_ALL_BUTTON_IF_ANY_POWER_AVAILABLE) == false;
				if( obj  )
				{
					if (enableButtonIfAnyPowerAvailable)
					{
						availability = COMMAND_RESTRICTED;
						const CommandSet* commandSet = findCommandSet(obj->getCommandSetString());
						if (commandSet)
						{

							for (Int commandIndex = 0; commandIndex < MAX_COMMANDS_PER_SET; commandIndex++)
							{
								const CommandButton* evalButton = commandSet->getCommandButton(commandIndex);
								GameWindow* evalButtonWin = m_commandWindows[commandIndex];
								if (evalButton && evalButton->getCommandType() == GUI_COMMAND_SPECIAL_POWER)
								{
									//We want to evaluate the special powerbutton... but apply the clock overlay to our button!
									availability = getCommandAvailability(evalButton, obj, evalButtonWin, win);
									if (availability == COMMAND_AVAILABLE)
									{
										break;
									}
									
								}
							}
						}
					}
					else
					{
						//Ugh... hacky.
					//Look for a command button for a special power and if so, then get the command availability for it.
						const CommandSet* commandSet = TheControlBar->findCommandSet(obj->getCommandSetString());
						if (commandSet)
						{

							for (Int commandIndex = 0; commandIndex < MAX_COMMANDS_PER_SET; commandIndex++)
							{
								const CommandButton* evalButton = commandSet->getCommandButton(commandIndex);
								GameWindow* evalButtonWin = m_commandWindows[commandIndex];
								if (evalButton && evalButton->getCommandType() == GUI_COMMAND_SPECIAL_POWER)
								{
									//We want to evaluate the special powerbutton... but apply the clock overlay to our button!
									availability = getCommandAvailability(evalButton, obj, evalButtonWin, win);
									break;
								}
							}
						}
					}
					
				}
			}
		}

		// enable/disable the window control
		switch( availability )
		{
			case COMMAND_HIDDEN:
				win->winHide( TRUE );
				break;
			case COMMAND_RESTRICTED:
				win->winEnable( FALSE );
				break;
			case COMMAND_NOT_READY:
				win->winEnable( FALSE );
				win->winSetStatus( WIN_STATUS_NOT_READY );
				break;
			case COMMAND_CANT_AFFORD:
				win->winEnable( FALSE );
				win->winSetStatus( WIN_STATUS_ALWAYS_COLOR );
				break;
			default:
				win->winEnable( TRUE );
				break;
		}

	}
}

//-------------------------------------------------------------------------------------------------
void ControlBar::drawSpecialPowerShortcutMultiplierText()
{
	for( Int i = 0; i < m_currentlyUsedSpecialPowersButtons; i++ )
	{
		GameWindow *win;
		const CommandButton *command;
		// get the window
		win = m_specialPowerShortcutButtons[ i ];

		if( win == nullptr || win->winIsHidden() == TRUE )
			continue;
		// get the command from the control
		command = getCommandButtonFromUserData(win);
		//command = (const CommandButton *)win->winGetUserData();
		if( command == NULL )
			continue;

		//draw superweapon ready multipliers
		for( int i = 0; i < MAX_SPECIAL_POWER_SHORTCUTS; i++ )
		{
			if( !m_shortcutDisplayStrings[ i ] )
			{
				//m_shortcutDisplayStrings[ i ] = TheDisplayStringManager->newDisplayString();
				//m_shortcutDisplayStrings[ i ]->setFont( TheFontLibrary->getFont( "Arial", 16, false ) );
			}

			const SpecialPowerTemplate *spTemplate = command->getSpecialPowerTemplate();
			Int numReady = 0;
			if( spTemplate )
			{
				numReady = ThePlayerList->getLocalPlayer()->countReadyShortcutSpecialPowersOfType( spTemplate->getSpecialPowerType() );
			}
			if( numReady > 1 ) // Lorenzen changed... Displaying a "1" is superfluous
			{
				UnicodeString unibuffer;
				unibuffer.format( L"%d", numReady );

				GadgetButtonSetText( win, unibuffer );

				//m_shortcutDisplayStrings[ i ]->setText( unibuffer );
				//TheControlBar->m_shortcutDisplayStrings[ i ]->draw( 600, i * 40 + 40, GameMakeColor(255,255,255,255), GameMakeColor(0,0,0,0), 0, 0 );
			}
			else
			{
				UnicodeString unibuffer;
				GadgetButtonSetText( win, unibuffer );
				//TheDisplayStringManager->freeDisplayString( m_shortcutDisplayStrings[ i ] );
				//m_shortcutDisplayStrings[ i ] = NULL;
			}
		}
	}
}

void ControlBar::animateSpecialPowerShortcut( Bool isOn )
{
	if(!m_specialPowerShortcutParent || !m_animateWindowManagerForGenShortcuts || !m_currentlyUsedSpecialPowersButtons)
		return;
	Bool dontAnimate = TRUE;
	for( Int i = 0; i < m_currentlyUsedSpecialPowersButtons; ++i )
	{
		if (m_specialPowerShortcutButtons[i] && m_specialPowerShortcutButtons[i]->winGetUserData())
		{
			dontAnimate = FALSE;
			break;
		}
	}
	if(dontAnimate)
		return;

	if(isOn)
	{
		m_animateWindowManagerForGenShortcuts->reset();
		m_animateWindowManagerForGenShortcuts->registerGameWindow(m_specialPowerShortcutParent,WIN_ANIMATION_SLIDE_RIGHT,TRUE,500,0);
	}
	else
	{
		m_animateWindowManagerForGenShortcuts->reverseAnimateWindow();
	}
}

void ControlBar::showSpecialPowerShortcut( void )
{
	if(TheScriptEngine->isGameEnding() || !m_specialPowerShortcutParent
		||!m_specialPowerShortcutButtons || !ThePlayerList || !ThePlayerList->getLocalPlayer())
		return;
	Bool dontAnimate = TRUE;
	for( Int i = 0; i < m_currentlyUsedSpecialPowersButtons; ++i )
	{
		if (m_specialPowerShortcutButtons[i] == nullptr || m_specialPowerShortcutButtons[i]->winGetUserData())
		{
			dontAnimate = FALSE;
			break;
		}
	}
	if( dontAnimate || (!ThePlayerList->getLocalPlayer()->hasAnyShortcutSpecialPower() && !hasAnyShortcutSelection()) )
		return;
	m_specialPowerShortcutParent->winHide(FALSE);
	populateSpecialPowerShortcut(ThePlayerList->getLocalPlayer());

}

void ControlBar::hideSpecialPowerShortcut( void )
{
	if(!m_specialPowerShortcutParent)
		return;

	m_specialPowerShortcutParent->winHide(TRUE);

}

void ControlBar::setFullViewportHeight()
{
	TheTacticalView->setHeight(TheDisplay->getHeight());
}

void ControlBar::setScaledViewportHeight()
{
	TheTacticalView->setHeight(TheDisplay->getHeight() * TheGlobalData->m_viewportHeightScale);
}

//-------------------------------------------------------------------------------------------------
// TheSuperHackers @feature Ahmed Salah 28/10/2025 Parse TargetKindOf for RAID filtering
//-------------------------------------------------------------------------------------------------
void CommandButton::parseTargetKindOf( INI* ini, void *instance, void *store, const void *userData )
{
	CommandButton* self = (CommandButton*)instance;
	const char* token = ini->getNextToken();
	if (token == NULL)
		throw INI_INVALID_DATA;
	AsciiString kindStr(token);
	// Single KindOf token expected (e.g., INFANTRY). Use scanIndexList to map name to enum.
	KindOfType k = (KindOfType)INI::scanIndexList(kindStr.str(), KindOfMaskType::getBitNames());
	self->m_targetKindOfType = k;
}

