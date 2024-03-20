#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>
#include <cmath>

Actor::Actor(Game* game)
: mGame(game)
, mState(ActorState::Active)
, mPosition(Vector2::Zero)
, mScale(1.0f)
, mRotation(0.0f)
{
	//adds actor to game's vector of actors
	mGame->AddActor(this);

	//creates a collision component to help detect whether the actor collides with another actor
	mCollisionComp = new CollisionComponent(this);
}

Actor::~Actor()
{
	//removes actor from game's vector of actors
	mGame->RemoveActor(this);

	//deallocates actor components
	for (auto c : mComponents)
	{
		delete c;
	}
	mComponents.clear();
}

void Actor::Update(float deltaTime)
{
	// goes through and updates all the actor's various components
	if (mState == ActorState::Active)
	{
		for (auto c : mComponents)
		{
			c->Update(deltaTime);
		}
		OnUpdate(deltaTime);
	}
}

//updates the actor, overriden by child classes
void Actor::OnUpdate(float deltaTime)
{
}

void Actor::ProcessInput(const Uint8* keyState)
{
	// reads in keys from player
	if (mState == ActorState::Active)
	{
		for (auto c : mComponents)
		{
			c->ProcessInput(keyState);
		}
		OnProcessInput(keyState);
	}
}

// updates actor based on keys pressed, overriden by child classes
void Actor::OnProcessInput(const Uint8* keyState)
{
}


void Actor::AddComponent(Component* c)
{
	//adds and sorts actor components
	mComponents.emplace_back(c);
	std::sort(mComponents.begin(), mComponents.end(), [](Component* a, Component* b) {
		return a->GetUpdateOrder() < b->GetUpdateOrder();
	});
}

Vector2 Actor::GetForward() const
{
	//returns a forward vector
	return Vector2(cos(mRotation), sin(mRotation) * -1);
}
