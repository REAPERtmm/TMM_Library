#include "TMM_Thread.h"
#include "TMM_Thread.h"
#include "TMM_Thread.h"
#include "TMM_Thread.h"

namespace TMM 
{
	ThreadHandle::ThreadHandle(const char* name, Thread* pHold, bool startPaused)
		: mName(name), mpSelf(pHold)
	{
		mShouldTerminate = false;
		mIsPaused = startPaused;
		mHasExited = false;
		InitializeCriticalSection(&mCS);
	}

	ThreadHandle::~ThreadHandle()
	{
		DeleteCriticalSection(&mCS);
	}

	const Thread* ThreadHandle::GetCurrentThread() const
	{
		return mpSelf;
	}

	const char* ThreadHandle::GetName() const
	{
		return mName;
	}

	bool ThreadHandle::TerminationStatus()
	{
		bool Result;
		EnterCriticalSection(&mCS);
		Result = mShouldTerminate;
		LeaveCriticalSection(&mCS);
		return Result;
	}

	bool ThreadHandle::IsPaused()
	{
		bool Result;
		EnterCriticalSection(&mCS);
		Result = mIsPaused;
		LeaveCriticalSection(&mCS);
		return Result;
	}

	ThreadStatusCode ThreadHandle::GetStatus()
	{
		ThreadStatusCode Result;
		EnterCriticalSection(&mCS);
		Result = mStatusCode;
		LeaveCriticalSection(&mCS);
		return Result;
	}

	void ThreadHandle::SafeTerminate()
	{
		EnterCriticalSection(&mCS);
		mShouldTerminate = true;
		LeaveCriticalSection(&mCS);
	}

	void ThreadHandle::SafePause()
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

	void ThreadHandle::SafeResume()
	{
		EnterCriticalSection(&mCS);
		if (mIsPaused) {
			ResumeThread(mpSelf->GetHandle());
			mIsPaused = false;
		}
		LeaveCriticalSection(&mCS);
	}

	DWORD ThreadHandle::ExitWithStatus(ThreadStatusCode status)
	{
		EnterCriticalSection(&mCS);
		mHasExited = true;
		mStatusCode = status;
		LeaveCriticalSection(&mCS);
		return status;
	}

	//void ThreadHandle::ChangeStatus(ThreadStatusCode status)
	//{
	//	EnterCriticalSection(&mCS);
	//	mStatusCode = status;
	//	LeaveCriticalSection(&mCS);
	//}

	Thread::Thread(const char* name, bool startPaused)
		: mhThread(name, this, startPaused)
	{
		mHandle = nullptr;
	}

	Thread::~Thread()
	{
		Terminate();
	}

	void Thread::Start(TMM::Function<DWORD, ThreadHandle*>* pFunc)
	{
		if (mHandle == nullptr) {
			mHandle = CreateThread(
				NULL,
				0,
				(LPTHREAD_START_ROUTINE)(pFunc->Ptr()),
				&mhThread,
				(mhThread.IsPaused() ? CREATE_SUSPENDED : 0),
				(DWORD*)&mID
			);
		}
	}

	HANDLE Thread::GetHandle() const
	{
		return mHandle;
	}

	uint32_t Thread::GetID() const
	{
		return mID;
	}

	ThreadStatusCode Thread::GetStatus()
	{
		return mhThread.GetStatus();
	}

	ThreadStatusCode Thread::TerminateWait(uint32_t maxDuration)
	{
		Terminate();
		WaitForSingleObject(mHandle, maxDuration);
		mHandle = nullptr;
		mID = 0;
		return GetStatus();
	}

	void Thread::Terminate()
	{
		mhThread.SafeTerminate();
	}

	void Thread::Pause()
	{
		mhThread.SafePause();
	}
	
	void Thread::Resume()
	{
		mhThread.SafeResume();
	}
}