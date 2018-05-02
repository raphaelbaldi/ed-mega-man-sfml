#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>

#include "Game.h"
#include "PlayState.h"

int main(int argc, char **argv)
{
    cgf::Game game(5,30);

	game.init("Mega Man Clone",256,240,false);

    game.changeState(PlayState::instance());

	while(game.isRunning())
	{
		game.handleEvents();
		game.update();
		game.draw();
	}

	// cleanup the engine
	game.clean();

    return 0;
}
