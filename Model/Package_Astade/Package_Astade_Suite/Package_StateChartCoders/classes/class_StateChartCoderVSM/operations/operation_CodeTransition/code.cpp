//~~ void CodeTransition(AdeState& theState, AdeTransition& theTransition) [StateChartCoderVSM] ~~

wxString event = theTransition.GetTrigger();

if (event.empty())
	return;

impl << "\t// "
	<< theTransition.GetLabel().c_str()
	<< std::endl;

wxString guard = theTransition.GetGuard();
if (guard.empty())
	impl << "\tif (message.Primitive() == "
		<< event.c_str()
		<< ")"
		<< std::endl;
else
	impl << "\tif (message.Primitive() == "
		<< event.c_str()
		<< " && "
		<< theTransition.GetGuard().c_str()
		<< "(message))"
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
			<< "(message);"
			<< std::endl;
	}
	if (!theState.GetTimeout().empty())
	{
		impl << "\t\t// Stop Timer" << std::endl;
		impl << "\t\tif (message.Primitive() != dIID_VFSM_MSG_AbbruchTimer && m_RunningTimer)" << std::endl;
		impl << "\t\t\t"
			<< myAdeStatechart->GetEventType().c_str()
			<< "::Delete(m_RunningTimer);"
			<< std::endl;
		impl << "\t\tm_RunningTimer = 0;\n" << std::endl;
	}
	impl << "\t\t// next state" << std::endl;

	if (theTransition.IsSelfTransition())
		impl << "\t\tnextState = &"
			<< myAdeStatechart->GetName().c_str()
			<< "::Enter_"
			<< theState.GetName().c_str()
			<< ";"
			<< std::endl;
	else
		impl << "\t\tnextState = &"
			<< myAdeStatechart->GetName().c_str()
			<< "::Enter_"
			<< nextState.c_str()
			<< ";"
			<< std::endl;
}
else
	impl << "\t\t// internal Transition" << std::endl;

if (!aList.empty())
	impl << "\t\t// Actions" << std::endl;

for (std::list<wxString>::iterator iter = aList.begin(); iter!=aList.end(); ++iter)
	impl << "\t\t"
		<< (*iter).c_str()
		<< "(message);"
		<< std::endl;

impl << "\t}" << std::endl;
impl << "\telse" << std::endl;
