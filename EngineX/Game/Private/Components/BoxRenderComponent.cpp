#include "Game/Public/Components/BoxRenderComponent.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Actors/Actor.h"
#include "Engine/Public/EngineInterface.h"

BoxRenderComponent::BoxRenderComponent(std::weak_ptr<Actor> owner, float width, float height, exColor color, exVector2 positionOffset, int layerID) :
	RenderComponent(owner, color, positionOffset, layerID)
	, mWidth(width)
	, mHeight(height)
{
}

bool BoxRenderComponent::CanAddComponent() const
{
	return true;
}


void BoxRenderComponent::Render(exEngineInterface* renderInterface)
{
	if (renderInterface)
	{
		exVector2 CenterPos = { 0.0f,0.0f };
		exVector2 TopLeft = { 0.0f,0.0f };
		exVector2 BottomRight = { 0.0f,0.0f };
		const exVector2 HalfBox = exVector2(mWidth, mHeight) * 0.5f;
		if (!mOwner.expired())
		{
			if (std::shared_ptr<TransformComponent> OwningTransformComp = mOwner.lock()->FindComponentOfType<TransformComponent>())
			{
				CenterPos = OwningTransformComp->GetLocation();
			}
		}
		CenterPos += mRenderOffset;
		TopLeft = CenterPos - HalfBox;
		BottomRight = CenterPos + HalfBox;

		renderInterface->DrawBox(TopLeft, BottomRight, mColor, mLayerId);
	}
}
