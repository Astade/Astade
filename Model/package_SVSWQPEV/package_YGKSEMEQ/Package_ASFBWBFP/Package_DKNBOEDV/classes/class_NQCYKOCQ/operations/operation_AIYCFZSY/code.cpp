configObject.Write("ClassName","GrafActor");

int count = 0;
for (std::set<GrafNode*>::iterator it = myAssociation.begin(); it != myAssociation.end(); it++)
{
	wxString associationName;
	associationName.Printf("Association%03d",++count);
	configObject.Write(associationName,(*it)->GetNodeID());
}

GrafNode::Save(configObject);


