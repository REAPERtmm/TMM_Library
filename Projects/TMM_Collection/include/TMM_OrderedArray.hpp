#include "TMM_OrderedArray.h"

namespace TMM {

	template<typename T>
	inline void ArrayOrdered<T>::Remove(const T& value)
	{
		T* pElt = this->InternalGetStartPtr();
		T* pLast = this->InternalGetStartPtr() + this->InternalGetSize();
		for (;pElt != pLast; ++pElt) {
			if (*pElt == value) break;
		}
		for (;pElt != pLast; ++pElt) {
			*pElt = *(pElt + 1);
		}
		this->InternalDecrementSize();
	}

	template<typename T>
	inline void ArrayOrdered<T>::InsertAt(const T& value, uint64_t index)
	{
		T* pElt = this->InternalGetStartPtr() + this->InternalGetSize();
		for (; pElt != this->InternalGetStartPtr() + index - 1; pElt--) {
			*(pElt + 1) = *pElt;
		}
		*(pElt + 1) = value;
		this->InternalIncrementSize();
	}

	template<typename T>
	inline void ArrayOrdered<T>::RemoveAt(uint64_t index)
	{
		for (T* pElt = this->InternalGetStartPtr() + index; pElt != this->InternalGetStartPtr() + this->InternalGetSize(); ++pElt) {
			*pElt = *(pElt + 1);
		}
		this->InternalDecrementSize();
	}
}