//~~ void CodePorts(int depth, const AdeClass* theClass, const wxString& nodename) [OMDgenerator] ~~

AdePorts* thePorts = theClass->GetPorts();

if (thePorts)
{
	for(AdeElementIterator it = thePorts->begin(); it != thePorts->end(); ++it)
	{
		AdeModelElement* aElement = it.CreateNewElement();
		wxASSERT(aElement);
		AdePort* aPort = dynamic_cast<AdePort*>(aElement);
		wxASSERT_MSG(aPort, "the ports folder should only contain ports");
        
        IndentOutput(depth);
        std::cout << nodename << "_" << aPort->GetName() 
            << "[shape=plaintext, label=\"" << aPort->GetName() << "\", fontname = arial, fontsize=8]" << std::endl;
        
        IndentOutput(depth);
        if (aPort->IsDelegate())
        {
            if (aPort->IsInput())
            {
                std::cout << nodename << " -> " << nodename << "_" << aPort->GetName() << "[arrowtail=vee, style=dotted, arrowhead=box]" << std::endl;
            }
            else
            {
                std::cout << nodename << " -> " << nodename << "_" << aPort->GetName() << "[style=dotted, arrowhead=oboxvee]" << std::endl;
            }
        }
        else
        {
            if (aPort->IsInput())
            {
                std::cout << nodename << " -> " << nodename << "_" << aPort->GetName() << "[arrowtail=vee, arrowhead=box]" << std::endl;
            }
            else
            {
                std::cout << nodename << " -> " << nodename << "_" << aPort->GetName() << "[arrowhead=oboxvee]" << std::endl;
            }
        }
        
		delete(aElement);
	}
    delete thePorts;
}

