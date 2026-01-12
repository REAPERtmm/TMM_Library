#include <TMM_Debugger.h>
#include <TMM_WAVParser.h>

#pragma comment(lib, "Winmm.lib")

struct A
{
	int v = 5;
	bool f(const uint64_t& index, int& value) {
		value = value + v;
		return true;
	}
};

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


	TMM::Parser_WAV parser;
	if (TMM_FAILED(parser.Parse("myaudio.wav"))) {
		LOG_INFO << "Failed to parse file" << ENDL;
	}
	auto pFileContent = parser.GetContentRef();

	DBG_UNINIT();

	return 0;
}
