#pragma once

#include <TMM_Setup.h>
#include "TMM_UI.h"

#include <SFML/Graphics.hpp>

#define TMM_WidgetSFMLTypenameDefine sf::Texture, sf::RectangleShape

namespace TMM
{

	using WidgetSFML = TMM::Widget<TMM_WidgetSFMLTypenameDefine>;
	using WidgetEventsSFML = TMM::WidgetEvents<TMM_WidgetSFMLTypenameDefine>;
	using WindowUISFML = TMM::WindowUI<TMM_WidgetSFMLTypenameDefine>;

	__forceinline sf::Color TranslateColor(const TMM::Color& c) { return { c.r, c.g, c.b, c.a }; }
	__forceinline TMM::Color TranslateColor(const sf::Color& c) { return { c.r, c.g, c.b, c.a }; }

	__forceinline sf::Vector2f TranslateVec2f(const TMM::Vec2f& v) { return { v.x, v.y }; }
	__forceinline TMM::Vec2f TranslateVec2f(const sf::Vector2f& v) { return { v.x, v.y }; }

}