#include <iostream>
#include <SDL.h>
#include "GameLoop.h"
#include "GameState.h"
#include "Character.h"
#include "TitleModule.h"

using namespace sc;

int main(int argc, char* argv[])
{
	GameState gameState;
	gameState.Characters = Character::GetCharacters();
	GameLoop gameLoop(gameState);
	gameLoop.SetModule(new TitleModule);
	gameLoop.Run();
	return 0;
}
