#include "TMM_Thread.h"

namespace TMM
{

	template<typename T>
	inline void Thread::Start(TMM::Function<DWORD, ThreadContext<T>*>* pFunc, T* pData, uint64_t elementCount)
	{
		if (mHandle == nullptr) {
			static_cast<ThreadContext<T>*>(mpThreadContext)->InitData(pData, elementCount);
			mHandle = CreateThread(
				NULL,
				0,
				static_cast<LPTHREAD_START_ROUTINE>(pFunc->Ptr()),
				mpThreadContext,
				(GetContextPtr()->IsPaused() ? CREATE_SUSPENDED : 0),
				(DWORD*)(&mID)
			);
		}
	}

}