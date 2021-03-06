//~~ void operations(std::ofstream& out, bool spec, bool inlines, int visibility) [CppGenerator] ~~

std::map<wxString, const AdeOperationBase*, AdeStringCompare> ops;

wxFileName op(source->GetFileName());
op.AppendDir(wxS("operations"));

if (wxDir::Exists(op.GetPath()))
{
    wxDir dir(op.GetPath());
    wxString filename;

    bool cont = dir.GetFirst(&filename, wxEmptyString, wxDIR_DIRS);
    while (cont)
    {
        wxFileName FullName = op;
        FullName.AppendDir(filename);
        FullName.SetFullName(wxS("ModelNode.ini"));
        const AdeModelElement* pe = AdeModelElement::CreateNewElement(FullName);
        if ((pe->GetType() & ITEM_TYPE_MASK) == ITEM_IS_OPERATION &&
            (pe->GetType() & visibility) == visibility)
        {
            const AdeOperationBase* po = dynamic_cast<const AdeOperationBase*>(pe);
            assert(po);
            ops[po->GetSignature()] = po;
        }
        else
            delete pe;
        cont = dir.GetNext(&filename);
    }
}

std::map<wxString, const AdeOperationBase*>::iterator it;

for (it = ops.begin(); it != ops.end(); ++it)
{
    const AdeOperationBase* po = it->second;
    if (spec)
    {
        specOperation(out, *po);
    }
    else
    {
        if (po->IsInline() == inlines)
            codeOperation(out, *po);
    }
    delete po;
}
