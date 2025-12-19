#include "TMM_OrderedArray.h"

namespace TMM {

	template<typename T>
	inline ArrayOrdered<T>::ArrayOrdered() : Array<T>() { }

	template<typename T>
	inline ArrayOrdered<T>::ArrayOrdered(uint64_t allacationByteSize) : Array<T>(allacationByteSize) {}

	template<typename T>
	inline ArrayOrdered<T>::~ArrayOrdered() { }

	template<typename T>
	inline void ArrayOrdered<T>::Remove(const T& value)
	{
		T* pElt = this->mpData;
		for (;pElt != this->mpData + this->mSize; ++pElt) {
			if (*pElt == value) break;
		}
		for (;pElt != this->mpData + this->mSize; ++pElt) {
			*pElt = *(pElt + 1);
		}
		this->mSize--;
	}

	template<typename T>
	inline void ArrayOrdered<T>::InsertAt(const T& value, uint64_t index)
	{
		T* pElt = this->mpData + this->mSize;
		for (; pElt != this->mpData + index - 1; pElt--) {
			*(pElt + 1) = *pElt;
		}
		*(pElt + 1) = value;
		this->mSize++;
	}

	template<typename T>
	inline void ArrayOrdered<T>::RemoveAt(uint64_t index)
	{
		for (T* pElt = this->mpData + index; pElt != this->mpData + this->mSize; ++pElt) {
			*pElt = *(pElt + 1);
		}
		this->mSize--;
	}
}