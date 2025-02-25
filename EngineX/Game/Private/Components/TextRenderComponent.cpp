#include "Game/Public/Components/TextRenderComponent.h"
#include "Game/Public/Components/TransformComponent.h"
#include "Game/Public/Actors/Actor.h"
#include "Engine/Public/EngineInterface.h"

TextRenderComponent::TextRenderComponent(std::weak_ptr<Actor> owner, char* text, exColor color, exVector2 positionOffset, int layerID) :
	RenderComponent(owner, color, positionOffset, layerID)
	, mText(text)
{
}

void TextRenderComponent::Render(exEngineInterface* renderInterface)
{
	if (renderInterface)
	{
		exVector2 CenterPos = { 0.0f,0.0f };
		if (!mOwner.expired())
		{
			if (std::shared_ptr<TransformComponent> OwningTransformComp = mOwner.lock()->FindComponentOfType<TransformComponent>())
			{
				CenterPos = OwningTransformComp->GetLocation();
			}
		}
		CenterPos += mRenderOffset;
		renderInterface->DrawText(0, CenterPos, mText, mColor, mLayerId);
	}
}

bool TextRenderComponent::CanAddComponent() const
{
	return true;
}
