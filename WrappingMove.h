#pragma once
#include "MoveComponent.h"
#include "Math.h"

class SpriteComponent;

class WrappingMove : public MoveComponent
{
public:
	WrappingMove(class Actor* owner);

	void Update(float deltaTime) override;
	void SetDirection(Vector2 direction) { mDirection = direction; }
	Vector2 GetDirection() { return mDirection; }

protected:
	// void OnProcessInput(const Uint8* keyState) override;

private:
	Vector2 mDirection;

	const int WINDOW_WIDTH = 448;
};