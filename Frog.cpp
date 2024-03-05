#include "Frog.h"
#include "Game.h"
#include "Math.h"
#include "SpriteComponent.h"

#include "Vehicle.h"
#include "DeadFrog.h"
#include "CollisionComponent.h"
#include "Log.h"
#include "WrappingMove.h"

Frog::Frog(Game* game)
: Actor(game)
{
	mSpriteC = new SpriteComponent(this);

	mLastFrame.insert({SDL_SCANCODE_W, false});
	mLastFrame.insert({SDL_SCANCODE_A, false});
	mLastFrame.insert({SDL_SCANCODE_S, false});
	mLastFrame.insert({SDL_SCANCODE_D, false});

	mCollisionC = new CollisionComponent(this);
	mCollisionC->SetSize(FROG_SIZE, FROG_SIZE);
}

void Frog::OnProcessInput(const Uint8* keyState)
{
	//moves frog up
	if (keyState[SDL_SCANCODE_W] && !mLastFrame[SDL_SCANCODE_W])
	{
		float y = Math::Clamp(GetPosition().y - BOX_SIZE, MIN_GAME_SCREEN_Y, MAX_GAME_SCREEN_Y);
		SetPosition(Vector2(GetPosition().x, y));
	}

	//moves frog left
	if (keyState[SDL_SCANCODE_A] && !mLastFrame[SDL_SCANCODE_A])
	{
		float x = Math::Clamp(GetPosition().x - BOX_SIZE, BOX_SIZE, MAX_GAME_SCREEN_X);
		SetPosition(Vector2(x, GetPosition().y));
	}

	//moves frog down
	if (keyState[SDL_SCANCODE_S] && !mLastFrame[SDL_SCANCODE_S])
	{
		float y = Math::Clamp(GetPosition().y + BOX_SIZE, MIN_GAME_SCREEN_Y, MAX_GAME_SCREEN_Y);
		SetPosition(Vector2(GetPosition().x, y));
	}

	//moves frog right
	if (keyState[SDL_SCANCODE_D] && !mLastFrame[SDL_SCANCODE_D])
	{
		float x = Math::Clamp(GetPosition().x + BOX_SIZE, BOX_SIZE, MAX_GAME_SCREEN_X);
		SetPosition(Vector2(x, GetPosition().y));
	}

	mLastFrame[SDL_SCANCODE_W] = keyState[SDL_SCANCODE_W];
	mLastFrame[SDL_SCANCODE_A] = keyState[SDL_SCANCODE_A];
	mLastFrame[SDL_SCANCODE_S] = keyState[SDL_SCANCODE_S];
	mLastFrame[SDL_SCANCODE_D] = keyState[SDL_SCANCODE_D];
}

void Frog::OnUpdate(float deltaTime)
{
	//run over by vehicle
	for (auto v : mGame->GetVehicles())
	{
		if (v->GetCollisionComponent()->Intersect(mCollisionC))
		{
			DeadFrog* died = new DeadFrog(mGame);
			died->SetPosition(GetPosition());

			SetPosition(Vector2(START_X, START_Y));
			break;
		}
	}

	//on log?
	bool onLog = false;
	for (auto l : mGame->GetLogs())
	{
		Vector2 offset;
		CollSide collision = mCollisionC->GetMinOverlap(l->GetCollisionComp(), offset);

		//on log
		if (collision != CollSide::None)
		{
			SetPosition(Vector2(GetPosition().x, l->GetPosition().y));

			//log movement
			WrappingMove* logWrap = l->GetWrappingMove();
			Vector2 newLocation =
				GetPosition() + (logWrap->GetDirection() * logWrap->GetForwardSpeed() * deltaTime);

			if (collision == CollSide::Left)
			{
				newLocation.x = newLocation.x + (BOX_SIZE / 2);
			}
			if (collision == CollSide::Right)
			{
				newLocation.x = newLocation.x - (BOX_SIZE / 2);
			}

			SetPosition(newLocation);

			onLog = true;
		}
	}

	//drowned?
	if (!onLog)
	{
		if (GetPosition().y <= WATER_MAX && GetPosition().y >= WATER_MIN)
		{
			DeadFrog* died = new DeadFrog(mGame);
			died->SetPosition(GetPosition());

			SetPosition(Vector2(START_X, START_Y));
		}
	}

	//at goal
	Vector2 offset;
	CollSide collision = mCollisionC->GetMinOverlap(mGame->GetGoal()->GetCollisionComp(), offset);
	if (collision != CollSide::None)
	{
		SetState(ActorState::Paused);
	}

	//didnt hit goal
	if (GetPosition().y < GOAL_LOC && collision == CollSide::None)
	{
		DeadFrog* died = new DeadFrog(mGame);
		died->SetPosition(GetPosition());

		SetPosition(Vector2(START_X, START_Y));
	}
}