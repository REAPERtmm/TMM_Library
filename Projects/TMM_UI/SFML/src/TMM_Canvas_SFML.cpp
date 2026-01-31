#include "TMM_Canvas_SFML.h"

namespace TMM
{
	CanvasSFML::CanvasSFML(WidgetSFML* pParent, WidgetEventsSFML* pEvents, CanvasSFMLDescriptor* pDesc) :
		mpParent(nullptr),
		mpChilds(new TMM::ArrayOrdered<WidgetSFML*>()),
		mRect({ 0, 0 }, pDesc->CanvasSize),
		mBorder(pDesc->CanvasBorder),
		mBackgroundColor(pDesc->CanvasBackgroundColor),
		mpBackgroundTexture(pDesc->pCanvasBackgroundTexture),
		mOverlayVisible(pDesc->CanvasOverlayVisibleByDefault),
		mpEvents(pEvents),
		mHoveredLastFrame(false),
		mpRenderTexture(new sf::RenderTexture({ static_cast<unsigned int>(pDesc->CanvasSize.x), static_cast<unsigned int>(pDesc->CanvasSize.y) })),
		mIsDirty(true),
		mLastSize(pDesc->CanvasSize),
		mIsDestroyed(false)
	{
		SetParent(pParent);
		SetOverlay(pDesc->pCanvasOverlayRoot);
		PlaceRelativeAnchor(pDesc->CanvasAnchor, pDesc->CanvasOffset);
	}

	void CanvasSFML::DrawBackgroundTexture(sf::RectangleShape& brush, TMM::Vec2f position, TMM::Vec2f size)
	{
		brush.setTexture(mpBackgroundTexture, true);
		brush.setPosition(TranslateVec2f(position));
		brush.setSize(TranslateVec2f(size));
		brush.setFillColor(sf::Color::White);
		brush.setScale({ 1, 1 });
		mpRenderTexture->draw(brush);
	}

	void CanvasSFML::DrawBackgroundColor(sf::RectangleShape& brush, TMM::Vec2f position, TMM::Vec2f size)
	{
		brush.setTexture(nullptr);
		brush.setPosition(TranslateVec2f(position));
		brush.setSize(TranslateVec2f(size));
		brush.setFillColor(TranslateColor(GetBackgroundColor_ReadOnly()));
		brush.setScale({ 1, 1 });
		mpRenderTexture->draw(brush);
	}

	CanvasSFML::CanvasSFML(WidgetSFML* pParent, CanvasSFMLDescriptor* pDesc) :
		CanvasSFML(pParent, new WidgetEventsSFML(), pDesc)
	{ }

	CanvasSFML::~CanvasSFML()
	{
		if (mIsDestroyed == false) Destroy();
	}

	TMM::Vec2f CanvasSFML::GetScreenPosition_ReadOnly() const
	{
		if (mpParent == nullptr) return GetPosition_ReadOnly();
		return mpParent->GetScreenPosition_ReadOnly() + GetPosition_ReadOnly();
	}

	TMM::Vec2f CanvasSFML::ToLocalPosition(TMM::Vec2f screen_point) const
	{
		return screen_point - GetScreenPosition_ReadOnly();
	}

	bool CanvasSFML::Contain(TMM::Vec2f point) const
	{
		return (
			point.x > GetPosition_ReadOnly().x &&
			point.x < GetPosition_ReadOnly().x + GetSize_ReadOnly().x &&
			point.y > GetPosition_ReadOnly().y &&
			point.y < GetPosition_ReadOnly().y + GetSize_ReadOnly().y
		);
	}

	void CanvasSFML::SetRelativeWidth(float ratio)
	{
		if (GetParent() == nullptr) return;

		Size().x = GetParent()->GetSize_ReadOnly().x * ratio;

		SetDirty();
	}

	void CanvasSFML::SetRelativeHeight(float ratio)
	{
		if (GetParent() == nullptr) return;

		Size().y = GetParent()->GetSize_ReadOnly().y * ratio;

		SetDirty();
	}

	void CanvasSFML::SetRelativePositionX(float ratio)
	{
		if (GetParent() == nullptr) return;

		Position().x = GetParent()->GetSize_ReadOnly().x * ratio;

		SetDirty();
	}

	void CanvasSFML::SetRelativePositionY(float ratio)
	{
		if (GetParent() == nullptr) return;

		Position().y = GetParent()->GetSize_ReadOnly().y * ratio;

		SetDirty();
	}

	void CanvasSFML::PlaceRelativeAnchor(ANCHOR anchor, TMM::Vec2f offset)
	{
		if (GetParent() == nullptr) {
			Position() = offset;
			return;
		}
		if (anchor == ANCHOR::NONE) anchor = ANCHOR::TOP_LEFT;

		// 0 => -1 | 0.5 => 0 | 1 => 1
		TMM::Vec2f s = {
			-2 * ANCHOR_DISPLACEMENT[anchor].x + 1,
			-2 * ANCHOR_DISPLACEMENT[anchor].y + 1,
		};

		Position() = {
			ANCHOR_DISPLACEMENT[anchor].x * (GetParent()->GetSize_ReadOnly().x - GetSize_ReadOnly().x) + s.x * offset.x,
			ANCHOR_DISPLACEMENT[anchor].y * (GetParent()->GetSize_ReadOnly().y - GetSize_ReadOnly().y) + s.y * offset.y
		};
		
		SetDirty();
	}


	void CanvasSFML::Update(WidgetUpdateCtx ctx)
	{
		ctx.PreCalcInRect = (ctx.PreCalcInRect ? Contain(ctx.mousePos) : false);

		mpEvents->ProcCallbackUpdate();
		if (mHoveredLastFrame && ctx.PreCalcInRect == false)
		{
			mpEvents->ProcCallbackHoverEnd(ctx.mousePos);
		}
		if (ctx.PreCalcInRect)
		{
			if (mHoveredLastFrame == false)
			{
				mpEvents->ProcCallbackHoverStart(ctx.mousePos);
			}
			mpEvents->ProcCallbackHover(ctx.mousePos);

			TMM_ITER(i_button, 3)
			{
				if (ctx.mouseClicked[i_button])
				{
					mpEvents->ProcCallbackClick((TMM::MouseButton)i_button, ctx.mousePos);
				}
				if (ctx.mouseDown[i_button])
				{
					mpEvents->ProcCallbackDrag((TMM::MouseButton)i_button, ctx.mousePos, ctx.mouseDelta);
				}
			}
		}

		TMM_ITER(i_key, 101)
		{
			if (ctx.KeyPressed[i_key]) mpEvents->ProcCallbackKeyPressed(i_key);
			if (ctx.KeyDown[i_key]) mpEvents->ProcCallbackKeyDown(i_key);
		}

		mHoveredLastFrame = ctx.PreCalcInRect;
		TMM_ITER(i_child, mpChilds->Size())
		{
			GetChild(i_child)->Update(ctx);
		}

		if (mpOverlay != nullptr) {
			mpOverlay->Update(ctx);
		}
	}

	void CanvasSFML::SetOverlay(Widget* pRoot)
	{
		SetDirty(); 
		mpOverlay = pRoot; 
		if(mpOverlay != nullptr)
			mpOverlay->SetParent(this);
	};

	void CanvasSFML::OnSendMessage(WidgetSFML* pDest, void* pData, unsigned int dataByteSize)
	{
		pDest->OnMessageReceived(this, pData, dataByteSize);
	}

	void CanvasSFML::OnMessageReceived(WidgetSFML* pSrc, void* pData, unsigned int dataByteSize)
	{
		// No Interaction
	}

	void CanvasSFML::Destroy()
	{
		if (mIsDestroyed) return;
		delete mpEvents;
		delete mpRenderTexture;
		if (mpOverlay != nullptr) {
			TMM::CanvasSFML* pOverlay = (TMM::CanvasSFML*)mpOverlay;
			pOverlay->Destroy();
			delete pOverlay;
		}
		TMM_ITER(i, mpChilds->Size())
		{
	
			TMM::CanvasSFML* pChild = (TMM::CanvasSFML*)mpChilds->at(i);
			pChild->Destroy();
			delete pChild;

		}
		delete mpChilds;
		mIsDestroyed = true;
	}

	void CanvasSFML::Draw(sf::RenderWindow* pWin, sf::RectangleShape& brush)
	{
		UpdateRenderTarget(brush);

		brush.setTexture(&GetRenderTarget(), true);
		brush.setPosition({ GetPosition_ReadOnly().x, GetPosition_ReadOnly().y });
		brush.setSize({ GetSize_ReadOnly().x, GetSize_ReadOnly().y });
		brush.setFillColor(sf::Color::White);
		brush.setScale({ 1, 1 });

		pWin->draw(brush);
	}

	const sf::Texture& CanvasSFML::GetRenderTarget()
	{
		return mpRenderTexture->getTexture();
	}

	void CanvasSFML::UpdateRenderTargetSelf(sf::RectangleShape& brush)
	{
		TMM::Vec2f position = { 0, 0 };
		TMM::Vec2f size = { GetSize_ReadOnly().x, GetSize_ReadOnly().y };

		if (HasBorder())
		{
			mpRenderTexture->clear(TranslateColor(GetBorderColor_ReadOnly()));
			position += { GetBorderThickness_ReadOnly(), GetBorderThickness_ReadOnly() };
			size -= { 2 * GetBorderThickness_ReadOnly(), 2 * GetBorderThickness_ReadOnly() };
			if (HasBackgroundTexture()) // BORDER - TEXTURE
			{
				DrawBackgroundTexture(
					brush,
					position,
					size
				);
			}
			else // BORDER - NO TEXTURE
			{
				DrawBackgroundColor(
					brush,
					position,
					size
				);
			}
		}
		else if (HasBackgroundTexture()) // NO BORDER - TEXTURE
		{
			DrawBackgroundTexture(
				brush,
				position,
				size
			);
		}
		else // NO BORDER - NO TEXTURE
		{
			mpRenderTexture->clear(TranslateColor(GetBackgroundColor_ReadOnly()));
		}
	}

	void CanvasSFML::UpdateRenderTargetChilds(sf::RectangleShape& brush)
	{
		TMM_ITER(i_child, mpChilds->Size())
		{
			GetChild(i_child)->UpdateRenderTarget(brush);

			brush.setTexture(&GetChild(i_child)->GetRenderTarget(), true);
			brush.setPosition({ GetChild(i_child)->GetPosition_ReadOnly().x, GetChild(i_child)->GetPosition_ReadOnly().y });
			brush.setSize({ GetChild(i_child)->GetSize_ReadOnly().x, GetChild(i_child)->GetSize_ReadOnly().y });
			brush.setFillColor(sf::Color::White);
			brush.setScale({ 1, 1 });

			mpRenderTexture->draw(brush);
		}
	}

	void CanvasSFML::LateUpdateRenderTargetChilds(sf::RectangleShape& brush)
	{

	}

	void CanvasSFML::LateUpdateRenderTargetSelf(sf::RectangleShape& brush)
	{
		if (mOverlayVisible)
		{
			mpOverlay->UpdateRenderTarget(brush);

			brush.setTexture(&mpOverlay->GetRenderTarget(), true);
			brush.setPosition({ mpOverlay->GetPosition_ReadOnly().x, mpOverlay->GetPosition_ReadOnly().y });
			brush.setSize({ mpOverlay->GetSize_ReadOnly().x, mpOverlay->GetSize_ReadOnly().y });
			brush.setFillColor(sf::Color::White);
			brush.setScale({ 1, 1 });

			mpRenderTexture->draw(brush);
		}
	}

	void CanvasSFML::UpdateRenderTarget(sf::RectangleShape& brush)
	{
		if (mIsDirty == false) return;

		if (mLastSize.x != GetSize_ReadOnly().x || mLastSize.y != GetSize_ReadOnly().y)
		{
			mLastSize = GetSize_ReadOnly();
			bool FAILED_RESIZE = mpRenderTexture->resize({ static_cast<uint32_t>(GetSize_ReadOnly().x), static_cast<uint32_t>(GetSize_ReadOnly().y) }) == false;
			if (FAILED_RESIZE) {
				return;
			}
		}

		UpdateRenderTargetSelf(brush);
		UpdateRenderTargetChilds(brush);
		LateUpdateRenderTargetChilds(brush);
		LateUpdateRenderTargetSelf(brush);

		mpRenderTexture->display();
		mIsDirty = false;
	}

	bool CanvasSFML::IsSelected()
	{
		if (GetParent() == nullptr) return false;
		else return GetParent()->ChildSelected() == this;
	}

	void CanvasSFML::IsSelectedParentRecusive(TMM::Stack<bool>* pOut)
	{
		if (GetParent() == nullptr) return;
		pOut->PushStack(IsSelected());
		GetParent()->IsSelectedParentRecusive(pOut);
	}

	WidgetSFML* CanvasSFML::ChildSelected()
	{
		return mpCurrentSelected;
	}

	void CanvasSFML::Select()
	{
		if (GetParent() == nullptr) return;
		GetParent()->SetChildSelected(this);
	}

	void CanvasSFML::SetNoSelected()
	{
		mpCurrentSelected = nullptr;
	}

	void CanvasSFML::SetChildSelected(unsigned int i)
	{
		mpCurrentSelected = GetChild(i);
	}

	void CanvasSFML::SetChildSelected(WidgetSFML* pChild)
	{
		TMM_ITER(i, mpChilds->Size())
		{
			if (mpChilds->at(i) == pChild) {
				mpCurrentSelected = pChild;
				return;
			}
		}
	}

}

