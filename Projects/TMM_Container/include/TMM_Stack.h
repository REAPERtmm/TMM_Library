#pragma once

// REQUIRED internal include
#include <TMM_Setup.h>
#include "TMM_LinkedList.h"

namespace TMM 
{
	template<typename T>
	class Stack : public TMM::LinkedList<T>
	{
	public:
		Stack();
		~Stack();

		void PushStack(const T& value);
		T PopStack();
		bool TryPopStack(T* pDest);
		bool Execute(const TMM::Function<bool, TMM::Node<T>&>& callback) override;
	};
}

#include "TMM_Stack.hpp"