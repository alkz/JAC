/**
 *
 * JACS (Just Another Chat Server)
 * 
 * by alkz (Alessandro Carrara)
 * 2011
 *
 */  


#define  DEBUG    0

#include "jacs.h"

IMPLEMENT_APP(JACS)

BEGIN_EVENT_TABLE(JACS, wxApp)
    EVT_SOCKET(SERVER_ID, JACS::OnClientConnects)
    EVT_SOCKET(CONTROLLER_ID, JACS::OnMessage)
END_EVENT_TABLE()


bool
JACS::OnInit()
{
    clients = 0;
    addr.Service(SERVER_PORT);
    
    Server = new wxSocketServer(addr);
    Server->SetNotify(wxSOCKET_CONNECTION_FLAG);
    Server->SetEventHandler(*this, SERVER_ID);
    Server->Notify(true);

    MainLoop();
    return true;
}


void
JACS::OnClientConnects(wxSocketEvent &event)
{
    clients++;
    char c = clients + '0';
    char client_id[SIZE_BUFFER] = "\0";

    wxSocketBase *sock = Server->Accept(true);

    char tmp[SIZE_BUFFER] = "\0";
    sock->Read(tmp, SIZE_BUFFER);
    sock->SetNotify(wxSOCKET_INPUT_FLAG | wxSOCKET_LOST_FLAG);
    sock->SetEventHandler(*this, CONTROLLER_ID);
    sock->Notify(true);

    if(strstr(tmp, "CLIENT_ID:"))    // A seguito di una richiesta di connessione il client ha restituito il proprio nick
    {
        for (int i = 10; i < strlen(tmp); i++)
            client_id[i-10] = tmp[i];
        
        if(DEBUG)
        {
            wxMessageBox("CLIENT_ID:" + (wxString)client_id, "sasasa"); 
            std::list<Client *>::const_iterator I;
            
            for (I = Clients.begin(); I != Clients.end(); I++)
                wxMessageBox((wxString)((*I)->nickname)); 
        }
        
         
        // Lo aggiungo alla lista dei client
        struct Client *toAdd = new struct Client; 

        toAdd->nickname = new char[strlen(client_id)+1];
        strcpy(toAdd->nickname, client_id);    //  FOTTUTO STRCPY

        toAdd->socket = sock;

        Clients.push_back(toAdd);
          
        if(DEBUG) 
        {
            std::list<Client *>::const_iterator I;
            for (I = Clients.begin(); I != Clients.end(); I++) 
                wxMessageBox((wxString)((*I)->nickname)); 
        }
            
        toAdd->socket->Write("HELLOK", 7);
    }

}


void
JACS::OnMessage(wxSocketEvent &event)
{
    wxSocketBase *sock = event.GetSocket();

    if(event.GetSocketEvent() == wxSOCKET_INPUT)
    {
        char tmp[SIZE_BUFFER] = "\0";
        sock->Read(tmp, SIZE_BUFFER);
        
        if(strstr(tmp, "CONNECT_TO:"))
        {
            char connect_to[SIZE_BUFFER] = "\0";
            for (int i = 11; tmp[i] != '-'; i++)
                connect_to[i-11] = tmp[i];
                
            char *tmpFrom = strstr(tmp, "FROM:");
            char from[SIZE_BUFFER] = "\0";

            for (int i = 5; i < strlen(tmpFrom); i++)
                from[i-5] = tmpFrom[i];


            if(DEBUG) wxMessageBox("CONNECT_TO:" + (wxString)connect_to + "-FROM:" + (wxString)from, "sasasa");

            wxSocketBase *sockDest = NULL;
            std::list<Client *>::const_iterator I;
            
            for (I = Clients.begin(); I != Clients.end(); I++)
            {
                if(DEBUG) wxMessageBox((wxString)((*I)->nickname) + "=" + (wxString)connect_to + "?"); 
                if( strcmp((*I)->nickname, connect_to) == 0 )
                {
                    if(DEBUG) wxMessageBox("TROVATO! IL SOCKET DI:" + (wxString)connect_to); 
                    sockDest = (*I)->socket;
                    break;
                }
            }


            char risp[SIZE_BUFFER] = "CONNECT_FROM:";
            strcat(risp, from);
            sockDest->Write(risp, SIZE_BUFFER);
        }

        else if(strstr(tmp, "ACK:"))
        {
            char ack[SIZE_BUFFER] = "\0";
            for (int i = 4; tmp[i] != '-'; i++)
                ack[i-4] = tmp[i];

            char *tmpTo = strstr(tmp, "TO:");
            char to[SIZE_BUFFER] = "\0";

            for (int i = 3; i < strlen(tmpTo); i++)
                to[i-3] = tmpTo[i];

            if(DEBUG) wxMessageBox("ACK:" + (wxString)ack + "-TO:" + (wxString)to, "sasasa");
                
            wxSocketBase *sockDest = NULL;
            std::list<Client *>::const_iterator I;
            
            for (I = Clients.begin(); I != Clients.end(); I++)
            {
                if(DEBUG) wxMessageBox((wxString)((*I)->nickname) + "=" + (wxString)to + "?"); 
                if( strcmp((*I)->nickname, to) == 0 )
                {
                    if(DEBUG) wxMessageBox("TROVATO! ACK IL SOCKET DI:" + (wxString)to); 
                    sockDest = (*I)->socket;
                }
            }


            char risp[SIZE_BUFFER] = "ACK:";
            strcat(risp, ack);
            sockDest->Write(risp, SIZE_BUFFER);
        }

        else if(strstr(tmp, "CLOSE:"))
        {
            char close[SIZE_BUFFER] = "\0";
            for(int i = 6; tmp[i] != '-'; i++)
                close[i-6] = tmp[i];
                
            char *tmpTo = strstr(tmp, "TO:");
            char to[SIZE_BUFFER] = "\0";

            for (int i = 3; i < strlen(tmpTo); i++)
                to[i-3] = tmpTo[i];

            if(DEBUG) wxMessageBox("CLOSE:" + (wxString)close + "-TO:" + (wxString)to, "sasasa"); 
            
            wxSocketBase *sockDest = NULL;
            std::list<Client *>::const_iterator I;
            
            for (I = Clients.begin(); I != Clients.end(); I++)
            {
                if(DEBUG) wxMessageBox((wxString)((*I)->nickname) + "=" + (wxString)to + "?"); 
                if( strcmp((*I)->nickname, to) == 0 )
                {
                    if(DEBUG) wxMessageBox("TROVATO! CLOSE IL SOCKET DI:" + (wxString)to); 
                    sockDest = (*I)->socket;
                }
            }
            
            char risp[SIZE_BUFFER] = "CLOSE:";
            strcat(risp, close);
            sockDest->Write(risp, SIZE_BUFFER);
        }
        
        else if(strstr(tmp, "TRUNCATE:"))
        {
            char truncate[SIZE_BUFFER] = "\0";
            for(int i = 9; strlen(tmp); i++)
                truncate[i-9] = tmp[i];
                
                
            if(DEBUG)
            {
                std::list<Client *>::const_iterator I;
            
                for (I = Clients.begin(); I != Clients.end(); I++)
                    wxMessageBox((wxString)((*I)->nickname)); 
            }

            std::list<Client *>::iterator I;
        
            for (I = Clients.begin(); I != Clients.end(); I++)
            {
                if(DEBUG) wxMessageBox((wxString)((*I)->nickname) + "=" + (wxString)truncate + "?"); 
                if( strcmp((*I)->nickname, truncate) == 0 )
                {
                    if(DEBUG) wxMessageBox("TROVATO! CANCELLO:" + (wxString)truncate); 

                    break;
                }
            }
            Clients.erase(I);
            
            if(DEBUG)
            {
                std::list<Client *>::const_iterator I;
            
                for (I = Clients.begin(); I != Clients.end(); I++)
                    wxMessageBox((wxString)((*I)->nickname)); 
            }
            clients--;
        }

        else if(strstr(tmp, "MESSAGE:"))
        {
            char message[SIZE_BUFFER] = "\0";
            for(int i = 8; tmp[i] != '-'; i++)
                message[i-8] = tmp[i];
                
            char *tmpTo = strstr(tmp, "TO:");
            char to[SIZE_BUFFER] = "\0";

            for (int i = 3; tmpTo[i] != '-'; i++)
                to[i-3] = tmpTo[i];
                
            char *tmpFrom = strstr(tmp, "FROM:");
            char from[SIZE_BUFFER] = "\0";

            for (int i = 5; i < strlen(tmpFrom); i++)
                from[i-5] = tmpFrom[i];

            if(DEBUG)
                wxMessageBox("MESSAGE:" + (wxString)message + "-TO:" + (wxString)to + "-FROM:" + (wxString)from);
                
            wxSocketBase *sockDest = NULL;
            std::list<Client *>::const_iterator I;
            
            for (I = Clients.begin(); I != Clients.end(); I++)
            {
                if(DEBUG) wxMessageBox((wxString)((*I)->nickname) + "=" + (wxString)to + "?"); 
                if( strcmp((*I)->nickname, to) == 0 )
                {
                    if(DEBUG) wxMessageBox("TROVATO! MESSAGE IL SOCKET DI:" + (wxString)to); 
                    sockDest = (*I)->socket;
                }
            }
 
            char risp[SIZE_BUFFER] = "MESSAGE:";
            strcat(risp, message);
            strcat(risp, "-FROM:");
            strcat(risp, from);
            sockDest->Write(risp, SIZE_BUFFER);
        }
    }
}
