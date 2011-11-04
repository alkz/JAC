///-----------------------------------------------------------------
///
/// @file      JACCFrm.cpp
/// @author    Alessandro
/// Created:   07/02/2011 17.49.35
/// @section   DESCRIPTION
///            JACCFrm class implementation
///
///------------------------------------------------------------------


#include "JACCFrm.h"

//Do not add custom headers between
//Header Include Start and Header Include End
//wxDev-C++ designer will remove them
////Header Include Start
#include "Images/Self_JACCFrm_XPM.xpm"
////Header Include End

//----------------------------------------------------------------------------
// JACCFrm
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(JACCFrm,wxFrame)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(JACCFrm::OnClose)
	EVT_BUTTON(ID_WXBUTTON1,JACCFrm::WxButton1Click0)
END_EVENT_TABLE()
////Event Table End

JACCFrm::JACCFrm(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style)
{
	CreateGUIControls();
	MyUser = NULL;
	sock = NULL;
}

JACCFrm::~JACCFrm()
{
}

void JACCFrm::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	WxPanel1 = new wxPanel(this, ID_WXPANEL1, wxPoint(-8, -8), wxSize(300, 280));
	WxPanel1->SetBackgroundColour(wxColour(192,222,250));

	WxEditNick = new wxTextCtrl(WxPanel1, ID_WXEDIT3, wxT(""), wxPoint(128, 96), wxSize(121, 19), 0, wxDefaultValidator, wxT("WxEditNick"));

	WxEditPasw = new wxTextCtrl(WxPanel1, ID_WXEDIT2, wxT(""), wxPoint(128, 144), wxSize(121, 19), wxTE_PASSWORD, wxDefaultValidator, wxT("WxEditPasw"));

	WxButton1 = new wxButton(WxPanel1, ID_WXBUTTON1, wxT("Login"), wxPoint(64, 184), wxSize(75, 25), 0, wxDefaultValidator, wxT("WxButton1"));

	WxStaticText4 = new wxStaticText(WxPanel1, ID_WXSTATICTEXT4, wxT("Nickname:"), wxPoint(56, 96), wxDefaultSize, 0, wxT("WxStaticText4"));

	WxStaticText3 = new wxStaticText(WxPanel1, ID_WXSTATICTEXT3, wxT("Password:"), wxPoint(56, 144), wxDefaultSize, 0, wxT("WxStaticText3"));

	WxStaticText1 = new wxStaticText(WxPanel1, ID_WXSTATICTEXT1, wxT("JACC Login"), wxPoint(68, 26), wxDefaultSize, 0, wxT("WxStaticText1"));
	WxStaticText1->SetFont(wxFont(24, wxSWISS, wxITALIC, wxNORMAL, false, wxT("Trebuchet MS")));

	WxHyperLinkCtrl1 = new wxHyperlinkCtrl(WxPanel1, ID_WXHYPERLINKCTRL1, wxT("Registrati!"), wxT("http://wxdsgn.sf.net"), wxPoint(168, 192), wxSize(57, 17), wxNO_BORDER | wxHL_CONTEXTMENU, wxT("WxHyperLinkCtrl1"));
	WxHyperLinkCtrl1->SetFont(wxFont(8, wxSWISS, wxNORMAL, wxNORMAL, true, wxT("MS Sans Serif")));

	SetTitle(wxT("JACC v0.1"));
	SetIcon(Self_JACCFrm_XPM);
	SetSize(8,8,300,269);
	Center();
	
	////GUI Items Creation End
	
	WxHyperLinkCtrl1->SetURL("http://jacc.dyndns-server.com");
}

void JACCFrm::OnClose(wxCloseEvent& event)
{
    if(MyUser) delete MyUser;
    mysql_close(sock);
	Destroy();
}


/*
 * WxButton1Click0
 */
void JACCFrm::WxButton1Click0(wxCommandEvent& event)
{
	sock = mysql_init(0);
	if(!sock) 
    {
        wxString text = "Errore inizializzazione MYSQL: " + (wxString)mysql_error(sock);
        wxMessageBox(text, "Error"); 
        return;  
    }
    
    if(!mysql_real_connect(sock, HOST, USER, PSW, DB, 0, NULL, 0))
    {
        wxString text = "Errore connessione al MYSQL: " + (wxString)mysql_error(sock);
        wxMessageBox(text, "Error"); 
        return;    
    }
   
    
    char sql[255] = "SELECT * FROM Users WHERE nickname = '";
    strcat(sql, (const char *)WxEditNick->GetValue());
    strcat(sql, "' AND password = SHA1('");
    strcat(sql, (const char *)WxEditPasw->GetValue());
    strcat(sql, "');");
    
    mysql_query(sock, sql);
    MYSQL_RES *result;
    result = mysql_store_result(sock);
    bool exists = false;
    
    MyUser = NULL;
     
    if(result) 
    {
        MYSQL_ROW row;
        while(row = mysql_fetch_row(result))
        {
            exists = true;
            break;
        }
        if(exists)
        {
            
            char tmp[41];
            strcpy(tmp, row[1]);
            
            //wxMessageBox(((wxString)row[0])+"\n" + ((wxString)tmp)+"\n"  + ((wxString)row[2])+"\n"  + ((wxString)row[3])+"\n"  + ((wxString)row[4])+"\n"  + ((wxString)row[5]), "TO");
            wxString myIp_ = getIP();
            if(myIp_ == "NULL") 
            {
                wxMessageBox("Can't get your IP!", "Error");
                return;
            }
            char *myIp = new char[myIp_.Length()+1];
            wxToCh(myIp_, myIp);
            MyUser = new User(row[0], tmp, row[2], row[3], row[4], row[5], myIp);
            /*wxMessageBox(((wxString)MyUser->nickname)+"\n" + 
            ((wxString)MyUser->password)+"\n"  + ((wxString)MyUser->signDate)+"\n"  + 
            ((wxString)MyUser->birthDate)+"\n"  + ((wxString)MyUser->image)+"\n"  + 
            ((wxString)MyUser->phrase), "TO");*/
            
            mysql_free_result(result);
           
        }
    }
        
    
    if(exists)
    {
        strcpy(sql, "\0");
        strcpy(sql, "INSERT INTO UsersOnLine(nickname,IP,loginDate) VALUES('");
        strcat(sql, MyUser->nickname);
        strcat(sql, "', '");
        strcat(sql, MyUser->ip);
        strcat(sql, "', NOW());");
            
        if(!mysql_query(sock, sql)) 
        {
            frameMain = new JACCMain(NULL);
            frameMain->takeFrame(this);
            frameMain->loadUserFriends();
            frameMain->Show();
            this->Hide();
        }
        else
        {
            wxString text = "Errore Esecuzione Query: " + (wxString)mysql_error(sock);
            wxMessageBox(text, "Error"); 
        }
    }
    else
        wxMessageBox("Login incorrect!", "Error"); 
}

wxString
JACCFrm::getIP(void)
{
    wxURL url(wxT("http://www.whatismyip.com/automation/n09230945.asp")); 
    wxString htmldata;
    
    if(url.GetError() == wxURL_NOERR)
    {
        wxInputStream *in = url.GetInputStream();
 
        if(in && in->IsOk())
        {
            wxStringOutputStream html_stream(&htmldata);
            in->Read(html_stream);
        }
        delete in;
        return htmldata;
    }
    else
    {
        htmldata = "NULL";
        return htmldata;
    }
        
}

void
JACCFrm::wxToCh(wxString s, char *s1)
{
    unsigned int i;
    for(i = 0; i <= s.Length(); i++)
        s1[i] = s[i];
    s1[i] = 0;        
}


