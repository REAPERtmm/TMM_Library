#include "TMM_Array.h"

namespace TMM {
	
	template<typename T>
	inline void Array<T>::InternalAllocate(uint64_t capacity)
	{
		InternalGetCapacity() = capacity;
		T* temp = new T[capacity];
		memcpy(temp, InternalGetStartPtr(), InternalGetSize());
		delete[] InternalGetStartPtr();
		InternalGetStartPtr() = temp;
	}

	template<typename T>
	inline Array<T>::Array()
	{
		InternalGetStartPtr() = new T[16];
		InternalGetCapacity() = 16;
		InternalGetSize() = 0;
	}

	template<typename T>
	inline Array<T>::Array(uint64_t allocationByteSize)
	{
		InternalGetStartPtr() = new T[allocationByteSize];
		InternalGetCapacity() = allocationByteSize;
		InternalGetSize() = 0;
	}

	template<typename T>
	inline Array<T>::~Array()
	{
		delete[] mpData;
	}

	template<typename T>
	inline bool Array<T>::TryGet(const uint64_t& key, T* pDest)
	{
		if (InternalCheckInBound(key) == false) return false;
		*pDest = InternalGet(key);
		return true;
	}

	template<typename T>
	void Array<T>::Add(const T& value)
	{
		mpData[mSize] = value;
		InternalIncrementSize();
		if (InternalGetSize() == mCapacity) {
			InternalAllocate(mCapacity * 2);
		}
	}

#ifdef TMM_COLLECTION_FUNCTIONAL_ENABLE
	template<typename T>
	inline bool Array<T>::Execute(const TMM::Callable<bool, const uint64_t&, T&>& callback)
	{
		bool error_code = true;
		for (uint64_t i = 0; i < InternalGetSize(); ++i) {
			error_code &= callback(i, InternalGet(i));
		}
		return error_code;
	}
#endif

	template<typename T>
	inline uint64_t Array<T>::Size() const
	{
		return InternalGetSize();
	}

	template<typename T>
	inline T& Array<T>::operator[](const uint64_t& key)
	{
		return InternalGet(key);
	}

	template<typename T>
	inline const T& Array<T>::at(const uint64_t& key) const
	{
		return InternalGet(key);
	}
}