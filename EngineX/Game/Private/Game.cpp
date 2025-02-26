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
MyGame* MyGame::sInstance = nullptr;

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::MyGame()
	: mEngine(nullptr)
	, mFontID(-1)
	, mPlayer1Score(0)
	, mPlayer2Score(0)
	, mIsMainMenu(true)
	, mIsGameOver(false)
	, mUp2(false)
	, mDown2(false)
{
	sInstance = this;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

MyGame::~MyGame()
{
	if (sInstance == this)
		sInstance = nullptr;
}

//-----------------------------------------------------------------
//-----------------------------------------------------------------

void MyGame::Initialize(exEngineInterface* pEngine)
{
	mEngine = pEngine;

	mFontID = mEngine->LoadFont("Resources/afternight.ttf", 32);

	mTextPosition.x = 50.0f;
	mTextPosition.y = 50.0f;

	mScorePosition1.x = 200.0f;
	mScorePosition1.y = 50.0f;

	mScorePosition2.x = 600.0f;
	mScorePosition2.y = 50.0f;

	mMenuTextPosition.x = 300.0f;
	mMenuTextPosition.y = 300.0f;

	Character1 = std::make_shared<Actor>();
	Character1->AddComponentOfType<TransformComponent>(exVector2(40.0f, 300.0f));
	Character1->AddComponentOfType<BoxRenderComponent>(5.0f, 100.0f, exColor({ 0,0,255,255 }));
	Character1->AddComponentOfType<BoxColliderComponent>(5.0f, 100.0f, exVector2(0.0f, 0.0f));
	mPlayer1 = Character1->FindComponentOfType<TransformComponent>()->GetLocation();

	Character2 = std::make_shared<Actor>();
	Character2->AddComponentOfType<TransformComponent>(exVector2(730.0f, 300.0f));
	Character2->AddComponentOfType<BoxRenderComponent>(5.0f, 100.0f);
	Character2->AddComponentOfType<BoxColliderComponent>(5.0f, 100.0f, exVector2(0.0f, 0.0f));
	mPlayer2 = Character2->FindComponentOfType<TransformComponent>()->GetLocation();

	mBall = std::make_shared<Ball>("Ball", exColor({ 150,20,30,255 }), exVector2(400.0f, 300.0f), exVector2(2.0f, 3.0f));
	mBall->BeginPlay();

	mOut1 = std::make_shared<Out>("out Line", exColor({ 150,20,30,255 }), exVector2(820, 300.0f), exVector2(0.0f, 0.0f));
	mOut1->BeginPlay();

	mOut2 = std::make_shared<Out>("out Line", exColor({ 150,20,30,255 }), exVector2(-30, 300.0f), exVector2(0.0f, 0.0f));
	mOut2->BeginPlay();

	// Create top wall
	mTopWall = std::make_shared<Actor>();
	mTopWall->AddComponentOfType<TransformComponent>(exVector2(400.0f, 10.0f));
	mTopWall->AddComponentOfType<BoxRenderComponent>(800.0f, 20.0f, exColor({ 0,0,0,255 }));
	mTopWall->AddComponentOfType<BoxColliderComponent>(800.0f, 20.0f, exVector2(0.0f, 0.0f), true);

	// Create bottom wall
	mBottomWall = std::make_shared<Actor>();
	mBottomWall->AddComponentOfType<TransformComponent>(exVector2(400.0f, 590.0f));
	mBottomWall->AddComponentOfType<BoxRenderComponent>(800.0f, 20.0f, exColor({ 0,0,0,255 }));
	mBottomWall->AddComponentOfType<BoxColliderComponent>(800.0f, 20.0f, exVector2(0.0f, 0.0f), true);

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
	switch (pEvent->type)
	{
	case SDL_KEYDOWN:
		switch (pEvent->key.keysym.sym)
		{
		case SDLK_w:
			mUp1 = true;
			break;
		case SDLK_s:
			mDown1 = true;
			break;
		case SDLK_UP:
			mUp2 = true;
			break;
		case SDLK_DOWN:
			mDown2 = true;
			break;
		case SDLK_SPACE:
			if (mIsMainMenu)
			{
				mIsMainMenu = false;
				// Reset game state
				mPlayer1Score = 0;
				mPlayer2Score = 0;
				mBall->FindComponentOfType<TransformComponent>()->SetLocation(exVector2(400.0f, 300.0f));
			}
			else if (mIsGameOver)
			{
				mIsGameOver = false;
				mIsMainMenu = true;
			}
			break;
		}
		break;
	case SDL_KEYUP:
		switch (pEvent->key.keysym.sym)
		{
		case SDLK_w:
			mUp1 = false;
			break;
		case SDLK_s:
			mDown1 = false;
			break;
		case SDLK_UP:
			mUp2 = false;
			break;
		case SDLK_DOWN:
			mDown2 = false;
			break;
		}
		break;
	}
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
	exColor textColor = { 255, 255, 255, 255 };

	if (mIsMainMenu)
	{
		mEngine->DrawText(mFontID, mMenuTextPosition, "Press SPACE to Start", textColor, 0);
		return;
	}

	if (mIsGameOver)
	{
		mEngine->DrawText(mFontID, mMenuTextPosition, "Player 1 Wins! Press SPACE to Restart", textColor, 0);
		return;
	}
	if (mIsGameOver2)
	{
		mEngine->DrawText(mFontID, mMenuTextPosition, "Player 2 Wins! Press SPACE to Restart", textColor, 0);
		return;
	}

	// Update paddle positions with constraints
	if (mUp1)
	{
		mPlayer1.y = std::max(mPlayer1.y - 400.0f * fDeltaT, 30.0f);  // 30.0f is minimum Y (accounting for wall)
		Character1->FindComponentOfType<TransformComponent>()->SetLocation(mPlayer1);
	}
	else if (mDown1)
	{
		mPlayer1.y = std::min(mPlayer1.y + 400.0f * fDeltaT, 570.0f);  // 570.0f is maximum Y (accounting for wall)
		Character1->FindComponentOfType<TransformComponent>()->SetLocation(mPlayer1);
	}

	if (mUp2)
	{
		mPlayer2.y = std::max(mPlayer2.y - 400.0f * fDeltaT, 30.0f);
		Character2->FindComponentOfType<TransformComponent>()->SetLocation(mPlayer2);
	}
	else if (mDown2)
	{
		mPlayer2.y = std::min(mPlayer2.y + 400.0f * fDeltaT, 570.0f);
		Character2->FindComponentOfType<TransformComponent>()->SetLocation(mPlayer2);
	}

	// Draw scores
	char score1Text[32];
	char score2Text[32];
	sprintf_s(score1Text, "%d", mPlayer1Score);
	sprintf_s(score2Text, "%d", mPlayer2Score);
	
	mEngine->DrawText(mFontID, mScorePosition1, score1Text, textColor, 0);
	mEngine->DrawText(mFontID, mScorePosition2, score2Text, textColor, 0);

	// Check for victory
	if (mPlayer1Score >= 7)
	{
		mIsGameOver = true;
	}
	if (mPlayer2Score >= 7)
	{
		mIsGameOver2 = true;
	}

	RENDER_ENGINE.Render(mEngine);
	PHYSICS_ENGINE.PhysicsUpdate(fDeltaT);
}
