//~~ void AddButtonSizer(wxSizer* topSizer, bool hasTracelevel = false, bool hasLanguageSelection = false, bool hasNamespaceSelection = false) [ResourceEdit] ~~

wxBoxSizer *button_sizer = new wxBoxSizer(wxHORIZONTAL);
topSizer->Add(button_sizer, 0, wxEXPAND|wxALL, 10);

if (hasTracelevel)
{
	button_sizer->Add(new wxStaticText(this, 0, wxS("Trace level:")), 0, wxRIGHT|wxLEFT, 10);
	traceLevel = new wxSpinCtrl(this);
	traceLevel->SetRange(0,9);
	button_sizer->Add(traceLevel, 0);
	traceLevel->SetValue(wxConfigBase::Get()->Read(wxS("Astade/Tracelevel"), 5));
}

if (hasLanguageSelection)
{
	//wxString choices[] = {CODE_CPlusPlus, CODE_C, CODE_JAVA, CODE_PYTHON, CODE_PHP};
    //codingLanguage = new wxComboBox(this, ID_CCODED, wxEmptyString, wxDefaultPosition, wxDefaultSize, 5, choices, wxCB_READONLY);
	wxString choices[] = {CODE_CPlusPlus, CODE_C, CODE_PYTHON};
    codingLanguage = new wxComboBox(this, ID_CCODED, wxEmptyString, wxDefaultPosition, wxDefaultSize, 3, choices, wxCB_READONLY);
	button_sizer->Add(codingLanguage, 0);

    wxString language;
	if (!wxConfigBase::Get()->Read(wxS("Astade/CodingLanguage"), &language))
		language = wxConfigBase::Get()->Read(wxS("Astade/CCoded")) == wxS("yes") ? CODE_C : CODE_CPlusPlus;
	if (language == wxS("Ansi C"))
		language = CODE_C;
    codingLanguage->SetValue(language);
}

if (hasNamespaceSelection)
{
    isNamespace = new wxCheckBox(this, ID_NAMESPACE, wxS("code as namespace"));
    isNamespace->SetValue(wxConfigBase::Get()->Read(wxS("Astade/IsNamespace"), wxS("no")) == wxS("yes"));
	button_sizer->Add(isNamespace, 0);
 }

button_sizer->AddStretchSpacer();

button_sizer->Add(new wxButton(this, wxID_CANCEL), 0);

button_sizer->AddSpacer(10);

button_sizer->Add(new wxButton(this, wxID_OK), 0);
