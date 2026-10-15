//~~ void Update() [AstadeTreeItemBase] ~~

myModelElement->Reload();

ourTree->SetItemImage(GetId(), GetIconIndex());

wxFont theFont = ourTree->GetItemFont(GetId());

theFont.SetPointSize(wxNORMAL_FONT->GetPointSize());

if (GetLabelIsUnderlined())
	theFont.SetUnderlined(true);
else
	theFont.SetUnderlined(false);

if (GetLabelIsBold())
	theFont.SetWeight(wxFONTWEIGHT_BOLD);
else
	theFont.SetWeight(wxFONTWEIGHT_NORMAL);

if (GetLabelIsItalic())
	theFont.SetStyle(wxFONTSTYLE_ITALIC);
else
	theFont.SetStyle(wxFONTSTYLE_NORMAL);

ourTree->SetItemHasChildren(GetId(), myModelElement->HasChildren());
ourTree->SetItemFont(GetId(), theFont);
ourTree->SetItemText(GetId(), wxS(";-)")); //This is neccessary because when setting the same text again, wxWidgets doesn't calculate the Textsize even if it's bold now.
ourTree->SetItemText(GetId(), myModelElement->GetLabel());
