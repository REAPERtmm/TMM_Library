#include <TMM_Debugger.h>
#include <TMM_Vectors.h>
#include <TMM_Matrices.h>

#pragma comment(lib, "Winmm.lib")

int main(int argc, char* argv[]) 
{
#ifndef NDEBUG
	auto tmp = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	tmp |= _CRTDBG_LEAK_CHECK_DF;
	_CrtSetDbgFlag(tmp);

	TMM::BitMask<TMM::DEBUGGER_FLAGS> flags = TMM::DEBUGGER_FLAGS::ALL;
	TMM::BitMask<TMM::DEBUGGER_OUTPUT> outputs;
	outputs |= TMM::DEBUGGER_OUTPUT::OUTPUT_CONSOLE;
	outputs |= TMM::DEBUGGER_OUTPUT::OUTPUT_LOGS;
	DBG_INIT(flags, outputs, true);
#else
	TMM::BitMask<TMM::DEBUGGER_FLAGS> flags = TMM::DEBUGGER_FLAGS::ALL;
	TMM::BitMask<TMM::DEBUGGER_OUTPUT> outputs = TMM::DEBUGGER_OUTPUT::OUTPUT_CONSOLE;
	outputs |= TMM::DEBUGGER_OUTPUT::OUTPUT_LOGS;
	DBG_INIT(flags, outputs, true);
#endif // !NDEBUG


	TMM::Matf4x4 mat44_0;
	TMM::Matf4x4 mat44_1(
		1.0f, 9.0f, 3.0f, 9.0f,
		9.0f, 6.0f, 7.0f, 8.0f,
		4.0f, 2.0f, 3.0f, 8.0f,
		5.0f, 6.0f, 7.0f, 8.0f
	);

	auto m = mat44_0 + mat44_1;
	float det = m.Determinant();
	
	DBG_UNINIT();

	return 0;
}
