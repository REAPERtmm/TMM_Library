#include <TMM_Setup.h>
#include <TMM_Debugger.h>
#include <TMM_OFile.h>
#include <TMM_Thread.h>

#define TEST_FILE_T TMM::OFile

DWORD WriteInFileAsync(TMM::ThreadContext<TEST_FILE_T>* ctx) {
	TMM::OFile* pFile = ctx->UnsafeData();
	
	for (size_t i = 0; i < 100; i++)
	{
		pFile->Write("Les oiseaux s'envolent", 20);
	}

	return ctx->ExitWithStatus(TMM::SUCESS);
}

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

	TMM::Thread thread1("Write 1");
	TMM::Thread thread2("Write 2");

	TEST_FILE_T oFile("log.txt");
	oFile.ClearAndOpen();
	oFile.Open();

	auto threadProc = TMM::MakeFunction(WriteInFileAsync);

	thread1.Start(&threadProc, &oFile);
	thread2.Start(&threadProc, &oFile);
	thread1.TerminateWait();
	thread2.TerminateWait();

	oFile.Close();

	DBG_UNINIT();

	return 0;
}
