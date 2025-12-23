#include "TMM_LinkedList.h"

namespace TMM 
{
	template<typename T>
	inline LinkedList<T>::LinkedList() : BASE(0)
	{
		mpFirst = nullptr;
		mpLast = nullptr;
	}

	template<typename T>
	inline LinkedList<T>::~LinkedList()
	{
		while (mpFirst != nullptr)
		{
			Node<T>* pTemp = mpFirst;
			mpFirst = mpFirst->pNext;
			delete pTemp;
		}
	}

	template<typename T>
	inline void LinkedList<T>::PushFirst(const T& value)
	{
		Node<T>* pNode = new Node<T>();
		pNode->Value = value;
		pNode->pPrevious = nullptr;
		pNode->pNext = mpFirst;
		if (pNode->pNext != nullptr)
			pNode->pNext->pPrevious = pNode;
		mpFirst = pNode;
		if (mpLast == nullptr) mpLast = mpFirst;
		this->mSize++;
	}

	template<typename T>
	inline void LinkedList<T>::PushLast(const T& value)
	{
		Node<T>* pNode = new Node<T>();
		pNode->Value = value;
		pNode->pPrevious = mpLast;
		pNode->pNext = nullptr;
		if (pNode->pPrevious != nullptr)
			pNode->pPrevious->pNext = pNode;
		mpLast = pNode;
		if (mpFirst == nullptr) mpFirst = mpLast;
		this->mSize++;
	}

	template<typename T>
	inline T LinkedList<T>::PopFirst()
	{
		Node<T>* pNode = mpFirst;
		T result = pNode->Value;

		mpFirst = pNode->pNext;
		if (mpFirst == nullptr) {
			mpLast = nullptr;
		}
		else {
			mpFirst->pPrevious = nullptr;
		}

		delete pNode;

		this->mSize--;
		return result;
	}

	template<typename T>
	inline T LinkedList<T>::PopLast()
	{
		Node<T>* pNode = mpLast;
		T result = pNode->Value;

		mpLast = pNode->pPrevious;
		if (mpLast == nullptr) {
			mpFirst = nullptr;
		}
		else {
			mpLast->pNext = nullptr;
		}

		delete pNode;

		this->mSize--;
		return result;
	}

#ifdef TMM_CONTAINER_FUNCTIONAL_ENABLE
	template<typename T>
	inline bool LinkedList<T>::Execute(const TMM::Function<bool, LIST_NODE&>& callback)
	{
		for (Node<T>* pNode = mpFirst; pNode != mpLast; pNode = pNode->pNext) {
			if (callback(*pNode) == false) {
				return false;
			}
		}
		return true;
	}
#endif

	template<typename T>
	inline T& LinkedList<T>::operator[](const uint64_t& key)
	{
		Node<T>* pNode = mpFirst;
		for (uint64_t i = 0; i < key; ++i) {
			pNode = pNode->pNext;
			if (pNode->pNext == nullptr) break;
		}
		return pNode->Value;
	}

	template<typename T>
	inline TMM::LinkedList<T>::LIST_NODE LinkedList<T>::at(const uint64_t& key)
	{
		Node<T>* pNode = mpFirst;
		for (uint64_t i = 0; i < key; ++i) {
			pNode = pNode->pNext;
			if (pNode->pNext == nullptr) break;
		}
		return *pNode;
	}

	template<typename T>
	inline bool LinkedList<T>::TryGet(const uint64_t& key, LIST_NODE* pDest)
	{
		if (this->InternalInBounds(key) == false) return false;
		*pDest = at(key);
		return true;
	}
}