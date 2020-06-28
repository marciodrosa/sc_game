#pragma once

#include "GameModule.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>

namespace sc
{
	/** Ending module that shows the ending line of the selected character. */
	class EndingModule : public GameModule
	{
	public:
		EndingModule();
		virtual ~EndingModule();
		void Start(GameState& state) override;
		void Update(GameState& state, SDL_Renderer* render, ModuleResult& result) override;
		void Finish(GameState& state) override;
		void HandleInput(GameState& state, SDL_KeyboardEvent& inputEvent, ModuleResult& result) override;

	private:
		SDL_Texture* characterTexture;
		SDL_Surface* mainLabelSurface;
		SDL_Texture* mainLabelTexture;
		SDL_Surface* characterLabelSurface;
		SDL_Texture* characterLabelTexture;
		SDL_Surface* theEndLabelSurface;
		SDL_Texture* theEndLabelTexture;
		TTF_Font* font;
	};
}
