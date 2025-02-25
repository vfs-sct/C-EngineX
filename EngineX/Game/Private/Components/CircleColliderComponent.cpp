#include "Game/Public/Components/CircleColliderComponent.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Actors/Actor.h"
#include "Game/Public/Components/BoxColliderComponent.h"

CircleColliderComponent::CircleColliderComponent(std::weak_ptr<Actor> owner, float radius, exVector2 velocity, bool isStatic, bool isGravityEnabled) :
	PhysicsComponent(owner, velocity, isStatic, isGravityEnabled)
	, mRadius(radius)
{
}

bool CircleColliderComponent::CanAddComponent() const
{
	return true;
}

bool CircleColliderComponent::IsCollisionDetected(std::weak_ptr<PhysicsComponent>& otherComponent)
{
	if (!otherComponent.expired())
	{
		std::shared_ptr<CircleColliderComponent> Self = std::dynamic_pointer_cast<CircleColliderComponent>(shared_from_this());
		return otherComponent.lock()->IsCollisionDetectedWithCircle(Self);
	}
	return false;
}

bool CircleColliderComponent::IsCollisionDetectedWithCircle(std::weak_ptr<CircleColliderComponent> otherComponent)
{
	exVector2 SelfCenterPos;
	exVector2 OtherCenterPos;

	if (!mOwner.expired())
	{
		if (const std::shared_ptr<TransformComponent> TransformComp = mOwner.lock()->FindComponentOfType<TransformComponent>())
		{
			SelfCenterPos = TransformComp->GetLocation();
		}
	}

	if (!otherComponent.expired())
	{
		if (!otherComponent.lock()->mOwner.expired())
		{
			if (const std::shared_ptr<TransformComponent> TransformComp = otherComponent.lock()->mOwner.lock()->FindComponentOfType<TransformComponent>())
			{
				OtherCenterPos = TransformComp->GetLocation();

				exVector2 Length = SelfCenterPos - OtherCenterPos;
				float DistanceSquared = (Length.x * Length.x) + (Length.y * Length.y);
				float RadiusSum = mRadius + otherComponent.lock()->mRadius;
				return DistanceSquared < (RadiusSum * RadiusSum);
			}
		}
	}

	return false;
}

bool CircleColliderComponent::IsCollisionDetectedWithBox(std::weak_ptr<BoxColliderComponent> otherComponent)
{
	exVector2 SelfCenterPos;
	exVector2 OtherCenterPos;

	if (!mOwner.expired())
	{
		if (const std::shared_ptr<TransformComponent> TransformComp = mOwner.lock()->FindComponentOfType<TransformComponent>())
		{
			SelfCenterPos = TransformComp->GetLocation();
		}
	}

	if (!otherComponent.expired())
	{
		if (!otherComponent.lock()->mOwner.expired())
		{
			if (const std::shared_ptr<TransformComponent> TransformComp = otherComponent.lock()->mOwner.lock()->FindComponentOfType<TransformComponent>())
			{
				OtherCenterPos = TransformComp->GetLocation();

				exVector2 Length = SelfCenterPos - OtherCenterPos;

				float DistanceSquaredX = (Length.x * Length.x);
				float DistanceSquaredY = (Length.y * Length.y);

				float WidthSum = mRadius + (otherComponent.lock()->GetWidth() / 2);
				float HeightSum = mRadius + (otherComponent.lock()->GetHeight() / 2);
				
				if (DistanceSquaredY < (HeightSum * HeightSum) && DistanceSquaredX < (WidthSum * WidthSum))
				{
					SetIsBoarder(false);
					return true;
				}
			}
		}
	}
	return false;
}
