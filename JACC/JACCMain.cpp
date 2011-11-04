///-----------------------------------------------------------------
///
/// @file      JACCMain.cpp
/// @author    Alessandro
/// Created:   07/02/2011 19.40.58
/// @section   DESCRIPTION
///            JACCMain class implementation
///
///------------------------------------------------------------------

#include "JACCMain.h"

//DECLARE_EVENT_TYPE(wxEVT_CLIENT_CONNECTS)

//Do not add custom headers between
//Header Include Start and Header Include End
//wxDev-C++ designer will remove them
////Header Include Start
#include "Images/Self_JACCMain_XPM.xpm"
////Header Include End

//----------------------------------------------------------------------------
// JACCMain
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(JACCMain,wxFrame)
	////Manual Code Start
	EVT_SOCKET(SERVER_ID, JACCMain::OnServerEvent)
	////Manual Code End
	
	EVT_CLOSE(JACCMain::OnClose)
	EVT_TIMER(ID_WXTIMER1,JACCMain::WxTimer1Timer)
	EVT_MENU(ID_MNU_EXIT_1026, JACCMain::Mnuexit1026Click)
	EVT_MENU(ID_MNU_SUBMENUITEM4_1004, JACCMain::Mnusubmenuitem41004Click)
	
	EVT_LISTBOX_DCLICK(ID_WXLISTBOX1,JACCMain::WxListBox1DoubleClicked)
END_EVENT_TABLE()
////Event Table End


JACCMain::JACCMain(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style)
{
	CreateGUIControls();
	n_conv = 10;   // default value max conversations
	convs =      new JACCConv * [n_conv];
	
	for(int i = n_conv-1; i <= 0; i++) convs[i] = NULL;
	
	addr.Service(LISTEN_PORT);
	sockServer = new wxSocketServer(addr);
	sockServer->SetNotify(wxSOCKET_CONNECTION_FLAG);
	sockServer->SetEventHandler(*this, SERVER_ID);
	sockServer->Notify(true);
	WxTimer1->Start(60000);
}

JACCMain::~JACCMain()
{
}

void JACCMain::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	WxPanel1 = new wxPanel(this, ID_WXPANEL1, wxPoint(-3, -2), wxSize(300, 620));
	WxPanel1->SetBackgroundColour(wxColour(192,222,250));

	WxPanel2 = new wxPanel(WxPanel1, ID_WXPANEL2, wxPoint(16, 105), wxSize(260, 408));
	WxPanel2->SetBackgroundColour(wxColour(252,252,252));

	wxArrayString arrayStringFor_WxListBox1;
	WxListBox1 = new wxListBox(WxPanel2, ID_WXLISTBOX1, wxPoint(17, 24), wxSize(225, 361), arrayStringFor_WxListBox1, wxLB_SINGLE | wxLB_HSCROLL | wxLB_NEEDED_SB);

	WxStaticText3 = new wxStaticText(WxPanel2, ID_WXSTATICTEXT3, wxT("Your Friends:"), wxPoint(158, 5), wxDefaultSize, 0, wxT("WxStaticText3"));

	WxStaticText1 = new wxStaticText(WxPanel1, ID_WXSTATICTEXT1, wxT("Welcome, "), wxPoint(170, 75), wxDefaultSize, 0, wxT("WxStaticText1"));

	WxStaticText2 = new wxStaticText(WxPanel1, ID_WXSTATICTEXT2, wxT(""), wxPoint(225, 75), wxDefaultSize, 0, wxT("WxStaticText2"));

	WxStaticText4 = new wxStaticText(WxPanel1, ID_WXSTATICTEXT4, wxT("Just Another Chat Client"), wxPoint(30, 26), wxDefaultSize, 0, wxT("WxStaticText4"));
	WxStaticText4->SetFont(wxFont(12, wxSWISS, wxNORMAL, wxNORMAL, false, wxT("DejaVu Sans")));

	WxStaticText5 = new wxStaticText(WxPanel1, ID_WXSTATICTEXT5, wxT("v0.1"), wxPoint(203, 42), wxDefaultSize, 0, wxT("WxStaticText5"));

	WxMenuBar1 = new wxMenuBar();
	wxMenu *ID_MNU_MENUITEM1_1001_Mnu_Obj = new wxMenu(0);
	ID_MNU_MENUITEM1_1001_Mnu_Obj->Append(ID_MNU_IMPOSTAZIONI_1033, wxT("Impostazioni"), wxT(""), wxITEM_NORMAL);
	ID_MNU_MENUITEM1_1001_Mnu_Obj->Append(ID_MNU_EXIT_1026, wxT("Exit"), wxT(""), wxITEM_NORMAL);
	WxMenuBar1->Append(ID_MNU_MENUITEM1_1001_Mnu_Obj, wxT("File"));
	
	wxMenu *ID_MNU_PROFILO_1028_Mnu_Obj = new wxMenu(0);
	ID_MNU_PROFILO_1028_Mnu_Obj->Append(ID_MNU_AMICI_1029, wxT("Amici"), wxT(""), wxITEM_NORMAL);
	ID_MNU_PROFILO_1028_Mnu_Obj->Append(ID_MNU_OPZIONI_1031, wxT("Opzioni"), wxT(""), wxITEM_NORMAL);
	WxMenuBar1->Append(ID_MNU_PROFILO_1028_Mnu_Obj, wxT("Profilo"));
	
	wxMenu *ID_MNU_MENUITEM3_1003_Mnu_Obj = new wxMenu(0);
	ID_MNU_MENUITEM3_1003_Mnu_Obj->Append(ID_MNU_SUBMENUITEM4_1004, wxT("About"), wxT(""), wxITEM_NORMAL);
	WxMenuBar1->Append(ID_MNU_MENUITEM3_1003_Mnu_Obj, wxT("Altro"));
	SetMenuBar(WxMenuBar1);

	WxTimer1 = new wxTimer();
	WxTimer1->SetOwner(this, ID_WXTIMER1);

	SetTitle(wxT("JACC v0.1"));
	SetIcon(Self_JACCMain_XPM);
	SetSize(8,8,300,586);
	Center();
	
	////GUI Items Creation End
}

void JACCMain::OnClose(wxCloseEvent& event)
{   
    char sql[255] = "DELETE FROM UsersOnLine WHERE nickname = '";
    strcat(sql, fLogin->MyUser->nickname);
    strcat(sql, "';");
    
    mysql_query(fLogin->sock, sql);
    mysql_close(fLogin->sock);
    
    if(sockServer)
    {
        sockServer->Notify(false);
        sockServer->Destroy();
        sockServer = NULL;
    } 
     
	Destroy();
    delete fLogin;
	exit(0);
}

void
JACCMain::loadUserFriends()
{
    
    WxStaticText2->SetLabel((wxString)fLogin->MyUser->nickname);
    
    // Carico gli amici nella list box
    WxListBox1->Clear();
    char sql[255] = "SELECT * FROM UsersFriends WHERE (nick1 = '";
    strcat(sql, fLogin->MyUser->nickname);
    strcat(sql, "' OR nick2 = '");
    strcat(sql, fLogin->MyUser->nickname);
    strcat(sql, "');");
    mysql_query(fLogin->sock, sql);
    
    MYSQL_RES *res = mysql_store_result(fLogin->sock);
    if(res)
    {
        MYSQL_ROW row;
        while(row = mysql_fetch_row(res))
        {
            //Degli amici trovati seleziona quelli online
            char sql1[255] = "SELECT Users.nickname, Users.phrase, UsersOnLine.state FROM Users INNER JOIN UsersOnLine ON Users.nickname = UsersOnLine.nickname WHERE Users.nickname = '";
            
            if(strcmp(row[0], fLogin->MyUser->nickname) == 0)
                strcat(sql1, row[1]);
            else  
                strcat(sql1, row[0]);
                
            strcat(sql1, "';");
            mysql_query(fLogin->sock, sql1);  
               
            MYSQL_RES *res1 = mysql_store_result(fLogin->sock);
            
            if(res1) 
            {
                MYSQL_ROW row1 = mysql_fetch_row(res1);
                if(row1) WxListBox1->AppendString((wxString)row1[0] + "(" + (wxString)row1[2] + ") - " + (wxString)row1[1]);
            } 
            mysql_free_result(res1);   
        }
        
        mysql_free_result(res);
    }
}


/*
 * Mnusubmenuitem41004Click
 */
void JACCMain::Mnusubmenuitem41004Click(wxCommandEvent& event)
{
	wxMessageBox(" Just Another Chat Client(JACC) v0.1 \n\n Developed by Alessandro Carrara (alkz.0x80@gmail.com)", "About");
}


/*
 * WxListBox1DoubleClicked
 */
void JACCMain::WxListBox1DoubleClicked(wxCommandEvent& event)
{
	convs[n_conv] = new JACCConv(NULL);
    convs[n_conv]->takeFrame(this);
	convs[n_conv]->takeFrame(fLogin);
	convs[n_conv]->Show();
	char *tmp = new char[(WxListBox1->GetStringSelection()).Length()+1];
	fLogin->wxToCh(WxListBox1->GetStringSelection(), tmp);
    char *dest = strtok(tmp, "(");
	convs[n_conv]->connectToDest((wxString)dest);
    n_conv--;
}

void 
JACCMain::OnServerEvent(wxSocketEvent& event)
{
    if (event.GetSocketEvent() == wxSOCKET_CONNECTION)
    { 
        if(n_conv > 0)
        {
            wxSocketBase *sock = sockServer->Accept(false);
            
            convs[n_conv] = new JACCConv(NULL);
            convs[n_conv]->takeFrame(this);
	        convs[n_conv]->takeFrame(fLogin);
	    
	        convs[n_conv]->SetClient(false, sock);
	        convs[n_conv]->WxEdit1->Enable();
	        convs[n_conv]->WxButton1->Enable();
            convs[n_conv]->Show();
              
            n_conv--;   
        }
        else
            wxMessageBox("Impossibile supportare altre connessioni", "Error");
    } 
} 

/*
 * Mnuexit1026Click
 */
void JACCMain::Mnuexit1026Click(wxCommandEvent& event)
{
	char sql[255] = "DELETE FROM UsersOnLine WHERE nickname = '";
    strcat(sql, fLogin->MyUser->nickname);
    strcat(sql, "';");
    
    mysql_query(fLogin->sock, sql);
    mysql_close(fLogin->sock);
    
    if(sockServer)
    {
        sockServer->Notify(false);
        sockServer->Destroy();
        sockServer = NULL;
    } 
     
	Destroy();
    delete fLogin;
	exit(0);
}

// Refresha la lista dei loggati ogni 60 secondi
/*
 * WxTimer1Timer
 */
void JACCMain::WxTimer1Timer(wxTimerEvent& event)
{
	loadUserFriends();
}
