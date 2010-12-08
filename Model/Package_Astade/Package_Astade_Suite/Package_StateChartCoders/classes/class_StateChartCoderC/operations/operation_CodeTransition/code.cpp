//~~ void CodeTransition(AdeState& theState, AdeTransition& theTransition) [StateChartCoderC] ~~

wxString event = theTransition.GetTrigger();
if (event.empty())
	return;

impl << "\t// "
	<< theTransition.GetLabel().c_str()
	<< std::endl;

wxString guard = theTransition.GetGuard();
if (guard.empty())
	impl << "\tif (itsID == ID_"
		<< event.c_str()
		<< ")"
		<< std::endl;
else
	impl << "\tif (itsID == ID_"
		<< event.c_str()
		<< " && "
		<< myAdeStatechart->GetName().c_str()
		<< "_impl_"
		<< theTransition.GetGuard().c_str()
		<< "(me->myHandler, theEvent))"
		<< std::endl;
impl << "\t{" << std::endl;

std::list<wxString> aList = theTransition.GetActions();

wxString nextState = theTransition.GetDestination();

if (!theTransition.IsInternalTransition())
{
	if (!theState.GetExitAction().empty())
	{
		impl << "\t\t// exit action" << std::endl;
		impl << "\t\t"
			<< theState.GetExitAction().c_str()
			<< "(theEvent);"
			<< std::endl;
	}
	if (!theState.GetTimeout().empty())
	{
		impl << "\t\t// Stop Timer" << std::endl;
		impl << "\t\t"
			<< myAdeStatechart->GetName().c_str()
			<< "_impl_StopTimer(me->myHandler);"
			<< std::endl;
	}
	impl << "\t\t// next state" << std::endl;

	if (theTransition.IsSelfTransition())
		impl << "\t\tme->nextState = &"
			<< myAdeStatechart->GetName().c_str()
			<< "_Enter_"
			<< theState.GetName().c_str()
			<< ";"
			<< std::endl;
	else
		impl << "\t\tme->nextState = &"
			<< myAdeStatechart->GetName().c_str()
			<< "_Enter_"
			<< nextState.c_str()
			<< ";"
			<< std::endl;
}
else
	impl << "\t\t// internal Transition" << std::endl;

if (!aList.empty())
	impl << "\t\t// Actions" << std::endl;

for (std::list<wxString>::iterator iter = aList.begin(); iter != aList.end(); ++iter)
	impl << "\t\t"
		<< myAdeStatechart->GetName().c_str()
		<< "_impl_"
		<< (*iter).c_str()
		<< "(me->myHandler, theEvent);"
		<< std::endl;

impl << "\t\treturn true;" << std::endl;
impl << "\t}" << std::endl;
impl << "\telse" << std::endl;
