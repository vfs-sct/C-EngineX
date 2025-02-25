#pragma once
#include "Game/Public/GameCore/GameCore.h"

class Actor;

class Component
{
	friend Actor;

public:

	Component() = delete;
	virtual ~Component();


	// game functions
	std::weak_ptr<Actor> mOwner;
protected:

	Component(std::weak_ptr<Actor> owner);
	virtual void InitializeComponent();
	virtual void DeinitializeComponent();
	virtual void TickComponent(float deltaSeconds);
	virtual bool CanAddComponent() const;
};

using ComponentList = std::list<std::shared_ptr<Component>>;

