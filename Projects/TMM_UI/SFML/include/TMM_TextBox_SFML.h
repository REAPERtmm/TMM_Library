#pragma once

#include <TMM_Setup.h>
#include "TMM_Widget.h"
#include "TMM_UI_Implement_SFML.h"
#include "TMM_Canvas_SFML.h"

namespace TMM
{

	struct TextBoxSFMLDescriptor : public CanvasSFMLDescriptor
	{
		const char* Text			= "";
		ANCHOR TextAnchor			= ANCHOR::CENTER_CENTER;
		TMM::Vec2f TextOffset		= { 0, 0 };
		TMM::Color TextColor		= TMM::CONSTANT::COLOR_BLACK;
		WidgetBorder TextOutline	= { -1.0f, TMM::CONSTANT::COLOR_RED };
		bool Bold					= false;
		bool Italic					= false;
		bool Underlined				= false;
		bool StrikeThrough			= false;
		unsigned int CharacterSize	= 12;
		float CharacterSpacingX		= 0.5f;
		float CharacterSpacingY		= 0.5f;
		const sf::Font* pFont		= nullptr;
	};

	class TextBoxSFML : public TMM::TextBox<sf::Font>, public TMM::CanvasSFML
	{
		TMM::String mStr;
		ANCHOR mTextAnchor;
		TMM::Vec2f mTextOffset;
		TMM::Color mTextColor;
		WidgetBorder mTextOutline;
		bool mBold;
		bool mItalic;
		bool mUnderlined;
		bool mStrikeThrough;
		unsigned int mCharacterSize;
		float mCharacterSpacingX;
		float mCharacterSpacingY;
		const sf::Font* mpFont;
		sf::Text* mpText;
	public:

		TextBoxSFML(WidgetSFML* pParent, TextBoxSFMLDescriptor* pDesc);

		// === ReadOnly ===

		virtual const Color& GetTextColor_ReadOnly() const override { return mTextColor; }
		virtual const WidgetBorder& GetOutline_ReadOnly() const override { return mTextOutline; }
		virtual float GetOutlineThickness_ReadOnly() const override { return mTextOutline.Thickness; }
		virtual const Color& GetOutlineColor_ReadOnly() const override { return mTextOutline.Color; }
		virtual float GetCharacterSpacingX_ReadOnly() const override { return mCharacterSpacingX; }
		virtual float GetCharacterSpacingY_ReadOnly() const override { return mCharacterSpacingY; }
		virtual unsigned int GetCharacterSize_ReadOnly() const override { return mCharacterSize; }
		virtual const String& GetText_ReadOnly() const override { return mStr; }
		virtual const sf::Font* GetFont_ReadOnly() const override { return mpFont; }
		virtual bool GetBold_ReadOnly() const override { return mBold; }
		virtual bool GetItalic_ReadOnly() const override { return mItalic; }
		virtual bool GetUnderLined_ReadOnly() const override { return mUnderlined; }
		virtual bool GetStrikeThrough_ReadOnly()const override { return mStrikeThrough; }

		// === Getter ===

		virtual bool HasOutline() const override { return mTextOutline.Thickness > 0.0f; }

		// === Accessor ===

		virtual Color& TextColor() override { SetDirty(); return mTextColor; }
		virtual WidgetBorder& Outline() override { SetDirty(); return mTextOutline; }
		virtual float& CharacterSpacingX() override { SetDirty(); return mCharacterSpacingX; }
		virtual float& CharacterSpacingY() override { SetDirty(); return mCharacterSpacingY; }
		virtual unsigned int& CharacterSize() override { SetDirty(); return mCharacterSize; }
		virtual TMM::String& Text() override { SetDirty(); return mStr; }
		virtual const sf::Font*& Font() override { SetDirty(); return mpFont; }
		virtual bool& Bold() override { SetDirty(); return mBold; }
		virtual bool& Italic() override { SetDirty(); return mItalic; }
		virtual bool& UnderLined() override { SetDirty(); return mUnderlined; }
		virtual bool& StrikeThrough() override { SetDirty(); return mStrikeThrough; }

		// === Setter ===

		virtual void SetNoOutline() override { mTextOutline.Thickness = -1.0f; SetDirty(); }
		virtual void PlaceTextRelativeAnchor(ANCHOR anchor, TMM::Vec2f offset) override { mTextAnchor = anchor; mTextOffset = offset; SetDirty(); }

		// === Override ===

		virtual void UpdateRenderTargetSelf(sf::RectangleShape& brush) override;
		virtual void Destroy() override;
	};
}