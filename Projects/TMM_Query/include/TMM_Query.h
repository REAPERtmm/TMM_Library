#pragma once

#include <TMM_Setup.h>

#include <TMM_Array.h>
#include <TMM_UnorderedArray.h>
#include <TMM_Method.h>

namespace TMM {
	struct QIndex {
		uint64_t Index;

		bool operator == (const QIndex& other) { return other.Index == Index; }

		QIndex(uint64_t index = 0) : Index(index) {}
	};

	template<typename T>
	class Query {
		Array<T>* mpArray;
		ArrayUnordered<QIndex> mFiletered;
	public:
		Query(Array<T>& array);

		template<typename Obj>
		Query<T>& Where(Method<Obj, void, const T&>& f);
		Query<T>& Where(Function<bool, const T&>& f);
		Query<T>& Where(bool (*f)(const T&));

		template<typename Obj>
		void Call(Method<Obj, void, const T&>& f);
		void Call(Function<void, const T&>& f);
		void Call(void (*f)(const T&));
	};




}

#include <TMM_Query.hpp>