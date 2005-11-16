wxBoxSizer *relations = new wxBoxSizer( wxHORIZONTAL );
topSizer->Add(relations,0,wxEXPAND|wxRIGHT|wxLEFT,10);

wxArrayString arrayStringFor_WxComboBox1;
arrayStringFor_WxComboBox1.Add("Normal");
arrayStringFor_WxComboBox1.Add("Internal");
arrayStringFor_WxComboBox1.Add("Self");

transitionType =  new wxComboBox(this, ID_AGREGATIONTYPE ,wxEmptyString ,wxDefaultPosition,wxDefaultSize, arrayStringFor_WxComboBox1, wxCB_READONLY   );

relations->Add(transitionType,1);

destinationText = new wxStaticText(this, 0 ,"Destination:");
relations->Add(destinationText,0,wxRIGHT|wxLEFT,10);

destinationEditField = new wxTextCtrl(this, -1);
relations->Add(destinationEditField,1);

relations = new wxBoxSizer( wxHORIZONTAL );
topSizer->Add(relations,0,wxEXPAND|wxRIGHT|wxLEFT,10);

relations->Add(new wxStaticText(this, 0 ,"Guard:"),0,wxRIGHT|wxLEFT,10);

guardEditField = new wxTextCtrl(this, -1);
relations->Add(guardEditField,1);

transitionType->SetValue(wxConfigBase::Get()->Read("Astade/TransitionType",wxEmptyString));
destinationEditField->SetValue(wxConfigBase::Get()->Read("Astade/DestinationState",wxEmptyString));
guardEditField->SetValue(wxConfigBase::Get()->Read("Astade/Guard",wxEmptyString));