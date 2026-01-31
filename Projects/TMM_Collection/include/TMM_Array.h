#pragma once

// REQUIRED internal include
#include <TMM_Setup.h>
#include "TMM_Collection.h"

// REQUIRED external include
#include <memory>

namespace TMM {
	template<typename T>
	class Array : 
		public _Collection<uint64_t, T, Array<T>>, 
		public _Iterable<uint64_t, T, Array<T>> 
	{
	protected:
		T* mpData;
		uint64_t mSize;
		uint64_t mCapacity;

		void InternalAllocate(uint64_t capacity);

		// constexpr inline accessor
		constexpr __forceinline T*& InternalGetStartPtr() { return mpData; }
		constexpr __forceinline uint64_t& InternalGetSize() { return mSize; }
		constexpr __forceinline uint64_t InternalGetSize() const { return mSize; }
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

#ifdef TMM_COLLECTION_FUNCTIONAL_ENABLE
		// Return if all of the <callback> succeded. 
		virtual bool Execute(
			const TMM::Callable<bool, const uint64_t&, T&>& callback
		) override;

		// Execute <callback> on every elements IF <condition> returned true (and Return if all of the <callback> succeded.)
		virtual bool ExecuteIf(
			const TMM::Callable<bool, const uint64_t&, T&>& condition,
			const TMM::Callable<bool, const uint64_t&, T&>& callback
		)  override;

		// Execute <callback> on every elements UNTIL the <condition> is met (excluded) or we reached the end (and Return if all of the <callback> succeded.)
		virtual bool ExecuteUntil(
			const TMM::Callable<bool, const uint64_t&, T&>& condition,
			const TMM::Callable<bool, const uint64_t&, T&>& callback
		)  override;

		// Execute <callback> on every elements from <start> UNTIL the <condition> is met (excluded) or we reached the end (and Return if all of the <callback> succeded.)
		virtual bool ExecuteUntil(
			const TMM::Callable<bool, const uint64_t&, T&>& condition,
			const TMM::Callable<bool, const uint64_t&, T&>& callback,
			const uint64_t& start
		)  override;

		// Execute <callback> on every elements FROM when the <condition> is met (included) to the end  or none if not reached (and Return if all of the <callback> succeded.)
		virtual bool ExecuteFrom(
			const TMM::Callable<bool, const uint64_t&, T&>& condition,
			const TMM::Callable<bool, const uint64_t&, T&>& callback
		)  override;

		// Execute <callback> on every elements FROM when the <condition> is met (included) to the <end> or none if not reached (and Return if all of the <callback> succeded.)
		virtual bool ExecuteFrom(
			const TMM::Callable<bool, const uint64_t&, T&>& condition,
			const TMM::Callable<bool, const uint64_t&, T&>& callback,
			const uint64_t& end
		)  override;

		// Execute <callback> on every elements FROM when the <conditionStart> is met to when the <conditionEnd> is met (and Return if all of the <callback> succeded.)
		virtual bool ExecuteBetween(
			const TMM::Callable<bool, const uint64_t&, T&>& conditionStart,
			const TMM::Callable<bool, const uint64_t&, T&>& conditionEnd,
			const TMM::Callable<bool, const uint64_t&, T&>& callback
		)  override;
#endif

		// Return the amount of different KEYS
		virtual uint64_t Size() const override final;

		// Resize to fit size element
		virtual void Resize(uint64_t size);

		// Return the T associated with a uint64_t
		virtual T& operator[](const uint64_t& key);

		// Return the T associated with a uint64_t
		virtual const T& at(const uint64_t& key) const override final;

		// Try to access the T associated with a uint64_t and return if it succeded
		virtual bool TryGet(const uint64_t& key, T* pDest) override final;

		virtual void Add(const T& value);
		virtual void Remove(const T& value) = 0;
		virtual void RemoveAt(uint64_t index) = 0;
	};

}

#include <TMM_Array.hpp>
