#pragma once
#include <TMM_Setup.h>

#include <cstdio>
#include <Windows.h>
#include <iostream>
#include <string>

#define DBG_INIT	TMM::Debugger::Init
#define LOG_INFO	*TMM::Debugger::Get(DBG_INFO)	<< "[INFO   ] "
#define LOG_SYSTEM	*TMM::Debugger::Get(DBG_SYSTEM)	<< "[SYSTEM ] "
#define LOG_WARNING *TMM::Debugger::Get(DBG_WARNING)	<< "[WARNING] "
#define LOG_ERROR	TMM::Debugger::Get(DBG_ERROR)->RegisterError(__LINE__, __FUNCTION__, __FILE__)	<< "[ERROR  ] "
#define ENDL		TMM::TMM_ENDL()
#define DBG_UNINIT	TMM::Debugger::UnInit

// Uncomment this to make the debugger ThreadSafe 
// #define ENABLE_DBG_THREAD_SAFE

enum DEBUGGER_FLAGS
{
	DBG_NONE = 0b00000000,

	DBG_INFO = 0b00000001,
	DBG_SYSTEM = 0b00000010,
	DBG_WARNING = 0b00000100,
	DBG_ERROR = 0b00001000,

	DBG_ALL = 0b11111111,
};

enum DEBUGGER_OUTPUT
{
	OUTPUT_CONSOLE,
	OUTPUT_DEBUGGER,
	OUTPUT_LOGS,
};

namespace TMM {
	struct DEBUGGER_DESCRIPTOR
	{
		uint32_t Flags;
		uint32_t Output;
	};

	struct TMM_ENDL {
		static const char Symbol = '\n';
	};

	class Debugger {

		struct ERROR_DESCRIPTOR {
			std::string ErrorMsg = {};
			uint64_t Line = 0;
			const char* FunctionName = "";
			const char* FileName = "";
		};

		bool mIsInit = false;

		bool mCurrentValid = false;
		DEBUGGER_FLAGS mCurrentFlag = DBG_NONE;

		DEBUGGER_DESCRIPTOR mDescriptor;

		FILE* pFile = nullptr;

		ERROR_DESCRIPTOR* mErrors;
		uint8_t mErrorIndex = 0;

#ifdef ENABLE_DBG_THREAD_SAFE
		CRITICAL_SECTION mCS;
#endif // ENABLE_DBG_THREAD_SAFE

		Debugger();
		~Debugger();

		void DisplayError(uint32_t index);

		void OutputString(const char* txt);
		void OutputString(const char* txt, uint64_t length);

		static Debugger* InternalGet(DEBUGGER_FLAGS flags);
	public:
		static Debugger* Get(DEBUGGER_FLAGS flags);
		static bool Init(uint32_t flags, uint32_t output);
		static void UnInit();

		Debugger& operator << (const char* other);
		Debugger& operator << (char other);

		Debugger& operator << (float other);
		Debugger& operator << (double other);

		Debugger& operator << (uint8_t other);
		Debugger& operator << (uint16_t other);
		Debugger& operator << (uint32_t other);
		Debugger& operator << (uint64_t other);

		Debugger& operator << (int8_t other);
		Debugger& operator << (int16_t other);
		Debugger& operator << (int32_t other);
		Debugger& operator << (int64_t other);

		Debugger& operator << (TMM_ENDL other);

		Debugger& RegisterError(uint64_t line, const char* functionName, const char* fileName);
	};


}
