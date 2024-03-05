#include "Vehicle.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "WrappingMove.h"

#include "Math.h"
#include "Frog.h"

Vehicle::Vehicle(Game* game, char texture)
: Actor(game)
{
	mSpriteC = new SpriteComponent(this);

	mWrapM = new WrappingMove(this);
	mWrapM->SetForwardSpeed(FORWARD_SPEED);

	mCollisionC = new CollisionComponent(this);

	if (texture == 'A')
	{
		GetSpriteComp()->SetTexture(mGame->GetTexture("Assets/CarA.png"));
		SetSize(CAR_SIZE, CAR_SIZE);
	}
	else if (texture == 'B')
	{
		GetSpriteComp()->SetTexture(mGame->GetTexture("Assets/CarB.png"));
		SetSize(CAR_SIZE, CAR_SIZE);
	}
	else if (texture == 'C')
	{
		GetSpriteComp()->SetTexture(mGame->GetTexture("Assets/CarC.png"));
		SetSize(CAR_SIZE, CAR_SIZE);
	}
	else if (texture == 'D')
	{
		GetSpriteComp()->SetTexture(mGame->GetTexture("Assets/CarD.png"));
		SetSize(CAR_SIZE, CAR_SIZE);
	}
	else if (texture == 'T')
	{
		GetSpriteComp()->SetTexture(mGame->GetTexture("Assets/Truck.png"));
		SetSize(TRUCK_WIDTH, TRUCK_HEIGHT);
	}

	mGame->AddVehicle(this);
}

Vehicle::~Vehicle()
{
	mGame->RemoveVehicle(this);
}

void Vehicle::OnUpdate(float deltaTime)
{
	Vector2 toFrog = mGame->GetFrog()->GetPosition() - GetPosition();

	toFrog.Normalize();

	float dot = Vector2::Dot(mWrapM->GetDirection(), toFrog);
	float angle = Math::Acos(dot);

	if (angle < (Math::Pi / 6.0f))
	{
		mWrapM->SetForwardSpeed(FORWARD_SPEED / 2);
	}
	else
	{
		mWrapM->SetForwardSpeed(FORWARD_SPEED);
	}
}

void Vehicle::SetDirection(int row)
{
	if (row % 2 == 0)
	{
		mWrapM->SetDirection(Vector2(1, 0));
	}
	else
	{
		mWrapM->SetDirection(Vector2(-1, 0));
	}
}