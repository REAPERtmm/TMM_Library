#pragma once

// REQUIRED internal include
#include <TMM_Setup.h>

namespace TMM {
	template<typename Ret, typename... Args>
	class Callable {
		virtual Ret Call(Args... args) const = 0;
		virtual Ret operator()(Args... args) const = 0;
	};
}

#include <TMM_Callable.hpp>
