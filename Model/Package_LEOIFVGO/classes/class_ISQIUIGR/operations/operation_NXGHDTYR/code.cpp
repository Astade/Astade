if ((object.empty()) || (object=="*"))
	return wxNOT_FOUND;

int index = classes.Index(object);

if ((index==wxNOT_FOUND) && (classes.GetCount()<32))
{
	index = AddObject(object);
	AddEventExist(index);
}

return index;