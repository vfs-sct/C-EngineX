#include "Game/Public/StateMachine/State.h"
#include "Game/Public/Actors/Ball.h"

void MainMenu::Enter(std::shared_ptr<Actor> DependcyObject)
{
	PlayButton = std::make_shared<Actor>();
	PlayButton->AddComponentOfType<TransformComponent>(exVector2(500.0f, 500.0f));
	PlayButton->AddComponentOfType<BoxRenderComponent>(125.0f,50.0f, exColor({ 255,0,255,255 }));

	QuitButton = std::make_shared<Actor>();
	QuitButton->AddComponentOfType<TransformComponent>(exVector2(500.0f, 250.0f));
	QuitButton->AddComponentOfType<BoxRenderComponent>(125.0f, 50.0f, exColor({ 255,0,255,255 }));
}

void MainMenu::Update(std::shared_ptr<Actor> DependcyObject)
{
}

void MainMenu::Exit(std::shared_ptr<Actor> DependcyObject)
{
	PlayButton.reset();
	QuitButton.reset();
}


void GamePlay::Enter(std::shared_ptr<Actor> DependcyObject)
{
	Player = std::make_shared<Ball>("Pirate Ship", exColor({ 150,20,30,255 }), exVector2(50.0f, 300.0f), exVector2(0.2f, 0.0f));
	Player->BeginPlay();
}

void GamePlay::Update(std::shared_ptr<Actor> DependcyObject)
{
}

void GamePlay::Exit(std::shared_ptr<Actor> DependcyObject)
{
	Player.reset();
}


void EndGame::Enter(std::shared_ptr<Actor> DependcyObject)
{
	RetryButton = std::make_shared<Actor>();
	RetryButton->AddComponentOfType<TransformComponent>(exVector2(500.0f, 500.0f));
	RetryButton->AddComponentOfType<BoxRenderComponent>(125.0f, 50.0f, exColor({ 255,0,255,255 }));
}

void EndGame::Update(std::shared_ptr<Actor> DependcyObject)
{
}

void EndGame::Exit(std::shared_ptr<Actor> DependcyObject)
{
	RetryButton.reset();
}
