#include "TMM_ThreadList.h"

namespace TMM
{
	template<typename Data>
	inline ThreadList<Data>::ThreadList(uint16_t threadCount, TMM::Function<bool, ThreadArg<Data>*>* pProc, ThreadArg<Data>* args)
		: mpProc(pr), mThreadCount(threadCount)
	{

	}


}