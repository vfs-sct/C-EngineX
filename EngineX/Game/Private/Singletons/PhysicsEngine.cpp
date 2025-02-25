#include "Game/Public/Singletons/PhysicsEngine.h"
#include "Game/Public/Components/PhysicsComponent.h"

std::unique_ptr<PhysicsEngine> PhysicsEngine::sPhysicsEngineInstance = nullptr;

PhysicsEngine::PhysicsEngine()
{
}

PhysicsEngine::~PhysicsEngine()
{
	ClearInvalidPhysicsComponents();
}

void PhysicsEngine::PhysicsUpdate(const float& deltaSeconds)
{
	ClearInvalidPhysicsComponents();


	for (size_t index1 = 0; index1 < mPhysicsComponents.size(); ++index1)
	{
		auto firstPhysicsCompIter = mPhysicsComponents.begin();
		std::advance(firstPhysicsCompIter, index1);

		if (!firstPhysicsCompIter->expired())
		{
			std::shared_ptr<PhysicsComponent> firstPhysicsCompToCheck = firstPhysicsCompIter->lock();

			for (size_t index2 = index1 + 1; index2 < mPhysicsComponents.size(); ++index2)
			{
				auto secondPhysicsCompIter = mPhysicsComponents.begin();
				std::advance(secondPhysicsCompIter, index2);

				if (!secondPhysicsCompIter->expired())
				{
					std::shared_ptr<PhysicsComponent> secondPhysicsCompToCheck = secondPhysicsCompIter->lock();

					if (firstPhysicsCompToCheck->IsCollisionDetected(*secondPhysicsCompIter))
					{
						firstPhysicsCompToCheck->BroadcastCollisionEvents(secondPhysicsCompToCheck->mOwner, exVector2(0.0f, 0.0f));
						secondPhysicsCompToCheck->BroadcastCollisionEvents(firstPhysicsCompToCheck->mOwner, exVector2(0.0f, 0.0f));

						firstPhysicsCompToCheck->CollisionResolution();
						secondPhysicsCompToCheck->CollisionResolution();
					}
				}
			}

			firstPhysicsCompToCheck->DoPhysics();
		}
	}
}

void PhysicsEngine::AddPhysicsComponent(std::weak_ptr<PhysicsComponent> componentToAdd)
{
	mPhysicsComponents.emplace_back(componentToAdd);
}

void PhysicsEngine::ClearInvalidPhysicsComponents()
{
	if (mPhysicsComponents.empty())
	{
		return;
	}
	mPhysicsComponents.erase(std::remove_if(mPhysicsComponents.begin(), mPhysicsComponents.end(),
		[](const std::weak_ptr<PhysicsComponent>& componentToCheck)->bool
		{
			return componentToCheck.expired();
		}), mPhysicsComponents.end());
}
