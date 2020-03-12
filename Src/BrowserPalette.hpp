// *****************************************************************************
// Header file for BrowserPalette class
// API Development Kit 23; Mac/Win
//
// Namespaces:			Contact person:
//		-None-					API Support (archicadapi@graphisoft.com)
//
// [SG compatible] - Yes
// *****************************************************************************

#ifndef BROWSERPALETTE_HPP
#define BROWSERPALETTE_HPP

// ---------------------------------- Includes ---------------------------------

#include	"APIEnvir.h"
#include	"ACAPinc.h"		// also includes APIdefs.h
#include	"DGModule.hpp"
#include	"Lock.hpp"

// --- Class declaration: BrowserPalette ------------------------------------------

class BrowserPalette final : public DG::Palette,
							 public DG::PanelObserver
{
public:
	//enum SelectionModification { RemoveFromSelection, AddToSelection };

	struct ElementInfo {
		GS::UniString	guidStr;
		GS::UniString	typeName;
		GS::UniString	elemID;
	};

protected:
	enum {
		BrowserId = 1
	};

	DG::Browser		browser;

	virtual void PanelResized (const DG::PanelResizeEvent& ev) override;
	virtual	void PanelCloseRequested (const DG::PanelCloseRequestEvent& ev, bool* accepted) override;

	static GSErrCode __ACENV_CALL	PaletteControlCallBack (Int32 paletteId, API_PaletteMessageID messageID, GS::IntPtr param);

	static GS::Ref<BrowserPalette> instance;

	BrowserPalette ();

public:
	virtual ~BrowserPalette ();

	static bool				HasInstance ();
	static void				CreateInstance ();
	static BrowserPalette&	GetInstance ();
	
	void LoadURL (GS::UniString);
	void Show ();
	void Hide ();

	static GSErrCode				RegisterPaletteControlCallBack ();
};

#endif // BROWSERPALETTE_HPP
