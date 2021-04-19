#include	"ACAPinc.h"
#include    "shellapi.h"

namespace JHP
{
    enum LinkType
    {
        Web,
        File,
        Directory
    };

    struct Link
    {
        GS::UniString path;
        LinkType type;            
    };

    void Open (Link link)
    {
        switch (link.type)
        {
            case LinkType::File :
            case LinkType::Web :
                ShellExecute(NULL, "open", link.path.ToCStr(), NULL, NULL, SW_SHOWNORMAL);
                break;
            case LinkType::Directory :
                ShellExecute(NULL, "explore", link.path.ToCStr(), NULL, NULL, SW_SHOWNORMAL);
                break;
        }  
    }
        
    namespace Links
    {
        const struct Link DesignManual = { 
            "\"\\\\earth\\STANDARDS\\01 PLANNING AND DESIGN\\Design Manual\\150722_JHP Design Manual.pdf\"", 
            File 
        };

        const struct Link FairHousing = {
			 "\"\\\\earth\\LIBRARY\\Fair Housing\\Fair Housing Act Design Manual.pdf\"",
            File
        };

        const struct Link CityOfDallas = {
            "\"\\\\earth\\STANDARDS\\CAD\\Autodesk\\Tools\\source\\CoD Parking_Driveways_Handbook.pdf\"",
            File
        };

//        const struct Link OCEPlotwave = {
//            "\"\\\\earth\\STANDARDS\\CAD\\Autodesk\\Tools\\source\\Oce Plotwave 500.pdf\"",
//            File
//        };
//
        const struct Link Dimensions101 = {
            "\"\\\\earth\\STANDARDS\\05 GENERAL OFFICE\\JHP University\\Lectures\\Dimensioning A101\\Dimension 101.PDF\"",
            File
        };

		const struct Link ANSI = {
			"https://codes.iccsafe.org/content/icca117-12009",
			Web
		};

        const struct Link IBC = {
            "https://codes.iccsafe.org/content/IBC2018P2",
            Web
        };

        const struct Link UL = {
            "https://iq2.ulprospector.com/session/new?redirect=http%3a%2f%2fiq.ulprospector.com%2fen%2f",
            Web
        };

//        const struct Link Github = {
//            "https://github.com/jhparchitecture",
//            Web
//        };
//
//        const struct Link Slack = {
//            "https://jhp-architecture.slack.com/app_redirect?channel=CFC6P6355",
//            Web
//        };
//
        const struct Link Logos = {
            "\"\\\\earth\\MARKETING\\4 - Brand_Website\\Logos\"",
            Directory
        };

        const struct Link Standards = {
            "\"\\\\earth\\STANDARDS\\05 GENERAL OFFICE\\Office Standards and Best Practices\"",
            Directory
        };

		const struct Link AutoScript = {
			"\"\\\\earth\\STANDARDS\\CAD\\ArchiCAD\\Tools\\JHP_AutoScript.exe\"",
			File
		};

    }
}