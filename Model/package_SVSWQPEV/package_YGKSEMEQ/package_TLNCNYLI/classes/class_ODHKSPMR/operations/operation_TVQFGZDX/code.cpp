wxTreeItemId aID = myTree->GetSelection();
wxFileName parentPath = myTree->GetItem(aID)->GetFileName();

AdeUsecaseDiagrams::CreateNewElement(parentPath);
UpdateSubtree(aID);