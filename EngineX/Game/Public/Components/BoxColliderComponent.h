#pragma once
#include "PhysicsComponent.h"

class BoxColliderComponent : public PhysicsComponent
{
	friend class Actor;

public:

	BoxColliderComponent() = delete;

	float GetWidth()
	{
		return mWidth;
	}

	float GetHeight()
	{
		return mHeight;
	}

protected:

	BoxColliderComponent(std::weak_ptr<Actor> owner, float width, float height, exVector2 velocity, bool isStatic = false, bool isGravityEnabled = false);

	virtual bool CanAddComponent() const override;
	virtual bool IsCollisionDetected(std::weak_ptr<PhysicsComponent>& otherComponent) override;
	virtual bool IsCollisionDetectedWithBox(std::weak_ptr<BoxColliderComponent> otherComponent) override;
	virtual bool IsCollisionDetectedWithCircle(std::weak_ptr<CircleColliderComponent> otherComponent) override;

private:

	float mWidth;
	float mHeight;
};