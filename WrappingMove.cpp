#include "WrappingMove.h"
#include "Game.h"
#include "Actor.h"

WrappingMove::WrappingMove(Actor* owner)
: MoveComponent(owner)
{
}

void WrappingMove::Update(float deltaTime)
{
	// moves log / vehicle forward
	Vector2 newLocation = mOwner->GetPosition() + (mDirection * mForwardSpeed * deltaTime);
	mOwner->SetPosition(newLocation);

	//sets its position to the other side of the screen if it is about to go offscreen
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