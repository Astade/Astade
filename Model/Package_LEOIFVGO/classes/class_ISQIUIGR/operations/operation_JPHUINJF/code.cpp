if ((object2 == wxNOT_FOUND) || (object1 == wxNOT_FOUND))
	return;

wxString s = label;

if (object1==object2)
	itsEvents.push_back(SeqEvent(object1,object2,ID_SELFRECEIVE,s.Trim(true).Trim(false)));
else
	itsEvents.push_back(SeqEvent(object1,object2,ID_RECEIVE,s.Trim(true).Trim(false)));