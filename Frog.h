#pragma once
#include "Actor.h"
#include <unordered_map>

#include <SDL2/SDL_image.h>

class SpriteComponent;

class Frog : public Actor
{
public:
	Frog(Game* game);

	SpriteComponent* GetSpriteComp() { return mSpriteC; }

protected:
	void OnProcessInput(const Uint8* keyState) override;
	void OnUpdate(float deltaTime) override;

private:
	SpriteComponent* mSpriteC;
	std::unordered_map<SDL_Scancode, bool> mLastFrame;

	CollisionComponent* mCollisionC;

	const float START_X = 224;
	const float START_Y = 464;

	const float WATER_MAX = 255.0f;
	const float WATER_MIN = 90.0f;

	const float FROG_SIZE = 25.0f;

	const float BOX_SIZE = 32.0f;
	const float MIN_GAME_SCREEN_Y = 80.0f;
	const float MAX_GAME_SCREEN_Y = 464.0f;
	const float MAX_GAME_SCREEN_X = 416.0f;

	const int GOAL_LOC = 90.0f;
};