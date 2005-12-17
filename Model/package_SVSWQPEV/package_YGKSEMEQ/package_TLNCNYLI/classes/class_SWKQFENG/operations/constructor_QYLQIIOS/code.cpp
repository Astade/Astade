SetMinSize(wxSize(280,300));
wxBoxSizer *topSizer = new wxBoxSizer( wxVERTICAL );
SetSizer( topSizer );

wxArrayString text;
text.Add("none");
text.Add("public");
text.Add("public + protected");
text.Add("all");

wxRadioBox* box = new wxRadioBox(this, -1, wxString("attributes:"),wxDefaultPosition,wxDefaultSize,text,1);
topSizer->Add(box,1,wxEXPAND);



box =  new wxRadioBox(this, -1, wxString("operations:"),wxDefaultPosition,wxDefaultSize,text,1);
topSizer->Add(box,1,wxEXPAND);

externalCheckBox = new wxCheckBox(this,-1,"include classes from outside this scope");
topSizer->Add(externalCheckBox,0,wxALL,10);

notInComponentCheckBox = new wxCheckBox(this,-1,"include classes, which are not in active component");
topSizer->Add(notInComponentCheckBox,0,wxLEFT|wxBOTTOM,10);

topSizer->Add(
	new wxButton(this, ID_OBJECTMODELDIAGRAM, "show"),0);
