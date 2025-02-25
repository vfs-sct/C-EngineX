#pragma once
#include "Game/Public/GameCore/GameCore.h"
#include "Game/Public/Actors/Actor.h"

class Ball;
template <class StateDependencyObject>
class State
{

public:
	State()
	{
		mNextState = "";
	};
	State(String NextState)
	{
		mNextState = NextState;
	};

	virtual ~State() {} ;

	// State Methods
	virtual void Enter(std::shared_ptr<StateDependencyObject> DependencyObject) = 0;
	virtual void Update(std::shared_ptr<StateDependencyObject> DependencyObject) = 0;
	virtual void Exit(std::shared_ptr<StateDependencyObject> DependencyObject) = 0;

	void SetNextState(const String& Nextstate)
	{
		mNextState = Nextstate;
	};

	String GetNextState() const
	{
		return mNextState;
	};

private:

	String mNextState;
};

class MainMenu : public State<Actor>
{
public:
	MainMenu()
	{
		SetNextState("GamePlay");
	}

	virtual void Enter(std::shared_ptr<Actor> DependcyObject) override;

	virtual void Update(std::shared_ptr<Actor> DependcyObject) override;

	virtual void Exit(std::shared_ptr<Actor> DependcyObject) override;

private:
	std::shared_ptr<Actor> PlayButton;
	std::shared_ptr<Actor> QuitButton;
};


class GamePlay : public State<Actor>
{
public:
	GamePlay()
	{
		SetNextState("EndGame");
	}

	virtual void Enter(std::shared_ptr<Actor> DependcyObject) override;

	virtual void Update(std::shared_ptr<Actor> DependcyObject) override;

	virtual void Exit(std::shared_ptr<Actor> DependcyObject) override;

private:
	std::shared_ptr<Ball> Player;
};


class EndGame : public State<Actor>
{
public:
	EndGame()
	{
		SetNextState("MainMenu");
	}

	virtual void Enter(std::shared_ptr<Actor> DependcyObject) override;

	virtual void Update(std::shared_ptr<Actor> DependcyObject) override;

	virtual void Exit(std::shared_ptr<Actor> DependcyObject) override;

private:
	std::shared_ptr<Actor> RetryButton;
};