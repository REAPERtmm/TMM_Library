#include "TMM_Container.h"

namespace TMM {

	template<typename KEY, typename CONTENT, typename CONTAINER_NODE>
	inline Container<KEY, CONTENT, CONTAINER_NODE>::Container(uint64_t default_size) : mSize(default_size) {}

	template<typename KEY, typename CONTENT, typename CONTAINER_NODE>
	inline const bool Container<KEY, CONTENT, CONTAINER_NODE>::InternalInBounds(const KEY& key) const
	{
		return 0 <= key && key < this->mSize;
	}

	template<typename KEY, typename CONTENT, typename CONTAINER_NODE>
	const uint64_t Container<KEY, CONTENT, CONTAINER_NODE>::Size() const {
		return mSize;
	}

}