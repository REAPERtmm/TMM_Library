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
		this->PushFirst(value);
	}

	template<typename T>
	inline T Stack<T>::PopStack()
	{
		return this->PopFirst();
	}

	template<typename T>
	inline bool Stack<T>::TryPopStack(T* pDest)
	{
		if (this->mpFirst == nullptr) return false;
		*pDest = PopStack();
		return true;
	}

	template<typename T>
	inline bool Stack<T>::Execute(const TMM::Function<bool, TMM::Node<T>&>& callback)
	{
		for (Node<T>* pNode = this->mpLast; pNode != this->mpFirst; pNode = pNode->pPrevious) {
			if (callback(*pNode) == false) {
				return false;
			}
		}
		return true;
	}
}