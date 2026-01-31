#pragma once

#include <TMM_Setup.h>
#include "TMM_Widget.h"
#include "TMM_WidgetEnums.h"

namespace TMM
{
	template<TMM_WidgetTemplateDefine>
	__interface WindowUI {

		virtual void Init(TMM::Vec2f size, const char* title, bool fullscreen) = 0;

		virtual TMM::Vec2f GetSize() const = 0;
		virtual bool IsOpen() const = 0;

		virtual void AddRoot(Widget<TMM_WidgetTemplateDefine>* pRoot) = 0;

		virtual void Update() = 0;
		virtual void Render() = 0;

		virtual void Destroy() = 0;
	};

}