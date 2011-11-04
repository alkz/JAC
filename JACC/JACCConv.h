///-----------------------------------------------------------------
///
/// @file      JACCConv.h
/// @author    Alessandro
/// Created:   09/02/2011 1.15.15
/// @section   DESCRIPTION
///            JACCConv class declaration
///
///------------------------------------------------------------------

#ifndef __JACCCONV_H__
#define __JACCCONV_H__

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
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/panel.h>
////Header Include End

////Dialog Style Start
#undef JACCConv_STYLE
#define JACCConv_STYLE wxCAPTION | wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

//My Headers

#include <wx/socket.h>

#include "JACCFrm.h"
#include "JACCMain.h"

class JACCConv : public wxFrame
{
    friend class JACCMain;
    friend class JACCFrm;
    
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		JACCConv(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("JACC Conversation"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = JACCConv_STYLE);
		virtual ~JACCConv();
		void connectToDest(wxString);
		void WxEdit1Enter(wxCommandEvent& event);
		void WxEdit1ClickUrl(wxTextUrlEvent& event);
		void WxButton1Click(wxCommandEvent& event);
		void takeFrame(JACCMain *F) { fMain = F; }; 
		void takeFrame(JACCFrm *F)  { fLogin = F; };
		void SetClient(bool, wxSocketBase *);
		void OnClientEvent(wxSocketEvent &);
		void WxEdit1Enter0(wxCommandEvent& event);
		
	private:
		//Do not add custom control declarations between
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxTextCtrl *WxEdit1;
		wxTextCtrl *WxMemo1;
		wxButton *WxButton1;
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
			ID_WXEDIT1 = 1012,
			ID_WXMEMO1 = 1011,
			ID_WXBUTTON1 = 1008,
			ID_WXPANEL1 = 1001,
			////GUI Enum Control ID End

			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
		
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
		wxString dest;
		wxString client_connected;

		wxSocketBase *sockClient;
		wxIPV4address addr;
		bool client;
		
		JACCMain *fMain;
		JACCFrm *fLogin;
};

#endif
