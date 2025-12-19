#pragma once
#include <TMM_Setup.h>
#include "TMM_Container.h"

namespace TMM 
{
	template<typename T>
	struct Node {
		T Value;
		Node<T>* pPrevious;
		Node<T>* pNext;
	};

	template<typename T>
	class LinkedList : public TMM::Container<uint64_t, T, Node<T>>
	{
	protected:
		Node<T>* mpFirst;
		Node<T>* mpLast;

		LinkedList();
		virtual ~LinkedList();

		void PushFirst(const T& value);
		void PushLast(const T& value);

		T PopFirst();
		T PopLast();
	public:
		using LIST_NODE = Node<T>;
		using BASE = Container<uint64_t, T, Node<T>>;

		bool Execute(const TMM::Function<bool, LIST_NODE&>& callback) override;
		virtual T& operator[](const uint64_t& key) override final;
		virtual LIST_NODE at(const uint64_t& key) override final;
		virtual bool TryGet(const uint64_t& key, LIST_NODE* pDest) override final;
	};

}

#include "TMM_LinkedList.hpp"