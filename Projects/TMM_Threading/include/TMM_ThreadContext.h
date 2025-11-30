#pragma once
#include <TMM_Setup.h>
#include <Windows.h>

namespace TMM
{
	class Thread;

	enum ThreadStatusCode
	{
		SUCESS = -1,
		IN_PROGRESS = 0,
		FAILED = 1
	};

	template<typename T>
	class ThreadContext
	{
		/* === Enter mCS === */
		CRITICAL_SECTION	mCS;
		const char*			mName;
		const Thread*		mpSelf;

		ThreadStatusCode	mStatusCode;
		bool				mShouldTerminate;
		bool				mIsPaused;
		bool				mHasExited;

		/* === Leave mCS === */

		uint64_t			mByteSize;
		uint64_t			mElementCount;
		T*					mpData;

		void InitData(T* pData, uint32_t elementCount = 1);
	public:
		ThreadContext(const char* name, const Thread* pHold, bool startPaused = false);
		~ThreadContext();

		const Thread* GetCurrentThread() const;
		const char* GetName() const;

		ThreadStatusCode GetStatus();
		bool TerminationStatus();
		bool IsPaused();
		bool IsExited();

		void SafeTerminate();
		void SafePause();
		void SafeResume();

		/// <summary>
		/// Always call this from curent thread, if you want to exit from an other, call SafeTerminate()
		/// </summary>
		DWORD ExitWithStatus(ThreadStatusCode status);

		/// <summary>
		/// Only call this from current thread
		/// </summary>
		T* UnsafeData();

		/// <summary>
		/// Only call this from current thread
		/// </summary>
		uint32_t UnsafeGetDataByteSize();

		/// <summary>
		/// Only call this from current thread
		/// </summary>
		uint32_t UnsafeGetElementCount();

		friend class Thread;
	};
}

#include "TMM_ThreadContext.hpp"