#pragma once
#include <TMM_Setup.h>
#include "TMM_LinkedList.h"

namespace TMM 
{

	template<typename T>
	class Queue : public TMM::LinkedList<T> 
	{
	public:
		Queue();
		~Queue();

		void Enqueue(const T& value);
		T Dequeue();
		bool TryDequeue(T* pDest);
		bool Execute(const TMM::Function<bool, TMM::Node<T>&>& callback) override;
	};
}

#include "TMM_Queue.hpp"