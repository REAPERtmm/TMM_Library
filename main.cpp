#include <TMM_Debugger.h>
#include <TMM_BitField.h>

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

	unsigned char mask = TMM_BITFIELD_MASK(
		TMM_OFF, TMM_ON, TMM_OFF, TMM_ON, TMM_OFF, TMM_ON, TMM_OFF, TMM_ON, TMM_OFF, TMM_ON
	);

	TMM::BitField field;
	field.ApplyOr(mask);

	for (int i = 0; i < 8; ++i) {
		LOG_INFO << "Le bit " << i << " : " << field.Get(i) << ENDL;
	}
	
	DBG_UNINIT();

	return 0;
}
