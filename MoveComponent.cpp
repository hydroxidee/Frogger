#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(class Actor* owner)
: Component(owner, 50)
, mAngularSpeed(0.0f)
, mForwardSpeed(0.0f)
{
}

void MoveComponent::Update(float deltaTime)
{
	//update rotation
	float newRotation = mOwner->GetRotation() + (mAngularSpeed * deltaTime);
	mOwner->SetRotation(newRotation);

	//update forward
	Vector2 newLocation = mOwner->GetPosition() +
						  (mOwner->GetForward() * mForwardSpeed * deltaTime);
	mOwner->SetPosition(newLocation);
}