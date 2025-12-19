#pragma once
#include <TMM_Setup.h>
#include <TMM_Function.h>
#include <memory>

namespace TMM
{
	template<typename KEY, typename CONTENT>
	struct DEFAULT_CONTAINER_NODE
	{
		KEY key;
		CONTENT content;
	};

	template<typename KEY, typename CONTENT, typename CONTAINER_NODE>
	class Container {
	protected:
		uint64_t mSize;
		Container(uint64_t default_size);
		virtual const bool InternalInBounds(const KEY& key) const;
	public:
		const uint64_t Size() const;
		
		// Return if all of the callbacks succeded. 
		virtual bool Execute(const TMM::Function<bool, CONTAINER_NODE&>& callback) = 0;
		virtual CONTENT& operator[](const KEY& key) = 0;
		virtual CONTAINER_NODE at(const KEY& key) = 0;
		virtual bool TryGet(const uint64_t& key, CONTAINER_NODE* pDest) = 0;
	};


}

#include "TMM_Container.hpp"