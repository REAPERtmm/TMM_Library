#include "TMM_UnorderedArray.h"

namespace TMM {

	template<typename T>
	inline void ArrayUnordered<T>::Remove(const T& value)
	{
		for (T* pElt = this->InternalGetStartPtr(); pElt != this->InternalGetStartPtr() + this->InternalGetSize(); ++pElt) {
			if (*pElt == value) {
				*pElt = *(this->InternalGetStartPtr() + this->InternalGetSize() - 1);
				this->InternalDecrementSize();
				return;
			}
		}
	}

	template<typename T>
	inline void ArrayUnordered<T>::RemoveAt(uint64_t index)
	{
		this->InternalGet(index) = this->InternalGet(this->InternalGetSize() - 1);
		this->InternalDecrementSize();
	}

}