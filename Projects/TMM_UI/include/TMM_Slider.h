#pragma once

#include <TMM_Setup.h>

#include "TMM_Widget.h"
#include "TMM_WidgetEnums.h"

#include "TMM_WidgetEvents.h"

namespace TMM
{
	
	enum SliderOrientation
	{
		HORIZONTAL,
		VERTICAL
	};

	template<TMM_WidgetTemplateDefine>
	class SliderEvents : public WidgetEvents<TMM_WidgetTypenameDefine>
	{
	public:
		using OnValueChanged = TMM::Callable<void, float, float>; // old value, new value
		using OnValueChangedNormalized = TMM::Callable<void, float, float>; // old value normalized, new value normalized
	private:		
		TMM::ArrayUnordered<OnValueChanged*>*			mpOnValueChanged;
		TMM::ArrayUnordered<OnValueChangedNormalized*>* mpOnValueChangedNormalized;
	public:
		SliderEvents() :
			mpOnValueChanged(new TMM::ArrayUnordered<OnValueChanged*>()),
			mpOnValueChangedNormalized(new TMM::ArrayUnordered<OnValueChangedNormalized*>())
		{}

		virtual ~SliderEvents()
		{
			TMM_ITER(i, mpOnValueChanged->Size()) { delete mpOnValueChanged->at(i); }
			TMM_ITER(i, mpOnValueChangedNormalized->Size()) { delete mpOnValueChangedNormalized->at(i); }

			delete mpOnValueChanged;
			delete mpOnValueChangedNormalized;
		}

		void RegisterCallbackValueChanged(OnValueChanged* pCallback) { mpOnValueChanged->Add(pCallback); }
		void RegisterCallbackValueChangedNormalized(OnValueChangedNormalized* pCallback) { mpOnValueChangedNormalized->Add(pCallback); }
	
		void ProcCallbackValueChanged(float old_value, float new_value) {
			TMM_ITER(i, mpOnValueChanged->Size()) { mpOnValueChanged->at(i)->Call(old_value, new_value); }
		}
		void ProcCallbackValueChangedNormalized(float old_value, float new_value) {
			TMM_ITER(i, mpOnValueChangedNormalized->Size()) { mpOnValueChangedNormalized->at(i)->Call(old_value, new_value); }
		}
	};

	__interface Slider
	{

	};

}