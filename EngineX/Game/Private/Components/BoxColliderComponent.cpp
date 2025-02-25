#include "Game/Public/Components/BoxColliderComponent.h"
#include "Game/Public/Components/CircleColliderComponent.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Actors/Actor.h"

BoxColliderComponent::BoxColliderComponent(std::weak_ptr<Actor> owner, float width, float height, exVector2 velocity, bool isStatic, bool isGravityEnabled) :
	PhysicsComponent(owner, velocity,isStatic,isGravityEnabled)
	,mWidth(width)
	,mHeight(height)
{
}

bool BoxColliderComponent::CanAddComponent() const
{
	return true;
}

bool BoxColliderComponent::IsCollisionDetected(std::weak_ptr<PhysicsComponent>& otherComponent)
{
	if (!otherComponent.expired())
	{
		std::shared_ptr<BoxColliderComponent> Self = std::dynamic_pointer_cast<BoxColliderComponent>(shared_from_this());
		return otherComponent.lock()->IsCollisionDetectedWithBox(Self);
	}
	return false;
}

bool BoxColliderComponent::IsCollisionDetectedWithBox(std::weak_ptr<BoxColliderComponent> otherComponent)
{
	exVector2 SelfCenterPos;
	exVector2 otherCenterPos;

	if (!mOwner.expired())
	{
		if (const std::shared_ptr<TransformComponent>TransFormComp = mOwner.lock()->FindComponentOfType<TransformComponent>())
		{
			SelfCenterPos = TransFormComp->GetLocation();
		}
	}

	if (!otherComponent.expired())
	{
		if (!otherComponent.lock()->mOwner.expired())
		{
			if (const std::shared_ptr<TransformComponent> TransformComp = otherComponent.lock()->mOwner.lock()->FindComponentOfType<TransformComponent>())
			{
				otherCenterPos = TransformComp->GetLocation();

				exVector2 Length = SelfCenterPos - otherCenterPos;

				float DistanceSquaredX = (Length.x * Length.x);
				float DistanceSquaredY = (Length.y * Length.y);

				float HeightSum = (mHeight / 2) + (otherComponent.lock()->mHeight / 2);
				float WidthSum = (mWidth / 2) + (otherComponent.lock()->mWidth / 2);
				if (DistanceSquaredY < (HeightSum * HeightSum) && DistanceSquaredX < (WidthSum * WidthSum))
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool BoxColliderComponent::IsCollisionDetectedWithCircle(std::weak_ptr<CircleColliderComponent> otherComponent)
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

				float WidthSum = mWidth + (otherComponent.lock()->GetRadius() / 2);
				float HeightSum = mHeight + (otherComponent.lock()->GetRadius() / 2);

				if (DistanceSquaredY < (HeightSum * HeightSum) && DistanceSquaredX < (WidthSum * WidthSum))
				{
					return true;
				}
			}
		}
	}

	return false;
}
