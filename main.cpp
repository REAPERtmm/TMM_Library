#include <TMM_Setup.h>
#include <TMM_Debugger.h>
#include <TMM_AudioOutput.h>

#include <TMM_StateMachine.h>

#pragma comment(lib, "Winmm.lib")

struct A
{
	float x = 0;
	float y	= 0;
	float z	= 0;
};

struct Action_IncrementX : public TMM::Action<A>
{
	void Start(A* pObj, void* pData) override {}
	void Update(A* pObj, void* pData) override { pObj->x += *(float*)pData; }
	void End(A* pObj, void* pData) override {}
};

struct Action_IncrementY : public TMM::Action<A>
{
	void Start(A* pObj, void* pData) override { }
	void Update(A* pObj, void* pData) override { pObj->y += *(float*)pData; }
	void End(A* pObj, void* pData) override {}
};


struct Condition_X_SUP_Y : public TMM::Condition<A>
{
	virtual bool GetExpected() override { return true; };
	bool Check(A* pObj, void* pData) override { return pObj->x > pObj->y; };
};

struct Condition_Y_SUP_X : public Condition_X_SUP_Y
{
	bool GetExpected() override { return false; };
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

	//TMM::AudioOutput audio;
	//audio.Init();

	//TMM::AudioData* data = new TMM::AudioData();

	//TMM::FileParser_WAV parser;
	//parser.Parse("res/Fish Spinning.wav");
	//auto fish = (TMM::FileContent_WAV*)parser.GetContentRef();
	//fish->Reverse();

	//auto err = audio.CreateAudioFromContent(fish, data);
	//if (FAILED(err)) {
	//	LOG_ERROR << "Failed to create Audio" << ENDL;
	//}
	//else {
	//	audio.Play(*data);
	//}

	//while (true) {
	//	XAUDIO2_VOICE_STATE state = (*data).GetState();
	//	if (state.BuffersQueued == 0) break;
	//	Sleep(100);
	//}

	//audio.UnInit();

	A a;

	TMM::STATE_MACHINE_DESCRIPTOR desc{};
	desc.pObj = &a;
	desc.BASE_STATE_COUNT = 2;

	TMM::StateMachine<A> stateMachine(desc);

	auto state0 = stateMachine.GetState(0);
	auto  action00 = state0->AddAction<Action_IncrementX>();
	auto  action01 = state0->AddAction<Action_IncrementY>();
	auto transition0 = state0->CreateTransition(1);
	auto  condition0 = transition0->AddCondition<Condition_X_SUP_Y>();

	auto state1 = stateMachine.GetState(1);
	auto  action1 = state1->AddAction<Action_IncrementY>();
	auto transition1 = state1->CreateTransition(0);
	auto  condition1 = transition1->AddCondition<Condition_Y_SUP_X>();

	LOG_INFO << "x : " << a.x << ", y : " << a.y << ", z : " << a.z << ENDL;

	float factor = 2.5;
	TMM_ITER(_, 10)
	{
		stateMachine.Update(&factor);
		LOG_INFO << "x : " << a.x << ", y : " << a.y << ", z : " << a.z << ENDL;
	}

	DBG_UNINIT();

	return 0;
}
