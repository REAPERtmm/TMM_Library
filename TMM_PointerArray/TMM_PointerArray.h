#pragma once
#include "framework.h"

template<typename _From, typename _To>
concept Castable = requires(_From value) { static_cast<_To>(value); };

template<typename _Type>
concept HasDefaultConstructor = requires(_Type value) { _Type(); };

template<typename T>
class TMM_PointerArray
{
	T** mpArray;
	UINT32 mCapacity;
	UINT32 mSize;
	void _Extend();
	void _Shrink();
public:
	// Construct
	template<typename... Args>
	TMM_PointerArray(Args... args) requires (Castable<Args, T*> && ...);
	
	// Get
	T* operator[](UINT32 index);
	T* Right();
	T* Left();
	UINT32 Size() const;

	// Modif
	void AddElementRight(T* pElt);
	void AddElementRight(T& elt) requires HasDefaultConstructor<T>;
};

#include "TMM_PointerArray.inl"

