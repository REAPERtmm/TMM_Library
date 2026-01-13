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
#define ALIGN(size) __declspec(align(size))
#else
#define ALIGN16 __attribute__((aligned(16)))
#define ALIGN(size) __attribute__((aligned(size)))
#endif

// Notation Defines

#define PURE = 0

// Compute Manip

#define TMM_MAX(a, b) ((a) < (b) ? (b) : (a))
#define TMM_MIN(a, b) ((a) < (b) ? (a) : (b))
#define TMM_CLAMP(v, v_min, v_max) ((v) < (v_min) ? (v_min) : ((v) > (v_max) ? (v_max) : (v)))
#define TMM_CLAMP01(v) TMM_CLAMP(v, 0, 1)
#define TMM_SWAP(a, b) auto temp = (a); (a) = (b); (b) = temp;
#define TMM_SWAP_XOR(a, b) (a) = (a) ^ (b); (b) = (a) ^ (b); (a) = (a) ^ (b);

// Bit Manip

#define TMM_ON  0b1
#define TMM_OFF 0b0
#define TMM_BITFIELD_MASK_ALL  0b11111111
#define TMM_BITFIELD_MASK_NONE 0b00000000
#define TMM_BITFIELD_MASK(bit0, bit1, bit2, bit3, bit4, bit5, bit6, bit7) ( \
				   (bit0) | ((bit1) << 1) | ((bit2) << 2 ) | ((bit3) << 3 ) | \
			((bit4) << 4) | ((bit5) << 5) | ((bit6) << 6 ) | ((bit7) << 7 ) \
	)

// REQUIRED external include
#include <stdint.h>

namespace TMM {

	using ERROR_CODE = int;

	using Second_f = float;
	using Second_u = unsigned int;

	using MilliSecond_f = float;
	using MilliSecond_u = unsigned int;

	using MicroSecond_u = unsigned int;
	
	using NanoSecond_u = unsigned int;

#define TMM_FAILED(code) (code) != 0
#define TMM_FAILED_WITH(code, err) (code) & (err) != 0

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
	struct is_array {
		static constexpr bool value = false;
	};

	template<typename T, uint64_t SIZE>
	struct is_array<T[SIZE]> {
		static constexpr bool value = true;
	};

	template<typename T>
	struct is_function {
		static constexpr bool value = false;
	};

	template<typename Ret, typename... Args>
	struct is_function<Ret(Args...)> {
		static constexpr bool value = true;
	};

	template<typename Ret, typename... Args>
	struct is_function<Ret(Args...) noexcept> {
		static constexpr bool value = true;
	};

	template<typename T>
	struct remove_ref { using type = T; };

	template<typename T>
	struct remove_ref<T&> { using type = T; };

	template<typename T>
	struct remove_ref<T&&> { using type = T; };

	template<typename T>
	using remove_ref_t = typename remove_ref<T>::type;

	// select<sizeof(T) > 1>::Apply<int, char>
	// si (sizeof(T) est superieur à 1) alors (int) sinon (char)

	template <bool>
	struct select { 
		template <class _Ty1, class>
		using Apply = _Ty1;
	};

	template <>
	struct select<false> {
		template <class, class _Ty2>
		using Apply = _Ty2;
	};

	template <class... _Types>
	using void_t = void;

	template <class T, class = void>
	struct Add_pointer {
		using type = T;
	};

	template<class T>
	struct Add_pointer<T, void_t<remove_ref_t<T>>*> { 
		using type = remove_ref_t<T>*;
	};

	template <class T>
		struct Add_pointer_t {
		using type = typename Add_pointer<T>::type;
	};


	template <class T>
	constexpr T&& forward(remove_ref_t<T>& _Arg) noexcept {
		return static_cast<T&&>(_Arg);
	}

	template <class T>
	constexpr T&& forward(remove_ref_t<T>&& _Arg) noexcept {
		return static_cast<T&&>(_Arg);
	}

	template<typename T, typename... Ts>
	concept OneOf = is_one_of<T, Ts...>::value;

	template<typename T>
	concept Countable = OneOf <T,
		unsigned char, unsigned short, unsigned int, unsigned long long,
		char, short, int, long long,
		float, double
	>;

	template<typename T>
	concept Decimal = OneOf <T,
		float, double
	>;

	template<typename T>
	constexpr bool IsFunction = is_function<T>::value;

	template<typename T>
	constexpr bool IsArray = is_array<T>::value;

	template<typename T>
	constexpr bool IsEnum = __is_enum(T);

	template<typename Base, typename Derived>
	constexpr bool IsBaseOf = __is_base_of(Base, Derived);

	// return : if (T is a function) => a ptr to this function else if (T is an array) => a ptr to this array
	template <class T>
	struct decay {
		using _T1 = remove_ref_t<T>;
		using _T2 = typename select<IsFunction<_T1>>::template Apply<Add_pointer_t<_T1>, _T1>;
		using type = typename select<IsArray<_T1>>::template Apply<Add_pointer_t<_T1>, _T2>;
	};
	
	template <class T>
	using decay_t = decay<T>::type;
}
