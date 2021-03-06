//~~ void doCpp() [CppGenerator] ~~

target.SetExt(wxS("cpp"));
std::ofstream out(target.GetFullPath().utf8_str());

wxFileName PrefixName(myAdeComponent->GetFileName());
PrefixName.SetFullName(wxS("prolog.cpp"));
wxTextFile Gprefixtext(PrefixName.GetFullPath());
if (Gprefixtext.Exists())
    Gprefixtext.Open();
if (Gprefixtext.IsOpened() && Gprefixtext.GetLineCount() > 0)
{
    wxString str;
    for (str = Gprefixtext.GetFirstLine(); !Gprefixtext.Eof(); str = Gprefixtext.GetNextLine())
        out << str.utf8_str() << std::endl;
    if (!str.empty())
        out << str.utf8_str() << std::endl;
    out << std::endl;
}

PrintHeader(out);

PrefixName = source->GetFileName();
PrefixName.SetFullName(wxS("prolog.cpp"));
wxTextFile prefixtext(PrefixName.GetFullPath());
PrefixName.MakeRelativeTo();

if (prefixtext.Exists())
    prefixtext.Open();
if (prefixtext.IsOpened() && prefixtext.GetLineCount() > 0)
{
    wxString str;
    out << "//****** implementation prolog ******" << std::endl;
    out << "//[" << PrefixName.GetFullPath(wxPATH_UNIX).utf8_str()
        <<   "]" << std::endl;
    for (str = prefixtext.GetFirstLine(); !prefixtext.Eof(); str = prefixtext.GetNextLine())
        out << str.utf8_str() << std::endl;
    if (!str.empty())
        out << str.utf8_str() << std::endl;
    out << "//[EOF]" << std::endl;
    out << "//***********************************" << std::endl;
    out << std::endl;
}

target.SetExt(wxS("h"));
out << "#include \"" << target.GetFullName().utf8_str();
out << "\"\t // own header" << std::endl;
out << std::endl;

RelationIncludes(out, false, NULL);

out << "//****** Trace Macros ***************" << std::endl;
out << "#ifndef NOTIFY_CONSTRUCTOR" << std::endl;
out << "///@brief Empty definition of a trace macro, so the code compiles with no trace, too." << std::endl;
out << "#  define NOTIFY_CONSTRUCTOR(a,b,c)" << std::endl;
out << "#endif" << std::endl;

out << "#ifndef NOTIFY_DESTRUCTOR" << std::endl;
out << "///@brief Empty definition of a trace macro, so the code compiles with no trace, too." << std::endl;
out << "#  define NOTIFY_DESTRUCTOR(a,b)" << std::endl;
out << "#endif" << std::endl;

out << "#ifndef NOTIFY_FUNCTION_CALL" << std::endl;
out << "///@brief Empty definition of a trace macro, so the code compiles with no trace, too." << std::endl;
out << "#  define NOTIFY_FUNCTION_CALL(a,b,c,d,e,f)" << std::endl;
out << "#endif" << std::endl;

out << "#ifndef NOTIFY_RETURN_VALUE" << std::endl;
out << "///@brief Empty definition of a trace macro, so the code compiles with no trace, too." << std::endl;
out << "#  define NOTIFY_RETURN_VALUE(a)" << std::endl;
out << "#endif" << std::endl;

out << "#ifndef RETURN" << std::endl;
out << "///@brief Empty definition of a trace macro, so the code compiles with no trace, too." << std::endl;
out << "#  define RETURN(a) return(a)" << std::endl;
out << "#endif" << std::endl << std::endl;

out << "#ifndef LOG" << std::endl;
out << "///@brief Empty definition of a trace macro, so the code compiles with no trace, too." << std::endl;
out << "#  define LOG(...)" << std::endl;
out << "#endif" << std::endl << std::endl;


if (!source->IsManualClass())
{
    staticAttribute(out, false, ITEM_IS_PUBLIC);
    staticAttribute(out, false, ITEM_IS_PROTECTED);
    staticAttribute(out, false, ITEM_IS_PRIVATE);
    relationAttribute(out, false);
    operations(out, false, false, ITEM_IS_PUBLIC);
    operations(out, false, false, ITEM_IS_PROTECTED);
    operations(out, false, false, ITEM_IS_PRIVATE);

    if (inheritsFromStatechart) // this is tested during relation coding
    {
        out << "#ifdef ASTADE_STATECHART_IMPLEMENTATION" << std::endl;
        out << "\tASTADE_STATECHART_IMPLEMENTATION(\""
            << source->GetName().utf8_str()
            << "\")" << std::endl;
        out << "#endif"	<< std::endl;
    }
}

wxFileName PostfixName(source->GetFileName());
PostfixName.SetFullName(wxS("epilog.cpp"));
wxTextFile postfixtext(PostfixName.GetFullPath());
PostfixName.MakeRelativeTo();

if (!hasConstructor)
    CodePortConnectionWarning(out);

if ((!hasConstructor) && (!memberDefaults.empty()))
    out << "#warning This class has default values for attributes but has no constructor. This will probably not work correctly." << std::endl;

if (postfixtext.Exists())
    postfixtext.Open();
if (postfixtext.IsOpened() && postfixtext.GetLineCount() > 0)
{
    out << "//****** implementation epilog ******" << std::endl;
    out << "//[" << PostfixName.GetFullPath(wxPATH_UNIX).utf8_str()
        <<   "]" << std::endl;
    wxString str;
    for (str = postfixtext.GetFirstLine(); !postfixtext.Eof(); str = postfixtext.GetNextLine())
        out << str.utf8_str() << std::endl;
    if (!str.empty())
        out << str.utf8_str() << std::endl;
    out << "//[EOF]" << std::endl;
    out << "//***********************************" << std::endl;
}

PostfixName = myAdeComponent->GetFileName();
PostfixName.SetFullName(wxS("epilog.cpp"));
wxTextFile Gpostfixtext(PostfixName.GetFullPath());
if (Gpostfixtext.Exists())
    Gpostfixtext.Open();
if (Gpostfixtext.IsOpened() && Gpostfixtext.GetLineCount() > 0)
{
    out << std::endl;
    wxString str;
    for (str = Gpostfixtext.GetFirstLine(); !Gpostfixtext.Eof(); str = Gpostfixtext.GetNextLine())
        out << str.utf8_str() << std::endl;
    if (!str.empty())
        out << str.utf8_str() << std::endl;
}

target.SetExt(wxS("cpp"));
out.close();

wxDateTime theTime(source->GetCodeModificationTime());
target.SetTimes(&theTime, &theTime, &theTime);
