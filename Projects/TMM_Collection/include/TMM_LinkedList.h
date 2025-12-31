#pragma once

// REQUIRED internal include
#include <TMM_Setup.h>
#include "TMM_Collection.h"

namespace TMM 
{
	template<typename T>
	struct Node {
		T Value;
		Node<T>* pPrevious;
		Node<T>* pNext;
	};

	template<typename T>
	class LinkedList : public TMM::Collection<uint64_t, T>
	{
	protected:
		uint64_t mSize;
		Node<T>* mpFirst;
		Node<T>* mpLast;

		// constexpr inline accessor
		constexpr __forceinline Node<T>*& InternalGetFirst() { return mpFirst; }
		constexpr __forceinline const Node<T>* const& InternalGetFirst() const { return mpFirst; }
		constexpr __forceinline Node<T>*& InternalGetLast() { return mpLast; }
		constexpr __forceinline const Node<T>* const& InternalGetLast() const { return mpLast; }
		constexpr __forceinline uint64_t& InternalGetSize() { return mSize; }
		constexpr __forceinline const uint64_t& InternalGetSize() const { return mSize; }
		constexpr __forceinline void InternalIncrementSize() { ++mSize; }
		constexpr __forceinline void InternalDecrementSize() { --mSize; }
		constexpr __forceinline bool InternalCheckInBound(uint64_t index) { return index < 0 || index >= mSize; }
		
		LinkedList();
		virtual ~LinkedList();

		void InternalPushFirst(const T& value);
		void InternalPushLast(const T& value);

		T InternalPopFirst();
		T InternalPopLast();

	public:
#ifdef TMM_COLLECTION_FUNCTIONAL_ENABLE
		/// <summary>
		/// Execute a fonction on every element in the list with as input : (const uint64_t& index, T& element)
		/// </summary>
		/// <returns>Return if all of the callbacks succeded.</returns>
		virtual bool Execute(const TMM::Callable<bool, const uint64_t&, T&>& callback) override;
		/// <summary>
		/// Execute a fonction on every element in the list with as input : (T* pPrevious, T& element, T* pNext)
		/// </summary>
		/// <returns>Return if all of the callbacks succeded.</returns>
		virtual bool Execute(const TMM::Callable<bool, T*, T&, T*>& callback);
#endif

		// Return the amount of different KEYS
		virtual uint64_t Size() const override final;

		// Return the CONTENT associated with a KEY
		virtual T& operator[](const uint64_t& key);

		// Return the CONTENT associated with a KEY
		virtual const T& at(const uint64_t& key) const override final;

		// Try to access the CONTENT associated with a KEY and return if it succeded
		virtual bool TryGet(const uint64_t& key, T* pDest) override final;
	};

}

#include "TMM_LinkedList.hpp"