//---------------------------------------------------------------------------
//
// Name:        JACCApp.cpp
// Author:      Alessandro
// Created:     07/02/2011 17.49.35
// Description: 
//
//---------------------------------------------------------------------------

#include "JACCApp.h"
#include "JACCFrm.h"

IMPLEMENT_APP(JACCFrmApp)

bool JACCFrmApp::OnInit()
{
    JACCFrm *frameLogin = new JACCFrm(NULL);
    SetTopWindow(frameLogin);
    
    frameLogin->Show(); 

    return true;
}
 
int JACCFrmApp::OnExit()
{
	return 0;
}
