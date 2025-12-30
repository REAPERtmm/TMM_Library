#pragma once

// REQUIRED internal include
#include <TMM_Setup.h>
#include "TMM_Container.h"

// REQUIRED external include
#include <memory>

namespace TMM {
	template<typename T>
	class Array : public Container<uint64_t, T> {
	protected:
		T* mpData;
		uint64_t mSize;
		uint64_t mCapacity;

		void InternalAllocate(uint64_t capacity);

		// constexpr inline accessor
		constexpr __forceinline T*& InternalGetStartPtr() { return mpData; }
		constexpr __forceinline uint64_t& InternalGetSize() { return mSize; }
		constexpr __forceinline uint64_t& InternalGetCapacity() { return mCapacity; }
		constexpr __forceinline T& InternalGet(const uint64_t& key) { return mpData[key]; }
		constexpr __forceinline const T& InternalGet(const uint64_t& key) const { return mpData[key]; }
		constexpr __forceinline void InternalIncrementSize() { ++mSize; }
		constexpr __forceinline void InternalDecrementSize() { --mSize; }
		constexpr __forceinline bool InternalCheckInBound(uint64_t index) { return index < 0 || index >= mSize; }

		Array();
		Array(uint64_t allocationByteSize);
		virtual ~Array();
	public:

#ifdef TMM_CONTAINER_FUNCTIONAL_ENABLE
		// Return if all of the callbacks succeded. 
		virtual bool Execute(const TMM::Function<bool, const uint64_t&, T&>& callback) override final;
#endif

		// Return the amount of different KEYS
		virtual uint64_t Size() override final;

		// Return the CONTENT associated with a KEY
		virtual T& operator[](const uint64_t& key);

		// Return the CONTENT associated with a KEY
		virtual const T& at(const uint64_t& key) const override final;

		// Try to access the CONTENT associated with a KEY and return if it succeded
		virtual bool TryGet(const uint64_t& key, T* pDest) override final;

		virtual void Add(const T& value);
		virtual void Remove(const T& value) = 0;
		virtual void RemoveAt(uint64_t index) = 0;
	};

}

#include <TMM_Array.hpp>
