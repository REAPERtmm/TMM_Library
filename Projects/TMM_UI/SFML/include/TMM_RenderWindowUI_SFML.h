#pragma once

#include <TMM_Setup.h>
#include <TMM_WindowUI.h>

#include "TMM_UI_Implement_SFML.h"
#include "TMM_Canvas_SFML.h"

#include <TMM_Vectors.h>
#include <TMM_OrderedArray.h>

namespace TMM
{

	class RenderWindowUISFML : public WindowUISFML
	{
		TMM::Vec2f mSize						= { 0, 0 };
		sf::RenderWindow* mpWindow				= nullptr;
		sf::RectangleShape* mpShape				= nullptr;
		TMM::ArrayOrdered<CanvasSFML*> mpRoots	= {};
		WidgetUpdateCtx mCtx					= {};

	public:
		RenderWindowUISFML() = default;
		virtual ~RenderWindowUISFML();

		virtual void Init(TMM::Vec2f size, const char* title, bool fullscreen = false) override;

		virtual TMM::Vec2f GetSize() const override { return mSize; }
		virtual bool IsOpen() const override { return mpWindow->isOpen(); }

		virtual void AddRoot(WidgetSFML* pRoot) override;

		virtual void Update() override;
		virtual void Render() override;

		virtual void Destroy() override;

	};

}
