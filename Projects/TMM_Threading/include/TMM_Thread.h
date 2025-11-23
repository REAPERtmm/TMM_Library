#pragma once
#include <TMM_Setup.h>
#include <TMM_Function.h>
#include <Windows.h>

namespace TMM 
{
	class Thread;

	enum ThreadStatusCode
	{
		SUCESS		= -1,
		IN_PROGRESS =  0,
		FAILED		=  1
	};

	class ThreadHandle
	{
		/* === Enter mCS === */
		CRITICAL_SECTION mCS;
		const char* mName;
		const Thread* mpSelf;
		ThreadStatusCode mStatusCode;
		bool mShouldTerminate;
		bool mIsPaused;
		bool mHasExited;
		/* === Leave mCS === */
	public:
		ThreadHandle(const char* name, Thread* pHold, bool startPaused = false);
		~ThreadHandle();

		const Thread* GetCurrentThread() const;
		const char* GetName() const;
		bool TerminationStatus();
		bool IsPaused();
		ThreadStatusCode GetStatus();

		void SafeTerminate();
		void SafePause();
		void SafeResume();

		/// <summary>
		/// Always call this from curent thread, if you want to exit from an other, call SafeTerminate()
		/// </summary>
		DWORD ExitWithStatus(ThreadStatusCode status);

		//void ChangeStatus(ThreadStatusCode status);
	};

	class Thread 
	{
		ThreadHandle mhThread;
		HANDLE mHandle;
		uint32_t mID;
	public:
		Thread(const char* name = "Unammed Thread", bool startPaused = false);
		~Thread();

		void Start(TMM::Function<DWORD, ThreadHandle*>* pFunc);

		HANDLE GetHandle() const;
		uint32_t GetID() const;
		ThreadStatusCode GetStatus();

		/// <summary>
		/// Pause the thread IF it hasn't been Paused else this function does nothing
		/// </summary>
		void Pause();

		/// <summary>
		/// Resume the thread IF it has been Paused else this function is ignored
		/// </summary>
		void Resume();

		/// <summary>
		///  Blocking Function Terminate
		/// </summary>
		ThreadStatusCode TerminateWait(uint32_t maxDuration = INFINITE);
		/// <summary>
		/// Non-blocking Function Terminate
		/// </summary>
		void Terminate();
	};

}