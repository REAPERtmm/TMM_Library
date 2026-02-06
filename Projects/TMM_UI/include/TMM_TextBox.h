#pragma once

#include <TMM_Setup.h>

#include "TMM_Widget.h"
#include "TMM_WidgetEnums.h"

#include <string>

namespace TMM
{
	template<typename Font_t>
	__interface TextBox
	{

		// === ReadOnly ===

		virtual const Color&			GetTextColor() const = 0;
		virtual const WidgetBorder&		GetOutline() const = 0;
		virtual float					GetOutlineThickness() const = 0;
		virtual const Color&			GetOutlineColor() const = 0;
		virtual float					GetCharacterSpacingX() const = 0;
		virtual float					GetCharacterSpacingY() const = 0;
		virtual unsigned int			GetCharacterSize() const = 0;
		virtual unsigned int			GetMaxCharacterByLine() const = 0;
		virtual const std::string&		GetText() const = 0;
		virtual const Font_t*			GetFont() const = 0;
		virtual bool					GetBold() const = 0;
		virtual bool					GetItalic() const = 0;
		virtual bool					GetUnderLined() const = 0;
		virtual bool					GetStrikeThrough()const = 0;

		// === Getter ===

		virtual bool HasOutline() const = 0;
		
		// === Accessor ===

		virtual void SetTextColor(const Color& color) = 0;
		virtual void SetOutline(const WidgetBorder& border) = 0;
		virtual void SetCharacterSpacingX(float x) = 0;
		virtual void SetCharacterSpacingY(float y) = 0;
		virtual void SetCharacterSize(unsigned int size) = 0;
		virtual void SetMaxCharacterByLine(unsigned int count) = 0;
		virtual void SetText(const std::string& txt) = 0;
		virtual void SetFont(const Font_t* pFont) = 0;
		virtual void SetBold(bool active) = 0;
		virtual void SetItalic(bool active) = 0;
		virtual void SetUnderLined(bool active) = 0;
		virtual void SetStrikeThrough(bool active) = 0;

		// === Setter ===

		virtual void SetNoOutline() = 0;
		virtual void PlaceTextRelativeAnchor(ANCHOR anchor, TMM::Vec2f offset) = 0;

	};

}