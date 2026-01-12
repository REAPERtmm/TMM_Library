#pragma once

// REQUIRED internal include
#include <TMM_Setup.h>

// NOT REQUIRED internal include
#ifdef TMM_COLLECTION_FUNCTIONAL_ENABLE
#include <TMM_Functional.h>
#endif

// REQUIRED external include
#include <memory>

namespace TMM
{
	template<typename KEY, typename CONTENT>
	__interface Collection
	{
	public:
		// Return the amount of different KEYS
		virtual uint64_t Size() const PURE;

		// Return the const CONTENT ref associated with a KEY
		virtual const CONTENT& at(const KEY& key) const PURE;

		// Try to access the CONTENT associated with a KEY and return if it succeded
		virtual bool TryGet(const KEY& key, CONTENT* pDest) PURE;
	};

	template<typename KEY, typename CONTENT>
	__interface Iterable
	{
		// TODO : Create Iterator

#ifdef TMM_COLLECTION_FUNCTIONAL_ENABLE
		// Return if all of the <callback> succeded. 
		virtual bool Execute(
			const TMM::Callable<bool, const KEY&, CONTENT&>& callback
		) PURE;

		// Execute <callback> on every elements IF <condition> returned true (and Return if all of the <callback> succeded.)
		virtual bool ExecuteIf(
			const TMM::Callable<bool, const KEY&, CONTENT&>& condition,
			const TMM::Callable<bool, const KEY&, CONTENT&>& callback
		)  PURE;

		// Execute <callback> on every elements UNTIL the <condition> is met (excluded) or we reached the end (and Return if all of the <callback> succeded.)
		virtual bool ExecuteUntil(
			const TMM::Callable<bool, const KEY&, CONTENT&>& condition,
			const TMM::Callable<bool, const KEY&, CONTENT&>& callback
		)  PURE;

		// Execute <callback> on every elements from <start> UNTIL the <condition> is met (excluded) or we reached the end (and Return if all of the <callback> succeded.)
		virtual bool ExecuteUntil(
			const TMM::Callable<bool, const KEY&, CONTENT&>& condition,
			const TMM::Callable<bool, const KEY&, CONTENT&>& callback,
			const KEY& start
		)  PURE;

		// Execute <callback> on every elements FROM when the <condition> is met (included) to the end or none if not reached (and Return if all of the <callback> succeded.)
		virtual bool ExecuteFrom(
			const TMM::Callable<bool, const KEY&, CONTENT&>& condition,
			const TMM::Callable<bool, const KEY&, CONTENT&>& callback
		)  PURE;

		// Execute <callback> on every elements FROM when the <condition> is met (included) to the <end> (excluded) or none if not reached (and Return if all of the <callback> succeded.)
		virtual bool ExecuteFrom(
			const TMM::Callable<bool, const KEY&, CONTENT&>& condition,
			const TMM::Callable<bool, const KEY&, CONTENT&>& callback,
			const KEY& end
		)  PURE;

		// Execute <callback> on every elements FROM when the <conditionStart> is met to when the <conditionEnd> is met (and Return if all of the <callback> succeded.)
		virtual bool ExecuteBetween(
			const TMM::Callable<bool, const KEY&, CONTENT&>& conditionStart,
			const TMM::Callable<bool, const KEY&, CONTENT&>& conditionEnd,
			const TMM::Callable<bool, const KEY&, CONTENT&>& callback
		)  PURE;
#endif
	};

	template<typename KEY, typename CONTENT, typename Derived>
	__interface _Collection : Collection<KEY, CONTENT> {};

	template<typename KEY, typename CONTENT, typename Derived>
	__interface _Iterable : Iterable<KEY, CONTENT> {};

}

#include "TMM_Collection.hpp"