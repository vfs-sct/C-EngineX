#include "Game/Public/Actors/Out.h"

Out::Out(String outName, exColor outColor, exVector2 startingPos, exVector2 velocity) : 
	mOutpName(outName),
	mOutColor(outColor),
	mOutStartingPosition(startingPos),
	mOutInitialVelocity(velocity)
{
}

void Out::BeginPlay()
{
	AddComponentOfType<TransformComponent>(mOutStartingPosition);
	AddComponentOfType<BoxRenderComponent>(20.0f, 700.0f, mOutColor, exVector2(0, 0));
	std::tuple<std::shared_ptr<BoxColliderComponent>, bool, String> Result = AddComponentOfType<BoxColliderComponent>(20.0f, 700.0f, mOutInitialVelocity);
	std::shared_ptr<BoxColliderComponent> ColliderComp = std::get<0>(Result);
	if (ColliderComp)
	{
		CollisionEventSignature delegate = std::bind(&Out::OnOutCollided, this, std::placeholders::_1, std::placeholders::_2);
		ColliderComp->ListenForCollision(delegate);
	}
}

void Out::OnOutCollided(std::weak_ptr<Actor> HitActor, const exVector2& HitPosition)
{
	if (!HitActor.expired())
	{
		if (const std::shared_ptr<TransformComponent> TransformComp = HitActor.lock()->FindComponentOfType<TransformComponent>())
		{
			TransformComp->SetLocation(exVector2(400, 300));
		}
	}
}
