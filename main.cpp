#include <TMM_Debugger.h>
#include <TMM_BitField.h>
#include <TMM_OrderedArray.h>
#include <TMM_Stack.h>

#pragma comment(lib, "Winmm.lib")

bool Func(const uint64_t& i, int& value) {
	value++;
	return true;
}

bool Offset(int* left, int& value, int* right) {
	if (left == nullptr)
	{
		value = 0;
	}
	else {
		value = *left;
	}
	return true;
}

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

	// TODO : Profiler / Benchmark / Time Testings

	TMM::ArrayOrdered<int> arr;
	TMM::Stack<int> stack;
	auto f = TMM::MakeFunction(Offset);

	stack.PushStack(1);
	stack.PushStack(2);
	stack.PushStack(3);
	stack.PushStack(4);
	stack.PushStack(5);
	stack.Execute(f);

	arr.Add(1);
	arr.Add(2);
	arr.Add(3);
	arr.Add(4);
	arr.Add(5);
	
	for (int i = 0; i < arr.Size(); ++i) {
		LOG_INFO << "[" << i << "] = " << arr[i] << ENDL;
	}

	for (int i = 0; i < arr.Size(); ++i) {
		LOG_INFO << "[STACK] = " << stack.PopStack() << ENDL;
	}

	DBG_UNINIT();

	return 0;
}
