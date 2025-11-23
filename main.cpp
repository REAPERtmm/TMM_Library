#include <TMM_Setup.h>
#include <TMM_Debugger.h>
#include <TMM_Threading.h>

DWORD TestThread(TMM::ThreadHandle* phandle) {
	LOG_INFO << "Hello I'm the thread, my Name is " << phandle->GetName() << " and my ID is " << phandle->GetCurrentThread()->GetID() << ENDL;
	return phandle->ExitWithStatus(TMM::ThreadStatusCode::SUCESS);
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

	auto thread_f = TMM::MakeFunction(TestThread);

	TMM::Thread t_1(
		"T_1",	// Name
		true	// start Paused
	);
	TMM::Thread t_2(
		"T_2"	// Name
				// start Not Paused
	);
	t_1.Start(&thread_f);	// => Start but paused !
	t_2.Start(&thread_f);	// => Start and execute !

	t_2.TerminateWait();	// => Execute T_2
	
	t_1.Resume();
	t_1.TerminateWait();	// => Execute T_1 only when T_2 is ended

	t_2.Start(&thread_f);
	t_2.TerminateWait();	// => Execute T_2 again only when T_1 is ended

	DBG_UNINIT();

	return 0;
}
