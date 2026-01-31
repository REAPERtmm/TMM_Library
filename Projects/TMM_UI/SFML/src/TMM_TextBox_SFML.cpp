#include "TMM_TextBox_SFML.h"

TMM::TextBoxSFML::TextBoxSFML(WidgetSFML* pParent, TextBoxSFMLDescriptor* pDesc) :
	CanvasSFML(pParent, pDesc),
	mStr(pDesc->Text),
	mTextAnchor(pDesc->TextAnchor),
	mTextOffset(pDesc->TextOffset),
	mTextColor(pDesc->TextColor),
	mTextOutline(pDesc->TextOutline),
	mBold(pDesc->Bold),
	mItalic(pDesc->Italic),
	mUnderlined(pDesc->Underlined),
	mStrikeThrough(pDesc->StrikeThrough),
	mCharacterSize(pDesc->CharacterSize),
	mCharacterSpacingX(pDesc->CharacterSpacingX),
	mCharacterSpacingY(pDesc->CharacterSpacingY),
	mpFont(pDesc->pFont),
	mpText(new sf::Text(*mpFont, mStr.data()))
{ }


void TMM::TextBoxSFML::UpdateRenderTargetSelf(sf::RectangleShape& brush)
{
	CanvasSFML::UpdateRenderTargetSelf(brush);

	mpText->setOrigin({ 0, 0 });
	mpText->setFillColor(TranslateColor(mTextColor));
	mpText->setStyle(
		(mBold ? sf::Text::Bold : 0) |
		(mItalic ? sf::Text::Italic : 0) |
		(mUnderlined ? sf::Text::Underlined : 0) |
		(mStrikeThrough ? sf::Text::StrikeThrough : 0)
	);
	mpText->setCharacterSize(mCharacterSize);
	mpText->setLetterSpacing(mCharacterSpacingX);
	mpText->setLineSpacing(mCharacterSpacingY);
	mpText->setString(mStr.data());
	if (HasBorder())
	{
		mpText->setOutlineThickness(mTextOutline.Thickness);
		mpText->setOutlineColor(TranslateColor(mTextOutline.Color));
	}
	else {
		mpText->setOutlineThickness(0);
	}
	mpText->setFont(*mpFont);

	TMM::Vec2f size = TranslateVec2f(mpText->getLocalBounds().size);
	sf::Vector2f final_position{
		ANCHOR_DISPLACEMENT[mTextAnchor].x * (GetSize_ReadOnly().x - size.x) + mTextOffset.x,
		ANCHOR_DISPLACEMENT[mTextAnchor].y * (GetSize_ReadOnly().y - size.y) + mTextOffset.y
	};
	mpText->setPosition(final_position);

	mpRenderTexture->draw(*mpText);
}

void TMM::TextBoxSFML::Destroy()
{
	CanvasSFML::Destroy();
	if (mpText != nullptr)
	{
		delete mpText;
		mpText = nullptr;
	}
}
