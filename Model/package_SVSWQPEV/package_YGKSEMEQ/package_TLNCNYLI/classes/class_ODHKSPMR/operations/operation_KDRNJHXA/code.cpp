wxTreeItemId aID = myTree->GetSelection();

AdeModelElement* aElement = myTree->GetItem(aID);

if (aElement->GetHasChildren())
{
	wxMessageDialog aDialog(this,"Element is not empty, delete anyway?","Delete:",wxOK | wxCANCEL | wxICON_EXCLAMATION );
	if (aDialog.ShowModal()==wxID_CANCEL)
		return;
}

aElement->Delete();

UpdateSubtree( myTree->GetItemParent(aID));