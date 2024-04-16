/* vi: set tabstop=4: */

#include <wx/wxprec.h>
#include <wx/utils.h>
#include <wx/sizer.h>
#include <wx/statbox.h>

#include "ResourceEdit.h"

#include "edit.xpm"

BEGIN_EVENT_TABLE(ResourceEdit, wxDialog)

	EVT_CLOSE(ResourceEdit::ResourceEditClose)
	EVT_INIT_DIALOG(ResourceEdit::Init)
	EVT_BUTTON(wxID_CANCEL,			ResourceEdit::Cancel)
	EVT_BUTTON(wxID_OK,				ResourceEdit::Save)
	EVT_CHECKBOX(ID_VIRTUAL,		ResourceEdit::TouchVirtual)
	EVT_CHECKBOX(ID_INLINE,			ResourceEdit::ChangeIcon)
	EVT_CHECKBOX(ID_STATIC,			ResourceEdit::TouchStatic)
	EVT_CHECKBOX(ID_ABSTRACT,		ResourceEdit::TouchAbstract)
	EVT_CHECKBOX(ID_CONST,			ResourceEdit::TouchConst)
	EVT_CHECKBOX(ID_DEPRECATED,		ResourceEdit::ToggleDeprecated)
	EVT_CHECKBOX(ID_IN,				ResourceEdit::ChangeIcon)
	EVT_CHECKBOX(ID_OUT,			ResourceEdit::ChangeIcon)
	EVT_CHECKBOX(ID_NAMESPACE,	    ResourceEdit::ChangeIcon)
	EVT_CHECKBOX(ID_ALL,            ResourceEdit::toggleAll)
	EVT_TEXT(ID_AGGREGATIONTYPE,	ResourceEdit::ChangeIcon)
	EVT_RADIOBUTTON(ID_M_PRIVATE,	ResourceEdit::ChangeIcon)
	EVT_RADIOBUTTON(ID_M_PROTECTED,	ResourceEdit::ChangeIcon)
	EVT_RADIOBUTTON(ID_M_PUBLIC,	ResourceEdit::ChangeIcon)
	EVT_COMBOBOX(ID_CCODED, 		ResourceEdit::ChangeIcon)

END_EVENT_TABLE()
