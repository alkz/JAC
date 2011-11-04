///-----------------------------------------------------------------
///
/// @file      JACCFrm.h
/// @author    Alessandro
/// Created:   07/02/2011 17.49.35
/// @section   DESCRIPTION
///            JACCFrm class declaration
///
///------------------------------------------------------------------

#ifndef __JACCFRM_H__
#define __JACCFRM_H__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/frame.h>
#else
	#include <wx/wxprec.h>
#endif

//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/hyperlink.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
////Header Include End

////Dialog Style Start
#undef JACCFrm_STYLE
#define JACCFrm_STYLE wxCAPTION | wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End


// My Headers

#include "Config.h"

#include <windows.h>
#include <mysql/mysql.h>
#include <wx/url.h>
#include <wx/sstream.h>

#include "JACCMain.h"

#include "User.h"

class JACCFrm : public wxFrame
{
    friend class JACCMain;
    friend class JACCConv;
    
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		JACCFrm(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("JACC"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = JACCFrm_STYLE);
		virtual ~JACCFrm();
		void WxHyperLinkCtrl1HyperLink(wxHyperlinkEvent& event);
		
	private:
		//Do not add custom control declarations between
		//GUI Control Declaration Start and GUI Control Declaration End.
		void WxButton1Click0(wxCommandEvent& event);
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxHyperlinkCtrl *WxHyperLinkCtrl1;
		wxStaticText *WxStaticText1;
		wxStaticText *WxStaticText3;
		wxStaticText *WxStaticText4;
		wxButton *WxButton1;
		wxTextCtrl *WxEditPasw;
		wxTextCtrl *WxEditNick;
		wxPanel *WxPanel1;
		////GUI Control Declaration End
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_WXHYPERLINKCTRL1 = 1034,
			ID_WXSTATICTEXT1 = 1033,
			ID_WXSTATICTEXT3 = 1030,
			ID_WXSTATICTEXT4 = 1026,
			ID_WXBUTTON1 = 1022,
			ID_WXEDIT2 = 1028,
			ID_WXEDIT3 = 1024,
			ID_WXPANEL1 = 1001,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
		
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
		
		JACCMain *frameMain;
		
		User  *MyUser;
		MYSQL *sock;
		
		wxString getIP(void);
		void wxToCh(wxString, char *);
};

#endif
