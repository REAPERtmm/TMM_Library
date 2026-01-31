#pragma once

#include <TMM_Setup.h>

#include "TMM_Widget.h"
#include "TMM_WidgetEnums.h"

namespace TMM
{
	template<typename Font_t>
	__interface TextBox
	{

		// === ReadOnly ===

		virtual const Color&			GetTextColor_ReadOnly() const = 0;
		virtual const WidgetBorder&		GetOutline_ReadOnly() const = 0;
		virtual float					GetOutlineThickness_ReadOnly() const = 0;
		virtual const Color&			GetOutlineColor_ReadOnly() const = 0;
		virtual float					GetCharacterSpacingX_ReadOnly() const = 0;
		virtual float					GetCharacterSpacingY_ReadOnly() const = 0;
		virtual unsigned int			GetCharacterSize_ReadOnly() const = 0;
		virtual const String&			GetText_ReadOnly() const = 0;
		virtual const Font_t*			GetFont_ReadOnly() const = 0;
		virtual bool					GetBold_ReadOnly() const = 0;
		virtual bool					GetItalic_ReadOnly() const = 0;
		virtual bool					GetUnderLined_ReadOnly() const = 0;
		virtual bool					GetStrikeThrough_ReadOnly()const = 0;

		// === Getter ===

		virtual bool HasOutline() const = 0;
		
		// === Accessor ===

		virtual Color& TextColor() = 0;
		virtual WidgetBorder& Outline() = 0;
		virtual float& CharacterSpacingX() = 0;
		virtual float& CharacterSpacingY() = 0;
		virtual unsigned int& CharacterSize() = 0;
		virtual TMM::String& Text() = 0;
		virtual const Font_t*& Font() = 0;
		virtual bool& Bold() = 0;
		virtual bool& Italic() = 0;
		virtual bool& UnderLined() = 0;
		virtual bool& StrikeThrough() = 0;

		// === Setter ===

		virtual void SetNoOutline() = 0;
		virtual void PlaceTextRelativeAnchor(ANCHOR anchor, TMM::Vec2f offset) = 0;

	};

}