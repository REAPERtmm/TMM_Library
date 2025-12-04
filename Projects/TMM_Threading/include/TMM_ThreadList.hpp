#include "TMM_ThreadList.h"

namespace TMM
{
	template<typename Data>
	inline ThreadList<Data>::ThreadList(uint16_t threadCount, ThreadArg<Data>* args, TMM::Function<bool, ThreadArg<Data>*>* pProc) : 
		mIsTerminated(false), 
		mCurrentLayer(0), 
		mLayerCount(0), 
		mThreadCount(threadCount),
		mpProc(pProc)
	{
		mThreads = new ThreadArg<Data>[mThreadCount];
		mThreadProcDescriptors = new ThreadProcDescriptor[mThreadCount];

		memcpy(mThreads, args, sizeof(ThreadArg<Data>) * mThreadCount);

		auto threadFunc = TMM::MakeFunction(ThreadProc);
		
		for (uint64_t i = 0; i < mThreadCount; ++i) {
			if (mThreads[i].layer > mLayerCount)
				mLayerCount = mThreads[i].layer;

			Thread* runThread = new Thread("SubThreadProc", true);
			mThreadProcDescriptors[i].index = i;
			mThreadProcDescriptors[i].pList = this;
			mThreads[i].pThread = runThread;
			runThread->Start<ThreadProcDescriptor>(&threadFunc, &mThreadProcDescriptors[i]);
		}
		++mLayerCount;
	}

	template<typename Data>
	inline ThreadList<Data>::~ThreadList()
	{
		for (uint64_t i = 0; i < mThreadCount; ++i)
		{
			delete mThreads[i].pThread;
			delete mThreads[i].pData;
		}

		delete[] mThreads;
		delete[] mThreadProcDescriptors;
	}

	template<typename Data>
	inline void ThreadList<Data>::Update()
	{
		if (mIsTerminated) return;

		ResumeCurrentLayer();

		// Check if all thread have reach the end
		bool layerUpdateFinish = false;
		while (!layerUpdateFinish) {
			layerUpdateFinish = IsLayerFinished();

			if (!layerUpdateFinish) continue;

			layerUpdateFinish = SwapLayer();
			if (!layerUpdateFinish) {
				ResumeCurrentLayer();
			}

		}
	}

	template<typename Data>
	inline ThreadArg<Data>* ThreadList<Data>::InternalGetThreadInfo(uint32_t index)
	{
		return &mThreads[index];
	}

	template<typename Data>
	inline const ThreadArg<Data>* ThreadList<Data>::GetThreadInfo(uint32_t index) const
	{
		return InternalGetThreadInfo(index);
	}

	template<typename Data>
	inline void ThreadList<Data>::TerminateWait()
	{
		mIsTerminated = true;
		for (uint64_t i = 0; i < mThreadCount; ++i) {
			mThreads[i].pThread->Terminate();
			mThreads[i].pThread->Resume();
			mThreads[i].pThread->TerminateWait();
		}
	}


	template<typename Data>
	inline void ThreadList<Data>::ResumeCurrentLayer()
	{
		for (uint64_t i = 0; i < mThreadCount; ++i) {
			if (mThreads[i].layer == mCurrentLayer) {
				mThreads[i].pThread->Resume();
			}
		}
	}

	template<typename Data>
	inline bool ThreadList<Data>::IsLayerFinished()
	{
		bool layerUpdateFinish = true;
		for (uint64_t i = 0; i < mThreadCount; ++i) {
			if (mThreads[i].layer != mCurrentLayer) continue;
			layerUpdateFinish &= mThreads[i].pThread->IsPaused();
		}
		return layerUpdateFinish;
	}

	template<typename Data>
	inline bool ThreadList<Data>::SwapLayer()
	{
		mCurrentLayer++;
		if (mCurrentLayer == mLayerCount) {
			mCurrentLayer = 0;
			return true;
		}
		else {
			return false;
		}
	}

	template<typename Data>
	inline DWORD ThreadList<Data>::ThreadProc(ThreadContext<ThreadProcDescriptor>* pHandle)
	{
		ThreadProcDescriptor* data = reinterpret_cast<ThreadProcDescriptor*>(pHandle->UnsafeData());
		TMM::ThreadList<Data>* pScheduler = data->pList;

		while (!pHandle->TerminationStatus()) {
			(*pScheduler->mpProc)(pScheduler->InternalGetThreadInfo(data->index));
			pHandle->SafePause();
		}

		return pHandle->ExitWithStatus(SUCESS);
	}



}