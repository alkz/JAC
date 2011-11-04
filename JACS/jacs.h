/**
 *
 * JACS (Just Another Chat Server)
 * 
 * by alkz (Alessandro Carrara)
 * 2011
 *
 */  


#include "wx/wx.h"
#include "wx/socket.h"

#include <list>
#include <string.h>

#include "config.h"

struct Client
{
    char *nickname;
    wxSocketBase *socket;
};

class JACS : public wxApp
{
    virtual bool OnInit();

    public:
        void OnClientConnects(wxSocketEvent &);
        void OnMessage(wxSocketEvent &);

    private: 
        wxSocketServer *Server;
        wxIPV4address addr;
        std::list<Client *> Clients;
        int clients;
        wxSocketBase * getSocket(char *);

    DECLARE_EVENT_TABLE()
};


