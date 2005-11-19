#include "AstadeDirDialog.h"
#include <wx/filedlg.h>

BEGIN_EVENT_TABLE(AstadeDirDialog,wxDialog)
	EVT_CLOSE(AstadeDirDialog::DlgClose)
	EVT_BUTTON(wxID_CANCEL, AstadeDirDialog::DlgCancel)
	EVT_BUTTON(IDSAVEEXIT, AstadeDirDialog::DlgSaveAndExit)
	EVT_BUTTON(IDMODELPATHBROWSE, AstadeDirDialog::ModelPathBrowse)
	EVT_BUTTON(IDHELPPATHBROWSE, AstadeDirDialog::HelpPathBrowse)
	EVT_BUTTON(IDFEATUREEDITPATHBROWSE, AstadeDirDialog::FeatureEditPathBrowse)
	EVT_BUTTON(IDCODEEDITPATHBROWSE, AstadeDirDialog::CodeEditPathBrowse)
	EVT_BUTTON(IDOMDPATHBROWSE, AstadeDirDialog::OmdViewPathBrowse)
	EVT_BUTTON(IDSTATECHARTPATHBROWSE, AstadeDirDialog::StatechartViewPathBrowse)
	EVT_BUTTON(IDCODERPATHBROWSE, AstadeDirDialog::CoderPathBrowse)
	EVT_BUTTON(IDMAKEPATHBROWSE, AstadeDirDialog::MakePathBrowse)
	EVT_BUTTON(IDTEMPLATESPATHBROWSE, AstadeDirDialog::TemplatesPathBrowse)
END_EVENT_TABLE()
