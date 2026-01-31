#pragma once

#include <TMM_Setup.h>
#include <TMM_Vectors.h>

#define TMM_WidgetTemplateDefine typename Texture_t, typename Brush_t
#define TMM_WidgetTypenameDefine Texture_t, Brush_t

namespace TMM 
{
	enum class MouseButton
	{
		LEFT,
		MIDDLE,
		RIGHT
	};
	
	enum ANCHOR : int
	{
		TOP_LEFT,	   CENTER_TOP,    TOP_RIGHT,
		CENTER_LEFT,   CENTER_CENTER, CENTER_RIGHT,
		BOTTOM_BOTTOM, CENTER_BOTTOM, BOTTOM_RIGHT,
		NONE
	};

	inline static const TMM::Vec2f ANCHOR_DISPLACEMENT[9]
	{
		{ 0.0f, 0.0f }, { 0.5f, 0.0f }, { 1.0f, 0.0f },
		{ 0.0f, 0.5f }, { 0.5f, 0.5f }, { 1.0f, 0.5f },
		{ 0.0f, 1.0f }, { 0.5f, 1.0f }, { 1.0f, 1.0f }
	};

	struct Color
	{
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;
	};

	namespace CONSTANT {
		inline static const Color COLOR_WHITE		= { 255, 255, 255, 255 };
		inline static const Color COLOR_BLACK		= { 0, 0, 0, 255 };
		inline static const Color COLOR_RED			= { 255, 0, 0, 255 };
		inline static const Color COLOR_GREEN		= { 0, 255, 0, 255 };
		inline static const Color COLOR_BLUE		= { 0, 0, 255, 255 };
		inline static const Color COLOR_YELLOW		= { 255, 255, 0, 255 };
		inline static const Color COLOR_CYAN		= { 0, 255, 255, 255 };
		inline static const Color COLOR_MAGENTA		= { 255, 0, 255, 255 };
		inline static const Color COLOR_TRANSPARENT = { 0, 0, 0, 0 };


		inline static const Color COLOR_DEEP_BLUE	= { 13, 0, 27, 255 };
	}

	struct WidgetUpdateCtx
	{
		TMM::Vec2f mousePos		= { 0.0f, 0.0f };
		TMM::Vec2f mouseDelta	= { 0.0f, 0.0f };
		bool mouseClicked[3]	= { false, false, false };
		bool mouseDown[3]		= { false, false, false };

		bool KeyPressed[101]	= { false }; // standard 101 sfml keys (TODO : see for imporovement)
		bool KeyDown[101]		= { false }; // standard 101 sfml keys (TODO : see for imporovement)

		bool PreCalcInRect		= true;
	};

	struct WidgetPadding
	{
		float Left	= 0.0f;
		float Right = 0.0f;
		float Top	= 0.0f;
		float Down	= 0.0f;
	};

	struct WidgetBorder
	{
		float Thickness = -1.0f;
		Color Color{255, 255, 255, 255};
	};


}