#pragma once

// REQUIRED internal include
#include <TMM_Setup.h>
#include "TMM_LinkedList.h"

namespace TMM 
{
	/// <summary>
	/// A Data Structure representing a queue (0 represent the next element retrieved)
	/// </summary>
	template<typename T>
	class Queue : public TMM::LinkedList<T> 
	{
	public:
		Queue();
		~Queue();

		void Enqueue(const T& value);
		T Dequeue();
		bool TryDequeue(T* pDest);
	};
}

#include "TMM_Queue.hpp"