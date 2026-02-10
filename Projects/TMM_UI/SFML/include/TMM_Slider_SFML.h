#pragma once

#include <TMM_Setup.h>
#include <TMM_UI.h>
#include <TMM_UI_Implement_SFML.h>

#include "TMM_Canvas_SFML.h"
#include "TMM_Slider.h"

namespace TMM
{

	struct SliderSFMLDescriptor : public CanvasSFMLDescriptor
	{
		SliderOrientation SliderOrient		= SliderOrientation::HORIZONTAL;
		float SliderMinValue				= 0;
		float SliderMaxValue				= 1;
		float SliderDefaultValue			= 0;
		float SliderHandleWidth				= 0.1f;

		CanvasSFMLDescriptor SliderHandleDesc = [] {
			CanvasSFMLDescriptor desc{};
			desc.CanvasBackgroundColor = { 200, 200, 200, 255 };
			return desc;
		} ();
	};


	class SliderSFML : public CanvasSFML, public Slider
	{
		SliderOrientation mOrient = SliderOrientation::HORIZONTAL;
		float mMinValue;
		float mMaxValue;
		float mValue;

		float mHandleWidth;
		CanvasSFML* mpHandle;

		void ReplaceHandleWithValue();
		void CallBackOnDrag(TMM::MouseButton button, TMM::Vec2f mouse_position, TMM::Vec2f delta);
	public:
		SliderSFML(WidgetSFML* pParent, SliderSFMLDescriptor* pDesc);

		float GetValue() { return mValue; }
		float GetValueNormalized() { return mValue / (mMaxValue - mMinValue); }

		void SetValue(float v);
		void SetValueNormalized(float v);
	};

}
