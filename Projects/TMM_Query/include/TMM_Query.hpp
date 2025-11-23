#include "TMM_Query.h"
#include <TMM_Query.h>

namespace TMM {

	template<typename T>
	inline Query<T>::Query(Array<T>& array)
	{
		mpArray = &array;
		// TODO : Fix with new Array
		//mFiletered = TMM::Array<QIndex>( mpArray->Size(), [](uint64_t index) { return QIndex(index); } );
	}

	template<typename T>
	template<typename Obj>
	inline Query<T>& Query<T>::Where(Method<Obj, void, const T&>& f)
	{
		uint64_t i = 0;
		while (i < mFiletered.Size()) {
			QIndex& qi = mFiletered[i];
			if (f(mpArray->at(qi.Index)) == false) {
				mFiletered.RemoveAt(i);
			}
			else
			{
				i++;
			}
		}
		return *this;
	}

	template<typename T>
	inline Query<T>& Query<T>::Where(Function<bool, const T&>& f)
	{
		uint64_t i = 0;
		while (i < mFiletered.Size()) {
			QIndex& qi = mFiletered[i];
			if (f(mpArray->at(qi.Index)) == false) {
				mFiletered.RemoveAt(i);
			}
			else 
			{
				i++;
			}
		}
		return *this;
	}

	template<typename T>
	inline Query<T>& Query<T>::Where(bool(*f)(const T&))
	{
		uint64_t i = 0;
		while (i < mFiletered.Size()) {
			QIndex& qi = mFiletered[i];
			if (f(mpArray->at(qi.Index)) == false) {
				mFiletered.RemoveAt(i);
			}
			else
			{
				i++;
			}
		}
		return *this;
	}



	template<typename T>
	template<typename Obj>
	inline void Query<T>::Call(Method<Obj, void, const T&>& f)
	{
		for (uint64_t i = 0; i < mFiletered.Size(); ++i) {
			f(mpArray->at(mFiletered[i].Index));
		}
	}

	template<typename T>
	inline void Query<T>::Call(Function<void, const T&>& f)
	{
		for (uint64_t i = 0; i < mFiletered.Size(); ++i) {
			f(mpArray->at(mFiletered[i].Index));
		}
	}
	template<typename T>
	inline void Query<T>::Call(void(*f)(const T&))
	{
		for (uint64_t i = 0; i < mFiletered.Size(); ++i) {
			f(mpArray->at(mFiletered[i].Index));
		}
	}
}