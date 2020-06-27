#include "GameLoop.h"
#include <SDL_image.h>

using namespace sc;

GameLoop::GameLoop(GameState& state)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	this->gameState = &state;
	this->gameModule = nullptr;
}

GameLoop::~GameLoop()
{
	SetModule(nullptr);
	IMG_Quit();
	SDL_Quit();
}

void GameLoop::Run()
{
	SDL_Window* window = SDL_CreateWindow("Segunda Cinefila", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 240, 0); // SDL_WINDOW_FULLSCREEN
	SDL_ShowCursor(0);
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	bool running = true;
	while (running)
	{
		SDL_RenderClear(render);
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				running = false;
			else if (event.type == SDL_KEYDOWN)
			{
				if (gameModule != nullptr)
				{
					ModuleResult moduleResult;
					gameModule->HandleInput(event.key, moduleResult);
					HandleModuleResult(moduleResult);
				}
			}
		}
		if (gameModule != nullptr)
		{
			ModuleResult moduleResult;
			gameModule->Update(*gameState, render, moduleResult);
			HandleModuleResult(moduleResult);
		}
		SDL_RenderPresent(render);
		SDL_Delay(100); // todo fps
	}
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	render = nullptr;
}

void GameLoop::SetModule(GameModule* gameModule)
{
	if (this->gameModule != gameModule)
	{
		if (this->gameModule != nullptr)
		{
			this->gameModule->Finish(*gameState);
			delete this->gameModule;
		}
		this->gameModule = gameModule;
		if (this->gameModule != nullptr)
			this->gameModule->Start(*gameState);
	}
}

void GameLoop::HandleModuleResult(ModuleResult& moduleResult)
{
	if (moduleResult.NextGameModule != nullptr)
		SetModule(moduleResult.NextGameModule);
}
