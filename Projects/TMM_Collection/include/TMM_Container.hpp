#include "TMM_Container.h"

namespace TMM
{
	template<uint64_t SIZE, typename T>
	inline Container<SIZE, T>::Container(const T& init_value)
	{
		for (T* ptr = InternalGetStartPtr(); ptr != InternalGetStartPtr() + InternalGetSize(); ++ptr)
		{
			*ptr = init_value;
		}
	}

	template<uint64_t SIZE, typename T>
	inline uint64_t Container<SIZE, T>::Size() const
	{
		return InternalGetSize();
	}

	template<uint64_t SIZE, typename T>
	inline T& Container<SIZE, T>::operator[](const uint64_t& key)
	{
		return InternalGet(key);
	}

	template<uint64_t SIZE, typename T>
	inline const T& Container<SIZE, T>::at(const uint64_t& key) const
	{
		return InternalGet(key);
	}

	template<uint64_t SIZE, typename T>
	inline bool Container<SIZE, T>::TryGet(const uint64_t& key, T* pDest)
	{
		if (InternalCheckInBound(key) == false) return false;
		*pDest = InternalGet(key);
		return true;
	}

	template<uint64_t SIZE, typename T>
	inline bool Container<SIZE, T>::Execute(const TMM::Callable<bool, const uint64_t&, T&>& callback)
	{
		bool error_code = true;
		for (uint64_t i = 0; i < InternalGetSize(); ++i) {
			error_code &= callback(i, InternalGet(i));
		}
		return error_code;
	}


}