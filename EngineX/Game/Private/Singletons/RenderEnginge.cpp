#include "Game/Public/Singletons/RenderEngine.h"
#include "Game/Public/Components/RenderComponent.h"

std::unique_ptr<RenderEngine> RenderEngine::sRenderEngineInstance = nullptr;

RenderEngine::RenderEngine()
{
}

RenderEngine::~RenderEngine()
{
	ClearInvalidRenderComponents();
}

void RenderEngine::Render(exEngineInterface* engineInterface)
{
	ClearInvalidRenderComponents();

	for (std::weak_ptr<RenderComponent>& currentRenderComponentIterator : mRenderComponents)
	{
		if (!currentRenderComponentIterator.expired())
		{
			currentRenderComponentIterator.lock()->Render(engineInterface);
		}
	}
}

void RenderEngine::AddRenderComponent(std::weak_ptr<RenderComponent> componentToAdd)
{
	mRenderComponents.emplace_back(componentToAdd);
}

void RenderEngine::ClearInvalidRenderComponents()
{
	mRenderComponents.erase(std::remove_if(mRenderComponents.begin(), mRenderComponents.end(),
		[](const std::weak_ptr<RenderComponent>& componentToCheck)->bool
		{
			return componentToCheck.expired();
		}), mRenderComponents.end());
}
