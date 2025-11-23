#pragma once
#include <TMM_Setup.h>
#include <TMM_Container.h>
#include <memory>

namespace TMM {
	template<typename T>
	class Array : public Container<uint64_t, T, DEFAULT_CONTAINER_NODE<uint64_t, T>> {
	protected:
		T* mpData;
		uint64_t mCapacity;

		void InternalAllocate(uint64_t capacity);
		T& InternalGet(const uint64_t& key);

		Array();
		Array(uint64_t allocationByteSize);
		virtual ~Array();
	public:
		using ARRAY_NODE = DEFAULT_CONTAINER_NODE<uint64_t, T>;
		using BASE = Container<uint64_t, T, DEFAULT_CONTAINER_NODE<uint64_t, T>>;

		virtual void Add(const T& value);
		virtual void Remove(const T& value)		= 0;
		virtual void RemoveAt(uint64_t index)	= 0;

		bool Execute(const TMM::Function<bool, ARRAY_NODE&>& callback) override final;
		virtual T& operator[](const uint64_t& key) override final;
		virtual ARRAY_NODE at(const uint64_t& key) override final;
		virtual bool TryGet(const uint64_t& key, ARRAY_NODE* pDest) override final;
	};

}

#include <TMM_Array.hpp>
