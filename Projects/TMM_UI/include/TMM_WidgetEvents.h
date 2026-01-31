#pragma once

#include <TMM_Setup.h>
#include <TMM_Callable.h>
#include <TMM_Vectors.h>
#include <TMM_UnorderedArray.h>

#include "TMM_WidgetEnums.h"

namespace TMM
{
	template<TMM_WidgetTemplateDefine>
	__interface Widget;

	template<TMM_WidgetTemplateDefine>
	class WidgetEvents
	{
	public:
		using OnHover		= TMM::Callable<void, TMM::Vec2f>;								// mouse_position
		using OnHoverStart	= TMM::Callable<void, TMM::Vec2f>;								// mouse_position
		using OnHoverEnd	= TMM::Callable<void, TMM::Vec2f>;								// mouse_position

		using OnClick		= TMM::Callable<void, TMM::MouseButton, TMM::Vec2f>;			// button, mouse_position
		using OnDrag		= TMM::Callable<void, TMM::MouseButton, TMM::Vec2f, TMM::Vec2f>;// button, mouse_position, delta
		using OnRelease		= TMM::Callable<void, TMM::MouseButton, TMM::Vec2f>;			// button, mouse_position

		using OnKeyPressed	= TMM::Callable<void, unsigned int>;							// key
		using OnKeyDown		= TMM::Callable<void, unsigned int>;							// key

		using OnUpdate		= TMM::Callable<void>;											// 

		using OnSelected	= TMM::Callable<void, Widget<Texture_t, Brush_t>*>;				// pSelected
		using OnUnselected	= TMM::Callable<void, Widget<Texture_t, Brush_t>*>;				// pUnselected
	private:
		TMM::ArrayUnordered<OnHover*>*		mpOnHover		;
		TMM::ArrayUnordered<OnHoverStart*>*	mpOnHoverStart	;
		TMM::ArrayUnordered<OnHoverEnd*>*	mpOnHoverEnd	;

		TMM::ArrayUnordered<OnClick*>*		mpOnClick		;
		TMM::ArrayUnordered<OnDrag*>*		mpOnDrag		;
		TMM::ArrayUnordered<OnRelease*>*	mpOnRelease		;

		TMM::ArrayUnordered<OnKeyPressed*>*	mpOnKeyPressed	;
		TMM::ArrayUnordered<OnKeyDown*>*	mpOnKeyDown		;

		TMM::ArrayUnordered<OnUpdate*>*		mpOnUpdate		;

		TMM::ArrayUnordered<OnSelected*>*	mpOnSelected	;
		TMM::ArrayUnordered<OnUnselected*>*	mpOnUnselected	;
	public:
		WidgetEvents() :
			mpOnHover(new TMM::ArrayUnordered<OnHover*>()),
			mpOnHoverStart(new TMM::ArrayUnordered<OnHoverStart*>()),
			mpOnHoverEnd(new TMM::ArrayUnordered<OnHoverEnd*>()),
			mpOnClick(new TMM::ArrayUnordered<OnClick*>()),
			mpOnDrag(new TMM::ArrayUnordered<OnDrag*>()),
			mpOnRelease(new TMM::ArrayUnordered<OnRelease*>()),
			mpOnKeyPressed(new TMM::ArrayUnordered<OnKeyPressed*>()),
			mpOnKeyDown(new TMM::ArrayUnordered<OnKeyDown*>()),
			mpOnUpdate(new TMM::ArrayUnordered<OnUpdate*>()),
			mpOnSelected(new TMM::ArrayUnordered<OnSelected*>()),
			mpOnUnselected(new TMM::ArrayUnordered<OnUnselected*>())
		{

		}
		virtual ~WidgetEvents() {
			TMM_ITER(i, mpOnHover->Size()) { delete mpOnHover->at(i); } 
			TMM_ITER(i, mpOnHoverStart->Size()) { delete mpOnHoverStart->at(i); }
			TMM_ITER(i, mpOnHoverEnd->Size()) { delete mpOnHoverEnd->at(i); }

			TMM_ITER(i, mpOnClick->Size()) { delete mpOnClick->at(i); }
			TMM_ITER(i, mpOnDrag->Size()) { delete mpOnDrag->at(i); }
			TMM_ITER(i, mpOnRelease->Size()) { delete mpOnRelease->at(i); }

			TMM_ITER(i, mpOnKeyPressed->Size()) { delete mpOnKeyPressed->at(i); }
			TMM_ITER(i, mpOnKeyDown->Size()) { delete mpOnKeyDown->at(i); }

			TMM_ITER(i, mpOnUpdate->Size()) { delete mpOnUpdate->at(i); }

			TMM_ITER(i, mpOnSelected->Size()) { delete mpOnSelected->at(i); }
			TMM_ITER(i, mpOnUnselected->Size()) { delete mpOnUnselected->at(i); }

			delete mpOnHover;
			delete mpOnHoverStart;
			delete mpOnHoverEnd;
			delete mpOnClick;
			delete mpOnDrag;
			delete mpOnRelease;
			delete mpOnKeyPressed;
			delete mpOnKeyDown;
			delete mpOnUpdate;
			delete mpOnSelected;
			delete mpOnUnselected;
		}

		void RegisterCallbackHover(OnHover* pCallback) { mpOnHover->Add(pCallback); }
		void RegisterCallbackHoverStart(OnHoverStart* pCallback) { mpOnHoverStart->Add(pCallback); }
		void RegisterCallbackHoverEnd(OnHoverEnd* pCallback) { mpOnHoverEnd->Add(pCallback); }

		void RegisterCallbackClick(OnClick* pCallback) { mpOnClick->Add(pCallback); }
		void RegisterCallbackDrag(OnDrag* pCallback) { mpOnDrag->Add(pCallback); }
		void RegisterCallbackRelease(OnRelease* pCallback) { mpOnRelease->Add(pCallback); }

		void RegisterCallbackKeyPressed(OnKeyPressed* pCallback) { mpOnKeyPressed->Add(pCallback); }
		void RegisterCallbackKeyDown(OnKeyDown* pCallback) { mpOnKeyDown->Add(pCallback); }

		void RegisterCallbackUpdate(OnUpdate* pCallback) { mpOnUpdate->Add(pCallback); }

		void RegisterCallbackSelected(OnSelected* pCallback) { mpOnSelected->Add(pCallback); }
		void RegisterCallbackUnselected(OnUnselected* pCallback) { mpOnUnselected->Add(pCallback); }

		void ProcCallbackHover(TMM::Vec2f mouse_position) {  
			TMM_ITER(i, mpOnHover->Size()) { mpOnHover->at(i)->Call(mouse_position); }
		}
		void ProcCallbackHoverStart(TMM::Vec2f mouse_position) {  
			TMM_ITER(i, mpOnHoverStart->Size()) { mpOnHoverStart->at(i)->Call(mouse_position); }
		}
		void ProcCallbackHoverEnd(TMM::Vec2f mouse_position) { 
			TMM_ITER(i, mpOnHoverEnd->Size()) { mpOnHoverEnd->at(i)->Call(mouse_position); }
		}

		void ProcCallbackClick(TMM::MouseButton button, TMM::Vec2f mouse_position) {  
			TMM_ITER(i, mpOnClick->Size()) { mpOnClick->at(i)->Call(button, mouse_position); }
		}
		void ProcCallbackDrag(TMM::MouseButton button, TMM::Vec2f mouse_position, TMM::Vec2f delta) {
			TMM_ITER(i, mpOnDrag->Size()) { mpOnDrag->at(i)->Call(button, mouse_position, delta); }
		}
		void ProcCallbackRelease(TMM::MouseButton button, TMM::Vec2f mouse_position) {
			TMM_ITER(i, mpOnRelease->Size()) { mpOnRelease->at(i)->Call(button, mouse_position); }
		}

		void ProcCallbackKeyPressed(unsigned int key) {
			TMM_ITER(i, mpOnKeyPressed->Size()) { mpOnKeyPressed->at(i)->Call(key); }
		}
		void ProcCallbackKeyDown(unsigned int key) {
			TMM_ITER(i, mpOnKeyDown->Size()) { mpOnKeyDown->at(i)->Call(key); }
		}

		void ProcCallbackUpdate() {
			TMM_ITER(i, mpOnUpdate->Size()) { mpOnUpdate->at(i)->Call(); }
		}

		void ProcCallbackSelected(Widget<TMM_WidgetTypenameDefine>* pWidget) {
			TMM_ITER(i, mpOnSelected->Size()) { mpOnSelected->at(i)->Call(pWidget); }
		}
		void ProcCallbackUnselected(Widget<TMM_WidgetTypenameDefine>* pWidget) {
			TMM_ITER(i, mpOnUnselected->Size()) { mpOnUnselected->at(i)->Call(pWidget); }
		}

	};

}