if (fileName.FileExists())
{
	wxString cmd = wxS("pj drop -y -P ") + myProjectFile + wxS(" \"") + fileName.GetFullPath(wxPATH_UNIX) + wxS("\"");
	wxExecute(cmd, theOutput, wxEXEC_SYNC);
}
else if (fileName.DirExists())
{
	wxDir thisDir(fileName.GetFullPath());
	wxString aFileName;
	wxFileName j;
	for (bool i = thisDir.GetFirst(&aFileName,wxEmptyString, wxDIR_FILES | wxDIR_DIRS ); i; i = thisDir.GetNext(&aFileName))
	{
		j.Clear();
		j.Assign(fileName.GetFullPath(), aFileName);
		Drop(j);
	}
}
