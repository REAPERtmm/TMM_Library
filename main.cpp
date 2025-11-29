#include <TMM_Setup.h>
#include <TMM_Debugger.h>
#include <TMM_OFile.h>

int main(int argc, char* argv[]) 
{
#ifndef NDEBUG
	auto tmp = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	tmp |= _CRTDBG_LEAK_CHECK_DF;
	_CrtSetDbgFlag(tmp);
	DBG_INIT(DBG_ALL, OUTPUT_CONSOLE);
#else
	DBG_INIT(DBG_ERROR, OUTPUT_DEBUGGER);
#endif // !NDEBUG

	TMM::OFile oFile("log.txt");
	oFile.ClearAndOpen();
	oFile.Open();

	oFile.Write("Les oiseaux chantent", 20);

	oFile.Close();

	DBG_UNINIT();

	return 0;
}
