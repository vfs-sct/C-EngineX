#include "Game/Public/Components/PhysicsComponent.h"
#include "Game/Public/Actors/Actor.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Singletons/PhysicsEngine.h"

void PhysicsComponent::DoPhysics()
{
	if (!mOwner.expired())
	{
		if (mIsStatic)
		{
			return;
		}

		if (const std::shared_ptr<TransformComponent> TransformComp = mOwner.lock()->FindComponentOfType<TransformComponent>())
		{
			exVector2 NewPosistion = TransformComp->GetLocation() + mVelocity;
			// add extra logic if you have gravity system @TODO
			TransformComp->SetLocation(NewPosistion);
		}
	}
}

PhysicsComponent::PhysicsComponent(std::weak_ptr<Actor> owner, exVector2 velocity, bool isStatic, bool isGravityEnabled) : Component(owner)
, mVelocity(velocity)
, mIsStatic(isStatic)
, mIsGravityEnabled(isGravityEnabled)
{

}

void PhysicsComponent::InitializeComponent()
{
	PHYSICS_ENGINE.AddPhysicsComponent(weak_from_this());
}

bool PhysicsComponent::CanAddComponent() const
{
	return false;
}

void PhysicsComponent::ListenForCollision(CollisionEventSignature& delegateToAdd)
{
	mCollisionEvents.emplace_back(delegateToAdd);
}

void PhysicsComponent::StopListeningForCollision(CollisionEventSignature& delegateToRemove)
{
	mCollisionEvents.erase(std::remove_if(mCollisionEvents.begin(), mCollisionEvents.end(),
		[delegateToRemove](const CollisionEventSignature& collisionEventIterator)->bool
		{
			return delegateToRemove.target<void(*)(std::weak_ptr<Actor>, const exVector2&)>()
				== collisionEventIterator.target<void(*)(std::weak_ptr<Actor>, const exVector2&)>();
		}), mCollisionEvents.end());
}

void PhysicsComponent::BroadcastCollisionEvents(std::weak_ptr<Actor>& otherActor, const exVector2 hitLocation)
{
	for (CollisionEventSignature& event : mCollisionEvents)
	{
		event(otherActor, hitLocation);
	}
}

void PhysicsComponent::CollisionResolution()
{
	if (mIsStatic)
	{
		return;
	}

	SetVelocity(mVelocity * -1.0f);
}

void PhysicsComponent::SetVelocity(const exVector2 inVelocity)
{
	mVelocity = inVelocity;
}

exVector2 PhysicsComponent::GetVelocity() const
{
	return mVelocity;
}
