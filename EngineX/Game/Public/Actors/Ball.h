#pragma once
#include "Actor.h"
#include "Game/Public/GameCore/GameCore.h"
#include "Engine/Public/EngineTypes.h"

class Out;
class MyGame;

class Ball : public Actor
{

public:

	Ball() = delete;
	Ball(String ballName, exColor ballColor, exVector2 startingPos, exVector2 velocity);

	virtual void BeginPlay() override;

	void OnBallCollided(std::weak_ptr<Actor> HitActor, const exVector2& HitPosition);

private: 
	String mBallName;
	exColor mBallColor;
	exVector2 mBallStartingPosition;
	exVector2 mBallInitialVelocity;

};
