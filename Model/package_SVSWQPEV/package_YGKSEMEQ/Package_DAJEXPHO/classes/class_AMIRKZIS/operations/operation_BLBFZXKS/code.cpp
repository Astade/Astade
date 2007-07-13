fprintf(specificationFile, "\t\t//! \\brief Constructor.\n");
fprintf(specificationFile, "\t\t%s();\n\n", (const char*)theStatechart.GetName().c_str());

fprintf(specificationFile, "\t\t//! \\brief Destructor.\n");
fprintf(specificationFile, "\t\tvirtual ~%s();\n\n", (const char*)theStatechart.GetName().c_str());

fprintf(implementationFile, "%s::%s() : wxTimer(this, TIMER_ID)\n{\n\ttheState = &%s::NoState;\n", (const char*)theStatechart.GetName().c_str(), (const char*)theStatechart.GetName().c_str(), (const char*)theStatechart.GetName().c_str());
fprintf(implementationFile, "\tnextState = 0;\n}\n\n");

fprintf(implementationFile, "%s::~%s()\n{\n}\n\n", (const char*)theStatechart.GetName().c_str(), (const char*)theStatechart.GetName().c_str());
