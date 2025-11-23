#include "TMM_Debugger.h"
#include "TMM_Debugger.h"

namespace TMM {
	Debugger::Debugger()
	{
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
		if (index != 0) *Debugger::Get(DBG_ERROR) << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n";
		*Debugger::Get(DBG_ERROR) << "= Line     : " << mErrors[index].Line << '\n';
		*Debugger::Get(DBG_ERROR) << "= Function : " << mErrors[index].FunctionName << '\n';
		*Debugger::Get(DBG_ERROR) << "= File     : " << mErrors[index].FileName << '\n';
		*Debugger::Get(DBG_ERROR) << "= Msg      : " << '\n';
		*Debugger::Get(DBG_ERROR) << mErrors[index].ErrorMsg.c_str() << '\n';
	}

	void Debugger::OutputString(const char* txt)
	{
		OutputString(txt, strlen(txt));
	}

	void Debugger::OutputString(const char* txt, uint64_t length)
	{
		if (mCurrentValid == false) return;

		if (mCurrentValid && (mCurrentFlag & DBG_ERROR)) {
			mErrors[mErrorIndex].ErrorMsg += txt;
		}
		if (Utils::CheckMaskLt(OUTPUT_CONSOLE, mDescriptor.Output)) {
			// TODO : Output in the console*
			std::cout << txt;
		}
		if (Utils::CheckMaskLt(OUTPUT_DEBUGGER, mDescriptor.Output)) {
			// TODO : Output in the debugger
			OutputDebugStringA(txt);
		}
		if (Utils::CheckMaskLt(OUTPUT_LOGS, mDescriptor.Output)) {
			// TODO : Output into the logs
			if (fwrite(txt, sizeof(char), length, pFile) != length) {
				mDescriptor.Output ^= OUTPUT_LOGS;
				OutputString("Failed to write in logs : stopping the log feature");
			}
		}
	}

	Debugger* Debugger::InternalGet(DEBUGGER_FLAGS flags)
	{
		static Debugger debugger;
		debugger.mCurrentFlag = flags;
		debugger.mCurrentValid = Utils::CheckMaskLt(flags, debugger.mDescriptor.Flags);
		return &debugger;
	}

	Debugger* Debugger::Get(DEBUGGER_FLAGS flag)
	{
#ifdef ENABLE_DBG_THREAD_SAFE
		Debugger* pDebugger = InternalGet(flag);
		EnterCriticalSection(&pDebugger->mCS);
		return pDebugger;
#else
		return InternalGet(flag);
#endif
	}

	bool Debugger::Init(uint32_t flags, uint32_t output)
	{
		Debugger* pDbg = InternalGet(DBG_NONE);
#ifdef ENABLE_DBG_THREAD_SAFE
		InitializeCriticalSection(&pDbg->mCS);
		EnterCriticalSection(&pDbg->mCS);
#endif
		pDbg->mDescriptor.Flags = flags;
		pDbg->mDescriptor.Output = output;

		if (Utils::CheckMaskLt(OUTPUT_LOGS, pDbg->mDescriptor.Output)) {
			if (fopen_s(&pDbg->pFile, "Logs.txt", "wb") != 0) {
				pDbg->OutputString("Failed to open Logs");
#ifdef ENABLE_DBG_THREAD_SAFE
				LeaveCriticalSection(&pDbg->mCS);
#endif
				return false;
			}
		}
		pDbg->mIsInit = true;
#ifdef ENABLE_DBG_THREAD_SAFE
		LeaveCriticalSection(&pDbg->mCS);
#endif
		return true;
	}

	void Debugger::UnInit()
	{
		Debugger* pDbg = InternalGet(DBG_NONE);
#ifdef ENABLE_DBG_THREAD_SAFE
		EnterCriticalSection(&pDbg->mCS);
#endif
		if (pDbg->mErrorIndex > 0) {
			*Debugger::Get(DBG_ERROR) << "============================\n\n";
			for (uint8_t i = 0; i < pDbg->mErrorIndex; ++i) {
				pDbg->DisplayError(i);
			}
			*Debugger::Get(DBG_ERROR) << "============================\n";
		}

		if (Utils::CheckMaskLt(OUTPUT_LOGS, pDbg->mDescriptor.Output)) {
			fclose(pDbg->pFile);
		}
		delete[] pDbg->mErrors;
		pDbg->mIsInit = false;
#ifdef ENABLE_DBG_THREAD_SAFE
		LeaveCriticalSection(&pDbg->mCS);
		DeleteCriticalSection(&pDbg->mCS);
#endif
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
		if (mCurrentValid && (mCurrentFlag & DBG_ERROR)) {
			++mErrorIndex;
			if (mErrorIndex >= 32) mErrorIndex = 31;
		}
#ifdef ENABLE_DBG_THREAD_SAFE
		LeaveCriticalSection(&mCS);
#endif
		return *this;
	}

	Debugger& Debugger::RegisterError(uint64_t line, const char* functionName, const char* fileName)
	{
		if (mCurrentValid && Utils::CheckMaskLt(DBG_ERROR, mDescriptor.Flags)) {
			mErrors[mErrorIndex].Line = line;
			mErrors[mErrorIndex].FunctionName = functionName;
			mErrors[mErrorIndex].FileName = fileName;
		}
		return *this;
	}
}