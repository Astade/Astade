//~~ void LoadRelations(wxConfigBase& configObject) [glArtefact] ~~

int count = 1;

wxString useName;
useName.Printf(wxS("CreateArtefact%03d"), count);

while (configObject.Exists(useName))
{
    int UseID;
    configObject.Read(useName, &UseID);
    
    glNode* partnerNode = glNode::getNodeById(UseID);
    
    if (partnerNode)
        new glCreateArtefact(myParent, *this, *partnerNode);
    
    count++;
    useName.Printf(wxS("CreateArtefact%03d"), count);
}

count = 1;
useName.Printf(wxS("ArtefactDependency%03d"), count);

while (configObject.Exists(useName))
{
    int UseID;
    configObject.Read(useName, &UseID);
    
    glNode* partnerNode = glNode::getNodeById(UseID);
    
    if (partnerNode)
        new glArtefactDependency(myParent, *this, *partnerNode);
    
    count++;
    useName.Printf(wxS("ArtefactDependency%03d"), count);
}

count = 1;
useName.Printf(wxS("ArtefactComposition%03d"), count);

while (configObject.Exists(useName))
{
    int UseID;
    configObject.Read(useName, &UseID);
    
    glNode* partnerNode = glNode::getNodeById(UseID);
    
    if (partnerNode)
        new glArtefactComposition(myParent, *this, *partnerNode);
    
    count++;
    useName.Printf(wxS("ArtefactComposition%03d"), count);
}
