//~~ void CodeState() [StateChartCoderQt] ~~

spec << "\t//! @brief The pointer holding the current state." << std::endl;
spec << "\tvoid ("
	<< myAdeStatechart->GetName().utf8_str()
	<< "::*theState)(const AQF_MessageReceiver*, const "
	<< myAdeStatechart->GetEventType().utf8_str()
	<< "&);\n"
	<< std::endl;
