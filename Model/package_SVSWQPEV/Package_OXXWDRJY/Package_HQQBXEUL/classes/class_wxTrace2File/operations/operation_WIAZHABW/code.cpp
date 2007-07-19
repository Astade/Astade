#define LOG_OUT_BUF_SIZE 1024
	// platz f�r den Ausgabestring
	char OutBuffer[LOG_OUT_BUF_SIZE];
	memset(OutBuffer,0,LOG_OUT_BUF_SIZE);
	int nRet;

	// Argumenteliste v�r eine variable Anzahl von
	// Funktionsargumenten erzeugen
	va_list ap;
	va_start(ap, fmt);

	// Ausgeben mit Lib-Funktion
	nRet=vsprintf(OutBuffer, fmt, ap );

	// Argumenteliste aufr�umen
	va_end( ap);              /* Reset variable arguments.      */
	// ausgeben
	OutBuffer[nRet]=0;
	std::string s(OutBuffer);

	if (!pause_output && ms_ofile.is_open())
		ms_ofile  << "#" << s << std::endl;
	return nRet;