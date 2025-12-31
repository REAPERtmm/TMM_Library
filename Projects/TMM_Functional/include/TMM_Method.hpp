#include "TMM_Method.h"


namespace TMM {
	template<typename Obj, typename Ret, typename ...Args>
	auto MakeMethod(Obj* obj, Ret(Obj::* method)(Args...))
	{
		return Method<Obj, Ret, Args...>(obj, method);
	}

	template<typename Obj, typename Ret>
	auto MakeMethod(Obj* obj, Ret(Obj::* method)())
	{
		return Method<Obj, Ret>(obj, method);
	}

	template<typename Obj, typename Ret, typename ...Args>
	inline Method<Obj, Ret, Args...>::Method(Obj* pObj, Ret(Obj::* pMethod)(Args...))
		: mpObj(pObj), mpMethod(pMethod)
	{

	}

	template<typename Obj, typename Ret, typename ...Args>
	inline Ret Method<Obj, Ret, Args...>::Call(Args ...args) const
	{
		return (mpObj->*mpMethod)(args...);
	}

	template<typename Obj, typename Ret, typename ...Args>
	inline Ret Method<Obj, Ret, Args...>::operator()(Args ...args) const
	{
		return Call(args...);
	}

	template<typename Obj, typename Ret, typename ...Args>
	inline void Method<Obj, Ret, Args...>::SwapObj(Obj* pObj)
	{
		mpObj = pObj;
	}

	template<typename Obj, typename Ret, typename ...Args>
	inline void Method<Obj, Ret, Args...>::operator = (Obj* pObj)
	{
		SwapObj(pObj);
	}


	template<typename Ret, typename ...Args>
	template<typename F>
	inline LambdaMethod<Ret, Args...>::LambdaMethod(F&& f)
	{
		using Fun = TMM::decay_t<F>;
		mpObj = new Fun(TMM::forward<F>(f));
		mCall = [](void* obj, Args... args) -> Ret {
			return (*static_cast<Fun*>(obj))(args...);
			};
		mDestroy = [](void* obj) -> void {
			delete static_cast<Fun*>(obj);
			};
	}

	template<typename Ret, typename ...Args>
	inline LambdaMethod<Ret, Args...>::~LambdaMethod()
	{
		if (mDestroy != nullptr)
		{
			mDestroy(mpObj);
		}
	}

	template<typename Ret, typename ...Args>
	inline Ret LambdaMethod<Ret, Args...>::Call(Args ...args) const
	{
		return mCall(mpObj, args...);
	}

	template<typename Ret, typename ...Args>
	inline Ret LambdaMethod<Ret, Args...>::operator()(Args ...args) const
	{
		return mCall(mpObj, args...);
	}
}