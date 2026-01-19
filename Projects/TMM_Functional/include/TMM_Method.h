#pragma once

// REQUIRED internal include
#include <TMM_Setup.h>
#include "TMM_Callable.h"

namespace TMM {

	template<typename Obj, typename Ret, typename... Args>
	class Method : public Callable<Ret, Args...> {
	protected:
		Obj* mpObj = nullptr;
		Ret(Obj::* mpMethod)(Args...);
	public:
		Method() = default;	
		Method(Obj* pObj, Ret(Obj::* pMethod)(Args...));

		Ret Call(Args... args) const override;
		virtual Ret operator()(Args... args) const override;

		virtual void SwapObj(Obj* pObj) final;
		virtual void operator = (Obj* pObj) final;
	};

	template<typename Ret, typename... Args>
	class LambdaMethod : public Callable<Ret, Args...>
	{
		using CallFn = Ret(*)(void*, Args...);
		using DestroyFn = void(*)(void*);
		void* mpObj = nullptr;
		CallFn mCall = nullptr;
		DestroyFn mDestroy = nullptr;
	public:
		LambdaMethod() = default;

		template<typename F>
		LambdaMethod(F&& f);

		~LambdaMethod();

		Ret operator()(Args... args) const override;

		Ret Call(Args... args) const override;
	};

	template <typename Obj, typename Ret, typename... Args>
	auto MakeMethod(Obj* obj, Ret(Obj::* method)(Args...));

	template <typename Obj, typename Ret>
	auto MakeMethod(Obj* obj, Ret(Obj::* method)());

	template <typename Obj, typename Ret, typename... Args>
	auto MakeMethodPtr(Obj* obj, Ret(Obj::* method)(Args...));

	template <typename Obj, typename Ret>
	auto MakeMethodPtr(Obj* obj, Ret(Obj::* method)());

	template<typename Obj, typename Ret, typename... Args>
	Method(Obj*, Ret(Obj::*)(Args...)) -> Method<Obj, Ret, Args...>;

	template<typename Obj, typename Ret, typename... Args>
	Method(Obj*, Ret(Obj::*)(Args...) const) -> Method<Obj, Ret, Args...>;
}

#include <TMM_Method.hpp>
