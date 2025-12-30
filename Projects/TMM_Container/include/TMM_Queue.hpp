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
		this->InternalPushFirst(value);
	}

	template<typename T>
	inline T Queue<T>::Dequeue()
	{
		return this->InternalPopLast();
	}

	template<typename T>
	inline bool Queue<T>::TryDequeue(T* pDest)
	{
		if(this->InternalGetFirst() == nullptr) return false;
		*pDest = Dequeue();
		return true;
	}
}