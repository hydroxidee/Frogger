//
//  Main.cpp
//  Game-mac
//
//  Created by Sanjay Madhav on 5/31/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Game.h"

#include <iostream>

int main(int argc, char** argv)
{
	// TODO
	Game game;
	bool initialized = game.Initialize();

	if (initialized)
	{
		game.RunLoop();
	}

	game.ShutDown();
	return 0;
}
