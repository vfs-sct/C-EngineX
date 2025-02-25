#include "Game/Public/Actors/Ball.h"
#include "Game/Public/Actors/Out.h"
#include "Game/Public/Game.h"

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
	auto hitActorPtr = HitActor.lock();
	if (!hitActorPtr) return;

	if (auto outActor = std::dynamic_pointer_cast<Out>(hitActorPtr))
	{
		// Reset ball position
		if (std::shared_ptr<TransformComponent> transform = FindComponentOfType<TransformComponent>())
		{
			transform->SetLocation(exVector2(400.0f, 300.0f));
			
			// Reset velocity
			if (std::shared_ptr<CircleColliderComponent> collider = FindComponentOfType<CircleColliderComponent>())
			{
				// Randomize direction slightly
				float randY = (rand() % 200) / 100.0f;  // Random value between -2 and 2
				exVector2 newVel = exVector2(HitPosition.x < 400.0f ? 2.0f : -2.0f, randY);
				collider->SetVelocity(newVel);
			}
			
			// Update score in MyGame
			if (HitPosition.x < 400.0f)  // Left side
			{
				MyGame::IncrementScore(2);  // Player 2 scores
			}
			else  // Right side
			{
				MyGame::IncrementScore(1);  // Player 1 scores
			}
		}
	}
}
