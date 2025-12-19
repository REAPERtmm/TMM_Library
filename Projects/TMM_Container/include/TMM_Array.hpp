#include "TMM_Array.h"

namespace TMM {
	
	template<typename T>
	inline void Array<T>::InternalAllocate(uint64_t capacity)
	{
		mCapacity = capacity;
		T* temp = new T[capacity];
		memcpy(temp, mpData, BASE::mSize);
		delete[] mpData;
		mpData = temp;
	}

	template<typename T>
	inline T& Array<T>::InternalGet(const uint64_t& key)
	{
		return mpData[key];
	}

	template<typename T>
	inline Array<T>::Array()
		: BASE(0)
	{
		mpData = new T[16];
		mCapacity = 16;
	}

	template<typename T>
	inline Array<T>::Array(uint64_t allocationByteSize)
		: BASE(0)
	{
		mpData = new T[allocationByteSize];
		mCapacity = allocationByteSize;
	}

	template<typename T>
	inline Array<T>::~Array()
	{
		delete[] mpData;
	}

	template<typename T>
	void Array<T>::Add(const T& value)
	{
		mpData[this->mSize] = value;
		this->mSize++;
		if (this->mSize == mCapacity) {
			InternalAllocate(mCapacity * 2);
		}
	}

	template<typename T>
	inline bool Array<T>::Execute(const TMM::Function<bool, ARRAY_NODE&>& callback)
	{
		bool error_code = true;

		for (uint64_t i = 0; i < this->Size(); ++i) {
			ARRAY_NODE node = this->at(i);
			error_code &= callback(node);
		}

		return error_code;
	}

	template<typename T>
	inline T& Array<T>::operator[](const uint64_t& key)
	{
		return InternalGet(key);
	}

	template<typename T>
	inline Array<T>::ARRAY_NODE Array<T>::at(const uint64_t& key)
	{
		ARRAY_NODE node;
		node.key = key;
		node.content = InternalGet(key);
		return node;
	}

	template<typename T>
	inline bool Array<T>::TryGet(const uint64_t& key, ARRAY_NODE* pDest)
	{
		if (this->InternalInBounds(key) == false) return false;
		pDest->key = key;
		pDest->content = InternalGet(key);
		return true;
	}
}