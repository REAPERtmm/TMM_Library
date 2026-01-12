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

#ifdef TMM_COLLECTION_FUNCTIONAL_ENABLE

	template<typename T>
	inline bool Stack<T>::Execute(const TMM::Callable<bool, T*, T&, T*>& callback)
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

	template<typename T>
	inline bool Stack<T>::Execute(const TMM::Callable<bool, const uint64_t&, T&>& callback)
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
	inline bool Stack<T>::ExecuteIf(const TMM::Callable<bool, const uint64_t&, T&>& condition, const TMM::Callable<bool, const uint64_t&, T&>& callback)
	{
		bool error_code = true;
		Node<T>* pNode = this->InternalGetLast();
		uint64_t i = 0;
		while (pNode != nullptr)
		{
			if (condition(i, pNode->Value))
			{
				error_code &= callback(i, pNode->Value);
			}
			pNode = pNode->pPrevious;
			++i;
		}
		return error_code;
	}

	template<typename T>
	inline bool Stack<T>::ExecuteUntil(const TMM::Callable<bool, const uint64_t&, T&>& condition, const TMM::Callable<bool, const uint64_t&, T&>& callback)
	{
		bool error_code = true;
		Node<T>* pNode = this->InternalGetLast();
		uint64_t i = 0;
		while (pNode != nullptr)
		{
			if (condition(i, pNode->Value)) {
				return error_code;
			}
			error_code &= callback(i, pNode->Value);
			pNode = pNode->pPrevious;
			++i;
		}
		return error_code;
	}

	template<typename T>
	inline bool Stack<T>::ExecuteUntil(const TMM::Callable<bool, const uint64_t&, T&>& condition, const TMM::Callable<bool, const uint64_t&, T&>& callback, const uint64_t& start)
	{
		bool error_code = true;
		Node<T>* pNode = this->InternalGetLast();
		uint64_t i = 0;
		while (pNode != nullptr)
		{
			if (i == start) break;
			pNode = pNode->pPrevious;
			++i;
		}
		while (pNode != nullptr)
		{
			if (condition(i, pNode->Value)) {
				return error_code;
			}
			error_code &= callback(i, pNode->Value);
			pNode = pNode->pPrevious;
			++i;
		}
		return error_code;
	}

	template<typename T>
	inline bool Stack<T>::ExecuteFrom(const TMM::Callable<bool, const uint64_t&, T&>& condition, const TMM::Callable<bool, const uint64_t&, T&>& callback)
	{
		bool error_code = true;
		Node<T>* pNode = this->InternalGetLast();
		uint64_t i = 0;
		while (pNode != nullptr)
		{
			if (condition(i, pNode->Value)) {
				break;
			}
			pNode = pNode->pPrevious;
			++i;
		}
		while (pNode != nullptr)
		{
			error_code &= callback(i, pNode->Value);
			pNode = pNode->pPrevious;
			++i;
		}
		return error_code;
	}

	template<typename T>
	inline bool Stack<T>::ExecuteFrom(const TMM::Callable<bool, const uint64_t&, T&>& condition, const TMM::Callable<bool, const uint64_t&, T&>& callback, const uint64_t& end)
	{
		bool error_code = true;
		Node<T>* pNode = this->InternalGetLast();
		uint64_t i = 0;
		while (pNode != nullptr)
		{
			if (condition(i, pNode->Value)) {
				break;
			}
			pNode = pNode->pPrevious;
			++i;
		}
		while (pNode != nullptr)
		{
			if (end == i) break;
			error_code &= callback(i, pNode->Value);
			pNode = pNode->pPrevious;
			++i;
		}
		return error_code;
	}

	template<typename T>
	inline bool Stack<T>::ExecuteBetween(const TMM::Callable<bool, const uint64_t&, T&>& conditionStart, const TMM::Callable<bool, const uint64_t&, T&>& conditionEnd, const TMM::Callable<bool, const uint64_t&, T&>& callback)
	{
		bool error_code = true;
		Node<T>* pNode = this->InternalGetLast();
		uint64_t i = 0;
		while (pNode != nullptr)
		{
			if (conditionStart(i, pNode->Value)) {
				error_code &= callback(i, pNode->Value);
				pNode = pNode->pPrevious;
				++i;
				break;
			}
			pNode = pNode->pPrevious;
			++i;
		}
		while (pNode != nullptr)
		{
			if (conditionEnd(i, pNode->Value)) {
				break;
			}
			error_code &= callback(i, pNode->Value);
			pNode = pNode->pPrevious;
			++i;
		}
		return error_code;
	}


#endif // TMM_COLLECTION_FUNCTIONAL_ENABLE

}