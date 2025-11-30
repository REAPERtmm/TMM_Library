#include "TMM_Thread.h"
#include "TMM_Thread.h"
#include "TMM_Thread.h"
#include "TMM_Thread.h"
#include "TMM_Thread.h"

namespace TMM 
{

	ThreadContext<char>* Thread::GetContextPtr()
	{
		return reinterpret_cast<ThreadContext<char>*>(mpThreadContext);
	}

	Thread::Thread(const char* name, bool startPaused)
		: mHandle(nullptr), mID(0), mpThreadContext(new ThreadContext<char>(name, this, startPaused)) 
	{ 

	}

	Thread::~Thread()
	{
		if (GetContextPtr()->IsExited()) {
			delete GetContextPtr();
		}
		//else {
		//	TerminateWait();
		//	delete GetContextPtr();
		//}
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
		return GetContextPtr()->GetStatus();
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
		GetContextPtr()->SafeTerminate();
	}

	void Thread::Pause()
	{
		GetContextPtr()->SafePause();
	}
	
	bool Thread::IsPaused() 
	{
		return GetContextPtr()->IsPaused();
	}

	void Thread::Resume()
	{
		GetContextPtr()->SafeResume();
	}

	uint16_t Thread::GetMaxThreadCount()
	{
		return static_cast<uint16_t>(GetMaximumProcessorCount(ALL_PROCESSOR_GROUPS));
	}
}