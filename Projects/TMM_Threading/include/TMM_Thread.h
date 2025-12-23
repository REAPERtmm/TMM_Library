#pragma once

// REQUIRED internal include
#include <TMM_Setup.h>
#include <TMM_Function.h>
#include "TMM_ThreadContext.h"

namespace TMM 
{
	class Thread 
	{
		void* mpThreadContext;
		HANDLE mHandle;
		uint32_t mID;

		ThreadContext<char>* GetContextPtr();
	public:
		Thread(const char* name = "Unammed Thread", bool startPaused = false);
		~Thread();

		HANDLE GetHandle() const;
		uint32_t GetID() const;
		ThreadStatusCode GetStatus();

		/// <summary>
		/// Pause the thread IF it hasn't been Paused else this function does nothing
		/// </summary>
		void Pause();

		/// <summary>
		/// Check if the thread is currently paused
		/// </summary>
		bool IsPaused();

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

		template<typename T>
		void Start(TMM::Function<DWORD, ThreadContext<T>*>* pFunc, T* pData, uint64_t elementCount = 1);

		static uint16_t GetMaxThreadCount();
	};

}

#include "TMM_Thread.hpp"