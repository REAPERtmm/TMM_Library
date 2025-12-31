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
#ifdef TMM_COLLECTION_FUNCTIONAL_ENABLE
		bool Execute(const TMM::Callable<bool, const uint64_t&, T&>& callback) override;
		bool Execute(const TMM::Callable<bool, T*, T&, T*>& callback) override;
#endif // TMM_COLLECTION_FUNCTIONAL_ENABLE

	};
}

#include "TMM_Stack.hpp"