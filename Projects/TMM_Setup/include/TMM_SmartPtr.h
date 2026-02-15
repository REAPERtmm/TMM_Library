#pragma once

// REQUIRED external include
#include <stdint.h>

namespace TMM
{

	template<typename T>
	class SmartPtr
	{
		struct cPtr
		{
			T* ptr;
			uint64_t count;
		};
		cPtr* mPtr;

	public:
		SmartPtr() : mPtr(nullptr) 
		{ 

		}

		SmartPtr(T* ptr) : mPtr(new cPtr(ptr, 1))
		{

		}

		SmartPtr(const SmartPtr<T>& other) 
		{
			mPtr = other.mPtr;
			mPtr->count++;
		}

		~SmartPtr()
		{
			Delete();
		}

		void Delete()
		{
			if (mPtr == nullptr) return;
			mPtr->count--;
			if (mPtr->count <= 0)
			{
				delete mPtr->ptr;
				delete mPtr;
			}
			mPtr = nullptr;
		}

		T* ptr() { return mPtr; }

		SmartPtr<T>& operator = (const SmartPtr<T>& other)
		{
			if (other.mPtr->ptr == mPtr->ptr) return;
			mPtr = other.mPtr;
			mPtr->count++;
		}

		SmartPtr<T>& operator = (T* ptr)
		{
			Delete();
			mPtr = new cPtr(
				ptr,
				1
			);
		}

		T& operator *()
		{
			return *mPtr->ptr;
		}

		T* operator ->()
		{
			return mPtr->ptr;
		}

		SmartPtr<T>& operator ++()
		{
			Delete();
			mPtr = new cPtr(
				mPtr->ptr++,
				1
			);
			return *this;
		}

		SmartPtr<T>& operator ++(int)
		{
			SmartPtr<T> old = *this;
			Delete();
			mPtr = new cPtr(
				mPtr->ptr++,
				1
			);
			return old;
		}

		SmartPtr<T>& operator --()
		{
			Delete();
			mPtr = new cPtr(
				mPtr->ptr--,
				1
			);
			return *this;
		}

		SmartPtr<T>& operator --(int)
		{
			SmartPtr<T> old = *this;
			Delete();
			mPtr = new cPtr(
				mPtr->ptr--,
				1
			);
			return old;
		}
	};

}