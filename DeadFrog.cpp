#include "DeadFrog.h"
#include "Game.h"
#include "Math.h"
#include "SpriteComponent.h"

#include "Vehicle.h"

DeadFrog::DeadFrog(Game* game)
: Actor(game)
{
	//creates a dead frog 
	mSpriteC = new SpriteComponent(this);
	mSpriteC->SetTexture(mGame->GetTexture("Assets/Dead.png"));

	mLifetime = 0.0f;
}

void DeadFrog::OnUpdate(float deltaTime)
{
	//keeps dead frog on screen for 0.5 seconds then removes it
	mLifetime = mLifetime + deltaTime;

	if (mLifetime > 0.5f)
	{
		SetState(ActorState::Destroy);
	}
}