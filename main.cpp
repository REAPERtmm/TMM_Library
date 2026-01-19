#include <TMM_Setup.h>
#include <TMM_Debugger.h>
#include <TMM_AudioOutput.h>

#include <TMM_StateMachine.h>

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

	TMM::IFile txt("res/aaa.txt");

	if (txt.Open() == false) {
		LOG_INFO << "NO FILE FOUND" << ENDL;
	}
	else {
		LOG_INFO << "FILE FOUND" << ENDL;
	}

	//TMM::AudioOutput audio;
	//audio.Init();

	//TMM::AudioData* data = new TMM::AudioData();

	//TMM::FileParser_WAV parser;
	//parser.Parse("res/YOUUSEDTOCALLMEONMYCELLPHONE.wav");
	//auto YOUUSEDTOCALLMEONMYCELLPHONE = (TMM::FileContent_WAV*)parser.GetContentRef();

	//auto out = YOUUSEDTOCALLMEONMYCELLPHONE->CutKeep(31.0f, 51.0f);
	//delete YOUUSEDTOCALLMEONMYCELLPHONE;
	//YOUUSEDTOCALLMEONMYCELLPHONE = out;

	//out = YOUUSEDTOCALLMEONMYCELLPHONE->Translate<float>();
	//delete YOUUSEDTOCALLMEONMYCELLPHONE;
	//YOUUSEDTOCALLMEONMYCELLPHONE = out;

	//parser.Serialize("res/YOUUSEDTOCALLMEONMYCELLPHONE2.wav", YOUUSEDTOCALLMEONMYCELLPHONE);
	//delete YOUUSEDTOCALLMEONMYCELLPHONE;

	//delete data;

	DBG_UNINIT();

	return 0;
}
