#include "TMM_ThreadContext.h"

namespace TMM
{
	template<typename T>
	inline void ThreadContext<T>::InitData(T* pData, uint32_t elementCount)
	{
		mpData = pData;
		mByteSize = elementCount * sizeof(T);
		mElementCount = elementCount;
	}

	template<typename T>
	ThreadContext<T>::ThreadContext(const char* name, const Thread* pHold, bool startPaused)
		: mName(name),
		mpSelf(pHold),

		mIsPaused(startPaused),
		mShouldTerminate(false),
		mHasExited(false),
		mStatusCode(ThreadStatusCode::IN_PROGRESS),
		
		mpData(nullptr),
		mByteSize(0),
		mElementCount(0)
	{
		InitializeCriticalSection(&mCS);
	}

	template<typename T>
	ThreadContext<T>::~ThreadContext()
	{
		DeleteCriticalSection(&mCS);
	}

	template<typename T>
	const Thread* ThreadContext<T>::GetCurrentThread() const
	{
		return mpSelf;
	}

	template<typename T>
	const char* ThreadContext<T>::GetName() const
	{
		return mName;
	}

	template<typename T>
	ThreadStatusCode ThreadContext<T>::GetStatus()
	{
		ThreadStatusCode Result;
		EnterCriticalSection(&mCS);
		Result = mStatusCode;
		LeaveCriticalSection(&mCS);
		return Result;
	}

	template<typename T>
	bool ThreadContext<T>::TerminationStatus()
	{
		bool Result;
		EnterCriticalSection(&mCS);
		Result = mShouldTerminate;
		LeaveCriticalSection(&mCS);
		return Result;
	}

	template<typename T>
	bool ThreadContext<T>::IsPaused()
	{
		bool Result;
		EnterCriticalSection(&mCS);
		Result = mIsPaused;
		LeaveCriticalSection(&mCS);
		return Result;
	}

	template<typename T>
	inline bool ThreadContext<T>::IsExited()
	{
		bool Result;
		EnterCriticalSection(&mCS);
		Result = mHasExited;
		LeaveCriticalSection(&mCS);
		return Result;
	}

	template<typename T>
	void ThreadContext<T>::SafeTerminate()
	{
		EnterCriticalSection(&mCS);
		mShouldTerminate = true;
		LeaveCriticalSection(&mCS);
	}

	template<typename T>
	void ThreadContext<T>::SafePause()
	{
		EnterCriticalSection(&mCS);
		if (mIsPaused == false) {
			mIsPaused = true;
			LeaveCriticalSection(&mCS);
			SuspendThread(mpSelf->GetHandle());
			return;
		}
		LeaveCriticalSection(&mCS);
	}

	template<typename T>
	void ThreadContext<T>::SafeResume()
	{
		EnterCriticalSection(&mCS);
		if (mIsPaused) {
			ResumeThread(mpSelf->GetHandle());
			mIsPaused = false;
		}
		LeaveCriticalSection(&mCS);
	}

	template<typename T>
	DWORD ThreadContext<T>::ExitWithStatus(ThreadStatusCode status)
	{
		EnterCriticalSection(&mCS);
		mHasExited = true;
		mStatusCode = status;
		LeaveCriticalSection(&mCS);
		return status;
	}

	template<typename T>
	inline T* ThreadContext<T>::UnsafeData()
	{
		return mpData;
	}

	template<typename T>
	inline uint32_t ThreadContext<T>::UnsafeGetDataByteSize()
	{
		return mByteSize;
	}

	template<typename T>
	inline uint32_t ThreadContext<T>::UnsafeGetElementCount()
	{
		return mElementCount;
	}


}