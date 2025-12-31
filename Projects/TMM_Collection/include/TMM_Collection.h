#pragma once

// REQUIRED internal include
#include <TMM_Setup.h>

// NOT REQUIRED internal include
#ifdef TMM_COLLECTION_FUNCTIONAL_ENABLE
#include <TMM_Function.h>
#endif

// REQUIRED external include
#include <memory>

namespace TMM
{
	template<typename KEY, typename CONTENT>
	__interface Collection{
	public:
#ifdef TMM_COLLECTION_FUNCTIONAL_ENABLE
		// Return if all of the callbacks succeded. 
		virtual bool Execute(const TMM::Callable<bool, const KEY&, CONTENT&>& callback) = 0;

		// TODO : 
		// Execute callback on every elements IF condition returned true (and Return if all of the callbacks succeded.)
		//virtual bool ExecuteIf(
		//	const TMM::Function<bool, CONTENT&>& condition,
		//	const TMM::Function<bool, const KEY&, CONTENT&>& callback
		//)  = 0;
#endif
		// Return the amount of different KEYS
		virtual uint64_t Size() const = 0;

		// Return the const CONTENT ref associated with a KEY
		virtual const CONTENT& at(const KEY& key) const = 0;

		// Try to access the CONTENT associated with a KEY and return if it succeded
		virtual bool TryGet(const KEY& key, CONTENT* pDest) = 0;
	};
}

#include "TMM_Collection.hpp"