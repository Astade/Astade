wxFileConfig theConfig(wxEmptyString,wxEmptyString,myFileName.GetFullPath());

wxString label = theConfig.Read("Astade/Name","<name unknown>");
wxString internals;

if (!theConfig.Read("Astade/EntryAction").empty())
{
	if (!internals.empty())
		internals += "\\n";
	internals += "Entry: ";
	internals += theConfig.Read("Astade/EntryAction");
}

if (!theConfig.Read("Astade/ExitAction").empty())
{
	if (!internals.empty())
		internals += "\\n";
	internals += "Exit: ";
	internals += theConfig.Read("Astade/ExitAction");
}

AdeElementIterator it;
for (it=begin();it!=end();++it)
{
	AdeModelElement* aElement = it.CreateNewElement();
	if ((aElement->GetType() & 0x7F00000) == ITEM_IS_TRANSITION)
	{
		AdeTransition* aTransition = static_cast<AdeTransition*>(aElement);
		if (aTransition->IsInternalTransition())
		{
			if (!internals.empty())
				internals += "\\n";
			internals += aTransition->GetLabel();
		}
	}
	delete aElement;
}

if (!internals.empty())
{
	label += " | ";
	label += internals;
}

return label;