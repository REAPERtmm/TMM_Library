#pragma once
#include <TMM_Setup.h>
#include <TMM_Function.h>

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

		ThreadArg<Data>*						mpThreads;
		ThreadProcDescriptor*					mThreadProcDescriptors;
		uint16_t								mThreadCount;

		uint8_t									mCurrentLayer;
		uint8_t									mLayerCount;

		bool									mIsTerminated;
	public:
		ThreadList(uint16_t threadCount, TMM::Function<bool, ThreadArg<Data>*>* pProc, ThreadArg<Data>* args);
		~ThreadList()
	};




}

#include "TMM_ThreadList.hpp"