#pragma once
#include "Actor.h"
#include "Game/Public/GameCore/GameCore.h"
#include "Engine/Public/EngineTypes.h"

class Out : public Actor
{

public:

	Out() = delete;
	Out(String outName, exColor outColor, exVector2 startingPos, exVector2 velocity);

	virtual void BeginPlay() override;

	void OnOutCollided(std::weak_ptr<Actor> HitActor, const exVector2& HitPosition);

private:
	String mOutpName;
	exColor mOutColor;
	exVector2 mOutStartingPosition;
	exVector2 mOutInitialVelocity;

};
