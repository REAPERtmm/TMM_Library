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
		brush.setFillColor(TranslateColor(GetBackgroundColor()));
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

	TMM::Vec2f CanvasSFML::GetScreenPosition() const
	{
		if (mpParent == nullptr) return GetPosition();
		return mpParent->GetScreenPosition() + GetPosition();
	}

	TMM::Vec2f CanvasSFML::ToLocalPosition(TMM::Vec2f screen_point) const
	{
		return screen_point - GetScreenPosition();
	}

	bool CanvasSFML::Contain(TMM::Vec2f point) const
	{
		return (
			point.x > GetPosition().x &&
			point.x < GetPosition().x + GetSize().x &&
			point.y > GetPosition().y &&
			point.y < GetPosition().y + GetSize().y
		);
	}

	void CanvasSFML::SetRelativeWidth(float ratio)
	{
		if (GetParent() == nullptr) return;

		SetSize(
			{
				GetParent()->GetSize().x * ratio,
				GetSize().y
			}
		);

		SetDirty();
	}

	void CanvasSFML::SetRelativeHeight(float ratio)
	{
		if (GetParent() == nullptr) return;

		SetSize(
			{
				GetSize().x,
				GetParent()->GetSize().y * ratio
			}
		);

		SetDirty();
	}

	void CanvasSFML::SetRelativePositionX(float ratio)
	{
		if (GetParent() == nullptr) return;

		SetPosition(
			{
				GetParent()->GetSize().x * ratio,
				GetPosition().y
			}
		);

		SetDirty();
	}

	void CanvasSFML::SetRelativePositionY(float ratio)
	{
		if (GetParent() == nullptr) return;

		SetPosition(
			{
				GetPosition().x,
				GetParent()->GetSize().y * ratio
			}
		);

		SetDirty();
	}

	void CanvasSFML::PlaceRelativeAnchor(ANCHOR anchor, TMM::Vec2f offset)
	{
		if (GetParent() == nullptr) {
			SetPosition(offset);
			return;
		}
		if (anchor == ANCHOR::NONE) anchor = ANCHOR::TOP_LEFT;

		// 0 => -1 | 0.5 => 0 | 1 => 1
		TMM::Vec2f s = {
			-2 * ANCHOR_DISPLACEMENT[anchor].x + 1,
			-2 * ANCHOR_DISPLACEMENT[anchor].y + 1,
		};

		SetPosition({
			ANCHOR_DISPLACEMENT[anchor].x * (GetParent()->GetSize().x - GetSize().x) + s.x * offset.x,
			ANCHOR_DISPLACEMENT[anchor].y * (GetParent()->GetSize().y - GetSize().y) + s.y * offset.y
		});
		
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
		brush.setPosition({ GetPosition().x, GetPosition().y });
		brush.setSize({ GetSize().x, GetSize().y });
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
		TMM::Vec2f size = { GetSize().x, GetSize().y };

		if (HasBorder())
		{
			mpRenderTexture->clear(TranslateColor(GetBorderColor()));
			position += { GetBorderThickness(), GetBorderThickness() };
			size -= { 2 * GetBorderThickness(), 2 * GetBorderThickness() };
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
			mpRenderTexture->clear(TranslateColor(GetBackgroundColor()));
		}
	}

	void CanvasSFML::UpdateRenderTargetChilds(sf::RectangleShape& brush)
	{
		TMM_ITER(i_child, mpChilds->Size())
		{
			GetChild(i_child)->UpdateRenderTarget(brush);

			brush.setTexture(&GetChild(i_child)->GetRenderTarget(), true);
			brush.setPosition({ GetChild(i_child)->GetPosition().x, GetChild(i_child)->GetPosition().y });
			brush.setSize({ GetChild(i_child)->GetSize().x, GetChild(i_child)->GetSize().y });
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
			brush.setPosition({ mpOverlay->GetPosition().x, mpOverlay->GetPosition().y });
			brush.setSize({ mpOverlay->GetSize().x, mpOverlay->GetSize().y });
			brush.setFillColor(sf::Color::White);
			brush.setScale({ 1, 1 });

			mpRenderTexture->draw(brush);
		}
	}

	void CanvasSFML::UpdateRenderTarget(sf::RectangleShape& brush)
	{
		if (mIsDirty == false) return;

		if (mLastSize.x != GetSize().x || mLastSize.y != GetSize().y)
		{
			mLastSize = GetSize();
			bool FAILED_RESIZE = mpRenderTexture->resize({ static_cast<uint32_t>(GetSize().x), static_cast<uint32_t>(GetSize().y) }) == false;
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

