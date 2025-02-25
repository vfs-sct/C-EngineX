#include "Game/Public/Actors/Ball.h"

Ball::Ball(String shipName, exColor shipColor, exVector2 startingPos, exVector2 velocity) :
	mBallName(shipName),
	mBallColor(shipColor),
	mBallStartingPosition(startingPos),
	mBallInitialVelocity(velocity)
{

}

void Ball::BeginPlay()
{
	AddComponentOfType<TransformComponent>(mBallStartingPosition);
	AddComponentOfType<CircleRenderComponent>(20.0f, mBallColor, exVector2(0, 0));
	std::tuple<std::shared_ptr<CircleColliderComponent>, bool, String> Result = AddComponentOfType<CircleColliderComponent>(20.0f, mBallInitialVelocity);
	std::shared_ptr<CircleColliderComponent> ColliderComp = std::get<0>(Result);
	if (ColliderComp)
	{
		CollisionEventSignature delegate = std::bind(&Ball::OnBallCollided, this, std::placeholders::_1, std::placeholders::_2);
		ColliderComp->ListenForCollision(delegate);
	}
}

void Ball::OnBallCollided(std::weak_ptr<Actor> HitActor, const exVector2& HitPosition)
{
	if (std::shared_ptr<CircleRenderComponent> CircleRenderComp = FindComponentOfType<CircleRenderComponent>())
	{
		//CircleRenderComp->SetColor(exColor({ 15,255,60,255 }));
	}
}
