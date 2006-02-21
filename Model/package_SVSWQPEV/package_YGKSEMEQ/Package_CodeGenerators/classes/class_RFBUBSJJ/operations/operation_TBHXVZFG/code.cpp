FILE* f;
target.SetExt("cpp");
f = fopen(target.GetFullPath().c_str(),"w");
fprintf(f,"//******************************************************\n");
fprintf(f,"//** Code generated by the Astade CppGenerator        **\n");
fprintf(f,"//** Filename: %-39s**\n",target.GetFullName().c_str());
fprintf(f,"//******************************************************\n\n");

wxFileName PrefixName(source->GetFileName());
PrefixName.SetFullName("prolog.cpp");
wxTextFile prefixtext(PrefixName.GetFullPath());

if (prefixtext.Exists())
    prefixtext.Open();

if (prefixtext.IsOpened() )
{
    wxString str;
    fprintf(f,"//****** implementation prolog ******\n");
    for ( str = prefixtext.GetFirstLine(); !prefixtext.Eof(); str = prefixtext.GetNextLine() )
    {
        fprintf(f,"%s\n",str.c_str());
    }
    if (str.size())
        fprintf(f,"%s\n",str.c_str());
    fprintf(f,"//***********************************\n");
}

target.SetExt("h");
fprintf(f,"#include \"%s\" // own header\n\n",target.GetFullName().c_str());

RelationIncludes(f,false,NULL);
staticAttribute(f,false,ITEM_IS_PUBLIC);
staticAttribute(f,false,ITEM_IS_PROTECTED);
staticAttribute(f,false,ITEM_IS_PRIVATE);
operations(f,false,ITEM_IS_PUBLIC);
operations(f,false,ITEM_IS_PROTECTED);
operations(f,false,ITEM_IS_PRIVATE);

wxFileName PostfixName(source->GetFileName());
PostfixName.SetFullName("epilog.cpp");
wxTextFile postfixtext(PostfixName.GetFullPath());

if (postfixtext.Exists())
    postfixtext.Open();

if (postfixtext.IsOpened() )
{
    wxString str;
    fprintf(f,"//****** implementation epilog ******\n");
    for (str = postfixtext.GetFirstLine(); !postfixtext.Eof(); str = postfixtext.GetNextLine())
    {
        fprintf(f,"%s\n",str.c_str());
    }
    if (str.size())
        fprintf(f,"%s\n",str.c_str());
    fprintf(f,"//***********************************\n");
}

fclose(f);
