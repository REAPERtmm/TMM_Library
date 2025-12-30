#include "TMM_LinkedList.h"

namespace TMM 
{
	template<typename T>
	inline LinkedList<T>::LinkedList()
	{
		InternalGetFirst() = nullptr;
		InternalGetLast() = nullptr;
		InternalGetSize() = 0;
	}

	template<typename T>
	inline LinkedList<T>::~LinkedList()
	{
		while (InternalGetFirst() != nullptr)
		{
			Node<T>* pTemp = InternalGetFirst();
			InternalGetFirst() = InternalGetFirst()->pNext;
			delete pTemp;
		}
	}

	template<typename T>
	inline void LinkedList<T>::InternalPushFirst(const T& value)
	{
		Node<T>* pNode = new Node<T>();
		pNode->Value = value;
		pNode->pPrevious = nullptr;
		pNode->pNext = InternalGetFirst();
		if (pNode->pNext != nullptr)
			pNode->pNext->pPrevious = pNode;
		InternalGetFirst() = pNode;
		if (InternalGetLast() == nullptr) InternalGetLast() = InternalGetFirst();
		InternalIncrementSize();
	}

	template<typename T>
	inline void LinkedList<T>::InternalPushLast(const T& value)
	{
		Node<T>* pNode = new Node<T>();
		pNode->Value = value;
		pNode->pPrevious = InternalGetLast();
		pNode->pNext = nullptr;
		if (pNode->pPrevious != nullptr)
			pNode->pPrevious->pNext = pNode;
		InternalGetLast() = pNode;
		if (InternalGetFirst() == nullptr) InternalGetFirst() = InternalGetLast();
		InternalIncrementSize();
	}

	template<typename T>
	inline T LinkedList<T>::InternalPopFirst()
	{
		Node<T>* pNode = InternalGetFirst();
		T result = pNode->Value;

		InternalGetFirst() = pNode->pNext;
		if (InternalGetFirst() == nullptr) {
			InternalGetLast() = nullptr;
		}
		else {
			InternalGetFirst()->pPrevious = nullptr;
		}

		delete pNode;

		InternalDecrementSize();
		return result;
	}

	template<typename T>
	inline T LinkedList<T>::InternalPopLast()
	{
		Node<T>* pNode = InternalGetLast();
		T result = pNode->Value;

		InternalGetLast() = pNode->pPrevious;
		if (InternalGetLast() == nullptr) {
			InternalGetFirst() = nullptr;
		}
		else {
			InternalGetLast()->pNext = nullptr;
		}

		delete pNode;

		InternalDecrementSize();
		return result;
	}

#ifdef TMM_CONTAINER_FUNCTIONAL_ENABLE

	template<typename T>
	inline bool LinkedList<T>::Execute(const TMM::Function<bool, const uint64_t&, T&>& callback)
	{
		bool error_code = true;
		Node<T>* pNode = InternalGetFirst();
		uint64_t i = 0;
		while (pNode != nullptr)
		{
			error_code &= callback(i, pNode->Value);
			pNode = pNode->pNext;
			++i;
		}
		return error_code;
	}

	template<typename T>
	inline bool LinkedList<T>::Execute(const TMM::Function<bool, T*, T&, T*>& callback)
	{
		if (InternalGetFirst() == nullptr) return true;
		bool error_code = true;
		Node<T>* pNode = InternalGetFirst();
		uint64_t i = 0;
		while (pNode != nullptr)
		{
			error_code &= callback(
				pNode->pPrevious == nullptr ? nullptr : &pNode->pPrevious->Value,
				pNode->Value,
				pNode->pNext == nullptr ? nullptr : &pNode->pNext->Value
			);
			pNode = pNode->pNext;
			++i;
		}
		return error_code;
	}

#endif

	template<typename T>
	inline uint64_t LinkedList<T>::Size()
	{
		return InternalGetSize();
	}

	template<typename T>
	inline T& LinkedList<T>::operator[](const uint64_t& key)
	{
		Node<T>* pNode = InternalGetFirst();
		for (uint64_t i = 0; i < key; ++i) {
			pNode = pNode->pNext;
			if (pNode->pNext == nullptr) break;
		}
		return pNode->Value;
	}

	template<typename T>
	inline const T& LinkedList<T>::at(const uint64_t& key) const
	{
		const Node<T>* pNode = InternalGetFirst();
		for (uint64_t i = 0; i < key; ++i) {
			pNode = pNode->pNext;
			if (pNode->pNext == nullptr) break;
		}
		return pNode->Value;
	}

	template<typename T>
	inline bool LinkedList<T>::TryGet(const uint64_t& key, T* pDest)
	{
		if (InternalCheckInBound(key) == false) return false;
		*pDest = operator[](key);
		return true;
	}
}