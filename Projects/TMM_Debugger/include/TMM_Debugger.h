#pragma once

// REQUIRED internal include
#include <TMM_Setup.h>
#include <TMM_BitMask.h>

// NOT REQUIRED internal include
#ifdef TMM_DEBUGGER_FILES_ENABLE
#include <TMM_OFile.h>
#endif
#ifdef TMM_DEBUGGER_MATHS_ENABLE
#include <TMM_Vectors.h>
#endif

// REQUIRED external include
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include <string>

#ifdef __ // NDEBUG
#define DBG_INIT	if(true) {} else TMM::Debugger::Init
#define LOG_INFO	if(true) {} else *TMM::Debugger::Get(TMM::DEBUGGER_FLAGS::DBG_INFO)	<< "[INFO   ] "
#define LOG_SYSTEM	if(true) {} else *TMM::Debugger::Get(TMM::DEBUGGER_FLAGS::DBG_SYSTEM)	<< "[SYSTEM ] "
#define LOG_WARNING if(true) {} else *TMM::Debugger::Get(TMM::DEBUGGER_FLAGS::DBG_WARNING)	<< "[WARNING] "
#define LOG_ERROR	if(true) {} else TMM::Debugger::Get(TMM::DEBUGGER_FLAGS::DBG_ERROR)->RegisterError(__LINE__, __FUNCTION__, __FILE__)	<< "[ERROR  ] "
#define ENDL		TMM::TMM_ENDL()
#define DBG_UNINIT	if(true) {} else TMM::Debugger::UnInit
#else
#define DBG_INIT	TMM::Debugger::Init
#define LOG_INFO	*TMM::Debugger::Get(TMM::DEBUGGER_FLAGS::DBG_INFO)	<< "[INFO   ] "
#define LOG_SYSTEM	*TMM::Debugger::Get(TMM::DEBUGGER_FLAGS::DBG_SYSTEM)	<< "[SYSTEM ] "
#define LOG_WARNING *TMM::Debugger::Get(TMM::DEBUGGER_FLAGS::DBG_WARNING)	<< "[WARNING] "
#define LOG_ERROR	TMM::Debugger::Get(TMM::DEBUGGER_FLAGS::DBG_ERROR)->RegisterError(__LINE__, __FUNCTION__, __FILE__)	<< "[ERROR  ] "
#define ENDL		TMM::TMM_ENDL()
#define DBG_UNINIT	TMM::Debugger::UnInit
#endif // NDEBUG

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
#ifdef TMM_DEBUGGER_FILES_ENABLE
	TMM_ADD_MASK(2, OUTPUT_LOGS)
#endif
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

#ifdef TMM_DEBUGGER_FILES_ENABLE
		TMM::OFile* mpOutputFile;
#endif

		bool mIsRegisteringError = false;
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

#ifdef TMM_DEBUGGER_MATHS_ENABLE

		template<typename T>
		Debugger& operator << (const TMM::Vec2<T>& other) {
			return *this << '(' << other.x << ", " << other.y << ')';
		}

		template<typename T>
		Debugger& operator << (const TMM::Vec3<T>& other) {
			return *this << '(' << other.x << ", " << other.y << ", " << other.z << ')';
		}

		template<typename T>
		Debugger& operator << (const TMM::Vec4<T>& other) {
			return *this << '(' << other.x << ", " << other.y << ", " << other.z << ", " << other.w << ')';
		}

#endif // TMM_DEBUGGER_MATHS_ENABLE

		Debugger& operator << (TMM_ENDL other);

		Debugger& RegisterError(uint64_t line, const char* functionName, const char* fileName);
	};


}
