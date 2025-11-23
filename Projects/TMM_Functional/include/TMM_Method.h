#pragma once
#include "TMM_Callable.h"

namespace TMM {

	template<typename Obj, typename Ret, typename... Args>
	class Method : public Callable<Ret, Args...> {
		Obj* mpObj;
		Ret(Obj::* mpMethod)(Args...);
	public:
		Method(Obj* pObj, Ret(Obj::* pMethod)(Args...));

		Ret Call(Args... args) const;
		void SwapObj(Obj* pObj);

		Ret operator()(Args... args) const;
		void operator = (Obj* pObj);
	};

	template <typename Obj, typename Ret, typename... Args>
	auto MakeMethod(Obj* obj, Ret(Obj::* method)(Args...));

	template <typename Obj, typename Ret>
	auto MakeMethod(Obj* obj, Ret(Obj::* method)());

	template<typename Obj, typename Ret, typename... Args>
	Method(Obj*, Ret(Obj::*)(Args...)) -> Method<Obj, Ret, Args...>;

	template<typename Obj, typename Ret, typename... Args>
	Method(Obj*, Ret(Obj::*)(Args...) const) -> Method<Obj, Ret, Args...>;
}

#include <TMM_Method.hpp>
