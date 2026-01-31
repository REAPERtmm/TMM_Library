#include "TMM_ThreadList.h"

namespace TMM
{

	template<typename Resource_t>
	inline ThreadListWorkerCtx<Resource_t>::ThreadListWorkerCtx()
	{

	}

	template<typename Resource_t>
	inline ThreadListWorkerCtx<Resource_t>::~ThreadListWorkerCtx()
	{

	}

	template<typename Resource_t>
	inline void ThreadListWorkerCtx<Resource_t>::Init(ThreadListResource<Resource_t>* pResource, const ThreadListDelimiter& delimiter, TMM::Callable<void, Resource_t&, const Resource_t*, uint64_t>* pFunc)
	{
		mpResource = pResource;
		mDelimiter = delimiter;
		mpFunc = pFunc;
		Reset();
	}

	template<typename Resource_t>
	inline void ThreadListWorkerCtx<Resource_t>::Reset()
	{
		mCurrent = mDelimiter.start;
	}

	template<typename Resource_t>
	inline bool ThreadListWorkerCtx<Resource_t>::Step()
	{
		mpFunc->Call(mpResource->pData[mCurrent], mpResource->pData, mpResource->dataSize);

		uint64_t v = ++mCurrent;
		if (v == mDelimiter.end) return false;
		//std::cout << " | i:" << mCurrent << std::endl;
		return true;
	}

	template<typename Resource_t>
	inline void ThreadList<Resource_t>::WorkerProc(ThreadHandle* pHandle)
	{
		ThreadListWorkerCtx<Resource_t>* pCtx = (ThreadListWorkerCtx<Resource_t>*)pHandle->GetData();

		pHandle->Pause();
		while (pHandle->Synchronize() == false)
		{
			pCtx->Reset();
			//std::cout << "Launching..." << std::endl;
			while (pCtx->Step()) { } // execute Step until return false (eq.no more data to process)
			pHandle->Pause();
		}

		pHandle->Exit();
	}

	template<typename Resource_t>
	inline ThreadList<Resource_t>::ThreadList() : 
		mpFunc(nullptr),
		mpWorkers(nullptr),
		mpWorkersCtx(nullptr)
	{

	}

	template<typename Resource_t>
	inline ThreadList<Resource_t>::~ThreadList()
	{
		for (int i = 0; i < mThreadCount; ++i)
		{
			mpWorkers[i].GetGateWay()->Terminate();
			mpWorkers[i].GetGateWay()->Resume();
		}
		delete mpFunc;
		delete[] mpWorkers;
		delete[] mpWorkersCtx;
	}

	template<typename Resource_t>
	inline void ThreadList<Resource_t>::Init(ThreadListDescriptor<Resource_t>* pDesc)
	{
		mThreadCount = pDesc->threadCount;
		mResource = pDesc->resource;

		mpFunc = pDesc->pFunc;
		mpWorkersCtx = new ThreadListWorkerCtx<Resource_t>[mThreadCount];
		mpWorkers = new Thread[mThreadCount];
		for (uint64_t i = 0; i < mThreadCount; ++i)
		{
			ThreadListWorkerCtx<Resource_t>& workerCtx = mpWorkersCtx[i];
			workerCtx.Init(&mResource, pDesc->pThreadDelimiters[i], mpFunc);
		}
	}

	template<typename Resource_t>
	inline void ThreadList<Resource_t>::Start()
	{
		for (uint64_t i = 0; i < mThreadCount; ++i)
		{
			mpWorkers[i].Start(TMM::MakeFunctionPtr(WorkerProc), mpWorkersCtx + i, 1);
		}
	}

	template<typename Resource_t>
	inline void ThreadList<Resource_t>::Process()
	{
		WaitForAllEnd();
		for (uint64_t i = 0; i < mThreadCount; ++i)
		{
			mpWorkers[i].GetGateWay()->Resume();
		}
	}

	template<typename Resource_t>
	inline void ThreadList<Resource_t>::WaitForAllEnd()
	{
		for (uint64_t i = 0; i < mThreadCount; ++i)
		{
			// TODO : Remplace with WaitForSingleObject
			while (mpWorkers[i].GetGateWay()->IsPaused() == false) {}
		}
	}

}