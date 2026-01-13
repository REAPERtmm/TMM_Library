#include <TMM_Debugger.h>
#include <TMM_WAVParser.h>

#include <vector>
#include <cmath>

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

	const char* WAV_FILE = "res/Haydn_94_Andante.wav";

	TMM::Parser_WAV* pParser;
	TMM::FileContent_WAV* pContent;

	pParser = new TMM::Parser_WAV();
	TMM::ERROR_CODE code = pParser->Parse(WAV_FILE);
	if (TMM_FAILED(code))
	{
		LOG_INFO << "Failed to Parse " << WAV_FILE << ENDL;
	}
	pContent = (TMM::FileContent_WAV*)pParser->GetContentRef();
	pContent->Cut(0.0f, 10.0f);

	pParser->Serialize("res/cutted.wav", pContent);

	delete pContent;
	delete pParser;

	DBG_UNINIT();

	return 0;
}
