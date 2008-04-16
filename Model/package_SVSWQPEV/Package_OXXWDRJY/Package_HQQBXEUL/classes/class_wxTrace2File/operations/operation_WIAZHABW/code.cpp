#define LOG_OUT_BUF_SIZE 1024

// platz f�r den Ausgabestring
char OutBuffer[LOG_OUT_BUF_SIZE];
memset(OutBuffer,0,LOG_OUT_BUF_SIZE);

// Argumenteliste v�r eine variable Anzahl von
// Funktionsargumenten erzeugen
va_list ap;
va_start(ap, fmt);

// Ausgeben mit Lib-Funktion
int nRet = vsprintf(OutBuffer, fmt, ap);
// Argumenteliste aufr�umen
va_end( ap);

// ausgeben
std::string s(OutBuffer);

if (ms_ofile.is_open())
	ms_ofile  << "#" << s << std::endl;
return nRet;
