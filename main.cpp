#include <TMM_Debugger.h>
#include <TMM_Functional.h>
#include <TMM_Container.h>

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

	int Start_offset = 10;
	A a;
	TMM::Container<5, int> data(0);

	TMM::Callable<bool, const uint64_t&, int&>* proc[3];
	// add Start_offset
	proc[0] = new TMM::LambdaMethod<bool, const uint64_t&, int&>(
		[&Start_offset](const uint64_t& index, int& value) -> bool { value = value + Start_offset; return true; }
	);

	// add 1
	proc[1] = new TMM::Function<bool, const uint64_t&, int&>(
		[](const uint64_t& index, int& value) { value = value + 1; return true; }
	);

	// add a::v
	proc[2] = new TMM::Method<A, bool, const uint64_t&, int&>(&a, &A::f);

	LOG_INFO << "START VALUES : " << ENDL;
	for (int i = 0; i < data.Size(); ++i)
	{
		LOG_INFO << "[" << i << "] = " << data[i] << ENDL;
	}

	data.Execute(*proc[0]);
	LOG_INFO << "FIRST PROC : " << ENDL;
	for (int i = 0; i < data.Size(); ++i)
	{
		LOG_INFO << "[" << i << "] = " << data[i] << ENDL;
	}

	data.Execute(*proc[1]);
	LOG_INFO << "SECOND PROC : " << ENDL;
	for (int i = 0; i < data.Size(); ++i)
	{
		LOG_INFO << "[" << i << "] = " << data[i] << ENDL;
	}

	data.Execute(*proc[2]);
	LOG_INFO << "THIRD PROC : " << ENDL;
	for (int i = 0; i < data.Size(); ++i)
	{
		LOG_INFO << "[" << i << "] = " << data[i] << ENDL;
	}

	delete proc[0];
	delete proc[1];
	delete proc[2];

	DBG_UNINIT();

	return 0;
}
