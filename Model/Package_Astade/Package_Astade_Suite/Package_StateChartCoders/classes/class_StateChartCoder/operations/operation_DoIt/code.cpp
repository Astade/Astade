wxCmdLineParser CmdLineParser(argc, const_cast<char**>(argv));
CmdLineParser.AddParam("DIRNAME",wxCMD_LINE_VAL_STRING,wxCMD_LINE_OPTION_MANDATORY);
CmdLineParser.AddParam("TARGETFILE",wxCMD_LINE_VAL_STRING,wxCMD_LINE_OPTION_MANDATORY);

CmdLineParser.SetLogo("StateChartCoder: the \"state-chart coder\"\n" COPYRIGHT);

if (CmdLineParser.Parse() != 0 || CmdLineParser.GetParamCount() != 2)
		return EXIT_FAILURE;

AdeModelElement* element = AdeModelElement::CreateNewElement(CmdLineParser.GetParam(0));

if ((element->GetType() & ITEM_TYPE_MASK) != ITEM_IS_STATECHART)
{
	printf("Error: only state charts please!");
	return EXIT_FAILURE;
}
myAdeStatechart = dynamic_cast<AdeStatechart*>(element);
assert(myAdeStatechart);

wxDateTime now;
now.SetToCurrent();
now.MakeTimezone(wxDateTime::UTC);
GenerationTime = now.FormatISODate() + " " + now.FormatISOTime() + " UTC";

wxFileName theFileName = CmdLineParser.GetParam(1);
wxFileName aPrologue(theFileName);
aPrologue.RemoveLastDir();
aPrologue.SetFullName("prolog.h");

theFileName.SetExt("h");
spec.open(theFileName.GetFullPath().c_str());
InsertFile(spec, aPrologue.GetFullPath().c_str());
PrintHeader(spec, theFileName.GetFullName());

theFileName.SetExt("cpp");
impl.open(theFileName.GetFullPath().c_str());
aPrologue.SetExt("cpp");
InsertFile(impl, aPrologue.GetFullPath().c_str());
PrintHeader(impl, theFileName.GetFullName());

CodeStatechart();

aPrologue.SetFullName("epilog.h");
InsertFile(spec, aPrologue.GetFullPath().c_str());
aPrologue.SetExt("cpp");
InsertFile(impl, aPrologue.GetFullPath().c_str());

return EXIT_SUCCESS;