// *****************************************************************************
// Source code for the JHP_Links Add-On
// API Development Kit 22; Mac/Win
//
// Namespaces:			Contact person:
//		-None-
//
// [SG compatible] - Yes
// *****************************************************************************

#include "APIEnvir.h"

// ---------------------------------- Includes ---------------------------------

#include "ACAPinc.h" // also includes APIdefs.h
#include "JHP_LinksResIDs.hpp"

#include "BrowserPalette.hpp"

#include "JHP_Links.h"
using namespace JHP;

// ---------------------------------- Types ------------------------------------

// ---------------------------------- Variables --------------------------------

// -----------------------------------------------------------------------------

/* static void ShowInEmbeddedBrowser (const char* url)
{
	if (!BrowserPalette::HasInstance ())
			BrowserPalette::CreateInstance ();
		BrowserPalette::GetInstance ().Show ();
		BrowserPalette::GetInstance ().LoadURL (url);
} */

GSErrCode __ACENV_CALL MenuCommandHandler(const API_MenuParams *params)
{
	return ACAPI_CallUndoableCommand("JHP_Links Menu Command", [&]() -> GSErrCode {
		switch (params->menuItemRef.menuResID)
		{
		case JHPLINKS_MENU_STRINGSID:
		{
			//Look at JHP_Links.grc for ordering
			switch (params->menuItemRef.itemIndex)
			{
			case 1:
				Open(Links::DesignManual);
				break;

			case 2:
				Open(Links::FairHousing);
				break;

			case 3:
				Open(Links::CityOfDallas);
				break;

			case 4:
				Open(Links::OCEPlotwave);
				break;

			case 5:
				Open(Links::Dimensions101);
				break;

			case 6:
				Open(Links::IBC);
				break;

			case 7:
				Open(Links::UL);
				break;

			case 8:
				Open(Links::Slack);
				break;

			case 9:
				Open(Links::Github);
				break;

			case 10:
				Open(Links::Standards);
				break;

			case 11:
				Open(Links::Logos);
				break;

			case 12:
				Open(Links::AutoScript);
				break;
			}
		}
		}

		return NoError;
	});
}
// MenuCommandHandler

// =============================================================================
//
// Required functions
//
// =============================================================================

//------------------------------------------------------
// Dependency definitions
//------------------------------------------------------
API_AddonType __ACENV_CALL CheckEnvironment(API_EnvirParams *envir)
{
	RSGetIndString(&envir->addOnInfo.name, JHPLINKS_ABOUT_STRINGSID, 1, ACAPI_GetOwnResModule());
	RSGetIndString(&envir->addOnInfo.description, JHPLINKS_ABOUT_STRINGSID, 2, ACAPI_GetOwnResModule());

	return APIAddon_Normal;
	//return APIAddon_Preload; //!Change to APIAddon_Preload to allow listening for events!
}
// CheckEnvironment

//------------------------------------------------------
// Interface definitions
//------------------------------------------------------
GSErrCode __ACENV_CALL RegisterInterface(void)
{
	GSErrCode err = NoError;
	err = ACAPI_Register_Menu(JHPLINKS_MENU_STRINGSID, 0, MenuCode_UserDef, MenuFlag_Default);

	return NoError;
}
// RegisterInterface

// -----------------------------------------------------------------------------
// Initialize
//		called after the Add-On has been loaded into memory
// -----------------------------------------------------------------------------

GSErrCode __ACENV_CALL Initialize(void)
{
	GSErrCode err = ACAPI_Install_MenuHandler(JHPLINKS_MENU_STRINGSID, MenuCommandHandler);

	return err;
}
// Initialize

// -----------------------------------------------------------------------------
// FreeData
//		called when the Add-On is going to be unloaded
// -----------------------------------------------------------------------------

GSErrCode __ACENV_CALL FreeData(void)
{
	return NoError;
}
// FreeData
