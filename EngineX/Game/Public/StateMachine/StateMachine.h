#pragma once
#include "Game/Public/GameCore/GameCore.h"
#include "Game/Public/StateMachine/State.h"
#include <Thread>
#include <Chrono>

template <class StateDependencyObject>
class StateMachine
{
public:
	void AddState(const String& StateName, std::shared_ptr<State<StateDependencyObject>> StateToAdd)
	{
		mStates[StateName] = StateToAdd;
	}

	void SetState(const String& NewState, std::shared_ptr<StateDependencyObject> DependencyObject)
	{
		if (mCurrentState)
		{
			mCurrentState->Exit(DependencyObject);
		}
		auto StateIterator = mStates.find(NewState);
		if (StateIterator != mStates.end())
		{
			mCurrentState = StateIterator->second;
			mCurrentState->Enter(DependencyObject);
		}
	}

	void Update(std::shared_ptr<StateDependencyObject> DependencyObject)
	{
		if (mCurrentState)
		{
			mCurrentState->Update(DependencyObject);
			std::this_thread::sleep_for(std::chrono::seconds(2));
			SetState(mCurrentState->GetNextState(), DependencyObject);
		}

	}

private:

	std::unordered_map<String, std::shared_ptr<State<StateDependencyObject>>> mStates;
	std::shared_ptr<State<StateDependencyObject>> mCurrentState;

};

