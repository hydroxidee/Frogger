#pragma once
#include "Actor.h"

class SpriteComponent;

class Vehicle : public Actor
{
public:
	Vehicle(Game* game, char texture);
	~Vehicle();

	SpriteComponent* GetSpriteComp() { return mSpriteC; }

	void SetDirection(int row);

	void SetSize(float width, float height) { mCollisionC->SetSize(width, height); }
	CollisionComponent* GetCollisionComponent() { return mCollisionC; }

protected:
	void OnUpdate(float deltaTime) override;

private:
	SpriteComponent* mSpriteC;
	class WrappingMove* mWrapM;
	CollisionComponent* mCollisionC;

	const float FORWARD_SPEED = 50.0f;
	const float CAR_SIZE = 32.0f;
	const float TRUCK_WIDTH = 64.0f;
	const float TRUCK_HEIGHT = 24.0f;
};