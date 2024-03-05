#pragma once
#include "Actor.h"

class SpriteComponent;
class WrappingMove;

class Log : public Actor
{
public:
	Log(Game* game, char texture);
	~Log();

	SpriteComponent* GetSpriteComp() { return mSpriteC; }
	void SetWidth(float width) { mCollisionC->SetWidth(width); }
	CollisionComponent* GetCollisionComp() { return mCollisionC; }
	WrappingMove* GetWrappingMove() { return mWrapM; }

	void SetDirection(int row);

private:
	SpriteComponent* mSpriteC;
	WrappingMove* mWrapM;
	class CollisionComponent* mCollisionC;

	const float FORWARD_SPEED = 37.5f;
	const float HEIGHT = 24.0f;
};