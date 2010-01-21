int count = 1;

wxString useName;

useName.Printf("Transition%03d",count);
while (configObject.Exists(useName))
{
	int UseID;
	configObject.Read(useName,&UseID);
	
	glNode* partnerNode = glNode::getNodeById(UseID);
	
	if (partnerNode)
	{
		glTransition* aTransition = new glTransition(myParent, *this, *partnerNode);
  	configObject.SetPath(useName);
  	aTransition->Load(configObject);
  	configObject.SetPath("..");
  }

	count++;
	useName.Printf("Transition%03d",count);
}

count = 1;
useName.Printf("SelfTransition%03d",count);
while (configObject.Exists(useName))
{
	glSelfTransition* aTransition = new glSelfTransition(*myParent, *this, glVector());
  	configObject.SetPath(useName);
  	aTransition->Load(configObject);
  	configObject.SetPath("..");

	count++;
	useName.Printf("SelfTransition%03d",count);
}
