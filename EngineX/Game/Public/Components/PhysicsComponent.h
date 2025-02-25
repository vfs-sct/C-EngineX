#pragma once
#include "Component.h"
#include "Engine/Public/EngineTypes.h"

class Actor;
class PhysicsEngine;
class CircleColliderComponent;
class BoxColliderComponent;

// this is the signature for collision events {Change it per your requirement}
using CollisionEventSignature = std::function<void(std::weak_ptr<Actor>, const exVector2&)>;

class PhysicsComponent : public Component, public std::enable_shared_from_this<PhysicsComponent>
{
	friend Actor;
	friend PhysicsEngine;

public:

	PhysicsComponent() = delete;
	virtual void DoPhysics();

	virtual void CollisionResolution();
	virtual bool IsCollisionDetectedWithCircle(std::weak_ptr<CircleColliderComponent> otherComponent) = 0;
	virtual bool IsCollisionDetectedWithBox(std::weak_ptr<BoxColliderComponent> otherComponent) = 0;

protected:

	PhysicsComponent(std::weak_ptr<Actor> owner, exVector2 velocity = { 0.0f,0.0f }, bool isStatic = false, bool isGravityEnabled = false);

	virtual void InitializeComponent() override;
	virtual bool CanAddComponent() const override;

#pragma region Collision

	virtual bool IsCollisionDetected(std::weak_ptr<PhysicsComponent>& otherComponent) = 0;
	void BroadcastCollisionEvents(std::weak_ptr<Actor>& otherActor, const exVector2 hitLocation);

public:

	void ListenForCollision(CollisionEventSignature& delegateToAdd);
	void StopListeningForCollision(CollisionEventSignature& delegateToRemove);



#pragma endregion

	void SetVelocity(const exVector2 inVelocity);
	exVector2 GetVelocity() const;


private:

	unsigned int mIsStatic : 1;
	unsigned int mIsGravityEnabled : 1;
	exVector2 mVelocity;

	std::list<CollisionEventSignature> mCollisionEvents;

};

