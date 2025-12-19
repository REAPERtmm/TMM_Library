#pragma once

#include <TMM_Setup.h>
#include <TMM_BitMask.h>
#include <TMM_OFile.h>

#include <Windows.h>
#include <iostream>
#include <string>

#define DBG_INIT	TMM::Debugger::Init
#define LOG_INFO	*TMM::Debugger::Get(TMM::DEBUGGER_FLAGS::DBG_INFO)	<< "[INFO   ] "
#define LOG_SYSTEM	*TMM::Debugger::Get(TMM::DEBUGGER_FLAGS::DBG_SYSTEM)	<< "[SYSTEM ] "
#define LOG_WARNING *TMM::Debugger::Get(TMM::DEBUGGER_FLAGS::DBG_WARNING)	<< "[WARNING] "
#define LOG_ERROR	TMM::Debugger::Get(TMM::DEBUGGER_FLAGS::DBG_ERROR)->RegisterError(__LINE__, __FUNCTION__, __FILE__)	<< "[ERROR  ] "
#define ENDL		TMM::TMM_ENDL()
#define DBG_UNINIT	TMM::Debugger::UnInit

namespace TMM {

	TMM_START_BITMASK(DEBUGGER_FLAGS)
	TMM_ADD_MASK(0, DBG_INFO)
	TMM_ADD_MASK(1, DBG_SYSTEM)
	TMM_ADD_MASK(2, DBG_WARNING)
	TMM_ADD_MASK(3, DBG_ERROR)
	TMM_END_BITMASK();

	TMM_START_BITMASK(DEBUGGER_OUTPUT)
	TMM_ADD_MASK(0, OUTPUT_CONSOLE)
	TMM_ADD_MASK(1, OUTPUT_DEBUGGER)
	TMM_ADD_MASK(2, OUTPUT_LOGS)
	TMM_END_BITMASK();

	struct DEBUGGER_DESCRIPTOR
	{
		BitMask<DEBUGGER_FLAGS> Flags;
		BitMask<DEBUGGER_OUTPUT> Output;
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
		BitMask<DEBUGGER_FLAGS> mCurrentFlag = DEBUGGER_FLAGS::NONE;

		DEBUGGER_DESCRIPTOR mDescriptor;

		TMM::OFile* mpOutputFile;

		ERROR_DESCRIPTOR* mErrors;
		uint8_t mErrorIndex = 0;

		bool mThreadSafetyEnabled;
		CRITICAL_SECTION mCS;

		Debugger();
		~Debugger();

		void DisplayError(uint32_t index);

		void OutputString(const char* txt);
		void OutputString(const char* txt, uint64_t length);

		static Debugger* InternalGet(DEBUGGER_FLAGS flags);
	public:
		static Debugger* Get(DEBUGGER_FLAGS flags);
		static bool Init(const BitMask<DEBUGGER_FLAGS>& flags, const BitMask<DEBUGGER_OUTPUT>& output, bool threadSafe = false);
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
