#pragma once

#include <TMM_Setup.h>
#include <TMM_OrderedArray.h>
#include <TMM_LinkedList.h>

namespace TMM
{
	template<typename T>
	class StateMachine;

	template<typename T>
	class State;

	template<typename T>
	class Transition;

	template<typename T>
	__interface Condition;

	template<typename T>
	__interface Action;


	struct STATE_MACHINE_DESCRIPTOR
	{
		void* pObj;
		unsigned int MAX_DEPTH = 2;
		unsigned int DEFAULT_STATE = 0;
		unsigned int BASE_STATE_COUNT = 1;
	};

	template<typename T>
	class StateMachine
	{
		T* mpObj;
		ArrayOrdered<State<T>*> mpStates;
		unsigned int mCurrentState = 0;
		const unsigned int mMaxDepth = 2;

		friend class State<T>;

		void InternalUpdate(void* pData, unsigned int depth = 0)
		{
			unsigned int NextState = mpStates[mCurrentState]->Update(mpObj, pData);
			if (NextState == -1) return;
			mpStates[mCurrentState]->End(mpObj, pData);
			mCurrentState = NextState;
			mpStates[mCurrentState]->Start(mpObj, pData);
			if (depth < mMaxDepth)
				InternalUpdate(pData, depth + 1);
		}
	public:
		StateMachine(STATE_MACHINE_DESCRIPTOR& desc) :
			mpObj((T*)desc.pObj),
			mCurrentState(desc.DEFAULT_STATE),
			mMaxDepth(desc.MAX_DEPTH)
		{
			TMM_ITER(_, desc.BASE_STATE_COUNT) {
				mpStates.Add(new TMM::State<T>());
			}
		}
		virtual ~StateMachine() {
			TMM_ITER(i, mpStates.Size())
			{
				delete mpStates[i];
			}
		}

		T* GetObj() { return mpObj; }

		void Update(void* pData) 
		{
			InternalUpdate(pData, 0);
		}

		State<T>* GetCurrentState() { return mpStates[mCurrentState]; }
		State<T>* GetState(unsigned int i) { return mpStates[i]; }
	};

	template<typename T>
	class State
	{
		ArrayOrdered<Transition<T>*> mpTransitions;
		ArrayOrdered<Action<T>*> mpActions;

		friend class StateMachine<T>;
		friend class Transition<T>;

		State() {}

		void Start(T* pObj, void* pData)
		{
			TMM_ITER(i, mpActions.Size())
			{
				mpActions[i]->Start(pObj, pData);
			}
		}

		unsigned int Update(T* pObj, void* pData)
		{
			TMM_ITER(i, mpTransitions.Size())
			{
				if (mpTransitions[i]->Check(pObj, pData))
				{
					return mpTransitions[i]->mTargetedState;
				}
			}
			TMM_ITER(i, mpActions.Size())
			{
				mpActions[i]->Update(pObj, pData);
			}
			return -1;
		}

		void End(T* pObj, void* pData)
		{
			TMM_ITER(i, mpActions.Size())
			{
				mpActions[i]->End(pObj, pData);
			}
		}

	public:
		virtual ~State()
		{
			TMM_ITER(i, mpActions.Size())
			{
				delete mpActions[i];
			}
			TMM_ITER(i, mpTransitions.Size())
			{
				delete mpTransitions[i];
			}
		}

		Transition<T>* CreateTransition(unsigned int target_state) 
		{
			mpTransitions.Add(new TMM::Transition<T>(target_state));
			return mpTransitions[mpTransitions.Size() - 1];
		}

		template<typename ACTION, typename... Args> requires TMM::IsBaseOf<TMM::Action<T>, ACTION>
		ACTION* AddAction(Args ...args) {
			mpActions.Add(new ACTION(TMM::forward<Args>(args)...));
			return reinterpret_cast<ACTION*>(mpActions[mpActions.Size() - 1]);
		}
	};

	template<typename T>
	class Transition
	{
		ArrayOrdered<Condition<T>*> mpConditions;
		unsigned int mTargetedState;

		friend class State<T>;

		Transition(unsigned int target) : mTargetedState(target) { }

		bool Check(T* pObj, void* pData)
		{
			TMM_ITER(i, mpConditions.Size())
			{
				if (mpConditions[i]->Check(pObj, pData) != mpConditions[i]->GetExpected()) return false;
			}
			return true;
		}
	public:
		virtual ~Transition()
		{
			TMM_ITER(i, mpConditions.Size())
			{
				delete mpConditions[i];
			}
		}

		template<typename CONDITION, typename... Args> requires TMM::IsBaseOf<TMM::Condition<T>, CONDITION>
		CONDITION* AddCondition(Args ...args) {
			mpConditions.Add(new CONDITION(TMM::forward<Args>(args)...));
			return reinterpret_cast<CONDITION*>(mpConditions[mpConditions.Size() - 1]);
		}
	};

	template<typename T>
	__interface Action
	{
		virtual void Start(T* pObj, void* pData)	PURE;
		virtual void Update(T* pObj, void* pData)	PURE;
		virtual void End(T* pObj, void* pData)		PURE;
	};

	template<typename T>
	__interface Condition
	{
		// Define if the output should be true or false
		virtual bool GetExpected() PURE;
		virtual bool Check(T* pObj, void* pData) PURE;
	};
}