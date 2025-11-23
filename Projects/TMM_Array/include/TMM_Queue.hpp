#include "TMM_Queue.h"

namespace TMM 
{
	template<typename T>
	inline Queue<T>::Queue() : LinkedList<T>() { }

	template<typename T>
	inline Queue<T>::~Queue() { }

	template<typename T>
	inline void Queue<T>::Enqueue(const T& value)
	{
		this->PushFirst(value);
	}

	template<typename T>
	inline T Queue<T>::Dequeue()
	{
		return this->PopLast();
	}

	template<typename T>
	inline bool Queue<T>::TryDequeue(T* pDest)
	{
		if(this->mpFirst == nullptr) return false;
		*pDest = Dequeue();
		return true;
	}

	template<typename T>
	inline bool Queue<T>::Execute(const TMM::Function<bool, TMM::Node<T>&>& callback)
	{
		for (Node<T>* pNode = this->mpFirst; pNode != this->mpLast; pNode = pNode->pNext) {
			if (callback(*pNode) == false) {
				return false;
			}
		}
		return true;
	}
}