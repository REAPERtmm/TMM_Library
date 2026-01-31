#pragma once

#include <TMM_Setup.h>
#include <TMM_OrderedArray.h>
#include "TMM_UI_Implement_SFML.h"


namespace TMM
{

	struct CanvasSFMLDescriptor
	{
		ANCHOR CanvasAnchor								= ANCHOR::TOP_LEFT;
		TMM::Vec2f CanvasOffset							= { 0, 0 };
		TMM::Vec2f CanvasSize							= { 1, 1 };
		WidgetBorder CanvasBorder						= { -1.0f, { 255, 255, 255, 255 } };
		Color CanvasBackgroundColor						= { 255, 255, 255, 255 };
		const sf::Texture* pCanvasBackgroundTexture		= nullptr;
		WidgetSFML* pCanvasOverlayRoot					= nullptr;
		bool CanvasOverlayVisibleByDefault				= false;
	};

#define WIDGET_CANVAS_SFML 1

	class CanvasSFML : public WidgetSFML
	{
		// Parent - Childs : 
		WidgetSFML* mpParent;
		TMM::ArrayOrdered<WidgetSFML*>* mpChilds;

		// Values :
		Rect2Df mRect;
		WidgetBorder mBorder;
		Color mBackgroundColor;
		const sf::Texture* mpBackgroundTexture;

		// Selection :
		WidgetSFML* mpCurrentSelected;

		// Overlay :
		WidgetSFML* mpOverlay;
		bool mOverlayVisible;

		// Events :
		WidgetEventsSFML* mpEvents;
		bool mHoveredLastFrame;

		// Optimization : 
		TMM::Vec2f mLastSize;
		bool mIsDirty;

		// Destruction :
		bool mIsDestroyed;

	protected:
		CanvasSFML(WidgetSFML* pParent, WidgetEventsSFML* pEvents, CanvasSFMLDescriptor* pDesc);
		sf::RenderTexture* mpRenderTexture;

		virtual void SetParent(WidgetSFML* pWidget) override final { mpParent = pWidget; }
		virtual void DrawBackgroundTexture(sf::RectangleShape& brush, TMM::Vec2f position, TMM::Vec2f size);
		virtual void DrawBackgroundColor(sf::RectangleShape& brush, TMM::Vec2f position, TMM::Vec2f size);

	public:
		CanvasSFML(WidgetSFML* pParent, CanvasSFMLDescriptor* pDesc);
		virtual ~CanvasSFML();

		// === ReadOnly ===

		virtual const TMM::Vec2f& GetPosition_ReadOnly() const override { return mRect.position; }
		virtual const TMM::Vec2f& GetSize_ReadOnly() const override { return mRect.size; }
		virtual const TMM::Rect2Df& GetRect_ReadOnly() const override { return mRect; }
		virtual const sf::Texture* GetBackgroundTexture_ReadOnly()	const override { return mpBackgroundTexture; }
		virtual const Color& GetBackgroundColor_ReadOnly() const override { return mBackgroundColor; }
		virtual const WidgetBorder& GetBorder_ReadOnly() const override { return mBorder; }
		virtual float GetBorderThickness_ReadOnly() const override { return (HasBorder() ? 0.0f : mBorder.Thickness); }
		virtual const Color& GetBorderColor_ReadOnly() const override { return mBorder.Color; }
		virtual TMM::Vec2f GetScreenPosition_ReadOnly() const override;

		// ===  Getter  ===

		virtual bool HasBorder() const override { return mBorder.Thickness > 0.0f; }
		virtual bool HasBackgroundTexture() const override { return mpBackgroundTexture != nullptr; };

		// === Accessor ===

		virtual TMM::Vec2f& Position() override { SetDirty(); return mRect.position; }
		virtual TMM::Vec2f& Size() override { SetDirty(); return mRect.position; }
		virtual const sf::Texture*& BackgroundTexture() override { SetDirty(); return mpBackgroundTexture; }
		virtual Color& BackgroundColor() override { SetDirty(); return mBackgroundColor; }
		virtual WidgetBorder& Border() override { SetDirty(); return mBorder; }

		// === Reset ===

		virtual void SetNoBorder() override { SetDirty(); mBorder.Thickness = -1.0f; }

		// === Transformation ===

		virtual TMM::Vec2f ToLocalPosition(TMM::Vec2f screen_point) const override;
		virtual bool Contain(TMM::Vec2f point) const override;

		// === Parent Relative Setter === 

		virtual void SetRelativeWidth(float ratio) override;
		virtual void SetRelativeHeight(float ratio) override;
		virtual void SetRelativePositionX(float ratio) override;
		virtual void SetRelativePositionY(float ratio) override;
		virtual void PlaceRelativeAnchor(ANCHOR anchor, TMM::Vec2f offset) override;

		// === Parent - childs ===


		virtual WidgetSFML* GetParent() override { return mpParent; }
		virtual unsigned int GetChildCount() const override { return mpChilds->Size(); }
		virtual WidgetSFML* AddChild(WidgetSFML* pChild) override { mpChilds->Add(pChild); return pChild; }
		virtual void RemoveChild(WidgetSFML* pChild) override { mpChilds->Remove(pChild); }
		virtual void RemoveChild(unsigned int index) override { mpChilds->RemoveAt(index); }
		virtual WidgetSFML* GetChild(unsigned int index) override { return mpChilds->at(index); }

		// === Render Target ===

		virtual const sf::Texture& GetRenderTarget() override;
		virtual void UpdateRenderTargetSelf(sf::RectangleShape& brush) override;
		virtual void UpdateRenderTargetChilds(sf::RectangleShape& brush) override;
		virtual void LateUpdateRenderTargetChilds(sf::RectangleShape& brush) override;
		virtual void LateUpdateRenderTargetSelf(sf::RectangleShape& brush) override;
		virtual void UpdateRenderTarget(sf::RectangleShape& brush) override;

		// === Selection ===

		virtual bool IsSelected() override;
		virtual void IsSelectedParentRecusive(TMM::Stack<bool>* pOut) override;
		virtual WidgetSFML* ChildSelected() override;

		virtual void Select() override;
		virtual void SetNoSelected() override;
		virtual void SetChildSelected(unsigned int i) override;
		virtual void SetChildSelected(WidgetSFML* pChild) override;

		// === Type Test ===

		virtual long long GetType() override { return WIDGET_CANVAS_SFML; }

		// === Update ===

		virtual void Update(WidgetUpdateCtx ctx) override;

		// === Overlay ===

		virtual bool GetOverlayVisibility_ReadOnly() const override { return mOverlayVisible; };
		virtual bool& OverlayVisibility() override { SetDirty(); return mOverlayVisible; };
		virtual void ToggleOverlayVisibility() override { SetDirty(); mOverlayVisible = !mOverlayVisible; };
		virtual void SetOverlay(Widget* pRoot) override;
		virtual Widget* GetOverlay() override { return mpOverlay; }

		// === Events === 

		virtual WidgetEventsSFML* GetEvents() override { return mpEvents; }
		virtual void OnSendMessage(WidgetSFML* pDest, void* pData, unsigned int dataByteSize) override;
		virtual void OnMessageReceived(WidgetSFML* pSrc, void* pData, unsigned int dataByteSize) override;

		// === Optimization ===

		virtual void SetDirty() override { mIsDirty = true; if (GetParent() != nullptr) GetParent()->SetDirty(); }
		virtual bool IsDirty() override { return mIsDirty; }
	
		// === Destruction ===
		
		virtual void Destroy() override;

		// === CanvasSFML ===
		
		virtual void Draw(sf::RenderWindow* pWin, sf::RectangleShape& brush);
	};

}
