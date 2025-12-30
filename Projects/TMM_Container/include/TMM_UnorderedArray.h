#pragma once

// REQUIRED internal include
#include <TMM_Setup.h>
#include "TMM_Array.h"

namespace TMM {

	template<typename T>
	class ArrayUnordered : public Array<T> {
	public:
		ArrayUnordered() : Array<T>() {}
		ArrayUnordered(uint64_t allacationByteSize) : Array<T>(allacationByteSize) {}
		virtual ~ArrayUnordered() override {}

		virtual void Remove(const T& value) override;
		virtual void RemoveAt(uint64_t index) override;
	};
	
}

#include <TMM_UnorderedArray.hpp>
