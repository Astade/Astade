// vi: set tabstop=4:
wxConfigBase::Set(new wxFileConfig("Astade.ini"));
wxCmdLineParser CmdLineParser(argc, const_cast<char**>(argv));

CmdLineParser.AddParam("model_node", wxCMD_LINE_VAL_STRING, wxCMD_LINE_OPTION_MANDATORY);
CmdLineParser.AddSwitch("e", "externals", "show external relations");
CmdLineParser.AddSwitch("s", "all-classes", "include scope outside of active component");
CmdLineParser.AddOption("a", "attributes", "attribute display level (0..3)", wxCMD_LINE_VAL_NUMBER);
CmdLineParser.AddOption("o", "operations", "operation display level (0..3)", wxCMD_LINE_VAL_NUMBER);

CmdLineParser.SetLogo("OMDgenerator: the \"Object Model Diagram generator\"\n"
	"from the Astade project (astade.tigris.org)\n"
	"Copyright (C) 2005  Thomas Spitzer and Anders Larsen\n\n"
	"This program is distributed in the hope that it will be useful,\n"
	"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
	"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
	"GNU General Public License for more details.\n\n"
	"To contact the author, mail to: dev@astade.tigris.org\n");

if (CmdLineParser.Parse() == 0 && CmdLineParser.GetParamCount() == 1)
{
	long verbosity;
	if (CmdLineParser.Found("a", &verbosity))
	{
		if (verbosity < 0 || verbosity > 3)
		{
			CmdLineParser.Usage();
			return EXIT_FAILURE;
		}
		showattr = static_cast<tVisibility>(verbosity);
	}
	if (CmdLineParser.Found("o", &verbosity))
	{
		if (verbosity < 0 || verbosity > 3)
		{
			CmdLineParser.Usage();
			return EXIT_FAILURE;
		}
		showoper = static_cast<tVisibility>(verbosity);
	}
	showall = CmdLineParser.Found("s");
	showext = CmdLineParser.Found("e");
	std::cout << "digraph G {"
		<< std::endl;
	std::cout << "\tnode [shape=box, fontname=arial, fontsize=10]"
		<< std::endl;
	wxFileName base(CmdLineParser.GetParam(0));
	AdeClass element(base);
	ListNodes(1, wxEmptyString, &element);
	ListEdges(wxEmptyString, &element);
	std::cout << '}'
		<< std::endl;
	return EXIT_SUCCESS;
}
return EXIT_FAILURE;
