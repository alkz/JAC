//---------------------------------------------------------------------------
//
// Name:        JACCApp.h
// Author:      Alessandro
// Created:     07/02/2011 17.49.35
// Description: 
//
//---------------------------------------------------------------------------

#ifndef __JACCFRMApp_h__
#define __JACCFRMApp_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif

class JACCFrmApp : public wxApp
{
	public:
		bool OnInit();
		int OnExit();
};


#endif
