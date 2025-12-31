#pragma once

// REQUIRED internal include
#include <TMM_Setup.h>
#include "TMM_Collection.h"

namespace TMM
{

	template<uint64_t SIZE, typename T>
	class Container : public TMM::Collection<uint64_t, T>
	{
		T mData[SIZE] = {};

		constexpr __forceinline T* InternalGetStartPtr() { return mData; }
		constexpr __forceinline uint64_t InternalGetSize() { return SIZE; }
		constexpr __forceinline uint64_t InternalGetSize() const { return SIZE; }
		constexpr __forceinline T& InternalGet(uint64_t index) { return mData[index]; }
		constexpr __forceinline const T& InternalGet(uint64_t index) const { return mData[index]; }
		constexpr __forceinline bool InternalCheckInBound(uint64_t index) const { return index > 0 && index <= InternalGetSize(); }

	public:
		Container() = default;
		Container(const T& init_value);
		
		virtual T& operator[](const uint64_t& key);
		
		// Return the amount of different KEYS
		virtual uint64_t Size() const override final;

		// Return the const CONTENT ref associated with a KEY
		virtual const T& at(const uint64_t& key) const override final;

		// Try to access the CONTENT associated with a KEY and return if it succeded
		virtual bool TryGet(const uint64_t& key, T* pDest) override final;

#ifdef TMM_COLLECTION_FUNCTIONAL_ENABLE
		// Return if all of the callbacks succeded. 
		virtual bool Execute(const TMM::Callable<bool, const uint64_t&, T&>& callback) override;
#endif
	};
}

#include "TMM_Container.hpp"