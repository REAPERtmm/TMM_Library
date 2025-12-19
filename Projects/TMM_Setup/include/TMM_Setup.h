#pragma once

#ifndef NDEBUG

#define _CRTDBG_MAP_ALLOC
#define D3D_DEBUG_INFO
#include <crtdbg.h>

#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__ , __LINE__)
#define new DEBUG_NEW

#endif // !NDEBUG

#ifdef _MSC_VER
#define ALIGN16 __declspec(align(16))
#else
#define ALIGN16 __attribute__((aligned(16)))
#endif


#include <stdint.h>

namespace TMM {

    template<typename A, typename B>
    struct is_same {
        static constexpr bool value = false;
    };

    template<typename A>
    struct is_same<A, A> {
        static constexpr bool value = true;
    };

	template<typename T, typename... Ts>
	struct is_one_of {
		static constexpr bool value = (false || ... || TMM::is_same<T, Ts>::value);
	};

	template<typename T>
	struct remove_ref { using type = T; };

	template<typename T>
	struct remove_ref<T&> { using type = T; };

	template<typename T>
	struct remove_ref<T&&> { using type = T; };

	template<typename T>
	using remove_ref_t = typename remove_ref<T>::type;

	template<typename T, typename... Ts>
	concept OneOf = is_one_of<T, Ts...>::value;

	template<typename T>
	concept Countable = OneOf <T,
		unsigned char, unsigned short, unsigned int, unsigned long long,
		char, short, int, long long,
		float, double
	>;

	template<typename Enum>
	constexpr bool IsEnum = __is_enum(Enum);

	template<typename Base, typename Derived>
	constexpr bool IsBaseOf = __is_base_of(Base, Derived);
}
