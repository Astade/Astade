//---------------------------------------------------------------------------
//
// Name:        newProgramDlgApp.cpp
// Author:      Guru Kathiresan
// Created:     12/10/2003 9:47:07 PM
// Copyright:
//
//---------------------------------------------------------------------------
#include "RecourceEditDlgApp.h"
#include "RecourceEdit.h"

IMPLEMENT_APP(newProgramDlgApp)

bool newProgramDlgApp::OnInit()
{
	RecourceEdit *myDlg = new  RecourceEdit(NULL);
    wxString t(wxGetApp().argv[1]);
    myDlg->file = t;
	SetTopWindow(myDlg);
	myDlg->Show(TRUE);		
	return TRUE;
}
 
int newProgramDlgApp::OnExit()
{
	return 0;
}
