#pragma once

#include <TMM_Setup.h>
#include <TMM_Stack.h>

#include "TMM_WidgetEnums.h"
#include "TMM_WidgetEvents.h"


namespace TMM
{
	/// \/ = (0, 0) worldposition(wp)
	///  _____________________________
	/// / \/ (1, 0)wp                 \
	/// |  ____________________       |
	/// | /                    \      |
	/// | |                    |      |
	/// | |(5, 5)wp,(4, 5)local|      |
	/// | |     \/             |      |
	/// | |      ___________   |      |
	/// | |		/ (0, 0)local  |      |
	/// | |     |           |  |      |
	/// | |		\___________/  |      |
	/// | |                    |      |
	/// | \____________________/      |
	/// |                             |
	/// |                             |
	/// \____________________________/

	template <TMM_WidgetTemplateDefine>
	__interface Widget {

		// === ReadOnly ===

		virtual const TMM::Vec2f&		GetPosition() const				= 0;
		virtual const TMM::Vec2f&		GetSize() const					= 0;
		virtual const TMM::Rect2Df&		GetRect() const					= 0;
		virtual const Texture_t*		GetBackgroundTexture()	const	= 0;
		virtual const Color&			GetBackgroundColor() const		= 0;
		virtual const WidgetBorder&		GetBorder() const				= 0;
		virtual float					GetBorderThickness() const		= 0;
		virtual const Color&			GetBorderColor() const			= 0;
		virtual TMM::Vec2f				GetScreenPosition() const		= 0;

		// ===  Getter  ===

		virtual bool HasBorder() const = 0;
		virtual bool HasBackgroundTexture() const = 0;

		// === Accessor ===
		
		virtual void	SetPosition(const TMM::Vec2f& pos)			= 0;
		virtual void	SetSize(const TMM::Vec2f& size)				= 0;
		virtual void	SetBackgroundTexture(const Texture_t* pTex)	= 0;
		virtual void	SetBackgroundColor(const Color& color)		= 0;
		virtual void	SetBorder(const WidgetBorder& border)		= 0;

		// === Reset ===

		virtual void SetNoBorder() = 0;

		// === Transformation ===

		virtual TMM::Vec2f ToLocalPosition(TMM::Vec2f screen_point) const = 0;
		virtual bool Contain(TMM::Vec2f point) const	= 0;

		// === Parent Relative Setter === 

		virtual void SetRelativeWidth(float ratio)														= 0;
		virtual void SetRelativeHeight(float ratio)														= 0;
		virtual void SetRelativePositionX(float ratio)													= 0;
		virtual void SetRelativePositionY(float ratio)													= 0;
		virtual void PlaceRelativeAnchor(ANCHOR anchor, TMM::Vec2f offset)								= 0;


		// === Parent - childs ===

		virtual void			SetParent(Widget* pWidget)			= 0;
		virtual Widget*			GetParent()							= 0;
		virtual unsigned int	GetChildCount()	const				= 0;
		virtual Widget*			AddChild(Widget* pChild)			= 0;
		virtual void			RemoveChild(Widget* pChild)			= 0;
		virtual void			RemoveChild(unsigned int index)		= 0;
		virtual Widget*			GetChild(unsigned int index)		= 0;

		// === Render Target ===

		virtual const Texture_t& GetRenderTarget()					= 0;
		virtual void UpdateRenderTargetSelf(Brush_t& brush)			= 0;
		virtual void UpdateRenderTargetChilds(Brush_t& brush)		= 0;
		virtual void LateUpdateRenderTargetChilds(Brush_t& brush)	= 0;
		virtual void LateUpdateRenderTargetSelf(Brush_t& brush)		= 0;
		virtual void UpdateRenderTarget(Brush_t& brush)				= 0;
		
		// === Selection ===

		virtual bool	IsSelected()										= 0;
		virtual void	IsSelectedParentRecusive(TMM::Stack<bool>* pOut)	= 0;
		virtual Widget* ChildSelected()										= 0;

		virtual void Select()							= 0;
		virtual void SetNoSelected()					= 0;
		virtual void SetChildSelected(unsigned int i)	= 0;
		virtual void SetChildSelected(Widget* pChild)	= 0;

		// === Type Test ===

		virtual long long GetType() = 0;

		// === Update ===

		virtual void Update(WidgetUpdateCtx ctx) = 0;

		// === Overlay ===
		
		virtual bool GetOverlayVisibility() const = 0;
		virtual bool& OverlayVisibility() = 0;
		virtual void ToggleOverlayVisibility() = 0;
		virtual void SetOverlay(Widget* pRoot) = 0;
		virtual Widget* GetOverlay() = 0;

		// === Events === 

		virtual WidgetEvents<Texture_t, Brush_t>* GetEvents() = 0;
		virtual void			OnSendMessage(Widget* pDest, void* pData, unsigned int dataByteSize)	= 0;
		virtual void			OnMessageReceived(Widget* pSrc, void* pData, unsigned int dataByteSize)	= 0;

		// === Optimization ===

		virtual void SetDirty() = 0;
		virtual bool IsDirty() = 0;

		// === Destruction ===

		virtual void Destroy() = 0;

	};

	template<typename Root_t, typename... Args>
	Root_t* CreateRootWidget(Args&&... args)
	{
		return new Root_t(nullptr, std::forward<Args>(args)...);
	}

	template<typename Child_t, TMM_WidgetTemplateDefine, typename... Args>
		requires(TMM::IsBaseOf<Widget<TMM_WidgetTypenameDefine>, Child_t>)
	Child_t* AddChildToWidget(Widget<TMM_WidgetTypenameDefine>* parent, Args&&... args)
	{
		return (Child_t*)parent->AddChild(new Child_t(parent, std::forward<Args>(args)...));
	}

}
