///-----------------------------------------------------------------
///
/// @file      JACCConv.cpp
/// @author    Alessandro
/// Created:   09/02/2011 1.15.15
/// @section   DESCRIPTION
///            JACCConv class implementation
///
///------------------------------------------------------------------

#include "JACCConv.h"

//Do not add custom headers between
//Header Include Start and Header Include End
//wxDev-C++ designer will remove them
////Header Include Start
#include "Images/Self_JACCConv_XPM.xpm"
////Header Include End

//----------------------------------------------------------------------------
// JACCConv
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(JACCConv,wxFrame)
	////Manual Code Start
	EVT_SOCKET(CLIENT_ID, JACCConv::OnClientEvent)
	////Manual Code End
	
	EVT_CLOSE(JACCConv::OnClose)
	EVT_BUTTON(ID_WXBUTTON1,JACCConv::WxButton1Click)
END_EVENT_TABLE()
////Event Table End

JACCConv::JACCConv(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

JACCConv::~JACCConv()
{
}

void JACCConv::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	WxPanel1 = new wxPanel(this, ID_WXPANEL1, wxPoint(-8, 0), wxSize(420, 380));
	WxPanel1->SetBackgroundColour(wxColour(192,222,250));

	WxButton1 = new wxButton(WxPanel1, ID_WXBUTTON1, wxT("Send"), wxPoint(300, 344), wxSize(75, 20), 0, wxDefaultValidator, wxT("WxButton1"));
	WxButton1->Enable(false);

	WxMemo1 = new wxTextCtrl(WxPanel1, ID_WXMEMO1, wxEmptyString, wxPoint(30, 24), wxSize(360, 273), wxTE_MULTILINE, wxDefaultValidator, wxT("WxMemo1"));
	WxMemo1->SetMaxLength(0);
	WxMemo1->SetFocus();
	WxMemo1->SetInsertionPointEnd();

	WxEdit1 = new wxTextCtrl(WxPanel1, ID_WXEDIT1, wxT("Scrivi il tuo messaggio..."), wxPoint(45, 320), wxSize(330, 24), 0, wxDefaultValidator, wxT("WxEdit1"));
	WxEdit1->Enable(false);

	SetTitle(wxT("JACC Conversation"));
	SetIcon(Self_JACCConv_XPM);
	SetSize(8,8,420,408);
	Center();
	
	////GUI Items Creation End
	
}

void JACCConv::OnClose(wxCloseEvent& event)
{
    if(sockClient)
    {
        sockClient->Notify(false);
        sockClient->Destroy();
        sockClient = NULL;
    }
    fMain->n_conv += 1;
	Destroy();
}

void
JACCConv::connectToDest(wxString d)
{   
    dest = d;
    WxMemo1->AppendText("Connecting to " + dest + "...");
    char sql[255] = "SELECT nickname, IP, state FROM UsersOnLine WHERE nickname = '";
    
    
    strcat(sql, dest.c_str()); 
    strcat(sql, "';");
   
    mysql_query(fLogin->sock, sql);
    
    MYSQL_RES *res = mysql_store_result(fLogin->sock);
    MYSQL_ROW row;
    if(res) row = mysql_fetch_row(res);
    
    addr.Hostname((wxString)row[1]);
    addr.Service(CONNECT_PORT);
    
    wxSocketClient *sock = new wxSocketClient();
    
    /*char s[9];
    itoa((int)addr.Service(), s, 10);

    wxMessageBox("Mi connetto a: " + addr.Hostname() + ":" + (wxString)s, "yo");*/
    if(sock->Connect(addr))
    {
        WxMemo1->AppendText("Connected!\n\n");
        SetClient(true, sock); 
        WxEdit1->Enable();
        WxButton1->Enable();
    }
}

/*
 * WxButton1Click
 */
void JACCConv::WxButton1Click(wxCommandEvent& event)
{
    char tmp[SIZE_BUFFER] = "\0";
        
    strcat(tmp, fLogin->MyUser->nickname);
    strcat(tmp, ": ");
    strcat(tmp, WxEdit1->GetValue());
        
    sockClient->Write(tmp, SIZE_BUFFER); 
    WxMemo1->AppendText(wxString(tmp) + "\n");
}

void
JACCConv::OnClientEvent(wxSocketEvent &event)
{
    if (event.GetSocketEvent() == wxSOCKET_CONNECTION)
    { 
        wxSocketBase* sock = event.GetSocket();
        
        WxMemo1->AppendText("Connected!\n\n");
        SetClient(true, sock); 
        WxEdit1->Enable();
        WxButton1->Enable();
    } 
    
    if(event.GetSocketEvent() == wxSOCKET_INPUT)
    {
        char tmp[SIZE_BUFFER];
	    sockClient->Read(tmp, SIZE_BUFFER);
	        
	    WxMemo1->AppendText((wxString)tmp + "\n");  
    }
    
    if(event.GetSocketEvent() == wxSOCKET_LOST)
    {
        if(client)
            WxMemo1->AppendText("\n" + dest + " has disconnected");
        else
            WxMemo1->AppendText("\n" + client_connected + " has disconnected");
    }
}

void
JACCConv::SetClient(bool c, wxSocketBase *sock)
{
    client = c;
    sockClient = sock;
    
    sockClient->SetEventHandler(*this, CLIENT_ID);
    sockClient->SetNotify(wxSOCKET_INPUT_FLAG | wxSOCKET_LOST_FLAG);
    sockClient->Notify(true);
    
    char tmp[100];
    if(!client)
    {
	    sockClient->Read(tmp, sizeof(tmp));
	    WxMemo1->AppendText((wxString)tmp + "\n");
	    char *ye = strtok(tmp, " ");
	    client_connected = ye;
    }
    else
    {
        strcpy(tmp, fLogin->MyUser->nickname);
        strcat(tmp, " has connected\n");
        sockClient->Write(tmp, sizeof(tmp));  
    }	
}
