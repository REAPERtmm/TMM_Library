#pragma once

// REQUIRED internal include
#include <TMM_Setup.h>
#include "TMM_LinkedList.h"

namespace TMM 
{
	/// <summary>
	/// A Data Structure representing a stack (0 represent the next element retrieved)
	/// </summary>
	template<typename T>
	class Stack : public TMM::LinkedList<T>
	{
	public:
		Stack();
		~Stack();

		void PushStack(const T& value);
		T PopStack();
		bool TryPopStack(T* pDest);
#ifdef TMM_COLLECTION_FUNCTIONAL_ENABLE
		bool Execute(const TMM::Callable<bool, T*, T&, T*>& callback) override;


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
#endif // TMM_COLLECTION_FUNCTIONAL_ENABLE

	};
}

#include "TMM_Stack.hpp"