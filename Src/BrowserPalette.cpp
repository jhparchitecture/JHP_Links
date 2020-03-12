// *****************************************************************************
// Source code for the Example Dialogs
// API Development Kit 23; Mac/Win
//
// Namespaces:			Contact person:
//		-None-					API Support (archicadapi@graphisoft.com)
//
// [SG compatible] - Yes
// *****************************************************************************

// ---------------------------------- Includes ---------------------------------

#include	"BrowserPalette.hpp"
#include	"Guard.hpp"

static const char*		siteURL = "http://www.google.com";
static const GS::Guid	paletteGuid ("{FEE27B6B-3873-4834-98B5-F0081AA4CD45}");
static const short		dialogResId = 32500;
static const short		menuResId = 32500;
//static const short		menuItemIndex = 0;

//GS::Array<BrowserPalette::ElementInfo>	BrowserPalette::selectedElements;
//GS::Lock								BrowserPalette::lockForSelectedElements;
GS::Ref<BrowserPalette>					BrowserPalette::instance;

// --- Class definition: BrowserPalette ----------------------------------------

BrowserPalette::BrowserPalette () :
	DG::Palette (ACAPI_GetOwnResModule (), dialogResId, ACAPI_GetOwnResModule (), paletteGuid),
	browser (GetReference (), BrowserId)
{
	Attach (*this);
	BeginEventProcessing();
}

BrowserPalette::~BrowserPalette ()
{
	EndEventProcessing ();
}

bool BrowserPalette::HasInstance ()
{
	return instance != nullptr;
}

void BrowserPalette::CreateInstance ()
{
	DBASSERT (!HasInstance ());
	instance = new BrowserPalette ();
	ACAPI_KeepInMemory (true);
}

BrowserPalette&	BrowserPalette::GetInstance ()
{
	DBASSERT (HasInstance ());
	return *instance;
}

void BrowserPalette::Show ()
{
	DG::Palette::Show ();
	//SetMenuItemCheckedState (true);
}

void BrowserPalette::Hide ()
{
	DG::Palette::Hide ();
	//SetMenuItemCheckedState (false);
}

void BrowserPalette::LoadURL (GS::UniString url)
{
	siteURL = url.ToCStr();
	browser.LoadURL (siteURL);
}

void BrowserPalette::PanelResized (const DG::PanelResizeEvent& ev)
{
	BeginMoveResizeItems ();
	browser.Resize (ev.GetHorizontalChange (), ev.GetVerticalChange ());
	EndMoveResizeItems ();
}

void BrowserPalette::PanelCloseRequested (const DG::PanelCloseRequestEvent&, bool* accepted)
{
	Hide ();
	*accepted = true;
}


GSErrCode __ACENV_CALL	BrowserPalette::PaletteControlCallBack (Int32, API_PaletteMessageID messageID, GS::IntPtr param)
{
	switch (messageID) {
		case APIPalMsg_OpenPalette:
			if (!HasInstance ())
				CreateInstance ();
			GetInstance ().Show ();
			break;

		case APIPalMsg_ClosePalette:
			if (!HasInstance ())
				break;
			GetInstance ().Hide ();
			break;

		case APIPalMsg_HidePalette_Begin:
			if (HasInstance () && GetInstance ().IsVisible ())
				GetInstance ().Hide ();
			break;

		case APIPalMsg_HidePalette_End:
			if (HasInstance () && !GetInstance ().IsVisible ())
				GetInstance ().Show ();
			break;

		case APIPalMsg_DisableItems_Begin:
			if (HasInstance () && GetInstance ().IsVisible ())
				GetInstance ().DisableItems ();
			break;

		case APIPalMsg_DisableItems_End:
			if (HasInstance () && GetInstance ().IsVisible ())
				GetInstance ().EnableItems ();
			break;

		case APIPalMsg_IsPaletteVisible:
			*(reinterpret_cast<bool*> (param)) = HasInstance () && GetInstance ().IsVisible ();
			break;

		default:
			break;
	}

	return NoError;
}

GSErrCode BrowserPalette::RegisterPaletteControlCallBack ()
{
	return ACAPI_RegisterModelessWindow (
					GS::GenerateHashValue (paletteGuid),
					PaletteControlCallBack,
					API_PalEnabled_FloorPlan + API_PalEnabled_Section + API_PalEnabled_Elevation +
					API_PalEnabled_InteriorElevation + API_PalEnabled_3D + API_PalEnabled_Detail +
					API_PalEnabled_Worksheet + API_PalEnabled_Layout + API_PalEnabled_DocumentFrom3D,
					GSGuid2APIGuid (paletteGuid));
}
