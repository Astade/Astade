#include "AstadeMakeOutputEdit.h"

#define AllPathFlags wxPATH_NORM_ENV_VARS|wxPATH_NORM_DOTS|wxPATH_NORM_TILDE|wxPATH_NORM_CASE|wxPATH_NORM_ABSOLUTE|wxPATH_NORM_LONG|wxPATH_NORM_SHORTCUT

BEGIN_EVENT_TABLE(AstadeMakeOutputEdit,wxTextCtrl)
	EVT_CONTEXT_MENU(AstadeMakeOutputEdit::ContextMenu)
	EVT_MENU(ID_EDIT_ERROR, AstadeMakeOutputEdit::Edit)
	EVT_MENU(ID_EDIT_ERROR_ELEMENT, AstadeMakeOutputEdit::Edit)
	EVT_END_PROCESS(wxID_ANY, AstadeMakeOutputEdit::EndProcess)
END_EVENT_TABLE()
