aPopUp.Append(ID_FEATURES,"features",wxEmptyString, wxITEM_NORMAL);
aPopUp.AppendSeparator();
aPopUp.Append(ID_COPY,"copy",wxEmptyString, wxITEM_NORMAL);
aPopUp.Append(ID_CUT,"cut",wxEmptyString, wxITEM_NORMAL);
aPopUp.AppendSeparator();
aPopUp.Append(ID_UP,"up",wxEmptyString, wxITEM_NORMAL);
aPopUp.Append(ID_DOWN,"down",wxEmptyString, wxITEM_NORMAL);
aPopUp.AppendSeparator();

if (AdeRevisionControlBase::GetRevisionControlObject()->IsRenameSupported())
	aPopUp.Append(ID_RENAMEELEMENT,"Rename element file",wxEmptyString, wxITEM_NORMAL);

aPopUp.Append(ID_DELETE,"delete from Model",wxEmptyString, wxITEM_NORMAL);

if (!ourTree->GetPrevSibling(GetId()).IsOk())
	aPopUp.Enable(ID_UP, false);

if (!ourTree->GetNextSibling(GetId()).IsOk())
	aPopUp.Enable(ID_DOWN, false);