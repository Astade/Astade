wxArrayString names;

names.Add("usecasediagram");

assert(myModelElement->IsUndocumented()==false);

if(myModelElement->ContainsUndocumented())
	names.Add("containundocumented");	
	
int index = AstadeIcons::Instance()->GetIconIndex(names);

assert(index>=0);

return index;