#include "Log.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "WrappingMove.h"
#include "CollisionComponent.h"

Log::Log(Game* game, char texture)
: Actor(game)
{
	// creates a log of varying width depending on the texture index
	mSpriteC = new SpriteComponent(this);

	mWrapM = new WrappingMove(this);
	mWrapM->SetForwardSpeed(FORWARD_SPEED);

	mCollisionC = new CollisionComponent(this);
	mCollisionC->SetHeight(HEIGHT);

	if (texture == 'X')
	{
		GetSpriteComp()->SetTexture(mGame->GetTexture("Assets/LogX.png"));
		SetWidth(96.0f);
	}
	else if (texture == 'Y')
	{
		GetSpriteComp()->SetTexture(mGame->GetTexture("Assets/LogY.png"));
		SetWidth(128.0f);
	}
	else if (texture == 'Z')
	{
		GetSpriteComp()->SetTexture(mGame->GetTexture("Assets/LogZ.png"));
		SetWidth(192.0f);
	}

	mGame->AddLog(this);
}

Log::~Log()
{
	mGame->RemoveLog(this);
}

void Log::SetDirection(int row)
{
	// sets direction in which log is moving (left or right)
	if (row % 2 == 0)
	{
		mWrapM->SetDirection(Vector2(1, 0));
	}
	else
	{
		mWrapM->SetDirection(Vector2(-1, 0));
	}
}