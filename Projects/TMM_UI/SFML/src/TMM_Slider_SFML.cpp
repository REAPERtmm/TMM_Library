#include "TMM_Slider_SFML.h"

void TMM::SliderSFML::ReplaceHandleWithValue()
{
	float normalized = GetValueNormalized();

	if (mOrient == SliderOrientation::HORIZONTAL)
	{
		float handleWidth = mpHandle->GetSize().x;
		mpHandle->SetPosition({
			(GetSize().x - handleWidth) * normalized,
			0
		});
	}
	else {
		float handleWidth = mpHandle->GetSize().y;
		mpHandle->SetPosition({
			0,
			(GetSize().y - handleWidth) * normalized
		});
	}
}

void TMM::SliderSFML::CallBackOnDrag(TMM::MouseButton button, TMM::Vec2f mouse_position, TMM::Vec2f delta)
{

	if (mOrient == SliderOrientation::HORIZONTAL)
	{
		float mouse_pos = ToLocalPosition(mouse_position).x - mpHandle->GetSize().x * 0.5f;
		float total_width = GetSize().x - mpHandle->GetSize().x;
		float value_normalized = mouse_pos / total_width;
		value_normalized = TMM_CLAMP01(value_normalized);
		SetValueNormalized(value_normalized);
	}
	else
	{
		float mouse_pos = ToLocalPosition(mouse_position).y - mpHandle->GetSize().y * 0.5f;
		float total_width = GetSize().y - mpHandle->GetSize().y;
		float value_normalized = mouse_pos / total_width;
		value_normalized = TMM_CLAMP01(value_normalized);
		SetValueNormalized(value_normalized);
	}

}

TMM::SliderSFML::SliderSFML(WidgetSFML* pParent, SliderSFMLDescriptor* pDesc) :
	CanvasSFML(pParent, new SliderEventsSFML(), pDesc),
	mOrient(pDesc->SliderOrient),
	mMinValue(pDesc->SliderMinValue),
	mMaxValue(pDesc->SliderMaxValue),
	mValue(pDesc->SliderDefaultValue),
	mHandleWidth(pDesc->SliderHandleWidth)
{
	
	CanvasSFMLDescriptor desc = pDesc->SliderHandleDesc;
	desc.CanvasSize =
		mOrient == SliderOrientation::HORIZONTAL ?
		TMM::Vec2f{ mHandleWidth * GetSize().x, GetSize().y } :
		TMM::Vec2f{ GetSize().x, mHandleWidth * GetSize().y };
	mpHandle = AddChildToWidget<CanvasSFML>(this, &desc);
	ReplaceHandleWithValue();
	
	((SliderEventsSFML*)GetEvents())->RegisterCallbackDrag(
		TMM::MakeMethodPtr(this, &SliderSFML::CallBackOnDrag)
	);
}

void TMM::SliderSFML::SetValue(float v)
{
	((SliderEventsSFML*)GetEvents())->ProcCallbackValueChanged(GetValue(), v);
	((SliderEventsSFML*)GetEvents())->ProcCallbackValueChanged(GetValueNormalized(), (v / (mMaxValue - mMinValue)));
	mValue = v;
	ReplaceHandleWithValue();
}


void TMM::SliderSFML::SetValueNormalized(float v)
{
	SetValue((mMaxValue - mMinValue) * v + mMinValue);
}
