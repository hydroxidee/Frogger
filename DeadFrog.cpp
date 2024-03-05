#include "DeadFrog.h"
#include "Game.h"
#include "Math.h"
#include "SpriteComponent.h"

#include "Vehicle.h"

DeadFrog::DeadFrog(Game* game)
: Actor(game)
{
	mSpriteC = new SpriteComponent(this);
	mSpriteC->SetTexture(mGame->GetTexture("Assets/Dead.png"));

	mLifetime = 0.0f;
}

void DeadFrog::OnUpdate(float deltaTime)
{
	mLifetime = mLifetime + deltaTime;

	if (mLifetime > 0.5f)
	{
		SetState(ActorState::Destroy);
	}
}