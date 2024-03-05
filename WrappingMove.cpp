#include "WrappingMove.h"
#include "Game.h"
#include "Actor.h"

WrappingMove::WrappingMove(Actor* owner)
: MoveComponent(owner)
{
}

void WrappingMove::Update(float deltaTime)
{
	Vector2 newLocation = mOwner->GetPosition() + (mDirection * mForwardSpeed * deltaTime);
	mOwner->SetPosition(newLocation);

	if (newLocation.x < 0)
	{
		newLocation.x = static_cast<float>(WINDOW_WIDTH);
	}
	else if (newLocation.x > WINDOW_WIDTH)
	{
		newLocation.x = 0;
	}

	mOwner->SetPosition(newLocation);
}