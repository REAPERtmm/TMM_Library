#include "TMM_Stack.h"

namespace TMM 
{
	template<typename T>
	inline Stack<T>::Stack() : LinkedList<T>() { }

	template<typename T>
	inline Stack<T>::~Stack() { }

	template<typename T>
	inline void Stack<T>::PushStack(const T& value)
	{
		this->InternalPushFirst(value);
	}

	template<typename T>
	inline T Stack<T>::PopStack()
	{
		return this->InternalPopFirst();
	}

	template<typename T>
	inline bool Stack<T>::TryPopStack(T* pDest)
	{
		if (this->InternalGetFirst() == nullptr) return false;
		*pDest = PopStack();
		return true;
	}

	template<typename T>
	inline bool Stack<T>::Execute(const TMM::Function<bool, const uint64_t&, T&>& callback)
	{
		bool error_code = true;
		Node<T>* pNode = this->InternalGetLast();
		uint64_t i = 0;
		while (pNode != nullptr)
		{
			error_code &= callback(i, pNode->Value);
			pNode = pNode->pPrevious;
			++i;
		}
		return error_code;
	}

	template<typename T>
	inline bool Stack<T>::Execute(const TMM::Function<bool, T*, T&, T*>& callback)
	{
		bool error_code = true;
		Node<T>* pNode = this->InternalGetLast();
		uint64_t i = 0;
		while (pNode != nullptr)
		{
			error_code &= callback(
				pNode->pPrevious == nullptr ? nullptr : &pNode->pPrevious->Value,
				pNode->Value,
				pNode->pNext == nullptr ? nullptr : &pNode->pNext->Value
			);
			pNode = pNode->pPrevious;
			++i;
		}
		return error_code;
	}
}