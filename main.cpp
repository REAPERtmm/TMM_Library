#include <TMM_Debugger.h>
#include <TMM_AudioOutput.h>

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

	//const char* INPUT_WAV_FILE = "res/Fish Spinning.wav";
	//const char* OUTPUT_WAV_FILE_CUT = "res/cutted.wav";

	//TMM::FileParser_WAV* pParser;
	//TMM::FileContent_WAV* pContent;

	//pParser = new TMM::FileParser_WAV();
	//TMM::ERROR_CODE code = pParser->Parse(INPUT_WAV_FILE);
	//if (TMM_FAILED(code))
	//{
	//	LOG_ERROR << "Failed to Parse " << INPUT_WAV_FILE << ENDL;
	//	return 1;
	//}

	//pContent = (TMM::FileContent_WAV*)pParser->GetContentRef();
	//auto pCutted = pContent->CutRemove(0.0f, 8.0f);

	//code = pParser->Serialize(OUTPUT_WAV_FILE_CUT, pCutted);
	//if (TMM_FAILED_WITH(code, TMM::PARSING::ERROR_OPEN))
	//{
	//	LOG_ERROR << "Failed to open " << OUTPUT_WAV_FILE_CUT << ENDL; 
	//	return 1;
	//}
	//else if (TMM_FAILED_WITH(code, TMM::PARSING::ERROR_WRITE))
	//{
	//	LOG_ERROR << "Failed to write " << OUTPUT_WAV_FILE_CUT << ENDL;
	//	return 1;
	//}

	//delete pContent;
	//delete pParser;
	//delete pCutted;

	TMM::AudioOutput audio;
	audio.Init();

	TMM::AudioData* data = new TMM::AudioData();

	TMM::FileParser_WAV parser;
	parser.Parse("res/Fish Spinning.wav");
	auto fish = (TMM::FileContent_WAV*)parser.GetContentRef();
	fish->Reverse();

	auto err = audio.CreateAudioFromContent(fish, data);
	if (FAILED(err)) {
		LOG_ERROR << "Failed to create Audio" << ENDL;
	}
	else {
		audio.Play(*data);
	}

	while (true) {
		XAUDIO2_VOICE_STATE state = (*data).GetState();
		if (state.BuffersQueued == 0) break;
		Sleep(100);
	}

	audio.UnInit();
	DBG_UNINIT();

	return 0;
}
