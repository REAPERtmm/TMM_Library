#pragma once
// REQUIRED internal include
#include <TMM_Setup.h>
#include <TMM_Function.h>
#include "TMM_Thread.h"

// TODO : remove
#include <iostream>

namespace TMM
{

	struct ThreadListDelimiter
	{
		// Start | stride | offset | stride | offset | ...
		uint64_t start;
		uint64_t end;
	};

	template<typename Resource_t>
	struct ThreadListResource
	{
		Resource_t* pData;
		uint64_t dataSize;
	};



	template<typename Resource_t>
	class ThreadListWorkerCtx
	{
		ThreadListResource<Resource_t>* mpResource;
		ThreadListDelimiter mDelimiter;
		TMM::Callable<void, Resource_t&, const Resource_t*, uint64_t>* mpFunc;

		uint64_t mCurrent;

	public:
		ThreadListWorkerCtx();
		virtual ~ThreadListWorkerCtx();

		void Init(
			ThreadListResource<Resource_t>* pResource, 
			const ThreadListDelimiter& delimiter,
			TMM::Callable<void, Resource_t&, const Resource_t*, uint64_t>* pFunc
		);

		void Reset();

		bool Step();
	};

	template<typename Resource_t>
	struct ThreadListDescriptor
	{
		TMM::Callable<void, Resource_t&, const Resource_t*, uint64_t>* pFunc;
		ThreadListDelimiter* pThreadDelimiters;
		ThreadListResource<Resource_t> resource;
		uint16_t threadCount;
		~ThreadListDescriptor() { delete[] pThreadDelimiters; }
	};

	template<typename Resource_t>
	class ThreadList {
		TMM::Callable<void, Resource_t&, const Resource_t*, uint64_t>* mpFunc;
		ThreadListResource<Resource_t> mResource;
		ThreadListWorkerCtx<Resource_t>* mpWorkersCtx;
		uint16_t mThreadCount;
		Thread* mpWorkers;

		static void WorkerProc(ThreadHandle* pHandle);

	public:
		ThreadList();
		virtual ~ThreadList();

		void Init(ThreadListDescriptor<Resource_t>* pDesc);

		void Start();

		void Process();

		void WaitForAllEnd();
	};



}

#include "TMM_ThreadList.hpp"