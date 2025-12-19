#include "TMM_UnorderedArray.h"

namespace TMM {

	template<typename T>
	inline ArrayUnordered<T>::ArrayUnordered() : Array<T>() {}

	template<typename T>
	inline ArrayUnordered<T>::ArrayUnordered(uint64_t allacationByteSize) : Array<T>(allacationByteSize) {}

	template<typename T>
	inline ArrayUnordered<T>::~ArrayUnordered()
	{

	}

	template<typename T>
	inline void ArrayUnordered<T>::Remove(const T& value)
	{
		for (T* pElt = this->mpData; pElt != this->mpData + this->mSize; ++pElt) {
			if (*pElt == value) {
				*pElt = *(this->mpData + this->mSize);
				this->mSize--;
				return;
			}
		}
	}

	template<typename T>
	inline void ArrayUnordered<T>::RemoveAt(uint64_t index)
	{
		this->mpData[index] = this->mpData[this->mSize - 1];
		this->mSize--;
	}

}