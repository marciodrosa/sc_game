#pragma once

#include <iostream>
#include <SDL.h>
#include "GameModule.h"
#include "GameState.h"
#include "ModuleResult.h"

namespace sc
{
	/** Main game loop, handles the window and events. */
	class GameLoop
	{
	public:
		GameLoop(GameState& state);
		virtual ~GameLoop();
		void Run();
		void SetModule(GameModule* gameModule);

	private:
		GameState* gameState;
		GameModule* gameModule;
		SDL_Renderer* render;
		bool running;
		void HandleModuleResult(ModuleResult& moduleResult);
	};
}
