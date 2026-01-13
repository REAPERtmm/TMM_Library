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

	const char* INPUT_WAV_FILE = "res/sea.wav";
	const char* OUTPUT_WAV_FILE_CUT = "res/cutted.wav";

	TMM::FileParser_WAV* pParser;
	TMM::FileContent_WAV* pContent;

	pParser = new TMM::FileParser_WAV();
	TMM::ERROR_CODE code = pParser->Parse(INPUT_WAV_FILE);
	if (TMM_FAILED(code))
	{
		LOG_ERROR << "Failed to Parse " << INPUT_WAV_FILE << ENDL;
	}

	pContent = (TMM::FileContent_WAV*)pParser->GetContentRef();
	auto pCutted = pContent->CutRemove(0.0f, 10.0f);
	pCutted->Amplify<short, 2.0f>();

	code = pParser->Serialize(OUTPUT_WAV_FILE_CUT, pCutted);
	if (TMM_FAILED_WITH(code, TMM::PARSING::ERROR_OPEN))
	{
		LOG_ERROR << "Failed to open " << OUTPUT_WAV_FILE_CUT << ENDL;
	}
	else if (TMM_FAILED_WITH(code, TMM::PARSING::ERROR_WRITE))
	{
		LOG_ERROR << "Failed to write " << OUTPUT_WAV_FILE_CUT << ENDL;
	}

	delete pContent;
	delete pParser;
	delete pCutted;

	DBG_UNINIT();

	return 0;
}
