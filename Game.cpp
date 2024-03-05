//
//  Game.cpp
//  Game-mac
//
//  Created by Sanjay Madhav on 5/31/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Game.h"
#include "Actor.h"
#include "Random.h"
#include "SpriteComponent.h"
#include <fstream>
#include <SDL2/SDL_image.h>
#include <algorithm>

#include "Frog.h"
#include "Log.h"
#include "Vehicle.h"

Game::Game()
{
	mWindow = nullptr;
	mRenderer = nullptr;
	mContGame = true;

	mPrevTime = 0;
	mFrog = nullptr;
	mGoal = nullptr;
}

bool Game::Initialize()
{
	Random::Init();
	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0)
	{
		return false;
	}

	//creates window
	mWindow = SDL_CreateWindow("Frogger", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							   WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	mRenderer = SDL_CreateRenderer(mWindow, -1,
								   SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	IMG_Init(IMG_INIT_PNG);
	LoadData();

	return mWindow && mRenderer;
}

void Game::RunLoop()
{
	while (mContGame)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ShutDown()
{
	UnloadData();
	IMG_Quit();
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::ProcessInput()
{
	//checks if player tries to exit window
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mContGame = false;
		}
	}

	//checks what key the player presses
	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
	//esc key
	if (keyboardState[SDL_SCANCODE_ESCAPE])
	{
		mContGame = false;
	}

	//updates each actor
	std::vector<Actor*> actors = mActors;
	for (auto a : actors)
	{
		a->ProcessInput(keyboardState);
	}
}

void Game::UpdateGame()
{
	//frame limiting
	Uint32 currTime = SDL_GetTicks();
	Uint32 timePassed = currTime - mPrevTime;
	while (timePassed < 16.0f)
	{
		currTime = SDL_GetTicks();
		timePassed = currTime - mPrevTime;
	}

	//delta time calculation
	float deltaTime = timePassed / 1000.0f;

	//capping max delta time
	if (deltaTime > MAX_DELTA_TIME)
	{
		deltaTime = MAX_DELTA_TIME;
	}

	mPrevTime = currTime;

	//updates actors
	std::vector<Actor*> actors = mActors;
	for (auto a : actors)
	{
		a->Update(deltaTime);
	}

	//gets actors in destroy state
	std::vector<Actor*> destroyActors;
	for (auto a : actors)
	{
		if (a->GetState() == ActorState::Destroy)
		{
			destroyActors.push_back(a);
		}
	}

	//deletes destroy state actors
	for (auto a : destroyActors)
	{
		delete a;
	}
}

void Game::GenerateOutput()
{
	//clears screen
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mRenderer);

	for (auto s : mSprites)
	{
		if (s->IsVisible())
		{
			s->Draw(mRenderer);
		}
	}
	//render
	SDL_RenderPresent(mRenderer);
}

void Game::AddActor(Actor* actor)
{
	mActors.push_back(actor);
}

void Game::RemoveActor(Actor* actor)
{
	auto it = std::find(mActors.begin(), mActors.end(), actor);

	if (it != mActors.end())
	{
		mActors.erase(it);
	}
}

void Game::AddSprite(SpriteComponent* sprite)
{
	mSprites.push_back(sprite);

	std::sort(mSprites.begin(), mSprites.end(), [](SpriteComponent* a, SpriteComponent* b) {
		return a->GetDrawOrder() < b->GetDrawOrder();
	});
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	auto it = std::find(mSprites.begin(), mSprites.end(), sprite);

	if (it != mSprites.end())
	{
		mSprites.erase(it);
	}
}

SDL_Texture* Game::GetTexture(std::string fileName)
{
	//texture already exists
	if (mTextures.find(fileName) != mTextures.end())
	{
		return mTextures.at(fileName);
	}

	//create texture
	SDL_Surface* surface = IMG_Load(fileName.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surface);
	SDL_FreeSurface(surface);

	if (surface == nullptr)
	{
		SDL_Log("SDL could not load texture file");
		return nullptr;
	}

	mTextures.insert({fileName, texture});

	return texture;
}

void Game::LoadData()
{
	//background
	Actor* background = new Actor(this);
	background->SetPosition(Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
	SpriteComponent* sc = new SpriteComponent(background);
	sc->SetTexture(GetTexture("Assets/Background.png"));

	std::fstream file;
	file.open("Assets/Level.txt");
	std::string temp;

	float x = 0.0f;
	float y = 80.0f;
	int row = 0;
	while (getline(file, temp))
	{
		for (auto c : temp)
		{
			x = x + 32.0f;
			if (c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == 'T')
			{
				Vehicle* car = new Vehicle(this, c);
				car->SetPosition(Vector2(x, y));
				car->SetDirection(row);
			}
			else if (c == 'X' || c == 'Y' || c == 'Z')
			{
				Log* log = new Log(this, c);
				log->SetPosition(Vector2(x, y));
				log->SetDirection(row);
			}
			else if (c == 'F')
			{
				Frog* frog = new Frog(this);
				frog->SetPosition(Vector2(x, y));
				frog->GetSpriteComp()->SetTexture(GetTexture("Assets/Frog.png"));
				mFrog = frog;
			}
			else if (c == 'G')
			{
				mGoal = new Actor(this);
				mGoal->SetPosition(Vector2(x, y));
				mGoal->GetCollisionComp()->SetHeight(32.0f);
				mGoal->GetCollisionComp()->SetWidth(32.0f);
			}
		}

		row = row + 1;

		x = 0.0f;
		y = y + 32.0f;
	}
}

void Game::UnloadData()
{
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	for (auto t : mTextures)
	{
		SDL_DestroyTexture(t.second);
	}
	mTextures.clear();
}

void Game::AddVehicle(Vehicle* vehicle)
{
	mVehicles.push_back(vehicle);
}

void Game::RemoveVehicle(Vehicle* vehicle)
{
	auto it = std::find(mVehicles.begin(), mVehicles.end(), vehicle);

	if (it != mVehicles.end())
	{
		mVehicles.erase(it);
	}
}

void Game::AddLog(Log* log)
{
	mLogs.push_back(log);
}

void Game::RemoveLog(Log* log)
{
	auto it = std::find(mLogs.begin(), mLogs.end(), log);

	if (it != mLogs.end())
	{
		mLogs.erase(it);
	}
}
