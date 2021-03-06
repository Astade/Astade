//~~ void Friends(std::ofstream& out) [CppGenerator] ~~

std::set<wxString, AdeStringCompare> classnames;

wxFileName relations(source->GetFileName());
relations.AppendDir(wxS("relations"));

wxDir dir(relations.GetPath());
wxString filename;

bool cont = dir.GetFirst(&filename, wxS("*.ini"));
while (cont)
{
    wxFileName FullName(relations);
    FullName.SetFullName(filename);
	const AdeModelElement* pe = AdeModelElement::CreateNewElement(FullName);
	if ((pe->GetType() & ITEM_TYPE_MASK) == ITEM_IS_RELATION)
	{
		const AdeRelation* pr = dynamic_cast<const AdeRelation*>(pe);
		assert(pr);
		long RelationType = pr->GetType() & ITEM_RELATION_MASK;
		if (RelationType == ITEM_IS_FRIEND)
		{
			wxFileName PartnerDir(pr->GetPartnerFile());
			wxFileName partner(PartnerDir);
			partner.RemoveDir(partner.GetDirCount()-1);
			partner.SetFullName(wxS("ModelNode.ini"));
			const AdeModelElement* pe2 = AdeModelElement::CreateNewElement(partner);
			const AdeClass* pc = dynamic_cast<const AdeClass*>(pe2);
			assert(pc);

			if (pc->GetName() != source->GetName())
				classnames.insert(pc->GetName());
			delete pe2;
        }
    }
	delete pe;
    cont = dir.GetNext(&filename);
}

std::set<wxString>::iterator it;

if (!classnames.empty())
{
	out << "// Friends:" << std::endl;
	for (it = classnames.begin(); it != classnames.end(); ++it)
		out << "\tfriend class " << it->utf8_str()
			<< ";" << std::endl;
}
out << std::endl;
