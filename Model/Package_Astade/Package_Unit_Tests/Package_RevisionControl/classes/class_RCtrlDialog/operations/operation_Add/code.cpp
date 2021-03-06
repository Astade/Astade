//~~ void Add(wxCommandEvent& event) [RCtrlDialog] ~~

wxFileName aFileName = wxFileName(fileName->GetValue());
AdeRevisionControlBase* theRevisionControl = AdeRevisionControlBase::GetRevisionControlObject();
if (theRevisionControl->IsAddSupported())
{
	int ret = theRevisionControl->Add(aFileName);
	wxArrayString output = theRevisionControl->GetOutput();
	wxString message;
	for (size_t i = 0; i < output.GetCount(); i++)
		message += output[i] + wxS("\n");
	if (ret == 0)
		wxMessageBox(message, wxS("Operation Successful"));
	else
		wxMessageBox(message, wxS("Operation failed"), wxOK | wxICON_ERROR);
}
