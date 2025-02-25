#pragma once
#include "RenderComponent.h"

class TextRenderComponent : public RenderComponent
{
	friend class Actor;
public:

	TextRenderComponent() = delete;
	virtual void Render(exEngineInterface* renderInterface) override;

protected:

	TextRenderComponent(std::weak_ptr<Actor> owner, char* text , exColor color = { 255,0,0,255 }, exVector2 positionOffset = { 0.0f,0.0f }, int layerID = 1);

	virtual bool CanAddComponent() const override;

private:

	char* mText;
};

