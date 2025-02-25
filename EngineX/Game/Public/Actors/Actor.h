#pragma once
#include "Game/Public/Components/ComponentTypes.h"

class Actor : public std::enable_shared_from_this<Actor>
{

public:

	Actor();
	~Actor();

protected:

	// parameters lower case, memebers prefix with m, statick prefix with s
	// will be called when the Actor is added or the Game Starts
	virtual void BeginPlay();
	// will be called before destruction or at game end
	virtual void EndPlay();
	// will be called every frame
	virtual void Tick(float deltaSeconds);


	unsigned int mCanEverTick : 1;

private:
	// stores all the components
	ComponentList mComponents;

#pragma region TemplateRegion

public:

	// Add component function
	template<std::derived_from<Component> ComponentType, typename ...Args>
	std::tuple<std::shared_ptr<ComponentType>, bool, String> AddComponentOfType(Args... arguments)
	{
		ComponentType* NewComponentRawPtr = new ComponentType(weak_from_this(), arguments...);
		std::shared_ptr<ComponentType> NewComponent = std::make_shared<ComponentType>(*NewComponentRawPtr);
		delete NewComponentRawPtr;
		if (NewComponent->CanAddComponent())
		{
			NewComponent->InitializeComponent();
			mComponents.emplace_back(NewComponent);
			return { NewComponent, true, "Componet was created successfully" };
		}
		return { nullptr, false, "failed to add component as it returns false in Component::CanAddComponent" };
	}

	// find component function
	template<std::derived_from<Component> ComponentClassToFind>
	std::shared_ptr<ComponentClassToFind> FindComponentOfType()
	{
		for (std::shared_ptr<Component> ComponentIterator : mComponents)
		{
			if (std::shared_ptr<ComponentClassToFind> FoundComponent =
				std::dynamic_pointer_cast<ComponentClassToFind>(ComponentIterator))
			{
				return FoundComponent;
			}

		}
		return nullptr;
	}

	template<std::derived_from<Component> ComponentClassToFind>
	std::list<std::shared_ptr<ComponentClassToFind>> FindAllComponentOfType()
	{
		std::list<std::shared_ptr<ComponentClassToFind>> FoundComponents;
		for (std::shared_ptr<Component> ComponentIterator : mComponents)
		{
			if (std::shared_ptr<ComponentClassToFind> FoundComponent =
				std::dynamic_pointer_cast<ComponentClassToFind>(ComponentIterator))
			{
				FoundComponents.emplace_back(FoundComponent);
			}
		}
		return FoundComponents;
	}

#pragma endregion

};

