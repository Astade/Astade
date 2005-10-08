wxTreeItemId aID = myTree->GetSelection();
wxTreeItemId parentID = myTree->GetItemParent(aID);

wxFileName component(myTree->GetItem(aID)->GetFileName());
component.MakeAbsolute();

wxString command = wxString("make -C \"") +
				component.GetPath() +
				"\" TARGET="+
				myTree->GetItem(parentID)->GetLabel()+
				" all";

myMakeOutput.SetNormalStyle();
myMakeOutput.theEdit.Clear();
myMakeOutput.theEdit << "make started ... \n";

myMakeOutput.Show();
theMakeProcess = new AstadeMakeProcess;

wxExecute(command,wxEXEC_ASYNC,theMakeProcess);
theMakeProcess->theMakeInputStream = theMakeProcess->GetInputStream();
theMakeProcess->theMakeErrorStream = theMakeProcess->GetErrorStream();
