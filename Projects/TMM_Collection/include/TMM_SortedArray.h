#pragma once

// REQUIRED internal include
#include <TMM_Setup.h>
#include "TMM_Array.h"

namespace TMM
{

	// TODO :
	// Store data in a way that at any time every element are sorted
	template<typename T> requires(sizeof(T) <= 8)
	class SortedArray : public TMM::Array<T> {

	};

}

#include "TMM_SortedArray.hpp"