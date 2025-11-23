#pragma once
#include <TMM_Array.h>

namespace TMM {

	template<typename T>
	class ArrayOrdered : public Array<T> {
	public:
		ArrayOrdered();
		ArrayOrdered(uint64_t allacationByteSize);
		virtual ~ArrayOrdered() override;

		virtual void Remove(const T& value) override;
		virtual void InsertAt(const T& value, uint64_t index);
		virtual void RemoveAt(uint64_t index) override;
	};
}

#include <TMM_OrderedArray.hpp>

