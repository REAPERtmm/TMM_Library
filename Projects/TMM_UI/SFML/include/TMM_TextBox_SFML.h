#pragma once

#include <TMM_Setup.h>
#include "TMM_Widget.h"
#include "TMM_UI_Implement_SFML.h"
#include "TMM_Canvas_SFML.h"

#include <istream>;

namespace TMM
{

	struct TextBoxSFMLDescriptor : public CanvasSFMLDescriptor
	{
		std::string Text					= "";
		ANCHOR TextAnchor					= ANCHOR::CENTER_CENTER;
		TMM::Vec2f TextOffset				= { 0, 0 };
		TMM::Color TextColor				= TMM::CONSTANT::COLOR_BLACK;
		WidgetBorder TextOutline			= { -1.0f, TMM::CONSTANT::COLOR_RED };
		bool Bold							= false;
		bool Italic							= false;
		bool Underlined						= false;
		bool StrikeThrough					= false;
		unsigned int CharacterSize			= 12;
		unsigned int MaxCharacterByLine		= 0;
		float CharacterSpacingX				= 0.5f;
		float CharacterSpacingY				= 0.5f;
		const sf::Font* pFont				= nullptr;
	};

	class TextBoxSFML : public TMM::TextBox<sf::Font>, public TMM::CanvasSFML
	{
		std::string mStr;
		ANCHOR mTextAnchor;
		TMM::Vec2f mTextOffset;
		TMM::Color mTextColor;
		WidgetBorder mTextOutline;
		bool mBold;
		bool mItalic;
		bool mUnderlined;
		bool mStrikeThrough;
		unsigned int mCharacterSize;
		unsigned int mMaxCharacterByLine;
		float mCharacterSpacingX;
		float mCharacterSpacingY;
		const sf::Font* mpFont;
		sf::Text* mpText;

	public:

		TextBoxSFML(WidgetSFML* pParent, TextBoxSFMLDescriptor* pDesc);

		// === ReadOnly ===

		virtual const Color& GetTextColor() const override { return mTextColor; }
		virtual const WidgetBorder& GetOutline() const override { return mTextOutline; }
		virtual float GetOutlineThickness() const override { return mTextOutline.Thickness; }
		virtual const Color& GetOutlineColor() const override { return mTextOutline.Color; }
		virtual float GetCharacterSpacingX() const override { return mCharacterSpacingX; }
		virtual float GetCharacterSpacingY() const override { return mCharacterSpacingY; }
		virtual unsigned int GetCharacterSize() const override { return mCharacterSize; }
		virtual unsigned int GetMaxCharacterByLine() const override { return mMaxCharacterByLine; }
		virtual const std::string& GetText() const override { return mStr; }
		virtual const sf::Font* GetFont() const override { return mpFont; }
		virtual bool GetBold() const override { return mBold; }
		virtual bool GetItalic() const override { return mItalic; }
		virtual bool GetUnderLined() const override { return mUnderlined; }
		virtual bool GetStrikeThrough()const override { return mStrikeThrough; }

		// === Getter ===

		virtual bool HasOutline() const override { return mTextOutline.Thickness > 0.0f; }

		// === Accessor ===

		virtual void SetTextColor(const Color& color) override { SetDirty(); mTextColor = color; }
		virtual void SetOutline(const WidgetBorder& border) override { SetDirty(); mTextOutline = border; }
		virtual void SetCharacterSpacingX(float x) override { SetDirty(); mCharacterSpacingX = x; }
		virtual void SetCharacterSpacingY(float y) override { SetDirty(); mCharacterSpacingY = y; }
		virtual void SetCharacterSize(unsigned int size) override { SetDirty(); mCharacterSize = size; }
		virtual void SetMaxCharacterByLine(unsigned int count) override { SetDirty(); mMaxCharacterByLine = count; }
		virtual void SetText(const std::string& txt) override;
		virtual void SetFont(const sf::Font* pFont) override { SetDirty(); mpFont = pFont; }
		virtual void SetBold(bool active) override { SetDirty(); mBold = active; }
		virtual void SetItalic(bool active) override { SetDirty(); mItalic = active; }
		virtual void SetUnderLined(bool active) override { SetDirty(); mUnderlined = active; }
		virtual void SetStrikeThrough(bool active) override { SetDirty(); mStrikeThrough = active; }

		// === Setter ===

		virtual void SetNoOutline() override { mTextOutline.Thickness = -1.0f; SetDirty(); }
		virtual void PlaceTextRelativeAnchor(ANCHOR anchor, TMM::Vec2f offset) override { mTextAnchor = anchor; mTextOffset = offset; SetDirty(); }

		// === Override ===

		virtual void UpdateRenderTargetSelf(sf::RectangleShape& brush) override;
		virtual void Destroy() override;
	};
}