///-----------------------------------------------------------------
///
/// @file      JACCMain.h
/// @author    Alessandro
/// Created:   07/02/2011 19.40.58
/// @section   DESCRIPTION
///            JACCMain class declaration
///
///------------------------------------------------------------------

#ifndef __JACCMAIN_H__
#define __JACCMAIN_H__

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
#include <wx/timer.h>
#include <wx/menu.h>
#include <wx/stattext.h>
#include <wx/listbox.h>
#include <wx/panel.h>
////Header Include End

////Dialog Style Start
#undef JACCMain_STYLE
#define JACCMain_STYLE wxCAPTION | wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End


// My Headers

#include <stdlib.h>
#include <map>
#include <wx/socket.h>

class JACCFrm;
class JACCConv;

#include "JACCFrm.h"
#include "JACCConv.h"

class JACCMain : public wxFrame
{
    friend class JACCFrm;
    friend class JACCConv;
  
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		JACCMain(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("JACCMain"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = JACCMain_STYLE);
		virtual ~JACCMain();
		void Mnusubmenuitem41004Click(wxCommandEvent& event);
		void setNickUser(char *nick);
		void loadUserFriends();
		void WxListBox1DoubleClicked(wxCommandEvent& event);
		void takeFrame(JACCFrm *F) { fLogin = F; };
		void OnServerEvent(wxSocketEvent &);
		void OnSocketEvent(wxSocketEvent &);
		void WxPanel1UpdateUI(wxUpdateUIEvent& event);
		void Mnuexit1026Click(wxCommandEvent& event);
		void WxTimer1Timer(wxTimerEvent& event);
		
	private:
		//Do not add custom control declarations between
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxTimer *WxTimer1;
		wxMenuBar *WxMenuBar1;
		wxStaticText *WxStaticText5;
		wxStaticText *WxStaticText4;
		wxStaticText *WxStaticText2;
		wxStaticText *WxStaticText1;
		wxStaticText *WxStaticText3;
		wxListBox *WxListBox1;
		wxPanel *WxPanel2;
		wxPanel *WxPanel1;
		////GUI Control Declaration End
		wxImage *myImage;
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_WXTIMER1 = 1034,
			ID_MNU_MENUITEM1_1001 = 1001,
			ID_MNU_IMPOSTAZIONI_1033 = 1033,
			ID_MNU_EXIT_1026 = 1026,
			ID_MNU_PROFILO_1028 = 1028,
			ID_MNU_AMICI_1029 = 1029,
			ID_MNU_OPZIONI_1031 = 1031,
			ID_MNU_MENUITEM3_1003 = 1003,
			ID_MNU_SUBMENUITEM4_1004 = 1004,
			
			ID_WXSTATICTEXT5 = 1025,
			ID_WXSTATICTEXT4 = 1024,
			ID_WXSTATICTEXT2 = 1014,
			ID_WXSTATICTEXT1 = 1013,
			ID_WXSTATICTEXT3 = 1023,
			ID_WXLISTBOX1 = 1022,
			ID_WXPANEL2 = 1010,
			ID_WXPANEL1 = 1006,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
		
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();

		wxSocketServer *sockServer;
		wxIPV4address addr;
		
		JACCFrm *fLogin;
		
		JACCConv **convs;
		int n_conv;
};



#endif
