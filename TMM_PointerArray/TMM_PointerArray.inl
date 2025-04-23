#include "TMM_PointerArray.h"

template<typename T>
template<typename... Args>
inline TMM_PointerArray<T>::TMM_PointerArray(Args... _args) requires (Castable<Args, T*> && ...)
{
	constexpr UINT64 size = sizeof...(_args);
	if constexpr (size == 0) {
		mpArray = new T * [DEFAULT_ARRAY_SIZE];
		mSize = 0;
		mCapacity = DEFAULT_ARRAY_SIZE;
	}
	else {
		UINT32 ArraySize;
		if constexpr (size * 2 < DEFAULT_ARRAY_SIZE) {
			ArraySize = DEFAULT_ARRAY_SIZE;
		}
		else {
			ArraySize = size * 2;
		}
		mpArray = new T * [ArraySize];
		mSize = size;
		mCapacity = ArraySize;

		UINT32 i = 0;
		auto ignore = {
			(mpArray[i++] = static_cast<T*>(_args), 0)...
		};
		(void)ignore;
	}
}

template<typename T>
inline void TMM_PointerArray<T>::_Extend()
{
	UINT32 _newCap = mCapacity * 2;
	T** _new = new T * [_newCap];
	for (UINT32 i = 0; i < mCapacity; ++i) {
		_new[i] = mpArray[i];
	}
	delete mpArray;
	mpArray = _new;
	mCapacity = _newCap;
}

template<typename T>
inline void TMM_PointerArray<T>::_Shrink()
{
	UINT32 _newCap = mCapacity * 2;
	if (_newCap < DEFAULT_ARRAY_SIZE) {
		_newCap = DEFAULT_ARRAY_SIZE;
	}
	T** _new = new T * [_newCap];
	for (UINT32 i = 0; i < mCapacity; ++i) {
		_new[i] = mpArray[i];
	}
	delete mpArray;
	mpArray = _new;
	mCapacity = _newCap;
}

template<typename T>
inline T* TMM_PointerArray<T>::operator[](UINT32 _index)
{
#ifdef _DEBUG
	if (_index < 0 || _index >= mSize) return nullptr;
#endif // _DEBUG
	return mpArray[_index];
}

template<typename T>
inline T* TMM_PointerArray<T>::Right()
{
#ifdef _DEBUG
	if (mSize == 0) return nullptr;
#endif // _DEBUG
	return mpArray[mSize - 1];
}

template<typename T>
inline T* TMM_PointerArray<T>::Left()
{
#ifdef _DEBUG
	if (mSize == 0) return nullptr;
#endif // _DEBUG
	return mpArray[0];
}

template<typename T>
inline UINT32 TMM_PointerArray<T>::Size() const 
{
	return mSize;
}

template<typename T>
inline void TMM_PointerArray<T>::AddElementRight(T* pElt)
{
	mpArray[mSize++] = pElt;
	if (mSize == mCapacity) {
		_Extend();
	}
}

template<typename T>
inline void TMM_PointerArray<T>::AddElementRight(T& elt) requires HasDefaultConstructor<T>
{
	mpArray[mSize++] = new T();
	*mpArray[mSize - 1] = elt;
	if (mSize == mCapacity) {
		_Extend();
	}
}
