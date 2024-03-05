#pragma once
#include "Actor.h"
#include <unordered_map>

#include <SDL2/SDL_image.h>

class SpriteComponent;

class DeadFrog : public Actor
{
public:
	DeadFrog(Game* game);

	SpriteComponent* GetSpriteComp() { return mSpriteC; }

protected:
	void OnUpdate(float deltaTime) override;

private:
	SpriteComponent* mSpriteC;

	float mLifetime;
};