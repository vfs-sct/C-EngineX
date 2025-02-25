//
// * ENGINE-X
// * SAMPLE GAME
//
// + Game.cpp
// implementation of MyGame, an implementation of exGameInterface
//

#include "Game/Public/Game.h"

#include "Engine/Public/EngineInterface.h"
#include "Engine/Public/SDL.h"

#include "Game/Public/Actors/Actor.h"
#include "Game/Public/Singletons/RenderEngine.h"	
#include "Game/Public/Singletons/PhysicsEngine.h"
#include "Game/Public/Actors/Ball.h"
#include "Game/Public/Actors/Out.h"

//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* gWindowName = "Sample EngineX Game";
std::string MyGame::sTeamName = "Text";

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::MyGame()
	: mEngine(nullptr)
	, mFontID(-1)
	, mUp2(false)
	, mDown2(false)
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::~MyGame()
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::Initialize(exEngineInterface* pEngine)
{
	mEngine = pEngine;

	mFontID = mEngine->LoadFont("Resources/afternight.ttf", 32);

	mTextPosition.x = 50.0f;
	mTextPosition.y = 50.0f;

	Character1 = std::make_shared<Actor>();
	Character1->AddComponentOfType<TransformComponent>(exVector2(40.0f, 300.0f));
	Character1->AddComponentOfType<BoxRenderComponent>(5.0f, 100.0f, exColor({ 0,0,255,255 }));
	Character1->AddComponentOfType<BoxColliderComponent>(5.0f, 100.0f, exVector2(0.0f, 0.0f));
	mPlayer1 = Character1->FindComponentOfType<TransformComponent>()->GetLocation();

	Character2 = std::make_shared<Actor>();
	Character2->AddComponentOfType<TransformComponent>(exVector2(730.0f, 300.0f));
	Character2->AddComponentOfType<BoxRenderComponent>(5.0f, 100.0f);
	Character2->AddComponentOfType<BoxColliderComponent>(5.0f, 100.0f, exVector2(0.0f, 0.0f));
	//Character2->AddComponentOfType<TextRenderComponent>("h6i");
	mPlayer2 = Character2->FindComponentOfType<TransformComponent>()->GetLocation();

	mBall = std::make_shared<Ball>("Ball", exColor({ 150,20,30,255 }), exVector2(400.0f, 300.0f), exVector2(2.0f, 0.0f));
	mBall->BeginPlay();

	mOut1 = std::make_shared<Out>("out Line", exColor({ 150,20,30,255 }), exVector2(820, 300.0f), exVector2(0.0f, 0.0f));
	mOut1->BeginPlay();

	mOut2 = std::make_shared<Out>("out Line", exColor({ 150,20,30,255 }), exVector2(-30, 300.0f), exVector2(0.0f, 0.0f));
	mOut2->BeginPlay();

	//mStateMachine = std::make_shared<StateMachine<Actor>>();
	//mStateMachine->AddState("GamePlay", std::make_shared<GamePlay>());
	//mStateMachine->AddState("MainMenu", std::make_shared<MainMenu>());
	//mStateMachine->AddState("EndGame", std::make_shared<EndGame>());

	//mStateMachine->SetState("MainMenu", nullptr);

}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

const char* MyGame::GetWindowName() const
{
	return gWindowName;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::GetClearColor(exColor& color) const
{
	color.mColor[0] = 128;
	color.mColor[1] = 128;
	color.mColor[2] = 128;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::OnEvent(SDL_Event* pEvent)
{
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::OnEventsConsumed()
{
	int nKeys = 0;
	const Uint8* pState = SDL_GetKeyboardState(&nKeys);

	mUp1 = pState[SDL_SCANCODE_W];
	mDown1 = pState[SDL_SCANCODE_S];

	mUp2 = pState[SDL_SCANCODE_UP];
	mDown2 = pState[SDL_SCANCODE_DOWN];
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::Run(float fDeltaT)
{
	if (mUp1)
	{
		mPlayer1.y -= 400.0f * fDeltaT;
		Character1->FindComponentOfType<TransformComponent>()->SetLocation(mPlayer1);
	}
	else if (mDown1)
	{
		mPlayer1.y += 400.0f * fDeltaT;
		Character1->FindComponentOfType<TransformComponent>()->SetLocation(mPlayer1);
	}

	if (mUp2)
	{
		mPlayer2.y -= 400.0f * fDeltaT;
		Character2->FindComponentOfType<TransformComponent>()->SetLocation(mPlayer2);
	}
	else if (mDown2)
	{
		mPlayer2.y += 400.0f * fDeltaT;
		Character2->FindComponentOfType<TransformComponent>()->SetLocation(mPlayer2);
	}

	//if (Character)
	//{
	//	if (std::shared_ptr<TransformComponent> TransformComp = Character->FindComponentOfType<TransformComponent>())
	//	{
	//		//TransformComp->SetLocation(TransformComp->GetLocation() += mTextPosition);
	//	}

	//	for (std::shared_ptr<RenderComponent> RenderCompIter : Character->FindAllComponentOfType<RenderComponent>())
	//	{
	//		RenderCompIter->Render(mEngine);
	//	}

	//}

	//exVector2 p1, p2;
	//exColor c;
	//float r;

	//c.mColor[0] = 25;
	//c.mColor[1] = 255;
	//c.mColor[2] = 0;
	//c.mColor[3] = 255;

	//p1.x = 175.0f;
	//p1.y = 175.0f;

	//r = 25.0f;

	//mEngine->DrawLineCircle(p1, r, c, 0);

	//p1.x = 100.0f;
	//p1.y = 100.0f;

	//p2.x = 200.0f;
	//p2.y = 200.0f;

	//c.mColor[0] = 255;
	//c.mColor[1] = 0;
	//c.mColor[2] = 0;

	//mEngine->DrawBox(p1, p2, c, 1);

	//p1.x = 400.0f;
	//p1.y = 400.0f;

	//p2.x = 500.0f;
	//p2.y = 500.0f;

	//mEngine->DrawLineBox(p1, p2, c, 1);

	//p1.x = 400.0f;
	//p1.y = 400.0f;

	//c.mColor[0] = 0;
	//c.mColor[1] = 0;
	//c.mColor[2] = 0;

	//mEngine->DrawCircle(p1, r, c, 2);

	//mEngine->DrawText(mFontID, mTextPosition, sTeamName.c_str(), c, 0);

	//mStateMachine->Update(nullptr);

	RENDER_ENGINE.Render(mEngine);
	PHYSICS_ENGINE.PhysicsUpdate(fDeltaT);
}
