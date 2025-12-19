#include "TMM_Debugger.h"
#include "TMM_Debugger.h"

namespace TMM {
	Debugger::Debugger()
	{
		mThreadSafetyEnabled = false;
		mErrors = new ERROR_DESCRIPTOR[32];
		mDescriptor = {};
		mIsInit = false;
	}

	Debugger::~Debugger()
	{
		if (mIsInit) {
			OutputDebugStringA("[/!\\] Forgot to Uninit Debugger !");
		}
	}

	void Debugger::DisplayError(uint32_t index)
	{
		if (index != 0) *Debugger::Get(DEBUGGER_FLAGS::DBG_ERROR) << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
		*Debugger::Get(DEBUGGER_FLAGS::DBG_ERROR) << "= Line     : " << mErrors[index].Line << '\n';
		*Debugger::Get(DEBUGGER_FLAGS::DBG_ERROR) << "= Function : " << mErrors[index].FunctionName << '\n';
		*Debugger::Get(DEBUGGER_FLAGS::DBG_ERROR) << "= File     : " << mErrors[index].FileName << '\n';
		*Debugger::Get(DEBUGGER_FLAGS::DBG_ERROR) << "= Msg      : " << '\n';
		*Debugger::Get(DEBUGGER_FLAGS::DBG_ERROR) << mErrors[index].ErrorMsg.c_str() << ENDL;
	}

	void Debugger::OutputString(const char* txt)
	{
		OutputString(txt, strlen(txt));
	}

	void Debugger::OutputString(const char* txt, uint64_t length)
	{
		if (mCurrentValid == false) return;

		if (mCurrentValid && mCurrentFlag.Contain(DEBUGGER_FLAGS::DBG_ERROR)) {
			mErrors[mErrorIndex].ErrorMsg += txt;
		}
		if (mDescriptor.Output.Contain(DEBUGGER_OUTPUT::OUTPUT_CONSOLE)) {
			std::cout << txt;
		}
		if (mDescriptor.Output.Contain(DEBUGGER_OUTPUT::OUTPUT_DEBUGGER)) {
			OutputDebugStringA(txt);
		}
		if (mDescriptor.Output.Contain(DEBUGGER_OUTPUT::OUTPUT_LOGS)) {
			if (mpOutputFile->Write(txt, length) == false) {
				mDescriptor.Output ^= DEBUGGER_OUTPUT::OUTPUT_LOGS;
				OutputString("Failed to write in logs : stopping the log feature");
			}
		}
	}

	Debugger* Debugger::InternalGet(DEBUGGER_FLAGS flags)
	{
		static Debugger debugger;
		debugger.mCurrentFlag = flags;
		debugger.mCurrentValid = debugger.mDescriptor.Flags.Contain(flags);
		return &debugger;
	}

	Debugger* Debugger::Get(DEBUGGER_FLAGS flag)
	{
		Debugger* pDebugger = InternalGet(flag);
		if (pDebugger->mThreadSafetyEnabled)
			EnterCriticalSection(&pDebugger->mCS);
		return pDebugger;
	}

	bool Debugger::Init(const BitMask<DEBUGGER_FLAGS>& flags, const BitMask<DEBUGGER_OUTPUT>& output, bool threadSafe)
	{
		Debugger* pDbg = InternalGet(DEBUGGER_FLAGS::NONE);
		pDbg->mThreadSafetyEnabled = threadSafe;
		if (pDbg->mThreadSafetyEnabled) {
			InitializeCriticalSection(&pDbg->mCS);
			EnterCriticalSection(&pDbg->mCS);
		}
		pDbg->mDescriptor.Flags = flags;
		pDbg->mDescriptor.Output = output;

		if (pDbg->mDescriptor.Output.Contain(DEBUGGER_OUTPUT::OUTPUT_LOGS)) {
			pDbg->mpOutputFile = new TMM::OFile("Logs.txt");
			if (pDbg->mpOutputFile->ClearAndOpen() == false) {
				pDbg->OutputString("Failed to open Logs");
				if(pDbg->mThreadSafetyEnabled)
					LeaveCriticalSection(&pDbg->mCS);
				return false;
			}
		}
		pDbg->mIsInit = true;
		if (pDbg->mThreadSafetyEnabled)
			LeaveCriticalSection(&pDbg->mCS);
		return true;
	}

	void Debugger::UnInit()
	{
		Debugger* pDbg = InternalGet(DEBUGGER_FLAGS::NONE);
		if (pDbg->mThreadSafetyEnabled)
			EnterCriticalSection(&pDbg->mCS);
		if (pDbg->mErrorIndex > 0) {
			*Debugger::Get(DEBUGGER_FLAGS::DBG_ERROR) << "============================\n\n";
			for (uint8_t i = 0; i < pDbg->mErrorIndex; ++i) {
				pDbg->DisplayError(i);
			}
			*Debugger::Get(DEBUGGER_FLAGS::DBG_ERROR) << "============================\n";
		}

		if (pDbg->mDescriptor.Output.Contain(DEBUGGER_OUTPUT::OUTPUT_LOGS)) {
			pDbg->mpOutputFile->Close();
			delete pDbg->mpOutputFile;
		}
		delete[] pDbg->mErrors;
		pDbg->mIsInit = false;
		if (pDbg->mThreadSafetyEnabled) {
			LeaveCriticalSection(&pDbg->mCS);
			DeleteCriticalSection(&pDbg->mCS);
		}
	}

	Debugger& Debugger::operator<<(const char* other)
	{
		OutputString(other);
		return *this;
	}

	Debugger& Debugger::operator<<(char other)
	{
		CHAR txt[2]{ other, '\0' };
		OutputString(txt, 1);
		return *this;
	}

	Debugger& Debugger::operator<<(float other)
	{
		OutputString(std::to_string(other).c_str());
		return *this;
	}

	Debugger& Debugger::operator<<(double other)
	{
		OutputString(std::to_string(other).c_str());
		return *this;
	}

	Debugger& Debugger::operator<<(uint8_t other)
	{
		OutputString(std::to_string(other).c_str());
		return *this;
	}

	Debugger& Debugger::operator<<(uint16_t other)
	{
		OutputString(std::to_string(other).c_str());
		return *this;
	}

	Debugger& Debugger::operator<<(uint32_t other)
	{
		OutputString(std::to_string(other).c_str());
		return *this;
	}

	Debugger& Debugger::operator<<(uint64_t other)
	{
		OutputString(std::to_string(other).c_str());
		return *this;
	}

	Debugger& Debugger::operator<<(int8_t other)
	{
		OutputString(std::to_string(other).c_str());
		return *this;
	}

	Debugger& Debugger::operator<<(int16_t other)
	{
		OutputString(std::to_string(other).c_str());
		return *this;
	}

	Debugger& Debugger::operator<<(int32_t other)
	{
		OutputString(std::to_string(other).c_str());
		return *this;
	}

	Debugger& Debugger::operator<<(int64_t other)
	{
		OutputString(std::to_string(other).c_str());
		return *this;
	}

	Debugger& Debugger::operator<<(TMM_ENDL other)
	{
		char txt[2]{ other.Symbol, '\0' };
		OutputString(txt, 1);
		if (mCurrentValid && mCurrentFlag.Contain(DEBUGGER_FLAGS::DBG_ERROR)) {
			++mErrorIndex;
			if (mErrorIndex >= 32) mErrorIndex = 31;
		}
		if (mThreadSafetyEnabled)
			LeaveCriticalSection(&mCS);
		return *this;
	}

	Debugger& Debugger::RegisterError(uint64_t line, const char* functionName, const char* fileName)
	{
		if (mCurrentValid && mDescriptor.Flags.Contain(DEBUGGER_FLAGS::DBG_ERROR)) {
			mErrors[mErrorIndex].Line = line;
			mErrors[mErrorIndex].FunctionName = functionName;
			mErrors[mErrorIndex].FileName = fileName;
		}
		return *this;
	}
}