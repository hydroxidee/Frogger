#pragma once

#include "SDL2/SDL.h"
#include <string>
#include <unordered_map>
#include <vector>

class Actor;
class SpriteComponent;
class Vehicle;
class Frog;
class Log;

class Game
{
public:
	Game();
	bool Initialize();
	void ShutDown();
	void RunLoop();

	void AddActor(Actor* actor);
	void RemoveActor(Actor* actor);

	void AddSprite(SpriteComponent* sprite);
	void RemoveSprite(SpriteComponent* sprite);

	SDL_Texture* GetTexture(std::string fileName);

	void AddVehicle(Vehicle* vehicle);
	void RemoveVehicle(Vehicle* vehicle);
	std::vector<Vehicle*>& GetVehicles() { return mVehicles; }

	void AddLog(Log* log);
	void RemoveLog(Log* log);
	std::vector<Log*>& GetLogs() { return mLogs; }

	Frog* GetFrog() { return mFrog; }
	Actor* GetGoal() { return mGoal; }

private:
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	bool mContGame;

	const int WINDOW_WIDTH = 448;
	const int WINDOW_HEIGHT = 512;

	const float MAX_DELTA_TIME = 0.033f;

	Uint32 mPrevTime;

	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	void LoadData();
	void UnloadData();

	std::vector<Actor*> mActors;
	std::unordered_map<std::string, SDL_Texture*> mTextures;
	std::vector<SpriteComponent*> mSprites;

	std::vector<Vehicle*> mVehicles;
	std::vector<Log*> mLogs;
	Frog* mFrog;

	Actor* mGoal;
};