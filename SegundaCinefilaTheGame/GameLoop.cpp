#include "GameLoop.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "ImagesProvider.h"
#include "Constants.h"

using namespace sc;

GameLoop::GameLoop(GameState& state)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	this->gameState = &state;
	this->gameModule = nullptr;
	this->running = false;
}

GameLoop::~GameLoop()
{
	SetModule(nullptr);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
	ImagesProvider::Release();
}

void GameLoop::Run()
{
	SDL_Window* window = SDL_CreateWindow("Segunda Cinefila", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SC_SCREEN_WIDTH, SC_SCREEN_HEIGHT, 0); // SDL_WINDOW_FULLSCREEN
	SDL_ShowCursor(0);
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	ImagesProvider::Get()->LoadImages();
	running = true;
	while (running)
	{
		unsigned int timeStart = SDL_GetTicks();
		SDL_RenderClear(render);
		PoolEvents();
		if (gameModule != nullptr)
		{
			ModuleResult moduleResult;
			gameModule->Update(*gameState, render, moduleResult);
			HandleModuleResult(moduleResult);
		}
		SDL_RenderPresent(render);
		unsigned int timeEnd = SDL_GetTicks();
		unsigned int frameTime = timeEnd < timeStart;
		if (frameTime < 33)
			SDL_Delay(33 - frameTime);
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
	if (moduleResult.FinishGame)
		running = false;
}

void GameLoop::PoolEvents()
{
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
				gameModule->HandleInput(*gameState, event.key, moduleResult);
				HandleModuleResult(moduleResult);
			}
		}
	}
}
