//
// * ENGINE-X
// * SAMPLE GAME
//
// + Game.h
// definition of MyGame, an implementation of exGameInterface
//

#include "Game/Public/GameInterface.h"
#include "Engine/Public/EngineTypes.h"
#include "string"
#include "Game/Public/GameCore/GameCore.h"
#include "Game/Public/StateMachine/StateMachine.h"

//-----------------------------------------------------------------
//-----------------------------------------------------------------
class Actor;
class Ball;
class Out;

class MyGame : public exGameInterface
{
public:

	MyGame();
	virtual						~MyGame();

	virtual void				Initialize(exEngineInterface* pEngine);

	virtual const char* GetWindowName() const;
	virtual void				GetClearColor(exColor& color) const;

	virtual void				OnEvent(SDL_Event* pEvent);
	virtual void				OnEventsConsumed();

	virtual void				Run(float fDeltaT);

	static void IncrementScore(int playerNum) {
		if (sInstance) {
			if (playerNum == 1) sInstance->mPlayer1Score++;
			else if (playerNum == 2) sInstance->mPlayer2Score++;
		}
	}

private:

	exEngineInterface* mEngine;

	int							mFontID;
	int                         mPlayer1Score;
	int                         mPlayer2Score;
	bool                        mIsMainMenu;
	bool                        mIsGameOver;
	bool                        mIsGameOver2;
	exVector2                   mScorePosition1;
	exVector2                   mScorePosition2;
	exVector2                   mMenuTextPosition;

	bool						mUp1;
	bool						mDown1;

	bool						mUp2;
	bool						mDown2;


	exVector2					mTextPosition;

	exVector2                   mPlayer1;
	exVector2                   mPlayer2;

	std::shared_ptr<Actor>		Character1;
	std::shared_ptr<Actor>		Character2;
	std::shared_ptr<Ball>		mBall;

	std::shared_ptr<Out>		mOut1;
	std::shared_ptr<Out>		mOut2;
	std::shared_ptr<Actor>		mTopWall;
	std::shared_ptr<Actor>		mBottomWall;

	std::shared_ptr<StateMachine<Actor>> mStateMachine;

	static std::string	sTeamName;
	static MyGame* sInstance;

};
