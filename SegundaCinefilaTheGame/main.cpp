#include <iostream>
#include <SDL.h>
#include "GameLoop.h"
#include "GameState.h"
#include "TitleModule.h"

using namespace sc;

int main(int argc, char* argv[])
{
	GameState gameState;
	GameLoop gameLoop(gameState);
	gameLoop.SetModule(new TitleModule);
	gameLoop.Run();
	return 0;
}
