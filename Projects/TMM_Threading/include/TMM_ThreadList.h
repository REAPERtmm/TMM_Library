#pragma once
#include <TMM_Setup.h>
#include <TMM_Function.h>
#include <TMM_Thread.h>

namespace TMM
{
	template<typename Data>
	struct ThreadArg {
		Thread*		pThread;
		Data*		pData;
		uint8_t		layer;
	};

	template<typename Data>
	class ThreadList {
		struct ThreadProcDescriptor
		{
			ThreadList* pList;
			uint64_t index;
		};

		TMM::Function<bool, ThreadArg<Data>*>*	mpProc;

		ThreadArg<Data>*						mThreads;
		ThreadProcDescriptor*					mThreadProcDescriptors;
		uint16_t								mThreadCount;

		uint8_t									mCurrentLayer;
		uint8_t									mLayerCount;

		bool									mIsTerminated;

		void ResumeCurrentLayer();
		bool IsLayerFinished();
		bool SwapLayer();

		static DWORD ThreadProc(ThreadContext<ThreadProcDescriptor>* pHandle);

		ThreadArg<Data>* InternalGetThreadInfo(uint32_t index);
	public:
		ThreadList(uint16_t threadCount, ThreadArg<Data>* args, TMM::Function<bool, ThreadArg<Data>*>* pProc);
		virtual ~ThreadList();

		void Update();
		const ThreadArg<Data>* GetThreadInfo(uint32_t index) const;

		void TerminateWait();
	};
}

#include "TMM_ThreadList.hpp"