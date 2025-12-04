#include <TMM_Setup.h>
#include <TMM_Debugger.h>
#include <TMM_OFile.h>
#include <TMM_Thread.h>
#include <TMM_ThreadList.h>

#pragma comment(lib, "Winmm.lib")

#define TEST_FILE_T TMM::OFile

struct MyStruct {
	int* pData;
	int dataSize;
	int start;
	int end;
};

bool CreateSuite(TMM::ThreadArg<MyStruct>* pArg) {
	for (int i = pArg->pData->start; i < pArg->pData->end; ++i) {
		pArg->pData->pData[i] = i;
		Sleep(1); // Fake work
	}
	return true;
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

	int time = timeGetTime();

	int threadCount = 64;
	int countMax = 1280;
	int subDivide = countMax / threadCount;
	int* suite = new int[countMax];

	TMM::ThreadArg<MyStruct>* args = new TMM::ThreadArg<MyStruct>[threadCount];

	for (int i = 0; i < threadCount; ++i) {
		args[i].layer = 0;
		args[i].pData = new MyStruct{ suite, countMax, i * subDivide, (i + 1) * subDivide };
	}
	auto func = TMM::MakeFunction(CreateSuite);

	TMM::ThreadList<MyStruct> mThreadList(threadCount, args, &func);

	delete[] args;

	mThreadList.Update();
	mThreadList.TerminateWait();

	int time2 = timeGetTime();

	for (int i = 0; i < countMax; ++i) {
		LOG_INFO << "at " << i << " : " << suite[i] << ENDL;
	}

	LOG_INFO << "The Simulation runned in : " << time2 - time << " ms" << ENDL;

	delete[] suite;

	DBG_UNINIT();

	return 0;
}
